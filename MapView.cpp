/*
/ MapView.cpp
/ a panel to show the Map
/
/ version 1.0, 2009 February 3
/
/ Author: Sandro Furieri a-furieri@lqt.it
/
/ Copyright (C) 2009  Alessandro Furieri
/
/    This program is free software: you can redistribute it and/or modify
/    it under the terms of the GNU General Public License as published by
/    the Free Software Foundation, either version 3 of the License, or
/    (at your option) any later version.
/
/    This program is distributed in the hope that it will be useful,
/    but WITHOUT ANY WARRANTY; without even the implied warranty of
/    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/    GNU General Public License for more details.
/
/    You should have received a copy of the GNU General Public License
/    along with this program.  If not, see <http://www.gnu.org/licenses/>.
/
*/

#include "Classdef.h"
#include "wx/mstream.h"
#include "wx/pen.h"
#include "wx/settings.h"
#include <float.h>

#include <spatialite.h>
#include <spatialite/gaiaexif.h>

//
// ICONs in XPM format [universally portable]
//
#include "icons/splash_screen.xpm"
#include "icons/center.xpm"
#include "icons/checked_brush.xpm"
#include "icons/up.xpm"
#include "icons/down.xpm"
#include "icons/left.xpm"
#include "icons/right.xpm"
#include "icons/zoom_min.xpm"
#include "icons/zoom_max.xpm"
#include "icons/zoom_in.xpm"
#include "icons/zoom_out.xpm"
#include "icons/map_frame.xpm"
#include "icons/line_meter.xpm"
#include "icons/polygon_meter.xpm"
#include "icons/pencil.xpm"
#include "icons/pencil_add.xpm"
#include "icons/pencil_delete.xpm"
#include "icons/pencil_go.xpm"
#include "icons/cut_blue.xpm"
#include "icons/asterisk.xpm"
#include "icons/edit_no.xpm"
#include "icons/edit_yes.xpm"
#include "icons/ident_on.xpm"
#include "icons/crosshair.xpm"
#include "icons/node_from.xpm"
#include "icons/node_to.xpm"

MyMapView::MyMapView(MyFrame * parent, wxWindowID id):
wxPanel(parent, id, wxDefaultPosition, wxSize(440, 480),
        wxBORDER_SUNKEN | wxWANTS_CHARS)
{
//
// constructor: a frame to show the Map
//
  MainFrame = parent;
  UnsetMapFrameSelection();
  SplashMode = true;
  SplashLogo = new wxBitmap(splash_screen_xpm);
  BitmapWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
  BitmapHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
  MapBitmap = wxBitmap(BitmapWidth, BitmapHeight, -1);
  DynamicMapBitmap = wxBitmap(BitmapWidth, BitmapHeight, -1);
  ScreenBitmap = wxBitmap(BitmapWidth, BitmapHeight, -1);
  MapTip = NULL;
  RoutingMarker = false;
  TimerMouseMove = NULL;
  TimerMouseWheel = NULL;
  TimerIdentify = NULL;
  TimerMarker = NULL;
  CurrentDraw = NULL;
  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  CurrentVertexIndex = -1;
  CurrentSegmentIndex = -1;
  OkCandidateEntity = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CandidateEntityPrimaryKey = -1;
  CandidateEntityGeometry = NULL;
  IsCurrentRoutingAlgorithmAStar = false;
  WheelTics = 0;
  MapMinX = DBL_MAX;
  MapMinY = DBL_MAX;
  MapMaxX = 0.0 - DBL_MAX;
  MapMaxY = 0.0 - DBL_MAX;
  ValidMapExtent = false;
  FrameWidth = 0;
  FrameHeight = 0;
  FrameCenterX = DBL_MAX;
  FrameCenterY = DBL_MAX;
  FrameRadius = 0.0;
  FrameMinX = DBL_MAX;
  FrameMinY = DBL_MAX;
  FrameMaxX = 0.0 - DBL_MAX;
  FrameMaxY = 0.0 - DBL_MAX;
  PixelRatio = DBL_MAX;
  CurrentScale = 0;
  DragStartX = -1;
  DragStartY = -1;
  LastDragX = -1;
  LastDragY = -1;
  ValidMap = false;
  LastZoom = 1;

  CheckedBrush.SetStipple(wxBitmap(checked_brush_xpm));
  CheckedBrush.SetStyle(wxSTIPPLE);

  wxImage crossImage = wxBitmap(crosshair_xpm).ConvertToImage();
#ifdef __WXMSW__
// setting up a WINDOWS cursor
  crossImage.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 8);
  crossImage.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 8);
  CursorCross = wxCursor(crossImage);
#else
#ifdef __WXMAC__
// setting up a MacOsX cursor
  crossImage.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 8);
  crossImage.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 8);
  CursorCross = wxCursor(crossImage);
#else
// setting up an UNIX -likecursor
  int row;
  int col;
  unsigned short bits[16];
  unsigned short mask[16];
  for (row = 0; row < 16; row++)
    {
      bits[row] = 0x0000;
      mask[row] = 0x0000;
      for (col = 0; col < 16; col++)
        {
          unsigned char pixel = crossImage.GetRed(col, row);
          if (pixel == 0)
            {
              switch (col)
                {
                  case 0:
                    bits[row] |= 0x8000;
                    break;
                  case 1:
                    bits[row] |= 0x4000;
                    break;
                  case 2:
                    bits[row] |= 0x2000;
                    break;
                  case 3:
                    bits[row] |= 0x1000;
                    break;
                  case 4:
                    bits[row] |= 0x0800;
                    break;
                  case 5:
                    bits[row] |= 0x0400;
                    break;
                  case 6:
                    bits[row] |= 0x0200;
                    break;
                  case 7:
                    bits[row] |= 0x0100;
                    break;
                  case 8:
                    bits[row] |= 0x0080;
                    break;
                  case 9:
                    bits[row] |= 0x0040;
                    break;
                  case 10:
                    bits[row] |= 0x0020;
                    break;
                  case 11:
                    bits[row] |= 0x0010;
                    break;
                  case 12:
                    bits[row] |= 0x0008;
                    break;
                  case 13:
                    bits[row] |= 0x0004;
                    break;
                  case 14:
                    bits[row] |= 0x0002;
                    break;
                  case 15:
                    bits[row] |= 0x0001;
                    break;
                };
              switch (col)
                {
                  case 0:
                    mask[row] |= 0x8000;
                    break;
                  case 1:
                    mask[row] |= 0x4000;
                    break;
                  case 2:
                    mask[row] |= 0x2000;
                    break;
                  case 3:
                    mask[row] |= 0x1000;
                    break;
                  case 4:
                    mask[row] |= 0x0800;
                    break;
                  case 5:
                    mask[row] |= 0x0400;
                    break;
                  case 6:
                    mask[row] |= 0x0200;
                    break;
                  case 7:
                    mask[row] |= 0x0100;
                    break;
                  case 8:
                    mask[row] |= 0x0080;
                    break;
                  case 9:
                    mask[row] |= 0x0040;
                    break;
                  case 10:
                    mask[row] |= 0x0020;
                    break;
                  case 11:
                    mask[row] |= 0x0010;
                    break;
                  case 12:
                    mask[row] |= 0x0008;
                    break;
                  case 13:
                    mask[row] |= 0x0004;
                    break;
                  case 14:
                    mask[row] |= 0x0002;
                    break;
                  case 15:
                    mask[row] |= 0x0001;
                    break;
                };
            }
          if (pixel == 255)
            {
              switch (col)
                {
                  case 0:
                    mask[row] |= 0x8000;
                    break;
                  case 1:
                    mask[row] |= 0x4000;
                    break;
                  case 2:
                    mask[row] |= 0x2000;
                    break;
                  case 3:
                    mask[row] |= 0x1000;
                    break;
                  case 4:
                    mask[row] |= 0x0800;
                    break;
                  case 5:
                    mask[row] |= 0x0400;
                    break;
                  case 6:
                    mask[row] |= 0x0200;
                    break;
                  case 7:
                    mask[row] |= 0x0100;
                    break;
                  case 8:
                    mask[row] |= 0x0080;
                    break;
                  case 9:
                    mask[row] |= 0x0040;
                    break;
                  case 10:
                    mask[row] |= 0x0020;
                    break;
                  case 11:
                    mask[row] |= 0x0010;
                    break;
                  case 12:
                    mask[row] |= 0x0008;
                    break;
                  case 13:
                    mask[row] |= 0x0004;
                    break;
                  case 14:
                    mask[row] |= 0x0002;
                    break;
                  case 15:
                    mask[row] |= 0x0001;
                    break;
                };
            }
        }
    }
  CursorCross =
    wxCursor((char *) bits, 16, 16, 8, 8, (char *) mask, wxWHITE, wxBLACK);
#endif
#endif
  CursorHand = wxCursor(wxCURSOR_HAND);
  SetCursor(CursorCross);

  wxCursor arrow = wxCursor(wxCURSOR_ARROW);
  //Zoom.Create(this, ID_Zoom, CurrentZoomLevel, CurrentZoomLevel, ZoomLevelsCount - 1, wxDefaultPosition, wxDefaultSize,
  Zoom.Create(this, ID_Zoom, 100, 1, 100, wxDefaultPosition, wxDefaultSize,
              wxSL_VERTICAL);
  Zoom.SetCursor(arrow);
  Center.Create(this, ID_Center, wxBitmap(center_xpm));
  Center.SetCursor(arrow);
  Up.Create(this, ID_Up, wxBitmap(up_xpm));
  Up.SetCursor(arrow);
  Down.Create(this, ID_Down, wxBitmap(down_xpm));
  Down.SetCursor(arrow);
  Left.Create(this, ID_Left, wxBitmap(left_xpm));
  Left.SetCursor(arrow);
  Right.Create(this, ID_Right, wxBitmap(right_xpm));
  Right.SetCursor(arrow);
  ZoomMin.Create(this, ID_ZoomMin, wxBitmap(zoom_min_xpm));
  ZoomMin.SetCursor(arrow);
  ZoomMax.Create(this, ID_ZoomMax, wxBitmap(zoom_max_xpm));
  ZoomMax.SetCursor(arrow);

// setting up event handlers
  Connect(wxID_ANY, wxEVT_ERASE_BACKGROUND,
          (wxObjectEventFunction) & MyMapView::OnEraseBackground);
  Connect(wxID_ANY, wxEVT_SIZE, (wxObjectEventFunction) & MyMapView::OnSize);
  Connect(wxID_ANY, wxEVT_PAINT, (wxObjectEventFunction) & MyMapView::OnPaint);
  Connect(wxID_ANY, wxEVT_MOUSEWHEEL,
          wxMouseEventHandler(MyMapView::OnMouseWheel), NULL, this);
  Connect(wxID_ANY, wxEVT_MOTION, wxMouseEventHandler(MyMapView::OnMouseMove),
          NULL, this);
  Connect(wxID_ANY, wxEVT_LEFT_DOWN,
          wxMouseEventHandler(MyMapView::OnMouseClick), NULL, this);
  Connect(wxID_ANY, wxEVT_LEFT_DCLICK,
          wxMouseEventHandler(MyMapView::OnMouseDoubleClick), NULL, this);
  Connect(wxID_ANY, wxEVT_LEFT_UP,
          wxMouseEventHandler(MyMapView::OnMouseDragStop), NULL, this);
  Connect(wxID_ANY, wxEVT_RIGHT_UP,
          wxMouseEventHandler(MyMapView::OnMouseRightClick), NULL, this);
  Connect(wxID_ANY, wxEVT_LEAVE_WINDOW,
          wxMouseEventHandler(MyMapView::OnMouseDragStop), NULL, this);
  Connect(ID_MOUSE_TIMER, wxEVT_TIMER,
          wxTimerEventHandler(MyMapView::OnTimerMouseMove), NULL, this);
  Connect(ID_WHEEL_TIMER, wxEVT_TIMER,
          wxTimerEventHandler(MyMapView::OnTimerMouseWheel), NULL, this);
  Connect(ID_IDENTIFY_TIMER, wxEVT_TIMER,
          wxTimerEventHandler(MyMapView::OnTimerIdentify), NULL, this);
  Connect(ID_MARKER_TIMER, wxEVT_TIMER,
          wxTimerEventHandler(MyMapView::OnTimerMarker), NULL, this);

  Connect(wxID_ANY, wxEVT_MOUSE_CAPTURE_LOST,
          (wxObjectEventFunction) & MyMapView::OnCapturedMouseLost);

  Connect(ID_Zoom, wxEVT_SCROLL_THUMBRELEASE,
          (wxObjectEventFunction) & MyMapView::OnZoom);
  Connect(ID_Zoom, wxEVT_SCROLL_CHANGED,
          (wxObjectEventFunction) & MyMapView::OnZoom);
  Connect(ID_Center, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & MyMapView::OnCenter);
  Connect(ID_Up, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & MyMapView::OnUp);
  Connect(ID_Down, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & MyMapView::OnDown);
  Connect(ID_Left, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & MyMapView::OnLeft);
  Connect(ID_Right, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & MyMapView::OnRight);
  Connect(ID_ZoomMin, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & MyMapView::OnZoomMinus);
  Connect(ID_ZoomMax, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & MyMapView::OnZoomPlus);
  Connect(ID_Center, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnCenter);
  Connect(ID_Up, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnUp);
  Connect(ID_Down, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnDown);
  Connect(ID_Left, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnLeft);
  Connect(ID_Right, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnRight);
  Connect(ID_MicroUp, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnMicroUp);
  Connect(ID_MicroDown, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnMicroDown);
  Connect(ID_MicroLeft, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnMicroLeft);
  Connect(ID_MicroRight, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnMicroRight);
  Connect(ID_ZoomMicroIn, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnZoomMicroIn);
  Connect(ID_ZoomMicroOut, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnZoomMicroOut);
  Connect(ID_ZoomIn, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnZoomIn);
  Connect(ID_ZoomOut, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnZoomOut);
  Connect(ID_DrawAbort, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnDrawAbort);
  Connect(ID_DrawStop, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnDrawStop);
  Connect(ID_DrawUndo, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnDrawUndo);
  Connect(ID_EditMode, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnCmdEditMode);
  Connect(ID_Identify, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnCmdIdentify);
  Connect(ID_NodeFrom, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnCmdNodeFrom);
  Connect(ID_NodeTo, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnCmdNodeTo);
  Connect(ID_ReturnTrip, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnCmdReturnTrip);
  Connect(ID_RouteClear, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnCmdRouteClear);
  Connect(ID_RoutingAlgorithm, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyMapView::OnCmdRoutingAlgorithm);

// setting up an ACCELERATOR TABLE for Keyboard shortcuts
  wxAcceleratorEntry accelEntries[17];
  accelEntries[0].Set(wxACCEL_NORMAL, WXK_HOME, ID_Center);
  accelEntries[1].Set(wxACCEL_NORMAL, WXK_UP, ID_MicroUp);
  accelEntries[2].Set(wxACCEL_SHIFT, WXK_UP, ID_Up);
  accelEntries[3].Set(wxACCEL_NORMAL, WXK_DOWN, ID_MicroDown);
  accelEntries[4].Set(wxACCEL_SHIFT, WXK_DOWN, ID_Down);
  accelEntries[5].Set(wxACCEL_NORMAL, WXK_LEFT, ID_MicroLeft);
  accelEntries[6].Set(wxACCEL_SHIFT, WXK_LEFT, ID_Left);
  accelEntries[7].Set(wxACCEL_NORMAL, WXK_RIGHT, ID_MicroRight);
  accelEntries[8].Set(wxACCEL_SHIFT, WXK_RIGHT, ID_Right);
  accelEntries[9].Set(wxACCEL_NORMAL, WXK_PAGEUP, ID_ZoomMicroIn);
  accelEntries[10].Set(wxACCEL_SHIFT, WXK_PAGEUP, ID_ZoomIn);
  accelEntries[11].Set(wxACCEL_NORMAL, WXK_PAGEDOWN, ID_ZoomMicroOut);
  accelEntries[12].Set(wxACCEL_SHIFT, WXK_PAGEDOWN, ID_ZoomOut);
  accelEntries[13].Set(wxACCEL_NORMAL, WXK_DELETE, ID_DrawAbort);
  accelEntries[14].Set(wxACCEL_CTRL, (int) 'U', ID_DrawUndo);
  accelEntries[15].Set(wxACCEL_NORMAL, WXK_END, ID_DrawStop);
  accelEntries[16].Set(wxACCEL_NORMAL, WXK_RETURN, ID_Identify);
  wxAcceleratorTable accelTbl(17, accelEntries);
  SetAcceleratorTable(accelTbl);
}

MyMapView::~MyMapView()
{
  if (SplashLogo)
    delete SplashLogo;
  if (TimerMouseMove)
    {
      TimerMouseMove->Stop();
      delete TimerMouseMove;
    }
  if (TimerMouseWheel)
    {
      TimerMouseWheel->Stop();
      delete TimerMouseWheel;
    }
  if (TimerIdentify)
    {
      TimerIdentify->Stop();
      delete TimerIdentify;
    }
  if (TimerMarker)
    {
      TimerMarker->Stop();
      delete TimerMarker;
    }
  ClearMapTip();
  if (CurrentDraw)
    gaiaFreeDynamicLine(CurrentDraw);
  if (CandidateEntityGeometry)
    gaiaFreeGeomColl(CandidateEntityGeometry);
}

void MyMapView::SetMapFrameFullExtent()
{
// setting the Map Frame to Full Extent
  MapFrame1x = MapMinX;
  MapFrame1y = MapMinY;
  OkMapFrame1 = true;
  MapFrame2x = MapMaxX;
  MapFrame2y = MapMaxY;
  OkMapFrame2 = true;
// refreshing the map
  DynamicDraw(false);
  MainFrame->EnableMapOutput();
}

void MyMapView::UnsetMapFrameSelection()
{
// invalidating the current Map Frame selection
  OkMapFrame1 = false;
  OkMapFrame2 = false;
  IsCapturedMouse = false;
}

bool MyMapView::IsMapFrameSelection()
{
// checking if the current Map Frame Selection is set
  if (OkMapFrame1 == true && OkMapFrame2 == true)
    return true;
  return false;
}

bool MyMapView::GetMapFrameSelection(double *minX, double *minY, double *maxX,
                                     double *maxY)
{
// computing the current Map Frame selection [if a valid one is set]
  double min_x = MapFrame1x;
  double min_y = MapFrame1y;
  double max_x = MapFrame2x;
  double max_y = MapFrame2y;
  if (IsMapFrameSelection() == false)
    return false;
  if (min_x > MapFrame2x)
    min_x = MapFrame2x;
  if (min_y > MapFrame2y)
    min_y = MapFrame2y;
  if (max_x < MapFrame1x)
    max_x = MapFrame1x;
  if (max_y < MapFrame1y)
    max_y = MapFrame1y;
  *minX = min_x;
  *minY = min_y;
  *maxX = max_x;
  *maxY = max_y;
  return true;
}

bool MyMapView::GetMapFrameSelection(double x, double y, double *minX,
                                     double *minY, double *maxX, double *maxY)
{
// computing the dynamic Map Frame selection [if a valid one is set]
  double min_x = MapFrame1x;
  double min_y = MapFrame1y;
  double max_x = x;
  double max_y = y;
  if (OkMapFrame1 == false)
    return false;
  if (min_x > x)
    min_x = x;
  if (min_y > y)
    min_y = y;
  if (max_x < MapFrame1x)
    max_x = MapFrame1x;
  if (max_y < MapFrame1y)
    max_y = MapFrame1y;
  *minX = min_x;
  *minY = min_y;
  *maxX = max_x;
  *maxY = max_y;
  return true;
}

void MyMapView::OnCapturedMouseLost(wxMouseCaptureLostEvent & WXUNUSED(event))
{
//
// loosing the mouse capture
  UnsetMapFrameSelection();
}

void MyMapView::OnSize(wxSizeEvent & WXUNUSED(event))
{
//
// this window has changed its size
//

// resizing and repositioning the Zoom slider
  wxSize sz = GetClientSize();

  int bx = 4;
  int by = 4;
  Center.SetSize(bx + 32, by + 32, 30, 30);
  Up.SetSize(bx + 32, by, 30, 30);
  Down.SetSize(bx + 32, by + 64, 30, 30);
  Left.SetSize(bx, by + 32, 30, 30);
  Right.SetSize(bx + 64, by + 32, 30, 30);

  ZoomMax.SetSize(bx + 32, by + 110, 30, 30);

  wxSize szZoom = Zoom.GetSize();
  Zoom.SetSize(bx + 46 - (szZoom.GetWidth() / 2), by + 142, szZoom.GetWidth(),
               120);

  ZoomMin.SetSize(bx + 32, by + 264, 30, 30);

// refreshing the map
  PrepareMap();
}

void MyMapView::OnPaint(wxPaintEvent & WXUNUSED(event))
{
//
// this window needs to be repainted
//
  wxPaintDC dc(this);
  if (SplashMode == true)
    {
      // drawing the Splash Logo
      wxSize sz = GetClientSize();
      int cx = sz.GetWidth() / 2;
      int cy = sz.GetHeight() / 2;
      int x;
      int y;
      int width = SplashLogo->GetWidth();
      int height = SplashLogo->GetHeight();
      while (width > (sz.GetWidth() / 2) || height > (sz.GetHeight() / 2))
        {
          width /= 2;
          height /= 2;
        }
      wxImage img = SplashLogo->ConvertToImage();
      wxImage logo;
      if (width == SplashLogo->GetWidth() && height == SplashLogo->GetHeight())
        logo = img.Copy();
      else
        logo = img.Scale(width, height, wxIMAGE_QUALITY_HIGH);
      x = cx - (width / 2);
      y = cy - (height / 2);
      wxGraphicsContext *gr = wxGraphicsContext::Create(dc);
      wxGraphicsBrush brush =
        gr->CreateLinearGradientBrush(0, 0, sz.GetWidth(), sz.GetHeight(),
                                      wxColour(255, 255, 0), wxColour(0, 64,
                                                                      255));
      gr->SetBrush(brush);
      gr->SetPen(wxPen(wxColour(255, 255, 255), 50));
      gr->DrawRoundedRectangle(0, 0, sz.GetWidth(), sz.GetHeight(), 50);
      gr->DrawBitmap(logo, x, y, width, height);
      delete gr;
      return;
    }
  if (dc.IsOk() && ScreenBitmap.IsOk())
    {
      wxMemoryDC *memDC = new wxMemoryDC(ScreenBitmap);
      dc.Blit(0, 0, BitmapWidth, BitmapHeight, memDC, 0, 0);
      delete memDC;
    }
}

void MyMapView::OnMouseRightClick(wxMouseEvent & event)
{
//
// MOUSE Click Right - event handler
// 
  SetFocus();
  wxMenu *menu = new wxMenu;
  wxPoint pt = wxPoint(event.GetX(), event.GetY());
  wxMenu *subMenu1 = new wxMenu();
  wxMenuItem *menuItem =
    new wxMenuItem(subMenu1, ID_Center, wxT("Full extent"));
  menuItem->SetBitmap(wxBitmap(center_xpm));
  subMenu1->Append(menuItem);
  subMenu1->AppendSeparator();
  menuItem = new wxMenuItem(subMenu1, ID_MicroUp, wxT("Up"));
  menuItem->SetBitmap(wxBitmap(up_xpm));
  subMenu1->Append(menuItem);
  menuItem = new wxMenuItem(subMenu1, ID_MicroDown, wxT("Down"));
  menuItem->SetBitmap(wxBitmap(down_xpm));
  subMenu1->Append(menuItem);
  menuItem = new wxMenuItem(subMenu1, ID_MicroLeft, wxT("Left"));
  menuItem->SetBitmap(wxBitmap(left_xpm));
  subMenu1->Append(menuItem);
  menuItem = new wxMenuItem(subMenu1, ID_MicroRight, wxT("Right"));
  menuItem->SetBitmap(wxBitmap(right_xpm));
  subMenu1->Append(menuItem);
  subMenu1->AppendSeparator();
  menuItem = new wxMenuItem(subMenu1, ID_ZoomMicroIn, wxT("Zoom In"));
  menuItem->SetBitmap(wxBitmap(zoom_in_xpm));
  subMenu1->Append(menuItem);
  menuItem = new wxMenuItem(subMenu1, ID_ZoomMicroOut, wxT("Zoom Out"));
  menuItem->SetBitmap(wxBitmap(zoom_out_xpm));
  subMenu1->Append(menuItem);
  menu->AppendSubMenu(subMenu1, wxT("&Navigation"));
  if (MainFrame->IsDrawActive() == true)
    {
      // draw mode is currently active
      wxMenu *subMenu2 = new wxMenu();
      menuItem =
        new wxMenuItem(subMenu2, ID_DrawAbort,
                       wxT("Current draw op &Abort [DEL]"), wxT(""),
                       wxITEM_CHECK);
      subMenu2->Append(menuItem);
      menuItem =
        new wxMenuItem(subMenu2, ID_DrawStop, wxT("Current draw op &End [END]"),
                       wxT(""), wxITEM_CHECK);
      subMenu2->Append(menuItem);
      subMenu2->AppendSeparator();
      menuItem =
        new wxMenuItem(subMenu2, ID_DrawUndo,
                       wxT("&Last inserted vertex &Undo [CTL/U]"), wxT(""),
                       wxITEM_CHECK);
      subMenu2->Append(menuItem);
      menu->AppendSubMenu(subMenu2, wxT("Current &Draw Op"));
  } else
    {
      // draw mode selection
      wxMenu *subMenu2 = new wxMenu();
      menuItem =
        new wxMenuItem(subMenu2, ID_MapFrameSel, wxT("Map Frame [selection]"),
                       wxT(""), wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(map_frame_xpm));
      menuItem->Enable(MainFrame->IsMapFrameSelectionEnabled());
      subMenu2->Append(menuItem);
      menuItem =
        new wxMenuItem(subMenu2, ID_MapFrameAll, wxT("Map Frame [full extent]"),
                       wxT(""));
      menuItem->Enable(MainFrame->IsMapFrameSelectionEnabled());
      subMenu2->Append(menuItem);
      menuItem =
        new wxMenuItem(subMenu2, ID_LineMeter, wxT("Measure &Length"), wxT(""),
                       wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(line_meter_xpm));
      menuItem->Enable(MainFrame->IsMeasureLineEnabled());
      subMenu2->Append(menuItem);
      menuItem =
        new wxMenuItem(subMenu2, ID_PolygonMeter, wxT("Measure &Area"), wxT(""),
                       wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(polygon_meter_xpm));
      menuItem->Enable(MainFrame->IsMeasurePolygonEnabled());
      subMenu2->Append(menuItem);
      subMenu2->AppendSeparator();
      menuItem =
        new wxMenuItem(subMenu2, ID_Draw, wxT("&Draw"), wxT(""), wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(pencil_xpm));
      menuItem->Enable(MainFrame->IsPencilEnabled());
      subMenu2->Append(menuItem);
      menuItem =
        new wxMenuItem(subMenu2, ID_DrawInterpolate, wxT("&Interpolate Vertex"),
                       wxT(""), wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(pencil_add_xpm));
      menuItem->Enable(MainFrame->IsPencilAddEnabled());
      subMenu2->Append(menuItem);
      menuItem =
        new wxMenuItem(subMenu2, ID_DrawDelete, wxT("&Delete Vertex"), wxT(""),
                       wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(pencil_delete_xpm));
      menuItem->Enable(MainFrame->IsPencilDeleteEnabled());
      subMenu2->Append(menuItem);
      menuItem =
        new wxMenuItem(subMenu2, ID_DrawMove, wxT("&Move Vertex"), wxT(""),
                       wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(pencil_go_xpm));
      menuItem->Enable(MainFrame->IsPencilGoEnabled());
      subMenu2->Append(menuItem);
      subMenu2->AppendSeparator();
      menuItem =
        new wxMenuItem(subMenu2, ID_DrawSplitLine, wxT("&Split Line"), wxT(""),
                       wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(cut_blue_xpm));
      menuItem->Enable(MainFrame->IsCutBlueEnabled());
      subMenu2->Append(menuItem);
      subMenu2->AppendSeparator();
      menuItem =
        new wxMenuItem(subMenu2, ID_DrawSelectMultiGeom,
                       wxT("Select Complex &Geometry"), wxT(""), wxITEM_CHECK);
      menuItem->SetBitmap(wxBitmap(asterisk_xpm));
      menuItem->Enable(MainFrame->IsAsteriskEnabled());
      subMenu2->Append(menuItem);
      menu->AppendSubMenu(subMenu2, wxT("Current &Draw Mode"));
    }
  menu->Check(ID_MapFrameSel, MainFrame->IsMapFrameSelectionChecked());
  menu->Check(ID_LineMeter, MainFrame->IsMeasureLineChecked());
  menu->Check(ID_PolygonMeter, MainFrame->IsMeasurePolygonChecked());
  menu->Check(ID_Draw, MainFrame->IsPencilChecked());
  menu->Check(ID_DrawInterpolate, MainFrame->IsPencilAddChecked());
  menu->Check(ID_DrawDelete, MainFrame->IsPencilDeleteChecked());
  menu->Check(ID_DrawMove, MainFrame->IsPencilGoChecked());
  menu->Check(ID_DrawSplitLine, MainFrame->IsCutBlueChecked());
  menu->Check(ID_DrawSelectMultiGeom, MainFrame->IsAsteriskChecked());
  menu->AppendSeparator();
  if (IsMapTipShown() == true)
    {
      menuItem = new wxMenuItem(menu, ID_Identify, wxT("Identify"));
      menuItem->SetBitmap(wxBitmap(ident_on_xpm));
      menu->Append(menuItem);
      menu->AppendSeparator();
    }
  if (MainFrame->GetActiveLayer() == NULL)
    {
      menuItem = new wxMenuItem(menu, ID_EditMode, wxT("Editing disabled"));
      menuItem->SetBitmap(wxBitmap(edit_no_xpm));
      menu->Append(menuItem);
      menuItem->Enable(false);
  } else
    {
      if (MainFrame->GetActiveLayer()->GetType() == VECTOR_LAYER)
        {
          if (MainFrame->GetActiveLayer()->IsLayerView() == true
              || MainFrame->GetActiveLayer()->IsLayerVirtual() == true
              || MainFrame->GetActiveLayer()->IsReadOnly() == true)
            {
              menuItem =
                new wxMenuItem(menu, ID_EditMode, wxT("Editing disabled"));
              menuItem->SetBitmap(wxBitmap(edit_no_xpm));
              menu->Append(menuItem);
              menuItem->Enable(false);
          } else
            {
              if (MainFrame->GetActiveLayer()->IsEditingEnabled() == true)
                {
                  menuItem =
                    new wxMenuItem(menu, ID_EditMode, wxT("Editing enabled"));
                  menuItem->SetBitmap(wxBitmap(edit_yes_xpm));
                  menu->Append(menuItem);
              } else
                {
                  menuItem =
                    new wxMenuItem(menu, ID_EditMode, wxT("Editing disabled"));
                  menuItem->SetBitmap(wxBitmap(edit_no_xpm));
                  menu->Append(menuItem);
                }
              if (MainFrame->GetActiveLayer()->GetGeometryType() ==
                  LAYER_LINESTRING
                  && MainFrame->GetActiveLayer()->IsNetwork() == true)
                menuItem->Enable(false);
            }
      } else
        {
          menuItem = new wxMenuItem(menu, ID_EditMode, wxT("Editing disabled"));
          menuItem->SetBitmap(wxBitmap(edit_no_xpm));
          menu->Append(menuItem);
          menuItem->Enable(false);
        }
    }
  if (MainFrame->GetNetwork())
    {
      menu->AppendSeparator();
      menuItem = new wxMenuItem(menu, ID_NodeFrom, wxT("Set Route Start"));
      if (MainFrame->GetNetwork()->GetNodeFrom()->IsValid() == true)
        menuItem->SetBitmap(wxBitmap(node_from_xpm));
      menu->Append(menuItem);
      menuItem->Enable(MainFrame->GetNetwork()->GetCurrentNode()->IsValid());
      menuItem = new wxMenuItem(menu, ID_NodeTo, wxT("Set Route End"));
      if (MainFrame->GetNetwork()->GetNodeTo()->IsValid() == true)
        menuItem->SetBitmap(wxBitmap(node_to_xpm));
      menu->Append(menuItem);
      menuItem->Enable(MainFrame->GetNetwork()->GetCurrentNode()->IsValid());
      menuItem = new wxMenuItem(menu, ID_ReturnTrip, wxT("Return Trip"));
      menu->Append(menuItem);
      if (!(MainFrame->GetNetwork()->GetSolution()))
        menuItem->Enable(false);
      menuItem = new wxMenuItem(menu, ID_RouteClear, wxT("Route Clear"));
      menu->Append(menuItem);
      if (!(MainFrame->GetNetwork()->GetSolution()))
        menuItem->Enable(false);
      menu->AppendSeparator();
      wxString algorithm = wxT("Change algorithm [current=");
      if (IsCurrentRoutingAlgorithmAStar == true)
        algorithm += wxT("A*]");
      else
        algorithm += wxT("Dijkstra]");
      menuItem = new wxMenuItem(menu, ID_RoutingAlgorithm, algorithm);
      menu->Append(menuItem);
      if (!(MainFrame->GetNetwork()->GetSolution()))
        menuItem->Enable(false);
    }
  PopupMenu(menu, pt);
}

void MyMapView::OnMouseClick(wxMouseEvent & event)
{
//
// MOUSE Click - event handler
// 
  SetFocus();
  if (MainFrame->IsAsteriskChecked() == true && OkCandidateEntity == true
      && CandidateEntityGeometry)
    {
      // selecting the current MultiGeometry
      MainFrame->SetCurrentEntity(CandidateEntityPrimaryKey,
                                  CandidateEntityGeometry);
      MainFrame->UnsetDrawTools();
      OkCurrentGeometry = true;
      OkCandidateEntity = false;
      CandidateEntityGeometry = NULL;
      CandidateEntityPrimaryKey = -1;
      // refreshing the map
      DynamicDraw(false);
      return;
    }
  if (MainFrame->IsPencilDeleteChecked() == true
      && MainFrame->IsCurrentEntity() == true && OkCurrentVertex == true)
    {
      // deleting a Vertex
      if (DynamicDeleteVertex() == true)
        {
          MainFrame->UpdateCurrentEntityGeometry();
          // refreshing the map
          PrepareMap();
        }
      return;
    }
  if (MainFrame->IsCutBlueChecked() == true
      && MainFrame->IsCurrentEntity() == true && OkCurrentGeometry == true
      && OkSplitLine == true)
    {
      // splitting a line
      if (DynamicSplitLine() == true)
        {
          // refreshing the map
          PrepareMap();
        }
      return;
    }
  if (MainFrame->IsCutRedChecked() == true
      && MainFrame->IsCurrentEntity() == true && OkCurrentGeometry == true)
    {
      // deleting a SubGeometry
      if (DynamicDeleteSubGeometry() == true)
        {
          MainFrame->UpdateCurrentEntityGeometry();
          // refreshing the map
          PrepareMap();
        }
      return;
    }
  if (MainFrame->IsDrawActive() == true)
    {
      // handling Draw mode
      double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
      double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
      if (MainFrame->IsDrawPointActive() == true)
        {
          // intercepting a POINT to be inserted as a new entity
          gaiaGeomCollPtr geom;
          if (MainFrame->IsCurrentEntity() == true)
            geom = MainFrame->GetCurrentEntityGeometry();
          else
            geom = MainFrame->CreateNewGeometry();
          gaiaAddPointToGeomColl(geom, x, y);
          geom->Srid = MainFrame->GetActiveLayer()->GetSrid();
          geom->DeclaredType = MainFrame->GetActiveLayerDeclaredType();
          if (MainFrame->IsCurrentEntity() == true)
            MainFrame->UpdateCurrentEntityGeometry();
          else
            MainFrame->InsertNewEntity();
          // refreshing the map
          PrepareMap();
          return;
        }
      // intercepting a point to be inserted as a line/ring vertex
      if (!CurrentDraw)
        CurrentDraw = gaiaAllocDynamicLine();
      gaiaAppendPointToDynamicLine(CurrentDraw, x, y);
      DynamicDraw(MainFrame->IsDrawRingActive());
      return;
    }
  if (MainFrame->IsMapFrameSelectionChecked() == true)
    {
      // starting Map Frame Selection
      MapFrame1x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
      MapFrame1y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
      OkMapFrame1 = true;
      IsCapturedMouse = true;
      CaptureMouse();
      // refreshing the map
      DynamicDraw(false);
      return;
    }
  DragStartX = event.GetX();
  DragStartY = event.GetY();
  LastDragX = event.GetX();
  LastDragY = event.GetY();
}

void MyMapView::OnMouseDoubleClick(wxMouseEvent & event)
{
//
// MOUSE DoubleClick - event handler
// 
  if (TimerIdentify)
    {
      TimerIdentify->Stop();
      delete TimerIdentify;
      TimerIdentify = NULL;
    }
  SetFocus();
  SetCursor(CursorCross);
  DragStartX = -1;
  DragStartY = -1;
  LastDragX = -1;
  LastDragY = -1;
  int zoom = Zoom.GetValue() - 10;
  if (zoom > Zoom.GetMax())
    zoom = Zoom.GetMax();
  Zoom.SetValue(zoom);
  FrameCenterX = FrameMinX + ((double) (event.GetX()) * PixelRatio);
  FrameCenterY = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
  DoZoom();
}

void MyMapView::OnMouseDragStop(wxMouseEvent & event)
{
//
// MOUSE left button up - event handler
// 
  if (MainFrame->IsMapFrameSelectionChecked() == true && OkMapFrame1 == true)
    {
      // stopping Map Frame Selection
      ReleaseMouse();
      IsCapturedMouse = false;
      MapFrame2x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
      MapFrame2y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
      OkMapFrame2 = true;
      MainFrame->UnsetMeterTools();
      MainFrame->EnableMapOutput();
      // refreshing the map
      DynamicDraw(false);
      return;
    }
  if (MainFrame->IsPencilGoChecked() == true && OkMovedVertex == true)
    {
      // moving a Point or Vertex
      OkMovedVertex = false;
      double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
      double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
      if (DynamicDoMoveVertex(x, y) == true)
        {
          MainFrame->UpdateCurrentEntityGeometry();
          // refreshing the map
          PrepareMap();
        }
      return;
    }
  if (MainFrame->IsPencilAddChecked() == true && OkInterpolatedVertex == true)
    {
      // interpolating a Vertex
      OkInterpolatedVertex = false;
      double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
      double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
      if (DynamicDoInterpolateVertex(x, y) == true)
        {
          MainFrame->UpdateCurrentEntityGeometry();
          // refreshing the map
          PrepareMap();
        }
      return;
    }
  if (DragStartX < 0 || DragStartY < 0)
    return;
  if (DragStartX == event.GetX() && DragStartY == event.GetY())
    {
      SetCursor(CursorCross);
      DragStartX = -1;
      DragStartY = -1;
      LastDragX = -1;
      LastDragY = -1;
      // setting up the Identify timer
      if (!TimerIdentify)
        TimerIdentify = new wxTimer(this, ID_IDENTIFY_TIMER);
      IdentifyMouseX = event.GetX();
      IdentifyMouseY = event.GetY();
      TimerIdentify->Start(250, wxTIMER_ONE_SHOT);
      return;
    }
// computing the new Map position
  double shiftX = (double) (LastDragX - DragStartX) * PixelRatio;
  double shiftY = (double) (LastDragY - DragStartY) * PixelRatio;
  FrameCenterX -= shiftX;
  FrameCenterY += shiftY;
  PrepareMap();
  SetCursor(CursorCross);
  DragStartX = -1;
  DragStartY = -1;
  LastDragX = -1;
  LastDragY = -1;
}

void MyMapView::OnTimerMarker(wxTimerEvent & WXUNUSED(event))
{
// making the geometry to mark as "blinking"
  if (DynamicMapBitmap.IsOk() && ScreenBitmap.IsOk())
    {
      if (MarkerOddEven == false)
        {
          // "base" cycle - repainting the standard map
          wxMemoryDC *memDC = new wxMemoryDC(DynamicMapBitmap);
          wxMemoryDC *dc = new wxMemoryDC(ScreenBitmap);
          dc->Blit(0, 0, BitmapWidth, BitmapHeight, memDC, 0, 0);
          delete memDC;
          delete dc;
          MarkerOddEven = true;
      } else
        {
          // "hilight" cycle - marking selected geometry
          wxBitmap bmp;
          bmp =
            DynamicMapBitmap.GetSubBitmap(wxRect
                                          (0, 0, BitmapWidth, BitmapHeight));
          DrawTemporaryMarkers(bmp);
          wxMemoryDC *memDC = new wxMemoryDC(bmp);
          wxMemoryDC *dc = new wxMemoryDC(ScreenBitmap);
          dc->Blit(0, 0, BitmapWidth, BitmapHeight, memDC, 0, 0);
          delete memDC;
          delete dc;
          MarkerOddEven = false;
        }
    }
  Refresh();

  MarkerCount++;
  if (MarkerCount >= 60)
    {
      StopGeometryMarker();
      return;
    }
// restarting the timer again
  if (!TimerMarker)
    TimerMarker = new wxTimer(this, ID_MARKER_TIMER);
  TimerMarker->Start(250, wxTIMER_ONE_SHOT);
}

void MyMapView::OnTimerIdentify(wxTimerEvent & WXUNUSED(event))
{
// trying to perform an IDENTIFY
  LayerObject *active = MainFrame->GetActiveLayer();
  if (!active)
    return;
  if (active->GetType() != VECTOR_LAYER)
    return;
  MapLayer *layer = LayersList.GetFirst();
  while (layer)
    {
      if (layer->IsVisible() == false)
        {
          // skipping an hidden layer
          layer = layer->GetNext();
          continue;
        }
      if (layer->IsVisible(CurrentScale) == false)
        {
          // hidden at the current scale
          layer = layer->GetNext();
          continue;
        }
      if (layer->IsIdentify() == false)
        {
          // identify is OFF
          layer = layer->GetNext();
          continue;
        }
      if (layer->GetType() == VECTOR_LAYER)
        {
          if (layer->GetTableName() == active->GetTableName() &&
              layer->GetGeometryColumn() && active->GetGeometryColumn())
            {
              // OK: performing Identify
              Identify(layer, IdentifyMouseX, IdentifyMouseY);
            }
        }
      layer = layer->GetNext();
    }
}

void MyMapView::OnMouseWheel(wxMouseEvent & event)
{
//
// MOUSE wheel rotation - event handler
//
  int tics = event.GetWheelRotation() / event.GetWheelDelta();
  if (!TimerMouseWheel)
    TimerMouseWheel = new wxTimer(this, ID_WHEEL_TIMER);
  WheelTics += tics;
  TimerMouseWheel->Start(100, wxTIMER_ONE_SHOT);
}

void MyMapView::OnTimerMouseWheel(wxTimerEvent & WXUNUSED(event))
{
//
// MOUSE wheel rotation - Timer event handler
// 
  int zoom = Zoom.GetValue();
  int old_zoom = zoom;
  zoom -= WheelTics;
  WheelTics = 0;
  if (zoom > Zoom.GetMax())
    zoom = Zoom.GetMax();
  if (zoom < Zoom.GetMin())
    zoom = Zoom.GetMin();
  if (zoom != old_zoom)
    {
      Zoom.SetValue(zoom);
      DoZoom();
    }
}

void MyMapView::OnMouseMove(wxMouseEvent & event)
{
//
// MOUSE motion - event handler
// 
  double x;
  double y;
  char dummy[1024];
  wxString coords;
  if (event.LeftIsDown() == false)
    {
      if (OkMapFrame1 == true && OkMapFrame2 == false)
        {
          UnsetMapFrameSelection();
          // refreshing the map
          DynamicDraw(false);
          return;
        }
    }
  if (event.LeftIsDown() == true)
    {
      if (MainFrame->IsMapFrameSelectionChecked() == true
          && OkMapFrame1 == true)
        {
          // updating Map Frame Selection
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicShowMapFrameSelection(x, y);
          return;
        }
      if (MainFrame->IsPencilGoChecked() == true && OkCurrentGeometry == true
          && ((OkCurrentVertex == true && CurrentVertexIndex >= 0)
              || CurrentPoint != NULL))
        {
          // moving a Point or Vertex
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicShowMoveVertex(x, y);
          return;
        }
      if (MainFrame->IsPencilAddChecked() == true && OkCurrentGeometry == true
          && (CurrentSegmentIndex >= 0))
        {
          // interpolating a Vertex
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicShowInterpolateVertex(x, y);
          return;
        }
  } else
    {
      if (MainFrame->IsCutBlueChecked() == true)
        {
          // handling InterpolateVertex mode
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicFindLineToSplit(x, y);
          return;
        }
      if (MainFrame->IsPencilAddChecked() == true)
        {
          // handling InterpolateVertex mode
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicFindSegment(x, y);
          return;
        }
      if (MainFrame->IsPencilDeleteChecked() == true)
        {
          // handling DeleteVertex mode
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicFindVertex(x, y, false);
          return;
        }
      if (MainFrame->IsPencilGoChecked() == true)
        {
          // handling MoveVertex mode
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicFindVertex(x, y, true);
          return;
        }
      if (MainFrame->IsCutRedChecked() == true)
        {
          // handling Delete SubGeometry mode
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicFindSubGeometry(x, y);
          return;
        }
      if (MainFrame->IsAsteriskChecked() == true)
        {
          // handling Select MultiGeometry mode
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicFindMultiGeometry(x, y);
          return;
        }
      if (MainFrame->IsDrawActive() == true
          && MainFrame->IsDrawPointActive() == false && CurrentDraw)
        {
          // handling Draw mode
          double x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
          double y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
          DynamicDrawElastic(MainFrame->IsDrawRingActive(), x, y);
          return;
        }
    }
  if (MapTip)
    {
// check if the current Map Tip has to be erased
      if (MapTip->IsToBeErased(event.GetX(), event.GetY()) == true)
        ClearMapTip();
    }
  if (event.LeftIsDown() == true)
    {
      SetCursor(CursorHand);
      if (abs(LastDragX - event.GetX()) > 25
          || abs(LastDragY - event.GetY()) > 25)
        DragMap(event.GetX(), event.GetY());
      return;
    }
  DragStartX = -1;
  DragStartY = -1;
  LastDragX = -1;
  LastDragY = -1;
  x = FrameMinX + ((double) (event.GetX()) * PixelRatio);
  y = FrameMaxY - ((double) (event.GetY()) * PixelRatio);
  if (MainFrame->GetProjectCrs().IsGeographic() == false)
    {
      // planar coordinates
      sprintf(dummy, "X: %1.3f   Y: %1.3f", x, y);
      coords = wxString::FromUTF8(dummy);
  } else
    {
      // geographic coordinates
      if (MainFrame->GetProjectCrs().IsDms() == true)
        {
          char north = 'N';
          char east = 'E';
          double absLong = x;
          double absLat = y;
          double longDegs;
          double longMins;
          double longSecs;
          double latDegs;
          double latMins;
          double latSecs;
          double fract;
          double fract2;
          if (x < 0.0)
            {
              east = 'W';
              absLong = x * -1.0;
            }
          if (y < 0.0)
            {
              north = 'S';
              absLat = y * -1.0;
            }
          longDegs = floor(absLong);
          fract = (absLong - longDegs) * 60.0;
          longMins = floor(fract);
          fract2 = (fract - longMins) * 60.0;
          longSecs = floor(fract2);

          latDegs = floor(absLat);
          fract = (absLat - latDegs) * 60.0;
          latMins = floor(fract);
          fract2 = (fract - latMins) * 60.0;
          latSecs = floor(fract2);
          sprintf(dummy,
                  "%3.0f^%02.0f'%02.0f\"%c   %3.0f^%02.0f'%02.0f\"%c",
                  latDegs, latMins, latSecs, north, longDegs, longMins,
                  longSecs, east);
          wxString dms = wxString::FromUTF8(dummy);
          wxString degree(wxT("?"));
          degree.SetChar(0, 0xB0);
          dms.Replace(wxT("^"), degree);
          coords = dms;
      } else
        {
          sprintf(dummy, "Lat: %1.6f   Long: %1.6f", y, x);
          coords = wxString::FromUTF8(dummy);
        }
    }
  MainFrame->UpdateCoords(coords);
  if (MainFrame->IsAnyDrawModeActive() == true)
    {
      // disabling on-the-fly-identify
      ClearMapTip();
      if (!TimerMouseMove)
        TimerMouseMove->Stop();
  } else
    {
      // starting the timer
      if (!TimerMouseMove)
        TimerMouseMove = new wxTimer(this, ID_MOUSE_TIMER);
      MouseLastX = event.GetX();
      MouseLastY = event.GetY();
      TimerMouseMove->Start(100, wxTIMER_ONE_SHOT);
    }
}

void MyMapView::OnTimerMouseMove(wxTimerEvent & WXUNUSED(event))
{
//
// MOUSE motion - Timer event handler
// 
// on-the-fly Identify
//
  LayerObject *active = MainFrame->GetActiveLayer();
  if (!active)
    return;
  if (active->GetType() != VECTOR_LAYER)
    return;
  MapLayer *layer = LayersList.GetFirst();
  while (layer)
    {
      if (layer->IsVisible() == false)
        {
          // skipping an hidden layer
          layer = layer->GetNext();
          continue;
        }
      if (layer->IsVisible(CurrentScale) == false)
        {
          // hidden at the current scale
          layer = layer->GetNext();
          continue;
        }
      if (layer->IsIdentify() == false)
        {
          // identify is OFF
          layer = layer->GetNext();
          continue;
        }
      if (layer->GetType() == VECTOR_LAYER)
        {
          if (layer->GetTableName() == active->GetTableName() &&
              layer->GetGeometryColumn() == active->GetGeometryColumn())
            {
              if (layer->GetGeometryType() == LAYER_LINESTRING
                  && layer->IsNetwork() == true && MainFrame->GetNetwork())
                {
                  // NETWORK: dynamic selection of network nodes for routing
                  SelectNetworkNode(MouseLastX, MouseLastY);
                }
              if (layer->GetLabelColumn().Len() > 0)
                {
                  // OK: performing on-the-fly Identify
                  OnTheFlyIdentify(layer, MouseLastX, MouseLastY);
                }
            }
        }
      layer = layer->GetNext();
    }
}

void MyMapView::OnZoom(wxScrollEvent & WXUNUSED(event))
{
//
// the Zoom slider has been moved
//
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::OnZoomMinus(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a ZOOM MINUS command
//
  int zoom = Zoom.GetValue() + 10;
  if (zoom > Zoom.GetMax())
    zoom = Zoom.GetMax();
  Zoom.SetValue(zoom);
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::OnZoomPlus(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a ZOOM PLUS command
//
  int zoom = Zoom.GetValue() - 10;
  if (zoom < Zoom.GetMin())
    zoom = Zoom.GetMin();
  Zoom.SetValue(zoom);
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::OnZoomMicroIn(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MICRO ZOOM IN command
//
  int zoom = Zoom.GetValue() - 5;
  if (zoom < Zoom.GetMin())
    zoom = Zoom.GetMin();
  Zoom.SetValue(zoom);
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::OnZoomMicroOut(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MICRO ZOOM OUT command
//
  int zoom = Zoom.GetValue() + 5;
  if (zoom > Zoom.GetMax())
    zoom = Zoom.GetMax();
  Zoom.SetValue(zoom);
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::OnZoomIn(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a ZOOM IN command
//
  int zoom = Zoom.GetValue() - 10;
  if (zoom < Zoom.GetMin())
    zoom = Zoom.GetMin();
  Zoom.SetValue(zoom);
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::OnZoomOut(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a ZOOM OUT command
//
  int zoom = Zoom.GetValue() + 10;
  if (zoom > Zoom.GetMax())
    zoom = Zoom.GetMax();
  Zoom.SetValue(zoom);
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::ZoomIn()
{
//
// excuting a ZOOM-IN command
//
  int zoom = Zoom.GetValue() - 5;
  if (zoom < Zoom.GetMin())
    zoom = Zoom.GetMin();
  Zoom.SetValue(zoom);
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::ZoomOut()
{
//
// excuting a ZOOM-OUT command
//
  int zoom = Zoom.GetValue() + 5;
  if (zoom > Zoom.GetMax())
    zoom = Zoom.GetMax();
  Zoom.SetValue(zoom);
  if (LastZoom != Zoom.GetValue())
    DoZoom();
}

void MyMapView::OnDrawAbort(wxCommandEvent & WXUNUSED(event))
{
//
// Aborting the current draw op
//
  MainFrame->UnsetMeterTools();
  if (CurrentDraw)
    gaiaFreeDynamicLine(CurrentDraw);
  CurrentDraw = NULL;
  Refresh();
}

void MyMapView::OnDrawStop(wxCommandEvent & WXUNUSED(event))
{
//
// Completing the current draw op
//
  gaiaGeomCollPtr geom;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  int points = 0;
  double length;
  double a;
  double b;
  double rf;
  double geodesic;
  double area;
  wxString msg;
  char dummy[1024];
  char unit[128];
  char unit2[128];
  char ellps[128];
  int len;
  SridInfo crs = MainFrame->GetProjectCrs();
  MainFrame->ConvertString(crs.GetUnitName(), unit, &len);
  sprintf(unit2, "sq.%s", unit);
  if (CurrentDraw)
    {
      points = GetCurrentDrawPoints();
      if (MainFrame->IsMeasureLineChecked() == true && points >= 2)
        {
          // Measure Line Length
          geom = gaiaAllocGeomColl();
          ln = gaiaAddLinestringToGeomColl(geom, points);
          CopyCurrentDraw(ln);
          gaiaGeomCollLength(geom, &length);
          msg = wxT("Measure Line:\n\n");
          sprintf(dummy, "Vertices: %d\n", points);
          msg += wxString::FromUTF8(dummy);
          sprintf(dummy, "Length: %1.6f %s\n", length, unit);
          msg += wxString::FromUTF8(dummy);
          if (crs.IsGeographic() == true)
            {
              MainFrame->ConvertString(crs.GetEllipsoid(), ellps, &len);
              gaiaEllipseParams(ellps, &a, &b, &rf);
              geodesic =
                gaiaGreatCircleTotalLength(a, b, ln->DimensionModel, ln->Coords,
                                           ln->Points);
              sprintf(dummy, "{ Geodesic: %1.2f m }\n", geodesic);
              msg += wxString::FromUTF8(dummy);
            }
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                       this);
          gaiaFreeGeomColl(geom);
      } else if (MainFrame->IsMeasurePolygonChecked() == true && points >= 3)
        {
          // Measure Polygon Area
          geom = gaiaAllocGeomColl();
          pg = gaiaAddPolygonToGeomColl(geom, points + 1, 0);
          CopyCurrentDraw(pg->Exterior);
          DynamicDraw(true);
          gaiaGeomCollLength(geom, &length);
          gaiaGeomCollArea(geom, &area);
          msg = wxT("Measure Polygon:\n\n");
          sprintf(dummy, "Vertices: %d\n", points + 1);
          msg += wxString::FromUTF8(dummy);
          sprintf(dummy, "Perimeter: %1.6f %s\n", length, unit);
          msg += wxString::FromUTF8(dummy);
          if (crs.IsGeographic() == true)
            {
              MainFrame->ConvertString(crs.GetEllipsoid(), ellps, &len);
              gaiaEllipseParams(ellps, &a, &b, &rf);
              geodesic =
                gaiaGreatCircleTotalLength(a, b, pg->Exterior->DimensionModel,
                                           pg->Exterior->Coords,
                                           pg->Exterior->Points);
              sprintf(dummy, "{ Geodesic: %1.2f m }\n", geodesic);
              msg += wxString::FromUTF8(dummy);
            }
          sprintf(dummy, "Area: %1.6f %s", area, unit2);
          msg += wxString::FromUTF8(dummy);
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                       this);
          gaiaFreeGeomColl(geom);
      } else if (MainFrame->IsDrawLineActive() == true)
        {
          // adding a Linestring
          if (MainFrame->IsCurrentEntity() == true)
            geom = MainFrame->GetCurrentEntityGeometry();
          else
            geom = MainFrame->CreateNewGeometry();
          geom->Srid = MainFrame->GetActiveLayer()->GetSrid();
          geom->DeclaredType = MainFrame->GetActiveLayerDeclaredType();
          ln = gaiaAddLinestringToGeomColl(geom, points);
          CopyCurrentDraw(ln);
          if (MainFrame->IsCurrentEntity() == true)
            MainFrame->UpdateCurrentEntityGeometry();
          else
            MainFrame->InsertNewEntity();
      } else if (MainFrame->IsDrawRingActive() == true)
        {
          // adding a Ring
          if (MainFrame->IsCurrentEntity() == true)
            geom = MainFrame->GetCurrentEntityGeometry();
          else
            geom = MainFrame->CreateNewGeometry();
          geom->Srid = MainFrame->GetActiveLayer()->GetSrid();
          geom->DeclaredType = MainFrame->GetActiveLayerDeclaredType();
          if (MainFrame->IsCurrentEntity() == true &&
              MainFrame->IsValidInteriorRing(CurrentDraw, &pg) == true)
            {
              // adding an Interior ring
              MainFrame->AddInteriorRing(CurrentDraw,
                                         GetCurrentDrawPoints() + 1, pg);
          } else
            {
              // trying to add an Exterior ring
              pg = gaiaAddPolygonToGeomColl(geom, points + 1, 0);
              CopyCurrentDraw(pg->Exterior);
            }
          if (MainFrame->IsCurrentEntity() == true)
            MainFrame->UpdateCurrentEntityGeometry();
          else
            MainFrame->InsertNewEntity();
        }
      gaiaFreeDynamicLine(CurrentDraw);
    }
  MainFrame->UnsetMeterTools();
  CurrentDraw = NULL;
// refreshing the map
  PrepareMap();
}

void MyMapView::OnDrawUndo(wxCommandEvent & WXUNUSED(event))
{
//
// Undoing the latest draw op
//
  if (CurrentDraw)
    {
      if (CurrentDraw->First == CurrentDraw->Last)
        return;
      gaiaDynamicLineDeletePoint(CurrentDraw, CurrentDraw->Last);
      DynamicDraw(MainFrame->IsDrawRingActive());
    }
}

void MyMapView::OnCmdEditMode(wxCommandEvent & WXUNUSED(event))
{
//
// Enabling / Disabling Editing for current Active Layer (if any)
//
  if (MainFrame->GetActiveLayer())
    {
      if (MainFrame->GetActiveLayer()->GetType() == VECTOR_LAYER)
        {
          bool mode = true;
          if (MainFrame->GetActiveLayer()->IsEditingEnabled() == true)
            mode = false;
          if (MainFrame->GetActiveLayer()->GetGeometryType() == LAYER_LINESTRING
              && MainFrame->GetActiveLayer()->IsNetwork() == true)
            mode = false;
          MainFrame->GetActiveLayer()->SetEditingEnabled(mode);
        }
    }
  MainFrame->EnableDrawTools();
}

void MyMapView::OnCmdIdentify(wxCommandEvent & WXUNUSED(event))
{
//
// Identifying the current entity
//
  LayerObject *active = MainFrame->GetActiveLayer();
  if (!active)
    return;
  if (active->GetType() != VECTOR_LAYER)
    return;
  if (IsMapTipShown() == true)
    {
      MapLayer *layer = LayersList.GetFirst();
      while (layer)
        {
          if (layer->IsVisible() == false)
            {
              // skipping an hidden layer
              layer = layer->GetNext();
              continue;
            }
          if (layer->IsVisible(CurrentScale) == false)
            {
              // hidden at the current scale
              layer = layer->GetNext();
              continue;
            }
          if (layer->IsIdentify() == false)
            {
              // identify is OFF
              layer = layer->GetNext();
              continue;
            }
          if (layer->GetType() == VECTOR_LAYER)
            {
              if (layer->GetTableName() == active->GetTableName() &&
                  layer->GetGeometryColumn() && active->GetGeometryColumn())
                {
                  // OK: performing Identify
                  Identify(layer, MouseIdentifyX, MouseIdentifyY);
                }
            }
          layer = layer->GetNext();
        }
    }
}

void MyMapView::OnCmdNodeFrom(wxCommandEvent & WXUNUSED(event))
{
//
// Setting up the Routing Node From
//
  if (MainFrame->GetNetwork()->GetCurrentNode()->IsValid() == true)
    {
      MainFrame->GetNetwork()->SetNodeFrom();
      MainFrame->GetNetwork()->UnsetCurrentNode();
      ResetScreenBitmap();
      ResolveRouting();
    }
}

void MyMapView::OnCmdNodeTo(wxCommandEvent & WXUNUSED(event))
{
//
// Setting up the Routing Node To
//
  if (MainFrame->GetNetwork()->GetCurrentNode()->IsValid() == true)
    {
      MainFrame->GetNetwork()->SetNodeTo();
      MainFrame->GetNetwork()->UnsetCurrentNode();
      ResetScreenBitmap();
      ResolveRouting();
    }
}

void MyMapView::OnCmdReturnTrip(wxCommandEvent & WXUNUSED(event))
{
//
// Swapping NodeTo/NodeFrom
//
  MainFrame->GetNetwork()->SwapFromTo();
  ResolveRouting();
}

void MyMapView::OnCmdRouteClear(wxCommandEvent & WXUNUSED(event))
{
//
// Cleaning up the current Route
//
  MainFrame->GetNetwork()->UnsetNodeFrom();
  MainFrame->GetNetwork()->UnsetNodeTo();
  MainFrame->GetNetwork()->UnsetSolution();
  ResetScreenBitmap();
}

void MyMapView::OnCmdRoutingAlgorithm(wxCommandEvent & WXUNUSED(event))
{
//
// trying to change the current Routing Algorithm
//
  if (MainFrame->IsCurrentRoutingAlgorithmAStar
      (MainFrame->GetNetwork()->GetNetworkTable()))
    MainFrame->SetRoutingAlgorithm(MainFrame->GetNetwork()->GetNetworkTable(),
                                   false);
  else
    MainFrame->SetRoutingAlgorithm(MainFrame->GetNetwork()->GetNetworkTable(),
                                   true);
  IsCurrentRoutingAlgorithmAStar =
    MainFrame->IsCurrentRoutingAlgorithmAStar(MainFrame->GetNetwork()->
                                              GetNetworkTable());
}

void MyMapView::OnCenter(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a CENTER MAP command
//
  ComputeMapExtent();
  SetFrameFullExtent();
  PrepareMap();
}

void MyMapView::OnUp(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MOVE UP command
//
  double shift = ((FrameHeight * PixelRatio) / 4.0) * 3.0;
  FrameCenterY += shift;
  PrepareMap();
}

void MyMapView::OnDown(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MOVE DOWN command
//
  double shift = ((FrameHeight * PixelRatio) / 4.0) * 3.0;
  FrameCenterY -= shift;
  PrepareMap();
}

void MyMapView::OnLeft(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MOVE LEFT command
//
  double shift = ((FrameWidth * PixelRatio) / 4.0) * 3.0;
  FrameCenterX -= shift;
  PrepareMap();
}

void MyMapView::OnRight(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MOVE RIGHT command
//
  double shift = ((FrameWidth * PixelRatio) / 4.0) * 3.0;
  FrameCenterX += shift;
  PrepareMap();
}

void MyMapView::OnMicroUp(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MICRO MOVE UP command
//
  double shift = (FrameHeight * PixelRatio) / 4.0;
  FrameCenterY += shift;
  PrepareMap();
}

void MyMapView::OnMicroDown(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MICRO MOVE DOWN command
//
  double shift = (FrameHeight * PixelRatio) / 4.0;
  FrameCenterY -= shift;
  PrepareMap();
}

void MyMapView::OnMicroLeft(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MICRO MOVE LEFT command
//
  double shift = (FrameWidth * PixelRatio) / 4.0;
  FrameCenterX -= shift;
  PrepareMap();
}

void MyMapView::OnMicroRight(wxCommandEvent & WXUNUSED(event))
{
//
// excuting a MICRO MOVE RIGHT command
//
  double shift = (FrameWidth * PixelRatio) / 4.0;
  FrameCenterX += shift;
  PrepareMap();
}

void MyMapView::DoZoom()
{
//
// applying a new Zoom factor
//
  double max_radius;
  double ext_x = MapMaxX - MapMinX;
  double ext_y = MapMaxY - MapMinY;
  if (ext_x > ext_y)
    max_radius = ext_x / 2.0;
  else
    max_radius = ext_y / 2.0;
  if (MainFrame->GetProjectCrs().IsGeographic() == true)
    {
      // geographic coordinates
      max_radius *= 36000.0;
    }
  max_radius -= 1.0;
  FrameRadius =
    pow(max_radius, ((double) (Zoom.GetValue()) / (double) Zoom.GetMax()));
  if (MainFrame->GetProjectCrs().IsGeographic() == true)
    FrameRadius /= 36000.0;
  LastZoom = Zoom.GetValue();
  PrepareMap();
}

void MyMapView::DragMap(int end_x, int end_y)
{
//
// Map dragging
//
  int width = FrameWidth;
  int height = FrameHeight;
  int baseX = 0;
  int baseY = 0;
  if (OkMapFrame1 == true && OkMapFrame2 == false)
    {
      UnsetMapFrameSelection();
      // refreshing the map
      DynamicDraw(false);
      return;
    }
  baseX = end_x - DragStartX;
  baseY = end_y - DragStartY;

  wxClientDC dc(this);
  dc.SetBrush(wxBrush(wxColour(192, 192, 192)));
  dc.DrawRectangle(-1, -1, width + 1, height + 1);
// copying the ScreenImage - dragged
  wxMemoryDC bmpDc(ScreenBitmap);
  int eff_width = width;
  int eff_height = height;
  int sx = 0;
  int sy = 0;
  int ix = 0;
  int iy = 0;
  if (baseX < 0)
    {
      ix = 0;
      sx = 0 - baseX;
      eff_width = width + baseX;
  } else
    {
      ix = baseX;
      eff_width = width - baseX;
    }
  if (baseY < 0)
    {
      iy = 0;
      sy = 0 - baseY;
      eff_height = height + baseY;
  } else
    {
      iy = baseY;
      eff_height = height - baseY;
    }
  dc.Blit(ix, iy, eff_width, eff_height, &bmpDc, sx, sy);
  LastDragX = end_x;
  LastDragY = end_y;
}

void MyMapView::SetMapToolsState(bool splash)
{
//
// enabling/disabling the Map Tools
//
  SplashMode = splash;
  if (ValidMap == false)
    SplashMode = true;
  if (SplashMode == true)
    {
      Zoom.Show(false);
      Center.Show(false);
      Up.Show(false);
      Down.Show(false);
      Left.Show(false);
      Right.Show(false);
      ZoomMin.Show(false);
      ZoomMax.Show(false);
      Refresh();
      Update();
  } else
    {
      Zoom.Show(ValidMap);
      Center.Show(ValidMap);
      Up.Show(ValidMap);
      Down.Show(ValidMap);
      Left.Show(ValidMap);
      Right.Show(ValidMap);
      ZoomMin.Show(ValidMap);
      ZoomMax.Show(ValidMap);
      Refresh();
      if (ValidMap == true)
        {
          Zoom.Refresh();
          Zoom.Update();
          Center.Refresh();
          Center.Update();
          Up.Refresh();
          Up.Update();
          Down.Refresh();
          Down.Update();
          Left.Refresh();
          Left.Update();
          Right.Refresh();
          Right.Update();
          ZoomMin.Refresh();
          ZoomMin.Update();
          ZoomMax.Refresh();
          ZoomMax.Update();
        }
    }
}

void MyMapView::StartGeometryMarker(wxString & table, wxString & geomColumn)
{
//
// setting up the geometry marker
//
  MapLayer *layer;
  if (TimerMarker)
    {
      TimerMarker->Stop();
      delete TimerMarker;
      TimerMarker = NULL;
    }
  RoutingMarker = false;
  if (GeomsToMark.GetFirst() == NULL)
    return;
  MarkerOddEven = true;
  MarkerCount = 0;
  MarkerGraphic.Reset();
  layer = LayersList.GetFirst();
  while (layer)
    {
      // searching the corresponding layer
      if (layer->GetTableName() == table
          && layer->GetGeometryColumn() == geomColumn)
        {
          MarkerGraphic.Init(layer);
          break;
        }
      layer = layer->GetNext();
    }
  if (!TimerMarker)
    TimerMarker = new wxTimer(this, ID_MARKER_TIMER);
  TimerMarker->Start(250, wxTIMER_ONE_SHOT);
}

void MyMapView::StartRoutingMarker()
{
//
// setting up the Routing marker
//
  if (TimerMarker)
    {
      TimerMarker->Stop();
      delete TimerMarker;
      TimerMarker = NULL;
    }
  if (GeomsToMark.GetFirst() == NULL)
    return;
  RoutingMarker = true;
  MarkerOddEven = true;
  MarkerCount = 0;
  MarkerGraphic.Reset();
// setting up Graphics attributes
  wxColour color(255, 128, 0, 128);
  MapLayer layer(color, 4);
  MarkerGraphic.Init(&layer);
  if (!TimerMarker)
    TimerMarker = new wxTimer(this, ID_MARKER_TIMER);
  TimerMarker->Start(250, wxTIMER_ONE_SHOT);
}

void MyMapView::StopGeometryMarker()
{
//
// shutting down the geometry marker
//
  if (TimerMarker)
    {
      TimerMarker->Stop();
      delete TimerMarker;
      TimerMarker = NULL;
    }
  GeomsToMark.Flush();
  RoutingMarker = false;
// restoring the screen
  Refresh();
}

void MyMapView::DrawTemporaryMarkers(wxBitmap & bitmap)
{
//
// draws the temporary markers - evidenced geometry
//
  wxMemoryDC *dc = new wxMemoryDC(bitmap);
  if (dc->IsOk() == false)
    {
      delete dc;
      return;
    }
  if (MarkerGraphic.IsOk() == true)
    {
      wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
      MarkerGraphic.CreateGraphicResources(gr);
      GeometryToMark *pMark = GeomsToMark.GetFirst();
      while (pMark)
        {
          gaiaGeomCollPtr geom = pMark->Geometry();
          if (geom->FirstPolygon)
            MarkPolygon(gr, geom);
          if (geom->FirstLinestring)
            MarkLinestring(gr, geom);
          if (geom->FirstPoint)
            MarkPoint(gr, geom);
          pMark = pMark->GetNext();
        }
      delete gr;
    }
  delete dc;
}

void MyMapView::PrepareMap()
{
//
// draws the MapBitmap
//
  MapLayer *layer;
  wxMemoryDC *dc = NULL;
  wxSize sz = GetClientSize();
  dc = new wxMemoryDC(MapBitmap);
  if (dc->IsOk() == false)
    {
      delete dc;
      return;
    }
  dc->SetBrush(CheckedBrush);
// initializing the bitmap background
  dc->DrawRectangle(0, 0, sz.GetWidth(), sz.GetHeight());

  if (ValidMap == true)
    {
      // computing the current Frame, Ratio and Scale
      FrameWidth = sz.GetWidth();
      FrameHeight = sz.GetHeight();
      double x_ratio = (FrameRadius * 2.0) / FrameHeight;
      double y_ratio = (FrameRadius * 2.0) / FrameWidth;
      if (x_ratio > y_ratio)
        PixelRatio = (FrameRadius * 2.0) / FrameHeight;
      else
        PixelRatio = (FrameRadius * 2.0) / FrameWidth;
      FrameMinX = FrameCenterX - ((FrameWidth / 2.0) * PixelRatio);
      FrameMaxX = FrameCenterX + ((FrameWidth / 2.0) * PixelRatio);
      FrameMinY = FrameCenterY - ((FrameHeight / 2.0) * PixelRatio);
      FrameMaxY = FrameCenterY + ((FrameHeight / 2.0) * PixelRatio);
      if (MainFrame->GetProjectCrs().IsGeographic() == true)
        {
          // geographic coordinates
          double cm = PixelRatio * 72.0 * 0.3937;
          CurrentScale = (int) (cm * 11113200.0);
      } else
        {
          // planar coordinates
          double cm = PixelRatio * 72.0 * 0.3937;
          CurrentScale = (int) (cm * 100.0);
        }
      char dummy[128];
      sprintf(dummy, "Scale 1:%d", CurrentScale);
      wxString scale = wxString::FromUTF8(dummy);
      MainFrame->UpdateScale(scale);

      // drawing the map Layers [following the zOrder]
      wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
      MainFrame->UpdateLayersList(&LayersList, false);
      LayersList.CreateGraphicResources(gr);

      ::wxBeginBusyCursor();

      layer = LayersList.GetFirst();
      bool labels = false;
      while (layer)
        {
          if (layer->IsVisible() == false)
            {
              // skipping an hidden layer
              layer = layer->GetNext();
              continue;
            }
          if (layer->IsVisible(CurrentScale) == false)
            {
              // hidden at the current scale
              layer = layer->GetNext();
              continue;
            }
          if (layer->GetType() == VECTOR_LAYER)
            {
              DrawVectorLayer(gr, layer);
              if (layer->HasMapLabels() == true)
                labels = true;
            }
          if (layer->GetType() == RASTER_LAYER)
            DrawRasterLayer(gr, layer);
          layer = layer->GetNext();
        }
      if (labels == true)
        {
          // creating the Map Label List
          MapLabelList *labelList = new MapLabelList(PixelRatio);
          // feeding the labels into the list
          layer = LayersList.GetFirst();
          while (layer)
            {
              if (layer->GetType() != VECTOR_LAYER)
                {
                  // skipping non-vector layers
                  layer = layer->GetNext();
                  continue;
                }
              if (layer->IsVisible() == false)
                {
                  // skipping an hidden layer
                  layer = layer->GetNext();
                  continue;
                }
              if (layer->IsVisible(CurrentScale) == false)
                {
                  // hidden at the current scale
                  layer = layer->GetNext();
                  continue;
                }
              if (layer->AreLabelsVisible(CurrentScale) == false)
                {
                  // no labels at the current scale
                  layer = layer->GetNext();
                  continue;
                }
              if (layer->HasMapLabels() == true)
                FeedMapLabels(gr, layer, labelList);
              layer = layer->GetNext();
            }
          // placing labels avoiding collisions [when required]
          labelList->CheckCollisions();
          // drawing the Map Labels
          wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
          MapOutliner *outliner =
            new MapOutliner(FrameWidth, FrameHeight, font);
          MapLabel *pL = labelList->GetFirst();
          while (pL)
            {
              // drawing Map Labels Outlines
              if (pL->IsValid() == true)
                {
                  if (pL->GetLayer()->IsLabelFontOutlined() == true)
                    {
                      double x = (pL->GetX() - FrameMinX) / PixelRatio;
                      double y =
                        (double) FrameHeight -
                        ((pL->GetY() - FrameMinY) / PixelRatio);
                      outliner->Draw(pL->GetLayer(), pL->GetLabel(), x, y,
                                     pL->GetRotation());
                    }
                }
              pL = pL->GetNext();
            }
          outliner->Outline();
          if (outliner->IsValid() == true)
            gr->DrawBitmap(*(outliner->GetBitmap()), 0, 0, FrameWidth,
                           FrameHeight);
          delete outliner;
          pL = labelList->GetFirst();
          while (pL)
            {
              // drawing Map Labels
              if (pL->IsValid() == true)
                {
                  layer = pL->GetLayer();
                  double x = (pL->GetX() - FrameMinX) / PixelRatio;
                  double y =
                    (double) FrameHeight -
                    ((pL->GetY() - FrameMinY) / PixelRatio);
                  font.SetPointSize(layer->GetLabelPointSize());
                  if (layer->IsLabelFontBold() == true)
                    font.SetWeight(wxFONTWEIGHT_BOLD);
                  else
                    font.SetWeight(wxFONTWEIGHT_NORMAL);
                  if (layer->IsLabelFontItalic() == true)
                    font.SetStyle(wxFONTSTYLE_ITALIC);
                  else
                    font.SetStyle(wxFONTSTYLE_NORMAL);
                  font.SetUnderlined(layer->IsLabelFontUnderlined());
                  gr->SetFont(font, layer->GetLabelColor());
                  gr->DrawText(pL->GetLabel(), x, y, pL->GetRotation());
                }
              pL = pL->GetNext();
            }
          // destroyng the label list
          delete labelList;
        }

      ::wxEndBusyCursor();

      delete gr;
      SetMapToolsState(false);
      MainFrame->EnableMeterTools(true);
  } else
    {
      SetMapToolsState(true);
      MainFrame->EnableMeterTools(false);
    }

  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  ResetScreenBitmap();
  DynamicDraw(false);
  Refresh();
}

void MyMapView::ResetScreenBitmap()
{
// copying the MapBitmap into the DynamicMapBitmap and ScreenBitmap
  wxMemoryDC *mapDc = new wxMemoryDC(MapBitmap);
  wxMemoryDC *dynDc = new wxMemoryDC(DynamicMapBitmap);
  dynDc->Blit(0, 0, BitmapWidth, BitmapHeight, mapDc, 0, 0);
  delete mapDc;
  if (MainFrame->GetNetwork())
    {
      wxGraphicsContext *gr = wxGraphicsContext::Create(*dynDc);
      DynamicDrawRoutingSolution(gr);
      delete gr;
    }
  wxMemoryDC *screenDc = new wxMemoryDC(ScreenBitmap);
  screenDc->Blit(0, 0, BitmapWidth, BitmapHeight, dynDc, 0, 0);
  delete dynDc;
  delete screenDc;
  Refresh();
}

bool MyMapView::IsValidMapFrame()
{
//
// checks for a valid MapFrame
//
  if (ValidMapExtent == true && ValidMap == true)
    {
      MainFrame->EnableMeterTools(false);
      return true;
    }
  MainFrame->EnableMeterTools(false);
  return false;
}

void MyMapView::ClearMapExtent()
{
//
// clearing the Map full extenxt
//
  UnsetMapFrameSelection();
  MapMinX = DBL_MAX;
  MapMinY = DBL_MAX;
  MapMaxX = 0.0 - DBL_MAX;
  MapMaxY = 0.0 - DBL_MAX;
  ValidMapExtent = false;
  FrameWidth = 0;
  FrameHeight = 0;
  FrameCenterX = DBL_MAX;
  FrameCenterY = DBL_MAX;
  FrameRadius = 0.0;
  FrameMinX = DBL_MAX;
  FrameMinY = DBL_MAX;
  FrameMaxX = 0.0 - DBL_MAX;
  FrameMaxY = 0.0 - DBL_MAX;
  PixelRatio = DBL_MAX;
  CurrentScale = 0;
  DragStartX = -1;
  DragStartY = -1;
  LastDragX = -1;
  LastDragY = -1;
  ValidMap = false;
  MainFrame->EnableMeterTools(false);
}

void MyMapView::ComputeMapExtent()
{
//
// computing the Map full extenxt
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  double min_x = DBL_MAX;
  double max_x = 0.0 - DBL_MAX;
  double min_y = DBL_MAX;
  double max_y = 0.0 - DBL_MAX;
  char *value;
  MapMinX = DBL_MAX;
  MapMinY = DBL_MAX;
  MapMaxX = 0.0 - DBL_MAX;
  MapMaxY = 0.0 - DBL_MAX;
  ValidMapExtent = false;

// checking the Vector Layers [table-based layers]
  sql = wxT("SELECT g.srid, r.proj4text, s.extent_min_x, s.extent_min_y, ");
  sql += wxT("s.extent_max_x, s.extent_max_y, p.reproject ");
  sql += wxT("FROM geometry_columns as g, spatial_ref_sys as r, ");
  sql += wxT("layer_statistics as s, layer_params as p ");
  sql += wxT("WHERE g.f_table_name = s.table_name AND ");
  sql += wxT("g.f_geometry_column = s.geometry_column AND r.srid = g.srid ");
  sql += wxT("AND p.table_name = s.table_name AND ");
  sql += wxT("p.geometry_column = s.geometry_column");

  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          int srid = -9999;
          char proj_params[1024];
          double mnX = DBL_MAX;
          double mnY = DBL_MAX;
          double mxX = 0.0 - DBL_MAX;
          double mxY = 0.0 - DBL_MAX;
          bool reproject = false;

          value = results[(i * columns) + 0];
          if (value)
            srid = atoi(value);
          value = results[(i * columns) + 1];
          if (value)
            strcpy(proj_params, value);
          value = results[(i * columns) + 2];
          if (value)
            mnX = atof(value);
          value = results[(i * columns) + 3];
          if (value)
            mnY = atof(value);
          value = results[(i * columns) + 4];
          if (value)
            mxX = atof(value);
          value = results[(i * columns) + 5];
          if (value)
            mxY = atof(value);
          value = results[(i * columns) + 6];
          if (value)
            {
              if (atoi(value) == 0)
                reproject = false;
              else
                reproject = true;
            }

          if (srid == MainFrame->GetProjectCrs().GetSrid())
            ;
          else
            {
              // this Layer uses a SRID not identical to the one set for the Project
              if (srid >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
                  && reproject == true)
                {
                  // we need to reproject this extenxt into the Project's CRS
                  char to_params[1024];
                  strcpy(to_params,
                         MainFrame->GetProjectCrs().GetParams().ToUTF8());
                  gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
                  gaiaAddPointToGeomColl(geom2, mnX, mnY);
                  gaiaAddPointToGeomColl(geom2, mxX, mxY);
                  gaiaAddPointToGeomColl(geom2, mnX, mxY);
                  gaiaAddPointToGeomColl(geom2, mxX, mnY);
                  gaiaGeomCollPtr geom =
                    gaiaTransform(geom2, proj_params, to_params);
                  gaiaFreeGeomColl(geom2);
                  mnX = geom->MinX;
                  mnY = geom->MinY;
                  mxX = geom->MaxX;
                  mxY = geom->MaxY;
                  gaiaFreeGeomColl(geom);
                }
            }
          if (mnX < min_x)
            min_x = mnX;
          if (mxX > max_x)
            max_x = mxX;
          if (mnY < min_y)
            min_y = mnY;
          if (mxY > max_y)
            max_y = mxY;
        }
    }
  sqlite3_free_table(results);

// checking the Vector Layers [view-based layers]
  sql = wxT("SELECT g2.srid, r.proj4text, s.extent_min_x, s.extent_min_y, ");
  sql += wxT("s.extent_max_x, s.extent_max_y, p.reproject ");
  sql += wxT("FROM views_geometry_columns as g, spatial_ref_sys as r, ");
  sql +=
    wxT("layer_statistics as s, layer_params as p, geometry_columns as g2 ");
  sql += wxT("WHERE g.view_name = s.table_name AND ");
  sql += wxT("g.view_geometry = s.geometry_column AND r.srid = g2.srid ");
  sql += wxT("AND g.f_table_name = g2.f_table_name ");
  sql += wxT("AND g.f_geometry_column = g2.f_geometry_column ");
  sql += wxT("AND p.table_name = s.table_name AND ");
  sql += wxT("p.geometry_column = s.geometry_column");

  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          int srid = -9999;
          char proj_params[1024];
          double mnX = DBL_MAX;
          double mnY = DBL_MAX;
          double mxX = 0.0 - DBL_MAX;
          double mxY = 0.0 - DBL_MAX;
          bool reproject = false;

          value = results[(i * columns) + 0];
          if (value)
            srid = atoi(value);
          value = results[(i * columns) + 1];
          if (value)
            strcpy(proj_params, value);
          value = results[(i * columns) + 2];
          if (value)
            mnX = atof(value);
          value = results[(i * columns) + 3];
          if (value)
            mnY = atof(value);
          value = results[(i * columns) + 4];
          if (value)
            mxX = atof(value);
          value = results[(i * columns) + 5];
          if (value)
            mxY = atof(value);
          value = results[(i * columns) + 6];
          if (value)
            {
              if (atoi(value) == 0)
                reproject = false;
              else
                reproject = true;
            }

          if (srid == MainFrame->GetProjectCrs().GetSrid())
            ;
          else
            {
              // this Layer uses a SRID not identical to the one set for the Project
              if (srid >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
                  && reproject == true)
                {
                  // we need to reproject this extenxt into the Project's CRS
                  char to_params[1024];
                  strcpy(to_params,
                         MainFrame->GetProjectCrs().GetParams().ToUTF8());
                  gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
                  gaiaAddPointToGeomColl(geom2, mnX, mnY);
                  gaiaAddPointToGeomColl(geom2, mxX, mxY);
                  gaiaAddPointToGeomColl(geom2, mnX, mxY);
                  gaiaAddPointToGeomColl(geom2, mxX, mnY);
                  gaiaGeomCollPtr geom =
                    gaiaTransform(geom2, proj_params, to_params);
                  gaiaFreeGeomColl(geom2);
                  mnX = geom->MinX;
                  mnY = geom->MinY;
                  mxX = geom->MaxX;
                  mxY = geom->MaxY;
                  gaiaFreeGeomColl(geom);
                }
            }
          if (mnX < min_x)
            min_x = mnX;
          if (mxX > max_x)
            max_x = mxX;
          if (mnY < min_y)
            min_y = mnY;
          if (mxY > max_y)
            max_y = mxY;
        }
    }
  sqlite3_free_table(results);

// checking the Vector Layers [virtualSHP-based layers]
  sql = wxT("SELECT g.srid, r.proj4text, s.extent_min_x, s.extent_min_y, ");
  sql += wxT("s.extent_max_x, s.extent_max_y, p.reproject ");
  sql += wxT("FROM virts_geometry_columns as g, spatial_ref_sys as r, ");
  sql += wxT("layer_statistics as s, layer_params as p ");
  sql += wxT("WHERE g.virt_name = s.table_name AND ");
  sql += wxT("g.virt_geometry = s.geometry_column AND r.srid = g.srid ");
  sql += wxT("AND p.table_name = s.table_name AND ");
  sql += wxT("p.geometry_column = s.geometry_column");

  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          int srid = -9999;
          char proj_params[1024];
          double mnX = DBL_MAX;
          double mnY = DBL_MAX;
          double mxX = 0.0 - DBL_MAX;
          double mxY = 0.0 - DBL_MAX;
          bool reproject = false;

          value = results[(i * columns) + 0];
          if (value)
            srid = atoi(value);
          value = results[(i * columns) + 1];
          if (value)
            strcpy(proj_params, value);
          value = results[(i * columns) + 2];
          if (value)
            mnX = atof(value);
          value = results[(i * columns) + 3];
          if (value)
            mnY = atof(value);
          value = results[(i * columns) + 4];
          if (value)
            mxX = atof(value);
          value = results[(i * columns) + 5];
          if (value)
            mxY = atof(value);
          value = results[(i * columns) + 6];
          if (value)
            {
              if (atoi(value) == 0)
                reproject = false;
              else
                reproject = true;
            }

          if (srid == MainFrame->GetProjectCrs().GetSrid())
            ;
          else
            {
              // this Layer uses a SRID not identical to the one set for the Project
              if (srid >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
                  && reproject == true)
                {
                  // we need to reproject this extenxt into the Project's CRS
                  char to_params[1024];
                  strcpy(to_params,
                         MainFrame->GetProjectCrs().GetParams().ToUTF8());
                  gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
                  gaiaAddPointToGeomColl(geom2, mnX, mnY);
                  gaiaAddPointToGeomColl(geom2, mxX, mxY);
                  gaiaAddPointToGeomColl(geom2, mnX, mxY);
                  gaiaAddPointToGeomColl(geom2, mxX, mnY);
                  gaiaGeomCollPtr geom =
                    gaiaTransform(geom2, proj_params, to_params);
                  gaiaFreeGeomColl(geom2);
                  mnX = geom->MinX;
                  mnY = geom->MinY;
                  mxX = geom->MaxX;
                  mxY = geom->MaxY;
                  gaiaFreeGeomColl(geom);
                }
            }
          if (mnX < min_x)
            min_x = mnX;
          if (mxX > max_x)
            max_x = mxX;
          if (mnY < min_y)
            min_y = mnY;
          if (mxY > max_y)
            max_y = mxY;
        }
    }
  sqlite3_free_table(results);

// checking the Raster Layers 
  sql = wxT("SELECT extent_min_x, extent_min_y, extent_max_x, extent_max_y ");
  sql += wxT("FROM layer_statistics WHERE raster_layer = 1");

  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          double mnX = DBL_MAX;
          double mnY = DBL_MAX;
          double mxX = 0.0 - DBL_MAX;
          double mxY = 0.0 - DBL_MAX;

          value = results[(i * columns) + 0];
          if (value)
            mnX = atof(value);
          value = results[(i * columns) + 1];
          if (value)
            mnY = atof(value);
          value = results[(i * columns) + 2];
          if (value)
            mxX = atof(value);
          value = results[(i * columns) + 3];
          if (value)
            mxY = atof(value);
          if (mnX < min_x)
            min_x = mnX;
          if (mxX > max_x)
            max_x = mxX;
          if (mnY < min_y)
            min_y = mnY;
          if (mxY > max_y)
            max_y = mxY;
        }
    }
  sqlite3_free_table(results);

  if (min_x != DBL_MAX && min_y != DBL_MAX && max_x != (0.0 - DBL_MAX)
      && max_y != (0.0 - DBL_MAX))
    {
      MapMinX = min_x;
      MapMinY = min_y;
      MapMaxX = max_x;
      MapMaxY = max_y;
      ValidMapExtent = true;
    }
  UnsetMapFrameSelection();
}

void MyMapView::SetFrameFullExtent()
{
//
// setting the Frame to full extenxt
//
  double ext_x;
  double ext_y;
  wxSize sz = GetClientSize();
  if (ValidMapExtent == true)
    {
      // OK: setting to MapFullExtent
      ext_x = MapMaxX - MapMinX;
      ext_y = MapMaxY - MapMinY;
      FrameCenterX = MapMinX + (ext_x / 2.0);
      FrameCenterY = MapMinY + (ext_y / 2.0);
      if (ext_x > ext_y)
        FrameRadius = ext_x / 2.0;
      else
        FrameRadius = ext_y / 2.0;
      ValidMap = true;
      LastZoom = Zoom.GetMax();
      Zoom.SetValue(Zoom.GetMax());
      MainFrame->EnableMeterTools(true);
  } else
    {
      // there is no current Map, or it is an invalid one 
      FrameWidth = 0;
      FrameHeight = 0;
      FrameCenterX = DBL_MAX;
      FrameCenterY = DBL_MAX;
      FrameRadius = 0.0;
      FrameMinX = DBL_MAX;
      FrameMinY = DBL_MAX;
      FrameMaxX = 0.0 - DBL_MAX;
      FrameMaxY = 0.0 - DBL_MAX;
      PixelRatio = DBL_MAX;
      CurrentScale = 0;
      DragStartX = -1;
      DragStartY = -1;
      LastDragX = -1;
      LastDragY = -1;
      ValidMap = false;
      MainFrame->EnableMeterTools(false);
    }
}

void MyMapView::UpdateFrameExtent(int lastSrid, bool lastGeographic)
{
//
// repositioning the MapFrame into the new SRID
//
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;

  if (lastSrid >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0)
    {
      bool ok_from = MainFrame->GetProjParams(lastSrid, proj_from);
      bool ok_to =
        MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(), proj_to);
      if (ok_from == true && ok_to == true)
        reproject = true;
    }

  if (reproject == true)
    {
      // OK: computing the new MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, FrameCenterX, FrameCenterY);
      // transforming the center point
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_from, proj_to);
      gaiaFreeGeomColl(geom2);
      FrameCenterX = geom->FirstPoint->X;
      FrameCenterY = geom->FirstPoint->Y;
      gaiaFreeGeomColl(geom);
      if (lastGeographic == MainFrame->GetProjectCrs().IsGeographic())
        ;
      else if (lastGeographic == true)
        {
          // geographic -> projected
          FrameRadius *= 111132.0;
      } else
        {
          // projected -> geographic
          FrameRadius /= 111132.0;
        }
    }
}

void MyMapView::DrawRasterLayer(wxGraphicsContext * gr, MapLayer * layer)
{
//
// drawing a Raster Layer
//
  if (!layer->GetRasterliteHandle())
    {
      // trying to open the RasterLite data source
      char db_path[1024];
      char table_prefix[1024];
      int len;
      void *handle;
      if (MainFrame->IsMemoryDatabase() == true)
        strcpy(db_path, ":memory:");
      else
        MainFrame->ConvertString(MainFrame->GetSqlitePath(), db_path, &len);
      MainFrame->ConvertString(layer->GetTableName(), table_prefix, &len);
      handle = rasterliteOpen(db_path, table_prefix);
      if (rasterliteIsError(handle))
        {
          rasterliteClose(handle);
          return;
        }
      rasterliteSetTransparentColor(handle, 255, 255, 255);
      rasterliteSetBackgroundColor(handle, 255, 255, 255);
      layer->SetRasterliteHandle(handle);
      ::wxInitAllImageHandlers();
    }
// trying to get the raster background image from the RasterLite data source
  wxBitmap bmp(wxImage(FrameWidth, FrameHeight));
  if (GetRaster(layer->GetRasterliteHandle(), &bmp) == false)
    {
      // error: marking a Magenta rectangle
      gr->SetBrush(wxBrush(wxColour(255, 0, 192)));
      gr->SetPen(wxPen(wxColour(192, 64, 192)));
      gr->DrawRectangle(0, 0, FrameWidth, FrameHeight);
      return;
    }
// drawing the raster background
  gr->DrawBitmap(bmp, 0, 0, FrameWidth, FrameHeight);
}

void MyMapView::DrawVectorLayer(wxGraphicsContext * gr, MapLayer * layer)
{
//
// drawing a Vector Layer
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  bool hasClasses = false;
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;
  double frameMinX = FrameMinX;
  double frameMaxX = FrameMaxX;
  double frameMinY = FrameMinY;
  double frameMaxY = FrameMaxY;
  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMaxY);
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      frameMinX = geom->MinX;
      frameMaxX = geom->MaxX;
      frameMinY = geom->MinY;
      frameMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              value = results[(i * columns) + 0];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              value = results[(i * columns) + 0];
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += layer->GetGeometryColumn();
  if (layer->GetClassifyColumn().Len() > 0)
    {
      sql += wxT("\", \"");
      sql += layer->GetClassifyColumn();
      hasClasses = true;
    }
  sql += wxT("\" FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE ");
  if (layer->IsLayerVirtual() == true)
    {
      // handling a VirtualShape
      sql += wxT("MbrIntersects(\"");
      sql += effectiveGeometry;
      sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  } else
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT("MbrIntersects(\"");
          sql += effectiveGeometry;
          sql += wxT("\", BuildMbr(?, ?, ?, ?))");
        }
    }
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 1, frameMaxX);
      sqlite3_bind_double(stmt, 2, frameMinX);
      sqlite3_bind_double(stmt, 3, frameMaxY);
      sqlite3_bind_double(stmt, 4, frameMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 1, frameMinX);
      sqlite3_bind_double(stmt, 2, frameMinY);
      sqlite3_bind_double(stmt, 3, frameMaxX);
      sqlite3_bind_double(stmt, 4, frameMaxY);
    }

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          gaiaGeomCollPtr geom = NULL;
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              if (reproject == true)
                {
                  // applying a reprojection
                  gaiaGeomCollPtr geom2 =
                    gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                              blob_size);
                  geom = gaiaTransform(geom2, proj_from, proj_to);
                  gaiaFreeGeomColl(geom2);
              } else
                geom =
                  gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                            blob_size);
            }
          if (hasClasses == true && geom)
            {
              // testing for SubClass
              int int_value;
              double dbl_value;
              char *str_value;
              wxString value;
              MapSubClass *subClass = NULL;
              if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
                {
                  int_value = sqlite3_column_int(stmt, 1);
                  dbl_value = int_value;
                  subClass = layer->GetSubClass(dbl_value);
                }
              if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
                {
                  dbl_value = sqlite3_column_double(stmt, 1);
                  subClass = layer->GetSubClass(dbl_value);
                }
              if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
                {
                  str_value = (char *) sqlite3_column_text(stmt, 1);
                  value = wxString::FromUTF8(str_value);
                  subClass = layer->GetSubClass(value);
                }
              if (subClass)
                {
                  if (subClass->IsVisible() == true)
                    {
                      // using SubClass
                      if (layer->GetGeometryType() == LAYER_POINT)
                        DrawPoint(gr, subClass, geom);
                      if (layer->GetGeometryType() == LAYER_LINESTRING)
                        DrawLinestring(gr, subClass, geom);
                      if (layer->GetGeometryType() == LAYER_POLYGON)
                        DrawPolygon(gr, subClass, geom);
                    }
                  gaiaFreeGeomColl(geom);
                  geom = NULL;
                }
            }
          if (geom)
            {
              // drawing the Default geometric entity
              if (layer->GetGeometryType() == LAYER_POINT)
                DrawPoint(gr, layer, geom);
              if (layer->GetGeometryType() == LAYER_LINESTRING)
                DrawLinestring(gr, layer, geom);
              if (layer->GetGeometryType() == LAYER_POLYGON)
                DrawPolygon(gr, layer, geom);
              if (geom)
                gaiaFreeGeomColl(geom);
            }
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

stop:
  return;
}

void MyMapView::FeedMapLabels(wxGraphicsContext * gr, MapLayer * layer,
                              MapLabelList * labelList)
{
//
// extracting Labels from some Layer
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;
  double frameMinX = FrameMinX;
  double frameMaxX = FrameMaxX;
  double frameMinY = FrameMinY;
  double frameMaxY = FrameMaxY;
  double labelWidth;
  double labelHeight;
  double labelDescent;
  double labelExternalLeading;
  wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
  if (layer->HasMapLabels() == false)
    return;
  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMaxY);
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      frameMinX = geom->MinX;
      frameMaxX = geom->MaxX;
      frameMinY = geom->MinY;
      frameMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              value = results[(i * columns) + 0];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              value = results[(i * columns) + 0];
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += layer->GetGeometryColumn();
  sql += wxT("\", \"");
  sql += layer->GetLabelColumn();
  sql += wxT("\" FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE ");
  if (layer->IsLayerVirtual() == true)
    {
      // handling a VirtualShape
      sql += wxT("MbrIntersects(\"");
      sql += effectiveGeometry;
      sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  } else
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT("MbrIntersects(\"");
          sql += layer->GetGeometryColumn();
          sql += wxT("\", BuildMbr(?, ?, ?, ?))");
        }
    }
  if (layer->HasLabelPriority() == true)
    {
      sql += wxT(" ORDER BY \"");
      sql += layer->GetLabelOrderByColumn();
      if (layer->IsLabelOrderByDescending() == true)
        sql += wxT("\" DESC");
      else
        sql += wxT("\" ASC");
    }
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 1, frameMaxX);
      sqlite3_bind_double(stmt, 2, frameMinX);
      sqlite3_bind_double(stmt, 3, frameMaxY);
      sqlite3_bind_double(stmt, 4, frameMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 1, frameMinX);
      sqlite3_bind_double(stmt, 2, frameMinY);
      sqlite3_bind_double(stmt, 3, frameMaxX);
      sqlite3_bind_double(stmt, 4, frameMaxY);
    }

// setting up the Font
  font.SetPointSize(layer->GetLabelPointSize());
  gr->SetFont(font, layer->GetLabelColor());

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          gaiaGeomCollPtr geom = NULL;
          wxString labelValue;
          char dummy[128];
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              if (reproject == true)
                {
                  // applying a reprojection
                  gaiaGeomCollPtr geom2 =
                    gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                              blob_size);
                  geom = gaiaTransform(geom2, proj_from, proj_to);
                  gaiaFreeGeomColl(geom2);
              } else
                geom =
                  gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                            blob_size);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
            {
              sprintf(dummy, "%d", sqlite3_column_int(stmt, 1));
              labelValue = wxString::FromUTF8(dummy);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
            {
              sprintf(dummy, "%1.6f", sqlite3_column_double(stmt, 1));
              labelValue = wxString::FromUTF8(dummy);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
            {
              labelValue =
                wxString::FromUTF8((char *) sqlite3_column_text(stmt, 1));
            }
          if (geom && labelValue.Len() > 0)
            {
              gaiaMbrGeometry(geom);
              gr->GetTextExtent(labelValue, &labelWidth, &labelHeight,
                                &labelDescent, &labelExternalLeading);
              PrepareLabels(labelList, geom, layer, labelValue, labelWidth,
                            labelHeight);
            }
          if (geom)
            gaiaFreeGeomColl(geom);
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

stop:
  return;
}

bool MyMapView::OutsideFrame(gaiaPointPtr point)
{
// checking if this POINT is outside the current screen frame
  if (point->X < FrameMinX)
    return true;
  if (point->X > FrameMaxX)
    return true;
  if (point->Y < FrameMinY)
    return true;
  if (point->Y > FrameMaxY)
    return true;
  return false;
}

bool MyMapView::OutsideFrame(gaiaLinestringPtr line)
{
// checking if this LINESTRING is outside the current screen frame
  if (line->MaxX < FrameMinX)
    return true;
  if (line->MinX > FrameMaxX)
    return true;
  if (line->MaxY < FrameMinY)
    return true;
  if (line->MinY > FrameMaxY)
    return true;
  return false;
}

bool MyMapView::OutsideFrame(gaiaPolygonPtr polygon)
{
// checking if this POLYGON is outside the current screen frame
  if (polygon->MaxX < FrameMinX)
    return true;
  if (polygon->MinX > FrameMaxX)
    return true;
  if (polygon->MaxY < FrameMinY)
    return true;
  if (polygon->MinY > FrameMaxY)
    return true;
  return false;
}

void MyMapView::PrepareLabels(MapLabelList * list, gaiaGeomCollPtr geom,
                              MapLayer * layer, wxString & label, double width,
                              double height)
{
// 
// creating Labels
// - separating elementary geometries
//
  gaiaGeomCollPtr newGeom;
  gaiaPointPtr point;
  gaiaLinestringPtr line;
  gaiaLinestringPtr newLine;
  gaiaPolygonPtr polygon;
  gaiaPolygonPtr newPolygon;
  gaiaRingPtr ring;
  gaiaRingPtr newRing;
  int iv;
  double x;
  double y;
  double z;
  double m;
  point = geom->FirstPoint;
  while (point)
    {
      if (OutsideFrame(point) == true)
        {
          point = point->Next;
          continue;
        }
      newGeom = gaiaAllocGeomColl();
      newGeom->DeclaredType = GAIA_POINT;
      gaiaAddPointToGeomColl(newGeom, point->X, point->Y);
      list->Add(layer, label, newGeom, width, height,
                layer->IsLabelAntiOverlapEnabled());
      point = point->Next;
    }
  line = geom->FirstLinestring;
  while (line)
    {
      if (OutsideFrame(line) == true)
        {
          line = line->Next;
          continue;
        }
      newGeom = gaiaAllocGeomColl();
      newGeom->DeclaredType = GAIA_LINESTRING;
      newLine = gaiaAddLinestringToGeomColl(newGeom, line->Points);
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &x, &y, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &x, &y, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &x, &y, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &x, &y);
            }
          gaiaSetPoint(newLine->Coords, iv, x, y);
        }
      list->Add(layer, label, newGeom, width, height,
                layer->IsLabelAntiOverlapEnabled());
      line = line->Next;
    }
  polygon = geom->FirstPolygon;
  while (polygon)
    {
      // NOTE: we are purposely ignoring any Interior Ring
      if (OutsideFrame(polygon) == true)
        {
          polygon = polygon->Next;
          continue;
        }
      ring = polygon->Exterior;
      newGeom = gaiaAllocGeomColl();
      newGeom->DeclaredType = GAIA_POLYGON;
      newPolygon = gaiaAddPolygonToGeomColl(newGeom, ring->Points, 0);
      newRing = newPolygon->Exterior;
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &x, &y, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &x, &y, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &x, &y, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &x, &y);
            }
          gaiaSetPoint(newRing->Coords, iv, x, y);
        }
      list->Add(layer, label, newGeom, width, height,
                layer->IsLabelAntiOverlapEnabled());
      polygon = polygon->Next;
    }
}

void MyMapView::DrawPoint(wxGraphicsContext * gr, MapSubClass * subClass,
                          gaiaGeomCollPtr geom)
{
// drawing a POINT/MULTIPOINT geometry
  gr->SetPen(subClass->GetPen());
  gr->SetBrush(subClass->GetBrush());
  gaiaPointPtr point = geom->FirstPoint;
  while (point)
    {
      int x = (int) ((point->X - FrameMinX) / PixelRatio);
      int y = FrameHeight - (int) ((point->Y - FrameMinY) / PixelRatio);
      if (subClass->GetSymbolType() == CLASSES_SYMBOL_SQUARE)
        gr->DrawRectangle(x - subClass->GetSize(), y - subClass->GetSize(),
                          subClass->GetSize() * 2, subClass->GetSize() * 2);
      else if (subClass->GetSymbolType() == CLASSES_SYMBOL_DIAMOND)
        {
          wxGraphicsPath path = gr->CreatePath();
          path.MoveToPoint(x, y - subClass->GetSize());
          path.AddLineToPoint(x + subClass->GetSize(), y);
          path.AddLineToPoint(x, y + subClass->GetSize());
          path.AddLineToPoint(x - subClass->GetSize(), y);
          path.AddLineToPoint(x, y - subClass->GetSize());
          gr->FillPath(path);
          gr->StrokePath(path);
      } else
        gr->DrawEllipse(x - subClass->GetSize(), y - subClass->GetSize(),
                        subClass->GetSize() * 2, subClass->GetSize() * 2);
      point = point->Next;
    }
}

void MyMapView::DrawPoint(wxGraphicsContext * gr, MapLayer * layer,
                          gaiaGeomCollPtr geom)
{
// drawing a POINT/MULTIPOINT geometry
  MyBitmap *symbol = layer->GetSymbol();
  gaiaPointPtr point = geom->FirstPoint;
  while (point)
    {
      int x = (int) ((point->X - FrameMinX) / PixelRatio);
      int y = FrameHeight - (int) ((point->Y - FrameMinY) / PixelRatio);
      if (symbol == NULL)
        {
          // drawing a default marker
          gr->SetPen(layer->GetPen());
          gr->SetBrush(layer->GetBrush());
          gr->DrawEllipse(x - 2, y - 2, 4, 4);
      } else
        {
          // drawing the symbol
          gr->DrawBitmap(layer->GetBitmap(), x - symbol->GetHotPointX(),
                         y - symbol->GetHotPointY(),
                         layer->GetBitmap().GetWidth(),
                         layer->GetBitmap().GetHeight());
        }
      point = point->Next;
    }
}

void MyMapView::DrawLinestring(wxGraphicsContext * gr, MapSubClass * subClass,
                               gaiaGeomCollPtr geom)
{
// drawing a LINESTRING/MULTILINESTRING geometry
  gr->SetPen(subClass->GetPen());
  gaiaLinestringPtr line = geom->FirstLinestring;
  while (line)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      wxGraphicsPath path = gr->CreatePath();
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &dx, &dy, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &dx, &dy, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      gr->StrokePath(path);
      line = line->Next;
    }
}

void MyMapView::DrawLinestring(wxGraphicsContext * gr, MapLayer * layer,
                               gaiaGeomCollPtr geom)
{
// drawing a LINESTRING/MULTILINESTRING geometry
  gr->SetPen(layer->GetPen());
  gaiaLinestringPtr line = geom->FirstLinestring;
  while (line)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      wxGraphicsPath path = gr->CreatePath();
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &dx, &dy, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &dx, &dy, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      gr->StrokePath(path);
      line = line->Next;
    }
}

void MyMapView::DrawPolygon(wxGraphicsContext * gr, MapSubClass * subClass,
                            gaiaGeomCollPtr geom)
{
// drawing a POLYGON/MULTIPOLYGON geometry
  gr->SetPen(subClass->GetPen());
  gr->SetBrush(subClass->GetBrush());
  gaiaPolygonPtr polyg = geom->FirstPolygon;
  while (polyg)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      int ib;
      wxGraphicsPath path = gr->CreatePath();
      gaiaRingPtr ring = polyg->Exterior;
      // exterior border
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      path.CloseSubpath();
      for (ib = 0; ib < polyg->NumInteriors; ib++)
        {
          // interior borders
          ring = polyg->Interiors + ib;
          for (iv = 0; iv < ring->Points; iv++)
            {
              if (ring->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
              } else if (ring->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
              } else if (ring->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
              } else
                {
                  gaiaGetPoint(ring->Coords, iv, &dx, &dy);
                }
              x = (int) ((dx - FrameMinX) / PixelRatio);
              y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
              if (iv == 0)
                {
                  path.MoveToPoint(x, y);
                  lastX = x;
                  lastY = y;
              } else
                {
                  if (x == lastX && y == lastY)
                    ;
                  else
                    {
                      path.AddLineToPoint(x, y);
                      lastX = x;
                      lastY = y;
                    }
                }
            }
          path.CloseSubpath();
        }
      gr->FillPath(path);
      gr->StrokePath(path);
      polyg = polyg->Next;
    }
}

void MyMapView::DrawPolygon(wxGraphicsContext * gr, MapLayer * layer,
                            gaiaGeomCollPtr geom)
{
// drawing a POLYGON/MULTIPOLYGON geometry
  if (layer->DrawBorderOk() == true)
    gr->SetPen(layer->GetPen());
  if (layer->IsToFill() == true)
    gr->SetBrush(layer->GetBrush());
  gaiaPolygonPtr polyg = geom->FirstPolygon;
  while (polyg)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      int ib;
      wxGraphicsPath path = gr->CreatePath();
      gaiaRingPtr ring = polyg->Exterior;
      // exterior border
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      path.CloseSubpath();
      for (ib = 0; ib < polyg->NumInteriors; ib++)
        {
          // interior borders
          ring = polyg->Interiors + ib;
          for (iv = 0; iv < ring->Points; iv++)
            {
              if (ring->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
              } else if (ring->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
              } else if (ring->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
              } else
                {
                  gaiaGetPoint(ring->Coords, iv, &dx, &dy);
                }
              x = (int) ((dx - FrameMinX) / PixelRatio);
              y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
              if (iv == 0)
                {
                  path.MoveToPoint(x, y);
                  lastX = x;
                  lastY = y;
              } else
                {
                  if (x == lastX && y == lastY)
                    ;
                  else
                    {
                      path.AddLineToPoint(x, y);
                      lastX = x;
                      lastY = y;
                    }
                }
            }
          path.CloseSubpath();
        }
      if (layer->IsToFill() == true)
        gr->FillPath(path);
      if (layer->DrawBorderOk() == true)
        gr->StrokePath(path);
      polyg = polyg->Next;
    }
}

void MyMapView::MarkPoint(wxGraphicsContext * gr, gaiaGeomCollPtr geom)
{
// marking a POINT/MULTIPOINT geometry
  if (!geom)
    return;
  gr->SetPen(MarkerGraphic.GetPen());
  gr->SetBrush(MarkerGraphic.GetBrush());
  gaiaPointPtr point = geom->FirstPoint;
  while (point)
    {
      int x = (int) ((point->X - FrameMinX) / PixelRatio);
      int y = FrameHeight - (int) ((point->Y - FrameMinY) / PixelRatio);
      gr->DrawEllipse(x - 18, y - 18, 36, 36);
      point = point->Next;
    }
}

void MyMapView::MarkLinestring(wxGraphicsContext * gr, gaiaGeomCollPtr geom)
{
// marking a LINESTRING/MULTILINESTRING geometry
  if (!geom)
    return;
  gr->SetPen(MarkerGraphic.GetPen());
  gaiaLinestringPtr line = geom->FirstLinestring;
  while (line)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      wxGraphicsPath path = gr->CreatePath();
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &dx, &dy, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &dx, &dy, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      gr->StrokePath(path);
      line = line->Next;
    }
}

void MyMapView::MarkPolygon(wxGraphicsContext * gr, gaiaGeomCollPtr geom)
{
// marking a POLYGON/MULTIPOLYGON geometry
  if (!geom)
    return;
  gr->SetPen(MarkerGraphic.GetPen());
  gr->SetBrush(MarkerGraphic.GetBrush());
  gaiaPolygonPtr polyg = geom->FirstPolygon;
  while (polyg)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      int ib;
      wxGraphicsPath path = gr->CreatePath();
      gaiaRingPtr ring = polyg->Exterior;
      // exterior border
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      path.CloseSubpath();
      for (ib = 0; ib < polyg->NumInteriors; ib++)
        {
          // interior borders
          ring = polyg->Interiors + ib;
          for (iv = 0; iv < ring->Points; iv++)
            {
              if (ring->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
              } else if (ring->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
              } else if (ring->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
              } else
                {
                  gaiaGetPoint(ring->Coords, iv, &dx, &dy);
                }
              x = (int) ((dx - FrameMinX) / PixelRatio);
              y = FrameHeight - (int) ((dy - FrameMinY) / PixelRatio);
              if (iv == 0)
                {
                  path.MoveToPoint(x, y);
                  lastX = x;
                  lastY = y;
              } else
                {
                  if (x == lastX && y == lastY)
                    ;
                  else
                    {
                      path.AddLineToPoint(x, y);
                      lastX = x;
                      lastY = y;
                    }
                }
            }
          path.CloseSubpath();
        }
      if (MarkerGraphic.IsToFill() == true)
        gr->FillPath(path);
      if (MarkerGraphic.OkDrawBorder() == true)
        gr->StrokePath(path);
      polyg = polyg->Next;
    }
}

void MyMapView::ZoomTo(double minx, double miny, double maxx, double maxy)
{
// performs a ZOOM based on the given rectangle
  int i;
  double max_radius;
  double ext_x = MapMaxX - MapMinX;
  double ext_y = MapMaxY - MapMinY;
  double rX = (maxx - minx) / 2.0;
  double rY = (maxy - miny) / 2.0;
  double reqRadius;
  if (ext_x > ext_y)
    max_radius = ext_x / 2.0;
  else
    max_radius = ext_y / 2.0;
  FrameCenterX = minx + rX;
  FrameCenterY = miny + rY;
  if (rX > rY)
    reqRadius = rX;
  else
    reqRadius = rY;
// adjusting the map coverage radius and zoom factor
  if (MainFrame->GetProjectCrs().IsGeographic() == true)
    {
      // geographic coordinates
      max_radius *= 36000.0;
      reqRadius *= 36000.0;
    }
  max_radius -= 1.0;
  for (i = Zoom.GetMin(); i <= Zoom.GetMax(); i++)
    {
      FrameRadius = pow(max_radius, ((double) i / (double) Zoom.GetMax()));
      if (FrameRadius >= reqRadius)
        break;
    }
  Zoom.SetValue(i);
  if (MainFrame->GetProjectCrs().IsGeographic() == true)
    FrameRadius /= 36000.0;
  LastZoom = Zoom.GetValue();

  PrepareMap();
}

void MyMapView::ZoomToMarkedEntities()
{
// performs a ZOOM IN on selected entities
  double minx = DBL_MAX;
  double miny = DBL_MAX;
  double maxx = 0.0 - DBL_MAX;
  double maxy = 0.0 - DBL_MAX;
  bool ok = false;
  gaiaGeomCollPtr geom;
  GeometryToMark *pMark = GeomsToMark.GetFirst();
  while (pMark)
    {
      geom = pMark->Geometry();
      if (geom)
        {
          if (geom->MinX < minx)
            minx = geom->MinX;
          if (geom->MinY < miny)
            miny = geom->MinY;
          if (geom->MaxX > maxx)
            maxx = geom->MaxX;
          if (geom->MaxY > maxy)
            maxy = geom->MaxY;
          ok = true;
        }
      pMark = pMark->GetNext();
    }
  if (ok == true)
    ZoomTo(minx, miny, maxx, maxy);
}

void MyMapView::Identify(MapLayer * layer, int mouse_x, int mouse_y)
{
//
// Identify [Vector Layer]
//
  IdentifyEntitiesList *list = NULL;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char proj_from[1024];
  char proj_to[1024];
  char dummy[128];
  bool reproject = false;
  wxString LabelValue;
  double queryMinX;
  double queryMaxX;
  double queryMinY;
  double queryMaxY;
  queryMinX = FrameMinX + ((double) (mouse_x - 8) * PixelRatio);
  queryMaxX = FrameMinX + ((double) (mouse_x + 8) * PixelRatio);
  queryMinY = FrameMaxY - ((double) (mouse_y + 8) * PixelRatio);
  queryMaxY = FrameMaxY - ((double) (mouse_y - 8) * PixelRatio);

  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, queryMinX, queryMinY);
      gaiaAddPointToGeomColl(geom2, queryMaxX, queryMinY);
      gaiaAddPointToGeomColl(geom2, queryMaxX, queryMaxY);
      gaiaAddPointToGeomColl(geom2, queryMinX, queryMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      queryMinX = geom->MinX;
      queryMaxX = geom->MaxX;
      queryMinY = geom->MinY;
      queryMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              value = results[(i * columns) + 0];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              value = results[(i * columns) + 0];
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT ROWID, \"");
  sql += layer->GetGeometryColumn();
  if (layer->GetLabelColumn().Len() > 0)
    {
      sql += wxT("\", \"");
      sql += layer->GetLabelColumn();
    }
  sql += wxT("\" FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE Intersects(\"");
  sql += layer->GetGeometryColumn();
  sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  if (layer->IsLayerVirtual() != true)
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT(" AND ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT(" AND ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT(" AND ROWID IN (SELECT ROWID FROM \"");
          sql += effectiveTable;
          sql += wxT("\" WHERE MbrIntersects(\"");
          sql += effectiveGeometry;
          sql += wxT("\", BuildMbr(?, ?, ?, ?)))");
        }
    }

  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  sqlite3_bind_double(stmt, 1, queryMinX);
  sqlite3_bind_double(stmt, 2, queryMinY);
  sqlite3_bind_double(stmt, 3, queryMaxX);
  sqlite3_bind_double(stmt, 4, queryMaxY);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 5, queryMaxX);
      sqlite3_bind_double(stmt, 6, queryMinX);
      sqlite3_bind_double(stmt, 7, queryMaxY);
      sqlite3_bind_double(stmt, 8, queryMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 5, queryMinX);
      sqlite3_bind_double(stmt, 6, queryMinY);
      sqlite3_bind_double(stmt, 7, queryMaxX);
      sqlite3_bind_double(stmt, 8, queryMaxY);
    }

  list = new IdentifyEntitiesList();

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          if (sqlite3_column_type(stmt, 0) == SQLITE_INTEGER)
            {
              gaiaGeomCollPtr geom = NULL;
              wxString labelValue;
              sqlite3_int64 rowId = sqlite3_column_int64(stmt, 0);
              if (sqlite3_column_type(stmt, 1) == SQLITE_BLOB)
                {
                  // fetching Geometry
                  const void *blob = sqlite3_column_blob(stmt, 1);
                  int blob_size = sqlite3_column_bytes(stmt, 1);
                  if (reproject == true)
                    {
                      // applying a reprojection
                      gaiaGeomCollPtr geom2 =
                        gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                                  blob_size);
                      geom = gaiaTransform(geom2, proj_from, proj_to);
                      gaiaFreeGeomColl(geom2);
                  } else
                    geom =
                      gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                                blob_size);
                }
              if (layer->GetLabelColumn().Len() > 0)
                {
                  if (sqlite3_column_type(stmt, 2) == SQLITE_INTEGER)
                    {
                      sprintf(dummy, "%d", sqlite3_column_int(stmt, 2));
                      labelValue = wxString::FromUTF8(dummy);
                    }
                  if (sqlite3_column_type(stmt, 2) == SQLITE_FLOAT)
                    {
                      sprintf(dummy, "%1.6f", sqlite3_column_double(stmt, 2));
                      labelValue = wxString::FromUTF8(dummy);
                    }
                  if (sqlite3_column_type(stmt, 2) == SQLITE_TEXT)
                    {
                      labelValue =
                        wxString::FromUTF8((char *)
                                           sqlite3_column_text(stmt, 2));
                    }
                }
              list->Add(rowId, geom, labelValue);
            }

      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

  if (list->GetCount() < 1)
    {
      // no entity found
      delete list;
  } else
    {
      // showing the Entities List
      ClearMapTip();
      IdentifyDialog dlg;
      dlg.Create(this, MainFrame, layer, list);
      dlg.ShowModal();
    }
  return;

stop:
  if (list)
    delete list;
  return;
}

void MyMapView::SelectNetworkNode(int mouse_x, int mouse_y)
{
//
// NETWORK: dynamic selection of network nodes for routing
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int ret;
  wxString sql;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;
  double queryMinX;
  double queryMaxX;
  double queryMinY;
  double queryMaxY;
  double mx;
  double my;
  double dist;
  double minDist;
  sqlite3_int64 nodeId;
  const unsigned char *nodeTxt;
  char type;
  double x;
  double y;
  MainFrame->GetNetwork()->UnsetCurrentNode();
  mx = FrameMinX + ((double) (mouse_x) * PixelRatio);
  my = FrameMaxY - ((double) (mouse_y) * PixelRatio);
  queryMinX = FrameMinX + ((double) (mouse_x - 4) * PixelRatio);
  queryMaxX = FrameMinX + ((double) (mouse_x + 4) * PixelRatio);
  queryMinY = FrameMaxY - ((double) (mouse_y + 4) * PixelRatio);
  queryMaxY = FrameMaxY - ((double) (mouse_y - 4) * PixelRatio);

  if (MainFrame->GetNetwork()->GetSrid() ==
      MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // the NodesAuxTable uses a SRID not identical to the one set for the Project
      if (MainFrame->GetNetwork()->GetSrid() >= 0
          && MainFrame->GetProjectCrs().GetSrid() >= 0)
        {
          bool ok_from =
            MainFrame->GetProjParams(MainFrame->GetNetwork()->GetSrid(),
                                     proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg =
                wxT("Unable to apply reprojection for NodesAuxTable:\n\n");
              msg += MainFrame->GetNetwork()->GetNodesAuxTable();
              msg += wxT(".Geometry\n\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              goto stop;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, queryMinX, queryMinY);
      gaiaAddPointToGeomColl(geom2, queryMaxX, queryMinY);
      gaiaAddPointToGeomColl(geom2, queryMaxX, queryMaxY);
      gaiaAddPointToGeomColl(geom2, queryMinX, queryMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      queryMinX = geom->MinX;
      queryMaxX = geom->MaxX;
      queryMinY = geom->MinY;
      queryMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
      // applying reprojection to current mouse coords
      geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, mx, my);
      geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      mx = geom->MinX;
      my = geom->MinY;
      gaiaFreeGeomColl(geom);
    }
// preparing the SQL statement
  sql = wxT("SELECT node, X(Geometry), Y(Geometry) FROM \"");
  sql += MainFrame->GetNetwork()->GetNodesAuxTable();
  sql += wxT("\" WHERE Intersects(Geometry, BuildMbr(?, ?, ?, ?)) AND ");
  if (MainFrame->GetNetwork()->IsAuxNodesRTree() == true)
    {
      // using the R*Tree Spatial Index
      sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
      sql += MainFrame->GetNetwork()->GetNodesAuxTable();
      sql +=
        wxT
        ("_Geometry\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
  } else
    {
      // applying simple MBR filtering
      sql += wxT("ROWID IN (SELECT ROWID FROM \"");
      sql += MainFrame->GetNetwork()->GetNodesAuxTable();
      sql += wxT("\" WHERE MbrIntersects(Geometry, BuildMbr(?, ?, ?, ?)))");
    }

  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  sqlite3_bind_double(stmt, 1, queryMinX);
  sqlite3_bind_double(stmt, 2, queryMinY);
  sqlite3_bind_double(stmt, 3, queryMaxX);
  sqlite3_bind_double(stmt, 4, queryMaxY);
  if (MainFrame->GetNetwork()->IsAuxNodesRTree() == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 5, queryMaxX);
      sqlite3_bind_double(stmt, 6, queryMinX);
      sqlite3_bind_double(stmt, 7, queryMaxY);
      sqlite3_bind_double(stmt, 8, queryMinY);
  } else
    {
      // simple Mbr filtering
      sqlite3_bind_double(stmt, 5, queryMinX);
      sqlite3_bind_double(stmt, 6, queryMinY);
      sqlite3_bind_double(stmt, 7, queryMaxX);
      sqlite3_bind_double(stmt, 8, queryMaxY);
    }

  minDist = DBL_MAX;
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          type = '\0';
          x = DBL_MAX;
          y = DBL_MAX;
          if (sqlite3_column_type(stmt, 0) == SQLITE_INTEGER)
            {
              nodeId = sqlite3_column_int64(stmt, 0);
              type = 'I';
            }
          if (sqlite3_column_type(stmt, 0) == SQLITE_TEXT)
            {
              nodeTxt = sqlite3_column_text(stmt, 0);
              type = 'T';
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
            x = sqlite3_column_double(stmt, 1);
          if (sqlite3_column_type(stmt, 2) == SQLITE_FLOAT)
            y = sqlite3_column_double(stmt, 2);
          if (type != '\0' && x != DBL_MAX && y != DBL_MAX)
            {
              dist = sqrt(((x - mx) * (x - mx)) + ((y - my) * (y - my)));
              if (dist < minDist)
                {
                  minDist = dist;
                  if (type == 'T')
                    MainFrame->GetNetwork()->SetCurrentNode(nodeTxt, x, y);
                  else
                    MainFrame->GetNetwork()->SetCurrentNode(nodeId, x, y);
                }
            }

      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);
  if (MainFrame->GetNetwork()->GetCurrentNode()->IsValid() == true
      && reproject == true)
    {
      // applying reprojection to current node
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2,
                             MainFrame->GetNetwork()->GetCurrentNode()->GetX(),
                             MainFrame->GetNetwork()->GetCurrentNode()->GetY());
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_from, proj_to);
      gaiaFreeGeomColl(geom2);
      MainFrame->GetNetwork()->GetCurrentNode()->SetCoords(geom->MinX,
                                                           geom->MinY);
      gaiaFreeGeomColl(geom);
    }
  DynamicDraw(false);
  return;

stop:
  MainFrame->GetNetwork()->UnsetCurrentNode();
  DynamicDraw(false);
  return;
}

void MyMapView::OnTheFlyIdentify(MapLayer * layer, int mouse_x, int mouse_y)
{
//
// on-the-fly Identify [Vector Layer]
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char proj_from[1024];
  char proj_to[1024];
  char dummy[128];
  bool reproject = false;
  wxString LabelValue;
  double queryMinX;
  double queryMaxX;
  double queryMinY;
  double queryMaxY;
  queryMinX = FrameMinX + ((double) (mouse_x - 4) * PixelRatio);
  queryMaxX = FrameMinX + ((double) (mouse_x + 4) * PixelRatio);
  queryMinY = FrameMaxY - ((double) (mouse_y + 4) * PixelRatio);
  queryMaxY = FrameMaxY - ((double) (mouse_y - 4) * PixelRatio);

  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, queryMinX, queryMinY);
      gaiaAddPointToGeomColl(geom2, queryMaxX, queryMinY);
      gaiaAddPointToGeomColl(geom2, queryMaxX, queryMaxY);
      gaiaAddPointToGeomColl(geom2, queryMinX, queryMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      queryMinX = geom->MinX;
      queryMaxX = geom->MaxX;
      queryMinY = geom->MinY;
      queryMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              value = results[(i * columns) + 0];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              value = results[(i * columns) + 0];
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += layer->GetLabelColumn();
  sql += wxT("\" FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE Intersects(\"");
  sql += layer->GetGeometryColumn();
  sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  if (layer->IsLayerVirtual() != true)
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT(" AND ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT(" AND ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT(" AND ROWID IN (SELECT ROWID FROM \"");
          sql += effectiveTable;
          sql += wxT("\" WHERE MbrIntersects(\"");
          sql += effectiveGeometry;
          sql += wxT("\", BuildMbr(?, ?, ?, ?)))");
        }
    }

  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  sqlite3_bind_double(stmt, 1, queryMinX);
  sqlite3_bind_double(stmt, 2, queryMinY);
  sqlite3_bind_double(stmt, 3, queryMaxX);
  sqlite3_bind_double(stmt, 4, queryMaxY);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 5, queryMaxX);
      sqlite3_bind_double(stmt, 6, queryMinX);
      sqlite3_bind_double(stmt, 7, queryMaxY);
      sqlite3_bind_double(stmt, 8, queryMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 5, queryMinX);
      sqlite3_bind_double(stmt, 6, queryMinY);
      sqlite3_bind_double(stmt, 7, queryMaxX);
      sqlite3_bind_double(stmt, 8, queryMaxY);
    }

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          if (sqlite3_column_type(stmt, 0) == SQLITE_INTEGER)
            {
              sprintf(dummy, "%d", sqlite3_column_int(stmt, 0));
              LabelValue = wxString::FromUTF8(dummy);
              break;
            }
          if (sqlite3_column_type(stmt, 0) == SQLITE_FLOAT)
            {
              sprintf(dummy, "%1.6f", sqlite3_column_double(stmt, 0));
              LabelValue = wxString::FromUTF8(dummy);
              break;
            }
          if (sqlite3_column_type(stmt, 0) == SQLITE_TEXT)
            {
              LabelValue =
                wxString::FromUTF8((char *) sqlite3_column_text(stmt, 0));
              break;
            }

      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);
  if (LabelValue.Len() > 0)
    ShowMapTip(LabelValue, mouse_x, mouse_y);
  else
    ClearMapTip();

stop:
  return;
}

double MyMapView::InternalRound(double value)
{
// replacing the C99 round() function 
  double min = floor(value);
  if (fabs(value - min) < 0.5)
    return min;
  return min + 1.0;
}

int MyMapView::IntRound(double value)
{
/* replacing the C99 round() function */
  double min = floor(value);
  if (fabs(value - min) < 0.5)
    return (int) min;
  return (int) (min + 1.0);
}

bool MyMapView::GetRaster(void *handle, wxBitmap * bmp)
{
//
// trying to build the required raster image from the RasterLite Data Source
//
  int ret;
  double pixel_x_size;
  double pixel_y_size;
  int use_rtree;
  sqlite3_stmt *stmt = NULL;
  double map_frame_width = (double) FrameWidth * PixelRatio;
  double map_frame_height = (double) FrameHeight * PixelRatio;
  double min_x = FrameCenterX - (map_frame_width / 2.0);
  double max_x = FrameCenterX + (map_frame_width / 2.0);
  double min_y = FrameCenterY - (map_frame_height / 2.0);
  double max_y = FrameCenterY + (map_frame_height / 2.0);
  if (handle == NULL)
    {
      fprintf(stderr, "invalid datasource\n");
      fflush(stderr);
      return false;
    }
  if (FrameWidth < 64 || FrameWidth > 32768 || FrameHeight < 64
      || FrameHeight > 32768)
    {
      fprintf(stderr, "invalid raster dims [%dh X %dv]\n", FrameWidth,
              FrameHeight);
      fflush(stderr);
      return false;
    }
  if (rasterliteGetBestAccess
      (handle, PixelRatio, &pixel_x_size, &pixel_y_size, &stmt,
       &use_rtree) != RASTERLITE_OK)
    {
      fprintf(stderr, "invalid Raster access method\n");
      fflush(stderr);
      return false;
    }
  wxMemoryDC *dc = NULL;
  dc = new wxMemoryDC(*bmp);
  if (dc->IsOk() == false)
    {
      delete dc;
      return false;
    }
// setting a white baground
  dc->SetBrush(wxBrush(wxColour(255, 255, 255)));
  dc->SetPen(wxPen(wxColour(255, 255, 255)));
  dc->DrawRectangle(0, 0, FrameWidth, FrameHeight);
// binding query params 
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (use_rtree)
    {
      // using the Spatial Index R*Tree 
      sqlite3_bind_double(stmt, 1, max_x);
      sqlite3_bind_double(stmt, 2, min_x);
      sqlite3_bind_double(stmt, 3, max_y);
      sqlite3_bind_double(stmt, 4, min_y);
  } else
    {
      // plain Table Scan 
      sqlite3_bind_double(stmt, 1, min_x);
      sqlite3_bind_double(stmt, 2, min_y);
      sqlite3_bind_double(stmt, 3, max_x);
      sqlite3_bind_double(stmt, 4, max_y);
    }
  sqlite3_bind_double(stmt, 5, pixel_x_size);
  sqlite3_bind_double(stmt, 6, pixel_y_size);
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          // retrieving query values 
          gaiaGeomCollPtr geom = NULL;
          wxImage *img = NULL;
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry 
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              geom =
                gaiaFromSpatiaLiteBlobWkb((const unsigned char *)
                                          blob, blob_size);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_BLOB)
            {
              // fetching Raster Image 
              const unsigned char *blob =
                (const unsigned char *) sqlite3_column_blob(stmt, 1);
              int blob_size = sqlite3_column_bytes(stmt, 1);
              int type = gaiaGuessBlobType(blob, blob_size);
              if (type == GAIA_JPEG_BLOB || type == GAIA_EXIF_BLOB
                  || type == GAIA_EXIF_GPS_BLOB || type == GAIA_PNG_BLOB
                  || type == GAIA_GIF_BLOB || type == GAIA_TIFF_BLOB)
                {
                  wxMemoryInputStream reader(blob, blob_size);
                  img = new wxImage(reader);
                }
            }
          if (geom && img)
            {
              // resizing the image [tile] 
              double pre_FrameWidth =
                InternalRound(((double) (img->GetWidth()) * pixel_x_size) /
                              PixelRatio);
              double pre_FrameHeight =
                InternalRound(((double) (img->GetHeight()) * pixel_y_size) /
                              PixelRatio);
              int new_FrameWidth = (int) pre_FrameWidth + 1;
              int new_FrameHeight = (int) pre_FrameHeight + 1;
              double x = (geom->MinX - min_x) / PixelRatio;
              double y =
                (double) FrameHeight - ((geom->MaxY - min_y) / PixelRatio);
              if (new_FrameWidth > (FrameWidth * 2)
                  || new_FrameHeight > (FrameHeight * 2))
                {
                  // TOO BIG: drawing a gray rectangle 
                  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
                  dc->SetPen(wxPen(wxColour(192, 192, 192)));
                  dc->DrawRectangle(IntRound(x), IntRound(y), new_FrameWidth,
                                    new_FrameHeight);
              } else
                {
                  // resizing the raster tile 
                  wxImage img2(new_FrameWidth, new_FrameHeight);
                  if (new_FrameWidth == FrameWidth
                      && new_FrameHeight == FrameHeight)
                    img2 = img->Copy();
                  else
                    img2 =
                      img->Rescale(new_FrameWidth, new_FrameHeight,
                                   wxIMAGE_QUALITY_NORMAL);
                  // drawing the raster tile
                  wxBitmap bitmap = wxBitmap(img2);
                  wxMask *mask = new wxMask(bitmap, wxColour(255, 255, 255));
                  bitmap.SetMask(mask);
                  dc->DrawBitmap(bitmap, (wxCoord) IntRound(x),
                                 (wxCoord) IntRound(y), true);
                }
            }
          if (geom)
            gaiaFreeGeomColl(geom);
          if (img)
            delete img;
      } else
        {
          fprintf(stderr, "Raster: SQL error\n");
          fflush(stderr);
          delete dc;
          return false;
        }
    }
  delete dc;
  return true;
}

bool MyMapView::IsMapTipShown()
{
//
// tests if some MapTip is currently shown
//
  if (!MapTip)
    return false;
  return true;
}

void MyMapView::ShowMapTip(wxString & text, int x, int y)
{
//
// shows the Map Tip
//
  ClearMapTip();
  MouseIdentifyX = x;
  MouseIdentifyY = y;
  MapTip = new MyTipWindow(this, text, x, y);
}

void MyMapView::ClearMapTip()
{
//
// destroys the Map Tip [if it exists]
//
  if (MapTip)
    {
      MapTip->Close();
      if (MapTip)
        MapTip->Destroy();
    }
  MapTip = NULL;
  MouseIdentifyX = -1;
  MouseIdentifyY = -1;
}

MyTipWindow::MyTipWindow(MyMapView * parent, wxString & text, int x,
                         int y):wxWindow(parent, wxID_ANY, wxDefaultPosition,
                                         wxDefaultSize, wxBORDER_NONE)
{
  int xx = x + 5;
  int yy = y + 5;
  Parent = parent;
  Text = text;
  MouseX = x;
  MouseY = y;
// computing the text extent
  wxClientDC dc(this);
  dc.SetFont(wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
  wxSize sz = dc.GetTextExtent(Text);
  wxSize szParent = Parent->GetClientSize();
  if ((sz.GetWidth() + 16 + MouseX) >= szParent.GetWidth())
    xx = MouseX - sz.GetWidth() - 15;
  if ((sz.GetHeight() + 16 + MouseY) >= szParent.GetHeight())
    yy = MouseY - sz.GetHeight() - 15;
  SetSize(xx, yy, sz.GetWidth() + 10, sz.GetHeight() + 10);
  Show();
// connexting event handlers
  Connect(wxID_ANY, wxEVT_PAINT,
          (wxObjectEventFunction) & MyTipWindow::OnPaint);
  Connect(wxID_ANY, wxEVT_ERASE_BACKGROUND,
          (wxObjectEventFunction) & MyTipWindow::OnEraseBackground);
  Connect(wxID_ANY, wxEVT_MOTION,
          wxMouseEventHandler(MyTipWindow::OnMouseEvent), NULL, this);
}

bool MyTipWindow::IsToBeErased(int x, int y)
{
  if (abs(x - MouseX) > 4)
    return true;
  if (abs(y - MouseY) > 4)
    return true;
  return false;
}

void MyTipWindow::OnPaint(wxPaintEvent & WXUNUSED(event))
{
  wxPaintDC dc(this);
  wxSize sz = GetClientSize();
  dc.SetBrush(wxBrush(wxColour(255, 255, 192)));
  dc.SetPen(wxPen(wxColour(64, 64, 192)));
  dc.DrawRectangle(0, 0, sz.GetWidth(), sz.GetHeight());
  dc.SetTextBackground(wxColour(255, 255, 192));
  dc.SetTextForeground(wxColour(64, 64, 192));
  dc.SetFont(wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
  dc.DrawText(Text, 5, 5);
}

void MyTipWindow::OnMouseEvent(wxMouseEvent & event)
{
//
// MOUSE motion - event handler
// 
  event.Skip();
}

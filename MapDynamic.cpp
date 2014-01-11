/*
/ MapDynamic.cpp
/ Map Editing functions 
/
/ version 1.0, 2009 April 27
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
#include <float.h>

#include "icons/node_from.xpm"
#include "icons/node_to.xpm"

void MyMapView::DynamicShowMapFrameSelection(double xx, double yy)
{
//
// updates the current Map Frame Selection
//
  double minX;
  double minY;
  double maxX;
  double maxY;
  int x;
  int y;
  int endx;
  int endy;
  int width;
  int height;
  if (GetMapFrameSelection(xx, yy, &minX, &minY, &maxX, &maxY) == false)
    return;
  if (DynamicMapBitmap.IsOk() && ScreenBitmap.IsOk())
    {
      wxMemoryDC *dynDC = new wxMemoryDC(DynamicMapBitmap);
      wxMemoryDC *dc = new wxMemoryDC(ScreenBitmap);
      dc->Blit(0, 0, BitmapWidth, BitmapHeight, dynDC, 0, 0);
      delete dynDC;
      wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
      gr->SetBrush(wxBrush(wxColour(255, 255, 0, 64)));
      gr->SetPen(wxPen(wxColour(255, 0, 0), 2, wxDOT));
      x = (int) ((minX - FrameMinX) / PixelRatio);
      y = FrameHeight - (int) ((maxY - FrameMinY) / PixelRatio);
      endx = (int) ((maxX - FrameMinX) / PixelRatio);
      endy = FrameHeight - (int) ((minY - FrameMinY) / PixelRatio);
      width = endx - x;
      height = endy - y;
      gr->DrawRectangle(x, y, width, height);
      delete gr;
      delete dc;
      Refresh();
    }
}

void MyMapView::DynamicDrawMapFrameSelection(wxGraphicsContext * gr)
{
//
// draws the current Map Frame Selection
//
  double minX;
  double minY;
  double maxX;
  double maxY;
  int x;
  int y;
  int endx;
  int endy;
  int width;
  int height;
  if (GetMapFrameSelection(&minX, &minY, &maxX, &maxY) == false)
    return;
  gr->SetBrush(wxBrush(wxColour(255, 255, 0, 64)));
  gr->SetPen(wxPen(wxColour(255, 0, 0), 2, wxDOT));
  x = (int) ((minX - FrameMinX) / PixelRatio);
  y = FrameHeight - (int) ((maxY - FrameMinY) / PixelRatio);
  endx = (int) ((maxX - FrameMinX) / PixelRatio);
  endy = FrameHeight - (int) ((minY - FrameMinY) / PixelRatio);
  width = endx - x;
  height = endy - y;
  gr->DrawRectangle(x, y, width, height);
}

void MyMapView::DynamicDrawVertex(wxGraphicsContext * gr)
{
//
// draws the current dynamic Vertex on the map
//
  int x;
  int y;
  gr->SetBrush(wxBrush(wxColour(255, 255, 255)));
  gr->SetPen(wxPen(wxColour(0, 0, 0), 1));
  x = (int) ((CurrentVertexCoords.X - FrameMinX) / PixelRatio);
  y = FrameHeight - (int) ((CurrentVertexCoords.Y - FrameMinY) / PixelRatio);
  gr->DrawRectangle(x - 4, y - 4, 8, 8);
  gr->SetPen(wxPen(wxColour(255, 0, 0), 1));
  gr->StrokeLine(x - 4, y - 4, x + 4, y + 4);
  gr->StrokeLine(x - 4, y + 4, x + 4, y - 4);
}

void MyMapView::DynamicDrawSegment(wxGraphicsContext * gr)
{
//
// draws the current dynamic Segment on the map
//
  int x0;
  int y0;
  int x1;
  int y1;
  double xx;
  double yy;
  double z;
  double m;
  bool ok = false;
  if (CurrentLinestring)
    {
      if (CurrentSegmentIndex >= 1
          && CurrentSegmentIndex < CurrentLinestring->Points)
        {
          if (CurrentLinestring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(CurrentLinestring->Coords,
                              CurrentSegmentIndex - 1, &xx, &yy, &z);
          } else if (CurrentLinestring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(CurrentLinestring->Coords,
                              CurrentSegmentIndex - 1, &xx, &yy, &m);
          } else if (CurrentLinestring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(CurrentLinestring->Coords,
                               CurrentSegmentIndex - 1, &xx, &yy, &z, &m);
          } else
            {
              gaiaGetPoint(CurrentLinestring->Coords, CurrentSegmentIndex - 1,
                           &xx, &yy);
            }
          x0 = (int) ((xx - FrameMinX) / PixelRatio);
          y0 = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
          if (CurrentLinestring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(CurrentLinestring->Coords, CurrentSegmentIndex,
                              &xx, &yy, &z);
          } else if (CurrentLinestring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(CurrentLinestring->Coords, CurrentSegmentIndex,
                              &xx, &yy, &m);
          } else if (CurrentLinestring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(CurrentLinestring->Coords, CurrentSegmentIndex,
                               &xx, &yy, &z, &m);
          } else
            {
              gaiaGetPoint(CurrentLinestring->Coords, CurrentSegmentIndex, &xx,
                           &yy);
            }
          x1 = (int) ((xx - FrameMinX) / PixelRatio);
          y1 = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
          ok = true;
        }
  } else if (CurrentRing)
    {
      if (CurrentSegmentIndex >= 1 && CurrentSegmentIndex < CurrentRing->Points)
        {
          if (CurrentRing->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(CurrentRing->Coords, CurrentSegmentIndex - 1, &xx,
                              &yy, &z);
          } else if (CurrentRing->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(CurrentRing->Coords, CurrentSegmentIndex - 1, &xx,
                              &yy, &m);
          } else if (CurrentRing->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(CurrentRing->Coords, CurrentSegmentIndex - 1,
                               &xx, &yy, &z, &m);
          } else
            {
              gaiaGetPoint(CurrentRing->Coords, CurrentSegmentIndex - 1, &xx,
                           &yy);
            }
          x0 = (int) ((xx - FrameMinX) / PixelRatio);
          y0 = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
          if (CurrentRing->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(CurrentRing->Coords, CurrentSegmentIndex, &xx,
                              &yy, &m);
          } else if (CurrentRing->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(CurrentRing->Coords, CurrentSegmentIndex, &xx,
                              &yy, &m);
          } else if (CurrentRing->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(CurrentRing->Coords, CurrentSegmentIndex, &xx,
                               &yy, &z, &m);
          } else
            {
              gaiaGetPoint(CurrentRing->Coords, CurrentSegmentIndex, &xx, &yy);
            }
          x1 = (int) ((xx - FrameMinX) / PixelRatio);
          y1 = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
          ok = true;
        }
    }
  if (ok == false)
    return;
  gr->SetPen(wxPen(wxColour(255, 255, 255), 5));
  gr->StrokeLine(x0, y0, x1, y1);
  gr->SetPen(wxPen(wxColour(255, 0, 0), 3));
  gr->StrokeLine(x0, y0, x1, y1);
}

void MyMapView::DynamicDrawGeometry(wxGraphicsContext * gr,
                                    gaiaGeomCollPtr geom)
{
//
// draws the current dynamic Geometry on the map
//  
  int x;
  int y;
  int iv;
  int ib;
  double xx;
  double yy;
  double z;
  double m;
  wxGraphicsPath path;
  wxGraphicsPath path2;
  gaiaPointPtr pt;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  if (!geom)
    return;
  pt = geom->FirstPoint;
  while (pt)
    {
      // marking any Point
      x = (int) ((pt->X - FrameMinX) / PixelRatio);
      y = FrameHeight - (int) ((pt->Y - FrameMinY) / PixelRatio);
      if (pt == CurrentPoint)
        {
          // active Point
          gr->SetBrush(wxBrush(wxColour(255, 255, 255)));
          gr->SetPen(wxPen(wxColour(0, 0, 0), 1));
      } else
        {
          // other Points [uneselected]
          gr->SetBrush(wxBrush(wxColour(192, 192, 192)));
          gr->SetPen(wxPen(wxColour(128, 128, 128), 1));
        }
      gr->DrawRectangle(x - 4, y - 4, 8, 8);
      if (pt == CurrentPoint)
        {
          // active Point
          gr->SetPen(wxPen(wxColour(255, 0, 0), 1));
      } else
        {
          // other Points [uneselected]
          gr->SetPen(wxPen(wxColour(255, 128, 128), 1));
        }
      gr->StrokeLine(x - 4, y - 4, x + 4, y + 4);
      gr->StrokeLine(x - 4, y + 4, x + 4, y - 4);
      pt = pt->Next;
    }
  ln = geom->FirstLinestring;
  while (ln)
    {
      // marking any Linestring
      path = gr->CreatePath();
      for (iv = 0; iv < ln->Points; iv++)
        {
          // prepearing the path
          if (ln->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ln->Coords, iv, &xx, &yy, &z);
          } else if (ln->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ln->Coords, iv, &xx, &yy, &m);
          } else if (ln->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ln->Coords, iv, &xx, &yy, &z, &m);
          } else
            {
              gaiaGetPoint(ln->Coords, iv, &xx, &yy);
            }
          x = (int) ((xx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
          if (iv == 0)
            path.MoveToPoint(x, y);
          else
            path.AddLineToPoint(x, y);
        }
      // stroking the thickest line
      gr->SetPen(wxPen(wxColour(255, 255, 255), 5));
      gr->StrokePath(path);
      // stroking the narrowest line
      if (ln == CurrentLinestring)
        {
          // active Linestring
          gr->SetPen(wxPen(wxColour(0, 0, 0), 3));
      } else
        {
          // other Linestrings [unselected]
          gr->SetPen(wxPen(wxColour(128, 128, 128), 3));
        }
      gr->StrokePath(path);
      // marking the vertices
      if (ln == CurrentLinestring)
        {
          // active Linestring
          gr->SetBrush(wxBrush(wxColour(255, 0, 0)));
          gr->SetPen(wxPen(wxColour(255, 0, 0), 1));
      } else
        {
          // other Linestrings [uneselected]
          gr->SetBrush(wxBrush(wxColour(255, 128, 128)));
          gr->SetPen(wxPen(wxColour(255, 128, 128), 1));
        }
      for (iv = 0; iv < ln->Points; iv++)
        {
          if (ln->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ln->Coords, iv, &xx, &yy, &z);
          } else if (ln->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ln->Coords, iv, &xx, &yy, &m);
          } else if (ln->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ln->Coords, iv, &xx, &yy, &z, &m);
          } else
            {
              gaiaGetPoint(ln->Coords, iv, &xx, &yy);
            }
          x = (int) ((xx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
          gr->DrawRectangle(x - 2, y - 2, 4, 4);

        }
      ln = ln->Next;
    }
  pg = geom->FirstPolygon;
  while (pg)
    {
      // marking any Polygon/Ring
      path = gr->CreatePath();
      path2 = gr->CreatePath();
      rng = pg->Exterior;
      for (iv = 0; iv < rng->Points; iv++)
        {
          // prepearing the path [Exterior Ring]
          if (rng->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(rng->Coords, iv, &xx, &yy, &z);
          } else if (rng->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(rng->Coords, iv, &xx, &yy, &m);
          } else if (rng->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(rng->Coords, iv, &xx, &yy, &z, &m);
          } else
            {
              gaiaGetPoint(rng->Coords, iv, &xx, &yy);
            }
          x = (int) ((xx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              path2.MoveToPoint(x, y);
          } else
            {
              path.AddLineToPoint(x, y);
              path2.AddLineToPoint(x, y);
            }
        }
      path2.CloseSubpath();
      // stroking the thickest line - Exterior Ring
      gr->SetPen(wxPen(wxColour(255, 255, 255), 5));
      gr->StrokePath(path);
      // stroking the narrowest line
      if (rng == CurrentRing)
        {
          // active Ring
          gr->SetPen(wxPen(wxColour(0, 0, 0), 3));
      } else
        {
          // other Rings [unselected]
          gr->SetPen(wxPen(wxColour(128, 128, 128), 3));
        }
      gr->StrokePath(path);
      // marking the Exterior Ring vertices
      if (rng == CurrentRing)
        {
          // active Ring
          gr->SetBrush(wxBrush(wxColour(255, 0, 0)));
          gr->SetPen(wxPen(wxColour(255, 0, 0), 1));
      } else
        {
          // other Rings [uneselected]
          gr->SetBrush(wxBrush(wxColour(255, 128, 128)));
          gr->SetPen(wxPen(wxColour(255, 128, 128), 1));
        }
      for (iv = 0; iv < (rng->Points - 1); iv++)
        {
          if (rng->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(rng->Coords, iv, &xx, &yy, &z);
          } else if (rng->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(rng->Coords, iv, &xx, &yy, &m);
          } else if (rng->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(rng->Coords, iv, &xx, &yy, &z, &m);
          } else
            {
              gaiaGetPoint(rng->Coords, iv, &xx, &yy);
            }
          x = (int) ((xx - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
          if (iv == 0)
            gr->DrawRectangle(x - 4, y - 4, 8, 8);
          else
            gr->DrawRectangle(x - 2, y - 2, 4, 4);

        }
      for (ib = 0; ib < pg->NumInteriors; ib++)
        {
          path = gr->CreatePath();
          rng = pg->Interiors + ib;
          for (iv = 0; iv < rng->Points; iv++)
            {
              // prepearing the path [Interior Ring]
              if (rng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(rng->Coords, iv, &xx, &yy, &z);
              } else if (rng->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(rng->Coords, iv, &xx, &yy, &m);
              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(rng->Coords, iv, &xx, &yy, &z, &m);
              } else
                {
                  gaiaGetPoint(rng->Coords, iv, &xx, &yy);
                }
              x = (int) ((xx - FrameMinX) / PixelRatio);
              y = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
              if (iv == 0)
                {
                  path.MoveToPoint(x, y);
                  path2.MoveToPoint(x, y);
              } else
                {
                  path.AddLineToPoint(x, y);
                  path2.AddLineToPoint(x, y);
                }
            }
          path2.CloseSubpath();
          // stroking the thickest line - Exterior Ring
          gr->SetPen(wxPen(wxColour(255, 255, 255), 5));
          gr->StrokePath(path);
          // stroking the narrowest line
          if (rng == CurrentRing)
            {
              // active Ring
              gr->SetPen(wxPen(wxColour(0, 0, 0), 3));
          } else
            {
              // other Linestrings [unselected]
              gr->SetPen(wxPen(wxColour(128, 128, 128), 3));
            }
          gr->StrokePath(path);
          // marking the Interior Ring vertices
          if (rng == CurrentRing)
            {
              // active Ring
              gr->SetBrush(wxBrush(wxColour(255, 0, 0)));
              gr->SetPen(wxPen(wxColour(255, 0, 0), 1));
          } else
            {
              // other Rings [uneselected]
              gr->SetBrush(wxBrush(wxColour(255, 128, 128)));
              gr->SetPen(wxPen(wxColour(255, 128, 128), 1));
            }
          for (iv = 0; iv < (rng->Points - 1); iv++)
            {
              if (rng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(rng->Coords, iv, &xx, &yy, &z);
              } else if (rng->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(rng->Coords, iv, &xx, &yy, &m);
              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(rng->Coords, iv, &xx, &yy, &z, &m);
              } else
                {
                  gaiaGetPoint(rng->Coords, iv, &xx, &yy);
                }
              x = (int) ((xx - FrameMinX) / PixelRatio);
              y = FrameHeight - (int) ((yy - FrameMinY) / PixelRatio);
              if (iv == 0)
                gr->DrawRectangle(x - 4, y - 4, 8, 8);
              else
                gr->DrawRectangle(x - 2, y - 2, 4, 4);
            }
        }
      gr->SetBrush(wxBrush(wxColour(0, 0, 0), wxCROSSDIAG_HATCH));
      gr->FillPath(path2);
      pg = pg->Next;
    }
}

void MyMapView::DynamicDrawCommon(bool ring, int points, wxGraphicsContext * gr)
{
//
// draws the current dynamic line/ring on the map
// COMMON function
//
  int x;
  int y;
  int lastX = 0;
  int lastY = 0;
  int x0;
  int y0;
  int x1;
  int y1;
  gaiaPointPtr pt;
  double p0_x;
  double p0_y;
  bool closed = false;
  MarkerGraphic.CreateGraphicResources(gr);
  if (ring == true && points >= 4)
    {
      // drawing a closed ring
      gr->SetBrush(wxBrush(wxColour(255, 255, 0, 128)));
      gr->SetPen(wxPen(wxColour(0, 0, 255, 192), 1));
      wxGraphicsPath path = gr->CreatePath();
      wxGraphicsPath path2 = gr->CreatePath();
      pt = CurrentDraw->First;
      while (pt)
        {
          x = (int) ((pt->X - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((pt->Y - FrameMinY) / PixelRatio);
          if (pt == CurrentDraw->First)
            {
              path.MoveToPoint(x, y);
              path2.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
              p0_x = pt->X;
              p0_y = pt->Y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  path2.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
          if (pt == CurrentDraw->Last)
            {
              if (pt->X == p0_x && pt->Y == p0_y)
                closed = true;
            }
          pt = pt->Next;
        }
      if (closed == false)
        {
          // inserting the last vertex if needed
          pt = CurrentDraw->First;
          x = (int) ((pt->X - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((pt->Y - FrameMinY) / PixelRatio);
          path2.AddLineToPoint(x, y);
        }
      gr->FillPath(path2);
      gr->StrokePath(path);
      if (closed == false)
        {
          // marking the last segment to ensure a closed figure 
          gr->SetPen(wxPen(wxColour(192, 0, 192, 128), 4, wxDOT));
          x0 = (int) ((pt->X - FrameMinX) / PixelRatio);
          y0 = FrameHeight - (int) ((pt->Y - FrameMinY) / PixelRatio);
          pt = CurrentDraw->Last;
          x1 = (int) ((pt->X - FrameMinX) / PixelRatio);
          y1 = FrameHeight - (int) ((pt->Y - FrameMinY) / PixelRatio);
          gr->StrokeLine(x0, y0, x1, y1);
        }
  } else if (points >= 2)
    {
      // drawing a linestring
      if (ring == true)
        gr->SetPen(wxPen(wxColour(0, 0, 255, 192), 1));
      else
        gr->SetPen(wxPen(wxColour(255, 255, 255), 5));
      wxGraphicsPath path = gr->CreatePath();
      pt = CurrentDraw->First;
      while (pt)
        {
          x = (int) ((pt->X - FrameMinX) / PixelRatio);
          y = FrameHeight - (int) ((pt->Y - FrameMinY) / PixelRatio);
          if (pt == CurrentDraw->First)
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
          pt = pt->Next;
        }
      gr->StrokePath(path);
      if (ring == false)
        {
          gr->SetPen(wxPen(wxColour(0, 0, 0), 3));
          gr->StrokePath(path);
        }
    }
}

void MyMapView::DynamicDrawNetworkNode(wxGraphicsContext * gr)
{
  int x;
  int y;
  NetworkNode *node = MainFrame->GetNetwork()->GetCurrentNode();
  if (node->IsValid() == true)
    {
      //
      // marking the current Network Node
      //
      gr->SetBrush(wxBrush(wxColour(192, 192, 192)));
      gr->SetPen(wxPen(wxColour(64, 64, 64), 1));
      x = (int) ((node->GetX() - FrameMinX) / PixelRatio);
      y = FrameHeight - (int) ((node->GetY() - FrameMinY) / PixelRatio);
      gr->DrawEllipse(x - 8, y - 8, 16, 16);
      gr->SetPen(wxPen(wxColour(0, 0, 192), 5));
      gr->StrokeLine(x - 8, y - 8, x + 8, y + 8);
      gr->StrokeLine(x - 8, y + 8, x + 8, y - 8);
      gr->SetPen(wxPen(wxColour(255, 255, 0), 3));
      gr->StrokeLine(x - 8, y - 8, x + 8, y + 8);
      gr->StrokeLine(x - 8, y + 8, x + 8, y - 8);
    }
}

void MyMapView::DynamicDrawRoutingSolution(wxGraphicsContext * gr)
{
  int x;
  int y;
  NetworkNode *node;
  RoutingSolution *solution = MainFrame->GetNetwork()->GetSolution();
  if (solution->IsValid() == true)
    {
      //
      // drawing the current routing solution
      //
      double lx;
      double ly;
      double z;
      double m;
      int iv;
      int lastX;
      int lastY;
      gaiaLinestringPtr ln = solution->GetGeometry()->FirstLinestring;
      if (ln)
        {
          gr->SetPen(wxPen(wxColour(255, 255, 0, 128), 16));
          wxGraphicsPath path = gr->CreatePath();
          for (iv = 0; iv < ln->Points; iv++)
            {
              if (ln->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(ln->Coords, iv, &lx, &ly, &z);
              } else if (ln->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(ln->Coords, iv, &lx, &ly, &m);
              } else if (ln->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(ln->Coords, iv, &lx, &ly, &z, &m);
              } else
                {
                  gaiaGetPoint(ln->Coords, iv, &lx, &ly);
                }
              x = (int) ((lx - FrameMinX) / PixelRatio);
              y = FrameHeight - (int) ((ly - FrameMinY) / PixelRatio);
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
          gr->SetPen(wxPen(wxColour(0, 255, 0, 128), 8));
          gr->StrokePath(path);
          gr->SetPen(wxPen(wxColour(0, 0, 255, 128), 4));
          gr->StrokePath(path);
        }
    }
  node = MainFrame->GetNetwork()->GetNodeFrom();
  if (node->IsValid() == true)
    {
      //
      // marking the current Network NodeFrom
      //
      wxBitmap bmp = wxBitmap(node_from_xpm);
      x = (int) ((node->GetX() - FrameMinX) / PixelRatio);
      y = FrameHeight - (int) ((node->GetY() - FrameMinY) / PixelRatio);
      gr->DrawBitmap(bmp, x - (bmp.GetWidth() / 2), y - (bmp.GetHeight() / 2),
                     bmp.GetWidth(), bmp.GetHeight());
    }
  node = MainFrame->GetNetwork()->GetNodeTo();
  if (node->IsValid() == true)
    {
      //
      // marking the current Network NodeTo
      //
      wxBitmap bmp = wxBitmap(node_to_xpm);
      x = (int) ((node->GetX() - FrameMinX) / PixelRatio);
      y = FrameHeight - (int) ((node->GetY() - FrameMinY) / PixelRatio);
      gr->DrawBitmap(bmp, x - (bmp.GetWidth() / 2), y - (bmp.GetHeight() / 2),
                     bmp.GetWidth(), bmp.GetHeight());
    }
}

void MyMapView::DynamicDraw(bool ring)
{
//
// draws the current dynamic elements on the map
//
  int points = 0;
  if (CurrentDraw)
    {
      points = GetCurrentDrawPoints();
      if (ring == true)
        {
          // counting an extra-vertex required to close the ring
          points++;
        }
    }
  if (MapBitmap.IsOk() && DynamicMapBitmap.IsOk() && ScreenBitmap.IsOk())
    {
      wxMemoryDC *mapDC = new wxMemoryDC(MapBitmap);
      wxMemoryDC *dynDC = new wxMemoryDC(DynamicMapBitmap);
      dynDC->Blit(0, 0, BitmapWidth, BitmapHeight, mapDC, 0, 0);
      delete mapDC;
      wxGraphicsContext *gr = wxGraphicsContext::Create(*dynDC);
      if (CurrentDraw)
        DynamicDrawCommon(ring, points, gr);
      if (OkCurrentGeometry == true)
        DynamicDrawGeometry(gr, MainFrame->GetCurrentEntityGeometry());
      if (OkCandidateEntity == true)
        DynamicDrawGeometry(gr, CandidateEntityGeometry);
      if (OkCurrentVertex == true)
        DynamicDrawVertex(gr);
      if (CurrentSegmentIndex >= 0 && (CurrentLinestring || CurrentRing))
        DynamicDrawSegment(gr);
      if (MainFrame->GetNetwork())
        {
          DynamicDrawNetworkNode(gr);
          DynamicDrawRoutingSolution(gr);
        }
      if (IsMapFrameSelection() == true)
        DynamicDrawMapFrameSelection(gr);
      delete gr;
      wxMemoryDC *dc = new wxMemoryDC(ScreenBitmap);
      dc->Blit(0, 0, BitmapWidth, BitmapHeight, dynDC, 0, 0);
      delete dynDC;
      delete dc;
      Refresh();
    }
}

void MyMapView::DynamicDrawElastic(bool ring, double x, double y)
{
//
// draws the current dynamic line/ring on the map 
// marking an "elastic" segment to follow mouse motion
//
  int x0;
  int y0;
  int x1;
  int y1;
  int points = 0;
  if (!CurrentDraw)
    return;
  points = GetCurrentDrawPoints();
  if (ring == true)
    {
      // counting an extra-vertex required to close the ring
      points++;
    }
  if (DynamicMapBitmap.IsOk() && ScreenBitmap.IsOk())
    {
      wxMemoryDC *dynDC = new wxMemoryDC(DynamicMapBitmap);
      wxMemoryDC *dc = new wxMemoryDC(ScreenBitmap);
      dc->Blit(0, 0, BitmapWidth, BitmapHeight, dynDC, 0, 0);
      delete dynDC;
      wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
      if (CurrentDraw->Last)
        {
          gr->SetPen(wxPen(wxColour(128, 0, 128), 1));
          x0 = (int) ((CurrentDraw->Last->X - FrameMinX) / PixelRatio);
          y0 =
            FrameHeight -
            (int) ((CurrentDraw->Last->Y - FrameMinY) / PixelRatio);
          x1 = (int) ((x - FrameMinX) / PixelRatio);
          y1 = FrameHeight - (int) ((y - FrameMinY) / PixelRatio);
          gr->StrokeLine(x0, y0, x1, y1);
          if (ring == true && points >= 2)
            {
              gr->SetPen(wxPen(wxColour(192, 0, 192, 128), 4, wxDOT));
              x0 = (int) ((CurrentDraw->First->X - FrameMinX) / PixelRatio);
              y0 =
                FrameHeight -
                (int) ((CurrentDraw->First->Y - FrameMinY) / PixelRatio);
              x1 = (int) ((x - FrameMinX) / PixelRatio);
              y1 = FrameHeight - (int) ((y - FrameMinY) / PixelRatio);
              gr->StrokeLine(x0, y0, x1, y1);
            }
        }
      delete gr;
      delete dc;
      Refresh();
    }
}

void MyMapView::DynamicShowMoveVertex(double x, double y)
{
//
// MoveVertex preview 
// marking "elastic" segments to follow mouse motion
//
  int ib;
  double x0;
  double y0;
  double x1;
  double y1;
  double x2;
  double y2;
  double z;
  double m;
  bool firstLast = false;
  bool this_point = false;
  bool prev_point = false;
  bool next_point = false;
  int xx0;
  int yy0;
  int xx1;
  int yy1;
  gaiaPointPtr pt;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  gaiaGeomCollPtr geom = MainFrame->GetCurrentEntityGeometry();
  OkMovedVertex = false;
  if (DynamicMapBitmap.IsOk() && ScreenBitmap.IsOk())
    {
      wxMemoryDC *dynDC = new wxMemoryDC(DynamicMapBitmap);
      wxMemoryDC *dc = new wxMemoryDC(ScreenBitmap);
      dc->Blit(0, 0, BitmapWidth, BitmapHeight, dynDC, 0, 0);
      delete dynDC;
      wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
      if (OkCurrentGeometry == true)
        DynamicDrawGeometry(gr, MainFrame->GetCurrentEntityGeometry());
      if (OkCurrentVertex == true)
        DynamicDrawVertex(gr);
      if (geom)
        {
          if (CurrentPoint)
            {
              pt = geom->FirstPoint;
              while (pt)
                {
                  if (CurrentPoint == pt)
                    {
                      // ok, this one is the moved POINT
                      x0 = pt->X;
                      y0 = pt->Y;
                      this_point = true;
                    }
                  pt = pt->Next;
                }
            }
          if (CurrentLinestring)
            {
              ln = geom->FirstLinestring;
              while (ln)
                {
                  if (CurrentLinestring == ln)
                    {
                      if (CurrentVertexIndex >= 0
                          && CurrentVertexIndex < ln->Points)
                        {
                          // ok, this one is the moved Vertex
                          if (ln->DimensionModel == GAIA_XY_Z)
                            {
                              gaiaGetPointXYZ(ln->Coords, CurrentVertexIndex,
                                              &x0, &y0, &z);
                          } else if (ln->DimensionModel == GAIA_XY_M)
                            {
                              gaiaGetPointXYM(ln->Coords, CurrentVertexIndex,
                                              &x0, &y0, &m);
                          } else if (ln->DimensionModel == GAIA_XY_Z_M)
                            {
                              gaiaGetPointXYZM(ln->Coords, CurrentVertexIndex,
                                               &x0, &y0, &z, &m);
                          } else
                            {
                              gaiaGetPoint(ln->Coords, CurrentVertexIndex, &x0,
                                           &y0);
                            }
                          this_point = true;
                        }
                      if ((CurrentVertexIndex - 1) >= 0
                          && (CurrentVertexIndex - 1) < ln->Points)
                        {
                          // ok, this one is the previous Vertex
                          if (ln->DimensionModel == GAIA_XY_Z)
                            {
                              gaiaGetPointXYZ(ln->Coords,
                                              CurrentVertexIndex - 1, &x1, &y1,
                                              &z);
                          } else if (ln->DimensionModel == GAIA_XY_M)
                            {
                              gaiaGetPointXYM(ln->Coords,
                                              CurrentVertexIndex - 1, &x1, &y1,
                                              &m);
                          } else if (ln->DimensionModel == GAIA_XY_Z_M)
                            {
                              gaiaGetPointXYZM(ln->Coords,
                                               CurrentVertexIndex - 1, &x1, &y1,
                                               &z, &m);
                          } else
                            {
                              gaiaGetPoint(ln->Coords, CurrentVertexIndex - 1,
                                           &x1, &y1);
                            }
                          prev_point = true;
                        }
                      if ((CurrentVertexIndex + 1) >= 0
                          && (CurrentVertexIndex + 1) < ln->Points)
                        {
                          // ok, this one is the next Vertex
                          if (ln->DimensionModel == GAIA_XY_Z)
                            {
                              gaiaGetPointXYZ(ln->Coords,
                                              CurrentVertexIndex + 1, &x2, &y2,
                                              &z);
                          } else if (ln->DimensionModel == GAIA_XY_M)
                            {
                              gaiaGetPointXYM(ln->Coords,
                                              CurrentVertexIndex + 1, &x2, &y2,
                                              &m);
                          } else if (ln->DimensionModel == GAIA_XY_Z_M)
                            {
                              gaiaGetPointXYZM(ln->Coords,
                                               CurrentVertexIndex + 1, &x2, &y2,
                                               &z, &m);
                          } else
                            {
                              gaiaGetPoint(ln->Coords, CurrentVertexIndex + 1,
                                           &x2, &y2);
                            }
                          next_point = true;
                        }
                    }
                  ln = ln->Next;
                }
            }
          if (CurrentPolygon)
            {
              pg = geom->FirstPolygon;
              while (pg)
                {
                  if (CurrentPolygon == pg)
                    {
                      rng = pg->Exterior;
                      if (CurrentRing == rng)
                        {
                          if (CurrentVertexIndex == 0
                              || CurrentVertexIndex == (rng->Points - 1))
                            firstLast = true;
                          if (CurrentVertexIndex >= 0
                              && CurrentVertexIndex < rng->Points)
                            {
                              // ok, this one is the moved Vertex
                              if (rng->DimensionModel == GAIA_XY_Z)
                                {
                                  gaiaGetPointXYZ(rng->Coords,
                                                  CurrentVertexIndex, &x0, &y0,
                                                  &z);
                              } else if (rng->DimensionModel == GAIA_XY_M)
                                {
                                  gaiaGetPointXYM(rng->Coords,
                                                  CurrentVertexIndex, &x0, &y0,
                                                  &m);
                              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                {
                                  gaiaGetPointXYZM(rng->Coords,
                                                   CurrentVertexIndex, &x0, &y0,
                                                   &z, &m);
                              } else
                                {
                                  gaiaGetPoint(rng->Coords, CurrentVertexIndex,
                                               &x0, &y0);
                                }
                              this_point = true;
                            }
                          if (firstLast == true)
                            {
                              // the moved Vertex is the first/last one
                              if (rng->DimensionModel == GAIA_XY_Z)
                                {
                                  gaiaGetPointXYZ(rng->Coords,
                                                  (rng->Points - 2), &x1, &y1,
                                                  &z);
                              } else if (rng->DimensionModel == GAIA_XY_M)
                                {
                                  gaiaGetPointXYM(rng->Coords,
                                                  (rng->Points - 2), &x1, &y1,
                                                  &m);
                              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                {
                                  gaiaGetPointXYZM(rng->Coords,
                                                   (rng->Points - 2), &x1, &y1,
                                                   &z, &m);
                              } else
                                {
                                  gaiaGetPoint(rng->Coords, (rng->Points - 2),
                                               &x1, &y1);
                                }
                              prev_point = true;
                              if (rng->DimensionModel == GAIA_XY_Z)
                                {
                                  gaiaGetPointXYZ(rng->Coords, 1, &x2, &y2, &z);
                              } else if (rng->DimensionModel == GAIA_XY_M)
                                {
                                  gaiaGetPointXYM(rng->Coords, 1, &x2, &y2, &m);
                              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                {
                                  gaiaGetPointXYZM(rng->Coords, 1, &x2, &y2, &z,
                                                   &m);
                              } else
                                {
                                  gaiaGetPoint(rng->Coords, 1, &x2, &y2);
                                }
                              next_point = true;
                          } else
                            {
                              if ((CurrentVertexIndex - 1) >= 0
                                  && (CurrentVertexIndex - 1) < rng->Points)
                                {
                                  // ok, this one is the previous Vertex
                                  if (rng->DimensionModel == GAIA_XY_Z)
                                    {
                                      gaiaGetPointXYZ(rng->Coords,
                                                      CurrentVertexIndex - 1,
                                                      &x1, &y1, &z);
                                  } else if (rng->DimensionModel == GAIA_XY_M)
                                    {
                                      gaiaGetPointXYM(rng->Coords,
                                                      CurrentVertexIndex - 1,
                                                      &x1, &y1, &m);
                                  } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                    {
                                      gaiaGetPointXYZM(rng->Coords,
                                                       CurrentVertexIndex - 1,
                                                       &x1, &y1, &z, &m);
                                  } else
                                    {
                                      gaiaGetPoint(rng->Coords,
                                                   CurrentVertexIndex - 1, &x1,
                                                   &y1);
                                    }
                                  prev_point = true;
                                }
                              if ((CurrentVertexIndex + 1) >= 0
                                  && (CurrentVertexIndex + 1) < rng->Points)
                                {
                                  // ok, this one is the next Vertex
                                  if (rng->DimensionModel == GAIA_XY_Z)
                                    {
                                      gaiaGetPointXYZ(rng->Coords,
                                                      CurrentVertexIndex + 1,
                                                      &x2, &y2, &z);
                                  } else if (rng->DimensionModel == GAIA_XY_M)
                                    {
                                      gaiaGetPointXYM(rng->Coords,
                                                      CurrentVertexIndex + 1,
                                                      &x2, &y2, &m);
                                  } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                    {
                                      gaiaGetPointXYZM(rng->Coords,
                                                       CurrentVertexIndex + 1,
                                                       &x2, &y2, &z, &m);
                                  } else
                                    {
                                      gaiaGetPoint(rng->Coords,
                                                   CurrentVertexIndex + 1, &x2,
                                                   &y2);
                                    }
                                  next_point = true;
                                }
                            }
                        }
                      for (ib = 0; ib < pg->NumInteriors; ib++)
                        {
                          rng = pg->Interiors + ib;
                          if (CurrentRing == rng)
                            {
                              if (CurrentVertexIndex == 0
                                  || CurrentVertexIndex == (rng->Points - 1))
                                firstLast = true;
                              if (CurrentVertexIndex >= 0
                                  && CurrentVertexIndex < rng->Points)
                                {
                                  // ok, this one is the moved Vertex
                                  if (rng->DimensionModel == GAIA_XY_Z)
                                    {
                                      gaiaGetPointXYZ(rng->Coords,
                                                      CurrentVertexIndex, &x0,
                                                      &y0, &z);
                                  } else if (rng->DimensionModel == GAIA_XY_M)
                                    {
                                      gaiaGetPointXYM(rng->Coords,
                                                      CurrentVertexIndex, &x0,
                                                      &y0, &m);
                                  } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                    {
                                      gaiaGetPointXYZM(rng->Coords,
                                                       CurrentVertexIndex, &x0,
                                                       &y0, &z, &m);
                                  } else
                                    {
                                      gaiaGetPoint(rng->Coords,
                                                   CurrentVertexIndex, &x0,
                                                   &y0);
                                    }
                                  this_point = true;
                                }
                              if (firstLast == true)
                                {
                                  // the moved Vertex is the first/last one
                                  if (rng->DimensionModel == GAIA_XY_Z)
                                    {
                                      gaiaGetPointXYZ(rng->Coords,
                                                      (rng->Points - 2), &x1,
                                                      &y1, &z);
                                  } else if (rng->DimensionModel == GAIA_XY_M)
                                    {
                                      gaiaGetPointXYM(rng->Coords,
                                                      (rng->Points - 2), &x1,
                                                      &y1, &m);
                                  } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                    {
                                      gaiaGetPointXYZM(rng->Coords,
                                                       (rng->Points - 2), &x1,
                                                       &y1, &z, &m);
                                  } else
                                    {
                                      gaiaGetPoint(rng->Coords,
                                                   (rng->Points - 2), &x1, &y1);
                                    }
                                  prev_point = true;
                                  if (rng->DimensionModel == GAIA_XY_Z)
                                    {
                                      gaiaGetPointXYZ(rng->Coords, 1, &x2, &y2,
                                                      &z);
                                  } else if (rng->DimensionModel == GAIA_XY_M)
                                    {
                                      gaiaGetPointXYM(rng->Coords, 1, &x2, &y2,
                                                      &m);
                                  } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                    {
                                      gaiaGetPointXYZM(rng->Coords, 1, &x2, &y2,
                                                       &z, &m);
                                  } else
                                    {
                                      gaiaGetPoint(rng->Coords, 1, &x2, &y2);
                                    }
                                  next_point = true;
                              } else
                                {
                                  if ((CurrentVertexIndex - 1) >= 0
                                      && (CurrentVertexIndex - 1) < rng->Points)
                                    {
                                      // ok, this one is the previous Vertex
                                      if (rng->DimensionModel == GAIA_XY_Z)
                                        {
                                          gaiaGetPointXYZ(rng->Coords,
                                                          CurrentVertexIndex -
                                                          1, &x1, &y1, &z);
                                      } else if (rng->DimensionModel ==
                                                 GAIA_XY_M)
                                        {
                                          gaiaGetPointXYM(rng->Coords,
                                                          CurrentVertexIndex -
                                                          1, &x1, &y1, &m);
                                      } else if (rng->DimensionModel ==
                                                 GAIA_XY_Z_M)
                                        {
                                          gaiaGetPointXYZM(rng->Coords,
                                                           CurrentVertexIndex -
                                                           1, &x1, &y1, &z, &m);
                                      } else
                                        {
                                          gaiaGetPoint(rng->Coords,
                                                       CurrentVertexIndex - 1,
                                                       &x1, &y1);
                                        }
                                      prev_point = true;
                                    }
                                  if ((CurrentVertexIndex + 1) >= 0
                                      && (CurrentVertexIndex + 1) < rng->Points)
                                    {
                                      // ok, this one is the next Vertex
                                      if (rng->DimensionModel == GAIA_XY_Z)
                                        {
                                          gaiaGetPointXYZ(rng->Coords,
                                                          CurrentVertexIndex +
                                                          1, &x2, &y2, &z);
                                      } else if (rng->DimensionModel ==
                                                 GAIA_XY_M)
                                        {
                                          gaiaGetPointXYM(rng->Coords,
                                                          CurrentVertexIndex +
                                                          1, &x2, &y2, &m);
                                      } else if (rng->DimensionModel ==
                                                 GAIA_XY_Z_M)
                                        {
                                          gaiaGetPointXYZM(rng->Coords,
                                                           CurrentVertexIndex +
                                                           1, &x2, &y2, &z, &m);
                                      } else
                                        {
                                          gaiaGetPoint(rng->Coords,
                                                       CurrentVertexIndex + 1,
                                                       &x2, &y2);
                                        }
                                      next_point = true;
                                    }
                                }
                            }
                        }
                    }
                  pg = pg->Next;
                }
            }
        }
      if (prev_point == true)
        {
          // marking the "previous" segment
          gr->SetPen(wxPen(wxColour(255, 255, 255), 3));
          xx0 = (int) ((x1 - FrameMinX) / PixelRatio);
          yy0 = FrameHeight - (int) ((y1 - FrameMinY) / PixelRatio);
          xx1 = (int) ((x - FrameMinX) / PixelRatio);
          yy1 = FrameHeight - (int) ((y - FrameMinY) / PixelRatio);
          gr->StrokeLine(xx0, yy0, xx1, yy1);
          gr->SetPen(wxPen(wxColour(0, 0, 0), 1));
          gr->StrokeLine(xx0, yy0, xx1, yy1);
        }
      if (next_point == true)
        {
          // marking the "next" segment
          gr->SetPen(wxPen(wxColour(255, 255, 255), 3));
          xx0 = (int) ((x2 - FrameMinX) / PixelRatio);
          yy0 = FrameHeight - (int) ((y2 - FrameMinY) / PixelRatio);
          xx1 = (int) ((x - FrameMinX) / PixelRatio);
          yy1 = FrameHeight - (int) ((y - FrameMinY) / PixelRatio);
          gr->StrokeLine(xx0, yy0, xx1, yy1);
          gr->SetPen(wxPen(wxColour(0, 0, 0), 1));
          gr->StrokeLine(xx0, yy0, xx1, yy1);
        }
      if (this_point == true)
        {
          // marking the "this-move" segment
          OkMovedVertex = true;
          gr->SetPen(wxPen(wxColour(128, 0, 0, 64), 3, wxDOT));
          xx0 = (int) ((x0 - FrameMinX) / PixelRatio);
          yy0 = FrameHeight - (int) ((y0 - FrameMinY) / PixelRatio);
          xx1 = (int) ((x - FrameMinX) / PixelRatio);
          yy1 = FrameHeight - (int) ((y - FrameMinY) / PixelRatio);
          gr->StrokeLine(xx0, yy0, xx1, yy1);
          // marking the "moved" vertex
          gr->SetPen(wxPen(wxColour(0, 0, 0), 1));
          gr->SetBrush(wxBrush(wxColour(255, 255, 255)));
          gr->DrawRectangle(xx1 - 4, yy1 - 4, 8, 8);
          gr->SetPen(wxPen(wxColour(255, 0, 0), 1));
          gr->StrokeLine(xx1 - 4, yy1 - 4, xx1 + 4, yy1 + 4);
          gr->StrokeLine(xx1 - 4, yy1 + 4, xx1 + 4, yy1 - 4);
        }
      delete gr;
      delete dc;
      Refresh();
    }
}

bool MyMapView::DynamicDoMoveVertex(double x, double y)
{
//
// MoveVertex actuation 
// modifying the Current Geometry
//
  int ib;
  gaiaPointPtr pt;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  bool ok = false;
  gaiaGeomCollPtr geom = MainFrame->GetCurrentEntityGeometry();
  if (geom)
    {
      if (CurrentPoint)
        {
          pt = geom->FirstPoint;
          while (pt)
            {
              if (CurrentPoint == pt)
                {
                  // ok, this one is the moved POINT
                  pt->X = x;
                  pt->Y = y;
                  ok = true;
                }
              pt = pt->Next;
            }
        }
      if (CurrentLinestring)
        {
          ln = geom->FirstLinestring;
          while (ln)
            {
              if (CurrentLinestring == ln)
                {
                  if (CurrentVertexIndex >= 0
                      && CurrentVertexIndex < ln->Points)
                    {
                      // ok, this one is the moved Vertex
                      if (ln->DimensionModel == GAIA_XY_Z)
                        {
                          gaiaSetPointXYZ(ln->Coords, CurrentVertexIndex, x, y,
                                          0.0);
                      } else if (ln->DimensionModel == GAIA_XY_M)
                        {
                          gaiaSetPointXYM(ln->Coords, CurrentVertexIndex, x, y,
                                          0.0);
                      } else if (ln->DimensionModel == GAIA_XY_Z_M)
                        {
                          gaiaSetPointXYZM(ln->Coords, CurrentVertexIndex, x, y,
                                           0.0, 0.0);
                      } else
                        {
                          gaiaSetPoint(ln->Coords, CurrentVertexIndex, x, y);
                        }
                      ok = true;
                    }
                }
              ln = ln->Next;
            }
        }
      if (CurrentPolygon)
        {
          pg = geom->FirstPolygon;
          while (pg)
            {
              if (CurrentPolygon == pg)
                {
                  rng = pg->Exterior;
                  if (CurrentRing == rng)
                    {
                      if (CurrentVertexIndex == 0
                          || CurrentVertexIndex == (rng->Points - 1))
                        {
                          // the moved Vertex is the first/last one
                          if (rng->DimensionModel == GAIA_XY_Z)
                            {
                              gaiaSetPointXYZ(rng->Coords, 0, x, y, 0.0);
                              gaiaSetPointXYZ(rng->Coords, (rng->Points - 1), x,
                                              y, 0.0);
                          } else if (rng->DimensionModel == GAIA_XY_M)
                            {
                              gaiaSetPointXYM(rng->Coords, 0, x, y, 0.0);
                              gaiaSetPointXYM(rng->Coords, (rng->Points - 1), x,
                                              y, 0.0);
                          } else if (rng->DimensionModel == GAIA_XY_Z_M)
                            {
                              gaiaSetPointXYZM(rng->Coords, 0, x, y, 0.0, 0.0);
                              gaiaSetPointXYZM(rng->Coords, (rng->Points - 1),
                                               x, y, 0.0, 0.0);
                          } else
                            {
                              gaiaSetPoint(rng->Coords, 0, x, y);
                              gaiaSetPoint(rng->Coords, (rng->Points - 1), x,
                                           y);
                            }
                          ok = true;
                      } else
                        {
                          if (CurrentVertexIndex >= 0
                              && CurrentVertexIndex < rng->Points)
                            {
                              // ok, this one is the moved Vertex
                              if (rng->DimensionModel == GAIA_XY_Z)
                                {
                                  gaiaSetPointXYZ(rng->Coords,
                                                  CurrentVertexIndex, x, y,
                                                  0.0);
                              } else if (rng->DimensionModel == GAIA_XY_M)
                                {
                                  gaiaSetPointXYM(rng->Coords,
                                                  CurrentVertexIndex, x, y,
                                                  0.0);
                              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                {
                                  gaiaSetPointXYZM(rng->Coords,
                                                   CurrentVertexIndex, x, y,
                                                   0.0, 0.0);
                              } else
                                {
                                  gaiaSetPoint(rng->Coords, CurrentVertexIndex,
                                               x, y);
                                }
                              ok = true;
                            }
                        }
                    }
                  for (ib = 0; ib < pg->NumInteriors; ib++)
                    {
                      rng = pg->Interiors + ib;
                      if (CurrentRing == rng)
                        {
                          if (CurrentVertexIndex == 0
                              || CurrentVertexIndex == (rng->Points - 1))
                            {
                              // the moved Vertex is the first/last one
                              if (rng->DimensionModel == GAIA_XY_Z)
                                {
                                  gaiaSetPointXYZ(rng->Coords, 0, x, y, 0.0);
                                  gaiaSetPointXYZ(rng->Coords,
                                                  (rng->Points - 1), x, y, 0.0);
                              } else if (rng->DimensionModel == GAIA_XY_M)
                                {
                                  gaiaSetPointXYM(rng->Coords, 0, x, y, 0.0);
                                  gaiaSetPointXYM(rng->Coords,
                                                  (rng->Points - 1), x, y, 0.0);
                              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                {
                                  gaiaSetPointXYZM(rng->Coords, 0, x, y, 0.0,
                                                   0.0);
                                  gaiaSetPointXYZM(rng->Coords,
                                                   (rng->Points - 1), x, y, 0.0,
                                                   0.0);
                              } else
                                {
                                  gaiaSetPoint(rng->Coords, 0, x, y);
                                  gaiaSetPoint(rng->Coords, (rng->Points - 1),
                                               x, y);
                                }
                              ok = true;
                          } else
                            {
                              if (CurrentVertexIndex >= 0
                                  && CurrentVertexIndex < rng->Points)
                                {
                                  // ok, this one is the moved Vertex
                                  if (rng->DimensionModel == GAIA_XY_Z)
                                    {
                                      gaiaSetPointXYZ(rng->Coords,
                                                      CurrentVertexIndex, x, y,
                                                      0.0);
                                  } else if (rng->DimensionModel == GAIA_XY_M)
                                    {
                                      gaiaSetPointXYM(rng->Coords,
                                                      CurrentVertexIndex, x, y,
                                                      0.0);
                                  } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                    {
                                      gaiaSetPointXYZM(rng->Coords,
                                                       CurrentVertexIndex, x, y,
                                                       0.0, 0.0);
                                  } else
                                    {
                                      gaiaSetPoint(rng->Coords,
                                                   CurrentVertexIndex, x, y);
                                    }
                                  ok = true;
                                }
                            }
                        }
                    }
                }
              pg = pg->Next;
            }
        }
    }
  return ok;
}

void MyMapView::DynamicShowInterpolateVertex(double x, double y)
{
//
// InterpolateVertex preview 
// marking "elastic" segments to follow mouse motion
//
  int ib;
  double x1;
  double y1;
  double x2;
  double y2;
  double z;
  double m;
  bool ok_segment = false;
  int xx0;
  int yy0;
  int xx1;
  int yy1;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  gaiaGeomCollPtr geom = MainFrame->GetCurrentEntityGeometry();
  OkInterpolatedVertex = false;
  if (DynamicMapBitmap.IsOk() && ScreenBitmap.IsOk())
    {
      wxMemoryDC *dynDC = new wxMemoryDC(DynamicMapBitmap);
      wxMemoryDC *dc = new wxMemoryDC(ScreenBitmap);
      dc->Blit(0, 0, BitmapWidth, BitmapHeight, dynDC, 0, 0);
      delete dynDC;
      wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
      if (OkCurrentGeometry == true)
        DynamicDrawGeometry(gr, MainFrame->GetCurrentEntityGeometry());
      if (CurrentSegmentIndex >= 0 && (CurrentLinestring || CurrentRing))
        DynamicDrawSegment(gr);
      if (geom)
        {
          if (CurrentLinestring)
            {
              ln = geom->FirstLinestring;
              while (ln)
                {
                  if (CurrentLinestring == ln)
                    {
                      if (CurrentSegmentIndex >= 1
                          && CurrentSegmentIndex < ln->Points)
                        {
                          // ok, this one is the current Segment
                          if (ln->DimensionModel == GAIA_XY_Z)
                            {
                              gaiaGetPointXYZ(ln->Coords,
                                              CurrentSegmentIndex - 1, &x1, &y1,
                                              &z);
                              gaiaGetPointXYZ(ln->Coords, CurrentSegmentIndex,
                                              &x2, &y2, &z);
                          } else if (ln->DimensionModel == GAIA_XY_M)
                            {
                              gaiaGetPointXYM(ln->Coords,
                                              CurrentSegmentIndex - 1, &x1, &y1,
                                              &m);
                              gaiaGetPointXYM(ln->Coords, CurrentSegmentIndex,
                                              &x2, &y2, &m);
                          } else if (ln->DimensionModel == GAIA_XY_Z_M)
                            {
                              gaiaGetPointXYZM(ln->Coords,
                                               CurrentSegmentIndex - 1, &x1,
                                               &y1, &z, &m);
                              gaiaGetPointXYZM(ln->Coords, CurrentSegmentIndex,
                                               &x2, &y2, &z, &m);
                          } else
                            {
                              gaiaGetPoint(ln->Coords, CurrentSegmentIndex - 1,
                                           &x1, &y1);
                              gaiaGetPoint(ln->Coords, CurrentSegmentIndex, &x2,
                                           &y2);
                            }
                          ok_segment = true;
                        }
                    }
                  ln = ln->Next;
                }
            }
          if (CurrentPolygon)
            {
              pg = geom->FirstPolygon;
              while (pg)
                {
                  if (CurrentPolygon == pg)
                    {
                      rng = pg->Exterior;
                      if (CurrentRing == rng)
                        {
                          if (CurrentSegmentIndex >= 1
                              && CurrentSegmentIndex < rng->Points)
                            {
                              // ok, this one is the current Segment
                              if (rng->DimensionModel == GAIA_XY_Z)
                                {
                                  gaiaGetPointXYZ(rng->Coords,
                                                  CurrentSegmentIndex - 1, &x1,
                                                  &y1, &z);
                                  gaiaGetPointXYZ(rng->Coords,
                                                  CurrentSegmentIndex, &x2, &y2,
                                                  &z);
                              } else if (rng->DimensionModel == GAIA_XY_M)
                                {
                                  gaiaGetPointXYM(rng->Coords,
                                                  CurrentSegmentIndex - 1, &x1,
                                                  &y1, &m);
                                  gaiaGetPointXYM(rng->Coords,
                                                  CurrentSegmentIndex, &x2, &y2,
                                                  &m);
                              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                {
                                  gaiaGetPointXYZM(rng->Coords,
                                                   CurrentSegmentIndex - 1, &x1,
                                                   &y1, &z, &m);
                                  gaiaGetPointXYZM(rng->Coords,
                                                   CurrentSegmentIndex, &x2,
                                                   &y2, &z, &m);
                              } else
                                {
                                  gaiaGetPoint(rng->Coords,
                                               CurrentSegmentIndex - 1, &x1,
                                               &y1);
                                  gaiaGetPoint(rng->Coords, CurrentSegmentIndex,
                                               &x2, &y2);
                                }
                              ok_segment = true;
                            }
                        }
                      for (ib = 0; ib < pg->NumInteriors; ib++)
                        {
                          rng = pg->Interiors + ib;
                          if (CurrentRing == rng)
                            {
                              if (CurrentSegmentIndex >= 1
                                  && CurrentSegmentIndex < rng->Points)
                                {
                                  // ok, this one is the current Segment
                                  if (rng->DimensionModel == GAIA_XY_Z)
                                    {
                                      gaiaGetPointXYZ(rng->Coords,
                                                      CurrentSegmentIndex - 1,
                                                      &x1, &y1, &z);
                                      gaiaGetPointXYZ(rng->Coords,
                                                      CurrentSegmentIndex, &x2,
                                                      &y2, &z);
                                  } else if (rng->DimensionModel == GAIA_XY_M)
                                    {
                                      gaiaGetPointXYM(rng->Coords,
                                                      CurrentSegmentIndex - 1,
                                                      &x1, &y1, &m);
                                      gaiaGetPointXYM(rng->Coords,
                                                      CurrentSegmentIndex, &x2,
                                                      &y2, &m);
                                  } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                    {
                                      gaiaGetPointXYZM(rng->Coords,
                                                       CurrentSegmentIndex - 1,
                                                       &x1, &y1, &z, &m);
                                      gaiaGetPointXYZM(rng->Coords,
                                                       CurrentSegmentIndex, &x2,
                                                       &y2, &z, &m);
                                  } else
                                    {
                                      gaiaGetPoint(rng->Coords,
                                                   CurrentSegmentIndex - 1, &x1,
                                                   &y1);
                                      gaiaGetPoint(rng->Coords,
                                                   CurrentSegmentIndex, &x2,
                                                   &y2);
                                    }
                                  ok_segment = true;
                                }
                            }
                        }
                    }
                  pg = pg->Next;
                }
            }
        }
      if (ok_segment == true)
        {
          // marking the "interpolated" segments
          gr->SetPen(wxPen(wxColour(255, 255, 255), 3));
          xx0 = (int) ((x1 - FrameMinX) / PixelRatio);
          yy0 = FrameHeight - (int) ((y1 - FrameMinY) / PixelRatio);
          xx1 = (int) ((x - FrameMinX) / PixelRatio);
          yy1 = FrameHeight - (int) ((y - FrameMinY) / PixelRatio);
          gr->StrokeLine(xx0, yy0, xx1, yy1);
          gr->SetPen(wxPen(wxColour(0, 0, 0), 1));
          gr->StrokeLine(xx0, yy0, xx1, yy1);
          gr->SetPen(wxPen(wxColour(255, 255, 255), 3));
          xx0 = (int) ((x2 - FrameMinX) / PixelRatio);
          yy0 = FrameHeight - (int) ((y2 - FrameMinY) / PixelRatio);
          xx1 = (int) ((x - FrameMinX) / PixelRatio);
          yy1 = FrameHeight - (int) ((y - FrameMinY) / PixelRatio);
          gr->StrokeLine(xx0, yy0, xx1, yy1);
          gr->SetPen(wxPen(wxColour(0, 0, 0), 1));
          gr->StrokeLine(xx0, yy0, xx1, yy1);
          // marking the "interpolated" vertex
          gr->SetPen(wxPen(wxColour(0, 0, 0), 1));
          gr->SetBrush(wxBrush(wxColour(255, 255, 255)));
          gr->DrawRectangle(xx1 - 4, yy1 - 4, 8, 8);
          gr->SetPen(wxPen(wxColour(255, 0, 0), 1));
          gr->StrokeLine(xx1 - 4, yy1 - 4, xx1 + 4, yy1 + 4);
          gr->StrokeLine(xx1 - 4, yy1 + 4, xx1 + 4, yy1 - 4);
          OkInterpolatedVertex = true;
        }
      delete gr;
      delete dc;
      Refresh();
    }
}

bool MyMapView::DynamicDoInterpolateVertex(double xx, double yy)
{
//
// InterpolateVertex actuation 
// modifying the Current Geometry [cloning is required]
//
  int iv;
  int iv2;
  int ib;
  double x;
  double y;
  double z;
  double m;
  bool ok = false;
  gaiaLinestringPtr oldLn;
  gaiaPolygonPtr oldPg;
  gaiaRingPtr oldRng;
  gaiaLinestringPtr newLn;
  gaiaPolygonPtr newPg;
  gaiaRingPtr newRng;
  gaiaGeomCollPtr oldGeom = MainFrame->GetCurrentEntityGeometry();
  gaiaGeomCollPtr newGeom = NULL;
  if (oldGeom)
    {
      // generating the modified Geometry
      if (oldGeom->DimensionModel == GAIA_XY_Z)
        newGeom = gaiaAllocGeomCollXYZ();
      else if (oldGeom->DimensionModel == GAIA_XY_M)
        newGeom = gaiaAllocGeomCollXYM();
      else if (oldGeom->DimensionModel == GAIA_XY_Z_M)
        newGeom = gaiaAllocGeomCollXYZM();
      else
        newGeom = gaiaAllocGeomColl();
      newGeom->Srid = oldGeom->Srid;
      newGeom->DeclaredType = MainFrame->GetActiveLayerDeclaredType();
      oldLn = oldGeom->FirstLinestring;
      while (oldLn)
        {
          // cloning any Linestring
          if (CurrentLinestring == oldLn)
            newLn = gaiaAddLinestringToGeomColl(newGeom, oldLn->Points + 1);
          else
            newLn = gaiaAddLinestringToGeomColl(newGeom, oldLn->Points);
          iv2 = 0;
          for (iv = 0; iv < oldLn->Points; iv++)
            {
              // copying vertices
              z = 0.0;
              m = 0.0;
              if (oldLn->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(oldLn->Coords, iv, &x, &y, &z);
              } else if (oldLn->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(oldLn->Coords, iv, &x, &y, &m);
              } else if (oldLn->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(oldLn->Coords, iv, &x, &y, &z, &m);
              } else
                {
                  gaiaGetPoint(oldLn->Coords, iv, &x, &y);
                }
              if (CurrentLinestring == oldLn && CurrentSegmentIndex == iv)
                {
                  // interpolating the new vertex
                  if (newLn->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaSetPointXYZ(newLn->Coords, iv2, xx, yy, 0.0);
                      iv2++;
                      gaiaSetPointXYZ(newLn->Coords, iv2, x, y, z);
                      iv2++;
                  } else if (newLn->DimensionModel == GAIA_XY_M)
                    {
                      gaiaSetPointXYM(newLn->Coords, iv2, xx, yy, 0.0);
                      iv2++;
                      gaiaSetPointXYM(newLn->Coords, iv2, x, y, m);
                      iv2++;
                  } else if (newLn->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaSetPointXYZM(newLn->Coords, iv2, xx, yy, 0.0, 0.0);
                      iv2++;
                      gaiaSetPointXYZM(newLn->Coords, iv2, x, y, z, m);
                      iv2++;
                  } else
                    {
                      gaiaSetPoint(newLn->Coords, iv2, xx, yy);
                      iv2++;
                      gaiaSetPoint(newLn->Coords, iv2, x, y);
                      iv2++;
                    }
                  ok = true;
              } else
                {
                  if (newLn->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaSetPointXYZ(newLn->Coords, iv2, x, y, z);
                  } else if (newLn->DimensionModel == GAIA_XY_M)
                    {
                      gaiaSetPointXYM(newLn->Coords, iv2, x, y, m);
                  } else if (newLn->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaSetPointXYZM(newLn->Coords, iv2, x, y, z, m);
                  } else
                    {
                      gaiaSetPoint(newLn->Coords, iv2, x, y);
                    }
                  iv2++;
                }
            }
          oldLn = oldLn->Next;
        }
      oldPg = oldGeom->FirstPolygon;
      while (oldPg)
        {
          // cloning any Polygon
          oldRng = oldPg->Exterior;
          if (CurrentRing == oldRng)
            newPg =
              gaiaAddPolygonToGeomColl(newGeom, oldRng->Points + 1,
                                       oldPg->NumInteriors);
          else
            newPg =
              gaiaAddPolygonToGeomColl(newGeom, oldRng->Points,
                                       oldPg->NumInteriors);
          newRng = newPg->Exterior;
          iv2 = 0;
          for (iv = 0; iv < oldRng->Points; iv++)
            {
              // copying vertices - EXTERIOR RING
              z = 0.0;
              m = 0.0;
              if (oldRng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(oldRng->Coords, iv, &x, &y, &z);
              } else if (oldRng->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(oldRng->Coords, iv, &x, &y, &m);
              } else if (oldRng->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(oldRng->Coords, iv, &x, &y, &z, &m);
              } else
                {
                  gaiaGetPoint(oldRng->Coords, iv, &x, &y);
                }
              if (CurrentRing == oldRng && CurrentSegmentIndex == iv)
                {
                  // interpolating the new vertex
                  if (newRng->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaSetPointXYZ(newRng->Coords, iv2, xx, yy, 0.0);
                      iv2++;
                      gaiaSetPointXYZ(newRng->Coords, iv2, x, y, z);
                      iv2++;
                  } else if (newRng->DimensionModel == GAIA_XY_M)
                    {
                      gaiaSetPointXYM(newRng->Coords, iv2, xx, yy, 0.0);
                      iv2++;
                      gaiaSetPointXYM(newRng->Coords, iv2, x, y, m);
                      iv2++;
                  } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaSetPointXYZM(newRng->Coords, iv2, xx, yy, 0.0, 0.0);
                      iv2++;
                      gaiaSetPointXYZM(newRng->Coords, iv2, x, y, z, m);
                      iv2++;
                  } else
                    {
                      gaiaSetPoint(newRng->Coords, iv2, xx, yy);
                      iv2++;
                      gaiaSetPoint(newRng->Coords, iv2, x, y);
                      iv2++;
                    }
                  ok = true;
              } else
                {
                  if (newRng->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaSetPointXYZ(newRng->Coords, iv2, x, y, z);
                    }
                  if (newRng->DimensionModel == GAIA_XY_M)
                    {
                      gaiaSetPointXYM(newRng->Coords, iv2, x, y, m);
                    }
                  if (newRng->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaSetPointXYZM(newRng->Coords, iv2, x, y, z, m);
                  } else
                    {
                      gaiaSetPoint(newRng->Coords, iv2, x, y);
                    }
                  iv2++;
                }
            }
          for (ib = 0; ib < oldPg->NumInteriors; ib++)
            {
              // cloning any INTERIOR RING
              oldRng = oldPg->Interiors + ib;
              if (CurrentRing == oldRng)
                newRng = gaiaAddInteriorRing(newPg, ib, oldRng->Points + 1);
              else
                newRng = gaiaAddInteriorRing(newPg, ib, oldRng->Points);
              iv2 = 0;
              for (iv = 0; iv < oldRng->Points; iv++)
                {
                  // copying vertices - INTERIOR RING
                  z = 0.0;
                  m = 0.0;
                  if (oldRng->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaGetPointXYZ(oldRng->Coords, iv, &x, &y, &z);
                  } else if (oldRng->DimensionModel == GAIA_XY_M)
                    {
                      gaiaGetPointXYM(oldRng->Coords, iv, &x, &y, &m);
                  } else if (oldRng->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaGetPointXYZM(oldRng->Coords, iv, &x, &y, &z, &m);
                  } else
                    {
                      gaiaGetPoint(oldRng->Coords, iv, &x, &y);
                    }
                  if (CurrentRing == oldRng && CurrentSegmentIndex == iv)
                    {
                      // interpolating the new vertex
                      if (newRng->DimensionModel == GAIA_XY_Z)
                        {
                          gaiaSetPointXYZ(newRng->Coords, iv2, xx, yy, 0.0);
                          iv2++;
                          gaiaSetPointXYZ(newRng->Coords, iv2, x, y, z);
                          iv2++;
                      } else if (newRng->DimensionModel == GAIA_XY_M)
                        {
                          gaiaSetPointXYM(newRng->Coords, iv2, xx, yy, 0.0);
                          iv2++;
                          gaiaSetPointXYM(newRng->Coords, iv2, x, y, m);
                          iv2++;
                      } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                        {
                          gaiaSetPointXYZM(newRng->Coords, iv2, xx, yy, 0.0,
                                           0.0);
                          iv2++;
                          gaiaSetPointXYZM(newRng->Coords, iv2, x, y, z, m);
                          iv2++;
                      } else
                        {
                          gaiaSetPoint(newRng->Coords, iv2, xx, yy);
                          iv2++;
                          gaiaSetPoint(newRng->Coords, iv2, x, y);
                          iv2++;
                        }
                      ok = true;
                  } else
                    {
                      if (newRng->DimensionModel == GAIA_XY_Z)
                        {
                          gaiaSetPointXYZ(newRng->Coords, iv2, x, y, z);
                        }
                      if (newRng->DimensionModel == GAIA_XY_M)
                        {
                          gaiaSetPointXYM(newRng->Coords, iv2, x, y, m);
                        }
                      if (newRng->DimensionModel == GAIA_XY_Z_M)
                        {
                          gaiaSetPointXYZM(newRng->Coords, iv2, x, y, z, m);
                      } else
                        {
                          gaiaSetPoint(newRng->Coords, iv2, x, y);
                        }
                      iv2++;
                    }
                }
            }
          oldPg = oldPg->Next;
        }
      if (ok == true)
        {
          MainFrame->SetCurrentEntityGeometry(newGeom);
          gaiaFreeGeomColl(oldGeom);
      } else
        gaiaFreeGeomColl(newGeom);
    }
  CurrentLinestring = NULL;
  CurrentRing = NULL;
  CurrentSegmentIndex = -1;
  return ok;
}

void MyMapView::DynamicFindVertex(double x, double y, bool includePoints)
{
//
// searches for some Vertex to be eventually moved or deleted
// if such a vertex is found, then it will be hilighted
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
  double dist;
  double minDist;
  double dx;
  double dy;
  double xx;
  double yy;
  double z;
  double m;
  int iv;
  int ib;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  sqlite3_int64 currentPK;
  gaiaGeomCollPtr currentGeometry = NULL;

  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  CurrentVertexIndex = -1;
  CurrentSegmentIndex = -1;

  if (!(MainFrame->GetActiveLayer()))
    return;

  queryMinX = x - (5.0 * PixelRatio);
  queryMaxX = x + (5.0 * PixelRatio);
  queryMinY = y - (5.0 * PixelRatio);
  queryMaxY = y + (5.0 * PixelRatio);

  if (MainFrame->GetActiveLayer()->GetSrid() ==
      MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (MainFrame->GetActiveLayer()->GetSrid() >= 0
          && MainFrame->GetProjectCrs().GetSrid() >= 0
          && MainFrame->GetActiveLayer()->IsReproject() == true)
        {
          bool ok_from =
            MainFrame->GetProjParams(MainFrame->GetActiveLayer()->GetSrid(),
                                     proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += MainFrame->GetActiveLayer()->GetTableName();
              msg += wxT(".");
              msg += MainFrame->GetActiveLayer()->GetGeometryColumn();
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
  sql = wxT("SELECT spatial_index_enabled ");
  sql += wxT("FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("' AND f_geometry_column = '");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("'");
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

// preparing the SQL statement
  sql = wxT("SELECT ROWID, \"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\" FROM \"");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("\" WHERE Intersects(\"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\", BuildMbr(?, ?, ?, ?)) AND ");
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql +=
        wxT("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
  } else if (mbrCacheSpatialIndex == true)
    {
      // using the MbrCache Spatial Index
      sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
  } else
    {
      // applying simple MBR filtering
      sql += wxT("ROWID IN (SELECT ROWID FROM \"");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("\" WHERE MbrIntersects(\"");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\", BuildMbr(?, ?, ?, ?)))");
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

  minDist = DBL_MAX;
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
                  if (geom)
                    {
                      if (includePoints == true)
                        {
                          // searching for Points too
                          gaiaPointPtr pt = geom->FirstPoint;
                          while (pt)
                            {
                              // checking any Point
                              dx = pt->X - x;
                              dy = pt->Y - y;
                              dist = sqrt((dx * dx) + (dy * dy));
                              if (dist < minDist)
                                {
                                  minDist = dist;
                                  if (currentGeometry != geom)
                                    {
                                      if (currentGeometry)
                                        gaiaFreeGeomColl(currentGeometry);
                                    }
                                  currentGeometry = geom;
                                  OkCurrentGeometry = true;
                                  OkCurrentVertex = false;
                                  CurrentPoint = pt;
                                  CurrentLinestring = ln;
                                  CurrentPolygon = NULL;
                                  CurrentRing = NULL;
                                  CurrentVertexIndex = -1;
                                  currentPK = rowId;
                                }
                              pt = pt->Next;
                            }
                        }
                      // finding out the nearest Vertex
                      ln = geom->FirstLinestring;
                      while (ln)
                        {
                          // checking any Linestring
                          for (iv = 0; iv < ln->Points; iv++)
                            {
                              // checking any Vertex
                              if (ln->DimensionModel == GAIA_XY_Z)
                                {
                                  gaiaGetPointXYZ(ln->Coords, iv, &xx, &yy, &z);
                              } else if (ln->DimensionModel == GAIA_XY_M)
                                {
                                  gaiaGetPointXYM(ln->Coords, iv, &xx, &yy, &m);
                              } else if (ln->DimensionModel == GAIA_XY_Z_M)
                                {
                                  gaiaGetPointXYZM(ln->Coords, iv, &xx, &yy, &z,
                                                   &m);
                              } else
                                {
                                  gaiaGetPoint(ln->Coords, iv, &xx, &yy);
                                }
                              dx = xx - x;
                              dy = yy - y;
                              dist = sqrt((dx * dx) + (dy * dy));
                              if (dist < minDist)
                                {
                                  minDist = dist;
                                  if (currentGeometry != geom)
                                    {
                                      if (currentGeometry)
                                        gaiaFreeGeomColl(currentGeometry);
                                    }
                                  currentGeometry = geom;
                                  OkCurrentGeometry = true;
                                  OkCurrentVertex = true;
                                  CurrentPoint = NULL;
                                  CurrentLinestring = ln;
                                  CurrentPolygon = NULL;
                                  CurrentRing = NULL;
                                  CurrentVertexCoords.X = xx;
                                  CurrentVertexCoords.Y = yy;
                                  CurrentVertexIndex = iv;
                                  currentPK = rowId;
                                }
                            }
                          ln = ln->Next;
                        }
                      pg = geom->FirstPolygon;
                      while (pg)
                        {
                          // checking any Polygon
                          rng = pg->Exterior;
                          for (iv = 0; iv < rng->Points; iv++)
                            {
                              // checking any Vertex [Exterior Ring]
                              if (rng->DimensionModel == GAIA_XY_Z)
                                {
                                  gaiaGetPointXYZ(rng->Coords, iv, &xx, &yy,
                                                  &z);
                              } else if (rng->DimensionModel == GAIA_XY_M)
                                {
                                  gaiaGetPointXYM(rng->Coords, iv, &xx, &yy,
                                                  &m);
                              } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                {
                                  gaiaGetPointXYZM(rng->Coords, iv, &xx, &yy,
                                                   &z, &m);
                              } else
                                {
                                  gaiaGetPoint(rng->Coords, iv, &xx, &yy);
                                }
                              dx = xx - x;
                              dy = yy - y;
                              dist = sqrt((dx * dx) + (dy * dy));
                              if (dist < minDist)
                                {
                                  minDist = dist;
                                  if (currentGeometry != geom)
                                    {
                                      if (currentGeometry)
                                        gaiaFreeGeomColl(currentGeometry);
                                    }
                                  currentGeometry = geom;
                                  OkCurrentGeometry = true;
                                  OkCurrentVertex = true;
                                  CurrentPoint = NULL;
                                  CurrentLinestring = NULL;
                                  CurrentPolygon = pg;
                                  CurrentRing = rng;
                                  CurrentVertexCoords.X = xx;
                                  CurrentVertexCoords.Y = yy;
                                  CurrentVertexIndex = iv;
                                  currentPK = rowId;
                                }
                            }
                          for (ib = 0; ib < pg->NumInteriors; ib++)
                            {
                              rng = pg->Interiors + ib;
                              for (iv = 0; iv < rng->Points; iv++)
                                {
                                  // checking any Vertex [Interior Ring]
                                  if (rng->DimensionModel == GAIA_XY_Z)
                                    {
                                      gaiaGetPointXYZ(rng->Coords, iv, &xx, &yy,
                                                      &z);
                                  } else if (rng->DimensionModel == GAIA_XY_M)
                                    {
                                      gaiaGetPointXYM(rng->Coords, iv, &xx, &yy,
                                                      &m);
                                  } else if (rng->DimensionModel == GAIA_XY_Z_M)
                                    {
                                      gaiaGetPointXYZM(rng->Coords, iv, &xx,
                                                       &yy, &z, &m);
                                  } else
                                    {
                                      gaiaGetPoint(rng->Coords, iv, &xx, &yy);
                                    }
                                  dx = xx - x;
                                  dy = yy - y;
                                  dist = sqrt((dx * dx) + (dy * dy));
                                  if (dist < minDist)
                                    {
                                      minDist = dist;
                                      if (currentGeometry != geom)
                                        {
                                          if (currentGeometry)
                                            gaiaFreeGeomColl(currentGeometry);
                                        }
                                      currentGeometry = geom;
                                      OkCurrentGeometry = true;
                                      OkCurrentVertex = true;
                                      CurrentPoint = NULL;
                                      CurrentLinestring = NULL;
                                      CurrentPolygon = pg;
                                      CurrentRing = rng;
                                      CurrentVertexCoords.X = xx;
                                      CurrentVertexCoords.Y = yy;
                                      CurrentVertexIndex = iv;
                                      currentPK = rowId;
                                    }
                                }
                            }
                          pg = pg->Next;
                        }
                      if (geom != currentGeometry)
                        gaiaFreeGeomColl(geom);
                    }
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

  if (minDist > (5.0 * PixelRatio))
    {
      if (currentGeometry)
        gaiaFreeGeomColl(currentGeometry);
      OkCurrentGeometry = false;
      OkCurrentVertex = false;
      OkMovedVertex = false;
      OkInterpolatedVertex = false;
      OkSplitLine = false;
      CurrentPoint = NULL;
      CurrentLinestring = NULL;
      CurrentPolygon = NULL;
      CurrentRing = NULL;
      CurrentVertexIndex = -1;
      DynamicDraw(false);
  } else
    {
      // setting up the CurrentEntity
      MainFrame->SetCurrentEntity(currentPK, currentGeometry);
      DynamicDraw(false);
    }
  return;

stop:
  if (currentGeometry)
    gaiaFreeGeomColl(currentGeometry);
  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  CurrentVertexIndex = -1;
  DynamicDraw(false);
  return;
}

bool MyMapView::DynamicDeleteVertex()
{
//
// deleting the currently selected Vertex
//
  bool found = false;
  bool degenerated = false;
  bool lastFirst = false;
  int iv;
  int iv2;
  int ib;
  double x;
  double y;
  double z;
  double m;
  gaiaLinestringPtr oldLn;
  gaiaPolygonPtr oldPg;
  gaiaRingPtr oldRng;
  gaiaLinestringPtr newLn;
  gaiaPolygonPtr newPg;
  gaiaRingPtr newRng;
  gaiaGeomCollPtr oldGeom = MainFrame->GetCurrentEntityGeometry();
  gaiaGeomCollPtr newGeom = NULL;
  if (oldGeom)
    {
      if (CurrentLinestring)
        {
          // checking a Linestring or MultiLinestring
          oldLn = oldGeom->FirstLinestring;
          while (oldLn)
            {
              // checking a Linestring
              if (CurrentLinestring == oldLn)
                {
                  if (oldLn->Points > CurrentVertexIndex)
                    found = true;
                  if (oldLn->Points <= 2)
                    degenerated = true;
                }
              oldLn = oldLn->Next;
            }
        }
      if (CurrentPolygon)
        {
          // checking a Polygon or MultiPolygon
          oldPg = oldGeom->FirstPolygon;
          while (oldPg)
            {
              // checking a Polygon
              if (CurrentPolygon == oldPg)
                {
                  oldRng = oldPg->Exterior;
                  if (CurrentRing == oldRng)
                    {
                      if (oldRng->Points > CurrentVertexIndex)
                        found = true;
                      if (oldRng->Points <= 4)
                        degenerated = true;
                      if (CurrentVertexIndex == 0
                          || CurrentVertexIndex == (oldRng->Points - 1))
                        lastFirst = true;
                  } else
                    {
                      for (ib = 0; ib < oldPg->NumInteriors; ib++)
                        {
                          oldRng = oldPg->Interiors + ib;
                          if (CurrentRing == oldRng)
                            {
                              if (oldRng->Points > CurrentVertexIndex)
                                found = true;
                              if (oldRng->Points <= 4)
                                degenerated = true;
                              if (CurrentVertexIndex == 0
                                  || CurrentVertexIndex == (oldRng->Points - 1))
                                lastFirst = true;
                            }
                        }
                    }
                }
              oldPg = oldPg->Next;
            }
        }
      if (found == true)
        {
          if (degenerated == true)
            {
              wxString msg =
                wxT
                ("Deleting this Vertex will produce a degenerated Geometry\n\n");
              msg += wxT("Illegal operation: no action was performed");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_WARNING,
                           this);
              return false;
            }
      } else
        return false;
      // generating the modified Geometry
      if (oldGeom->DeclaredType == GAIA_XY_Z)
        newGeom = gaiaAllocGeomCollXYZ();
      if (oldGeom->DeclaredType == GAIA_XY_M)
        newGeom = gaiaAllocGeomCollXYM();
      if (oldGeom->DeclaredType == GAIA_XY_Z_M)
        newGeom = gaiaAllocGeomCollXYZM();
      else
        newGeom = gaiaAllocGeomColl();
      newGeom->Srid = oldGeom->Srid;
      newGeom->DeclaredType = MainFrame->GetActiveLayerDeclaredType();
      oldLn = oldGeom->FirstLinestring;
      while (oldLn)
        {
          // cloning any Linestring
          if (CurrentLinestring == oldLn)
            newLn = gaiaAddLinestringToGeomColl(newGeom, oldLn->Points - 1);
          else
            newLn = gaiaAddLinestringToGeomColl(newGeom, oldLn->Points);
          iv2 = 0;
          for (iv = 0; iv < oldLn->Points; iv++)
            {
              // copying vertices
              z = 0.0;
              m = 0.0;
              if (oldLn->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(oldLn->Coords, iv, &x, &y, &z);
              } else if (oldLn->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(oldLn->Coords, iv, &x, &y, &m);
              } else if (oldLn->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(oldLn->Coords, iv, &x, &y, &z, &m);
              } else
                {
                  gaiaGetPoint(oldLn->Coords, iv, &x, &y);
                }
              if (CurrentLinestring == oldLn && CurrentVertexIndex == iv)
                ;               // skipping the selected vertex
              else
                {
                  if (newLn->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaSetPointXYZ(newLn->Coords, iv2, x, y, z);
                  } else if (newLn->DimensionModel == GAIA_XY_M)
                    {
                      gaiaSetPointXYM(newLn->Coords, iv2, x, y, m);
                  } else if (newLn->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaSetPointXYZM(newLn->Coords, iv2, x, y, z, m);
                  } else
                    {
                      gaiaSetPoint(newLn->Coords, iv2, x, y);
                    }
                  iv2++;
                }
            }
          oldLn = oldLn->Next;
        }
      oldPg = oldGeom->FirstPolygon;
      while (oldPg)
        {
          // cloning any Polygon
          oldRng = oldPg->Exterior;
          if (CurrentRing == oldRng)
            newPg =
              gaiaAddPolygonToGeomColl(newGeom, oldRng->Points - 1,
                                       oldPg->NumInteriors);
          else
            newPg =
              gaiaAddPolygonToGeomColl(newGeom, oldRng->Points,
                                       oldPg->NumInteriors);
          newRng = newPg->Exterior;
          iv2 = 0;
          for (iv = 0; iv < oldRng->Points; iv++)
            {
              // copying vertices - EXTERIOR RING
              z = 0.0;
              m = 0.0;
              if (oldRng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(oldRng->Coords, iv, &x, &y, &z);
              } else if (oldRng->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(oldRng->Coords, iv, &x, &y, &m);
              } else if (oldRng->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(oldRng->Coords, iv, &x, &y, &z, &m);
              } else
                {
                  gaiaGetPoint(oldRng->Coords, iv, &x, &y);
                }
              if (CurrentRing == oldRng && lastFirst == true
                  && (iv == 0 || iv == (oldRng->Points - 1)))
                ;               // skipping the first and last vertices
              else if (CurrentRing == oldRng && CurrentVertexIndex == iv)
                ;               // skipping the selected vertex
              else
                {
                  if (newRng->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaSetPointXYZ(newRng->Coords, iv2, x, y, z);
                  } else if (newRng->DimensionModel == GAIA_XY_M)
                    {
                      gaiaSetPointXYM(newRng->Coords, iv2, x, y, m);
                  } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaSetPointXYZM(newRng->Coords, iv2, x, y, z, m);
                  } else
                    {
                      gaiaSetPoint(newRng->Coords, iv2, x, y);
                    }
                  iv2++;
                }
            }
          if (CurrentRing == oldRng && lastFirst == true)
            {
              // ensuring the ring closure
              if (newRng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(newRng->Coords, 0, &x, &y, &z);
                  gaiaSetPointXYZ(newRng->Coords, (newRng->Points - 1), x, y,
                                  z);
              } else if (newRng->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(newRng->Coords, 0, &x, &y, &m);
                  gaiaSetPointXYM(newRng->Coords, (newRng->Points - 1), x, y,
                                  m);
              } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(newRng->Coords, 0, &x, &y, &z, &m);
                  gaiaSetPointXYZM(newRng->Coords, (newRng->Points - 1), x, y,
                                   z, m);
              } else
                {
                  gaiaGetPoint(newRng->Coords, 0, &x, &y);
                  gaiaSetPoint(newRng->Coords, (newRng->Points - 1), x, y);
                }
            }
          for (ib = 0; ib < oldPg->NumInteriors; ib++)
            {
              // cloning any INTERIOR RING
              oldRng = oldPg->Interiors + ib;
              if (CurrentRing == oldRng)
                newRng = gaiaAddInteriorRing(newPg, ib, oldRng->Points - 1);
              else
                newRng = gaiaAddInteriorRing(newPg, ib, oldRng->Points);
              iv2 = 0;
              for (iv = 0; iv < oldRng->Points; iv++)
                {
                  // copying vertices - INTERIOR RING
                  z = 0.0;
                  m = 0.0;
                  if (oldRng->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaGetPointXYZ(oldRng->Coords, iv, &x, &y, &z);
                  } else if (oldRng->DimensionModel == GAIA_XY_M)
                    {
                      gaiaGetPointXYM(oldRng->Coords, iv, &x, &y, &m);
                  } else if (oldRng->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaGetPointXYZM(oldRng->Coords, iv, &x, &y, &z, &m);
                  } else
                    {
                      gaiaGetPoint(oldRng->Coords, iv, &x, &y);
                    }
                  if (CurrentRing == oldRng && lastFirst == true
                      && (iv == 0 || iv == (oldRng->Points - 1)))
                    ;           // skipping the first and last vertices
                  else if (CurrentRing == oldRng && CurrentVertexIndex == iv)
                    ;           // skipping the selected vertex
                  else
                    {
                      if (newRng->DimensionModel == GAIA_XY_Z)
                        {
                          gaiaSetPointXYZ(newRng->Coords, iv2, x, y, z);
                      } else if (newRng->DimensionModel == GAIA_XY_M)
                        {
                          gaiaSetPointXYM(newRng->Coords, iv2, x, y, m);
                      } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                        {
                          gaiaSetPointXYZM(newRng->Coords, iv2, x, y, z, m);
                      } else
                        {
                          gaiaSetPoint(newRng->Coords, iv2, x, y);
                        }
                      iv2++;
                    }
                }
              if (CurrentRing == oldRng && lastFirst == true)
                {
                  // ensuring the ring closure
                  if (newRng->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaGetPointXYZ(newRng->Coords, 0, &x, &y, &z);
                      gaiaSetPointXYZ(newRng->Coords, (newRng->Points - 1), x,
                                      y, z);
                  } else if (newRng->DimensionModel == GAIA_XY_M)
                    {
                      gaiaGetPointXYM(newRng->Coords, 0, &x, &y, &m);
                      gaiaSetPointXYM(newRng->Coords, (newRng->Points - 1), x,
                                      y, m);
                  } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaGetPointXYZM(newRng->Coords, 0, &x, &y, &z, &m);
                      gaiaSetPointXYZM(newRng->Coords, (newRng->Points - 1), x,
                                       y, z, m);
                  } else
                    {
                      gaiaGetPoint(newRng->Coords, 0, &x, &y);
                      gaiaSetPoint(newRng->Coords, (newRng->Points - 1), x, y);
                    }
                }
            }
          oldPg = oldPg->Next;
        }
      MainFrame->SetCurrentEntityGeometry(newGeom);
      gaiaFreeGeomColl(oldGeom);
      return true;
    }
  return false;
}

void MyMapView::DynamicFindSubGeometry(double x, double y)
{
//
// searches for some SubGeometry to be eventually deleted
// if such a SubGeometry is found, then it will be hilighted
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
  double dist;
  double minDist;
  double dx;
  double dy;
  int ib;
  gaiaPointPtr pt;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  sqlite3_int64 currentPK;
  gaiaGeomCollPtr currentGeometry = NULL;

  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  CurrentVertexIndex = -1;
  CurrentSegmentIndex = -1;

  if (!(MainFrame->GetActiveLayer()))
    return;

  queryMinX = x - (5.0 * PixelRatio);
  queryMaxX = x + (5.0 * PixelRatio);
  queryMinY = y - (5.0 * PixelRatio);
  queryMaxY = y + (5.0 * PixelRatio);

  if (MainFrame->GetActiveLayer()->GetSrid() ==
      MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (MainFrame->GetActiveLayer()->GetSrid() >= 0
          && MainFrame->GetProjectCrs().GetSrid() >= 0
          && MainFrame->GetActiveLayer()->IsReproject() == true)
        {
          bool ok_from =
            MainFrame->GetProjParams(MainFrame->GetActiveLayer()->GetSrid(),
                                     proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += MainFrame->GetActiveLayer()->GetTableName();
              msg += wxT(".");
              msg += MainFrame->GetActiveLayer()->GetGeometryColumn();
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
  sql = wxT("SELECT spatial_index_enabled ");
  sql += wxT("FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("' AND f_geometry_column = '");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("'");
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

// preparing the SQL statement
  sql = wxT("SELECT ROWID, \"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\" FROM \"");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("\" WHERE Intersects(\"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\", BuildMbr(?, ?, ?, ?)) AND ");
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql +=
        wxT("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
  } else if (mbrCacheSpatialIndex == true)
    {
      // using the MbrCache Spatial Index
      sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
  } else
    {
      // applying simple MBR filtering
      sql += wxT("ROWID IN (SELECT ROWID FROM \"");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("\" WHERE MbrIntersects(\"");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\", BuildMbr(?, ?, ?, ?)))");
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

  minDist = DBL_MAX;
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
                  if (geom)
                    {
                      // finding out the nearest point
                      pt = geom->FirstPoint;
                      while (pt)
                        {
                          // checking any Point
                          dx = pt->X - x;
                          dy = pt->Y - y;
                          dist = sqrt((dx * dx) + (dy * dy));
                          if (dist < minDist)
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              OkCurrentGeometry = true;
                              CurrentPoint = pt;
                              CurrentLinestring = NULL;
                              CurrentPolygon = NULL;
                              CurrentRing = NULL;
                              currentPK = rowId;
                            }
                          pt = pt->Next;
                        }
                      ln = geom->FirstLinestring;
                      while (ln)
                        {
                          // checking any Linestring
                          dist =
                            gaiaMinDistance(x, y, ln->DimensionModel,
                                            ln->Coords, ln->Points);
                          if (dist < minDist)
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              OkCurrentGeometry = true;
                              CurrentPoint = NULL;
                              CurrentLinestring = ln;
                              CurrentPolygon = NULL;
                              CurrentRing = NULL;
                              currentPK = rowId;
                            }
                          ln = ln->Next;
                        }
                      pg = geom->FirstPolygon;
                      while (pg)
                        {
                          // checking any Polygon
                          rng = pg->Exterior;
                          dist =
                            gaiaMinDistance(x, y, rng->DimensionModel,
                                            rng->Coords, rng->Points);
                          if (dist < minDist)
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              OkCurrentGeometry = true;
                              CurrentPoint = NULL;
                              CurrentLinestring = NULL;
                              CurrentPolygon = pg;
                              CurrentRing = rng;
                              currentPK = rowId;
                            }
                          for (ib = 0; ib < pg->NumInteriors; ib++)
                            {
                              rng = pg->Interiors + ib;
                              dist =
                                gaiaMinDistance(x, y, rng->DimensionModel,
                                                rng->Coords, rng->Points);
                              if (dist < minDist)
                                {
                                  minDist = dist;
                                  if (currentGeometry != geom)
                                    {
                                      if (currentGeometry)
                                        gaiaFreeGeomColl(currentGeometry);
                                    }
                                  currentGeometry = geom;
                                  OkCurrentGeometry = true;
                                  CurrentPoint = NULL;
                                  CurrentLinestring = NULL;
                                  CurrentPolygon = pg;
                                  CurrentRing = rng;
                                  currentPK = rowId;
                                }
                            }
                          pg = pg->Next;
                        }
                      if (geom != currentGeometry)
                        gaiaFreeGeomColl(geom);
                    }
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

  if (minDist > (5.0 * PixelRatio))
    {
      if (currentGeometry)
        gaiaFreeGeomColl(currentGeometry);
      OkCurrentGeometry = false;
      OkCurrentVertex = false;
      OkMovedVertex = false;
      OkInterpolatedVertex = false;
      OkSplitLine = false;
      CurrentPoint = NULL;
      CurrentLinestring = NULL;
      CurrentPolygon = NULL;
      CurrentRing = NULL;
      CurrentVertexIndex = -1;
      DynamicDraw(false);
  } else
    {
      // setting up the CurrentEntity
      MainFrame->SetCurrentEntity(currentPK, currentGeometry);
      DynamicDraw(false);
    }
  return;

stop:
  if (currentGeometry)
    gaiaFreeGeomColl(currentGeometry);
  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  CurrentVertexIndex = -1;
  DynamicDraw(false);
  return;
}

bool MyMapView::DynamicDeleteSubGeometry()
{
//
// deleting the currently selected SubGeometry
//
  bool found = false;
  int count = 0;
  int iv;
  int ib;
  int ib2;
  double x;
  double y;
  double z;
  double m;
  gaiaPointPtr pt;
  gaiaLinestringPtr oldLn;
  gaiaPolygonPtr oldPg;
  gaiaRingPtr oldRng;
  gaiaLinestringPtr newLn;
  gaiaPolygonPtr newPg;
  gaiaRingPtr newRng;
  gaiaGeomCollPtr oldGeom = MainFrame->GetCurrentEntityGeometry();
  gaiaGeomCollPtr newGeom = NULL;
  if (oldGeom)
    {
      if (CurrentPoint)
        {
          // checking a MultiPoint
          pt = oldGeom->FirstPoint;
          while (pt)
            {
              // checking any Point
              if (CurrentPoint == pt)
                found = true;
              else
                count++;
              pt = pt->Next;
            }
        }
      if (CurrentLinestring)
        {
          // checking a Linestring or MultiLinestring
          oldLn = oldGeom->FirstLinestring;
          while (oldLn)
            {
              // checking a Linestring
              if (CurrentLinestring == oldLn)
                found = true;
              else
                count++;
              oldLn = oldLn->Next;
            }
        }
      if (CurrentPolygon)
        {
          // checking a Polygon or MultiPolygon
          oldPg = oldGeom->FirstPolygon;
          while (oldPg)
            {
              // checking a Polygon
              if (CurrentPolygon == oldPg)
                {
                  oldRng = oldPg->Exterior;
                  if (CurrentRing == oldRng)
                    found = true;
                  for (ib = 0; ib < oldPg->NumInteriors; ib++)
                    {
                      oldRng = oldPg->Interiors + ib;
                      if (CurrentRing == oldRng)
                        found = true;
                    }
              } else
                count++;
              oldPg = oldPg->Next;
            }
        }
      if (found == true)
        {
          if (count < 1)
            {
              wxString msg =
                wxT
                ("Deleting this SubGeometry will produce a NULL Geometry\n\n");
              msg += wxT("Illegal operation: no action was performed");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_WARNING,
                           this);
              return false;
            }
      } else
        return false;
      // generating the modified Geometry
      if (oldGeom->DimensionModel == GAIA_XY_Z)
        newGeom = gaiaAllocGeomCollXYZ();
      else if (oldGeom->DimensionModel == GAIA_XY_M)
        newGeom = gaiaAllocGeomCollXYM();
      else if (oldGeom->DimensionModel == GAIA_XY_Z_M)
        newGeom = gaiaAllocGeomCollXYZM();
      else
        newGeom = gaiaAllocGeomColl();
      newGeom->Srid = oldGeom->Srid;
      newGeom->DeclaredType = MainFrame->GetActiveLayerDeclaredType();
      pt = oldGeom->FirstPoint;
      while (pt)
        {
          // cloning any Point, except the selected one
          if (CurrentPoint != pt)
            {
              if (pt->DimensionModel == GAIA_XY_Z)
                gaiaAddPointToGeomCollXYZ(newGeom, pt->X, pt->Y, pt->Z);
              else if (pt->DimensionModel == GAIA_XY_M)
                gaiaAddPointToGeomCollXYM(newGeom, pt->X, pt->Y, pt->M);
              else if (pt->DimensionModel == GAIA_XY_Z_M)
                gaiaAddPointToGeomCollXYZM(newGeom, pt->X, pt->Y, pt->Z, pt->M);
              else
                gaiaAddPointToGeomColl(newGeom, pt->X, pt->Y);
            }
          pt = pt->Next;
        }
      oldLn = oldGeom->FirstLinestring;
      while (oldLn)
        {
          // cloning any Linestring, except the selected one
          if (CurrentLinestring == oldLn)
            {
              oldLn = oldLn->Next;
              continue;
            }
          newLn = gaiaAddLinestringToGeomColl(newGeom, oldLn->Points);
          for (iv = 0; iv < oldLn->Points; iv++)
            {
              // copying vertices
              z = 0.0;
              m = 0.0;
              if (oldLn->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(oldLn->Coords, iv, &x, &y, &z);
              } else if (oldLn->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(oldLn->Coords, iv, &x, &y, &m);
              } else if (oldLn->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(oldLn->Coords, iv, &x, &y, &z, &m);
              } else
                {
                  gaiaGetPoint(oldLn->Coords, iv, &x, &y);
                }
              if (newLn->DimensionModel == GAIA_XY_Z)
                {
                  gaiaSetPointXYZ(newLn->Coords, iv, x, y, z);
              } else if (newLn->DimensionModel == GAIA_XY_M)
                {
                  gaiaSetPointXYM(newLn->Coords, iv, x, y, m);
              } else if (newLn->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaSetPointXYZM(newLn->Coords, iv, x, y, z, m);
              } else
                {
                  gaiaSetPoint(newLn->Coords, iv, x, y);
                }
            }
          oldLn = oldLn->Next;
        }
      oldPg = oldGeom->FirstPolygon;
      while (oldPg)
        {
          // cloning any Polygon, except the select Ring
          oldRng = oldPg->Exterior;
          if (CurrentPolygon == oldPg && CurrentRing == oldRng)
            {
              // when deleting an Exterior Ring, we'll delete the whole Polygon
              oldPg = oldPg->Next;
              continue;
            }
          if (CurrentPolygon == oldPg)
            {
              // this Polygon requires an Interior Ring to be deleted
              newPg =
                gaiaAddPolygonToGeomColl(newGeom, oldRng->Points,
                                         oldPg->NumInteriors - 1);
          } else
            {
              // unaffected Polygon
              newPg =
                gaiaAddPolygonToGeomColl(newGeom, oldRng->Points,
                                         oldPg->NumInteriors);
            }
          newRng = newPg->Exterior;
          for (iv = 0; iv < oldRng->Points; iv++)
            {
              // copying vertices - EXTERIOR RING
              if (oldRng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(oldRng->Coords, iv, &x, &y, &z);
              } else if (oldRng->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(oldRng->Coords, iv, &x, &y, &m);
              } else if (oldRng->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(oldRng->Coords, iv, &x, &y, &z, &m);
              } else
                {
                  gaiaGetPoint(oldRng->Coords, iv, &x, &y);
                }
              if (newRng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaSetPointXYZ(newRng->Coords, iv, x, y, z);
              } else if (newRng->DimensionModel == GAIA_XY_M)
                {
                  gaiaSetPointXYM(newRng->Coords, iv, x, y, m);
              } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaSetPointXYZM(newRng->Coords, iv, x, y, z, m);
              } else
                {
                  gaiaSetPoint(newRng->Coords, iv, x, y);
                }
            }
          ib2 = 0;
          for (ib = 0; ib < oldPg->NumInteriors; ib++)
            {
              // cloning any INTERIOR RING
              oldRng = oldPg->Interiors + ib;
              if (CurrentRing == oldRng)
                continue;
              newRng = gaiaAddInteriorRing(newPg, ib2, oldRng->Points);
              ib2++;
              for (iv = 0; iv < oldRng->Points; iv++)
                {
                  // copying vertices - INTERIOR RING
                  if (oldRng->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaGetPointXYZ(oldRng->Coords, iv, &x, &y, &z);
                  } else if (oldRng->DimensionModel == GAIA_XY_M)
                    {
                      gaiaGetPointXYM(oldRng->Coords, iv, &x, &y, &m);
                  } else if (oldRng->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaGetPointXYZM(oldRng->Coords, iv, &x, &y, &z, &m);
                  } else
                    {
                      gaiaGetPoint(oldRng->Coords, iv, &x, &y);
                    }
                  if (newRng->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaSetPointXYZ(newRng->Coords, iv, x, y, z);
                  } else if (newRng->DimensionModel == GAIA_XY_M)
                    {
                      gaiaSetPointXYM(newRng->Coords, iv, x, y, m);
                  } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaSetPointXYZM(newRng->Coords, iv, x, y, z, m);
                  } else
                    {
                      gaiaSetPoint(newRng->Coords, iv, x, y);
                    }
                }
            }
          oldPg = oldPg->Next;
        }
      MainFrame->SetCurrentEntityGeometry(newGeom);
      gaiaFreeGeomColl(oldGeom);
      return true;
    }
  return false;
}

void MyMapView::DynamicFindSegment(double x, double y)
{
//
// searches for some Segment to be eventually interpolated
// if such a Segment is found, then it will be hilighted
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
  double dist;
  double minDist;
  int ib;
  int index;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  sqlite3_int64 currentPK;
  gaiaGeomCollPtr currentGeometry = NULL;

  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  CurrentVertexIndex = -1;
  CurrentSegmentIndex = -1;

  if (!(MainFrame->GetActiveLayer()))
    return;

  queryMinX = x - (5.0 * PixelRatio);
  queryMaxX = x + (5.0 * PixelRatio);
  queryMinY = y - (5.0 * PixelRatio);
  queryMaxY = y + (5.0 * PixelRatio);

  if (MainFrame->GetActiveLayer()->GetSrid() ==
      MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (MainFrame->GetActiveLayer()->GetSrid() >= 0
          && MainFrame->GetProjectCrs().GetSrid() >= 0
          && MainFrame->GetActiveLayer()->IsReproject() == true)
        {
          bool ok_from =
            MainFrame->GetProjParams(MainFrame->GetActiveLayer()->GetSrid(),
                                     proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += MainFrame->GetActiveLayer()->GetTableName();
              msg += wxT(".");
              msg += MainFrame->GetActiveLayer()->GetGeometryColumn();
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
  sql = wxT("SELECT spatial_index_enabled ");
  sql += wxT("FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("' AND f_geometry_column = '");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("'");
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

// preparing the SQL statement
  sql = wxT("SELECT ROWID, \"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\" FROM \"");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("\" WHERE Intersects(\"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\", BuildMbr(?, ?, ?, ?)) AND ");
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql +=
        wxT("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
  } else if (mbrCacheSpatialIndex == true)
    {
      // using the MbrCache Spatial Index
      sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
  } else
    {
      // applying simple MBR filtering
      sql += wxT("ROWID IN (SELECT ROWID FROM \"");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("\" WHERE MbrIntersects(\"");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\", BuildMbr(?, ?, ?, ?)))");
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

  minDist = DBL_MAX;
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
                  if (geom)
                    {
                      ln = geom->FirstLinestring;
                      while (ln)
                        {
                          // checking any Linestring
                          DynamicMinDistance(x, y, ln->DimensionModel,
                                             ln->Coords, ln->Points, &dist,
                                             &index);
                          if (dist < minDist)
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              OkCurrentGeometry = true;
                              CurrentLinestring = ln;
                              CurrentPolygon = NULL;
                              CurrentRing = NULL;
                              CurrentSegmentIndex = index;
                              currentPK = rowId;
                            }
                          ln = ln->Next;
                        }
                      pg = geom->FirstPolygon;
                      while (pg)
                        {
                          // checking any Polygon
                          rng = pg->Exterior;
                          DynamicMinDistance(x, y, rng->DimensionModel,
                                             rng->Coords, rng->Points, &dist,
                                             &index);
                          if (dist < minDist)
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              OkCurrentGeometry = true;
                              CurrentLinestring = NULL;
                              CurrentPolygon = pg;
                              CurrentRing = rng;
                              CurrentSegmentIndex = index;
                              currentPK = rowId;
                            }
                          for (ib = 0; ib < pg->NumInteriors; ib++)
                            {
                              rng = pg->Interiors + ib;
                              DynamicMinDistance(x, y, rng->DimensionModel,
                                                 rng->Coords, rng->Points,
                                                 &dist, &index);
                              if (dist < minDist)
                                {
                                  minDist = dist;
                                  if (currentGeometry != geom)
                                    {
                                      if (currentGeometry)
                                        gaiaFreeGeomColl(currentGeometry);
                                    }
                                  currentGeometry = geom;
                                  OkCurrentGeometry = true;
                                  CurrentLinestring = NULL;
                                  CurrentPolygon = pg;
                                  CurrentRing = rng;
                                  CurrentSegmentIndex = index;
                                  currentPK = rowId;
                                }
                            }
                          pg = pg->Next;
                        }
                      if (geom != currentGeometry)
                        gaiaFreeGeomColl(geom);
                    }
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

  if (minDist > (5.0 * PixelRatio))
    {
      if (currentGeometry)
        gaiaFreeGeomColl(currentGeometry);
      OkCurrentGeometry = false;
      OkCurrentVertex = false;
      OkMovedVertex = false;
      OkInterpolatedVertex = false;
      OkSplitLine = false;
      CurrentPoint = NULL;
      CurrentLinestring = NULL;
      CurrentPolygon = NULL;
      CurrentRing = NULL;
      CurrentVertexIndex = -1;
      CurrentSegmentIndex = -1;
      DynamicDraw(false);
  } else
    {
      // setting up the CurrentEntity
      MainFrame->SetCurrentEntity(currentPK, currentGeometry);
      DynamicDraw(false);
    }
  return;

stop:
  if (currentGeometry)
    gaiaFreeGeomColl(currentGeometry);
  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  CurrentVertexIndex = -1;
  CurrentSegmentIndex = -1;
  DynamicDraw(false);
  return;
}

void MyMapView::DynamicFindLineToSplit(double x, double y)
{
//
// searches for some Segment or Vertex to be eventually used in order to split a Linestring
// if such a Segment or Vertex is found, then it will be hilighted
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
  double dist;
  double minDist;
  int index;
  double xx;
  double yy;
  gaiaLinestringPtr ln;
  sqlite3_int64 currentPK;
  gaiaGeomCollPtr currentGeometry = NULL;

  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  OkSplitLine = false;
  CurrentVertexIndex = -1;
  CurrentSegmentIndex = -1;

  if (!(MainFrame->GetActiveLayer()))
    return;

  queryMinX = x - (5.0 * PixelRatio);
  queryMaxX = x + (5.0 * PixelRatio);
  queryMinY = y - (5.0 * PixelRatio);
  queryMaxY = y + (5.0 * PixelRatio);

  if (MainFrame->GetActiveLayer()->GetSrid() ==
      MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (MainFrame->GetActiveLayer()->GetSrid() >= 0
          && MainFrame->GetProjectCrs().GetSrid() >= 0
          && MainFrame->GetActiveLayer()->IsReproject() == true)
        {
          bool ok_from =
            MainFrame->GetProjParams(MainFrame->GetActiveLayer()->GetSrid(),
                                     proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += MainFrame->GetActiveLayer()->GetTableName();
              msg += wxT(".");
              msg += MainFrame->GetActiveLayer()->GetGeometryColumn();
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
  sql = wxT("SELECT spatial_index_enabled ");
  sql += wxT("FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("' AND f_geometry_column = '");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("'");
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

// preparing the SQL statement
  sql = wxT("SELECT ROWID, \"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\" FROM \"");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("\" WHERE Intersects(\"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\", BuildMbr(?, ?, ?, ?)) AND ");
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql +=
        wxT("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
  } else if (mbrCacheSpatialIndex == true)
    {
      // using the MbrCache Spatial Index
      sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
  } else
    {
      // applying simple MBR filtering
      sql += wxT("ROWID IN (SELECT ROWID FROM \"");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("\" WHERE MbrIntersects(\"");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\", BuildMbr(?, ?, ?, ?)))");
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

  minDist = DBL_MAX;
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
                  if (geom)
                    {
                      ln = geom->FirstLinestring;
                      while (ln)
                        {
                          // checking any Linestring
                          DynamicMinDistanceIntersect(x, y, ln->DimensionModel,
                                                      ln->Coords, ln->Points,
                                                      &dist, &index, &xx, &yy);
                          if (dist < minDist)
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              OkCurrentGeometry = true;
                              CurrentLinestring = ln;
                              CurrentPolygon = NULL;
                              CurrentRing = NULL;
                              CurrentSegmentIndex = index;
                              CurrentVertexIndex = -1;
                              CurrentVertexCoords.X = xx;
                              CurrentVertexCoords.Y = yy;
                              OkCurrentVertex = true;
                              OkSplitLine = true;
                              currentPK = rowId;
                            }
                          DynamicMinDistanceVertex(x, y, ln->DimensionModel,
                                                   ln->Coords, ln->Points,
                                                   &dist, &index, &xx, &yy);
                          if (dist < minDist || dist < (5.0 * PixelRatio))
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              OkCurrentGeometry = true;
                              CurrentLinestring = ln;
                              CurrentPolygon = NULL;
                              CurrentRing = NULL;
                              CurrentSegmentIndex = -1;
                              CurrentVertexIndex = index;
                              CurrentVertexCoords.X = xx;
                              CurrentVertexCoords.Y = yy;
                              OkCurrentVertex = true;
                              OkSplitLine = true;
                              currentPK = rowId;
                            }
                          ln = ln->Next;
                        }
                      if (geom != currentGeometry)
                        gaiaFreeGeomColl(geom);
                    }
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

  if (minDist > (5.0 * PixelRatio))
    {
      if (currentGeometry)
        gaiaFreeGeomColl(currentGeometry);
      OkCurrentGeometry = false;
      OkCurrentVertex = false;
      OkMovedVertex = false;
      OkInterpolatedVertex = false;
      OkSplitLine = false;
      CurrentPoint = NULL;
      CurrentLinestring = NULL;
      CurrentPolygon = NULL;
      CurrentRing = NULL;
      CurrentVertexIndex = -1;
      CurrentSegmentIndex = -1;
      DynamicDraw(false);
  } else
    {
      // setting up the CurrentEntity
      MainFrame->SetCurrentEntity(currentPK, currentGeometry);
      DynamicDraw(false);
    }
  return;

stop:
  if (currentGeometry)
    gaiaFreeGeomColl(currentGeometry);
  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  CurrentVertexIndex = -1;
  CurrentSegmentIndex = -1;
  DynamicDraw(false);
  return;
}

void MyMapView::DynamicMinDistance(double x0, double y0, int dims,
                                   double *coords, int n_vert, double *retDist,
                                   int *index)
{
//
// computing minimal distance between a POINT and a linestring/ring
// identifying the nearest segment
//
  double x;
  double y;
  double z;
  double m;
  double ox;
  double oy;
  double lineMag;
  double u;
  double px;
  double py;
  double dist;
  double min_dist = DBL_MAX;
  int iv;
  int segIdx = -1;
  *retDist = min_dist;
  *index = segIdx;
  if (n_vert < 2)
    {
      // not a valid Linestring
      return;
    }
  for (iv = 1; iv < n_vert; iv++)
    {
      // segment start-end coordinates */
      if (dims == GAIA_XY_Z)
        {
          gaiaGetPointXYZ(coords, iv - 1, &ox, &oy, &z);
          gaiaGetPointXYZ(coords, iv, &x, &y, &z);
      } else if (dims == GAIA_XY_M)
        {
          gaiaGetPointXYM(coords, iv - 1, &ox, &oy, &m);
          gaiaGetPointXYM(coords, iv, &x, &y, &m);
      } else if (dims == GAIA_XY_Z_M)
        {
          gaiaGetPointXYZM(coords, iv - 1, &ox, &oy, &z, &m);
          gaiaGetPointXYZM(coords, iv, &x, &y, &z, &m);
      } else
        {
          gaiaGetPoint(coords, iv - 1, &ox, &oy);
          gaiaGetPoint(coords, iv, &x, &y);
        }
      // computing a projection 
      lineMag = ((x - ox) * (x - ox)) + ((y - oy) * (y - oy));
      u = (((x0 - ox) * (x - ox)) + ((y0 - oy) * (y - oy))) / lineMag;
      if (u < 0.0 || u > 1.0)
        ;                       // closest point does not fall within the line segment
      else
        {
          px = ox + u * (x - ox);
          py = oy + u * (y - oy);
          dist = sqrt(((x0 - px) * (x0 - px)) + ((y0 - py) * (y0 - py)));
          if (dist < min_dist)
            {
              min_dist = dist;
              segIdx = iv;
            }
        }
    }
  *retDist = min_dist;
  *index = segIdx;
  return;
}

void MyMapView::DynamicMinDistanceIntersect(double x0, double y0, int dims,
                                            double *coords, int n_vert,
                                            double *retDist, int *index,
                                            double *x1, double *y1)
{
//
// computing minimal distance between a POINT and a linestring/ring
// identifying the nearest segment and the intersection point
//
  double x;
  double y;
  double z;
  double m;
  double ox;
  double oy;
  double lineMag;
  double u;
  double px;
  double py;
  double sx;
  double sy;
  double dist;
  double min_dist = DBL_MAX;
  int iv;
  int segIdx = -1;
  *retDist = min_dist;
  *index = segIdx;
  if (n_vert < 2)
    {
      // not a valid Linestring
      return;
    }
  for (iv = 1; iv < n_vert; iv++)
    {
      // segment start-end coordinates */
      if (dims == GAIA_XY_Z)
        {
          gaiaGetPointXYZ(coords, iv - 1, &ox, &oy, &z);
          gaiaGetPointXYZ(coords, iv, &x, &y, &z);
      } else if (dims == GAIA_XY_M)
        {
          gaiaGetPointXYM(coords, iv - 1, &ox, &oy, &m);
          gaiaGetPointXYM(coords, iv, &x, &y, &m);
      } else if (dims == GAIA_XY_Z_M)
        {
          gaiaGetPointXYZM(coords, iv - 1, &ox, &oy, &z, &m);
          gaiaGetPointXYZM(coords, iv, &x, &y, &z, &m);
      } else
        {
          gaiaGetPoint(coords, iv - 1, &ox, &oy);
          gaiaGetPoint(coords, iv, &x, &y);
        }
      // computing a projection 
      lineMag = ((x - ox) * (x - ox)) + ((y - oy) * (y - oy));
      u = (((x0 - ox) * (x - ox)) + ((y0 - oy) * (y - oy))) / lineMag;
      if (u < 0.0 || u > 1.0)
        ;                       // closest point does not fall within the line segment
      else
        {
          px = ox + u * (x - ox);
          py = oy + u * (y - oy);
          dist = sqrt(((x0 - px) * (x0 - px)) + ((y0 - py) * (y0 - py)));
          if (dist < min_dist)
            {
              min_dist = dist;
              sx = px;
              sy = py;
              segIdx = iv;
            }
        }
    }
  *x1 = sx;
  *y1 = sy;
  *retDist = min_dist;
  *index = segIdx;
  return;
}

void MyMapView::DynamicMinDistanceVertex(double x0, double y0, int dims,
                                         double *coords, int n_vert,
                                         double *retDist, int *index,
                                         double *x1, double *y1)
{
//
// computing minimal distance between a POINT and a linestring/ring
// identifying the nearest vertex
//
  double x;
  double y;
  double z;
  double m;
  double sx;
  double sy;
  double dist;
  double min_dist = DBL_MAX;
  int iv;
  int vertIdx = -1;
  *retDist = min_dist;
  *index = vertIdx;
  if (n_vert < 2)
    {
      // not a valid Linestring
      return;
    }
  for (iv = 0; iv < n_vert; iv++)
    {
      // segment start-end coordinates */
      if (dims == GAIA_XY_Z)
        {
          gaiaGetPointXYZ(coords, iv, &x, &y, &z);
      } else if (dims == GAIA_XY_M)
        {
          gaiaGetPointXYM(coords, iv, &x, &y, &m);
      } else if (dims == GAIA_XY_Z_M)
        {
          gaiaGetPointXYZM(coords, iv, &x, &y, &z, &m);
      } else
        {
          gaiaGetPoint(coords, iv, &x, &y);
        }
      dist = sqrt(((x0 - x) * (x0 - x)) + ((y0 - y) * (y0 - y)));
      if (dist < min_dist)
        {
          min_dist = dist;
          sx = x;
          sy = y;
          vertIdx = iv;
        }
    }
  *x1 = sx;
  *y1 = sy;
  *retDist = min_dist;
  *index = vertIdx;
  return;
}

void MyMapView::DynamicFindMultiGeometry(double x, double y)
{
//
// searches for some MultiGeometry to be eventually selected
// if such a MultiGeometry is found, then it will be hilighted
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
  double dist;
  double minDist;
  double dx;
  double dy;
  gaiaPointPtr pt;
  gaiaLinestringPtr ln;
  gaiaPolygonPtr pg;
  sqlite3_int64 currentPK;
  gaiaGeomCollPtr currentGeometry = NULL;

  SetCandidateEntity(-1, NULL);

  if (!(MainFrame->GetActiveLayer()))
    return;

  queryMinX = x - (5.0 * PixelRatio);
  queryMaxX = x + (5.0 * PixelRatio);
  queryMinY = y - (5.0 * PixelRatio);
  queryMaxY = y + (5.0 * PixelRatio);

  if (MainFrame->GetActiveLayer()->GetSrid() ==
      MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (MainFrame->GetActiveLayer()->GetSrid() >= 0
          && MainFrame->GetProjectCrs().GetSrid() >= 0
          && MainFrame->GetActiveLayer()->IsReproject() == true)
        {
          bool ok_from =
            MainFrame->GetProjParams(MainFrame->GetActiveLayer()->GetSrid(),
                                     proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += MainFrame->GetActiveLayer()->GetTableName();
              msg += wxT(".");
              msg += MainFrame->GetActiveLayer()->GetGeometryColumn();
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
  sql = wxT("SELECT spatial_index_enabled ");
  sql += wxT("FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("' AND f_geometry_column = '");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("'");
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

// preparing the SQL statement
  sql = wxT("SELECT ROWID, \"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\" FROM \"");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("\" WHERE Intersects(\"");
  sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
  sql += wxT("\", BuildMbr(?, ?, ?, ?)) AND ");
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql +=
        wxT("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
  } else if (mbrCacheSpatialIndex == true)
    {
      // using the MbrCache Spatial Index
      sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("_");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
  } else
    {
      // applying simple MBR filtering
      sql += wxT("ROWID IN (SELECT ROWID FROM \"");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("\" WHERE MbrIntersects(\"");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\", BuildMbr(?, ?, ?, ?)))");
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

  minDist = DBL_MAX;
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
                  if (geom)
                    {
                      // finding out a Geometry candidable for selection
                      pt = geom->FirstPoint;
                      while (pt)
                        {
                          // checking any Point
                          dx = pt->X - x;
                          dy = pt->Y - y;
                          dist = sqrt((dx * dx) + (dy * dy));
                          if (dist < minDist)
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              currentPK = rowId;
                            }
                          pt = pt->Next;
                        }
                      ln = geom->FirstLinestring;
                      while (ln)
                        {
                          // checking any Linestring
                          dist =
                            gaiaMinDistance(x, y, ln->DimensionModel,
                                            ln->Coords, ln->Points);
                          if (dist < minDist)
                            {
                              minDist = dist;
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              currentPK = rowId;
                            }
                          ln = ln->Next;
                        }
                      pg = geom->FirstPolygon;
                      while (pg)
                        {
                          // checking any Polygon
                          if (gaiaIsPointOnPolygonSurface(pg, x, y))
                            {
                              if (currentGeometry != geom)
                                {
                                  if (currentGeometry)
                                    gaiaFreeGeomColl(currentGeometry);
                                }
                              currentGeometry = geom;
                              currentPK = rowId;
                              minDist = 0.0;
                            }
                          pg = pg->Next;
                        }
                      if (geom != currentGeometry)
                        gaiaFreeGeomColl(geom);
                    }
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

  if (minDist > (5.0 * PixelRatio))
    {
      if (currentGeometry)
        gaiaFreeGeomColl(currentGeometry);
      SetCandidateEntity(-1, NULL);
      DynamicDraw(false);
  } else
    {
      // setting up the CandidateEntity
      SetCandidateEntity(currentPK, currentGeometry);
      DynamicDraw(false);
    }
  return;

stop:
  if (currentGeometry)
    gaiaFreeGeomColl(currentGeometry);
  SetCandidateEntity(-1, NULL);
  DynamicDraw(false);
  return;
}

void MyMapView::UnsetMultiGeometry()
{
//
// unsetting the currently selected MultyGeometry
//
  MainFrame->SetCurrentEntity(-1, NULL);
  SetCandidateEntity(-1, NULL);
  DynamicDraw(false);
}

bool MyMapView::DynamicSplitLine()
{
//
// splits a line in two, creating a new Entity
//
  int iv;
  double x;
  double y;
  double z;
  double m;
  bool ok = false;
  gaiaPointPtr pt;
  int points;
  int ret;
  char *errMsg = NULL;
  wxString sql;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  gaiaLinestringPtr oldLn;
  gaiaLinestringPtr newLn;
  gaiaDynamicLinePtr line1;
  gaiaDynamicLinePtr line2;
  gaiaGeomCollPtr oldGeom = MainFrame->GetCurrentEntityGeometry();
  gaiaGeomCollPtr newGeom = NULL;
  QueryTable columnList;
  QueryColumn *pColumn;
  bool comma;
  char **results;
  int rows;
  int columns;
  int i;
  char *column;
  char *type;
  bool pk;
  bool not_null;
  wxString xColumn;
  wxString xType;
  char xSql[1024];
  int len;
  unsigned char *blob;
  int blob_size;
  int srid;
  sqlite3_int64 rowid = MainFrame->GetCurrentEntityPrimaryKey();

//
// retrieving the Table Metadata
//
  sql = wxT("PRAGMA table_info(\"");
  sql += MainFrame->GetActiveLayer()->GetTableName();
  sql += wxT("\")");
  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  sql = wxT("");
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          column = results[(i * columns) + 1];
          type = results[(i * columns) + 2];
          if (atoi(results[(i * columns) + 3]) == 0)
            not_null = false;
          else
            not_null = true;
          if (atoi(results[(i * columns) + 5]) == 0)
            pk = false;
          else
            pk = true;
          xColumn = wxString::FromUTF8(column);
          xType = wxString::FromUTF8(type);
          if (xColumn != MainFrame->GetActiveLayer()->GetGeometryColumn())
            columnList.Add(xColumn, xType, pk, not_null);
        }
    }
  sqlite3_free_table(results);
  if (columnList.GetCount() <= 0)
    return false;

//
// starting a transaction
//
  ret = sqlite3_exec(sqlite, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }

  if (oldGeom)
    {
      // generating the modified Geometry - already existing Entity
      if (oldGeom->DimensionModel == GAIA_XY_Z)
        newGeom = gaiaAllocGeomCollXYZ();
      else if (oldGeom->DimensionModel == GAIA_XY_M)
        newGeom = gaiaAllocGeomCollXYM();
      else if (oldGeom->DimensionModel == GAIA_XY_Z_M)
        newGeom = gaiaAllocGeomCollXYZM();
      else
        newGeom = gaiaAllocGeomColl();
      srid = oldGeom->Srid;
      newGeom->Srid = srid;
      newGeom->DeclaredType = MainFrame->GetActiveLayerDeclaredType();
      oldLn = oldGeom->FirstLinestring;
      while (oldLn)
        {
          if (CurrentLinestring == oldLn)
            {
              // splitting the selected line
              if (DynamicDoSplitLinestring
                  (CurrentLinestring, CurrentSegmentIndex, CurrentVertexIndex,
                   &CurrentVertexCoords, &line1, &line2) == true)
                {
                  // inserting the first sub-line into the original Geometry
                  points = 0;
                  pt = line1->First;
                  while (pt)
                    {
                      // counting how many vertices are there
                      points++;
                      pt = pt->Next;
                    }
                  newLn = gaiaAddLinestringToGeomColl(newGeom, points);
                  pt = line1->First;
                  iv = 0;
                  while (pt)
                    {
                      // copying vertices
                      if (newLn->DimensionModel == GAIA_XY_Z)
                        {
                          gaiaSetPointXYZ(newLn->Coords, iv, pt->X, pt->Y, 0.0);
                      } else if (newLn->DimensionModel == GAIA_XY_M)
                        {
                          gaiaSetPointXYM(newLn->Coords, iv, pt->X, pt->Y, 0.0);
                      } else if (newLn->DimensionModel == GAIA_XY_Z_M)
                        {
                          gaiaSetPointXYZM(newLn->Coords, iv, pt->X, pt->Y, 0.0,
                                           0.0);
                      } else
                        {
                          gaiaSetPoint(newLn->Coords, iv, pt->X, pt->Y);
                        }
                      iv++;
                      pt = pt->Next;
                    }
                  ok = true;
                }
          } else
            {
              // cloning any other unaffected Linestring
              newLn = gaiaAddLinestringToGeomColl(newGeom, oldLn->Points);
              for (iv = 0; iv < oldLn->Points; iv++)
                {
                  // copying vertices
                  z = 0.0;
                  m = 0.0;
                  if (oldLn->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaGetPointXYZ(oldLn->Coords, iv, &x, &y, &z);
                  } else if (oldLn->DimensionModel == GAIA_XY_M)
                    {
                      gaiaGetPointXYM(oldLn->Coords, iv, &x, &y, &m);
                  } else if (oldLn->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaGetPointXYZM(oldLn->Coords, iv, &x, &y, &z, &m);
                  } else
                    {
                      gaiaGetPoint(oldLn->Coords, iv, &x, &y);
                    }
                  if (newLn->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaSetPointXYZ(newLn->Coords, iv, x, y, z);
                  } else if (newLn->DimensionModel == GAIA_XY_M)
                    {
                      gaiaSetPointXYM(newLn->Coords, iv, x, y, m);
                  } else if (newLn->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaSetPointXYZM(newLn->Coords, iv, x, y, z, m);
                  } else
                    {
                      gaiaSetPoint(newLn->Coords, iv, x, y);
                    }
                }
            }
          oldLn = oldLn->Next;
        }
      if (ok == false)
        {
          gaiaFreeGeomColl(newGeom);
          goto rollback;
        }
      // deleting the fist sub-line
      gaiaFreeDynamicLine(line1);
      // updating the original Entity
      MainFrame->SetCurrentEntityGeometry(newGeom);
      gaiaFreeGeomColl(oldGeom);
      MainFrame->UpdateCurrentEntityGeometry();
      MainFrame->SetCurrentEntity(-1, NULL);
      newGeom = NULL;

      //
      // prepearing the second sub-line Geometry
      //
      if (oldGeom->DimensionModel == GAIA_XY_Z)
        newGeom = gaiaAllocGeomCollXYZ();
      else if (oldGeom->DimensionModel == GAIA_XY_M)
        newGeom = gaiaAllocGeomCollXYM();
      else if (oldGeom->DimensionModel == GAIA_XY_Z_M)
        newGeom = gaiaAllocGeomCollXYZM();
      else
        newGeom = gaiaAllocGeomColl();
      newGeom->Srid = srid;
      newGeom->DeclaredType = MainFrame->GetActiveLayerDeclaredType();
      points = 0;
      pt = line2->First;
      while (pt)
        {
          // counting how many vertices are there
          points++;
          pt = pt->Next;
        }
      newLn = gaiaAddLinestringToGeomColl(newGeom, points);
      pt = line2->First;
      iv = 0;
      while (pt)
        {
          // copying vertices
          if (newLn->DimensionModel == GAIA_XY_Z)
            {
              gaiaSetPointXYZ(newLn->Coords, iv, pt->X, pt->Y, 0.0);
          } else if (newLn->DimensionModel == GAIA_XY_M)
            {
              gaiaSetPointXYM(newLn->Coords, iv, pt->X, pt->Y, 0.0);
          } else if (newLn->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaSetPointXYZM(newLn->Coords, iv, pt->X, pt->Y, 0.0, 0.0);
          } else
            {
              gaiaSetPoint(newLn->Coords, iv, pt->X, pt->Y);
            }
          iv++;
          pt = pt->Next;
        }
      gaiaFreeDynamicLine(line2);

      //
      // preparing the SQL statement to insert the second sub-line
      //
      sql = wxT("INSERT INTO \"");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("\" (");
      comma = false;
      pColumn = columnList.GetFirst();
      while (pColumn)
        {
          // adding any Primary Key column
          if (pColumn->IsPrimaryKey() == true)
            {
              if (comma == false)
                comma = true;
              else
                sql += wxT(", ");
              sql += wxT("\"");
              sql += pColumn->GetColumn();
              sql += wxT("\"");
            }
          pColumn = pColumn->GetNext();
        }
      // adding the Geometry Column
      if (comma == false)
        comma = true;
      else
        sql += wxT(", ");
      sql += wxT("\"");
      sql += MainFrame->GetActiveLayer()->GetGeometryColumn();
      sql += wxT("\"");
      pColumn = columnList.GetFirst();
      while (pColumn)
        {
          // adding any other ordinary column
          if (pColumn->IsPrimaryKey() == false)
            {
              if (comma == false)
                comma = true;
              else
                sql += wxT(", ");
              sql += wxT("\"");
              sql += pColumn->GetColumn();
              sql += wxT("\"");
            }
          pColumn = pColumn->GetNext();
        }
      sql += wxT(") SELECT ");
      comma = false;
      pColumn = columnList.GetFirst();
      while (pColumn)
        {
          // setting any Primary Key value as NULL
          if (pColumn->IsPrimaryKey() == true)
            {
              if (comma == false)
                comma = true;
              else
                sql += wxT(", ");
              sql += wxT("NULL");
            }
          pColumn = pColumn->GetNext();
        }
      // adding the Geometry Column parameter (?)
      if (comma == false)
        comma = true;
      else
        sql += wxT(", ");
      sql += wxT("?");
      pColumn = columnList.GetFirst();
      while (pColumn)
        {
          // adding any other ordinary column name
          if (pColumn->IsPrimaryKey() == false)
            {
              if (comma == false)
                comma = true;
              else
                sql += wxT(", ");
              sql += wxT("\"");
              sql += pColumn->GetColumn();
              sql += wxT("\"");
            }
          pColumn = pColumn->GetNext();
        }
      // adding the FROM and WHERE clauses
      sql += wxT(" FROM \"");
      sql += MainFrame->GetActiveLayer()->GetTableName();
      sql += wxT("\" WHERE ROWID = ?");

      //
      // executing the SQL statement to insert the second sub-line
      //

      MainFrame->ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto rollback;
        }

      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      // binding the Geometry column value
      gaiaToSpatiaLiteBlobWkb(newGeom, &blob, &blob_size);
      sqlite3_bind_blob(stmt, 1, blob, blob_size, free);
      // binding the ROWID value
      sqlite3_bind_int64(stmt, 2, rowid);

      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto rollback;
        }

      sqlite3_finalize(stmt);
    }
  if (newGeom)
    gaiaFreeGeomColl(newGeom);

//
// committing the transaction
//
  ret = sqlite3_exec(sqlite, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  return true;

rollback:
  if (newGeom)
    gaiaFreeGeomColl(newGeom);
//
// performing a rollback anyway
//
  ret = sqlite3_exec(sqlite, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  return false;
}

bool MyMapView::DynamicDoSplitLinestring(gaiaLinestringPtr oldLine, int segmIdx,
                                         int vrtxIdx, gaiaPointPtr vrtxCoords,
                                         gaiaDynamicLinePtr * newLine1,
                                         gaiaDynamicLinePtr * newLine2)
{
//
// trying to split a linestring in two
//
  int iv;
  double x;
  double y;
  double z;
  double m;
  gaiaDynamicLinePtr ln1;
  gaiaDynamicLinePtr ln2;
  *newLine1 = NULL;
  *newLine2 = NULL;
  if (!oldLine)
    return false;
  if (segmIdx < 0 && vrtxIdx < 0)
    return false;
  if (segmIdx >= 0 && vrtxIdx >= 0)
    return false;
  if (segmIdx >= 0)
    {
      // splitting in the middle of some segment requires a vertex interpolation
      if (segmIdx < 1 || vrtxIdx > (oldLine->Points - 1))
        return false;
      ln1 = gaiaAllocDynamicLine();
      for (iv = 0; iv < segmIdx; iv++)
        {
          // creating the first sub-line
          if (oldLine->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(oldLine->Coords, iv, &x, &y, &z);
          } else if (oldLine->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(oldLine->Coords, iv, &x, &y, &m);
          } else if (oldLine->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(oldLine->Coords, iv, &x, &y, &z, &m);
          } else
            {
              gaiaGetPoint(oldLine->Coords, iv, &x, &y);
            }
          gaiaAppendPointToDynamicLine(ln1, x, y);
        }
      // inserting the interpolated vertex into the first sub-line
      gaiaAppendPointToDynamicLine(ln1, vrtxCoords->X, vrtxCoords->Y);
      ln2 = gaiaAllocDynamicLine();
      // inserting the interpolated vertex into the second sub-line
      gaiaAppendPointToDynamicLine(ln2, vrtxCoords->X, vrtxCoords->Y);
      for (iv = segmIdx; iv < oldLine->Points; iv++)
        {
          // creating the second sub-line
          if (oldLine->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(oldLine->Coords, iv, &x, &y, &z);
          } else if (oldLine->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(oldLine->Coords, iv, &x, &y, &m);
          } else if (oldLine->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(oldLine->Coords, iv, &x, &y, &z, &m);
          } else
            {
              gaiaGetPoint(oldLine->Coords, iv, &x, &y);
            }
          gaiaAppendPointToDynamicLine(ln2, x, y);
        }
  } else
    {
      // splitting on some vertex
      if (vrtxIdx < 1 || vrtxIdx > (oldLine->Points - 2))
        return false;
      ln1 = gaiaAllocDynamicLine();
      for (iv = 0; iv <= vrtxIdx; iv++)
        {
          // creating the first sub-line
          if (oldLine->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(oldLine->Coords, iv, &x, &y, &z);
          } else if (oldLine->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(oldLine->Coords, iv, &x, &y, &m);
          } else if (oldLine->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(oldLine->Coords, iv, &x, &y, &z, &m);
          } else
            {
              gaiaGetPoint(oldLine->Coords, iv, &x, &y);
            }
          gaiaAppendPointToDynamicLine(ln1, x, y);
        }
      ln2 = gaiaAllocDynamicLine();
      for (iv = vrtxIdx; iv < oldLine->Points; iv++)
        {
          // creating the second sub-line
          if (oldLine->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(oldLine->Coords, iv, &x, &y, &z);
          } else if (oldLine->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(oldLine->Coords, iv, &x, &y, &m);
          } else if (oldLine->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(oldLine->Coords, iv, &x, &y, &z, &m);
          } else
            {
              gaiaGetPoint(oldLine->Coords, iv, &x, &y);
            }
          gaiaAppendPointToDynamicLine(ln2, x, y);
        }
    }
  *newLine1 = ln1;
  *newLine2 = ln2;
  return true;
}

void MyMapView::SetCandidateEntity(sqlite3_int64 pk, gaiaGeomCollPtr geom)
{
//
// setting up the Candidate Entity
//
  if (CandidateEntityGeometry)
    gaiaFreeGeomColl(CandidateEntityGeometry);
  OkCandidateEntity = false;
  CandidateEntityGeometry = NULL;
  CandidateEntityPrimaryKey = -1;
  if (geom)
    {
      OkCandidateEntity = true;
      CandidateEntityPrimaryKey = pk;
      CandidateEntityGeometry = geom;
    }
}

void MyMapView::ResetDynamics(LayerObject * activeLayer)
{
//
// resetting the Dynamic items [drawing]
//
  int invalid;
  MainFrame->SetActiveLayer(activeLayer);
  if (MainFrame->GetActiveLayer() != NULL)
    {
      if (MainFrame->GetActiveLayer()->GetGeometryType() == LAYER_LINESTRING
          && MainFrame->GetActiveLayer()->IsNetwork() == true)
        {
          MainFrame->LoadNetworkParams();
          if (MainFrame->GetNetwork() == NULL)
            {
              wxString msg = wxT("Internal error: invalid Network\n\n");
              msg +=
                wxT
                ("Sorry, I cannot enable Routing features for this Network ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
          } else
            {
              if (MainFrame->CheckNetworkNodes(&invalid) == false)
                {
                  // the Network Nodes aux table doesn't exists
                  if (invalid)
                    {
                      // the table exists, but has an invalid layout
                      wxString msg =
                        wxT
                        ("The Network Nodes auxiliary table already exists, but has an invalid layout\n\n");
                      msg +=
                        wxT
                        ("Sorry, I cannot enable Routing features for this Network ...\n");
                      wxMessageBox(msg, wxT("spatialite-gis"),
                                   wxOK | wxICON_WARNING, this);
                  } else
                    {
                      // asking the user in order to create
                      wxString msg =
                        wxT
                        ("The Network Nodes auxiliary table doesn't exists\n\n");
                      msg += wxT("Can I create and initialize this table ?");
                      if (wxMessageBox
                          (msg, wxT("spatialite-gis"),
                           wxYES_NO | wxICON_WARNING, this) == wxYES)
                        {
                          if (MainFrame->FeedNetworkNodes() == false)
                            {
                              wxString msg =
                                wxT
                                ("Network Nodes auxiliary table creation failed\n\n");
                              msg +=
                                wxT
                                ("Sorry, I'm not able to enable Routing features for this Network ...\n");
                              wxMessageBox(msg, wxT("spatialite-gis"),
                                           wxOK | wxICON_WARNING, this);
                            }
                      } else
                        {
                          wxString msg =
                            wxT
                            ("You refused to create the Network Nodes auxiliary table\n\n");
                          msg +=
                            wxT
                            ("Sorry, I cannot enable Routing features for this Network ...\n");
                          wxMessageBox(msg, wxT("spatialite-gis"),
                                       wxOK | wxICON_WARNING, this);
                        }
                    }
              } else
                {
                  if (MainFrame->GetNetwork()->IsAuxNodesRTree() == false)
                    {
                      // asking the user in order to create a Spatial Index
                      wxString msg =
                        wxT
                        ("The Network Nodes auxiliary table already exists, but isn't\n");
                      msg +=
                        wxT
                        ("Spatially Indexed: this may cause poor (slow) performance\n\n");
                      msg += wxT("Can I create a Spatial Index ?");
                      if (wxMessageBox
                          (msg, wxT("spatialite-gis"),
                           wxYES_NO | wxICON_WARNING, this) == wxYES)
                        {
                          if (MainFrame->CreateNetworkNodesRTree() == false)
                            {
                              wxString msg =
                                wxT("Spatial Index creation failed\n\n");
                              wxMessageBox(msg, wxT("spatialite-gis"),
                                           wxOK | wxICON_WARNING, this);
                            }
                        }
                    }
                }
            }
        }
    }
  MainFrame->SetCurrentEntity(-1, NULL);
  SetCandidateEntity(-1, NULL);
  if (CurrentDraw)
    gaiaFreeDynamicLine(CurrentDraw);
  CurrentDraw = NULL;
  OkCurrentGeometry = false;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  DynamicDraw(false);
}

void MyMapView::ResetDynamics()
{
//
// resetting the Dynamic items [drawing]
//
  SetCandidateEntity(-1, NULL);
  if (CurrentDraw)
    gaiaFreeDynamicLine(CurrentDraw);
  CurrentDraw = NULL;
  OkCurrentVertex = false;
  OkMovedVertex = false;
  OkInterpolatedVertex = false;
  OkSplitLine = false;
  CurrentPoint = NULL;
  CurrentLinestring = NULL;
  CurrentPolygon = NULL;
  CurrentRing = NULL;
  DynamicDraw(false);
}

int MyMapView::GetCurrentDrawPoints()
{
//
// computing how many points (vertices) are in the Current Draw
//
  gaiaPointPtr pt;
  int points = 0;
  if (!CurrentDraw)
    return 0;
  pt = CurrentDraw->First;
  while (pt)
    {
      points++;
      pt = pt->Next;
    }
  return points;
}

void MyMapView::CopyCurrentDraw(gaiaLinestringPtr ln)
{
//
// copying points from Current Draw to Linestring
//
  int iv = 0;
  gaiaPointPtr pt;
  if (!CurrentDraw || !ln)
    return;
  pt = CurrentDraw->First;
  while (pt)
    {
      if (ln->DimensionModel == GAIA_XY_Z)
        {
          gaiaSetPointXYZ(ln->Coords, iv, pt->X, pt->Y, 0.0);
      } else if (ln->DimensionModel == GAIA_XY_M)
        {
          gaiaSetPointXYM(ln->Coords, iv, pt->X, pt->Y, 0.0);
      } else if (ln->DimensionModel == GAIA_XY_Z_M)
        {
          gaiaSetPointXYZM(ln->Coords, iv, pt->X, pt->Y, 0.0, 0.0);
      } else
        {
          gaiaSetPoint(ln->Coords, iv, pt->X, pt->Y);
        }
      iv++;
      pt = pt->Next;
    }
}

void MyMapView::CopyCurrentDraw(gaiaRingPtr rng)
{
//
// copying points from Current Draw to Ring
//
  int iv = 0;
  gaiaPointPtr pt;
  if (!CurrentDraw || !rng)
    return;
  pt = CurrentDraw->First;
  while (pt)
    {
      if (rng->DimensionModel == GAIA_XY_Z)
        {
          gaiaSetPointXYZ(rng->Coords, iv, pt->X, pt->Y, 0.0);
      } else if (rng->DimensionModel == GAIA_XY_M)
        {
          gaiaSetPointXYM(rng->Coords, iv, pt->X, pt->Y, 0.0);
      } else if (rng->DimensionModel == GAIA_XY_Z_M)
        {
          gaiaSetPointXYZM(rng->Coords, iv, pt->X, pt->Y, 0.0, 0.0);
      } else
        {
          gaiaSetPoint(rng->Coords, iv, pt->X, pt->Y);
        }
      iv++;
      pt = pt->Next;
    }
// inserting last vertex
  pt = CurrentDraw->First;
  if (rng->DimensionModel == GAIA_XY_Z)
    {
      gaiaSetPointXYZ(rng->Coords, iv, pt->X, pt->Y, 0.0);
  } else if (rng->DimensionModel == GAIA_XY_M)
    {
      gaiaSetPointXYM(rng->Coords, iv, pt->X, pt->Y, 0.0);
  } else if (rng->DimensionModel == GAIA_XY_Z_M)
    {
      gaiaSetPointXYZM(rng->Coords, iv, pt->X, pt->Y, 0.0, 0.0);
  } else
    {
      gaiaSetPoint(rng->Coords, iv, pt->X, pt->Y);
    }
  gaiaAppendPointToDynamicLine(CurrentDraw, pt->X, pt->Y);
}

void MyMapView::ResolveRouting()
{
//
// trying to resolve a routing problem
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  wxString sql;
  int ret;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  bool nameCol = false;
  RoutingSolution *solution = MainFrame->GetNetwork()->GetSolution();
  if (MainFrame->GetNetwork()->GetNodeFrom()->IsValid() == false)
    return;
  if (MainFrame->GetNetwork()->GetNodeTo()->IsValid() == false)
    return;
  ::wxBeginBusyCursor();
  solution->TimeStart();
  solution->CleanUp();
// preparing the SQL query
  sql = wxT("SELECT Algorithm, ArcRowid, NodeFrom, NodeTo, Cost, Geometry");
  if (MainFrame->GetNetwork()->GetNameColumn().Len() > 0)
    {
      sql += wxT(", Name");
      nameCol = true;
    }
  sql += wxT(" FROM \"");
  sql += MainFrame->GetNetwork()->GetNetworkTable();
  sql += wxT("\" WHERE NodeFrom = ? AND NodeTo = ?");
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
  if (MainFrame->GetNetwork()->IsTextNodes() == true)
    {
      // nodes are identified by TEXT
      char from[256];
      char to[256];
      strcpy(from,
             MainFrame->GetNetwork()->GetNodeFrom()->GetNodeText().ToUTF8());
      strcpy(to, MainFrame->GetNetwork()->GetNodeTo()->GetNodeText().ToUTF8());
      sqlite3_bind_text(stmt, 1, from, strlen(from), SQLITE_TRANSIENT);
      sqlite3_bind_text(stmt, 2, to, strlen(to), SQLITE_TRANSIENT);
      solution->SetFromTo(MainFrame->GetNetwork()->GetNodeFrom()->GetNodeText(),
                          MainFrame->GetNetwork()->GetNodeTo()->GetNodeText());
  } else
    {
      // nodes are identifies by INTs
      sqlite3_bind_int64(stmt, 1,
                         MainFrame->GetNetwork()->GetNodeFrom()->GetNodeId());
      sqlite3_bind_int64(stmt, 2,
                         MainFrame->GetNetwork()->GetNodeTo()->GetNodeId());
      solution->SetFromTo(MainFrame->GetNetwork()->GetNodeFrom()->GetNodeId(),
                          MainFrame->GetNetwork()->GetNodeTo()->GetNodeId());
    }

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          // fetching a valid row
          if (sqlite3_column_type(stmt, 1) == SQLITE_NULL)
            {
              // found the global solution row
              gaiaGeomCollPtr geom = NULL;
              char proj_from[1024];
              char proj_to[1024];
              const unsigned char *algorithm;
              double cost = sqlite3_column_double(stmt, 4);
              if (sqlite3_column_type(stmt, 5) == SQLITE_BLOB)
                {
                  const void *blob = sqlite3_column_blob(stmt, 5);
                  int blob_size = sqlite3_column_bytes(stmt, 5);
                  geom =
                    gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                              blob_size);
                }
              if (sqlite3_column_type(stmt, 0) == SQLITE_TEXT)
                {
                  algorithm = sqlite3_column_text(stmt, 0);
                  if (strcmp((char *) algorithm, "A*") == 0)
                    {
                      wxString a_star = wxT("A*");
                      solution->SetRoutingAlgorithm(a_star);
                    }
                }
              solution->SetCost(cost);
              if (geom)
                {
                  if (geom->Srid == MainFrame->GetProjectCrs().GetSrid())
                    ;
                  else
                    {
                      // the Routing Solution uses a SRID not identical to the one set for the Project
                      bool ok_from =
                        MainFrame->GetProjParams(geom->Srid, proj_from);
                      bool ok_to =
                        MainFrame->GetProjParams(MainFrame->GetProjectCrs().
                                                 GetSrid(),
                                                 proj_to);
                      if (ok_from == true && ok_to == true)
                        {
                          // applying reprojection to current MapFrame
                          gaiaGeomCollPtr geom2 =
                            gaiaTransform(geom, proj_to, proj_from);
                          gaiaFreeGeomColl(geom);
                          geom = geom2;
                        }
                    }
                }
              solution->SetGeometry(geom);
          } else
            {
              // found an arc row
              sqlite3_int64 arcId;
              const unsigned char *nodeFromText = NULL;
              sqlite3_int64 nodeFromId;
              const unsigned char *nodeToText = NULL;
              sqlite3_int64 nodeToId;
              double cost;
              const unsigned char *roadName = NULL;
              arcId = sqlite3_column_int64(stmt, 1);
              if (sqlite3_column_type(stmt, 2) == SQLITE_TEXT)
                nodeFromText = sqlite3_column_text(stmt, 2);
              else
                nodeFromId = sqlite3_column_int64(stmt, 2);
              if (sqlite3_column_type(stmt, 3) == SQLITE_TEXT)
                nodeToText = sqlite3_column_text(stmt, 3);
              else
                nodeToId = sqlite3_column_int64(stmt, 3);
              cost = sqlite3_column_double(stmt, 4);
              if (nameCol == true)
                roadName = sqlite3_column_text(stmt, 6);
              if (!nodeFromText && !nodeToText)
                solution->Add(arcId, nodeFromId, nodeToId, cost, roadName);
              if (nodeFromText && nodeToText)
                solution->Add(arcId, nodeFromText, nodeToText, cost, roadName);
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
  solution->CheckValid();

stop:
  solution->TimeStop();
  ::wxEndBusyCursor();
  ResetScreenBitmap();
  if (solution->IsValid() == false)
    {
      wxMessageBox(wxT("Invalid routing\nDestination unreachable"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
  } else
    {
      // displaying the Routing Solution Dialog
      ClearMapTip();
      RoutingSolutionDialog dlg;
      dlg.Create(this, MainFrame, solution, nameCol,
                 MainFrame->GetNetwork()->IsTextNodes());
      dlg.ShowModal();
    }
}

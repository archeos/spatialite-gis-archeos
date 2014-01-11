/*
/ GraphicsDlgs.cpp
/ various dialog classes [graphics]
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

#include "wx/colordlg.h"
#include "wx/graphics.h"
#include "wx/imaglist.h"

#include "Classdef.h"

#include "icons/checked_brush.xpm"

bool PointGraphicsDialog::Create(MyFrame * parent, wxString & table,
                                 wxString & geom, wxString & descName,
                                 int symbolId, wxColour & foreground,
                                 wxColour & background)
{
//
// creating the dialog
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  SymbolId = symbolId;
  ColorSymbol = false;
  ForegroundColor = foreground;
  BackgroundColor = background;
  CurrentForeground = foreground;
  CurrentBackground = background;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Graphics - POINT")) ==
      false)
    return false;
// populates individual controls
  Bitmap = wxBitmap(64, 64);
  MainFrame->GetSymbolBitmaps(&SymbolsList);
  CurrentSymbol = SymbolsList.FindById(SymbolId);
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void PointGraphicsDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: the Layer Table+Geometry
  wxBoxSizer *layerSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *layerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Vector Layer:"));
  layerSizer->Add(layerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString name = TableName + wxT(".") + GeometryColumn;
  wxTextCtrl *layerValue = new wxTextCtrl(this, wxID_STATIC,
                                          name, wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  layerSizer->Add(layerValue, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: description
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  DescCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                            wxDefaultPosition, wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// third row: Symbol
  wxBoxSizer *symbolBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(symbolBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *symBox = new wxStaticBox(this, wxID_STATIC,
                                        wxT("Symbol selection"),
                                        wxDefaultPosition,
                                        wxDefaultSize);
  wxBoxSizer *symGroupSizer = new wxStaticBoxSizer(symBox, wxVERTICAL);
  symbolBoxSizer->Add(symGroupSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *symSizer = new wxBoxSizer(wxHORIZONTAL);
  symGroupSizer->Add(symSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  SymbolsCtrl =
    new wxListCtrl(this, ID_POINT_SYMBOLS, wxDefaultPosition, wxSize(400, 300),
                   wxLC_ICON | wxLC_SINGLE_SEL);
  symGroupSizer->Add(SymbolsCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  SymbolsCtrl->AssignImageList(SymbolsList.BuildList(), wxIMAGE_LIST_NORMAL);
  int i;
  for (i = 0;
       i < SymbolsCtrl->GetImageList(wxIMAGE_LIST_NORMAL)->GetImageCount(); i++)
    SymbolsCtrl->InsertItem(i, i);
  SymbolsCtrl->SetBackgroundColour(wxColour(240, 240, 208));
  if (CurrentSymbol)
    {
      // selecting the current item
      SymbolsCtrl->SetItemState(CurrentSymbol->GetListId(),
                                wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
      SymbolsCtrl->EnsureVisible(CurrentSymbol->GetListId());
    }
// fourth row: FOREGROUND and BACKGROUND buttons
  wxBoxSizer *foreBackBox = new wxBoxSizer(wxHORIZONTAL);
  symGroupSizer->Add(foreBackBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticText *foreLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Foreground:"));
  foreBackBox->Add(foreLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap disabledBmp;
  GetDisabledButtonBitmap(disabledBmp);
  wxBitmap foreBmp;
  GetButtonBitmap(CurrentForeground, foreBmp);
  ForegroundCtrl = new wxBitmapButton(this, ID_POINT_FOREGROUND, foreBmp);
  ForegroundCtrl->SetBitmapDisabled(disabledBmp);
  foreBackBox->Add(ForegroundCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxStaticText *backLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Background:"));
  foreBackBox->Add(backLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap backBmp;
  GetButtonBitmap(CurrentBackground, backBmp);
  BackgroundCtrl = new wxBitmapButton(this, ID_POINT_BACKGROUND, backBmp);
  BackgroundCtrl->SetBitmapDisabled(disabledBmp);
  foreBackBox->Add(BackgroundCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  if (CurrentSymbol)
    {
      if (CurrentSymbol->IsFullColor() == true)
        {
          ForegroundCtrl->Enable(false);
          BackgroundCtrl->Enable(false);
      } else
        {
          ForegroundCtrl->Enable(true);
          BackgroundCtrl->Enable(true);
        }
  } else
    {
      ForegroundCtrl->Enable(false);
      BackgroundCtrl->Enable(false);
    }

  // fifth row: Example
  wxBoxSizer *exampleBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(exampleBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *exampleBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Example"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *exampleSizer = new wxStaticBoxSizer(exampleBox, wxHORIZONTAL);
  exampleBoxSizer->Add(exampleSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  PaintBitmap();
  ExampleCtrl =
    new wxStaticBitmap(this, ID_POINT_EXAMPLE, Bitmap, wxDefaultPosition,
                       wxSize(Bitmap.GetWidth(), Bitmap.GetHeight()),
                       wxBORDER_SUNKEN);
  exampleSizer->Add(ExampleCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PointGraphicsDialog::OnOk);
  Connect(ID_POINT_SYMBOLS, wxEVT_COMMAND_LIST_ITEM_SELECTED,
          (wxObjectEventFunction) & PointGraphicsDialog::OnSymbolSelected);
  Connect(ID_POINT_FOREGROUND, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PointGraphicsDialog::OnForeground);
  Connect(ID_POINT_BACKGROUND, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PointGraphicsDialog::OnBackground);
}

void PointGraphicsDialog::GetButtonBitmap(wxColour & color, wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(color));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

void PointGraphicsDialog::GetDisabledButtonBitmap(wxBitmap & bmp)
{
// creating the disabled Bitmap
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

void PointGraphicsDialog::PaintBitmap()
{
// painting the Example Bitmap
  wxBrush checkedBrush;
  checkedBrush.SetStipple(wxBitmap(checked_brush_xpm));
  checkedBrush.SetStyle(wxSTIPPLE);
  wxMemoryDC *dc = new wxMemoryDC(Bitmap);
  wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
// background initialization
  gr->SetBrush(checkedBrush);
  gr->DrawRectangle(0, 0, Bitmap.GetWidth(), Bitmap.GetHeight());
// drawing the crosshair
  gr->SetPen(wxPen(wxColour(255, 0, 0, 64)));
  gr->StrokeLine(-1, -1, Bitmap.GetWidth(), Bitmap.GetHeight());
  gr->StrokeLine(Bitmap.GetWidth(), -1, -1, Bitmap.GetHeight());
  gr->StrokeLine(Bitmap.GetWidth() / 2, -1, Bitmap.GetWidth() / 2,
                 Bitmap.GetHeight());
  gr->StrokeLine(-1, Bitmap.GetHeight() / 2, Bitmap.GetWidth(),
                 Bitmap.GetHeight() / 2);
  if (CurrentSymbol == NULL)
    {
      // drawing a default marker
      gr->SetPen(wxColour(0, 255, 0));
      gr->SetBrush(wxBrush(wxColour(255, 0, 0)));
      gr->DrawEllipse(Bitmap.GetWidth() / 2, Bitmap.GetHeight() / 2, 4, 4);
  } else
    {
      // drawing the symbol
      wxBitmap bmp;
      CurrentSymbol->GetBitmap(bmp, CurrentForeground, CurrentBackground);
      wxMask *mask = new wxMask(CurrentSymbol->GetMask());
      bmp.SetMask(mask);
      gr->DrawBitmap(bmp,
                     (Bitmap.GetWidth() / 2) - CurrentSymbol->GetHotPointX(),
                     (Bitmap.GetHeight() / 2) - CurrentSymbol->GetHotPointY(),
                     bmp.GetWidth(), bmp.GetHeight());
    }
  delete gr;
  delete dc;
}

void PointGraphicsDialog::OnSymbolSelected(wxCommandEvent & WXUNUSED(event))
{
// symbol selection changed
  int item = -1;
  for (;;)
    {
      item =
        SymbolsCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
      if (item == -1)
        break;
      CurrentSymbol = SymbolsList.FindByPos(item);
    }
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
  if (CurrentSymbol)
    {
      if (CurrentSymbol->IsFullColor() == true)
        {
          ForegroundCtrl->Enable(false);
          BackgroundCtrl->Enable(false);
      } else
        {
          ForegroundCtrl->Enable(true);
          BackgroundCtrl->Enable(true);
        }
  } else
    {
      ForegroundCtrl->Enable(false);
      BackgroundCtrl->Enable(false);
    }
}

void PointGraphicsDialog::OnForeground(wxCommandEvent & WXUNUSED(event))
{
// foreground color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(CurrentForeground);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      CurrentForeground = colorData.GetColour();
      PaintBitmap();
      ExampleCtrl->SetBitmap(Bitmap);
      wxBitmap bmp;
      GetButtonBitmap(CurrentForeground, bmp);
      ForegroundCtrl->SetBitmapLabel(bmp);
    }
}

void PointGraphicsDialog::OnBackground(wxCommandEvent & WXUNUSED(event))
{
// background color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(CurrentBackground);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      CurrentBackground = colorData.GetColour();
      PaintBitmap();
      ExampleCtrl->SetBitmap(Bitmap);
      wxBitmap bmp;
      GetButtonBitmap(CurrentBackground, bmp);
      BackgroundCtrl->SetBitmapLabel(bmp);
    }
}

void PointGraphicsDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  if (CurrentSymbol)
    {
      SymbolId = CurrentSymbol->GetId();
      ColorSymbol = CurrentSymbol->IsFullColor();
    }
  ForegroundColor = CurrentForeground;
  BackgroundColor = CurrentBackground;
  DescName = DescCtrl->GetValue();
  wxDialog::EndModal(wxID_OK);
}

bool LineGraphicsDialog::Create(MyFrame * parent, wxString & table,
                                wxString & geom, wxString & descName,
                                wxColour & color, int thickness, int style)
{
//
// creating the dialog
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  LineColor = color;
  CurrentColor = color;
  LineThickness = thickness;
  CurrentThickness = thickness;
  LineStyle = style;
  CurrentStyle = style;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Graphics - LINESTRING")) ==
      false)
    return false;
// populates individual controls
  Bitmap = wxBitmap(400, 64);
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void LineGraphicsDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: the Layer Table+Geometry
  wxBoxSizer *layerSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *layerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Vector Layer:"));
  layerSizer->Add(layerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString name = TableName + wxT(".") + GeometryColumn;
  wxTextCtrl *layerValue = new wxTextCtrl(this, wxID_STATIC,
                                          name, wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  layerSizer->Add(layerValue, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: description
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  DescCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                            wxDefaultPosition, wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// third row: Graphics
  wxBoxSizer *graphicsBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(graphicsBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *grBox = new wxStaticBox(this, wxID_STATIC,
                                       wxT("Line graphics"),
                                       wxDefaultPosition,
                                       wxDefaultSize);
  wxBoxSizer *grGroupSizer = new wxStaticBoxSizer(grBox, wxVERTICAL);
  graphicsBoxSizer->Add(grGroupSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *colorSizer = new wxBoxSizer(wxHORIZONTAL);
  grGroupSizer->Add(colorSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxBitmap disabledBmp;
  GetDisabledButtonBitmap(disabledBmp);
  wxBitmap colorBmp;
  GetButtonBitmap(CurrentColor, colorBmp);
  ColorCtrl = new wxBitmapButton(this, ID_LINE_COLOR, colorBmp);
  ColorCtrl->SetBitmapDisabled(disabledBmp);
  colorSizer->Add(ColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxStaticText *alphaLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Transparency:"));
  colorSizer->Add(alphaLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  AlphaCtrl =
    new wxSlider(this, ID_LINE_ALPHA, CurrentColor.Alpha(), 0, 255,
                 wxDefaultPosition, wxSize(75, 20),
                 wxSL_HORIZONTAL | wxSL_INVERSE);
  colorSizer->Add(AlphaCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxStaticText *thicknessLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Thickness:"));
  colorSizer->Add(thicknessLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  char dummy[64];
  sprintf(dummy, "%d", CurrentThickness);
  wxString thick = wxString::FromUTF8(dummy);
  ThicknessCtrl = new wxSpinCtrl(this, ID_LINE_THICKNESS, thick,
                                 wxDefaultPosition, wxSize(80, 20),
                                 wxSP_ARROW_KEYS, 1, 32, CurrentThickness);
  colorSizer->Add(ThicknessCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxBoxSizer *styleBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  grGroupSizer->Add(styleBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *stlBox = new wxStaticBox(this, wxID_STATIC,
                                        wxT("Style"),
                                        wxDefaultPosition,
                                        wxDefaultSize);
  wxBoxSizer *styleSizer = new wxStaticBoxSizer(stlBox, wxVERTICAL);
  styleBoxSizer->Add(styleSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

  StyleCtrl =
    new wxListCtrl(this, ID_LINE_STYLE, wxDefaultPosition, wxSize(400, 100),
                   wxLC_ICON | wxLC_SINGLE_SEL);
  styleSizer->Add(StyleCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  StyleCtrl->AssignImageList(BuildStyleList(), wxIMAGE_LIST_NORMAL);
  int i;
  for (i = 0; i < StyleCtrl->GetImageList(wxIMAGE_LIST_NORMAL)->GetImageCount();
       i++)
    StyleCtrl->InsertItem(i, i);
// selecting the current item
  int pos = Find();
  if (pos > 0)
    {
      StyleCtrl->SetItemState(pos, wxLIST_STATE_SELECTED,
                              wxLIST_STATE_SELECTED);
      StyleCtrl->EnsureVisible(pos);
    }
  // fourth row: Example
  wxBoxSizer *exampleBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(exampleBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *exampleBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Example"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *exampleSizer = new wxStaticBoxSizer(exampleBox, wxHORIZONTAL);
  exampleBoxSizer->Add(exampleSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  PaintBitmap();
  ExampleCtrl =
    new wxStaticBitmap(this, ID_LINE_EXAMPLE, Bitmap, wxDefaultPosition,
                       wxSize(Bitmap.GetWidth(), Bitmap.GetHeight()),
                       wxBORDER_SUNKEN);
  exampleSizer->Add(ExampleCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LineGraphicsDialog::OnOk);
  Connect(ID_LINE_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LineGraphicsDialog::OnColor);
  Connect(ID_LINE_ALPHA, wxEVT_SCROLL_THUMBRELEASE,
          (wxObjectEventFunction) & LineGraphicsDialog::OnAlphaChanged);
  Connect(ID_LINE_ALPHA, wxEVT_SCROLL_CHANGED,
          (wxObjectEventFunction) & LineGraphicsDialog::OnAlphaChanged);
  Connect(ID_LINE_THICKNESS, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & LineGraphicsDialog::OnThicknessChanged);
  Connect(ID_LINE_STYLE, wxEVT_COMMAND_LIST_ITEM_SELECTED,
          (wxObjectEventFunction) & LineGraphicsDialog::OnStyleSelected);
}

void LineGraphicsDialog::GetButtonBitmap(wxColour & color, wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(color));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

void LineGraphicsDialog::GetDisabledButtonBitmap(wxBitmap & bmp)
{
// creating the disabled Bitmap
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

wxImageList *LineGraphicsDialog::BuildStyleList()
{
// building the style's images
  wxBitmap img1(72, 8);
  wxBitmap img2(72, 8);
  wxBitmap img3(72, 8);
  wxBitmap img4(72, 8);
  wxBitmap img5(72, 8);
  wxColour color(255, 255, 255);
  wxBrush background(wxColour(204, 204, 204));
  wxColour foreground(0, 0, 0);
  wxImageList *list = new wxImageList(72, 8, true, 5);
  wxMemoryDC *dc = new wxMemoryDC(img1);
// wxSOLID example
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img1.GetWidth() + 2, img1.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxSOLID));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img1, color);
// wxDOT example
  dc = new wxMemoryDC(img2);
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img2.GetWidth() + 2, img2.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxDOT));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img2, color);
// wxLONG_DASH example
  dc = new wxMemoryDC(img3);
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img3.GetWidth() + 2, img3.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxLONG_DASH));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img3, color);
// wxSHORT_DASH example
  dc = new wxMemoryDC(img4);
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img4.GetWidth() + 2, img4.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxSHORT_DASH));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img4, color);
// wxDOT_DASH example
  dc = new wxMemoryDC(img5);
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img5.GetWidth() + 2, img5.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxDOT_DASH));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img5, color);

  return list;
}

int LineGraphicsDialog::Find()
{
// return the position corresponding to the current style
  if (CurrentStyle == wxSOLID)
    return 0;
  if (CurrentStyle == wxDOT)
    return 1;
  if (CurrentStyle == wxLONG_DASH)
    return 2;
  if (CurrentStyle == wxSHORT_DASH)
    return 3;
  if (CurrentStyle == wxDOT_DASH)
    return 4;
// otherwyse we have some odd style
  CurrentStyle = wxSOLID;
  return 0;
}

int LineGraphicsDialog::Find(int pos)
{
// return the wxXXX constant corresponding to the currently selected style
  if (pos == 0)
    return wxSOLID;
  if (pos == 1)
    return wxDOT;
  if (pos == 2)
    return wxLONG_DASH;
  if (pos == 3)
    return wxSHORT_DASH;
  if (pos == 4)
    return wxDOT_DASH;
// otherwyse we have some odd style
  return wxSOLID;
}

void LineGraphicsDialog::PaintBitmap()
{
// painting the Example Bitmap
  wxBrush checkedBrush;
  int tick = Bitmap.GetWidth() / 6;
  checkedBrush.SetStipple(wxBitmap(checked_brush_xpm));
  checkedBrush.SetStyle(wxSTIPPLE);
  wxMemoryDC *dc = new wxMemoryDC(Bitmap);
  wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
// background initialization
  gr->SetBrush(checkedBrush);
  gr->DrawRectangle(0, 0, Bitmap.GetWidth(), Bitmap.GetHeight());
// drawing the line
  gr->SetPen(wxPen(CurrentColor, CurrentThickness, CurrentStyle));
  wxGraphicsPath path = gr->CreatePath();
  path.MoveToPoint(12, 12);
  path.AddLineToPoint(tick, Bitmap.GetHeight() - 12);
  path.AddLineToPoint((tick * 2), 12);
  path.AddLineToPoint((tick * 3), Bitmap.GetHeight() - 12);
  path.AddLineToPoint((tick * 4), 12);
  path.AddLineToPoint((tick * 5), Bitmap.GetHeight() - 12);
  path.AddLineToPoint(Bitmap.GetWidth() - 12, 12);
  gr->StrokePath(path);

  delete gr;
  delete dc;
}

void LineGraphicsDialog::OnColor(wxCommandEvent & WXUNUSED(event))
{
// color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(CurrentColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      wxColour color = colorData.GetColour();
      CurrentColor =
        wxColour(color.Red(), color.Green(), color.Blue(),
                 CurrentColor.Alpha());
      PaintBitmap();
      ExampleCtrl->SetBitmap(Bitmap);
      wxBitmap bmp;
      GetButtonBitmap(CurrentColor, bmp);
      ColorCtrl->SetBitmapLabel(bmp);
    }
}

void LineGraphicsDialog::OnAlphaChanged(wxCommandEvent & WXUNUSED(event))
{
//
// ALPHA selection changed
//
  CurrentColor =
    wxColour(CurrentColor.Red(), CurrentColor.Green(), CurrentColor.Blue(),
             AlphaCtrl->GetValue());
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LineGraphicsDialog::OnThicknessChanged(wxCommandEvent & WXUNUSED(event))
{
//
// THICKNESS selection changed
//
  CurrentThickness = ThicknessCtrl->GetValue();
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LineGraphicsDialog::OnStyleSelected(wxCommandEvent & WXUNUSED(event))
{
// style selection changed
  int item = -1;
  for (;;)
    {
      item =
        StyleCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
      if (item == -1)
        break;
      CurrentStyle = Find(item);
    }
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LineGraphicsDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  LineColor = CurrentColor;
  LineThickness = CurrentThickness;
  LineStyle = CurrentStyle;
  DescName = DescCtrl->GetValue();
  wxDialog::EndModal(wxID_OK);
}

bool PolygonGraphicsDialog::Create(MyFrame * parent, wxString & table,
                                   wxString & geom, wxString & descName,
                                   wxColour & borderColor, int thickness,
                                   int style)
{
//
// creating the dialog - border, no interior filling
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  BorderColor = borderColor;
  CurrentBorderColor = borderColor;
  BorderThickness = thickness;
  CurrentBorderThickness = thickness;
  BorderStyle = style;
  CurrentBorderStyle = style;
  DrawBorder = true;
  ToFill = false;
  SolidFilling = true;
  CurrentDrawBorder = DrawBorder;
  CurrentToFill = ToFill;
  CurrentSolidFilling = SolidFilling;
  FillColor = wxColour(0, 128, 64);
  CurrentFillColor = FillColor;
  PatternId = 1;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Graphics - POLYGON")) ==
      false)
    return false;
// populates individual controls
  Bitmap = wxBitmap(400, 64);
  MainFrame->GetPatternBitmaps(&PatternsList);
  CurrentPattern = PatternsList.FindById(PatternId);
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

bool PolygonGraphicsDialog::Create(MyFrame * parent, wxString & table,
                                   wxString & geom, wxString & descName,
                                   wxColour & fillColor)
{
//
// creating the dialog - no border, solid color interior filling
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  BorderColor = wxColour(0, 255, 128, 255);
  CurrentBorderColor = BorderColor;
  BorderThickness = 1;
  CurrentBorderThickness = BorderThickness;
  BorderStyle = wxSOLID;
  CurrentBorderStyle = BorderStyle;
  DrawBorder = false;
  ToFill = true;
  SolidFilling = true;
  CurrentDrawBorder = DrawBorder;
  CurrentToFill = ToFill;
  CurrentSolidFilling = SolidFilling;
  FillColor = fillColor;
  CurrentFillColor = FillColor;
  PatternId = 1;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Graphics - POLYGON")) ==
      false)
    return false;
// populates individual controls
  Bitmap = wxBitmap(400, 64);
  MainFrame->GetPatternBitmaps(&PatternsList);
  CurrentPattern = PatternsList.FindById(PatternId);
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

bool PolygonGraphicsDialog::Create(MyFrame * parent, wxString & table,
                                   wxString & geom, wxString & descName,
                                   wxColour & borderColor, int thickness,
                                   int style, wxColour & fillColor)
{
//
// creating the dialog - border and solid color interior filling
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  BorderColor = borderColor;
  CurrentBorderColor = borderColor;
  BorderThickness = thickness;
  CurrentBorderThickness = thickness;
  BorderStyle = style;
  CurrentBorderStyle = style;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = true;
  CurrentDrawBorder = DrawBorder;
  CurrentToFill = ToFill;
  CurrentSolidFilling = SolidFilling;
  FillColor = fillColor;
  CurrentFillColor = FillColor;
  PatternId = 1;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Graphics - POLYGON")) ==
      false)
    return false;
// populates individual controls
  Bitmap = wxBitmap(400, 64);
  MainFrame->GetPatternBitmaps(&PatternsList);
  CurrentPattern = PatternsList.FindById(PatternId);
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

bool PolygonGraphicsDialog::Create(MyFrame * parent, wxString & table,
                                   wxString & geom, wxString & descName,
                                   int patternId, wxColour & fillColor)
{
//
// creating the dialog - no border, pattern interior filling
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  BorderColor = wxColour(0, 255, 128, 255);
  CurrentBorderColor = BorderColor;
  BorderThickness = 1;
  CurrentBorderThickness = BorderThickness;
  BorderStyle = wxSOLID;
  CurrentBorderStyle = BorderStyle;
  DrawBorder = false;
  ToFill = true;
  SolidFilling = false;
  CurrentDrawBorder = DrawBorder;
  CurrentToFill = ToFill;
  CurrentSolidFilling = SolidFilling;
  FillColor = fillColor;
  CurrentFillColor = FillColor;
  PatternId = patternId;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Graphics - POLYGON")) ==
      false)
    return false;
// populates individual controls
  Bitmap = wxBitmap(400, 64);
  MainFrame->GetPatternBitmaps(&PatternsList);
  CurrentPattern = PatternsList.FindById(PatternId);
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

bool PolygonGraphicsDialog::Create(MyFrame * parent, wxString & table,
                                   wxString & geom, wxString & descName,
                                   wxColour & borderColor, int thickness,
                                   int style, int patternId,
                                   wxColour & fillColor)
{
//
// creating the dialog - border and pattern interior filling
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  BorderColor = borderColor;
  CurrentBorderColor = borderColor;
  BorderThickness = thickness;
  CurrentBorderThickness = thickness;
  BorderStyle = style;
  CurrentBorderStyle = style;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = false;
  CurrentDrawBorder = DrawBorder;
  CurrentToFill = ToFill;
  CurrentSolidFilling = SolidFilling;
  FillColor = fillColor;
  CurrentFillColor = FillColor;
  PatternId = patternId;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Graphics - POLYGON")) ==
      false)
    return false;
// populates individual controls
  Bitmap = wxBitmap(128, 64);
  MainFrame->GetPatternBitmaps(&PatternsList);
  CurrentPattern = PatternsList.FindById(PatternId);
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void PolygonGraphicsDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: the Layer Table+Geometry
  wxBoxSizer *layerSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *layerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Vector Layer:"));
  layerSizer->Add(layerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString name = TableName + wxT(".") + GeometryColumn;
  wxTextCtrl *layerValue = new wxTextCtrl(this, wxID_STATIC,
                                          name, wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  layerSizer->Add(layerValue, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: description
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  DescCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                            wxDefaultPosition, wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: Border Mode / Filling Mode
  wxBoxSizer *modeSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(modeSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxString border_modes[2];
  border_modes[0] = wxT("&Visible");
  border_modes[1] = wxT("&No border");
  BorderModeCtrl = new wxRadioBox(this, ID_POLYGON_BORDER_MODE,
                                  wxT("&Border Mode"), wxDefaultPosition,
                                  wxDefaultSize, 2, border_modes, 1,
                                  wxRA_SPECIFY_ROWS);
  if (DrawBorder == true)
    BorderModeCtrl->SetSelection(0);
  else
    BorderModeCtrl->SetSelection(1);
  modeSizer->Add(BorderModeCtrl, 0, wxALIGN_LEFT | wxALL, 5);

  wxString fill_modes[3];
  fill_modes[0] = wxT("&Omit");
  fill_modes[1] = wxT("&Solid Color");
  fill_modes[2] = wxT("&Pattern");
  FillingModeCtrl = new wxRadioBox(this, ID_POLYGON_FILL_MODE,
                                   wxT("&Interior Filling Mode"),
                                   wxDefaultPosition, wxDefaultSize, 3,
                                   fill_modes, 1, wxRA_SPECIFY_ROWS);
  if (ToFill == false)
    FillingModeCtrl->SetSelection(0);
  else
    {
      if (SolidFilling == true)
        FillingModeCtrl->SetSelection(1);
      else
        FillingModeCtrl->SetSelection(2);
    }
  modeSizer->Add(FillingModeCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// fourth row: Border Graphics
  wxBoxSizer *borderGraphicsBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(borderGraphicsBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                0);
  wxStaticBox *borderGrBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Border graphics"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *borderGrGroupSizer =
    new wxStaticBoxSizer(borderGrBox, wxVERTICAL);
  borderGraphicsBoxSizer->Add(borderGrGroupSizer, 0,
                              wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *borderColorSizer = new wxBoxSizer(wxHORIZONTAL);
  borderGrGroupSizer->Add(borderColorSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxBitmap disabledBmp;
  GetDisabledButtonBitmap(disabledBmp);
  wxBitmap borderBmp;
  GetButtonBitmap(CurrentBorderColor, borderBmp);
  BorderColorCtrl =
    new wxBitmapButton(this, ID_POLYGON_BORDER_COLOR, borderBmp);
  BorderColorCtrl->SetBitmapDisabled(disabledBmp);
  borderColorSizer->Add(BorderColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxStaticText *borderAlphaLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Transparency:"));
  borderColorSizer->Add(borderAlphaLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5);
  BorderAlphaCtrl =
    new wxSlider(this, ID_POLYGON_BORDER_ALPHA, CurrentBorderColor.Alpha(), 0,
                 255, wxDefaultPosition, wxSize(75, 20),
                 wxSL_HORIZONTAL | wxSL_INVERSE);
  borderColorSizer->Add(BorderAlphaCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxStaticText *thicknessLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Thickness:"));
  borderColorSizer->Add(thicknessLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  char dummy[64];
  sprintf(dummy, "%d", CurrentBorderThickness);
  wxString thick = wxString::FromUTF8(dummy);
  ThicknessCtrl = new wxSpinCtrl(this, ID_POLYGON_BORDER_THICKNESS, thick,
                                 wxDefaultPosition, wxSize(80, 20),
                                 wxSP_ARROW_KEYS, 1, 32,
                                 CurrentBorderThickness);
  borderColorSizer->Add(ThicknessCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxBoxSizer *styleBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  borderGrGroupSizer->Add(styleBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                          0);
  wxStaticBox *stlBox = new wxStaticBox(this, wxID_STATIC,
                                        wxT("Style"),
                                        wxDefaultPosition,
                                        wxDefaultSize);
  wxBoxSizer *styleSizer = new wxStaticBoxSizer(stlBox, wxVERTICAL);
  styleBoxSizer->Add(styleSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

  StyleCtrl =
    new wxListCtrl(this, ID_POLYGON_BORDER_STYLE, wxDefaultPosition,
                   wxSize(400, 40), wxLC_ICON | wxLC_SINGLE_SEL);
  styleSizer->Add(StyleCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  StyleCtrl->AssignImageList(BuildStyleList(), wxIMAGE_LIST_NORMAL);
  int i;
  for (i = 0; i < StyleCtrl->GetImageList(wxIMAGE_LIST_NORMAL)->GetImageCount();
       i++)
    StyleCtrl->InsertItem(i, i);
  if (DrawBorder == false)
    {
      // disabling the border controls
      BorderColorCtrl->Enable(false);
      BorderAlphaCtrl->Enable(false);
      ThicknessCtrl->Enable(false);
      StyleCtrl->Enable(false);
  } else
    {
      // selecting the current item
      int pos = Find();
      if (pos > 0)
        {
          StyleCtrl->SetItemState(pos, wxLIST_STATE_SELECTED,
                                  wxLIST_STATE_SELECTED);
          StyleCtrl->EnsureVisible(pos);
        }
    }
// fifth row: Filling Graphics
  wxBoxSizer *fillGraphicsBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(fillGraphicsBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *fillGrBox = new wxStaticBox(this, wxID_STATIC,
                                           wxT("Interior filling graphics"),
                                           wxDefaultPosition,
                                           wxDefaultSize);
  wxBoxSizer *fillGrGroupSizer = new wxStaticBoxSizer(fillGrBox, wxVERTICAL);
  fillGraphicsBoxSizer->Add(fillGrGroupSizer, 0,
                            wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *fillPatternSizer = new wxBoxSizer(wxHORIZONTAL);
  fillGrGroupSizer->Add(fillPatternSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  PatternsCtrl =
    new wxListCtrl(this, ID_POLYGON_PATTERNS, wxDefaultPosition,
                   wxSize(400, 100), wxLC_ICON | wxLC_SINGLE_SEL);
  fillPatternSizer->Add(PatternsCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  PatternsCtrl->AssignImageList(PatternsList.BuildList(), wxIMAGE_LIST_NORMAL);
  for (i = 0;
       i < PatternsCtrl->GetImageList(wxIMAGE_LIST_NORMAL)->GetImageCount();
       i++)
    PatternsCtrl->InsertItem(i, i);
  if (CurrentPattern)
    {
      // selecting the current item
      PatternsCtrl->SetItemState(CurrentPattern->GetListId(),
                                 wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
      PatternsCtrl->EnsureVisible(CurrentPattern->GetListId());
    }
  wxBoxSizer *fillColorSizer = new wxBoxSizer(wxHORIZONTAL);
  fillGrGroupSizer->Add(fillColorSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                        0);
  wxBitmap fillBmp;
  GetButtonBitmap(CurrentFillColor, fillBmp);
  FillColorCtrl = new wxBitmapButton(this, ID_POLYGON_FILL_COLOR, fillBmp);
  FillColorCtrl->SetBitmapDisabled(disabledBmp);
  fillColorSizer->Add(FillColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxStaticText *fillAlphaLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Transparency:"));
  fillColorSizer->Add(fillAlphaLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  FillAlphaCtrl =
    new wxSlider(this, ID_POLYGON_FILL_ALPHA, CurrentFillColor.Alpha(), 0, 255,
                 wxDefaultPosition, wxSize(75, 20),
                 wxSL_HORIZONTAL | wxSL_INVERSE);
  fillColorSizer->Add(FillAlphaCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  if (FillingModeCtrl->GetSelection() == 0)
    {
      PatternsCtrl->Enable(false);
      FillColorCtrl->Enable(false);
      FillAlphaCtrl->Enable(false);
  } else if (FillingModeCtrl->GetSelection() == 1)
    {
      PatternsCtrl->Enable(false);
  } else if (FillingModeCtrl->GetSelection() == 2)
    {
      FillAlphaCtrl->Enable(false);
    }
  // sixth row: Example
  wxBoxSizer *exampleBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(exampleBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *exampleBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Example"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *exampleSizer = new wxStaticBoxSizer(exampleBox, wxHORIZONTAL);
  exampleBoxSizer->Add(exampleSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  PaintBitmap();
  ExampleCtrl =
    new wxStaticBitmap(this, ID_POLYGON_EXAMPLE, Bitmap, wxDefaultPosition,
                       wxSize(Bitmap.GetWidth(), Bitmap.GetHeight()),
                       wxBORDER_SUNKEN);
  exampleSizer->Add(ExampleCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PolygonGraphicsDialog::OnOk);
  Connect(ID_POLYGON_BORDER_MODE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & PolygonGraphicsDialog::OnBorderModeChanged);
  Connect(ID_POLYGON_FILL_MODE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) &
          PolygonGraphicsDialog::OnFillingModeChanged);
  Connect(ID_POLYGON_BORDER_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PolygonGraphicsDialog::OnBorderColor);
  Connect(ID_POLYGON_BORDER_ALPHA, wxEVT_SCROLL_THUMBRELEASE,
          (wxObjectEventFunction) &
          PolygonGraphicsDialog::OnBorderAlphaChanged);
  Connect(ID_POLYGON_BORDER_ALPHA, wxEVT_SCROLL_CHANGED,
          (wxObjectEventFunction) &
          PolygonGraphicsDialog::OnBorderAlphaChanged);
  Connect(ID_POLYGON_BORDER_THICKNESS, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) &
          PolygonGraphicsDialog::OnBorderThicknessChanged);
  Connect(ID_POLYGON_BORDER_STYLE, wxEVT_COMMAND_LIST_ITEM_SELECTED,
          (wxObjectEventFunction) &
          PolygonGraphicsDialog::OnBorderStyleSelected);
  Connect(ID_POLYGON_FILL_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PolygonGraphicsDialog::OnFillColor);
  Connect(ID_POLYGON_FILL_ALPHA, wxEVT_SCROLL_THUMBRELEASE,
          (wxObjectEventFunction) & PolygonGraphicsDialog::OnFillAlphaChanged);
  Connect(ID_POLYGON_FILL_ALPHA, wxEVT_SCROLL_CHANGED,
          (wxObjectEventFunction) & PolygonGraphicsDialog::OnFillAlphaChanged);
  Connect(ID_POLYGON_PATTERNS, wxEVT_COMMAND_LIST_ITEM_SELECTED,
          (wxObjectEventFunction) & PolygonGraphicsDialog::OnPatternSelected);
}

void PolygonGraphicsDialog::GetButtonBitmap(wxColour & color, wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(color));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

void PolygonGraphicsDialog::GetDisabledButtonBitmap(wxBitmap & bmp)
{
// creating the disabled Bitmap
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

wxImageList *PolygonGraphicsDialog::BuildStyleList()
{
// building the style's images
  wxBitmap img1(32, 8);
  wxBitmap img2(32, 8);
  wxBitmap img3(32, 8);
  wxBitmap img4(32, 8);
  wxBitmap img5(32, 8);
  wxColour color(255, 255, 255);
  wxBrush background(wxColour(204, 204, 204));
  wxColour foreground(0, 0, 0);
  wxImageList *list = new wxImageList(32, 8, true, 5);
  wxMemoryDC *dc = new wxMemoryDC(img1);
// wxSOLID example
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img1.GetWidth() + 2, img1.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxSOLID));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img1, color);
// wxDOT example
  dc = new wxMemoryDC(img2);
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img2.GetWidth() + 2, img2.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxDOT));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img2, color);
// wxLONG_DASH example
  dc = new wxMemoryDC(img3);
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img3.GetWidth() + 2, img3.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxLONG_DASH));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img3, color);
// wxSHORT_DASH example
  dc = new wxMemoryDC(img4);
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img4.GetWidth() + 2, img4.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxSHORT_DASH));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img4, color);
// wxDOT_DASH example
  dc = new wxMemoryDC(img5);
  dc->SetBrush(background);
  dc->DrawRectangle(-1, -1, img5.GetWidth() + 2, img5.GetHeight() + 2);
  dc->SetPen(wxPen(foreground, 4, wxDOT_DASH));
  dc->DrawLine(0, 4, 128, 4);
  dc->SetBrush(wxNullBrush);
  dc->SetPen(wxNullPen);
  delete dc;
  list->Add(img5, color);

  return list;
}

int PolygonGraphicsDialog::Find()
{
// return the position corresponding to the current style
  if (CurrentBorderStyle == wxSOLID)
    return 0;
  if (CurrentBorderStyle == wxDOT)
    return 1;
  if (CurrentBorderStyle == wxLONG_DASH)
    return 2;
  if (CurrentBorderStyle == wxSHORT_DASH)
    return 3;
  if (CurrentBorderStyle == wxDOT_DASH)
    return 4;
// otherwyse we have some odd style
  CurrentBorderStyle = wxSOLID;
  return 0;
}

int PolygonGraphicsDialog::Find(int pos)
{
// return the wxXXX constant corresponding to the currently selected style
  if (pos == 0)
    return wxSOLID;
  if (pos == 1)
    return wxDOT;
  if (pos == 2)
    return wxLONG_DASH;
  if (pos == 3)
    return wxSHORT_DASH;
  if (pos == 4)
    return wxDOT_DASH;
// otherwyse we have some odd style
  return wxSOLID;
}

void PolygonGraphicsDialog::PaintBitmap()
{
// painting the Example Bitmap
  wxBrush checkedBrush;
  int tick = Bitmap.GetWidth() / 6;
  int hi1 = 12;
  int hi2 = (Bitmap.GetHeight() / 3);
  int lo1 = Bitmap.GetHeight() - 12;
  int lo2 = Bitmap.GetHeight() - (Bitmap.GetHeight() / 3);
  checkedBrush.SetStipple(wxBitmap(checked_brush_xpm));
  checkedBrush.SetStyle(wxSTIPPLE);
  wxMemoryDC *dc = new wxMemoryDC(Bitmap);
  wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
// background initialization
  gr->SetBrush(checkedBrush);
  gr->DrawRectangle(0, 0, Bitmap.GetWidth(), Bitmap.GetHeight());
// drawing the polygon
  wxGraphicsPath path = gr->CreatePath();
  path.MoveToPoint(12, 12);
  path.AddLineToPoint(12, lo2);
  path.AddLineToPoint(tick, lo1);
  path.AddLineToPoint((tick * 2), lo2);
  path.AddLineToPoint((tick * 3), lo1);
  path.AddLineToPoint((tick * 4), lo2);
  path.AddLineToPoint((tick * 5), lo1);
  path.AddLineToPoint(Bitmap.GetWidth() - 12, lo2);
  path.AddLineToPoint(Bitmap.GetWidth() - 12, hi1);
  path.AddLineToPoint((tick * 5), hi2);
  path.AddLineToPoint((tick * 4), hi1);
  path.AddLineToPoint((tick * 3), hi2);
  path.AddLineToPoint((tick * 2), hi1);
  path.AddLineToPoint(tick, hi2);
  path.AddLineToPoint(12, 12);

  if (CurrentToFill == true)
    {
      if (CurrentSolidFilling == true)
        {
          gr->SetBrush(wxBrush(CurrentFillColor));
          gr->FillPath(path);
      } else
        {
          if (CurrentPattern)
            {
              wxBitmap bmp;
              CurrentPattern->GetBitmap(bmp, CurrentFillColor);
              wxMask *mask = new wxMask(CurrentPattern->GetMask());
              bmp.SetMask(mask);

              wxBrush brush(bmp);
              gr->SetBrush(brush);
              gr->FillPath(path);
            }
        }
    }
  if (CurrentDrawBorder == true)
    {
      gr->SetPen(wxPen
                 (CurrentBorderColor, CurrentBorderThickness,
                  CurrentBorderStyle));
      gr->StrokePath(path);
    }

  delete gr;
  delete dc;
}

void PolygonGraphicsDialog::OnBorderColor(wxCommandEvent & WXUNUSED(event))
{
// border color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(CurrentBorderColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      wxColour color = colorData.GetColour();
      CurrentBorderColor =
        wxColour(color.Red(), color.Green(), color.Blue(),
                 CurrentBorderColor.Alpha());
      PaintBitmap();
      ExampleCtrl->SetBitmap(Bitmap);
      wxBitmap bmp;
      GetButtonBitmap(CurrentBorderColor, bmp);
      BorderColorCtrl->SetBitmapLabel(bmp);
    }
}

void PolygonGraphicsDialog::
OnBorderAlphaChanged(wxCommandEvent & WXUNUSED(event))
{
//
// border ALPHA selection changed
//
  CurrentBorderColor =
    wxColour(CurrentBorderColor.Red(), CurrentBorderColor.Green(),
             CurrentBorderColor.Blue(), BorderAlphaCtrl->GetValue());
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void PolygonGraphicsDialog::
OnBorderThicknessChanged(wxCommandEvent & WXUNUSED(event))
{
//
// border THICKNESS selection changed
//
  CurrentBorderThickness = ThicknessCtrl->GetValue();
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void PolygonGraphicsDialog::OnFillColor(wxCommandEvent & WXUNUSED(event))
{
// inerior filling color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(CurrentFillColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      wxColour color = colorData.GetColour();
      CurrentFillColor =
        wxColour(color.Red(), color.Green(), color.Blue(),
                 CurrentFillColor.Alpha());
      PaintBitmap();
      ExampleCtrl->SetBitmap(Bitmap);
      wxBitmap bmp;
      GetButtonBitmap(CurrentFillColor, bmp);
      FillColorCtrl->SetBitmapLabel(bmp);
    }
}

void PolygonGraphicsDialog::OnFillAlphaChanged(wxCommandEvent & WXUNUSED(event))
{
//
// interior filling ALPHA selection changed
//
  CurrentFillColor =
    wxColour(CurrentFillColor.Red(), CurrentFillColor.Green(),
             CurrentFillColor.Blue(), FillAlphaCtrl->GetValue());
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void PolygonGraphicsDialog::
OnBorderStyleSelected(wxCommandEvent & WXUNUSED(event))
{
// border style selection changed
  int item = -1;
  for (;;)
    {
      item =
        StyleCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
      if (item == -1)
        break;
      CurrentBorderStyle = Find(item);
    }
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void PolygonGraphicsDialog::
OnBorderModeChanged(wxCommandEvent & WXUNUSED(event))
{
// border mode radiobox changed
  if (BorderModeCtrl->GetSelection() == 0)
    {
      CurrentDrawBorder = true;
      BorderColorCtrl->Enable(true);
      BorderAlphaCtrl->Enable(true);
      BorderAlphaCtrl->SetValue(CurrentBorderColor.Alpha());
      ThicknessCtrl->Enable(true);
      StyleCtrl->Enable(true);
  } else
    {
      CurrentDrawBorder = false;
      BorderColorCtrl->Enable(false);
      BorderAlphaCtrl->SetValue(255);
      BorderAlphaCtrl->Enable(false);
      ThicknessCtrl->Enable(false);
      StyleCtrl->Enable(false);
    }
  if (BorderModeCtrl->GetSelection() == 1
      && FillingModeCtrl->GetSelection() == 0)
    {
      // if there is no border, we must have interior filling set
      CurrentToFill = true;
      CurrentSolidFilling = true;
      FillingModeCtrl->SetSelection(1);
      FillColorCtrl->Enable(true);
      FillAlphaCtrl->Enable(true);
      FillAlphaCtrl->SetValue(CurrentFillColor.Alpha());
    }
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void PolygonGraphicsDialog::
OnFillingModeChanged(wxCommandEvent & WXUNUSED(event))
{
// interior fill mode radiobox changed
  if (FillingModeCtrl->GetSelection() == 0)
    {
      CurrentToFill = false;
      PatternsCtrl->Enable(false);
      FillColorCtrl->Enable(false);
      FillAlphaCtrl->Enable(false);
      FillAlphaCtrl->SetValue(255);
  } else if (FillingModeCtrl->GetSelection() == 1)
    {
      CurrentToFill = true;
      CurrentSolidFilling = true;
      PatternsCtrl->Enable(false);
      FillColorCtrl->Enable(true);
      FillAlphaCtrl->Enable(true);
      FillAlphaCtrl->SetValue(CurrentFillColor.Alpha());
  } else
    {
      CurrentToFill = true;
      CurrentSolidFilling = false;
      PatternsCtrl->Enable(true);
      FillColorCtrl->Enable(true);
      FillAlphaCtrl->Enable(false);
      FillAlphaCtrl->SetValue(255);
      if (CurrentPattern)
        {
          if (CurrentPattern->IsFullColor() == true)
            {
              FillColorCtrl->Enable(false);
              FillAlphaCtrl->Enable(false);
              FillAlphaCtrl->SetValue(255);
            }
      } else
        {
          FillColorCtrl->Enable(false);
          FillAlphaCtrl->Enable(false);
          FillAlphaCtrl->SetValue(255);
        }
    }
  if (BorderModeCtrl->GetSelection() == 1
      && FillingModeCtrl->GetSelection() == 0)
    {
      // if there is no interior filling, we must have border set
      CurrentDrawBorder = true;
      BorderModeCtrl->SetSelection(0);
      BorderColorCtrl->Enable(true);
      BorderAlphaCtrl->Enable(true);
      BorderAlphaCtrl->SetValue(CurrentBorderColor.Alpha());
      ThicknessCtrl->Enable(true);
      StyleCtrl->Enable(true);
    }
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void PolygonGraphicsDialog::OnPatternSelected(wxCommandEvent & WXUNUSED(event))
{
// pattern selection changed
  int item = -1;
  for (;;)
    {
      item =
        PatternsCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
      if (item == -1)
        break;
      CurrentPattern = PatternsList.FindByPos(item);
    }
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
  if (CurrentPattern)
    {
      if (CurrentPattern->IsFullColor() == false)
        {
          FillColorCtrl->Enable(true);
          FillColorCtrl->Enable(true);
      } else
        {
          FillColorCtrl->Enable(false);
          FillColorCtrl->Enable(false);
        }
  } else
    {
      FillColorCtrl->Enable(false);
      FillColorCtrl->Enable(false);
    }
}

void PolygonGraphicsDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  if (BorderModeCtrl->GetSelection() == 0)
    DrawBorder = true;
  else
    DrawBorder = false;
  if (FillingModeCtrl->GetSelection() == 0)
    ToFill = false;
  else
    {
      ToFill = true;
      if (FillingModeCtrl->GetSelection() == 1)
        SolidFilling = true;
      else
        SolidFilling = false;
    }
  BorderColor = CurrentBorderColor;
  BorderThickness = CurrentBorderThickness;
  BorderStyle = CurrentBorderStyle;
  if (CurrentPattern)
    {
      PatternId = CurrentPattern->GetId();
      ColorPattern = CurrentPattern->IsFullColor();
    }
  FillColor = CurrentFillColor;
  DescName = DescCtrl->GetValue();
  wxDialog::EndModal(wxID_OK);
}

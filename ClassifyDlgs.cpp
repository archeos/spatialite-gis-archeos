/*
/ ClassifyDlgs.cpp
/ various dialog classes [layer classify]
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
#include "wx/imaglist.h"

#include "Classdef.h"

SubClassesPreview::SubClassesPreview(wxDialog * parent, wxWindowID id, int geomType, double min, double max):wxTreeCtrl(parent, id, wxDefaultPosition,
           wxSize(250, 150),
           wxTR_NO_BUTTONS)
{
//
// constructor: TREE control to manage Layer SubClasses
//
  PointParent = NULL;
  LineParent = NULL;
  PolygonParent = NULL;
  CurrentItem = wxTreeItemId();
  GeometryType = geomType;
  MinValue = min;
  MaxValue = max;
// setting up event handlers 
  Connect(wxID_ANY, wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK,
          (wxObjectEventFunction) & SubClassesPreview::OnRightClick);
  Connect(ID_CLASSES_CMD_SYMBOL, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & SubClassesPreview::OnCmdEditSymbol);
  Connect(ID_CLASSES_CMD_SIZE, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & SubClassesPreview::OnCmdEditSize);
  Connect(ID_CLASSES_CMD_RANGE, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & SubClassesPreview::OnCmdEditRange);
  Connect(ID_CLASSES_CMD_COLOR, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & SubClassesPreview::OnCmdEditColor);
}

void SubClassesPreview::OnRightClick(wxTreeEvent & event)
{
//
// right click on some node [mouse action]
//
  wxMenuItem *menuItem;
  wxMenu *menu = new wxMenu;
  wxTreeItemId item = event.GetItem();
  SelectItem(item);
  wxPoint pt = event.GetPoint();
  SubClassObject *obj = (SubClassObject *) GetItemData(item);
  if (obj == NULL)
    return;
  CurrentItem = item;
  if (GeometryType == LAYER_POINT)
    {
      menuItem =
        new wxMenuItem(menu, ID_CLASSES_CMD_SYMBOL, wxT("&Modify Symbol Type"));
      menu->Append(menuItem);
    }
  if (GeometryType == LAYER_POINT || GeometryType == LAYER_LINESTRING)
    {
      menuItem = new wxMenuItem(menu, ID_CLASSES_CMD_SIZE, wxT("&Modify Size"));
      menu->Append(menuItem);
    }
  if (obj->IsUnique() == false)
    {
      menuItem =
        new wxMenuItem(menu, ID_CLASSES_CMD_RANGE, wxT("&Modify Range Values"));
      menu->Append(menuItem);
    }
  menuItem = new wxMenuItem(menu, ID_CLASSES_CMD_COLOR, wxT("&Modify Color"));
  menu->Append(menuItem);
  PopupMenu(menu, pt);
  return;
}

void SubClassesPreview::OnCmdEditRange(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the range values
//
  SubClassObject *obj = (SubClassObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  SubClassRangeDialog dlg;
  wxDialog *parent = NULL;
  wxString tableName;
  wxString geometryColumn;
  wxString descName;
  wxString classifyColumn;
  if (GeometryType == LAYER_POINT)
    {
      parent = PointParent;
      tableName = PointParent->GetTableName();
      geometryColumn = PointParent->GetGeometryColumn();
      descName = PointParent->GetDescName();
      classifyColumn = PointParent->GetClassifyColumn();
    }
  if (GeometryType == LAYER_LINESTRING)
    {
      parent = LineParent;
      tableName = LineParent->GetTableName();
      geometryColumn = LineParent->GetGeometryColumn();
      descName = LineParent->GetDescName();
      classifyColumn = LineParent->GetClassifyColumn();
    }
  if (GeometryType == LAYER_POLYGON)
    {
      parent = PolygonParent;
      tableName = PolygonParent->GetTableName();
      geometryColumn = PolygonParent->GetGeometryColumn();
      descName = PolygonParent->GetDescName();
      classifyColumn = PolygonParent->GetClassifyColumn();
    }
  dlg.Create(parent, tableName, geometryColumn, descName, classifyColumn,
             GetItemText(CurrentItem), obj->GetMinValue(), obj->GetMaxValue(),
             MinValue, MaxValue);
  int ret = dlg.ShowModal();
  if (ret == wxID_OK)
    {
      double min = dlg.GetMinValue();
      double max = dlg.GetMaxValue();
      if (min < MinValue)
        min = MinValue;
      if (max > MaxValue)
        max = MaxValue;
      obj->SetRange(min, max);
      SetItemText(CurrentItem, obj->GetValueAsString());
    }
}

void SubClassesPreview::OnCmdEditSymbol(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the Symbol Type
//
  SubClassObject *obj = (SubClassObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  SubClassSymbolTypeDialog dlg;
  wxDialog *parent = NULL;
  wxString tableName;
  wxString geometryColumn;
  wxString descName;
  wxString classifyColumn;
  parent = PointParent;
  tableName = PointParent->GetTableName();
  geometryColumn = PointParent->GetGeometryColumn();
  descName = PointParent->GetDescName();
  classifyColumn = PointParent->GetClassifyColumn();
  dlg.Create(parent, tableName, geometryColumn, descName, classifyColumn,
             GetItemText(CurrentItem), obj->GetSymbolType());
  int ret = dlg.ShowModal();
  if (ret == wxID_OK)
    {
      obj->SetSymbolType(dlg.GetSymbolType());
      SetItemImage(CurrentItem, -1);
      obj->UpdateSubClassIcon(GetImageList(), 32, 16, LAYER_POINT);
      SetItemImage(CurrentItem, obj->GetIconIndex());
    }
}

void SubClassesPreview::OnCmdEditSize(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the Size
//
  SubClassObject *obj = (SubClassObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  SubClassSizeDialog dlg;
  wxDialog *parent = NULL;
  wxString tableName;
  wxString geometryColumn;
  wxString descName;
  wxString classifyColumn;
  if (GeometryType == LAYER_POINT)
    {
      parent = PointParent;
      tableName = PointParent->GetTableName();
      geometryColumn = PointParent->GetGeometryColumn();
      descName = PointParent->GetDescName();
      classifyColumn = PointParent->GetClassifyColumn();
    }
  if (GeometryType == LAYER_LINESTRING)
    {
      parent = LineParent;
      tableName = LineParent->GetTableName();
      geometryColumn = LineParent->GetGeometryColumn();
      descName = LineParent->GetDescName();
      classifyColumn = LineParent->GetClassifyColumn();
    }
  if (GeometryType == LAYER_POLYGON)
    {
      parent = PolygonParent;
      tableName = PolygonParent->GetTableName();
      geometryColumn = PolygonParent->GetGeometryColumn();
      descName = PolygonParent->GetDescName();
      classifyColumn = PolygonParent->GetClassifyColumn();
    }
  dlg.Create(parent, tableName, geometryColumn, descName, classifyColumn,
             GetItemText(CurrentItem), obj->GetSize());
  int ret = dlg.ShowModal();
  if (ret == wxID_OK)
    {
      obj->SetSize(dlg.GetSize());
      SetItemImage(CurrentItem, -1);
      if (GeometryType == LAYER_POINT)
        obj->UpdateSubClassIcon(GetImageList(), 32, 16, LAYER_POINT);
      if (GeometryType == LAYER_LINESTRING)
        obj->UpdateSubClassIcon(GetImageList(), 32, 16, LAYER_LINESTRING);
      if (GeometryType == LAYER_POLYGON)
        obj->UpdateSubClassIcon(GetImageList(), 32, 16, LAYER_POLYGON);
      SetItemImage(CurrentItem, obj->GetIconIndex());
    }
}

void SubClassesPreview::OnCmdEditColor(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the color
//
  SubClassObject *obj = (SubClassObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  SubClassColorDialog dlg;
  wxDialog *parent = NULL;
  wxString tableName;
  wxString geometryColumn;
  wxString descName;
  wxString classifyColumn;
  if (GeometryType == LAYER_POINT)
    {
      parent = PointParent;
      tableName = PointParent->GetTableName();
      geometryColumn = PointParent->GetGeometryColumn();
      descName = PointParent->GetDescName();
      classifyColumn = PointParent->GetClassifyColumn();
    }
  if (GeometryType == LAYER_LINESTRING)
    {
      parent = LineParent;
      tableName = LineParent->GetTableName();
      geometryColumn = LineParent->GetGeometryColumn();
      descName = LineParent->GetDescName();
      classifyColumn = LineParent->GetClassifyColumn();
    }
  if (GeometryType == LAYER_POLYGON)
    {
      parent = PolygonParent;
      tableName = PolygonParent->GetTableName();
      geometryColumn = PolygonParent->GetGeometryColumn();
      descName = PolygonParent->GetDescName();
      classifyColumn = PolygonParent->GetClassifyColumn();
    }
  bool skipEnabled = false;
  if (obj->IsUnique() == true)
    skipEnabled = true;
  dlg.Create(parent, tableName, geometryColumn, descName, classifyColumn,
             GetItemText(CurrentItem), obj->GetColor(), obj->IsRandomizeSkip(),
             skipEnabled);
  int ret = dlg.ShowModal();
  if (ret == wxID_OK)
    {
      obj->SetColor(dlg.GetColor());
      obj->SetRandomizeSkip(dlg.IsRandomizeSkip());
      SetItemImage(CurrentItem, -1);
      if (GeometryType == LAYER_POINT)
        obj->UpdateSubClassIcon(GetImageList(), 32, 16, LAYER_POINT);
      if (GeometryType == LAYER_LINESTRING)
        obj->UpdateSubClassIcon(GetImageList(), 32, 16, LAYER_LINESTRING);
      if (GeometryType == LAYER_POLYGON)
        obj->UpdateSubClassIcon(GetImageList(), 32, 16, LAYER_POLYGON);
      SetItemImage(CurrentItem, obj->GetIconIndex());
    }
}

bool SubClassSymbolTypeDialog::Create(wxDialog * parent, wxString & table,
                                      wxString & geom, wxString & descName,
                                      wxString & column, wxString classText,
                                      int symbolType)
{
//
// creating the dialog
//
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  ClassifyColumn = column;
  ClassText = classText;
  SymbolType = symbolType;

  if (wxDialog::Create(parent, wxID_ANY, wxT("Manual Symbol Type Selection")) ==
      false)
    return false;
// populates individual controls
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void SubClassSymbolTypeDialog::CreateControls()
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
  wxTextCtrl *descCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                                        wxDefaultPosition,
                                        wxSize(350, 22), wxTE_READONLY);
  descSizer->Add(descCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: Classify Column
  wxBoxSizer *columnSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(columnSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *columnLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column:"));
  columnSizer->Add(columnLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *columnCtrl = new wxTextCtrl(this, wxID_STATIC, ClassifyColumn,
                                          wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  columnSizer->Add(columnCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fourth row:  ClassText
  wxBoxSizer *classSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(classSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *classLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Sub-Class:"));
  classSizer->Add(classLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *classCtrl = new wxTextCtrl(this, wxID_STATIC, ClassText,
                                         wxDefaultPosition,
                                         wxSize(350, 22), wxTE_READONLY);
  classSizer->Add(classCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fifth row: Symbol Type value
  wxBoxSizer *symbolSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(symbolSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxString symbols[3];
  symbols[0] = wxT("&Circle");
  symbols[1] = wxT("&Square");
  symbols[2] = wxT("Diamond");
  SymbolTypeCtrl = new wxRadioBox(this, ID_CLASSES_SYMBOL,
                                  wxT("&Symbol Type"), wxDefaultPosition,
                                  wxDefaultSize, 3, symbols, 3,
                                  wxRA_SPECIFY_COLS);
  if (SymbolType == CLASSES_SYMBOL_SQUARE)
    SymbolTypeCtrl->SetSelection(1);
  else if (SymbolType == CLASSES_SYMBOL_DIAMOND)
    SymbolTypeCtrl->SetSelection(2);
  else
    SymbolTypeCtrl->SetSelection(0);
  symbolSizer->Add(SymbolTypeCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & SubClassSymbolTypeDialog::OnOk);
}

void SubClassSymbolTypeDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  if (SymbolTypeCtrl->GetSelection() == 1)
    SymbolType = CLASSES_SYMBOL_SQUARE;
  else if (SymbolTypeCtrl->GetSelection() == 2)
    SymbolType = CLASSES_SYMBOL_DIAMOND;
  else
    SymbolType = CLASSES_SYMBOL_CIRCLE;
  wxDialog::EndModal(wxID_OK);
}

bool SubClassSizeDialog::Create(wxDialog * parent, wxString & table,
                                wxString & geom, wxString & descName,
                                wxString & column, wxString classText, int size)
{
//
// creating the dialog
//
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  ClassifyColumn = column;
  ClassText = classText;
  Size = size;

  if (wxDialog::Create(parent, wxID_ANY, wxT("Manual Size Selection")) == false)
    return false;
// populates individual controls
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void SubClassSizeDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[128];
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
  wxTextCtrl *descCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                                        wxDefaultPosition,
                                        wxSize(350, 22), wxTE_READONLY);
  descSizer->Add(descCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: Classify Column
  wxBoxSizer *columnSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(columnSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *columnLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column:"));
  columnSizer->Add(columnLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *columnCtrl = new wxTextCtrl(this, wxID_STATIC, ClassifyColumn,
                                          wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  columnSizer->Add(columnCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fourth row:  ClassText
  wxBoxSizer *classSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(classSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *classLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Sub-Class:"));
  classSizer->Add(classLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *classCtrl = new wxTextCtrl(this, wxID_STATIC, ClassText,
                                         wxDefaultPosition,
                                         wxSize(350, 22), wxTE_READONLY);
  classSizer->Add(classCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fifth row: Size value
  wxStaticBox *sizeBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Size"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *szSizer = new wxStaticBoxSizer(sizeBox, wxVERTICAL);
  boxSizer->Add(szSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *size1Sizer = new wxBoxSizer(wxHORIZONTAL);
  szSizer->Add(size1Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *sizeLabel = new wxStaticText(this, wxID_STATIC, wxT("&Size:"));
  size1Sizer->Add(sizeLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", Size);
  wxString sz = wxString::FromUTF8(dummy);
  SizeCtrl =
    new wxSpinCtrl(this, ID_CLASSES_SIZE, sz, wxDefaultPosition, wxSize(50, 20),
                   wxSP_ARROW_KEYS, 1, 16, Size);
  size1Sizer->Add(SizeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & SubClassSizeDialog::OnOk);
}

void SubClassSizeDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  Size = SizeCtrl->GetValue();
  wxDialog::EndModal(wxID_OK);
}

bool SubClassColorDialog::Create(wxDialog * parent, wxString & table,
                                 wxString & geom, wxString & descName,
                                 wxString & column, wxString classText,
                                 wxColour & color, bool skip, bool skipEnabled)
{
//
// creating the dialog
//
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  ClassifyColumn = column;
  ClassText = classText;
  Color = color;
  RandomizeSkip = skip;
  SkipEnabled = skipEnabled;

  if (wxDialog::Create(parent, wxID_ANY, wxT("Manual Color Selection")) ==
      false)
    return false;
// populates individual controls
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void SubClassColorDialog::CreateControls()
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
  wxTextCtrl *descCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                                        wxDefaultPosition,
                                        wxSize(350, 22), wxTE_READONLY);
  descSizer->Add(descCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: Classify Column
  wxBoxSizer *columnSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(columnSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *columnLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column:"));
  columnSizer->Add(columnLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *columnCtrl = new wxTextCtrl(this, wxID_STATIC, ClassifyColumn,
                                          wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  columnSizer->Add(columnCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fourth row:  ClassText
  wxBoxSizer *classSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(classSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *classLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Sub-Class:"));
  classSizer->Add(classLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *classCtrl = new wxTextCtrl(this, wxID_STATIC, ClassText,
                                         wxDefaultPosition,
                                         wxSize(350, 22), wxTE_READONLY);
  classSizer->Add(classCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fifth row: Color
  wxBoxSizer *colorSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(colorSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticText *colorLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Color:"));
  colorSizer->Add(colorLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap bmp;
  GetButtonBitmap(Color, bmp);
  ColorCtrl = new wxBitmapButton(this, ID_CLASSES_COLOR, bmp);
  colorSizer->Add(ColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  if (SkipEnabled == true)
    {
      RandomizeSkipCtrl =
        new wxCheckBox(this, ID_CLASSES_RANDOMIZE_SKIP,
                       wxT("Don't randomize this color"), wxDefaultPosition,
                       wxDefaultSize);
      RandomizeSkipCtrl->SetValue(RandomizeSkip);
      colorSizer->Add(RandomizeSkipCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    }
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & SubClassColorDialog::OnOk);
  Connect(ID_CLASSES_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & SubClassColorDialog::OnColor);
}

void SubClassColorDialog::GetButtonBitmap(wxColour & color, wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(color));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

void SubClassColorDialog::OnColor(wxCommandEvent & WXUNUSED(event))
{
// color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(Color);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      Color = colorData.GetColour();
      wxBitmap bmp;
      GetButtonBitmap(Color, bmp);
      ColorCtrl->SetBitmapLabel(bmp);
    }
}

void SubClassColorDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  if (SkipEnabled == true)
    RandomizeSkip = RandomizeSkipCtrl->GetValue();
  else
    RandomizeSkip = false;
  wxDialog::EndModal(wxID_OK);
}

bool SubClassRangeDialog::Create(wxDialog * parent, wxString & table,
                                 wxString & geom, wxString & descName,
                                 wxString & column, wxString classText,
                                 double minValue, double maxValue,
                                 double limitMin, double limitMax)
{
//
// creating the dialog
//
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  ClassifyColumn = column;
  ClassText = classText;
  MinValue = (int) minValue;
  MaxValue = (int) maxValue;
  LimitMin = (int) floor(limitMin);
  LimitMax = (int) ceil(limitMax);

  if (wxDialog::Create(parent, wxID_ANY, wxT("Manual Range Selection")) ==
      false)
    return false;
// populates individual controls
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void SubClassRangeDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[128];
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
  wxTextCtrl *descCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                                        wxDefaultPosition,
                                        wxSize(350, 22), wxTE_READONLY);
  descSizer->Add(descCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: Classify Column
  wxBoxSizer *columnSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(columnSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *columnLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column:"));
  columnSizer->Add(columnLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *columnCtrl = new wxTextCtrl(this, wxID_STATIC, ClassifyColumn,
                                          wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  columnSizer->Add(columnCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fourth row:  ClassText
  wxBoxSizer *classSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(classSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *classLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Sub-Class:"));
  classSizer->Add(classLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *classCtrl = new wxTextCtrl(this, wxID_STATIC, ClassText,
                                         wxDefaultPosition,
                                         wxSize(350, 22), wxTE_READONLY);
  classSizer->Add(classCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fifth row: Range values
  wxStaticBox *rangeBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Range Values"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *rngSizer = new wxStaticBoxSizer(rangeBox, wxVERTICAL);
  boxSizer->Add(rngSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *range1Sizer = new wxBoxSizer(wxHORIZONTAL);
  rngSizer->Add(range1Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *minLabel = new wxStaticText(this, wxID_STATIC, wxT("&Min:"));
  range1Sizer->Add(minLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", MinValue);
  wxString min = wxString::FromUTF8(dummy);
  MinValueCtrl = new wxSpinCtrl(this, ID_CLASSES_MIN_VALUE, min,
                                wxDefaultPosition, wxSize(100, 20),
                                wxSP_ARROW_KEYS, LimitMin, LimitMax, MinValue);
  range1Sizer->Add(MinValueCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxStaticText *maxLabel = new wxStaticText(this, wxID_STATIC, wxT("&Max:"));
  range1Sizer->Add(maxLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", MaxValue);
  wxString max = wxString::FromUTF8(dummy);
  MaxValueCtrl = new wxSpinCtrl(this, ID_CLASSES_MAX_VALUE, max,
                                wxDefaultPosition, wxSize(100, 20),
                                wxSP_ARROW_KEYS, LimitMin, LimitMax, MaxValue);
  range1Sizer->Add(MaxValueCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & SubClassRangeDialog::OnOk);
}

void SubClassRangeDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  MinValue = MinValueCtrl->GetValue();
  MaxValue = MaxValueCtrl->GetValue();
  if (MinValue > MaxValue)
    {
      wxMessageBox(wxT("Invalid Range [mismatching Min/Max]"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  wxDialog::EndModal(wxID_OK);
}

bool PointLayerClassifyDialog::Create(MyFrame * parent, wxString & table,
                                      wxString & geom, wxString & descName,
                                      wxString & column, bool unique,
                                      int numClasses, double minValue,
                                      double maxValue, int symbolType,
                                      int minSize, int maxSize,
                                      wxColour & minColor, wxColour & maxColor,
                                      SubClassesContainer * subClasses)
{
//
// creating the dialog
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  ClassifyColumn = column;
  DistinctList = NULL;
  RangeList = NULL;
  UniqueValue = unique;
  NumClasses = numClasses;
  MinValue = minValue;
  MaxValue = maxValue;
  SymbolType = symbolType;
  SymbolMinSize = minSize;
  SymbolMaxSize = maxSize;
  MinColor = minColor;
  MaxColor = maxColor;
  HueMode = RANDOM_COLOR_ALL;
  TransparencyMode = RANDOM_COLOR_OPAQUE;
  Images = NULL;

  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Classify - POINT")) ==
      false)
    return false;
// populates individual controls
  MainFrame->GetColumnList(TableName, &NumColumns, &ColumnList, GeometryColumn,
                           LAYER_POINT);
  CreateControls();
  if (subClasses->GetCount() > 0)
    PreviewBuild(subClasses);
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

PointLayerClassifyDialog::~PointLayerClassifyDialog()
{
// destructor 
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  if (ColumnList)
    delete[]ColumnList;
  if (Images)
    delete Images;
}

void PointLayerClassifyDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[128];
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
  wxTextCtrl *descCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                                        wxDefaultPosition,
                                        wxSize(350, 22), wxTE_READONLY);
  descSizer->Add(descCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// third row:  Classify column
  wxBoxSizer *classifyBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(classifyBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *classifyBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Classify cryteria"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *classifySizer = new wxStaticBoxSizer(classifyBox, wxVERTICAL);
  classifyBoxSizer->Add(classifySizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *classify2Sizer = new wxBoxSizer(wxHORIZONTAL);
  classifySizer->Add(classify2Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *classifyLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column:"));
  classify2Sizer->Add(classifyLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  ColumnCtrl =
    new wxComboBox(this, ID_CLASSES_COLUMN, wxT(""), wxDefaultPosition,
                   wxDefaultSize, NumColumns, ColumnList,
                   wxCB_DROPDOWN | wxCB_READONLY);
  classify2Sizer->Add(ColumnCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  int sel = 0;
  int i;
  for (i = 1; i < NumColumns; i++)
    {
      if (ColumnList[i] == ClassifyColumn)
        sel = i;
    }
  ColumnCtrl->SetSelection(sel);
  wxString modes[2];
  modes[0] = wxT("&Distinct values");
  modes[1] = wxT("&Range of values");
  ModeCtrl =
    new wxRadioBox(this, ID_CLASSES_MODE, wxT("&Mode"), wxDefaultPosition,
                   wxDefaultSize, 2, modes, 2, wxRA_SPECIFY_ROWS);
  if (UniqueValue == true)
    ModeCtrl->SetSelection(0);
  else
    ModeCtrl->SetSelection(1);
  classify2Sizer->Add(ModeCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  wxStaticText *numLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Classes:"));
  classify2Sizer->Add(numLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  sprintf(dummy, "%d", NumClasses);
  wxString num = wxString::FromUTF8(dummy);
  ClassesCtrl =
    new wxSpinCtrl(this, ID_CLASSES_NUM, num, wxDefaultPosition, wxSize(50, 20),
                   wxSP_ARROW_KEYS, 2, 32, NumClasses);
  classify2Sizer->Add(ClassesCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);

// fourth row: graphics and test example
  wxBoxSizer *grSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(grSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxBoxSizer *testSizer = new wxBoxSizer(wxVERTICAL);
  grSizer->Add(testSizer, 0, wxALIGN_LEFT | wxALL, 0);

  wxStaticBox *testBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Preview"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *tstSizer = new wxStaticBoxSizer(testBox, wxVERTICAL);
  testSizer->Add(tstSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *tst2Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst2Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  PreviewCtrl = new SubClassesPreview(this, ID_CLASSES_PREVIEW, LAYER_POINT);
  PreviewCtrl->SetPointParent(this);
  tst2Sizer->Add(PreviewCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  wxBoxSizer *tst3Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst3Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  DisplayCtrl = new wxTextCtrl(this, ID_CLASSES_DISPLAY,
                               wxT(""), wxDefaultPosition, wxSize(250, 44),
                               wxTE_RICH | wxTE_MULTILINE | wxTE_READONLY);
  tst3Sizer->Add(DisplayCtrl, 0, wxALIGN_LEFT | wxALL, 1);

  wxBoxSizer *hueSizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(hueSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString hueOptions[4];
  hueOptions[0] = wxT("Any");
  hueOptions[1] = wxT("Sature");
  hueOptions[2] = wxT("Medium");
  hueOptions[3] = wxT("Light");
  HueCtrl = new wxRadioBox(this, ID_CLASSES_HUE,
                           wxT("Random Color Hue"),
                           wxDefaultPosition, wxDefaultSize, 4, hueOptions, 4,
                           wxRA_SPECIFY_COLS);
  HueCtrl->SetSelection(0);
  hueSizer->Add(HueCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  wxBoxSizer *transpSizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(transpSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString transpOptions[4];
  transpOptions[0] = wxT("Opaque");
  transpOptions[1] = wxT("Medium");
  transpOptions[2] = wxT("Light");
  TransparencyCtrl = new wxRadioBox(this, ID_CLASSES_TRANSPARENCY,
                                    wxT("Random Color Transparency"),
                                    wxDefaultPosition, wxDefaultSize, 3,
                                    transpOptions, 3, wxRA_SPECIFY_COLS);
  TransparencyCtrl->SetSelection(0);
  transpSizer->Add(TransparencyCtrl, 0, wxALIGN_RIGHT | wxALL, 1);

  wxBoxSizer *tst4Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst4Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  RebuildCtrl =
    new wxButton(this, ID_CLASSES_REBUILD, wxT("&Reset/Reinitialize"));
  tst4Sizer->Add(RebuildCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  RandomizeCtrl =
    new wxButton(this, ID_CLASSES_RANDOMIZE, wxT("&Randomize Colors"));
  tst4Sizer->Add(RandomizeCtrl, 0, wxALIGN_RIGHT | wxALL, 1);

  wxBoxSizer *graphicsSizer = new wxBoxSizer(wxVERTICAL);
  grSizer->Add(graphicsSizer, 0, wxALIGN_RIGHT | wxALL, 0);

  wxStaticBox *graphicsBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Graphics"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *grphcsSizer = new wxStaticBoxSizer(graphicsBox, wxVERTICAL);
  graphicsSizer->Add(grphcsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *grphcs2Sizer = new wxBoxSizer(wxHORIZONTAL);
  grphcsSizer->Add(grphcs2Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);

  wxString symbols[3];
  symbols[0] = wxT("&Circle");
  symbols[1] = wxT("&Square");
  symbols[2] = wxT("Diamond");
  SymbolTypeCtrl = new wxRadioBox(this, ID_CLASSES_SYMBOL,
                                  wxT("&Symbol Type"), wxDefaultPosition,
                                  wxDefaultSize, 3, symbols, 3,
                                  wxRA_SPECIFY_ROWS);
  if (SymbolType == CLASSES_SYMBOL_SQUARE)
    SymbolTypeCtrl->SetSelection(1);
  else if (SymbolType == CLASSES_SYMBOL_DIAMOND)
    SymbolTypeCtrl->SetSelection(2);
  else
    SymbolTypeCtrl->SetSelection(0);
  grphcs2Sizer->Add(SymbolTypeCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

  wxStaticBox *sizeBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Symbol Size Range"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *szSizer = new wxStaticBoxSizer(sizeBox, wxVERTICAL);
  grphcsSizer->Add(szSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *grphcs3Sizer = new wxBoxSizer(wxHORIZONTAL);
  szSizer->Add(grphcs3Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *minLabel = new wxStaticText(this, wxID_STATIC, wxT("&Min:"));
  grphcs3Sizer->Add(minLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", SymbolMinSize);
  wxString min = wxString::FromUTF8(dummy);
  MinSizeCtrl = new wxSpinCtrl(this, ID_CLASSES_MIN_SIZE, min,
                               wxDefaultPosition, wxSize(50, 20),
                               wxSP_ARROW_KEYS, 1, 16, SymbolMinSize);
  grphcs3Sizer->Add(MinSizeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *grphcs4Sizer = new wxBoxSizer(wxHORIZONTAL);
  szSizer->Add(grphcs4Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *maxLabel = new wxStaticText(this, wxID_STATIC, wxT("&Max:"));
  grphcs4Sizer->Add(maxLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", SymbolMaxSize);
  wxString max = wxString::FromUTF8(dummy);
  MaxSizeCtrl = new wxSpinCtrl(this, ID_CLASSES_MAX_SIZE, max,
                               wxDefaultPosition, wxSize(50, 20),
                               wxSP_ARROW_KEYS, 1, 16, SymbolMaxSize);
  grphcs4Sizer->Add(MaxSizeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxStaticBox *colorBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Color Range"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *colSizer = new wxStaticBoxSizer(colorBox, wxVERTICAL);
  grphcsSizer->Add(colSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *grphcs5Sizer = new wxBoxSizer(wxHORIZONTAL);
  colSizer->Add(grphcs5Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *minColorLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Min:"));
  grphcs5Sizer->Add(minColorLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap disabledBmp;
  GetDisabledButtonBitmap(disabledBmp);
  wxBitmap minBmp;
  GetButtonBitmap(MinColor, minBmp);
  MinColorCtrl = new wxBitmapButton(this, ID_CLASSES_MIN_COLOR, minBmp);
  MinColorCtrl->SetBitmapDisabled(disabledBmp);
  grphcs5Sizer->Add(MinColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *grphcs6Sizer = new wxBoxSizer(wxHORIZONTAL);
  colSizer->Add(grphcs6Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *maxColorLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Max:"));
  grphcs6Sizer->Add(maxColorLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap maxBmp;
  GetButtonBitmap(MaxColor, maxBmp);
  MaxColorCtrl = new wxBitmapButton(this, ID_CLASSES_MAX_COLOR, maxBmp);
  MaxColorCtrl->SetBitmapDisabled(disabledBmp);
  grphcs6Sizer->Add(MaxColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  if (UniqueValue == true)
    {
      ClassesCtrl->Enable(false);
      MaxSizeCtrl->Enable(false);
      MinColorCtrl->Enable(false);
      MaxColorCtrl->Enable(false);
      RandomizeCtrl->Enable(true);
      HueCtrl->Show(true);
      TransparencyCtrl->Show(true);
  } else
    {
      ClassesCtrl->Enable(true);
      MaxSizeCtrl->Enable(true);
      MinColorCtrl->Enable(true);
      MaxColorCtrl->Enable(true);
      RandomizeCtrl->Enable(false);
      HueCtrl->Show(false);
      TransparencyCtrl->Show(false);
    }
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnOk);
  Connect(ID_CLASSES_COLUMN, wxEVT_COMMAND_COMBOBOX_SELECTED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnColumnSelected);
  Connect(ID_CLASSES_MODE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnModeSelected);
  Connect(ID_CLASSES_SYMBOL, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnSymbolSelected);
  Connect(ID_CLASSES_NUM, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) &
          PointLayerClassifyDialog::OnNumClassesChanged);
  Connect(ID_CLASSES_MIN_SIZE, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnMinSizeChanged);
  Connect(ID_CLASSES_MAX_SIZE, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnMaxSizeChanged);
  Connect(ID_CLASSES_MIN_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnMinColor);
  Connect(ID_CLASSES_MAX_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnMaxColor);
  Connect(ID_CLASSES_REBUILD, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnPreviewRefresh);
  Connect(ID_CLASSES_RANDOMIZE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) &
          PointLayerClassifyDialog::OnRandomizeColors);
  Connect(ID_CLASSES_HUE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & PointLayerClassifyDialog::OnHueModeChanged);
  Connect(ID_CLASSES_TRANSPARENCY, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) &
          PointLayerClassifyDialog::OnTransparencyModeChanged);
}

void PointLayerClassifyDialog::
OnHueModeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Random Color Hue selection changed
//
  if (HueCtrl->GetSelection() == 1)
    HueMode = RANDOM_COLOR_SATURE;
  else if (HueCtrl->GetSelection() == 2)
    HueMode = RANDOM_COLOR_MEDIUM;
  else if (HueCtrl->GetSelection() == 3)
    HueMode = RANDOM_COLOR_LIGHT;
  else
    HueMode = RANDOM_COLOR_ALL;
}

void PointLayerClassifyDialog::
OnTransparencyModeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Random Color Transparency selection changed
//
  if (TransparencyCtrl->GetSelection() == 1)
    TransparencyMode = RANDOM_COLOR_MEDIUM_TRANSPARENT;
  else if (TransparencyCtrl->GetSelection() == 2)
    TransparencyMode = RANDOM_COLOR_LIGHT_TRANSPARENT;
  else
    TransparencyMode = RANDOM_COLOR_OPAQUE;
}

void PointLayerClassifyDialog::PreviewBuild(SubClassesContainer * subClasses)
{
//
// populating the SubClasses from received SubClasses
//
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  DistinctList = NULL;
  RangeList = NULL;
  if (ClassifyColumn.Len() == 0)
    return;
  DisplayCtrl->SetValue(wxT(""));
  if (UniqueValue == true)
    {
      // DISTINCT values
      DistinctList = new MyDistinctValueList();
      // generating the preview - DISTINCT values
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      subClasses->BuildDistinctList(DistinctList);
      if (subClasses->HasColors() == false)
        DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_POINT, SymbolType,
                                     SymbolMinSize);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // range of values
      RangeList = new MyRangeValueList();
      // generating the preview - RANGE values
      PreviewCtrl->SetRange(MinValue, MaxValue);
      PreviewCtrl->Show(false);
      subClasses->BuildRangeList(RangeList);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_POINT, SymbolType);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void PointLayerClassifyDialog::PreviewLoad()
{
//
// querying the DB and populating the SubClasses
//
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  DistinctList = NULL;
  RangeList = NULL;
  if (ClassifyColumn.Len() == 0)
    return;

  DisplayCtrl->SetValue(wxT(""));
  if (UniqueValue == true)
    {
      // DISTINCT values
      DistinctList = new MyDistinctValueList();
      bool truncated;
      MainFrame->GetDistinctValues(TableName, ClassifyColumn, DistinctList,
                                   &truncated);
      if (DistinctList->GetType() == CLASSES_INVALID_TYPE)
        {
          wxString msg = wxT("This column doesn't contains valid values\n");
          msg += wxT("Please, select a different Column");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(), wxTextAttr(wxColour(255, 0, 0)));
          delete DistinctList;
          DistinctList = NULL;
          return;
        }
      if (truncated == true)
        {
          wxString msg =
            wxT("The limit for DISTINCT values has been exceded\n");
          msg +=
            wxT
            ("This is an incomplete list [truncated], and only the first 50 values will be shown\n");
          msg += wxT("Any other subsequent value will be then ignored.");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(),
                                wxTextAttr(wxColour(255, 128, 0)));
        }
      // generating the preview - DISTINCT values
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_POINT, SymbolType,
                                     SymbolMinSize);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          obj->SetSymbolType(SymbolType);
          obj->SetSize(SymbolMinSize);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // range of values
      RangeList = new MyRangeValueList();
      double min;
      double max;
      bool invalid;
      MainFrame->GetMaxMinValues(TableName, ClassifyColumn, &min, &max,
                                 &invalid);
      if (invalid == true)
        {
          wxString msg = wxT("This column doesn't contains NUMERIC values\n");
          msg +=
            wxT("Please, select a different Column, or try using DISTINCT");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(), wxTextAttr(wxColour(255, 0, 0)));
          delete RangeList;
          RangeList = NULL;
          return;
        }
      // generating the preview - RANGE values
      PreviewCtrl->SetRange(min, max);
      PreviewCtrl->Show(false);
      RangeList->Build(min, max, NumClasses, SymbolMinSize, SymbolMaxSize,
                       MinColor, MaxColor);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_POINT, SymbolType);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          obj->SetSymbolType(SymbolType);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void PointLayerClassifyDialog::PreviewUpdate()
{
  if (DistinctList == NULL && RangeList == NULL)
    {
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = NULL;
      PreviewCtrl->DeleteAllItems();
      PreviewCtrl->AddRoot(wxT("default"));
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
      DisplayCtrl->SetValue(wxT(""));
      return;
    }
  if (UniqueValue == true)
    {
      // generating the preview - DISTINCT values
      PreviewCtrl->Show(false);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_POINT, SymbolType,
                                     SymbolMinSize);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          obj->SetSymbolType(SymbolType);
          obj->SetSize(SymbolMinSize);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // generating the preview - RANGE values
      PreviewCtrl->Show(false);
      RangeList->Build(PreviewCtrl->GetMinValue(), PreviewCtrl->GetMaxValue(),
                       NumClasses, SymbolMinSize, SymbolMaxSize, MinColor,
                       MaxColor);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_POINT, SymbolType);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          obj->SetSymbolType(SymbolType);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void PointLayerClassifyDialog::GetButtonBitmap(wxColour & color, wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(32, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(color));
  dc->DrawRectangle(-1, -1, 34, 26);
  delete dc;
}

void PointLayerClassifyDialog::GetDisabledButtonBitmap(wxBitmap & bmp)
{
// creating the disabled Bitmap
  bmp = wxBitmap(32, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
  dc->DrawRectangle(-1, -1, 34, 26);
  delete dc;
}

void PointLayerClassifyDialog::
OnColumnSelected(wxCommandEvent & WXUNUSED(event))
{
// column selection
  if (ColumnCtrl->GetSelection() > 0)
    ClassifyColumn = ColumnCtrl->GetStringSelection();
  else
    ClassifyColumn = wxT("");
  PreviewLoad();
}

void PointLayerClassifyDialog::OnModeSelected(wxCommandEvent & WXUNUSED(event))
{
// mode selection
  if (ModeCtrl->GetSelection() == 0)
    UniqueValue = true;
  else
    UniqueValue = false;
  if (UniqueValue == true)
    {
      ClassesCtrl->Enable(false);
      MaxSizeCtrl->Enable(false);
      MinColorCtrl->Enable(false);
      MaxColorCtrl->Enable(false);
      RandomizeCtrl->Enable(true);
      HueCtrl->Show(true);
      TransparencyCtrl->Show(true);
  } else
    {
      ClassesCtrl->Enable(true);
      MaxSizeCtrl->Enable(true);
      MinColorCtrl->Enable(true);
      MaxColorCtrl->Enable(true);
      RandomizeCtrl->Enable(false);
      HueCtrl->Show(false);
      TransparencyCtrl->Show(false);
    }
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
  Centre();
  PreviewLoad();
}

void PointLayerClassifyDialog::
OnSymbolSelected(wxCommandEvent & WXUNUSED(event))
{
// symbol type selection
  if (SymbolTypeCtrl->GetSelection() == 1)
    SymbolType = CLASSES_SYMBOL_SQUARE;
  else if (SymbolTypeCtrl->GetSelection() == 2)
    SymbolType = CLASSES_SYMBOL_DIAMOND;
  else
    SymbolType = CLASSES_SYMBOL_CIRCLE;
  PreviewUpdate();
}

void PointLayerClassifyDialog::
OnNumClassesChanged(wxCommandEvent & WXUNUSED(event))
{
// # classes selection
  NumClasses = ClassesCtrl->GetValue();
  PreviewUpdate();
}

void PointLayerClassifyDialog::
OnMinSizeChanged(wxCommandEvent & WXUNUSED(event))
{
// minimun symbol size selection
  SymbolMinSize = MinSizeCtrl->GetValue();
  PreviewUpdate();
}

void PointLayerClassifyDialog::
OnMaxSizeChanged(wxCommandEvent & WXUNUSED(event))
{
// maximun symbol size selection
  SymbolMaxSize = MaxSizeCtrl->GetValue();
  PreviewUpdate();
}

void PointLayerClassifyDialog::OnMinColor(wxCommandEvent & WXUNUSED(event))
{
// minimun color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(MinColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      MinColor = colorData.GetColour();
      wxBitmap bmp;
      GetButtonBitmap(MinColor, bmp);
      MinColorCtrl->SetBitmapLabel(bmp);
      PreviewUpdate();
    }
}

void PointLayerClassifyDialog::OnMaxColor(wxCommandEvent & WXUNUSED(event))
{
// maximum color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(MaxColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      MaxColor = colorData.GetColour();
      wxBitmap bmp;
      GetButtonBitmap(MaxColor, bmp);
      MaxColorCtrl->SetBitmapLabel(bmp);
      PreviewUpdate();
    }
}

void PointLayerClassifyDialog::
OnPreviewRefresh(wxCommandEvent & WXUNUSED(event))
{
// loading SubClasses again
  PreviewLoad();
}

void PointLayerClassifyDialog::
OnRandomizeColors(wxCommandEvent & WXUNUSED(event))
{
// randomizing colors again
  if (DistinctList)
    {
      DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewUpdate();
    }
}

void PointLayerClassifyDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  MinValue = PreviewCtrl->GetMinValue();
  MaxValue = PreviewCtrl->GetMaxValue();
  wxDialog::EndModal(wxID_OK);
}

bool LineLayerClassifyDialog::Create(MyFrame * parent, wxString & table,
                                     wxString & geom, wxString & descName,
                                     wxString & column, bool unique,
                                     int numClasses, double minValue,
                                     double maxValue, int minSize, int maxSize,
                                     wxColour & minColor, wxColour & maxColor,
                                     SubClassesContainer * subClasses)
{
//
// creating the dialog
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  ClassifyColumn = column;
  DistinctList = NULL;
  RangeList = NULL;
  UniqueValue = unique;
  NumClasses = numClasses;
  MinValue = minValue;
  MaxValue = maxValue;
  LineMinSize = minSize;
  LineMaxSize = maxSize;
  MinColor = minColor;
  MaxColor = maxColor;
  HueMode = RANDOM_COLOR_ALL;
  TransparencyMode = RANDOM_COLOR_OPAQUE;
  Images = NULL;

  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Classify - LINESTRING")) ==
      false)
    return false;
// populates individual controls
  MainFrame->GetColumnList(TableName, &NumColumns, &ColumnList, GeometryColumn,
                           LAYER_LINESTRING);
  CreateControls();
  if (subClasses->GetCount() > 0)
    PreviewBuild(subClasses);
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

LineLayerClassifyDialog::~LineLayerClassifyDialog()
{
// destructor 
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  if (ColumnList)
    delete[]ColumnList;
  if (Images)
    delete Images;
}

void LineLayerClassifyDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[128];
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
  wxTextCtrl *descCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                                        wxDefaultPosition,
                                        wxSize(350, 22), wxTE_READONLY);
  descSizer->Add(descCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// third row:  Classify column
  wxBoxSizer *classifyBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(classifyBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *classifyBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Classify cryteria"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *classifySizer = new wxStaticBoxSizer(classifyBox, wxVERTICAL);
  classifyBoxSizer->Add(classifySizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *classify2Sizer = new wxBoxSizer(wxHORIZONTAL);
  classifySizer->Add(classify2Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *classifyLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column:"));
  classify2Sizer->Add(classifyLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  ColumnCtrl =
    new wxComboBox(this, ID_CLASSES_COLUMN, wxT(""), wxDefaultPosition,
                   wxDefaultSize, NumColumns, ColumnList,
                   wxCB_DROPDOWN | wxCB_READONLY);
  classify2Sizer->Add(ColumnCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  int sel = 0;
  int i;
  for (i = 1; i < NumColumns; i++)
    {
      if (ColumnList[i] == ClassifyColumn)
        sel = i;
    }
  ColumnCtrl->SetSelection(sel);
  wxString modes[2];
  modes[0] = wxT("&Distinct values");
  modes[1] = wxT("&Range of values");
  ModeCtrl =
    new wxRadioBox(this, ID_CLASSES_MODE, wxT("&Mode"), wxDefaultPosition,
                   wxDefaultSize, 2, modes, 2, wxRA_SPECIFY_ROWS);
  if (UniqueValue == true)
    ModeCtrl->SetSelection(0);
  else
    ModeCtrl->SetSelection(1);
  classify2Sizer->Add(ModeCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  wxStaticText *numLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Classes:"));
  classify2Sizer->Add(numLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  sprintf(dummy, "%d", NumClasses);
  wxString num = wxString::FromUTF8(dummy);
  ClassesCtrl =
    new wxSpinCtrl(this, ID_CLASSES_NUM, num, wxDefaultPosition, wxSize(50, 20),
                   wxSP_ARROW_KEYS, 2, 32, NumClasses);
  classify2Sizer->Add(ClassesCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);

// fourth row: graphics and test example
  wxBoxSizer *grSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(grSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxBoxSizer *testSizer = new wxBoxSizer(wxVERTICAL);
  grSizer->Add(testSizer, 0, wxALIGN_LEFT | wxALL, 0);

  wxStaticBox *testBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Preview"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *tstSizer = new wxStaticBoxSizer(testBox, wxVERTICAL);
  testSizer->Add(tstSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *tst2Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst2Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  PreviewCtrl =
    new SubClassesPreview(this, ID_CLASSES_PREVIEW, LAYER_LINESTRING);
  PreviewCtrl->SetLineParent(this);
  tst2Sizer->Add(PreviewCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  wxBoxSizer *tst3Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst3Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  DisplayCtrl = new wxTextCtrl(this, ID_CLASSES_DISPLAY,
                               wxT(""), wxDefaultPosition, wxSize(250, 44),
                               wxTE_RICH | wxTE_MULTILINE | wxTE_READONLY);
  tst3Sizer->Add(DisplayCtrl, 0, wxALIGN_LEFT | wxALL, 1);

  wxBoxSizer *hueSizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(hueSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString hueOptions[4];
  hueOptions[0] = wxT("Any");
  hueOptions[1] = wxT("Sature");
  hueOptions[2] = wxT("Medium");
  hueOptions[3] = wxT("Light");
  HueCtrl = new wxRadioBox(this, ID_CLASSES_HUE,
                           wxT("Random Color Hue"),
                           wxDefaultPosition, wxDefaultSize, 4, hueOptions, 4,
                           wxRA_SPECIFY_COLS);
  HueCtrl->SetSelection(0);
  hueSizer->Add(HueCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  wxBoxSizer *transpSizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(transpSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString transpOptions[4];
  transpOptions[0] = wxT("Opaque");
  transpOptions[1] = wxT("Medium");
  transpOptions[2] = wxT("Light");
  TransparencyCtrl = new wxRadioBox(this, ID_CLASSES_TRANSPARENCY,
                                    wxT("Random Color Transparency"),
                                    wxDefaultPosition, wxDefaultSize, 3,
                                    transpOptions, 3, wxRA_SPECIFY_COLS);
  TransparencyCtrl->SetSelection(0);
  transpSizer->Add(TransparencyCtrl, 0, wxALIGN_RIGHT | wxALL, 1);

  wxBoxSizer *tst4Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst4Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  RebuildCtrl =
    new wxButton(this, ID_CLASSES_REBUILD, wxT("&Reset/Reinitialize"));
  tst4Sizer->Add(RebuildCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  RandomizeCtrl =
    new wxButton(this, ID_CLASSES_RANDOMIZE, wxT("&Randomize Colors"));
  tst4Sizer->Add(RandomizeCtrl, 0, wxALIGN_RIGHT | wxALL, 1);

  wxBoxSizer *graphicsSizer = new wxBoxSizer(wxVERTICAL);
  grSizer->Add(graphicsSizer, 0, wxALIGN_RIGHT | wxALL, 0);

  wxStaticBox *graphicsBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Graphics"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *grphcsSizer = new wxStaticBoxSizer(graphicsBox, wxVERTICAL);
  graphicsSizer->Add(grphcsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *grphcs2Sizer = new wxBoxSizer(wxHORIZONTAL);
  grphcsSizer->Add(grphcs2Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);


  wxStaticBox *sizeBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Line Thickness Range"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *szSizer = new wxStaticBoxSizer(sizeBox, wxVERTICAL);
  grphcsSizer->Add(szSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *grphcs3Sizer = new wxBoxSizer(wxHORIZONTAL);
  szSizer->Add(grphcs3Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *minLabel = new wxStaticText(this, wxID_STATIC, wxT("&Min:"));
  grphcs3Sizer->Add(minLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", LineMinSize);
  wxString min = wxString::FromUTF8(dummy);
  MinSizeCtrl =
    new wxSpinCtrl(this, ID_CLASSES_MIN_SIZE, min, wxDefaultPosition,
                   wxSize(50, 20), wxSP_ARROW_KEYS, 1, 16, LineMinSize);
  grphcs3Sizer->Add(MinSizeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *grphcs4Sizer = new wxBoxSizer(wxHORIZONTAL);
  szSizer->Add(grphcs4Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *maxLabel = new wxStaticText(this, wxID_STATIC, wxT("&Max:"));
  grphcs4Sizer->Add(maxLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", LineMaxSize);
  wxString max = wxString::FromUTF8(dummy);
  MaxSizeCtrl =
    new wxSpinCtrl(this, ID_CLASSES_MAX_SIZE, max, wxDefaultPosition,
                   wxSize(50, 20), wxSP_ARROW_KEYS, 1, 16, LineMaxSize);
  grphcs4Sizer->Add(MaxSizeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxStaticBox *colorBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Color Range"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *colSizer = new wxStaticBoxSizer(colorBox, wxVERTICAL);
  grphcsSizer->Add(colSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *grphcs5Sizer = new wxBoxSizer(wxHORIZONTAL);
  colSizer->Add(grphcs5Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *minColorLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Min:"));
  grphcs5Sizer->Add(minColorLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap disabledBmp;
  GetDisabledButtonBitmap(disabledBmp);
  wxBitmap minBmp;
  GetButtonBitmap(MinColor, minBmp);
  MinColorCtrl = new wxBitmapButton(this, ID_CLASSES_MIN_COLOR, minBmp);
  MinColorCtrl->SetBitmapDisabled(disabledBmp);
  grphcs5Sizer->Add(MinColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *grphcs6Sizer = new wxBoxSizer(wxHORIZONTAL);
  colSizer->Add(grphcs6Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *maxColorLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Max:"));
  grphcs6Sizer->Add(maxColorLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap maxBmp;
  GetButtonBitmap(MaxColor, maxBmp);
  MaxColorCtrl = new wxBitmapButton(this, ID_CLASSES_MAX_COLOR, maxBmp);
  MaxColorCtrl->SetBitmapDisabled(disabledBmp);
  grphcs6Sizer->Add(MaxColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  if (UniqueValue == true)
    {
      ClassesCtrl->Enable(false);
      MaxSizeCtrl->Enable(false);
      MinColorCtrl->Enable(false);
      MaxColorCtrl->Enable(false);
      RandomizeCtrl->Enable(true);
      HueCtrl->Show(true);
      TransparencyCtrl->Show(true);
  } else
    {
      ClassesCtrl->Enable(true);
      MaxSizeCtrl->Enable(true);
      MinColorCtrl->Enable(true);
      MaxColorCtrl->Enable(true);
      RandomizeCtrl->Enable(false);
      HueCtrl->Show(false);
      TransparencyCtrl->Show(false);
    }
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnOk);
  Connect(ID_CLASSES_COLUMN, wxEVT_COMMAND_COMBOBOX_SELECTED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnColumnSelected);
  Connect(ID_CLASSES_MODE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnModeSelected);
  Connect(ID_CLASSES_NUM, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) &
          LineLayerClassifyDialog::OnNumClassesChanged);
  Connect(ID_CLASSES_MIN_SIZE, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnMinSizeChanged);
  Connect(ID_CLASSES_MAX_SIZE, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnMaxSizeChanged);
  Connect(ID_CLASSES_MIN_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnMinColor);
  Connect(ID_CLASSES_MAX_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnMaxColor);
  Connect(ID_CLASSES_REBUILD, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnPreviewRefresh);
  Connect(ID_CLASSES_RANDOMIZE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnRandomizeColors);
  Connect(ID_CLASSES_HUE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & LineLayerClassifyDialog::OnHueModeChanged);
  Connect(ID_CLASSES_TRANSPARENCY, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) &
          LineLayerClassifyDialog::OnTransparencyModeChanged);
}

void LineLayerClassifyDialog::OnHueModeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Random Color Hue selection changed
//
  if (HueCtrl->GetSelection() == 1)
    HueMode = RANDOM_COLOR_SATURE;
  else if (HueCtrl->GetSelection() == 2)
    HueMode = RANDOM_COLOR_MEDIUM;
  else if (HueCtrl->GetSelection() == 3)
    HueMode = RANDOM_COLOR_LIGHT;
  else
    HueMode = RANDOM_COLOR_ALL;
}

void LineLayerClassifyDialog::
OnTransparencyModeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Random Color Transparency selection changed
//
  if (TransparencyCtrl->GetSelection() == 1)
    TransparencyMode = RANDOM_COLOR_MEDIUM_TRANSPARENT;
  else if (TransparencyCtrl->GetSelection() == 2)
    TransparencyMode = RANDOM_COLOR_LIGHT_TRANSPARENT;
  else
    TransparencyMode = RANDOM_COLOR_OPAQUE;
}

void LineLayerClassifyDialog::PreviewBuild(SubClassesContainer * subClasses)
{
//
// populating the SubClasses from received SubClasses
//
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  DistinctList = NULL;
  RangeList = NULL;
  if (ClassifyColumn.Len() == 0)
    return;
  DisplayCtrl->SetValue(wxT(""));
  if (UniqueValue == true)
    {
      // DISTINCT values
      DistinctList = new MyDistinctValueList();
      // generating the preview - DISTINCT values
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      subClasses->BuildDistinctList(DistinctList);
      if (subClasses->HasColors() == false)
        DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_LINESTRING, 0,
                                     LineMinSize);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // range of values
      RangeList = new MyRangeValueList();
      // generating the preview - RANGE values
      PreviewCtrl->SetRange(MinValue, MaxValue);
      PreviewCtrl->Show(false);
      subClasses->BuildRangeList(RangeList);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_LINESTRING, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void LineLayerClassifyDialog::PreviewLoad()
{
//
// querying the DB and populating the SubClasses
//
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  DistinctList = NULL;
  RangeList = NULL;
  if (ClassifyColumn.Len() == 0)
    return;

  DisplayCtrl->SetValue(wxT(""));
  if (UniqueValue == true)
    {
      // DISTINCT values
      DistinctList = new MyDistinctValueList();
      bool truncated;
      MainFrame->GetDistinctValues(TableName, ClassifyColumn, DistinctList,
                                   &truncated);
      if (DistinctList->GetType() == CLASSES_INVALID_TYPE)
        {
          wxString msg = wxT("This column doesn't contains valid values\n");
          msg += wxT("Please, select a different Column");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(), wxTextAttr(wxColour(255, 0, 0)));
          delete DistinctList;
          DistinctList = NULL;
          return;
        }
      if (truncated == true)
        {
          wxString msg =
            wxT("The limit for DISTINCT values has been exceded\n");
          msg +=
            wxT
            ("This is an incomplete list [truncated], and only the first 50 values will be shown\n");
          msg += wxT("Any other subsequent value will be then ignored.");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(),
                                wxTextAttr(wxColour(255, 128, 0)));
        }
      // generating the preview - DISTINCT values
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_LINESTRING, 0,
                                     LineMinSize);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          obj->SetSize(LineMinSize);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // range of values
      RangeList = new MyRangeValueList();
      double min;
      double max;
      bool invalid;
      MainFrame->GetMaxMinValues(TableName, ClassifyColumn, &min, &max,
                                 &invalid);
      if (invalid == true)
        {
          wxString msg = wxT("This column doesn't contains NUMERIC values\n");
          msg +=
            wxT("Please, select a different Column, or try using DISTINCT");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(), wxTextAttr(wxColour(255, 0, 0)));
          delete RangeList;
          RangeList = NULL;
          return;
        }
      // generating the preview - RANGE values
      PreviewCtrl->SetRange(min, max);
      PreviewCtrl->Show(false);
      RangeList->Build(min, max, NumClasses, LineMinSize, LineMaxSize, MinColor,
                       MaxColor);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_LINESTRING, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void LineLayerClassifyDialog::PreviewUpdate()
{
  if (DistinctList == NULL && RangeList == NULL)
    {
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = NULL;
      PreviewCtrl->DeleteAllItems();
      PreviewCtrl->AddRoot(wxT("default"));
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
      DisplayCtrl->SetValue(wxT(""));
      return;
    }
  if (UniqueValue == true)
    {
      // generating the preview - DISTINCT values
      PreviewCtrl->Show(false);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_LINESTRING, 0,
                                     LineMinSize);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          obj->SetSize(LineMinSize);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // generating the preview - RANGE values
      PreviewCtrl->Show(false);
      RangeList->Build(PreviewCtrl->GetMinValue(), PreviewCtrl->GetMaxValue(),
                       NumClasses, LineMinSize, LineMaxSize, MinColor,
                       MaxColor);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_LINESTRING, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void LineLayerClassifyDialog::GetButtonBitmap(wxColour & color, wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(32, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(color));
  dc->DrawRectangle(-1, -1, 34, 26);
  delete dc;
}

void LineLayerClassifyDialog::GetDisabledButtonBitmap(wxBitmap & bmp)
{
// creating the disabled Bitmap
  bmp = wxBitmap(32, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
  dc->DrawRectangle(-1, -1, 34, 26);
  delete dc;
}

void LineLayerClassifyDialog::OnColumnSelected(wxCommandEvent & WXUNUSED(event))
{
// column selection
  if (ColumnCtrl->GetSelection() > 0)
    ClassifyColumn = ColumnCtrl->GetStringSelection();
  else
    ClassifyColumn = wxT("");
  PreviewLoad();
}

void LineLayerClassifyDialog::OnModeSelected(wxCommandEvent & WXUNUSED(event))
{
// mode selection
  if (ModeCtrl->GetSelection() == 0)
    UniqueValue = true;
  else
    UniqueValue = false;
  if (UniqueValue == true)
    {
      ClassesCtrl->Enable(false);
      MaxSizeCtrl->Enable(false);
      MinColorCtrl->Enable(false);
      MaxColorCtrl->Enable(false);
      RandomizeCtrl->Enable(true);
      HueCtrl->Show(true);
      TransparencyCtrl->Show(true);
  } else
    {
      ClassesCtrl->Enable(true);
      MaxSizeCtrl->Enable(true);
      MinColorCtrl->Enable(true);
      MaxColorCtrl->Enable(true);
      RandomizeCtrl->Enable(false);
      HueCtrl->Show(false);
      TransparencyCtrl->Show(false);
    }
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
  Centre();
  PreviewLoad();
}

void LineLayerClassifyDialog::
OnNumClassesChanged(wxCommandEvent & WXUNUSED(event))
{
// # classes selection
  NumClasses = ClassesCtrl->GetValue();
  PreviewUpdate();
}

void LineLayerClassifyDialog::OnMinSizeChanged(wxCommandEvent & WXUNUSED(event))
{
// minimun symbol size selection
  LineMinSize = MinSizeCtrl->GetValue();
  if (LineMinSize > LineMaxSize)
    {
      LineMinSize = LineMaxSize;
      MinSizeCtrl->SetValue(LineMinSize);
    }
  PreviewUpdate();
}

void LineLayerClassifyDialog::OnMaxSizeChanged(wxCommandEvent & WXUNUSED(event))
{
// maximun symbol size selection
  LineMaxSize = MaxSizeCtrl->GetValue();
  if (LineMaxSize < LineMinSize)
    {
      LineMaxSize = LineMinSize;
      MaxSizeCtrl->SetValue(LineMaxSize);
    }
  PreviewUpdate();
}

void LineLayerClassifyDialog::OnMinColor(wxCommandEvent & WXUNUSED(event))
{
// minimun color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(MinColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      MinColor = colorData.GetColour();
      wxBitmap bmp;
      GetButtonBitmap(MinColor, bmp);
      MinColorCtrl->SetBitmapLabel(bmp);
      PreviewUpdate();
    }
}

void LineLayerClassifyDialog::OnMaxColor(wxCommandEvent & WXUNUSED(event))
{
// maximum color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(MaxColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      MaxColor = colorData.GetColour();
      wxBitmap bmp;
      GetButtonBitmap(MaxColor, bmp);
      MaxColorCtrl->SetBitmapLabel(bmp);
      PreviewUpdate();
    }
}

void LineLayerClassifyDialog::OnPreviewRefresh(wxCommandEvent & WXUNUSED(event))
{
// loading SubClasses again
  PreviewLoad();
}

void LineLayerClassifyDialog::
OnRandomizeColors(wxCommandEvent & WXUNUSED(event))
{
// randomizing colors again
  if (DistinctList)
    {
      DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewUpdate();
    }
}

void LineLayerClassifyDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  MinValue = PreviewCtrl->GetMinValue();
  MaxValue = PreviewCtrl->GetMaxValue();
  wxDialog::EndModal(wxID_OK);
}

bool PolygonLayerClassifyDialog::Create(MyFrame * parent, wxString & table,
                                        wxString & geom, wxString & descName,
                                        wxString & column, bool unique,
                                        int numClasses, double minValue,
                                        double maxValue, wxColour & minColor,
                                        wxColour & maxColor,
                                        SubClassesContainer * subClasses)
{
//
// creating the dialog
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  ClassifyColumn = column;
  DistinctList = NULL;
  RangeList = NULL;
  UniqueValue = unique;
  NumClasses = numClasses;
  MinValue = minValue;
  MaxValue = maxValue;
  MinColor = minColor;
  MaxColor = maxColor;
  HueMode = RANDOM_COLOR_ALL;
  TransparencyMode = RANDOM_COLOR_OPAQUE;
  Images = NULL;

  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Classify - POLYGON")) ==
      false)
    return false;
// populates individual controls
  MainFrame->GetColumnList(TableName, &NumColumns, &ColumnList, GeometryColumn,
                           LAYER_POLYGON);
  CreateControls();
  if (subClasses->GetCount() > 0)
    PreviewBuild(subClasses);
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

PolygonLayerClassifyDialog::~PolygonLayerClassifyDialog()
{
// destructor 
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  if (ColumnList)
    delete[]ColumnList;
  if (Images)
    delete Images;
}

void PolygonLayerClassifyDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[128];
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
  wxTextCtrl *descCtrl = new wxTextCtrl(this, wxID_STATIC, DescName,
                                        wxDefaultPosition,
                                        wxSize(350, 22), wxTE_READONLY);
  descSizer->Add(descCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row:  Classify column
  wxBoxSizer *classifyBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(classifyBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *classifyBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Classify cryteria"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *classifySizer = new wxStaticBoxSizer(classifyBox, wxVERTICAL);
  classifyBoxSizer->Add(classifySizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *classify2Sizer = new wxBoxSizer(wxHORIZONTAL);
  classifySizer->Add(classify2Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *classifyLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column:"));
  classify2Sizer->Add(classifyLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  ColumnCtrl =
    new wxComboBox(this, ID_CLASSES_COLUMN, wxT(""), wxDefaultPosition,
                   wxDefaultSize, NumColumns, ColumnList,
                   wxCB_DROPDOWN | wxCB_READONLY);
  classify2Sizer->Add(ColumnCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  int sel = 0;
  int i;
  for (i = 1; i < NumColumns; i++)
    {
      if (ColumnList[i] == ClassifyColumn)
        sel = i;
    }
  ColumnCtrl->SetSelection(sel);
  wxString modes[2];
  modes[0] = wxT("&Distinct values");
  modes[1] = wxT("&Range of values");
  ModeCtrl =
    new wxRadioBox(this, ID_CLASSES_MODE, wxT("&Mode"), wxDefaultPosition,
                   wxDefaultSize, 2, modes, 2, wxRA_SPECIFY_ROWS);
  if (UniqueValue == true)
    ModeCtrl->SetSelection(0);
  else
    ModeCtrl->SetSelection(1);
  classify2Sizer->Add(ModeCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  wxStaticText *numLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Classes:"));
  classify2Sizer->Add(numLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  sprintf(dummy, "%d", NumClasses);
  wxString num = wxString::FromUTF8(dummy);
  ClassesCtrl =
    new wxSpinCtrl(this, ID_CLASSES_NUM, num, wxDefaultPosition, wxSize(50, 20),
                   wxSP_ARROW_KEYS, 2, 32, NumClasses);
  classify2Sizer->Add(ClassesCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
// fourth row: graphics and test example
  wxBoxSizer *grSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(grSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxBoxSizer *testSizer = new wxBoxSizer(wxVERTICAL);
  grSizer->Add(testSizer, 0, wxALIGN_LEFT | wxALL, 0);

  wxStaticBox *testBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Preview"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *tstSizer = new wxStaticBoxSizer(testBox, wxVERTICAL);
  testSizer->Add(tstSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *tst2Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst2Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  PreviewCtrl = new SubClassesPreview(this, ID_CLASSES_PREVIEW, LAYER_POLYGON);
  PreviewCtrl->SetPolygonParent(this);
  tst2Sizer->Add(PreviewCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  wxBoxSizer *tst3Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst3Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  DisplayCtrl = new wxTextCtrl(this, ID_CLASSES_DISPLAY,
                               wxT(""), wxDefaultPosition, wxSize(250, 44),
                               wxTE_RICH | wxTE_MULTILINE | wxTE_READONLY);
  tst3Sizer->Add(DisplayCtrl, 0, wxALIGN_LEFT | wxALL, 1);

  wxBoxSizer *hueSizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(hueSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString hueOptions[4];
  hueOptions[0] = wxT("Any");
  hueOptions[1] = wxT("Sature");
  hueOptions[2] = wxT("Medium");
  hueOptions[3] = wxT("Light");
  HueCtrl = new wxRadioBox(this, ID_CLASSES_HUE,
                           wxT("Random Color Hue"),
                           wxDefaultPosition, wxDefaultSize, 4, hueOptions, 4,
                           wxRA_SPECIFY_COLS);
  HueCtrl->SetSelection(0);
  hueSizer->Add(HueCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  wxBoxSizer *transpSizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(transpSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString transpOptions[4];
  transpOptions[0] = wxT("Opaque");
  transpOptions[1] = wxT("Medium");
  transpOptions[2] = wxT("Light");
  TransparencyCtrl = new wxRadioBox(this, ID_CLASSES_TRANSPARENCY,
                                    wxT("Random Color Transparency"),
                                    wxDefaultPosition, wxDefaultSize, 3,
                                    transpOptions, 3, wxRA_SPECIFY_COLS);
  TransparencyCtrl->SetSelection(0);
  transpSizer->Add(TransparencyCtrl, 0, wxALIGN_RIGHT | wxALL, 1);

  wxBoxSizer *tst4Sizer = new wxBoxSizer(wxHORIZONTAL);
  tstSizer->Add(tst4Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  RebuildCtrl =
    new wxButton(this, ID_CLASSES_REBUILD, wxT("&Reset/Reinitialize"));
  tst4Sizer->Add(RebuildCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  RandomizeCtrl =
    new wxButton(this, ID_CLASSES_RANDOMIZE, wxT("&Randomize Colors"));
  tst4Sizer->Add(RandomizeCtrl, 0, wxALIGN_RIGHT | wxALL, 1);

  wxBoxSizer *graphicsSizer = new wxBoxSizer(wxVERTICAL);
  grSizer->Add(graphicsSizer, 0, wxALIGN_RIGHT | wxALL, 0);

  wxStaticBox *graphicsBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Graphics"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *grphcsSizer = new wxStaticBoxSizer(graphicsBox, wxVERTICAL);
  graphicsSizer->Add(grphcsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *grphcs2Sizer = new wxBoxSizer(wxHORIZONTAL);
  grphcsSizer->Add(grphcs2Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);

  wxStaticBox *colorBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Color Range"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *colSizer = new wxStaticBoxSizer(colorBox, wxVERTICAL);
  grphcsSizer->Add(colSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *grphcs5Sizer = new wxBoxSizer(wxHORIZONTAL);
  colSizer->Add(grphcs5Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *minColorLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Min:"));
  grphcs5Sizer->Add(minColorLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap disabledBmp;
  GetDisabledButtonBitmap(disabledBmp);
  wxBitmap minBmp;
  GetButtonBitmap(MinColor, minBmp);
  MinColorCtrl = new wxBitmapButton(this, ID_CLASSES_MIN_COLOR, minBmp);
  MinColorCtrl->SetBitmapDisabled(disabledBmp);
  grphcs5Sizer->Add(MinColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *grphcs6Sizer = new wxBoxSizer(wxHORIZONTAL);
  colSizer->Add(grphcs6Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *maxColorLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Max:"));
  grphcs6Sizer->Add(maxColorLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBitmap maxBmp;
  GetButtonBitmap(MaxColor, maxBmp);
  MaxColorCtrl = new wxBitmapButton(this, ID_CLASSES_MAX_COLOR, maxBmp);
  MaxColorCtrl->SetBitmapDisabled(disabledBmp);
  grphcs6Sizer->Add(MaxColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  if (UniqueValue == true)
    {
      ClassesCtrl->Enable(false);
      MinColorCtrl->Enable(false);
      MaxColorCtrl->Enable(false);
      RandomizeCtrl->Enable(true);
      HueCtrl->Show(true);
      TransparencyCtrl->Show(true);
  } else
    {
      ClassesCtrl->Enable(true);
      MinColorCtrl->Enable(true);
      MaxColorCtrl->Enable(true);
      RandomizeCtrl->Enable(false);
      HueCtrl->Show(false);
      TransparencyCtrl->Show(false);
    }
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PolygonLayerClassifyDialog::OnOk);
  Connect(ID_CLASSES_COLUMN, wxEVT_COMMAND_COMBOBOX_SELECTED,
          (wxObjectEventFunction) &
          PolygonLayerClassifyDialog::OnColumnSelected);
  Connect(ID_CLASSES_MODE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & PolygonLayerClassifyDialog::OnModeSelected);
  Connect(ID_CLASSES_NUM, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) &
          PolygonLayerClassifyDialog::OnNumClassesChanged);
  Connect(ID_CLASSES_MIN_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PolygonLayerClassifyDialog::OnMinColor);
  Connect(ID_CLASSES_MAX_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & PolygonLayerClassifyDialog::OnMaxColor);
  Connect(ID_CLASSES_REBUILD, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) &
          PolygonLayerClassifyDialog::OnPreviewRefresh);
  Connect(ID_CLASSES_RANDOMIZE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) &
          PolygonLayerClassifyDialog::OnRandomizeColors);
  Connect(ID_CLASSES_HUE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) &
          PolygonLayerClassifyDialog::OnHueModeChanged);
  Connect(ID_CLASSES_TRANSPARENCY, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) &
          PolygonLayerClassifyDialog::OnTransparencyModeChanged);
}

void PolygonLayerClassifyDialog::
OnHueModeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Random Color Hue selection changed
//
  if (HueCtrl->GetSelection() == 1)
    HueMode = RANDOM_COLOR_SATURE;
  else if (HueCtrl->GetSelection() == 2)
    HueMode = RANDOM_COLOR_MEDIUM;
  else if (HueCtrl->GetSelection() == 3)
    HueMode = RANDOM_COLOR_LIGHT;
  else
    HueMode = RANDOM_COLOR_ALL;
}

void PolygonLayerClassifyDialog::
OnTransparencyModeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Random Color Transparency selection changed
//
  if (TransparencyCtrl->GetSelection() == 1)
    TransparencyMode = RANDOM_COLOR_MEDIUM_TRANSPARENT;
  else if (TransparencyCtrl->GetSelection() == 2)
    TransparencyMode = RANDOM_COLOR_LIGHT_TRANSPARENT;
  else
    TransparencyMode = RANDOM_COLOR_OPAQUE;
}

void PolygonLayerClassifyDialog::PreviewBuild(SubClassesContainer * subClasses)
{
//
// populating the SubClasses from received SubClasses
//
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  DistinctList = NULL;
  RangeList = NULL;
  if (ClassifyColumn.Len() == 0)
    return;
  DisplayCtrl->SetValue(wxT(""));
  if (UniqueValue == true)
    {
      // DISTINCT values
      DistinctList = new MyDistinctValueList();
      // generating the preview - DISTINCT values
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      subClasses->BuildDistinctList(DistinctList);
      if (subClasses->HasColors() == false)
        DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_POLYGON, 0, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // range of values
      RangeList = new MyRangeValueList();
      // generating the preview - RANGE values
      PreviewCtrl->SetRange(MinValue, MaxValue);
      PreviewCtrl->Show(false);
      subClasses->BuildRangeList(RangeList);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_POLYGON, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void PolygonLayerClassifyDialog::PreviewLoad()
{
//
// querying the DB and populating the SubClasses
//  
  if (DistinctList)
    delete DistinctList;
  if (RangeList)
    delete RangeList;
  DistinctList = NULL;
  RangeList = NULL;
  if (ClassifyColumn.Len() == 0)
    return;

  DisplayCtrl->SetValue(wxT(""));
  if (UniqueValue == true)
    {
      // DISTINCT values
      DistinctList = new MyDistinctValueList();
      bool truncated;
      MainFrame->GetDistinctValues(TableName, ClassifyColumn, DistinctList,
                                   &truncated);
      if (DistinctList->GetType() == CLASSES_INVALID_TYPE)
        {
          wxString msg = wxT("This column doesn't contains valid values\n");
          msg += wxT("Please, select a different Column");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(), wxTextAttr(wxColour(255, 0, 0)));
          delete DistinctList;
          DistinctList = NULL;
          return;
        }
      if (truncated == true)
        {
          wxString msg =
            wxT("The limit for DISTINCT values has been exceded\n");
          msg +=
            wxT
            ("This is an incomplete list [truncated], and only the first 50 values will be shown\n");
          msg += wxT("Any other subsequent value will be then ignored.");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(),
                                wxTextAttr(wxColour(255, 128, 0)));
        }
      // generating the preview - DISTINCT values
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_POLYGON, 0, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // range of values
      RangeList = new MyRangeValueList();
      double min;
      double max;
      bool invalid;
      MainFrame->GetMaxMinValues(TableName, ClassifyColumn, &min, &max,
                                 &invalid);
      if (invalid == true)
        {
          wxString msg = wxT("This column doesn't contains NUMERIC values\n");
          msg +=
            wxT("Please, select a different Column, or try using DISTINCT");
          DisplayCtrl->SetValue(msg);
          DisplayCtrl->SetStyle(0, msg.Len(), wxTextAttr(wxColour(255, 0, 0)));
          delete RangeList;
          RangeList = NULL;
          return;
        }
      // generating the preview - RANGE values
      PreviewCtrl->SetRange(min, max);
      PreviewCtrl->Show(false);
      RangeList->Build(min, max, NumClasses, MinColor, MaxColor);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_POLYGON, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void PolygonLayerClassifyDialog::PreviewUpdate()
{
  if (DistinctList == NULL && RangeList == NULL)
    {
      PreviewCtrl->SetRange(0.0, 0.0);
      PreviewCtrl->Show(false);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = NULL;
      PreviewCtrl->DeleteAllItems();
      PreviewCtrl->AddRoot(wxT("default"));
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
      DisplayCtrl->SetValue(wxT(""));
      return;
    }
  if (UniqueValue == true)
    {
      // generating the preview - DISTINCT values
      PreviewCtrl->Show(false);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, DistinctList->GetCount());
      DistinctList->AddSubClassIcons(Images, 32, 16, LAYER_POLYGON, 0, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyDistinctValue *value = DistinctList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetValueAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
  } else
    {
      // generating the preview - RANGE values
      PreviewCtrl->Show(false);
      RangeList->Build(PreviewCtrl->GetMinValue(), PreviewCtrl->GetMaxValue(),
                       NumClasses, MinColor, MaxColor);
      PreviewCtrl->SetImageList(NULL);
      if (Images)
        delete Images;
      Images = new wxImageList(32, 16, RangeList->GetCount());
      RangeList->AddSubClassIcons(Images, 32, 16, LAYER_POLYGON, 0);
      // re-creating the Tree
      PreviewCtrl->SetImageList(Images);
      PreviewCtrl->DeleteAllItems();
      wxTreeItemId root = PreviewCtrl->AddRoot(wxT("default"));
      MyRangeValue *value = RangeList->GetFirst();
      while (value)
        {
          // inserting items into the Tree
          SubClassObject *obj = new SubClassObject(value);
          PreviewCtrl->AppendItem(root, value->GetRangeAsString(),
                                  value->GetIconIndex(), -1, obj);
          value = value->GetNext();
        }
      PreviewCtrl->ExpandAll();
      PreviewCtrl->Show(true);
    }
}

void PolygonLayerClassifyDialog::GetButtonBitmap(wxColour & color,
                                                 wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(32, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(color));
  dc->DrawRectangle(-1, -1, 34, 26);
  delete dc;
}

void PolygonLayerClassifyDialog::GetDisabledButtonBitmap(wxBitmap & bmp)
{
// creating the disabled Bitmap
  bmp = wxBitmap(32, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
  dc->DrawRectangle(-1, -1, 34, 26);
  delete dc;
}

void PolygonLayerClassifyDialog::
OnColumnSelected(wxCommandEvent & WXUNUSED(event))
{
// column selection
  if (ColumnCtrl->GetSelection() > 0)
    ClassifyColumn = ColumnCtrl->GetStringSelection();
  else
    ClassifyColumn = wxT("");
  PreviewLoad();
}

void PolygonLayerClassifyDialog::
OnModeSelected(wxCommandEvent & WXUNUSED(event))
{
// mode selection
  if (ModeCtrl->GetSelection() == 0)
    UniqueValue = true;
  else
    UniqueValue = false;
  if (UniqueValue == true)
    {
      ClassesCtrl->Enable(false);
      MinColorCtrl->Enable(false);
      MaxColorCtrl->Enable(false);
      RandomizeCtrl->Enable(true);
      HueCtrl->Show(true);
      TransparencyCtrl->Show(true);
  } else
    {
      ClassesCtrl->Enable(true);
      MinColorCtrl->Enable(true);
      MaxColorCtrl->Enable(true);
      RandomizeCtrl->Enable(false);
      HueCtrl->Show(false);
      TransparencyCtrl->Show(false);
    }
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
  Centre();
  PreviewLoad();
}

void PolygonLayerClassifyDialog::
OnNumClassesChanged(wxCommandEvent & WXUNUSED(event))
{
// # classes selection
  NumClasses = ClassesCtrl->GetValue();
  PreviewUpdate();
}

void PolygonLayerClassifyDialog::OnMinColor(wxCommandEvent & WXUNUSED(event))
{
// minimun color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(MinColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      MinColor = colorData.GetColour();
      wxBitmap bmp;
      GetButtonBitmap(MinColor, bmp);
      MinColorCtrl->SetBitmapLabel(bmp);
      PreviewUpdate();
    }
}

void PolygonLayerClassifyDialog::OnMaxColor(wxCommandEvent & WXUNUSED(event))
{
// maximum color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(MaxColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      MaxColor = colorData.GetColour();
      wxBitmap bmp;
      GetButtonBitmap(MaxColor, bmp);
      MaxColorCtrl->SetBitmapLabel(bmp);
      PreviewUpdate();
    }
}

void PolygonLayerClassifyDialog::
OnPreviewRefresh(wxCommandEvent & WXUNUSED(event))
{
// loading SubClasses again
  PreviewLoad();
}

void PolygonLayerClassifyDialog::
OnRandomizeColors(wxCommandEvent & WXUNUSED(event))
{
// randomizing colors again
  if (DistinctList)
    {
      DistinctList->RandomizeColors(MainFrame, HueMode, TransparencyMode);
      PreviewUpdate();
    }
}

void PolygonLayerClassifyDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  MinValue = PreviewCtrl->GetMinValue();
  MaxValue = PreviewCtrl->GetMaxValue();
  wxDialog::EndModal(wxID_OK);
}

/*
/ Objects.cpp
/ miscellaneous classe and objects
/
/ version 1.0, 2009 February 9
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
#include "wx/tokenzr.h"
#include "wx/imaglist.h"
#include "wx/mstream.h"

#include "icons/checked_brush.xpm"
#include "icons/checked_brush2.xpm"
#include "icons/checked_brush3.xpm"

LayerObject::LayerObject(LayerObject * org)
{
//
// copy constructor - TreeItemData
//
  this->Type = org->Type;
  this->LayerView = org->LayerView;
  this->LayerVirtual = org->LayerVirtual;
  this->ReadOnly = org->ReadOnly;
  this->GeometryType = org->GeometryType;
  this->MultiType = org->MultiType;
  this->TableName = org->TableName;
  this->GeometryColumn = org->GeometryColumn;
  this->DescName = org->DescName;
  this->Srid = org->Srid;
  this->Network = org->Network;
  this->Visible = org->Visible;
  this->Identify = org->Identify;
  this->EditingEnabled = false;
  this->Reproject = org->Reproject;
  this->AlwaysVisible = org->AlwaysVisible;
  this->MinScale = org->MinScale;
  this->MaxScale = org->MaxScale;
  this->SymbolId = org->SymbolId;
  this->ForegroundColor = org->ForegroundColor;
  this->BackgroundColor = org->BackgroundColor;
  this->LineColor = org->LineColor;
  this->LineThickness = org->LineThickness;
  this->LineStyle = org->LineStyle;
  this->DrawBorder = org->DrawBorder;
  this->ToFill = org->ToFill;
  this->SolidFilling = org->SolidFilling;
  this->FillColor = org->FillColor;
  this->PatternId = org->PatternId;
  this->LabelColumn = org->LabelColumn;
  this->MapLabeling = org->MapLabeling;
  this->LabelColor = org->LabelColor;
  this->LabelPointSize = org->LabelPointSize;
  this->LabelFontBold = org->LabelFontBold;
  this->LabelFontItalic = org->LabelFontItalic;
  this->LabelFontUnderlined = org->LabelFontUnderlined;
  this->LabelFontOutlined = org->LabelFontOutlined;
  this->LabelOrderByColumn = org->LabelOrderByColumn;
  this->LabelOrderByDescending = org->LabelOrderByDescending;
  this->LabelAlwaysVisible = org->LabelAlwaysVisible;
  this->LabelMinScale = org->LabelMinScale;
  this->LabelMaxScale = org->LabelMaxScale;
  this->LabelAntiOverlap = org->LabelAntiOverlap;
  this->Default = org->Default;
  this->IconIndex = org->IconIndex;
  this->SubClasses = org->SubClasses;
  this->ClassifyColumn = org->ClassifyColumn;
  this->UniqueValue = org->UniqueValue;
  this->NumClasses = org->NumClasses;
  this->ClassesMinValue = org->ClassesMinValue;
  this->ClassesMaxValue = org->ClassesMaxValue;
  this->ClassesSymbolType = org->ClassesSymbolType;
  this->ClassesMinSize = org->ClassesMinSize;
  this->ClassesMaxSize = org->ClassesMaxSize;
  this->ClassesMinColor = org->ClassesMinColor;
  this->ClassesMaxColor = org->ClassesMaxColor;
  this->SubClassUnique = org->SubClassUnique;
  this->SubClassText = org->SubClassText;
  this->SubClassTextValue = org->SubClassTextValue;
  this->SubClassNumValue = org->SubClassNumValue;
  this->SubClassMinValue = org->SubClassMinValue;
  this->SubClassMaxValue = org->SubClassMaxValue;
  this->SubClassSymbolType = org->SubClassSymbolType;
  this->SubClassSize = org->SubClassSize;
  this->SubClassColor = org->SubClassColor;
}

LayerObject::LayerObject(LayerObject * org, bool dflt)
{
//
// copy constructor - TreeItemData
//
  if (dflt)
    dflt = dflt;                // unused arg warning suppression
  this->Type = org->Type;
  this->LayerView = org->LayerView;
  this->LayerVirtual = org->LayerVirtual;
  this->ReadOnly = org->ReadOnly;
  this->GeometryType = org->GeometryType;
  this->MultiType = org->MultiType;
  this->TableName = org->TableName;
  this->GeometryColumn = org->GeometryColumn;
  this->DescName = org->DescName;
  this->Srid = org->Srid;
  this->Network = org->Network;
  this->Visible = org->Visible;
  this->Identify = org->Identify;
  this->EditingEnabled = false;
  this->Reproject = org->Reproject;
  this->AlwaysVisible = org->AlwaysVisible;
  this->MinScale = org->MinScale;
  this->MaxScale = org->MaxScale;
  this->SymbolId = org->SymbolId;
  this->ForegroundColor = org->ForegroundColor;
  this->BackgroundColor = org->BackgroundColor;
  this->LineColor = org->LineColor;
  this->LineThickness = org->LineThickness;
  this->LineStyle = org->LineStyle;
  this->DrawBorder = org->DrawBorder;
  this->ToFill = org->ToFill;
  this->SolidFilling = org->SolidFilling;
  this->FillColor = org->FillColor;
  this->LabelColumn = org->LabelColumn;
  this->MapLabeling = org->MapLabeling;
  this->LabelColor = org->LabelColor;
  this->LabelPointSize = org->LabelPointSize;
  this->LabelFontBold = org->LabelFontBold;
  this->LabelFontItalic = org->LabelFontItalic;
  this->LabelFontUnderlined = org->LabelFontUnderlined;
  this->LabelFontOutlined = org->LabelFontOutlined;
  this->LabelOrderByColumn = org->LabelOrderByColumn;
  this->LabelOrderByDescending = org->LabelOrderByDescending;
  this->LabelAlwaysVisible = org->LabelAlwaysVisible;
  this->LabelMinScale = org->LabelMinScale;
  this->LabelMaxScale = org->LabelMaxScale;
  this->LabelAntiOverlap = org->LabelAntiOverlap;
  this->PatternId = org->PatternId;
  this->Default = true;
  this->IconIndex = -1;
  this->SubClasses = org->SubClasses;
  this->ClassifyColumn = org->ClassifyColumn;
  this->UniqueValue = org->UniqueValue;
  this->NumClasses = org->NumClasses;
  this->ClassesMinValue = org->ClassesMinValue;
  this->ClassesMaxValue = org->ClassesMaxValue;
  this->ClassesSymbolType = org->ClassesSymbolType;
  this->ClassesMinSize = org->ClassesMinSize;
  this->ClassesMaxSize = org->ClassesMaxSize;
  this->ClassesMinColor = org->ClassesMinColor;
  this->ClassesMaxColor = org->ClassesMaxColor;
  this->SubClassUnique = org->SubClassUnique;
  this->SubClassText = org->SubClassText;
  this->SubClassTextValue = org->SubClassTextValue;
  this->SubClassNumValue = org->SubClassNumValue;
  this->SubClassMinValue = org->SubClassMinValue;
  this->SubClassMaxValue = org->SubClassMaxValue;
  this->SubClassSymbolType = org->SubClassSymbolType;
  this->SubClassSize = org->SubClassSize;
  this->SubClassColor = org->SubClassColor;
}

LayerObject::LayerObject(MyLayerParams * layer)
{
//
// constructor - TreeItemData
//
  if (layer->IsRasterLayer() == true)
    Type = RASTER_LAYER;
  else
    Type = VECTOR_LAYER;
  LayerView = layer->IsLayerView();
  LayerVirtual = layer->IsLayerVirtual();
  this->ReadOnly = layer->IsReadOnly();
  GeometryType = layer->GetGeometryType();
  MultiType = layer->IsMultiType();
  TableName = layer->GetTableName();
  GeometryColumn = layer->GetGeometryColumn();
  DescName = layer->GetDescName();
  Srid = layer->GetSrid();
  Network = layer->IsNetwork();
  Visible = layer->IsVisible();
  Identify = layer->IsIdentify();
  EditingEnabled = false;
  Reproject = layer->IsReproject();
  AlwaysVisible = layer->IsAlwaysVisible();
  MinScale = layer->GetMinScale();
  MaxScale = layer->GetMaxScale();
  SymbolId = layer->GetSymbolId();
  ForegroundColor = layer->GetForegroundColor();
  BackgroundColor = layer->GetBackgroundColor();
  LineColor = layer->GetLineColor();
  LineThickness = layer->GetLineThickness();
  LineStyle = layer->GetLineStyle();
  DrawBorder = layer->DrawBorderOk();
  ToFill = layer->IsToFill();
  SolidFilling = layer->SolidFillingOk();
  FillColor = layer->GetFillColor();
  PatternId = layer->GetPatternId();
  LabelColumn = layer->GetLabelColumn();
  MapLabeling = layer->IsMapLabelingEnabled();
  LabelColor = layer->GetLabelColor();
  LabelPointSize = layer->GetLabelPointSize();
  LabelFontBold = layer->IsLabelFontBold();
  LabelFontItalic = layer->IsLabelFontItalic();
  LabelFontUnderlined = layer->IsLabelFontUnderlined();
  LabelFontOutlined = layer->IsLabelFontOutlined();
  LabelOrderByColumn = layer->GetLabelOrderByColumn();
  LabelOrderByDescending = layer->IsLabelOrderByDescending();
  LabelAlwaysVisible = layer->IsLabelAlwaysVisible();
  LabelMinScale = layer->GetLabelMinScale();
  LabelMaxScale = layer->GetLabelMaxScale();
  LabelAntiOverlap = layer->IsLabelAntiOverlapEnabled();
  Default = false;
  IconIndex = -1;
  SubClasses = layer->HasSubClasses();
  ClassifyColumn = layer->GetClassifyColumn();
  UniqueValue = layer->IsUniqueValue();
  NumClasses = layer->GetNumClasses();
  ClassesMinValue = layer->GetClassesMinValue();
  ClassesMaxValue = layer->GetClassesMaxValue();
  ClassesSymbolType = layer->GetClassesSymbolType();
  ClassesMinSize = layer->GetClassesMinSize();
  ClassesMaxSize = layer->GetClassesMaxSize();
  ClassesMinColor = layer->GetClassesMinColor();
  ClassesMaxColor = layer->GetClassesMaxColor();
  SubClassUnique = false;
  SubClassText = false;
  SubClassTextValue = wxT("");
  SubClassNumValue = 0.0;
  SubClassMinValue = 0.0;
  SubClassMaxValue = 0.0;
  SubClassSymbolType = CLASSES_SYMBOL_CIRCLE;
  SubClassSize = 1;
  SubClassColor = wxColour(255, 255, 255);
}

LayerObject::LayerObject(wxString & name, int srid)
{
//
// constructor - TreeItemData
//
  Type = RASTER_LAYER;
  LayerView = false;
  LayerVirtual = false;
  ReadOnly = false;
  GeometryType = -1;
  MultiType = false;
  TableName = name;
  GeometryColumn = wxT("RASTER");
  Srid = srid;
  Network = false;
  Visible = true;
  Identify = false;
  EditingEnabled = false;
  Reproject = false;
  AlwaysVisible = true;
  MinScale = 0;
  MaxScale = 0;
  SymbolId = 1;
  ForegroundColor = wxColour(255, 255, 255);
  BackgroundColor = wxColour(0, 0, 0);
  LineColor = wxColour(0, 255, 128, 255);
  LineThickness = 1;
  LineStyle = wxSOLID;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = true;
  FillColor = wxColour(0, 128, 64);
  PatternId = 1;
  LabelColumn = wxT("");
  MapLabeling = false;
  LabelColor = wxColour(0, 0, 0);
  LabelPointSize = 10;
  LabelFontBold = false;
  LabelFontItalic = false;
  LabelFontUnderlined = false;
  LabelFontOutlined = false;
  LabelOrderByColumn = wxT("");
  LabelOrderByDescending = false;
  LabelAlwaysVisible = true;
  LabelMinScale = 0;
  LabelMaxScale = 0;
  LabelAntiOverlap = false;
  Default = false;
  IconIndex = -1;
  SubClasses = false;
  ClassifyColumn = wxT("");
  UniqueValue = false;
  NumClasses = 2;
  ClassesMinValue = 0.0;
  ClassesMaxValue = 0.0;
  ClassesSymbolType = CLASSES_SYMBOL_CIRCLE;
  ClassesMinSize = 1;
  ClassesMaxSize = 16;
  ClassesMinColor = wxColour(0, 0, 0);
  ClassesMaxColor = wxColour(255, 255, 255);
  SubClassUnique = false;
  SubClassText = false;
  SubClassTextValue = wxT("");
  SubClassNumValue = 0.0;
  SubClassMinValue = 0.0;
  SubClassMaxValue = 0.0;
  SubClassSymbolType = CLASSES_SYMBOL_CIRCLE;
  SubClassSize = 1;
  SubClassColor = wxColour(255, 255, 255);
}

LayerObject::LayerObject(wxString & name, wxString & column, int srid,
                         int geom_type, bool multi_type)
{
//
// constructor - TreeItemData
//
  Type = VECTOR_LAYER;
  LayerView = false;
  LayerVirtual = false;
  ReadOnly = false;
  GeometryType = geom_type;
  MultiType = multi_type;
  TableName = name;
  GeometryColumn = column;
  Srid = srid;
  Network = false;
  Visible = true;
  Identify = true;
  EditingEnabled = false;
  Reproject = true;
  AlwaysVisible = true;
  MinScale = 0;
  MaxScale = 0;
  SymbolId = 1;
  ForegroundColor = wxColour(255, 255, 255);
  BackgroundColor = wxColour(0, 0, 0);
  LineColor = wxColour(0, 255, 128, 255);
  LineThickness = 1;
  LineStyle = wxSOLID;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = true;
  FillColor = wxColour(0, 128, 64);
  PatternId = 1;
  LabelColumn = wxT("");
  MapLabeling = false;
  LabelColor = wxColour(0, 0, 0);
  LabelPointSize = 10;
  LabelFontBold = false;
  LabelFontItalic = false;
  LabelFontUnderlined = false;
  LabelFontOutlined = false;
  LabelOrderByColumn = wxT("");
  LabelOrderByDescending = false;
  LabelAlwaysVisible = true;
  LabelMinScale = 0;
  LabelMaxScale = 0;
  LabelAntiOverlap = false;
  Default = false;
  IconIndex = -1;
  SubClasses = false;
  UniqueValue = false;
  NumClasses = 2;
  ClassesMinValue = 0.0;
  ClassesMaxValue = 0.0;
  ClassesSymbolType = CLASSES_SYMBOL_CIRCLE;
  ClassesMinSize = 1;
  ClassesMaxSize = 16;
  ClassesMinColor = wxColour(0, 0, 0);
  ClassesMaxColor = wxColour(255, 255, 255);
  SubClassUnique = false;
  SubClassText = false;
  SubClassTextValue = wxT("");
  SubClassNumValue = 0.0;
  SubClassMinValue = 0.0;
  SubClassMaxValue = 0.0;
  SubClassSymbolType = CLASSES_SYMBOL_CIRCLE;
  SubClassSize = 1;
  SubClassColor = wxColour(255, 255, 255);
}

LayerObject::LayerObject()
{
//
// constructor - TreeItemData
//
  Type = VECTOR_LAYER;
  LayerView = false;
  LayerVirtual = false;
  ReadOnly = false;
  GeometryType = -1;
  MultiType = false;
  TableName = wxT("");
  GeometryColumn = wxT("");
  Srid = -1;
  Network = false;
  Visible = true;
  Identify = true;
  EditingEnabled = false;
  Reproject = true;
  AlwaysVisible = true;
  MinScale = 0;
  MaxScale = 0;
  SymbolId = 1;
  ForegroundColor = wxColour(255, 255, 255);
  BackgroundColor = wxColour(0, 0, 0);
  LineColor = wxColour(0, 255, 128, 255);
  LineThickness = 1;
  LineStyle = wxSOLID;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = true;
  FillColor = wxColour(0, 128, 64);
  PatternId = 1;
  LabelColumn = wxT("");
  MapLabeling = false;
  LabelColor = wxColour(0, 0, 0);
  LabelPointSize = 10;
  LabelFontBold = false;
  LabelFontItalic = false;
  LabelFontUnderlined = false;
  LabelFontOutlined = false;
  LabelOrderByColumn = wxT("");
  LabelOrderByDescending = false;
  LabelAlwaysVisible = true;
  LabelMinScale = 0;
  LabelMaxScale = 0;
  LabelAntiOverlap = false;
  Default = false;
  IconIndex = -1;
  SubClasses = false;
  UniqueValue = false;
  NumClasses = 2;
  ClassesMinValue = 0.0;
  ClassesMaxValue = 0.0;
  ClassesSymbolType = CLASSES_SYMBOL_CIRCLE;
  ClassesMinSize = 1;
  ClassesMaxSize = 16;
  ClassesMinColor = wxColour(0, 0, 0);
  ClassesMaxColor = wxColour(255, 255, 255);
  SubClassUnique = false;
  SubClassText = false;
  SubClassTextValue = wxT("");
  SubClassNumValue = 0.0;
  SubClassMinValue = 0.0;
  SubClassMaxValue = 0.0;
  SubClassSymbolType = CLASSES_SYMBOL_CIRCLE;
  SubClassSize = 1;
  SubClassColor = wxColour(255, 255, 255);
}

LayerObject::LayerObject(SubClassObject * sub)
{
//
// constructor - TreeItemData
//
  Type = LAYER_SUB_CLASS;
  LayerView = false;
  LayerVirtual = false;
  ReadOnly = false;
  GeometryType = -1;
  MultiType = false;
  TableName = wxT("");
  GeometryColumn = wxT("");
  Srid = -1;
  Network = false;
  Visible = true;
  Identify = false;
  EditingEnabled = false;
  Reproject = false;
  AlwaysVisible = true;
  MinScale = 0;
  MaxScale = 0;
  SymbolId = 1;
  ForegroundColor = wxColour(255, 255, 255);
  BackgroundColor = wxColour(0, 0, 0);
  LineColor = wxColour(0, 255, 128, 255);
  LineThickness = 1;
  LineStyle = wxSOLID;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = true;
  FillColor = wxColour(0, 128, 64);
  PatternId = 1;
  LabelColumn = wxT("");
  MapLabeling = false;
  LabelColor = wxColour(0, 0, 0);
  LabelPointSize = 10;
  LabelFontBold = false;
  LabelFontItalic = false;
  LabelFontUnderlined = false;
  LabelFontOutlined = false;
  LabelOrderByColumn = wxT("");
  LabelOrderByDescending = false;
  LabelAlwaysVisible = true;
  LabelMinScale = 0;
  LabelMaxScale = 0;
  LabelAntiOverlap = false;
  Default = false;
  IconIndex = -1;
  SubClasses = false;
  UniqueValue = false;
  NumClasses = 2;
  ClassesMinValue = 0.0;
  ClassesMaxValue = 0.0;
  ClassesSymbolType = CLASSES_SYMBOL_CIRCLE;
  ClassesMinSize = 1;
  ClassesMaxSize = 16;
  ClassesMinColor = wxColour(0, 0, 0);
  ClassesMaxColor = wxColour(255, 255, 255);
  SubClassUnique = sub->IsUnique();
  SubClassText = sub->IsText();
  SubClassTextValue = sub->GetTextValue();
  SubClassNumValue = sub->GetNumValue();
  SubClassMinValue = sub->GetMinValue();
  SubClassMaxValue = sub->GetMaxValue();
  SubClassSymbolType = sub->GetSymbolType();
  SubClassSize = sub->GetSize();
  SubClassColor = sub->GetColor();
}

LayerObject::LayerObject(MyLayerSubClass * sub)
{
//
// constructor - TreeItemData
//
  Type = LAYER_SUB_CLASS;
  LayerView = false;
  LayerVirtual = false;
  ReadOnly = false;
  GeometryType = -1;
  MultiType = false;
  TableName = wxT("");
  GeometryColumn = wxT("");
  Srid = -1;
  Network = false;
  Visible = true;
  Identify = false;
  EditingEnabled = false;
  Reproject = false;
  AlwaysVisible = true;
  MinScale = 0;
  MaxScale = 0;
  SymbolId = 1;
  ForegroundColor = wxColour(255, 255, 255);
  BackgroundColor = wxColour(0, 0, 0);
  LineColor = wxColour(0, 255, 128, 255);
  LineThickness = 1;
  LineStyle = wxSOLID;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = true;
  FillColor = wxColour(0, 128, 64);
  PatternId = 1;
  LabelColumn = wxT("");
  MapLabeling = false;
  LabelColor = wxColour(0, 0, 0);
  LabelPointSize = 10;
  LabelFontBold = false;
  LabelFontItalic = false;
  LabelFontUnderlined = false;
  LabelFontOutlined = false;
  LabelOrderByColumn = wxT("");
  LabelOrderByDescending = false;
  LabelAlwaysVisible = true;
  LabelMinScale = 0;
  LabelMaxScale = 0;
  LabelAntiOverlap = false;
  Default = false;
  IconIndex = -1;
  SubClasses = false;
  UniqueValue = false;
  NumClasses = 2;
  ClassesMinValue = 0.0;
  ClassesMaxValue = 0.0;
  ClassesSymbolType = CLASSES_SYMBOL_CIRCLE;
  ClassesMinSize = 1;
  ClassesMaxSize = 16;
  ClassesMinColor = wxColour(0, 0, 0);
  ClassesMaxColor = wxColour(255, 255, 255);
  SubClassUnique = sub->IsUnique();
  SubClassText = sub->IsText();
  SubClassTextValue = sub->GetTextValue();
  SubClassNumValue = sub->GetNumValue();
  SubClassMinValue = sub->GetMinValue();
  SubClassMaxValue = sub->GetMaxValue();
  SubClassSymbolType = sub->GetSymbolType();
  SubClassSize = sub->GetSize();
  SubClassColor = sub->GetColor();
}

void LayerObject::Set(wxString & name, wxString & column, int srid,
                      int geom_type, bool multi_type, wxString & desc)
{
//
// constructor - TreeItemData
//
  Type = VECTOR_LAYER;
  LayerView = false;
  LayerVirtual = false;
  ReadOnly = false;
  GeometryType = geom_type;
  MultiType = multi_type;
  TableName = name;
  GeometryColumn = column;
  DescName = desc;
  Srid = srid;
  Network = false;
  Visible = true;
  Identify = true;
  EditingEnabled = false;
  Reproject = true;
  AlwaysVisible = true;
  MinScale = 0;
  MaxScale = 0;
  SymbolId = 1;
  ForegroundColor = wxColour(255, 255, 255);
  BackgroundColor = wxColour(0, 0, 0);
  LineColor = wxColour(0, 255, 128, 255);
  LineThickness = 1;
  LineStyle = wxSOLID;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = true;
  FillColor = wxColour(0, 128, 64);
  PatternId = 1;
  LabelColumn = wxT("");
  MapLabeling = false;
  LabelColor = wxColour(0, 0, 0);
  LabelPointSize = 10;
  LabelFontBold = false;
  LabelFontItalic = false;
  LabelFontUnderlined = false;
  LabelFontOutlined = false;
  LabelOrderByColumn = wxT("");
  LabelOrderByDescending = false;
  LabelAlwaysVisible = true;
  LabelMinScale = 0;
  LabelMaxScale = 0;
  LabelAntiOverlap = false;
  Default = false;
  IconIndex = -1;
  SubClasses = false;
  UniqueValue = false;
  NumClasses = 2;
  ClassesMinValue = 0.0;
  ClassesMaxValue = 0.0;
  ClassesSymbolType = CLASSES_SYMBOL_CIRCLE;
  ClassesMinSize = 1;
  ClassesMaxSize = 16;
  ClassesMinColor = wxColour(0, 0, 0);
  ClassesMaxColor = wxColour(255, 255, 255);
  SubClassUnique = false;
  SubClassText = false;
  SubClassTextValue = wxT("");
  SubClassNumValue = 0.0;
  SubClassMinValue = 0.0;
  SubClassMaxValue = 0.0;
  SubClassSymbolType = CLASSES_SYMBOL_CIRCLE;
  SubClassSize = 1;
  SubClassColor = wxColour(255, 255, 255);
}

void LayerObject::UpdateDefault(LayerObject * org)
{
//
// updating the Default element
//
  this->Type = org->Type;
  this->LayerView = org->LayerView;
  this->LayerVirtual = org->LayerVirtual;
  this->ReadOnly = org->ReadOnly;
  this->GeometryType = org->GeometryType;
  this->MultiType = org->MultiType;
  this->TableName = org->TableName;
  this->GeometryColumn = org->GeometryColumn;
  this->DescName = org->DescName;
  this->Srid = org->Srid;
  this->Network = org->Network;
  this->Visible = org->Visible;
  this->Identify = org->Identify;
  this->EditingEnabled = false;
  this->Reproject = org->Reproject;
  this->AlwaysVisible = org->AlwaysVisible;
  this->MinScale = org->MinScale;
  this->MaxScale = org->MaxScale;
  this->SymbolId = org->SymbolId;
  this->ForegroundColor = org->ForegroundColor;
  this->BackgroundColor = org->BackgroundColor;
  this->LineColor = org->LineColor;
  this->LineThickness = org->LineThickness;
  this->LineStyle = org->LineStyle;
  this->DrawBorder = org->DrawBorder;
  this->ToFill = org->ToFill;
  this->SolidFilling = org->SolidFilling;
  this->FillColor = org->FillColor;
  this->PatternId = org->PatternId;
  this->LabelColumn = org->LabelColumn;
  this->MapLabeling = org->MapLabeling;
  this->LabelColor = org->LabelColor;
  this->LabelPointSize = org->LabelPointSize;
  this->LabelFontBold = org->LabelFontBold;
  this->LabelFontItalic = org->LabelFontItalic;
  this->LabelFontUnderlined = org->LabelFontUnderlined;
  this->LabelFontOutlined = org->LabelFontOutlined;
  this->LabelOrderByColumn = org->LabelOrderByColumn;
  this->LabelOrderByDescending = org->LabelOrderByDescending;
  this->LabelAlwaysVisible = org->LabelAlwaysVisible;
  this->LabelMinScale = org->LabelMinScale;
  this->LabelMaxScale = org->LabelMaxScale;
  this->LabelAntiOverlap = org->LabelAntiOverlap;
  this->Default = true;
  this->SubClasses = org->SubClasses;
  this->ClassifyColumn = org->ClassifyColumn;
  this->UniqueValue = org->UniqueValue;
  this->NumClasses = org->NumClasses;
  this->ClassesMinValue = org->ClassesMinValue;
  this->ClassesMaxValue = org->ClassesMaxValue;
  this->ClassesSymbolType = org->ClassesSymbolType;
  this->ClassesMinSize = org->ClassesMinSize;
  this->ClassesMaxSize = org->ClassesMaxSize;
  this->ClassesMinColor = org->ClassesMinColor;
  this->ClassesMaxColor = org->ClassesMaxColor;
  this->SubClassUnique = org->SubClassUnique;
  this->SubClassText = org->SubClassText;
  this->SubClassTextValue = org->SubClassTextValue;
  this->SubClassNumValue = org->SubClassNumValue;
  this->SubClassMinValue = org->SubClassMinValue;
  this->SubClassMaxValue = org->SubClassMaxValue;
  this->SubClassSymbolType = org->SubClassSymbolType;
  this->SubClassSize = org->SubClassSize;
  this->SubClassColor = org->SubClassColor;
}

void LayerObject::DisableMapLabeling()
{
// disabling Map Labeling
  MapLabeling = false;
  LabelColor = wxColour(0, 0, 0);
  LabelPointSize = 10;
  LabelFontBold = false;
  LabelFontItalic = false;
  LabelFontUnderlined = false;
  LabelFontOutlined = false;
  LabelOrderByColumn = wxT("");
  LabelOrderByDescending = false;
  LabelAlwaysVisible = true;
  LabelMinScale = 0;
  LabelMaxScale = 0;
  LabelAntiOverlap = false;
}

void LayerObject::EnableMapLabeling(wxColour & color, int size, bool fontBold,
                                    bool fontItalic, bool fontUnderlined,
                                    bool fontOutlined, wxString & column,
                                    bool desc, bool overlap)
{
// enabling Map Labeling
  MapLabeling = true;
  LabelColor = color;
  LabelPointSize = size;
  LabelFontBold = fontBold;
  LabelFontItalic = fontItalic;
  LabelFontUnderlined = fontUnderlined;
  LabelFontOutlined = fontOutlined;
  LabelOrderByColumn = column;
  LabelOrderByDescending = desc;
  LabelAntiOverlap = overlap;
}

void LayerObject::PrepareStaticValues()
{
// preparing the static values to be serialized into the DB
  char dummy[64];
  sprintf(dummy, "%02x%02x%02x%02x", ForegroundColor.Red(),
          ForegroundColor.Green(), ForegroundColor.Blue(),
          ForegroundColor.Alpha());
  ForegroundColorAsRGBA = wxString::FromUTF8(dummy);
  sprintf(dummy, "%02x%02x%02x%02x", BackgroundColor.Red(),
          BackgroundColor.Green(), BackgroundColor.Blue(),
          BackgroundColor.Alpha());
  BackgroundColorAsRGBA = wxString::FromUTF8(dummy);
  sprintf(dummy, "%02x%02x%02x%02x", LineColor.Red(), LineColor.Green(),
          LineColor.Blue(), LineColor.Alpha());
  LineColorAsRGBA = wxString::FromUTF8(dummy);
  sprintf(dummy, "%02x%02x%02x%02x", FillColor.Red(), FillColor.Green(),
          FillColor.Blue(), FillColor.Alpha());
  FillColorAsRGBA = wxString::FromUTF8(dummy);
  if (LineStyle == wxDOT)
    LineStyleAsConstant = wxT("DOT");
  else if (LineStyle == wxLONG_DASH)
    LineStyleAsConstant = wxT("LONG_DASH");
  else if (LineStyle == wxSHORT_DASH)
    LineStyleAsConstant = wxT("SHORT_DASH");
  else if (LineStyle == wxDOT_DASH)
    LineStyleAsConstant = wxT("DOT_DASH");
  else
    LineStyleAsConstant = wxT("SOLID");
  sprintf(dummy, "%02x%02x%02x%02x", LabelColor.Red(), LabelColor.Green(),
          LabelColor.Blue(), LabelColor.Alpha());
  LabelColorAsRGBA = wxString::FromUTF8(dummy);
  if (LabelFontBold == true)
    LabelFontWeight = wxT("BOLD");
  else
    LabelFontWeight = wxT("NORMAL");
  if (LabelFontItalic == true)
    LabelFontStyle = wxT("ITALIC");
  else
    LabelFontStyle = wxT("NORMAL");
}

void LayerObject::PrepareStaticClassesValues()
{
// preparing the static values to be serialized into the DB
  char dummy[64];
  sprintf(dummy, "%02x%02x%02x%02x", ClassesMinColor.Red(),
          ClassesMinColor.Green(), ClassesMinColor.Blue(), 255);
  ClassesMinColorAsRGBA = wxString::FromUTF8(dummy);
  sprintf(dummy, "%02x%02x%02x%02x", ClassesMaxColor.Red(),
          ClassesMaxColor.Green(), ClassesMaxColor.Blue(), 255);
  ClassesMaxColorAsRGBA = wxString::FromUTF8(dummy);
  if (ClassesSymbolType == CLASSES_SYMBOL_SQUARE)
    SymbolTypeAsConstant = wxT("SQUARE");
  else if (ClassesSymbolType == CLASSES_SYMBOL_DIAMOND)
    SymbolTypeAsConstant = wxT("DIAMOND");
  else
    SymbolTypeAsConstant = wxT("CIRCLE");
}

void LayerObject::SetPointGraphics(int symbolId)
{
//
// setting a FullColor Symbol POINT graphics
//
  SymbolId = symbolId;
  ForegroundColor = wxColour(255, 255, 255, 255);
  BackgroundColor = wxColour(0, 0, 0, 255);
}

void LayerObject::SetPointGraphics(int symbolId, wxColour & foreground,
                                   wxColour & background)
{
//
// setting a Bicolor Symbol POINT graphics
//
  SymbolId = symbolId;
  ForegroundColor = foreground;
  BackgroundColor = background;
}

void LayerObject::SetLineGraphics(wxColour & color, int thickness, int style)
{
//
// setting LINE graphics
//
  LineColor = color;
  LineThickness = thickness;
  LineStyle = style;
}

void LayerObject::SetPolygonGraphics(wxColour & borderColor, int thickness,
                                     int style)
{
//
// setting POLYGON graphics - border, no interior filling
  DrawBorder = true;
  LineColor = borderColor;
  LineThickness = thickness;
  LineStyle = style;
  ToFill = false;
}

void LayerObject::SetPolygonGraphics(wxColour & fillColor)
{
// setting POLYGON graphics - no border, solid color filling
  DrawBorder = false;
  ToFill = true;
  SolidFilling = true;
  FillColor = wxColour(fillColor.Red(), fillColor.Green(), fillColor.Blue());
}

void LayerObject::SetPolygonGraphics(wxColour & borderColor, int thickness,
                                     int style, wxColour & fillColor)
{
// setting POLYGON graphics - border and solid color interior filling
  DrawBorder = true;
  LineColor = borderColor;
  LineThickness = thickness;
  LineStyle = style;
  ToFill = true;
  SolidFilling = true;
  PatternId = 1;
  FillColor = fillColor;
}

void LayerObject::SetPolygonGraphics(int patternId, wxColour & fillColor)
{
// setting POLYGON graphics - no border, pattern filling
  DrawBorder = false;
  ToFill = true;
  SolidFilling = false;
  PatternId = patternId;
  FillColor = fillColor;
}

void LayerObject::SetPolygonGraphics(wxColour & borderColor, int thickness,
                                     int style, int patternId,
                                     wxColour & fillColor)
{
// setting POLYGON graphics - border and pattern filling
  DrawBorder = true;
  LineColor = borderColor;
  LineThickness = thickness;
  LineStyle = style;
  ToFill = true;
  SolidFilling = false;
  PatternId = patternId;
  FillColor = fillColor;
}

void LayerObject::SetClassifyParams(wxString & column, bool unique,
                                    int numClasses, double minValue,
                                    double maxValue, int symbolType,
                                    int minSize, int maxSize,
                                    wxColour & minColor, wxColour & maxColor)
{
// setting SubClasses main params
  SubClasses = true;
  ClassifyColumn = column;
  UniqueValue = unique;
  NumClasses = numClasses;
  ClassesMinValue = minValue;
  ClassesMaxValue = maxValue;
  ClassesSymbolType = symbolType;
  ClassesMinSize = minSize;
  ClassesMaxSize = maxSize;
  ClassesMinColor = minColor;
  ClassesMaxColor = maxColor;
}

void LayerObject::ClearClassifyParams()
{
// setting SubClasses main params
  SubClasses = false;
  ClassifyColumn = wxT("");
  UniqueValue = false;
  NumClasses = 2;
  ClassesMinValue = 0.0;
  ClassesMaxValue = 0.0;
  ClassesSymbolType = CLASSES_SYMBOL_CIRCLE;
  ClassesMinSize = 1;
  ClassesMaxSize = 16;
  ClassesMinColor = wxColour(0, 0, 0);
  ClassesMaxColor = wxColour(255, 255, 255);
}

int LayerObject::AddLayerIcon(wxImageList * list, int width, int height,
                              MyImageList * symbols, MyImageList * patterns)
{
//
// creating the Layer Icons and inserting into the ImageList
//
  wxBitmap bmp(width, height);
  wxMemoryDC *bmp_dc = new wxMemoryDC(bmp);
  bmp_dc->SetPen(wxColour(255, 255, 255));
  bmp_dc->SetBrush(wxColour(255, 255, 255));
  bmp_dc->DrawRectangle(0, 0, width, height);
  if (GeometryType == LAYER_POINT)
    DrawPointLayerIcon(bmp_dc, width, height, symbols);
  if (GeometryType == LAYER_LINESTRING)
    DrawLinestringLayerIcon(bmp_dc, width, height);
  if (GeometryType == LAYER_POLYGON)
    DrawPolygonLayerIcon(bmp_dc, width, height, patterns);
  bmp_dc->SetPen(wxNullPen);
  bmp_dc->SetBrush(wxNullBrush);
  delete bmp_dc;
  IconIndex = list->Add(bmp, wxColour(255, 255, 255));
  return IconIndex;
}

int LayerObject::AddSubClassIcon(wxImageList * list, int width, int height,
                                 int geometryType)
{
//
// creating the SubClass Icons and inserting into the ImageList
//
  wxBitmap bmp(width, height);
  wxMemoryDC *bmp_dc = new wxMemoryDC(bmp);
  bmp_dc->SetPen(wxColour(255, 255, 255));
  bmp_dc->SetBrush(wxColour(255, 255, 255));
  bmp_dc->DrawRectangle(0, 0, width, height);
  if (geometryType == LAYER_POINT)
    DrawPointSubClassIcon(bmp_dc, width, height);
  if (geometryType == LAYER_LINESTRING)
    DrawLinestringSubClassIcon(bmp_dc, width, height);
  if (geometryType == LAYER_POLYGON)
    DrawPolygonSubClassIcon(bmp_dc, width, height);
  bmp_dc->SetPen(wxNullPen);
  bmp_dc->SetBrush(wxNullBrush);
  delete bmp_dc;
  IconIndex = list->Add(bmp, wxColour(255, 255, 255));
  return IconIndex;
}

void LayerObject::UpdateLayerIcon(wxImageList * list, int width, int height,
                                  MyImageList * symbols, MyImageList * patterns)
{
//
// updating the Layer Icons and replacing into the ImageList
//
  wxBitmap bmp(width, height);
  wxMemoryDC *bmp_dc = new wxMemoryDC(bmp);
  bmp_dc->SetPen(wxColour(255, 255, 255));
  bmp_dc->SetBrush(wxColour(255, 255, 255));
  bmp_dc->DrawRectangle(0, 0, width, height);
  if (GeometryType == LAYER_POINT)
    DrawPointLayerIcon(bmp_dc, width, height, symbols);
  if (GeometryType == LAYER_LINESTRING)
    DrawLinestringLayerIcon(bmp_dc, width, height);
  if (GeometryType == LAYER_POLYGON)
    DrawPolygonLayerIcon(bmp_dc, width, height, patterns);
  bmp_dc->SetPen(wxNullPen);
  bmp_dc->SetBrush(wxNullBrush);
  delete bmp_dc;
  list->Replace(IconIndex, bmp);
}

void LayerObject::DrawPointLayerIcon(wxMemoryDC * dc, int width,
                                     int height, MyImageList * symbols)
{
// creating a POINT Layer Icons
  int x;
  int y;
  MyBitmap *symbol = symbols->FindById(SymbolId);
  if (symbol == NULL)
    {
      // drawing a default marker
      dc->SetPen(wxColour(0, 255, 0));
      dc->SetBrush(wxBrush(wxColour(255, 0, 0)));
      dc->DrawEllipse(width / 2, height / 2, 4, 4);
  } else
    {
      // drawing the symbol
      wxBitmap bmp;
      symbol->GetBitmap(bmp, ForegroundColor, BackgroundColor);
      wxMask *mask = new wxMask(symbol->GetMask());
      bmp.SetMask(mask);
      x = (width - bmp.GetWidth()) / 2;
      y = (height - bmp.GetHeight()) / 2;
      dc->DrawBitmap(bmp, x, y, true);
    }
}

void LayerObject::DrawLinestringLayerIcon(wxMemoryDC * dc, int width,
                                          int height)
{
// creating a LINESTRING Layer Icon
  wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
  gr->SetPen(wxPen(wxColour(192, 192, 192), LineThickness, LineStyle));
  gr->StrokeLine(4, height / 2, width - 4, height / 2);
  gr->SetPen(wxPen(LineColor, LineThickness, LineStyle));
  gr->StrokeLine(4, height / 2, width - 4, height / 2);
  delete gr;
}

void LayerObject::DrawPolygonLayerIcon(wxMemoryDC * dc, int width, int height,
                                       MyImageList * patterns)
{
// creating a POLYGON Layer Icon
  MyBitmap *pattern = patterns->FindById(PatternId);
  wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
  wxGraphicsPath path = gr->CreatePath();
  path.MoveToPoint(2, 2);
  path.AddLineToPoint(width - 2, 2);
  path.AddLineToPoint(width - 2, height - 2);
  path.AddLineToPoint(2, height - 2);
  path.AddLineToPoint(2, 2);
  if (ToFill == true)
    {
      if (SolidFilling == true)
        {
          gr->SetBrush(wxBrush(FillColor));
          gr->FillPath(path);
      } else
        {
          if (pattern)
            {
              wxBitmap bmp;
              pattern->GetBitmap(bmp, FillColor);
              wxMask *mask = new wxMask(pattern->GetMask());
              bmp.SetMask(mask);
              wxBrush brush(bmp);
              gr->SetBrush(brush);
              gr->FillPath(path);
            }
        }
    }
  if (DrawBorder == true)
    {
      gr->SetPen(wxPen(wxColour(192, 192, 192), LineThickness, LineStyle));
      gr->StrokePath(path);
      gr->SetPen(wxPen(LineColor, LineThickness, LineStyle));
      gr->StrokePath(path);
    }
  delete gr;
}

void LayerObject::DrawPointSubClassIcon(wxMemoryDC * dc, int width, int height)
{
// creating a POINT SubClass Icons
  int x = width / 2;
  int y = height / 2;
  int pen_r = 255 - SubClassColor.Red();
  int pen_g = 255 - SubClassColor.Green();
  int pen_b = 255 - SubClassColor.Blue();
  dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
  dc->SetBrush(wxBrush(SubClassColor));
  if (SubClassSymbolType == CLASSES_SYMBOL_SQUARE)
    dc->DrawRectangle(x - SubClassSize, y - SubClassSize, SubClassSize * 2,
                      SubClassSize * 2);
  else if (SubClassSymbolType == CLASSES_SYMBOL_DIAMOND)
    {
      wxPoint points[5];
      points[0].x = x;
      points[0].y = y - SubClassSize;
      points[1].x = x + SubClassSize;
      points[1].y = y;
      points[2].x = x;
      points[2].y = y + SubClassSize;
      points[3].x = x - SubClassSize;
      points[3].y = y;
      points[4].x = x;
      points[4].y = y - SubClassSize;
      dc->DrawPolygon(5, points);
  } else
    dc->DrawCircle(x, y, SubClassSize);
  if ((SubClassSize * 2) >= height || (SubClassSize * 2) >= width)
    {
      dc->SetPen(wxPen(wxColour(255, 192, 192)));
      dc->SetBrush(*wxTRANSPARENT_BRUSH);
      dc->DrawRectangle(0, 0, width, height);
    }
}

void LayerObject::DrawLinestringSubClassIcon(wxMemoryDC * dc, int width,
                                             int height)
{
// creating a LINESTRING SubClass Icon
  int pen_r = 255 - SubClassColor.Red();
  int pen_g = 255 - SubClassColor.Green();
  int pen_b = 255 - SubClassColor.Blue();
  wxPen pen(SubClassColor, SubClassSize);
  pen.SetCap(wxCAP_BUTT);
  dc->SetPen(pen);
  dc->DrawLine(4, height / 2, width - 4, height / 2);
  if (SubClassSize >= height || SubClassSize >= width)
    {
      dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
      dc->SetBrush(*wxTRANSPARENT_BRUSH);
      dc->DrawRectangle(0, 0, width, height);
    }
}

void LayerObject::DrawPolygonSubClassIcon(wxMemoryDC * dc, int width,
                                          int height)
{
// creating a POLYGON SubClass Icon
  int pen_r = 255 - SubClassColor.Red();
  int pen_g = 255 - SubClassColor.Green();
  int pen_b = 255 - SubClassColor.Blue();
  dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
  dc->SetBrush(wxBrush(SubClassColor));
  wxPoint points[5];
  points[0].x = 2;
  points[0].y = 2;
  points[1].x = width - 2;
  points[1].y = 2;
  points[2].x = width - 2;
  points[2].y = height - 2;
  points[3].x = 2;
  points[3].y = height - 2;
  points[4].x = 2;
  points[4].y = 2;
  dc->DrawPolygon(5, points);
}

wxString & LayerObject::GetSubClassString()
{
// preparing the Tree Item Label
  char buf[128];
  int ind;
  SubClassString = wxT("???");
  if (SubClassUnique == true)
    {
      if (SubClassText == true)
        return SubClassTextValue;
      sprintf(buf, "%1.6f", SubClassNumValue);
      for (ind = strlen(buf) - 1; ind > 0; ind--)
        {
          if (buf[ind] == '0')
            buf[ind] = '\0';
          else
            break;
        }
      if (buf[strlen(buf) - 1] == '.')
        buf[strlen(buf) - 1] = '\0';
      if (strlen(buf) == 0)
        strcpy(buf, "0");
      SubClassString = wxString::FromUTF8(buf);
  } else
    {
      if (fabs(SubClassMinValue) >= 100.0)
        sprintf(buf, "%1.1f", SubClassMinValue);
      else if (fabs(SubClassMinValue) >= 10.0)
        sprintf(buf, "%1.2f", SubClassMinValue);
      else if (fabs(SubClassMinValue) >= 1.0)
        sprintf(buf, "%1.3f", SubClassMinValue);
      else
        sprintf(buf, "%1.6f", SubClassMinValue);
      for (ind = strlen(buf) - 1; ind > 0; ind--)
        {
          if (buf[ind] == '0')
            buf[ind] = '\0';
          else
            break;
        }
      if (buf[strlen(buf) - 1] == '.')
        buf[strlen(buf) - 1] = '\0';
      if (strlen(buf) == 0)
        strcpy(buf, "0");
      SubClassString = wxString::FromUTF8(buf);
      SubClassString += wxT(" / ");
      if (fabs(SubClassMaxValue) >= 100.0)
        sprintf(buf, "%1.1f", SubClassMaxValue);
      else if (fabs(SubClassMaxValue) >= 10.0)
        sprintf(buf, "%1.2f", SubClassMaxValue);
      else if (fabs(SubClassMaxValue) >= 1.0)
        sprintf(buf, "%1.3f", SubClassMaxValue);
      else
        sprintf(buf, "%1.6f", SubClassMaxValue);
      for (ind = strlen(buf) - 1; ind > 0; ind--)
        {
          if (buf[ind] == '0')
            buf[ind] = '\0';
          else
            break;
        }
      if (buf[strlen(buf) - 1] == '.')
        buf[strlen(buf) - 1] = '\0';
      if (strlen(buf) == 0)
        strcpy(buf, "0");
      SubClassString += wxString::FromUTF8(buf);
    }
  return SubClassString;
}

SridInfo::SridInfo()
{
//
// empty constructor - Srid Infos
//
  Srid = -1;
  AuthSrid = -1;
  Geographic = false;
  Dms = false;
}

SridInfo::SridInfo(int srid)
{
//
// constructor - Srid Infos
//
  Srid = srid;
  AuthSrid = -1;
  Geographic = false;
  Dms = false;
}

SridInfo::SridInfo(SridInfo * org)
{
//
// constructor - Srid Infos
//
  this->Srid = org->Srid;
  this->AuthName = org->AuthName;
  this->AuthSrid = org->AuthSrid;
  this->SridName = org->SridName;
  this->Params = org->Params;
  this->Geographic = org->Geographic;
  this->UnitName = org->UnitName;
  this->Dms = org->Dms;
}

void SridInfo::Set(int srid, wxString & authName, int authSrid, wxString & name,
                   wxString & params)
{
//
// setting values for Srid Info
//
  Srid = srid;
  AuthName = authName;
  AuthSrid = authSrid;
  SridName = name;
  Params = params;
  ParseUnit();
}

void SridInfo::ParseUnit()
{
//
// trying to retrieve the Unit Name
//
  wxStringTokenizer tokenizer(Params, wxT(" "));
  while (tokenizer.HasMoreTokens())
    {
      wxString token = tokenizer.GetNextToken();
      if (token == wxT("+proj=longlat"))
        {
          UnitName = wxT("degrees");
          Geographic = true;
          Dms = true;
          ParseEllipsoid();
          return;
        }
      wxString unit;
      if (token.StartsWith(wxT("+units="), &unit) == true)
        {
          UnitName = unit;
          Geographic = false;
          Dms = false;
          return;
        }
    }
  UnitName = wxT("?");
  Geographic = false;
  Dms = false;
}

void SridInfo::ParseEllipsoid()
{
//
// trying to retrieve the Ellipsoid Name
//
  wxStringTokenizer tokenizer(Params, wxT(" "));
  while (tokenizer.HasMoreTokens())
    {
      wxString token = tokenizer.GetNextToken();
      wxString ellps;
      if (token.StartsWith(wxT("+ellps="), &ellps) == true)
        {
          Ellipsoid = ellps;
          return;
        }
    }
  Ellipsoid = wxT("");
}

MyBitmap::MyBitmap(MyBitmap * org)
{
//
// constructor - COPY
//
  wxBitmap bmp;
  this->Id = org->Id;
  this->FullColor = org->FullColor;
  this->HotPointX = org->HotPointX;
  this->HotPointY = org->HotPointY;
  bmp = org->GetBitmap();
  this->Bitmap =
    bmp.GetSubBitmap(wxRect(0, 0, bmp.GetWidth(), bmp.GetHeight()));
  bmp = org->GetMask();
  this->Mask = bmp.GetSubBitmap(wxRect(0, 0, bmp.GetWidth(), bmp.GetHeight()));
  this->ListId = -1;
  Next = NULL;
}

MyBitmap::MyBitmap(MyBitmap * org, wxColour & foreground, wxColour & background)
{
//
// constructor - COPY
//
  wxBitmap bmp;
  int blob_size;
  unsigned char *blob;
  unsigned char *p_blob;
  int row;
  int col;
  this->Id = org->Id;
  this->FullColor = org->FullColor;
  this->HotPointX = org->HotPointX;
  this->HotPointY = org->HotPointY;
  bmp = org->GetBitmap().GetSubBitmap(wxRect(0, 0, org->GetBitmap().GetWidth(),
                                             org->GetBitmap().GetHeight()));
  wxMask *mask = new wxMask(org->GetMask());
  bmp.SetMask(mask);
  wxImage img = bmp.ConvertToImage();
  blob_size = bmp.GetWidth() * bmp.GetHeight() * 4;
  blob = (unsigned char *) malloc(blob_size);
  p_blob = blob;
  for (row = 0; row < img.GetHeight(); row++)
    {
      for (col = 0; col < img.GetWidth(); col++)
        {
          if (img.IsTransparent(col, row) == true)
            {
              *(p_blob++) = img.GetRed(col, row);
              *(p_blob++) = img.GetGreen(col, row);
              *(p_blob++) = img.GetBlue(col, row);
              *(p_blob++) = 0x00;
          } else
            {
              *(p_blob++) = img.GetRed(col, row);
              *(p_blob++) = img.GetGreen(col, row);
              *(p_blob++) = img.GetBlue(col, row);
              *(p_blob++) = 0xff;
            }
        }
    }
  BuildBitmap(bmp.GetWidth(), bmp.GetHeight(), blob, foreground, background);
  BuildMask(bmp.GetWidth(), bmp.GetHeight(), blob);
  free(blob);
  this->ListId = -1;
  Next = NULL;
}

MyBitmap::MyBitmap(MyBitmap * org, wxColour & color)
{
//
// constructor - COPY
//
  wxBitmap bmp;
  int blob_size;
  unsigned char *blob;
  unsigned char *p_blob;
  int row;
  int col;
  this->Id = org->Id;
  this->FullColor = org->FullColor;
  this->HotPointX = org->HotPointX;
  this->HotPointY = org->HotPointY;
  bmp = org->GetBitmap().GetSubBitmap(wxRect(0, 0, org->GetBitmap().GetWidth(),
                                             org->GetBitmap().GetHeight()));
  wxMask *mask = new wxMask(org->GetMask());
  bmp.SetMask(mask);
  wxImage img = bmp.ConvertToImage();
  blob_size = bmp.GetWidth() * bmp.GetHeight() * 4;
  blob = (unsigned char *) malloc(blob_size);
  p_blob = blob;
  for (row = 0; row < img.GetHeight(); row++)
    {
      for (col = 0; col < img.GetWidth(); col++)
        {
          if (img.IsTransparent(col, row) == true)
            {
              *(p_blob++) = img.GetRed(col, row);
              *(p_blob++) = img.GetGreen(col, row);
              *(p_blob++) = img.GetBlue(col, row);
              *(p_blob++) = 0x00;
          } else
            {
              *(p_blob++) = img.GetRed(col, row);
              *(p_blob++) = img.GetGreen(col, row);
              *(p_blob++) = img.GetBlue(col, row);
              *(p_blob++) = 0xff;
            }
        }
    }
  BuildBitmap(bmp.GetWidth(), bmp.GetHeight(), blob, color);
  BuildMask(bmp.GetWidth(), bmp.GetHeight(), blob);
  free(blob);
  this->ListId = -1;
  Next = NULL;
}

MyBitmap::MyBitmap(int id, int width, int height, unsigned char *blob,
                   int hot_x, int hot_y, wxColour & foreground,
                   wxColour & background)
{
//
// constructor - Bicolor Symbol
//
  Id = id;
  FullColor = false;
  HotPointX = hot_x;
  HotPointY = hot_y;
  BuildBitmap(width, height, blob, foreground, background);
  BuildMask(width, height, blob);
  ListId = -1;
  Next = NULL;
}

MyBitmap::MyBitmap(int id, int width, int height, unsigned char *blob,
                   int hot_x, int hot_y)
{
//
// constructor - FullColor Symbol
//
  Id = id;
  FullColor = true;
  HotPointX = hot_x;
  HotPointY = hot_y;
  BuildBitmap(width, height, blob);
  BuildMask(width, height, blob);
  ListId = -1;
  Next = NULL;
}

MyBitmap::MyBitmap(int id, int width, int height, unsigned char *blob,
                   wxColour & color)
{
//
// constructor - Monocolor Pattern
//
  Id = id;
  FullColor = false;
  HotPointX = 0;
  HotPointY = 0;
  BuildBitmap(width, height, blob, color);
  BuildMask(width, height, blob);
  ListId = -1;
  Next = NULL;
}

MyBitmap::MyBitmap(int id, int width, int height, unsigned char *blob)
{
//
// constructor - FullColor Pattern
//
  Id = id;
  FullColor = true;
  HotPointX = 0;
  HotPointY = 0;
  BuildBitmap(width, height, blob);
  BuildMask(width, height, blob);
  ListId = -1;
  Next = NULL;
}

void MyBitmap::BuildMask(int width, int height, unsigned char *blob)
{
// building the mask
  wxImage img;
  int row;
  int col;
#ifdef __WXMAC__
  int transparent = 255;
  int opaque = 0;
#else
  int transparent = 0;
  int opaque = 255;
#endif
  unsigned char *data = (unsigned char *) malloc(width * height * 3);
  unsigned char *p_out = data;
  unsigned char *p_in = blob;
  for (row = 0; row < height; row++)
    {
      for (col = 0; col < width; col++)
        {
          p_in += 3;            // skipping RGB
          if (*(p_in++) < 128)
            {
              // transparent pixel
              *(p_out++) = transparent;
              *(p_out++) = transparent;
              *(p_out++) = transparent;
          } else
            {
              // opaque pixel
              *(p_out++) = opaque;
              *(p_out++) = opaque;
              *(p_out++) = opaque;
            }
        }
    }
  img = wxImage(width, height, data);
  Mask = wxBitmap(img, 1);
}

void MyBitmap::BuildBitmap(int width, int height, unsigned char *blob)
{
// building the bitmap [FullColor]
  wxImage img;
  int row;
  int col;
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char *data = (unsigned char *) malloc(width * height * 3);
  unsigned char *p_out = data;
  unsigned char *p_in = blob;
  for (row = 0; row < height; row++)
    {
      for (col = 0; col < width; col++)
        {
          r = *(p_in++);
          g = *(p_in++);
          b = *(p_in++);
          p_in++;               // skipping ALPHA
          *(p_out++) = r;
          *(p_out++) = g;
          *(p_out++) = b;
        }
    }
  img = wxImage(width, height, data);
  Bitmap = wxBitmap(img);
}

void MyBitmap::BuildBitmap(int width, int height, unsigned char *blob,
                           wxColour & foreground, wxColour & background)
{
// building the bitmap [BiColor]
  wxImage img;
  int row;
  int col;
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char fr = foreground.Red();
  unsigned char fg = foreground.Green();
  unsigned char fb = foreground.Blue();
  unsigned char br = background.Red();
  unsigned char bg = background.Green();
  unsigned char bb = background.Blue();
  bool is_foreground;
  unsigned char *data = (unsigned char *) malloc(width * height * 3);
  unsigned char *p_out = data;
  unsigned char *p_in = blob;
  for (row = 0; row < height; row++)
    {
      for (col = 0; col < width; col++)
        {
          r = *(p_in++);
          g = *(p_in++);
          b = *(p_in++);
          p_in++;               // skipping ALPHA
          if (r < 128 && g < 128 && b < 128)
            is_foreground = true;
          else
            is_foreground = false;
          if (is_foreground == true)
            {
              // setting the foreground color to this pixel
              *(p_out++) = fr;
              *(p_out++) = fg;
              *(p_out++) = fb;
          } else
            {
              // setting the background color to this pixel
              *(p_out++) = br;
              *(p_out++) = bg;
              *(p_out++) = bb;
            }
        }
    }
  img = wxImage(width, height, data);
  Bitmap = wxBitmap(img);
}

void MyBitmap::BuildBitmap(int width, int height, unsigned char *blob,
                           wxColour & color)
{
// building the bitmap [MonoColor]
  wxImage img;
  int row;
  int col;
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char cr = color.Red();
  unsigned char cg = color.Green();
  unsigned char cb = color.Blue();
  unsigned char *data = (unsigned char *) malloc(width * height * 3);
  unsigned char *p_out = data;
  unsigned char *p_in = blob;
  bool is_foreground;
  for (row = 0; row < height; row++)
    {
      for (col = 0; col < width; col++)
        {
          r = *(p_in++);
          g = *(p_in++);
          b = *(p_in++);
          p_in++;               // skipping ALPHA
          if (r < 128 && g < 128 && b < 128)
            is_foreground = true;
          else
            is_foreground = false;
          if (is_foreground == true)
            {
              // setting the foreground color to this pixel
              *(p_out++) = cr;
              *(p_out++) = cg;
              *(p_out++) = cb;
          } else
            {
              // setting the background color to this pixel
              *(p_out++) = 255;
              *(p_out++) = 255;
              *(p_out++) = 255;
            }
        }
    }
  img = wxImage(width, height, data);
  Bitmap = wxBitmap(img, 1);
}

void MyBitmap::GetBitmap(wxBitmap & bitmap, wxColour & foreground,
                         wxColour & background)
{
//
// builds the effective bitmap
//
  wxImage img;
  wxImage orgImg = Bitmap.ConvertToImage();
  int row;
  int col;
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char fr = foreground.Red();
  unsigned char fg = foreground.Green();
  unsigned char fb = foreground.Blue();
  unsigned char br = background.Red();
  unsigned char bg = background.Green();
  unsigned char bb = background.Blue();
  bool is_foreground;
  unsigned char *data;
  unsigned char *p_out;
  if (FullColor == true)
    {
      // FullColor; simply using the plain bitmap
      bitmap = Bitmap;
      return;
    }
// Bicolor; we need to adjust colors
  data = (unsigned char *) malloc(Bitmap.GetWidth() * Bitmap.GetHeight() * 3);
  p_out = data;
  for (row = 0; row < Bitmap.GetHeight(); row++)
    {
      for (col = 0; col < Bitmap.GetWidth(); col++)
        {
          r = orgImg.GetRed(col, row);
          g = orgImg.GetGreen(col, row);
          b = orgImg.GetBlue(col, row);
          if (r < 128 && g < 128 && b < 128)
            is_foreground = false;
          else
            is_foreground = true;
          if (is_foreground == true)
            {
              // setting the foreground color to this pixel
              *(p_out++) = fr;
              *(p_out++) = fg;
              *(p_out++) = fb;
          } else
            {
              // setting the background color to this pixel
              *(p_out++) = br;
              *(p_out++) = bg;
              *(p_out++) = bb;
            }
        }
    }
  img = wxImage(Bitmap.GetWidth(), Bitmap.GetHeight(), data);
  bitmap = wxBitmap(img);
}

void MyBitmap::GetBitmap(wxBitmap & bitmap, wxColour & color)
{
//
// builds the effective bitmap
//
  wxImage img;
  wxImage orgImg = Bitmap.ConvertToImage();
  int row;
  int col;
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char cr = color.Red();
  unsigned char cg = color.Green();
  unsigned char cb = color.Blue();
  bool is_foreground;
  if (FullColor == true)
    {
      // FullColor; simply using the plain bitmap
      bitmap = Bitmap;
      return;
    }
// MonoColor; we need to adjust colors and Alpha
  img = wxImage(Bitmap.GetWidth(), Bitmap.GetHeight());
  for (row = 0; row < Bitmap.GetHeight(); row++)
    {
      for (col = 0; col < Bitmap.GetWidth(); col++)
        {
          r = orgImg.GetRed(col, row);
          g = orgImg.GetGreen(col, row);
          b = orgImg.GetBlue(col, row);
          if (r < 128 && g < 128 && b < 128)
            is_foreground = true;
          else
            is_foreground = false;
          if (is_foreground == true)
            {
              // setting the foreground color to this pixel
              img.SetRGB(col, row, cr, cg, cb);
          } else
            {
              // setting the background color to this pixel
              img.SetRGB(col, row, 255, 255, 255);
            }
        }
    }
  bitmap = wxBitmap(img);
}

MyImageList::~MyImageList()
{
//
// destructor
//
  MyBitmap *p;
  MyBitmap *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

void MyImageList::Add(int id, int width, int height, unsigned char *blob,
                      int hot_x, int hot_y, wxColour & foreground,
                      wxColour & background)
{
//
// adding a Bicolor Symbol
//
  MyBitmap *p =
    new MyBitmap(id, width, height, blob, hot_x, hot_y, foreground, background);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void MyImageList::Add(int id, int width, int height, unsigned char *blob,
                      int hot_x, int hot_y)
{
//
// adding a FullColor Symbol
//
  MyBitmap *p = new MyBitmap(id, width, height, blob, hot_x, hot_y);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void MyImageList::Add(int id, int width, int height, unsigned char *blob,
                      wxColour & color)
{
//
// adding a MonoColor Pattern
//
  MyBitmap *p = new MyBitmap(id, width, height, blob, color);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void MyImageList::Add(int id, int width, int height, unsigned char *blob)
{
//
// adding a FullColor Pattern
//
  MyBitmap *p = new MyBitmap(id, width, height, blob);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

wxImageList *MyImageList::BuildList()
{
//
// builds the Image List
//
  wxImageList *list;
  MyBitmap *p;
  int cnt = 0;
  int width = 0;
  int height = 0;
  p = First;
  while (p)
    {
      // counting how many images are there
      cnt++;
      if (p->GetBitmap().GetWidth() > width)
        width = p->GetBitmap().GetWidth();
      if (p->GetBitmap().GetHeight() > height)
        height = p->GetBitmap().GetHeight();
      p = p->GetNext();
    }
  if (cnt == 0)
    {
      // returning an empty Image List
      list = new wxImageList();
      return list;
    }
  list = new wxImageList(width, height, true, cnt);
  p = First;
  while (p)
    {
      // populating the Image List
      p->SetListId(list->Add(p->GetBitmap(), p->GetMask()));
      p = p->GetNext();
    }
  return list;
}

MyBitmap *MyImageList::FindById(int id)
{
//
// finding an Image by Id
//
  MyBitmap *p = First;
  while (p)
    {
      if (p->GetId() == id)
        return p;
      p = p->GetNext();
    }
  return NULL;
}

MyBitmap *MyImageList::FindByPos(int list_id)
{
//
// finding an Image by ListId
//
  MyBitmap *p = First;
  while (p)
    {
      if (p->GetListId() == list_id)
        return p;
      p = p->GetNext();
    }
  return NULL;
}

MyLayer::MyLayer(wxString & raster)
{
//
// constructor - raster layer
//
  RasterLayer = true;
  LayerView = false;
  LayerVirtual = false;
  Hidden = false;
  ReadOnly = false;
  TableName = raster;
  GeometryColumn = wxT("RASTER");
  ToInsert = true;
  ToDelete = false;
  Next = NULL;
}

MyLayer::MyLayer(wxString & table, wxString & geometry)
{
//
// constructor - vector layer
//
  RasterLayer = false;
  LayerView = false;
  LayerVirtual = false;
  Hidden = false;
  ReadOnly = false;
  TableName = table;
  GeometryColumn = geometry;
  ToInsert = true;
  ToDelete = false;
  Next = NULL;
}

MyLayer::MyLayer(wxString & table, wxString & geometry, bool isView,
                 bool isVirtual)
{
//
// constructor - vector layer
//
  RasterLayer = false;
  LayerView = isView;
  LayerVirtual = isVirtual;
  Hidden = false;
  ReadOnly = false;
  TableName = table;
  GeometryColumn = geometry;
  ToInsert = true;
  ToDelete = false;
  Next = NULL;
}

MyLayerList::~MyLayerList()
{
//
// destructor - Layer List
  MyLayer *p;
  MyLayer *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

MyLayer *MyLayerList::Add(wxString & raster)
{
//
// adding a raster layer to the list
//
  MyLayer *p = new MyLayer(raster);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
  return p;
}

MyLayer *MyLayerList::Add(wxString & table, wxString & geometry)
{
//
// adding a vector layer to the list
//
  MyLayer *p = new MyLayer(table, geometry);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
  return p;
}

MyLayer *MyLayerList::Add(wxString & table, wxString & geometry, bool isView,
                          bool isVirtual)
{
//
// adding a vector layer to the list
//
  MyLayer *p = new MyLayer(table, geometry, isView, isVirtual);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
  return p;
}

bool MyLayerList::ExistsRaster(wxString & table)
{
//
// checking if a corresponding raster layer exists 
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsRasterLayer() == true)
        {
          wxString metaName = p->GetTableName() + wxT("_metadata");
          if (table.CmpNoCase(metaName) == 0)
            return true;
        }
      p = p->GetNext();
    }
  return false;
}

void MyLayerList::Evaluate(wxString & raster)
{
//
// checking if a raster layer exists 
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsRasterLayer() == true
          && raster.CmpNoCase(p->GetTableName()) == 0)
        {
          p->NotToInsert();
          return;
        }
      p = p->GetNext();
    }
  p = Add(raster);
  p->ToBeDeleted();
}

void MyLayerList::SetGisLayerAuth(wxString & table, wxString & geometry,
                                  bool rdOnly, bool hidden)
{
//
// setting the GIS layer auths 
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsRasterLayer() == false && table.CmpNoCase(p->GetTableName()) == 0
          && geometry.CmpNoCase(p->GetGeometryColumn()) == 0)
        {
          if (hidden == true)
            p->SetHidden();
          else if (rdOnly == true)
            p->SetReadOnly();
          return;
        }
      p = p->GetNext();
    }
}

void MyLayerList::Evaluate(wxString & table, wxString & geometry, bool network)
{
//
// checking if a vector layer exists 
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsRasterLayer() == false && table.CmpNoCase(p->GetTableName()) == 0
          && geometry.CmpNoCase(p->GetGeometryColumn()) == 0)
        {
          p->NotToInsert();
          p->SetNetwork(network);
          return;
        }
      p = p->GetNext();
    }
  p = Add(table, geometry);
  p->ToBeDeleted();
}

bool MyLayerList::ToBeInserted()
{
//
// checking if there are new layers to be inserted
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsToInsert() == true)
        return true;
      p = p->GetNext();
    }
  return false;
}

bool MyLayerList::ToBeDeleted()
{
//
// checking if there are any layers no longer existing [to be deleted]
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsToDelete() == true)
        return true;
      p = p->GetNext();
    }
  return false;
}

bool MyLayerList::ToBeDeletedTable()
{
//
// checking if there are any layers no longer existing [to be deleted]
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsToDelete() == true && p->IsLayerVirtual() == false
          && p->IsLayerView() == false)
        return true;
      p = p->GetNext();
    }
  return false;
}

bool MyLayerList::ToBeDeletedView()
{
//
// checking if there are any layers no longer existing [to be deleted]
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsToDelete() == true && p->IsLayerVirtual() == false
          && p->IsLayerView() == true)
        return true;
      p = p->GetNext();
    }
  return false;
}

bool MyLayerList::ToBeDeletedVirt()
{
//
// checking if there are any layers no longer existing [to be deleted]
//
  MyLayer *p = First;
  while (p)
    {
      if (p->IsToDelete() == true && p->IsLayerVirtual() == true
          && p->IsLayerView() == false)
        return true;
      p = p->GetNext();
    }
  return false;
}

MyLayerSubClass::MyLayerSubClass(bool unique, bool text, wxString & textValue,
                                 double numValue, double minValue,
                                 double maxValue, int symbolType, int size,
                                 wxColour & color)
{
//
// Constructor 
//
  Unique = unique;
  Text = text;
  TextValue = textValue;
  NumValue = numValue;
  MinValue = minValue;
  MaxValue = maxValue;
  SymbolType = symbolType;
  Size = size;
  Color = color;
  Next = NULL;
}

MyLayerParams::MyLayerParams(wxString & raster, wxString & descName,
                             bool visible, bool alwaysVisible, int minScale,
                             int maxScale)
{
//
// constructor - raster layer Params
//
  RasterLayer = true;
  LayerView = false;
  LayerVirtual = false;
  ReadOnly = false;
  TableName = raster;
  GeometryColumn = wxT("RASTER");
  DescName = descName;
  GeometryType = -1;
  MultiType = false;
  Srid = -9999;
  Network = false;
  Visible = visible;
  Identify = false;
  Reproject = false;
  LabelColumn = wxT("");
  AlwaysVisible = alwaysVisible;
  MinScale = minScale;
  MaxScale = maxScale;
  SymbolId = 1;
  ForegroundColor = wxColour(255, 255, 255);
  BackgroundColor = wxColour(0, 0, 0);
  LineColor = wxColour(0, 255, 128, 255);
  LineThickness = 1;
  LineStyle = wxSOLID;
  DrawBorder = true;
  ToFill = true;
  SolidFilling = true;
  FillColor = wxColour(0, 128, 64);
  PatternId = 1;
  First = NULL;
  Last = NULL;
  Next = NULL;
}

MyLayerParams::MyLayerParams(wxString & table, wxString & geometry,
                             wxString & descName, bool network, bool visible,
                             bool identify, bool reproject,
                             wxString & labelColumn, bool alwaysVisible,
                             int minScale, int maxScale, int symbolId,
                             wxColour & foreground, wxColour & background,
                             wxColour & lineColor, int lineThickness,
                             int lineStyle, bool drawBorder, bool toFill,
                             bool solidFilling, wxColour & fillColor,
                             int patternId, bool subClasses,
                             wxString & classifyColumn, bool uniqueValue,
                             int numClasses, double classesMin,
                             double classesMax, int classesSymbol,
                             int classesMinSize, int classesMaxSize,
                             wxColour & classesMinColor,
                             wxColour & classesMaxColor, bool mapLabeling,
                             wxColour labelColor, int labelPointSize,
                             bool labelFontBold, bool labelFontItalic,
                             bool labelFontUnderlined, bool labelFontOutlined,
                             wxString & labelOrderByColumn,
                             bool labelOrderByDesc, bool labelAlwaysVisible,
                             int labelMinScale, int labelMaxScale,
                             bool labelAntiOverlap)
{
//
// constructor - vector layer Params
//
  RasterLayer = false;
  LayerView = false;
  LayerVirtual = false;
  ReadOnly = false;
  TableName = table;
  GeometryColumn = geometry;
  DescName = descName;
  GeometryType = -1;
  MultiType = false;
  Srid = -9999;
  Network = network;
  Visible = visible;
  Identify = identify;
  Reproject = reproject;
  LabelColumn = labelColumn;
  AlwaysVisible = alwaysVisible;
  MinScale = minScale;
  MaxScale = maxScale;
  SymbolId = symbolId;
  ForegroundColor = foreground;
  BackgroundColor = background;
  LineColor = lineColor;
  LineThickness = lineThickness;
  LineStyle = lineStyle;
  DrawBorder = drawBorder;
  ToFill = toFill;
  SolidFilling = solidFilling;
  FillColor = fillColor;
  PatternId = patternId;
  SubClasses = subClasses;
  ClassifyColumn = classifyColumn;
  UniqueValue = uniqueValue;
  NumClasses = numClasses;
  ClassesMinValue = classesMin;
  ClassesMaxValue = classesMax;
  ClassesSymbolType = classesSymbol;
  ClassesMinSize = classesMinSize;
  ClassesMaxSize = classesMaxSize;
  ClassesMinColor = classesMinColor;
  ClassesMaxColor = classesMaxColor;
  MapLabeling = mapLabeling;
  LabelColor = labelColor;
  LabelPointSize = labelPointSize;
  LabelFontBold = labelFontBold;
  LabelFontItalic = labelFontItalic;
  LabelFontUnderlined = labelFontUnderlined;
  LabelFontOutlined = labelFontOutlined;
  LabelOrderByColumn = labelOrderByColumn;
  LabelOrderByDescending = labelOrderByDesc;
  LabelAlwaysVisible = labelAlwaysVisible;
  LabelMinScale = labelMinScale;
  LabelMaxScale = labelMaxScale;
  LabelAntiOverlap = labelAntiOverlap;
  First = NULL;
  Last = NULL;
  Next = NULL;
}

MyLayerParams::~MyLayerParams()
{
//
// destructor - Layer 
  MyLayerSubClass *p;
  MyLayerSubClass *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

void MyLayerParams::Add(bool unique, bool text, wxString & textValue,
                        double numValue, double minValue, double maxValue,
                        int symbolType, int size, wxColour & color)
{
// adding a SubCLass to this Layer
  MyLayerSubClass *p =
    new MyLayerSubClass(unique, text, textValue, numValue, minValue, maxValue,
                        symbolType, size, color);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

MyLayerParamsList::~MyLayerParamsList()
{
//
// destructor - Layer List
  MyLayerParams *p;
  MyLayerParams *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

void MyLayerParamsList::Add(wxString & raster, wxString & descName,
                            bool visible, bool alwaysVisible, int minScale,
                            int maxScale)
{
//
// adding a raster layer to the list
//
  MyLayerParams *p =
    new MyLayerParams(raster, descName, visible, alwaysVisible, minScale,
                      maxScale);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void MyLayerParamsList::Add(wxString & table, wxString & geometry,
                            wxString & descName, bool network, bool visible,
                            bool identify, bool reproject,
                            wxString & labelColumn, bool alwaysVisible,
                            int minScale, int maxScale, int symbolId,
                            wxColour & foreground, wxColour & background,
                            wxColour & lineColor, int lineThickness,
                            int lineStyle, bool drawBorder, bool toFill,
                            bool solidFilling, wxColour & fillColor,
                            int patternId, bool subClasses,
                            wxString & classifyColumn, bool uniqueValue,
                            int numClasses, double classesMin,
                            double classesMax, int classesSymbol,
                            int classesMinSize, int classesMaxSize,
                            wxColour & classesMinColor,
                            wxColour & classesMaxColor, bool mapLabeling,
                            wxColour labelColor, int labelPointSize,
                            bool labelFontBold, bool labelFontItalic,
                            bool labelFontUnderlined, bool labelFontOutlined,
                            wxString & labelOrderByColumn,
                            bool labelOrderByDesc, bool labelAlwaysVisible,
                            int labelMinScale, int labelMaxScale,
                            bool labelAntiOverlap)
{
//
// adding a vector layer to the list
//
  MyLayerParams *p =
    new MyLayerParams(table, geometry, descName, network, visible, identify,
                      reproject, labelColumn, alwaysVisible, minScale,
                      maxScale, symbolId, foreground, background, lineColor,
                      lineThickness, lineStyle, drawBorder, toFill,
                      solidFilling, fillColor, patternId, subClasses,
                      classifyColumn, uniqueValue, numClasses, classesMin,
                      classesMax, classesSymbol,
                      classesMinSize, classesMaxSize, classesMinColor,
                      classesMaxColor, mapLabeling, labelColor,
                      labelPointSize, labelFontBold, labelFontItalic,
                      labelFontUnderlined, labelFontOutlined,
                      labelOrderByColumn, labelOrderByDesc,
                      labelAlwaysVisible, labelMinScale, labelMaxScale,
                      labelAntiOverlap);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

MyLayerParams *MyLayerParamsList::FindRaster(wxString & table)
{
//
// finding a raster layer [metadata]
//
  MyLayerParams *p = First;
  while (p)
    {
      if (p->IsRasterLayer() == true)
        {
          wxString metaName = p->GetTableName() + wxT("_metadata");
          if (table.CmpNoCase(metaName) == 0)
            return p;
        }
      p = p->GetNext();
    }
  return NULL;
}

MyLayerParams *MyLayerParamsList::Find(wxString & raster)
{
//
// finding a raster layer 
//
  MyLayerParams *p = First;
  while (p)
    {
      if (p->IsRasterLayer() == true
          && raster.CmpNoCase(p->GetTableName()) == 0)
        return p;
      p = p->GetNext();
    }
  return NULL;
}

MyLayerParams *MyLayerParamsList::Find(wxString & table, wxString & geometry)
{
//
// finding a vector layer 
//
  MyLayerParams *p = First;
  while (p)
    {
      if (p->IsRasterLayer() == false && table.CmpNoCase(p->GetTableName()) == 0
          && geometry.CmpNoCase(p->GetGeometryColumn()) == 0)
        return p;
      p = p->GetNext();
    }
  return NULL;
}

void MyLayerParamsList::Add(wxString & table, wxString & geometry, bool unique,
                            bool text, wxString & textValue, double numValue,
                            double minValue, double maxValue, int symbolType,
                            int size, wxColour & color)
{
// adding a SubCLass to some Layer
  MyLayerParams *p = NULL;
  if (Current != NULL)
    {
      if (Current->GetTableName() == table
          && Current->GetGeometryColumn() == geometry)
        p = Current;
    }
  if (p == NULL)
    {
      Current = Find(table, geometry);
      p = Current;
    }
  if (p != NULL)
    p->Add(unique, text, textValue, numValue, minValue, maxValue, symbolType,
           size, color);
}

MyDistinctValue::MyDistinctValue(wxString & value)
{
//
// Constructor - Text Value
//
  Text = true;
  TextValue = value;
  NumValue = 0.0;
  Color = wxColour(0, 0, 0);
  IconIndex = -1;
  RandomizeSkip = false;
  Next = NULL;
}

MyDistinctValue::MyDistinctValue(double value)
{
//
// Constructor - Num Value
//
  Text = false;
  NumValue = value;
  Color = wxColour(0, 0, 0);
  IconIndex = -1;
  RandomizeSkip = false;
  Next = NULL;
}

wxString & MyDistinctValue::GetValueAsString()
{
//
// return a String value anyway
//
  if (Text == true)
    return TextValue;
  char buf[128];
  int ind;
  sprintf(buf, "%1.6f", NumValue);
  for (ind = strlen(buf) - 1; ind > 0; ind--)
    {
      if (buf[ind] == '0')
        buf[ind] = '\0';
      else
        break;
    }
  if (buf[strlen(buf) - 1] == '.')
    buf[strlen(buf) - 1] = '\0';
  if (strlen(buf) == 0)
    strcpy(buf, "0");
  TextValue = wxString::FromUTF8(buf);
  return TextValue;
}

MyDistinctValueList::~MyDistinctValueList()
{
//
// destructor
//
  MyDistinctValue *p;
  MyDistinctValue *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

MyDistinctValue *MyDistinctValueList::Add(wxString & value)
{
//
// adding a Text value
//
  MyDistinctValue *p = new MyDistinctValue(value);
  TextCount++;
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
  return p;
}

MyDistinctValue *MyDistinctValueList::Add(double value)
{
//
// adding a Num value
//
  MyDistinctValue *p = new MyDistinctValue(value);
  DoubleCount++;
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
  return p;
}

int MyDistinctValueList::GetType()
{
// identifying the type
  if (DoubleCount == 0 && TextCount > 0)
    return CLASSES_TEXT_TYPE;
  if (DoubleCount > 0 && TextCount == 0)
    return CLASSES_NUMERIC_TYPE;
  return CLASSES_INVALID_TYPE;
}

void MyDistinctValueList::RandomizeColors(MyFrame * main, int hueMode,
                                          int transparencyMode)
{
//
// setting random colors to each element
//
  int red;
  int green;
  int blue;
  wxColour color;
  MyDistinctValue *value = First;
  while (value)
    {
      if (value->IsRandomizeSkip() == false)
        {
          if (hueMode == RANDOM_COLOR_SATURE)
            main->GetRandomColorSature(&red, &green, &blue);
          else if (hueMode == RANDOM_COLOR_MEDIUM)
            main->GetRandomColorMedium(&red, &green, &blue);
          else if (hueMode == RANDOM_COLOR_LIGHT)
            main->GetRandomColorLight(&red, &green, &blue);
          else
            main->GetRandomColor(&red, &green, &blue);
          if (transparencyMode == RANDOM_COLOR_LIGHT_TRANSPARENT)
            color = wxColour(red, green, blue, 64);
          else if (transparencyMode == RANDOM_COLOR_MEDIUM_TRANSPARENT)
            color = wxColour(red, green, blue, 96);
          else
            color = wxColour(red, green, blue);
          value->SetColor(color);
        }
      value = value->GetNext();
    }
}

void MyDistinctValueList::AddSubClassIcons(wxImageList * list, int width,
                                           int height, int geomType,
                                           int symbolType, int size)
{
//
// creating the SubClass Icons and inserting into the ImageList
//
  int x;
  int y;
  x = width / 2;
  y = height / 2;
  MyDistinctValue *value = First;
  while (value)
    {
      // generating the SubClass Icon for each value
      int pen_r = 255 - value->GetColor().Red();
      int pen_g = 255 - value->GetColor().Green();
      int pen_b = 255 - value->GetColor().Blue();
      wxBitmap bmp(width, height);
      wxMemoryDC *bmp_dc = new wxMemoryDC(bmp);
      bmp_dc->SetPen(wxColour(255, 255, 255));
      bmp_dc->SetBrush(wxColour(255, 255, 255));
      bmp_dc->DrawRectangle(0, 0, width, height);
      if (geomType == LAYER_POINT)
        {
          bmp_dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
          bmp_dc->SetBrush(wxBrush(value->GetColor()));
          if (symbolType == CLASSES_SYMBOL_SQUARE)
            bmp_dc->DrawRectangle(x - size, y - size, size * 2, size * 2);
          else if (symbolType == CLASSES_SYMBOL_DIAMOND)
            {
              wxPoint points[5];
              points[0].x = x;
              points[0].y = y - size;
              points[1].x = x + size;
              points[1].y = y;
              points[2].x = x;
              points[2].y = y + size;
              points[3].x = x - size;
              points[3].y = y;
              points[4].x = x;
              points[4].y = y - size;
              bmp_dc->DrawPolygon(5, points);
          } else
            bmp_dc->DrawCircle(x, y, size);
          if ((size * 2) >= height || (size * 2) >= width)
            {
              bmp_dc->SetPen(wxPen(wxColour(255, 192, 192)));
              bmp_dc->SetBrush(*wxTRANSPARENT_BRUSH);
              bmp_dc->DrawRectangle(0, 0, width, height);
            }
        }
      if (geomType == LAYER_LINESTRING)
        {
          wxPen pen(value->GetColor(), size);
          pen.SetCap(wxCAP_BUTT);
          bmp_dc->SetPen(pen);
          bmp_dc->DrawLine(4, height / 2, width - 4, height / 2);
          if (size >= height || size >= width)
            {
              bmp_dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
              bmp_dc->SetBrush(*wxTRANSPARENT_BRUSH);
              bmp_dc->DrawRectangle(0, 0, width, height);
            }
        }
      if (geomType == LAYER_POLYGON)
        {
          bmp_dc->SetPen(wxPen(wxColour(0, 0, 0)));
          bmp_dc->SetBrush(wxBrush(value->GetColor()));
          wxPoint points[5];
          points[0].x = 2;
          points[0].y = 2;
          points[1].x = width - 2;
          points[1].y = 2;
          points[2].x = width - 2;
          points[2].y = height - 2;
          points[3].x = 2;
          points[3].y = height - 2;
          points[4].x = 2;
          points[4].y = 2;
          bmp_dc->DrawPolygon(5, points);
        }
      bmp_dc->SetPen(wxNullPen);
      bmp_dc->SetBrush(wxNullBrush);
      delete bmp_dc;
      value->SetIconIndex(list->Add(bmp, wxColour(255, 255, 255)));
      value = value->GetNext();
    }
}

MyRangeValue::MyRangeValue(double min, double max, int size, wxColour & color)
{
//
// Constructor 
//
  MinValue = min;
  MaxValue = max;
  Size = size;
  Color = color;
  IconIndex = -1;
  Next = NULL;
}

wxString & MyRangeValue::GetRangeAsString()
{
//
// return the Range as a String value 
//
  char buf[128];
  int ind;
  if (fabs(MinValue) >= 100.0)
    sprintf(buf, "%1.1f", MinValue);
  else if (fabs(MinValue) >= 10.0)
    sprintf(buf, "%1.2f", MinValue);
  else if (fabs(MinValue) >= 1.0)
    sprintf(buf, "%1.3f", MinValue);
  else
    sprintf(buf, "%1.6f", MinValue);
  for (ind = strlen(buf) - 1; ind > 0; ind--)
    {
      if (buf[ind] == '0')
        buf[ind] = '\0';
      else
        break;
    }
  if (buf[strlen(buf) - 1] == '.')
    buf[strlen(buf) - 1] = '\0';
  if (strlen(buf) == 0)
    strcpy(buf, "0");
  TextValue = wxString::FromUTF8(buf);
  TextValue += wxT(" / ");
  if (fabs(MaxValue) >= 100.0)
    sprintf(buf, "%1.1f", MaxValue);
  else if (fabs(MaxValue) >= 10.0)
    sprintf(buf, "%1.2f", MaxValue);
  else if (fabs(MaxValue) >= 1.0)
    sprintf(buf, "%1.3f", MaxValue);
  else
    sprintf(buf, "%1.6f", MaxValue);
  for (ind = strlen(buf) - 1; ind > 0; ind--)
    {
      if (buf[ind] == '0')
        buf[ind] = '\0';
      else
        break;
    }
  if (buf[strlen(buf) - 1] == '.')
    buf[strlen(buf) - 1] = '\0';
  if (strlen(buf) == 0)
    strcpy(buf, "0");
  TextValue += wxString::FromUTF8(buf);
  return TextValue;
}

MyRangeValueList::~MyRangeValueList()
{
//
// destructor
//
  MyRangeValue *p;
  MyRangeValue *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

void MyRangeValueList::Add(double min, double max, int size, wxColour & color)
{
//
// adding a Range value
//
  MyRangeValue *p = new MyRangeValue(min, max, size, color);
  Count++;
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void MyRangeValueList::Build(double min, double max, int numClasses,
                             int minSize, int maxSize, wxColour & minColor,
                             wxColour & maxColor)
{
//
// setting the RANGE Classes 
//
  MyRangeValue *p;
  MyRangeValue *pN;
  p = First;
  while (p)
    {
      // cleaning the old Range list [if exists]
      pN = p->GetNext();
      delete p;
      p = pN;
    }
  First = NULL;
  Last = NULL;
  Count = 0;
// determining interval and increments
  double oldMin = min;
  double size = minSize;
  wxColour color = minColor;
  double step = (max - min) / (double) numClasses;
  double inc_size = (double) (maxSize - minSize) / (double) numClasses;
  double inc_red =
    (double) (maxColor.Red() - minColor.Red()) / (double) numClasses;
  double inc_green =
    (double) (maxColor.Green() - minColor.Green()) / (double) numClasses;
  double inc_blue =
    (double) (maxColor.Blue() - minColor.Blue()) / (double) numClasses;
  int ind;
  for (ind = 0; ind < numClasses; ind++)
    {
      // inserting the RANGE classes
      if (ind == numClasses - 1)
        Add(oldMin, max, maxSize, maxColor);
      else
        Add(oldMin, oldMin + step, (int) size, color);
      oldMin += step;
      // next size
      size += inc_size;
      // next color
      int r = (int) ((double) color.Red() + inc_red);
      int g = (int) ((double) color.Green() + inc_green);
      int b = (int) ((double) color.Blue() + inc_blue);
      if (r < 0)
        r = 0;
      if (r > 255)
        r = 255;
      if (g < 0)
        g = 0;
      if (g > 255)
        g = 255;
      if (b < 0)
        b = 0;
      if (b > 255)
        b = 255;
      color = wxColor(r, g, b);
    }
}

void MyRangeValueList::Build(double min, double max, int numClasses,
                             wxColour & minColor, wxColour & maxColor)
{
//
// setting the RANGE Classes 
//
  MyRangeValue *p;
  MyRangeValue *pN;
  p = First;
  while (p)
    {
      // cleaning the old Range list [if exists]
      pN = p->GetNext();
      delete p;
      p = pN;
    }
  First = NULL;
  Last = NULL;
  Count = 0;
// determining interval and increments
  double oldMin = min;
  wxColour color = minColor;
  double step = (max - min) / (double) numClasses;
  double inc_red =
    (double) (maxColor.Red() - minColor.Red()) / (double) numClasses;
  double inc_green =
    (double) (maxColor.Green() - minColor.Green()) / (double) numClasses;
  double inc_blue =
    (double) (maxColor.Blue() - minColor.Blue()) / (double) numClasses;
  int ind;
  for (ind = 0; ind < numClasses; ind++)
    {
      // inserting the RANGE classes
      if (ind == numClasses - 1)
        Add(oldMin, max, 0, maxColor);
      else
        Add(oldMin, oldMin + step, 0, color);
      oldMin += step;
      // next color
      int r = (int) ((double) color.Red() + inc_red);
      int g = (int) ((double) color.Green() + inc_green);
      int b = (int) ((double) color.Blue() + inc_blue);
      if (r < 0)
        r = 0;
      if (r > 255)
        r = 255;
      if (g < 0)
        g = 0;
      if (g > 255)
        g = 255;
      if (b < 0)
        b = 0;
      if (b > 255)
        b = 255;
      color = wxColor(r, g, b);
    }
}

void MyRangeValueList::AddSubClassIcons(wxImageList * list, int width,
                                        int height, int geomType,
                                        int symbolType)
{
//
// creating the SubClass Icons and inserting into the ImageList - POINTs
//
  int x;
  int y;
  x = width / 2;
  y = height / 2;
  MyRangeValue *value = First;
  while (value)
    {
      // generating the SubClass Icon for each value
      int pen_r = 255 - value->GetColor().Red();
      int pen_g = 255 - value->GetColor().Green();
      int pen_b = 255 - value->GetColor().Blue();
      wxBitmap bmp(width, height);
      wxMemoryDC *bmp_dc = new wxMemoryDC(bmp);
      bmp_dc->SetPen(wxColour(255, 255, 255));
      bmp_dc->SetBrush(wxColour(255, 255, 255));
      bmp_dc->DrawRectangle(0, 0, width, height);
      if (geomType == LAYER_POINT)
        {
          bmp_dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
          bmp_dc->SetBrush(wxBrush(value->GetColor()));
          if (symbolType == CLASSES_SYMBOL_SQUARE)
            bmp_dc->DrawRectangle(x - value->GetSize(), y - value->GetSize(),
                                  value->GetSize() * 2, value->GetSize() * 2);
          else if (symbolType == CLASSES_SYMBOL_DIAMOND)
            {
              wxPoint points[5];
              points[0].x = x;
              points[0].y = y - value->GetSize();
              points[1].x = x + value->GetSize();
              points[1].y = y;
              points[2].x = x;
              points[2].y = y + value->GetSize();
              points[3].x = x - value->GetSize();
              points[3].y = y;
              points[4].x = x;
              points[4].y = y - value->GetSize();
              bmp_dc->DrawPolygon(5, points);
          } else
            bmp_dc->DrawCircle(x, y, value->GetSize());
          if ((value->GetSize() * 2) >= height
              || (value->GetSize() * 2) >= width)
            {
              bmp_dc->SetPen(wxPen(wxColour(255, 192, 192)));
              bmp_dc->SetBrush(*wxTRANSPARENT_BRUSH);
              bmp_dc->DrawRectangle(0, 0, width, height);
            }
        }
      if (geomType == LAYER_LINESTRING)
        {
          wxPen pen(value->GetColor(), value->GetSize());
          pen.SetCap(wxCAP_BUTT);
          bmp_dc->SetPen(pen);
          bmp_dc->DrawLine(4, height / 2, width - 4, height / 2);
          if (value->GetSize() >= height || value->GetSize() >= width)
            {
              bmp_dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
              bmp_dc->SetBrush(*wxTRANSPARENT_BRUSH);
              bmp_dc->DrawRectangle(0, 0, width, height);
            }
        }
      if (geomType == LAYER_POLYGON)
        {
          bmp_dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
          bmp_dc->SetBrush(wxBrush(value->GetColor()));
          wxPoint points[5];
          points[0].x = 2;
          points[0].y = 2;
          points[1].x = width - 2;
          points[1].y = 2;
          points[2].x = width - 2;
          points[2].y = height - 2;
          points[3].x = 2;
          points[3].y = height - 2;
          points[4].x = 2;
          points[4].y = 2;
          bmp_dc->DrawPolygon(5, points);
        }
      bmp_dc->SetPen(wxNullPen);
      bmp_dc->SetBrush(wxNullBrush);
      delete bmp_dc;
      value->SetIconIndex(list->Add(bmp, wxColour(255, 255, 255)));
      value = value->GetNext();
    }
}

SubClassObject::SubClassObject(MyDistinctValue * ptr)
{
//
// Constructor 
//
  PtrDistinct = ptr;
  PtrRange = NULL;
  Unique = true;
  Text = ptr->IsText();
  TextValue = ptr->GetTextValue();
  NumValue = ptr->GetNumValue();
  MinValue = 0.0;
  MaxValue = 0.0;
  Size = 0;
  Color = ptr->GetColor();
  RandomizeSkip = ptr->IsRandomizeSkip();
  IconIndex = ptr->GetIconIndex();
}

SubClassObject::SubClassObject(MyRangeValue * ptr)
{
//
// Constructor 
//
  PtrDistinct = NULL;
  PtrRange = ptr;
  Unique = false;
  Text = false;
  NumValue = 0.0;
  MinValue = ptr->GetMinValue();
  MaxValue = ptr->GetMaxValue();
  Size = ptr->GetSize();
  Color = ptr->GetColor();
  RandomizeSkip = false;
  IconIndex = ptr->GetIconIndex();
}

void SubClassObject::SetColor(wxColour & color)
{
  Color = color;
  if (PtrDistinct)
    PtrDistinct->SetColor(color);
  if (PtrRange)
    PtrRange->SetColor(color);
}

void SubClassObject::SetRandomizeSkip(bool skip)
{
  if (PtrDistinct)
    {
      RandomizeSkip = skip;
      PtrDistinct->SetRandomizeSkip(skip);
    }
}

wxString & SubClassObject::GetValueAsString()
{
// preparing the Tree Item Label
  char buf[128];
  int ind;
  TextValue = wxT("???");
  if (Unique == true)
    {
      if (Text == true)
        return TextValue;
      sprintf(buf, "%1.6f", NumValue);
      for (ind = strlen(buf) - 1; ind > 0; ind--)
        {
          if (buf[ind] == '0')
            buf[ind] = '\0';
          else
            break;
        }
      if (buf[strlen(buf) - 1] == '.')
        buf[strlen(buf) - 1] = '\0';
      if (strlen(buf) == 0)
        strcpy(buf, "0");
      TextValue = wxString::FromUTF8(buf);
  } else
    {
      if (fabs(MinValue) >= 100.0)
        sprintf(buf, "%1.1f", MinValue);
      else if (fabs(MinValue) >= 10.0)
        sprintf(buf, "%1.2f", MinValue);
      else if (fabs(MinValue) >= 1.0)
        sprintf(buf, "%1.3f", MinValue);
      else
        sprintf(buf, "%1.6f", MinValue);
      for (ind = strlen(buf) - 1; ind > 0; ind--)
        {
          if (buf[ind] == '0')
            buf[ind] = '\0';
          else
            break;
        }
      if (buf[strlen(buf) - 1] == '.')
        buf[strlen(buf) - 1] = '\0';
      if (strlen(buf) == 0)
        strcpy(buf, "0");
      TextValue = wxString::FromUTF8(buf);
      TextValue += wxT(" / ");
      if (fabs(MaxValue) >= 100.0)
        sprintf(buf, "%1.1f", MaxValue);
      else if (fabs(MaxValue) >= 10.0)
        sprintf(buf, "%1.2f", MaxValue);
      else if (fabs(MaxValue) >= 1.0)
        sprintf(buf, "%1.3f", MaxValue);
      else
        sprintf(buf, "%1.6f", MaxValue);
      for (ind = strlen(buf) - 1; ind > 0; ind--)
        {
          if (buf[ind] == '0')
            buf[ind] = '\0';
          else
            break;
        }
      if (buf[strlen(buf) - 1] == '.')
        buf[strlen(buf) - 1] = '\0';
      if (strlen(buf) == 0)
        strcpy(buf, "0");
      TextValue += wxString::FromUTF8(buf);
    }
  return TextValue;
}

void SubClassObject::UpdateSubClassIcon(wxImageList * list, int width,
                                        int height, int geomType)
{
//
// updating the SubClass Icons and replacing into the ImageList
//
  int pen_r = 255 - Color.Red();
  int pen_g = 255 - Color.Green();
  int pen_b = 255 - Color.Blue();
  int x;
  int y;
  x = width / 2;
  y = height / 2;
  wxBitmap bmp(width, height);
  wxMemoryDC *bmp_dc = new wxMemoryDC(bmp);
  bmp_dc->SetPen(wxColour(255, 255, 255));
  bmp_dc->SetBrush(wxColour(255, 255, 255));
  bmp_dc->DrawRectangle(0, 0, width, height);
  bmp_dc->SetPen(wxColour(pen_r, pen_g, pen_b));
  bmp_dc->SetBrush(wxBrush(Color));
  if (geomType == LAYER_POINT)
    {
      if (SymbolType == CLASSES_SYMBOL_SQUARE)
        bmp_dc->DrawRectangle(x - Size, y - Size, Size * 2, Size * 2);
      else if (SymbolType == CLASSES_SYMBOL_DIAMOND)
        {
          wxPoint points[5];
          points[0].x = x;
          points[0].y = y - Size;
          points[1].x = x + Size;
          points[1].y = y;
          points[2].x = x;
          points[2].y = y + Size;
          points[3].x = x - Size;
          points[3].y = y;
          points[4].x = x;
          points[4].y = y - Size;
          bmp_dc->DrawPolygon(5, points);
      } else
        bmp_dc->DrawCircle(x, y, Size);
      if ((Size * 2) > height || (Size * 2) > width)
        {
          bmp_dc->SetPen(wxPen(wxColour(255, 192, 192)));
          bmp_dc->SetBrush(*wxTRANSPARENT_BRUSH);
          bmp_dc->DrawRectangle(0, 0, width, height);
        }
    }
  if (geomType == LAYER_LINESTRING)
    {
      wxPen pen(Color, Size);
      pen.SetCap(wxCAP_BUTT);
      bmp_dc->SetPen(pen);
      bmp_dc->DrawLine(4, height / 2, width - 4, height / 2);
      if (Size >= height || Size >= width)
        {
          bmp_dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
          bmp_dc->SetBrush(*wxTRANSPARENT_BRUSH);
          bmp_dc->DrawRectangle(0, 0, width, height);
        }
    }
  if (geomType == LAYER_POLYGON)
    {
      bmp_dc->SetPen(wxPen(wxColour(pen_r, pen_g, pen_b)));
      bmp_dc->SetBrush(wxBrush(Color));
      wxPoint points[5];
      points[0].x = 2;
      points[0].y = 2;
      points[1].x = width - 2;
      points[1].y = 2;
      points[2].x = width - 2;
      points[2].y = height - 2;
      points[3].x = 2;
      points[3].y = height - 2;
      points[4].x = 2;
      points[4].y = 2;
      bmp_dc->DrawPolygon(5, points);
    }
  bmp_dc->SetPen(wxNullPen);
  bmp_dc->SetBrush(wxNullBrush);
  delete bmp_dc;
  list->Replace(IconIndex, bmp);
}

void SubClassObject::PrepareStaticValues()
{
// preparing the static values to be serialized into the DB
  char dummy[64];
  sprintf(dummy, "%02x%02x%02x%02x", Color.Red(), Color.Green(), Color.Blue(),
          Color.Alpha());
  ColorAsRGBA = wxString::FromUTF8(dummy);
  if (SymbolType == CLASSES_SYMBOL_SQUARE)
    SymbolTypeAsConstant = wxT("SQUARE");
  else if (SymbolType == CLASSES_SYMBOL_DIAMOND)
    SymbolTypeAsConstant = wxT("DIAMOND");
  else
    SymbolTypeAsConstant = wxT("CIRCLE");
}

void SubClassesContainer::Create(int count)
{
// allocating the SubClasses array
  int i;
  if (SubClasses)
    delete[]SubClasses;
  SubClasses = NULL;
  if (count > 0)
    {
      Count = count;
      Index = 0;
      SubClasses = new LayerObject *[count];
      for (i = 0; i < count; i++)
        SubClasses[i] = NULL;
    }
}

void SubClassesContainer::Add(LayerObject * subClass)
{
// inserting a pointer into the array
  if (Index < Count && Count > 0)
    SubClasses[Index++] = subClass;
}

void SubClassesContainer::BuildDistinctList(MyDistinctValueList * list)
{
// populating the DistinctValueList
  LayerObject *obj;
  MyDistinctValue *val;
  int i;
  for (i = 0; i < Count; i++)
    {
      obj = SubClasses[i];
      if (obj != NULL)
        {
          if (obj->IsSubClassText() == true)
            val = list->Add(obj->GetSubClassTextValue());
          else
            val = list->Add(obj->GetSubClassNumValue());
          if (HasColors() == true)
            val->SetColor(obj->GetSubClassColor());
        }
    }
}

void SubClassesContainer::BuildRangeList(MyRangeValueList * list)
{
// populating the RangeValueList
  double min;
  double max;
  LayerObject *obj;
  int i;
  for (i = 0; i < Count; i++)
    {
      obj = SubClasses[i];
      if (obj != NULL)
        {
          min = obj->GetSubClassMinValue();
          max = obj->GetSubClassMaxValue();
          list->Add(min, max, obj->GetSubClassSize(), obj->GetSubClassColor());
        }
    }
}

MapSubClass::MapSubClass(LayerObject * org)
{
//
// constructor
//
  Visible = org->IsVisible();
  Unique = org->IsSubClassUnique();
  Text = org->IsSubClassText();
  TextValue = org->GetSubClassTextValue();
  NumValue = org->GetSubClassNumValue();
  MinValue = org->GetSubClassMinValue();
  MaxValue = org->GetSubClassMaxValue();
  SymbolType = org->GetSubClassSymbolType();
  Size = org->GetSubClassSize();
  Color = org->GetSubClassColor();
  Next = NULL;
}

bool MapSubClass::OkValue(wxString & value)
{
//
// evaluating a TEXT SUBCLASS value
//
  if (Unique == true && Text == true)
    {
      if (value == TextValue)
        return true;
    }
  return false;
}

bool MapSubClass::OkValue(double value)
{
//
// evaluating a NUMERIC SUBCLASS value
//
  if (Text == true)
    return false;
  if (Unique == true)
    {
      if (value == NumValue)
        return true;
  } else
    {
      if (value >= MinValue && value <= MaxValue)
        return true;
    }
  return false;
}

void MapSubClass::CreateGraphicResources(wxGraphicsContext * gr, int geomType)
{
// setting Pens, Brushes etc
  int pen_r = 255 - Color.Red();
  int pen_g = 255 - Color.Green();
  int pen_b = 255 - Color.Blue();
  if (geomType == LAYER_POINT)
    {
      Pen = gr->CreatePen(wxPen(wxColour(pen_r, pen_g, pen_b)));
      Brush = gr->CreateBrush(wxBrush(Color));
    }
  if (geomType == LAYER_LINESTRING)
    {
      Pen = gr->CreatePen(wxPen(Color, Size));
    }
  if (geomType == LAYER_POLYGON)
    {
      Pen = gr->CreatePen(wxPen(wxColour(0, 0, 0)));
      Brush = gr->CreateBrush(wxBrush(Color));
    }
}

MapLayer::MapLayer(LayerObject * org)
{
//
// constructor
//
  RasterliteHandle = NULL;
  LayerView = org->IsLayerView();
  LayerVirtual = org->IsLayerVirtual();
  Type = org->GetType();
  GeometryType = org->GetGeometryType();
  TableName = org->GetTableName();
  GeometryColumn = org->GetGeometryColumn();
  DescName = org->GetDescName();
  Srid = org->GetSrid();
  Network = org->IsNetwork();
  Visible = org->IsVisible();
  Identify = org->IsIdentify();
  if (org->IsEditingEnabled() == false)
    ReadOnly = true;
  else
    ReadOnly = false;
  Reproject = org->IsReproject();
  AlwaysVisible = org->IsAlwaysVisible();
  MinScale = org->GetMinScale();
  MaxScale = org->GetMaxScale();
  SymbolId = org->GetSymbolId();
  Symbol = NULL;
  ForegroundColor = org->GetForegroundColor();
  BackgroundColor = org->GetBackgroundColor();
  LineColor = org->GetLineColor();
  LineThickness = org->GetLineThickness();
  LineStyle = org->GetLineStyle();
  DrawBorder = org->DrawBorderOk();
  ToFill = org->IsToFill();
  SolidFilling = org->SolidFillingOk();
  FillColor = org->GetFillColor();
  PatternId = org->GetPatternId();
  Pattern = NULL;
  LabelColumn = org->GetLabelColumn();
  MapLabeling = org->IsMapLabelingEnabled();
  LabelColor = org->GetLabelColor();
  LabelPointSize = org->GetLabelPointSize();
  LabelFontBold = org->IsLabelFontBold();
  LabelFontItalic = org->IsLabelFontItalic();
  LabelFontUnderlined = org->IsLabelFontUnderlined();
  LabelFontOutlined = org->IsLabelFontOutlined();
  LabelOrderByColumn = org->GetLabelOrderByColumn();
  LabelOrderByDescending = org->IsLabelOrderByDescending();
  LabelAlwaysVisible = org->IsLabelAlwaysVisible();
  LabelMinScale = org->GetLabelMinScale();
  LabelMaxScale = org->GetLabelMaxScale();
  LabelAntiOverlap = org->IsLabelAntiOverlapEnabled();
  ClassifyColumn = org->GetClassifyColumn();
  First = NULL;
  Last = NULL;
  Next = NULL;
}

MapLayer::MapLayer(wxColour & color, int thickness)
{
//
// constructor {Routing marker]
//
  GeometryType = LAYER_LINESTRING;
  LayerView = false;
  LayerVirtual = false;
  LineColor = color;
  LineThickness = thickness;
  DrawBorder = true;
  ToFill = false;
  RasterliteHandle = NULL;
  Symbol = NULL;
  Pattern = NULL;
  First = NULL;
  Last = NULL;
  Next = NULL;
}

MapLayer::~MapLayer()
{
//
// destructor
//
  MapSubClass *p;
  MapSubClass *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
  if (Symbol)
    delete Symbol;
  if (Pattern)
    delete Pattern;
  if (RasterliteHandle)
    rasterliteClose(RasterliteHandle);
}

void MapLayer::Add(LayerObject * obj)
{
// inserting a SubClass
  MapSubClass *p = new MapSubClass(obj);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

bool MapLayer::IsVisible(int scale)
{
// 
// testing the scale related visibility
//
  if (AlwaysVisible == true)
    return true;
  if (scale >= MinScale && scale <= MaxScale)
    return true;
  return false;
}

bool MapLayer::AreLabelsVisible(int scale)
{
// 
// testing the scale related Labels visibility
//
  if (LabelAlwaysVisible == true)
    return true;
  if (scale >= LabelMinScale && scale <= LabelMaxScale)
    return true;
  return false;
}

MapSubClass *MapLayer::GetSubClass(double value)
{
// evaluating SubClasses by value
  MapSubClass *sub = First;
  while (sub)
    {
      if (sub->OkValue(value) == true)
        return sub;
      sub = sub->GetNext();
    }
  return NULL;
}

MapSubClass *MapLayer::GetSubClass(wxString & value)
{
// evaluating SubClasses by value
  MapSubClass *sub = First;
  while (sub)
    {
      if (sub->OkValue(value) == true)
        return sub;
      sub = sub->GetNext();
    }
  return NULL;
}

void MapLayer::CreateGraphicResources(wxGraphicsContext * gr)
{
// setting Pens, Brushes etc
  MapSubClass *sub;
  if (GeometryType == LAYER_POINT)
    {
      Pen = gr->CreatePen(wxColour(0, 255, 0));
      Brush = gr->CreateBrush(wxBrush(wxColour(255, 0, 0)));
      if (Symbol)
        {
          Symbol->GetBitmap(Bitmap, ForegroundColor, BackgroundColor);
          wxMask *mask = new wxMask(Symbol->GetMask());
          Bitmap.SetMask(mask);
        }
    }
  if (GeometryType == LAYER_LINESTRING)
    {
      Pen = gr->CreatePen(wxPen(LineColor, LineThickness, LineStyle));
    }
  if (GeometryType == LAYER_POLYGON)
    {
      Pen = gr->CreatePen(wxPen(LineColor, LineThickness, LineStyle));
      if (ToFill == true)
        {
          if (SolidFilling == true)
            {
              Brush = gr->CreateBrush(wxBrush(FillColor));
          } else
            {
              if (Pattern)
                {
                  wxBitmap bmp;
                  Pattern->GetBitmap(bmp, FillColor);
                  wxMask *mask = new wxMask(Pattern->GetMask());
                  bmp.SetMask(mask);
                  wxBrush brush(bmp);
                  Brush = gr->CreateBrush(brush);
              } else
                Brush = gr->CreateBrush(wxBrush(FillColor));
            }
        }
    }
  sub = First;
  while (sub)
    {
      sub->CreateGraphicResources(gr, GeometryType);
      sub = sub->GetNext();
    }
}

MapLayersList::~MapLayersList()
{
// destructor
  Flush();
}

void MapLayersList::Flush()
{
//
// flushing the list
//
  MapLayer *p;
  MapLayer *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
  First = NULL;
  Last = NULL;
}

void MapLayersList::Add(LayerObject * obj)
{
//
// inserting a Layer or SubClass into the list
//
  MapLayer *p;
  if (obj->GetType() == LAYER_SUB_CLASS)
    {
      // appending a SubClass to the current Layer
      if (First)
        First->Add(obj);
      return;
    }
// 
// inserting a Layer into the list
// Please note: we must reverse the zOrder
//
  p = new MapLayer(obj);
  p->SetNext(First);
  if (!Last)
    Last = p;
  First = p;
}

void MapLayersList::SetGraphicResources(MyImageList * symbols,
                                        MyImageList * patterns)
{
// setting Symbols and Patterns
  MyBitmap *bmp;
  MyBitmap *newBmp;
  MapLayer *p = First;
  while (p)
    {
      bmp = symbols->FindById(p->GetSymbolId());
      if (bmp)
        {
          newBmp = new MyBitmap(bmp);
          p->SetSymbol(newBmp);
        }
      bmp = patterns->FindById(p->GetPatternId());
      if (bmp)
        {
          newBmp = new MyBitmap(bmp);
          p->SetPattern(newBmp);
        }
      p = p->GetNext();
    }
}

void MapLayersList::CreateGraphicResources(MyImageList * symbols,
                                           MyImageList * patterns)
{
// setting Symbols and Patterns
  MyBitmap *bmp;
  MyBitmap *newBmp;
  MapLayer *p = First;
  while (p)
    {
      bmp = symbols->FindById(p->GetSymbolId());
      if (bmp)
        {
          if (bmp->IsFullColor() == true)
            newBmp = new MyBitmap(bmp);
          else
            newBmp =
              new MyBitmap(bmp, p->GetBackgroundColor(),
                           p->GetForegroundColor());
          p->SetSymbol(newBmp);
        }
      bmp = patterns->FindById(p->GetPatternId());
      if (bmp)
        {
          newBmp = new MyBitmap(bmp, p->GetFillColor());
          p->SetPattern(newBmp);
        }
      p = p->GetNext();
    }
}

void MapLayersList::CreateGraphicResources(wxGraphicsContext * gr)
{
// setting Symbols and Patterns
  MapLayer *p = First;
  while (p)
    {
      p->CreateGraphicResources(gr);
      p = p->GetNext();
    }
}

void MapLayersList::UpdateEditMode(wxString & table, wxString & geomColumn,
                                   bool mode)
{
// updating the edit mode for some Vector Layer
  MapLayer *p = First;
  while (p)
    {
      if (p->GetTableName() == table && p->GetGeometryColumn() == geomColumn)
        {
          p->SetReadOnly(mode);
          return;
        }
      p = p->GetNext();
    }
}

IdentifyEntity::IdentifyEntity(sqlite3_int64 rowid, gaiaGeomCollPtr geom,
                               wxString & label)
{
// constructor
  RowId = rowid;
  Geometry = geom;
  Label = label;
  Deleted = false;
  Changed = false;
  Next = NULL;
}

IdentifyEntity::~IdentifyEntity()
{
// destructor
  if (Geometry)
    gaiaFreeGeomColl(Geometry);
}

IdentifyEntitiesList::~IdentifyEntitiesList()
{
// destructor
  IdentifyEntity *p;
  IdentifyEntity *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

void IdentifyEntitiesList::Add(sqlite3_int64 rowId, gaiaGeomCollPtr geom,
                               wxString & label)
{
//
// adding an entity to the list
//
  IdentifyEntity *p = new IdentifyEntity(rowId, geom, label);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

int IdentifyEntitiesList::GetCount()
{
// counting the items
  int count = 0;
  IdentifyEntity *p;
  p = First;
  while (p)
    {
      count++;
      p = p->GetNext();
    }
  return count;
}

IdentifyEntity *IdentifyEntitiesList::GetItemByPos(int index)
{
// retrieving an item by its position
  int count = 0;
  IdentifyEntity *p;
  p = First;
  while (p)
    {
      if (index == count)
        return p;
      count++;
      p = p->GetNext();
    }
  return NULL;
}

void MarkerGraphicResource::Init(MapLayer * layer)
{
// initializing the marker graphic
  DrawBorder = layer->DrawBorderOk();
  ToFill = layer->IsToFill();
  LineColor = wxColour(0, 255, 0, 64);
  LineThickness = 1;
  FillColor = wxColour(255, 0, 0, 64);
  if (layer->GetGeometryType() == LAYER_LINESTRING)
    {
      int r = layer->GetLineColor().Red();
      int g = layer->GetLineColor().Green();
      int b = layer->GetLineColor().Blue();
      int a = layer->GetLineColor().Alpha();
      LineColor = wxColour(r, g, b, a);
      LineThickness = layer->GetLineThickness() * 3;
      FillColor = wxColour(255, 0, 0);
    }
  if (layer->GetGeometryType() == LAYER_POLYGON)
    {
      if (layer->DrawBorderOk() == true)
        {
          int r = layer->GetLineColor().Red();
          int g = layer->GetLineColor().Green();
          int b = layer->GetLineColor().Blue();
          LineColor = wxColour(r, g, b);
          if (layer->IsToFill() == false)
            LineThickness = layer->GetLineThickness() * 3;
          else
            LineThickness = layer->GetLineThickness();
        }
      if (layer->IsToFill() == true && layer->SolidFillingOk() == true)
        {
          int r = 255 - layer->GetFillColor().Red();
          int g = 255 - layer->GetFillColor().Green();
          int b = 255 - layer->GetFillColor().Blue();
          FillColor = wxColour(r, g, b);
        }
    }
  Ok = true;
}


void MarkerGraphicResource::CreateGraphicResources(wxGraphicsContext * gr)
{
// setting Pens, Brushes etc
  Pen = gr->CreatePen(wxPen(LineColor, LineThickness, wxSOLID));
  Brush = gr->CreateBrush(wxBrush(FillColor));
}

void MyVariant::Copy(MyVariant * other)
{
// 
// transfers a BLOB value
//
  if (other->Type != MY_BLOB_VARIANT)
    return;
  if (!(other->Blob))
    return;
  if (Blob)
    delete[]Blob;
  Type = MY_BLOB_VARIANT;
  BlobSize = other->BlobSize;
  Blob = other->Blob;
  other->Type = MY_NULL_VARIANT;
  other->Blob = NULL;
  other->BlobSize = 0;
}

bool MyVariant::Equals(MyVariant * other)
{
//
// checks if two variants are identical
//
  if (this->GetType() == other->GetType())
    {
      if (other->GetType() == MY_INT_VARIANT)
        {
          if (other->GetIntValue() != this->GetIntValue())
            return false;
      } else if (other->GetType() == MY_DBL_VARIANT)
        {
          if (other->GetDblValue() != this->GetDblValue())
            return false;
      } else if (other->GetType() == MY_TXT_VARIANT)
        {
          if (other->GetTxtValue() != this->GetTxtValue())
            return false;
      } else if (other->GetType() == MY_BLOB_VARIANT)
        {
          if (other->GetBlobSize() != this->GetBlobSize())
            return false;
          if (memcmp(other->GetBlob(), this->GetBlob(), other->GetBlobSize()) !=
              0)
            return false;
        }
  } else
    return false;
  return true;
}

void MyVariant::Set(const unsigned char *text)
{
//
// sets a String value for this Variant value
//
  Type = MY_TXT_VARIANT;
  TxtValue = wxString::FromUTF8((const char *) text);
}

void MyVariant::Set(const void *blob, int size)
{
//
// sets a BLOB value for this Variant value
//
  if (size <= 0)
    return;
  Type = MY_BLOB_VARIANT;
  BlobSize = size;
  Blob = new unsigned char[size];
  memcpy(Blob, blob, size);
}

MyRowVariant::MyRowVariant()
{
  NumCols = 0;
  ColumnArray = NULL;
  Deleted = false;
  Next = NULL;
}


MyRowVariant::MyRowVariant(int cols)
{
  NumCols = cols;
  ColumnArray = new MyVariant[cols];
  Deleted = false;
  Next = NULL;
}

MyRowVariant::~MyRowVariant()
{
  if (ColumnArray)
    delete[]ColumnArray;
}

void MyRowVariant::Create(int cols)
{
//
// creating the row variant
//
  if (ColumnArray)
    delete[]ColumnArray;
  NumCols = cols;
  ColumnArray = new MyVariant[NumCols];
  Deleted = false;
}

void MyRowVariant::Set(int col, sqlite3_int64 value)
{
//
// setting an Integer value for the Nth column
//
  MyVariant *var;
  if (col < 0 || col >= NumCols)
    return;
  var = ColumnArray + col;
  var->Set(value);
}

void MyRowVariant::Set(int col, double value)
{
//
// setting a Double value for the Nth column
//
  MyVariant *var;
  if (col < 0 || col >= NumCols)
    return;
  var = ColumnArray + col;
  var->Set(value);
}

void MyRowVariant::Set(int col, const unsigned char *value)
{
//
// setting a String value for the Nth column
//
  MyVariant *var;
  if (col < 0 || col >= NumCols)
    return;
  var = ColumnArray + col;
  var->Set(value);
}

void MyRowVariant::Set(int col, const void *blob, int size)
{
//
// setting a BLOB value for the Nth column
//
  MyVariant *var;
  if (col < 0 || col >= NumCols)
    return;
  var = ColumnArray + col;
  var->Set(blob, size);
}

MyVariant *MyRowVariant::GetColumn(int col)
{
//
// returns a Column Variant Value
//
  MyVariant *var;
  if (col < 0 || col >= NumCols)
    return NULL;
  var = ColumnArray + col;
  return var;
}

MyVariantList::MyVariantList()
{
//
// constructor - result set container
//
  NumCols = 0;
  ColumnName = NULL;
  First = NULL;
  Last = NULL;
}

MyVariantList::~MyVariantList()
{
//
// destructor - result set container
//
  MyRowVariant *el;
  MyRowVariant *elN;
  if (ColumnName)
    delete[]ColumnName;
  el = First;
  while (el)
    {
      elN = el->GetNext();
      delete el;
      el = elN;
    }
}

int MyVariantList::GetRows()
{
//
// counting how many rows are there
//
  int cnt = 0;
  MyRowVariant *el = First;
  while (el)
    {
      cnt++;
      el = el->GetNext();
    }
  return cnt;
}

MyRowVariant *MyVariantList::Add(int columns)
{
//
// adds a row into the result set
//
  if (!NumCols)
    {
      NumCols = columns;
      ColumnName = new wxString[NumCols];
    }
  MyRowVariant *el = new MyRowVariant(columns);
  if (!First)
    First = el;
  if (Last)
    Last->SetNext(el);
  Last = el;
  return el;
}

void MyVariantList::SetColumnName(int col, const char *name)
{
//
// storing a column name
//
  if (col < 0 || col >= NumCols)
    return;
  int len = strlen(name);
  if (*name == '"' && *(name + len - 1) == '"')
    {
      // dequoting the column name
      char dequoted[1024];
      strcpy(dequoted, name);
      dequoted[len - 1] = '\0';
      ColumnName[col] = wxString::FromUTF8(dequoted + 1);
      return;
    }
  ColumnName[col] = wxString::FromUTF8(name);
}

wxString & MyVariantList::GetColumnName(int col)
{
//
// retrieving a column name
//
  return ColumnName[col];
}

MyBlobs::MyBlobs(int rows, int cols)
{
//
// constructor - a BLOB matrix
//
  int r;
  MyRowVariant *rowVar;
  NumRows = 0;
  NumCols = 0;
  Rows = NULL;
  if (rows < 1 || cols < 1)
    return;
  NumRows = rows;
  NumCols = cols;
  Rows = new MyRowVariant[rows];
  for (r = 0; r < rows; r++)
    {
      rowVar = Rows + r;
      rowVar->Create(cols);
    }
}

MyBlobs::~MyBlobs()
{
//
// destructor - a BLOB matrix
//
  if (Rows)
    delete[]Rows;
}

void MyBlobs::SetBlob(int row, int col, MyVariant * org)
{
//
// setting a BLOB value
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return;
  if (col < 0 || col >= NumCols)
    return;
  rowVar = Rows + row;
  if (!rowVar)
    return;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return;
  dest->Copy(org);
}

MyVariant *MyBlobs::GetBlob(int row, int col)
{
//
// return a BLOB value
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return NULL;
  if (col < 0 || col >= NumCols)
    return NULL;
  rowVar = Rows + row;
  if (!rowVar)
    return NULL;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return NULL;
  if (dest->GetType() != MY_BLOB_VARIANT)
    return NULL;
  return dest;
}

MyValues::MyValues(int rows, int cols)
{
//
// constructor - a generic values matrix
//
  int r;
  MyRowVariant *rowVar;
  NumRows = 0;
  NumCols = 0;
  Rows = NULL;
  if (rows < 1 || cols < 1)
    return;
  NumRows = rows;
  NumCols = cols;
  Rows = new MyRowVariant[rows];
  for (r = 0; r < rows; r++)
    {
      rowVar = Rows + r;
      rowVar->Create(cols);
    }
}

MyValues::~MyValues()
{
//
// destructor - a generic values matrix
//
  if (Rows)
    delete[]Rows;
}

void MyValues::SetError(int row, int col, bool mode)
{
//
// setting the Error status
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return;
  if (col < 0 || col >= NumCols)
    return;
  rowVar = Rows + row;
  if (!rowVar)
    return;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return;
  dest->SetError(mode);
}

void MyValues::SetValue(int row, int col)
{
//
// setting a NULL value
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return;
  if (col < 0 || col >= NumCols)
    return;
  rowVar = Rows + row;
  if (!rowVar)
    return;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return;
  dest->Clear();
}

void MyValues::SetValue(int row, int col, sqlite3_int64 value)
{
//
// setting an integer value
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return;
  if (col < 0 || col >= NumCols)
    return;
  rowVar = Rows + row;
  if (!rowVar)
    return;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return;
  dest->Set(value);
}

void MyValues::SetValue(int row, int col, double value)
{
//
// setting a double value
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return;
  if (col < 0 || col >= NumCols)
    return;
  rowVar = Rows + row;
  if (!rowVar)
    return;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return;
  dest->Set(value);
}

void MyValues::SetValue(int row, int col, wxString & value)
{
//
// setting a string value
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return;
  if (col < 0 || col >= NumCols)
    return;
  rowVar = Rows + row;
  if (!rowVar)
    return;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return;
  dest->Set(value);
}

void MyValues::SetValue(int row, int col, const void *blob, int size)
{
//
// setting a BLOB value
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return;
  if (col < 0 || col >= NumCols)
    return;
  rowVar = Rows + row;
  if (!rowVar)
    return;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return;
  dest->Set(blob, size);
}

MyVariant *MyValues::GetValue(int row, int col)
{
//
// return a generic value
//
  MyRowVariant *rowVar;
  MyVariant *dest;
  if (row < 0 || row >= NumRows)
    return NULL;
  if (col < 0 || col >= NumCols)
    return NULL;
  rowVar = Rows + row;
  if (!rowVar)
    return NULL;
  dest = rowVar->GetColumn(col);
  if (!dest)
    return NULL;
  return dest;
}

MyRowVariant *MyValues::GetRow(int row)
{
//
// return a row of generic values
//
  MyRowVariant *rowVar;
  if (row < 0 || row >= NumRows)
    return NULL;
  rowVar = Rows + row;
  return rowVar;
}

QueryColumn::QueryColumn(wxString & col, wxString & type, bool pk)
{
// constructor
  Column = col;
  Type = type;
  PrimaryKey = pk;
  NotNull = false;
  Hidden = false;
  Function = false;
  DescName = wxT("");
  DataType = -1;
  Length = -1;
  Decimals = -1;
  Next = NULL;
}

QueryColumn::QueryColumn(wxString & col, wxString & type, bool pk,
                         bool not_null)
{
// constructor
  Column = col;
  Type = type;
  PrimaryKey = pk;
  NotNull = not_null;
  Hidden = false;
  Function = false;
  DescName = wxT("");
  DataType = -1;
  Length = -1;
  Decimals = -1;
  Next = NULL;
}

void QueryColumn::SetHints(wxString & descName, int type, int len, int dec)
{
// setting hint values
  DescName = descName;
  DataType = type;
  Length = len;
  Decimals = dec;
}

bool QueryColumn::IsBlobColumn()
{
// checks if the given column is of the BLOB type
  char type[128];
  strcpy(type, GetType().ToUTF8());
  if (strcasecmp(type, "BLOB") == 0)
    return true;
  else
    return false;
}

QueryTable::QueryTable()
{
// constructor
  First = NULL;
  Last = NULL;
  ResetOrderBy();
}

QueryTable::~QueryTable()
{
// destructor
  QueryColumn *p;
  QueryColumn *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

void QueryTable::ResetWhereClause()
{
// resets the WHERE clause
  WhereColumn = wxT("");
  WhereType = WHERE_NONE;
}

void QueryTable::ResetOrderBy()
{
// resets the ORDER BY clause
  OrderBy1 = wxT("");
  Ascending1 = true;
  OrderBy2 = wxT("");
  Ascending2 = true;
  OrderBy3 = wxT("");
  Ascending3 = true;
}

void QueryTable::Add(wxString & col, wxString & type, bool pk)
{
// adding a new column
  QueryColumn *p = new QueryColumn(col, type, pk);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void QueryTable::Add(wxString & col, wxString & type, bool pk, bool not_null)
{
// adding a new column
  QueryColumn *p = new QueryColumn(col, type, pk, not_null);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void QueryTable::AddFunction(wxString & col, wxString & type)
{
// adding a new column [hidden]
  QueryColumn *p = new QueryColumn(col, type, false);
  p->SetHidden(true);
  p->SetFunction();
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

int QueryTable::GetCount()
{
// counting how many columns are there
  int count = 0;
  QueryColumn *p = First;
  while (p)
    {
      count++;
      p = p->GetNext();
    }
  return count;
}

void QueryTable::SetHiddenStatus(int index, bool mode)
{
  int count = 0;
  QueryColumn *p = First;
  while (p)
    {
      if (count == index)
        {
          p->SetHidden(mode);
          return;
        }
      count++;
      p = p->GetNext();
    }
}

void QueryTable::SetHints(wxString & col, wxString & desc, int type, int len,
                          int dec)
{
  QueryColumn *p = First;
  while (p)
    {
      if (p->GetColumn() == col)
        {
          p->SetHints(desc, type, len, dec);
          return;
        }
      p = p->GetNext();
    }
}

QueryColumn *QueryTable::FindAlias(wxString & col, bool useAlias)
{
  QueryColumn *p;
  if (useAlias == true)
    {
      p = First;
      while (p)
        {
          // trying to resolve the alias name
          if (p->GetDescName() == col)
            return p;
          p = p->GetNext();
        }
    }
  p = First;
  while (p)
    {
      // trying to resolve the plain column name
      if (p->GetColumn() == col)
        return p;
      p = p->GetNext();
    }
  return NULL;
}

QueryColumn *QueryTable::Find(wxString & col)
{
  QueryColumn *p = First;
  while (p)
    {
      if (p->GetColumn() == col)
        return p;
      p = p->GetNext();
    }
  return NULL;
}

QueryColumn *QueryTable::Find(int idx)
{
  int count = 0;
  QueryColumn *p = First;
  while (p)
    {
      if (count == idx)
        return p;
      count++;
      p = p->GetNext();
    }
  return NULL;
}

GridCellImage::GridCellImage(int maxHeight)
{
//
// a wxGridCellRenderer used for grid cells containing an image / thumbnail - constructor
//
  Image = wxImage();
  ImageSize.Set(maxHeight, maxHeight);
  Error = false;
  Changed = false;
}

GridCellImage::GridCellImage(unsigned char *blob, int blobSize, int maxHeight)
{
//
// a wxGridCellRenderer used for grid cells containing an image / thumbnail - constructor
//
  wxMemoryInputStream reader(blob, blobSize);
  Image = wxImage(reader);
  ImageSize.Set(maxHeight, maxHeight);
  Error = false;
  Changed = false;
}

GridCellImage::GridCellImage(const GridCellImage * org)
{
//
// copy constructor
//
  Image = org->Image.Copy();
  if (Image.IsOk() == true)
    ImageSize.Set(Image.GetWidth(), Image.GetHeight());
  else
    ImageSize.Set(32, 32);
  Error = false;
  Changed = false;
}

void GridCellImage::SetImage(unsigned char *blob, int blobSize)
{
//
// setting up a new image
//
  wxMemoryInputStream reader(blob, blobSize);
  Image = wxImage(reader);
}

void GridCellImage::NullImage()
{
//
// setting up a NULL image
//
  Image = wxImage();
}

void GridCellImage::Draw(wxGrid & grid, wxGridCellAttr & attr, wxDC & dc,
                         const wxRect & rect, int row, int col, bool isSelected)
{
// drawing the image / thumbnail for some cell
  wxGridCellRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);
  if (isSelected == false)
    {
      // initializing the cell background
      wxBrush checkedBrush;
      if (Error == true)
        checkedBrush.SetStipple(wxBitmap(checked_brush2_xpm));
      else if (Changed == true)
        checkedBrush.SetStipple(wxBitmap(checked_brush3_xpm));
      else
        checkedBrush.SetStipple(wxBitmap(checked_brush_xpm));
      checkedBrush.SetStyle(wxSTIPPLE);
      dc.SetBrush(checkedBrush);
      dc.DrawRectangle(rect.GetX() - 1, rect.GetY() - 1, rect.GetWidth() + 2,
                       rect.GetHeight() + 2);
    }
  if (Image.IsOk() == true)
    {
      wxImage scaledImg;
      if (ImageSize.GetWidth() >= Image.GetWidth()
          && ImageSize.GetHeight() >= Image.GetHeight())
        scaledImg = Image.Copy();
      else
        {
          // resizing the image [thumbnail]
          double horz = Image.GetWidth();
          double vert = Image.GetHeight();
          while (horz > ImageSize.GetWidth() || vert > ImageSize.GetHeight())
            {
              horz *= 0.9;
              vert *= 0.9;
            }
          scaledImg = Image.Scale((int) horz, (int) vert, wxIMAGE_QUALITY_HIGH);
        }
      wxBitmap bmp(scaledImg);
      int x = rect.GetX() + ((rect.GetWidth() - scaledImg.GetWidth()) / 2);
      int y = rect.GetY() + ((rect.GetHeight() - scaledImg.GetHeight()) / 2);
      dc.DrawBitmap(bmp, x, y, true);
    }
}

wxSize GridCellImage::GetBestSize(wxGrid & WXUNUSED(grid),
                                  wxGridCellAttr & WXUNUSED(attr),
                                  wxDC & WXUNUSED(dc), int WXUNUSED(row),
                                  int WXUNUSED(col))
{
// returning the required size to the parent grid
  return ImageSize;
}

wxGridCellRenderer *GridCellImage::Clone() const
{
// creating a copy of this renderer
  GridCellImage *copy = new GridCellImage(this);
  return copy;
}

void GeometriesToMark::Flush()
{
// cleaning up the list
  GeometryToMark *p;
  GeometryToMark *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
  First = NULL;
  Last = NULL;
}


void GeometriesToMark::Add(gaiaGeomCollPtr geom)
{
// inserting an item into the linked list
  GeometryToMark *p = new GeometryToMark(geom);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

TableColumn::TableColumn(wxString & col, wxString & desc, int type, bool pk,
                         bool notNull, int len, int decs)
{
// constructor
  Column = col;
  DescName = desc;
  Type = type;
  PrimaryKey = pk;
  NotNull = notNull;
  Length = len;
  Decimals = decs;
  Deleted = false;
  Exists = false;
  ToBeDeleted = false;
  ToBeInserted = false;
  ToBeUpdated = false;
  IntegerCount = 0;
  FloatCount = 0;
  TextCount = 0;
  BlobCount = 0;
  NullCount = 0;
  Next = NULL;
}

TableColumn::TableColumn(wxString & col, bool notNull, bool pk)
{
// constructor
  Column = col;
  DescName = wxT("");
  Type = SQLITE_TEXT;
  PrimaryKey = pk;
  NotNull = notNull;
  Length = 0;
  Decimals = 0;
  Deleted = false;
  Exists = false;
  ToBeDeleted = false;
  ToBeInserted = true;
  ToBeUpdated = false;
  IntegerCount = 0;
  FloatCount = 0;
  TextCount = 0;
  BlobCount = 0;
  NullCount = 0;
  Next = NULL;
}

void TableColumn::Reset()
{
// restting any pending switch
  if (ToBeDeleted == true)
    Deleted = true;
  ToBeDeleted = false;
  ToBeInserted = false;
  ToBeUpdated = false;
  Exists = true;
}

void TableColumn::Set(wxString & col, wxString & desc, int type, bool pk,
                      bool notNull, int len, int decs)
{
// setting up values
  Column = col;
  DescName = desc;
  Type = type;
  PrimaryKey = pk;
  NotNull = notNull;
  Length = len;
  Decimals = decs;
}

wxString & TableColumn::GetColumnDefs()
{
// returning the Column Defs as a string
  char dummy[128];
  int i;
  Defs = Column;
  if (Column.Len() < 16)
    {
      int ind = 0;
      for (i = Column.Len(); i < 16; i++)
        dummy[ind++] = ' ';
      dummy[ind] = '\0';
  } else
    strcpy(dummy, " ");
  Defs += wxString::FromUTF8(dummy);
  if (PrimaryKey == true)
    {
      Defs += wxT("INTEGER PRIMARY KEY AUTOINCREMENT");
      return Defs;
    }
  switch (Type)
    {
      case SQLITE_INTEGER:
        Defs += wxT("INTEGER ");
        Defs += wxT("             ");
        break;
      case SQLITE_DATE:
        Defs += wxT("DOUBLE  ");
        Defs += wxT("[DATE]       ");
        break;
      case SQLITE_DATETIME:
        Defs += wxT("DOUBLE  ");
        Defs += wxT("[DATETIME]   ");
        break;
      case SQLITE_FLOAT:
        Defs += wxT("DOUBLE  ");
        if (Decimals < 10)
          sprintf(dummy, "[decs=%d]     ", Decimals);
        else
          sprintf(dummy, "[decs=%d]    ", Decimals);
        Defs += wxString::FromUTF8(dummy);
        break;
      case SQLITE_TEXT:
        Defs += wxT("TEXT    ");
        if (Length < 10)
          sprintf(dummy, "[max=%d]      ", Length);
        else if (Length < 100)
          sprintf(dummy, "[max=%d]     ", Length);
        else
          sprintf(dummy, "[max=%d]    ", Length);
        Defs += wxString::FromUTF8(dummy);
        break;
      case SQLITE_BOOLEAN:
        Defs += wxT("INTEGER ");
        Defs += wxT("[BOOLEAN]    ");
        break;
      case SQLITE_IMAGE:
        Defs += wxT("BLOB    ");
        Defs += wxT("[IMAGE]      ");
        break;
      default:
        Defs += wxT("BLOB    ");
        Defs += wxT("[generic]    ");
        break;
    };
  if (NotNull == true)
    Defs += wxT(" NOT NULL");
  return Defs;
}

wxString & TableColumn::GetColumnTypeAsConstant()
{
// returning the Column Type as a string
  ColumnTypeAsConstant = wxT("");
  switch (Type)
    {
      case SQLITE_INTEGER:
        ColumnTypeAsConstant = wxT("INTEGER");
        break;
      case SQLITE_DATE:
        ColumnTypeAsConstant = wxT("DATE");
        break;
      case SQLITE_DATETIME:
        ColumnTypeAsConstant = wxT("DATETIME");
        break;
      case SQLITE_FLOAT:
        ColumnTypeAsConstant = wxT("DOUBLE");
        break;
      case SQLITE_TEXT:
        ColumnTypeAsConstant = wxT("TEXT");
        break;
      case SQLITE_BOOLEAN:
        ColumnTypeAsConstant = wxT("BOOLEAN");
        break;
      case SQLITE_IMAGE:
        ColumnTypeAsConstant = wxT("IMAGE");
        break;
      default:
        ColumnTypeAsConstant = wxT("BLOB");
        break;
    };
  return ColumnTypeAsConstant;
}

void TableColumn::AddTypeCount(char *type, int count)
{
// incrementing the DataType Count
  if (!type)
    {
      NullCount += count;
      return;
    }
  if (strcasecmp(type, "integer") == 0)
    {
      IntegerCount += count;
      return;
    }
  if (strcasecmp(type, "real") == 0)
    {
      FloatCount += count;
      return;
    }
  if (strcasecmp(type, "text") == 0)
    {
      TextCount += count;
      return;
    }
  if (strcasecmp(type, "blob") == 0)
    {
      BlobCount += count;
      return;
    }
  NullCount += count;
}

void TableColumn::GuessType()
{
// trying to guess the DataType [evaluating the DataType counters]
  if (IntegerCount > 0 && FloatCount == 0 && TextCount == 0 && BlobCount == 0)
    {
      Type = SQLITE_INTEGER;
      return;
    }
  if (IntegerCount == 0 && FloatCount > 0 && TextCount == 0 && BlobCount == 0)
    {
      Type = SQLITE_FLOAT;
      Decimals = 2;
      return;
    }
  if (IntegerCount == 0 && FloatCount == 0 && TextCount > 0 && BlobCount == 0)
    {
      Type = SQLITE_TEXT;
      Length = 40;
      return;
    }
  if (IntegerCount == 0 && FloatCount == 0 && TextCount == 0 && BlobCount > 0)
    {
      Type = SQLITE_BLOB;
      return;
    }
  if (IntegerCount > 0 && FloatCount > 0 && TextCount == 0 && BlobCount == 0)
    {
      Type = SQLITE_FLOAT;
      Decimals = 2;
      return;
    }
  Type = SQLITE_TEXT;
  Length = 40;
}

TableLayout::TableLayout()
{
// constructor
  TableName = wxT("");
  DescName = wxT("");
  GeometryColumn = wxT("");
  Srid = -1;
  First = NULL;
  Last = NULL;
}

TableLayout::~TableLayout()
{
// destructor
  TableColumn *p;
  TableColumn *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
}

void TableLayout::Set(wxString & name, wxString & descName,
                      wxString & geomColumn, int type, int srid)
{
// setting up values
  TableName = name;
  DescName = descName;
  GeometryColumn = geomColumn;
  GeometryType = type;
  Srid = srid;
}

void TableLayout::Add(wxString & col, wxString & desc, int type, bool pk,
                      bool notNull, int len, int decs)
{
// adding a new column
  TableColumn *p = new TableColumn(col, desc, type, pk, notNull, len, decs);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void TableLayout::AddExisting(wxString & col, wxString & desc, int type,
                              bool pk, bool notNull, int len, int decs)
{
// adding a new column
  TableColumn *p = new TableColumn(col, desc, type, pk, notNull, len, decs);
  p->SetExisting();
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void TableLayout::Add(wxString & col, bool notNull, bool pk)
{
// adding a new column
  TableColumn *p = First;
  while (p)
    {
      if (p->GetColumn() == col)
        {
          // confirming and completing an already defined Column
          p->Confirm(notNull, pk);
          return;
        }
      p = p->GetNext();
    }
  p = new TableColumn(col, notNull, pk);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

TableColumn *TableLayout::Find(int index)
{
// searching an item by its position
  int count = 0;
  TableColumn *p = First;
  while (p)
    {
      if (p->IsDeleted() == true)
        {
          p = p->GetNext();
          continue;
        }
      if (count == index)
        return p;
      count++;
      p = p->GetNext();
    }
  return NULL;
}

int TableLayout::Find(wxString & name)
{
// searching an item by its name
  int count = 0;
  TableColumn *p = First;
  while (p)
    {
      if (p->IsDeleted() == true)
        {
          p = p->GetNext();
          continue;
        }
      if (name == p->GetColumn())
        return count;
      count++;
      p = p->GetNext();
    }
  return wxNOT_FOUND;
}

int TableLayout::GetCount()
{
// counting how many columns are there
  int count = 0;
  TableColumn *p = First;
  while (p)
    {
      if (p->IsDeleted() == false)
        count++;
      p = p->GetNext();
    }
  return count;
}

bool TableLayout::IsDuplicate(wxString & name)
{
// checking if this column name is a duplicate one
  TableColumn *p = First;
  while (p)
    {
      if (p->IsDeleted() == false)
        {
          if (p->GetColumn() == name)
            return true;
        }
      p = p->GetNext();
    }
  return false;
}

bool TableLayout::IsDuplicate(TableColumn * pColumn, wxString & name)
{
// checking if this column name is a duplicate one
  TableColumn *p = First;
  while (p)
    {
      if (p->IsDeleted() == false && pColumn != p)
        {
          if (p->GetColumn() == name)
            return true;
        }
      p = p->GetNext();
    }
  return false;
}

MyRowGroup::MyRowGroup()
{
// constructor
  RowArray = NULL;
  RelocationArray = NULL;
  MaxIndex = 0;
  NextIndex = 0;
  ApplyRelocation = false;
}

MyRowGroup::~MyRowGroup()
{
// destructor
  if (RowArray)
    delete[]RowArray;
  if (RelocationArray)
    delete[]RelocationArray;
}

void MyRowGroup::Reset()
{
// resetting to initial state
  int i;
  if (RowArray)
    {
      for (i = 0; i < MaxIndex; i++)
        *(RowArray + i) = -1;
    }
  NextIndex = 0;
}

void MyRowGroup::RelocationReset()
{
// resetting relocation to initial state
  int i;
  ApplyRelocation = false;
  if (RelocationArray)
    {
      for (i = 0; i < MaxIndex; i++)
        *(RelocationArray + i) = -1;
    }
}

void MyRowGroup::Create(int items)
{
// actual creation
  int i;
  RowArray = new int[items];
  RelocationArray = new int[items];
  MaxIndex = items;
  NextIndex = 0;
  for (i = 0; i < MaxIndex; i++)
    {
      *(RowArray + i) = -1;
      *(RelocationArray + i) = -1;
    }
  ApplyRelocation = false;
}

void MyRowGroup::Insert(int row_id)
{
// inserting a row index
  if (NextIndex < MaxIndex)
    {
      *(RowArray + NextIndex) = row_id;
      NextIndex++;
    }
}

bool MyRowGroup::IsSelected(int row_id)
{
// testing if some row index is a selected one
  int i;
  for (i = 0; i < NextIndex; i++)
    {
      if (*(RowArray + i) == row_id)
        return true;
    }
  return false;
}

void MyRowGroup::Relocate(int oldPos, int newPos)
{
// relocating a row
  if (newPos >= 0 && newPos < MaxIndex)
    {
      *(RelocationArray + newPos) = oldPos;
      ApplyRelocation = true;
    }
}

int MyRowGroup::GetBaseIndex(int newPos)
{
// retrieving the base index
  if (ApplyRelocation == false)
    return newPos;
  if (newPos >= 0 && newPos < MaxIndex)
    return *(RelocationArray + newPos);
  else
    return -1;
}

NetworkParams::NetworkParams()
{
  Srid = -1;
  TextNodes = false;
  MainRTree = false;
  AuxNodesRTree = false;
}

void NetworkParams::SwapFromTo()
{
// swapping From->To [return trip]
  NetworkNode node;
  node.Set(&NodeFrom);
  NodeFrom.Set(&NodeTo);
  NodeTo.Set(&node);
}

RoutingSolution::RoutingSolution()
{
  First = NULL;
  Last = NULL;
  Geometry = NULL;
  Valid = false;
  RoutingAlgorithm = wxT("Dijkstra");
}

void RoutingSolution::CleanUp()
{
// cleaning up the solution
  SolutionArc *p;
  SolutionArc *pN;
  p = First;
  while (p)
    {
      pN = p->GetNext();
      delete p;
      p = pN;
    }
  First = NULL;
  Last = NULL;
  if (Geometry)
    gaiaFreeGeomColl(Geometry);
  Geometry = NULL;
  Valid = false;
}

void RoutingSolution::CheckValid()
{
// checking for solution validity
  Valid = false;
  if (!Geometry)
    return;
  if (GetCount() > 0)
    Valid = true;
}

void RoutingSolution::SetFromTo(sqlite3_int64 from, sqlite3_int64 to)
{
  NodeFromId = from;
  NodeToId = to;
}

void RoutingSolution::SetFromTo(wxString & from, wxString & to)
{
  NodeFromText = from;
  NodeToText = to;
}

void RoutingSolution::TimeStart()
{
// setting the Start time
  StartTime = wxDateTime::UNow();
}

void RoutingSolution::TimeStop()
{
// setting the Stop time
  StopTime = wxDateTime::UNow();
}

void RoutingSolution::GetElapsedTime(wxString & str)
{
// formatting the elapsed time
  wxTimeSpan tm = StopTime.Subtract(StartTime);
  str = tm.Format(wxT("%M:%S:%l"));
}

int RoutingSolution::GetCount()
{
// counting how many arcs are in this solution
  SolutionArc *p;
  int count = 0;
  p = First;
  while (p)
    {
      count++;
      p = p->GetNext();
    }
  return count;
}

SolutionArc *RoutingSolution::FindByPos(int pos)
{
// return an arc identified by its relative position
  SolutionArc *p;
  int count = 0;
  p = First;
  while (p)
    {
      if (count == pos)
        return p;
      count++;
      p = p->GetNext();
    }
  return NULL;
}

void RoutingSolution::Add(sqlite3_int64 id, sqlite3_int64 from,
                          sqlite3_int64 to, double cost,
                          const unsigned char *name)
{
// adding an arc [int IDs]
  SolutionArc *p = new SolutionArc(id, from, to, cost, (const char *) name);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

void RoutingSolution::Add(sqlite3_int64 id, const unsigned char *from,
                          const unsigned char *to, double cost,
                          const unsigned char *name)
{
// adding an arc [text codes]
  SolutionArc *p =
    new SolutionArc(id, (const char *) from, (const char *) to, cost,
                    (const char *) name);
  if (!First)
    First = p;
  if (Last)
    Last->SetNext(p);
  Last = p;
}

SolutionArc::SolutionArc(sqlite3_int64 id, sqlite3_int64 from, sqlite3_int64 to,
                         double cost, const char *name)
{
// arc constructor [int IDs]
  ArcId = id;
  NodeFromId = from;
  NodeToId = to;
  Cost = cost;
  if (!name)
    Name = wxT("");
  else
    Name = wxString::FromUTF8(name);
  Next = NULL;
}

SolutionArc::SolutionArc(sqlite3_int64 id, const char *from, const char *to,
                         double cost, const char *name)
{
// arc constructor [text codes]
  ArcId = id;
  NodeFromText = wxString::FromUTF8(from);
  NodeToText = wxString::FromUTF8(to);
  Cost = cost;
  if (!name)
    Name = wxT("");
  else
    Name = wxString::FromUTF8(name);
  Next = NULL;
}

MapLabelCandidate::MapLabelCandidate(double x, double y, double rotation,
                                     gaiaGeomCollPtr geom)
{
// Label Candidate Position - constructor
  X = x;
  Y = y;
  Rotation = rotation;
  Geometry = geom;
  Valid = true;
  Next = NULL;
}

MapLabelCandidate::~MapLabelCandidate()
{
//
// destructor
//
  if (Geometry)
    gaiaFreeGeomColl(Geometry);
}

bool MapLabelCandidate::EvaluateCollision(gaiaGeomCollPtr other)
{
//
// evaluating a possible collision between labels
//
  if (gaiaMbrsIntersects(Geometry, other))
    {
      Valid = false;
      return true;
    }
  return false;
}

gaiaGeomCollPtr MapLabelCandidate::TransferGeometry()
{
  gaiaGeomCollPtr geom = Geometry;
  Geometry = NULL;
  return geom;
}

MapLabel::MapLabel(MapLayer * layer, wxString & label, double width,
                   double height, double pixelRatio, bool noCollision)
{
//
// constructor: Map Label
//
  Layer = layer;
  Label = label;
  Geometry = NULL;
  Width = width;
  Height = height;
  PixelRatio = pixelRatio;
  Valid = false;
  NoCollision = noCollision;
  First = NULL;
  Last = NULL;
  Next = NULL;
}

MapLabel::~MapLabel()
{
//
// destructor
//
  DeleteCandidates();
  if (Geometry)
    gaiaFreeGeomColl(Geometry);
}

void MapLabel::AddCandidate(double x, double y, double rotation,
                            gaiaGeomCollPtr geom)
{
//
// inserting a Label candidate position
//
  MapLabelCandidate *pC = new MapLabelCandidate(x, y, rotation, geom);
  if (!First)
    First = pC;
  if (Last)
    Last->SetNext(pC);
  Last = pC;
}

void MapLabel::DeleteCandidates()
{
//
// deleting Label candidate positions
//
  MapLabelCandidate *pC;
  MapLabelCandidate *pCn;
  pC = First;
  while (pC)
    {
      pC = pC->GetNext();
      delete pC;
      pCn = pC;
    }
  First = NULL;
  Last = NULL;
}

gaiaGeomCollPtr MapLabel::CreateRectangle(double x, double y)
{
// creating a Rectangle representing a Label Position
  gaiaGeomCollPtr geom = gaiaAllocGeomColl();
  geom->DeclaredType = GAIA_POLYGON;
  gaiaPolygonPtr pg = gaiaAddPolygonToGeomColl(geom, 5, 0);
  gaiaRingPtr rng = pg->Exterior;
// creating the label rectangle
  gaiaSetPoint(rng->Coords, 0, x, y);
  gaiaSetPoint(rng->Coords, 1, x + (Width * PixelRatio), y);
  gaiaSetPoint(rng->Coords, 2, x + (Width * PixelRatio),
               y - (Height * PixelRatio));
  gaiaSetPoint(rng->Coords, 3, x, y - (Height * PixelRatio));
  gaiaSetPoint(rng->Coords, 4, x, y);
  gaiaMbrGeometry(geom);
  return geom;
}

gaiaGeomCollPtr MapLabel::CreateRectangle(double cx, double cy, double rotation)
{
// creating a Rectangle representing a Label Position
  double x;
  double y;
  double sinW = (Width * PixelRatio) * sin(rotation);
  double cosW = (Width * PixelRatio) * cos(rotation);
  double sinH = (Height * PixelRatio) * sin(rotation);
  double cosH = (Height * PixelRatio) * cos(rotation);
  double baseX = cx - ((sinH + cosW) / 2.0);
  double baseY = cy - ((cosH + sinW) / 2.0);
  gaiaGeomCollPtr geom = gaiaAllocGeomColl();
  geom->DeclaredType = GAIA_POLYGON;
  gaiaPolygonPtr pg = gaiaAddPolygonToGeomColl(geom, 5, 0);
  gaiaRingPtr rng = pg->Exterior;
// creating the label rectangle
  x = baseX + sinH;
  y = baseY;
  gaiaSetPoint(rng->Coords, 0, x, y);
  gaiaSetPoint(rng->Coords, 4, x, y);
  x = baseX + sinH + cosW;
  y = baseY + sinW;
  gaiaSetPoint(rng->Coords, 1, x, y);
  x = baseX + cosW;
  y = baseY + (cosH + sinW);
  gaiaSetPoint(rng->Coords, 2, x, y);
  x = baseX;
  y = baseY + cosH;
  gaiaSetPoint(rng->Coords, 3, x, y);
  gaiaMbrGeometry(geom);
  return geom;
}

void MapLabel::AssignLabelPosition(double x, double y)
{
// setting the final Label Position
  if (Geometry)
    gaiaFreeGeomColl(Geometry);
  Geometry = CreateRectangle(x, y);
  X = x;
  Y = y;
  Rotation = 0.0;
  Valid = true;
  DeleteCandidates();
}

void MapLabel::AssignLabelPosition(double cx, double cy, double rotation)
{
// setting the final Label Position
  double x;
  double y;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  if (Geometry)
    gaiaFreeGeomColl(Geometry);
  Geometry = CreateRectangle(cx, cy, rotation);
  pg = Geometry->FirstPolygon;
  rng = pg->Exterior;
  gaiaGetPoint(rng->Coords, 3, &x, &y);
  X = x;
  Y = y;
  Rotation = rotation;
  Valid = true;
  DeleteCandidates();
}

void MapLabel::AssignLabelPosition(MapLabelCandidate * candidate)
{
// setting the final Label Position
  if (Geometry)
    gaiaFreeGeomColl(Geometry);
  Geometry = candidate->TransferGeometry();
  X = candidate->GetX();
  Y = candidate->GetY();
  Rotation = candidate->GetRotation();
  Valid = true;
  DeleteCandidates();
}

bool MapLabel::GetBaseline(double *x0, double *y0, double *x1, double *y1)
{
// retrieving the label baseline
  if (!Geometry)
    return false;
  gaiaPolygonPtr pg = Geometry->FirstPolygon;
  if (!pg)
    return false;
  gaiaRingPtr rng = pg->Exterior;
  if (!rng)
    return false;
  if (rng->Points != 5)
    return false;
  double xx0;
  double yy0;
  double xx1;
  double yy1;
  gaiaGetPoint(rng->Coords, 0, &xx0, &yy0);
  gaiaGetPoint(rng->Coords, 1, &xx1, &yy1);
  *x0 = xx0;
  *y0 = yy0;
  *x1 = xx1;
  *y1 = yy1;
  return true;
}

bool MapLabel::CheckSize(gaiaGeomCollPtr geom)
{
// checking the Label size
  return CheckSize(geom, Geometry);
}

bool MapLabel::CheckSize(gaiaGeomCollPtr geom, gaiaGeomCollPtr label)
{
// checking the Label size
  gaiaRingPtr ring;
  gaiaRingPtr pgRing;
  double x;
  double y;
  int count = 0;
  int count1 = 0;
  int count2 = 0;
  if (!label)
    return false;
  if (!(label->FirstPolygon))
    return false;
  ring = label->FirstPolygon->Exterior;
  if (!ring)
    return false;
  if (!geom)
    return false;
  if (!(geom->FirstPolygon))
    return false;
  pgRing = geom->FirstPolygon->Exterior;
  if (!pgRing)
    return false;
  if (ring->Points != 5 || ring->DimensionModel != GAIA_XY)
    return false;
  gaiaGetPoint(ring->Coords, 0, &x, &y);
  if (gaiaIsPointOnRingSurface(pgRing, x, y))
    {
      count++;
      count1++;
    }
  gaiaGetPoint(ring->Coords, 1, &x, &y);
  if (gaiaIsPointOnRingSurface(pgRing, x, y))
    {
      count++;
      count2++;
    }
  gaiaGetPoint(ring->Coords, 2, &x, &y);
  if (!gaiaIsPointOnRingSurface(pgRing, x, y))
    {
      count++;
      count1++;
    }
  gaiaGetPoint(ring->Coords, 3, &x, &y);
  if (gaiaIsPointOnRingSurface(pgRing, x, y))
    {
      count++;
      count2++;
    }
  if (count >= 3)
    return true;
  if (count1 == 2)
    return true;
  if (count2 == 2)
    return true;
  return false;
}

void MapLabel::LineLabelCentered(gaiaGeomCollPtr geom, double pixelRatio)
{
// Line Label Position - single candidate
  LineLabelAux candidates(pixelRatio);
  candidates.Feed(this, geom);
  if (candidates.GetCount() == 0)
    {
      Valid = false;
      return;
    }
  LineLabelItem *lbl = candidates.GetItem();
  AssignLabelPosition(lbl->GetX(), lbl->GetY(), lbl->GetRotation());
}

void MapLabel::LineLabelMultiple(gaiaGeomCollPtr geom, double pixelRatio)
{
// Line Label Position - multiple candidates
  double x;
  double y;
  gaiaPolygonPtr pg;
  gaiaRingPtr rng;
  LineLabelAux candidates(pixelRatio);
  candidates.Feed(this, geom);
  if (candidates.GetCount() == 0)
    {
      Valid = false;
      return;
    }
  gaiaGeomCollPtr g;
  LineLabelItem *firstLabel = candidates.GetItem();
  if (firstLabel)
    {
      g =
        CreateRectangle(firstLabel->GetX(), firstLabel->GetY(),
                        firstLabel->GetRotation());
      pg = g->FirstPolygon;
      rng = pg->Exterior;
      gaiaGetPoint(rng->Coords, 3, &x, &y);
      AddCandidate(x, y, firstLabel->GetRotation(), g);
    }
  LineLabelItem *secondLabel = candidates.GetFirst();
  if (secondLabel && (firstLabel != secondLabel))
    {
      g =
        CreateRectangle(secondLabel->GetX(), secondLabel->GetY(),
                        secondLabel->GetRotation());
      pg = g->FirstPolygon;
      rng = pg->Exterior;
      gaiaGetPoint(rng->Coords, 3, &x, &y);
      AddCandidate(x, y, secondLabel->GetRotation(), g);
    }
  LineLabelItem *thirdLabel = candidates.GetLast();
  if (secondLabel && (firstLabel != thirdLabel && secondLabel != thirdLabel))
    {
      g =
        CreateRectangle(thirdLabel->GetX(), thirdLabel->GetY(),
                        thirdLabel->GetRotation());
      pg = g->FirstPolygon;
      rng = pg->Exterior;
      gaiaGetPoint(rng->Coords, 3, &x, &y);
      AddCandidate(x, y, thirdLabel->GetRotation(), g);
    }
}

MapLabelList::MapLabelList(double pixelRatio)
{
// label list constructor
  PixelRatio = pixelRatio;
  First = NULL;
  Last = NULL;
}

MapLabelList::~MapLabelList()
{
// label list destructor
  MapLabel *pL;
  MapLabel *pLn;
  pL = First;
  while (pL)
    {
      pLn = pL->GetNext();
      delete pL;
      pL = pLn;
    }
}

void MapLabelList::Add(MapLayer * layer, wxString & label, gaiaGeomCollPtr geom,
                       double width, double height, bool noCollision)
{
// adding a Map Label
  double x;
  double y;
  double cx;
  double cy;
  gaiaGeomCollPtr g;
  MapLabel *pL = NULL;
  if (geom->DeclaredType == GAIA_POINT)
    {
      // inserting a POINT label
      pL = new MapLabel(layer, label, width, height, PixelRatio, noCollision);
      if (noCollision == false)
        {
          // directly setting the label position
          x = geom->FirstPoint->X - ((width / 2.0) * PixelRatio);
          y = geom->FirstPoint->Y - (5.0 * PixelRatio);
          pL->AssignLabelPosition(x, y);
      } else
        {
          // setting the Label Candidate Positions [centered - down]
          x = geom->FirstPoint->X - ((width / 2.0) * PixelRatio);
          y = geom->FirstPoint->Y - (5.0 * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
          // centered - middle
          x = geom->FirstPoint->X - ((width / 2.0) * PixelRatio);
          y = geom->FirstPoint->Y + ((height / 2.0) * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
          // centered - up
          x = geom->FirstPoint->X - ((width / 2.0) * PixelRatio);
          y = geom->FirstPoint->Y + ((height + 5.0) * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
          // right - middle
          x = geom->FirstPoint->X + (5.0 * PixelRatio);
          y = geom->FirstPoint->Y + ((height / 2.0) * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
          // right - up
          x = geom->FirstPoint->X + (5.0 * PixelRatio);
          y = geom->FirstPoint->Y + ((height + 5.0) * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
          // right - down
          x = geom->FirstPoint->X + (5.0 * PixelRatio);
          y = geom->FirstPoint->Y - (5.0 * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
          // left - middle
          x = geom->FirstPoint->X - ((width + 5.0) * PixelRatio);
          y = geom->FirstPoint->Y + ((height / 2.0) * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
          // left - up
          x = geom->FirstPoint->X - ((width + 5.0) * PixelRatio);
          y = geom->FirstPoint->Y + ((height + 5.0) * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
          // left - down
          x = geom->FirstPoint->X - ((width + 5.0) * PixelRatio);
          y = geom->FirstPoint->Y - (5.0 * PixelRatio);
          g = pL->CreateRectangle(x, y);
          pL->AddCandidate(x, y, 0.0, g);
        }
    }
  if (geom->DeclaredType == GAIA_LINESTRING)
    {
      // inserting a LINESTRING label
      pL = new MapLabel(layer, label, width, height, PixelRatio, noCollision);
      if (noCollision == false)
        {
          // directly setting the label position
          pL->LineLabelCentered(geom, PixelRatio);
      } else
        {
          // setting the Label Candidate Positions [centered - down]
          pL->LineLabelMultiple(geom, PixelRatio);
        }
    }
  if (geom->DeclaredType == GAIA_POLYGON)
    {
      // inserting a POLYGON label
      pL = new MapLabel(layer, label, width, height, PixelRatio, noCollision);
      if (noCollision == false)
        {
          // directly setting the label position
          if (!gaiaGeomCollCentroid(geom, &cx, &cy))
            goto stop;
          if (!gaiaIsPointOnRingSurface(geom->FirstPolygon->Exterior, cx, cy))
            {
              // centroid falls outside polygon - choosing an alternative
              if (!gaiaGetPointOnSurface(geom, &cx, &cy))
                goto stop;
            }
          pL->AssignLabelPosition(cx, cy, 0.0);
          if (pL->CheckSize(geom) == false)
            pL->Invalidate();
      } else
        {
          // setting the Label Candidate Positions 
          double toRads = .0174532925199432958;
          double angle;
          gaiaPolygonPtr pg;
          gaiaRingPtr rng;
          if (!gaiaGeomCollCentroid(geom, &cx, &cy))
            goto stop;
          if (!gaiaIsPointOnRingSurface(geom->FirstPolygon->Exterior, cx, cy))
            {
              // centroid falls outside polygon - choosing an alternative
              if (!gaiaGetPointOnSurface(geom, &cx, &cy))
                goto stop;
            }
          // horizontal
          angle = 0.0;
          g = pL->CreateRectangle(cx, cy, angle);
          if (pL->CheckSize(geom, g) == true)
            {
              pg = g->FirstPolygon;
              rng = pg->Exterior;
              gaiaGetPoint(rng->Coords, 3, &x, &y);
              pL->AddCandidate(x, y, angle, g);
          } else
            gaiaFreeGeomColl(g);
          // +30 degs
          angle = 30.0 * toRads;
          g = pL->CreateRectangle(cx, cy, angle);
          if (pL->CheckSize(geom, g) == true)
            {
              pg = g->FirstPolygon;
              rng = pg->Exterior;
              gaiaGetPoint(rng->Coords, 3, &x, &y);
              pL->AddCandidate(x, y, angle, g);
          } else
            gaiaFreeGeomColl(g);
          // -30 degs
          angle = 330.0 * toRads;
          g = pL->CreateRectangle(cx, cy, angle);
          if (pL->CheckSize(geom, g) == true)
            {
              pg = g->FirstPolygon;
              rng = pg->Exterior;
              gaiaGetPoint(rng->Coords, 3, &x, &y);
              pL->AddCandidate(x, y, angle, g);
          } else
            gaiaFreeGeomColl(g);
          // +45 degs
          angle = 45.0 * toRads;
          g = pL->CreateRectangle(cx, cy, angle);
          if (pL->CheckSize(geom, g) == true)
            {
              pg = g->FirstPolygon;
              rng = pg->Exterior;
              gaiaGetPoint(rng->Coords, 3, &x, &y);
              pL->AddCandidate(x, y, angle, g);
          } else
            gaiaFreeGeomColl(g);
          // -45 degs
          angle = 315.0 * toRads;
          g = pL->CreateRectangle(cx, cy, angle);
          if (pL->CheckSize(geom, g) == true)
            {
              pg = g->FirstPolygon;
              rng = pg->Exterior;
              gaiaGetPoint(rng->Coords, 3, &x, &y);
              pL->AddCandidate(x, y, angle, g);
          } else
            gaiaFreeGeomColl(g);
          // +60 degs
          angle = 60.0 * toRads;
          g = pL->CreateRectangle(cx, cy, angle);
          if (pL->CheckSize(geom, g) == true)
            {
              pg = g->FirstPolygon;
              rng = pg->Exterior;
              gaiaGetPoint(rng->Coords, 3, &x, &y);
              pL->AddCandidate(x, y, angle, g);
          } else
            gaiaFreeGeomColl(g);
          // -60 degs
          angle = 300.0 * toRads;
          g = pL->CreateRectangle(cx, cy, angle);
          if (pL->CheckSize(geom, g) == true)
            {
              pg = g->FirstPolygon;
              rng = pg->Exterior;
              gaiaGetPoint(rng->Coords, 3, &x, &y);
              pL->AddCandidate(x, y, angle, g);
          } else
            gaiaFreeGeomColl(g);
          // vertical
          angle = 90.0 * toRads;
          g = pL->CreateRectangle(cx, cy, angle);
          if (pL->CheckSize(geom, g) == true)
            {
              pg = g->FirstPolygon;
              rng = pg->Exterior;
              gaiaGetPoint(rng->Coords, 3, &x, &y);
              pL->AddCandidate(x, y, angle, g);
          } else
            gaiaFreeGeomColl(g);
        }
    }
stop:
  gaiaFreeGeomColl(geom);
  if (!pL)
    return;
  if (!First)
    First = pL;
  if (Last)
    Last->SetNext(pL);
  Last = pL;
}

void MapLabelList::CheckCollisions()
{
//
// evaluating collisions between labels and choosing optimal positions
//
  MapLabel *pL;
  MapLabel *pL2;
  pL = First;
  while (pL)
    {
      if (pL->IsNoCollision() == true)
        {
          // evaluating collisions
          MapLabelCandidate *pC = pL->GetFirst();
          while (pC)
            {
              // looping on candidate positions
              pL2 = First;
              while (pL2)
                {
                  if (pL2->IsValid() == true)
                    {
                      // evaluating a possible collision
                      if (pC->EvaluateCollision(pL2->GetGeometry()) == true)
                        break;
                    }
                  pL2 = pL2->GetNext();
                }
              if (pC->IsValid() == true)
                {
                  // ok, we've found a valid position
                  pL->AssignLabelPosition(pC);
                  break;
                }
              pC = pC->GetNext();
            }
        }
      pL = pL->GetNext();
    }
}

LineLabelItem::LineLabelItem(double x0, double y0, double x1, double y1)
{
// constructor - Line Label Item
  double p1x;
  double p1y;
  double p2x;
  double p2y;
  double cx;
  double cy;
  double m;
  if (x0 == x1)
    {
      if (y0 > y1)
        {
          p1x = x1;
          p1y = y1;
          p2x = x0;
          p2y = y0;
      } else
        {
          p1x = x0;
          p1y = y0;
          p2x = x1;
          p2y = y1;
        }
  } else
    {
      if (x0 > x1)
        {
          p1x = x1;
          p1y = y1;
          p2x = x0;
          p2y = y0;
      } else
        {
          p1x = x0;
          p1y = y0;
          p2x = x1;
          p2y = y1;
        }
    }
  m = (p2y - p1y) / (p2x - p1x);
  cx = p1x + ((p2x - p1x) / 2.0);
  cy = p1y + ((p2y - p1y) / 2.0);
  X = cx;
  Y = cy;
  Rotation = atan(m);
  Next = NULL;
}

LineLabelAux::LineLabelAux(double pixelRatio)
{
// constructor - Line Labels List
  PixelRatio = pixelRatio;
  First = NULL;
  Last = NULL;
  Count = 0;
}

LineLabelAux::~LineLabelAux()
{
// destructor - Line Labels List
  LineLabelItem *pL;
  LineLabelItem *pLn;
  pL = First;
  while (pL)
    {
      pLn = pL->GetNext();
      delete pL;
      pL = pLn;
    }
}

LineLabelItem *LineLabelAux::GetItem()
{
// returning the 'central' item
  LineLabelItem *item;
  int cnt = 0;
  int idx;
  if (Count <= 0)
    return NULL;
  idx = (Count / 2) - 1;
  if (idx < 0)
    idx = 0;
  if (idx >= Count)
    idx = Count - 1;
  item = First;
  while (item)
    {
      if (idx == cnt)
        return item;
      cnt++;
      item = item->GetNext();
    }
  return NULL;
}

void LineLabelAux::Feed(MapLabel * label, gaiaGeomCollPtr geom)
{
// identifying the Line Labels positions
  int iv;
  double x;
  double y;
  double x0;
  double y0;
  double dist;
  gaiaLinestringPtr line = geom->FirstLinestring;
  if (!line)
    return;
  for (iv = 0; iv < line->Points; iv++)
    {
      gaiaGetPoint(line->Coords, iv, &x, &y);
      if (iv == 0)
        {
          x0 = x;
          y0 = y;
      } else
        {
          dist = sqrt(((x - x0) * (x - x0)) + ((y - y0) * (y - y0)));
          if (dist >= label->GetWidth() * label->GetPixelRatio())
            {
              LineLabelItem *lbl = new LineLabelItem(x, y, x0, y0);
              if (!First)
                First = lbl;
              if (Last)
                Last->SetNext(lbl);
              Last = lbl;
              Count++;
              x0 = x;
              y0 = y;
            }
        }
    }
}

MapOutliner::MapOutliner(int width, int height, wxFont & font)
{
// constructor - Map Label Outliner
  Valid = false;
  Font = font;
  Bitmap = new wxBitmap(width, height);
  BmpDC = new wxMemoryDC(*Bitmap);
  BmpGR = wxGraphicsContext::Create(*BmpDC);
  TextColor = 0;
  TransparentColor = 128;
  OutlineColor = 255;
  BmpGR->SetBrush(wxColour
                  (TransparentColor, TransparentColor, TransparentColor));
  BmpGR->DrawRectangle(0, 0, width, height);
}

MapOutliner::~MapOutliner()
{
// destructor - Map Label Outliner
  if (BmpGR)
    delete BmpGR;
  if (BmpDC)
    delete BmpDC;
  delete Bitmap;
}

void MapOutliner::Draw(MapLayer * layer, wxString & label, double x, double y,
                       double rotation)
{
// drawing some label text
  Valid = true;
  Font.SetPointSize(layer->GetLabelPointSize());
  if (layer->IsLabelFontBold() == true)
    Font.SetWeight(wxFONTWEIGHT_BOLD);
  else
    Font.SetWeight(wxFONTWEIGHT_NORMAL);
  if (layer->IsLabelFontItalic() == true)
    Font.SetStyle(wxFONTSTYLE_ITALIC);
  else
    Font.SetStyle(wxFONTSTYLE_NORMAL);
  Font.SetUnderlined(layer->IsLabelFontUnderlined());
  BmpGR->SetFont(Font, TextColor);
  BmpGR->DrawText(label, x, y, rotation);
}

void MapOutliner::Outline()
{
// applying outlines to text
  if (Valid == false)
    return;
  int x;
  int y;
  wxImage img = Bitmap->ConvertToImage();
  for (y = 0; y < img.GetHeight(); y++)
    {
      for (x = 0; x < img.GetWidth(); x++)
        {
          int r = img.GetRed(x, y);
          int g = img.GetGreen(x, y);
          int b = img.GetBlue(x, y);
          if (r == TransparentColor && g == TransparentColor
              && b == TransparentColor)
            continue;
          if (r == OutlineColor && g == OutlineColor && b == OutlineColor)
            continue;
          // ok, this one is a text pixel
          OutlinePixel(&img, x - 1, y - 1);
          OutlinePixel(&img, x, y - 1);
          OutlinePixel(&img, x + 1, y - 1);
          OutlinePixel(&img, x - 1, y);
          OutlinePixel(&img, x + 1, y);
          OutlinePixel(&img, x - 1, y + 1);
          OutlinePixel(&img, x, y + 1);
          OutlinePixel(&img, x + 1, y + 1);
        }
    }
  for (y = 0; y < img.GetHeight(); y++)
    {
      for (x = 0; x < img.GetWidth(); x++)
        {
          int r = img.GetRed(x, y);
          int g = img.GetGreen(x, y);
          int b = img.GetBlue(x, y);
          if (r == TransparentColor && g == TransparentColor
              && b == TransparentColor)
            continue;
          if (r == OutlineColor && g == OutlineColor && b == OutlineColor)
            continue;
          img.SetRGB(x, y, TransparentColor, TransparentColor,
                     TransparentColor);
        }
    }
  delete Bitmap;
  Bitmap = new wxBitmap(img);
  wxMask *msk = new wxMask(*Bitmap,
                           wxColour(TransparentColor, TransparentColor,
                                    TransparentColor));
  Bitmap->SetMask(msk);
}

void MapOutliner::OutlinePixel(wxImage * img, int x, int y)
{
// trying to apply the outline color to some pixel
  if (x < 0 || x >= img->GetWidth())
    return;
  if (y < 0 || y >= img->GetHeight())
    return;
  int r = img->GetRed(x, y);
  int g = img->GetGreen(x, y);
  int b = img->GetBlue(x, y);
  if (r == TransparentColor && g == TransparentColor && b == TransparentColor)
    img->SetRGB(x, y, OutlineColor, OutlineColor, OutlineColor);
}

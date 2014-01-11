/*
/ Dialogs.cpp
/ various dialog classes
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
#include "wx/filename.h"
#include "wx/colordlg.h"

#include <spatialite/gaiaaux.h>

#include "icons/route_yes.xpm"
#include "icons/route_no.xpm"
#include "icons/arc_yes.xpm"
#include "icons/arc_no.xpm"
#include "icons/zoom_in_yes.xpm"
#include "icons/zoom_in_no.xpm"
#include "icons/zoom_out_yes.xpm"
#include "icons/zoom_out_no.xpm"
#include "icons/checked_brush.xpm"

#if defined(_WIN32) || defined (__MINGW32__)
#define FORMAT_64	"%I64d"
#else
#define FORMAT_64	"%lld"
#endif

CreateInternalTableDialog::CreateInternalTableDialog(MyFrame * parent,
                                                     wxString & msg)
{
//
// constructor
//
  MainFrame = parent;
  Message = msg;
}

bool CreateInternalTableDialog::Create()
{
//
// dialog creation
//
  if (wxDialog::Create(MainFrame, wxID_ANY, wxT("spatialite-gis")) == false)
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

void CreateInternalTableDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: message
  wxBoxSizer *msgSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(msgSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticText *msgLabel = new wxStaticText(this, wxID_STATIC, Message);
  msgSizer->Add(msgLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// second row: OPTIONS
  wxBoxSizer *optSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(optSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString options[3];
  options[0] =
    wxT("Yes, create this Table and ask me again for any other missing table");
  options[1] = wxT("Yes, create any missing Table and don't ask me any longer");
  options[2] = wxT("No, I'm not willing to create this Table");
  OptionCtrl = new wxRadioBox(this, ID_CREATE_INTERNAL_OPTION,
                              wxT("Options"),
                              wxDefaultPosition, wxDefaultSize, 3, options, 3,
                              wxRA_SPECIFY_ROWS);
  OptionCtrl->SetSelection(1);
  optSizer->Add(OptionCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// OK button
  wxBoxSizer *okBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & CreateInternalTableDialog::OnOk);
}

void CreateInternalTableDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  Yes = false;
  YesToAll = false;
  if (OptionCtrl->GetSelection() == 0)
    Yes = true;
  if (OptionCtrl->GetSelection() == 1)
    YesToAll = true;
  wxDialog::EndModal(wxID_OK);
}

bool ProjectCrsDialog::Create(MyFrame * parent, SridInfo & info,
                              wxString & projectName)
{
//
// creating the dialog
//
  MainFrame = parent;
  DescName = projectName;
  Info = SridInfo(&info);
  Info.ParseUnit();
  Dms = info.IsDms();
  Info.SetDms(Dms);
  if (wxDialog::Create(parent, wxID_ANY, wxT("Project Reference System")) ==
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

void ProjectCrsDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[64];
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: description
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Project's Name:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  DescCtrl =
    new wxTextCtrl(this, wxID_ANY, DescName, wxDefaultPosition,
                   wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: SRID
  wxBoxSizer *sridSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(sridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticText *sridLabel = new wxStaticText(this, wxID_STATIC, wxT("&SRID:"));
  sridSizer->Add(sridLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", Info.GetSrid());
  wxString srid = wxString::FromUTF8(dummy);
  SridCtrl = new wxSpinCtrl(this, ID_PROJECT_SRID, srid,
                            wxDefaultPosition, wxSize(80, 20), wxSP_ARROW_KEYS,
                            -1, 40000, Info.GetSrid());
  sridSizer->Add(SridCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// third row:  SRID Infos
  wxBoxSizer *projectCrsSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(projectCrsSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticBox *projectCrsBox = new wxStaticBox(this, wxID_STATIC,
                                               wxT
                                               ("Project's Reference System"),
                                               wxDefaultPosition,
                                               wxDefaultSize);
  wxBoxSizer *crsProjectSizer = new wxStaticBoxSizer(projectCrsBox, wxVERTICAL);
  projectCrsSizer->Add(crsProjectSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                       5);
  wxBoxSizer *sridProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(sridProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *sridProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&AuthSRID:"));
  sridProjectSizer->Add(sridProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5);
  srid = Info.GetAuthName();
  sprintf(dummy, " %d", Info.GetAuthSrid());
  srid += wxString::FromUTF8(dummy);
  wxTextCtrl *sridProjectCtrl = new wxTextCtrl(this, ID_PROJECT_AUTH_SRID, srid,
                                               wxDefaultPosition, wxSize(350,
                                                                         22),
                                               wxTE_READONLY);
  sridProjectSizer->Add(sridProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *nameProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(nameProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *nameProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Name:"));
  nameProjectSizer->Add(nameProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5);
  wxTextCtrl *nameProjectCtrl =
    new wxTextCtrl(this, ID_PROJECT_SRID_NAME, Info.GetSridName(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  nameProjectSizer->Add(nameProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *paramProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(paramProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *paramProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Params:"));
  paramProjectSizer->Add(paramProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                         5);
  wxTextCtrl *paramProjectCtrl =
    new wxTextCtrl(this, ID_PROJECT_SRID_PARAMS, Info.GetParams(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  paramProjectSizer->Add(paramProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// fourth row: UNITS
  wxBoxSizer *unitSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(unitSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticText *unitLabel = new wxStaticText(this, wxID_STATIC, wxT("&Units:"));
  unitSizer->Add(unitLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  UnitCtrl =
    new wxTextCtrl(this, ID_PROJECT_UNITS_NAME, Info.GetUnitName(),
                   wxDefaultPosition, wxSize(100, 22), wxTE_READONLY);
  unitSizer->Add(UnitCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString dms[2];
  dms[0] = wxT("&DMS [degrees, minutes, secons]");
  dms[1] = wxT("&DD [decimal degrees]");
  DmsCtrl = new wxRadioBox(this, ID_PROJECT_DMS,
                           wxT("&Geographic coordinates format"),
                           wxDefaultPosition, wxDefaultSize, 2, dms, 2,
                           wxRA_SPECIFY_ROWS);
  if (Info.IsGeographic() == false)
    {
      DmsCtrl->Enable(false);
  } else
    {
      if (Info.IsDms() == true)
        DmsCtrl->SetSelection(0);
      else
        DmsCtrl->SetSelection(1);
    }
  unitSizer->Add(DmsCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & ProjectCrsDialog::OnOk);
  Connect(ID_PROJECT_SRID, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & ProjectCrsDialog::OnSridChanged);
  Connect(ID_PROJECT_DMS, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & ProjectCrsDialog::OnDmsChanged);
}

void ProjectCrsDialog::OnSridChanged(wxCommandEvent & WXUNUSED(event))
{
//
// SRID changed
//
  char dummy[64];
  int srid = SridCtrl->GetValue();
  SridInfo info(srid);
  MainFrame->GetSridInfo(&info);
  wxTextCtrl *sridProjectCtrl = (wxTextCtrl *) FindWindow(ID_PROJECT_AUTH_SRID);
  wxString str = info.GetAuthName();
  sprintf(dummy, " %d", info.GetAuthSrid());
  str += wxString::FromUTF8(dummy);
  sridProjectCtrl->SetValue(str);
  wxTextCtrl *nameProjectCtrl = (wxTextCtrl *) FindWindow(ID_PROJECT_SRID_NAME);
  nameProjectCtrl->SetValue(info.GetSridName());
  wxTextCtrl *paramProjectCtrl =
    (wxTextCtrl *) FindWindow(ID_PROJECT_SRID_PARAMS);
  paramProjectCtrl->SetValue(info.GetParams());
  info.ParseUnit();
  UnitCtrl->SetValue(info.GetUnitName());
  if (info.IsGeographic() == false)
    {
      DmsCtrl->Enable(false);
  } else
    {
      DmsCtrl->Enable(true);
      if (Dms == true)
        DmsCtrl->SetSelection(0);
      else
        DmsCtrl->SetSelection(1);
    }
}

void ProjectCrsDialog::OnDmsChanged(wxCommandEvent & WXUNUSED(event))
{
//
// DMS - DD selection changed
//
  if (DmsCtrl->GetSelection() == 0)
    Dms = true;
  else
    Dms = false;
}

void ProjectCrsDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  int srid = SridCtrl->GetValue();
  SridInfo info(srid);
  MainFrame->GetSridInfo(&info);
  if (info.IsNotSet() == true)
    {
      wxMessageBox(wxT("You must specify a valid SRID !!!"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  info.SetDms(Dms);
  MainFrame->SetProjectCrs(info);
  DescName = DescCtrl->GetValue();
  MainFrame->SetProjectName(DescName);
  MainFrame->SetTitle(DescName);
  wxDialog::EndModal(wxID_OK);
}

bool VectorCrsDialog::Create(MyFrame * parent, SridInfo & project_info,
                             wxString & table, wxString & geom, wxString & desc,
                             int srid, bool reproject)
{
//
// creating the dialog
//
  MainFrame = parent;
  ProjectCrs = SridInfo(&project_info);
  TableName = table;
  GeometryColumn = geom;
  DescName = desc;
  Srid = srid;
  Reproject = reproject;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Vector Layer Reference System"))
      == false)
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

void VectorCrsDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[64];
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
  DescCtrl = new wxTextCtrl(this, wxID_ANY, DescName,
                            wxDefaultPosition, wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: Layer SRID
  SridInfo layerInfo(Srid);
  MainFrame->GetSridInfo(&layerInfo);
  wxBoxSizer *layerCrsSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerCrsSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticBox *layerCrsBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Layer's Reference System"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *crsLayerSizer = new wxStaticBoxSizer(layerCrsBox, wxVERTICAL);
  layerCrsSizer->Add(crsLayerSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *sridLayerSizer = new wxBoxSizer(wxHORIZONTAL);
  crsLayerSizer->Add(sridLayerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *sridLayerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&SRID:"));
  sridLayerSizer->Add(sridLayerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d   [", Srid);
  wxString srid = wxString::FromUTF8(dummy) + layerInfo.GetAuthName();
  sprintf(dummy, " %d]", layerInfo.GetAuthSrid());
  srid += wxString::FromUTF8(dummy);
  wxTextCtrl *sridLayerCtrl = new wxTextCtrl(this, ID_LAYER_SRID, srid,
                                             wxDefaultPosition, wxSize(350, 22),
                                             wxTE_READONLY);
  sridLayerSizer->Add(sridLayerCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *nameLayerSizer = new wxBoxSizer(wxHORIZONTAL);
  crsLayerSizer->Add(nameLayerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *nameLayerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Name:"));
  nameLayerSizer->Add(nameLayerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *nameLayerCtrl =
    new wxTextCtrl(this, ID_LAYER_SRID_NAME, layerInfo.GetSridName(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  nameLayerSizer->Add(nameLayerCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *paramLayerSizer = new wxBoxSizer(wxHORIZONTAL);
  crsLayerSizer->Add(paramLayerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *paramLayerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Params:"));
  paramLayerSizer->Add(paramLayerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *paramLayerCtrl =
    new wxTextCtrl(this, ID_LAYER_SRID_PARAMS, layerInfo.GetParams(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  paramLayerSizer->Add(paramLayerCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// fourth row:  Project SRID
  wxBoxSizer *projectCrsSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(projectCrsSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticBox *projectCrsBox = new wxStaticBox(this, wxID_STATIC,
                                               wxT
                                               ("Project's Reference System"),
                                               wxDefaultPosition,
                                               wxDefaultSize);
  wxBoxSizer *crsProjectSizer = new wxStaticBoxSizer(projectCrsBox, wxVERTICAL);
  projectCrsSizer->Add(crsProjectSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                       5);
  wxBoxSizer *sridProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(sridProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *sridProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&SRID:"));
  sridProjectSizer->Add(sridProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5);
  sprintf(dummy, "%d   [", ProjectCrs.GetSrid());
  srid = wxString::FromUTF8(dummy) + ProjectCrs.GetAuthName();
  sprintf(dummy, " %d]", ProjectCrs.GetAuthSrid());
  srid += wxString::FromUTF8(dummy);
  wxTextCtrl *sridProjectCtrl = new wxTextCtrl(this, ID_PROJECT_AUTH_SRID, srid,
                                               wxDefaultPosition, wxSize(350,
                                                                         22),
                                               wxTE_READONLY);
  sridProjectSizer->Add(sridProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *nameProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(nameProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *nameProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Name:"));
  nameProjectSizer->Add(nameProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5);
  wxTextCtrl *nameProjectCtrl =
    new wxTextCtrl(this, ID_PROJECT_SRID_NAME, ProjectCrs.GetSridName(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  nameProjectSizer->Add(nameProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *paramProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(paramProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *paramProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Params:"));
  paramProjectSizer->Add(paramProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                         5);
  wxTextCtrl *paramProjectCtrl =
    new wxTextCtrl(this, ID_PROJECT_SRID_PARAMS, ProjectCrs.GetParams(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  paramProjectSizer->Add(paramProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// fifth row: OnTheFly Reproject
  if (layerInfo.GetSrid() == ProjectCrs.GetSrid())
    Reproject = true;
  wxBoxSizer *reprojectSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(reprojectSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  ReprojectCtrl =
    new wxCheckBox(this, ID_REPROJECT, wxT("On-the-fly reproject"),
                   wxDefaultPosition, wxDefaultSize);
  ReprojectCtrl->SetValue(Reproject);
  reprojectSizer->Add(ReprojectCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  if (layerInfo.GetSrid() == ProjectCrs.GetSrid())
    ReprojectCtrl->Enable(false);

// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & VectorCrsDialog::OnOk);
}

void VectorCrsDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  Reproject = ReprojectCtrl->GetValue();
  DescName = DescCtrl->GetValue();
  wxDialog::EndModal(wxID_OK);
}

bool RasterCrsDialog::Create(MyFrame * parent, SridInfo & project_info,
                             wxString & table, wxString & desc, int srid)
{
//
// creating the dialog
//
  MainFrame = parent;
  ProjectCrs = SridInfo(&project_info);
  TableName = table;
  DescName = desc;
  Srid = srid;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Raster Layer Reference System"))
      == false)
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

void RasterCrsDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[64];
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: the Layer Table
  wxBoxSizer *layerSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *layerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Raster Layer:"));
  layerSizer->Add(layerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *layerValue = new wxTextCtrl(this, wxID_STATIC,
                                          TableName, wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  layerSizer->Add(layerValue, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: description
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *descCtrl = new wxTextCtrl(this, wxID_ANY, DescName,
                                        wxDefaultPosition,
                                        wxSize(350, 22), wxTE_READONLY);
  descSizer->Add(descCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: Layer SRID
  SridInfo layerInfo(Srid);
  MainFrame->GetSridInfo(&layerInfo);
  wxBoxSizer *layerCrsSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerCrsSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticBox *layerCrsBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Layer's Reference System"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *crsLayerSizer = new wxStaticBoxSizer(layerCrsBox, wxVERTICAL);
  layerCrsSizer->Add(crsLayerSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *sridLayerSizer = new wxBoxSizer(wxHORIZONTAL);
  crsLayerSizer->Add(sridLayerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *sridLayerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&SRID:"));
  sridLayerSizer->Add(sridLayerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d   [", Srid);
  wxString srid = wxString::FromUTF8(dummy) + layerInfo.GetAuthName();
  sprintf(dummy, " %d]", layerInfo.GetAuthSrid());
  srid += wxString::FromUTF8(dummy);
  wxTextCtrl *sridLayerCtrl = new wxTextCtrl(this, ID_LAYER_SRID, srid,
                                             wxDefaultPosition, wxSize(350, 22),
                                             wxTE_READONLY);
  sridLayerSizer->Add(sridLayerCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *nameLayerSizer = new wxBoxSizer(wxHORIZONTAL);
  crsLayerSizer->Add(nameLayerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *nameLayerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Name:"));
  nameLayerSizer->Add(nameLayerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *nameLayerCtrl =
    new wxTextCtrl(this, ID_LAYER_SRID_NAME, layerInfo.GetSridName(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  nameLayerSizer->Add(nameLayerCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *paramLayerSizer = new wxBoxSizer(wxHORIZONTAL);
  crsLayerSizer->Add(paramLayerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *paramLayerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Params:"));
  paramLayerSizer->Add(paramLayerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *paramLayerCtrl =
    new wxTextCtrl(this, ID_LAYER_SRID_PARAMS, layerInfo.GetParams(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  paramLayerSizer->Add(paramLayerCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// fourth row:  Project SRID
  wxBoxSizer *projectCrsSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(projectCrsSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticBox *projectCrsBox = new wxStaticBox(this, wxID_STATIC,
                                               wxT
                                               ("Project's Reference System"),
                                               wxDefaultPosition,
                                               wxDefaultSize);
  wxBoxSizer *crsProjectSizer = new wxStaticBoxSizer(projectCrsBox, wxVERTICAL);
  projectCrsSizer->Add(crsProjectSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                       5);
  wxBoxSizer *sridProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(sridProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *sridProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&SRID:"));
  sridProjectSizer->Add(sridProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5);
  sprintf(dummy, "%d   [", ProjectCrs.GetSrid());
  srid = wxString::FromUTF8(dummy) + ProjectCrs.GetAuthName();
  sprintf(dummy, " %d]", ProjectCrs.GetAuthSrid());
  srid += wxString::FromUTF8(dummy);
  wxTextCtrl *sridProjectCtrl = new wxTextCtrl(this, ID_PROJECT_AUTH_SRID, srid,
                                               wxDefaultPosition, wxSize(350,
                                                                         22),
                                               wxTE_READONLY);
  sridProjectSizer->Add(sridProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *nameProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(nameProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *nameProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Name:"));
  nameProjectSizer->Add(nameProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5);
  wxTextCtrl *nameProjectCtrl =
    new wxTextCtrl(this, ID_PROJECT_SRID_NAME, ProjectCrs.GetSridName(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  nameProjectSizer->Add(nameProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

  wxBoxSizer *paramProjectSizer = new wxBoxSizer(wxHORIZONTAL);
  crsProjectSizer->Add(paramProjectSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *paramProjectLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Params:"));
  paramProjectSizer->Add(paramProjectLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                         5);
  wxTextCtrl *paramProjectCtrl =
    new wxTextCtrl(this, ID_PROJECT_SRID_PARAMS, ProjectCrs.GetParams(),
                   wxDefaultPosition, wxSize(350, 22), wxTE_READONLY);
  paramProjectSizer->Add(paramProjectCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// CANCEL button
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
}

bool VisibilityRangeDialog::Create(MyFrame * parent, int type, wxString & table,
                                   wxString & geom, wxString & descName,
                                   bool alwaysVisible, int minScale,
                                   int maxScale)
{
//
// creating the dialog
//
  MainFrame = parent;
  if (type == RASTER_LAYER)
    RasterLayer = true;
  else
    RasterLayer = false;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  AlwaysVisible = alwaysVisible;
  MinScale = minScale;
  MaxScale = maxScale;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Layer Visibility Range")) ==
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

void VisibilityRangeDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[64];
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: the Layer Table+Geometry
  wxBoxSizer *layerSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxString type = wxT("&Vector Layer:");
  if (RasterLayer == true)
    type = wxT("&Raster Layer:");
  wxStaticText *layerLabel = new wxStaticText(this, wxID_STATIC, type);
  layerSizer->Add(layerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString name = TableName + wxT(".") + GeometryColumn;
  if (RasterLayer == true)
    name = TableName;
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
  DescCtrl = new wxTextCtrl(this, wxID_ANY, DescName, wxDefaultPosition,
                            wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row:  Visibility RANGE
  wxBoxSizer *rangeBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(rangeBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *rangeBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Visibility Range Selection"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *rangeSizer = new wxStaticBoxSizer(rangeBox, wxVERTICAL);
  rangeBoxSizer->Add(rangeSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *range1Sizer = new wxBoxSizer(wxHORIZONTAL);
  rangeSizer->Add(range1Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxString visibility[2];
  visibility[0] = wxT("&This layer is always visible");
  visibility[1] =
    wxT("&This layer is visible only within the following Scale range");
  VisibilityCtrl =
    new wxRadioBox(this, ID_RANGE_VISIBILITY, wxT("&Visibility Mode"),
                   wxDefaultPosition, wxDefaultSize, 2, visibility, 2,
                   wxRA_SPECIFY_ROWS);
  if (AlwaysVisible == true)
    VisibilityCtrl->SetSelection(0);
  else
    VisibilityCtrl->SetSelection(1);
  range1Sizer->Add(VisibilityCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *range2Sizer = new wxBoxSizer(wxHORIZONTAL);
  rangeSizer->Add(range2Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticText *minLabel = new wxStaticText(this, wxID_STATIC, wxT("&Min:"));
  range2Sizer->Add(minLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", MinScale);
  wxString val = wxString::FromUTF8(dummy);
  MinScaleCtrl = new wxSpinCtrl(this, ID_RANGE_MIN_SCALE, val,
                                wxDefaultPosition, wxSize(120, 20),
                                wxSP_ARROW_KEYS, 0, 1000000000, MinScale);
  range2Sizer->Add(MinScaleCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
  wxBoxSizer *range3Sizer = new wxBoxSizer(wxHORIZONTAL);
  rangeSizer->Add(range3Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticText *maxLabel = new wxStaticText(this, wxID_STATIC, wxT("&Max:"));
  range3Sizer->Add(maxLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d", MaxScale);
  val = wxString::FromUTF8(dummy);
  MaxScaleCtrl = new wxSpinCtrl(this, ID_RANGE_MAX_SCALE, val,
                                wxDefaultPosition, wxSize(120, 20),
                                wxSP_ARROW_KEYS, 0, 1000000000, MaxScale);
  range3Sizer->Add(MaxScaleCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
  if (AlwaysVisible == true)
    {
      MinScaleCtrl->SetValue(wxT(""));
      MaxScaleCtrl->SetValue(wxT(""));
      MinScaleCtrl->Enable(false);
      MaxScaleCtrl->Enable(false);
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
          (wxObjectEventFunction) & VisibilityRangeDialog::OnOk);
  Connect(ID_RANGE_VISIBILITY, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & VisibilityRangeDialog::OnVisibilityChanged);
}

void VisibilityRangeDialog::
OnVisibilityChanged(wxCommandEvent & WXUNUSED(event))
{
// always visibile radiobox changed
  if (VisibilityCtrl->GetSelection() == 0)
    {
      MinScaleCtrl->SetValue(wxT(""));
      MaxScaleCtrl->SetValue(wxT(""));
      MinScaleCtrl->Enable(false);
      MaxScaleCtrl->Enable(false);
  } else
    {
      MinScaleCtrl->SetValue(0);
      MaxScaleCtrl->SetValue(1000000000);
      MinScaleCtrl->Enable(true);
      MaxScaleCtrl->Enable(true);
    }
}

void VisibilityRangeDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  if (VisibilityCtrl->GetSelection() != 0)
    {
      if (MaxScaleCtrl->GetValue() <= MinScaleCtrl->GetValue())
        {
          wxMessageBox(wxT("Invalid Scale Range [mismatching Min/Max]"),
                       wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
          return;
        }
    }
  if (VisibilityCtrl->GetSelection() == 0)
    AlwaysVisible = true;
  else
    AlwaysVisible = false;
  MinScale = MinScaleCtrl->GetValue();
  MaxScale = MaxScaleCtrl->GetValue();
  DescName = DescCtrl->GetValue();
  wxDialog::EndModal(wxID_OK);
}

bool LabelsDialog::Create(MyFrame * parent, wxString & table, wxString & geom,
                          wxString & descName, wxString & labelColumn,
                          bool mapLabeling, wxColour & textColor, int pointSize,
                          bool fontBold, bool fontItalic, bool fontUnderlined,
                          bool fontOutlined, wxString & orderByColumn,
                          bool descending, bool alwaysVisible, int minScale,
                          int maxScale, bool antiOverlap)
{
//
// creating the dialog
//
  ColumnList = NULL;
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geom;
  DescName = descName;
  LabelColumn = labelColumn;
  MapLabeling = mapLabeling;
  TextColor = textColor;
  PointSize = pointSize;
  if (PointSize == 0)
    PointSize = 10;
  if (fontBold == true)
    FontWeight = wxFONTWEIGHT_BOLD;
  else
    FontWeight = wxFONTWEIGHT_NORMAL;
  if (fontItalic == true)
    FontStyle = wxFONTSTYLE_ITALIC;
  else
    FontStyle = wxFONTSTYLE_NORMAL;
  FontUnderlined = fontUnderlined;
  FontOutlined = fontOutlined;
  OrderByColumn = orderByColumn;
  Descending = descending;
  Priority = false;
  if (orderByColumn.Len() > 0)
    Priority = true;
  AlwaysVisible = alwaysVisible;
  MinScale = minScale;
  MaxScale = maxScale;
  AntiOverlap = antiOverlap;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Labels")) == false)
    return false;
// populates individual controls
  Bitmap = wxBitmap(256, 64);
  OutlineBitmap = NULL;
  MainFrame->GetColumnList(TableName, &NumColumns, &ColumnList);
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

LabelsDialog::~LabelsDialog()
{
// destructor 
  if (OutlineBitmap)
    delete OutlineBitmap;
  if (ColumnList)
    delete[]ColumnList;
}

void LabelsDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[64];
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *headSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(headSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxBoxSizer *headSizer1 = new wxBoxSizer(wxVERTICAL);
  headSizer->Add(headSizer1, 0, wxALIGN_LEFT | wxALL, 0);
  wxBoxSizer *headSizer2 = new wxBoxSizer(wxVERTICAL);
  headSizer->Add(headSizer2, 0, wxALIGN_RIGHT | wxALL, 0);
// first row: the Layer Table+Geometry
  wxBoxSizer *layerSizer = new wxBoxSizer(wxHORIZONTAL);
  headSizer1->Add(layerSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxString type = wxT("&Vector Layer:");
  wxStaticText *layerLabel = new wxStaticText(this, wxID_STATIC, type);
  layerSizer->Add(layerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString name = TableName + wxT(".") + GeometryColumn;
  wxTextCtrl *layerValue = new wxTextCtrl(this, wxID_STATIC,
                                          name, wxDefaultPosition,
                                          wxSize(350, 22), wxTE_READONLY);
  layerSizer->Add(layerValue, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: description
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  headSizer1->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  DescCtrl = new wxTextCtrl(this, wxID_ANY, DescName, wxDefaultPosition,
                            wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row:  LABEL column
  wxBoxSizer *labelBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  headSizer2->Add(labelBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *labelBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Label value"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *labelSizer = new wxStaticBoxSizer(labelBox, wxVERTICAL);
  labelBoxSizer->Add(labelSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *label2Sizer = new wxBoxSizer(wxHORIZONTAL);
  labelSizer->Add(label2Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *labelLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column:"));
  label2Sizer->Add(labelLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  LabelCtrl =
    new wxComboBox(this, ID_LABEL_LABEL, wxT(""), wxDefaultPosition,
                   wxDefaultSize, NumColumns, ColumnList,
                   wxCB_DROPDOWN | wxCB_READONLY);
  label2Sizer->Add(LabelCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
  int sel = 0;
  int i;
  for (i = 1; i < NumColumns; i++)
    {
      if (ColumnList[i] == LabelColumn)
        sel = i;
    }
  LabelCtrl->SetSelection(sel);
// Map Label frame container
  wxBoxSizer *mapLabelBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(mapLabelBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *mapLabelBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Map Labeling"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *mapLabelSizer = new wxStaticBoxSizer(mapLabelBox, wxVERTICAL);
  mapLabelBoxSizer->Add(mapLabelSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *enableBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  mapLabelSizer->Add(enableBoxSizer, 0, wxALIGN_LEFT | wxALL, 0);
  MapLabelingCtrl =
    new wxCheckBox(this, ID_LABEL_ENABLED, wxT("Enable &Map Labeling"));
  MapLabelingCtrl->SetValue(MapLabeling);
  enableBoxSizer->Add(MapLabelingCtrl, 0, wxALIGN_LEFT | wxALL, 1);
// fourth row: COLOR
  wxBoxSizer *colorBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  mapLabelSizer->Add(colorBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxBoxSizer *graphicsBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  colorBoxSizer->Add(graphicsBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *grBox = new wxStaticBox(this, wxID_STATIC,
                                       wxT("Label graphics"),
                                       wxDefaultPosition,
                                       wxDefaultSize);
  wxBoxSizer *grGroupSizer = new wxStaticBoxSizer(grBox, wxVERTICAL);
  graphicsBoxSizer->Add(grGroupSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *colorSizer = new wxBoxSizer(wxHORIZONTAL);
  grGroupSizer->Add(colorSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxBoxSizer *grSizer = new wxBoxSizer(wxHORIZONTAL);
  grGroupSizer->Add(grSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxBoxSizer *col1Sizer = new wxBoxSizer(wxVERTICAL);
  grSizer->Add(col1Sizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  wxBoxSizer *col13Sizer = new wxBoxSizer(wxHORIZONTAL);
  col1Sizer->Add(col13Sizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxBoxSizer *col14Sizer = new wxBoxSizer(wxHORIZONTAL);
  col1Sizer->Add(col14Sizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxBoxSizer *col2Sizer = new wxBoxSizer(wxHORIZONTAL);
  grSizer->Add(col2Sizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  wxBitmap disabledBmp;
  GetDisabledButtonBitmap(disabledBmp);
  wxBitmap colorBmp;
  GetButtonBitmap(TextColor, colorBmp);
  TextColorCtrl = new wxBitmapButton(this, ID_LABEL_COLOR, colorBmp);
  TextColorCtrl->SetBitmapDisabled(disabledBmp);
  colorSizer->Add(TextColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  colorSizer->AddSpacer(20);
  wxStaticText *alphaLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Transparency:"));
  colorSizer->Add(alphaLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  AlphaCtrl =
    new wxSlider(this, ID_LABEL_ALPHA, TextColor.Alpha(), 0, 255,
                 wxDefaultPosition, wxSize(75, 20),
                 wxSL_HORIZONTAL | wxSL_INVERSE);
  colorSizer->Add(AlphaCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  colorSizer->AddSpacer(20);
  wxStaticText *sizeLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Font Size [pts]:"));
  colorSizer->Add(sizeLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  sprintf(dummy, "%d", PointSize);
  wxString ptSize = wxString::FromUTF8(dummy);
  PointSizeCtrl = new wxSpinCtrl(this, ID_LABEL_SIZE, ptSize,
                                 wxDefaultPosition, wxSize(80, 20),
                                 wxSP_ARROW_KEYS, 1, 32, PointSize);
  colorSizer->Add(PointSizeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  wxString weight[2];
  weight[0] = wxT("&Normal");
  weight[1] = wxT("&Bold");
  FontWeightCtrl = new wxRadioBox(this, ID_LABEL_WEIGHT,
                                  wxT("&Font Weight"), wxDefaultPosition,
                                  wxDefaultSize, 2, weight, 2,
                                  wxRA_SPECIFY_COLS);
  if (FontWeight == wxFONTWEIGHT_BOLD)
    FontWeightCtrl->SetSelection(1);
  else
    FontWeightCtrl->SetSelection(0);
  col13Sizer->Add(FontWeightCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  FontOutlineCtrl =
    new wxCheckBox(this, ID_LABEL_OUTLINE,
                   wxT("Outlined"), wxDefaultPosition, wxDefaultSize);
  FontOutlineCtrl->SetValue(FontOutlined);
  col13Sizer->Add(FontOutlineCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString style[2];
  style[0] = wxT("&Normal");
  style[1] = wxT("&Italic");
  FontStyleCtrl = new wxRadioBox(this, ID_LABEL_STYLE,
                                 wxT("&Font Style"), wxDefaultPosition,
                                 wxDefaultSize, 2, style, 2, wxRA_SPECIFY_COLS);
  if (FontStyle == wxFONTSTYLE_ITALIC)
    FontStyleCtrl->SetSelection(1);
  else
    FontStyleCtrl->SetSelection(0);
  col14Sizer->Add(FontStyleCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  FontUnderlineCtrl =
    new wxCheckBox(this, ID_LABEL_UNDERLINE,
                   wxT("Underlined"), wxDefaultPosition, wxDefaultSize);
  FontUnderlineCtrl->SetValue(FontUnderlined);
  col14Sizer->Add(FontUnderlineCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// fifth row: Example
  wxBoxSizer *exampleBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  col2Sizer->Add(exampleBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *exampleBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Example"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *exampleSizer = new wxStaticBoxSizer(exampleBox, wxHORIZONTAL);
  exampleBoxSizer->Add(exampleSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  PaintBitmap();
  ExampleCtrl =
    new wxStaticBitmap(this, ID_LABEL_EXAMPLE, Bitmap, wxDefaultPosition,
                       wxSize(Bitmap.GetWidth(), Bitmap.GetHeight()),
                       wxBORDER_SUNKEN);
  exampleSizer->Add(ExampleCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
// sixth row:  Visibility RANGE
  wxBoxSizer *rangeBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  mapLabelSizer->Add(rangeBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *rangeBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Visibility Range Selection"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *rangeSizer = new wxStaticBoxSizer(rangeBox, wxHORIZONTAL);
  rangeBoxSizer->Add(rangeSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  wxBoxSizer *rngSizer1 = new wxBoxSizer(wxHORIZONTAL);
  rangeSizer->Add(rngSizer1, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  wxBoxSizer *rngSizer2 = new wxBoxSizer(wxVERTICAL);
  rangeSizer->Add(rngSizer2, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  wxBoxSizer *range1Sizer = new wxBoxSizer(wxHORIZONTAL);
  rngSizer1->Add(range1Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxString visibility[2];
  visibility[0] = wxT("&Map Labels are always visible");
  visibility[1] =
    wxT("&Map Labels are visible only within the following Scale range");
  VisibilityCtrl =
    new wxRadioBox(this, ID_LABEL_VISIBILITY, wxT("&Visibility Mode"),
                   wxDefaultPosition, wxDefaultSize, 2, visibility, 2,
                   wxRA_SPECIFY_ROWS);
  if (AlwaysVisible == true)
    VisibilityCtrl->SetSelection(0);
  else
    VisibilityCtrl->SetSelection(1);
  range1Sizer->Add(VisibilityCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *range2Sizer = new wxBoxSizer(wxHORIZONTAL);
  rngSizer2->Add(range2Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *minLabel = new wxStaticText(this, wxID_STATIC, wxT("&Min:"));
  range2Sizer->Add(minLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  sprintf(dummy, "%d", MinScale);
  wxString val = wxString::FromUTF8(dummy);
  MinScaleCtrl = new wxSpinCtrl(this, ID_LABEL_MIN_SCALE, val,
                                wxDefaultPosition, wxSize(120, 20),
                                wxSP_ARROW_KEYS, 0, 1000000000, MinScale);
  range2Sizer->Add(MinScaleCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  wxBoxSizer *range3Sizer = new wxBoxSizer(wxHORIZONTAL);
  rngSizer2->Add(range3Sizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *maxLabel = new wxStaticText(this, wxID_STATIC, wxT("&Max:"));
  range3Sizer->Add(maxLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  sprintf(dummy, "%d", MaxScale);
  val = wxString::FromUTF8(dummy);
  MaxScaleCtrl = new wxSpinCtrl(this, ID_LABEL_MAX_SCALE, val,
                                wxDefaultPosition, wxSize(120, 20),
                                wxSP_ARROW_KEYS, 0, 1000000000, MaxScale);
  range3Sizer->Add(MaxScaleCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  if (AlwaysVisible == true)
    {
      MinScaleCtrl->SetValue(wxT(""));
      MaxScaleCtrl->SetValue(wxT(""));
      MinScaleCtrl->Enable(false);
      MaxScaleCtrl->Enable(false);
    }
// saventh row:  ANTI-OVERLAP
  wxBoxSizer *antiBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  mapLabelSizer->Add(antiBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *antiBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("AntiOverlap Optimization"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *antiSizer = new wxStaticBoxSizer(antiBox, wxHORIZONTAL);
  antiBoxSizer->Add(antiSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  AntiOverlapCtrl =
    new wxCheckBox(this, ID_LABEL_ANTI_OVERLAP, wxT("Enable &Anti-Overlap"));
  AntiOverlapCtrl->SetValue(AntiOverlap);
  antiSizer->Add(AntiOverlapCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  wxBoxSizer *priorityBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  antiSizer->Add(priorityBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *priorityBox = new wxStaticBox(this, wxID_STATIC,
                                             wxT("Priority"),
                                             wxDefaultPosition,
                                             wxDefaultSize);
  wxBoxSizer *prioritySizer = new wxStaticBoxSizer(priorityBox, wxHORIZONTAL);
  priorityBoxSizer->Add(prioritySizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  PriorityCtrl =
    new wxCheckBox(this, ID_LABEL_PRIORITY, wxT("Apply &Priority"));
  PriorityCtrl->SetValue(Priority);
  prioritySizer->Add(PriorityCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  prioritySizer->AddSpacer(20);
  wxStaticText *orderByLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&OrderBy Column:"));
  prioritySizer->Add(orderByLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  OrderByCtrl =
    new wxComboBox(this, ID_LABEL_ORDER_BY, wxT(""), wxDefaultPosition,
                   wxDefaultSize, NumColumns, ColumnList,
                   wxCB_DROPDOWN | wxCB_READONLY);
  prioritySizer->Add(OrderByCtrl, 0, wxALIGN_RIGHT | wxALL, 1);
  sel = 0;
  for (i = 1; i < NumColumns; i++)
    {
      if (ColumnList[i] == OrderByColumn)
        sel = i;
    }
  OrderByCtrl->SetSelection(sel);
  DescendingCtrl = new wxCheckBox(this, ID_LABEL_DESCENDING, wxT("&Z-A"));
  DescendingCtrl->SetValue(Descending);
  prioritySizer->Add(DescendingCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// setting initial state
  if (MapLabeling == false)
    {
      AntiOverlapCtrl->Enable(false);
      TextColorCtrl->Enable(false);
      AlphaCtrl->Enable(false);
      PointSizeCtrl->Enable(false);
      FontWeightCtrl->Enable(false);
      FontStyleCtrl->Enable(false);
      FontUnderlineCtrl->Enable(false);
      FontOutlineCtrl->Enable(false);
      VisibilityCtrl->Enable(false);
      MinScaleCtrl->Enable(false);
      MaxScaleCtrl->Enable(false);
      PriorityCtrl->Enable(false);
      OrderByCtrl->Enable(false);
      DescendingCtrl->Enable(false);
      AntiOverlapCtrl->SetValue(false);
      AlphaCtrl->SetValue(255);
      PointSizeCtrl->SetValue(wxT(""));
      FontWeightCtrl->SetSelection(0);
      FontStyleCtrl->SetSelection(0);
      FontUnderlineCtrl->SetValue(false);
      FontOutlineCtrl->SetValue(false);
      VisibilityCtrl->SetSelection(0);
      MinScaleCtrl->SetValue(wxT(""));
      MaxScaleCtrl->SetValue(wxT(""));
      PriorityCtrl->SetValue(false);
      OrderByCtrl->SetSelection(0);
      DescendingCtrl->SetValue(false);
  } else
    {
      if (AntiOverlap == false)
        {
          PriorityCtrl->Enable(false);
          OrderByCtrl->Enable(false);
          DescendingCtrl->Enable(false);
          PriorityCtrl->SetValue(false);
          OrderByCtrl->SetSelection(0);
          DescendingCtrl->SetValue(false);
      } else
        {
          OrderByCtrl->Enable(Priority);
          DescendingCtrl->Enable(Priority);
          if (Priority == false)
            {
              OrderByCtrl->SetSelection(0);
              DescendingCtrl->SetValue(false);
            }
        }
    }
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LabelsDialog::OnOk);
  Connect(ID_LABEL_VISIBILITY, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & LabelsDialog::OnVisibilityChanged);
  Connect(ID_LABEL_COLOR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LabelsDialog::OnTextColorChanged);
  Connect(ID_LABEL_ALPHA, wxEVT_SCROLL_THUMBRELEASE,
          (wxObjectEventFunction) & LabelsDialog::OnAlphaChanged);
  Connect(ID_LABEL_ALPHA, wxEVT_SCROLL_CHANGED,
          (wxObjectEventFunction) & LabelsDialog::OnAlphaChanged);
  Connect(ID_LABEL_SIZE, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & LabelsDialog::OnPointSizeChanged);
  Connect(ID_LABEL_WEIGHT, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & LabelsDialog::OnFontWeightChanged);
  Connect(ID_LABEL_STYLE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & LabelsDialog::OnFontStyleChanged);
  Connect(ID_LABEL_UNDERLINE, wxEVT_COMMAND_CHECKBOX_CLICKED,
          (wxObjectEventFunction) & LabelsDialog::OnFontUnderlineChanged);
  Connect(ID_LABEL_OUTLINE, wxEVT_COMMAND_CHECKBOX_CLICKED,
          (wxObjectEventFunction) & LabelsDialog::OnFontOutlineChanged);
  Connect(ID_LABEL_ENABLED, wxEVT_COMMAND_CHECKBOX_CLICKED,
          (wxObjectEventFunction) & LabelsDialog::OnMapLabelingChanged);
  Connect(ID_LABEL_ANTI_OVERLAP, wxEVT_COMMAND_CHECKBOX_CLICKED,
          (wxObjectEventFunction) & LabelsDialog::OnAntiOverlapChanged);
  Connect(ID_LABEL_PRIORITY, wxEVT_COMMAND_CHECKBOX_CLICKED,
          (wxObjectEventFunction) & LabelsDialog::OnPriorityChanged);
}

void LabelsDialog::GetButtonBitmap(wxColour & color, wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(color));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

void LabelsDialog::GetDisabledButtonBitmap(wxBitmap & bmp)
{
// creating the disabled Bitmap
  bmp = wxBitmap(64, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
  dc->DrawRectangle(-1, -1, 66, 26);
  delete dc;
}

void LabelsDialog::PaintBitmap()
{
// painting the Example Bitmap
  wxBrush checkedBrush;
  double width;
  double height;
  double descent;
  double externalLeading;
  double x;
  double y;
  checkedBrush.SetStipple(wxBitmap(checked_brush_xpm));
  checkedBrush.SetStyle(wxSTIPPLE);
  wxMemoryDC *dc = new wxMemoryDC(Bitmap);
  wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
// background initialization
  gr->SetBrush(checkedBrush);
  gr->DrawRectangle(0, 0, Bitmap.GetWidth(), Bitmap.GetHeight());
  if (MapLabeling == true)
    {
      if (FontOutlined == true)
        {
          // Outlining the text
          if (OutlineBitmap)
            delete OutlineBitmap;
          OutlineBitmap = new wxBitmap(Bitmap.GetWidth(), Bitmap.GetHeight());
          wxMemoryDC *bmp_dc = new wxMemoryDC(*OutlineBitmap);
          wxGraphicsContext *bmp_gr = wxGraphicsContext::Create(*bmp_dc);
          bmp_gr->SetBrush(wxColour(128, 128, 128));
          bmp_gr->DrawRectangle(0, 0, OutlineBitmap->GetWidth(),
                                OutlineBitmap->GetHeight());
          wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
          font.SetPointSize(PointSize);
          if (IsFontBold() == true)
            font.SetWeight(wxFONTWEIGHT_BOLD);
          else
            font.SetWeight(wxFONTWEIGHT_NORMAL);
          if (IsFontItalic() == true)
            font.SetStyle(wxFONTSTYLE_ITALIC);
          else
            font.SetStyle(wxFONTSTYLE_NORMAL);
          font.SetUnderlined(IsFontUnderlined());
          bmp_gr->SetFont(font, wxColour(0, 0, 0));
          wxString text = wxT("Qwerty");
          bmp_gr->GetTextExtent(text, &width, &height, &descent,
                                &externalLeading);
          x = OutlineBitmap->GetWidth() / 2.0;
          y = OutlineBitmap->GetHeight() / 2.0;
          x -= width / 2.0;
          y -= height / 2.0;
          bmp_gr->DrawText(text, x, y);
          delete bmp_gr;
          delete bmp_dc;
          TextOutline();
          wxMask *msk = new wxMask(*OutlineBitmap, wxColour(128, 128, 128));
          OutlineBitmap->SetMask(msk);
          gr->DrawBitmap(*OutlineBitmap, 0, 0, Bitmap.GetWidth(),
                         Bitmap.GetHeight());
        }
      wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
      font.SetPointSize(PointSize);
      if (IsFontBold() == true)
        font.SetWeight(wxFONTWEIGHT_BOLD);
      else
        font.SetWeight(wxFONTWEIGHT_NORMAL);
      if (IsFontItalic() == true)
        font.SetStyle(wxFONTSTYLE_ITALIC);
      else
        font.SetStyle(wxFONTSTYLE_NORMAL);
      font.SetUnderlined(IsFontUnderlined());
      wxColour color;
      if (TextColor.Alpha() == 255)
        color.Set(TextColor.Red(), TextColor.Green(), TextColor.Blue(), 254);
      else
        color.Set(TextColor.Red(), TextColor.Green(), TextColor.Blue(),
                  TextColor.Alpha());
      gr->SetFont(font, color);
      wxString text = wxT("Qwerty");
      gr->GetTextExtent(text, &width, &height, &descent, &externalLeading);
      x = Bitmap.GetWidth() / 2.0;
      y = Bitmap.GetHeight() / 2.0;
      x -= width / 2.0;
      y -= height / 2.0;
      gr->DrawText(text, x, y);

    }
  delete gr;
  delete dc;
}

void LabelsDialog::TextOutline()
{
// applying an outline to text
  int x;
  int y;
  wxImage img = OutlineBitmap->ConvertToImage();
  for (y = 0; y < img.GetHeight(); y++)
    {
      for (x = 0; x < img.GetWidth(); x++)
        {
          if (img.GetRed(x, y) == 128 && img.GetGreen(x, y) == 128
              && img.GetBlue(x, y) == 128)
            continue;
          if (img.GetRed(x, y) == 255 && img.GetGreen(x, y) == 255
              && img.GetBlue(x, y) == 255)
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
          if (img.GetRed(x, y) == 128 && img.GetGreen(x, y) == 128
              && img.GetBlue(x, y) == 128)
            continue;
          if (img.GetRed(x, y) == 255 && img.GetGreen(x, y) == 255
              && img.GetBlue(x, y) == 255)
            continue;
          img.SetRGB(x, y, 128, 128, 128);
        }
    }
  delete OutlineBitmap;
  OutlineBitmap = new wxBitmap(img);
}

void LabelsDialog::OutlinePixel(wxImage * img, int x, int y)
{
// trying to apply the outline color to some pixel
  if (x < 0 || x >= img->GetWidth())
    return;
  if (y < 0 || y >= img->GetHeight())
    return;
  if (img->GetRed(x, y) == 128 && img->GetGreen(x, y) == 128
      && img->GetBlue(x, y) == 128)
    img->SetRGB(x, y, 255, 255, 255);
}

void LabelsDialog::OnTextColorChanged(wxCommandEvent & WXUNUSED(event))
{
// color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(TextColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      wxColour color = colorData.GetColour();
      TextColor =
        wxColour(color.Red(), color.Green(), color.Blue(), TextColor.Alpha());
      PaintBitmap();
      ExampleCtrl->SetBitmap(Bitmap);
      wxBitmap bmp;
      GetButtonBitmap(TextColor, bmp);
      TextColorCtrl->SetBitmapLabel(bmp);
    }
}

void LabelsDialog::OnAlphaChanged(wxCommandEvent & WXUNUSED(event))
{
//
// ALPHA selection changed
//
  TextColor =
    wxColour(TextColor.Red(), TextColor.Green(), TextColor.Blue(),
             AlphaCtrl->GetValue());
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LabelsDialog::OnPointSizeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// PointSize selection changed
//
  PointSize = PointSizeCtrl->GetValue();
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LabelsDialog::OnFontWeightChanged(wxCommandEvent & WXUNUSED(event))
{
//
// FontWeight selection changed
//
  if (FontWeightCtrl->GetSelection() == 1)
    FontWeight = wxFONTWEIGHT_BOLD;
  else
    FontWeight = wxFONTWEIGHT_NORMAL;
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LabelsDialog::OnFontStyleChanged(wxCommandEvent & WXUNUSED(event))
{
//
// FontStyle selection changed
//
  if (FontStyleCtrl->GetSelection() == 1)
    FontStyle = wxFONTSTYLE_ITALIC;
  else
    FontStyle = wxFONTSTYLE_NORMAL;
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LabelsDialog::OnFontUnderlineChanged(wxCommandEvent & WXUNUSED(event))
{
// Font Underlined radiobox changed
  FontUnderlined = FontUnderlineCtrl->GetValue();
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LabelsDialog::OnFontOutlineChanged(wxCommandEvent & WXUNUSED(event))
{
// Font Outlined radiobox changed
  FontOutlined = FontOutlineCtrl->GetValue();
  PaintBitmap();
  ExampleCtrl->SetBitmap(Bitmap);
}

void LabelsDialog::OnVisibilityChanged(wxCommandEvent & WXUNUSED(event))
{
// always visibile radiobox changed
  if (VisibilityCtrl->GetSelection() == 0)
    {
      MinScaleCtrl->SetValue(wxT(""));
      MaxScaleCtrl->SetValue(wxT(""));
      MinScaleCtrl->Enable(false);
      MaxScaleCtrl->Enable(false);
  } else
    {
      MinScaleCtrl->SetValue(0);
      MaxScaleCtrl->SetValue(1000000000);
      MinScaleCtrl->Enable(true);
      MaxScaleCtrl->Enable(true);
    }
}

void LabelsDialog::OnMapLabelingChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Map Labeling on/off
//
  MapLabeling = MapLabelingCtrl->GetValue();
  if (MapLabeling == false)
    {
      AntiOverlapCtrl->Enable(false);
      TextColorCtrl->Enable(false);
      AlphaCtrl->Enable(false);
      PointSizeCtrl->Enable(false);
      FontWeightCtrl->Enable(false);
      FontStyleCtrl->Enable(false);
      FontUnderlineCtrl->Enable(false);
      FontOutlineCtrl->Enable(false);
      VisibilityCtrl->Enable(false);
      MinScaleCtrl->Enable(false);
      MaxScaleCtrl->Enable(false);
      PriorityCtrl->Enable(false);
      OrderByCtrl->Enable(false);
      DescendingCtrl->Enable(false);
      AntiOverlapCtrl->SetValue(false);
      AlphaCtrl->SetValue(255);
      PointSizeCtrl->SetValue(wxT(""));
      FontWeightCtrl->SetSelection(0);
      FontStyleCtrl->SetSelection(0);
      FontUnderlineCtrl->SetValue(false);
      FontOutlineCtrl->SetValue(false);
      VisibilityCtrl->SetSelection(0);
      MinScaleCtrl->SetValue(wxT(""));
      MaxScaleCtrl->SetValue(wxT(""));
      PriorityCtrl->SetValue(false);
      OrderByCtrl->SetSelection(0);
      DescendingCtrl->SetValue(false);
  } else
    {
      AntiOverlapCtrl->Enable(true);
      TextColorCtrl->Enable(true);
      AlphaCtrl->Enable(true);
      PointSizeCtrl->Enable(true);
      FontWeightCtrl->Enable(true);
      FontStyleCtrl->Enable(true);
      FontUnderlineCtrl->Enable(true);
      FontOutlineCtrl->Enable(true);
      FontWeight = wxFONTWEIGHT_NORMAL;
      FontWeightCtrl->SetSelection(0);
      FontStyle = wxFONTSTYLE_NORMAL;
      FontStyleCtrl->SetSelection(0);
      FontUnderlined = false;
      FontUnderlineCtrl->SetValue(FontUnderlined);
      FontOutlined = false;
      FontOutlineCtrl->SetValue(FontOutlined);
      VisibilityCtrl->Enable(true);
      if (AlwaysVisible == false)
        {
          VisibilityCtrl->SetSelection(1);
          MinScaleCtrl->Enable(true);
          MaxScaleCtrl->Enable(true);
          MinScaleCtrl->SetValue(0);
          MaxScaleCtrl->SetValue(1000000000);
      } else
        {
          VisibilityCtrl->SetSelection(0);
          MinScaleCtrl->Enable(false);
          MaxScaleCtrl->Enable(false);
        }
      AntiOverlapCtrl->SetValue(AntiOverlap);
      if (AntiOverlap == true)
        {
          PriorityCtrl->SetValue(Priority);
          if (Priority == true)
            {
              int sel = 0;
              int i;
              for (i = 1; i < NumColumns; i++)
                {
                  if (ColumnList[i] == OrderByColumn)
                    sel = i;
                }
              OrderByCtrl->SetSelection(sel);
              DescendingCtrl->SetValue(Descending);
              OrderByCtrl->Enable(true);
              DescendingCtrl->Enable(true);
          } else
            {
              OrderByCtrl->Enable(false);
              DescendingCtrl->Enable(false);
              OrderByCtrl->SetSelection(0);
              DescendingCtrl->SetValue(false);
            }
        }
      AlphaCtrl->SetValue(TextColor.Alpha());
      PointSizeCtrl->SetValue(PointSize);
    }
}

void LabelsDialog::OnAntiOverlapChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Anti Overlap on/off
//
  AntiOverlap = AntiOverlapCtrl->GetValue();
  if (AntiOverlap == false)
    {
      PriorityCtrl->Enable(false);
      OrderByCtrl->Enable(false);
      DescendingCtrl->Enable(false);
      OrderByCtrl->SetSelection(0);
      DescendingCtrl->SetValue(false);
  } else
    {
      PriorityCtrl->Enable(true);
      OrderByCtrl->Enable(Priority);
      DescendingCtrl->Enable(Priority);
      int sel = 0;
      int i;
      for (i = 1; i < NumColumns; i++)
        {
          if (ColumnList[i] == OrderByColumn)
            sel = i;
        }
      OrderByCtrl->SetSelection(sel);
      DescendingCtrl->SetValue(Descending);
      PriorityCtrl->SetValue(Priority);
    }
}

void LabelsDialog::OnPriorityChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Priority [OrderBy] on/off
//
  Priority = PriorityCtrl->GetValue();
  if (Priority == false)
    {
      OrderByCtrl->SetSelection(0);
      DescendingCtrl->SetValue(false);
  } else
    {
      int sel = 0;
      int i;
      for (i = 1; i < NumColumns; i++)
        {
          if (ColumnList[i] == OrderByColumn)
            sel = i;
        }
      OrderByCtrl->SetSelection(sel);
      DescendingCtrl->SetValue(Descending);
    }
  OrderByCtrl->Enable(Priority);
  DescendingCtrl->Enable(Priority);
}

void LabelsDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  DescName = DescCtrl->GetValue();
  if (LabelCtrl->GetSelection() > 0)
    LabelColumn = LabelCtrl->GetStringSelection();
  else
    LabelColumn = wxT("");
  if (MapLabeling == true && LabelColumn.Len() < 1)
    {
      wxMessageBox(wxT("You must select some Label Column !!!"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  if (MapLabeling == false)
    {
      TextColor = wxColour(0, 0, 0);
      PointSize = 10;
      OrderByColumn = wxT("");
      Descending = false;
      AntiOverlap = false;
      AlwaysVisible = true;
      MinScale = 0;
      MaxScale = 0;
  } else
    {
      PointSize = PointSizeCtrl->GetValue();
      if (AntiOverlap == true)
        {
          if (Priority == false)
            {
              OrderByColumn = wxT("");
              Descending = false;
          } else
            {
              if (OrderByCtrl->GetSelection() > 0)
                OrderByColumn = OrderByCtrl->GetStringSelection();
              else
                OrderByColumn = wxT("");
              if (OrderByColumn.Len() < 1)
                {
                  wxMessageBox(wxT
                               ("You must select some Column Name supporting Priority !!!"),
                               wxT("spatialite-gis"), wxOK | wxICON_WARNING,
                               this);
                  return;
                }
              Descending = DescendingCtrl->GetValue();
            }
      } else
        {
          OrderByColumn = wxT("");
          Descending = false;
        }
      if (VisibilityCtrl->GetSelection() != 0)
        {
          if (MaxScaleCtrl->GetValue() <= MinScaleCtrl->GetValue())
            {
              wxMessageBox(wxT("Invalid Scale Range [mismatching Min/Max]"),
                           wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
              return;
            }
        }
      if (VisibilityCtrl->GetSelection() == 0)
        AlwaysVisible = true;
      else
        AlwaysVisible = false;
      MinScale = MinScaleCtrl->GetValue();
      MaxScale = MaxScaleCtrl->GetValue();
    }
  wxDialog::EndModal(wxID_OK);
}

bool LoadShpDialog::Create(MyFrame * parent, wxString & path, wxString & table,
                           int srid, wxString & column, wxString & defCs)
{
//
// creating the dialog
//
  MainFrame = parent;
  Path = path;
  Table = table;
  Srid = srid;
  Column = column;
  Default = defCs;
  Coerce2D = true;
  Compressed = false;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Load Shapefile")) == false)
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

void LoadShpDialog::CreateControls()
{
//
// creating individual control and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: the Shapefile path
  wxBoxSizer *pathSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(pathSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *pathLabel = new wxStaticText(this, wxID_STATIC, wxT("&Path:"));
  pathSizer->Add(pathLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *pathValue = new wxTextCtrl(this, wxID_STATIC,
                                         Path, wxDefaultPosition,
                                         wxSize(350, 22), wxTE_READONLY);
  pathSizer->Add(pathValue, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: TABLE name
  wxBoxSizer *tableSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(tableSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *tableLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Table name:"));
  tableSizer->Add(tableLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *tableCtrl = new wxTextCtrl(this, ID_LDSHP_TABLE, Table,
                                         wxDefaultPosition, wxSize(350,
                                                                   22));
  tableSizer->Add(tableCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: GEOMETRY COLUMN name
  wxBoxSizer *colSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(colSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *colLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&GeomColumn name:"));
  colSizer->Add(colLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *colCtrl = new wxTextCtrl(this, ID_LDSHP_COLUMN, Column,
                                       wxDefaultPosition, wxSize(350, 22));
  colSizer->Add(colCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fourth row: SRID
  wxBoxSizer *sridSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(sridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticText *sridLabel = new wxStaticText(this, wxID_STATIC, wxT("&SRID:"));
  sridSizer->Add(sridLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxSpinCtrl *sridCtrl = new wxSpinCtrl(this, ID_LDSHP_SRID, wxEmptyString,
                                        wxDefaultPosition, wxSize(80, 20),
                                        wxSP_ARROW_KEYS,
                                        -1, 40000, Srid);
  sridSizer->Add(sridCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// fifth row: CHARSET
  wxStaticBox *charsetBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Charset Encoding"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *charsetSizer = new wxStaticBoxSizer(charsetBox, wxHORIZONTAL);
  sridSizer->Add(charsetSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxListBox *charsetCtrl = new wxListBox(this, ID_LDSHP_CHARSET,
                                         wxDefaultPosition, wxDefaultSize,
                                         MainFrame->GetCharsetsLen(),
                                         MainFrame->GetCharsetsNames(),
                                         wxLB_SINGLE | wxLB_HSCROLL);
  charsetCtrl->SetFont(wxFont
                       (8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_NORMAL));
  int idSel = MainFrame->GetCharsetIndex(Default);
  if (idSel != wxNOT_FOUND)
    charsetCtrl->SetSelection(idSel);
  charsetSizer->Add(charsetCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
// 2D + Compress
  wxBoxSizer *compressBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(compressBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *storageBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Geometry storage"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *storageSizer = new wxStaticBoxSizer(storageBox, wxVERTICAL);
  compressBox->Add(storageSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxCheckBox *coerce2DCtrl = new wxCheckBox(this, ID_LDSHP_COERCE_2D,
                                            wxT("Coerce 2D geometries [x,y]"),
                                            wxDefaultPosition, wxDefaultSize);
  coerce2DCtrl->SetValue(Coerce2D);
  storageSizer->Add(coerce2DCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxCheckBox *compressCtrl = new wxCheckBox(this, ID_LDSHP_COMPRESSED,
                                            wxT("Apply geometry compression"),
                                            wxDefaultPosition, wxDefaultSize);
  compressCtrl->SetValue(Compressed);
  storageSizer->Add(compressCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & LoadShpDialog::OnOk);
}

void LoadShpDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  wxTextCtrl *tableCtrl = (wxTextCtrl *) FindWindow(ID_LDSHP_TABLE);
  Table = tableCtrl->GetValue();
  if (Table.Len() < 1)
    {
      wxMessageBox(wxT("You must specify the TABLE NAME !!!"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  if (MainFrame->TableAlreadyExists(Table) == true)
    {
      wxMessageBox(wxT("a table name '") + Table + wxT("' already exists"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  wxTextCtrl *columnCtrl = (wxTextCtrl *) FindWindow(ID_LDSHP_COLUMN);
  Column = columnCtrl->GetValue();
  if (Column.Len() < 1)
    {
      wxMessageBox(wxT("You must specify the GEOMETRY COLUMN NAME !!!"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  wxSpinCtrl *sridCtrl = (wxSpinCtrl *) FindWindow(ID_LDSHP_SRID);
  Srid = sridCtrl->GetValue();
  if (MainFrame->SridNotExists(Srid) == true)
    {
      wxMessageBox(wxT("invalid SRID value"), wxT("spatialite-gis"),
                   wxOK | wxICON_WARNING, this);
      return;
    }
  wxListBox *charsetCtrl = (wxListBox *) FindWindow(ID_LDSHP_CHARSET);
  int idSel = charsetCtrl->GetSelection();
  if (idSel == wxNOT_FOUND)
    {
      wxMessageBox(wxT("you must select some Charset Encoding from the list"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  wxString *charsets = MainFrame->GetCharsets();
  Charset = *(charsets + idSel);
  wxCheckBox *coerce2DCtrl = (wxCheckBox *) FindWindow(ID_LDSHP_COERCE_2D);
  Coerce2D = coerce2DCtrl->GetValue();
  wxCheckBox *compressCtrl = (wxCheckBox *) FindWindow(ID_LDSHP_COMPRESSED);
  Compressed = compressCtrl->GetValue();
  wxDialog::EndModal(wxID_OK);
}

bool DumpShpDialog::Create(MyFrame * parent, wxString & path, wxString & table,
                           wxString & column, wxString & defCs)
{
//
// creating the dialog
//
  MainFrame = parent;
  Path = path;
  Table = table;
  Column = column;
  Default = defCs;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Dump Shapefile")) == false)
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

void DumpShpDialog::CreateControls()
{
//
// creating individual control and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: the Shapefile path
  wxBoxSizer *pathSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(pathSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *pathLabel = new wxStaticText(this, wxID_STATIC, wxT("&Path:"));
  pathSizer->Add(pathLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *pathValue = new wxTextCtrl(this, wxID_STATIC,
                                         Path, wxDefaultPosition,
                                         wxSize(350, 22), wxTE_READONLY);
  pathSizer->Add(pathValue, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: TABLE name
  wxBoxSizer *tableSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(tableSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *tableLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Table name:"));
  tableSizer->Add(tableLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *tableCtrl = new wxTextCtrl(this, wxID_STATIC, Table,
                                         wxDefaultPosition, wxSize(350,
                                                                   22));
  tableCtrl->Enable(false);
  tableSizer->Add(tableCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// third row: GEOMETRY COLUMN name
  wxBoxSizer *colSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(colSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *colLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&GeomColumn name:"));
  colSizer->Add(colLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *colCtrl = new wxTextCtrl(this, wxID_STATIC, Column,
                                       wxDefaultPosition, wxSize(350, 22));
  colCtrl->Enable(false);
  colSizer->Add(colCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// fourth row: CHARSET
  wxBoxSizer *csSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(csSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *charsetBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Charset Encoding"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *charsetSizer = new wxStaticBoxSizer(charsetBox, wxHORIZONTAL);
  csSizer->Add(charsetSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxListBox *charsetCtrl = new wxListBox(this, ID_DMPSHP_CHARSET,
                                         wxDefaultPosition, wxDefaultSize,
                                         MainFrame->GetCharsetsLen(),
                                         MainFrame->GetCharsetsNames(),
                                         wxLB_SINGLE | wxLB_HSCROLL);
  charsetCtrl->SetFont(wxFont
                       (8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_NORMAL));
  int idSel = MainFrame->GetCharsetIndex(Default);
  if (idSel != wxNOT_FOUND)
    charsetCtrl->SetSelection(idSel);
  charsetSizer->Add(charsetCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & DumpShpDialog::OnOk);
}

void DumpShpDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  wxListBox *charsetCtrl = (wxListBox *) FindWindow(ID_DMPSHP_CHARSET);
  int idSel = charsetCtrl->GetSelection();
  if (idSel == wxNOT_FOUND)
    {
      wxMessageBox(wxT("you must select some Charset Encoding from the list"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  wxString *charsets = MainFrame->GetCharsets();
  Charset = *(charsets + idSel);
  wxDialog::EndModal(wxID_OK);
}

bool DefaultCharsetDialog::Create(MyFrame * parent, wxString & charset,
                                  bool ask)
{
//
// creating the dialog
//
  MainFrame = parent;
  Charset = charset;
  AskCharset = ask;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Charset settings")) == false)
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

void DefaultCharsetDialog::CreateControls()
{
//
// creating individual control and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: the DEFAULT CHARSET
  wxBoxSizer *csSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(csSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticBox *charsetBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Default Output Charset"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *charsetSizer = new wxStaticBoxSizer(charsetBox, wxVERTICAL);
  csSizer->Add(charsetSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxListBox *charsetCtrl = new wxListBox(this, ID_DFLT_CHARSET,
                                         wxDefaultPosition, wxDefaultSize,
                                         MainFrame->GetCharsetsLen(),
                                         MainFrame->GetCharsetsNames(),
                                         wxLB_SINGLE | wxLB_HSCROLL);
  charsetCtrl->SetFont(wxFont
                       (8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_NORMAL));
  int idSel = MainFrame->GetCharsetIndex(Charset);
  if (idSel != wxNOT_FOUND)
    charsetCtrl->SetSelection(idSel);
  charsetSizer->Add(charsetCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
// second row: the ASK CHARSET
  wxBoxSizer *askSizer = new wxBoxSizer(wxHORIZONTAL);
  charsetSizer->Add(askSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxCheckBox *askCtrl = new wxCheckBox(this, ID_DFLT_ASK,
                                       wxT("Ask output charset every time"),
                                       wxDefaultPosition, wxDefaultSize);
  askCtrl->SetValue(AskCharset);
  askSizer->Add(askCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & DefaultCharsetDialog::OnOk);
}

void DefaultCharsetDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  wxListBox *charsetCtrl = (wxListBox *) FindWindow(ID_DFLT_CHARSET);
  int idSel = charsetCtrl->GetSelection();
  if (idSel == wxNOT_FOUND)
    {
      wxMessageBox(wxT
                   ("you must select some Default Charset Encoding from the list"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  wxString *charsets = MainFrame->GetCharsets();
  Charset = *(charsets + idSel);
  wxCheckBox *askCtrl = (wxCheckBox *) FindWindow(ID_DFLT_ASK);
  AskCharset = askCtrl->GetValue();
  wxDialog::EndModal(wxID_OK);
}

bool SearchSridDialog::Create(MyFrame * parent)
{
//
// creating the dialog
//
  MainFrame = parent;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Searching a SRID by its name")) ==
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

void SearchSridDialog::CreateControls()
{
//
// creating individual control and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// First row: SEARCH string
  wxBoxSizer *searchSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(searchSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticText *searchLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Search for:"));
  searchSizer->Add(searchLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  TextCtrl = new wxTextCtrl(this, ID_SRID_TEXT, wxT(""),
                            wxDefaultPosition, wxSize(200, 22));
  searchSizer->Add(TextCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// serch mode
  wxString mode[2];
  mode[0] = wxT("by EPSG &SRID code");
  mode[1] = wxT("by &name");
  ModeCtrl = new wxRadioBox(this, ID_SRID_MODE,
                            wxT("&search mode"),
                            wxDefaultPosition, wxDefaultSize, 2, mode, 2,
                            wxRA_SPECIFY_ROWS);
  ModeCtrl->SetSelection(1);
  searchSizer->Add(ModeCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// SEARCH - CANCEL buttons
  wxBoxSizer *srcCancelBox = new wxBoxSizer(wxVERTICAL);
  searchSizer->Add(srcCancelBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  SearchCtrl = new wxButton(this, ID_SRID_SEARCH, wxT("&Search"));
  srcCancelBox->Add(SearchCtrl, 0, wxALIGN_TOP | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Quit"));
  srcCancelBox->Add(cancel, 0, wxALIGN_BOTTOM | wxALL, 5);
// a GRID to show results
  wxBoxSizer *sridBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(sridBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *sridBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT
                                         ("CRS - Coordinate Reference Systems"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *sridSizer = new wxStaticBoxSizer(sridBox, wxVERTICAL);
  sridBoxSizer->Add(sridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  GridSizer = new wxBoxSizer(wxHORIZONTAL);
  sridSizer->Add(GridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  GridCtrl =
    new wxGrid(this, ID_SRID_GRID, wxDefaultPosition, wxSize(500, 200));
  GridCtrl->CreateGrid(1, 1);
  GridCtrl->SetColLabelValue(0, wxT("Message"));
  GridCtrl->SetRowLabelValue(0, wxT("1"));
  GridCtrl->SetCellValue(0, 0, wxT("no matching SRID was found"));
  GridCtrl->SetRowLabelSize(wxGRID_AUTOSIZE);
  GridCtrl->AutoSize();
  GridSizer->Add(GridCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// appends event handler for SEARCH button
  Connect(ID_SRID_SEARCH, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & SearchSridDialog::OnSearch);
}

void SearchSridDialog::OnSearch(wxCommandEvent & WXUNUSED(event))
{
//
// searching and displaying the results 
//
  wxString searchFor = TextCtrl->GetValue();
  wxString sql;
  int ret;
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *value;
  char num[16];
  wxString cell;
  if (ModeCtrl->GetSelection() == 0)
    {
      // searching by EPSG code
      long srid;
      if (searchFor.ToLong(&srid) == false)
        {
          wxMessageBox(wxT("You must specify a numeric code to search for !!!"),
                       wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
          return;
        }
      sql = wxT("SELECT srid, auth_name, ref_sys_name, proj4text ");
      sql += wxT("FROM spatial_ref_sys ");
      sql += wxT("WHERE auth_name = 'epsg' AND auth_srid = ");
      sql += searchFor;
  } else
    {
      // searching by SRID name
      if (searchFor.Len() < 3)
        {
          wxMessageBox(wxT
                       ("You must specify a string to search for !!! [min. 3 chars]"),
                       wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
          return;
        }
      sql = wxT("SELECT srid, auth_name, ref_sys_name, proj4text ");
      sql += wxT("FROM spatial_ref_sys ");
      sql += wxT("WHERE ref_sys_name LIKE '%");
      sql += searchFor;
      sql += wxT("%' ORDER BY srid");
    }
// retrieving the result set
  ret = sqlite3_get_table(MainFrame->GetSqlite(), sql.ToUTF8(), &results,
                          &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  wxGrid *newGrid =
    new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(500, 200));
  if (rows < 1)
    {
      // empty result set
      newGrid->CreateGrid(1, 1);
      newGrid->SetColLabelValue(0, wxT("Message"));
      newGrid->SetRowLabelValue(0, wxT("1"));
      newGrid->SetCellValue(0, 0, wxT("no matching SRID was found"));
  } else
    {
      newGrid->CreateGrid(rows, 4);
      newGrid->SetColLabelValue(0, wxT("srid"));
      newGrid->SetColLabelValue(1, wxT("auth_name"));
      newGrid->SetColLabelValue(2, wxT("ref_sys_name"));
      newGrid->SetColLabelValue(3, wxT("proj4text"));
      for (i = 1; i <= rows; i++)
        {
          sprintf(num, "%d", i);
          cell = wxString::FromUTF8(num);
          newGrid->SetRowLabelValue(i - 1, cell);
          value = results[(i * columns) + 0];
          cell = wxString::FromUTF8(value);
          newGrid->SetCellValue(i - 1, 0, cell);
          value = results[(i * columns) + 1];
          cell = wxString::FromUTF8(value);
          newGrid->SetCellValue(i - 1, 1, cell);
          value = results[(i * columns) + 2];
          cell = wxString::FromUTF8(value);
          newGrid->SetCellValue(i - 1, 2, cell);
          value = results[(i * columns) + 3];
          cell = wxString::FromUTF8(value);
          newGrid->SetCellValue(i - 1, 3, cell);
        }
    }
  sqlite3_free_table(results);

// showing the new grid  
  newGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
  newGrid->AutoSize();
  newGrid->EnableEditing(false);
  GridSizer->Replace(GridCtrl, newGrid);
  GridSizer->Layout();
  delete GridCtrl;
  GridCtrl = newGrid;
}

bool CreateTableDialog::Create(MyFrame * parent, int srid)
{
//
// creating the dialog
//
  MainFrame = parent;
  Srid = srid;
  CurrentColumn = NULL;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Create DB Spatial Table")) ==
      false)
    return false;
  wxString name(wxT("PkId"));
  wxString desc(wxT("Unique ID"));
  Table.Add(name, desc, SQLITE_INTEGER, true, false, 0, 0);
// populates individual controls
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void CreateTableDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[128];
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
// first row: the Table name
  wxBoxSizer *tableBoxSizer = new wxBoxSizer(wxVERTICAL);
  boxSizer->Add(tableBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *tableBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Vector Layer - DB Table"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *tableSizer = new wxStaticBoxSizer(tableBox, wxVERTICAL);
  tableBoxSizer->Add(tableSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxBoxSizer *tblSizer = new wxBoxSizer(wxHORIZONTAL);
  tableSizer->Add(tblSizer, 0, wxALIGN_RIGHT | wxALL, 2);
  wxStaticText *tableLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Table Name:"));
  tblSizer->Add(tableLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  TableCtrl = new wxTextCtrl(this, ID_CREATE_TABLE_TABLE,
                             wxT(""), wxDefaultPosition, wxSize(350, 22));
  tblSizer->Add(TableCtrl, 0, wxALIGN_RIGHT | wxALL, 2);
// second row: description
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  tableSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  DescCtrl =
    new wxTextCtrl(this, ID_CREATE_TABLE_DESC, wxT(""), wxDefaultPosition,
                   wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
// third row: the Geometry name
  wxBoxSizer *geomBoxSizer = new wxBoxSizer(wxVERTICAL);
  boxSizer->Add(geomBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *geomBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Geometry Column"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *geomSizer = new wxStaticBoxSizer(geomBox, wxVERTICAL);
  geomBoxSizer->Add(geomSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxBoxSizer *geoSizer = new wxBoxSizer(wxHORIZONTAL);
  geomSizer->Add(geoSizer, 0, wxALIGN_RIGHT | wxALL, 2);
  wxStaticText *geomLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column Name:"));
  geoSizer->Add(geomLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  GeomCtrl = new wxTextCtrl(this, ID_CREATE_TABLE_GEOM,
                            wxT("Geometry"), wxDefaultPosition,
                            wxSize(150, 22));
  geoSizer->Add(GeomCtrl, 0, wxALIGN_RIGHT | wxALL, 2);
  wxStaticText *sridLabel = new wxStaticText(this, wxID_STATIC, wxT("&SRID:"));
  geoSizer->Add(sridLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  sprintf(dummy, "%d", Srid);
  wxString srid = wxString::FromUTF8(dummy);
  SridCtrl = new wxSpinCtrl(this, ID_CREATE_TABLE_GEOM_SRID, srid,
                            wxDefaultPosition, wxSize(80, 20), wxSP_ARROW_KEYS,
                            -1, 40000, Srid);
  geoSizer->Add(SridCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
// fifth row: Geometry Type
  wxBoxSizer *geomTypeSizer = new wxBoxSizer(wxHORIZONTAL);
  geomSizer->Add(geomTypeSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxString gtypes[6];
  gtypes[0] = wxT("&POINT");
  gtypes[1] = wxT("&LINESTRING");
  gtypes[2] = wxT("&POLYGON");
  gtypes[3] = wxT("&MULTIPOINT");
  gtypes[4] = wxT("&MULTILINESTRING");
  gtypes[5] = wxT("&MULTIPOLYGON");
  GeoTypeCtrl = new wxRadioBox(this, ID_CREATE_TABLE_GEOM_TYPE,
                               wxT("&Geometry Type"),
                               wxDefaultPosition, wxDefaultSize, 6, gtypes, 3,
                               wxRA_SPECIFY_COLS);
  GeoTypeCtrl->SetSelection(0);
  geomSizer->Add(GeoTypeCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
// sixth row: Column List
  wxStaticBox *columnsBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Columns"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *columnsSizer = new wxStaticBoxSizer(columnsBox, wxHORIZONTAL);
  boxSizer->Add(columnsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  int count = Table.GetCount();
  wxString *columns = new wxString[count];
  int i = 0;
  TableColumn *pColumn = Table.GetFirst();
  while (pColumn)
    {
      columns[i] = pColumn->GetColumnDefs();
      i++;
      pColumn = pColumn->GetNext();
    }
  ListCtrl = new wxListBox(this, ID_CREATE_TABLE_LIST,
                           wxDefaultPosition, wxSize(400, 100),
                           count, columns, wxLB_SINGLE | wxLB_HSCROLL);
  ListCtrl->SetFont(wxFont
                    (8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL,
                     wxFONTWEIGHT_NORMAL));
  ListCtrl->SetSelection(0);
  columnsSizer->Add(ListCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  CurrentColumn = Table.Find(ListCtrl->GetSelection());
// eigth row: Column Name
  wxBoxSizer *columnBoxSizer = new wxBoxSizer(wxVERTICAL);
  boxSizer->Add(columnBoxSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticBox *columnBox = new wxStaticBox(this, wxID_STATIC,
                                           wxT("Column details"),
                                           wxDefaultPosition,
                                           wxDefaultSize);
  wxBoxSizer *columnSizer = new wxStaticBoxSizer(columnBox, wxVERTICAL);
  columnBoxSizer->Add(columnSizer, 0, wxALIGN_LEFT | wxALL, 2);
  wxBoxSizer *nameSizer = new wxBoxSizer(wxHORIZONTAL);
  columnSizer->Add(nameSizer, 0, wxALIGN_LEFT | wxALL, 2);
  wxStaticText *nameLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column Name:"));
  nameSizer->Add(nameLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  ColNameCtrl = new wxTextCtrl(this, ID_CREATE_TABLE_COLUMN,
                               wxT(""), wxDefaultPosition, wxSize(150, 22));
  nameSizer->Add(ColNameCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  wxString isnull[2];
  isnull[0] = wxT("yes");
  isnull[1] = wxT("&no");
  ColNullCtrl = new wxRadioBox(this, ID_CREATE_TABLE_COL_NULL,
                               wxT("&NULL values"),
                               wxDefaultPosition, wxDefaultSize, 2, isnull, 2,
                               wxRA_SPECIFY_COLS);
  ColNullCtrl->SetSelection(0);
  ColNullCtrl->Enable(false);
  nameSizer->Add(ColNullCtrl, 0, wxALIGN_RIGHT | wxALL, 2);
// ninethd row: column description
  wxBoxSizer *colDescSizer = new wxBoxSizer(wxHORIZONTAL);
  columnSizer->Add(colDescSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *colDescLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  colDescSizer->Add(colDescLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  ColDescCtrl =
    new wxTextCtrl(this, ID_CREATE_TABLE_COL_DESC, wxT(""), wxDefaultPosition,
                   wxSize(350, 22));
  colDescSizer->Add(ColDescCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
// tenth row: Column Type
  wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
  columnSizer->Add(mainSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxBoxSizer *leftSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(leftSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(rightSizer, 0, wxALIGN_BOTTOM | wxALL, 0);
  wxBoxSizer *colTypeSizer = new wxBoxSizer(wxHORIZONTAL);
  leftSizer->Add(colTypeSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxString coltypes[8];
  coltypes[0] = wxT("&INTEGER");
  coltypes[1] = wxT("&FLOAT");
  coltypes[2] = wxT("&TEXT");
  coltypes[3] = wxT("&BOOLEAN");
  coltypes[4] = wxT("&DATE");
  coltypes[5] = wxT("&DATETIME");
  coltypes[6] = wxT("&IMAGE");
  coltypes[7] = wxT("&BLOB");
  ColTypeCtrl = new wxRadioBox(this, ID_CREATE_TABLE_COL_TYPE,
                               wxT("&Data Type"),
                               wxDefaultPosition, wxDefaultSize, 8, coltypes, 4,
                               wxRA_SPECIFY_COLS);
  ColTypeCtrl->SetSelection(0);
  colTypeSizer->Add(ColTypeCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
// eleventh row: Format hints
  wxStaticBox *formatBox = new wxStaticBox(this, wxID_STATIC,
                                           wxT("Format hints"),
                                           wxDefaultPosition,
                                           wxDefaultSize);
  wxBoxSizer *formatSizer = new wxStaticBoxSizer(formatBox, wxHORIZONTAL);
  leftSizer->Add(formatSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxStaticText *lenLabel = new wxStaticText(this, wxID_STATIC, wxT("&Length:"));
  formatSizer->Add(lenLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  ColLenCtrl = new wxSpinCtrl(this, ID_CREATE_TABLE_COL_LEN, wxT(""),
                              wxDefaultPosition, wxSize(80, 20),
                              wxSP_ARROW_KEYS, 1, 255, 1);
  ColLenCtrl->Enable(false);
  formatSizer->Add(ColLenCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  wxStaticText *decLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Decimal digits:"));
  formatSizer->Add(decLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  ColDecCtrl = new wxSpinCtrl(this, ID_CREATE_TABLE_COL_DEC, wxT(""),
                              wxDefaultPosition, wxSize(80, 20),
                              wxSP_ARROW_KEYS, 1, 18, 1);
  ColDecCtrl->Enable(false);
  formatSizer->Add(ColDecCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  ClearBtn = new wxButton(this, ID_CREATE_TABLE_COL_CLEAR, wxT("New Column"));
  rightSizer->Add(ClearBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  AddBtn = new wxButton(this, ID_CREATE_TABLE_COL_ADD, wxT("Save Changes"));
  rightSizer->Add(AddBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  DeleteBtn =
    new wxButton(this, ID_CREATE_TABLE_COL_DELETE, wxT("Delete Column"));
  DeleteBtn->Enable(false);
  rightSizer->Add(DeleteBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  pColumn = Table.Find(0);
  ColNameCtrl->SetValue(pColumn->GetColumn());
  ColDescCtrl->SetValue(pColumn->GetDescName());
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&Create Table"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & CreateTableDialog::OnOk);
  Connect(ID_CREATE_TABLE_COL_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & CreateTableDialog::OnClear);
  Connect(ID_CREATE_TABLE_COL_ADD, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & CreateTableDialog::OnAdd);
  Connect(ID_CREATE_TABLE_COL_DELETE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & CreateTableDialog::OnDelete);
  Connect(ID_CREATE_TABLE_LIST, wxEVT_COMMAND_LISTBOX_SELECTED,
          (wxObjectEventFunction) & CreateTableDialog::OnColumnSelected);
  Connect(ID_CREATE_TABLE_COL_TYPE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & CreateTableDialog::OnTypeSelected);
}

void CreateTableDialog::OnClear(wxCommandEvent & WXUNUSED(event))
{
//
// prepating to insert a new column
//
  CurrentColumn = NULL;
  ListCtrl->SetSelection(wxNOT_FOUND);
  ColNameCtrl->SetValue(wxT(""));
  ColDescCtrl->SetValue(wxT(""));
  ColLenCtrl->SetValue(wxT(""));
  ColDecCtrl->SetValue(wxT(""));
  ColNullCtrl->SetSelection(0);
  ColTypeCtrl->SetSelection(0);
  ColDecCtrl->Enable(false);
  ColLenCtrl->Enable(false);
  ClearBtn->Enable(false);
  DeleteBtn->Enable(false);
  ColNullCtrl->Enable(true);
  AddBtn->SetLabel(wxT("Add Column"));
}

void CreateTableDialog::OnAdd(wxCommandEvent & WXUNUSED(event))
{
//
// adding a new column  def[or replacing an existing one]
//
  wxString name = ColNameCtrl->GetValue();
  if (name.Len() == 0)
    {
      wxString msg = wxT("You must specify some COLUMN NAME !!!");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  bool duplicate;
  if (CurrentColumn)
    duplicate = Table.IsDuplicate(CurrentColumn, name);
  else
    duplicate = Table.IsDuplicate(name);
  if (duplicate == true)
    {
      wxString msg = wxT("Duplicate Column Name: '");
      msg += name;
      msg += wxT("'");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  wxString desc = ColDescCtrl->GetValue();
  int type = SQLITE_INTEGER;
  switch (ColTypeCtrl->GetSelection())
    {
      case 1:
        type = SQLITE_FLOAT;
        break;
      case 2:
        type = SQLITE_TEXT;
        break;
      case 3:
        type = SQLITE_BOOLEAN;
        break;
      case 4:
        type = SQLITE_DATE;
        break;
      case 5:
        type = SQLITE_DATETIME;
        break;
      case 6:
        type = SQLITE_IMAGE;
        break;
      case 7:
        type = SQLITE_BLOB;
        break;
    };
  bool notNull = false;
  if (ColNullCtrl->GetSelection() == 1)
    notNull = true;
  if (type == SQLITE_FLOAT)
    {
      int decs = ColDecCtrl->GetValue();
      if (CurrentColumn)
        CurrentColumn->Set(name, desc, type, false, notNull, 0, decs);
      else
        Table.Add(name, desc, type, false, notNull, 0, decs);
  } else if (type == SQLITE_TEXT)
    {
      int len = ColLenCtrl->GetValue();
      if (CurrentColumn)
        CurrentColumn->Set(name, desc, type, false, notNull, len, 0);
      else
        Table.Add(name, desc, type, false, notNull, len, 0);
  } else
    {
      if (CurrentColumn)
        CurrentColumn->Set(name, desc, type, false, notNull, 0, 0);
      else
        Table.Add(name, desc, type, false, notNull, 0, 0);
    }
// updating the Columns List
  ListCtrl->Clear();
  TableColumn *pColumn = Table.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsDeleted() == false)
        ListCtrl->Append(pColumn->GetColumnDefs());
      pColumn = pColumn->GetNext();
    }
  int pos = Table.Find(name);
  if (pos < 4)
    pos = 4;
  ListCtrl->SetFirstItem(pos - 4);
// resetting the fields
  CurrentColumn = NULL;
  ListCtrl->SetSelection(wxNOT_FOUND);
  ColNameCtrl->SetValue(wxT(""));
  ColDescCtrl->SetValue(wxT(""));
  ColLenCtrl->SetValue(wxT(""));
  ColDecCtrl->SetValue(wxT(""));
  ColNullCtrl->SetSelection(0);
  ColTypeCtrl->SetSelection(0);
  ColDecCtrl->Enable(false);
  ColLenCtrl->Enable(false);
  ClearBtn->Enable(false);
  DeleteBtn->Enable(false);
  AddBtn->SetLabel(wxT("Add Column"));
}

void CreateTableDialog::OnDelete(wxCommandEvent & WXUNUSED(event))
{
//
// deleting some column
//
  if (!CurrentColumn)
    return;
  CurrentColumn->Delete();
// updating the Columns List
  ListCtrl->Clear();
  TableColumn *pColumn = Table.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsDeleted() == false)
        ListCtrl->Append(pColumn->GetColumnDefs());
      pColumn = pColumn->GetNext();
    }
// resetting the fields
  CurrentColumn = NULL;
  ListCtrl->SetSelection(wxNOT_FOUND);
  ColNameCtrl->SetValue(wxT(""));
  ColDescCtrl->SetValue(wxT(""));
  ColLenCtrl->SetValue(wxT(""));
  ColDecCtrl->SetValue(wxT(""));
  ColNullCtrl->SetSelection(0);
  ColTypeCtrl->SetSelection(0);
  ColDecCtrl->Enable(false);
  ColLenCtrl->Enable(false);
  ClearBtn->Enable(false);
  DeleteBtn->Enable(false);
  AddBtn->SetLabel(wxT("Add Column"));
}

void CreateTableDialog::OnTypeSelected(wxCommandEvent & WXUNUSED(event))
{
//
// some Data Type has just been selected
//
  if (ColTypeCtrl->GetSelection() == 1)
    ColDecCtrl->Enable(true);
  else
    ColDecCtrl->Enable(false);
  if (ColTypeCtrl->GetSelection() == 2)
    ColLenCtrl->Enable(true);
  else
    ColLenCtrl->Enable(false);
}

void CreateTableDialog::OnColumnSelected(wxCommandEvent & WXUNUSED(event))
{
//
// some Column Def has just been selected
//
  TableColumn *pColumn = Table.Find(ListCtrl->GetSelection());
  if (pColumn == NULL)
    {
      // clearing the Column Def fields
      CurrentColumn = NULL;
      ListCtrl->SetSelection(wxNOT_FOUND);
      ColNameCtrl->SetValue(wxT(""));
      ColDescCtrl->SetValue(wxT(""));
      ColLenCtrl->SetValue(wxT(""));
      ColDecCtrl->SetValue(wxT(""));
      ColNullCtrl->SetSelection(0);
      ColTypeCtrl->SetSelection(0);
      ColDecCtrl->Enable(false);
      ColLenCtrl->Enable(false);
      ClearBtn->Enable(false);
      DeleteBtn->Enable(false);
      AddBtn->SetLabel(wxT("Add Column"));
  } else
    {
      // updating the Column Defs fields
      ColNameCtrl->SetValue(pColumn->GetColumn());
      ColDescCtrl->SetValue(pColumn->GetDescName());
      ColLenCtrl->SetValue(pColumn->GetLength());
      ColDecCtrl->SetValue(pColumn->GetDecimals());
      if (pColumn->IsNotNull() == true)
        ColNullCtrl->SetSelection(1);
      else
        ColNullCtrl->SetSelection(0);
      switch (pColumn->GetType())
        {
          case SQLITE_INTEGER:
            ColTypeCtrl->SetSelection(0);
            break;
          case SQLITE_FLOAT:
            ColTypeCtrl->SetSelection(1);
            break;
          case SQLITE_TEXT:
            ColTypeCtrl->SetSelection(2);
            break;
          case SQLITE_BOOLEAN:
            ColTypeCtrl->SetSelection(3);
            break;
          case SQLITE_DATE:
            ColTypeCtrl->SetSelection(4);
            break;
          case SQLITE_DATETIME:
            ColTypeCtrl->SetSelection(5);
            break;
          case SQLITE_IMAGE:
            ColTypeCtrl->SetSelection(6);
            break;
          case SQLITE_BLOB:
            ColTypeCtrl->SetSelection(7);
            break;
        };
      switch (pColumn->GetType())
        {
          case SQLITE_FLOAT:
            ColLenCtrl->SetValue(wxT(""));
            ColLenCtrl->Enable(false);
            ColDecCtrl->SetValue(pColumn->GetDecimals());
            ColDecCtrl->Enable(true);
            break;
          case SQLITE_TEXT:
            ColLenCtrl->SetValue(pColumn->GetLength());
            ColLenCtrl->Enable(true);
            ColDecCtrl->SetValue(wxT(""));
            ColDecCtrl->Enable(false);
            break;
          case SQLITE_INTEGER:
          case SQLITE_DATE:
          case SQLITE_DATETIME:
          case SQLITE_BOOLEAN:
          case SQLITE_IMAGE:
          case SQLITE_BLOB:
            ColLenCtrl->SetValue(wxT(""));
            ColDecCtrl->SetValue(wxT(""));
            ColDecCtrl->Enable(false);
            ColLenCtrl->Enable(false);
            break;
        };
      ClearBtn->Enable(true);
      if (pColumn == Table.GetFirst())
        {
          ColNullCtrl->SetSelection(0);
          ColNullCtrl->Enable(false);
          ColTypeCtrl->SetSelection(0);
          ColTypeCtrl->Enable(false);
          ColLenCtrl->SetValue(wxT(""));
          ColDecCtrl->SetValue(wxT(""));
          ColDecCtrl->Enable(false);
          ColLenCtrl->Enable(false);
          DeleteBtn->Enable(false);
          ColNullCtrl->Enable(false);
      } else
        {
          DeleteBtn->Enable(true);
          ColNullCtrl->Enable(true);
        }
      AddBtn->SetLabel(wxT("Save Changes"));
      CurrentColumn = pColumn;
    }
}

void CreateTableDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  TableName = TableCtrl->GetValue();
  if (TableName.Len() == 0)
    {
      wxString msg = wxT("You must specify some TABLE NAME !!!");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  if (MainFrame->TableAlreadyExists(TableName) == true)
    {
      wxString msg = wxT("Duplicate TABLE NAME !!!\n\n");
      msg += wxT("A table of identical name already exists");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  DescName = DescCtrl->GetValue();
  GeometryColumn = GeomCtrl->GetValue();
  if (GeometryColumn.Len() == 0)
    {
      wxString msg = wxT("You must specify some GEOMETRY COLUMN NAME !!!");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  if (Table.IsDuplicate(GeometryColumn) == true)
    {
      wxString msg = wxT("Duplicate Column Name for GEOMETRY Column !!!");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  Srid = SridCtrl->GetValue();
  SridInfo info(Srid);
  MainFrame->GetSridInfo(&info);
  if (info.IsNotSet() == true)
    {
      wxMessageBox(wxT("You must specify a valid SRID !!!"),
                   wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  switch (GeoTypeCtrl->GetSelection())
    {
      case 0:
        GeometryType = wxT("POINT");
        break;
      case 1:
        GeometryType = wxT("LINESTRING");
        break;
      case 2:
        GeometryType = wxT("POLYGON");
        break;
      case 3:
        GeometryType = wxT("MULTIPOINT");
        break;
      case 4:
        GeometryType = wxT("MULTILINESTRING");
        break;
      case 5:
        GeometryType = wxT("MULTIPOLYGON");
        break;
    };
  if (DoCreateTable() == false)
    return;
  wxDialog::EndModal(wxID_OK);
}

bool CreateTableDialog::DoCreateTable()
{
//
// trying to create the table 
//
  wxString sql;
  int ret;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char dummy[128];
  char tblName[1024];
  char geomCol[1024];
  char colName[1024];
  char descName[1024];
  char type[64];
  char *errMsg = NULL;
  int red;
  int green;
  int blue;
  int geomType = LAYER_GEOMETRY;
  bool multiType = false;
  LayerObject layer;
  TableColumn *pColumn;

  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(sqlite, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
// creating the table
  sql = wxT("CREATE TABLE \"");
  sql += TableName;
  sql += wxT("\" (\n");
  pColumn = Table.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsDeleted() == true)
        {
          pColumn = pColumn->GetNext();
          continue;
        }
      sql += wxT("\"");
      sql += pColumn->GetColumn();
      sql += wxT("\" ");
      switch (pColumn->GetType())
        {
          case SQLITE_INTEGER:
            sql += wxT("INTEGER");
            break;
          case SQLITE_DATE:
          case SQLITE_DATETIME:
          case SQLITE_FLOAT:
            sql += wxT("DOUBLE");
            break;
          case SQLITE_TEXT:
            sql += wxT("TEXT");
            break;
          default:
            sql += wxT("BLOB");
            break;
        };
      if (pColumn->IsPrimaryKey() == true)
        sql += wxT(" PRIMARY KEY AUTOINCREMENT");
      else if (pColumn->IsNotNull() == true)
        sql += wxT(" NOT NULL");
      if (pColumn != Table.GetLast())
        sql += wxT(",\n");
      else
        sql += wxT("\n");
      pColumn = pColumn->GetNext();
    }
  sql += wxT(")");
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(sqlite, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
// adding the Geometry column
  sql = wxT("SELECT AddGeometryColumn('");
  sql += TableName;
  sql += wxT("', '");
  sql += GeometryColumn;
  sql += wxT("', ");
  sprintf(dummy, "%d", Srid);
  sql += wxString::FromUTF8(dummy);
  sql += wxT(", '");
  sql += GeometryType;
  sql += wxT("', 2)");
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(sqlite, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
// inserting into layer_table_layout
  sql = wxT("INSERT INTO layer_table_layout ");
  sql += wxT("(table_name, geometry_column, column_name, desc_name, ");
  sql += wxT("data_type, length, decimals) VALUES ");
  sql += wxT("(?, ?, ?, ?, ?, ?, ?)");
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
  pColumn = Table.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsDeleted() == true)
        {
          pColumn = pColumn->GetNext();
          continue;
        }
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      MainFrame->ConvertString(TableName, tblName, &len);
      sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
      MainFrame->ConvertString(GeometryColumn, geomCol, &len);
      sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
      MainFrame->ConvertString(pColumn->GetColumn(), colName, &len);
      sqlite3_bind_text(stmt, 3, colName, len, SQLITE_STATIC);
      MainFrame->ConvertString(pColumn->GetDescName(), descName, &len);
      if (len == 0)
        sqlite3_bind_null(stmt, 4);
      else
        sqlite3_bind_text(stmt, 4, descName, len, SQLITE_STATIC);
      MainFrame->ConvertString(pColumn->GetColumnTypeAsConstant(), type, &len);
      sqlite3_bind_text(stmt, 5, type, len, SQLITE_STATIC);
      if (pColumn->GetType() != SQLITE_TEXT)
        sqlite3_bind_null(stmt, 6);
      else
        sqlite3_bind_int(stmt, 6, pColumn->GetLength());
      if (pColumn->GetType() != SQLITE_FLOAT)
        sqlite3_bind_null(stmt, 7);
      else
        sqlite3_bind_int(stmt, 7, pColumn->GetDecimals());
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
      pColumn = pColumn->GetNext();
    }
  sqlite3_finalize(stmt);
// inserting into layer_params
  if (GeometryType == wxT("POINT") || GeometryType == wxT("MULTIPOINT"))
    geomType = LAYER_POINT;
  if (GeometryType == wxT("LINESTRING")
      || GeometryType == wxT("MULTILINESTRING"))
    geomType = LAYER_LINESTRING;
  if (GeometryType == wxT("POLYGON") || GeometryType == wxT("MULTIPOLYGON"))
    geomType = LAYER_POLYGON;
  if (GeometryType == wxT("MULTIPOINT")
      || GeometryType == wxT("MULTILINESTRING")
      || GeometryType == wxT("MULTIPOLYGON"))
    multiType = true;
  layer.Set(TableName, GeometryColumn, Srid, geomType, multiType, DescName);
  if (geomType == LAYER_POINT)
    {
      MainFrame->GetRandomColor(&red, &green, &blue);
      wxColour col1(red, green, blue);
      MainFrame->GetRandomColor(&red, &green, &blue);
      wxColour col2(red, green, blue);
      layer.SetPointGraphics(1, col1, col2);
    }
  if (geomType == LAYER_LINESTRING)
    {
      MainFrame->GetRandomColor(&red, &green, &blue);
      wxColour color(red, green, blue);
      layer.SetLineGraphics(color, 1, wxSOLID);
    }
  if (geomType == LAYER_POLYGON)
    {
      MainFrame->GetRandomColor(&red, &green, &blue);
      wxColour col1(red, green, blue);
      MainFrame->GetRandomColor(&red, &green, &blue);
      wxColour col2(red, green, blue);
      layer.SetPolygonGraphics(col1, 1, wxSOLID, col2);
    }
  layer.PrepareStaticValues();
  MainFrame->InsertLayerParams(&layer);
//
// committing the transaction
//
  ret = sqlite3_exec(sqlite, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  ::wxEndBusyCursor();
  MainFrame->InitLayerTree();
  return true;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(sqlite, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
  return false;
}

bool TableLayoutDialog::Create(MyFrame * parent, wxString & table,
                               wxString & geomColumn)
{
//
// creating the dialog
//
  MainFrame = parent;
  TableName = table;
  GeometryColumn = geomColumn;
  CurrentColumn = NULL;
  if (wxDialog::Create(parent, wxID_ANY, wxT("DB Spatial Table Layout")) ==
      false)
    return false;
  LoadDefs();
// populates individual controls
  CreateControls();
// sets dialog sizer
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
// centers the dialog window
  Centre();
  return true;
}

void TableLayoutDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[256];
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
// first row: the Table name
  wxBoxSizer *tableBoxSizer = new wxBoxSizer(wxVERTICAL);
  boxSizer->Add(tableBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *tableBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Vector Layer - DB Table"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *tableSizer = new wxStaticBoxSizer(tableBox, wxVERTICAL);
  tableBoxSizer->Add(tableSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxBoxSizer *tblSizer = new wxBoxSizer(wxHORIZONTAL);
  tableSizer->Add(tblSizer, 0, wxALIGN_RIGHT | wxALL, 2);
  wxStaticText *tableLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Table Name:"));
  tblSizer->Add(tableLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  wxTextCtrl *tableCtrl = new wxTextCtrl(this, wxID_ANY,
                                         TableName, wxDefaultPosition,
                                         wxSize(350, 22), wxTE_READONLY);
  tblSizer->Add(tableCtrl, 0, wxALIGN_RIGHT | wxALL, 2);
// second row: description
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  tableSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  DescCtrl =
    new wxTextCtrl(this, ID_TABLE_LAYOUT_DESC, DescName, wxDefaultPosition,
                   wxSize(350, 22));
  descSizer->Add(DescCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
// third row: the Geometry name
  wxBoxSizer *geomBoxSizer = new wxBoxSizer(wxVERTICAL);
  boxSizer->Add(geomBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *geomBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Geometry Column"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *geomSizer = new wxStaticBoxSizer(geomBox, wxVERTICAL);
  geomBoxSizer->Add(geomSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxBoxSizer *geoSizer = new wxBoxSizer(wxHORIZONTAL);
  geomSizer->Add(geoSizer, 0, wxALIGN_LEFT | wxALL, 2);
  wxStaticText *geomLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column Name:"));
  geoSizer->Add(geomLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *geomCtrl = new wxTextCtrl(this, wxID_ANY,
                                        GeometryColumn, wxDefaultPosition,
                                        wxSize(150, 22), wxTE_READONLY);
  geoSizer->Add(geomCtrl, 0, wxALIGN_LEFT | wxALL, 2);
  wxStaticText *geomTypeLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Type:"));
  geoSizer->Add(geomTypeLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *geomTypeCtrl = new wxTextCtrl(this, wxID_ANY,
                                            GeometryType, wxDefaultPosition,
                                            wxSize(100, 22), wxTE_READONLY);
  geoSizer->Add(geomTypeCtrl, 0, wxALIGN_LEFT | wxALL, 2);
  wxBoxSizer *sridSizer = new wxBoxSizer(wxHORIZONTAL);
  geomSizer->Add(sridSizer, 0, wxALIGN_RIGHT | wxALL, 2);
  wxStaticText *sridLayerLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&SRID:"));
  sridSizer->Add(sridLayerLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%d   [", Info.GetSrid());
  wxString srid = wxString::FromUTF8(dummy) + Info.GetAuthName();
  sprintf(dummy, " %d] ", Info.GetAuthSrid());
  srid += wxString::FromUTF8(dummy);
  srid += Info.GetSridName();
  wxTextCtrl *sridLayerCtrl = new wxTextCtrl(this, wxID_ANY, srid,
                                             wxDefaultPosition, wxSize(350, 22),
                                             wxTE_READONLY);
  sridSizer->Add(sridLayerCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// sixth row: Column List
  wxStaticBox *columnsBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Columns"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *columnsSizer = new wxStaticBoxSizer(columnsBox, wxHORIZONTAL);
  boxSizer->Add(columnsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  int count = Table.GetCount();
  wxString *columns = new wxString[count];
  int i = 0;
  TableColumn *pColumn = Table.GetFirst();
  while (pColumn)
    {
      columns[i] = pColumn->GetColumnDefs();
      i++;
      pColumn = pColumn->GetNext();
    }
  ListCtrl = new wxListBox(this, ID_TABLE_LAYOUT_LIST,
                           wxDefaultPosition, wxSize(400, 100),
                           count, columns, wxLB_SINGLE | wxLB_HSCROLL);
  ListCtrl->SetFont(wxFont
                    (8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL,
                     wxFONTWEIGHT_NORMAL));
  ListCtrl->SetSelection(0);
  columnsSizer->Add(ListCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  CurrentColumn = Table.Find(ListCtrl->GetSelection());
// eigth row: Column Name
  wxBoxSizer *columnBoxSizer = new wxBoxSizer(wxVERTICAL);
  boxSizer->Add(columnBoxSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticBox *columnBox = new wxStaticBox(this, wxID_STATIC,
                                           wxT("Column details"),
                                           wxDefaultPosition,
                                           wxDefaultSize);
  wxBoxSizer *columnSizer = new wxStaticBoxSizer(columnBox, wxVERTICAL);
  columnBoxSizer->Add(columnSizer, 0, wxALIGN_LEFT | wxALL, 2);
  wxBoxSizer *nameSizer = new wxBoxSizer(wxHORIZONTAL);
  columnSizer->Add(nameSizer, 0, wxALIGN_LEFT | wxALL, 2);
  wxStaticText *nameLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Column Name:"));
  nameSizer->Add(nameLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  ColNameCtrl = new wxTextCtrl(this, ID_TABLE_LAYOUT_COLUMN,
                               wxT(""), wxDefaultPosition, wxSize(150, 22));
  nameSizer->Add(ColNameCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  wxString isnull[2];
  isnull[0] = wxT("yes");
  isnull[1] = wxT("&no");
  ColNullCtrl = new wxRadioBox(this, ID_TABLE_LAYOUT_COL_NULL,
                               wxT("&NULL values"),
                               wxDefaultPosition, wxDefaultSize, 2, isnull, 2,
                               wxRA_SPECIFY_COLS);
  ColNullCtrl->SetSelection(0);
  ColNullCtrl->Enable(false);
  nameSizer->Add(ColNullCtrl, 0, wxALIGN_RIGHT | wxALL, 2);
// ninethd row: column description
  wxBoxSizer *colDescSizer = new wxBoxSizer(wxHORIZONTAL);
  columnSizer->Add(colDescSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *colDescLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  colDescSizer->Add(colDescLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  ColDescCtrl =
    new wxTextCtrl(this, ID_TABLE_LAYOUT_COL_DESC, wxT(""), wxDefaultPosition,
                   wxSize(350, 22));
  colDescSizer->Add(ColDescCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
// tenth row: Column Type
  wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
  columnSizer->Add(mainSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxBoxSizer *leftSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(leftSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(rightSizer, 0, wxALIGN_BOTTOM | wxALL, 0);
  wxBoxSizer *colTypeSizer = new wxBoxSizer(wxHORIZONTAL);
  leftSizer->Add(colTypeSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxString coltypes[8];
  coltypes[0] = wxT("&INTEGER");
  coltypes[1] = wxT("&FLOAT");
  coltypes[2] = wxT("&TEXT");
  coltypes[3] = wxT("&BOOLEAN");
  coltypes[4] = wxT("&DATE");
  coltypes[5] = wxT("&DATETIME");
  coltypes[6] = wxT("&IMAGE");
  coltypes[7] = wxT("&BLOB");
  ColTypeCtrl = new wxRadioBox(this, ID_TABLE_LAYOUT_COL_TYPE,
                               wxT("&Data Type"),
                               wxDefaultPosition, wxDefaultSize, 8, coltypes, 4,
                               wxRA_SPECIFY_COLS);
  ColTypeCtrl->SetSelection(0);
  colTypeSizer->Add(ColTypeCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
// eleventh row: Format hints
  wxStaticBox *formatBox = new wxStaticBox(this, wxID_STATIC,
                                           wxT("Format hints"),
                                           wxDefaultPosition,
                                           wxDefaultSize);
  wxBoxSizer *formatSizer = new wxStaticBoxSizer(formatBox, wxHORIZONTAL);
  leftSizer->Add(formatSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxStaticText *lenLabel = new wxStaticText(this, wxID_STATIC, wxT("&Length:"));
  formatSizer->Add(lenLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  ColLenCtrl = new wxSpinCtrl(this, ID_TABLE_LAYOUT_COL_LEN, wxT(""),
                              wxDefaultPosition, wxSize(80, 20),
                              wxSP_ARROW_KEYS, 1, 255, 1);
  ColLenCtrl->Enable(false);
  formatSizer->Add(ColLenCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  wxStaticText *decLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Decimal digits:"));
  formatSizer->Add(decLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  ColDecCtrl = new wxSpinCtrl(this, ID_TABLE_LAYOUT_COL_DEC, wxT(""),
                              wxDefaultPosition, wxSize(80, 20),
                              wxSP_ARROW_KEYS, 1, 18, 1);
  ColDecCtrl->Enable(false);
  formatSizer->Add(ColDecCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  ClearBtn = new wxButton(this, ID_TABLE_LAYOUT_COL_CLEAR, wxT("New Column"));
  rightSizer->Add(ClearBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  AddBtn = new wxButton(this, ID_TABLE_LAYOUT_COL_ADD, wxT("Save Changes"));
  rightSizer->Add(AddBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  DeleteBtn =
    new wxButton(this, ID_TABLE_LAYOUT_COL_DELETE, wxT("Delete Column"));
  rightSizer->Add(DeleteBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  pColumn = Table.Find(0);
  ColNameCtrl->SetValue(pColumn->GetColumn());
  ColDescCtrl->SetValue(pColumn->GetDescName());
// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&Update Table Layout"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableLayoutDialog::OnOk);
  Connect(ID_TABLE_LAYOUT_COL_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableLayoutDialog::OnClear);
  Connect(ID_TABLE_LAYOUT_COL_ADD, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableLayoutDialog::OnAdd);
  Connect(ID_TABLE_LAYOUT_COL_DELETE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableLayoutDialog::OnDelete);
  Connect(ID_TABLE_LAYOUT_LIST, wxEVT_COMMAND_LISTBOX_SELECTED,
          (wxObjectEventFunction) & TableLayoutDialog::OnColumnSelected);
  Connect(ID_TABLE_LAYOUT_COL_TYPE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & TableLayoutDialog::OnTypeSelected);
}

void TableLayoutDialog::LoadDefs()
{
// loading the Table Defs
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  int srid = -1;
  int len;
  char xSql[1024];
  char tblName[1024];
  char geomCol[1024];
  char colName[1024];
  char type[64];
  GeometryType = wxT("UNKNOWN");
  GeometryType = wxT("Anonymous");
  ::wxBeginBusyCursor();
// retrieving the Geometry Column defs
  sql = wxT("SELECT type, srid ");
  sql += wxT("FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += TableName;
  sql += wxT("' AND f_geometry_column = '");
  sql += GeometryColumn;
  sql += wxT("'");
  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto srid;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          value = results[(i * columns) + 0];
          GeometryType = wxString::FromUTF8(value);
          value = results[(i * columns) + 1];
          srid = atoi(value);
        }
    }
  sqlite3_free_table(results);
srid:
  Info = SridInfo(srid);
  MainFrame->GetSridInfo(&Info);
// retrieving the DescName def
  sql = wxT("SELECT desc_name ");
  sql += wxT("FROM layer_params ");
  sql += wxT("WHERE raster_layer = 0 AND table_name = '");
  sql += TableName;
  sql += wxT("' AND geometry_column = '");
  sql += GeometryColumn;
  sql += wxT("'");
  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto columns;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          value = results[(i * columns) + 0];
          DescName = wxString::FromUTF8(value);
        }
    }
  sqlite3_free_table(results);
columns:
// retrieving the Column defs
  sql = wxT("SELECT column_name, desc_name, data_type, length, decimals ");
  sql += wxT("FROM layer_table_layout ");
  sql += wxT("WHERE table_name = '");
  sql += TableName;
  sql += wxT("' AND geometry_column = '");
  sql += GeometryColumn;
  sql += wxT("' ORDER BY ROWID");
  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto done_columns;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          wxString name = wxT("UNKNOWN");
          wxString desc = wxT("");
          int type = SQLITE_TEXT;
          int len = 0;
          int dec = 0;
          value = results[(i * columns) + 0];
          if (value)
            name = wxString::FromUTF8(value);
          value = results[(i * columns) + 1];
          if (value)
            desc = wxString::FromUTF8(value);
          value = results[(i * columns) + 2];
          if (value)
            type = MainFrame->ColumnTypeFromConstant(value);
          value = results[(i * columns) + 3];
          if (value)
            len = atoi(value);
          value = results[(i * columns) + 4];
          if (value)
            dec = atoi(value);
          Table.AddExisting(name, desc, type, false, false, len, dec);
        }
    }
  sqlite3_free_table(results);
done_columns:
// retrieving the PRAGMA table_info
  sql = wxT("PRAGMA table_info(\"");
  sql += TableName;
  sql += wxT("\")");
  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto end_columns;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          wxString name = wxT("UNKNOWN");
          bool notNull = false;
          bool pk = false;
          value = results[(i * columns) + 1];
          if (value)
            name = wxString::FromUTF8(value);
          value = results[(i * columns) + 3];
          if (value)
            {
              if (atoi(value) == 0)
                notNull = false;
              else
                notNull = true;
            }
          value = results[(i * columns) + 5];
          if (value)
            {
              if (atoi(value) == 0)
                pk = false;
              else
                pk = true;
            }
          if (name != GeometryColumn)
            Table.Add(name, notNull, pk);
        }
    }
  sqlite3_free_table(results);
end_columns:
  bool toInsert = false;
  bool toDelete = false;
  TableColumn *pColumn = Table.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsToBeInserted() == true)
        toInsert = true;
      if (pColumn->IsToBeDeleted() == true)
        toDelete = true;
      pColumn = pColumn->GetNext();
    }
  if (toInsert == true || toDelete == true)
    {
      //
      // starting a transaction
      //
      ret = sqlite3_exec(sqlite, "BEGIN", NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
    }
  if (toDelete == true)
    {
      // trying to delete unused column defs
      sql = wxT("DELETE FROM layer_table_layout ");
      sql +=
        wxT
        ("(WHERE table_name = ? AND geometry_column = ? AND column_name = ?");
      MainFrame->ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto rollback;
        }
      pColumn = Table.GetFirst();
      while (pColumn)
        {
          if (pColumn->IsToBeDeleted() == false)
            {
              pColumn = pColumn->GetNext();
              continue;
            }
          sqlite3_reset(stmt);
          sqlite3_clear_bindings(stmt);
          MainFrame->ConvertString(TableName, tblName, &len);
          sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
          MainFrame->ConvertString(GeometryColumn, geomCol, &len);
          sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
          MainFrame->ConvertString(pColumn->GetColumn(), colName, &len);
          sqlite3_bind_text(stmt, 3, colName, len, SQLITE_STATIC);
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
          pColumn = pColumn->GetNext();
        }
      sqlite3_finalize(stmt);
    }
  if (toInsert == true)
    {
      // trying to guess missing column types
      sql = wxT("SELECT ");
      pColumn = Table.GetFirst();
      while (pColumn)
        {
          if (pColumn->IsToBeInserted() == true)
            {
              sql += wxT("TypeOf(\"");
              sql += pColumn->GetColumn();
              sql += wxT("\"), ");
            }
          pColumn = pColumn->GetNext();
        }
      sql += wxT("Count(*) FROM \"");
      sql += TableName;
      sql += wxT("\"");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          goto rollback;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              int count = 0;
              value = results[(i * columns) + (columns - 1)];
              if (value)
                count = atoi(value);
              int col = 0;
              pColumn = Table.GetFirst();
              while (pColumn)
                {
                  if (pColumn->IsToBeInserted() == true)
                    {
                      value = results[(i * columns) + col];
                      pColumn->AddTypeCount(value, count);
                      col++;
                    }
                  pColumn = pColumn->GetNext();
                }
            }
        }
      sqlite3_free_table(results);
      // inserting into layer_table_layout
      sql = wxT("INSERT INTO layer_table_layout ");
      sql += wxT("(table_name, geometry_column, column_name, desc_name, ");
      sql += wxT("data_type, length, decimals) VALUES ");
      sql += wxT("(?, ?, ?, ?, ?, ?, ?)");
      MainFrame->ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto rollback;
        }
      pColumn = Table.GetFirst();
      while (pColumn)
        {
          if (pColumn->IsToBeInserted() == false)
            {
              pColumn = pColumn->GetNext();
              continue;
            }
          sqlite3_reset(stmt);
          sqlite3_clear_bindings(stmt);
          MainFrame->ConvertString(TableName, tblName, &len);
          sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
          MainFrame->ConvertString(GeometryColumn, geomCol, &len);
          sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
          MainFrame->ConvertString(pColumn->GetColumn(), colName, &len);
          sqlite3_bind_text(stmt, 3, colName, len, SQLITE_STATIC);
          sqlite3_bind_null(stmt, 4);
          pColumn->GuessType();
          MainFrame->ConvertString(pColumn->GetColumnTypeAsConstant(), type,
                                   &len);
          sqlite3_bind_text(stmt, 5, type, len, SQLITE_STATIC);
          if (pColumn->GetType() != SQLITE_TEXT)
            sqlite3_bind_null(stmt, 6);
          else
            sqlite3_bind_int(stmt, 6, pColumn->GetLength());
          if (pColumn->GetType() != SQLITE_FLOAT)
            sqlite3_bind_null(stmt, 7);
          else
            sqlite3_bind_int(stmt, 7, pColumn->GetDecimals());
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
          pColumn = pColumn->GetNext();
        }
      sqlite3_finalize(stmt);
    }
  if (toInsert == true || toDelete == true)
    {
      //
      // committing the transaction
      //
      ret = sqlite3_exec(sqlite, "COMMIT", NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      pColumn = Table.GetFirst();
      while (pColumn)
        {
          // resetting any toInsert / toUpdate / toDelete switch
          pColumn->Reset();
          pColumn = pColumn->GetNext();
        }
    }
  ::wxEndBusyCursor();
  return;

rollback:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(sqlite, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
}

void TableLayoutDialog::OnClear(wxCommandEvent & WXUNUSED(event))
{
//
// prepating to insert a new column
//
  CurrentColumn = NULL;
  ListCtrl->SetSelection(wxNOT_FOUND);
  ColNameCtrl->SetValue(wxT(""));
  ColDescCtrl->SetValue(wxT(""));
  ColLenCtrl->SetValue(wxT(""));
  ColDecCtrl->SetValue(wxT(""));
  ColNullCtrl->SetSelection(0);
  ColTypeCtrl->SetSelection(0);
  ColDecCtrl->Enable(false);
  ColLenCtrl->Enable(false);
  ClearBtn->Enable(false);
  DeleteBtn->Enable(false);
  ColNullCtrl->Enable(true);
  AddBtn->SetLabel(wxT("Add Column"));
}

void TableLayoutDialog::OnAdd(wxCommandEvent & WXUNUSED(event))
{
//
// adding a new column  def[or replacing an existing one]
//
  wxString name = ColNameCtrl->GetValue();
  if (CurrentColumn)
    {
      if (CurrentColumn->IsExisting() == true
          && name != CurrentColumn->GetColumn())
        {
          wxString msg =
            wxT
            ("You cannot alter the name for an already existing Column !!!\n\n");
          msg += wxT("Such an operation is not supported by SQLite");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
          ColNameCtrl->SetValue(CurrentColumn->GetColumn());
          return;
        }
    }
  if (name.Len() == 0)
    {
      wxString msg = wxT("You must specify some COLUMN NAME !!!");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  bool duplicate;
  if (CurrentColumn)
    duplicate = Table.IsDuplicate(CurrentColumn, name);
  else
    duplicate = Table.IsDuplicate(name);
  if (duplicate == true)
    {
      wxString msg = wxT("Duplicate Column Name: '");
      msg += name;
      msg += wxT("'");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  wxString desc = ColDescCtrl->GetValue();
  int type = SQLITE_INTEGER;
  switch (ColTypeCtrl->GetSelection())
    {
      case 1:
        type = SQLITE_FLOAT;
        break;
      case 2:
        type = SQLITE_TEXT;
        break;
      case 3:
        type = SQLITE_BOOLEAN;
        break;
      case 4:
        type = SQLITE_DATE;
        break;
      case 5:
        type = SQLITE_DATETIME;
        break;
      case 6:
        type = SQLITE_IMAGE;
        break;
      case 7:
        type = SQLITE_BLOB;
        break;
    };
  if (CurrentColumn)
    {
      if (CurrentColumn->IsExisting() == true
          && type != CurrentColumn->GetType())
        {
          bool dontCare = false;
          switch (CurrentColumn->GetType())
            {
              case SQLITE_FLOAT:
              case SQLITE_DATE:
              case SQLITE_DATETIME:
                if (type == SQLITE_DATE || type == SQLITE_DATE
                    || type == SQLITE_DATETIME)
                  dontCare = true;
                break;
              case SQLITE_BLOB:
                if (type == SQLITE_IMAGE)
                  dontCare = true;
                break;
              case SQLITE_IMAGE:
                if (type == SQLITE_BLOB)
                  dontCare = true;
                break;
            };
          if (dontCare == false)
            {
              wxString msg =
                wxT
                ("Altering the preferred DATA TYPE for an already existing Column\n");
              msg += wxT("may be a very bad idea ...\n\n");
              msg += wxT("Do you really really want to confirm this ?");
              int ret = wxMessageBox(msg, wxT("spatialite-gis"),
                                     wxYES_NO | wxICON_QUESTION, this);
              if (ret != wxYES)
                {
                  switch (CurrentColumn->GetType())
                    {
                      case SQLITE_INTEGER:
                        ColTypeCtrl->SetSelection(0);
                        break;
                      case SQLITE_FLOAT:
                        ColTypeCtrl->SetSelection(1);
                        break;
                      case SQLITE_TEXT:
                        ColTypeCtrl->SetSelection(2);
                        break;
                      case SQLITE_BOOLEAN:
                        ColTypeCtrl->SetSelection(3);
                        break;
                      case SQLITE_DATE:
                        ColTypeCtrl->SetSelection(4);
                        break;
                      case SQLITE_DATETIME:
                        ColTypeCtrl->SetSelection(5);
                        break;
                      case SQLITE_IMAGE:
                        ColTypeCtrl->SetSelection(6);
                        break;
                      case SQLITE_BLOB:
                        ColTypeCtrl->SetSelection(7);
                        break;
                    };
                  return;
                }
            }
        }
    }
  bool notNull = false;
  if (ColNullCtrl->GetSelection() == 1)
    notNull = true;
  if (CurrentColumn)
    {
      if (CurrentColumn->IsExisting() == true
          && notNull != CurrentColumn->IsNotNull())
        {
          wxString msg =
            wxT
            ("You cannot alter the NOT NULL clause for an already existing Column !!!\n\n");
          msg += wxT("Such an operation is not supported by SQLite");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
          if (CurrentColumn->IsNotNull() == false)
            ColNullCtrl->SetSelection(0);
          else
            ColNullCtrl->SetSelection(1);
          return;
        }
    }
  if (type == SQLITE_FLOAT)
    {
      int decs = ColDecCtrl->GetValue();
      if (CurrentColumn)
        CurrentColumn->Set(name, desc, type, false, notNull, 0, decs);
      else
        Table.Add(name, desc, type, false, notNull, 0, decs);
  } else if (type == SQLITE_TEXT)
    {
      int len = ColLenCtrl->GetValue();
      if (CurrentColumn)
        CurrentColumn->Set(name, desc, type, false, notNull, len, 0);
      else
        Table.Add(name, desc, type, false, notNull, len, 0);
  } else
    {
      if (CurrentColumn)
        CurrentColumn->Set(name, desc, type, false, notNull, 0, 0);
      else
        Table.Add(name, desc, type, false, notNull, 0, 0);
    }
  if (CurrentColumn)
    CurrentColumn->SetUpdate();
// updating the Columns List
  ListCtrl->Clear();
  TableColumn *pColumn = Table.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsDeleted() == false)
        ListCtrl->Append(pColumn->GetColumnDefs());
      pColumn = pColumn->GetNext();
    }
  int pos = Table.Find(name);
  if (pos < 4)
    pos = 4;
  ListCtrl->SetFirstItem(pos - 4);
// resetting the fields
  CurrentColumn = NULL;
  ListCtrl->SetSelection(wxNOT_FOUND);
  ColNameCtrl->SetValue(wxT(""));
  ColDescCtrl->SetValue(wxT(""));
  ColLenCtrl->SetValue(wxT(""));
  ColDecCtrl->SetValue(wxT(""));
  ColNullCtrl->SetSelection(0);
  ColTypeCtrl->SetSelection(0);
  ColDecCtrl->Enable(false);
  ColLenCtrl->Enable(false);
  ClearBtn->Enable(false);
  DeleteBtn->Enable(false);
  AddBtn->SetLabel(wxT("Add Column"));
}

void TableLayoutDialog::OnDelete(wxCommandEvent & WXUNUSED(event))
{
//
// deleting some column
//
  if (!CurrentColumn)
    return;
  if (CurrentColumn->IsExisting() == true)
    {
      wxString msg =
        wxT("You cannot delete an already existing Column !!!\n\n");
      msg += wxT("Such an operation is not supported by SQLite");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
      return;
    }
  CurrentColumn->Delete();
// updating the Columns List
  ListCtrl->Clear();
  TableColumn *pColumn = Table.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsDeleted() == false)
        ListCtrl->Append(pColumn->GetColumnDefs());
      pColumn = pColumn->GetNext();
    }
// resetting the fields
  CurrentColumn = NULL;
  ListCtrl->SetSelection(wxNOT_FOUND);
  ColNameCtrl->SetValue(wxT(""));
  ColDescCtrl->SetValue(wxT(""));
  ColLenCtrl->SetValue(wxT(""));
  ColDecCtrl->SetValue(wxT(""));
  ColNullCtrl->SetSelection(0);
  ColTypeCtrl->SetSelection(0);
  ColDecCtrl->Enable(false);
  ColLenCtrl->Enable(false);
  ClearBtn->Enable(false);
  DeleteBtn->Enable(false);
  AddBtn->SetLabel(wxT("Add Column"));
}

void TableLayoutDialog::OnTypeSelected(wxCommandEvent & WXUNUSED(event))
{
//
// some Data Type has just been selected
//
  if (ColTypeCtrl->GetSelection() == 1)
    ColDecCtrl->Enable(true);
  else
    ColDecCtrl->Enable(false);
  if (ColTypeCtrl->GetSelection() == 2)
    ColLenCtrl->Enable(true);
  else
    ColLenCtrl->Enable(false);
}

void TableLayoutDialog::OnColumnSelected(wxCommandEvent & WXUNUSED(event))
{
//
// some Column Def has just been selected
//
  TableColumn *pColumn = Table.Find(ListCtrl->GetSelection());
  if (pColumn == NULL)
    {
      // clearing the Column Def fields
      CurrentColumn = NULL;
      ListCtrl->SetSelection(wxNOT_FOUND);
      ColNameCtrl->SetValue(wxT(""));
      ColDescCtrl->SetValue(wxT(""));
      ColLenCtrl->SetValue(wxT(""));
      ColDecCtrl->SetValue(wxT(""));
      ColNullCtrl->SetSelection(0);
      ColTypeCtrl->SetSelection(0);
      ColDecCtrl->Enable(false);
      ColLenCtrl->Enable(false);
      ClearBtn->Enable(false);
      DeleteBtn->Enable(false);
      AddBtn->SetLabel(wxT("Add Column"));
  } else
    {
      // updating the Column Defs fields
      ColNameCtrl->SetValue(pColumn->GetColumn());
      ColDescCtrl->SetValue(pColumn->GetDescName());
      ColLenCtrl->SetValue(pColumn->GetLength());
      ColDecCtrl->SetValue(pColumn->GetDecimals());
      if (pColumn->IsNotNull() == true)
        ColNullCtrl->SetSelection(1);
      else
        ColNullCtrl->SetSelection(0);
      switch (pColumn->GetType())
        {
          case SQLITE_INTEGER:
            ColTypeCtrl->SetSelection(0);
            break;
          case SQLITE_FLOAT:
            ColTypeCtrl->SetSelection(1);
            break;
          case SQLITE_TEXT:
            ColTypeCtrl->SetSelection(2);
            break;
          case SQLITE_BOOLEAN:
            ColTypeCtrl->SetSelection(3);
            break;
          case SQLITE_DATE:
            ColTypeCtrl->SetSelection(4);
            break;
          case SQLITE_DATETIME:
            ColTypeCtrl->SetSelection(5);
            break;
          case SQLITE_IMAGE:
            ColTypeCtrl->SetSelection(6);
            break;
          case SQLITE_BLOB:
            ColTypeCtrl->SetSelection(7);
            break;
        };
      switch (pColumn->GetType())
        {
          case SQLITE_FLOAT:
            ColLenCtrl->SetValue(wxT(""));
            ColLenCtrl->Enable(false);
            ColDecCtrl->SetValue(pColumn->GetDecimals());
            ColDecCtrl->Enable(true);
            break;
          case SQLITE_TEXT:
            ColLenCtrl->SetValue(pColumn->GetLength());
            ColLenCtrl->Enable(true);
            ColDecCtrl->SetValue(wxT(""));
            ColDecCtrl->Enable(false);
            break;
          case SQLITE_INTEGER:
          case SQLITE_DATE:
          case SQLITE_DATETIME:
          case SQLITE_BOOLEAN:
          case SQLITE_IMAGE:
          case SQLITE_BLOB:
            ColLenCtrl->SetValue(wxT(""));
            ColDecCtrl->SetValue(wxT(""));
            ColDecCtrl->Enable(false);
            ColLenCtrl->Enable(false);
            break;
        };
      ClearBtn->Enable(true);
      AddBtn->SetLabel(wxT("Save Changes"));
      DeleteBtn->Enable(true);
      CurrentColumn = pColumn;
      if (pColumn->IsExisting() == true)
        ColNullCtrl->Enable(false);
      else
        ColNullCtrl->Enable(true);
    }
}

void TableLayoutDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  ModDescName = DescCtrl->GetValue();
  if (DoUpdateTable() == false)
    return;
  wxDialog::EndModal(wxID_OK);
}

bool TableLayoutDialog::DoUpdateTable()
{
//
// trying to update the table layout 
//
  wxString sql;
  int ret;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char tblName[1024];
  char geomCol[1024];
  char colName[1024];
  char descName[1024];
  char type[64];
  char *errMsg = NULL;
  bool toInsert = false;
  bool toUpdate = false;
  TableColumn *pColumn = Table.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsExisting() == false && pColumn->IsDeleted() == false)
        toInsert = true;
      if (pColumn->IsToBeUpdated() == true)
        toUpdate = true;
      pColumn = pColumn->GetNext();
    }

  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(sqlite, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  if (toInsert == true)
    {
      // there is some new Column to be added
      pColumn = Table.GetFirst();
      while (pColumn)
        {
          if (pColumn->IsExisting() == false && pColumn->IsDeleted() == false)
            ;
          else
            {
              pColumn = pColumn->GetNext();
              continue;
            }
          // performing an ALTER TABLE ADD COLUMN ...
          sql = wxT("ALTER TABLE \"");
          sql += TableName;
          sql += wxT("\" ADD COLUMN \"");
          sql += pColumn->GetColumn();
          sql += wxT("\" ");
          switch (pColumn->GetType())
            {
              case SQLITE_INTEGER:
                sql += wxT("INTEGER");
                break;
              case SQLITE_DATE:
              case SQLITE_DATETIME:
              case SQLITE_FLOAT:
                sql += wxT("DOUBLE");
                break;
              case SQLITE_TEXT:
                sql += wxT("TEXT");
                break;
              default:
                sql += wxT("BLOB");
                break;
            };
          MainFrame->ConvertString(sql, xSql, &len);
          ret = sqlite3_exec(sqlite, xSql, NULL, 0, &errMsg);
          if (ret != SQLITE_OK)
            {
              wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                           wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
              sqlite3_free(errMsg);
              goto stop;
            }
          pColumn = pColumn->GetNext();
        }
      // inserting into layer_table_layout
      sql = wxT("INSERT INTO layer_table_layout ");
      sql += wxT("(table_name, geometry_column, column_name, desc_name, ");
      sql += wxT("data_type, length, decimals) VALUES ");
      sql += wxT("(?, ?, ?, ?, ?, ?, ?)");
      MainFrame->ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto stop;
        }
      pColumn = Table.GetFirst();
      while (pColumn)
        {
          if (pColumn->IsExisting() == false && pColumn->IsDeleted() == false)
            ;
          else
            {
              pColumn = pColumn->GetNext();
              continue;
            }
          sqlite3_reset(stmt);
          sqlite3_clear_bindings(stmt);
          MainFrame->ConvertString(TableName, tblName, &len);
          sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
          MainFrame->ConvertString(GeometryColumn, geomCol, &len);
          sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
          MainFrame->ConvertString(pColumn->GetColumn(), colName, &len);
          sqlite3_bind_text(stmt, 3, colName, len, SQLITE_STATIC);
          MainFrame->ConvertString(pColumn->GetDescName(), descName, &len);
          if (len == 0)
            sqlite3_bind_null(stmt, 4);
          else
            sqlite3_bind_text(stmt, 4, descName, len, SQLITE_STATIC);
          MainFrame->ConvertString(pColumn->GetColumnTypeAsConstant(), type,
                                   &len);
          sqlite3_bind_text(stmt, 5, type, len, SQLITE_STATIC);
          if (pColumn->GetType() != SQLITE_TEXT)
            sqlite3_bind_null(stmt, 6);
          else
            sqlite3_bind_int(stmt, 6, pColumn->GetLength());
          if (pColumn->GetType() != SQLITE_FLOAT)
            sqlite3_bind_null(stmt, 7);
          else
            sqlite3_bind_int(stmt, 7, pColumn->GetDecimals());
          ret = sqlite3_step(stmt);
          if (ret == SQLITE_DONE || ret == SQLITE_ROW)
            ;
          else
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              sqlite3_finalize(stmt);
              goto stop;
            }
          pColumn = pColumn->GetNext();
        }
      sqlite3_finalize(stmt);
    }
  if (toUpdate == true)
    {
      // updating changed Column Defs
      sql = wxT("UPDATE layer_table_layout SET ");
      sql += wxT("desc_name = ?, data_type = ?, length = ?, decimals = ?");
      sql +=
        wxT
        (" WHERE table_name = ? AND geometry_column = ? AND column_name = ?");
      MainFrame->ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto stop;
        }
      pColumn = Table.GetFirst();
      while (pColumn)
        {
          if (pColumn->IsToBeUpdated() == true)
            ;
          else
            {
              pColumn = pColumn->GetNext();
              continue;
            }
          sqlite3_reset(stmt);
          sqlite3_clear_bindings(stmt);
          MainFrame->ConvertString(pColumn->GetDescName(), descName, &len);
          if (len == 0)
            sqlite3_bind_null(stmt, 1);
          else
            sqlite3_bind_text(stmt, 1, descName, len, SQLITE_STATIC);
          MainFrame->ConvertString(pColumn->GetColumnTypeAsConstant(), type,
                                   &len);
          sqlite3_bind_text(stmt, 2, type, len, SQLITE_STATIC);
          if (pColumn->GetType() != SQLITE_TEXT)
            sqlite3_bind_null(stmt, 3);
          else
            sqlite3_bind_int(stmt, 3, pColumn->GetLength());
          if (pColumn->GetType() != SQLITE_FLOAT)
            sqlite3_bind_null(stmt, 4);
          else
            sqlite3_bind_int(stmt, 4, pColumn->GetDecimals());
          MainFrame->ConvertString(TableName, tblName, &len);
          sqlite3_bind_text(stmt, 5, tblName, len, SQLITE_STATIC);
          MainFrame->ConvertString(GeometryColumn, geomCol, &len);
          sqlite3_bind_text(stmt, 6, geomCol, len, SQLITE_STATIC);
          MainFrame->ConvertString(pColumn->GetColumn(), colName, &len);
          sqlite3_bind_text(stmt, 7, colName, len, SQLITE_STATIC);
          ret = sqlite3_step(stmt);
          if (ret == SQLITE_DONE || ret == SQLITE_ROW)
            ;
          else
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              sqlite3_finalize(stmt);
              goto stop;
            }
          pColumn = pColumn->GetNext();
        }
      sqlite3_finalize(stmt);
    }
  if (ModDescName != DescName)
    {
      // updating the Table's DescName
      sql = wxT("UPDATE layer_params SET desc_name = ? ");
      sql +=
        wxT
        ("WHERE raster_layer = 0 AND table_name = ? AND geometry_column = ?");
      MainFrame->ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto stop;
        }
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      MainFrame->ConvertString(ModDescName, descName, &len);
      if (len == 0)
        sqlite3_bind_null(stmt, 1);
      else
        sqlite3_bind_text(stmt, 1, descName, len, SQLITE_STATIC);
      MainFrame->ConvertString(TableName, tblName, &len);
      sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
      MainFrame->ConvertString(GeometryColumn, geomCol, &len);
      sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
//
// committing the transaction
//
  ret = sqlite3_exec(sqlite, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  ::wxEndBusyCursor();
  MainFrame->InitLayerTree();
  return true;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(sqlite, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
  return false;
}

bool AutoSaveDialog::Create(MyFrame * parent, wxString & path, int secs)
{
//
// creating the dialog
//
  MainFrame = parent;
  Path = path;
  Seconds = secs;
  if (wxDialog::Create(parent, wxID_ANY, wxT("MEMORY-DB AutoSave settings")) ==
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

void AutoSaveDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// first row: export path
  wxBoxSizer *pathSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(pathSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *pathLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Save as:"));
  pathSizer->Add(pathLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString pth = Path;
  if (pth.Len() == 0)
    pth = wxT("*** not set: AutoSave IS DISABLED ***");
  PathCtrl = new wxTextCtrl(this, ID_AUTO_SAVE_PATH, pth, wxDefaultPosition,
                            wxSize(350, 22), wxTE_READONLY);
  pathSizer->Add(PathCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// second row: CHANGE PATH button
  wxBoxSizer *changeBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(changeBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *change =
    new wxButton(this, ID_AUTO_SAVE_CHANGE_PATH, wxT("&Set the export path"));
  changeBox->Add(change, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// third row: INTERVAL
  wxBoxSizer *modeSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(modeSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString modes[6];
  modes[0] = wxT("&Disable AutoSaving");
  modes[1] = wxT("Every &30 seconds");
  modes[2] = wxT("Every &minute");
  modes[3] = wxT("Every &2 minutes");
  modes[4] = wxT("Every &5 minutes");
  modes[5] = wxT("Every &10 minutes");
  IntervalCtrl = new wxRadioBox(this, ID_AUTO_SAVE_INTERVAL,
                                wxT("&AutoSave interval"),
                                wxDefaultPosition, wxDefaultSize, 6, modes, 6,
                                wxRA_SPECIFY_ROWS);
  if (Seconds <= 0)
    IntervalCtrl->SetSelection(0);
  else if (Seconds <= 30)
    IntervalCtrl->SetSelection(1);
  else if (Seconds <= 60)
    IntervalCtrl->SetSelection(2);
  else if (Seconds <= 120)
    IntervalCtrl->SetSelection(3);
  else if (Seconds <= 300)
    IntervalCtrl->SetSelection(4);
  else
    IntervalCtrl->SetSelection(5);
  modeSizer->Add(IntervalCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// OK - CANCEL buttons
  wxBoxSizer *okCancelBox = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// appends event handler for OK button
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & AutoSaveDialog::OnOk);
  Connect(ID_AUTO_SAVE_CHANGE_PATH, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & AutoSaveDialog::OnChangePath);
  Connect(ID_AUTO_SAVE_INTERVAL, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & AutoSaveDialog::OnIntervalChanged);
}

void AutoSaveDialog::OnChangePath(wxCommandEvent & WXUNUSED(event))
{
//
//  exporting the MEMORY-DB into an external DB 
//
  int retdlg;
  wxString lastDir;
  wxFileDialog fileDialog(this, wxT("Saving the MEMORY-DB"),
                          wxT(""), wxT("db.sqlite"),
                          wxT
                          ("SQLite DB (*.sqlite)|*.sqlite|All files (*.*)|*.*"),
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition,
                          wxDefaultSize, wxT("filedlg"));
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  retdlg = fileDialog.ShowModal();
  if (retdlg == wxID_OK)
    {
      // exporting the external DB
      wxString pth = fileDialog.GetPath();
      wxString extPth = wxT("*** not set: AutoSave IS DISABLED ***");
      MainFrame->SetExternalSqlitePath(pth);
      if (MainFrame->MemoryDbSave() == true)
        {
          wxMessageBox(wxT("Ok, MEMORY-DB was succesfully saved"),
                       wxT("spatialite-gis"), wxOK | wxICON_INFORMATION, this);
          wxFileName file(fileDialog.GetPath());
          lastDir = file.GetPath();
          MainFrame->SetLastDirectory(lastDir);
          extPth = MainFrame->GetExternalSqlitePath();
          PathCtrl->SetValue(extPth);
      } else
        PathCtrl->SetValue(extPth);
    }
}

void AutoSaveDialog::OnIntervalChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Interval selection changed
//
  if (IntervalCtrl->GetSelection() == 0)
    Seconds = 0;
  else if (IntervalCtrl->GetSelection() == 1)
    Seconds = 30;
  else if (IntervalCtrl->GetSelection() == 2)
    Seconds = 60;
  else if (IntervalCtrl->GetSelection() == 3)
    Seconds = 120;
  else if (IntervalCtrl->GetSelection() == 4)
    Seconds = 300;
  else
    Seconds = 600;
}

void AutoSaveDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  wxDialog::EndModal(wxID_OK);
}

bool RoutingSolutionDialog::Create(MyMapView * map, MyFrame * parent,
                                   RoutingSolution * solution, bool hasNames,
                                   bool textNodes)
{
//
// creating the dialog
//
  MapView = map;
  MainFrame = parent;
  Solution = solution;
  HasNames = hasNames;
  TextNodes = textNodes;
  CurrentArc = NULL;
  if (wxDialog::Create(parent, wxID_ANY, wxT("Routing Solution")) == false)
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

void RoutingSolutionDialog::CreateControls()
{
//
// creating individual control and setting initial values
//
  char dummy[128];
  wxString label;
  TopSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(TopSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  TopSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  HeadSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(HeadSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
// the Route's From-To header
  wxStaticBox *hdBox = new wxStaticBox(this, wxID_STATIC,
                                       wxT("Connection"),
                                       wxDefaultPosition,
                                       wxDefaultSize);
  wxBoxSizer *hd1Sizer = new wxStaticBoxSizer(hdBox, wxVERTICAL);
  HeadSizer->Add(hd1Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *hdFromSizer = new wxBoxSizer(wxHORIZONTAL);
  hd1Sizer->Add(hdFromSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *fromLabel =
    new wxStaticText(this, wxID_STATIC, wxT("NodeFrom:"));
  hdFromSizer->Add(fromLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  if (MainFrame->GetNetwork()->IsTextNodes() == true)
    label = Solution->GetNodeFromText();
  else
    {
      sprintf(dummy, FORMAT_64, Solution->GetNodeFromId());
      label = wxString::FromUTF8(dummy);
    }
  wxTextCtrl *fromCtrl =
    new wxTextCtrl(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize,
                   wxTE_READONLY);
  hdFromSizer->Add(fromCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *hdToSizer = new wxBoxSizer(wxHORIZONTAL);
  hd1Sizer->Add(hdToSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *toLabel = new wxStaticText(this, wxID_STATIC, wxT("NodeTo:"));
  hdToSizer->Add(toLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  if (MainFrame->GetNetwork()->IsTextNodes() == true)
    label = Solution->GetNodeToText();
  else
    {
      sprintf(dummy, FORMAT_64, Solution->GetNodeToId());
      label = wxString::FromUTF8(dummy);
    }
  wxTextCtrl *toCtrl =
    new wxTextCtrl(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize,
                   wxTE_READONLY);
  hdToSizer->Add(toCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// the Route's Costs header
  wxStaticBox *hd2Box = new wxStaticBox(this, wxID_STATIC,
                                        wxT("Cost"),
                                        wxDefaultPosition,
                                        wxDefaultSize);
  wxBoxSizer *hd2Sizer = new wxStaticBoxSizer(hd2Box, wxVERTICAL);
  HeadSizer->Add(hd2Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 1);
  wxBoxSizer *hdCostSizer = new wxBoxSizer(wxHORIZONTAL);
  hd2Sizer->Add(hdCostSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *costLabel =
    new wxStaticText(this, wxID_STATIC, wxT("TotalCost:"));
  hdCostSizer->Add(costLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sprintf(dummy, "%1.6f", Solution->GetCost());
  label = wxString::FromUTF8(dummy);
  wxTextCtrl *costCtrl =
    new wxTextCtrl(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize,
                   wxTE_READONLY);
  hdCostSizer->Add(costCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *hdLengthSizer = new wxBoxSizer(wxHORIZONTAL);
  hd2Sizer->Add(hdLengthSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *lengthLabel =
    new wxStaticText(this, wxID_STATIC, wxT("RouteLength:"));
  hdLengthSizer->Add(lengthLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  double length = 0.0;
  wxString unit;
  if (MainFrame->GetProjectCrs().IsGeographic() == true)
    {
      char ellps[128];
      int len;
      double a;
      double b;
      double rf;
      gaiaLinestringPtr ln = Solution->GetGeometry()->FirstLinestring;
      MainFrame->ConvertString(MainFrame->GetProjectCrs().GetEllipsoid(), ellps,
                               &len);
      gaiaEllipseParams(ellps, &a, &b, &rf);
      length =
        gaiaGreatCircleTotalLength(a, b, ln->DimensionModel, ln->Coords,
                                   ln->Points);
      unit = wxT("m");
  } else
    {
      gaiaGeomCollLength(Solution->GetGeometry(), &length);
      unit = MainFrame->GetProjectCrs().GetUnitName();
    }
  sprintf(dummy, "%1.2f ", length);
  label = wxString::FromUTF8(dummy);
  label += unit;
  wxTextCtrl *lengthCtrl =
    new wxTextCtrl(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize,
                   wxTE_READONLY);
  hdLengthSizer->Add(lengthCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
// Routing Algorithm
  wxBoxSizer *hd3Sizer = new wxBoxSizer(wxVERTICAL);
  HeadSizer->Add(hd3Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *algorithmBox = new wxStaticBox(this, wxID_STATIC,
                                              wxT("Routing Algorithm"),
                                              wxDefaultPosition,
                                              wxDefaultSize);
  wxBoxSizer *hd31Sizer = new wxStaticBoxSizer(algorithmBox, wxVERTICAL);
  hd3Sizer->Add(hd31Sizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  wxTextCtrl *algorithmCtrl =
    new wxTextCtrl(this, wxID_ANY, Solution->GetRoutingAlgorithm(),
                   wxDefaultPosition, wxDefaultSize,
                   wxTE_READONLY);
  hd31Sizer->Add(algorithmCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
// elapsed time  
  wxStaticBox *timeBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Elapsed Time"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *hd32Sizer = new wxStaticBoxSizer(timeBox, wxVERTICAL);
  hd3Sizer->Add(hd32Sizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  Solution->GetElapsedTime(label);
  wxTextCtrl *timeCtrl =
    new wxTextCtrl(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize,
                   wxTE_READONLY);
  hd32Sizer->Add(timeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
// a GRID to show results
  wxBoxSizer *routeBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(routeBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *routeBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Routing Details"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *routeSizer = new wxStaticBoxSizer(routeBox, wxVERTICAL);
  routeBoxSizer->Add(routeSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  GridSizer = new wxBoxSizer(wxHORIZONTAL);
  routeSizer->Add(GridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  GridCtrl =
    new wxGrid(this, ID_ROUTING_GRID, wxDefaultPosition, wxSize(500, 200));
// populating the Grid
  if (HasNames == true)
    GridCtrl->CreateGrid(Solution->GetCount(), 6);
  else
    GridCtrl->CreateGrid(Solution->GetCount(), 5);
  GridCtrl->SetColLabelValue(0, wxT("ArcRowid"));
  GridCtrl->SetColLabelValue(1, wxT("NodeFrom"));
  GridCtrl->SetColLabelValue(2, wxT("NodeTo"));
  GridCtrl->SetColLabelValue(3, wxT("ArcCost"));
  GridCtrl->SetColLabelValue(4, wxT("TotalCost"));
  if (HasNames == true)
    GridCtrl->SetColLabelValue(5, wxT("RoadName"));
  int rowNo = 0;
  double TotalCost = 0.0;
  SolutionArc *arc = Solution->GetFirst();
  while (arc)
    {
      wxString cell;
      char dummy[128];
      sprintf(dummy, "%d", rowNo + 1);
      cell = wxString::FromUTF8(dummy);
      GridCtrl->SetRowLabelValue(rowNo, cell);
      sprintf(dummy, FORMAT_64, arc->GetArcId());
      cell = wxString::FromUTF8(dummy);
      GridCtrl->SetCellValue(rowNo, 0, cell);
      if (TextNodes == true)
        {
          GridCtrl->SetCellValue(rowNo, 1, arc->GetNodeFromText());
          GridCtrl->SetCellValue(rowNo, 2, arc->GetNodeToText());
      } else
        {
          sprintf(dummy, FORMAT_64, arc->GetNodeFromId());
          cell = wxString::FromUTF8(dummy);
          GridCtrl->SetCellValue(rowNo, 1, cell);
          sprintf(dummy, FORMAT_64, arc->GetNodeToId());
          cell = wxString::FromUTF8(dummy);
          GridCtrl->SetCellValue(rowNo, 2, cell);
        }
      sprintf(dummy, "%1.2f", arc->GetCost());
      cell = wxString::FromUTF8(dummy);
      GridCtrl->SetCellValue(rowNo, 3, cell);
      TotalCost += arc->GetCost();
      sprintf(dummy, "%1.2f", TotalCost);
      cell = wxString::FromUTF8(dummy);
      GridCtrl->SetCellValue(rowNo, 4, cell);
      if (HasNames == true)
        GridCtrl->SetCellValue(rowNo, 5, arc->GetName());
      rowNo++;
      arc = arc->GetNext();
    }

  GridCtrl->SetRowLabelSize(wxGRID_AUTOSIZE);
  GridCtrl->AutoSize();
  GridCtrl->ClearSelection();
  GridSizer->Add(GridCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
//  CLOSE button etc
  FootSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(FootSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *close = new wxButton(this, wxID_CANCEL, wxT("&Close"));
  FootSizer->Add(close, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  FootSizer->AddSpacer(32);
  FootSizer->AddSpacer(32);
  FootSizer->AddSpacer(32);
  FootSizer->AddSpacer(32);
  ZoomArcBtn =
    new wxBitmapButton(this, ID_ROUTING_ZOOM_ARC, wxBitmap(arc_yes_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  ZoomArcBtn->SetBitmapDisabled(wxBitmap(arc_no_xpm));
  ZoomArcBtn->Enable(false);
  ZoomArcBtn->SetToolTip(wxT("Zoom to selected Arc"));
  FootSizer->Add(ZoomArcBtn, 0, wxALIGN_RIGHT | wxALL, 2);
  ZoomArcBtn->SetToolTip(wxT("Zoom to selected Arc"));
  FootSizer->Add(ZoomArcBtn, 0, wxALIGN_RIGHT | wxALL, 2);
  ZoomRouteBtn =
    new wxBitmapButton(this, ID_ROUTING_ZOOM_ROUTE, wxBitmap(route_yes_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  ZoomRouteBtn->SetBitmapDisabled(wxBitmap(route_no_xpm));
  ZoomRouteBtn->SetToolTip(wxT("Zoom to whole Route"));
  FootSizer->Add(ZoomRouteBtn, 0, wxALIGN_RIGHT | wxALL, 2);
  FootSizer->AddSpacer(32);
  ZoomInBtn =
    new wxBitmapButton(this, ID_ROUTING_ZOOM_IN, wxBitmap(zoom_in_yes_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  ZoomInBtn->SetBitmapDisabled(wxBitmap(zoom_in_no_xpm));
  ZoomInBtn->SetToolTip(wxT("ZoomIn"));
  FootSizer->Add(ZoomInBtn, 0, wxALIGN_RIGHT | wxALL, 2);
  ZoomOutBtn =
    new wxBitmapButton(this, ID_ROUTING_ZOOM_OUT, wxBitmap(zoom_out_yes_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  ZoomOutBtn->SetBitmapDisabled(wxBitmap(zoom_out_no_xpm));
  ZoomOutBtn->SetToolTip(wxT("ZoomOut"));
  FootSizer->Add(ZoomOutBtn, 0, wxALIGN_RIGHT | wxALL, 2);
// appends event handler for SEARCH button
  Connect(ID_ROUTING_GRID, wxEVT_GRID_CELL_LEFT_CLICK,
          (wxObjectEventFunction) & RoutingSolutionDialog::OnArcSelected);
  Connect(ID_ROUTING_GRID, wxEVT_GRID_CELL_RIGHT_CLICK,
          (wxObjectEventFunction) & RoutingSolutionDialog::OnArcSelected);
  Connect(ID_ROUTING_GRID, wxEVT_GRID_LABEL_LEFT_CLICK,
          (wxObjectEventFunction) & RoutingSolutionDialog::OnArcSelected);
  Connect(ID_ROUTING_GRID, wxEVT_GRID_LABEL_RIGHT_CLICK,
          (wxObjectEventFunction) & RoutingSolutionDialog::OnArcSelected);
  Connect(ID_ROUTING_ZOOM_ARC, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & RoutingSolutionDialog::OnZoomArc);
  Connect(ID_ROUTING_ZOOM_ROUTE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & RoutingSolutionDialog::OnZoomRoute);
  Connect(ID_ROUTING_ZOOM_IN, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & RoutingSolutionDialog::OnZoomIn);
  Connect(ID_ROUTING_ZOOM_OUT, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & RoutingSolutionDialog::OnZoomOut);
}

void RoutingSolutionDialog::UnsetCurrentArc()
{
// cleaning the currently selected Arc
  if (CurrentArc)
    gaiaFreeGeomColl(CurrentArc);
  CurrentArc = NULL;
  MapView->FlushGeometriesToMark();
}

void RoutingSolutionDialog::SetCurrentArc(sqlite3_int64 id)
{
// retrieving Geometry corresponding to the currently selected Arc
  sqlite3 *sqlite = MainFrame->GetSqlite();
  wxString sql;
  int ret;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  NetworkParams *net = MainFrame->GetNetwork();
  UnsetCurrentArc();
  if (!net)
    return;
// preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += net->GetGeometryColumn();
  sql += wxT("\" FROM \"");
  sql += net->GetMainTable();
  sql += wxT("\" WHERE ROWID = ?");
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    return;
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  sqlite3_bind_int64(stmt, 1, id);
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          // fetching a valid row} 
          gaiaGeomCollPtr geom = NULL;
          char proj_from[1024];
          char proj_to[1024];
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              geom =
                gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                          blob_size);
            }
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
              CurrentArc = geom;
            }
      } else
        return;
    }
  sqlite3_finalize(stmt);
}

void RoutingSolutionDialog::OnArcSelected(wxGridEvent & event)
{
//
// cell selection changed
//
  int row = event.GetRow();
  if (row >= 0)
    {
      ZoomArcBtn->Enable(true);
      SolutionArc *arc = Solution->FindByPos(row);
      if (arc)
        {
          SetCurrentArc(arc->GetArcId());
          if (!CurrentArc)
            {
              UnsetCurrentArc();
              ZoomArcBtn->Enable(false);
              GridCtrl->ClearSelection();
          } else
            {
              ZoomArcBtn->Enable(true);
              GridCtrl->SelectRow(row);
              MapView->AddGeometryToMark(CurrentArc);
              MapView->StartRoutingMarker();
            }
      } else
        {
          UnsetCurrentArc();
          ZoomArcBtn->Enable(false);
          GridCtrl->ClearSelection();
        }
  } else
    {
      UnsetCurrentArc();
      ZoomArcBtn->Enable(false);
      GridCtrl->ClearSelection();
    }
}

void RoutingSolutionDialog::OnZoomArc(wxCommandEvent & WXUNUSED(event))
{
//
// performing a ZoomTo -> selected Arc
//
  double minx = CurrentArc->MinX;
  double miny = CurrentArc->MinY;
  double maxx = CurrentArc->MaxX;
  double maxy = CurrentArc->MaxY;
  double ticx = (maxx - minx);
  double ticy = (maxy - miny);
  minx -= ticx;
  maxx += ticx;
  miny -= ticy;
  maxy += ticy;
  MapView->ZoomTo(minx, miny, maxx, maxy);
}

void RoutingSolutionDialog::OnZoomRoute(wxCommandEvent & WXUNUSED(event))
{
//
// performing a ZoomTo -> whole Route
//
  double minx = Solution->GetGeometry()->MinX;
  double miny = Solution->GetGeometry()->MinY;
  double maxx = Solution->GetGeometry()->MaxX;
  double maxy = Solution->GetGeometry()->MaxY;
  double ticx = (maxx - minx) / 4.0;
  double ticy = (maxy - miny) / 4.0;
  minx -= ticx;
  maxx += ticx;
  miny -= ticy;
  maxy += ticy;
  MapView->ZoomTo(minx, miny, maxx, maxy);
}

bool OutputMapDialog::Create(MyFrame * parent, double minX, double minY,
                             double maxX, double maxY)
{
//
// dialog creation
//
  MainFrame = parent;
  MinX = minX;
  MinY = minY;
  MaxX = maxX;
  MaxY = maxY;
  ExtentX = maxX - minX;
  ExtentY = maxY - minY;
  Jpeg = false;
  Png = false;
  Tiff = false;
  Svg = false;
  Pdf = true;
  PdfA3 = false;
  PdfLandscape = false;
  PdfDpi = 300;
  CopyToClipboard = false;
  WorldFile = false;
  BackgroundColor = wxColour(255, 255, 255);
  Width = 1024;
  Height = 1024;
  MaxWidth = 8192;
  MaxHeight = 8192;
  PixelRatio = ExtentX / Width;
  if (ExtentY > ExtentX)
    {
      PixelRatio = ExtentY / Height;
      Width = (int) (ExtentX / PixelRatio);
      double px = ExtentY / 8192;
      MaxWidth = (int) (ExtentX / px);
  } else
    {
      Height = (int) (ExtentY / PixelRatio);
      double px = ExtentX / 8192;
      MaxHeight = (int) (ExtentY / px);
    }
  if (wxDialog::Create(MainFrame, wxID_ANY, wxT("Setting Output Map options"))
      == false)
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

void OutputMapDialog::CreateControls()
{
//
// creating individual controls and setting initial values
//
  char dummy[128];
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxHORIZONTAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// Left block: OUTPUT FORMAT
  wxBoxSizer *grpSizer = new wxBoxSizer(wxVERTICAL);
  boxSizer->Add(grpSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  wxBoxSizer *grp2Sizer = new wxBoxSizer(wxHORIZONTAL);
  grpSizer->Add(grp2Sizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  wxBoxSizer *formatSizer = new wxBoxSizer(wxHORIZONTAL);
  grp2Sizer->Add(formatSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  wxString format[6];
  format[0] = wxT("JPEG");
  format[1] = wxT("PNG");
  format[2] = wxT("TIFF");
  format[3] = wxT("PDF document");
  format[4] = wxT("SVG [vector graphics]");
  format[5] = wxT("Copy into the clipboard");
  FormatCtrl = new wxRadioBox(this, ID_OUTMAP_FORMAT,
                              wxT("Output format"),
                              wxDefaultPosition, wxDefaultSize, 6, format, 1,
                              wxRA_SPECIFY_COLS);
  FormatCtrl->SetSelection(3);
  formatSizer->Add(FormatCtrl, 0, wxALIGN_RIGHT | wxALL, 5);

// Center block
  wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);
  grp2Sizer->Add(rightSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
// first row: Width / Height
  wxStaticBox *dimsBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Image Size"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *dimsSizer = new wxStaticBoxSizer(dimsBox, wxVERTICAL);
  rightSizer->Add(dimsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 3);
  wxBoxSizer *widthSizer = new wxBoxSizer(wxHORIZONTAL);
  dimsSizer->Add(widthSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *widthLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Width:"));
  widthSizer->Add(widthLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);
  sprintf(dummy, "%d", Width);
  wxString width = wxString::FromUTF8(dummy);
  WidthCtrl = new wxSpinCtrl(this, ID_OUTMAP_WIDTH, width,
                             wxDefaultPosition, wxSize(80, 20), wxSP_ARROW_KEYS,
                             32, MaxWidth, Width);
  WidthCtrl->Enable(false);
  widthSizer->Add(WidthCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);
  wxBoxSizer *heightSizer = new wxBoxSizer(wxHORIZONTAL);
  dimsSizer->Add(heightSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *heightLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Height:"));
  heightSizer->Add(heightLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);
  sprintf(dummy, "%d", Height);
  wxString height = wxString::FromUTF8(dummy);
  HeightCtrl = new wxSpinCtrl(this, ID_OUTMAP_HEIGHT, height,
                              wxDefaultPosition, wxSize(80, 20),
                              wxSP_ARROW_KEYS, 32, MaxHeight, Height);
  HeightCtrl->Enable(false);
  heightSizer->Add(HeightCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);

// second row: Mode
  wxBoxSizer *modeSizer = new wxBoxSizer(wxHORIZONTAL);
  dimsSizer->Add(modeSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxString mode[2];
  mode[0] = wxT("Image");
  mode[1] = wxT("Pixel");
  ModeCtrl = new wxRadioBox(this, ID_OUTMAP_FORMAT,
                            wxT("Set size mode"),
                            wxDefaultPosition, wxDefaultSize, 2, mode, 2,
                            wxRA_SPECIFY_COLS);
  ModeCtrl->SetSelection(0);
  ModeCtrl->Enable(false);
  modeSizer->Add(ModeCtrl, 0, wxALIGN_RIGHT | wxALL, 0);

// third row: pixel size
  wxStaticBox *pixelBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Pixel Size [in Map Units]"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *pixelSizer = new wxStaticBoxSizer(pixelBox, wxHORIZONTAL);
  dimsSizer->Add(pixelSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 3);
  wxStaticText *pixelLabel = new wxStaticText(this, wxID_STATIC, wxT("&Size:"));
  pixelSizer->Add(pixelLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);
  sprintf(dummy, "%1.6f", PixelRatio);
  wxString pixel = wxString::FromUTF8(dummy);
  PixelCtrl =
    new wxTextCtrl(this, ID_OUTMAP_PIXEL, pixel, wxDefaultPosition,
                   wxDefaultSize, wxTE_RICH);
  PixelCtrl->Enable(false);
  DefaultPixelStyle = PixelCtrl->GetDefaultStyle();
  pixelSizer->Add(PixelCtrl, 0, wxALIGN_RIGHT | wxALL, 3);

// lower block: Background Color
  wxBoxSizer *lowerSizer = new wxBoxSizer(wxHORIZONTAL);
  grpSizer->Add(lowerSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxString world[2];
  world[0] = wxT("No");
  world[1] = wxT("Yes");
  WorldFileCtrl = new wxRadioBox(this, ID_OUTMAP_WORLDFILE,
                                 wxT("World File"),
                                 wxDefaultPosition, wxDefaultSize, 2, world, 1,
                                 wxRA_SPECIFY_COLS);
  WorldFileCtrl->SetSelection(0);
  WorldFileCtrl->Enable(false);
  lowerSizer->Add(WorldFileCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxStaticBox *backBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Image background color"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *backSizer = new wxStaticBoxSizer(backBox, wxHORIZONTAL);
  lowerSizer->Add(backSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBitmap disabledBmp;
  GetDisabledButtonBitmap(disabledBmp);
  wxBitmap backBmp;
  GetButtonBitmap(backBmp);
  BackgroundColorCtrl = new wxBitmapButton(this, ID_OUTMAP_BACKGROUND, backBmp);
  BackgroundColorCtrl->SetBitmapDisabled(disabledBmp);
  BackgroundColorCtrl->Enable(false);
  backSizer->Add(BackgroundColorCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  // right block: PDF settings
  wxBoxSizer *xpdfSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(xpdfSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  wxStaticBox *pdfBox = new wxStaticBox(this, wxID_STATIC,
                                        wxT("PDF settings"),
                                        wxDefaultPosition,
                                        wxDefaultSize);
  wxBoxSizer *pdfSizer = new wxStaticBoxSizer(pdfBox, wxVERTICAL);
  xpdfSizer->Add(pdfSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);
// A3 - A4
  wxString a3[2];
  a3[0] = wxT("A4 page");
  a3[1] = wxT("A3 page");
  PdfPageSizeCtrl = new wxRadioBox(this, ID_OUTMAP_PAGESIZE,
                                   wxT("Size"),
                                   wxDefaultPosition, wxDefaultSize, 2, a3, 1,
                                   wxRA_SPECIFY_COLS);
  PdfPageSizeCtrl->SetSelection(0);
  pdfSizer->Add(PdfPageSizeCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// Page Orientation
  wxString orientation[2];
  orientation[0] = wxT("Portrait");
  orientation[1] = wxT("Landscape");
  PdfLandscapeCtrl = new wxRadioBox(this, ID_OUTMAP_LANDSCAPE,
                                    wxT("Orientation"),
                                    wxDefaultPosition, wxDefaultSize, 2,
                                    orientation, 1, wxRA_SPECIFY_COLS);
  PdfLandscapeCtrl->SetSelection(0);
  pdfSizer->Add(PdfLandscapeCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// DPI resolution
  wxString dpi[3];
  dpi[0] = wxT("72 DPI [screen quality]");
  dpi[1] = wxT("300 DPI [printer quality]");
  dpi[2] = wxT("600 DPI [printer hi-res]");
  PdfDpiCtrl = new wxRadioBox(this, ID_OUTMAP_DPI,
                              wxT("Resolution"),
                              wxDefaultPosition, wxDefaultSize, 3, dpi, 1,
                              wxRA_SPECIFY_COLS);
  PdfDpiCtrl->SetSelection(1);
  pdfSizer->Add(PdfDpiCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

// OK button
  wxBoxSizer *okBox = new wxBoxSizer(wxHORIZONTAL);
  topSizer->Add(okBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *ok = new wxButton(this, wxID_OK, wxT("&OK"));
  okBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
  okBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  IgnoreWidthEvent = false;
  IgnoreHeightEvent = false;
  IgnorePixelEvent = false;
// appends event handlers
  Connect(ID_OUTMAP_WIDTH, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & OutputMapDialog::OnWidthChanged);
  Connect(ID_OUTMAP_HEIGHT, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & OutputMapDialog::OnHeightChanged);
  Connect(ID_OUTMAP_PIXEL, wxEVT_COMMAND_TEXT_UPDATED,
          (wxObjectEventFunction) & OutputMapDialog::OnPixelChanged);
  Connect(ID_OUTMAP_FORMAT, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & OutputMapDialog::OnFormatChanged);
  Connect(ID_OUTMAP_MODE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & OutputMapDialog::OnModeChanged);
  Connect(ID_OUTMAP_WORLDFILE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & OutputMapDialog::OnWorldFileChanged);
  Connect(ID_OUTMAP_PAGESIZE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & OutputMapDialog::OnPdfA3Changed);
  Connect(ID_OUTMAP_LANDSCAPE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & OutputMapDialog::OnPdfLandscapeChanged);
  Connect(ID_OUTMAP_DPI, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & OutputMapDialog::OnPdfDpiChanged);
  Connect(ID_OUTMAP_BACKGROUND, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & OutputMapDialog::OnBackgroundColor);
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & OutputMapDialog::OnOk);
}

void OutputMapDialog::GetButtonBitmap(wxBitmap & bmp)
{
// creating a Bitmap representing some Color
  bmp = wxBitmap(128, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(BackgroundColor));
  dc->DrawRectangle(-1, -1, 130, 26);
  delete dc;
}

void OutputMapDialog::GetDisabledButtonBitmap(wxBitmap & bmp)
{
// creating the disabled Bitmap
  bmp = wxBitmap(128, 24);
  wxMemoryDC *dc = new wxMemoryDC(bmp);
  dc->SetBrush(wxBrush(wxColour(224, 224, 224)));
  dc->DrawRectangle(-1, -1, 130, 26);
  delete dc;
}

void OutputMapDialog::OnBackgroundColor(wxCommandEvent & WXUNUSED(event))
{
// color selection
  wxColourData initColor;
  int ret;
  initColor.SetChooseFull(false);
  initColor.SetColour(BackgroundColor);
  wxColourDialog colorDialog(this, &initColor);
  ret = colorDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxColourData colorData = colorDialog.GetColourData();
      BackgroundColor = colorData.GetColour();
      wxBitmap bmp;
      GetButtonBitmap(bmp);
      BackgroundColorCtrl->SetBitmapLabel(bmp);
    }
}

void OutputMapDialog::OnFormatChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Format changed
//
  Jpeg = false;
  Png = false;
  Tiff = false;
  Svg = false;
  Pdf = false;
  CopyToClipboard = false;
  switch (FormatCtrl->GetSelection())
    {
      case 0:
        Jpeg = true;
        break;
      case 1:
        Png = true;
        break;
      case 2:
        Tiff = true;
        break;
      case 3:
        Pdf = true;
        break;
      case 4:
        Svg = true;
        break;
      case 5:
        CopyToClipboard = true;
        break;
    };
  if (Svg == true || Pdf == true)
    {
      BackgroundColorCtrl->Enable(false);
      WorldFile = false;
      WorldFileCtrl->SetSelection(0);
      WorldFileCtrl->Enable(false);
  } else
    {
      BackgroundColorCtrl->Enable(true);
      if (CopyToClipboard == true)
        {
          WorldFile = false;
          WorldFileCtrl->SetSelection(0);
          WorldFileCtrl->Enable(false);
      } else
        {
          if (WorldFile == true)
            WorldFileCtrl->SetSelection(1);
          else
            WorldFileCtrl->SetSelection(0);
          WorldFileCtrl->Enable(true);
        }
    }
  if (Pdf == true)
    {
      WidthCtrl->Enable(false);
      HeightCtrl->Enable(false);
      ModeCtrl->Enable(false);
      PdfPageSizeCtrl->Enable(true);
      PdfLandscapeCtrl->Enable(true);
      PdfDpiCtrl->Enable(true);
  } else
    {
      WidthCtrl->Enable(true);
      HeightCtrl->Enable(true);
      ModeCtrl->Enable(true);
      PdfPageSizeCtrl->Enable(false);
      PdfLandscapeCtrl->Enable(false);
      PdfDpiCtrl->Enable(false);
    }
}

void OutputMapDialog::OnModeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Mode changed
//
  if (ModeCtrl->GetSelection() == 0)
    {
      HeightCtrl->Enable(true);
      WidthCtrl->Enable(true);
      PixelCtrl->Enable(false);
  } else
    {
      HeightCtrl->Enable(false);
      WidthCtrl->Enable(false);
      PixelCtrl->Enable(true);
    }
}

void OutputMapDialog::OnWorldFileChanged(wxCommandEvent & WXUNUSED(event))
{
//
// WorldFile changed
//
  if (WorldFileCtrl->GetSelection() == 0)
    WorldFile = false;
  else
    WorldFile = true;
}

void OutputMapDialog::OnPdfA3Changed(wxCommandEvent & WXUNUSED(event))
{
//
// PDF Page Size changed
//
  if (PdfPageSizeCtrl->GetSelection() == 0)
    PdfA3 = false;
  else
    PdfA3 = true;
}

void OutputMapDialog::OnPdfLandscapeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// PDF Orientation changed
//
  if (PdfLandscapeCtrl->GetSelection() == 0)
    PdfLandscape = false;
  else
    PdfLandscape = true;
}

void OutputMapDialog::OnPdfDpiChanged(wxCommandEvent & WXUNUSED(event))
{
//
// PDF resolution changed
//
  if (PdfDpiCtrl->GetSelection() == 1)
    PdfDpi = 300;
  else if (PdfDpiCtrl->GetSelection() == 2)
    PdfDpi = 600;
  else
    PdfDpi = 72;
}

void OutputMapDialog::OnWidthChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Width changed
//
  if (IgnoreWidthEvent == true)
    {
      IgnoreWidthEvent = false;
      return;
    }
  Width = WidthCtrl->GetValue();
  PixelRatio = ExtentX / Width;
  char dummy[128];
  sprintf(dummy, "%1.6f", PixelRatio);
  wxString pixel = wxString::FromUTF8(dummy);
  IgnorePixelEvent = true;
  PixelCtrl->SetValue(pixel);
  IgnoreHeightEvent = true;
  Height = (int) (ExtentY / PixelRatio);
  HeightCtrl->SetValue(Height);
}

void OutputMapDialog::OnHeightChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Height changed
//
  if (IgnoreHeightEvent == true)
    {
      IgnoreHeightEvent = false;
      return;
    }
  Height = HeightCtrl->GetValue();
  PixelRatio = ExtentY / Height;
  char dummy[128];
  sprintf(dummy, "%1.6f", PixelRatio);
  wxString pixel = wxString::FromUTF8(dummy);
  IgnorePixelEvent = true;
  PixelCtrl->SetValue(pixel);
  IgnoreWidthEvent = true;
  Width = (int) (ExtentX / PixelRatio);
  WidthCtrl->SetValue(Width);
}

void OutputMapDialog::OnPixelChanged(wxCommandEvent & WXUNUSED(event))
{
//
// Pixel changed
//
  if (IgnorePixelEvent == true)
    {
      IgnorePixelEvent = false;
      return;
    }
  double px;
  wxString str = PixelCtrl->GetValue();
  if (str.ToDouble(&px) == true)
    {
      double w = ExtentX / px;
      double h = ExtentY / px;
      if (w > 8192.0)
        goto error;
      if (h > 8192.0)
        goto error;
      if (w < 32.0)
        goto error;
      if (h < 32.0)
        goto error;
      IgnoreWidthEvent = true;
      IgnoreHeightEvent = true;
      Width = (int) w;
      Height = (int) h;
      WidthCtrl->SetValue(Width);
      HeightCtrl->SetValue(Height);
      PixelRatio = px;
      PixelCtrl->SetStyle(0, str.Len(), DefaultPixelStyle);
      return;
    }
error:
  wxTextAttr style(wxColour(255, 0, 0), wxColour(255, 255, 0));
  PixelCtrl->SetStyle(0, str.Len(), style);
}

void OutputMapDialog::OnOk(wxCommandEvent & WXUNUSED(event))
{
//
// all done: 
//
  if (Svg == false)
    {
      // checking the raster dims
      int width;
      int height;
      int dx;
      int dy;
      width = (int) (ExtentX / PixelRatio);
      height = (int) (ExtentY / PixelRatio);
      dx = Width - width;
      dy = Height - height;
      if (abs(dx) > 2 || abs(dy) > 2)
        {
          wxMessageBox(wxT
                       ("Mismatching image size ...\n\nPlease, check better"),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          return;
        }
    }
  if (Svg == true)
    {
      // checking graphic settings for SVG
      if (MainFrame->CheckSvgGraphics() == false)
        {
          wxString msg =
            wxT("WARNING: the current map graphic settings cannot be\n");
          msg += wxT("faithfully translated into SVG graphic.\n\n");
          msg +=
            wxT("This is because you are using points [always rendered as\n");
          msg +=
            wxT
            ("circles on SVG] and/or pattern-based polygon fillings, that\n");
          msg +=
            wxT
            ("aren't supported by corresponding SVG graphic capabilities.\n\n");
          msg +=
            wxT("Accordingly to this, the map you are going to export as\n");
          msg +=
            wxT("SVG may appear quite different as you are expecting.\n\n");
          msg += wxT("Do you confirm proceding anyway ?");
          int ret =
            wxMessageBox(msg, wxT("spatialite-gis"), wxYES_NO | wxICON_QUESTION,
                         this);
          if (ret != wxYES)
            return;
        }
    }
  if (Pdf == true)
    {
      // checking graphic settings for PDF
      if (MainFrame->CheckPdfGraphics() == false)
        {
          wxString msg =
            wxT("WARNING: the current map graphic settings cannot be\n");
          msg += wxT("faithfully translated into PDF graphic.\n\n");
          msg +=
            wxT("This is because you are using transparent colors and/or\n");
          msg +=
            wxT("pattern-based polygon fillings, that aren't supported by\n");
          msg += wxT("corresponding PDF graphic capabilities.\n\n");
          msg +=
            wxT("Accordingly to this, the map you are going to export as\n");
          msg +=
            wxT("PDF may appear quite different as you are expecting.\n\n");
          msg += wxT("Do you confirm proceding anyway ?");
          int ret =
            wxMessageBox(msg, wxT("spatialite-gis"), wxYES_NO | wxICON_QUESTION,
                         this);
          if (ret != wxYES)
            return;
        }
    }
  wxDialog::EndModal(wxID_OK);
}

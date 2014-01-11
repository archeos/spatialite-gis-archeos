/*
/ TableDialogs.cpp
/ various dialog classes - identify and show table
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
#include "wx/clipbrd.h"
#include "wx/filename.h"

#include <spatialite/gaiaaux.h>
#include <spatialite/gaiaexif.h>

#include "icons/rs_first_on.xpm"
#include "icons/rs_last_on.xpm"
#include "icons/rs_next_on.xpm"
#include "icons/rs_previous_on.xpm"
#include "icons/rs_first_off.xpm"
#include "icons/rs_last_off.xpm"
#include "icons/rs_next_off.xpm"
#include "icons/rs_previous_off.xpm"
#include "icons/refresh.xpm"
#include "icons/zoom_in_yes.xpm"
#include "icons/zoom_in_no.xpm"
#include "icons/table_save_yes.xpm"
#include "icons/table_save_no.xpm"
#include "icons/selection_top_yes.xpm"
#include "icons/selection_top_no.xpm"
#include "icons/selection_remove.xpm"

#if defined(_WIN32) || defined (__MINGW32__)
#define FORMAT_64	"%I64d"
#else
#define FORMAT_64	"%lld"
#endif

IdentifyDialog::~IdentifyDialog()
{
  Map->StopGeometryMarker();
  delete Entities;
  if (TableValues)
    delete TableValues;
  if (TableBackupValues)
    delete TableBackupValues;
}

bool IdentifyDialog::Create(MyMapView * map, MyFrame * parent, MapLayer * layer,
                            IdentifyEntitiesList * list)
{
//
// creating the dialog
//
  Map = map;
  MainFrame = parent;
  TableName = layer->GetTableName();
  GeometryColumn = layer->GetGeometryColumn();
  DescName = layer->GetDescName();
  UseAlias = true;
  CurrentEntityRow = wxNOT_FOUND;
  Entities = list;
  CurrentEntity = NULL;
  ReadOnly = layer->IsReadOnly();
  TableValues = NULL;
  TableBackupValues = NULL;
  OkColor = wxColour(255, 255, 255);
  ErrorColor = wxColour(255, 192, 128);
  TableMetadata();
  if (wxDialog::Create(parent, wxID_ANY, wxT("Identify Entities")) == false)
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

void IdentifyDialog::CreateControls()
{
//
// creating individual control and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// First row: Layer description
  wxBoxSizer *layerBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerBoxSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticBox *layerBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Current Layer"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *layerSizer = new wxStaticBoxSizer(layerBox, wxVERTICAL);
  layerBoxSizer->Add(layerSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *geomSizer = new wxBoxSizer(wxHORIZONTAL);
  layerSizer->Add(geomSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *geomLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Vector Layer:"));
  geomSizer->Add(geomLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString geom = TableName + wxT(".") + GeometryColumn;
  wxTextCtrl *geomValue = new wxTextCtrl(this, wxID_ANY, geom,
                                         wxDefaultPosition, wxSize(200,
                                                                   22),
                                         wxTE_READONLY);
  geomSizer->Add(geomValue, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  layerSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *descValue = new wxTextCtrl(this, wxID_ANY, DescName,
                                         wxDefaultPosition, wxSize(200,
                                                                   22),
                                         wxTE_READONLY);
  descSizer->Add(descValue, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *aliasBox = new wxBoxSizer(wxHORIZONTAL);
  layerBoxSizer->Add(aliasBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  AliasCtrl = new wxCheckBox(this, ID_IDENTIFY_ALIAS, wxT("Use alias names"));
  AliasCtrl->SetValue(UseAlias);
  aliasBox->Add(AliasCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// Second row: Entities list and current Entity
  wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(mainSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
// Left group: Entities list
  wxBoxSizer *listBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  mainSizer->Add(listBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *listBox = new wxStaticBox(this, wxID_STATIC,
                                         wxT("Selected entities"),
                                         wxDefaultPosition,
                                         wxDefaultSize);
  wxBoxSizer *listSizer = new wxStaticBoxSizer(listBox, wxVERTICAL);
  listBoxSizer->Add(listSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *entitiesSizer = new wxBoxSizer(wxHORIZONTAL);
  listSizer->Add(entitiesSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  ListCtrl =
    new wxGrid(this, ID_IDENTIFY_LIST, wxDefaultPosition, wxSize(200, 300));
  ListCtrl->CreateGrid(Entities->GetCount(), 2);
  ListCtrl->SetColLabelValue(0, wxT("RowId"));
  ListCtrl->SetColLabelValue(1, wxT("Entity label"));
  int row = 0;
  IdentifyEntity *entity = Entities->GetFirst();
  while (entity)
    {
      wxString strNum;
      char num[64];
      sprintf(num, "%d", row + 1);
      strNum = wxString::FromUTF8(num);
      ListCtrl->SetRowLabelValue(row, strNum);
      sprintf(num, FORMAT_64, entity->GetRowId());
      strNum = wxString::FromUTF8(num);
      ListCtrl->SetCellValue(row, 0, strNum);
      ListCtrl->SetCellValue(row, 1, entity->GetLabel());
      row++;
      entity = entity->GetNext();
    }
  ListCtrl->SetRowLabelSize(wxGRID_AUTOSIZE);
  ListCtrl->AutoSize();
  listSizer->Add(ListCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// Right group: current Entity
  wxBoxSizer *entityBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  mainSizer->Add(entityBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *entityBox = new wxStaticBox(this, wxID_STATIC,
                                           wxT("Current entity"),
                                           wxDefaultPosition,
                                           wxDefaultSize);
  wxBoxSizer *entitySizer = new wxStaticBoxSizer(entityBox, wxVERTICAL);
  entityBoxSizer->Add(entitySizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// appending the DELETE button
  wxBoxSizer *delSizer = new wxBoxSizer(wxHORIZONTAL);
  entitySizer->Add(delSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  DeleteBtn =
    new wxButton(this, ID_IDENTIFY_DELETE, wxT("&Delete this entity"));
  delSizer->Add(DeleteBtn, 0, wxALIGN_LEFT | wxALL, 5);
  GridSizer = new wxBoxSizer(wxHORIZONTAL);
  entitySizer->Add(GridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  EntityCtrl =
    new wxGrid(this, ID_IDENTIFY_ENTITY, wxDefaultPosition, wxSize(300, 300));
  EntityCtrl->CreateGrid(1, 1);
  EntityCtrl->SetColLabelValue(0, wxT("Attribute value"));
  EntityCtrl->SetRowLabelValue(0, wxT("1"));
  EntityCtrl->SetCellValue(0, 0, wxT("empty"));
  EntityCtrl->SetRowLabelSize(wxGRID_AUTOSIZE);
  EntityCtrl->AutoSize();
  GridSizer->Add(EntityCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// appending the SAVE / RESTORE buttons
  wxBoxSizer *editSizer = new wxBoxSizer(wxHORIZONTAL);
  entitySizer->Add(editSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  SaveBtn = new wxButton(this, ID_IDENTIFY_SAVE, wxT("&Save changes"));
  editSizer->Add(SaveBtn, 0, wxALIGN_LEFT | wxALL, 5);
  RestoreBtn = new wxButton(this, ID_IDENTIFY_RESTORE, wxT("&Restore"));
  editSizer->Add(RestoreBtn, 0, wxALIGN_LEFT | wxALL, 5);
  if (ReadOnly == true)
    {
      // updating button's visibility if ReadOnly is set
      SaveBtn->Show(false);
      RestoreBtn->Show(false);
      DeleteBtn->Show(false);
    }
//  QUIT button
  wxBoxSizer *quitBox = new wxBoxSizer(wxVERTICAL);
  boxSizer->Add(quitBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *quitCtrl = new wxButton(this, wxID_CANCEL, wxT("&Quit"));
  quitBox->Add(quitCtrl, 0, wxALIGN_LEFT | wxALL, 5);
// adding the event handlers
  Connect(ID_IDENTIFY_LIST, wxEVT_GRID_LABEL_LEFT_CLICK,
          (wxObjectEventFunction) & IdentifyDialog::OnEntitySelected);
  Connect(ID_IDENTIFY_LIST, wxEVT_GRID_LABEL_RIGHT_CLICK,
          (wxObjectEventFunction) & IdentifyDialog::OnEntitySelected);
  Connect(ID_IDENTIFY_LIST, wxEVT_GRID_SELECT_CELL,
          (wxObjectEventFunction) & IdentifyDialog::OnEntitySelected);
  Connect(ID_IDENTIFY_ENTITY, wxEVT_GRID_CELL_RIGHT_CLICK,
          (wxObjectEventFunction) & IdentifyDialog::OnEntityRightClick);
  Connect(ID_IDENTIFY_ENTITY2, wxEVT_GRID_CELL_RIGHT_CLICK,
          (wxObjectEventFunction) & IdentifyDialog::OnEntityRightClick);
  Connect(ID_IDENTIFY_ENTITY, wxEVT_GRID_CELL_CHANGE,
          (wxObjectEventFunction) & IdentifyDialog::OnCellValueChanged);
  Connect(ID_IDENTIFY_ENTITY2, wxEVT_GRID_CELL_CHANGE,
          (wxObjectEventFunction) & IdentifyDialog::OnCellValueChanged);
  Connect(ID_IDENTIFY_CLEAR, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdClearSelection);
  Connect(ID_IDENTIFY_ALL, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdSelectAll);
  Connect(ID_IDENTIFY_COPY, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdCopy);
  Connect(ID_IDENTIFY_COPY_IMAGE, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdCopyImage);
  Connect(ID_IDENTIFY_ALIAS, wxEVT_COMMAND_CHECKBOX_CLICKED,
          (wxObjectEventFunction) & IdentifyDialog::OnAliasSelected);
  Connect(ID_IDENTIFY_DELETE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdDelete);
  Connect(ID_IDENTIFY_SAVE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdSave);
  Connect(ID_IDENTIFY_RESTORE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdRestore);
  Connect(ID_IDENTIFY_BLOB_IN, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdBlobIn);
  Connect(ID_IDENTIFY_BLOB_OUT, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdBlobOut);
  Connect(ID_IDENTIFY_BLOB_NULL, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & IdentifyDialog::OnCmdBlobNull);
// selecting the first entity
  CurrentEntityRow = 0;
  ListCtrl->SelectRow(0);
  CurrentEntity = Entities->GetItemByPos(0);
  ShowEntity();
}

void IdentifyDialog::TableMetadata()
{
//
// retrivieng the column list for the current table
//
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  wxString sql;
  char *column;
  char *type;
  bool pk;
  bool not_null;
  wxString xColumn;
  wxString xType;
  bool noLayout;
  sql = wxT("PRAGMA table_info(\"");
  sql += TableName;
  sql += wxT("\")");
  int ret = sqlite3_get_table(MainFrame->GetSqlite(), sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
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
          if (xColumn != GeometryColumn)
            ColumnList.Add(xColumn, xType, pk, not_null);
        }
    }
  sqlite3_free_table(results);
// retrieving the Column defs
  noLayout = true;
  sql = wxT("SELECT column_name, desc_name, data_type, length, decimals ");
  sql += wxT("FROM layer_table_layout ");
  sql += wxT("WHERE table_name = '");
  sql += TableName;
  sql += wxT("' AND geometry_column = '");
  sql += GeometryColumn;
  sql += wxT("'");
  ret =
    sqlite3_get_table(MainFrame->GetSqlite(), sql.ToUTF8(), &results, &rows,
                      &columns, &errMsg);
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
          char *value;
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
          ColumnList.SetHints(name, desc, type, len, dec);
          noLayout = false;
        }
    }
  sqlite3_free_table(results);
  if (noLayout == true)
    {
      if (ReadOnly == true)
        {
          wxString msg =
            wxT("The layout for this DB Table has not yet been defined.\n\n");
          msg +=
            wxT
            ("In order to get a cleaner data presentation you are suggested\n");
          msg += wxT("to set up this table layout as soon as possible.\n\n");
          msg += wxT("Please, use the LayerConfiguratio/TableLayout tool");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                       this);
      } else
        {
          wxString msg =
            wxT("The layout for this DB Table has not yet been defined.\n\n");
          msg += wxT("This is not compatible with attribute editing.\n");
          msg += wxT("So, any data editing feature has been disabled.\n\n");
          msg += wxT("Please, use the LayerConfiguratio/TableLayout tool");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_EXCLAMATION,
                       this);
          ReadOnly = true;
        }
    }
}

void IdentifyDialog::ShowEntity()
{
//
// showing an entity
//
  wxString sql;
  int ret;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char dummy[128];
  wxString value;
  wxGrid *newGrid;
  int id;
  if (TableValues)
    delete TableValues;
  if (TableBackupValues)
    delete TableBackupValues;
  TableValues = NULL;
  TableBackupValues = NULL;
  Map->FlushGeometriesToMark();
  if (EntityCtrl->GetId() == ID_IDENTIFY_ENTITY)
    id = ID_IDENTIFY_ENTITY2;
  else
    id = ID_IDENTIFY_ENTITY;
  if (!CurrentEntity)
    goto stop;
  Map->AddGeometryToMark(CurrentEntity->GetGeometry());
  Map->StartGeometryMarker(TableName, GeometryColumn);
  newGrid = new wxGrid(this, id, wxDefaultPosition, wxSize(300, 300));
  newGrid->Show(false);
  sql = wxT("SELECT * FROM \"");
  sql += TableName;
  sql += wxT("\" WHERE ROWID = ?");
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
// binding the ROWID
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  sqlite3_bind_int64(stmt, 1, CurrentEntity->GetRowId());
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          int i;
          int col;
          int cols = sqlite3_column_count(stmt);
          newGrid->CreateGrid(cols - 1, 1);
          newGrid->SetColLabelValue(0, wxT("Attribute value"));
          TableValues = new MyValues(cols, 1);
          TableBackupValues = new MyValues(cols, 1);
          if (ReadOnly == true)
            newGrid->EnableEditing(false);
          else
            newGrid->EnableEditing(true);
          col = 0;
          for (i = 0; i < cols; i++)
            {
              bool useRenderer = false;
              value = wxString::FromUTF8(sqlite3_column_name(stmt, i));
              if (value == GeometryColumn)
                continue;
              QueryColumn *pColumn = ColumnList.Find(value);
              if (UseAlias == true)
                {
                  // trying to use the alias nome for this Column
                  if (pColumn)
                    {
                      if (pColumn->GetDescName().Len() > 0)
                        value = pColumn->GetDescName();
                    }
                }
              newGrid->SetRowLabelValue(col, value);
              value = wxT("NULL");
              if (sqlite3_column_type(stmt, i) == SQLITE_INTEGER)
                {
                  if (pColumn->GetDataType() == SQLITE_BOOLEAN)
                    {
                      if (sqlite3_column_int64(stmt, i) == 0)
                        value = wxT("FALSE");
                      else
                        value = wxT("TRUE");
                  } else
                    {
                      sprintf(dummy, FORMAT_64, sqlite3_column_int64(stmt, i));
                      value = wxString::FromUTF8(dummy);
                    }
                  TableValues->SetValue(col, 0, sqlite3_column_int64(stmt, i));
                  TableBackupValues->SetValue(col, 0,
                                              sqlite3_column_int64(stmt, i));
                }
              if (sqlite3_column_type(stmt, i) == SQLITE_FLOAT)
                {
                  bool formatted = false;
                  if (pColumn)
                    {
                      // trying to apply Formatting Hints
                      if (pColumn->GetDataType() == SQLITE_FLOAT)
                        {
                          char fmt[16];
                          sprintf(fmt, "%%1.%df", pColumn->GetDecimals());
                          sprintf(dummy, fmt, sqlite3_column_double(stmt, i));
                          formatted = true;
                        }
                      if (pColumn->GetDataType() == SQLITE_DATE)
                        {
                          MainFrame->ConvertFromJulianDate(sqlite3_column_double
                                                           (stmt, i), dummy);
                          formatted = true;
                        }
                      if (pColumn->GetDataType() == SQLITE_DATETIME)
                        {
                          MainFrame->ConvertFromJulianDateTime
                            (sqlite3_column_double(stmt, i), dummy);
                          formatted = true;
                        }
                    }
                  if (formatted == false)
                    sprintf(dummy, "%1.6f", sqlite3_column_double(stmt, i));
                  value = wxString::FromUTF8(dummy);
                  TableValues->SetValue(col, 0, sqlite3_column_double(stmt, i));
                  TableBackupValues->SetValue(col, 0,
                                              sqlite3_column_double(stmt, i));
                }
              if (sqlite3_column_type(stmt, i) == SQLITE_TEXT)
                {
                  value =
                    wxString::FromUTF8((char *) sqlite3_column_text(stmt, i));
                  TableValues->SetValue(col, 0, value);
                  TableBackupValues->SetValue(col, 0, value);
                }
              if (sqlite3_column_type(stmt, i) == SQLITE_BLOB)
                {
                  unsigned char *blob =
                    (unsigned char *) sqlite3_column_blob(stmt, i);
                  int blobSize = sqlite3_column_bytes(stmt, i);
                  int blobType = gaiaGuessBlobType(blob, blobSize);
                  if (blobType == GAIA_GEOMETRY_BLOB)
                    {
                      value = wxT("GEOMETRY");
                  } else if (blobType == GAIA_JPEG_BLOB
                             || blobType == GAIA_EXIF_BLOB
                             || blobType == GAIA_EXIF_GPS_BLOB
                             || blobType == GAIA_PNG_BLOB
                             || blobType == GAIA_GIF_BLOB
                             || blobType == GAIA_TIFF_BLOB)
                    {
                      GridCellImage *renderer =
                        new GridCellImage(blob, blobSize, 128);
                      newGrid->SetCellRenderer(col, 0, renderer);
                      useRenderer = true;
                  } else
                    {
                      value = wxT("BLOB");
                    }
                  newGrid->SetReadOnly(col, 0);
                  TableValues->SetValue(col, 0, blob, blobSize);
                  TableBackupValues->SetValue(col, 0, blob, blobSize);
                }
              if (sqlite3_column_type(stmt, i) == SQLITE_NULL
                  && pColumn->GetDataType() == SQLITE_IMAGE)
                {
                  GridCellImage *renderer = new GridCellImage(128);
                  newGrid->SetCellRenderer(col, 0, renderer);
                  useRenderer = true;
                  if (pColumn->IsNotNull() == true)
                    renderer->SetError(true);
                }
              if (useRenderer == false)
                newGrid->SetCellValue(col, 0, value);
              col++;
              if (ReadOnly == false)
                {
                  if (pColumn->IsPrimaryKey() == true)
                    newGrid->SetReadOnly(col, 0);
                  if (pColumn->IsBlobColumn() == true)
                    newGrid->SetReadOnly(col, 0);
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

  newGrid->Show(true);
  newGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
  newGrid->AutoSize();
  GridSizer->Replace(EntityCtrl, newGrid);
  GridSizer->Layout();
  delete EntityCtrl;
  EntityCtrl = newGrid;
  GetSizer()->Fit(this);
  DeleteBtn->Enable(true);
  SaveBtn->Enable(false);
  RestoreBtn->Enable(true);
  return;

stop:
  newGrid = new wxGrid(this, id, wxDefaultPosition, wxSize(300, 300));
  newGrid->CreateGrid(1, 1);
  newGrid->SetColLabelValue(0, wxT("DELETED"));
  newGrid->SetColLabelValue(1, wxT("DELETED"));
  newGrid->SetReadOnly(0, 0);
  newGrid->SetCellValue(0, 0, wxT("DELETED"));
  newGrid->Show(true);
  newGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
  newGrid->AutoSize();
  GridSizer->Replace(EntityCtrl, newGrid);
  GridSizer->Layout();
  delete EntityCtrl;
  EntityCtrl = newGrid;
  GetSizer()->Fit(this);
  DeleteBtn->Enable(false);
  SaveBtn->Enable(false);
  RestoreBtn->Enable(false);
  return;
}

void IdentifyDialog::OnAliasSelected(wxCommandEvent & WXUNUSED(event))
{
//
// USE ALIAS changed
//
  UseAlias = AliasCtrl->GetValue();
  ShowEntity();
}

void IdentifyDialog::OnEntitySelected(wxGridEvent & event)
{
//
// cell selection changed
//
  int row = event.GetRow();
  if (row >= 0)
    {
      CurrentEntityRow = row;
      ListCtrl->SelectRow(row);
      CurrentEntity = Entities->GetItemByPos(row);
      if (CurrentEntity->IsDeleted() == true)
        CurrentEntity = NULL;
      ShowEntity();
    }
  event.Skip();
}

void IdentifyDialog::OnCellValueChanged(wxGridEvent & event)
{
//
// user changed some cell value
//
  int row = event.GetRow();
  int col = event.GetCol();
  long int_value;
  sqlite3_int64 int64_value;
  double dbl_value;
  bool bool_value;
  char dummy[128];
  wxString value = EntityCtrl->GetCellValue(row, col);
  QueryColumn *pColumn = ColumnList.Find(row);
  if (pColumn)
    {
      if (pColumn->GetDataType() == SQLITE_INTEGER)
        {
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetValue(row, col);
                  TableValues->SetError(row, col, false);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (value.ToLong(&int_value) == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              int64_value = int_value;
              TableValues->SetValue(row, col, int64_value);
              TableValues->SetError(row, col, false);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              sprintf(dummy, FORMAT_64, int64_value);
              value = wxString::FromUTF8(dummy);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_FLOAT)
        {
          MainFrame->ReplaceDecimalComma(value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (value.ToDouble(&dbl_value) == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              char fmt[16];
              sprintf(fmt, "%%1.%df", pColumn->GetDecimals());
              sprintf(dummy, fmt, dbl_value);
              value = wxString::FromUTF8(dummy);
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, dbl_value);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_DATE)
        {
          strcpy(dummy, value.ToUTF8());
          bool ret = MainFrame->ConvertToJulianDate(dummy, &dbl_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (ret == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, dbl_value);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              MainFrame->ConvertFromJulianDate(dbl_value, dummy);
              value = wxString::FromUTF8(dummy);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_DATETIME)
        {
          strcpy(dummy, value.ToUTF8());
          bool ret = MainFrame->ConvertToJulianDateTime(dummy, &dbl_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (ret == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, dbl_value);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              MainFrame->ConvertFromJulianDateTime(dbl_value, dummy);
              value = wxString::FromUTF8(dummy);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_BOOLEAN)
        {
          bool ret = MainFrame->FormatBoolean(value, &bool_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (ret == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              if (bool_value == true)
                {
                  TableValues->SetValue(row, col, (sqlite3_int64) 1);
                  value = wxT("TRUE");
              } else
                {
                  TableValues->SetValue(row, col, (sqlite3_int64) 0);
                  value = wxT("FALSE");
                }
              TableValues->SetError(row, col, false);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_TEXT)
        {
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetValue(row, col);
                  TableValues->SetError(row, col, false);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else
            {
              wxString trunct = value.Truncate(pColumn->GetLength());
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, trunct);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              EntityCtrl->SetCellValue(row, col, trunct);
            }
        }
    }
  SaveBtn->Enable(CheckChanged());
}

void IdentifyDialog::OnEntityRightClick(wxGridEvent & event)
{
//
// right click on some cell [mouse action]
//
  if (!CurrentEntity)
    return;
  wxMenu *menu = new wxMenu();
  wxMenuItem *menuItem;
  wxPoint pt = event.GetPosition();
  CurrentEvtRow = event.GetRow();
  CurrentEvtColumn = event.GetCol();
  MyVariant *blobVar = TableValues->GetValue(CurrentEvtRow, CurrentEvtColumn);
  if (blobVar)
    {
      if (blobVar->GetType() == MY_BLOB_VARIANT)
        {
          // this one is a BLOB cell
          int guessType =
            gaiaGuessBlobType(blobVar->GetBlob(), blobVar->GetBlobSize());
          if (guessType == GAIA_GEOMETRY_BLOB)
            ;
          else
            {
              if (ReadOnly == false)
                {
                  menuItem =
                    new wxMenuItem(menu, ID_IDENTIFY_BLOB_IN,
                                   wxT("BLOB &import"));
                  menu->Append(menuItem);
                }
              menuItem =
                new wxMenuItem(menu, ID_IDENTIFY_BLOB_OUT, wxT("BLOB &export"));
              menu->Append(menuItem);
              if (ReadOnly == false)
                {
                  menuItem =
                    new wxMenuItem(menu, ID_IDENTIFY_BLOB_NULL,
                                   wxT("Set BLOB as &NULL"));
                  menu->Append(menuItem);
                }
              menu->AppendSeparator();
              if (guessType == GAIA_JPEG_BLOB
                  || guessType == GAIA_EXIF_BLOB
                  || guessType == GAIA_EXIF_GPS_BLOB
                  || guessType == GAIA_PNG_BLOB || guessType == GAIA_GIF_BLOB
                  || guessType == GAIA_TIFF_BLOB)
                {
                  menuItem =
                    new wxMenuItem(menu, ID_IDENTIFY_COPY_IMAGE,
                                   wxT("&Image Copy"));
                  menu->Append(menuItem);
                  menu->AppendSeparator();
                }
            }
      } else
        {
          // this one is an ordinary cell
          if (ReadOnly == false)
            {
              MyRowVariant *varRow = TableValues->GetRow(CurrentEvtRow);
              if (varRow->IsDeleted() == false)
                {
                  menuItem =
                    new wxMenuItem(menu, ID_IDENTIFY_BLOB_IN,
                                   wxT("BLOB &import"));
                  menu->Append(menuItem);
                  menu->AppendSeparator();
                }
            }
        }
    }
  menuItem = new wxMenuItem(menu, ID_IDENTIFY_CLEAR, wxT("&Clear selection"));
  menu->Append(menuItem);
  menuItem = new wxMenuItem(menu, ID_IDENTIFY_ALL, wxT("Select &all"));
  menu->Append(menuItem);
  menu->AppendSeparator();
  menuItem = new wxMenuItem(menu, ID_IDENTIFY_COPY, wxT("&Copy"));
  menu->Append(menuItem);
  if (EntityCtrl->IsSelection() == false)
    menuItem->Enable(false);

  EntityCtrl->PopupMenu(menu, pt);
}

void IdentifyDialog::OnCmdClearSelection(wxCommandEvent & WXUNUSED(event))
{
//
// clearing current selection
//
  EntityCtrl->ClearSelection();
}

void IdentifyDialog::OnCmdSelectAll(wxCommandEvent & WXUNUSED(event))
{
//
// selecting all
//
  EntityCtrl->SelectAll();
}

void IdentifyDialog::OnCmdCopy(wxCommandEvent & WXUNUSED(event))
{
//
// copying the selection into the clipboard
//
  wxString copyData;
  int row;
  int col;
  bool newRow;
  bool firstRow = true;
  for (row = 0; row < EntityCtrl->GetNumberRows(); row++)
    {
      newRow = true;
      for (col = 0; col < EntityCtrl->GetNumberCols(); col++)
        {
          if (EntityCtrl->IsInSelection(row, col) == true)
            {
              // ok, this cell is included into the selection to copy
              if (firstRow == true)
                {
                  newRow = false;
                  firstRow = false;
              } else if (newRow == true)
                {
                  newRow = false;
                  copyData += wxT("\n");
              } else
                copyData += wxT("\t");
              copyData += EntityCtrl->GetCellValue(row, col);
            }
        }
    }
  if (wxTheClipboard->Open())
    {
      wxTheClipboard->SetData(new wxTextDataObject(copyData));
      wxTheClipboard->Close();
    }
}

void IdentifyDialog::OnCmdCopyImage(wxCommandEvent & WXUNUSED(event))
{
//
// copying an image into the clipboard
//
  MyVariant *blobVar = TableValues->GetValue(CurrentEvtRow, CurrentEvtColumn);
  if (!blobVar)
    return;
  if (blobVar->GetType() != MY_BLOB_VARIANT)
    return;
  wxMemoryInputStream reader(blobVar->GetBlob(), blobVar->GetBlobSize());
  wxImage img = wxImage(reader);
  if (wxTheClipboard->Open())
    {
      wxTheClipboard->SetData(new wxBitmapDataObject(img));
      wxTheClipboard->Close();
    }
}

void IdentifyDialog::OnCmdSave(wxCommandEvent & WXUNUSED(event))
{
//
// ROW UPDATE
//
  wxString sql;
  char xSql[1024];
  char dummy[1024];
  int len;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  bool errors = false;
  int cols = ColumnList.GetCount();
  int c;
  QueryColumn *pColumn;
  bool comma;
  int param;
  int ret;
  for (c = 0; c < cols; c++)
    {
      MyVariant *pVar = TableValues->GetValue(c, 0);
      if (pVar->IsError() == true)
        errors = true;
    }
  if (errors == true)
    {
      wxString msg = wxT("Some illegal/invalid attribute value was found\n\n");
      msg += wxT("Please correct any error and then retry");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  sql = wxT("UPDATE \"");
  sql += TableName;
  sql += wxT("\" SET ");
  comma = false;
  pColumn = ColumnList.GetFirst();
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
          sql += wxT("\" = ?");
        }
      pColumn = pColumn->GetNext();
    }
  sql += wxT(" WHERE ROWID = ?");
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
  param = 1;
  c = 0;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      // binding any ordinary column value
      if (pColumn->IsPrimaryKey() == false)
        {
          MyVariant *pVar = TableValues->GetValue(c, 0);
          if (pVar->GetType() == MY_INT_VARIANT)
            sqlite3_bind_int64(stmt, param++, pVar->GetIntValue());
          else if (pVar->GetType() == MY_DBL_VARIANT)
            sqlite3_bind_double(stmt, param++, pVar->GetDblValue());
          else if (pVar->GetType() == MY_TXT_VARIANT)
            {
              MainFrame->ConvertString(pVar->GetTxtValue(), dummy, &len);
              sqlite3_bind_text(stmt, param++, dummy, len, SQLITE_TRANSIENT);
          } else if (pVar->GetType() == MY_BLOB_VARIANT)
            sqlite3_bind_blob(stmt, param++, pVar->GetBlob(),
                              pVar->GetBlobSize(), SQLITE_STATIC);
          else
            sqlite3_bind_null(stmt, param++);
        }
      c++;
      pColumn = pColumn->GetNext();
    }
// binding the ROWID
  sqlite3_bind_int64(stmt, param++, CurrentEntity->GetRowId());

  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      return;
    }

  sqlite3_finalize(stmt);
  wxDialog::EndModal(wxID_OK);
stop:
  return;
}

void IdentifyDialog::OnCmdDelete(wxCommandEvent & WXUNUSED(event))
{
//
// user required entity deletion
//
  char *errMsg = NULL;
  bool error = false;
  int ret;
  wxString sql;
  wxString rowid;
  char dummy[256];
  int row;
  if (!CurrentEntity)
    return;
  if (CurrentEntity->IsDeleted() == true)
    return;
  sprintf(dummy, FORMAT_64, CurrentEntity->GetRowId());
  rowid = wxString::FromUTF8(dummy);
  ret =
    wxMessageBox(wxT("Requested deletion for row identified by RowId = ")
                 + rowid + wxT("\n\nConfirm ?"), wxT("spatialite-gis"),
                 wxYES_NO | wxICON_QUESTION, this);
  if (ret != wxYES)
    return;
  sql = wxT("DELETE FROM \"") + TableName + wxT("\" WHERE ROWID = ") + rowid;
  ret = sqlite3_exec(MainFrame->GetSqlite(), sql.ToUTF8(), NULL, NULL, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      error = true;
    }
  if (error == false)
    {
      // marking row as deleted
      CurrentEntity->SetDeleted();
      CurrentEntity = NULL;
      ListCtrl->SetCellTextColour(CurrentEntityRow, 0, wxColour(192, 192, 192));
      ListCtrl->SetCellBackgroundColour(CurrentEntityRow, 0,
                                        wxColour(64, 64, 64));
      ListCtrl->SetCellTextColour(CurrentEntityRow, 1, wxColour(192, 192, 192));
      ListCtrl->SetCellBackgroundColour(CurrentEntityRow, 1,
                                        wxColour(64, 64, 64));
      ListCtrl->ForceRefresh();
      Map->PrepareMap();
      row = GetNextValidEntity();
      if (row < 0)
        wxDialog::EndModal(wxID_CANCEL);
      else
        {
          CurrentEntityRow = row;
          ListCtrl->SelectRow(row);
          CurrentEntity = Entities->GetItemByPos(row);
          ShowEntity();
        }
    }
}

int IdentifyDialog::GetNextValidEntity()
{
//
// trying to get the next valid entity
//
  int i = 0;
  IdentifyEntity *p = Entities->GetFirst();
  while (p)
    {
      // PASS 1: trying to get a row following the current one
      if (i > CurrentEntityRow && p->IsDeleted() == false)
        return i;
      i++;
      p = p->GetNext();
    }
  i = 0;
  p = Entities->GetFirst();
  while (p)
    {
      // PASS 2: trying to get the first valid row
      if (p->IsDeleted() == false)
        return i;
      i++;
      p = p->GetNext();
    }
  return -1;
}

void IdentifyDialog::OnCmdRestore(wxCommandEvent & WXUNUSED(event))
{
//
// ROW Restore
//
  int c = 0;
  wxString value;
  char dummy[1024];
  QueryColumn *pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      bool useRenderer = false;
      MyVariant *pVar = TableBackupValues->GetValue(c, 0);
      if (pVar->GetType() == MY_INT_VARIANT)
        {
          TableValues->SetValue(c, 0, pVar->GetIntValue());
          if (pColumn->GetDataType() == SQLITE_BOOLEAN)
            {
              if (pVar->GetIntValue() == 0)
                value = wxT("FALSE");
              else
                value = wxT("TRUE");
          } else
            {
              sprintf(dummy, FORMAT_64, pVar->GetIntValue());
              value = wxString::FromUTF8(dummy);
            }
      } else if (pVar->GetType() == MY_DBL_VARIANT)
        {
          bool formatted = false;
          if (pColumn->GetDataType() == SQLITE_FLOAT)
            {
              char fmt[16];
              sprintf(fmt, "%%1.%df", pColumn->GetDecimals());
              sprintf(dummy, fmt, pVar->GetDblValue());
              formatted = true;
            }
          if (pColumn->GetDataType() == SQLITE_DATE)
            {
              MainFrame->ConvertFromJulianDate(pVar->GetDblValue(), dummy);
              formatted = true;
            }
          if (pColumn->GetDataType() == SQLITE_DATETIME)
            {
              MainFrame->ConvertFromJulianDateTime(pVar->GetDblValue(), dummy);
              formatted = true;
            }
          if (formatted == false)
            sprintf(dummy, "%1.6f", pVar->GetDblValue());
          value = wxString::FromUTF8(dummy);
          TableValues->SetValue(c, 0, pVar->GetDblValue());
      } else if (pVar->GetType() == MY_TXT_VARIANT)
        {
          TableValues->SetValue(c, 0, pVar->GetTxtValue());
          value = pVar->GetTxtValue();
      } else if (pVar->GetType() == MY_BLOB_VARIANT)
        {
          TableValues->SetValue(c, 0, pVar->GetBlob(), pVar->GetBlobSize());
          if (pColumn->GetDataType() == SQLITE_IMAGE)
            {
              GridCellImage *renderer =
                (GridCellImage *) EntityCtrl->GetCellRenderer(c, 0);
              if (renderer == NULL)
                {
                  renderer =
                    new GridCellImage(pVar->GetBlob(), pVar->GetBlobSize(),
                                      128);
                  EntityCtrl->SetCellRenderer(c, 0, renderer);
              } else
                renderer->SetImage(pVar->GetBlob(), pVar->GetBlobSize());
              useRenderer = true;
            }
      } else
        TableValues->SetValue(c, 0);
      if (useRenderer == false)
        EntityCtrl->SetCellValue(c, 0, value);
      EntityCtrl->SetCellBackgroundColour(c, 0, OkColor);
      c++;
      pColumn = pColumn->GetNext();
    }
  EntityCtrl->ForceRefresh();
  SaveBtn->Enable(false);
}

void IdentifyDialog::OnCmdBlobIn(wxCommandEvent & WXUNUSED(event))
{
//
// importing a BLOB
//
  FILE *in = NULL;
  char path[2048];
  int rd;
  int maxSize = 1024 * 1024;    // limit BLOB size to 1MB
  wxString fileList;
  unsigned char *buffer = NULL;
  int ret;
  wxString lastDir;
  bool image = false;
  wxString value;
  bool useRenderer = false;
  QueryColumn *pColumn = ColumnList.Find(CurrentEvtRow);
  if (pColumn)
    {
      if (pColumn->GetDataType() == SQLITE_IMAGE)
        image = true;
    }
  if (image == true)
    {
      // IMAGE
      fileList =
        wxT
        ("Image (*.jpg;*.jpeg;*.png;*.gif;*.tif)|*.jpg;*.jpeg;*.png;*.gif;*.tif|");
      fileList +=
        wxT
        ("JPEG Image (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Image (*.png)|*.png|GIF Image (*.gif)|*.gif|TIFF Image (*.tif)|*.tif|");
      fileList += wxT("All files (*.*)|*.*");
  } else
    {
      // generic BLOB
      fileList =
        wxT
        ("BLOB Document (*.jpg;*.jpeg;*.png;*.gif;*.tif;*.pdf;*.zip)|*.jpg;*.jpeg;*.png;*.gif;*.tif;*.pdf;*.zip|");
      fileList +=
        wxT
        ("Image (*.jpg;*.jpeg;*.png;*.gif;*.tif)|*.jpg;*.jpeg;*.png;*.gif;*.tif|");
      fileList +=
        wxT
        ("JPEG Image (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Image (*.png)|*.png|GIF Image (*.gif)|*.gif|TIFF Image (*.tif)|*.tif|");
      fileList +=
        wxT
        ("PDF Document (*.pdf)|*.pdf|ZIP Archive|(*.zip)|All files (*.*)|*.*");
    }
  wxFileDialog fileDialog(this, wxT("loading a BLOB value"),
                          wxT(""), wxT(""), fileList,
                          wxFD_OPEN | wxFD_FILE_MUST_EXIST,
                          wxDefaultPosition, wxDefaultSize, wxT("filedlg"));
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      strcpy(path, fileDialog.GetPath().ToUTF8());
      in = fopen(path, "rb");
      if (!in)
        {
          wxMessageBox(wxT("Cannot open '") + fileDialog.GetPath() +
                       wxT("' for reading"), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          return;
        }
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      MainFrame->SetLastDirectory(lastDir);
      ::wxBeginBusyCursor();
      buffer = new unsigned char[maxSize];
      rd = fread(buffer, 1, maxSize, in);
      if (rd == maxSize && !(feof(in)))
        {
          // exceding 1MB; it's too big for a BLOB
          wxMessageBox(wxT
                       ("Selected file excedes 1MB; cowardly refusing to load it as a BLOB value ..."),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          goto end;
        }
      if (ferror(in))
        {
          // I/O error
          wxMessageBox(wxT("an I/O error occurred"), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto end;
        }
      // updating the Grid cell
      int blobType = gaiaGuessBlobType(buffer, maxSize);
      if (blobType == GAIA_GEOMETRY_BLOB)
        {
          value = wxT("GEOMETRY");
      } else if (blobType == GAIA_JPEG_BLOB
                 || blobType == GAIA_EXIF_BLOB
                 || blobType == GAIA_EXIF_GPS_BLOB
                 || blobType == GAIA_PNG_BLOB || blobType == GAIA_GIF_BLOB
                 || blobType == GAIA_TIFF_BLOB)
        {
          GridCellImage *renderer =
            (GridCellImage *) EntityCtrl->GetCellRenderer(CurrentEvtRow,
                                                          CurrentEvtColumn);
          if (renderer == NULL)
            {
              renderer = new GridCellImage(buffer, maxSize, 128);
              EntityCtrl->SetCellRenderer(CurrentEvtRow, CurrentEvtColumn,
                                          renderer);
          } else
            renderer->SetImage(buffer, maxSize);
          renderer->SetError(false);
          useRenderer = true;
      } else
        {
          value = wxT("BLOB");
        }
      EntityCtrl->SetReadOnly(CurrentEvtRow, CurrentEvtColumn);
      TableValues->SetValue(CurrentEvtRow, CurrentEvtColumn, buffer, maxSize);
      if (useRenderer == false)
        EntityCtrl->SetCellValue(CurrentEvtRow, CurrentEvtColumn, value);
      if (image == true && useRenderer == false)
        {
          TableValues->SetError(CurrentEvtRow, CurrentEvtColumn, true);
          EntityCtrl->SetCellBackgroundColour(CurrentEvtRow, CurrentEvtColumn,
                                              ErrorColor);
      } else
        {
          TableValues->SetError(CurrentEvtRow, CurrentEvtColumn, false);
          EntityCtrl->SetCellBackgroundColour(CurrentEvtRow, CurrentEvtColumn,
                                              OkColor);
        }
      EntityCtrl->ForceRefresh();
    }
end:
// clean-up
  ::wxEndBusyCursor();
  if (in)
    fclose(in);
  if (buffer)
    delete[]buffer;
  SaveBtn->Enable(CheckChanged());
}

void IdentifyDialog::OnCmdBlobOut(wxCommandEvent & WXUNUSED(event))
{
//
// exporting a BLOB
//
  int blobType;
  wxString fileName;
  wxString fileType;
  int ret;
  wxString path;
  FILE *out = NULL;
  char xpath[2048];
  int wr;
  wxString lastDir;
  MyVariant *blobVar = TableValues->GetValue(CurrentEvtRow, CurrentEvtColumn);
  if (!blobVar)
    return;
  if (blobVar->GetType() != MY_BLOB_VARIANT)
    return;
  blobType = gaiaGuessBlobType(blobVar->GetBlob(), blobVar->GetBlobSize());
  switch (blobType)
    {
      case GAIA_JPEG_BLOB:
      case GAIA_EXIF_BLOB:
      case GAIA_EXIF_GPS_BLOB:
        fileName = wxT("image.jpg");
        fileType = wxT("File JPEG (*.jpg;*.jpeg)|*.jpg");
        break;
      case GAIA_PNG_BLOB:
        fileName = wxT("image.png");
        fileType = wxT("File PNG (*.png)|*.png");
        break;
      case GAIA_GIF_BLOB:
        fileName = wxT("image.gif");
        fileType = wxT("File GIF (*.gif)|*.gif");
        break;
      case GAIA_TIFF_BLOB:
        fileName = wxT("image.tif");
        fileType = wxT("File TIFF (*.tif)|*.tif");
        break;
      case GAIA_PDF_BLOB:
        fileName = wxT("document.pdf");
        fileType = wxT("PDF document (*.pdf)|*.pdf");
        break;
      case GAIA_ZIP_BLOB:
        fileName = wxT("archive.zip");
        fileType = wxT("ZIP Archive (*.zip)|*.zip");
        break;
      default:
        fileName = wxT("file");
    };
  fileType += wxT("|All files (*.*)|*.*");
  wxFileDialog fileDialog(this, wxT("exporting a BLOB value to file"),
                          wxT(""), fileName, fileType,
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition,
                          wxDefaultSize, wxT("filedlg"));
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxFileName file(fileDialog.GetPath());
      path = file.GetPath();
      path += file.GetPathSeparator();
      path += file.GetName();
      switch (blobType)
        {
          case GAIA_JPEG_BLOB:
          case GAIA_EXIF_BLOB:
          case GAIA_EXIF_GPS_BLOB:
            path += wxT(".jpg");
            break;
          case GAIA_PNG_BLOB:
            path += wxT(".png");
            break;
          case GAIA_GIF_BLOB:
            path += wxT(".gif");
            break;
          case GAIA_TIFF_BLOB:
            path += wxT(".tif");
            break;
          case GAIA_PDF_BLOB:
            path += wxT(".pdf");
            break;
          case GAIA_ZIP_BLOB:
            path += wxT(".zip");
            break;
          default:
            path += file.GetExt();
        };
      strcpy(xpath, path.ToUTF8());
      out = fopen(xpath, "wb");
      if (!out)
        {
          wxMessageBox(wxT("Cannot open '") + path + wxT("' for writing"),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          return;
        }
      lastDir = file.GetPath();
      MainFrame->SetLastDirectory(lastDir);
      ::wxBeginBusyCursor();
      wr = fwrite(blobVar->GetBlob(), 1, blobVar->GetBlobSize(), out);
      if (wr != blobVar->GetBlobSize())
        {
          wxMessageBox(wxT("an I/O error occurred"), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
        }
      fclose(out);
      ::wxEndBusyCursor();
    }
}

void IdentifyDialog::OnCmdBlobNull(wxCommandEvent & WXUNUSED(event))
{
//
// setting a NULL BLOB
//
  QueryColumn *pColumn = ColumnList.Find(CurrentEvtRow);
  EntityCtrl->SetReadOnly(CurrentEvtRow, CurrentEvtColumn);
  TableValues->SetValue(CurrentEvtRow, CurrentEvtColumn);
  GridCellImage *renderer =
    (GridCellImage *) EntityCtrl->GetCellRenderer(CurrentEvtRow,
                                                  CurrentEvtColumn);
  if (renderer != NULL)
    {
      renderer->NullImage();
      if (pColumn->IsNotNull() == true)
        renderer->SetError(true);
      EntityCtrl->ForceRefresh();
    }
  SaveBtn->Enable(CheckChanged());
}

bool IdentifyDialog::CheckChanged()
{
//
// checking if there is any changed value
//
  int c = 0;
  QueryColumn *pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      MyVariant *pOld = TableBackupValues->GetValue(c, 0);
      MyVariant *pNew = TableValues->GetValue(c, 0);
      if (pOld->GetType() == pNew->GetType())
        {
          if (pNew->GetType() == MY_INT_VARIANT)
            {
              if (pNew->GetIntValue() != pOld->GetIntValue())
                return true;
          } else if (pNew->GetType() == MY_DBL_VARIANT)
            {
              if (pNew->GetDblValue() != pOld->GetDblValue())
                return true;
          } else if (pNew->GetType() == MY_TXT_VARIANT)
            {
              if (pNew->GetTxtValue() != pOld->GetTxtValue())
                return true;
          } else if (pNew->GetType() == MY_BLOB_VARIANT)
            {
              if (pNew->GetBlobSize() != pOld->GetBlobSize())
                return true;
              if (memcmp(pNew->GetBlob(), pOld->GetBlob(), pNew->GetBlobSize())
                  != 0)
                return true;
            }
      } else
        return true;
      c++;
      pColumn = pColumn->GetNext();
    }
  return false;
}

InsertEntityDialog::~InsertEntityDialog()
{
  Map->StopGeometryMarker();
  if (TableValues)
    delete TableValues;
}

bool InsertEntityDialog::Create(MyMapView * map, MyFrame * parent,
                                LayerObject * layer)
{
//
// creating the dialog
//
  Map = map;
  MainFrame = parent;
  TableName = layer->GetTableName();
  GeometryColumn = layer->GetGeometryColumn();
  DescName = layer->GetDescName();
  UseAlias = true;
  TableValues = NULL;
  OkColor = wxColour(255, 255, 255);
  ErrorColor = wxColour(255, 192, 128);
  TableMetadata();
  if (wxDialog::Create(parent, wxID_ANY, wxT("Insert Entity")) == false)
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

void InsertEntityDialog::CreateControls()
{
//
// creating individual control and setting initial values
//
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// First row: Layer description
  wxBoxSizer *layerBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerBoxSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticBox *layerBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Current Layer"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *layerSizer = new wxStaticBoxSizer(layerBox, wxVERTICAL);
  layerBoxSizer->Add(layerSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *geomSizer = new wxBoxSizer(wxHORIZONTAL);
  layerSizer->Add(geomSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *geomLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Vector Layer:"));
  geomSizer->Add(geomLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxString geom = TableName + wxT(".") + GeometryColumn;
  wxTextCtrl *geomValue = new wxTextCtrl(this, wxID_ANY, geom,
                                         wxDefaultPosition, wxSize(200,
                                                                   22),
                                         wxTE_READONLY);
  geomSizer->Add(geomValue, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *descSizer = new wxBoxSizer(wxHORIZONTAL);
  layerSizer->Add(descSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *descLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Description:"));
  descSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxTextCtrl *descValue = new wxTextCtrl(this, wxID_ANY, DescName,
                                         wxDefaultPosition, wxSize(200,
                                                                   22),
                                         wxTE_READONLY);
  descSizer->Add(descValue, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  wxBoxSizer *aliasBox = new wxBoxSizer(wxHORIZONTAL);
  layerBoxSizer->Add(aliasBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  AliasCtrl = new wxCheckBox(this, ID_INSERT_ALIAS, wxT("Use alias names"));
  AliasCtrl->SetValue(UseAlias);
  aliasBox->Add(AliasCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// Second row: Entities list and current Entity
  wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(mainSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
// Entity
  wxBoxSizer *entityBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  mainSizer->Add(entityBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *entityBox = new wxStaticBox(this, wxID_STATIC,
                                           wxT("New Entity"),
                                           wxDefaultPosition,
                                           wxDefaultSize);
  wxBoxSizer *entitySizer = new wxStaticBoxSizer(entityBox, wxVERTICAL);
  entityBoxSizer->Add(entitySizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  GridSizer = new wxBoxSizer(wxHORIZONTAL);
  entitySizer->Add(GridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  EntityCtrl =
    new wxGrid(this, ID_INSERT_ENTITY, wxDefaultPosition, wxSize(400, 300));
  EntityCtrl->CreateGrid(1, 1);
  EntityCtrl->SetColLabelValue(0, wxT("Attribute value"));
  EntityCtrl->SetRowLabelValue(0, wxT("1"));
  EntityCtrl->SetCellValue(0, 0, wxT("empty"));
  EntityCtrl->SetRowLabelSize(wxGRID_AUTOSIZE);
  EntityCtrl->AutoSize();
  GridSizer->Add(EntityCtrl, 0, wxALIGN_RIGHT | wxALL, 5);
// appending the INSERT / ABORT buttons
  wxBoxSizer *editSizer = new wxBoxSizer(wxHORIZONTAL);
  entitySizer->Add(editSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxButton *insertBtn = new wxButton(this, wxID_OK, wxT("&Insert Entity"));
  editSizer->Add(insertBtn, 0, wxALIGN_LEFT | wxALL, 5);
  wxButton *abortBtn = new wxButton(this, wxID_CANCEL, wxT("&Abort"));
  editSizer->Add(abortBtn, 0, wxALIGN_LEFT | wxALL, 5);
// adding the event handlers
  Connect(ID_INSERT_ENTITY, wxEVT_GRID_CELL_RIGHT_CLICK,
          (wxObjectEventFunction) & InsertEntityDialog::OnRightClick);
  Connect(ID_INSERT_ENTITY2, wxEVT_GRID_CELL_RIGHT_CLICK,
          (wxObjectEventFunction) & InsertEntityDialog::OnRightClick);
  Connect(ID_INSERT_ENTITY, wxEVT_GRID_CELL_CHANGE,
          (wxObjectEventFunction) & InsertEntityDialog::OnCellValueChanged);
  Connect(ID_INSERT_ENTITY2, wxEVT_GRID_CELL_CHANGE,
          (wxObjectEventFunction) & InsertEntityDialog::OnCellValueChanged);
  Connect(ID_INSERT_ALIAS, wxEVT_COMMAND_CHECKBOX_CLICKED,
          (wxObjectEventFunction) & InsertEntityDialog::OnAliasSelected);
  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & InsertEntityDialog::OnCmdInsert);
  Connect(wxID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & InsertEntityDialog::OnCmdAbort);
  Connect(ID_INSERT_BLOB_IN, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & InsertEntityDialog::OnCmdBlobIn);
  Connect(ID_INSERT_BLOB_NULL, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & InsertEntityDialog::OnCmdBlobNull);
// preparing the Grid
  PrepareGrid();
}

void InsertEntityDialog::TableMetadata()
{
//
// retrivieng the column list for the current table
//
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  wxString sql;
  char *column;
  char *type;
  bool pk;
  bool not_null;
  bool noLayout;
  wxString xColumn;
  wxString xType;
  sql = wxT("PRAGMA table_info(\"");
  sql += TableName;
  sql += wxT("\")");
  int ret = sqlite3_get_table(MainFrame->GetSqlite(), sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
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
          if (xColumn != GeometryColumn)
            ColumnList.Add(xColumn, xType, pk, not_null);
        }
    }
  sqlite3_free_table(results);
// retrieving the Column defs
  noLayout = true;
  sql = wxT("SELECT column_name, desc_name, data_type, length, decimals ");
  sql += wxT("FROM layer_table_layout ");
  sql += wxT("WHERE table_name = '");
  sql += TableName;
  sql += wxT("' AND geometry_column = '");
  sql += GeometryColumn;
  sql += wxT("'");
  ret =
    sqlite3_get_table(MainFrame->GetSqlite(), sql.ToUTF8(), &results, &rows,
                      &columns, &errMsg);
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
          char *value;
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
          ColumnList.SetHints(name, desc, type, len, dec);
          noLayout = false;
        }
    }
  sqlite3_free_table(results);
  if (noLayout == true)
    {
      wxString msg =
        wxT("The layout for this DB Table has not yet been defined.\n\n");
      msg +=
        wxT("In order to get a cleaner data presentation you are suggested\n");
      msg += wxT("to set up this table layout as soon as possible.\n\n");
      msg += wxT("Please, use the LayerConfiguratio/TableLayout tool");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION, this);
    }
// creating the arrays to store values
  columns = ColumnList.GetCount();
  TableValues = new MyValues(columns, 1);
}

void InsertEntityDialog::PrepareGrid()
{
//
// setting up the Grid
//
  wxGrid *newGrid;
  wxString value;
  int id;
  int i;
  int cols = ColumnList.GetCount();
  char dummy[128];
  if (EntityCtrl->GetId() == ID_INSERT_ENTITY)
    id = ID_INSERT_ENTITY2;
  else
    id = ID_INSERT_ENTITY;
  Map->AddGeometryToMark(MainFrame->GetCurrentEntityGeometry());
  Map->StartGeometryMarker(TableName, GeometryColumn);
  newGrid = new wxGrid(this, id, wxDefaultPosition, wxSize(400, 300));
  newGrid->Show(false);

  newGrid->CreateGrid(cols, 1);
  newGrid->SetColLabelValue(0, wxT("Attribute value"));
  newGrid->EnableEditing(true);
  i = 0;
  QueryColumn *pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      bool useRenderer = false;
      value = pColumn->GetColumn();
      if (UseAlias == true)
        {
          // trying to use the alias nome for this Column
          if (pColumn->GetDescName().Len() > 0)
            value = pColumn->GetDescName();
        }
      newGrid->SetRowLabelValue(i, value);
      MyVariant *pVar = TableValues->GetValue(i, 0);
      if (pVar)
        {
          // displaying the current cell value
          value = wxT("");
          if (pVar->GetType() == MY_INT_VARIANT)
            {
              if (pColumn->GetDataType() == SQLITE_INTEGER)
                {
                  sprintf(dummy, FORMAT_64, pVar->GetIntValue());
                  value = wxString::FromUTF8(dummy);
                }
              if (pColumn->GetDataType() == SQLITE_BOOLEAN)
                {
                  if (pVar->GetIntValue() == 0)
                    value = wxT("FALSE");
                  else
                    value = wxT("TRUE");
                }
            }
          if (pVar->GetType() == MY_DBL_VARIANT)
            {
              bool formatted = false;
              if (pColumn)
                {
                  // trying to apply Formatting Hints
                  if (pColumn->GetDataType() == SQLITE_FLOAT)
                    {
                      char fmt[16];
                      sprintf(fmt, "%%1.%df", pColumn->GetDecimals());
                      sprintf(dummy, fmt, pVar->GetDblValue());
                      formatted = true;
                    }
                  if (pColumn->GetDataType() == SQLITE_DATE)
                    {
                      MainFrame->ConvertFromJulianDate(pVar->GetDblValue(),
                                                       dummy);
                      formatted = true;
                    }
                  if (pColumn->GetDataType() == SQLITE_DATETIME)
                    {
                      MainFrame->ConvertFromJulianDateTime(pVar->GetDblValue(),
                                                           dummy);
                      formatted = true;
                    }
                }
              if (formatted == false)
                sprintf(dummy, "%1.6f", pVar->GetDblValue());
              value = wxString::FromUTF8(dummy);
            }
          if (pVar->GetType() == MY_TXT_VARIANT)
            value = pVar->GetTxtValue();
          if (pVar->GetType() == MY_BLOB_VARIANT)
            {
              unsigned char *blob = pVar->GetBlob();
              int blobSize = pVar->GetBlobSize();
              int blobType = gaiaGuessBlobType(blob, blobSize);
              if (blobType == GAIA_GEOMETRY_BLOB)
                {
                  value = wxT("GEOMETRY");
              } else if (blobType == GAIA_JPEG_BLOB
                         || blobType == GAIA_EXIF_BLOB
                         || blobType == GAIA_EXIF_GPS_BLOB
                         || blobType == GAIA_PNG_BLOB
                         || blobType == GAIA_GIF_BLOB
                         || blobType == GAIA_TIFF_BLOB)
                {
                  GridCellImage *renderer =
                    new GridCellImage(blob, blobSize, 128);
                  newGrid->SetCellRenderer(i, 0, renderer);
                  useRenderer = true;
              } else
                {
                  value = wxT("BLOB");
                }
              newGrid->SetReadOnly(i, 0);
            }
          if (pColumn->GetDataType() == SQLITE_IMAGE
              && pVar->GetType() == MY_NULL_VARIANT)
            {
              GridCellImage *renderer = new GridCellImage(128);
              newGrid->SetCellRenderer(i, 0, renderer);
              useRenderer = true;
              if (pColumn->IsNotNull() == true)
                renderer->SetError(true);
          } else if (pColumn->IsNotNull() == true
                     && pVar->GetType() == MY_NULL_VARIANT)
            newGrid->SetCellBackgroundColour(i, 0, ErrorColor);
          if (useRenderer == false)
            newGrid->SetCellValue(i, 0, value);
      } else
        {
          if (pColumn->IsNotNull() == true)
            newGrid->SetCellBackgroundColour(i, 0, ErrorColor);
        }
      if (pColumn->IsPrimaryKey() == true
          || pColumn->GetDataType() == SQLITE_BLOB
          || pColumn->GetDataType() == SQLITE_IMAGE)
        newGrid->SetReadOnly(i, 0);
      i++;
      pColumn = pColumn->GetNext();
    }

  newGrid->Show(true);
  newGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
  newGrid->AutoSize();
  GridSizer->Replace(EntityCtrl, newGrid);
  GridSizer->Layout();
  delete EntityCtrl;
  EntityCtrl = newGrid;
  GetSizer()->Fit(this);
  return;
}

void InsertEntityDialog::OnAliasSelected(wxCommandEvent & WXUNUSED(event))
{
//
// USE ALIAS changed
//
  UseAlias = AliasCtrl->GetValue();
  PrepareGrid();
}

void InsertEntityDialog::OnCellValueChanged(wxGridEvent & event)
{
//
// user changed some cell value
//
  int row = event.GetRow();
  int col = event.GetCol();
  long int_value;
  sqlite3_int64 int64_value;
  double dbl_value;
  bool bool_value;
  char dummy[128];
  wxString value = EntityCtrl->GetCellValue(row, col);
  QueryColumn *pColumn = ColumnList.Find(row);
  if (pColumn)
    {
      if (pColumn->GetDataType() == SQLITE_INTEGER)
        {
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (value.ToLong(&int_value) == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              int64_value = int_value;
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, int64_value);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              sprintf(dummy, FORMAT_64, int64_value);
              value = wxString::FromUTF8(dummy);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_FLOAT)
        {
          MainFrame->ReplaceDecimalComma(value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                  TableValues->SetValue(row, col);
                }
          } else if (value.ToDouble(&dbl_value) == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              char fmt[16];
              sprintf(fmt, "%%1.%df", pColumn->GetDecimals());
              sprintf(dummy, fmt, dbl_value);
              value = wxString::FromUTF8(dummy);
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, dbl_value);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_DATE)
        {
          strcpy(dummy, value.ToUTF8());
          bool ret = MainFrame->ConvertToJulianDate(dummy, &dbl_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (ret == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, dbl_value);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              MainFrame->ConvertFromJulianDate(dbl_value, dummy);
              value = wxString::FromUTF8(dummy);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_DATETIME)
        {
          strcpy(dummy, value.ToUTF8());
          bool ret = MainFrame->ConvertToJulianDateTime(dummy, &dbl_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (ret == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, dbl_value);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              MainFrame->ConvertFromJulianDateTime(dbl_value, dummy);
              value = wxString::FromUTF8(dummy);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_BOOLEAN)
        {
          bool ret = MainFrame->FormatBoolean(value, &bool_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else if (ret == false)
            {
              TableValues->SetError(row, col, true);
              EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              if (bool_value == true)
                {
                  TableValues->SetValue(row, col, (sqlite3_int64) 1);
                  value = wxT("TRUE");
              } else
                {
                  TableValues->SetValue(row, col, (sqlite3_int64) 0);
                  value = wxT("FALSE");
                }
              TableValues->SetError(row, col, false);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              EntityCtrl->SetCellValue(row, col, value);
            }
      } else if (pColumn->GetDataType() == SQLITE_TEXT)
        {
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(row, col, true);
                  EntityCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(row, col, false);
                  TableValues->SetValue(row, col);
                  EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
                }
          } else
            {
              wxString trunct = value.Truncate(pColumn->GetLength());
              TableValues->SetError(row, col, false);
              TableValues->SetValue(row, col, trunct);
              EntityCtrl->SetCellBackgroundColour(row, col, OkColor);
              EntityCtrl->SetCellValue(row, col, trunct);
            }
        }
    }
}

void InsertEntityDialog::OnRightClick(wxGridEvent & event)
{
//
// right click on some cell [mouse action]
//
  CurrentRow = event.GetRow();
  CurrentCol = event.GetCol();
  wxMenu *menu = new wxMenu();
  wxMenuItem *menuItem;
  wxPoint pt = event.GetPosition();
  menuItem = new wxMenuItem(menu, ID_INSERT_BLOB_IN, wxT("BLOB &import"));
  menu->Append(menuItem);
  menuItem =
    new wxMenuItem(menu, ID_INSERT_BLOB_NULL, wxT("Set BLOB as &NULL"));
  menu->Append(menuItem);
  menu->AppendSeparator();
  EntityCtrl->PopupMenu(menu, pt);
}

void InsertEntityDialog::OnCmdInsert(wxCommandEvent & WXUNUSED(event))
{
//
// Confirm - Insert Entity
//
  wxString sql;
  char xSql[1024];
  char dummy[1024];
  int len;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  bool errors = false;
  int cols = ColumnList.GetCount();
  int c;
  QueryColumn *pColumn;
  bool comma;
  int param;
  int ret;
  unsigned char *blob;
  int blob_size;
  for (c = 0; c < cols; c++)
    {
      MyVariant *pVar = TableValues->GetValue(c, 0);
      if (pVar->IsError() == true)
        errors = true;
    }
  if (errors == true)
    {
      wxString msg = wxT("Some illegal/invalid attribute value was found\n\n");
      msg += wxT("Please correct any error and then retry");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  sql = wxT("INSERT INTO \"");
  sql += TableName;
  sql += wxT("\" (");
  comma = false;
  pColumn = ColumnList.GetFirst();
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
  sql += GeometryColumn;
  sql += wxT("\"");
  pColumn = ColumnList.GetFirst();
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
  sql += wxT(") VALUES (");
  comma = false;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      // adding parameters (?)
      if (comma == false)
        comma = true;
      else
        sql += wxT(", ");
      sql += wxT("?");
      pColumn = pColumn->GetNext();
    }
  sql += wxT(", ?)");           // the Geometry column
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
  param = 1;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      // binding any Primary Key value [NULL, because we assume everyway this one has to be AUTOINCREMENT]
      if (pColumn->IsPrimaryKey() == true)
        sqlite3_bind_null(stmt, param++);
      pColumn = pColumn->GetNext();
    }
// binding the Geometry column value
  gaiaToSpatiaLiteBlobWkb(MainFrame->GetCurrentEntityGeometry(), &blob,
                          &blob_size);
  sqlite3_bind_blob(stmt, param++, blob, blob_size, free);
  c = 0;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      // binding any ordinary column value
      if (pColumn->IsPrimaryKey() == false)
        {
          MyVariant *pVar = TableValues->GetValue(c, 0);
          if (pVar->GetType() == MY_INT_VARIANT)
            sqlite3_bind_int64(stmt, param++, pVar->GetIntValue());
          else if (pVar->GetType() == MY_DBL_VARIANT)
            sqlite3_bind_double(stmt, param++, pVar->GetDblValue());
          else if (pVar->GetType() == MY_TXT_VARIANT)
            {
              MainFrame->ConvertString(pVar->GetTxtValue(), dummy, &len);
              sqlite3_bind_text(stmt, param++, dummy, len, SQLITE_TRANSIENT);
          } else if (pVar->GetType() == MY_BLOB_VARIANT)
            sqlite3_bind_blob(stmt, param++, pVar->GetBlob(),
                              pVar->GetBlobSize(), SQLITE_STATIC);
          else
            sqlite3_bind_null(stmt, param++);
        }
      c++;
      pColumn = pColumn->GetNext();
    }

  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      return;
    }

  sqlite3_finalize(stmt);
  wxDialog::EndModal(wxID_OK);
stop:
  return;
}

void InsertEntityDialog::OnCmdAbort(wxCommandEvent & WXUNUSED(event))
{
//
// Aborting
//
  wxDialog::EndModal(wxID_CANCEL);
}

void InsertEntityDialog::OnCmdBlobIn(wxCommandEvent & WXUNUSED(event))
{
//
// importing a BLOB
//
  FILE *in = NULL;
  char path[2048];
  int rd;
  int maxSize = 1024 * 1024;    // limit BLOB size to 1MB
  wxString fileList;
  unsigned char *buffer = NULL;
  int ret;
  wxString lastDir;
  bool image = false;
  wxString value;
  bool useRenderer = false;
  QueryColumn *pColumn = ColumnList.Find(CurrentRow);
  if (pColumn)
    {
      if (pColumn->GetDataType() == SQLITE_IMAGE)
        image = true;
    }
  if (image == true)
    {
      // IMAGE
      fileList =
        wxT("Image (*.jpg;*.jpeg;*.png;*.gif)|*.jpg;*.jpeg;*.png;*.gif;*.tif|");
      fileList +=
        wxT
        ("JPEG Image (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Image (*.png)|*.png|GIF Image (*.gif)|*.gif|TIFF Image (*.tif)|*.tif|");
      fileList += wxT("All files (*.*)|*.*");
  } else
    {
      // generic BLOB
      fileList =
        wxT
        ("BLOB Document (*.jpg;*.jpeg;*.png;*.gif;*.tif;*.pdf;*.zip)|*.jpg;*.jpeg;*.png;*.gif;*.tif;*.pdf;*.zip|");
      fileList +=
        wxT
        ("Image (*.jpg;*.jpeg;*.png;*.gif;*.tif)|*.jpg;*.jpeg;*.png;*.gif;*.tif|");
      fileList +=
        wxT
        ("JPEG Image (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Image (*.png)|*.png|GIF Image (*.gif)|*.gif|TIFF Image (*.tif)|*.tif|");
      fileList +=
        wxT
        ("PDF Document (*.pdf)|*.pdf|ZIP Archive|(*.zip)|All files (*.*)|*.*");
    }
  wxFileDialog fileDialog(this, wxT("loading a BLOB value"),
                          wxT(""), wxT(""), fileList,
                          wxFD_OPEN | wxFD_FILE_MUST_EXIST,
                          wxDefaultPosition, wxDefaultSize, wxT("filedlg"));
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      strcpy(path, fileDialog.GetPath().ToUTF8());
      in = fopen(path, "rb");
      if (!in)
        {
          wxMessageBox(wxT("Cannot open '") + fileDialog.GetPath() +
                       wxT("' for reading"), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          return;
        }
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      MainFrame->SetLastDirectory(lastDir);
      ::wxBeginBusyCursor();
      buffer = new unsigned char[maxSize];
      rd = fread(buffer, 1, maxSize, in);
      if (rd == maxSize && !(feof(in)))
        {
          // exceding 1MB; it's too big for a BLOB
          wxMessageBox(wxT
                       ("Selected file excedes 1MB; cowardly refusing to load it as a BLOB value ..."),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          goto end;
        }
      if (ferror(in))
        {
          // I/O error
          wxMessageBox(wxT("an I/O error occurred"), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto end;
        }
      // updating the Grid cell
      int blobType = gaiaGuessBlobType(buffer, maxSize);
      if (blobType == GAIA_GEOMETRY_BLOB)
        {
          value = wxT("GEOMETRY");
      } else if (blobType == GAIA_JPEG_BLOB
                 || blobType == GAIA_EXIF_BLOB
                 || blobType == GAIA_EXIF_GPS_BLOB
                 || blobType == GAIA_PNG_BLOB || blobType == GAIA_GIF_BLOB
                 || blobType == GAIA_TIFF_BLOB)
        {
          GridCellImage *renderer =
            (GridCellImage *) EntityCtrl->GetCellRenderer(CurrentRow,
                                                          CurrentCol);
          if (renderer == NULL)
            {
              renderer = new GridCellImage(buffer, maxSize, 128);
              EntityCtrl->SetCellRenderer(CurrentRow, CurrentCol, renderer);
          } else
            renderer->SetImage(buffer, maxSize);
          renderer->SetError(false);
          useRenderer = true;
      } else
        {
          value = wxT("BLOB");
        }
      EntityCtrl->SetReadOnly(CurrentRow, CurrentCol);
      TableValues->SetValue(CurrentRow, CurrentCol, buffer, maxSize);
      if (useRenderer == false)
        EntityCtrl->SetCellValue(CurrentRow, CurrentCol, value);
      if (image == true && useRenderer == false)
        {
          TableValues->SetError(CurrentRow, CurrentCol, true);
          EntityCtrl->SetCellBackgroundColour(CurrentRow, CurrentCol,
                                              ErrorColor);
      } else
        {
          TableValues->SetError(CurrentRow, CurrentCol, false);
          EntityCtrl->SetCellBackgroundColour(CurrentRow, CurrentCol, OkColor);
        }
      EntityCtrl->ForceRefresh();
    }
end:
// clean-up
  ::wxEndBusyCursor();
  if (in)
    fclose(in);
  if (buffer)
    delete[]buffer;
}

void InsertEntityDialog::OnCmdBlobNull(wxCommandEvent & WXUNUSED(event))
{
//
// setting a NULL BLOB
//
  QueryColumn *pColumn = ColumnList.Find(CurrentRow);
  EntityCtrl->SetReadOnly(CurrentRow, CurrentCol);
  TableValues->SetValue(CurrentRow, CurrentCol);
  GridCellImage *renderer =
    (GridCellImage *) EntityCtrl->GetCellRenderer(CurrentRow, CurrentCol);
  if (renderer != NULL)
    {
      renderer->NullImage();
      if (pColumn->IsNotNull() == true)
        renderer->SetError(true);
      EntityCtrl->ForceRefresh();
    }
}

TableDialog::~TableDialog()
{
// destructor
  Map->StopGeometryMarker();
  if (Layer)
    delete Layer;
  if (TableValues)
    delete TableValues;
  if (TableBackupValues)
    delete TableBackupValues;
}

bool TableDialog::Create(MyFrame * parent, MapLayer * layer, bool readOnly)
{
//
// creating the dialog
//
  MainFrame = parent;
  Map = MainFrame->GetMap();
  Layer = layer;
  TableName = Layer->GetTableName();
  GeometryColumn = Layer->GetGeometryColumn();
  DescName = Layer->GetDescName();
  GeometryType = Layer->GetGeometryType();
  UseAlias = true;
  RsBlock = 100;                // the ResultSet block size
  ReadOnly = readOnly;
  TableValues = NULL;
  TableBackupValues = NULL;
  OkColor = wxColour(192, 255, 192);
  ErrorColor = wxColour(255, 192, 128);
  GroupColor = wxColour(255, 255, 128);
  GroupSelection.Create(RsBlock);
  TableMetadata();
  if (wxDialog::Create(parent, wxID_ANY, wxT("DB Table")) == false)
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

void TableDialog::CreateControls()
{
//
// creating individual control and setting initial values
//
  int count;
  int i;
  QueryColumn *pColumn;
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(topSizer);
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
// First row: Layer description
  wxBoxSizer *layerBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(layerBoxSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticBox *layerBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Current Layer"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *layerSizer = new wxStaticBoxSizer(layerBox, wxVERTICAL);
  layerBoxSizer->Add(layerSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxBoxSizer *geomSizer = new wxBoxSizer(wxHORIZONTAL);
  layerSizer->Add(geomSizer, 0, wxALIGN_RIGHT | wxALL, 0);
  wxStaticText *geomLabel =
    new wxStaticText(this, wxID_STATIC, wxT("&Vector Layer:"));
  geomSizer->Add(geomLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  wxString geom = TableName + wxT(".") + GeometryColumn;
  wxTextCtrl *geomValue = new wxTextCtrl(this, wxID_ANY, geom,
                                         wxDefaultPosition, wxSize(200,
                                                                   22),
                                         wxTE_READONLY);
  geomSizer->Add(geomValue, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  wxStaticText *descLabel = new wxStaticText(this, wxID_STATIC, wxT("&Desc:"));
  geomSizer->Add(descLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  wxTextCtrl *descValue = new wxTextCtrl(this, wxID_ANY, DescName,
                                         wxDefaultPosition, wxSize(200,
                                                                   22),
                                         wxTE_READONLY);
  geomSizer->Add(descValue, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
// Second row: filter selection
  wxBoxSizer *filterBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(filterBoxSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxStaticBox *columnsBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("SelectedColumns"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *columnSizer = new wxStaticBoxSizer(columnsBox, wxVERTICAL);
  filterBoxSizer->Add(columnSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxBoxSizer *colsSizer = new wxBoxSizer(wxHORIZONTAL);
  columnSizer->Add(colsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  count = ColumnList.GetCount();
  wxString *columns = new wxString[count];
  i = 0;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      columns[i] = pColumn->GetColumn();
      i++;
      pColumn = pColumn->GetNext();
    }
  ColsCtrl = new wxListBox(this, ID_TABLE_COLUMNS,
                           wxDefaultPosition, wxSize(150, 120),
                           count, columns,
                           wxLB_HSCROLL | wxLB_NEEDED_SB | wxLB_EXTENDED);
  i = 0;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsHidden() == false)
        ColsCtrl->SetSelection(i);
      i++;
      pColumn = pColumn->GetNext();
    }
  colsSizer->Add(ColsCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
  wxStaticBox *whereBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Filter Clause"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *whereSizer = new wxStaticBoxSizer(whereBox, wxVERTICAL);
  filterBoxSizer->Add(whereSizer, 0, wxALIGN_RIGHT | wxALL, 2);
  wxBoxSizer *whereColSizer = new wxBoxSizer(wxHORIZONTAL);
  whereSizer->Add(whereColSizer, 0, wxALIGN_LEFT | wxALL, 0);
  count = ColumnList.GetCount() + 1;
  wxString *whereCols = new wxString[count];
  whereCols[0] = wxT("-- unused --");
  i = 1;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      whereCols[i] = pColumn->GetColumn();
      i++;
      pColumn = pColumn->GetNext();
    }
  WhereColCtrl =
    new wxComboBox(this, ID_TABLE_WHERE_COLUMN, wxT(""), wxDefaultPosition,
                   wxSize(180, 22), count, whereCols,
                   wxCB_DROPDOWN | wxCB_READONLY);
  WhereColCtrl->SetSelection(0);
  whereColSizer->Add(WhereColCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  wxBoxSizer *whereValSizer = new wxBoxSizer(wxHORIZONTAL);
  whereSizer->Add(whereValSizer, 0, wxALIGN_LEFT | wxALL, 0);
  WhereValCtrl =
    new wxTextCtrl(this, ID_TABLE_WHERE_VALUE, wxT(""), wxDefaultPosition,
                   wxSize(180, 22));
  whereValSizer->Add(WhereValCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  wxBoxSizer *whereModeSizer = new wxBoxSizer(wxHORIZONTAL);
  whereSizer->Add(whereModeSizer, 0, wxALIGN_LEFT | wxALL, 0);
  wxString whereModes[9];
  whereModes[0] = wxT("&=");
  whereModes[1] = wxT("&<>");
  whereModes[2] = wxT("&Like");
  whereModes[3] = wxT("&<");
  whereModes[4] = wxT("&<=");
  whereModes[5] = wxT("&IsNull");
  whereModes[6] = wxT("&>");
  whereModes[7] = wxT("&>=");
  whereModes[8] = wxT("&NotNull");
  WhereModeCtrl = new wxRadioBox(this, ID_TABLE_WHERE_MODE,
                                 wxT("Comparison operator"),
                                 wxDefaultPosition, wxDefaultSize, 9,
                                 whereModes, 3, wxRA_SPECIFY_COLS);
  WhereModeCtrl->SetSelection(0);
  whereModeSizer->Add(WhereModeCtrl, 0, wxALIGN_LEFT | wxALL, 1);
  wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);
  filterBoxSizer->Add(rightSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *orderByBox = new wxStaticBox(this, wxID_STATIC,
                                            wxT("Order By"),
                                            wxDefaultPosition,
                                            wxDefaultSize);
  wxBoxSizer *orderBySizer = new wxStaticBoxSizer(orderByBox, wxVERTICAL);
  rightSizer->Add(orderBySizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxBoxSizer *order1Sizer = new wxBoxSizer(wxHORIZONTAL);
  orderBySizer->Add(order1Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  count = ColumnList.GetCount() + 1;
  wxString *cols1 = new wxString[count];
  cols1[0] = wxT("-- unused --");
  i = 1;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      cols1[i] = pColumn->GetColumn();
      i++;
      pColumn = pColumn->GetNext();
    }
  Order1Ctrl =
    new wxComboBox(this, ID_TABLE_ORDER_BY1, wxT(""), wxDefaultPosition,
                   wxDefaultSize, count, cols1, wxCB_DROPDOWN | wxCB_READONLY);
  order1Sizer->Add(Order1Ctrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  Order1Ctrl->SetSelection(0);
  Desc1Ctrl = new wxCheckBox(this, ID_TABLE_ASC_DESC1, wxT("Z-A"));
  Desc1Ctrl->SetValue(false);
  order1Sizer->Add(Desc1Ctrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);
  wxBoxSizer *order2Sizer = new wxBoxSizer(wxHORIZONTAL);
  orderBySizer->Add(order2Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  count = ColumnList.GetCount() + 1;
  wxString *cols2 = new wxString[count];
  cols2[0] = wxT("-- unused --");
  i = 1;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      cols2[i] = pColumn->GetColumn();
      i++;
      pColumn = pColumn->GetNext();
    }
  Order2Ctrl =
    new wxComboBox(this, ID_TABLE_ORDER_BY2, wxT(""), wxDefaultPosition,
                   wxDefaultSize, count, cols2, wxCB_DROPDOWN | wxCB_READONLY);
  order2Sizer->Add(Order2Ctrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  Order2Ctrl->SetSelection(0);
  Desc2Ctrl = new wxCheckBox(this, ID_TABLE_ASC_DESC2, wxT("Z-A"));
  Desc2Ctrl->SetValue(false);
  order2Sizer->Add(Desc2Ctrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);
  wxBoxSizer *order3Sizer = new wxBoxSizer(wxHORIZONTAL);
  orderBySizer->Add(order3Sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  count = ColumnList.GetCount() + 1;
  wxString *cols3 = new wxString[count];
  cols3[0] = wxT("-- unused --");
  i = 1;
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      cols3[i] = pColumn->GetColumn();
      i++;
      pColumn = pColumn->GetNext();
    }
  Order3Ctrl =
    new wxComboBox(this, ID_TABLE_ORDER_BY3, wxT(""), wxDefaultPosition,
                   wxDefaultSize, count, cols3, wxCB_DROPDOWN | wxCB_READONLY);
  order3Sizer->Add(Order3Ctrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 1);
  Order3Ctrl->SetSelection(0);
  Desc3Ctrl = new wxCheckBox(this, ID_TABLE_ASC_DESC3, wxT("Z-A"));
  Desc3Ctrl->SetValue(false);
  order3Sizer->Add(Desc3Ctrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 3);
  wxBoxSizer *queryBox = new wxBoxSizer(wxHORIZONTAL);
  rightSizer->Add(queryBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  QueryBtn = new wxButton(this, ID_TABLE_QUERY, wxT("&Query"));
  queryBox->Add(QueryBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  wxBoxSizer *aliasBox = new wxBoxSizer(wxHORIZONTAL);
  rightSizer->Add(aliasBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  AliasCtrl = new wxCheckBox(this, ID_TABLE_ALIAS, wxT("Use alias names"));
  AliasCtrl->SetValue(UseAlias);
  aliasBox->Add(AliasCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
// Third row: Table rows
  wxBoxSizer *tableBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(tableBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  wxStaticBox *tableBox = new wxStaticBox(this, wxID_STATIC,
                                          wxT("Selected entities"),
                                          wxDefaultPosition,
                                          wxDefaultSize);
  wxBoxSizer *tableSizer = new wxStaticBoxSizer(tableBox, wxVERTICAL);
  tableBoxSizer->Add(tableSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  wxBoxSizer *rowsSizer = new wxBoxSizer(wxHORIZONTAL);
  tableSizer->Add(rowsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  GridSizer = new wxBoxSizer(wxHORIZONTAL);
  rowsSizer->Add(GridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  TableCtrl =
    new wxGrid(this, ID_TABLE_ROWS, wxDefaultPosition, wxSize(550, 300));
  TableCtrl->CreateGrid(1, 1);
  TableCtrl->SetColLabelValue(0, wxT("Attribute value"));
  TableCtrl->SetRowLabelValue(0, wxT("1"));
  TableCtrl->SetCellValue(0, 0, wxT("empty"));
  TableCtrl->SetRowLabelSize(wxGRID_AUTOSIZE);
  TableCtrl->AutoSize();
  GridSizer->Add(TableCtrl, 0, wxALIGN_RIGHT | wxALL, 2);
//  QUIT button etc
  ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
  boxSizer->Add(ButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);
  BtnRsFirst =
    new wxBitmapButton(this, ID_TABLE_RS_FIRST, wxBitmap(rs_first_on_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  BtnRsFirst->SetBitmapDisabled(wxBitmap(rs_first_off_xpm));
  BtnRsFirst->SetToolTip(wxT("ResultSet: go to first row"));
  ButtonSizer->Add(BtnRsFirst, 0, wxALIGN_LEFT | wxALL, 2);
  BtnRsPrevious =
    new wxBitmapButton(this, ID_TABLE_RS_PREVIOUS, wxBitmap(rs_previous_on_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  BtnRsPrevious->SetBitmapDisabled(wxBitmap(rs_previous_off_xpm));
  BtnRsPrevious->SetToolTip(wxT("ResultSet: go to previous block"));
  ButtonSizer->Add(BtnRsPrevious, 0, wxALIGN_LEFT | wxALL, 2);
  BtnRsRefresh =
    new wxBitmapButton(this, ID_TABLE_REFRESH, wxBitmap(refresh_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  BtnRsRefresh->SetToolTip(wxT("ResultSet: refresh"));
  ButtonSizer->Add(BtnRsRefresh, 0, wxALIGN_LEFT | wxALL, 2);
  BtnRsNext =
    new wxBitmapButton(this, ID_TABLE_RS_NEXT, wxBitmap(rs_next_on_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  BtnRsNext->SetBitmapDisabled(wxBitmap(rs_next_off_xpm));
  BtnRsNext->SetToolTip(wxT("ResultSet: go to next block"));
  ButtonSizer->Add(BtnRsNext, 0, wxALIGN_LEFT | wxALL, 2);
  BtnRsLast =
    new wxBitmapButton(this, ID_TABLE_RS_LAST, wxBitmap(rs_last_on_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  BtnRsLast->SetBitmapDisabled(wxBitmap(rs_last_off_xpm));
  BtnRsLast->SetToolTip(wxT("ResultSet: go to last row"));
  ButtonSizer->Add(BtnRsLast, 0, wxALIGN_LEFT | wxALL, 2);
  RsCurrentBlock =
    new wxStaticText(this, ID_TABLE_RS_BLOCK, wxT(""), wxDefaultPosition,
                     wxSize(200, 18));
  ButtonSizer->Add(RsCurrentBlock, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
  TopBtn =
    new wxBitmapButton(this, ID_TABLE_TOP, wxBitmap(selection_top_yes_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  TopBtn->SetBitmapDisabled(wxBitmap(selection_top_no_xpm));
  TopBtn->SetToolTip(wxT("Bring to top any selected row"));
  ButtonSizer->Add(TopBtn, 0, wxALIGN_RIGHT | wxALL, 2);
  RemoveSelBtn =
    new wxBitmapButton(this, ID_TABLE_REMOVE_SEL,
                       wxBitmap(selection_remove_xpm), wxDefaultPosition,
                       wxSize(32, 32));
  RemoveSelBtn->SetToolTip(wxT("Remove rows group selection"));
  ButtonSizer->Add(RemoveSelBtn, 0, wxALIGN_RIGHT | wxALL, 2);
  ZoomBtn =
    new wxBitmapButton(this, ID_TABLE_ZOOM, wxBitmap(zoom_in_yes_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  ZoomBtn->SetBitmapDisabled(wxBitmap(zoom_in_no_xpm));
  ZoomBtn->SetToolTip(wxT("Zoom to selected entities"));
  ButtonSizer->Add(ZoomBtn, 0, wxALIGN_RIGHT | wxALL, 2);
  SaveBtn =
    new wxBitmapButton(this, ID_TABLE_SAVE, wxBitmap(table_save_yes_xpm),
                       wxDefaultPosition, wxSize(32, 32));
  SaveBtn->SetBitmapDisabled(wxBitmap(table_save_no_xpm));
  SaveBtn->SetToolTip(wxT("Save any changed value"));
  ButtonSizer->Add(SaveBtn, 0, wxALIGN_RIGHT | wxALL, 2);
  wxButton *quitCtrl = new wxButton(this, wxID_CANCEL, wxT("&Quit"));
  ButtonSizer->Add(quitCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
// adding the event handlers
  Connect(ID_TABLE_RS_FIRST, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnRsFirst);
  Connect(ID_TABLE_RS_PREVIOUS, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnRsPrevious);
  Connect(ID_TABLE_RS_NEXT, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnRsNext);
  Connect(ID_TABLE_RS_LAST, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnRsLast);
  Connect(ID_TABLE_REFRESH, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnRefresh);
  Connect(ID_TABLE_QUERY, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnQuery);
  Connect(ID_TABLE_ZOOM, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnZoomIn);
  Connect(ID_TABLE_WHERE_MODE, wxEVT_COMMAND_RADIOBOX_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnWhereModeChanged);
  Connect(wxID_ANY, wxEVT_GRID_SELECT_CELL,
          (wxObjectEventFunction) & TableDialog::OnCellSelection);
  Connect(wxID_ANY, wxEVT_GRID_RANGE_SELECT,
          (wxObjectEventFunction) & TableDialog::OnCellRangeSelection);
  Connect(wxID_ANY, wxEVT_GRID_LABEL_LEFT_CLICK,
          (wxObjectEventFunction) & TableDialog::OnLabelSelection);
  Connect(wxID_ANY, wxEVT_GRID_LABEL_RIGHT_CLICK,
          (wxObjectEventFunction) & TableDialog::OnLabelSelection);
  Connect(wxID_ANY, wxEVT_GRID_CELL_RIGHT_CLICK,
          (wxObjectEventFunction) & TableDialog::OnRightClick);
  Connect(wxID_ANY, wxEVT_GRID_CELL_CHANGE,
          (wxObjectEventFunction) & TableDialog::OnCellChanged);
  Connect(ID_TABLE_CLEAR, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdClearSelection);
  Connect(ID_TABLE_ALL, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdSelectAll);
  Connect(ID_TABLE_ROW, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdSelectRow);
  Connect(ID_TABLE_COLUMN, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdSelectColumn);
  Connect(ID_TABLE_COPY, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdCopy);
  Connect(ID_TABLE_BLOB_IN, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdBlobIn);
  Connect(ID_TABLE_BLOB_OUT, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdBlobOut);
  Connect(ID_TABLE_BLOB_NULL, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdBlobNull);
  Connect(ID_TABLE_DELETE, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnCmdDelete);
  Connect(ID_TABLE_ALIAS, wxEVT_COMMAND_CHECKBOX_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnAliasSelected);
  Connect(ID_TABLE_SAVE, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnSave);
  Connect(ID_TABLE_TOP, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnTopSelection);
  Connect(ID_TABLE_TOP, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnTopSelection);
  Connect(ID_TABLE_REMOVE_SEL, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & TableDialog::OnRemoveSelection);
  Connect(ID_TABLE_REMOVE_SEL, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnRemoveSelection);
  Connect(wxID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED,
          (wxObjectEventFunction) & TableDialog::OnCancel);
// querying the table
  UpdateButtonStatus();
  PrepareSqlQuery();
  DoQueryTable(0);
}

void TableDialog::TableMetadata()
{
//
// retrivieng the column list for the current table
//
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  wxString sql;
  char *column;
  char *type;
  bool pk;
  wxString xColumn;
  wxString xType;
  bool noLayout;
  sql = wxT("PRAGMA table_info(\"");
  sql += TableName;
  sql += wxT("\")");
  int ret = sqlite3_get_table(MainFrame->GetSqlite(), sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  sql = wxT("");
  if (rows < 1)
    ;
  else
    {
      xColumn = wxT("ROWID");
      xType = wxT("INTEGER");
      ColumnList.Add(xColumn, xType, true);
      xColumn = wxT("GeometryType(\"") + GeometryColumn + wxT("\")");
      xType = wxT("TEXT");
      ColumnList.AddFunction(xColumn, xType);
      xColumn = wxT("Srid(\"") + GeometryColumn + wxT("\")");
      xType = wxT("INTEGER");
      ColumnList.AddFunction(xColumn, xType);
      xColumn = wxT("IsValid(\"") + GeometryColumn + wxT("\")");
      xType = wxT("INTEGER");
      ColumnList.AddFunction(xColumn, xType);
      if (GeometryType == LAYER_LINESTRING)
        {
          xColumn = wxT("GLength(\"") + GeometryColumn + wxT("\")");
          xType = wxT("DOUBLE");
          ColumnList.AddFunction(xColumn, xType);
        }
      if (GeometryType == LAYER_POLYGON)
        {
          xColumn = wxT("Area(\"") + GeometryColumn + wxT("\")");
          xType = wxT("DOUBLE");
          ColumnList.AddFunction(xColumn, xType);
          xColumn = wxT("AsText(Centroid(\"") + GeometryColumn + wxT("\"))");
          xType = wxT("TEXT");
          ColumnList.AddFunction(xColumn, xType);
          xColumn = wxT("X(Centroid(\"") + GeometryColumn + wxT("\"))");
          xType = wxT("DOUBLE");
          ColumnList.AddFunction(xColumn, xType);
          xColumn = wxT("Y(Centroid(\"") + GeometryColumn + wxT("\"))");
          xType = wxT("DOUBLE");
          ColumnList.AddFunction(xColumn, xType);
        }
      for (i = 1; i <= rows; i++)
        {
          column = results[(i * columns) + 1];
          type = results[(i * columns) + 2];
          if (atoi(results[(i * columns) + 5]) == 0)
            pk = false;
          else
            pk = true;
          xColumn = wxString::FromUTF8(column);
          xType = wxString::FromUTF8(type);
          if (xColumn == GeometryColumn)
            continue;
          if (xColumn == wxString::FromUTF8("ROWID"))
            continue;
          ColumnList.Add(xColumn, xType, pk);
        }
    }
  sqlite3_free_table(results);
// retrieving the Column defs
  noLayout = true;
  sql = wxT("SELECT column_name, desc_name, data_type, length, decimals ");
  sql += wxT("FROM layer_table_layout ");
  sql += wxT("WHERE table_name = '");
  sql += TableName;
  sql += wxT("' AND geometry_column = '");
  sql += GeometryColumn;
  sql += wxT("'");
  ret =
    sqlite3_get_table(MainFrame->GetSqlite(), sql.ToUTF8(), &results, &rows,
                      &columns, &errMsg);
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
          char *value;
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
          ColumnList.SetHints(name, desc, type, len, dec);
          noLayout = false;
        }
    }
  sqlite3_free_table(results);
  if (noLayout == true)
    {
      if (ReadOnly == true)
        {
          wxString msg =
            wxT("The layout for this DB Table has not yet been defined.\n\n");
          msg +=
            wxT
            ("In order to get a cleaner data presentation you are suggested\n");
          msg += wxT("to set up this table layout as soon as possible.\n\n");
          msg += wxT("Please, use the LayerConfiguratio/TableLayout tool");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                       this);
      } else
        {
          wxString msg =
            wxT("The layout for this DB Table has not yet been defined.\n\n");
          msg += wxT("This is not compatible with attribute editing.\n");
          msg += wxT("So, any data editing feature has been disabled.\n\n");
          msg += wxT("Please, use the LayerConfiguratio/TableLayout tool");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_EXCLAMATION,
                       this);
          ReadOnly = true;
        }
    }
}

void TableDialog::PrepareSqlQuery()
{
//
// preparing the Query SQL statement
//
  QueryColumn *pColumn;
  bool first = true;
// preparing the SELECT columns list
  SqlQuery = wxT("SELECT ");
  pColumn = ColumnList.GetFirst();
  while (pColumn)
    {
      if (pColumn->IsHidden() == true)
        {
          // skipping hidden columns
          pColumn = pColumn->GetNext();
          continue;
        }
      if (first == true)
        first = false;
      else
        SqlQuery += wxT(", ");
      if (pColumn->IsFunction() == true)
        SqlQuery += pColumn->GetColumn();
      else
        SqlQuery += wxT("\"") + pColumn->GetColumn() + wxT("\"");
      pColumn = pColumn->GetNext();
    }
  SqlQuery += wxT(" FROM \"");
  SqlQuery += TableName + wxT("\"");
  if (ColumnList.IsWhereClause() == true)
    {
      // preparing the WHERE clause
      SqlQuery += wxT(" WHERE ");
      if (IsFunction(ColumnList.GetWhereColumn()) == true)
        SqlQuery += ColumnList.GetWhereColumn();
      else
        SqlQuery += wxT("\"") + ColumnList.GetWhereColumn() + wxT("\"");
      switch (ColumnList.GetWhereCondition())
        {
          case WHERE_EQ:
            SqlQuery += wxT(" = ");
            break;
          case WHERE_NE:
            SqlQuery += wxT(" <> ");
            break;
          case WHERE_LT:
            SqlQuery += wxT(" < ");
            break;
          case WHERE_LE:
            SqlQuery += wxT(" <= ");
            break;
          case WHERE_GT:
            SqlQuery += wxT(" > ");
            break;
          case WHERE_GE:
            SqlQuery += wxT(" >= ");
            break;
          case WHERE_LIKE:
            SqlQuery += wxT(" LIKE ");
            break;
          case WHERE_IS_NULL:
            SqlQuery += wxT(" IS NULL");
            break;
          case WHERE_IS_NOT_NULL:
            SqlQuery += wxT(" IS NOT NULL");
            break;
        };
      if (ColumnList.GetWhereCondition() == WHERE_IS_NULL ||
          ColumnList.GetWhereCondition() == WHERE_IS_NOT_NULL)
        ;
      else
        {
          // formatting the comparison value
          char dummy[128];
          if (ColumnList.GetWhereType() == WHERE_INT)
            {
              sprintf(dummy, "%ld", ColumnList.GetWhereInt());
              SqlQuery += wxString::FromUTF8(dummy);
            }
          if (ColumnList.GetWhereType() == WHERE_DOUBLE)
            {
              sprintf(dummy, "%1.6f", ColumnList.GetWhereDbl());
              SqlQuery += wxString::FromUTF8(dummy);
            }
          if (ColumnList.GetWhereType() == WHERE_TEXT)
            {
              SqlQuery += wxT("'");
              if (ColumnList.GetWhereCondition() == WHERE_LIKE)
                SqlQuery += wxT("%");
              SqlQuery += ColumnList.GetWhereText();
              if (ColumnList.GetWhereCondition() == WHERE_LIKE)
                SqlQuery += wxT("%");
              SqlQuery += wxT("'");
            }
          if (ColumnList.GetWhereType() == WHERE_NONE)
            SqlQuery += wxT("''");
        }
    }
  if (ColumnList.OkOrderBy1() == true || ColumnList.OkOrderBy2() == true
      || ColumnList.OkOrderBy3() == true)
    {
      // adding an ORDER BY clause
      bool comma = false;
      SqlQuery += wxT(" ORDER BY ");
      if (ColumnList.OkOrderBy1() == true)
        {
          if (comma == false)
            comma = true;
          else
            SqlQuery += wxT(", ");
          if (IsFunction(ColumnList.GetOrderBy1()) == true)
            SqlQuery += ColumnList.GetOrderBy1();
          else
            SqlQuery += wxT("\"") + ColumnList.GetOrderBy1() + wxT("\"");
          if (ColumnList.IsAscending1() == true)
            SqlQuery += wxT(" ASC");
          else
            SqlQuery += wxT(" DESC");
        }
      if (ColumnList.OkOrderBy2() == true)
        {
          if (comma == false)
            comma = true;
          else
            SqlQuery += wxT(", ");
          if (IsFunction(ColumnList.GetOrderBy2()) == true)
            SqlQuery += ColumnList.GetOrderBy2();
          else
            SqlQuery += wxT("\"") + ColumnList.GetOrderBy2() + wxT("\"");
          if (ColumnList.IsAscending2() == true)
            SqlQuery += wxT(" ASC");
          else
            SqlQuery += wxT(" DESC");
        }
      if (ColumnList.OkOrderBy3() == true)
        {
          if (comma == false)
            comma = true;
          else
            SqlQuery += wxT(", ");
          if (IsFunction(ColumnList.GetOrderBy3()) == true)
            SqlQuery += ColumnList.GetOrderBy3();
          else
            SqlQuery += wxT("\"") + ColumnList.GetOrderBy3() + wxT("\"");
          if (ColumnList.IsAscending3() == true)
            SqlQuery += wxT(" ASC");
          else
            SqlQuery += wxT(" DESC");
        }
    }
}

bool TableDialog::IsFunction(wxString & name)
{
//
// checking if a column name corresponds to some Function
//
  QueryColumn *pColumn = ColumnList.Find(name);
  if (pColumn)
    return pColumn->IsFunction();
  return false;
}

void TableDialog::DoQueryTable(int start)
{
//
// querying the table
//
  int ret;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char dummy[1024];
  wxString value;
  int i_row;
  int i_col;
  int end_row = 0;
  wxGrid *newGrid;
  MyVariantList list;
  wxString currentBlock;
  if (TableValues)
    delete TableValues;
  if (TableBackupValues)
    delete TableBackupValues;
  TableValues = NULL;
  TableBackupValues = NULL;
  GridCellImage *renderer;
  RsBeginRow = 0;
  RsEndRow = 0;
  RsMaxRow = 0;
  ::wxBeginBusyCursor();
  GroupSelection.Reset();
  GroupSelection.RelocationReset();
  newGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(550, 300));
  newGrid->Show(false);
  MainFrame->ConvertString(SqlQuery, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
  i_row = 0;
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          int i;
          int cols = sqlite3_column_count(stmt);
          if ((i_row % 100) == 0)
            {
              sprintf(dummy, "fetching the result set: %d rows", i_row);
              currentBlock = wxString::FromUTF8(dummy);
              RsCurrentBlock->SetLabel(currentBlock);
            }
          if (i_row < start)
            {
              i_row++;
              continue;
            }
          if ((i_row - start) >= RsBlock)
            {
              i_row++;
              continue;
            }
          end_row = i_row;
          MyRowVariant *rowVariant = list.Add(cols);
          for (i = 0; i < cols; i++)
            {
              list.SetColumnName(i, sqlite3_column_name(stmt, i));
              if (sqlite3_column_type(stmt, i) == SQLITE_INTEGER)
                {
                  sqlite3_int64 int_value = sqlite3_column_int(stmt, i);
                  rowVariant->Set(i, int_value);
                }
              if (sqlite3_column_type(stmt, i) == SQLITE_FLOAT)
                {
                  double dbl_value = sqlite3_column_double(stmt, i);
                  rowVariant->Set(i, dbl_value);
                }
              if (sqlite3_column_type(stmt, i) == SQLITE_TEXT)
                {
                  const unsigned char *txt_value = sqlite3_column_text(stmt, i);
                  rowVariant->Set(i, txt_value);
                }
              if (sqlite3_column_type(stmt, i) == SQLITE_BLOB)
                {
                  unsigned char *blob =
                    (unsigned char *) sqlite3_column_blob(stmt, i);
                  int blobSize = sqlite3_column_bytes(stmt, i);
                  rowVariant->Set(i, blob, blobSize);
                }
            }
          i_row++;
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
  RsBeginRow = start;
  RsEndRow = end_row;
  RsMaxRow = i_row;

  if (list.GetRows() == 0)
    {
      //
      // this one is an EMPTY Result Set
      //
      newGrid->CreateGrid(1, 1);
      newGrid->SetColLabelValue(0, wxT("Message"));
      newGrid->SetRowLabelValue(0, wxT("Message"));
      newGrid->SetCellValue(0, 0,
                            wxT
                            ("SQL query returned an empty ResultSet\n\nThis is not an error"));
  } else
    {
      //
      // preparing the Grid to show the result set
      //
      i_row = 0;
      wxString cellValue;
      MyVariant *value;
      char dummy[256];
      wxString blobType;
      newGrid->CreateGrid(list.GetRows(), list.GetColumns());
      TableValues = new MyValues(list.GetRows(), list.GetColumns());
      TableBackupValues = new MyValues(list.GetRows(), list.GetColumns());
      if (ReadOnly == true)
        newGrid->EnableEditing(false);
      else
        newGrid->EnableEditing(true);
      newGrid->SetColLabelValue(0, wxT("ROWID"));
      for (i_col = 1; i_col < list.GetColumns(); i_col++)
        {
          wxString colName = list.GetColumnName(i_col);
          if (UseAlias == true)
            {
              // trying to use the alias nome for this Column
              QueryColumn *pColumn = ColumnList.Find(colName);
              if (pColumn)
                {
                  if (pColumn->GetDescName().Len() > 0)
                    colName = pColumn->GetDescName();
                }
            }
          newGrid->SetColLabelValue(i_col, colName);
        }
      MyRowVariant *row = list.GetFirst();
      while (row)
        {
          sprintf(dummy, "%d", i_row + RsBeginRow + 1);
          cellValue = wxString::FromUTF8(dummy);
          newGrid->SetRowLabelValue(i_row, cellValue);
          for (i_col = 0; i_col < row->GetNumCols(); i_col++)
            {
              wxString colName = list.GetColumnName(i_col);
              QueryColumn *pColumn = ColumnList.Find(colName);
              if (!pColumn)
                continue;
              value = row->GetColumn(i_col);
              if (value)
                {
                  bool useRenderer = false;
                  bool formatted = false;
                  switch (value->GetType())
                    {
                      case MY_INT_VARIANT:
                        if (pColumn->GetDataType() == SQLITE_BOOLEAN)
                          {
                            if (value->GetIntValue() == 0)
                              cellValue = wxT("FALSE");
                            else
                              cellValue = wxT("TRUE");
                            newGrid->SetCellValue(i_row, i_col, cellValue);
                        } else
                          {
                            sprintf(dummy, FORMAT_64, value->GetIntValue());
                            cellValue = wxString::FromUTF8(dummy);
                            newGrid->SetCellValue(i_row, i_col, cellValue);
                          }
                        TableValues->SetValue(i_row, i_col,
                                              value->GetIntValue());
                        TableBackupValues->SetValue(i_row, i_col,
                                                    value->GetIntValue());
                        break;
                      case MY_DBL_VARIANT:
                        if (pColumn)
                          {
                            // trying to apply Formatting Hints
                            if (pColumn->GetDataType() == SQLITE_FLOAT)
                              {
                                char fmt[16];
                                sprintf(fmt, "%%1.%df", pColumn->GetDecimals());
                                sprintf(dummy, fmt, value->GetDblValue());
                                formatted = true;
                              }
                            if (pColumn->GetDataType() == SQLITE_DATE)
                              {
                                MainFrame->ConvertFromJulianDate(value->
                                                                 GetDblValue(),
                                                                 dummy);
                                formatted = true;
                              }
                            if (pColumn->GetDataType() == SQLITE_DATETIME)
                              {
                                MainFrame->ConvertFromJulianDateTime(value->
                                                                     GetDblValue
                                                                     (), dummy);
                                formatted = true;
                              }
                          }
                        if (formatted == false)
                          sprintf(dummy, "%1.6f", value->GetDblValue());
                        cellValue = wxString::FromUTF8(dummy);
                        newGrid->SetCellValue(i_row, i_col, cellValue);
                        TableValues->SetValue(i_row, i_col,
                                              value->GetDblValue());
                        TableBackupValues->SetValue(i_row, i_col,
                                                    value->GetDblValue());
                        break;
                      case MY_TXT_VARIANT:
                        newGrid->SetCellValue(i_row, i_col,
                                              value->GetTxtValue());
                        TableValues->SetValue(i_row, i_col,
                                              value->GetTxtValue());
                        TableBackupValues->SetValue(i_row, i_col,
                                                    value->GetTxtValue());
                        break;
                      case MY_BLOB_VARIANT:
                        blobType = wxT("UNKNOWN type");
                        switch (gaiaGuessBlobType
                                (value->GetBlob(), value->GetBlobSize()))
                          {
                            case GAIA_GEOMETRY_BLOB:
                              blobType = wxT("GEOMETRY");
                              break;
                            case GAIA_JPEG_BLOB:
                            case GAIA_EXIF_BLOB:
                            case GAIA_EXIF_GPS_BLOB:
                            case GAIA_PNG_BLOB:
                            case GAIA_GIF_BLOB:
                            case GAIA_TIFF_BLOB:
                              renderer =
                                new GridCellImage(value->GetBlob(),
                                                  value->GetBlobSize(), 64);
                              newGrid->SetCellRenderer(i_row, i_col, renderer);
                              useRenderer = true;
                              break;
                            case GAIA_PDF_BLOB:
                              blobType = wxT("PDF document");
                              break;
                            case GAIA_ZIP_BLOB:
                              blobType = wxT("ZIP archive");
                              break;
                          };
                        if (useRenderer == false)
                          {
                            sprintf(dummy, "BLOB sz=%d ", value->GetBlobSize());
                            cellValue = wxString::FromUTF8(dummy);
                            cellValue += blobType;
                            newGrid->SetCellValue(i_row, i_col, cellValue);
                          }
                        newGrid->SetReadOnly(i_row, i_col);
                        TableValues->SetValue(i_row, i_col, value->GetBlob(),
                                              value->GetBlobSize());
                        TableBackupValues->SetValue(i_row, i_col,
                                                    value->GetBlob(),
                                                    value->GetBlobSize());
                        break;
                      default:
                        if (pColumn->GetDataType() == SQLITE_IMAGE)
                          {
                            renderer = new GridCellImage(64);
                            newGrid->SetCellRenderer(i_row, i_col, renderer);
                            newGrid->SetReadOnly(i_row, i_col);
                            TableValues->SetValue(i_row, i_col);
                            TableBackupValues->SetValue(i_row, i_col);
                        } else if (pColumn->GetDataType() == SQLITE_BLOB)
                          {
                            newGrid->SetReadOnly(i_row, i_col);
                            TableValues->SetValue(i_row, i_col);
                            TableBackupValues->SetValue(i_row, i_col);
                        } else
                          newGrid->SetCellValue(i_row, i_col, wxT(""));
                        break;
                    };
              } else
                {
                  newGrid->SetCellValue(i_row, i_col, wxT(""));
                  newGrid->SetReadOnly(i_row, i_col);
                  TableValues->SetValue(i_row, i_col);
                  TableBackupValues->SetValue(i_row, i_col);
                }
              if (ReadOnly == false)
                {
                  if (pColumn->IsPrimaryKey() == true)
                    newGrid->SetReadOnly(i_row, i_col);
                  if (pColumn->IsFunction() == true)
                    newGrid->SetReadOnly(i_row, i_col);
                  if (pColumn->IsBlobColumn() == true)
                    newGrid->SetReadOnly(i_row, i_col);
                }
            }
          i_row++;
          row = row->GetNext();
        }
    }
  newGrid->Show(true);
  newGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
  newGrid->AutoSize();
  GridSizer->Replace(TableCtrl, newGrid);
  GridSizer->Layout();
  delete TableCtrl;
  TableCtrl = newGrid;
  sprintf(dummy, "current block: %d / %d [%d rows]", RsBeginRow + 1,
          RsEndRow + 1, RsMaxRow);
  currentBlock = wxString::FromUTF8(dummy);
  RsCurrentBlock->SetLabel(currentBlock);
  if (RsMaxRow <= RsBlock)
    {
      // hidding the result set scrolling buttons
      BtnRsFirst->Enable(false);
      BtnRsPrevious->Enable(false);
      BtnRsNext->Enable(false);
      BtnRsLast->Enable(false);
  } else
    {
      // showing the result set scrolling buttons
      BtnRsFirst->Enable(true);
      BtnRsPrevious->Enable(true);
      BtnRsNext->Enable(true);
      BtnRsLast->Enable(true);
    }
  ::wxEndBusyCursor();
  return;

stop:
  ::wxEndBusyCursor();
  return;
}

void TableDialog::OnAliasSelected(wxCommandEvent & WXUNUSED(event))
{
//
// USE ALIAS changed
//
  UseAlias = AliasCtrl->GetValue();
}

bool TableDialog::IgnorePendingChanges()
{
//
// checking if there is any pending chages
//
  if (PendingChanges() == true)
    {
      // asking user to confirm
      wxString msg =
        wxT("Warning: uncommitted pending changes where detected.\n\n");
      msg +=
        wxT("Performing a new query without saving any pending change will\n");
      msg += wxT("cause such changes to be unrecoverably lost.\n\n");
      msg += wxT("Do you really intend perform a new query without saving ?");
      int ret =
        wxMessageBox(msg, wxT("spatialite-gis"), wxYES_NO | wxICON_QUESTION,
                     this);
      if (ret == wxYES)
        return true;
      return false;
    }
  return true;
}

void TableDialog::OnRsFirst(wxCommandEvent & WXUNUSED(event))
{
//
// scrolling to the result set beginning
//
  if (IgnorePendingChanges() == false)
    return;
  DoQueryTable(0);
  UpdateButtonStatus();
}

void TableDialog::OnRsPrevious(wxCommandEvent & WXUNUSED(event))
{
//
// scrolling to the result set previous block
//
  int start = RsBeginRow - RsBlock;
  if (start < 0)
    start = 0;
  if (IgnorePendingChanges() == false)
    return;
  DoQueryTable(start);
  UpdateButtonStatus();
}

void TableDialog::OnRsNext(wxCommandEvent & WXUNUSED(event))
{
//
// scrolling to the result set next block
//
  int start = RsEndRow + 1;
  DoQueryTable(start);
  UpdateButtonStatus();
}

void TableDialog::OnRsLast(wxCommandEvent & WXUNUSED(event))
{
//
// scrolling to the result set ending
//
  int start = RsMaxRow - RsBlock;
  if (start < 0)
    start = 0;
  DoQueryTable(start);
  UpdateButtonStatus();
}

void TableDialog::OnRefresh(wxCommandEvent & WXUNUSED(event))
{
//
// refreshing the result set
//
  int start = RsBeginRow;
  if (IgnorePendingChanges() == false)
    return;
  DoQueryTable(start);
  UpdateButtonStatus();
}

void TableDialog::OnQuery(wxCommandEvent & WXUNUSED(event))
{
//
// performing a new Query
//
  int i;
  bool mode;
  int countCols = 0;
  wxString column;
  wxString unused = wxT("-- unused --");
  int count = ColumnList.GetCount();
  if (IgnorePendingChanges() == false)
    return;
  ColumnList.ResetWhereClause();
  ColumnList.ResetOrderBy();
  ColsCtrl->Select(0);
  for (i = 0; i < count; i++)
    {
      // setting the active columns
      if (ColsCtrl->IsSelected(i) == false)
        ColumnList.SetHiddenStatus(i, true);
      else
        {
          ColumnList.SetHiddenStatus(i, false);
          countCols++;
        }
    }
  if (countCols == 0)
    {
      wxString msg = wxT("No column was selected\n\n");
      msg += wxT("You must select at least one column in order\n");
      msg += wxT("to perform a valid SQL query");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
// setting the WHERE clause
  if (WhereColCtrl->GetValue() != unused)
    {
      column = WhereColCtrl->GetValue();
      ColumnList.SetWhereColumn(column);
    }
  switch (WhereModeCtrl->GetSelection())
    {
      case 0:
        ColumnList.SetWhereCondition(WHERE_EQ);
        break;
      case 1:
        ColumnList.SetWhereCondition(WHERE_NE);
        break;
      case 2:
        ColumnList.SetWhereCondition(WHERE_LIKE);
        break;
      case 3:
        ColumnList.SetWhereCondition(WHERE_LT);
        break;
      case 4:
        ColumnList.SetWhereCondition(WHERE_LE);
        break;
      case 5:
        ColumnList.SetWhereCondition(WHERE_IS_NULL);
        break;
      case 6:
        ColumnList.SetWhereCondition(WHERE_GT);
        break;
      case 7:
        ColumnList.SetWhereCondition(WHERE_GE);
        break;
      case 8:
        ColumnList.SetWhereCondition(WHERE_IS_NOT_NULL);
        break;
      default:
        ColumnList.SetWhereCondition(WHERE_NONE);
        break;
    };
  if (ColumnList.GetWhereCondition() == WHERE_IS_NULL
      || ColumnList.GetWhereCondition() == WHERE_IS_NOT_NULL)
    ColumnList.SetWhere();
  else
    {
      // trying to check the WHERE value
      long intValue;
      double dblValue;
      wxString strValue = WhereValCtrl->GetValue();
      if (strValue.ToLong(&intValue) == true)
        {
          // this one seems to be an INTEGER value
          ColumnList.SetWhere(intValue);
      } else if (strValue.ToDouble(&dblValue) == true)
        {
          // this one seems to be a DOUBLE value
          ColumnList.SetWhere(dblValue);
      } else
        {
          // this one seems to be a TEXT value
          ColumnList.SetWhere(strValue);
        }
    }
// setting the ORDER BY clause
  if (Order1Ctrl->GetValue() != unused)
    {
      if (Desc1Ctrl->GetValue() == true)
        mode = false;
      else
        mode = true;
      column = Order1Ctrl->GetValue();
      ColumnList.SetOrderBy1(column, mode);
    }
  if (Order2Ctrl->GetValue() != unused)
    {
      if (Desc2Ctrl->GetValue() == true)
        mode = false;
      else
        mode = true;
      column = Order2Ctrl->GetValue();
      ColumnList.SetOrderBy2(column, mode);
    }
  if (Order3Ctrl->GetValue() != unused)
    {
      if (Desc3Ctrl->GetValue() == true)
        mode = false;
      else
        mode = true;
      column = Order3Ctrl->GetValue();
      ColumnList.SetOrderBy3(column, mode);
    }
  PrepareSqlQuery();
  DoQueryTable(0);
  UpdateButtonStatus();
}

void TableDialog::OnZoomIn(wxCommandEvent & WXUNUSED(event))
{
//
// performing a ZoomIn on selected entities
//
  int i_row;
  int i_col;
  int count = 0;
  wxString sql;
  int ret;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char proj_from[1024];
  char proj_to[1024];
  bool firstItem = true;
  bool reproject = false;

  Map->StopGeometryMarker();
  if (TableCtrl->IsSelection() == false)
    return;

  if (Layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (Layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && Layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(Layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += Layer->GetTableName();
              msg += wxT(".");
              msg += Layer->GetGeometryColumn();
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

  Map->FlushGeometriesToMark();
// pass I - counting how many selected entities are there
  for (i_row = 0; i_row < TableCtrl->GetNumberRows(); i_row++)
    {
      for (i_col = 0; i_col < TableCtrl->GetNumberCols(); i_col++)
        {
          if (TableCtrl->IsInSelection(i_row, i_col) == true)
            {
              count++;
              break;
            }
        }
    }
// pass II - preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += GeometryColumn;
  sql += wxT("\" FROM \"");
  sql += TableName;
  sql += wxT("\" WHERE ROWID IN (");
  for (i_row = 0; i_row < TableCtrl->GetNumberRows(); i_row++)
    {
      for (i_col = 0; i_col < TableCtrl->GetNumberCols(); i_col++)
        {
          if (TableCtrl->IsInSelection(i_row, i_col) == true)
            {
              if (firstItem == true)
                firstItem = false;
              else
                sql += wxT(", ");
              char dummy[64];
              MyVariant *pVar = TableValues->GetValue(i_row, 0);
              sprintf(dummy, FORMAT_64, pVar->GetIntValue());
              wxString id = wxString::FromUTF8(dummy);
              sql += id;
              break;
            }
        }
    }
  sql += wxT(")");
// pass III - fetching geometries
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              unsigned char *blob =
                (unsigned char *) sqlite3_column_blob(stmt, 0);
              int blobSize = sqlite3_column_bytes(stmt, 0);
              gaiaGeomCollPtr geom = NULL;
              if (reproject == true)
                {
                  // applying a reprojection
                  gaiaGeomCollPtr geom2 =
                    gaiaFromSpatiaLiteBlobWkb(blob, blobSize);
                  geom = gaiaTransform(geom2, proj_from, proj_to);
                  gaiaFreeGeomColl(geom2);
              } else
                geom = gaiaFromSpatiaLiteBlobWkb(blob, blobSize);
              if (geom)
                Map->AddGeometryToMark(geom);
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

  Map->ZoomToMarkedEntities();
  Map->StartGeometryMarker(TableName, GeometryColumn);
  return;
stop:
  Map->FlushGeometriesToMark();
}

void TableDialog::OnSave(wxCommandEvent & WXUNUSED(event))
{
//
// saving any pending change
//
  int row;
  int col;
  wxString sql;
  char xSql[1024];
  char dummy[1024];
  int len;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  sqlite3_stmt *stmt;
  QueryColumn *pColumn;
  bool comma;
  int param;
  int ret;
  int start = RsBeginRow;
  int realRow;
  wxString columnName;
  MyVariant *pVar;
  MyRowVariant *varRow;
  char *errMsg = NULL;
  bool toBeDeleted;
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
// preparing the SQL UPDATE statement
  sql = wxT("UPDATE \"");
  sql += TableName;
  sql += wxT("\" SET ");
  comma = false;
  for (col = 0; col < TableCtrl->GetNumberCols(); col++)
    {
      // adding any other ordinary column
      columnName = TableCtrl->GetColLabelValue(col);
      pColumn = ColumnList.FindAlias(columnName, UseAlias);
      if (!pColumn)
        continue;
      if (pColumn->IsPrimaryKey() == true)
        continue;
      if (pColumn->IsFunction() == true)
        continue;
      if (comma == false)
        comma = true;
      else
        sql += wxT(", ");
      sql += wxT("\"");
      sql += pColumn->GetColumn();
      sql += wxT("\" = ?");
    }
  sql += wxT(" WHERE ROWID = ?");
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      bool toBeUpdated = false;
      realRow = GroupSelection.GetBaseIndex(row);
      varRow = TableValues->GetRow(realRow);
      if (varRow->IsDeleted() == true)
        continue;
      for (col = 0; col < TableCtrl->GetNumberCols(); col++)
        {
          MyVariant *pOld = TableBackupValues->GetValue(realRow, col);
          MyVariant *pNew = TableValues->GetValue(realRow, col);
          if (pOld->Equals(pNew) == false)
            toBeUpdated = true;
        }
      if (toBeUpdated == false)
        continue;

      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      param = 1;
      for (col = 0; col < TableCtrl->GetNumberCols(); col++)
        {
          // binding any ordinary column value
          columnName = TableCtrl->GetColLabelValue(col);
          pColumn = ColumnList.FindAlias(columnName, UseAlias);
          if (!pColumn)
            continue;
          if (pColumn->IsPrimaryKey() == true)
            continue;
          if (pColumn->IsFunction() == true)
            continue;
          pVar = TableValues->GetValue(realRow, col);
          if (pVar->GetType() == MY_INT_VARIANT)
            sqlite3_bind_int64(stmt, param++, pVar->GetIntValue());
          else if (pVar->GetType() == MY_DBL_VARIANT)
            sqlite3_bind_double(stmt, param++, pVar->GetDblValue());
          else if (pVar->GetType() == MY_TXT_VARIANT)
            {
              MainFrame->ConvertString(pVar->GetTxtValue(), dummy, &len);
              sqlite3_bind_text(stmt, param++, dummy, len, SQLITE_TRANSIENT);
          } else if (pVar->GetType() == MY_BLOB_VARIANT)
            sqlite3_bind_blob(stmt, param++, pVar->GetBlob(),
                              pVar->GetBlobSize(), SQLITE_STATIC);
          else
            sqlite3_bind_null(stmt, param++);
        }
      // binding the ROWID
      pVar = TableValues->GetValue(realRow, 0);
      sqlite3_bind_int64(stmt, param++, pVar->GetIntValue());

      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          return;
        }
    }

  sqlite3_finalize(stmt);

// preparing the SQL DELETE statement
  toBeDeleted = false;
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      realRow = GroupSelection.GetBaseIndex(row);
      varRow = TableValues->GetRow(realRow);
      if (varRow->IsDeleted() == true)
        {
          toBeDeleted = true;
          break;
        }
    }
  if (toBeDeleted == true)
    {
      sql = wxT("DELETE FROM \"");
      sql += TableName;
      sql += wxT("\" WHERE ROWID = ?");
      MainFrame->ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto stop;
        }


      sqlite3_finalize(stmt);
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

  DoQueryTable(start);
  Map->PrepareMap();
  UpdateButtonStatus();
  return;
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

  DoQueryTable(start);
  Map->PrepareMap();
  UpdateButtonStatus();
  return;
}

void TableDialog::OnCancel(wxCommandEvent & WXUNUSED(event))
{
//
// quitting the dialog
//
  if (PendingChanges() == true)
    {
      wxString msg =
        wxT("Warning: uncommitted pending changes where detected.\n\n");
      msg +=
        wxT("Quitting this dialog without saving any pending change will\n");
      msg += wxT("cause such changes to be unrecoverably lost.\n\n");
      msg += wxT("Do you really intend to quit without saving ?");
      int ret =
        wxMessageBox(msg, wxT("spatialite-gis"), wxYES_NO | wxICON_QUESTION,
                     this);
      if (ret != wxYES)
        return;
    }
  wxDialog::EndModal(wxID_CANCEL);
}

void TableDialog::GroupHighlight(int row, bool mode)
{
//
// marking [or resetting] a group selection row
//
  int col;
  wxColour dfltColor = TableCtrl->GetDefaultCellBackgroundColour();
  for (col = 0; col < TableCtrl->GetNumberCols(); col++)
    {
      if (mode == true)
        TableCtrl->SetCellBackgroundColour(row, col, GroupColor);
      else
        TableCtrl->SetCellBackgroundColour(row, col, dfltColor);
    }
}

void TableDialog::OnRemoveSelection(wxCommandEvent & WXUNUSED(event))
{
//
// removing the current group selection
//
  int row;
  TableCtrl->ClearSelection();
  TableCtrl->ClearGrid();
  GroupSelection.Reset();
  GroupSelection.RelocationReset();
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      GroupHighlight(row, false);
      RelocateRow(row);
    }
  TableCtrl->ForceRefresh();
  TableCtrl->Scroll(0, 0);
  UpdateButtonStatus();
}

void TableDialog::OnTopSelection(wxCommandEvent & WXUNUSED(event))
{
//
// bringing selection on top
//
  int row;
  int col;
  int newRow = 0;
  GroupSelection.Reset();
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      // identifying any selected row
      bool okRow = false;
      for (col = 0; col < TableCtrl->GetNumberCols(); col++)
        {
          if (TableCtrl->IsInSelection(row, col) == true)
            okRow = true;
        }
      if (okRow == true)
        GroupSelection.Insert(row);
    }
  TableCtrl->ClearSelection();
  TableCtrl->ClearGrid();
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      // first step: relocating any selected row so that they will be placed on the top
      if (GroupSelection.IsSelected(row) == true)
        {
          GroupHighlight(newRow, true);
          GroupSelection.Relocate(row, newRow);
          RelocateRow(newRow);
          newRow++;
        }
    }
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      // second step: relocating any other row so that they will be placed on the bottom
      if (GroupSelection.IsSelected(row) == false)
        {
          GroupSelection.Relocate(row, newRow);
          RelocateRow(newRow);
          newRow++;
        }
    }
  TableCtrl->ForceRefresh();
  TableCtrl->Scroll(0, 0);
  UpdateButtonStatus();
}

void TableDialog::OnRightClick(wxGridEvent & event)
{
//
// right click on some cell [mouse action]
//
  MyVariant *blobVar;
  wxMenu *menu = new wxMenu();
  wxMenuItem *menuItem;
  wxPoint pt = event.GetPosition();
  CurrentEvtRow = event.GetRow();
  CurrentEvtColumn = event.GetCol();

  blobVar = TableValues->GetValue(CurrentEvtRow, CurrentEvtColumn);
  if (blobVar)
    {
      // this one is a BLOB cell
      if (ReadOnly == false)
        {
          MyRowVariant *varRow = TableValues->GetRow(CurrentEvtRow);
          if (varRow->IsDeleted() == false)
            {
              menuItem =
                new wxMenuItem(menu, ID_TABLE_DELETE, wxT("&Delete row"));
              menu->Append(menuItem);
              menu->AppendSeparator();
            }
        }
      if (gaiaGuessBlobType(blobVar->GetBlob(), blobVar->GetBlobSize()) ==
          GAIA_GEOMETRY_BLOB)
        ;
      else
        {
          if (ReadOnly == false)
            {
              menuItem =
                new wxMenuItem(menu, ID_TABLE_BLOB_IN, wxT("BLOB &import"));
              menu->Append(menuItem);
            }
          menuItem =
            new wxMenuItem(menu, ID_TABLE_BLOB_OUT, wxT("BLOB &export"));
          menu->Append(menuItem);
          if (ReadOnly == false)
            {
              menuItem =
                new wxMenuItem(menu, ID_TABLE_BLOB_NULL,
                               wxT("Set BLOB as &NULL"));
              menu->Append(menuItem);
            }
          menu->AppendSeparator();
        }
  } else
    {
      // this one is an ordinary cell
      if (ReadOnly == false)
        {
          MyRowVariant *varRow = TableValues->GetRow(CurrentEvtRow);
          if (varRow->IsDeleted() == false)
            {
              menuItem =
                new wxMenuItem(menu, ID_TABLE_DELETE, wxT("&Delete row"));
              menu->Append(menuItem);
              wxString columnName =
                TableCtrl->GetColLabelValue(CurrentEvtColumn);
              QueryColumn *pColumn = ColumnList.FindAlias(columnName, UseAlias);
              if (pColumn->IsBlobColumn() == true)
                {
                  menu->AppendSeparator();
                  menuItem =
                    new wxMenuItem(menu, ID_TABLE_BLOB_IN, wxT("BLOB &import"));
                  menu->Append(menuItem);
                }
              menu->AppendSeparator();
            }
        }
    }
  menuItem = new wxMenuItem(menu, ID_TABLE_CLEAR, wxT("&Clear selection"));
  menu->Append(menuItem);
  menuItem = new wxMenuItem(menu, ID_TABLE_ALL, wxT("Select &all"));
  menu->Append(menuItem);
  menuItem = new wxMenuItem(menu, ID_TABLE_ROW, wxT("Select &row"));
  menu->Append(menuItem);
  menuItem = new wxMenuItem(menu, ID_TABLE_COLUMN, wxT("&Select column"));
  menu->Append(menuItem);
  menu->AppendSeparator();
  menuItem = new wxMenuItem(menu, ID_TABLE_COPY, wxT("&Copy"));
  menu->Append(menuItem);
  if (TableCtrl->IsSelection() == false)
    menuItem->Enable(false);
  menu->AppendSeparator();
  if (GroupSelection.IsRelocated() == true)
    {
      menuItem =
        new wxMenuItem(menu, ID_TABLE_REMOVE_SEL,
                       wxT("&Remove rows group selection"));
      menu->Append(menuItem);
  } else
    {
      menuItem =
        new wxMenuItem(menu, ID_TABLE_TOP,
                       wxT("&Bring to top any selected row"));
      menu->Append(menuItem);
      menuItem->Enable(SelectionExists());
    }
  TableCtrl->PopupMenu(menu, pt);
  UpdateButtonStatus();
}

void TableDialog::OnLabelSelection(wxGridEvent & event)
{
//
// cell selection changed
//
  if (event.GetRow() >= 0)
    TableCtrl->SelectRow(event.GetRow());
  if (event.GetCol() >= 0)
    TableCtrl->SelectCol(event.GetCol());
  UpdateButtonStatus();
}

void TableDialog::OnCellSelection(wxGridEvent & event)
{
//
// cell selection changed
//
  event.Skip();
  UpdateButtonStatus();
}

void TableDialog::OnCellRangeSelection(wxGridRangeSelectEvent & event)
{
//
// cell selection changed
//
  event.Skip();
  UpdateButtonStatus();
}

void TableDialog::OnCellChanged(wxGridEvent & event)
{
//
// user changed value in some cell
//
  wxString value;
  int row = event.GetRow();
  int col = event.GetCol();
  long int_value;
  sqlite3_int64 int64_value;
  double dbl_value;
  bool bool_value;
  char dummy[128];
  int realRow = GroupSelection.GetBaseIndex(row);
  wxString columnName = TableCtrl->GetColLabelValue(col);
  QueryColumn *pColumn = ColumnList.FindAlias(columnName, UseAlias);
  value = TableCtrl->GetCellValue(row, col);
  if (pColumn)
    {
      if (pColumn->GetDataType() == SQLITE_INTEGER)
        {
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(realRow, col, true);
                  TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetValue(realRow, col);
                  TableValues->SetError(realRow, col, false);
                  TableCtrl->SetCellBackgroundColour(row, col, OkColor);
                  GroupReplace(row, col, pColumn->GetDataType(),
                               pColumn->GetDecimals());
                }
          } else if (value.ToLong(&int_value) == false)
            {
              TableValues->SetError(realRow, col, true);
              TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              int64_value = int_value;
              TableValues->SetValue(realRow, col, int64_value);
              TableValues->SetError(realRow, col, false);
              TableCtrl->SetCellBackgroundColour(row, col, OkColor);
              sprintf(dummy, FORMAT_64, int64_value);
              value = wxString::FromUTF8(dummy);
              TableCtrl->SetCellValue(row, col, value);
              GroupReplace(row, col, pColumn->GetDataType(),
                           pColumn->GetDecimals());
            }
      } else if (pColumn->GetDataType() == SQLITE_FLOAT)
        {
          MainFrame->ReplaceDecimalComma(value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(realRow, col, true);
                  TableValues->SetValue(realRow, col);
                  TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(realRow, col, false);
                  TableCtrl->SetCellBackgroundColour(row, col, OkColor);
                  GroupReplace(row, col, pColumn->GetDataType(),
                               pColumn->GetDecimals());
                }
          } else if (value.ToDouble(&dbl_value) == false)
            {
              TableValues->SetError(realRow, col, true);
              TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              char fmt[16];
              sprintf(fmt, "%%1.%df", pColumn->GetDecimals());
              sprintf(dummy, fmt, dbl_value);
              value = wxString::FromUTF8(dummy);
              TableValues->SetError(realRow, col, false);
              TableValues->SetValue(realRow, col, dbl_value);
              TableCtrl->SetCellBackgroundColour(row, col, OkColor);
              TableCtrl->SetCellValue(row, col, value);
              GroupReplace(row, col, pColumn->GetDataType(),
                           pColumn->GetDecimals());
            }
      } else if (pColumn->GetDataType() == SQLITE_DATE)
        {
          strcpy(dummy, value.ToUTF8());
          bool ret = MainFrame->ConvertToJulianDate(dummy, &dbl_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(realRow, col, true);
                  TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(realRow, col, false);
                  TableValues->SetValue(realRow, col);
                  TableCtrl->SetCellBackgroundColour(row, col, OkColor);
                  GroupReplace(row, col, pColumn->GetDataType(),
                               pColumn->GetDecimals());
                }
          } else if (ret == false)
            {
              TableValues->SetError(realRow, col, true);
              TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              TableValues->SetError(realRow, col, false);
              TableValues->SetValue(realRow, col, dbl_value);
              TableCtrl->SetCellBackgroundColour(row, col, OkColor);
              MainFrame->ConvertFromJulianDate(dbl_value, dummy);
              value = wxString::FromUTF8(dummy);
              TableCtrl->SetCellValue(row, col, value);
              GroupReplace(row, col, pColumn->GetDataType(),
                           pColumn->GetDecimals());
            }
      } else if (pColumn->GetDataType() == SQLITE_DATETIME)
        {
          strcpy(dummy, value.ToUTF8());
          bool ret = MainFrame->ConvertToJulianDateTime(dummy, &dbl_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(realRow, col, true);
                  TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(realRow, col, false);
                  TableValues->SetValue(realRow, col);
                  TableCtrl->SetCellBackgroundColour(row, col, OkColor);
                  GroupReplace(row, col, pColumn->GetDataType(),
                               pColumn->GetDecimals());
                }
          } else if (ret == false)
            {
              TableValues->SetError(realRow, col, true);
              TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              TableValues->SetError(realRow, col, false);
              TableValues->SetValue(realRow, col, dbl_value);
              TableCtrl->SetCellBackgroundColour(row, col, OkColor);
              MainFrame->ConvertFromJulianDateTime(dbl_value, dummy);
              value = wxString::FromUTF8(dummy);
              TableCtrl->SetCellValue(row, col, value);
              GroupReplace(row, col, pColumn->GetDataType(),
                           pColumn->GetDecimals());
            }
      } else if (pColumn->GetDataType() == SQLITE_BOOLEAN)
        {
          bool ret = MainFrame->FormatBoolean(value, &bool_value);
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(realRow, col, true);
                  TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetError(realRow, col, false);
                  TableValues->SetValue(realRow, col);
                  TableCtrl->SetCellBackgroundColour(row, col, OkColor);
                  GroupReplace(row, col, pColumn->GetDataType(),
                               pColumn->GetDecimals());
                }
          } else if (ret == false)
            {
              TableValues->SetError(realRow, col, true);
              TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
          } else
            {
              if (bool_value == true)
                {
                  TableValues->SetValue(realRow, col, (sqlite3_int64) 1);
                  value = wxT("TRUE");
              } else
                {
                  TableValues->SetValue(realRow, col, (sqlite3_int64) 0);
                  value = wxT("FALSE");
                }
              TableValues->SetError(realRow, col, false);
              TableCtrl->SetCellBackgroundColour(row, col, OkColor);
              TableCtrl->SetCellValue(row, col, value);
              GroupReplace(row, col, pColumn->GetDataType(),
                           pColumn->GetDecimals());
            }
      } else if (pColumn->GetDataType() == SQLITE_TEXT)
        {
          if (value.Len() == 0)
            {
              if (pColumn->IsNotNull() == true)
                {
                  TableValues->SetError(realRow, col, true);
                  TableCtrl->SetCellBackgroundColour(row, col, ErrorColor);
              } else
                {
                  TableValues->SetValue(realRow, col);
                  TableValues->SetError(realRow, col, false);
                  TableCtrl->SetCellBackgroundColour(row, col, OkColor);
                  GroupReplace(row, col, pColumn->GetDataType(),
                               pColumn->GetDecimals());
                }
          } else
            {
              wxString trunct = value.Truncate(pColumn->GetLength());
              TableValues->SetError(realRow, col, false);
              TableValues->SetValue(realRow, col, trunct);
              TableCtrl->SetCellBackgroundColour(row, col, OkColor);
              TableCtrl->SetCellValue(row, col, trunct);
              GroupReplace(row, col, pColumn->GetDataType(),
                           pColumn->GetDecimals());
            }
        }
    }
  UpdateButtonStatus();
}

void TableDialog::GroupReplace(int orgRow, int col, int dataType, int decimals)
{
//
// propagating a cell value on any selected cell
//
  wxString value;
  int row;
  int realRow = GroupSelection.GetBaseIndex(orgRow);
  char dummy[128];
  MyVariant *pOld = TableValues->GetValue(realRow, col);
  if (!pOld)
    return;
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      realRow = GroupSelection.GetBaseIndex(row);
      if (GroupSelection.IsSelected(realRow) == false)
        continue;
      if (row == orgRow)
        continue;
      if (dataType == SQLITE_INTEGER)
        {
          TableValues->SetValue(realRow, col, pOld->GetIntValue());
          TableValues->SetError(realRow, col, false);
          TableCtrl->SetCellBackgroundColour(row, col, OkColor);
          sprintf(dummy, FORMAT_64, pOld->GetIntValue());
          value = wxString::FromUTF8(dummy);
          TableCtrl->SetCellValue(row, col, value);
      } else if (dataType == SQLITE_FLOAT)
        {
          char fmt[16];
          sprintf(fmt, "%%1.%df", decimals);
          sprintf(dummy, fmt, pOld->GetDblValue());
          value = wxString::FromUTF8(dummy);
          TableValues->SetError(realRow, col, false);
          TableValues->SetValue(realRow, col, pOld->GetDblValue());
          TableCtrl->SetCellBackgroundColour(row, col, OkColor);
          TableCtrl->SetCellValue(row, col, value);
      } else if (dataType == SQLITE_DATE)
        {
          TableValues->SetError(realRow, col, false);
          TableValues->SetValue(realRow, col, pOld->GetDblValue());
          TableCtrl->SetCellBackgroundColour(row, col, OkColor);
          MainFrame->ConvertFromJulianDate(pOld->GetDblValue(), dummy);
          value = wxString::FromUTF8(dummy);
          TableCtrl->SetCellValue(row, col, value);
      } else if (dataType == SQLITE_DATETIME)
        {
          TableValues->SetError(realRow, col, false);
          TableValues->SetValue(realRow, col, pOld->GetDblValue());
          TableCtrl->SetCellBackgroundColour(row, col, OkColor);
          MainFrame->ConvertFromJulianDateTime(pOld->GetDblValue(), dummy);
          value = wxString::FromUTF8(dummy);
          TableCtrl->SetCellValue(row, col, value);
      } else if (dataType == SQLITE_BOOLEAN)
        {
          TableValues->SetValue(realRow, col, pOld->GetIntValue());
          if (pOld->GetIntValue() == 0)
            value = wxT("TRUE");
          else
            value = wxT("FALSE");
          TableValues->SetError(realRow, col, false);
          TableCtrl->SetCellBackgroundColour(row, col, OkColor);
          TableCtrl->SetCellValue(row, col, value);
      } else if (dataType == SQLITE_TEXT)
        {
          TableValues->SetError(realRow, col, false);
          TableValues->SetValue(realRow, col, pOld->GetTxtValue());
          TableCtrl->SetCellBackgroundColour(row, col, OkColor);
          TableCtrl->SetCellValue(row, col, pOld->GetTxtValue());
      } else
        {
          TableValues->SetError(realRow, col, false);
          TableValues->SetValue(realRow, col);
          TableCtrl->SetCellBackgroundColour(row, col, OkColor);
          TableCtrl->SetCellValue(row, col, wxT(""));
        }
    }
}

void TableDialog::RelocateRow(int newPos)
{
//
// relocating some grid row
//
  wxString value;
  int oldPos = GroupSelection.GetBaseIndex(newPos);
  int col;
  char dummy[128];
  GridCellImage *renderer;
  wxString blobType;
  for (col = 0; col < TableCtrl->GetNumberCols(); col++)
    {
      MyVariant *pVar = TableValues->GetValue(oldPos, col);
      MyVariant *pBase = TableBackupValues->GetValue(oldPos, col);
      wxString columnName = TableCtrl->GetColLabelValue(col);
      QueryColumn *pColumn = ColumnList.FindAlias(columnName, UseAlias);
      if (pColumn && pVar && pBase)
        {
          if (pVar->IsError() == true)
            TableCtrl->SetCellBackgroundColour(newPos, col, ErrorColor);
          else
            {
              if (pVar->Equals(pBase) == false)
                TableCtrl->SetCellBackgroundColour(newPos, col, OkColor);
            }
          bool useRenderer = false;
          bool formatted = false;
          switch (pVar->GetType())
            {
              case MY_INT_VARIANT:
                if (pColumn->GetDataType() == SQLITE_BOOLEAN)
                  {
                    if (pVar->GetIntValue() == 0)
                      value = wxT("FALSE");
                    else
                      value = wxT("TRUE");
                    TableCtrl->SetCellValue(newPos, col, value);
                } else
                  {
                    sprintf(dummy, FORMAT_64, pVar->GetIntValue());
                    value = wxString::FromUTF8(dummy);
                    TableCtrl->SetCellValue(newPos, col, value);
                  }
                break;
              case MY_DBL_VARIANT:
                if (pColumn)
                  {
                    // trying to apply Formatting Hints
                    if (pColumn->GetDataType() == SQLITE_FLOAT)
                      {
                        char fmt[16];
                        sprintf(fmt, "%%1.%df", pColumn->GetDecimals());
                        sprintf(dummy, fmt, pVar->GetDblValue());
                        formatted = true;
                      }
                    if (pColumn->GetDataType() == SQLITE_DATE)
                      {
                        MainFrame->ConvertFromJulianDate(pVar->GetDblValue(),
                                                         dummy);
                        formatted = true;
                      }
                    if (pColumn->GetDataType() == SQLITE_DATETIME)
                      {
                        MainFrame->ConvertFromJulianDateTime(pVar->
                                                             GetDblValue(),
                                                             dummy);
                        formatted = true;
                      }
                  }
                if (formatted == false)
                  sprintf(dummy, "%1.6f", pVar->GetDblValue());
                value = wxString::FromUTF8(dummy);
                TableCtrl->SetCellValue(newPos, col, value);
                break;
              case MY_TXT_VARIANT:
                TableCtrl->SetCellValue(newPos, col, pVar->GetTxtValue());
                break;
              case MY_BLOB_VARIANT:
                blobType = wxT("UNKNOWN type");
                switch (gaiaGuessBlobType(pVar->GetBlob(), pVar->GetBlobSize()))
                  {
                    case GAIA_GEOMETRY_BLOB:
                      blobType = wxT("GEOMETRY");
                      break;
                    case GAIA_JPEG_BLOB:
                    case GAIA_EXIF_BLOB:
                    case GAIA_EXIF_GPS_BLOB:
                    case GAIA_PNG_BLOB:
                    case GAIA_GIF_BLOB:
                    case GAIA_TIFF_BLOB:
                      renderer =
                        new GridCellImage(pVar->GetBlob(), pVar->GetBlobSize(),
                                          64);
                      TableCtrl->SetCellRenderer(newPos, col, renderer);
                      useRenderer = true;
                      break;
                    case GAIA_PDF_BLOB:
                      blobType = wxT("PDF document");
                      break;
                    case GAIA_ZIP_BLOB:
                      blobType = wxT("ZIP archive");
                      break;
                  };
                if (useRenderer == false)
                  {
                    sprintf(dummy, "BLOB sz=%d ", pVar->GetBlobSize());
                    value = wxString::FromUTF8(dummy);
                    value += blobType;
                    TableCtrl->SetCellValue(newPos, col, value);
                  }
                TableCtrl->SetReadOnly(newPos, col);
            };
      } else
        TableCtrl->SetCellValue(newPos, col, wxT("NULL"));
      if (ReadOnly == false)
        {
          if (pColumn->IsPrimaryKey() == true)
            TableCtrl->SetReadOnly(newPos, col);
          if (pColumn->IsFunction() == true)
            TableCtrl->SetReadOnly(newPos, col);
          if (pColumn->IsBlobColumn() == true)
            TableCtrl->SetReadOnly(newPos, col);
        }
    }
}

void TableDialog::OnCmdClearSelection(wxCommandEvent & WXUNUSED(event))
{
//
// clearing current selection
//
  TableCtrl->ClearSelection();
  UpdateButtonStatus();
}

void TableDialog::OnCmdSelectAll(wxCommandEvent & WXUNUSED(event))
{
//
// selecting all
//
  TableCtrl->SelectAll();
  UpdateButtonStatus();
}

void TableDialog::OnCmdSelectRow(wxCommandEvent & WXUNUSED(event))
{
//
// selecting the current row
//
  TableCtrl->SelectRow(CurrentEvtRow);
  UpdateButtonStatus();
}

void TableDialog::OnCmdSelectColumn(wxCommandEvent & WXUNUSED(event))
{
//
// selecting column
//
  TableCtrl->SelectCol(CurrentEvtColumn);
  UpdateButtonStatus();
}

void TableDialog::OnCmdCopy(wxCommandEvent & WXUNUSED(event))
{
//
// copying the selection into the clipboard
//
  wxString copyData;
  int row;
  int col;
  bool newRow;
  bool firstRow = true;
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      newRow = true;
      for (col = 0; col < TableCtrl->GetNumberCols(); col++)
        {
          if (TableCtrl->IsInSelection(row, col) == true)
            {
              // ok, this cell is included into the selection to copy
              if (firstRow == true)
                {
                  newRow = false;
                  firstRow = false;
              } else if (newRow == true)
                {
                  newRow = false;
                  copyData += wxT("\n");
              } else
                copyData += wxT("\t");
              copyData += TableCtrl->GetCellValue(row, col);
            }
        }
    }
  if (wxTheClipboard->Open())
    {
      wxTheClipboard->SetData(new wxTextDataObject(copyData));
      wxTheClipboard->Close();
    }
  UpdateButtonStatus();
}

void TableDialog::OnCmdDelete(wxCommandEvent & WXUNUSED(event))
{
//
// user required row deletion
//
  int i;
  MyRowVariant *varRow = TableValues->GetRow(CurrentEvtRow);
  if (varRow->IsDeleted() == true)
    return;
// marking row as deleted
  varRow->SetDeleted();
  for (i = 0; i < TableCtrl->GetNumberCols(); i++)
    {
      TableCtrl->SetCellTextColour(CurrentEvtRow, i, wxColour(128, 128, 128));
      TableCtrl->SetCellBackgroundColour(CurrentEvtRow, i,
                                         wxColour(64, 64, 64));
      TableCtrl->SetReadOnly(CurrentEvtRow, i);
    }
  TableCtrl->ForceRefresh();
  UpdateButtonStatus();
}

bool TableDialog::SelectionExists()
{
//
// testing if any selected cell exists
//
  int row;
  int col;
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      for (col = 0; col < TableCtrl->GetNumberCols(); col++)
        {
          if (TableCtrl->IsInSelection(row, col) == true)
            return true;
        }
    }
  return false;
}

bool TableDialog::PendingChanges()
{
//
// testing if any pending change exists
//
  int row;
  int col;
  if (TableValues == NULL || TableBackupValues == NULL)
    return false;
  for (row = 0; row < TableCtrl->GetNumberRows(); row++)
    {
      MyRowVariant *varRow = TableValues->GetRow(row);
      if (varRow->IsDeleted() == true)
        return true;
      for (col = 0; col < TableCtrl->GetNumberCols(); col++)
        {
          MyVariant *pOld = TableBackupValues->GetValue(row, col);
          MyVariant *pNew = TableValues->GetValue(row, col);
          if (pOld->Equals(pNew) == false)
            return true;
        }
    }
  return false;
}

void TableDialog::UpdateButtonStatus()
{
// updating the ZOOM IN / SELECTION ON TOP / SAVE buttons status
  if (SelectionExists() == true)
    {
      ZoomBtn->Enable(true);
      TopBtn->Enable(true);
  } else
    {
      ZoomBtn->Enable(false);
      TopBtn->Enable(false);
    }
  if (GroupSelection.IsRelocated() == true)
    {
      if (RemoveSelBtn->IsShown() == false)
        {
          TopBtn->Show(false);
          RemoveSelBtn->Show(true);
          ButtonSizer->Layout();
          GetSizer()->Fit(this);
        }
  } else
    {
      if (RemoveSelBtn->IsShown() == true)
        {
          TopBtn->Show(true);
          RemoveSelBtn->Show(false);
          ButtonSizer->Layout();
          GetSizer()->Fit(this);
        }
    }
  if (PendingChanges() == true)
    SaveBtn->Enable(true);
  else
    SaveBtn->Enable(false);
}

void TableDialog::HexBlobValue(unsigned char *blob, int size, wxString & hex)
{
//
// builds the HEX BLOB as X'01234567890abcdef'
//
  int i;
  char digit[16];
  hex = wxT("X'");
  for (i = 0; i < size; i++)
    {
      sprintf(digit, "%02x", *(blob + i));
      hex += wxString::FromUTF8(digit);
    }
  hex += wxT("'");
}

void TableDialog::OnCmdBlobIn(wxCommandEvent & WXUNUSED(event))
{
// importing an external file into a BLOB-value
  FILE *in = NULL;
  char path[2048];
  int rd;
  int maxSize = 1024 * 1024;    // limit BLOB size to 1MB
  wxString fileList;
  unsigned char *buffer = NULL;
  int ret;
  wxString lastDir;
  int realRow;
  MyVariant *pVar;
  MyVariant *pOrg;
  GridCellImage *renderer;
  QueryColumn *pColumn;
  wxString columnName;
  bool changed = false;
  bool image = false;
  wxString value;
  columnName = TableCtrl->GetColLabelValue(CurrentEvtColumn);
  pColumn = ColumnList.FindAlias(columnName, UseAlias);
  if (pColumn)
    {
      if (pColumn->GetDataType() == SQLITE_IMAGE)
        image = true;
    }
  if (image == true)
    {
      // IMAGE
      fileList =
        wxT
        ("Image (*.jpg;*.jpeg;*.png;*.gif;*.tif)|*.jpg;*.jpeg;*.png;*.gif;*.tif|");
      fileList +=
        wxT
        ("JPEG Image (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Image (*.png)|*.png|GIF Image (*.gif)|*.gif|TIFF Image (*.tif)|*.tif|");
      fileList += wxT("All files (*.*)|*.*");
  } else
    {
      // generic BLOB
      fileList =
        wxT
        ("BLOB Document (*.jpg;*.jpeg;*.png;*.gif;*.tif;*.pdf;*.zip)|*.jpg;*.jpeg;*.png;*.gif;*.tif;*.pdf;*.zip|");
      fileList +=
        wxT
        ("Image (*.jpg;*.jpeg;*.png;*.gif;*.tif)|*.jpg;*.jpeg;*.png;*.gif;*.tif|");
      fileList +=
        wxT
        ("JPEG Image (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Image (*.png)|*.png|GIF Image (*.gif)|*.gif|TIFF Image (*.tif)|*.tif|");
      fileList +=
        wxT
        ("PDF Document (*.pdf)|*.pdf|ZIP Archive|(*.zip)|All files (*.*)|*.*");
    }
  wxFileDialog fileDialog(this, wxT("loading a BLOB value"),
                          wxT(""), wxT(""), fileList,
                          wxFD_OPEN | wxFD_FILE_MUST_EXIST,
                          wxDefaultPosition, wxDefaultSize, wxT("filedlg"));
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      strcpy(path, fileDialog.GetPath().ToUTF8());
      in = fopen(path, "rb");
      if (!in)
        {
          wxMessageBox(wxT("Cannot open '") + fileDialog.GetPath() +
                       wxT("' for reading"), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          return;
        }
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      MainFrame->SetLastDirectory(lastDir);
      ::wxBeginBusyCursor();
      buffer = new unsigned char[maxSize];
      rd = fread(buffer, 1, maxSize, in);
      if (rd == maxSize && !(feof(in)))
        {
          // exceding 1MB; it's too big for a BLOB
          wxMessageBox(wxT
                       ("Selected file excedes 1MB; cowardly refusing to load it as a BLOB value ..."),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          goto end;
        }
      if (ferror(in))
        {
          // I/O error
          wxMessageBox(wxT("an I/O error occurred"), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto end;
        }
      ::wxEndBusyCursor();
      realRow = GroupSelection.GetBaseIndex(CurrentEvtRow);
      pVar = TableValues->GetValue(realRow, CurrentEvtColumn);
      pOrg = TableBackupValues->GetValue(realRow, CurrentEvtColumn);
      pVar->Set(buffer, rd);
      if (pVar->Equals(pOrg) == false)
        changed = true;
      if (pColumn->GetDataType() == SQLITE_IMAGE)
        {
          renderer =
            (GridCellImage *) TableCtrl->GetCellRenderer(CurrentEvtRow,
                                                         CurrentEvtColumn);
          if (renderer != NULL)
            {
              renderer->SetImage(buffer, rd);
              renderer->SetError(false);
              if (changed == true)
                renderer->SetChanged(true);
          } else
            {
              renderer = new GridCellImage(buffer, rd, 64);
              TableCtrl->SetCellRenderer(CurrentEvtRow, CurrentEvtColumn,
                                         renderer);
              renderer->SetError(false);
              if (changed == true)
                renderer->SetChanged(true);
            }
      } else
        {
          int blobType = gaiaGuessBlobType(buffer, maxSize);
          if (blobType == GAIA_GEOMETRY_BLOB)
            value = wxT("GEOMETRY");
          else if (blobType == GAIA_PDF_BLOB)
            value = wxT("PDF document");
          else if (blobType == GAIA_ZIP_BLOB)
            value = wxT("ZIP archive");
          else
            value = wxT("BLOB");
          TableCtrl->SetCellValue(CurrentEvtRow, CurrentEvtColumn, value);
          if (changed == true)
            TableCtrl->SetCellBackgroundColour(CurrentEvtRow, CurrentEvtColumn,
                                               OkColor);
        }
      TableCtrl->ForceRefresh();
    }
end:
// clean-up
  ::wxEndBusyCursor();
  if (in)
    fclose(in);
  if (buffer)
    delete[]buffer;
}

void TableDialog::OnCmdBlobOut(wxCommandEvent & WXUNUSED(event))
{
// exporting to external file a BLOB-value
  int blobType;
  wxString fileName;
  wxString fileType;
  int ret;
  wxString path;
  FILE *out = NULL;
  char xpath[2048];
  int wr;
  wxString lastDir;
  MyVariant *blobVar = TableValues->GetValue(CurrentEvtRow, CurrentEvtColumn);
  if (!blobVar)
    return;
  if (blobVar->GetType() != MY_BLOB_VARIANT)
    return;
  blobType = gaiaGuessBlobType(blobVar->GetBlob(), blobVar->GetBlobSize());
  switch (blobType)
    {
      case GAIA_JPEG_BLOB:
      case GAIA_EXIF_BLOB:
      case GAIA_EXIF_GPS_BLOB:
        fileName = wxT("image.jpg");
        fileType = wxT("File JPEG (*.jpg;*.jpeg)|*.jpg");
        break;
      case GAIA_PNG_BLOB:
        fileName = wxT("image.png");
        fileType = wxT("File PNG (*.png)|*.png");
        break;
      case GAIA_GIF_BLOB:
        fileName = wxT("image.gif");
        fileType = wxT("File GIF (*.gif)|*.gif");
        break;
      case GAIA_TIFF_BLOB:
        fileName = wxT("image.tif");
        fileType = wxT("File TIFF (*.tif)|*.tif");
        break;
      case GAIA_PDF_BLOB:
        fileName = wxT("document.pdf");
        fileType = wxT("PDF document (*.pdf)|*.pdf");
        break;
      case GAIA_ZIP_BLOB:
        fileName = wxT("archive.zip");
        fileType = wxT("ZIP Archive (*.zip)|*.zip");
        break;
      default:
        fileName = wxT("file");
    };
  fileType += wxT("|All files (*.*)|*.*");
  wxFileDialog fileDialog(this, wxT("exporting a BLOB value to file"),
                          wxT(""), fileName, fileType,
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition,
                          wxDefaultSize, wxT("filedlg"));
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxFileName file(fileDialog.GetPath());
      path = file.GetPath();
      path += file.GetPathSeparator();
      path += file.GetName();
      switch (blobType)
        {
          case GAIA_JPEG_BLOB:
          case GAIA_EXIF_BLOB:
          case GAIA_EXIF_GPS_BLOB:
            path += wxT(".jpg");
            break;
          case GAIA_PNG_BLOB:
            path += wxT(".png");
            break;
          case GAIA_GIF_BLOB:
            path += wxT(".gif");
            break;
          case GAIA_TIFF_BLOB:
            path += wxT(".tif");
            break;
          case GAIA_PDF_BLOB:
            path += wxT(".pdf");
            break;
          case GAIA_ZIP_BLOB:
            path += wxT(".zip");
            break;
          default:
            path += file.GetExt();
        };
      strcpy(xpath, path.ToUTF8());
      out = fopen(xpath, "wb");
      if (!out)
        {
          wxMessageBox(wxT("Cannot open '") + path + wxT("' for writing"),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          return;
        }
      lastDir = file.GetPath();
      MainFrame->SetLastDirectory(lastDir);
      ::wxBeginBusyCursor();
      wr = fwrite(blobVar->GetBlob(), 1, blobVar->GetBlobSize(), out);
      if (wr != blobVar->GetBlobSize())
        {
          wxMessageBox(wxT("an I/O error occurred"), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
        }
      fclose(out);
      ::wxEndBusyCursor();
    }
}

void TableDialog::OnCmdBlobNull(wxCommandEvent & WXUNUSED(event))
{
// setting to NULL a BLOB-value
  int realRow;
  MyVariant *pVar;
  MyVariant *pOrg;
  GridCellImage *renderer;
  QueryColumn *pColumn;
  wxString columnName;
  bool changed = false;
  realRow = GroupSelection.GetBaseIndex(CurrentEvtRow);
  pVar = TableValues->GetValue(realRow, CurrentEvtColumn);
  pOrg = TableBackupValues->GetValue(realRow, CurrentEvtColumn);
  pVar->Clear();
  if (pVar->Equals(pOrg) == false)
    changed = true;
  columnName = TableCtrl->GetColLabelValue(CurrentEvtColumn);
  pColumn = ColumnList.FindAlias(columnName, UseAlias);
  if (pColumn->GetDataType() == SQLITE_IMAGE)
    {
      renderer =
        (GridCellImage *) TableCtrl->GetCellRenderer(CurrentEvtRow,
                                                     CurrentEvtColumn);
      if (renderer != NULL)
        {
          renderer->NullImage();
          if (pColumn->IsNotNull() == true)
            renderer->SetError(true);
          else if (changed == true)
            renderer->SetChanged(true);
      } else
        {
          TableCtrl->SetCellValue(CurrentEvtRow, CurrentEvtColumn, wxT(""));
          if (pColumn->IsNotNull() == true)
            {
              pVar->SetError(true);
              TableCtrl->SetCellBackgroundColour(CurrentEvtRow,
                                                 CurrentEvtColumn, ErrorColor);
          } else if (changed == true)
            TableCtrl->SetCellBackgroundColour(CurrentEvtRow, CurrentEvtColumn,
                                               OkColor);
        }
  } else
    {
      TableCtrl->SetCellValue(CurrentEvtRow, CurrentEvtColumn, wxT(""));
      if (pColumn->IsNotNull() == true)
        {
          pVar->SetError(true);
          TableCtrl->SetCellBackgroundColour(CurrentEvtRow, CurrentEvtColumn,
                                             ErrorColor);
      } else if (changed == true)
        TableCtrl->SetCellBackgroundColour(CurrentEvtRow, CurrentEvtColumn,
                                           OkColor);
    }
  TableCtrl->ForceRefresh();
}

void TableDialog::OnWhereModeChanged(wxCommandEvent & WXUNUSED(event))
{
//
// WHERE op changed
//
  if (WhereModeCtrl->GetSelection() == 5 || WhereModeCtrl->GetSelection() == 8)
    {
      WhereValCtrl->SetValue(wxT(""));
      WhereValCtrl->Enable(false);
  } else
    WhereValCtrl->Enable(true);
}

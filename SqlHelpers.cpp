/*
/ SqlHelpers.cpp
/ SQL based methods
/
/ version 1.0, 2009 February 10
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

bool MyFrame::CheckMetadata()
{
// checks the Spatial Metadata tables for validity
  int ret;
  int i;
  char **results;
  int rows;
  int columns;
  char sql[1024];
  int spatial_type = 0;
  strcpy(sql, "SELECT CheckSpatialMetadata()");
  ret = sqlite3_get_table(SqliteHandle, sql, &results, &rows, &columns, NULL);
  if (ret != SQLITE_OK)
    goto error;
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        spatial_type = atoi(results[(i * columns) + 0]);
    }
  sqlite3_free_table(results);
  if (spatial_type == 1)
    return true;
error:
  return false;
}

void MyFrame::InitLayerTree()
{
// loads the table TREE list
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *table;
  char *geom;
  char *type;
  char *value;
  wxString tblName;
  wxString geomCol;
  bool hidden;
  bool rdOnly;
  int srid = -9999;
  int x_type = -1;
  bool multiType;
  wxString sql;
  wxString suffixNodesAuxTable = wxT(" NodesAuxTable");
  MyLayerParams *layer;
  MapView->ResetDynamics(NULL);
  EnableDrawTools();
  SetCurrentEntity(-1, NULL);

  LayerTree->Show(false);
  if (MemoryDatabase == true)
    {
      wxString memory = wxT("MEMORY-DB");
      LayerTree->SetPath(memory);
  } else
    LayerTree->SetPath(SqlitePath);
  LayerTree->FlushAll();

  LoadProjectDefs();
  AlignLayerParams();
  AlignStatistics();

  MyLayerParamsList *list = GetLayerParamsList();

// retrieving any Layer based on some plain TABLE
  sql = wxT("SELECT f_table_name, f_geometry_column, type, srid ");
  sql += wxT("FROM geometry_columns ORDER BY f_table_name, f_geometry_column");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
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
          table = results[(i * columns) + 0];
          geom = results[(i * columns) + 1];
          type = results[(i * columns) + 2];
          srid = atoi(results[(i * columns) + 3]);
          tblName = wxString::FromUTF8(table);
          geomCol = wxString::FromUTF8(geom);
          x_type = LAYER_GEOMETRY;
          multiType = false;
          if (strcasecmp(type, "POINT") == 0
              || strcasecmp(type, "MULTIPOINT") == 0)
            x_type = LAYER_POINT;
          if (strcasecmp(type, "LINESTRING") == 0
              || strcasecmp(type, "MULTILINESTRING") == 0)
            x_type = LAYER_LINESTRING;
          if (strcasecmp(type, "POLYGON") == 0
              || strcasecmp(type, "MULTIPOLYGON") == 0)
            x_type = LAYER_POLYGON;
          if (strcasecmp(type, "MULTIPOINT") == 0
              || strcasecmp(type, "MULTILINESTRING") == 0
              || strcasecmp(type, "MULTIPOLYGON") == 0)
            multiType = true;
          if (x_type == LAYER_POINT)
            {
              if (tblName.Len() > suffixNodesAuxTable.Len())
                {
                  wxString suffix = tblName.Right(suffixNodesAuxTable.Len());
                  if (suffix == suffixNodesAuxTable)
                    {
                      // ignoring any Network NodesAuxTable
                      continue;
                    }
                }
            }
          layer = list->FindRaster(tblName);
          if (layer)
            {
              layer->SetSrid(srid);
          } else
            {
              layer = list->Find(tblName, geomCol);
              if (layer)
                {
                  layer->SetGeometryType(x_type);
                  layer->SetSrid(srid);
                  layer->SetMultiType(multiType);
                  if (CheckNetwork(tblName) == true)
                    layer->SetNetwork();
                }
            }
        }
    }
  sqlite3_free_table(results);

// retrieving any Layer based on some VIEW
  sql = wxT("SELECT view_name, view_geometry, type, srid ");
  sql += wxT("FROM views_geometry_columns ");
  sql += wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
  sql +=
    wxT("JOIN spatial_ref_sys USING (srid) ORDER BY view_name, view_geometry");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
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
          table = results[(i * columns) + 0];
          geom = results[(i * columns) + 1];
          type = results[(i * columns) + 2];
          srid = atoi(results[(i * columns) + 3]);
          tblName = wxString::FromUTF8(table);
          geomCol = wxString::FromUTF8(geom);
          x_type = LAYER_GEOMETRY;
          multiType = false;
          if (strcasecmp(type, "POINT") == 0
              || strcasecmp(type, "MULTIPOINT") == 0)
            x_type = LAYER_POINT;
          if (strcasecmp(type, "LINESTRING") == 0
              || strcasecmp(type, "MULTILINESTRING") == 0)
            x_type = LAYER_LINESTRING;
          if (strcasecmp(type, "POLYGON") == 0
              || strcasecmp(type, "MULTIPOLYGON") == 0)
            x_type = LAYER_POLYGON;
          if (strcasecmp(type, "MULTIPOINT") == 0
              || strcasecmp(type, "MULTILINESTRING") == 0
              || strcasecmp(type, "MULTIPOLYGON") == 0)
            multiType = true;
          if (x_type == LAYER_POINT)
            {
              if (tblName.Len() > suffixNodesAuxTable.Len())
                {
                  wxString suffix = tblName.Right(suffixNodesAuxTable.Len());
                  if (suffix == suffixNodesAuxTable)
                    {
                      // ignoring any Network NodesAuxTable
                      continue;
                    }
                }
            }
          layer = list->Find(tblName, geomCol);
          if (layer)
            {
              layer->SetGeometryType(x_type);
              layer->SetSrid(srid);
              layer->SetMultiType(multiType);
              layer->SetLayerView();
            }
        }
    }
  sqlite3_free_table(results);

// retrieving any Layer based on some VirtualShape
  sql = wxT("SELECT virt_name, virt_geometry, type, srid ");
  sql += wxT("FROM virts_geometry_columns ");
  sql +=
    wxT("JOIN spatial_ref_sys USING (srid) ORDER BY virt_name, virt_geometry");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
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
          table = results[(i * columns) + 0];
          geom = results[(i * columns) + 1];
          type = results[(i * columns) + 2];
          srid = atoi(results[(i * columns) + 3]);
          tblName = wxString::FromUTF8(table);
          geomCol = wxString::FromUTF8(geom);
          x_type = LAYER_GEOMETRY;
          multiType = false;
          if (strcasecmp(type, "POINT") == 0
              || strcasecmp(type, "MULTIPOINT") == 0)
            x_type = LAYER_POINT;
          if (strcasecmp(type, "LINESTRING") == 0
              || strcasecmp(type, "MULTILINESTRING") == 0)
            x_type = LAYER_LINESTRING;
          if (strcasecmp(type, "POLYGON") == 0
              || strcasecmp(type, "MULTIPOLYGON") == 0)
            x_type = LAYER_POLYGON;
          if (strcasecmp(type, "MULTIPOINT") == 0
              || strcasecmp(type, "MULTILINESTRING") == 0
              || strcasecmp(type, "MULTIPOLYGON") == 0)
            multiType = true;
          if (x_type == LAYER_POINT)
            {
              if (tblName.Len() > suffixNodesAuxTable.Len())
                {
                  wxString suffix = tblName.Right(suffixNodesAuxTable.Len());
                  if (suffix == suffixNodesAuxTable)
                    {
                      // ignoring any Network NodesAuxTable
                      continue;
                    }
                }
            }
          layer = list->Find(tblName, geomCol);
          if (layer)
            {
              layer->SetGeometryType(x_type);
              layer->SetSrid(srid);
              layer->SetMultiType(multiType);
              layer->SetLayerVirtual();
            }
        }
    }
  sqlite3_free_table(results);


// retrieving any GIS Layer auth
  sql =
    wxT
    ("SELECT f_table_name, f_geometry_column, read_only, hidden FROM geometry_columns_auth");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto no_auth;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          table = results[(i * columns) + 0];
          geom = results[(i * columns) + 1];
          tblName = wxString::FromUTF8(table);
          geomCol = wxString::FromUTF8(geom);
          rdOnly = false;
          hidden = false;
          value = results[(i * columns) + 2];
          if (value)
            {
              if (atoi(value) == 0)
                rdOnly = false;
              else
                rdOnly = true;
            }
          value = results[(i * columns) + 3];
          if (value)
            {
              if (atoi(value) == 0)
                hidden = false;
              else
                hidden = true;
            }
          if (hidden == false && rdOnly == true)
            {
              layer = list->Find(tblName, geomCol);
              if (layer)
                layer->SetReadOnly();
            }
        }
    }
  sqlite3_free_table(results);

no_auth:
  layer = list->GetFirst();
  while (layer)
    {
      // feeding the Layer Tree
      LayerTree->AddLayer(layer);
      layer = layer->GetNext();
    }
  if (ProjectSrid.IsNotSet() == true)
    {
      GetSridInfo(srid);
      UpdateProjectDefs();
    }

  delete list;
  LayerTree->SetLayerIcons();
  LayerObject *obj;
  wxTreeItemId item;
  wxTreeItemIdValue cookie;
  LayerTree->ExpandAllChildren(LayerTree->GetRoot());
  item = LayerTree->GetFirstChild(LayerTree->GetRoot(), cookie);
  while (item.IsOk() == true)
    {
      // inserting a Layer
      obj = (LayerObject *) LayerTree->GetItemData(item);
      if (obj != NULL)
        {
          if (obj->IsVisible() == true)
            LayerTree->ExpandAllChildren(item);
          else
            LayerTree->CollapseAllChildren(item);
        }
      item = LayerTree->GetNextChild(LayerTree->GetRoot(), cookie);
    }
  LayerTree->Show(true);
}

MyLayerList *MyFrame::GetLayerList()
{
// building a Layer List
  int ret;
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *table;
  char *geom;
  char *value;
  wxString tblName;
  wxString geomCol;
  bool rdOnly;
  bool hidden;
  wxString sql;

  MyLayerList *list = new MyLayerList();

  sql = wxT("SELECT DISTINCT table_prefix FROM raster_pyramids");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return list;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          table = results[(i * columns) + 0];
          tblName = wxString::FromUTF8(table);
          list->Add(tblName);
        }
    }
  sqlite3_free_table(results);

// retrieving any Table-based Layer
  sql = wxT("SELECT f_table_name, f_geometry_column FROM geometry_columns");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return list;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          table = results[(i * columns) + 0];
          geom = results[(i * columns) + 1];
          tblName = wxString::FromUTF8(table);
          geomCol = wxString::FromUTF8(geom);
          if (list->ExistsRaster(tblName) == false)
            list->Add(tblName, geomCol);
        }
    }
  sqlite3_free_table(results);

// retrieving any View-based Layer
  sql = wxT("SELECT view_name, view_geometry FROM views_geometry_columns");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return list;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          table = results[(i * columns) + 0];
          geom = results[(i * columns) + 1];
          tblName = wxString::FromUTF8(table);
          geomCol = wxString::FromUTF8(geom);
          list->Add(tblName, geomCol, true, false);
        }
    }
  sqlite3_free_table(results);

// retrieving any VirtualShape-based Layer
  sql = wxT("SELECT virt_name, virt_geometry FROM virts_geometry_columns");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return list;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          table = results[(i * columns) + 0];
          geom = results[(i * columns) + 1];
          tblName = wxString::FromUTF8(table);
          geomCol = wxString::FromUTF8(geom);
          list->Add(tblName, geomCol, false, true);
        }
    }
  sqlite3_free_table(results);

// retrieving any GIS Layer auth
  sql =
    wxT
    ("SELECT f_table_name, f_geometry_column, read_only, hidden FROM geometry_columns_auth");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return list;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          table = results[(i * columns) + 0];
          geom = results[(i * columns) + 1];
          tblName = wxString::FromUTF8(table);
          geomCol = wxString::FromUTF8(geom);
          rdOnly = false;
          hidden = false;
          value = results[(i * columns) + 2];
          if (value)
            {
              if (atoi(value) == 0)
                rdOnly = false;
              else
                rdOnly = true;
            }
          value = results[(i * columns) + 3];
          if (value)
            {
              if (atoi(value) == 0)
                hidden = false;
              else
                hidden = true;
            }
          list->SetGisLayerAuth(tblName, geomCol, rdOnly, hidden);
        }
    }
  sqlite3_free_table(results);

  return list;
}

MyLayerParamsList *MyFrame::GetLayerParamsList()
{
// building a Layer Params List
  wxString sql;
  int ret;
  sqlite3_stmt *stmt;
  int int_value;
  char *str_value;
  int len;
  char xSql[1024];

  MyLayerParamsList *list = new MyLayerParamsList();

  sql =
    wxT
    ("SELECT raster_layer, table_name, geometry_column, desc_name, visible, ");
  sql += wxT("identify, reproject, label_column, always_visible, min_scale, ");
  sql += wxT("max_scale, symbol_id, foreground_color, background_color, ");
  sql += wxT("line_color, line_thickness, line_style, draw_border, to_fill, ");
  sql +=
    wxT
    ("solid_filling, fill_color, pattern_id, has_sub_classes, classify_column, ");
  sql +=
    wxT("distinct_values, num_classes, classes_min_value, classes_max_value, ");
  sql +=
    wxT
    ("classes_symbol_type, classes_min_size, classes_max_size, classes_min_color, ");
  sql += wxT("classes_max_color, network, map_labeling, label_color, ");
  sql +=
    wxT
    ("label_point_size, label_font_weight, label_font_style, label_font_underlined, ");
  sql +=
    wxT("label_font_outlined, label_order_by_column, label_order_by_desc, ");
  sql +=
    wxT
    ("label_always_visible, label_min_scale, label_max_scale, label_anti_overlap ");
  sql += wxT("FROM layer_params ORDER BY z_order DESC");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
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
          bool rasterLayer = false;
          wxString tableName;
          wxString geometryColumn;
          wxString descName;
          bool visible = true;
          bool identify = true;
          bool reproject = true;
          wxString labelColumn;
          bool alwaysVisible = true;
          int minScale = 0;
          int maxScale = 0;
          int symbolId = 1;
          wxColour foreground;
          wxColour background;
          wxColour lineColor;
          int lineThickness = 1;
          int lineStyle = wxSOLID;
          bool drawBorder = true;
          bool toFill = true;
          bool solidFilling = true;
          wxColour fillColor;
          int patternId = 1;
          bool subClasses = false;
          wxString classifyColumn;
          bool distinctValues = false;
          int numClasses = 2;
          double classesMinValue = 0.0;
          double classesMaxValue = 0.0;
          int classesSymbolType = CLASSES_SYMBOL_CIRCLE;
          int classesMinSize = 1;
          int classesMaxSize = 16;
          wxColour classesMinColor(0, 0, 0);
          wxColour classesMaxColor(255, 255, 255);
          bool network = false;
          bool mapLabeling = false;
          wxColour labelColor(0, 0, 0);
          int labelPointSize = 10;
          bool labelFontBold = false;
          bool labelFontItalic = false;
          bool labelFontUnderlined = false;
          bool labelFontOutlined = false;
          wxString labelOrderByColumn;
          bool labelOrderByDesc = false;
          bool labelAlwaysVisible = true;
          int labelMinScale = 0;
          int labelMaxScale = 0;
          bool labelAntiOverlap = false;
          if (sqlite3_column_type(stmt, 0) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 0);
              if (int_value == 0)
                rasterLayer = false;
              else
                rasterLayer = true;
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 1);
              tableName = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 2) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 2);
              geometryColumn = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 3) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 3);
              descName = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 4) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 4);
              if (int_value == 0)
                visible = false;
              else
                visible = true;
            }
          if (sqlite3_column_type(stmt, 5) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 5);
              if (int_value == 0)
                identify = false;
              else
                identify = true;
            }
          if (sqlite3_column_type(stmt, 6) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 6);
              if (int_value == 0)
                reproject = false;
              else
                reproject = true;
            }
          if (sqlite3_column_type(stmt, 7) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 7);
              labelColumn = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 8) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 8);
              if (int_value == 0)
                alwaysVisible = false;
              else
                alwaysVisible = true;
            }
          if (sqlite3_column_type(stmt, 9) == SQLITE_INTEGER)
            minScale = sqlite3_column_int(stmt, 9);
          if (sqlite3_column_type(stmt, 10) == SQLITE_INTEGER)
            maxScale = sqlite3_column_int(stmt, 10);
          if (sqlite3_column_type(stmt, 11) == SQLITE_INTEGER)
            symbolId = sqlite3_column_int(stmt, 11);
          if (sqlite3_column_type(stmt, 12) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 12);
              ColorFromRGBA(str_value, foreground);
            }
          if (sqlite3_column_type(stmt, 13) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 13);
              ColorFromRGBA(str_value, background);
            }
          if (sqlite3_column_type(stmt, 14) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 14);
              ColorFromRGBA(str_value, lineColor);
            }
          if (sqlite3_column_type(stmt, 15) == SQLITE_INTEGER)
            lineThickness = sqlite3_column_int(stmt, 15);
          if (sqlite3_column_type(stmt, 16) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 16);
              lineStyle = LineStyleFromConstant(str_value);
            }
          if (sqlite3_column_type(stmt, 17) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 17);
              if (int_value == 0)
                drawBorder = false;
              else
                drawBorder = true;
            }
          if (sqlite3_column_type(stmt, 18) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 18);
              if (int_value == 0)
                toFill = false;
              else
                toFill = true;
            }
          if (sqlite3_column_type(stmt, 19) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 19);
              if (int_value == 0)
                solidFilling = false;
              else
                solidFilling = true;
            }
          if (sqlite3_column_type(stmt, 20) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 20);
              ColorFromRGBA(str_value, fillColor);
            }
          if (sqlite3_column_type(stmt, 21) == SQLITE_INTEGER)
            patternId = sqlite3_column_int(stmt, 21);
          if (sqlite3_column_type(stmt, 22) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 22);
              if (int_value == 0)
                subClasses = false;
              else
                subClasses = true;
            }
          if (sqlite3_column_type(stmt, 23) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 23);
              classifyColumn = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 24) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 24);
              if (int_value == 0)
                distinctValues = false;
              else
                distinctValues = true;
            }
          if (sqlite3_column_type(stmt, 25) == SQLITE_INTEGER)
            numClasses = sqlite3_column_int(stmt, 25);
          if (sqlite3_column_type(stmt, 26) == SQLITE_FLOAT)
            classesMinValue = sqlite3_column_double(stmt, 26);
          if (sqlite3_column_type(stmt, 27) == SQLITE_FLOAT)
            classesMaxValue = sqlite3_column_double(stmt, 27);
          if (sqlite3_column_type(stmt, 28) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 28);
              classesSymbolType = SymbolTypeFromConstant(str_value);
            }
          if (sqlite3_column_type(stmt, 29) == SQLITE_INTEGER)
            classesMinSize = sqlite3_column_int(stmt, 29);
          if (sqlite3_column_type(stmt, 30) == SQLITE_INTEGER)
            classesMaxSize = sqlite3_column_int(stmt, 30);
          if (sqlite3_column_type(stmt, 31) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 31);
              ColorFromRGBA(str_value, classesMinColor);
            }
          if (sqlite3_column_type(stmt, 32) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 32);
              ColorFromRGBA(str_value, classesMaxColor);
            }
          if (sqlite3_column_type(stmt, 33) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 33);
              if (int_value == 0)
                network = false;
              else
                network = true;
            }
          if (sqlite3_column_type(stmt, 34) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 34);
              if (int_value == 0)
                mapLabeling = false;
              else
                mapLabeling = true;
            }
          if (sqlite3_column_type(stmt, 35) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 35);
              ColorFromRGBA(str_value, labelColor);
            }
          if (sqlite3_column_type(stmt, 36) == SQLITE_INTEGER)
            labelPointSize = sqlite3_column_int(stmt, 36);
          if (sqlite3_column_type(stmt, 37) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 37);
              if (strcasecmp(str_value, "BOLD") == 0)
                labelFontBold = true;
            }
          if (sqlite3_column_type(stmt, 38) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 38);
              if (strcasecmp(str_value, "ITALIC") == 0)
                labelFontItalic = true;
            }
          if (sqlite3_column_type(stmt, 39) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 39);
              if (int_value == 0)
                labelFontUnderlined = false;
              else
                labelFontUnderlined = true;
            }
          if (sqlite3_column_type(stmt, 40) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 40);
              if (int_value == 0)
                labelFontOutlined = false;
              else
                labelFontOutlined = true;
            }
          if (sqlite3_column_type(stmt, 41) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 41);
              labelOrderByColumn = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 42) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 42);
              if (int_value == 0)
                labelOrderByDesc = false;
              else
                labelOrderByDesc = true;
            }
          if (sqlite3_column_type(stmt, 43) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 43);
              if (int_value == 0)
                labelAlwaysVisible = false;
              else
                labelAlwaysVisible = true;
            }
          if (sqlite3_column_type(stmt, 44) == SQLITE_INTEGER)
            labelMinScale = sqlite3_column_int(stmt, 44);
          if (sqlite3_column_type(stmt, 45) == SQLITE_INTEGER)
            labelMaxScale = sqlite3_column_int(stmt, 45);
          if (sqlite3_column_type(stmt, 46) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 46);
              if (int_value == 0)
                labelAntiOverlap = false;
              else
                labelAntiOverlap = true;
            }
          if (rasterLayer == true)
            list->Add(tableName, descName, visible, alwaysVisible, minScale,
                      maxScale);
          else
            list->Add(tableName, geometryColumn, descName, network, visible,
                      identify, reproject, labelColumn, alwaysVisible, minScale,
                      maxScale, symbolId, foreground, background, lineColor,
                      lineThickness, lineStyle, drawBorder, toFill,
                      solidFilling, fillColor, patternId, subClasses,
                      classifyColumn, distinctValues, numClasses,
                      classesMinValue, classesMaxValue, classesSymbolType,
                      classesMinSize, classesMaxSize, classesMinColor,
                      classesMaxColor, mapLabeling, labelColor, labelPointSize,
                      labelFontBold, labelFontItalic, labelFontUnderlined,
                      labelFontOutlined, labelOrderByColumn, labelOrderByDesc,
                      labelAlwaysVisible, labelMinScale, labelMaxScale,
                      labelAntiOverlap);
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

// now we'll try to load the SubClasses defs
  sql =
    wxT
    ("SELECT table_name, geometry_column, range_value, is_text, text_value, ");
  sql += wxT("num_value, min_value, max_value, symbol_type, size, color ");
  sql +=
    wxT
    ("FROM layer_sub_classes ORDER BY table_name, geometry_column, class_id");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
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
          wxString tableName;
          wxString geometryColumn;
          bool rangeValue = true;
          bool isText = true;
          wxString textValue;
          double numValue = 0.0;
          double minValue = 0.0;
          double maxValue = 0.0;
          int symbolType = CLASSES_SYMBOL_CIRCLE;
          int size = 1;
          wxColour color(0, 0, 0);
          if (sqlite3_column_type(stmt, 0) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 0);
              tableName = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 1);
              geometryColumn = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 2) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 2);
              if (int_value == 0)
                rangeValue = false;
              else
                rangeValue = true;
            }
          if (sqlite3_column_type(stmt, 3) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 3);
              if (int_value == 0)
                isText = false;
              else
                isText = true;
            }
          if (sqlite3_column_type(stmt, 4) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 4);
              textValue = wxString::FromUTF8(str_value);
            }
          if (sqlite3_column_type(stmt, 5) == SQLITE_FLOAT)
            numValue = sqlite3_column_double(stmt, 5);
          if (sqlite3_column_type(stmt, 6) == SQLITE_FLOAT)
            minValue = sqlite3_column_double(stmt, 6);
          if (sqlite3_column_type(stmt, 7) == SQLITE_FLOAT)
            maxValue = sqlite3_column_double(stmt, 7);
          if (sqlite3_column_type(stmt, 8) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 8);
              symbolType = SymbolTypeFromConstant(str_value);
            }
          if (sqlite3_column_type(stmt, 9) == SQLITE_INTEGER)
            size = sqlite3_column_int(stmt, 9);
          if (sqlite3_column_type(stmt, 10) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 10);
              ColorFromRGBA(str_value, color);
            }
          list->Add(tableName, geometryColumn, rangeValue, isText, textValue,
                    numValue, minValue, maxValue, symbolType, size, color);
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);
stop:
  return list;
}

bool MyFrame::GetProjParams(int srid, char *proj_params)
{
// fetching PROJ.4 params corresponding to some SRID
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *params;
  wxString sql;
  char dummy[64];

  *proj_params = '\0';

  sql = wxT("SELECT proj4text ");
  sql += wxT("FROM spatial_ref_sys WHERE srid = ");
  sprintf(dummy, "%d", srid);
  sql += wxString::FromUTF8(dummy);
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          params = results[(i * columns) + 0];
          if (params)
            strcpy(proj_params, params);
        }
    }
  sqlite3_free_table(results);
  if (*proj_params == '\0')
    return false;
  return true;
}

void MyFrame::GetSridInfo(SridInfo * info)
{
// loads the SRID infos
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *auth_name;
  int auth_srid = -1;
  char *name;
  char *params;
  wxString authName;
  wxString sridName;
  wxString sridParams;
  wxString sql;
  char dummy[64];
  int reqSrid = info->GetSrid();
  info->Set(-1, authName, auth_srid, sridName, sridParams);
  sql = wxT("SELECT auth_name, auth_srid, ref_sys_name, proj4text ");
  sql += wxT("FROM spatial_ref_sys WHERE srid = ");
  sprintf(dummy, "%d", reqSrid);
  sql += wxString::FromUTF8(dummy);
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
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
          auth_name = results[(i * columns) + 0];
          auth_srid = atoi(results[(i * columns) + 1]);
          name = results[(i * columns) + 2];
          params = results[(i * columns) + 3];
          authName = wxString::FromUTF8(auth_name);
          sridName = wxString::FromUTF8(name);
          sridParams = wxString::FromUTF8(params);
          info->Set(reqSrid, authName, auth_srid, sridName, sridParams);
        }
    }
  sqlite3_free_table(results);
}

void MyFrame::GetSridInfo(int srid)
{
// loads the project's SRID infos
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *auth_name;
  int auth_srid = -1;
  char *name;
  char *params;
  wxString authName;
  wxString sridName;
  wxString sridParams;
  wxString sql;
  char dummy[64];

  ProjectSrid.Set(-1, authName, auth_srid, sridName, sridParams);

  sql = wxT("SELECT auth_name, auth_srid, ref_sys_name, proj4text ");
  sql += wxT("FROM spatial_ref_sys WHERE srid = ");
  sprintf(dummy, "%d", srid);
  sql += wxString::FromUTF8(dummy);
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
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
          auth_name = results[(i * columns) + 0];
          auth_srid = atoi(results[(i * columns) + 1]);
          name = results[(i * columns) + 2];
          params = results[(i * columns) + 3];
          authName = wxString::FromUTF8(auth_name);
          sridName = wxString::FromUTF8(name);
          sridParams = wxString::FromUTF8(params);
          ProjectSrid.Set(srid, authName, auth_srid, sridName, sridParams);
        }
    }
  sqlite3_free_table(results);
  UpdateReferenceSystem();
  ProjectSridChanged();
}

void MyFrame::SetProjectCrs(SridInfo & info)
{
//
// setting the Project CSR [Reference System]
  ProjectSrid.Set(info.GetSrid(), info.GetAuthName(), info.GetAuthSrid(),
                  info.GetSridName(), info.GetParams());
  ProjectSrid.ParseUnit();
  ProjectSrid.SetDms(info.IsDms());
  UpdateReferenceSystem();
  ProjectSridChanged();
}

bool MyFrame::CheckSymbolBitmaps(int *invalid)
{
//
// checking for 'symbol_bitmap' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool ok_id = false;
  bool ok_full_color = false;
  bool ok_bitmap = false;
  bool ok_hotpoint_x = false;
  bool ok_hotpoint_y = false;
  *invalid = 1;
  sql = wxT("PRAGMA table_info(symbol_bitmaps)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "symbol_id") == 0)
                ok_id = true;
              if (strcasecmp(name, "full_color") == 0)
                ok_full_color = true;
              if (strcasecmp(name, "bitmap") == 0)
                ok_bitmap = true;
              if (strcasecmp(name, "hotpoint_x") == 0)
                ok_hotpoint_x = true;
              if (strcasecmp(name, "hotpoint_y") == 0)
                ok_hotpoint_y = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    {
      *invalid = 0;
      return false;
    }
  if (ok_id == true && ok_full_color == true && ok_bitmap == true
      && ok_hotpoint_x == true && ok_hotpoint_y == true)
    {
      *invalid = 0;
      return true;
    }
  return false;
}

bool MyFrame::CheckPatternBitmaps(int *invalid)
{
//
// checking for 'pattern_bitmap' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool ok_id = false;
  bool ok_bitmap = false;
  bool ok_full_color = false;
  *invalid = 1;
  sql = wxT("PRAGMA table_info(pattern_bitmaps)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "pattern_id") == 0)
                ok_id = true;
              if (strcasecmp(name, "full_color") == 0)
                ok_full_color = true;
              if (strcasecmp(name, "bitmap") == 0)
                ok_bitmap = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    {
      *invalid = 0;
      return false;
    }
  if (ok_id == true && ok_full_color == true && ok_bitmap == true)
    {
      *invalid = 0;
      return true;
    }
  return false;
}

bool MyFrame::CheckRasterPyramids(int *invalid)
{
//
// checking for 'raster_pyramids' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okTablePrefix = false;
  bool okPixelXSize = false;
  bool okPixelYSize = false;
  bool okTileCount = false;
  *invalid = 1;
  sql = wxT("PRAGMA table_info(raster_pyramids)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "table_prefix") == 0)
                okTablePrefix = true;
              if (strcasecmp(name, "pixel_x_size") == 0)
                okPixelXSize = true;
              if (strcasecmp(name, "pixel_y_size") == 0)
                okPixelYSize = true;
              if (strcasecmp(name, "tile_count") == 0)
                okTileCount = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    {
      *invalid = 0;
      return false;
    }
  if (okTablePrefix == true && okPixelXSize == true && okPixelYSize == true
      && okTileCount == true)
    {
      *invalid = 0;
      return true;
    }
  return false;
}

bool MyFrame::CreateRasterPyramids()
{
//
// creating and initializing the 'raster_pyramids' table 
//
  int ret;
  char *errMsg = NULL;
  wxString sql;

  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// creating the Table 
//
  sql = wxT("CREATE TABLE raster_pyramids (\n");
  sql += wxT("table_prefix TEXT NOT NULL PRIMARY KEY,\n");
  sql += wxT("pixel_x_size DOUBLE NOT NULL,\n");
  sql += wxT("pixel_y_size DOUBLE NOT NULL,\n");
  sql += wxT("tile_count INTEGER NOT NULL)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  ::wxEndBusyCursor();
  return true;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
  return false;
}

void MyFrame::CheckLayerStatistics(int *invalid)
{
//
// checking for 'layer_statistics' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okRaster = false;
  bool okTable = false;
  bool okGeometry = false;
  bool okRowCount = false;
  bool okMinX = false;
  bool okMinY = false;
  bool okMaxX = false;
  bool okMaxY = false;
  *invalid = 0;
  sql = wxT("PRAGMA table_info(layer_statistics)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "raster_layer") == 0)
                okRaster = true;
              if (strcasecmp(name, "table_name") == 0)
                okTable = true;
              if (strcasecmp(name, "row_count") == 0)
                okRowCount = true;
              if (strcasecmp(name, "geometry_column") == 0)
                okGeometry = true;
              if (strcasecmp(name, "extent_min_x") == 0)
                okMinX = true;
              if (strcasecmp(name, "extent_min_y") == 0)
                okMinY = true;
              if (strcasecmp(name, "extent_max_x") == 0)
                okMaxX = true;
              if (strcasecmp(name, "extent_max_y") == 0)
                okMaxY = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    return;
  if (okRaster == true && okTable == true && okGeometry == true
      && okRowCount == true && okMinX == true && okMinY == true
      && okMaxX == true && okMaxY == true)
    return;
  *invalid = 1;
}

void MyFrame::CheckViewsLayerStatistics(int *invalid)
{
//
// checking for 'views_layer_statistics' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okTable = false;
  bool okGeometry = false;
  bool okRowCount = false;
  bool okMinX = false;
  bool okMinY = false;
  bool okMaxX = false;
  bool okMaxY = false;
  *invalid = 0;
  sql = wxT("PRAGMA table_info(views_layer_statistics)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "view_name") == 0)
                okTable = true;
              if (strcasecmp(name, "view_geometry") == 0)
                okGeometry = true;
              if (strcasecmp(name, "row_count") == 0)
                okRowCount = true;
              if (strcasecmp(name, "extent_min_x") == 0)
                okMinX = true;
              if (strcasecmp(name, "extent_min_y") == 0)
                okMinY = true;
              if (strcasecmp(name, "extent_max_x") == 0)
                okMaxX = true;
              if (strcasecmp(name, "extent_max_y") == 0)
                okMaxY = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    return;
  if (okTable == true && okGeometry == true && okRowCount == true
      && okMinX == true && okMinY == true && okMaxX == true && okMaxY == true)
    return;
  *invalid = 1;
}

void MyFrame::CheckVirtsLayerStatistics(int *invalid)
{
//
// checking for 'virts_layer_statistics' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okTable = false;
  bool okGeometry = false;
  bool okRowCount = false;
  bool okMinX = false;
  bool okMinY = false;
  bool okMaxX = false;
  bool okMaxY = false;
  *invalid = 0;
  sql = wxT("PRAGMA table_info(virts_layer_statistics)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "virt_name") == 0)
                okTable = true;
              if (strcasecmp(name, "virt_geometry") == 0)
                okGeometry = true;
              if (strcasecmp(name, "row_count") == 0)
                okRowCount = true;
              if (strcasecmp(name, "extent_min_x") == 0)
                okMinX = true;
              if (strcasecmp(name, "extent_min_y") == 0)
                okMinY = true;
              if (strcasecmp(name, "extent_max_x") == 0)
                okMaxX = true;
              if (strcasecmp(name, "extent_max_y") == 0)
                okMaxY = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    return;
  if (okTable == true && okGeometry == true && okRowCount
      && okMinX == true && okMinY == true && okMaxX == true && okMaxY == true)
    return;
  *invalid = 1;
}

bool MyFrame::CheckLayerParams(int *invalid)
{
//
// checking for 'layer_params' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okRasterLayer = false;
  bool okTableName = false;
  bool okGeometryColumn = false;
  bool okDescName = false;
  bool okNetwork = false;
  bool okVisible = false;
  bool okIdentify = false;
  bool okReproject = false;
  bool okLabelColumn = false;
  bool okAlwaysVisible = false;
  bool okMinScale = false;
  bool okMaxScale = false;
  bool okSymbolId = false;
  bool okForegroundColor = false;
  bool okBackgroundColor = false;
  bool okLineColor = false;
  bool okLineThickness = false;
  bool okLineStyle = false;
  bool okDrawBorder = false;
  bool okToFill = false;
  bool okSolidFilling = false;
  bool okFillColor = false;
  bool okPatternId = false;
  bool okZOrder = false;
  bool okHasSubClasses = false;
  bool okClassifyColumn = false;
  bool okDistinctValues = false;
  bool okNumClasses = false;
  bool okClassesMinValue = false;
  bool okClassesMaxValue = false;
  bool okClassesSymbolType = false;
  bool okClassesMinSize = false;
  bool okClassesMaxSize = false;
  bool okClassesMinColor = false;
  bool okClassesMaxColor = false;
  bool okMapLabeling = false;
  bool okLabelColor = false;
  bool okLabelPointSize = false;
  bool okLabelFontWeight = false;
  bool okLabelFontStyle = false;
  bool okLabelFontUnderlined = false;
  bool okLabelFontOutlined = false;
  bool okLabelOrderByColumn = false;
  bool okLabelOrderByDesc = false;
  bool okLabelAlwaysVisible = false;
  bool okLabelMinScale = false;
  bool okLabelMaxScale = false;
  bool okLabelAntiOverlap = false;
  *invalid = 1;
  sql = wxT("PRAGMA table_info(layer_params)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "raster_layer") == 0)
                okRasterLayer = true;
              if (strcasecmp(name, "table_name") == 0)
                okTableName = true;
              if (strcasecmp(name, "geometry_column") == 0)
                okGeometryColumn = true;
              if (strcasecmp(name, "network") == 0)
                okNetwork = true;
              if (strcasecmp(name, "desc_name") == 0)
                okDescName = true;
              if (strcasecmp(name, "visible") == 0)
                okVisible = true;
              if (strcasecmp(name, "identify") == 0)
                okIdentify = true;
              if (strcasecmp(name, "reproject") == 0)
                okReproject = true;
              if (strcasecmp(name, "label_column") == 0)
                okLabelColumn = true;
              if (strcasecmp(name, "always_visible") == 0)
                okAlwaysVisible = true;
              if (strcasecmp(name, "min_scale") == 0)
                okMinScale = true;
              if (strcasecmp(name, "max_scale") == 0)
                okMaxScale = true;
              if (strcasecmp(name, "symbol_id") == 0)
                okSymbolId = true;
              if (strcasecmp(name, "foreground_color") == 0)
                okForegroundColor = true;
              if (strcasecmp(name, "background_color") == 0)
                okBackgroundColor = true;
              if (strcasecmp(name, "line_color") == 0)
                okLineColor = true;
              if (strcasecmp(name, "line_thickness") == 0)
                okLineThickness = true;
              if (strcasecmp(name, "line_style") == 0)
                okLineStyle = true;
              if (strcasecmp(name, "draw_border") == 0)
                okDrawBorder = true;
              if (strcasecmp(name, "to_fill") == 0)
                okToFill = true;
              if (strcasecmp(name, "solid_filling") == 0)
                okSolidFilling = true;
              if (strcasecmp(name, "fill_color") == 0)
                okFillColor = true;
              if (strcasecmp(name, "pattern_id") == 0)
                okPatternId = true;
              if (strcasecmp(name, "z_order") == 0)
                okZOrder = true;
              if (strcasecmp(name, "has_sub_classes") == 0)
                okHasSubClasses = true;
              if (strcasecmp(name, "classify_column") == 0)
                okClassifyColumn = true;
              if (strcasecmp(name, "distinct_values") == 0)
                okDistinctValues = true;
              if (strcasecmp(name, "num_classes") == 0)
                okNumClasses = true;
              if (strcasecmp(name, "classes_min_value") == 0)
                okClassesMinValue = true;
              if (strcasecmp(name, "classes_max_value") == 0)
                okClassesMaxValue = true;
              if (strcasecmp(name, "classes_symbol_type") == 0)
                okClassesSymbolType = true;
              if (strcasecmp(name, "classes_min_size") == 0)
                okClassesMinSize = true;
              if (strcasecmp(name, "classes_max_size") == 0)
                okClassesMaxSize = true;
              if (strcasecmp(name, "classes_min_color") == 0)
                okClassesMinColor = true;
              if (strcasecmp(name, "classes_max_color") == 0)
                okClassesMaxColor = true;
              if (strcasecmp(name, "map_labeling") == 0)
                okMapLabeling = true;
              if (strcasecmp(name, "label_color") == 0)
                okLabelColor = true;
              if (strcasecmp(name, "label_point_size") == 0)
                okLabelPointSize = true;
              if (strcasecmp(name, "label_font_weight") == 0)
                okLabelFontWeight = true;
              if (strcasecmp(name, "label_font_style") == 0)
                okLabelFontStyle = true;
              if (strcasecmp(name, "label_font_underlined") == 0)
                okLabelFontUnderlined = true;
              if (strcasecmp(name, "label_font_outlined") == 0)
                okLabelFontOutlined = true;
              if (strcasecmp(name, "label_order_by_column") == 0)
                okLabelOrderByColumn = true;
              if (strcasecmp(name, "label_order_by_desc") == 0)
                okLabelOrderByDesc = true;
              if (strcasecmp(name, "label_always_visible") == 0)
                okLabelAlwaysVisible = true;
              if (strcasecmp(name, "label_min_scale") == 0)
                okLabelMinScale = true;
              if (strcasecmp(name, "label_max_scale") == 0)
                okLabelMaxScale = true;
              if (strcasecmp(name, "label_anti_overlap") == 0)
                okLabelAntiOverlap = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    {
      *invalid = 0;
      return false;
    }
  if (okNetwork == false && okRasterLayer == true && okTableName == true
      && okGeometryColumn == true && okDescName == true && okVisible == true
      && okIdentify == true && okReproject == true && okLabelColumn == true
      && okAlwaysVisible == true && okMinScale == true && okMaxScale == true
      && okSymbolId == true && okForegroundColor == true
      && okBackgroundColor == true && okLineColor == true
      && okLineThickness == true && okLineStyle && okDrawBorder == true
      && okToFill == true && okSolidFilling == true && okPatternId == true
      && okZOrder == true && okHasSubClasses == true && okClassifyColumn == true
      && okDistinctValues == true && okNumClasses == true
      && okClassesMinValue == true && okClassesMaxValue == true
      && okClassesSymbolType == true && okClassesMinSize == true
      && okClassesMaxSize == true && okClassesMinColor == true
      && okClassesMaxColor == true)
    {
      // adding the 'network' column
      char alter_table[128];
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN network ");
      strcat(alter_table, "INTEGER NOT NULL DEFAULT 0");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okNetwork = true;
    }
  if (okMapLabeling == false && okLabelColor == false
      && okLabelPointSize == false && okLabelFontWeight == false
      && okLabelFontStyle == false && okLabelFontUnderlined == false
      && okLabelFontOutlined == false && okLabelOrderByColumn == false
      && okLabelOrderByDesc == false && okLabelAlwaysVisible == false
      && okLabelMinScale == false && okLabelMaxScale == false
      && okLabelAntiOverlap == false && okRasterLayer == true
      && okTableName == true && okGeometryColumn == true && okDescName == true
      && okVisible == true && okIdentify == true && okReproject == true
      && okLabelColumn == true && okAlwaysVisible == true && okMinScale == true
      && okMaxScale == true && okSymbolId == true && okForegroundColor == true
      && okBackgroundColor == true && okLineColor == true
      && okLineThickness == true && okLineStyle && okDrawBorder == true
      && okToFill == true && okSolidFilling == true && okPatternId == true
      && okZOrder == true && okHasSubClasses == true && okClassifyColumn == true
      && okDistinctValues == true && okNumClasses == true
      && okClassesMinValue == true && okClassesMaxValue == true
      && okClassesSymbolType == true && okClassesMinSize == true
      && okClassesMaxSize == true && okClassesMinColor == true
      && okClassesMaxColor == true && okNetwork == true)
    {
      // adding the 'map_label' columns
      char alter_table[128];
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "map_labeling INTEGER NOT NULL DEFAULT 0");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okMapLabeling = true;
      // adding the 'label_color' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_color TEXT");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelColor = true;
      // adding the 'label_point_size' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_point_size INTEGER NOT NULL DEFAULT 0");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelPointSize = true;
      // adding the 'label_font_weight' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_font_weight TEXT");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelFontWeight = true;
      // adding the 'label_font_style' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_font_style TEXT");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelFontStyle = true;
      // adding the 'label_font_underlined' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_font_underlined INTEGER");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelFontUnderlined = true;
      // adding the 'label_font_outlined' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_font_outlined INTEGER");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelFontOutlined = true;
      // adding the 'label_order_by_column' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_order_by_column TEXT");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelOrderByColumn = true;
      // adding the 'label_order_by_desc' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_order_by_desc INTEGER NOT NULL DEFAULT 0");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelOrderByDesc = true;
      // adding the 'label_always_visible' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_always_visible INTEGER NOT NULL DEFAULT 0");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelAlwaysVisible = true;
      // adding the 'label_min_scale' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_min_scale INTEGER NOT NULL DEFAULT 0");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelMinScale = true;
      // adding the 'label_min_scale' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_max_scale INTEGER NOT NULL DEFAULT 0");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelMaxScale = true;
      // adding the 'label_min_scale' columns
      strcpy(alter_table, "ALTER TABLE layer_params ADD COLUMN ");
      strcat(alter_table, "label_anti_overlap INTEGER NOT NULL DEFAULT 0");
      ret = sqlite3_exec(SqliteHandle, alter_table, NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
      } else
        okLabelAntiOverlap = true;
    }
  if (okRasterLayer == true && okTableName == true && okGeometryColumn == true
      && okNetwork == true && okDescName == true && okVisible == true
      && okIdentify == true && okReproject == true && okLabelColumn == true
      && okAlwaysVisible == true && okMinScale == true && okMaxScale == true
      && okSymbolId == true && okForegroundColor == true
      && okBackgroundColor == true && okLineColor == true
      && okLineThickness == true && okLineStyle && okDrawBorder == true
      && okToFill == true && okSolidFilling == true && okPatternId == true
      && okZOrder == true && okHasSubClasses == true && okClassifyColumn == true
      && okDistinctValues == true && okNumClasses == true
      && okClassesMinValue == true && okClassesMaxValue == true
      && okClassesSymbolType == true && okClassesMinSize == true
      && okClassesMaxSize == true && okClassesMinColor == true
      && okClassesMaxColor == true && okMapLabeling == true
      && okLabelColor == true && okLabelPointSize == true
      && okLabelFontWeight == true && okLabelFontStyle == true
      && okLabelFontUnderlined == true && okLabelFontOutlined == true
      && okLabelOrderByColumn == true && okLabelOrderByDesc == true
      && okLabelAlwaysVisible == true && okLabelMinScale == true
      && okLabelMaxScale == true && okLabelAntiOverlap == true)
    {
      *invalid = 0;
      return true;
    }
  return false;
}

bool MyFrame::CreateLayerParams()
{
//
// creating and initializing the 'layer_params' table 
//
  int ret;
  char *errMsg = NULL;
  wxString sql;

//
// creating the Table 
//
  sql = wxT("CREATE TABLE layer_params (\n");
  sql += wxT("raster_layer INTEGER NOT NULL,\n");
  sql += wxT("table_name TEXT NOT NULL,\n");
  sql += wxT("geometry_column TEXT NOT NULL,\n");
  sql += wxT("desc_name TEXT,\n");
  sql += wxT("network INTEGER NOT NULL,\n");
  sql += wxT("visible INTEGER NOT NULL,\n");
  sql += wxT("identify INTEGER,\n");
  sql += wxT("reproject INTEGER,\n");
  sql += wxT("always_visible INTEGER NOT NULL,\n");
  sql += wxT("min_scale INTEGER NOT NULL,\n");
  sql += wxT("max_scale INTEGER NOT NULL,\n");
  sql += wxT("symbol_id INTEGER,\n");
  sql += wxT("foreground_color TEXT,\n");
  sql += wxT("background_color TEXT,\n");
  sql += wxT("line_color TEXT,\n");
  sql += wxT("line_thickness INTEGER,\n");
  sql += wxT("line_style TEXT,\n");
  sql += wxT("draw_border INTEGER,\n");
  sql += wxT("to_fill INTEGER,\n");
  sql += wxT("solid_filling INTEGER,\n");
  sql += wxT("fill_color TEXT,\n");
  sql += wxT("pattern_id INTEGER,\n");
  sql += wxT("label_column TEXT,\n");
  sql += wxT("map_labeling INTEGER NOT NULL,\n");
  sql += wxT("label_color TEXT,\n");
  sql += wxT("label_point_size INTEGER NOT NULL,\n");
  sql += wxT("label_font_weight TEXT,\n");
  sql += wxT("label_font_style TEXT,\n");
  sql += wxT("label_font_underlined INTEGER,\n");
  sql += wxT("label_font_outlined INTEGER,\n");
  sql += wxT("label_order_by_column TEXT,\n");
  sql += wxT("label_order_by_desc INTEGER NOT NULL,\n");
  sql += wxT("label_always_visible INTEGER NOT NULL,\n");
  sql += wxT("label_min_scale INTEGER NOT NULL,\n");
  sql += wxT("label_max_scale INTEGER NOT NULL,\n");
  sql += wxT("label_anti_overlap INTEGER NOT NULL,\n");
  sql += wxT("z_order INTEGER NOT NULL,\n");
  sql += wxT("has_sub_classes INTEGER NOT NULL,\n");
  sql += wxT("classify_column TEXT,\n");
  sql += wxT("distinct_values INTEGER,\n");
  sql += wxT("num_classes INTEGER,\n");
  sql += wxT("classes_min_value DOUBLE,\n");
  sql += wxT("classes_max_value DOUBLE,\n");
  sql += wxT("classes_symbol_type TEXT,\n");
  sql += wxT("classes_min_size INTEGER,\n");
  sql += wxT("classes_max_size INTEGER,\n");
  sql += wxT("classes_min_color TEXT,\n");
  sql += wxT("classes_max_color TEXT,\n");
  sql += wxT("CONSTRAINT pk_layer_params PRIMARY KEY ");
  sql += wxT("(table_name, geometry_column),\n");
  sql += wxT("CONSTRAINT fk_symbol FOREIGN KEY (symbol_id) ");
  sql += wxT("REFERENCES symbol_bitmaps (symbol_id),\n");
  sql += wxT("CONSTRAINT fk_pattern FOREIGN KEY (pattern_id) ");
  sql += wxT("REFERENCES pattern_bitmaps (pattern_id))");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  sql = wxT("CREATE INDEX idx_lp_symbol ON layer_params (symbol_id)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  sql = wxT("CREATE INDEX idx_lp_pattern ON layer_params (pattern_id)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  return true;
}

bool MyFrame::CheckLayerSubClasses(int *invalid)
{
//
// checking for 'layer_sub_classes' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okTableName = false;
  bool okGeometryColumn = false;
  bool okClassId = false;
  bool okRangeValue = false;
  bool okIsText = false;
  bool okTextValue = false;
  bool okNumValue = false;
  bool okMinValue = false;
  bool okMaxValue = false;
  bool okSymbolType = false;
  bool okSize = false;
  bool okColor = false;
  *invalid = 1;
  sql = wxT("PRAGMA table_info(layer_sub_classes)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "table_name") == 0)
                okTableName = true;
              if (strcasecmp(name, "geometry_column") == 0)
                okGeometryColumn = true;
              if (strcasecmp(name, "class_id") == 0)
                okClassId = true;
              if (strcasecmp(name, "range_value") == 0)
                okRangeValue = true;
              if (strcasecmp(name, "is_text") == 0)
                okIsText = true;
              if (strcasecmp(name, "text_value") == 0)
                okTextValue = true;
              if (strcasecmp(name, "num_value") == 0)
                okNumValue = true;
              if (strcasecmp(name, "min_value") == 0)
                okMinValue = true;
              if (strcasecmp(name, "max_value") == 0)
                okMaxValue = true;
              if (strcasecmp(name, "symbol_type") == 0)
                okSymbolType = true;
              if (strcasecmp(name, "size") == 0)
                okSize = true;
              if (strcasecmp(name, "color") == 0)
                okColor = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    {
      *invalid = 0;
      return false;
    }
  if (okTableName == true && okGeometryColumn == true && okClassId == true
      && okRangeValue == true && okIsText == true && okTextValue == true
      && okNumValue == true && okMinValue == true && okMaxValue == true
      && okSymbolType == true && okSize == true && okColor == true)
    {
      *invalid = 0;
      return true;
    }
  return false;
}

bool MyFrame::CreateLayerSubClasses()
{
//
// creating and initializing the 'layer_sub_classes' table 
//
  int ret;
  char *errMsg = NULL;
  wxString sql;

//
// creating the Table 
//
  sql = wxT("CREATE TABLE layer_sub_classes (\n");
  sql += wxT("table_name TEXT NOT NULL,\n");
  sql += wxT("geometry_column TEXT NOT NULL,\n");
  sql += wxT("class_id INTEGER NOT NULL,\n");
  sql += wxT("range_value INTEGER NOT NULL,\n");
  sql += wxT("is_text INTEGER NOT NULL,\n");
  sql += wxT("text_value TEXT,\n");
  sql += wxT("num_value DOUBLE,\n");
  sql += wxT("min_value DOUBLE,\n");
  sql += wxT("max_value DOUBLE,\n");
  sql += wxT("symbol_type TEXT,\n");
  sql += wxT("size INTEGER,\n");
  sql += wxT("color TEXT NOT NULL,\n");
  sql += wxT("CONSTRAINT pk_layer_sub_classes PRIMARY KEY ");
  sql += wxT("(table_name, geometry_column, class_id),\n");
  sql += wxT("CONSTRAINT fk_layer_sub_classes FOREIGN KEY ");
  sql += wxT("(table_name, geometry_column) REFERENCES ");
  sql += wxT("layer_params (table_name, geometry_column) ");
  sql += wxT("ON DELETE CASCADE)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  return true;
}

bool MyFrame::CheckNetwork(wxString & table)
{
//
// checking if a corresponding VirtualNetwork exists
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okArcRowid = false;
  bool okNodeFrom = false;
  bool okNodeTo = false;
  bool okCost = false;
  bool okGeometry = false;
  sql = wxT("PRAGMA table_info(\"");
  sql += table;
  sql += wxT("_net\")");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "ArcRowid") == 0)
                okArcRowid = true;
              if (strcasecmp(name, "NodeFrom") == 0)
                okNodeFrom = true;
              if (strcasecmp(name, "NodeTo") == 0)
                okNodeTo = true;
              if (strcasecmp(name, "Cost") == 0)
                okCost = true;
              if (strcasecmp(name, "Geometry") == 0)
                okGeometry = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    return false;
  if (okArcRowid == true && okNodeFrom == true && okNodeTo == true
      && okCost == true && okGeometry == true)
    return true;
  return false;
}

void MyFrame::AlignLayerParams()
{
//
// aligning the 'layer_params' table 
//
  int ret;
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  sqlite3_stmt *stmt;
  bool raster_layer;
  wxString table;
  wxString geometry;
  char xSql[1024];
  char tblName[1024];
  char geomCol[1024];
  char descName[1024];
  char labelColumn[1024];
  char foreGround[64];
  char backGround[64];
  char lineColor[64];
  char lineStyle[128];
  char fillColor[64];
  char labelColor[64];
  char labelOrderByColumn[1024];
  char labelFontWeight[128];
  char labelFontStyle[128];
  int len;
  MyLayerList *list = GetLayerList();
  MyLayer *p;

// first step: checking existing layer params
  sql =
    wxT("SELECT raster_layer, table_name, geometry_column FROM layer_params");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
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
          if (results[(i * columns) + 0] == NULL)
            raster_layer = false;
          else
            {
              if (atoi(results[(i * columns) + 0]) == 0)
                raster_layer = false;
              else
                raster_layer = true;
            }
          name = results[(i * columns) + 1];
          table = wxString::FromUTF8(name);
          name = results[(i * columns) + 2];
          geometry = wxString::FromUTF8(name);
          if (raster_layer == true)
            list->Evaluate(table);
          else
            {
              bool network = CheckNetwork(table);
              list->Evaluate(table, geometry, network);
            }
        }
    }
  sqlite3_free_table(results);

//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }

  if (list->ToBeDeleted() == true)
    {
      // second step: deleting no longer existing layer params
      sql = wxT("DELETE FROM layer_params ");
      sql +=
        wxT
        ("WHERE raster_layer = ? AND table_name = ? AND geometry_column = ?");
      ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto stop;
        }

      p = list->GetFirst();
      while (p)
        {
          if (p->IsToDelete() == false)
            {
              p = p->GetNext();
              continue;
            }
          sqlite3_reset(stmt);
          sqlite3_clear_bindings(stmt);
          if (p->IsRasterLayer() == true)
            {
              // raster layer
              sqlite3_bind_int(stmt, 1, 1);
              ConvertString(p->GetTableName(), tblName, &len);
              sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
              sqlite3_bind_text(stmt, 3, "RASTER", strlen("RASTER"),
                                SQLITE_STATIC);
          } else
            {
              // vector layer
              sqlite3_bind_int(stmt, 1, 0);
              ConvertString(p->GetTableName(), tblName, &len);
              sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
              ConvertString(p->GetGeometryColumn(), geomCol, &len);
              sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);
            }

          ret = sqlite3_step(stmt);
          if (ret == SQLITE_DONE || ret == SQLITE_ROW)
            ;
          else
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              sqlite3_finalize(stmt);
              return;
            }
          p = p->GetNext();
        }

      sqlite3_finalize(stmt);

      // trying to delete SubClasses
      sql = wxT("DELETE FROM layer_sub_classes ");
      sql += wxT("WHERE table_name = ? AND geometry_column = ?");
      ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto stop;
        }

      p = list->GetFirst();
      while (p)
        {
          if (p->IsToDelete() == false)
            {
              p = p->GetNext();
              continue;
            }
          sqlite3_reset(stmt);
          sqlite3_clear_bindings(stmt);
          if (p->IsRasterLayer() == false)
            {
              // vector layer
              ConvertString(p->GetTableName(), tblName, &len);
              sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
              ConvertString(p->GetGeometryColumn(), geomCol, &len);
              sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
            }

          ret = sqlite3_step(stmt);
          if (ret == SQLITE_DONE || ret == SQLITE_ROW)
            ;
          else
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              sqlite3_finalize(stmt);
              return;
            }
          p = p->GetNext();
        }

      sqlite3_finalize(stmt);
    }

  if (list->ToBeInserted() == true)
    {
      // third step: inserting new layer params
      sql = wxT("INSERT INTO layer_params ");
      sql +=
        wxT("(raster_layer, table_name, geometry_column, desc_name, visible, ");
      sql +=
        wxT("identify, reproject, label_column, always_visible, min_scale, ");
      sql += wxT("max_scale, symbol_id, foreground_color, background_color, ");
      sql +=
        wxT("line_color, line_thickness, line_style, draw_border, to_fill, ");
      sql +=
        wxT
        ("solid_filling, fill_color, pattern_id, z_order, has_sub_classes, network, ");
      sql +=
        wxT
        ("map_labeling, label_color, label_point_size, label_font_weight, label_font_style, ");
      sql +=
        wxT
        ("label_font_underlined, label_font_outlined, label_order_by_column, ");
      sql +=
        wxT("label_order_by_desc, label_always_visible, label_min_scale, ");
      sql += wxT("label_max_scale, label_anti_overlap) VALUES ");
      sql +=
        wxT
        ("(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ");
      sql += wxT("?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
      ConvertString(sql, xSql, &len);
      ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
      if (ret != SQLITE_OK)
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          goto stop;
        }

      p = list->GetFirst();
      while (p)
        {
          if (p->IsToInsert() == false)
            {
              p = p->GetNext();
              continue;
            }
          sqlite3_reset(stmt);
          sqlite3_clear_bindings(stmt);
          if (p->IsRasterLayer() == true)
            {
              // raster layer
              LayerObject layer(p->GetTableName(), 0);
              sqlite3_bind_int(stmt, 1, 1);
              ConvertString(layer.GetTableName(), tblName, &len);
              sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
              ConvertString(layer.GetGeometryColumn(), geomCol, &len);
              sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);
              ConvertString(layer.GetDescName(), descName, &len);
              sqlite3_bind_text(stmt, 4, descName, len, SQLITE_STATIC);
              sqlite3_bind_int(stmt, 5, layer.IsVisible());
              sqlite3_bind_null(stmt, 6);
              sqlite3_bind_null(stmt, 7);
              sqlite3_bind_null(stmt, 8);
              sqlite3_bind_int(stmt, 9, layer.IsAlwaysVisible());
              sqlite3_bind_int(stmt, 10, layer.GetMinScale());
              sqlite3_bind_int(stmt, 11, layer.GetMaxScale());
              sqlite3_bind_null(stmt, 12);
              sqlite3_bind_null(stmt, 13);
              sqlite3_bind_null(stmt, 14);
              sqlite3_bind_null(stmt, 15);
              sqlite3_bind_null(stmt, 16);
              sqlite3_bind_null(stmt, 17);
              sqlite3_bind_null(stmt, 18);
              sqlite3_bind_null(stmt, 19);
              sqlite3_bind_null(stmt, 20);
              sqlite3_bind_null(stmt, 21);
              sqlite3_bind_null(stmt, 22);
              sqlite3_bind_int(stmt, 23, 0);
              sqlite3_bind_int(stmt, 24, 0);
              sqlite3_bind_int(stmt, 25, 0);
              sqlite3_bind_int(stmt, 26, 0);
              sqlite3_bind_null(stmt, 27);
              sqlite3_bind_int(stmt, 28, 10);
              sqlite3_bind_null(stmt, 29);
              sqlite3_bind_null(stmt, 30);
              sqlite3_bind_null(stmt, 31);
              sqlite3_bind_null(stmt, 32);
              sqlite3_bind_null(stmt, 33);
              sqlite3_bind_int(stmt, 34, 0);
              sqlite3_bind_int(stmt, 35, layer.IsLabelAlwaysVisible());
              sqlite3_bind_int(stmt, 36, layer.GetLabelMinScale());
              sqlite3_bind_int(stmt, 37, layer.GetLabelMaxScale());
              sqlite3_bind_int(stmt, 38, 0);
          } else
            {
              // vector layer
              LayerObject layer(p->GetTableName(), p->GetGeometryColumn(), 0,
                                LAYER_POINT, false);
              layer.PrepareStaticValues();
              sqlite3_bind_int(stmt, 1, 0);
              ConvertString(layer.GetTableName(), tblName, &len);
              sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
              ConvertString(layer.GetGeometryColumn(), geomCol, &len);
              sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);
              ConvertString(layer.GetDescName(), descName, &len);
              sqlite3_bind_text(stmt, 4, descName, len, SQLITE_STATIC);
              sqlite3_bind_int(stmt, 5, layer.IsVisible());
              sqlite3_bind_int(stmt, 6, layer.IsIdentify());
              sqlite3_bind_int(stmt, 7, layer.IsReproject());
              ConvertString(layer.GetLabelColumn(), labelColumn, &len);
              sqlite3_bind_text(stmt, 8, labelColumn, len, SQLITE_STATIC);
              sqlite3_bind_int(stmt, 9, layer.IsAlwaysVisible());
              sqlite3_bind_int(stmt, 10, layer.GetMinScale());
              sqlite3_bind_int(stmt, 11, layer.GetMaxScale());
              sqlite3_bind_int(stmt, 12, layer.GetSymbolId());
              ConvertString(layer.GetForegroundColorAsRGBA(), foreGround, &len);
              sqlite3_bind_text(stmt, 13, foreGround, len, SQLITE_STATIC);
              ConvertString(layer.GetBackgroundColorAsRGBA(), backGround, &len);
              sqlite3_bind_text(stmt, 14, backGround, len, SQLITE_STATIC);
              ConvertString(layer.GetLineColorAsRGBA(), lineColor, &len);
              sqlite3_bind_text(stmt, 15, lineColor, len, SQLITE_STATIC);
              sqlite3_bind_int(stmt, 16, layer.GetLineThickness());
              ConvertString(layer.GetLineStyleAsConstant(), lineStyle, &len);
              sqlite3_bind_text(stmt, 17, lineStyle, len, SQLITE_STATIC);
              sqlite3_bind_int(stmt, 18, layer.DrawBorderOk());
              sqlite3_bind_int(stmt, 19, layer.IsToFill());
              sqlite3_bind_int(stmt, 20, layer.SolidFillingOk());
              ConvertString(layer.GetFillColorAsRGBA(), fillColor, &len);
              sqlite3_bind_text(stmt, 21, fillColor, len, SQLITE_STATIC);
              sqlite3_bind_int(stmt, 22, layer.GetPatternId());
              sqlite3_bind_int(stmt, 23, 0);
              sqlite3_bind_int(stmt, 24, 0);
              sqlite3_bind_int(stmt, 25, 0);
              sqlite3_bind_int(stmt, 26, layer.IsMapLabelingEnabled());
              ConvertString(layer.GetLabelColorAsRGBA(), labelColor, &len);
              sqlite3_bind_text(stmt, 27, labelColor, len, SQLITE_STATIC);
              sqlite3_bind_int(stmt, 28, layer.GetLabelPointSize());
              ConvertString(layer.GetLabelOrderByColumn(), labelOrderByColumn,
                            &len);
              ConvertString(layer.GetLabelFontWeight(), labelFontWeight, &len);
              sqlite3_bind_text(stmt, 29, labelFontWeight, len, SQLITE_STATIC);
              ConvertString(layer.GetLabelFontStyle(), labelFontStyle, &len);
              sqlite3_bind_text(stmt, 30, labelFontStyle, len, SQLITE_STATIC);
              sqlite3_bind_int(stmt, 31, layer.IsLabelFontUnderlined());
              sqlite3_bind_int(stmt, 32, layer.IsLabelFontOutlined());
              sqlite3_bind_text(stmt, 33, labelOrderByColumn, len,
                                SQLITE_STATIC);
              sqlite3_bind_int(stmt, 34, layer.IsLabelOrderByDescending());
              sqlite3_bind_int(stmt, 35, layer.IsLabelAlwaysVisible());
              sqlite3_bind_int(stmt, 36, layer.GetLabelMinScale());
              sqlite3_bind_int(stmt, 37, layer.GetLabelMaxScale());
              sqlite3_bind_int(stmt, 38, layer.IsLabelAntiOverlapEnabled());
            }

          ret = sqlite3_step(stmt);
          if (ret == SQLITE_DONE || ret == SQLITE_ROW)
            ;
          else
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              sqlite3_finalize(stmt);
              goto stop;
            }
          p = p->GetNext();
        }
      sqlite3_finalize(stmt);
    }
// fourth step: updating the Network column
  sql = wxT("UPDATE layer_params SET network = ? ");
  sql += wxT("WHERE table_name = ? AND geometry_column = ?");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  p = list->GetFirst();
  while (p)
    {
      if (p->IsToDelete() == true || list->ToBeInserted() == true)
        {
          p = p->GetNext();
          continue;
        }
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      sqlite3_bind_int(stmt, 1, p->IsNetwork());
      ConvertString(p->GetTableName(), tblName, &len);
      sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
      ConvertString(p->GetGeometryColumn(), geomCol, &len);
      sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);

      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
      p = p->GetNext();
    }
  sqlite3_finalize(stmt);
//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  delete list;
  return;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  delete list;
}

bool MyFrame::InsertLayerParams(LayerObject * layer)
{
//
// inserting a new layer
//
  wxString sql;
  sqlite3_stmt *stmt;
  char xSql[1024];
  int len;
  int ret;
  char tblName[1024];
  char geomCol[1024];
  char descName[1024];
  char labelColumn[1024];
  char foreGround[64];
  char backGround[64];
  char lineColor[64];
  char lineStyle[128];
  char fillColor[64];
  char labelColor[64];
  char labelOrderByColumn[1024];
  char labelFontWeight[128];
  char labelFontStyle[128];

  sql = wxT("INSERT INTO layer_params ");
  sql +=
    wxT("(raster_layer, table_name, geometry_column, desc_name, visible, ");
  sql += wxT("identify, reproject, label_column, always_visible, min_scale, ");
  sql += wxT("max_scale, symbol_id, foreground_color, background_color, ");
  sql += wxT("line_color, line_thickness, line_style, draw_border, to_fill, ");
  sql +=
    wxT
    ("solid_filling, fill_color, pattern_id, z_order, has_sub_classes, network, ");
  sql +=
    wxT("map_labeling, label_color, label_point_size, label_font_weight, ");
  sql +=
    wxT
    ("label_font_style, label_font_underlined, label_font_outlined, label_order_by_column, ");
  sql += wxT("label_order_by_desc, label_always_visible, label_min_scale, ");
  sql += wxT("label_max_scale, label_anti_overlap ) VALUES ");
  sql +=
    wxT
    ("(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ");
  sql += wxT("?, ?, ?, ?, ?, ?, ?, ?, ?)");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (layer->GetType() == RASTER_LAYER)
    {
      // raster layer
      sqlite3_bind_int(stmt, 1, 1);
      ConvertString(layer->GetTableName(), tblName, &len);
      sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
      ConvertString(layer->GetGeometryColumn(), geomCol, &len);
      sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);
      ConvertString(layer->GetDescName(), descName, &len);
      sqlite3_bind_text(stmt, 4, descName, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 5, layer->IsVisible());
      sqlite3_bind_null(stmt, 6);
      sqlite3_bind_null(stmt, 7);
      sqlite3_bind_null(stmt, 8);
      sqlite3_bind_int(stmt, 9, layer->IsAlwaysVisible());
      sqlite3_bind_int(stmt, 10, layer->GetMinScale());
      sqlite3_bind_int(stmt, 11, layer->GetMaxScale());
      sqlite3_bind_null(stmt, 12);
      sqlite3_bind_null(stmt, 13);
      sqlite3_bind_null(stmt, 14);
      sqlite3_bind_null(stmt, 15);
      sqlite3_bind_null(stmt, 16);
      sqlite3_bind_null(stmt, 17);
      sqlite3_bind_null(stmt, 18);
      sqlite3_bind_null(stmt, 19);
      sqlite3_bind_null(stmt, 20);
      sqlite3_bind_null(stmt, 21);
      sqlite3_bind_null(stmt, 22);
      sqlite3_bind_int(stmt, 23, 0);
      sqlite3_bind_int(stmt, 24, 0);
      sqlite3_bind_int(stmt, 25, 0);
      sqlite3_bind_int(stmt, 26, 0);
      sqlite3_bind_null(stmt, 27);
      sqlite3_bind_int(stmt, 28, 10);
      sqlite3_bind_null(stmt, 29);
      sqlite3_bind_null(stmt, 30);
      sqlite3_bind_null(stmt, 31);
      sqlite3_bind_null(stmt, 32);
      sqlite3_bind_null(stmt, 33);
      sqlite3_bind_int(stmt, 34, 0);
      sqlite3_bind_int(stmt, 35, layer->IsLabelAlwaysVisible());
      sqlite3_bind_int(stmt, 36, layer->GetLabelMinScale());
      sqlite3_bind_int(stmt, 37, layer->GetLabelMaxScale());
      sqlite3_bind_int(stmt, 38, 0);
  } else
    {
      // vector layer
      sqlite3_bind_int(stmt, 1, 0);
      ConvertString(layer->GetTableName(), tblName, &len);
      sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
      ConvertString(layer->GetGeometryColumn(), geomCol, &len);
      sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);
      ConvertString(layer->GetDescName(), descName, &len);
      sqlite3_bind_text(stmt, 4, descName, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 5, layer->IsVisible());
      sqlite3_bind_int(stmt, 6, layer->IsIdentify());
      sqlite3_bind_int(stmt, 7, layer->IsReproject());
      ConvertString(layer->GetLabelColumn(), labelColumn, &len);
      sqlite3_bind_text(stmt, 8, labelColumn, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 9, layer->IsAlwaysVisible());
      sqlite3_bind_int(stmt, 10, layer->GetMinScale());
      sqlite3_bind_int(stmt, 11, layer->GetMaxScale());
      sqlite3_bind_int(stmt, 12, layer->GetSymbolId());
      ConvertString(layer->GetForegroundColorAsRGBA(), foreGround, &len);
      sqlite3_bind_text(stmt, 13, foreGround, len, SQLITE_STATIC);
      ConvertString(layer->GetBackgroundColorAsRGBA(), backGround, &len);
      sqlite3_bind_text(stmt, 14, backGround, len, SQLITE_STATIC);
      ConvertString(layer->GetLineColorAsRGBA(), lineColor, &len);
      sqlite3_bind_text(stmt, 15, lineColor, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 16, layer->GetLineThickness());
      ConvertString(layer->GetLineStyleAsConstant(), lineStyle, &len);
      sqlite3_bind_text(stmt, 17, lineStyle, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 18, layer->DrawBorderOk());
      sqlite3_bind_int(stmt, 19, layer->IsToFill());
      sqlite3_bind_int(stmt, 20, layer->SolidFillingOk());
      ConvertString(layer->GetFillColorAsRGBA(), fillColor, &len);
      sqlite3_bind_text(stmt, 21, fillColor, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 22, layer->GetPatternId());
      sqlite3_bind_int(stmt, 23, 0);
      sqlite3_bind_int(stmt, 24, 0);
      sqlite3_bind_int(stmt, 25, layer->IsNetwork());
      sqlite3_bind_int(stmt, 26, layer->IsMapLabelingEnabled());
      ConvertString(layer->GetLabelColorAsRGBA(), labelColor, &len);
      sqlite3_bind_text(stmt, 27, labelColor, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 28, layer->GetLabelPointSize());
      ConvertString(layer->GetLabelFontWeight(), labelFontWeight, &len);
      sqlite3_bind_text(stmt, 29, labelFontWeight, len, SQLITE_STATIC);
      ConvertString(layer->GetLabelFontStyle(), labelFontStyle, &len);
      sqlite3_bind_text(stmt, 30, labelFontStyle, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 31, layer->IsLabelFontUnderlined());
      sqlite3_bind_int(stmt, 32, layer->IsLabelFontOutlined());
      ConvertString(layer->GetLabelOrderByColumn(), labelOrderByColumn, &len);
      sqlite3_bind_text(stmt, 33, labelOrderByColumn, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 34, layer->IsLabelOrderByDescending());
      sqlite3_bind_int(stmt, 35, layer->IsLabelAlwaysVisible());
      sqlite3_bind_int(stmt, 36, layer->GetLabelMinScale());
      sqlite3_bind_int(stmt, 37, layer->GetLabelMaxScale());
      sqlite3_bind_int(stmt, 38, layer->IsLabelAntiOverlapEnabled());
    }

  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      return false;
    }

  sqlite3_finalize(stmt);
  return true;
stop:
  return false;
}

void MyFrame::AlignStatistics()
{
//
// aligning the 'layer_statistics' table 
//
  int ret;
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  sqlite3_stmt *stmt;
  sqlite3_stmt *stmt_table = NULL;
  sqlite3_stmt *stmt_views = NULL;
  sqlite3_stmt *stmt_virts = NULL;
  bool raster_layer;
  wxString table;
  wxString geometry;
  char xSql[1024];
  char tblName[1024];
  char geomCol[1024];
  int len;
  MyLayer *p;
  MyLayerList *list = GetLayerList();

// checking existing layer statistics
  sql =
    wxT
    ("SELECT raster_layer, table_name, geometry_column FROM layer_statistics");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    goto views;
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          if (results[(i * columns) + 0] == NULL)
            raster_layer = false;
          else
            {
              if (atoi(results[(i * columns) + 0]) == 0)
                raster_layer = false;
              else
                raster_layer = true;
            }
          name = results[(i * columns) + 1];
          table = wxString::FromUTF8(name);
          name = results[(i * columns) + 2];
          geometry = wxString::FromUTF8(name);
          if (raster_layer == true)
            list->Evaluate(table);
          else
            {
              bool network = CheckNetwork(table);
              list->Evaluate(table, geometry, network);
            }
        }
    }
  sqlite3_free_table(results);

// checking existing VIEW layer statistics
views:
  sql = wxT("SELECT view_name, view_geometry FROM views_layer_statistics");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    goto virts;
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 0];
          table = wxString::FromUTF8(name);
          name = results[(i * columns) + 1];
          geometry = wxString::FromUTF8(name);
          list->Evaluate(table, geometry, false);
        }
    }
  sqlite3_free_table(results);

// checking existing VIRTUAL layer statistics
virts:
  sql = wxT("SELECT virt_name, virt_geometry FROM virts_layer_statistics");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    goto end_check;
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 0];
          table = wxString::FromUTF8(name);
          name = results[(i * columns) + 1];
          geometry = wxString::FromUTF8(name);
          list->Evaluate(table, geometry, false);
        }
    }
  sqlite3_free_table(results);

//
// starting a transaction
//
end_check:
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }

  if (list->ToBeDeleted() == true)
    {
      if (list->ToBeDeletedTable() == true)
        {
          // deleting no longer existing layer statistics
          sql = wxT("DELETE FROM layer_statistics ");
          sql +=
            wxT
            ("WHERE raster_layer = ? AND table_name = ? AND geometry_column = ?");
          ConvertString(sql, xSql, &len);
          ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt_table, NULL);
          if (ret != SQLITE_OK)
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              goto stop;
            }
        }
      if (list->ToBeDeletedView() == true)
        {
          // deleting no longer existing VIEW layer statistics
          sql = wxT("DELETE FROM views_layer_statistics ");
          sql += wxT("WHERE view_name = ? AND view_geometry = ?");
          ConvertString(sql, xSql, &len);
          ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt_views, NULL);
          if (ret != SQLITE_OK)
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              goto stop;
            }
        }
      if (list->ToBeDeletedVirt() == true)
        {
          // deleting no longer existing VIRTUAL layer statistics
          sql = wxT("DELETE FROM virst_layer_statistics ");
          sql += wxT("WHERE virt_table = ? AND virt_geometry = ?");
          ConvertString(sql, xSql, &len);
          ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt_virts, NULL);
          if (ret != SQLITE_OK)
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              goto stop;
            }
        }

      p = list->GetFirst();
      while (p)
        {
          if (p->IsToDelete() == false)
            {
              p = p->GetNext();
              continue;
            }
          if (p->IsRasterLayer() == true)
            {
              // raster layer
              stmt = stmt_table;
              sqlite3_reset(stmt);
              sqlite3_clear_bindings(stmt);
              sqlite3_bind_int(stmt, 1, 1);
              ConvertString(p->GetTableName(), tblName, &len);
              sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
              sqlite3_bind_text(stmt, 3, "RASTER", strlen("RASTER"),
                                SQLITE_STATIC);
          } else
            {
              // vector layer
              if (p->IsLayerView() == true)
                {
                  stmt = stmt_views;
                  sqlite3_reset(stmt);
                  sqlite3_clear_bindings(stmt);
                  ConvertString(p->GetTableName(), tblName, &len);
                  sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
                  ConvertString(p->GetGeometryColumn(), geomCol, &len);
                  sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
              } else if (p->IsLayerVirtual() == true)
                {
                  stmt = stmt_virts;
                  sqlite3_reset(stmt);
                  sqlite3_clear_bindings(stmt);
                  ConvertString(p->GetTableName(), tblName, &len);
                  sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
                  ConvertString(p->GetGeometryColumn(), geomCol, &len);
                  sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
              } else
                {
                  stmt = stmt_table;
                  sqlite3_reset(stmt);
                  sqlite3_clear_bindings(stmt);
                  sqlite3_bind_int(stmt, 1, 0);
                  ConvertString(p->GetTableName(), tblName, &len);
                  sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
                  ConvertString(p->GetGeometryColumn(), geomCol, &len);
                  sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);
                }
            }

          ret = sqlite3_step(stmt);
          if (ret == SQLITE_DONE || ret == SQLITE_ROW)
            ;
          else
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              sqlite3_finalize(stmt);
              return;
            }
          p = p->GetNext();
        }

      if (stmt_table != NULL)
        sqlite3_finalize(stmt_table);
      if (stmt_views != NULL)
        sqlite3_finalize(stmt_views);
      if (stmt_virts != NULL)
        sqlite3_finalize(stmt_virts);
      stmt_table = NULL;
      stmt_views = NULL;
      stmt_virts = NULL;
    }

  p = list->GetFirst();
  while (p)
    {
      // updating statistics for newly inserted layers
      if (p->IsToInsert() == false)
        {
          p = p->GetNext();
          continue;
        }
      if (p->IsRasterLayer() == true)
        UpdateStatistics(p->GetTableName());
      else
        UpdateStatistics(p->GetTableName(), p->GetGeometryColumn());
      p = p->GetNext();
    }

//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  delete list;
  return;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  delete list;
  if (stmt_table != NULL)
    sqlite3_finalize(stmt_table);
  if (stmt_views != NULL)
    sqlite3_finalize(stmt_views);
  if (stmt_virts != NULL)
    sqlite3_finalize(stmt_virts);
}

bool MyFrame::InsertLayerStatistics(LayerObject * layer, int count, double minx,
                                    double miny, double maxx, double maxy)
{
//
// inserting a new layer into the 'layer_statistic' table
//
  wxString sql;
  sqlite3_stmt *stmt;
  char xSql[1024];
  int len;
  int ret;
  char tblName[1024];
  char geomCol[1024];

  sql = wxT("INSERT INTO layer_statistics ");
  sql +=
    wxT
    ("(raster_layer, table_name, geometry_column, row_count, extent_min_x, ");
  sql += wxT("extent_min_y, extent_max_x, extent_max_y) VALUES ");
  sql += wxT("(?, ?, ?, ?, ?, ?, ?, ?)");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  sqlite3_bind_int(stmt, 1, 0);
  ConvertString(layer->GetTableName(), tblName, &len);
  sqlite3_bind_text(stmt, 2, tblName, len, SQLITE_STATIC);
  ConvertString(layer->GetGeometryColumn(), geomCol, &len);
  sqlite3_bind_text(stmt, 3, geomCol, len, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 4, count);
  sqlite3_bind_double(stmt, 5, minx);
  sqlite3_bind_double(stmt, 6, miny);
  sqlite3_bind_double(stmt, 7, maxx);
  sqlite3_bind_double(stmt, 8, maxy);

  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      return false;
    }

  sqlite3_finalize(stmt);
  return true;
stop:
  return false;
}

void MyFrame::UpdateLayerParams(LayerObject * layer)
{
//
// updating Params for some Layer
//
  int ret;
  wxString sql;
  sqlite3_stmt *stmt;
  char xSql[1024];
  char tblName[1024];
  char geomCol[1024];
  char descName[1024];
  char labelColumn[1024];
  char foreGround[64];
  char backGround[64];
  char lineColor[64];
  char lineStyle[128];
  char fillColor[64];
  char labelColor[64];
  char labelOrderByColumn[1024];
  char labelFontWeight[128];
  char labelFontStyle[128];
  int len;

  layer->PrepareStaticValues();

  sql =
    wxT("UPDATE layer_params SET desc_name = ?, visible = ?, identify = ?, ");
  sql +=
    wxT("reproject = ?, label_column = ?, always_visible = ?, min_scale = ?, ");
  sql +=
    wxT
    ("max_scale = ?, symbol_id = ?, foreground_color = ?, background_color = ?, ");
  sql +=
    wxT
    ("line_color = ?, line_thickness = ?, line_style = ?, draw_border = ?, ");
  sql +=
    wxT("to_fill = ?, solid_filling = ?, fill_color = ?, pattern_id = ?, ");
  sql += wxT("map_labeling = ?, label_color = ?, label_point_size = ?, ");
  sql += wxT("label_font_weight = ?, label_font_style = ?, ");
  sql += wxT("label_font_underlined = ?, label_font_outlined = ?, ");
  sql +=
    wxT
    ("label_order_by_column = ?, label_order_by_desc = ?, label_always_visible = ?, ");
  sql +=
    wxT("label_min_scale = ?, label_max_scale = ?, label_anti_overlap = ? ");
  sql +=
    wxT("WHERE raster_layer = ? AND table_name = ? AND geometry_column = ?");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      return;
    }

  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (layer->GetType() == RASTER_LAYER)
    {
      // raster layer
      ConvertString(layer->GetDescName(), descName, &len);
      sqlite3_bind_text(stmt, 1, descName, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 2, layer->IsVisible());
      sqlite3_bind_null(stmt, 3);
      sqlite3_bind_null(stmt, 4);
      sqlite3_bind_null(stmt, 5);
      sqlite3_bind_int(stmt, 6, layer->IsAlwaysVisible());
      sqlite3_bind_int(stmt, 7, layer->GetMinScale());
      sqlite3_bind_int(stmt, 8, layer->GetMaxScale());
      sqlite3_bind_null(stmt, 9);
      sqlite3_bind_null(stmt, 10);
      sqlite3_bind_null(stmt, 11);
      sqlite3_bind_null(stmt, 12);
      sqlite3_bind_null(stmt, 13);
      sqlite3_bind_null(stmt, 14);
      sqlite3_bind_null(stmt, 15);
      sqlite3_bind_null(stmt, 16);
      sqlite3_bind_null(stmt, 17);
      sqlite3_bind_null(stmt, 18);
      sqlite3_bind_null(stmt, 19);
      sqlite3_bind_int(stmt, 20, 0);
      sqlite3_bind_null(stmt, 21);
      sqlite3_bind_int(stmt, 22, 10);
      sqlite3_bind_null(stmt, 23);
      sqlite3_bind_null(stmt, 24);
      sqlite3_bind_null(stmt, 25);
      sqlite3_bind_null(stmt, 26);
      sqlite3_bind_null(stmt, 27);
      sqlite3_bind_int(stmt, 28, 0);
      sqlite3_bind_int(stmt, 29, layer->IsLabelAlwaysVisible());
      sqlite3_bind_int(stmt, 30, layer->GetLabelMinScale());
      sqlite3_bind_int(stmt, 31, layer->GetLabelMaxScale());
      sqlite3_bind_int(stmt, 32, 0);
  } else
    {
      // vector layer
      ConvertString(layer->GetDescName(), descName, &len);
      sqlite3_bind_text(stmt, 1, descName, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 2, layer->IsVisible());
      sqlite3_bind_int(stmt, 3, layer->IsIdentify());
      sqlite3_bind_int(stmt, 4, layer->IsReproject());
      ConvertString(layer->GetLabelColumn(), labelColumn, &len);
      sqlite3_bind_text(stmt, 5, labelColumn, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 6, layer->IsAlwaysVisible());
      sqlite3_bind_int(stmt, 7, layer->GetMinScale());
      sqlite3_bind_int(stmt, 8, layer->GetMaxScale());
      sqlite3_bind_int(stmt, 9, layer->GetSymbolId());
      ConvertString(layer->GetForegroundColorAsRGBA(), foreGround, &len);
      sqlite3_bind_text(stmt, 10, foreGround, len, SQLITE_STATIC);
      ConvertString(layer->GetBackgroundColorAsRGBA(), backGround, &len);
      sqlite3_bind_text(stmt, 11, backGround, len, SQLITE_STATIC);
      ConvertString(layer->GetLineColorAsRGBA(), lineColor, &len);
      sqlite3_bind_text(stmt, 12, lineColor, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 13, layer->GetLineThickness());
      ConvertString(layer->GetLineStyleAsConstant(), lineStyle, &len);
      sqlite3_bind_text(stmt, 14, lineStyle, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 15, layer->DrawBorderOk());
      sqlite3_bind_int(stmt, 16, layer->IsToFill());
      sqlite3_bind_int(stmt, 17, layer->SolidFillingOk());
      ConvertString(layer->GetFillColorAsRGBA(), fillColor, &len);
      sqlite3_bind_text(stmt, 18, fillColor, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 19, layer->GetPatternId());
      sqlite3_bind_int(stmt, 20, layer->IsMapLabelingEnabled());
      ConvertString(layer->GetLabelColorAsRGBA(), labelColor, &len);
      sqlite3_bind_text(stmt, 21, labelColor, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 22, layer->GetLabelPointSize());
      ConvertString(layer->GetLabelFontWeight(), labelFontWeight, &len);
      sqlite3_bind_text(stmt, 23, labelFontWeight, len, SQLITE_STATIC);
      ConvertString(layer->GetLabelFontStyle(), labelFontStyle, &len);
      sqlite3_bind_text(stmt, 24, labelFontStyle, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 25, layer->IsLabelFontUnderlined());
      sqlite3_bind_int(stmt, 26, layer->IsLabelFontOutlined());
      ConvertString(layer->GetLabelOrderByColumn(), labelOrderByColumn, &len);
      sqlite3_bind_text(stmt, 27, labelOrderByColumn, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 28, layer->IsLabelOrderByDescending());
      sqlite3_bind_int(stmt, 29, layer->IsLabelAlwaysVisible());
      sqlite3_bind_int(stmt, 30, layer->GetLabelMinScale());
      sqlite3_bind_int(stmt, 31, layer->GetLabelMaxScale());
      sqlite3_bind_int(stmt, 32, layer->IsLabelAntiOverlapEnabled());
    }
  if (layer->GetType() == RASTER_LAYER)
    sqlite3_bind_int(stmt, 33, 1);
  else
    sqlite3_bind_int(stmt, 33, 0);
  ConvertString(layer->GetTableName(), tblName, &len);
  sqlite3_bind_text(stmt, 34, tblName, len, SQLITE_STATIC);
  ConvertString(layer->GetGeometryColumn(), geomCol, &len);
  sqlite3_bind_text(stmt, 35, geomCol, len, SQLITE_STATIC);
  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      return;
    }

  sqlite3_finalize(stmt);
}

bool MyFrame::ZoomToLayerExtent(LayerObject * layer)
{
//
// Zoom to Layer Extent
//
  int ret;
  wxString sql;
  sqlite3_stmt *stmt;
  char xSql[1024];
  int len;
  double min_x;
  double min_y;
  double max_x;
  double max_y;
  int count = 0;

  if (layer->GetType() != VECTOR_LAYER)
    return false;

  sql = wxT("SELECT extent_min_x, extent_min_y, extent_max_x, extent_max_y ");
  if (layer->IsLayerView() == true)
    {
      sql += wxT("FROM views_layer_statistics ");
      sql += wxT("WHERE view_name LIKE '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry LIKE '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
  } else if (layer->IsLayerVirtual() == true)
    {
      sql += wxT("FROM virts_layer_statistics ");
      sql += wxT("WHERE virt_name LIKE '");
      sql += layer->GetTableName();
      sql += wxT("' AND virt_geometry LIKE '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
  } else
    {
      sql += wxT("FROM layer_statistics ");
      sql += wxT("WHERE raster_layer = 0 ");
      sql += wxT("AND table_name LIKE '");
      sql += layer->GetTableName();
      sql += wxT("' AND geometry_column LIKE '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
    }

  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      return false;
    }
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          if (sqlite3_column_type(stmt, 0) == SQLITE_FLOAT)
            {
              min_x = sqlite3_column_double(stmt, 0);
              count++;
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
            {
              min_y = sqlite3_column_double(stmt, 1);
              count++;
            }
          if (sqlite3_column_type(stmt, 2) == SQLITE_FLOAT)
            {
              max_x = sqlite3_column_double(stmt, 2);
              count++;
            }
          if (sqlite3_column_type(stmt, 3) == SQLITE_FLOAT)
            {
              max_y = sqlite3_column_double(stmt, 3);
              count++;
            }
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          return false;
        }
    }

  sqlite3_finalize(stmt);
  if (count != 4)
    return false;
  MapView->ZoomTo(min_x, min_y, max_x, max_y);
  return true;
}

void MyFrame::UpdateSubClassesParams(wxTreeItemId & layer,
                                     SubClassesPreview * subClasses,
                                     bool uniqueValue, wxString & columnName,
                                     int numClasses, double minValue,
                                     double maxValue, int symbolType,
                                     int minSize, int maxSize,
                                     wxColour & minColor, wxColour & maxColor)
{
//
// updating Params for some SubClasses
//
  int ret;
  wxString sql;
  sqlite3_stmt *stmt;
  char *errMsg = NULL;
  char xSql[1024];
  char tblName[1024];
  char geomCol[1024];
  char classifyColumn[1024];
  char classesSymbolType[128];
  char classesMinColor[64];
  char classesMaxColor[64];
  char textValue[1024];
  char color[64];
  int len;
  int classId;
  LayerObject *newObj;
  wxTreeItemId newItem;
  wxTreeItemId item;
  wxTreeItemIdValue cookie;
  LayerObject *obj = (LayerObject *) LayerTree->GetItemData(layer);
  if (obj == NULL)
    return;
// updating Layer's general criteria for SubClasses
  obj->SetClassifyParams(columnName, uniqueValue, numClasses, minValue,
                         maxValue, symbolType, minSize, maxSize, minColor,
                         maxColor);
// appending SubClasses to the Layer
  LayerTree->DeleteChildren(layer);
  newObj = new LayerObject(obj, true);
  newItem = LayerTree->AppendItem(layer, wxT(""), -1, -1, newObj);
  item = subClasses->GetFirstChild(subClasses->GetRootItem(), cookie);
  while (item.IsOk() == true)
    {
      SubClassObject *sub = (SubClassObject *) subClasses->GetItemData(item);
      if (sub != NULL)
        {
          newObj = new LayerObject(sub);
          newItem =
            LayerTree->AppendItem(layer, newObj->GetSubClassString(), -1, -1,
                                  newObj);
        }
      item = subClasses->GetNextChild(subClasses->GetRootItem(), cookie);
    }
  LayerTree->SetLayerIcons();

  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
// updating the 'layer_params' table
  sql =
    wxT("UPDATE layer_params SET has_sub_classes = ?, classify_column = ?, ");
  sql += wxT("distinct_values = ?, num_classes = ?, classes_min_value = ?, ");
  sql += wxT("classes_max_value = ?, classes_symbol_type = ?, ");
  sql += wxT("classes_min_size = ?, classes_max_size = ?, ");
  sql += wxT("classes_max_color = ?, classes_min_color = ? ");
  sql +=
    wxT("WHERE raster_layer = ? AND table_name = ? AND geometry_column = ?");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  if (obj->GetType() == VECTOR_LAYER)
    {
      obj->PrepareStaticClassesValues();
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      sqlite3_bind_int(stmt, 1, 1);
      ConvertString(obj->GetClassifyColumn(), classifyColumn, &len);
      sqlite3_bind_text(stmt, 2, classifyColumn, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 3, obj->IsUniqueValue());
      sqlite3_bind_int(stmt, 4, obj->GetNumClasses());
      sqlite3_bind_double(stmt, 5, obj->GetClassesMinValue());
      sqlite3_bind_double(stmt, 6, obj->GetClassesMaxValue());
      ConvertString(obj->GetSymbolTypeAsConstant(), classesSymbolType, &len);
      sqlite3_bind_text(stmt, 7, classesSymbolType, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 8, obj->GetClassesMinSize());
      sqlite3_bind_int(stmt, 9, obj->GetClassesMaxSize());
      ConvertString(obj->GetClassesMinColorAsRGBA(), classesMinColor, &len);
      sqlite3_bind_text(stmt, 10, classesMinColor, len, SQLITE_STATIC);
      ConvertString(obj->GetClassesMaxColorAsRGBA(), classesMaxColor, &len);
      sqlite3_bind_text(stmt, 11, classesMaxColor, len, SQLITE_STATIC);
      sqlite3_bind_int(stmt, 12, 0);
      ConvertString(obj->GetTableName(), tblName, &len);
      sqlite3_bind_text(stmt, 13, tblName, len, SQLITE_STATIC);
      ConvertString(obj->GetGeometryColumn(), geomCol, &len);
      sqlite3_bind_text(stmt, 14, geomCol, len, SQLITE_STATIC);
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

// deleting any existing SubClass
  sql = wxT("DELETE FROM layer_sub_classes ");
  sql += wxT("WHERE table_name = ? AND geometry_column = ?");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  ConvertString(obj->GetTableName(), tblName, &len);
  sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
  ConvertString(obj->GetGeometryColumn(), geomCol, &len);
  sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      goto stop;
    }
  sqlite3_finalize(stmt);

// inserting into the 'layer_sub_classes' table
  sql =
    wxT
    ("INSERT INTO layer_sub_classes (table_name, geometry_column, class_id, ");
  sql +=
    wxT("range_value, is_text, text_value, num_value, min_value, max_value, ");
  sql += wxT("symbol_type, size, color) VALUES ");
  sql += wxT("(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  classId = 0;
  item = subClasses->GetFirstChild(subClasses->GetRootItem(), cookie);
  while (item.IsOk() == true)
    {
      SubClassObject *sub = (SubClassObject *) subClasses->GetItemData(item);
      if (sub != NULL)
        {
          classId++;
          sub->PrepareStaticValues();
          sqlite3_reset(stmt);
          sqlite3_clear_bindings(stmt);
          ConvertString(obj->GetTableName(), tblName, &len);
          sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
          ConvertString(obj->GetGeometryColumn(), geomCol, &len);
          sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
          sqlite3_bind_int(stmt, 3, classId);
          if (sub->IsUnique() == true)
            sqlite3_bind_int(stmt, 4, 1);
          else
            sqlite3_bind_int(stmt, 4, 0);
          if (sub->IsText() == true)
            sqlite3_bind_int(stmt, 5, 1);
          else
            sqlite3_bind_int(stmt, 5, 0);
          if (sub->IsUnique() == true)
            {
              if (sub->IsText() == true)
                {
                  ConvertString(sub->GetTextValue(), textValue, &len);
                  sqlite3_bind_text(stmt, 6, textValue, len, SQLITE_STATIC);
                  sqlite3_bind_null(stmt, 7);
              } else
                {
                  sqlite3_bind_null(stmt, 6);
                  sqlite3_bind_double(stmt, 7, sub->GetNumValue());
                }
              sqlite3_bind_null(stmt, 8);
              sqlite3_bind_null(stmt, 9);
          } else
            {
              sqlite3_bind_null(stmt, 6);
              sqlite3_bind_null(stmt, 7);
              sqlite3_bind_double(stmt, 8, sub->GetMinValue());
              sqlite3_bind_double(stmt, 9, sub->GetMaxValue());
            }
          if (obj->GetGeometryType() == LAYER_POINT)
            {
              ConvertString(sub->GetSymbolTypeAsConstant(), classesSymbolType,
                            &len);
              sqlite3_bind_text(stmt, 10, classesSymbolType, len,
                                SQLITE_STATIC);
          } else
            sqlite3_bind_null(stmt, 10);
          if (obj->GetGeometryType() == LAYER_POINT
              || obj->GetGeometryType() == LAYER_LINESTRING)
            sqlite3_bind_int(stmt, 11, sub->GetSize());
          else
            sqlite3_bind_null(stmt, 11);
          ConvertString(sub->GetColorAsRGBA(), color, &len);
          sqlite3_bind_text(stmt, 12, color, len, SQLITE_STATIC);
          ret = sqlite3_step(stmt);
          if (ret == SQLITE_DONE || ret == SQLITE_ROW)
            ;
          else
            {
              wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
              wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                           wxOK | wxICON_ERROR, this);
              sqlite3_finalize(stmt);
              goto stop;
            }
        }
      item = subClasses->GetNextChild(subClasses->GetRootItem(), cookie);
    }
  sqlite3_finalize(stmt);


//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  ::wxEndBusyCursor();
  return;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
  return;
}

void MyFrame::DropSubClasses(wxTreeItemId & layer)
{
//
// dropping someSubClasses
//
  int ret;
  wxString sql;
  sqlite3_stmt *stmt;
  char *errMsg = NULL;
  char xSql[1024];
  char tblName[1024];
  char geomCol[1024];
  int len;
  LayerObject *newObj;
  LayerObject *obj = (LayerObject *) LayerTree->GetItemData(layer);
  if (obj == NULL)
    return;
  obj->ClearClassifyParams();
  LayerTree->DeleteChildren(layer);
  newObj = new LayerObject(obj, true);
  LayerTree->AppendItem(layer, wxT(""), -1, -1, newObj);
  LayerTree->SetLayerIcons();

  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
// updating the 'layer_params' table
  sql =
    wxT("UPDATE layer_params SET has_sub_classes = ?, classify_column = ?, ");
  sql += wxT("distinct_values = ?, num_classes = ?, classes_min_value = ?, ");
  sql += wxT("classes_max_value = ?, classes_symbol_type = ?, ");
  sql += wxT("classes_min_size = ?, classes_max_size = ?, ");
  sql += wxT("classes_max_color = ?, classes_min_color = ? ");
  sql +=
    wxT("WHERE raster_layer = ? AND table_name = ? AND geometry_column = ?");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  if (obj->GetType() == VECTOR_LAYER)
    {
      obj->PrepareStaticClassesValues();
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      sqlite3_bind_int(stmt, 1, 0);
      sqlite3_bind_null(stmt, 2);
      sqlite3_bind_null(stmt, 3);
      sqlite3_bind_null(stmt, 4);
      sqlite3_bind_null(stmt, 5);
      sqlite3_bind_null(stmt, 6);
      sqlite3_bind_null(stmt, 7);
      sqlite3_bind_null(stmt, 8);
      sqlite3_bind_null(stmt, 9);
      sqlite3_bind_null(stmt, 10);
      sqlite3_bind_null(stmt, 11);
      sqlite3_bind_int(stmt, 12, 0);
      ConvertString(obj->GetTableName(), tblName, &len);
      sqlite3_bind_text(stmt, 13, tblName, len, SQLITE_STATIC);
      ConvertString(obj->GetGeometryColumn(), geomCol, &len);
      sqlite3_bind_text(stmt, 14, geomCol, len, SQLITE_STATIC);
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

// deleting any existing SubClass
  sql = wxT("DELETE FROM layer_sub_classes ");
  sql += wxT("WHERE table_name = ? AND geometry_column = ?");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  ConvertString(obj->GetTableName(), tblName, &len);
  sqlite3_bind_text(stmt, 1, tblName, len, SQLITE_STATIC);
  ConvertString(obj->GetGeometryColumn(), geomCol, &len);
  sqlite3_bind_text(stmt, 2, geomCol, len, SQLITE_STATIC);
  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      goto stop;
    }
  sqlite3_finalize(stmt);

//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  ::wxEndBusyCursor();
  return;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
  return;
}

void MyFrame::UpdateZOrder()
{
//
// updating the Layers' ZOrder
//
  int ret;
  wxString sql;
  char *errMsg = NULL;
  sqlite3_stmt *stmt;
  int zOrder = 0;
  wxTreeItemId item;
  wxTreeItemIdValue cookie;
  LayerObject *layer;
  char xSql[1024];
  char tableName[1024];
  char geometryColumn[1024];
  int len;

  item = LayerTree->GetFirstChild(LayerTree->GetRoot(), cookie);
  while (item.IsOk() == true)
    {
      // counting how many layers are there
      zOrder++;
      item = LayerTree->GetNextChild(LayerTree->GetRoot(), cookie);
    }
  if (!zOrder)
    return;

  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }

  sql = wxT("UPDATE layer_params SET z_order = ? ");
  sql +=
    wxT("WHERE raster_layer = ? AND table_name = ? AND geometry_column = ?");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  item = LayerTree->GetFirstChild(LayerTree->GetRoot(), cookie);
  while (item.IsOk() == true)
    {
      // updating ZOrder
      layer = (LayerObject *) LayerTree->GetItemData(item);
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      sqlite3_bind_int(stmt, 1, zOrder);
      if (layer->GetType() == RASTER_LAYER)
        sqlite3_bind_int(stmt, 2, 1);
      else
        sqlite3_bind_int(stmt, 2, 0);
      ConvertString(layer->GetTableName(), tableName, &len);
      sqlite3_bind_text(stmt, 3, tableName, len, SQLITE_STATIC);
      ConvertString(layer->GetGeometryColumn(), geometryColumn, &len);
      sqlite3_bind_text(stmt, 4, geometryColumn, len, SQLITE_STATIC);

      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }

      zOrder--;
      item = LayerTree->GetNextChild(LayerTree->GetRoot(), cookie);
    }

  sqlite3_finalize(stmt);

//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  ::wxEndBusyCursor();
  return;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
  return;
}

void MyFrame::UpdateStatistics()
{
//
// updating Statistics for any Layer into this Project
//
  wxTreeItemId item;
  wxTreeItemIdValue cookie;
  LayerObject *layer;

  item = LayerTree->GetFirstChild(LayerTree->GetRoot(), cookie);
  while (item.IsOk() == true)
    {
      // processing a single layer at each time
      layer = (LayerObject *) LayerTree->GetItemData(item);
      if (layer == NULL)
        ;
      else
        {
          if (layer->GetType() == VECTOR_LAYER)
            UpdateStatistics(layer->GetTableName(), layer->GetGeometryColumn());
          if (layer->GetType() == RASTER_LAYER)
            UpdateStatistics(layer->GetTableName());
        }
      item = LayerTree->GetNextChild(LayerTree->GetRoot(), cookie);
    }
}

void MyFrame::UpdateStatistics(wxString & tableName)
{
//
// updating Statistics for some Raster Layer
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  sqlite3_stmt *stmt;
  char xSql[1024];
  char tblName[1024];
  int len;
  char *value;
  int count = -1;
  double min_x = DBL_MAX;
  double min_y = 0.0 - DBL_MAX;
  double max_x = DBL_MAX;
  double max_y = 0.0 - DBL_MAX;

  ::wxBeginBusyCursor();

  sql = wxT("SELECT Count(*), Min(MbrMinX(geometry)), ");
  sql += wxT("Min(MbrMinY(geometry)), ");
  sql += wxT("Max(MbrMaxX(geometry)), ");
  sql += wxT("Max(MbrMaxY(geometry)) ");
  sql += wxT("FROM \"");
  sql += tableName;
  sql += wxT("_metadata\"");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      ::wxEndBusyCursor();
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
            count = atoi(value);
          value = results[(i * columns) + 1];
          if (value)
            min_x = atof(value);
          value = results[(i * columns) + 2];
          if (value)
            min_y = atof(value);
          value = results[(i * columns) + 3];
          if (value)
            max_x = atof(value);
          value = results[(i * columns) + 4];
          if (value)
            max_y = atof(value);
        }
    }
  sqlite3_free_table(results);

  sql = wxT("UPDATE layer_statistics SET row_count = ?, ");
  sql += wxT("extent_min_x = ?, extent_min_y = ?, ");
  sql += wxT("extent_max_x = ?, extent_max_y = ? ");
  sql +=
    wxT
    ("WHERE raster_layer = 1 AND table_name = ? and geometry_column = 'RASTER'");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      ::wxEndBusyCursor();
      return;
    }

  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (count < 0 || min_x == DBL_MAX || min_y == DBL_MAX
      || max_x == 0.0 - DBL_MAX || max_y == 0.0 - DBL_MIN)
    {
      sqlite3_bind_null(stmt, 1);
      sqlite3_bind_null(stmt, 2);
      sqlite3_bind_null(stmt, 3);
      sqlite3_bind_null(stmt, 4);
      sqlite3_bind_null(stmt, 5);
  } else
    {
      sqlite3_bind_int(stmt, 1, count);
      sqlite3_bind_double(stmt, 2, min_x);
      sqlite3_bind_double(stmt, 3, min_y);
      sqlite3_bind_double(stmt, 4, max_x);
      sqlite3_bind_double(stmt, 5, max_y);
    }
  ConvertString(tableName, tblName, &len);
  sqlite3_bind_text(stmt, 6, tblName, len, SQLITE_STATIC);

  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      ::wxEndBusyCursor();
      return;
    }

  sqlite3_finalize(stmt);
  ::wxEndBusyCursor();
}

void MyFrame::UpdateStatistics(wxString & tableName, wxString & geometryColumn)
{
//
// updating Statistics for some Vector Layer
//
  char *errMsg = NULL;
  int ret;
  wxString sql;

  ::wxBeginBusyCursor();

  sql = wxT("SELECT UpdateLayerStatistics('");
  sql += tableName;
  if (geometryColumn.Len() > 0)
    {
      sql += wxT("', '");
      sql += geometryColumn;
    }
  sql += wxT("')");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
}

bool MyFrame::CheckLayerTableLayout(int *invalid)
{
//
// checking for 'layer_table_layout' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okTableName = false;
  bool okGeometryColumn = false;
  bool okColumnName = false;
  bool okDescName = false;
  bool okDataType = false;
  bool okLength = false;
  bool okDecimals = false;
  *invalid = 1;
  sql = wxT("PRAGMA table_info(layer_table_layout)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "table_name") == 0)
                okTableName = true;
              if (strcasecmp(name, "geometry_column") == 0)
                okGeometryColumn = true;
              if (strcasecmp(name, "column_name") == 0)
                okColumnName = true;
              if (strcasecmp(name, "desc_name") == 0)
                okDescName = true;
              if (strcasecmp(name, "data_type") == 0)
                okDataType = true;
              if (strcasecmp(name, "length") == 0)
                okLength = true;
              if (strcasecmp(name, "decimals") == 0)
                okDecimals = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    {
      *invalid = 0;
      return false;
    }
  if (okTableName == true && okGeometryColumn == true && okColumnName == true
      && okDescName == true && okDataType == true && okLength == true
      && okDecimals == true)
    {
      *invalid = 0;
      return true;
    }
  return false;
}

bool MyFrame::CreateLayerTableLayout()
{
//
// creating and initializing the 'layer_table_layout' table 
//
  int ret;
  char *errMsg = NULL;
  wxString sql;

//
// creating the Table 
//
  sql = wxT("CREATE TABLE layer_table_layout (\n");
  sql += wxT("table_name TEXT NOT NULL,\n");
  sql += wxT("geometry_column TEXT NOT NULL,\n");
  sql += wxT("column_name TEXT NOT NULL,\n");
  sql += wxT("desc_name TEXT,\n");
  sql += wxT("data_type TEXT,\n");
  sql += wxT("length INTEGER,\n");
  sql += wxT("decimals INTEGER,\n");
  sql += wxT("CONSTRAINT pk_layer_table_layout PRIMARY KEY ");
  sql += wxT("(table_name, geometry_column, column_name),\n");
  sql += wxT("CONSTRAINT fk_layer_table_layout FOREIGN KEY ");
  sql += wxT("(table_name, geometry_column) REFERENCES ");
  sql += wxT("layer_params (table_name, geometry_column) ");
  sql += wxT("ON DELETE CASCADE)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  return true;
}

bool MyFrame::CheckProjectDefs(int *invalid)
{
//
// checking for 'project_defs' validity
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  bool empty = false;
  bool okProjectId = false;
  bool okProjectName = false;
  bool okSrid = false;
  bool okDms = false;
  *invalid = 1;
  sql = wxT("PRAGMA table_info(project_defs)");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "project_id") == 0)
                okProjectId = true;
              if (strcasecmp(name, "project_name") == 0)
                okProjectName = true;
              if (strcasecmp(name, "project_srid") == 0)
                okSrid = true;
              if (strcasecmp(name, "dms_format") == 0)
                okDms = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    {
      *invalid = 0;
      return false;
    }
  if (okProjectId == true && okProjectName == true && okSrid == true
      && okDms == true)
    {
      *invalid = 0;
      return true;
    }
  return false;
}

bool MyFrame::CreateProjectDefs()
{
//
// creating and initializing the 'project_defs' table 
//
  int ret;
  char *errMsg = NULL;
  wxString sql;

//
// creating the Table 
//
  sql = wxT("CREATE TABLE project_defs (\n");
  sql += wxT("project_id INTEGER PRIMARY KEY,\n");
  sql += wxT("project_name TEXT NOT NULL,\n");
  sql += wxT("project_srid INTEGER NOT NULL,\n");
  sql += wxT("dms_format INTEGER NOT NULL)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  sql = wxT("INSERT INTO project_defs ");
  sql += wxT("(project_id, project_name, project_srid, dms_format) ");
  sql += wxT("VALUES (0, 'Anonymous', -1, 1)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  return true;
}

void MyFrame::UpdateProjectDefs()
{
//
// updating the 'project_defs' table 
//
  int ret;
  wxString sql;
  char *errMsg = NULL;
  sqlite3_stmt *stmt;
  char xSql[1024];
  char projectName[1024];
  int len;

//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }

  sql = wxT("UPDATE project_defs ");
  sql += wxT("SET project_name = ?, project_srid = ?, dms_format = ? ");
  sql += wxT("WHERE project_id = 0");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  ConvertString(ProjectName, projectName, &len);
  sqlite3_bind_text(stmt, 1, projectName, len, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, ProjectSrid.GetSrid());
  sqlite3_bind_int(stmt, 3, ProjectSrid.IsDms());

  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      return;
    }

//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  return;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
}

void MyFrame::LoadProjectDefs()
{
//
// loading from 'project_defs' 
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *value;
  int srid;
  bool dms;
  wxString sql;

  ProjectName = wxT("Anonymous");

  sql =
    wxT
    ("SELECT project_name, project_srid, dms_format FROM project_defs WHERE project_id = 0");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
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
          ProjectName = wxString::FromUTF8(value);
          if (ProjectName.Len() == 0)
            ProjectName = wxT("Anonymous");
          if (results[(i * columns) + 1] == NULL)
            srid = -1;
          else
            srid = atoi(results[(i * columns) + 1]);
          if (results[(i * columns) + 2] == NULL)
            dms = true;
          else
            {
              if (atoi(results[(i * columns) + 2]) == 0)
                dms = false;
              else
                dms = true;
            }
          GetSridInfo(srid);
          ProjectSrid.SetDms(dms);
          UpdateReferenceSystem();
          ProjectSridChanged();
        }
    }
  sqlite3_free_table(results);
}

void MyFrame::GetColumnList(wxString & table, int *count, wxString ** list)
{
//
// retrieving the Columns for the given table
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  int cnt;
  wxString *tables;
  sql = wxT("PRAGMA table_info(\"");
  sql += table;
  sql += wxT("\")");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      cnt = 1;
      tables = new wxString[1];
      tables[0] = wxT(" - not selected -");
      goto end;
    }
  if (rows < 1)
    {
      cnt = 1;
      tables = new wxString[1];
      tables[0] = wxT(" - not selected -");
  } else
    {
      cnt = rows + 1;
      tables = new wxString[rows + 1];
      tables[0] = wxT(" - not selected -");
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          tables[i] = wxString::FromUTF8(name);
        }
    }
  sqlite3_free_table(results);
end:
  *count = cnt;
  *list = tables;
}

void MyFrame::GetColumnList(wxString & table, int *count, wxString ** list,
                            wxString & geomColumn, int geomType)
{
//
// retrieving the Columns for the given table
//
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString sql;
  int cnt;
  int col = 1;
  wxString *tables;
  char geocolumn[1024];
  strcpy(geocolumn, geomColumn.ToUTF8());
  sql = wxT("PRAGMA table_info(\"");
  sql += table;
  sql += wxT("\")");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      cnt = 1;
      tables = new wxString[1];
      tables[0] = wxT(" - not selected -");
      goto end;
    }
  if (rows < 1)
    {
      cnt = 1;
      tables = new wxString[1];
      tables[0] = wxT(" - not selected -");
  } else
    {
      cnt = rows;
      if (geomType == LAYER_LINESTRING)
        cnt += 1;
      if (geomType == LAYER_POLYGON)
        cnt += 2;
      tables = new wxString[cnt];
      tables[0] = wxT(" - not selected -");
      col = 1;
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (strcasecmp(name, geocolumn) != 0)
            tables[col++] = wxString::FromUTF8(name);
        }
    }
  sqlite3_free_table(results);
  if (geomType == LAYER_LINESTRING || geomType == LAYER_POLYGON)
    {
      wxString colFnct = wxT("GLength(\"") + geomColumn + wxT("\")");
      tables[col++] = colFnct;
    }
  if (geomType == LAYER_POLYGON)
    {
      wxString colFnct = wxT("Area(\"") + geomColumn + wxT("\")");
      tables[col++] = colFnct;
    }
end:
  *count = cnt;
  *list = tables;
}

void MyFrame::GetDistinctValues(wxString & tableName, wxString & classifyColumn,
                                MyDistinctValueList * list, bool * truncated)
{
// building a DISTINCT values List
  wxString sql;
  int ret;
  sqlite3_stmt *stmt;
  int int_value;
  double dbl_value;
  char *str_value;
  int len;
  char xSql[1024];
  int count = 0;

  ::wxBeginBusyCursor();

  sql = wxT("SELECT DISTINCT \"");
  sql += classifyColumn;
  sql += wxT("\" FROM \"");
  sql += tableName;
  sql += wxT("\" LIMIT 251");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
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
          if (sqlite3_column_type(stmt, 0) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 0);
              if (count < 250)
                list->Add(int_value);
              count++;
            }
          if (sqlite3_column_type(stmt, 0) == SQLITE_FLOAT)
            {
              dbl_value = sqlite3_column_double(stmt, 0);
              if (count < 250)
                list->Add(dbl_value);
              count++;
            }
          if (sqlite3_column_type(stmt, 0) == SQLITE_TEXT)
            {
              str_value = (char *) sqlite3_column_text(stmt, 0);
              wxString value = wxString::FromUTF8(str_value);
              if (count < 250)
                list->Add(value);
              count++;
            }
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);
stop:
  ::wxEndBusyCursor();
  if (count > 250)
    *truncated = true;
  else
    *truncated = false;
  return;
}

void MyFrame::GetMaxMinValues(wxString & tableName, wxString & classifyColumn,
                              double *min, double *max, bool * invalid)
{
// identifying the values range
  wxString sql;
  int ret;
  sqlite3_stmt *stmt;
  int int_value;
  double dbl_value;
  int len;
  char xSql[1024];
  double vmin = DBL_MAX;
  double vmax = 0.0 - DBL_MAX;
  bool err = false;

  ::wxBeginBusyCursor();

  sql = wxT("SELECT \"");
  sql += classifyColumn;
  sql += wxT("\" FROM \"");
  sql += tableName;
  sql += wxT("\"");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
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
          if (sqlite3_column_type(stmt, 0) == SQLITE_INTEGER)
            {
              int_value = sqlite3_column_int(stmt, 0);
              if (vmin > int_value)
                vmin = int_value;
              if (vmax < int_value)
                vmax = int_value;
            }
          if (sqlite3_column_type(stmt, 0) == SQLITE_FLOAT)
            {
              dbl_value = sqlite3_column_double(stmt, 0);
              if (vmin > dbl_value)
                vmin = dbl_value;
              if (vmax < dbl_value)
                vmax = dbl_value;
            }
          if (sqlite3_column_type(stmt, 0) == SQLITE_TEXT
              || sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            err = true;
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);
stop:
  ::wxEndBusyCursor();
  if (vmin == 0.0 - DBL_MAX || vmax == DBL_MAX)
    *invalid = true;
  else if (err == true)
    *invalid = true;
  else
    {
      *invalid = false;
      *min = vmin;
      *max = vmax;
    }
  return;
}

bool MyFrame::BestRasterResolution(wxString & prefix, double requested_ratio,
                                   double *pixel_x_size, double *pixel_y_size)
{
// selects the best resolution available querying the raster_pyramids table
  wxString sql;
  int ret;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  double min_dist = DBL_MAX;
  double dist;
  double best_x = DBL_MAX;
  double best_y = DBL_MAX;

  sql = wxT("SELECT pixel_x_size, pixel_y_size ");
  sql += wxT("FROM raster_pyramids WHERE table_prefix = '");
  sql += prefix;
  sql += wxT("' ORDER BY pixel_x_size DESC");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
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
          double x_size = 0.0;
          double y_size = 0.0;
          bool ok_x = false;
          bool ok_y = false;
          if (sqlite3_column_type(stmt, 0) == SQLITE_FLOAT)
            {
              x_size = sqlite3_column_double(stmt, 0);
              ok_x = true;
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
            {
              y_size = sqlite3_column_double(stmt, 1);
              ok_y = true;
            }
          if (ok_x == true && ok_y == true)
            {
              dist = fabs(requested_ratio - x_size);
              if (dist < min_dist)
                {
                  min_dist = dist;
                  best_x = x_size;
                  best_y = y_size;
                }
            }
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);
  if (best_x == DBL_MAX || best_y == DBL_MAX)
    return false;
  *pixel_x_size = best_x;
  *pixel_y_size = best_y;
  return true;

stop:
  return false;
}

int MyFrame::GetSpatialIndexType(wxString & table, wxString & geometry)
{
//
// checks the Spatial Index type 
//
  sqlite3 *sqlite = GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  int retval = SPATIAL_INDEX_NONE;
  sql = wxT("SELECT spatial_index_enabled ");
  sql += wxT("FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += table;
  sql += wxT("' AND f_geometry_column = '");
  sql += geometry;
  sql += wxT("'");
  ret =
    sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return retval;
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
                retval = SPATIAL_INDEX_RTREE;
              if (atoi(value) == 2)
                retval = SPATIAL_INDEX_CACHED;
            }
        }
    }
  sqlite3_free_table(results);
  return retval;
}

bool MyFrame::DeleteLayer(LayerObject * layer)
{
//
// deleting some Vector or Raster layer
//
  int ret;
  wxString msg;
  char *errMsg = NULL;
  wxString sql = wxT("BEGIN; ");
  if (layer->GetType() == VECTOR_LAYER) // deleting a Vector layer
    {
      // dropping the SpatialIndex [if existing]
      sql += wxT("DROP TABLE IF EXISTS \"idx_");
      sql += layer->GetTableName();
      sql += wxT("_");
      sql += layer->GetGeometryColumn();
      sql += wxT("\"; ");
      // dropping the MBR cache [if existing]
      sql += wxT("DROP TABLE IF EXISTS \"cache_");
      sql += layer->GetTableName();
      sql += wxT("_");
      sql += layer->GetGeometryColumn();
      sql += wxT("\"; ");
      // deleting from layer_table_layout
      sql += wxT("DELETE FROM layer_table_layout WHERE table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'; ");
      // deleting from layer_statistics
      sql +=
        wxT
        ("DELETE FROM layer_statistics WHERE raster_layer = 0 AND table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'; ");
      // deleting from layer_sub_classes
      sql += wxT("DELETE FROM layer_sub_classes WHERE table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'; ");
      // deleting from layer_params
      sql +=
        wxT
        ("DELETE FROM layer_params WHERE raster_layer = 0 AND table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'; ");
      // deleting from geometry_columns
      sql += wxT("DELETE FROM geometry_columns WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'; ");
      if (layer->IsLayerView() == true)
        {
          // deleting from views_geometry_columns
          sql += wxT("DELETE FROM views_geometry_columns WHERE view_name = '");
          sql += layer->GetTableName();
          sql += wxT("'; ");
          // deleting the view itself
          sql += wxT("DROP VIEW IF EXISTS \"");
      } else
        {
          if (layer->IsLayerVirtual() == true)
            {
              // deleting from virts_geometry_columns
              sql +=
                wxT("DELETE FROM virts_geometry_columns WHERE virt_name = '");
              sql += layer->GetTableName();
              sql += wxT("'; ");
            }
          // deleting the table itself
          sql += wxT("DROP TABLE IF EXISTS \"");
        }
      sql += layer->GetTableName();
      sql += wxT("\"; COMMIT;");
    }
  if (layer->GetType() == RASTER_LAYER) // deleting a Raster layer
    {
      // dropping the SpatialIndex [if existing]
      sql += wxT("DROP TABLE IF EXISTS \"idx_");
      sql += layer->GetTableName();
      sql += wxT("_metadata_geometry\"; ");
      // deleting from layer_statistics
      sql +=
        wxT
        ("DELETE FROM layer_statistics WHERE raster_layer = 1 AND table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND geometry_column = 'RASTER'; ");
      // deleting from layer_params
      sql +=
        wxT
        ("DELETE FROM layer_params WHERE raster_layer = 1 AND table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND geometry_column = 'RASTER'; ");
      // deleting from raster_pyramids
      sql += wxT("DELETE FROM raster_pyramids WHERE table_prefix = '");
      sql += layer->GetTableName();
      sql += wxT("'; ");
      // deleting from geometry_columns
      sql += wxT("DELETE FROM geometry_columns WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("_metadata' AND f_geometry_column = 'geometry'; ");
      // deleting the table [metadata]
      sql += wxT("DROP TABLE IF EXISTS \"");
      sql += layer->GetTableName();
      sql += wxT("_metadata\"; ");
      // deleting the table [rasters]
      sql += wxT("DROP TABLE IF EXISTS \"");
      sql += layer->GetTableName();
      sql += wxT("_rasters\"; COMMIT;");
    }
// performing SQL statements
  ::wxBeginBusyCursor();
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, NULL, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      ::wxEndBusyCursor();
      goto rollback;
    }
  ::wxEndBusyCursor();
  wxMessageBox(wxT("The layer '") + layer->GetTableName() +
               wxT("' was successfully deleted"), wxT("spatialite-gis"),
               wxOK | wxICON_INFORMATION, this);
  return true;
rollback:
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, NULL, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      ::wxEndBusyCursor();
      return false;
    }
  ::wxEndBusyCursor();
  wxMessageBox(wxT
               ("An error occurred\n\na ROLLBACK was automatically performed"),
               wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
  return false;
}

bool MyFrame::CheckNetworkNodes(int *invalid)
{
//
// checks if the Network Nodes aux tables exists
//
  wxString sql;
  int len;
  char xSql[1024];
  sqlite3_stmt *stmt;
  bool invalidSrid = false;
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  bool empty = false;
  bool ok_node = false;
  bool ok_geometry = false;
  int ret;
  *invalid = 1;

  sql = wxT("SELECT srid, spatial_index_enabled FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += NetParms->GetNodesAuxTable();
  sql += wxT("' AND f_geometry_column = 'Geometry'");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    goto skip;
  while (1)
    {
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;
      if (ret == SQLITE_ROW)
        {
          if (NetParms->GetSrid() != sqlite3_column_int(stmt, 0))
            invalidSrid = true;
          if (sqlite3_column_int(stmt, 1) == 1)
            NetParms->SetAuxNodesRTree(true);
      } else
        {
          sqlite3_finalize(stmt);
          goto skip;
        }
    }
  sqlite3_finalize(stmt);
skip:
  if (invalidSrid == true)
    {
      wxString msg = wxT("Network AuxNodes: illegal SRID\n\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return false;
    }

  sql = wxT("PRAGMA table_info(\"");
  sql += NetParms->GetNodesAuxTable();
  sql += wxT("\")");
  ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                          &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return false;
    }
  if (rows < 1)
    empty = true;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 1];
          if (name != NULL)
            {
              if (strcasecmp(name, "node") == 0)
                ok_node = true;
              if (strcasecmp(name, "geometry") == 0)
                ok_geometry = true;
            }
        }
    }
  sqlite3_free_table(results);
  if (empty == true)
    {
      *invalid = 0;
      return false;
    }
  if (ok_node == true && ok_geometry == true)
    return true;
  return false;
}

bool MyFrame::DestroyNetwork(wxString & table)
{
//
// destroying a network
//
  wxString sql;
  int len;
  char xSql[1024];
  int ret;
  char *errMsg = NULL;
  ::wxBeginBusyCursor();
//
// disabling the Spatial Index for Network Nodes aux table
//
  sql = wxT("SELECT DisableSpatialIndex('");
  sql += table;
  sql += wxT("_net NodesAuxTable', 'Geometry')");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(SqliteHandle, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// dropping the Spatial Index for Network Nodes aux table
//  
  sql = wxT("DROP TABLE IF EXISTS \"idx_");
  sql += table;
  sql += wxT("_net NodesAuxTable_Geometry\"");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(SqliteHandle, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
// deleting from geometry_columns
  sql = wxT("DELETE FROM geometry_columns WHERE f_table_name = '");
  sql += table;
  sql += wxT("_net NodesAuxTable' AND f_geometry_column = 'Geometry'");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(SqliteHandle, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
// deleting from layer_parames
  sql = wxT("DELETE FROM layer_params WHERE table_name = '");
  sql += table;
  sql += wxT("_net NodesAuxTable' AND geometry_column = 'Geometry'");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(SqliteHandle, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
// deleting from layer_statistics
  sql = wxT("DELETE FROM layer_statistics WHERE table_name = '");
  sql += table;
  sql += wxT("_net NodesAuxTable' AND geometry_column = 'Geometry'");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(SqliteHandle, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// dropping the Network Nodes aux table
//  
  sql = wxT("DROP TABLE IF EXISTS \"");
  sql += table;
  sql += wxT("_net NodesAuxTable\"");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(SqliteHandle, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// dropping the Network Virtual table
//  
  sql = wxT("DROP TABLE IF EXISTS \"");
  sql += table;
  sql += wxT("_net\"");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(SqliteHandle, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// dropping the Network Virtual table
//  
  sql = wxT("DROP TABLE IF EXISTS \"");
  sql += table;
  sql += wxT("_net_data\"");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_exec(SqliteHandle, xSql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  ::wxEndBusyCursor();
  return true;
stop:
  ::wxEndBusyCursor();
  return false;
}

bool MyFrame::FeedNetworkNodes()
{
//
// creating and feeding a Network Nodes aux table
//
  int ret;
  char *errMsg = NULL;
  wxString sql;
  char buf[1024];
  wxString sBuf;
  int i;
  char **results;
  int rows;
  int columns;
  int retval = 0;

  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// creating the Table 
//
  sql = wxT("CREATE TABLE \"") + NetParms->GetNodesAuxTable() + wxT("\" (\n");
  if (NetParms->IsTextNodes() == true)
    sql += wxT("node TEXT PRIMARY KEY NOT NULL)");
  else
    sql += wxT("node INTEGER PRIMARY KEY NOT NULL)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// creating geometry 
//
  sql = wxT("SELECT AddGeometryColumn('");
  sql += NetParms->GetNodesAuxTable();
  sql += wxT("', 'Geometry', ");
  sprintf(buf, "%d", NetParms->GetSrid());
  sBuf = wxString::FromUTF8(buf);
  sql += sBuf;
  sql += wxT(", 'POINT', 2)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// inserting NodeFrom
//
  sql = wxT("INSERT OR IGNORE INTO \"");
  sql += NetParms->GetNodesAuxTable();
  sql += wxT("\" (node, Geometry) SELECT \"");
  sql += NetParms->GetNodeFromColumn();
  sql += wxT("\", MakePoint(X(StartPoint(\"");
  sql += NetParms->GetGeometryColumn();
  sql += wxT("\")), Y(StartPoint(\"");
  sql += NetParms->GetGeometryColumn();
  sql += wxT("\")), ");
  sprintf(buf, "%d", NetParms->GetSrid());
  sBuf = wxString::FromUTF8(buf);
  sql += sBuf;
  sql += wxT(") FROM ");
  sql += NetParms->GetMainTable();
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// inserting NodeTo
//
  sql = wxT("INSERT OR IGNORE INTO \"");
  sql += NetParms->GetNodesAuxTable();
  sql += wxT("\" (node, Geometry) SELECT \"");
  sql += NetParms->GetNodeToColumn();
  sql += wxT("\", MakePoint(X(EndPoint(\"");
  sql += NetParms->GetGeometryColumn();
  sql += wxT("\")), Y(EndPoint(\"");
  sql += NetParms->GetGeometryColumn();
  sql += wxT("\")), ");
  sprintf(buf, "%d", NetParms->GetSrid());
  sBuf = wxString::FromUTF8(buf);
  sql += sBuf;
  sql += wxT(") FROM ");
  sql += NetParms->GetMainTable();
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// creating an R*Tree Spatial Index
//
  sql = wxT("SELECT CreateSpatialIndex('");
  sql += NetParms->GetNodesAuxTable();
  sql += wxT("', 'Geometry')");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          if (results[(i * columns) + 0])
            retval = atoi(results[(i * columns) + 0]);
        }
    }
  sqlite3_free_table(results);
  if (!retval)
    goto stop;
//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  NetParms->SetAuxNodesRTree(true);
  ::wxEndBusyCursor();
  return true;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
  return false;
}

bool MyFrame::CreateNetworkNodesRTree()
{
//
// creating an RTree Spatial Index for Network Nodes aux table
//
  int ret;
  char *errMsg = NULL;
  wxString sql;
  wxString sBuf;
  int i;
  char **results;
  int rows;
  int columns;
  int retval = 0;

  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// creating an R*Tree Spatial Index
//
  sql = wxT("SELECT CreateSpatialIndex('");
  sql += NetParms->GetNodesAuxTable();
  sql += wxT("', 'Geometry')");
  ret =
    sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results, &rows, &columns,
                      &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  if (rows < 1)
    ;
  else
    {
      for (i = 1; i <= rows; i++)
        {
          if (results[(i * columns) + 0])
            retval = atoi(results[(i * columns) + 0]);
        }
    }
  sqlite3_free_table(results);
  if (!retval)
    goto stop;
//
// committing the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
  NetParms->SetAuxNodesRTree(true);
  ::wxEndBusyCursor();
  return true;

stop:
//
// trying to perform a rollback anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
  ::wxEndBusyCursor();
  return false;
}

void MyFrame::LoadNetworkParams()
{
//
// trying to load Network Params
//
  wxString sql;
  int len;
  char xSql[1024];
  int ret;
  sqlite3_stmt *stmt;
  const unsigned char *blob;
  int size;
  bool ok;
  wxString str;
  FreeNetworkParams();
  NetworkParams *net = new NetworkParams();
  net->SetMainTable(ActiveLayer->GetTableName());
  str = ActiveLayer->GetTableName() + wxT("_net");
  net->SetNetworkTable(str);
  str = ActiveLayer->GetTableName() + wxT("_net NodesAuxTable");
  net->SetNodesAuxTable(str);

// trying to load the Network Header Block
  ok = false;
  str = net->GetNetworkTable() + wxT("_data");
  sql = wxT("SELECT NetworkData FROM \"");
  sql += str;
  sql += wxT("\" WHERE id = 0");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    goto abort_1;
  while (1)
    {
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;
      if (ret == SQLITE_ROW)
        {
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              blob = (const unsigned char *) sqlite3_column_blob(stmt, 0);
              size = sqlite3_column_bytes(stmt, 0);
              ok = ParseNetworkHeader(net, blob, size);
          } else
            {
              sqlite3_finalize(stmt);
              goto abort_1;
            }
      } else
        {
          sqlite3_finalize(stmt);
          goto abort_1;
        }
    }
  sqlite3_finalize(stmt);
abort_1:
  if (ok == false)
    {
      delete net;
      wxString msg = wxT("Network Header Block: invalid format\n\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
// trying to load the main table SRID
  ok = false;
  sql = wxT("SELECT srid, spatial_index_enabled FROM geometry_columns ");
  sql += wxT("WHERE f_table_name = '");
  sql += net->GetMainTable();
  sql += wxT("' AND f_geometry_column = '");
  sql += net->GetGeometryColumn();
  sql += wxT("'");
  ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(SqliteHandle, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    goto abort_2;
  while (1)
    {
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;
      if (ret == SQLITE_ROW)
        {
          net->SetSrid(sqlite3_column_int(stmt, 0));
          if (sqlite3_column_int(stmt, 1) == 1)
            net->SetMainRTree(true);
          ok = true;
      } else
        {
          sqlite3_finalize(stmt);
          goto abort_2;
        }
    }
  sqlite3_finalize(stmt);
abort_2:
  if (ok == false)
    {
      delete net;
      wxString msg = wxT("Network SRID not found\n\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  NetParms = net;
}

bool MyFrame::ParseNetworkHeader(NetworkParams * network,
                                 const unsigned char *blob, int size)
{
//
// trying to parse the Network Header block
//
  const char *table;
  const char *from;
  const char *to;
  const char *geom;
  const char *name;
  int len;
  const unsigned char *ptr;
  bool net64;
  bool aStar = false;
  int endian_arch = gaiaEndianArch();
  if (size < 9)
    return false;
  if (*(blob + 0) == GAIA_NET_START)  // signature - legacy format using 32bit ints 
    net64 = false;
  else if (*(blob + 0) == GAIA_NET64_START) // signature - format using 64bit ints 
    net64 = true;
  else if (*(blob + 0) == GAIA_NET64_A_STAR_START)  // signature - format using 64bit ints + A* support
    {
      net64 = true;
      aStar = true;
  } else
    return false;
  if (*(blob + 1) != GAIA_NET_HEADER) // signature 
    return false;
  if (*(blob + 6) == GAIA_NET_CODE) // Nodes identified by a TEXT code
    network->SetTextNodes(true);
  else if (*(blob + 6) == GAIA_NET_ID)  // Nodes indentified by an INTEGER id
    network->SetTextNodes(false);
  else
    return false;
  if (*(blob + 8) != GAIA_NET_TABLE)  // signature for TABLE NAME
    return false;
  ptr = blob + 9;
  len = gaiaImport16(ptr, 1, endian_arch);  // TABLE NAME is varlen
  ptr += 2;
  table = (char *) ptr;
  ptr += len;
  if (*ptr != GAIA_NET_FROM)    // signature for FromNode COLUMN
    return false;
  ptr++;
  len = gaiaImport16(ptr, 1, endian_arch);  // FromNode COLUMN is varlen
  ptr += 2;
  from = (char *) ptr;
  ptr += len;
  if (*ptr != GAIA_NET_TO)      // signature for ToNode COLUMN 
    return false;
  ptr++;
  len = gaiaImport16(ptr, 1, endian_arch);  // ToNode COLUMN is varlen
  ptr += 2;
  to = (char *) ptr;
  ptr += len;
  if (*ptr != GAIA_NET_GEOM)    // signature for Geometry COLUMN
    return false;
  ptr++;
  len = gaiaImport16(ptr, 1, endian_arch);  // Geometry COLUMN is varlen
  ptr += 2;
  geom = (char *) ptr;
  ptr += len;
  if (net64 == true)
    {
      if (*ptr != GAIA_NET_NAME)  // signature for Name COLUMN - may be empty
        return false;
      ptr++;
      len = gaiaImport16(ptr, 1, endian_arch);  /* Name COLUMN is varlen */
      ptr += 2;
      name = (char *) ptr;
      ptr += len;
    }
  if (net64 == true && aStar == true)
    {
      if (*ptr != GAIA_NET_A_STAR_COEFF)  // signature for A* Heuristic Coeff
        return false;
      ptr += 9;
    }
  if (*ptr != GAIA_NET_END)     // signature
    return false;
// setting up values
  wxString tableName = wxString::FromUTF8(table);
  if (tableName != network->GetMainTable())
    return false;
  network->SetNodeFromColumn(from);
  network->SetNodeToColumn(to);
  network->SetGeometryColumn(geom);
  network->SetNameColumn(name);
  return true;
}

wxString *MyFrame::GetTables(int *n, wxString & selectedTable, int *sel)
{
// loads the table list
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  char *name;
  wxString *tables = NULL;
  wxString sql;
  *n = 0;
  *sel = -1;
  sql =
    wxT("SELECT name FROM sqlite_master WHERE type = 'table' ORDER BY name");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return tables;
    }
  if (rows < 1)
    ;
  else
    {
      tables = new wxString[rows];
      *n = rows;
      for (i = 1; i <= rows; i++)
        {
          name = results[(i * columns) + 0];
          tables[i - 1] = wxString::FromUTF8(name);
          if (tables[i - 1] == selectedTable)
            *sel = i - 1;
        }
    }
  sqlite3_free_table(results);
  return tables;
}

wxString *MyFrame::GetColumnNames(wxString & tableName, int *n_cols,
                                  wxString & geom, int *sel)
{
// loads the table's column names list
  wxString *cols = NULL;
  int nCols = 0;
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  wxString sql;
  char *column;
  int xSel = -1;
  sql = wxT("PRAGMA table_info(\"");
  sql += tableName;
  sql += wxT("\")");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      return NULL;
    }
  sql = wxT("");
  if (rows < 1)
    ;
  else
    {
      nCols = rows;
      cols = new wxString[rows];
      for (i = 1; i <= rows; i++)
        {
          column = results[(i * columns) + 1];
          *(cols + i - 1) += wxString::FromUTF8(column);
          if (*(cols + i - 1) == geom)
            xSel = i - 1;
        }
    }
  sqlite3_free_table(results);
  *n_cols = nCols;
  *sel = xSel;
  return cols;
}

bool MyFrame::IsCurrentRoutingAlgorithmAStar(wxString & table)
{
// trying to identify the current Routing Algorithm
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  wxString sql;
  char *column;
  bool a_star = false;
  sql = wxT("SELECT Algorithm FROM \"");
  sql += table;
  sql += wxT("\"");
  int ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
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
          column = results[(i * columns) + 0];
          if (strcmp(column, "A*") == 0)
            a_star = true;
        }
    }
  sqlite3_free_table(results);
  return a_star;
}

void MyFrame::SetRoutingAlgorithm(wxString & table, bool aStar)
{
// trying to change the current Routing Algorithm
  char *errMsg = NULL;
  wxString sql;
  sql = wxT("UPDATE \"");
  sql += table;
  sql += wxT("\" SET Algorithm = '");
  if (aStar)
    sql += wxT("A*");
  else
    sql += wxT("Dijkstra");
  sql += wxT("'");
  int ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
    }
}

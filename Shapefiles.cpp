/*
/ Shapefiles.cpp
/ methods related to Shapefile loading and saving
/
/ version 1.0, 2009 March 11
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

#include "float.h"

#include <spatialite/gaiaaux.h>

bool MyFrame::TableAlreadyExists(wxString & name)
{
//
// checks if a table of this name already exists 
//
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  bool already_exists = false;
  wxString sql =
    wxT("SELECT name FROM sqlite_master WHERE type = 'table' AND name LIKE '");
  sql += name;
  sql += wxT("'");
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
        already_exists = true;
    }
  sqlite3_free_table(results);
  return already_exists;
}

bool MyFrame::SridNotExists(int srid)
{
//
// checks if a SRID value is a valid one
//
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  bool constrained = false;
  bool not_exists = true;
  wxString RefSysName;
  char xsql[1024];
  wxString sql =
    wxT
    ("SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'spatial_ref_sys'");
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
        constrained = true;
    }
  sqlite3_free_table(results);
  if (constrained == false)
    return false;
  sprintf(xsql, "SELECT ref_sys_name FROM spatial_ref_sys WHERE srid = %d",
          srid);
  ret =
    sqlite3_get_table(SqliteHandle, xsql, &results, &rows, &columns, &errMsg);
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
        not_exists = false;
    }
  sqlite3_free_table(results);
  return not_exists;
}

void MyFrame::LoadShapefile(wxString & path, wxString & table, int srid,
                            wxString & column, wxString & charset,
                            bool coerce2D, bool compressed)
{
//
// loading a Shapefile as a new DB table
//
  sqlite3_stmt *stmt;
  int cnt;
  int col_cnt;
  int seed;
  int len;
  int dup;
  int idup;
  int current_row;
  int ret;
  int rows = 0;
  char *errMsg = NULL;
  char xtable[1024];
  char xcolumn[1024];
  char dummyName[4096];
  char sql[65536];
  char **col_name = NULL;
  unsigned char *blob;
  int blob_size;
  const char *geom_type = "UNKNOWN";
  const char *txt_dims;
  wxString dummyStr;
  wxString msg;
  gaiaShapefilePtr shp = NULL;
  gaiaDbfFieldPtr dbf_field;
  bool sqlError = false;
  double minx = DBL_MAX;
  double maxx = 0.0 - DBL_MAX;
  double miny = DBL_MAX;
  double maxy = 0.0 - DBL_MAX;
  const char *pkuidName = "PK_UID";
  const char *pkuidDesc = "Unique ID";
  int length = 0;
  int decimals = 0;
  char type[64];
//
// performing some checks before starting
//
  if (TableAlreadyExists(table) == true)
    {
      wxMessageBox(wxT("a table name '") + table + wxT("' already exists"),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  if (SridNotExists(srid) == true)
    {
      wxMessageBox(wxT("invalid SRID value"), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      return;
    }
//
// initalizing the SHP struct
//
  shp = gaiaAllocShapefile();
  gaiaOpenShpRead(shp, path.ToUTF8(), charset.ToUTF8(), "UTF-8");
  if (!(shp->Valid))
    {
      wxString error = wxT("ERROR: invalid Shapefile\n\n");
      if (shp->LastError)
        error += wxString::FromUTF8(shp->LastError);
      gaiaFreeShapefile(shp);
      wxMessageBox(error, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      return;
    }
  ::wxBeginBusyCursor();
//
// checking for duplicate / illegal column names and antialising them 
//
  col_cnt = 0;
  dbf_field = shp->Dbf->First;
  while (dbf_field)
    {
      // counting DBF fields
      col_cnt++;
      dbf_field = dbf_field->Next;
    }
  col_name = (char **) malloc(sizeof(char *) * col_cnt);
  cnt = 0;
  seed = 0;
  dbf_field = shp->Dbf->First;
  while (dbf_field)
    {
      // preparing column names
      strcpy(dummyName, dbf_field->Name);
      dup = 0;
      for (idup = 0; idup < cnt; idup++)
        {
          if (strcasecmp(dummyName, *(col_name + idup)) == 0)
            dup = 1;
        }
      if (strcasecmp(dummyName, "PK_UID") == 0)
        dup = 1;
      if (strcasecmp(dummyName, column.ToUTF8()) == 0)
        dup = 1;
      if (dup)
        sprintf(dummyName, "COL_%d", seed++);
      len = strlen(dummyName);
      *(col_name + cnt) = (char *) malloc(len + 1);
      strcpy(*(col_name + cnt), dummyName);
      cnt++;
      dbf_field = dbf_field->Next;
    }
//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("load shapefile error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      sqlError = true;
      goto clean_up;
    }
//
// creating the Table 
//
  strcpy(xtable, table.ToUTF8());
  strcpy(xcolumn, column.ToUTF8());
  sprintf(sql, "CREATE TABLE \"%s\"", xtable);
  strcat(sql, " (\nPK_UID INTEGER PRIMARY KEY AUTOINCREMENT");
  cnt = 0;
  dbf_field = shp->Dbf->First;
  while (dbf_field)
    {
      strcat(sql, ",\n\"");
      strcat(sql, *(col_name + cnt));
      cnt++;
      switch (dbf_field->Type)
        {
          case 'C':
            strcat(sql, "\" TEXT");
            break;
          case 'N':
            if (dbf_field->Decimals)
              strcat(sql, "\" DOUBLE");
            else
              {
                if (dbf_field->Length <= 18)
                  strcat(sql, "\" INTEGER");
                else
                  strcat(sql, "\" DOUBLE");
              }
            break;
          case 'D':
            strcat(sql, "\" DOUBLE");
            break;
          case 'F':
            strcat(sql, "\" DOUBLE");
            break;
          case 'L':
            strcat(sql, "\" INTEGER");
            break;
        };
      dbf_field = dbf_field->Next;
    }
  strcat(sql, ")");
  ret = sqlite3_exec(SqliteHandle, sql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("load shapefile error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      sqlError = true;
      goto clean_up;
    }
  // creating Geometry column 
  switch (shp->Shape)
    {
      case GAIA_SHP_POINT:
      case GAIA_SHP_POINTM:
      case GAIA_SHP_POINTZ:
        geom_type = "POINT";
        break;
      case GAIA_SHP_MULTIPOINT:
      case GAIA_SHP_MULTIPOINTM:
      case GAIA_SHP_MULTIPOINTZ:
        geom_type = "MULTIPOINT";
        break;
      case GAIA_SHP_POLYLINE:
      case GAIA_SHP_POLYLINEM:
      case GAIA_SHP_POLYLINEZ:
        gaiaShpAnalyze(shp);
        if (shp->EffectiveType == GAIA_LINESTRING)
          geom_type = "LINESTRING";
        else
          geom_type = "MULTILINESTRING";
        break;
      case GAIA_SHP_POLYGON:
      case GAIA_SHP_POLYGONM:
      case GAIA_SHP_POLYGONZ:
        gaiaShpAnalyze(shp);
        if (shp->EffectiveType == GAIA_POLYGON)
          geom_type = "POLYGON";
        else
          geom_type = "MULTIPOLYGON";
        break;
    };
  if (coerce2D == true)
    shp->EffectiveDims = GAIA_XY;
  switch (shp->EffectiveDims)
    {
      case GAIA_XY_Z:
        txt_dims = "XYZ";
        break;
      case GAIA_XY_M:
        txt_dims = "XYM";
        break;
      case GAIA_XY_Z_M:
        txt_dims = "XYZM";
        break;
      default:
        txt_dims = "XY";
        break;
    };
  sprintf(sql, "SELECT AddGeometryColumn('%s', '%s', %d, '%s', '%s')", xtable,
          xcolumn, srid, geom_type, txt_dims);
  ret = sqlite3_exec(SqliteHandle, sql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("load shapefile error:") +
                   wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      sqlError = true;
      goto clean_up;
    }
// preparing the INSERT INTO parametrerized statement
  sprintf(sql, "INSERT INTO \"%s\" (PK_UID,", xtable);
  cnt = 0;
  dbf_field = shp->Dbf->First;
  while (dbf_field)
    {
      // columns corresponding to some DBF attribute 
      strcat(sql, "\"");
      strcat(sql, *(col_name + cnt));
      cnt++;
      strcat(sql, "\",");
      dbf_field = dbf_field->Next;
    }
  strcat(sql, xcolumn);         // the GEOMETRY column
  strcat(sql, ")\nVALUES (? ");
  dbf_field = shp->Dbf->First;
  while (dbf_field)
    {
      // column values
      strcat(sql, ", ?");
      dbf_field = dbf_field->Next;
    }
  strcat(sql, ", ?)");          // the GEOMETRY column
  ret = sqlite3_prepare_v2(SqliteHandle, sql, strlen(sql), &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("load shapefile error: ") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlError = true;
      goto clean_up;
    }
  current_row = 0;
  while (1)
    {
      //
      // inserting rows from shapefile 
      //
      ret = gaiaReadShpEntity(shp, current_row, srid);
      if (!ret)
        {
          if (!(shp->LastError))  // normal SHP EOF
            break;
          wxMessageBox(wxT("load shapefile error:") +
                       wxString::FromUTF8(shp->LastError),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlError = true;
          goto clean_up;
        }
      current_row++;
      // binding query params
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      sqlite3_bind_int(stmt, 1, current_row);
      cnt = 0;
      dbf_field = shp->Dbf->First;
      while (dbf_field)
        {
          // column values
          if (!(dbf_field->Value))
            sqlite3_bind_null(stmt, cnt + 2);
          else
            {
              switch (dbf_field->Value->Type)
                {
                  case GAIA_INT_VALUE:
                    sqlite3_bind_int64(stmt, cnt + 2,
                                       dbf_field->Value->IntValue);
                    break;
                  case GAIA_DOUBLE_VALUE:
                    sqlite3_bind_double(stmt, cnt + 2,
                                        dbf_field->Value->DblValue);
                    break;
                  case GAIA_TEXT_VALUE:
                    sqlite3_bind_text(stmt, cnt + 2,
                                      dbf_field->Value->TxtValue,
                                      strlen(dbf_field->Value->TxtValue),
                                      SQLITE_STATIC);
                    break;
                  default:
                    sqlite3_bind_null(stmt, cnt + 2);;
                    break;
                };
            }
          cnt++;
          dbf_field = dbf_field->Next;
        }
      if (shp->Dbf->Geometry)
        {
          if (compressed == true)
            gaiaToCompressedBlobWkb(shp->Dbf->Geometry, &blob, &blob_size);
          else
            gaiaToSpatiaLiteBlobWkb(shp->Dbf->Geometry, &blob, &blob_size);
          if (shp->Dbf->Geometry->MinX < minx)
            minx = shp->Dbf->Geometry->MinX;
          if (shp->Dbf->Geometry->MaxX > maxx)
            maxx = shp->Dbf->Geometry->MaxX;
          if (shp->Dbf->Geometry->MinY < miny)
            miny = shp->Dbf->Geometry->MinY;
          if (shp->Dbf->Geometry->MaxY > maxy)
            maxy = shp->Dbf->Geometry->MaxY;
          sqlite3_bind_blob(stmt, cnt + 2, blob, blob_size, free);
      } else
        {
          /* handling a NULL-Geometry */
          sqlite3_bind_null(stmt, cnt + 2);
        }
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("load shapefile error:") + err,
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          sqlError = true;
          goto clean_up;
        }
      rows++;
    }
  sqlite3_finalize(stmt);

clean_up:
  int red;
  int green;
  int blue;
  int geomType = LAYER_GEOMETRY;
  bool multiType = false;
  if (strcasecmp(geom_type, "POINT") == 0
      || strcasecmp(geom_type, "MULTIPOINT") == 0)
    geomType = LAYER_POINT;
  if (strcasecmp(geom_type, "LINESTRING") == 0
      || strcasecmp(geom_type, "MULTILINESTRING") == 0)
    geomType = LAYER_LINESTRING;
  if (strcasecmp(geom_type, "POLYGON") == 0
      || strcasecmp(geom_type, "MULTIPOLYGON") == 0)
    geomType = LAYER_POLYGON;
  if (strcasecmp(geom_type, "MULTIPOINT") == 0
      || strcasecmp(geom_type, "MULTILINESTRING") == 0
      || strcasecmp(geom_type, "MULTIPOLYGON") == 0)
    multiType = true;
  LayerObject layer(table, column, srid, geomType, multiType);
  if (geomType == LAYER_POINT)
    {
      GetRandomColor(&red, &green, &blue);
      wxColour col1(red, green, blue);
      GetRandomColor(&red, &green, &blue);
      wxColour col2(red, green, blue);
      layer.SetPointGraphics(1, col1, col2);
    }
  if (geomType == LAYER_LINESTRING)
    {
      GetRandomColor(&red, &green, &blue);
      wxColour color(red, green, blue);
      layer.SetLineGraphics(color, 1, wxSOLID);
    }
  if (geomType == LAYER_POLYGON)
    {
      GetRandomColor(&red, &green, &blue);
      wxColour col1(red, green, blue);
      GetRandomColor(&red, &green, &blue);
      wxColour col2(red, green, blue);
      layer.SetPolygonGraphics(col1, 1, wxSOLID, col2);
    }
  layer.PrepareStaticValues();
  if (sqlError == false)
    {
      // trying to insert a new layer into the 'layer_params' table
      if (InsertLayerParams(&layer) == false)
        sqlError = true;
    }
  if (sqlError == false)
    {
      // trying to insert a new layer into the 'layer_statistics' table
      if (InsertLayerStatistics(&layer, rows, minx, miny, maxx, maxy) == false)
        sqlError = true;
    }
// inserting into layer_table_layout
  strcpy(sql, "INSERT INTO layer_table_layout ");
  strcat(sql, "(table_name, geometry_column, column_name, desc_name, ");
  strcat(sql, "data_type, length, decimals) VALUES (?, ?, ?, ?, ?, ?, ?)");
  ret = sqlite3_prepare_v2(SqliteHandle, sql, strlen(sql), &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlError = true;
      goto clean_up2;
    }
// inserting the PK_UID column anyway
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  sqlite3_bind_text(stmt, 1, xtable, strlen(xtable), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, xcolumn, strlen(xcolumn), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, pkuidName, strlen(pkuidName), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, pkuidDesc, strlen(pkuidDesc), SQLITE_STATIC);
  strcpy(type, "INTEGER");
  sqlite3_bind_text(stmt, 5, type, strlen(type), SQLITE_STATIC);
  sqlite3_bind_null(stmt, 6);
  sqlite3_bind_null(stmt, 7);
  ret = sqlite3_step(stmt);
  if (ret == SQLITE_DONE || ret == SQLITE_ROW)
    ;
  else
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_finalize(stmt);
      sqlError = true;
      goto clean_up2;
    }
  cnt = 0;
  dbf_field = shp->Dbf->First;
  while (dbf_field)
    {
      // inserting the other attributes
      strcpy(type, "TEXT");
      char *colName = *(col_name + cnt);
      cnt++;
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      sqlite3_bind_text(stmt, 1, xtable, strlen(xtable), SQLITE_STATIC);
      sqlite3_bind_text(stmt, 2, xcolumn, strlen(xcolumn), SQLITE_STATIC);
      sqlite3_bind_text(stmt, 3, colName, strlen(colName), SQLITE_STATIC);
      sqlite3_bind_null(stmt, 4);
      switch (dbf_field->Type)
        {
          case 'C':
            strcpy(type, "TEXT");
            length = dbf_field->Length;
            break;
          case 'N':
            if (dbf_field->Decimals)
              {
                strcpy(type, "DOUBLE");
                decimals = dbf_field->Decimals;
            } else
              {
                if (dbf_field->Length <= 18)
                  strcpy(type, "INTEGER");
                else
                  {
                    strcpy(type, "DOUBLE");
                    decimals = 1;
                  }
              }
            break;
          case 'D':
            strcpy(type, "DATE");
            break;
          case 'L':
            strcpy(type, "BOOLEAN");
            break;
        };
      sqlite3_bind_text(stmt, 5, type, strlen(type), SQLITE_STATIC);
      if (length <= 0)
        sqlite3_bind_null(stmt, 6);
      else
        sqlite3_bind_int(stmt, 6, length);
      if (decimals <= 0)
        sqlite3_bind_null(stmt, 7);
      else
        sqlite3_bind_int(stmt, 7, decimals);
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          sqlError = true;
          goto clean_up2;
        }
      dbf_field = dbf_field->Next;
    }
  sqlite3_finalize(stmt);

clean_up2:
  gaiaFreeShapefile(shp);
  if (col_name)
    {
      // releasing memory allocation for column names 
      for (cnt = 0; cnt < col_cnt; cnt++)
        free(*(col_name + cnt));
      free(col_name);
    }
  if (sqlError == true)
    {
      // some error occurred - ROLLBACK 
      ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("load shapefile error:") +
                       wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
        }
      ::wxEndBusyCursor();
      msg =
        wxT("Shapefile not loaded\n\n\na ROLLBACK was automatically performed");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
  } else
    {
      // ok - confirming pending transaction - COMMIT 
      ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("load shapefile error:") +
                       wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      ::wxEndBusyCursor();
      sprintf(dummyName, "Shapefile loaded\n\n%d inserted rows", rows);
      msg = wxString::FromUTF8(dummyName);
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION, this);
      InitLayerTree();
      MapView->ComputeMapExtent();
      MapView->SetFrameFullExtent();
      MapView->PrepareMap();
    }
}

gaiaDbfFieldPtr MyFrame::GetDbfField(gaiaDbfListPtr list, char *name)
{
//
// find a DBF attribute by name 
//
  gaiaDbfFieldPtr fld = list->First;
  while (fld)
    {
      if (strcasecmp(fld->Name, name) == 0)
        return fld;
      fld = fld->Next;
    }
  return NULL;
}

void MyFrame::DumpShapefile(wxString & path, wxString & table,
                            wxString & column, wxString & charset, bool isView)
{
//
// dumping a  geometry table as Shapefile
//
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  char *gtype;
  char *gdims;
  wxString geometryType;
  wxString geometryDims;
  int shape = -1;
  char xtable[1024];
  char xcolumn[1024];
  char xpath[1024];
  char xsql[4096];
  sqlite3_stmt *stmt;
  int row1 = 0;
  int n_cols = 0;
  int offset = 0;
  int type;
  int multiple_entities = 0;
  const unsigned char *char_value;
  const void *blob_value;
  gaiaShapefilePtr shp = NULL;
  gaiaDbfListPtr dbf_export_list = NULL;
  gaiaDbfListPtr dbf_list = NULL;
  gaiaDbfListPtr dbf_write;
  gaiaDbfFieldPtr dbf_field;
  gaiaGeomCollPtr geom;
  int *max_length = NULL;
  int *sql_type = NULL;
  char dummy[1024];
  int len;
  wxString msg;
  int ret;
  if (isView == true)
    {
      wxString sql =
        wxT("SELECT type, coord_dimension FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += table;
      sql += wxT("' AND view_geometry = '");
      sql += column;
      sql += wxT("'");
      ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("dump shapefile error:") +
                       wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              gtype = results[(i * columns) + 0];
              geometryType = wxString::FromUTF8(gtype);
              gdims = results[(i * columns) + 1];
              geometryDims = wxString::FromUTF8(gdims);
            }
        }
      sqlite3_free_table(results);
  } else
    {
      wxString sql =
        wxT
        ("SELECT type, coord_dimension FROM geometry_columns WHERE f_table_name = '");
      sql += table;
      sql += wxT("' AND f_geometry_column = '");
      sql += column;
      sql += wxT("'");
      ret = sqlite3_get_table(SqliteHandle, sql.ToUTF8(), &results,
                              &rows, &columns, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("dump shapefile error:") +
                       wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          return;
        }
      if (rows < 1)
        ;
      else
        {
          for (i = 1; i <= rows; i++)
            {
              gtype = results[(i * columns) + 0];
              geometryType = wxString::FromUTF8(gtype);
              gdims = results[(i * columns) + 1];
              geometryDims = wxString::FromUTF8(gdims);
            }
        }
      sqlite3_free_table(results);
    }
  if (geometryType == wxT("POINT"))
    {
      if (geometryDims == wxT("XYZ") || geometryDims == wxT("3"))
        shape = GAIA_POINTZ;
      else if (geometryDims == wxT("XYM"))
        shape = GAIA_POINTM;
      else if (geometryDims == wxT("XYZM"))
        shape = GAIA_POINTZM;
      else
        shape = GAIA_POINT;
    }
  if (geometryType == wxT("MULTIPOINT"))
    {
      if (geometryDims == wxT("XYZ") || geometryDims == wxT("3"))
        shape = GAIA_MULTIPOINTZ;
      else if (geometryDims == wxT("XYM"))
        shape = GAIA_MULTIPOINTM;
      else if (geometryDims == wxT("XYZM"))
        shape = GAIA_MULTIPOINTZM;
      else
        shape = GAIA_MULTIPOINT;
    }
  if (geometryType == wxT("LINESTRING")
      || geometryType == wxT("MULTILINESTRING"))
    {
      if (geometryDims == wxT("XYZ") || geometryDims == wxT("3"))
        shape = GAIA_LINESTRINGZ;
      else if (geometryDims == wxT("XYM"))
        shape = GAIA_LINESTRINGM;
      else if (geometryDims == wxT("XYZM"))
        shape = GAIA_LINESTRINGZM;
      else
        shape = GAIA_LINESTRING;
    }
  if (geometryType == wxT("POLYGON") || geometryType == wxT("MULTIPOLYGON"))
    {
      if (geometryDims == wxT("XYZ") || geometryDims == wxT("3"))
        shape = GAIA_POLYGONZ;
      else if (geometryDims == wxT("XYM"))
        shape = GAIA_POLYGONM;
      else if (geometryDims == wxT("XYZM"))
        shape = GAIA_POLYGONZM;
      else
        shape = GAIA_POLYGON;
    }
  if (shape < 0)
    {
      wxMessageBox(wxT("Unable to detect GeometryType for '") +
                   table + wxT(".") + column + wxT("'"), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      return;
    }
//
// preparing SQL statement 
//
  strcpy(xtable, table.ToUTF8());
  strcpy(xcolumn, column.ToUTF8());
  sprintf(xsql, "SELECT * FROM \"%s\" WHERE GeometryAliasType(\"%s\") = ",
          xtable, xcolumn);
  if (shape == GAIA_LINESTRING || shape == GAIA_LINESTRINGZ
      || shape == GAIA_LINESTRINGM || shape == GAIA_LINESTRINGZM)
    {
      strcat(xsql, "'LINESTRING' OR GeometryAliasType(\"");
      strcat(xsql, xcolumn);
      strcat(xsql, "\") = 'MULTILINESTRING'");
  } else if (shape == GAIA_POLYGON || shape == GAIA_POLYGONZ
             || shape == GAIA_POLYGONM || shape == GAIA_POLYGONZM)
    {
      strcat(xsql, "'POLYGON' OR GeometryAliasType(\"");
      strcat(xsql, xcolumn);
      strcat(xsql, "\") = 'MULTIPOLYGON'");
  } else if (shape == GAIA_MULTIPOINT || shape == GAIA_MULTIPOINTZ
             || shape == GAIA_MULTIPOINTM || shape == GAIA_MULTIPOINTZM)
    {
      strcat(xsql, "'POINT' OR GeometryAliasType(\"");
      strcat(xsql, xcolumn);
      strcat(xsql, "\") = 'MULTIPOINT'");
  } else
    strcat(xsql, "'POINT'");
// fetching anyway NULL Geometries 
  strcat(xsql, " OR \"");
  strcat(xsql, xcolumn);
  strcat(xsql, "\" IS NULL");
//
// compiling SQL prepared statement 
//
  ret = sqlite3_prepare_v2(SqliteHandle, xsql, strlen(xsql), &stmt, NULL);
  if (ret != SQLITE_OK)
    goto sql_error;
  rows = 0;
  while (1)
    {
      //
      // Pass I - scrolling the result set to compute real DBF attributes' sizes and types 
      //
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          // processing a result set row 
          row1++;
          if (n_cols == 0)
            {
              // this one is the first row, so we are going to prepare the DBF Fields list 
              n_cols = sqlite3_column_count(stmt);
              dbf_export_list = gaiaAllocDbfList();
              max_length = (int *) malloc(sizeof(int) * n_cols);
              sql_type = (int *) malloc(sizeof(int) * n_cols);
              for (i = 0; i < n_cols; i++)
                {
                  // initializes the DBF export fields
                  strcpy(dummy, sqlite3_column_name(stmt, i));
                  gaiaAddDbfField(dbf_export_list, dummy, '\0', 0, 0, 0);
                  max_length[i] = 0;
                  sql_type[i] = SQLITE_NULL;
                }
            }
          for (i = 0; i < n_cols; i++)
            {
              // update the DBF export fields analyzing fetched data
              type = sqlite3_column_type(stmt, i);
              if (type == SQLITE_BLOB && strcasecmp((char *) xcolumn,
                                                    (char *)
                                                    sqlite3_column_name(stmt,
                                                                        i)) == 0
                  && shape == GAIA_POINT)
                {
                  // 
                  // we need to check if there is any MULTIPOINT,
                  // because shapefile handles simple-points shapes and multi-points shapes
                  // in a complete differet way
                  //
                  blob_value = sqlite3_column_blob(stmt, i);
                  len = sqlite3_column_bytes(stmt, i);
                  geom =
                    gaiaFromSpatiaLiteBlobWkb((unsigned char *) blob_value,
                                              len);
                  if (geom)
                    {
                      if (geom->FirstPoint != geom->LastPoint)
                        multiple_entities = 1;
                      gaiaFreeGeomColl(geom);
                    }
                }
              if (type == SQLITE_NULL || type == SQLITE_BLOB)
                continue;
              if (type == SQLITE_TEXT)
                {
                  char_value = sqlite3_column_text(stmt, i);
                  len = sqlite3_column_bytes(stmt, i);
                  sql_type[i] = SQLITE_TEXT;
                  if (len > max_length[i])
                    max_length[i] = len;
              } else if (type == SQLITE_FLOAT && sql_type[i] != SQLITE_TEXT)
                sql_type[i] = SQLITE_FLOAT; // promoting a numeric column to be DOUBLE
              else if (type == SQLITE_INTEGER
                       && (sql_type[i] == SQLITE_NULL
                           || sql_type[i] == SQLITE_INTEGER))
                sql_type[i] = SQLITE_INTEGER; // promoting a null column to be INTEGER
              if (type == SQLITE_INTEGER && max_length[i] < 18)
                max_length[i] = 18;
              if (type == SQLITE_FLOAT && max_length[i] < 24)
                max_length[i] = 24;
            }
      } else
        goto sql_error;
    }
  if (!row1)
    goto empty_result_set;
  i = 0;
  offset = 0;
  dbf_list = gaiaAllocDbfList();
  dbf_field = dbf_export_list->First;
  while (dbf_field)
    {
      // preparing the final DBF attribute list 
      if (sql_type[i] == SQLITE_NULL)
        {
          i++;
          dbf_field = dbf_field->Next;
          continue;
        }
      if (sql_type[i] == SQLITE_TEXT)
        {
          gaiaAddDbfField(dbf_list, dbf_field->Name, 'C', offset, max_length[i],
                          0);
          offset += max_length[i];
        }
      if (sql_type[i] == SQLITE_FLOAT)
        {
          gaiaAddDbfField(dbf_list, dbf_field->Name, 'N', offset, 24, 6);
          offset += 24;
        }
      if (sql_type[i] == SQLITE_INTEGER)
        {
          gaiaAddDbfField(dbf_list, dbf_field->Name, 'N', offset, 18, 0);
          offset += 18;
        }
      i++;
      dbf_field = dbf_field->Next;
    }
  free(max_length);
  free(sql_type);
  gaiaFreeDbfList(dbf_export_list);
// resetting SQLite query 
  ret = sqlite3_reset(stmt);
  if (ret != SQLITE_OK)
    goto sql_error;
// trying to open shapefile files 
  shp = gaiaAllocShapefile();
  strcpy(xpath, path.ToUTF8());
  gaiaOpenShpWrite(shp, xpath, shape, dbf_list, "UTF-8", charset.ToUTF8());
  if (!(shp->Valid))
    goto no_file;
  while (1)
    {
      // Pass II - scrolling the result set to dump data into shapefile 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          rows++;
          geom = NULL;
          dbf_write = gaiaCloneDbfEntity(dbf_list);
          for (i = 0; i < n_cols; i++)
            {
              if (strcasecmp
                  ((char *) xcolumn,
                   (char *) sqlite3_column_name(stmt, i)) == 0)
                {
                  // this one is the internal BLOB encoded GEOMETRY to be exported 
                  if (sqlite3_column_type(stmt, i) != SQLITE_BLOB)
                    {
                      // this one is a NULL Geometry
                      dbf_write->Geometry = NULL;
                  } else
                    {
                      blob_value = sqlite3_column_blob(stmt, i);
                      len = sqlite3_column_bytes(stmt, i);
                      dbf_write->Geometry =
                        gaiaFromSpatiaLiteBlobWkb((unsigned char *) blob_value,
                                                  len);
                    }
                }
              strcpy(dummy, sqlite3_column_name(stmt, i));
              dbf_field = GetDbfField(dbf_write, dummy);
              if (!dbf_field)
                continue;
              if (sqlite3_column_type(stmt, i) == SQLITE_NULL)
                {
                  // handling NULL values
                  gaiaSetNullValue(dbf_field);
              } else
                {
                  switch (dbf_field->Type)
                    {
                      case 'N':
                        if (sqlite3_column_type(stmt, i) == SQLITE_INTEGER)
                          gaiaSetIntValue(dbf_field,
                                          sqlite3_column_int64(stmt, i));
                        else if (sqlite3_column_type(stmt, i) == SQLITE_FLOAT)
                          gaiaSetDoubleValue(dbf_field,
                                             sqlite3_column_double(stmt, i));
                        else
                          gaiaSetNullValue(dbf_field);
                        break;
                      case 'C':
                        if (sqlite3_column_type(stmt, i) == SQLITE_TEXT)
                          {
                            strcpy(dummy,
                                   (char *) sqlite3_column_text(stmt, i));
                            gaiaSetStrValue(dbf_field, dummy);
                        } else if (sqlite3_column_type(stmt, i) ==
                                   SQLITE_INTEGER)
                          {
#if defined(_WIN32) || defined(__MINGW32__)
                            /* CAVEAT - M$ runtime doesn't supports %lld for 64 bits */
                            sprintf(dummy, "%I64d",
                                    sqlite3_column_int64(stmt, i));
#else
                            sprintf(dummy, "%lld",
                                    sqlite3_column_int64(stmt, i));
#endif
                            gaiaSetStrValue(dbf_field, dummy);
                        } else if (sqlite3_column_type(stmt, i) == SQLITE_FLOAT)
                          {
                            sprintf(dummy, "%1.6f",
                                    sqlite3_column_double(stmt, i));
                            gaiaSetStrValue(dbf_field, dummy);
                        } else
                          gaiaSetNullValue(dbf_field);
                        break;
                    };
                }
            }
          if (!gaiaWriteShpEntity(shp, dbf_write))
            {
              wxMessageBox(wxT("Shapefile write error"), wxT("spatialite-gis"),
                           wxOK | wxICON_INFORMATION, this);
            }
          gaiaFreeDbfList(dbf_write);
      } else
        goto sql_error;
    }
  sqlite3_finalize(stmt);
  gaiaFlushShpHeaders(shp);
  gaiaFreeShapefile(shp);
  sprintf(dummy, "Exported %d rows into Shapefile", rows);
  msg = wxString::FromUTF8(dummy);
  wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION, this);
  return;
sql_error:
//
// some SQL error occurred
//
  sqlite3_finalize(stmt);
  if (dbf_export_list)
    gaiaFreeDbfList(dbf_export_list);
  if (dbf_list)
    gaiaFreeDbfList(dbf_list);
  if (shp)
    gaiaFreeShapefile(shp);
  wxMessageBox(wxT("dump shapefile error:") +
               wxString::FromUTF8(sqlite3_errmsg(SqliteHandle)),
               wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
  return;
no_file:
//
// shapefile can't be created/opened
//
  if (dbf_export_list)
    gaiaFreeDbfList(dbf_export_list);
  if (dbf_list)
    gaiaFreeDbfList(dbf_list);
  if (shp)
    gaiaFreeShapefile(shp);
  wxMessageBox(wxT("ERROR: unable to open '") + path + wxT("' for writing"),
               wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
  return;
empty_result_set:
//
// the result set is empty - nothing to do 
//
  sqlite3_finalize(stmt);
  if (dbf_export_list)
    gaiaFreeDbfList(dbf_export_list);
  if (dbf_list)
    gaiaFreeDbfList(dbf_list);
  if (shp)
    gaiaFreeShapefile(shp);
  wxMessageBox(wxT
               ("The SQL SELECT returned an empty result set\n... there is nothing to export ..."),
               wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
}

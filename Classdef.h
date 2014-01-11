/*
/ Classdef.h
/ class definitions for spatialite-gis  - the SpatiaLite GIS Viewer
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

#include "wx/wx.h"
#include "wx/aui/aui.h"
#include "wx/treectrl.h"
#include "wx/tipwin.h"
#include "wx/spinctrl.h"
#include "wx/listctrl.h"
#include "wx/grid.h"

#ifdef SPATIALITE_AMALGAMATION
#include <spatialite/sqlite3.h>
#else
#include <sqlite3.h>
#endif
#include <spatialite/gaiageo.h>

#include <rasterlite.h>

#include <hpdf.h>

#if defined(__MINGW32__) || defined(_WIN32)
#define LIBICONV_STATIC
#endif /* not WINDOWS */
#include <iconv.h>

enum
{
// control IDs for main window and tree list control
  ID_Connect = 1,
  ID_CreateNew,
  ID_Disconnect,
  ID_MemoryDbLoad,
  ID_MemoryDbNew,
  ID_MemoryDbClock,
  ID_MemoryDbSave,
  ID_Vacuum,
  ID_MapFrameSel,
  ID_MapFrameAll,
  ID_OutputMap,
  ID_Crs,
  ID_LoadShp,
  ID_TableAdd,
  ID_Srids,
  ID_Charset,
  ID_LineMeter,
  ID_PolygonMeter,
  ID_Draw,
  ID_DrawInterpolate,
  ID_DrawDelete,
  ID_DrawMove,
  ID_DrawDeleteSubGeom,
  ID_DrawSplitLine,
  ID_DrawSelectMultiGeom,
  ID_Zoom,
  ID_Center,
  ID_Up,
  ID_Down,
  ID_Left,
  ID_Right,
  ID_ZoomMin,
  ID_ZoomMax,
  ID_DrawAbort,
  ID_DrawUndo,
  ID_DrawStop,
  ID_MicroUp,
  ID_MicroDown,
  ID_MicroLeft,
  ID_MicroRight,
  ID_ZoomIn,
  ID_ZoomOut,
  ID_ZoomMicroIn,
  ID_ZoomMicroOut,
  ID_EditMode,
  ID_Identify,
  ID_NodeFrom,
  ID_NodeTo,
  ID_ReturnTrip,
  ID_RouteClear,
  ID_RoutingAlgorithm,
  Tree_ShowAll,
  Tree_HideAll,
  Tree_Refresh,
  Tree_Visible,
  Tree_Identify,
  Tree_LayerExtent,
  Tree_Crs,
  Tree_ScaleVisibility,
  Tree_Labels,
  Tree_Graphics,
  Tree_Classify,
  Tree_ClassesDrop,
  Tree_Statistics,
  Tree_SpatialIndex,
  Tree_MbrCache,
  Tree_DumpShp,
  Tree_DeleteLayer,
  Tree_ShowTable,
  Tree_EditMode,
  Tree_TableLayout,
  Tree_BuildNetwork,
  Tree_DropNetwork,
};

enum
{
// layer types
  LAYER_GEOMETRY = 1,
  LAYER_POINT,
  LAYER_LINESTRING,
  LAYER_POLYGON,
  RASTER_LAYER,
  VECTOR_LAYER,
  LAYER_SUB_CLASS,
  CLASSES_SYMBOL_CIRCLE,
  CLASSES_SYMBOL_SQUARE,
  CLASSES_SYMBOL_DIAMOND,
  CLASSES_TEXT_TYPE,
  CLASSES_NUMERIC_TYPE,
  CLASSES_INVALID_TYPE,
  SPATIAL_INDEX_NONE,
  SPATIAL_INDEX_RTREE,
  SPATIAL_INDEX_CACHED,
  MY_INT_VARIANT,
  MY_DBL_VARIANT,
  MY_TXT_VARIANT,
  MY_BLOB_VARIANT,
  MY_NULL_VARIANT,
  WHERE_EQ,
  WHERE_LT,
  WHERE_LE,
  WHERE_GT,
  WHERE_GE,
  WHERE_NE,
  WHERE_LIKE,
  WHERE_IS_NULL,
  WHERE_IS_NOT_NULL,
  WHERE_NONE,
  WHERE_INT,
  WHERE_DOUBLE,
  WHERE_TEXT,
  DRAW_MODE_NONE,
  DRAW_MODE_MAP_FRAME,
  DRAW_MODE_LN_METER,
  DRAW_MODE_PG_METER,
  DRAW_MODE_DRAW,
  DRAW_MODE_INTERPOLATE,
  DRAW_MODE_DELETE,
  DRAW_MODE_MOVE,
  DRAW_MODE_DELETE_SUB,
  DRAW_MODE_SPLIT,
  DRAW_MODE_SELECT,
  SQLITE_IMAGE,
  SQLITE_DATE,
  SQLITE_DATETIME,
  SQLITE_BOOLEAN,
};

enum
{
// control IDs for dialogs
  ID_LAYER_SRID = 10000,
  ID_LAYER_SRID_NAME,
  ID_LAYER_SRID_PARAMS,
  ID_PROJECT_NAME,
  ID_PROJECT_SRID,
  ID_PROJECT_AUTH_SRID,
  ID_PROJECT_SRID_NAME,
  ID_PROJECT_SRID_PARAMS,
  ID_PROJECT_UNITS_NAME,
  ID_PROJECT_DMS,
  ID_REPROJECT,
  ID_RANGE_VISIBILITY,
  ID_RANGE_MIN_SCALE,
  ID_RANGE_MAX_SCALE,
  ID_LABEL_LABEL,
  ID_LABEL_ENABLED,
  ID_LABEL_COLOR,
  ID_LABEL_ALPHA,
  ID_LABEL_SIZE,
  ID_LABEL_WEIGHT,
  ID_LABEL_STYLE,
  ID_LABEL_UNDERLINE,
  ID_LABEL_OUTLINE,
  ID_LABEL_PRIORITY,
  ID_LABEL_ORDER_BY,
  ID_LABEL_DESCENDING,
  ID_LABEL_VISIBILITY,
  ID_LABEL_MIN_SCALE,
  ID_LABEL_MAX_SCALE,
  ID_LABEL_ANTI_OVERLAP,
  ID_LABEL_EXAMPLE,
  ID_POINT_EXAMPLE,
  ID_POINT_SYMBOLS,
  ID_POINT_FOREGROUND,
  ID_POINT_BACKGROUND,
  ID_LINE_EXAMPLE,
  ID_LINE_COLOR,
  ID_LINE_ALPHA,
  ID_LINE_THICKNESS,
  ID_LINE_STYLE,
  ID_POLYGON_EXAMPLE,
  ID_POLYGON_BORDER_COLOR,
  ID_POLYGON_BORDER_ALPHA,
  ID_POLYGON_BORDER_THICKNESS,
  ID_POLYGON_BORDER_STYLE,
  ID_POLYGON_BORDER_MODE,
  ID_POLYGON_FILL_MODE,
  ID_POLYGON_FILL_COLOR,
  ID_POLYGON_FILL_ALPHA,
  ID_POLYGON_PATTERNS,
  ID_CLASSES_COLUMN,
  ID_CLASSES_MODE,
  ID_CLASSES_NUM,
  ID_CLASSES_SYMBOL,
  ID_CLASSES_MIN_SIZE,
  ID_CLASSES_MAX_SIZE,
  ID_CLASSES_MIN_COLOR,
  ID_CLASSES_MAX_COLOR,
  ID_CLASSES_PREVIEW,
  ID_CLASSES_DISPLAY,
  ID_CLASSES_REBUILD,
  ID_CLASSES_RANDOMIZE,
  ID_CLASSES_HUE,
  ID_CLASSES_TRANSPARENCY,
  ID_CLASSES_SIZE,
  ID_CLASSES_COLOR,
  ID_CLASSES_RANDOMIZE_SKIP,
  ID_CLASSES_MIN_VALUE,
  ID_CLASSES_MAX_VALUE,
  ID_CLASSES_CMD_SYMBOL,
  ID_CLASSES_CMD_SIZE,
  ID_CLASSES_CMD_RANGE,
  ID_CLASSES_CMD_COLOR,
  ID_LDSHP_TABLE,
  ID_LDSHP_COLUMN,
  ID_LDSHP_SRID,
  ID_LDSHP_CHARSET,
  ID_LDSHP_COERCE_2D,
  ID_LDSHP_COMPRESSED,
  ID_DMPSHP_CHARSET,
  ID_DFLT_CHARSET,
  ID_DFLT_ASK,
  ID_SRID_TEXT,
  ID_SRID_SEARCH,
  ID_SRID_MODE,
  ID_SRID_GRID,
  ID_IDENTIFY_LIST,
  ID_IDENTIFY_ENTITY,
  ID_IDENTIFY_ENTITY2,
  ID_IDENTIFY_DELETE,
  ID_IDENTIFY_SAVE,
  ID_IDENTIFY_RESTORE,
  ID_IDENTIFY_CLEAR,
  ID_IDENTIFY_ALL,
  ID_IDENTIFY_ROW,
  ID_IDENTIFY_COLUMN,
  ID_IDENTIFY_COPY,
  ID_IDENTIFY_COPY_IMAGE,
  ID_IDENTIFY_BLOB_IN,
  ID_IDENTIFY_BLOB_OUT,
  ID_IDENTIFY_BLOB_NULL,
  ID_IDENTIFY_ALIAS,
  ID_INSERT_ENTITY,
  ID_INSERT_ENTITY2,
  ID_INSERT_BLOB_IN,
  ID_INSERT_BLOB_NULL,
  ID_INSERT_ALIAS,
  ID_TABLE_ROWS,
  ID_TABLE_RS_FIRST,
  ID_TABLE_RS_LAST,
  ID_TABLE_RS_NEXT,
  ID_TABLE_RS_PREVIOUS,
  ID_TABLE_REFRESH,
  ID_TABLE_RS_BLOCK,
  ID_TABLE_COLUMNS,
  ID_TABLE_WHERE_COLUMN,
  ID_TABLE_WHERE_MODE,
  ID_TABLE_WHERE_VALUE,
  ID_TABLE_ORDER_BY1,
  ID_TABLE_ASC_DESC1,
  ID_TABLE_ORDER_BY2,
  ID_TABLE_ASC_DESC2,
  ID_TABLE_ORDER_BY3,
  ID_TABLE_ASC_DESC3,
  ID_TABLE_QUERY,
  ID_TABLE_ZOOM,
  ID_TABLE_CLEAR,
  ID_TABLE_ALL,
  ID_TABLE_ROW,
  ID_TABLE_COLUMN,
  ID_TABLE_COPY,
  ID_TABLE_DELETE,
  ID_TABLE_BLOB_IN,
  ID_TABLE_BLOB_OUT,
  ID_TABLE_BLOB_NULL,
  ID_TABLE_ALIAS,
  ID_TABLE_SAVE,
  ID_TABLE_TOP,
  ID_TABLE_REMOVE_SEL,
  ID_CREATE_TABLE_TABLE,
  ID_CREATE_TABLE_DESC,
  ID_CREATE_TABLE_GEOM,
  ID_CREATE_TABLE_GEOM_TYPE,
  ID_CREATE_TABLE_GEOM_SRID,
  ID_CREATE_TABLE_LIST,
  ID_CREATE_TABLE_COLUMN,
  ID_CREATE_TABLE_COL_DESC,
  ID_CREATE_TABLE_COL_TYPE,
  ID_CREATE_TABLE_COL_LEN,
  ID_CREATE_TABLE_COL_DEC,
  ID_CREATE_TABLE_COL_NULL,
  ID_CREATE_TABLE_COL_CLEAR,
  ID_CREATE_TABLE_COL_ADD,
  ID_CREATE_TABLE_COL_DELETE,
  ID_TABLE_LAYOUT_DESC,
  ID_TABLE_LAYOUT_LIST,
  ID_TABLE_LAYOUT_COLUMN,
  ID_TABLE_LAYOUT_COL_DESC,
  ID_TABLE_LAYOUT_COL_TYPE,
  ID_TABLE_LAYOUT_COL_LEN,
  ID_TABLE_LAYOUT_COL_DEC,
  ID_TABLE_LAYOUT_COL_NULL,
  ID_TABLE_LAYOUT_COL_CLEAR,
  ID_TABLE_LAYOUT_COL_ADD,
  ID_TABLE_LAYOUT_COL_DELETE,
  ID_AUTO_SAVE_PATH,
  ID_AUTO_SAVE_INTERVAL,
  ID_AUTO_SAVE_CHANGE_PATH,
  ID_CREATE_INTERNAL_OPTION,
  ID_ROUTING_GRID,
  ID_ROUTING_ZOOM_ARC,
  ID_ROUTING_ZOOM_ROUTE,
  ID_ROUTING_ZOOM_IN,
  ID_ROUTING_ZOOM_OUT,
  ID_NET_TABLE,
  ID_NET_FROM,
  ID_NET_TO,
  ID_NET_GEOM,
  ID_NET_LENGTH,
  ID_NET_COST,
  ID_NET_BIDIR,
  ID_NET_ONEWAY,
  ID_NET_FROM_TO,
  ID_NET_TO_FROM,
  ID_NET_NAME_ENABLE,
  ID_NET_NAME,
  ID_NET_A_STAR,
  ID_OUTMAP_FORMAT,
  ID_OUTMAP_MODE,
  ID_OUTMAP_WIDTH,
  ID_OUTMAP_HEIGHT,
  ID_OUTMAP_PIXEL,
  ID_OUTMAP_BACKGROUND,
  ID_OUTMAP_WORLDFILE,
  ID_OUTMAP_PAGESIZE,
  ID_OUTMAP_LANDSCAPE,
  ID_OUTMAP_DPI,
};

enum
{
// control IDs for timers
  ID_MOUSE_TIMER = 20000,
  ID_WHEEL_TIMER,
  ID_IDENTIFY_TIMER,
  ID_MARKER_TIMER,
  ID_AUTO_SAVE_TIMER,
};

enum
{
// random colors hue
  RANDOM_COLOR_ALL = 1000,
  RANDOM_COLOR_SATURE,
  RANDOM_COLOR_MEDIUM,
  RANDOM_COLOR_LIGHT,
};

enum
{
// random colors transparency
  RANDOM_COLOR_OPAQUE = 1000,
  RANDOM_COLOR_LIGHT_TRANSPARENT,
  RANDOM_COLOR_MEDIUM_TRANSPARENT,
};

class MyApp:public wxApp
{
//
// the main APP
//
  virtual bool OnInit();
};

class MyVariant
{
//
// a class to store Variant-Type values
//
private:
  int Type;                     // the Variant-Type
  sqlite3_int64 IntValue;       // the Integer value
  double DblValue;              // the Double value
  wxString TxtValue;            // the Text value
  unsigned char *Blob;          // the BLOB value
  int BlobSize;                 // the BLOB size
  bool Error;                   // switch to mark an error condition
public:
    MyVariant()
  {
    Type = MY_NULL_VARIANT;
    Blob = NULL;
    Error = false;
  }
   ~MyVariant()
  {
    if (Blob)
      delete Blob;
  }
  void Clear()
  {
    if (Blob)
      delete Blob;
    Blob = NULL;
    Type = MY_NULL_VARIANT;
  }
  void Set(sqlite3_int64 value)
  {
    Type = MY_INT_VARIANT;
    IntValue = value;
  }
  void Set(double value)
  {
    Type = MY_DBL_VARIANT;
    DblValue = value;
  }
  void Set(const unsigned char *text);
  void Set(wxString & string)
  {
    Type = MY_TXT_VARIANT;
    TxtValue = string;
  }
  void Set(const void *blob, int size);
  void Copy(MyVariant * other);
  int GetType()
  {
    return Type;
  }
  sqlite3_int64 GetIntValue()
  {
    return IntValue;
  }
  double GetDblValue()
  {
    return DblValue;
  }
  wxString & GetTxtValue()
  {
    return TxtValue;
  }
  int GetBlobSize()
  {
    return BlobSize;
  }
  unsigned char *GetBlob()
  {
    return Blob;
  }
  void SetError(bool mode)
  {
    Error = mode;
  }
  bool IsError()
  {
    return Error;
  }
  bool Equals(MyVariant * other);
};

class MyRowVariant
{
//
// a class to store a row composed of Variant-Type values
//
private:
  int NumCols;                  // number of columns
  MyVariant *ColumnArray;       // the column as an array
  bool Deleted;                 // switch to mark a deleted row
  MyRowVariant *Next;           // pointer to next element into the linked list
public:
    MyRowVariant();
    MyRowVariant(int cols);
   ~MyRowVariant();
  void Create(int cols);
  int GetNumCols()
  {
    return NumCols;
  }
  void Set(int col, sqlite3_int64 value);
  void Set(int col, double value);
  void Set(int col, const unsigned char *text);
  void Set(int col, const void *blob, int size);
  MyVariant *GetColumn(int col);
  void SetDeleted()
  {
    Deleted = true;
  }
  bool IsDeleted()
  {
    return Deleted;
  }
  void SetNext(MyRowVariant * next)
  {
    Next = next;
  }
  MyRowVariant *GetNext()
  {
    return Next;
  }
};

class MyVariantList
{
//
// a class to store a whole result set
//
private:
  int NumCols;                  // number of columns
  wxString *ColumnName;         // the column names
  MyRowVariant *First;          // first element into the linked list
  MyRowVariant *Last;           // last element into the linked list
public:
    MyVariantList();
   ~MyVariantList();
  MyRowVariant *Add(int columns);
  void SetColumnName(int col, const char *colName);
  MyRowVariant *GetFirst()
  {
    return First;
  }
  int GetRows();
  int GetColumns()
  {
    return NumCols;
  }
  wxString & GetColumnName(int col);
};

class MyBlobs
{
//
// a class to store BLOBs
//
private:
  int NumRows;                  // the number of rows
  int NumCols;                  // the number of columns
  MyRowVariant *Rows;           // pointer to an array of rows
public:
    MyBlobs(int rows, int cols);
   ~MyBlobs();
  void SetBlob(int row, int col, MyVariant * blobVar);
  MyVariant *GetBlob(int row, int col);
};

class MyValues
{
//
// a class to store column values for editing
//
private:
  int NumRows;                  // the number of rows
  int NumCols;                  // the number of columns
  MyRowVariant *Rows;           // pointer to an array of rows
public:
    MyValues(int rows, int cols);
   ~MyValues();
  void SetValue(int row, int col);
  void SetValue(int row, int col, sqlite3_int64 value);
  void SetValue(int row, int col, double value);
  void SetValue(int row, int col, wxString & string);
  void SetValue(int row, int col, const void *blob, int size);
  void SetError(int row, int col, bool mode);
  MyRowVariant *GetRow(int row);
  MyVariant *GetValue(int row, int col);
};

class QueryColumn
{
//
// a class to store a Table Column [used by SHOW TABLE]
//
private:
  wxString Column;
  wxString Type;
  bool PrimaryKey;
  bool NotNull;
  bool Hidden;
  bool Function;
  wxString DescName;
  int DataType;
  int Length;
  int Decimals;
  QueryColumn *Next;
public:
    QueryColumn(wxString & col, wxString & type, bool pk);
    QueryColumn(wxString & col, wxString & type, bool pk, bool not_null);
   ~QueryColumn()
  {;
  }
  wxString & GetColumn()
  {
    return Column;
  }
  wxString & GetType()
  {
    return Type;
  }
  bool IsPrimaryKey()
  {
    return PrimaryKey;
  }
  bool IsNotNull()
  {
    return NotNull;
  }
  void SetHidden(bool mode)
  {
    Hidden = mode;
  }
  bool IsHidden()
  {
    return Hidden;
  }
  void SetHints(wxString & descName, int type, int len, int dec);
  wxString & GetDescName()
  {
    return DescName;
  }
  int GetDataType()
  {
    return DataType;
  }
  void SetFunction()
  {
    Function = true;
  }
  bool IsFunction()
  {
    return Function;
  }
  bool IsBlobColumn();
  int GetLength()
  {
    return Length;
  }
  int GetDecimals()
  {
    return Decimals;
  }
  void SetNext(QueryColumn * next)
  {
    Next = next;
  }
  QueryColumn *GetNext()
  {
    return Next;
  }
};

class QueryTable
{
//
// a class to store the Table Columns list [used by SHOW TABLE]
//
private:
  QueryColumn * First;
  QueryColumn *Last;
  wxString WhereColumn;
  int WhereCondition;
  int WhereType;
  wxString WhereText;
  long WhereInt;
  double WhereDbl;
  wxString OrderBy1;
  bool Ascending1;
  wxString OrderBy2;
  bool Ascending2;
  wxString OrderBy3;
  bool Ascending3;
public:
    QueryTable();
   ~QueryTable();
  int GetCount();
  QueryColumn *GetFirst()
  {
    return First;
  }
  void Add(wxString & col, wxString & type, bool pk);
  void Add(wxString & col, wxString & type, bool pk, bool not_null);
  void AddFunction(wxString & function, wxString & type);
  void SetHints(wxString & col, wxString & desc, int type, int len, int dec);
  QueryColumn *FindAlias(wxString & col, bool useAlias);
  QueryColumn *Find(wxString & col);
  QueryColumn *Find(int index);
  void SetHiddenStatus(int index, bool mode);
  void ResetWhereClause();
  void SetWhereCondition(int code)
  {
    WhereCondition = code;
  }
  int GetWhereCondition()
  {
    return WhereCondition;
  }
  bool IsWhereClause()
  {
    if (WhereColumn.Len() == 0)
      return false;
    else
      return true;
  }
  void SetWhereColumn(wxString & column)
  {
    WhereColumn = column;
  }
  wxString & GetWhereColumn()
  {
    return WhereColumn;
  }
  void SetWhere()
  {
    WhereType = WHERE_NONE;
  }
  void SetWhere(wxString & text)
  {
    WhereText = text;
    WhereType = WHERE_TEXT;
  }
  void SetWhere(long num)
  {
    WhereInt = num;
    WhereType = WHERE_INT;
  }
  void SetWhere(double num)
  {
    WhereDbl = num;
    WhereType = WHERE_DOUBLE;
  }
  int GetWhereType()
  {
    return WhereType;
  }
  long GetWhereInt()
  {
    return WhereInt;
  }
  double GetWhereDbl()
  {
    return WhereDbl;
  }
  wxString & GetWhereText()
  {
    return WhereText;
  }
  void ResetOrderBy();
  void SetOrderBy1(wxString & column, bool mode)
  {
    OrderBy1 = column;
    Ascending1 = mode;
  }
  void SetOrderBy2(wxString & column, bool mode)
  {
    OrderBy2 = column;
    Ascending2 = mode;
  }
  void SetOrderBy3(wxString & column, bool mode)
  {
    OrderBy3 = column;
    Ascending3 = mode;
  }
  bool OkOrderBy1()
  {
    if (OrderBy1.Len() == 0)
      return false;
    else
      return true;
  }
  wxString & GetOrderBy1()
  {
    return OrderBy1;
  }
  bool IsAscending1()
  {
    return Ascending1;
  }
  bool OkOrderBy2()
  {
    if (OrderBy2.Len() == 0)
      return false;
    else
      return true;
  }
  wxString & GetOrderBy2()
  {
    return OrderBy2;
  }
  bool IsAscending2()
  {
    return Ascending2;
  }
  bool OkOrderBy3()
  {
    if (OrderBy3.Len() == 0)
      return false;
    else
      return true;
  }
  wxString & GetOrderBy3()
  {
    return OrderBy3;
  }
  bool IsAscending3()
  {
    return Ascending3;
  }
};

class IdentifyEntity
{
//
// a class storing a GIS entity [used by IDENTIFY]
//
private:
  sqlite3_int64 RowId;
  gaiaGeomCollPtr Geometry;
  wxString Label;
  bool Deleted;
  bool Changed;
  IdentifyEntity *Next;
public:
    IdentifyEntity(sqlite3_int64 rowid, gaiaGeomCollPtr geom, wxString & label);
   ~IdentifyEntity();
  sqlite3_int64 GetRowId()
  {
    return RowId;
  }
  gaiaGeomCollPtr GetGeometry()
  {
    return Geometry;
  }
  wxString GetLabel()
  {
    return Label;
  }
  bool HasLabel()
  {
    if (Label.Len() > 0)
      return true;
    else
      return false;
  }
  void SetDeleted()
  {
    Deleted = true;
  }
  bool IsDeleted()
  {
    return Deleted;
  }
  void SetChanged()
  {
    Changed = true;
  }
  bool IsChanged()
  {
    return Changed;
  }
  void SetNext(IdentifyEntity * next)
  {
    Next = next;
  }
  IdentifyEntity *GetNext()
  {
    return Next;
  }
};

class IdentifyEntitiesList
{
//
// a list of GIS Entities [used by IDENTIFY]
//
private:
  IdentifyEntity * First;
  IdentifyEntity *Last;
public:
    IdentifyEntitiesList()
  {
    First = NULL;
    Last = NULL;
  }
   ~IdentifyEntitiesList();
  void Add(sqlite3_int64 rowid, gaiaGeomCollPtr geom, wxString & label);
  IdentifyEntity *GetFirst()
  {
    return First;
  }
  IdentifyEntity *GetItemByPos(int index);
  int GetCount();
};

class MyDistinctValue
{
// 
// a class to store DISTINCT values
//
private:
  bool Text;
  wxString TextValue;
  double NumValue;
  wxColour Color;
  int IconIndex;
  bool RandomizeSkip;
  MyDistinctValue *Next;
public:
    MyDistinctValue(wxString & value);
    MyDistinctValue(double value);
   ~MyDistinctValue()
  {;
  }
  bool IsText()
  {
    return Text;
  }
  wxString & GetTextValue()
  {
    return TextValue;
  }
  double GetNumValue()
  {
    return NumValue;
  }
  wxString & GetValueAsString();
  void SetColor(wxColour & color)
  {
    Color = color;
  }
  wxColor & GetColor()
  {
    return Color;
  }
  void SetIconIndex(int idx)
  {
    IconIndex = idx;
  }
  int GetIconIndex()
  {
    return IconIndex;
  }
  void SetRandomizeSkip(bool skip)
  {
    RandomizeSkip = skip;
  }
  bool IsRandomizeSkip()
  {
    return RandomizeSkip;
  }
  void SetNext(MyDistinctValue * next)
  {
    Next = next;
  }
  MyDistinctValue *GetNext()
  {
    return Next;
  }
};

class MyDistinctValueList
{
//
// a list of DISTINCT values
private:
  int TextCount;
  int DoubleCount;
  MyDistinctValue *First;
  MyDistinctValue *Last;
  void DrawPointLayerIcon(wxMemoryDC * dc, int width, int height, int size);
  void DrawLinestringLayerIcon(wxMemoryDC * dc, int width, int height,
                               int size);
  void DrawPolygonLayerIcon(wxMemoryDC * dc, int width, int height);
public:
    MyDistinctValueList()
  {
    TextCount = 0;
    DoubleCount = 0;
    First = NULL;
    Last = NULL;
  }
   ~MyDistinctValueList();
  MyDistinctValue *Add(wxString & value);
  MyDistinctValue *Add(double value);
  MyDistinctValue *GetFirst()
  {
    return First;
  }
  int GetCount()
  {
    return TextCount + DoubleCount;
  }
  int GetType();
  void RandomizeColors(class MyFrame * main, int hueMode, int transparencyMode);
  void AddSubClassIcons(wxImageList * imageList, int width, int height,
                        int geomType, int symbolType, int size);
};

class MyRangeValue
{
// 
// a class to store RANGE values
//
private:
  wxString TextValue;
  double MinValue;
  double MaxValue;
  int Size;
  wxColour Color;
  int IconIndex;
  MyRangeValue *Next;
public:
    MyRangeValue(double min, double max, int size, wxColour & color);
   ~MyRangeValue()
  {;
  }
  double GetMinValue()
  {
    return MinValue;
  }
  double GetMaxValue()
  {
    return MaxValue;
  }
  void SetRange(double min, double max)
  {
    MinValue = min;
    MaxValue = max;
  }
  wxString & GetRangeAsString();
  int GetSize()
  {
    return Size;
  }
  void SetColor(wxColour & color)
  {
    Color = color;
  }
  wxColor & GetColor()
  {
    return Color;
  }
  void SetIconIndex(int idx)
  {
    IconIndex = idx;
  }
  int GetIconIndex()
  {
    return IconIndex;
  }
  void SetNext(MyRangeValue * next)
  {
    Next = next;
  }
  MyRangeValue *GetNext()
  {
    return Next;
  }
};

class MyRangeValueList
{
//
// a list of RANGE values
private:
  int Count;
  MyRangeValue *First;
  MyRangeValue *Last;
  void DrawPointLayerIcon(wxMemoryDC * dc, int width, int height, int size);
  void DrawLinestringLayerIcon(wxMemoryDC * dc, int width, int height,
                               int size);
  void DrawPolygonLayerIcon(wxMemoryDC * dc, int width, int height);
public:
    MyRangeValueList()
  {
    Count = 0;
    First = NULL;
    Last = NULL;
  }
   ~MyRangeValueList();
  void Build(double min, double max, int numClasses, int minSize, int maxSize,
             wxColour & minColor, wxColour & maxColor);
  void Build(double min, double max, int numClasses, wxColour & minColor,
             wxColour & maxColor);
  void Add(double min, double max, int size, wxColour & color);
  MyRangeValue *GetFirst()
  {
    return First;
  }
  int GetCount()
  {
    return Count;
  }
  void AddSubClassIcons(wxImageList * imageList, int width, int height,
                        int geomType, int symbolType);
};

class MyBitmap
{
//
// image element for Symbols and Brushes
//
private:
  bool FullColor;
  int Id;
  wxBitmap Bitmap;
  wxBitmap Mask;
  int HotPointX;
  int HotPointY;
  int ListId;
  MyBitmap *Next;
  void BuildMask(int width, int height, unsigned char *blob);
  void BuildBitmap(int width, int height, unsigned char *blob,
                   wxColour & foreground, wxColour & background);
  void BuildBitmap(int width, int height, unsigned char *blob);
  void BuildBitmap(int width, int height, unsigned char *blob,
                   wxColour & color);
public:
    MyBitmap(MyBitmap * org);
    MyBitmap(MyBitmap * org, wxColour & foreground, wxColour & background);
    MyBitmap(MyBitmap * org, wxColour & color);
    MyBitmap(int id, int width, int height, unsigned char *blob, int hot_x,
             int hot_y, wxColour & foreground, wxColour & background);
    MyBitmap(int id, int width, int height, unsigned char *blob, int hot_x,
             int hot_y);
    MyBitmap(int id, int width, int height, unsigned char *blob,
             wxColour & foreground, wxColour & background);
    MyBitmap(int id, int width, int height, unsigned char *blob);
    MyBitmap(int id, int width, int height, unsigned char *blob,
             wxColour & color);
   ~MyBitmap()
  {;
  }
  bool IsFullColor()
  {
    return FullColor;
  }
  int GetId()
  {
    return Id;
  }
  wxBitmap & GetBitmap()
  {
    return Bitmap;
  }
  void GetBitmap(wxBitmap & bitmap, wxColour & foreground,
                 wxColour & background);
  void GetBitmap(wxBitmap & bitmap, wxColour & color);
  wxBitmap & GetMask()
  {
    return Mask;
  }
  int GetHotPointX()
  {
    return HotPointX;
  }
  int GetHotPointY()
  {
    return HotPointY;
  }
  void SetListId(int id)
  {
    ListId = id;
  }
  int GetListId()
  {
    return ListId;
  }
  void SetNext(MyBitmap * next)
  {
    Next = next;
  }
  MyBitmap *GetNext()
  {
    return Next;
  }
};

class MyImageList
{
//
// image list for Symbols and Brushes
//
private:
  MyBitmap * First;
  MyBitmap *Last;
public:
    MyImageList()
  {
    First = NULL;
    Last = NULL;
  }
   ~MyImageList();
  void Add(int id, int width, int height, unsigned char *blob, int hot_x,
           int hot_y, wxColour & foreground, wxColour & background);
  void Add(int id, int width, int height, unsigned char *blob, int hot_x,
           int hot_y);
  void Add(int id, int width, int height, unsigned char *blob,
           wxColour & foreground, wxColour & background);
  void Add(int id, int width, int height, unsigned char *blob,
           wxColour & color);
  void Add(int id, int width, int height, unsigned char *blob);
  wxImageList *BuildList();
  MyBitmap *FindById(int id);
  MyBitmap *FindByPos(int list_id);
};

class PdfSymbol
{
//
// a class used to store a PDF symbol
//
private:
  MyBitmap * Symbol;
  int Width;
  int Height;
  HPDF_Image Handle;
  PdfSymbol *Next;
public:
    PdfSymbol(HPDF_Doc pdf, MyBitmap * symbol);
   ~PdfSymbol()
  {;
  }
  MyBitmap *GetSymbol()
  {
    return Symbol;
  }
  int GetWidth()
  {
    return Width;
  }
  int GetHeight()
  {
    return Height;
  }
  HPDF_Image GetHandle()
  {
    return Handle;
  }
  void SetNext(PdfSymbol * next)
  {
    Next = next;
  }
  PdfSymbol *GetNext()
  {
    return Next;
  }
};

class PdfSymbolList
{
//
// a class used to hold a PDF symbol list
//
private:
  HPDF_Doc Pdf;
  PdfSymbol *First;
  PdfSymbol *Last;
public:
    PdfSymbolList(HPDF_Doc pdf);
   ~PdfSymbolList();
  PdfSymbol *Add(MyBitmap * symbol);
};

class SridInfo
{
//
// a class to store SRID infos
//
private:
  int Srid;
  wxString AuthName;
  int AuthSrid;
  wxString SridName;
  wxString Params;
  bool Geographic;
  wxString UnitName;
  bool Dms;
  wxString Ellipsoid;
public:
    SridInfo();
    SridInfo(int srid);
    SridInfo(SridInfo * org);
    virtual ~ SridInfo()
  {;
  }
  int GetSrid()
  {
    return Srid;
  }
  void Set(int srid, wxString & authName, int authSrid, wxString & name,
           wxString & params);
  wxString & GetAuthName()
  {
    return AuthName;
  }
  int GetAuthSrid()
  {
    return AuthSrid;
  }
  wxString & GetSridName()
  {
    return SridName;
  }
  wxString & GetParams()
  {
    return Params;
  }
  bool IsNotSet()
  {
    if (Srid < 0)
      return true;
    else
      return false;
  }
  void ParseUnit();
  void ParseEllipsoid();
  bool IsGeographic()
  {
    return Geographic;
  }
  wxString & GetUnitName()
  {
    return UnitName;
  }
  wxString & GetEllipsoid()
  {
    return Ellipsoid;
  }
  void SetDms(bool mode)
  {
    Dms = mode;
  }
  bool IsDms()
  {
    return Dms;
  }
};

class MyLayer
{
//
// a class to store Layer identifiers
// 
private:
  bool RasterLayer;             // Raster or Vector layer
  bool LayerView;               // marking a Layer based on some View
  bool LayerVirtual;            // marking a Layer based on some VirtualShape
  bool Hidden;                  // marking an invisble GIS layer
  bool ReadOnly;                // marking a read only GIS layer
  wxString TableName;           // the table name
  wxString GeometryColumn;      // the geometry column name
  bool ToInsert;
  bool ToDelete;
  bool Network;
  MyLayer *Next;                // next element pointer [linked list]
public:
    MyLayer(wxString & raster);
    MyLayer(wxString & table, wxString & geometry);
    MyLayer(wxString & table, wxString & geometry, bool isView, bool isVirtual);
   ~MyLayer()
  {;
  }
  bool IsLayerView()
  {
    return LayerView;
  }
  bool IsLayerVirtual()
  {
    return LayerVirtual;
  }
  bool IsRasterLayer()
  {
    return RasterLayer;
  }
  wxString & GetTableName()
  {
    return TableName;
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  void NotToInsert()
  {
    ToInsert = false;
  }
  void ToBeDeleted()
  {
    ToDelete = true;
  }
  bool IsToInsert()
  {
    return ToInsert;
  }
  bool IsToDelete()
  {
    return ToDelete;
  }
  void SetNetwork(bool network)
  {
    Network = network;
  }
  bool IsNetwork()
  {
    return Network;
  }
  void SetHidden()
  {
    Hidden = true;
    ToInsert = false;
    ToDelete = true;
  }
  bool IsHiddenLayer()
  {
    return Hidden;
  }
  void SetReadOnly()
  {
    ReadOnly = true;
  }
  bool IsReadOnly()
  {
    return ReadOnly;
  }
  void SetNext(MyLayer * next)
  {
    Next = next;
  }
  MyLayer *GetNext()
  {
    return Next;
  }
};

class MyLayerList
{
//
// a class to store a Layer List
//
private:
  MyLayer * First;
  MyLayer *Last;
public:
    MyLayerList()
  {
    First = NULL;
    Last = NULL;
  }
   ~MyLayerList();
  MyLayer *Add(wxString & raster);
  MyLayer *Add(wxString & table, wxString & geometry);
  MyLayer *Add(wxString & table, wxString & geometry, bool isView,
               bool isVirtual);
  MyLayer *GetFirst()
  {
    return First;
  }
  bool ExistsRaster(wxString & table);
  void Evaluate(wxString & raster);
  void Evaluate(wxString & table, wxString & geometry, bool network);
  void SetGisLayerAuth(wxString & table, wxString & geometry, bool rdOnly,
                       bool hidden);
  bool ToBeDeleted();
  bool ToBeDeletedTable();
  bool ToBeDeletedView();
  bool ToBeDeletedVirt();
  bool ToBeInserted();
};

class MyLayerSubClass
{
//
// a class to store Layer SubClasses
//
private:
  bool Unique;
  bool Text;
  wxString TextValue;
  double NumValue;
  double MinValue;
  double MaxValue;
  int SymbolType;
  int Size;
  wxColour Color;
  MyLayerSubClass *Next;
public:
    MyLayerSubClass(bool unique, bool text, wxString & textValue,
                    double numValue, double minValue, double maxValue,
                    int symbolType, int size, wxColour & color);
    virtual ~ MyLayerSubClass()
  {;
  }
  bool IsUnique()
  {
    return Unique;
  }
  bool IsText()
  {
    return Text;
  }
  wxString & GetTextValue()
  {
    return TextValue;
  }
  double GetNumValue()
  {
    return NumValue;
  }
  double GetMinValue()
  {
    return MinValue;
  }
  double GetMaxValue()
  {
    return MaxValue;
  }
  int GetSymbolType()
  {
    return SymbolType;
  }
  int GetSize()
  {
    return Size;
  }
  wxColour & GetColor()
  {
    return Color;
  }
  void SetNext(MyLayerSubClass * next)
  {
    Next = next;
  }
  MyLayerSubClass *GetNext()
  {
    return Next;
  }
};

class MyLayerParams
{
//
// a class to store Layer Params
// 
private:
  bool RasterLayer;             // Raster or Vector layer
  bool LayerView;               // marking a Layer based on some View
  bool LayerVirtual;            // marking a Layer based on some VirtualShape
  bool ReadOnly;                // marking a ReadOnly GIS layer
  int GeometryType;             // the Geometry class for Vector Layers
  bool MultiType;               // MULTIxxxx geometry type
  wxString TableName;           // the table name
  wxString GeometryColumn;      // the geometry column name
  wxString DescName;            // descriptive name
  bool Network;
  bool Visible;
  bool Identify;
  int Srid;
  bool Reproject;
  wxString LabelColumn;         // the LABEL column name
  bool AlwaysVisible;           // always visible [ignoresSCALE Range]
  int MinScale;                 // Min Scale [visibility]         
  int MaxScale;                 // Max Scale [visibility]
  int SymbolId;                 // GRAPHICS: Symbol ID [for Points]
  wxColour ForegroundColor;     // GRAPHICS: Foreground color
  wxColour BackgroundColor;     // GRAPHICS: Background color
  wxColour LineColor;           // GRAPHICS: line color [or border color for Polygons]
  int LineThickness;            // GRAPHICS: line thickness [or border thickness for Polygons]
  int LineStyle;                // GRAPHICS: line style [or border style for Polygons]
  bool DrawBorder;              // GRAPHICS: drawing the Polygon's border
  bool ToFill;                  // GRAPHICS: filling the Polygon's interior
  bool SolidFilling;            // GRAPHICS: using a solid color for Polygon's interior fillig / using a brush pattern
  wxColour FillColor;           // GRAPHICS: solid color to be used for Polygon's interior filling
  int PatternId;                // GRAPHICS: brush PatternId [Polygon's interior filling]
  bool MapLabeling;             // LABEL: MapLabeling enabled
  wxColour LabelColor;          // LABEL: text color
  int LabelPointSize;           // LABEL: text point size
  bool LabelFontBold;           // the LABEL font is BOLD
  bool LabelFontItalic;         // the LABEL font is ITALIC
  bool LabelFontUnderlined;     // the LABEL font is UNDERLINED
  bool LabelFontOutlined;       // the LABEL font is OUTLINED
  wxString LabelOrderByColumn;  // LABEL: 'order by' column [priority]
  bool LabelOrderByDescending;  // LABEL: 'order by' clause [ASC | DESC]
  bool LabelAlwaysVisible;      // LABEL: always visible [ignoresSCALE Range]
  int LabelMinScale;            // LABEL: Min Scale [visibility]  
  int LabelMaxScale;            // LABEL: Max Scale [visibility]
  bool LabelAntiOverlap;        // LABEL: AntiOverlap enabled
  bool SubClasses;              // this layer has SUBCLASSes
  wxString ClassifyColumn;      // CLASSES: column storing class values
  bool UniqueValue;             // CLASSES: classify on unique values
  int NumClasses;               // CLASSES: num classes
  double ClassesMinValue;       // CLASSES: minimum value
  double ClassesMaxValue;       // CLASSES: maximum value
  int ClassesSymbolType;        // CLASSES: the symbol type
  int ClassesMinSize;           // CLASSES: min symbol size or min line thickness
  int ClassesMaxSize;           // CLASSES: max symbol size or max line thickness
  wxColour ClassesMinColor;     // CLASSES: min color
  wxColour ClassesMaxColor;     // CLASSES: max color 
  MyLayerSubClass *First;       // pointer to first SubCLASS
  MyLayerSubClass *Last;        // pointer to last SubCLASS
  MyLayerParams *Next;          // next element pointer [linked list]
public:
    MyLayerParams(wxString & raster, wxString & descName, bool visible,
                  bool alwaysVisible, int minScale, int maxScale);
    MyLayerParams(wxString & table, wxString & geometry, wxString & descName,
                  bool network, bool visible, bool identify, bool reproject,
                  wxString & labelColumn, bool alwaysVisible, int minScale,
                  int maxScale, int symbolId, wxColour & foreground,
                  wxColour & background, wxColour & lineColor,
                  int lineThickness, int lineStyle, bool drawBorder,
                  bool toFill, bool solidFilling, wxColour & fillColor,
                  int patternId, bool subClasses, wxString & classifyColumn,
                  bool uniqueValue, int numClasses, double classesMin,
                  double classesMax, int classesSymbol, int classesMinSize,
                  int classesMaxSize, wxColour & classesMinColor,
                  wxColour & classesMaxColor, bool mapLabeling,
                  wxColour labelColor, int labelPointSize,
                  bool labelFontBold, bool labelFontItalic,
                  bool labelFontUnderlined, bool labelFontOutlined,
                  wxString & labelOrderByColumn, bool labelOrderByDesc,
                  bool labelAlwaysVisible, int labelMinScale, int labelMaxScale,
                  bool labelAntiOverlap);
   ~MyLayerParams();
  void SetLayerView()
  {
    LayerView = true;
    LayerVirtual = false;
  }
  void SetLayerVirtual()
  {
    LayerView = false;
    LayerVirtual = true;
  }
  void SetLayerTable()
  {
    LayerView = false;
    LayerVirtual = false;
  }
  void SetReadOnly()
  {
    ReadOnly = true;
  }
  bool IsLayerView()
  {
    return LayerView;
  }
  bool IsLayerVirtual()
  {
    return LayerVirtual;
  }
  bool IsReadOnly()
  {
    return ReadOnly;
  }
  void SetNetwork()
  {
    Network = true;
  }
  bool IsNetwork()
  {
    return Network;
  }
  bool IsRasterLayer()
  {
    return RasterLayer;
  }
  void SetSrid(int srid)
  {
    Srid = srid;
  }
  int GetSrid()
  {
    return Srid;
  }
  int GetGeometryType()
  {
    return GeometryType;
  }
  bool IsMultiType()
  {
    return MultiType;
  }
  wxString & GetTableName()
  {
    return TableName;
  }
  void SetGeometryType(int type)
  {
    GeometryType = type;
  }
  void SetMultiType(bool multi)
  {
    MultiType = multi;
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  bool IsVisible()
  {
    return Visible;
  }
  bool IsIdentify()
  {
    return Identify;
  }
  bool IsReproject()
  {
    return Reproject;
  }
  wxString & GetLabelColumn()
  {
    return LabelColumn;
  }
  bool IsAlwaysVisible()
  {
    return AlwaysVisible;
  }
  int GetMinScale()
  {
    return MinScale;
  }
  int GetMaxScale()
  {
    return MaxScale;
  }
  int GetSymbolId()
  {
    return SymbolId;
  }
  wxColour & GetForegroundColor()
  {
    return ForegroundColor;
  }
  wxColour & GetBackgroundColor()
  {
    return BackgroundColor;
  }
  wxColour & GetLineColor()
  {
    return LineColor;
  }
  int GetLineThickness()
  {
    return LineThickness;
  }
  int GetLineStyle()
  {
    return LineStyle;
  }
  bool DrawBorderOk()
  {
    return DrawBorder;
  }
  bool IsToFill()
  {
    return ToFill;
  }
  bool SolidFillingOk()
  {
    return SolidFilling;
  }
  wxColour & GetFillColor()
  {
    return FillColor;
  }
  int GetPatternId()
  {
    return PatternId;
  }
  bool HasSubClasses()
  {
    return SubClasses;
  }
  wxString & GetClassifyColumn()
  {
    return ClassifyColumn;
  }
  bool IsUniqueValue()
  {
    return UniqueValue;
  }
  int GetNumClasses()
  {
    return NumClasses;
  }
  double GetClassesMinValue()
  {
    return ClassesMinValue;
  }
  double GetClassesMaxValue()
  {
    return ClassesMaxValue;
  }
  int GetClassesSymbolType()
  {
    return ClassesSymbolType;
  }
  int GetClassesMinSize()
  {
    return ClassesMinSize;
  }
  int GetClassesMaxSize()
  {
    return ClassesMaxSize;
  }
  wxColour & GetClassesMinColor()
  {
    return ClassesMinColor;
  }
  wxColour & GetClassesMaxColor()
  {
    return ClassesMaxColor;
  }
  bool IsMapLabelingEnabled()
  {
    return MapLabeling;
  }
  wxColour & GetLabelColor()
  {
    return LabelColor;
  }
  int GetLabelPointSize()
  {
    return LabelPointSize;
  }
  bool IsLabelFontBold()
  {
    return LabelFontBold;
  }
  bool IsLabelFontItalic()
  {
    return LabelFontItalic;
  }
  bool IsLabelFontUnderlined()
  {
    return LabelFontUnderlined;
  }
  bool IsLabelFontOutlined()
  {
    return LabelFontOutlined;
  }
  wxString & GetLabelOrderByColumn()
  {
    return LabelOrderByColumn;
  }
  bool IsLabelOrderByDescending()
  {
    return LabelOrderByDescending;
  }
  bool IsLabelAlwaysVisible()
  {
    return LabelAlwaysVisible;
  }
  int GetLabelMinScale()
  {
    return LabelMinScale;
  }
  int GetLabelMaxScale()
  {
    return LabelMaxScale;
  }
  bool IsLabelAntiOverlapEnabled()
  {
    return LabelAntiOverlap;
  }
  void SetNext(MyLayerParams * next)
  {
    Next = next;
  }
  MyLayerParams *GetNext()
  {
    return Next;
  }
  void Add(bool unique, bool text, wxString & textValue, double numValue,
           double minValue, double maxValue, int symbolType, int size,
           wxColour & color);
  MyLayerSubClass *GetFirst()
  {
    return First;
  }
};

class MyLayerParamsList
{
//
// a class to store Layer Params
//
private:
  MyLayerParams * First;
  MyLayerParams *Last;
  MyLayerParams *Current;
public:
    MyLayerParamsList()
  {
    First = NULL;
    Last = NULL;
    Current = NULL;
  }
   ~MyLayerParamsList();
  void Add(wxString & raster, wxString & descName, bool visible,
           bool alwaysVisible, int minScale, int maxScale);
  void Add(wxString & table, wxString & geometry, wxString & descName,
           bool network, bool visible, bool identify, bool reproject,
           wxString & labelColumn, bool alwaysVisible, int minScale,
           int maxScale, int symbolId, wxColour & foreground,
           wxColour & background, wxColour & lineColor, int lineThickness,
           int lineStyle, bool drawBorder, bool toFill, bool solidFilling,
           wxColour & fillColor, int patternId, bool subClasses,
           wxString & classifyColumn, bool uniqueValue, int numClasses,
           double classesMin, double classesMax, int classesSymbol,
           int classesMinSize, int classesMaxSize, wxColour & classesMinColor,
           wxColour & classesMaxColor, bool mapLabeling, wxColour labelColor,
           int labelPointSize, bool labelFontBold, bool labelFontItalic,
           bool labelFontUnderlined, bool labelFontOutlined,
           wxString & labelOrderByColumn, bool labelOrderByDesc,
           bool labelAlwaysVisible, int labelMinScale, int labelMaxScale,
           bool labelAntiOverlap);
  void Add(wxString & table, wxString & geometry, bool unique, bool text,
           wxString & textValue, double numValue, double minValue,
           double maxValue, int symbolType, int size, wxColour & color);
  MyLayerParams *GetFirst()
  {
    return First;
  }
  MyLayerParams *Find(wxString & raster);
  MyLayerParams *Find(wxString & table, wxString & geometry);
  MyLayerParams *FindRaster(wxString & table);
};

class LayerObject:public wxTreeItemData
{
//
// a class to store TreeItemData - Layer Params
//
private:
  int Type;                     // the object type
  bool LayerView;               // marking a Layer based on some View
  bool LayerVirtual;            // marking a Layer based on some VirtualShape
  bool ReadOnly;                // marking a ReadOnly GIS Layer
  int GeometryType;             // the Geometry class for Vector Layers
  bool MultiType;               // MULTIxxxx Type
  wxString TableName;           // the table name
  wxString GeometryColumn;      // the geometry column name
  wxString DescName;            // descriptive name
  bool Visible;
  bool Identify;
  bool EditingEnabled;
  int Srid;
  bool Network;
  bool Reproject;

  bool AlwaysVisible;           // always visible [ignores SCALE Range]
  int MinScale;                 // Min Scale [visibility]         
  int MaxScale;                 // Max Scale [visibility]

  int SymbolId;                 // GRAPHICS: Symbol ID [for Points]
  wxColour ForegroundColor;     // GRAPHICS: Foreground color
  wxColour BackgroundColor;     // GRAPHICS: Background color
  wxColour LineColor;           // GRAPHICS: line color [or border color for Polygons]
  int LineThickness;            // GRAPHICS: line thickness [or border thickness for Polygons]
  int LineStyle;                // GRAPHICS: line style [or border style for Polygons]
  bool DrawBorder;              // GRAPHICS: drawing the Polygon's border
  bool ToFill;                  // GRAPHICS: filling the Polygon's interior
  bool SolidFilling;            // GRAPHICS: using a solid color for Polygon's interior fillig / using a brush pattern
  wxColour FillColor;           // GRAPHICS: solid color to be used for Polygon's interior filling
  int PatternId;                // GRAPHICS: brush PatternId [Polygon's interior filling]

  wxString LabelColumn;         // the LABEL column name
  bool MapLabeling;             // LABEL MapLabeling enabled
  wxColour LabelColor;          // the LABEL text color
  int LabelPointSize;           // the LABEL font size (in points)
  bool LabelFontBold;           // the LABEL font is BOLD
  bool LabelFontItalic;         // the LABEL font is ITALIC
  bool LabelFontUnderlined;     // the LABEL font is UNDERLINED
  bool LabelFontOutlined;       // the LABEL font is OUTLINED
  wxString LabelOrderByColumn;  // the LABEL 'order by' column name [priority]
  bool LabelOrderByDescending;  // the LABEL 'order by' mode [ASC | DESC]
  bool LabelAlwaysVisible;      // LABEL always visible [ignoresSCALE Range]
  int LabelMinScale;            // LABEL Min Scale [visibility]         
  int LabelMaxScale;            // LABEL Max Scale [visibility]
  bool LabelAntiOverlap;        // the LABEL anti-overlap mode

  int IconIndex;                // the Icon Index [Image List]
  bool Default;                 // DEFAULT: corresponds to the standard layer icon

  bool SubClasses;              // this layer has SUBCLASSes
  wxString ClassifyColumn;      // CLASSES: column storing class values
  bool UniqueValue;             // CLASSES: classify on unique values
  int NumClasses;               // CLASSES: num classes
  double ClassesMinValue;       // CLASSES: minimum value
  double ClassesMaxValue;       // CLASSES: maximum value
  int ClassesSymbolType;        // CLASSES: the symbol type
  int ClassesMinSize;           // CLASSES: min symbol size or min line thickness
  int ClassesMaxSize;           // CLASSES: max symbol size or max line thickness
  wxColour ClassesMinColor;     // CLASSES: min color
  wxColour ClassesMaxColor;     // CLASSES: max color 

  bool SubClassUnique;          // SubCLASS: unique value
  bool SubClassText;            // SubCLASS: value is TEXT
  wxString SubClassString;      // SubCLASS: generic string
  wxString SubClassTextValue;   // SubCLASS: text value
  double SubClassNumValue;      // SubCLASS: numeric value
  double SubClassMinValue;      // SubCLASS: range min
  double SubClassMaxValue;      // SubCLASS: range max
  int SubClassSymbolType;       // SubCLASS: symbol type
  int SubClassSize;             // SubCLASS: size
  wxColour SubClassColor;       // SubCLass: color

  wxString ForegroundColorAsRGBA;
  wxString BackgroundColorAsRGBA;
  wxString LineColorAsRGBA;
  wxString LineStyleAsConstant;
  wxString FillColorAsRGBA;
  wxString LabelColorAsRGBA;
  wxString LabelFontWeight;
  wxString LabelFontStyle;
  wxString SymbolTypeAsConstant;
  wxString ClassesMinColorAsRGBA;
  wxString ClassesMaxColorAsRGBA;
  void DrawPointLayerIcon(wxMemoryDC * dc, int width, int height,
                          MyImageList * symbols);
  void DrawLinestringLayerIcon(wxMemoryDC * dc, int width, int height);
  void DrawPolygonLayerIcon(wxMemoryDC * dc, int width, int height,
                            MyImageList * patterns);
  void DrawPointSubClassIcon(wxMemoryDC * dc, int width, int height);
  void DrawLinestringSubClassIcon(wxMemoryDC * dc, int width, int height);
  void DrawPolygonSubClassIcon(wxMemoryDC * dc, int width, int height);
public:
    LayerObject();
    LayerObject(LayerObject * org);
    LayerObject(LayerObject * org, bool dflt);
    LayerObject(MyLayerParams * params);
    LayerObject(MyLayerSubClass * subClass);
    LayerObject(wxString & raster, int srid);
    LayerObject(wxString & table, wxString & geometry, int srid, int geom_type,
                bool multi_type);
// SUBCLASSES constructors
    LayerObject(class SubClassObject * sub);
    virtual ~ LayerObject()
  {;
  }
  void SetLayerView()
  {
    LayerView = true;
    LayerVirtual = false;
  }
  void SetLayerVirtual()
  {
    LayerView = false;
    LayerVirtual = true;
  }
  void SetLayerTable()
  {
    LayerView = false;
    LayerVirtual = false;
  }
  bool IsLayerView()
  {
    return LayerView;
  }
  bool IsLayerVirtual()
  {
    return LayerVirtual;
  }
  bool IsReadOnly()
  {
    return ReadOnly;
  }
  void Set(wxString & table, wxString & geometry, int srid, int geom_type,
           bool multi_type, wxString & desc);
  void SetNetwork()
  {
    Network = true;
  }
  bool IsNetwork()
  {
    return Network;
  }
  int GetType()
  {
    return Type;
  }
  bool IsMultiType()
  {
    return MultiType;
  }
  bool IsDefault()
  {
    return Default;
  }
  int GetGeometryType()
  {
    return GeometryType;
  }
  wxString & GetTableName()
  {
    return TableName;
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  void SetDescName(wxString & name)
  {
    DescName = name;
  }
  int GetSrid()
  {
    return Srid;
  }
  bool IsVisible()
  {
    return Visible;
  }
  void SetVisible(bool mode)
  {
    Visible = mode;
  }
  bool IsIdentify()
  {
    return Identify;
  }
  void SetIdentify(bool mode)
  {
    Identify = mode;
  }
  bool IsEditingEnabled()
  {
    return EditingEnabled;
  }
  void SetEditingEnabled(bool mode)
  {
    EditingEnabled = mode;
  }
  bool IsReproject()
  {
    return Reproject;
  }
  void SetReproject(bool mode)
  {
    Reproject = mode;
  }
  void SetAlwaysVisible()
  {
    AlwaysVisible = true;
  }
  void SetScaleVisibility(int min, int max)
  {
    AlwaysVisible = false;
    MinScale = min;
    MaxScale = max;
  }
  bool IsAlwaysVisible()
  {
    return AlwaysVisible;
  }
  int GetMinScale()
  {
    return MinScale;
  }
  int GetMaxScale()
  {
    return MaxScale;
  }
  void SetLabelColumn(wxString & label)
  {
    LabelColumn = label;
  }
  wxString & GetLabelColumn()
  {
    return LabelColumn;
  }
  void DisableMapLabeling();
  void EnableMapLabeling(wxColour & color, int size, bool fontBold,
                         bool fontItalic, bool fontUnderlined,
                         bool fontOutlined, wxString & column, bool desc,
                         bool overlap);
  bool IsMapLabelingEnabled()
  {
    return MapLabeling;
  }
  wxColour & GetLabelColor()
  {
    return LabelColor;
  }
  int GetLabelPointSize()
  {
    return LabelPointSize;
  }
  bool IsLabelFontBold()
  {
    return LabelFontBold;
  }
  bool IsLabelFontItalic()
  {
    return LabelFontItalic;
  }
  bool IsLabelFontUnderlined()
  {
    return LabelFontUnderlined;
  }
  bool IsLabelFontOutlined()
  {
    return LabelFontOutlined;
  }
  wxString & GetLabelOrderByColumn()
  {
    return LabelOrderByColumn;
  }
  bool IsLabelOrderByDescending()
  {
    return LabelOrderByDescending;
  }
  void SetLabelAlwaysVisible()
  {
    LabelAlwaysVisible = true;
  }
  void SetLabelScaleVisibility(int min, int max)
  {
    LabelAlwaysVisible = false;
    LabelMinScale = min;
    LabelMaxScale = max;
  }
  bool IsLabelAlwaysVisible()
  {
    return LabelAlwaysVisible;
  }
  int GetLabelMinScale()
  {
    return LabelMinScale;
  }
  int GetLabelMaxScale()
  {
    return LabelMaxScale;
  }
  bool IsLabelAntiOverlapEnabled()
  {
    return LabelAntiOverlap;
  }
  void SetPointGraphics(int sym);
  void SetPointGraphics(int sym, wxColour & foreground, wxColour & background);
  int GetSymbolId()
  {
    return SymbolId;
  }
  wxColour & GetForegroundColor()
  {
    return ForegroundColor;
  }
  wxColour & GetBackgroundColor()
  {
    return BackgroundColor;
  }
  void SetLineGraphics(wxColour & color, int thick, int style);
  wxColour & GetLineColor()
  {
    return LineColor;
  }
  int GetLineThickness()
  {
    return LineThickness;
  }
  int GetLineStyle()
  {
    return LineStyle;
  }
  void SetPolygonGraphics(wxColour & borderColor, int thickness, int style);
  void SetPolygonGraphics(wxColour & fillColor);
  void SetPolygonGraphics(wxColour & borderColor, int thickness, int style,
                          wxColour & fillColor);
  void SetPolygonGraphics(int patternId, wxColour & fillColor);
  void SetPolygonGraphics(wxColour & borderColor, int thickness, int style,
                          int patternId, wxColour & fillColor);
  bool DrawBorderOk()
  {
    return DrawBorder;
  }
  bool IsToFill()
  {
    return ToFill;
  }
  bool SolidFillingOk()
  {
    return SolidFilling;
  }
  wxColour & GetFillColor()
  {
    return FillColor;
  }
  int GetPatternId()
  {
    return PatternId;
  }
  void UpdateDefault(LayerObject * org);
  int GetIconIndex()
  {
    return IconIndex;
  }

// CLASSES functions
  void SetClassifyParams(wxString & column, bool unique, int numClasses,
                         double minValue, double maxValue, int symbolType,
                         int minSize, int maxSize, wxColour & minColor,
                         wxColour & maxColor);
  void ClearClassifyParams();
  wxString & GetClassifyColumn()
  {
    return ClassifyColumn;
  }
  bool IsUniqueValue()
  {
    return UniqueValue;
  }
  int GetNumClasses()
  {
    return NumClasses;
  }
  double GetClassesMinValue()
  {
    return ClassesMinValue;
  }
  double GetClassesMaxValue()
  {
    return ClassesMaxValue;
  }
  int GetClassesSymbolType()
  {
    return ClassesSymbolType;
  }
  int GetClassesMinSize()
  {
    return ClassesMinSize;
  }
  int GetClassesMaxSize()
  {
    return ClassesMaxSize;
  }
  wxColour & GetClassesMinColor()
  {
    return ClassesMinColor;
  }
  wxColour & GetClassesMaxColor()
  {
    return ClassesMaxColor;
  }

// SUBCLASSES functions
  bool HasSubClasses()
  {
    return SubClasses;
  }
  wxString & GetSubClassString();
  int GetSubClassSymbolType()
  {
    return SubClassSymbolType;
  }
  int GetSubClassSize()
  {
    return SubClassSize;
  }
  wxColour & GetSubClassColor()
  {
    return SubClassColor;
  }
  wxString & GetSubClassTextValue()
  {
    return SubClassTextValue;
  }
  bool IsSubClassUnique()
  {
    return SubClassUnique;
  }
  bool IsSubClassText()
  {
    return SubClassText;
  }
  double GetSubClassNumValue()
  {
    return SubClassNumValue;
  }
  double GetSubClassMinValue()
  {
    return SubClassMinValue;
  }
  double GetSubClassMaxValue()
  {
    return SubClassMaxValue;
  }

// serialization/deserialization functions
  void PrepareStaticValues();
  void PrepareStaticClassesValues();
  wxString & GetForegroundColorAsRGBA()
  {
    return ForegroundColorAsRGBA;
  }
  wxString & GetBackgroundColorAsRGBA()
  {
    return BackgroundColorAsRGBA;
  }
  wxString & GetLineColorAsRGBA()
  {
    return LineColorAsRGBA;
  }
  wxString & GetFillColorAsRGBA()
  {
    return FillColorAsRGBA;
  }
  wxString & GetLabelColorAsRGBA()
  {
    return LabelColorAsRGBA;
  }
  wxString & GetLabelFontWeight()
  {
    return LabelFontWeight;
  }
  wxString & GetLabelFontStyle()
  {
    return LabelFontStyle;
  }
  wxString & GetLineStyleAsConstant()
  {
    return LineStyleAsConstant;
  }
  wxString & GetSymbolTypeAsConstant()
  {
    return SymbolTypeAsConstant;
  }
  wxString & GetClassesMinColorAsRGBA()
  {
    return ClassesMinColorAsRGBA;
  }
  wxString & GetClassesMaxColorAsRGBA()
  {
    return ClassesMaxColorAsRGBA;
  }

// feeding the Image List [layer icons]
  int AddLayerIcon(wxImageList * imageList, int width, int height,
                   MyImageList * symbols, MyImageList * patterns);
  int AddSubClassIcon(wxImageList * imageList, int width, int height,
                      int geometryType);
  void UpdateLayerIcon(wxImageList * imageList, int width, int height,
                       MyImageList * symbols, MyImageList * patterns);
};

class SubClassesContainer
{
//
// a class containing an array of LayerObject pointers
//
private:
  int Count;
  int Index;
  bool ColorsIncluded;
  LayerObject **SubClasses;
public:
    SubClassesContainer()
  {
    Count = 0;
    SubClasses = NULL;
    ColorsIncluded = false;
  }
   ~SubClassesContainer()
  {
    if (SubClasses)
      delete[]SubClasses;
  }
  void Create(int count);
  void Add(LayerObject * layer);
  int GetCount()
  {
    return Count;
  }
  void BuildDistinctList(MyDistinctValueList * list);
  void BuildRangeList(MyRangeValueList * list);
  void SetColorsIncluded()
  {
    ColorsIncluded = true;
  }
  bool HasColors()
  {
    return ColorsIncluded;
  }
};

class MyLayerTree:public wxTreeCtrl
{
//
// a tree-control used for Map Layers
//
private:
  class MyFrame * MainFrame;
  bool Changed;
  wxTreeItemId Root;            // the root node
  wxImageList *BaseImages;      // the fixed image list
  wxImageList *Images;          // the actual [variable] image list
  wxTreeItemId CurrentItem;     // the tree item holding the current context menu
  wxTreeItemId DraggedItem;     // the tree item to be moved
  void AddBitmap(wxBitmap & bitmap);
  void AddOnBitmap(wxBitmap & bitmap);
  void AddOffBitmap(wxBitmap & bitmap);
public:
    MyLayerTree()
  {;
  }
  MyLayerTree(class MyFrame * parent, wxWindowID id = wxID_ANY);
  virtual ~ MyLayerTree();
  void SetPath(wxString & path)
  {
    SetItemText(Root, path);
  }
  void FlushAll()
  {
    DeleteChildren(Root);
    Changed = true;
  }
  int GetIconIndex(LayerObject * obj);
  wxTreeItemId & GetRoot()
  {
    return Root;
  }
  void AddLayer(MyLayerParams * layer);
  void SetLayerIcons();
  void MarkCurrentItem();
  void UpdateDefault(wxTreeItemId item, wxImageList * imageList,
                     MyImageList * symbols, MyImageList * patterns);
  void SetChanged()
  {
    Changed = true;
  }
  bool IsChanged()
  {
    return Changed;
  }
  void BuildLayersList(class MapLayersList * list);
  void UpdateLayersEditMode(class MapLayersList * list);
  void ResetEditingMode();
  void ResetEditingMode(wxTreeItemId & item);
  void OnSelChanged(wxTreeEvent & event);
  void OnItemActivated(wxTreeEvent & event);
  void OnRightClick(wxTreeEvent & event);
  void OnCmdRefresh(wxCommandEvent & event);
  void OnCmdShowAll(wxCommandEvent & event);
  void OnCmdHideAll(wxCommandEvent & event);
  void OnCmdVisible(wxCommandEvent & event);
  void OnCmdIdentify(wxCommandEvent & event);
  void OnCmdLayerExtent(wxCommandEvent & event);
  void OnCmdCrs(wxCommandEvent & event);
  void OnCmdScaleVisibility(wxCommandEvent & event);
  void OnCmdLabels(wxCommandEvent & event);
  void OnCmdGraphics(wxCommandEvent & event);
  void OnCmdClassify(wxCommandEvent & event);
  void OnCmdClassesDrop(wxCommandEvent & event);
  void OnCmdUpdateStatistics(wxCommandEvent & event);
  void OnCmdSpatialIndex(wxCommandEvent & event);
  void OnCmdMbrCache(wxCommandEvent & event);
  void OnCmdDumpShp(wxCommandEvent & event);
  void OnCmdDeleteLayer(wxCommandEvent & event);
  void OnCmdShowTable(wxCommandEvent & event);
  void OnCmdEditMode(wxCommandEvent & event);
  void OnCmdTableLayout(wxCommandEvent & event);
  void OnCmdBuildNetwork(wxCommandEvent & event);
  void OnCmdDropNetwork(wxCommandEvent & event);
  void OnDragStart(wxTreeEvent & event);
  void OnDragEnd(wxTreeEvent & event);
};

class MapSubClass
{
//
// a class to store a Map Layer SubClass
//
private:
  bool Visible;
  bool Unique;
  bool Text;
  wxString TextValue;
  double NumValue;
  double MinValue;
  double MaxValue;
  int SymbolType;
  int Size;
  wxColour Color;
// Graphic resources
  wxGraphicsPen Pen;
  wxGraphicsBrush Brush;

  MapSubClass *Next;
public:
    MapSubClass(LayerObject * org);
   ~MapSubClass()
  {;
  }
  bool IsVisible()
  {
    return Visible;
  }
  bool OkValue(wxString & value);
  bool OkValue(double value);
  int GetSymbolType()
  {
    return SymbolType;
  }
  int GetSize()
  {
    return Size;
  }
  wxColour & GetColor()
  {
    return Color;
  }
  void CreateGraphicResources(wxGraphicsContext * gr, int geomType);
  wxGraphicsPen & GetPen()
  {
    return Pen;
  }
  wxGraphicsBrush & GetBrush()
  {
    return Brush;
  }
  void SetNext(MapSubClass * next)
  {
    Next = next;
  }
  MapSubClass *GetNext()
  {
    return Next;
  }
};

class MapLayer
{
//
// a class to store a Map Layer
//
private:
  int Type;
  bool LayerView;
  bool LayerVirtual;
  void *RasterliteHandle;
  int GeometryType;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  bool Network;
  bool Visible;
  bool Identify;
  bool ReadOnly;
  int Srid;
  bool Reproject;
  bool AlwaysVisible;
  int MinScale;
  int MaxScale;
  int SymbolId;
  MyBitmap *Symbol;
  wxColour ForegroundColor;
  wxColour BackgroundColor;
  wxColour LineColor;
  int LineThickness;
  int LineStyle;
  bool DrawBorder;
  bool ToFill;
  bool SolidFilling;
  wxColour FillColor;
  int PatternId;
  MyBitmap *Pattern;
  wxString LabelColumn;
  bool MapLabeling;
  wxColour LabelColor;
  int LabelPointSize;
  bool LabelFontBold;
  bool LabelFontItalic;
  bool LabelFontUnderlined;
  bool LabelFontOutlined;
  wxString LabelOrderByColumn;
  bool LabelOrderByDescending;
  bool LabelAlwaysVisible;
  int LabelMinScale;
  int LabelMaxScale;
  bool LabelAntiOverlap;
  wxString ClassifyColumn;
// Graphic resources
  wxGraphicsPen Pen;
  wxGraphicsBrush Brush;
  wxBitmap Bitmap;

  MapSubClass *First;
  MapSubClass *Last;
  MapLayer *Next;
public:
    MapLayer(LayerObject * org);
    MapLayer(wxColour & color, int thickness);
   ~MapLayer();
  void SetLayerView()
  {
    LayerView = true;
    LayerVirtual = false;
  }
  void SetLayerVirtual()
  {
    LayerView = false;
    LayerVirtual = true;
  }
  void SetLayerTable()
  {
    LayerView = false;
    LayerVirtual = false;
  }
  bool IsLayerView()
  {
    return LayerView;
  }
  bool IsLayerVirtual()
  {
    return LayerVirtual;
  }
  void *GetRasterliteHandle()
  {
    return RasterliteHandle;
  }
  void SetRasterliteHandle(void *handle)
  {
    RasterliteHandle = handle;
  }
  int GetType()
  {
    return Type;
  }
  int GetGeometryType()
  {
    return GeometryType;
  }
  wxString & GetTableName()
  {
    return TableName;
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  int GetSrid()
  {
    return Srid;
  }
  bool IsNetwork()
  {
    return Network;
  }
  bool IsVisible()
  {
    return Visible;
  }
  bool IsVisible(int scale);
  bool AreLabelsVisible(int scale);
  bool IsIdentify()
  {
    return Identify;
  }
  bool IsReadOnly()
  {
    return ReadOnly;
  }
  void SetReadOnly(bool mode)
  {
    ReadOnly = mode;
  }
  bool IsReproject()
  {
    return Reproject;
  }
  wxString & GetLabelColumn()
  {
    return LabelColumn;
  }
  bool HasMapLabels()
  {
    if (LabelColumn.Len() > 0 && MapLabeling == true)
      return true;
    else
      return false;
  }
  wxColour & GetLabelColor()
  {
    return LabelColor;
  }
  int GetLabelPointSize()
  {
    return LabelPointSize;
  }
  bool IsLabelFontBold()
  {
    return LabelFontBold;
  }
  bool IsLabelFontItalic()
  {
    return LabelFontItalic;
  }
  bool IsLabelFontUnderlined()
  {
    return LabelFontUnderlined;
  }
  bool IsLabelFontOutlined()
  {
    return LabelFontOutlined;
  }
  wxString & GetLabelOrderByColumn()
  {
    return LabelOrderByColumn;
  }
  bool IsLabelOrderByDescending()
  {
    return LabelOrderByDescending;
  }
  bool HasLabelPriority()
  {
    if (LabelOrderByColumn.Len() > 0 && LabelAntiOverlap == true)
      return true;
    else
      return false;
  }
  bool IsLabelAlwaysVisible()
  {
    return LabelAlwaysVisible;
  }
  int GetLabelMinScale()
  {
    return LabelMinScale;
  }
  int GetLabelMaxScale()
  {
    return LabelMaxScale;
  }
  bool IsLabelAntiOverlapEnabled()
  {
    return LabelAntiOverlap;
  }
  bool IsAlwaysVisible()
  {
    return AlwaysVisible;
  }
  int GetMinScale()
  {
    return MinScale;
  }
  int GetMaxScale()
  {
    return MaxScale;
  }
  int GetSymbolId()
  {
    return SymbolId;
  }
  void SetSymbol(MyBitmap * x)
  {
    Symbol = x;
  }
  MyBitmap *GetSymbol()
  {
    return Symbol;
  }
  wxColour & GetForegroundColor()
  {
    return ForegroundColor;
  }
  wxColour & GetBackgroundColor()
  {
    return BackgroundColor;
  }
  wxColour & GetLineColor()
  {
    return LineColor;
  }
  int GetLineThickness()
  {
    return LineThickness;
  }
  int GetLineStyle()
  {
    return LineStyle;
  }
  bool DrawBorderOk()
  {
    return DrawBorder;
  }
  bool IsToFill()
  {
    return ToFill;
  }
  bool SolidFillingOk()
  {
    return SolidFilling;
  }
  wxColour & GetFillColor()
  {
    return FillColor;
  }
  int GetPatternId()
  {
    return PatternId;
  }
  void SetPattern(MyBitmap * x)
  {
    Pattern = x;
  }
  MyBitmap *GetPattern()
  {
    return Pattern;
  }
  void Add(LayerObject * org);
  wxString & GetClassifyColumn()
  {
    return ClassifyColumn;
  }
  void CreateGraphicResources(wxGraphicsContext * gr);
  wxGraphicsPen & GetPen()
  {
    return Pen;
  }
  wxGraphicsBrush & GetBrush()
  {
    return Brush;
  }
  wxBitmap & GetBitmap()
  {
    return Bitmap;
  }
  MapSubClass *GetFirst()
  {
    return First;
  }
  MapSubClass *GetSubClass(wxString & value);
  MapSubClass *GetSubClass(double value);
  void SetNext(MapLayer * next)
  {
    Next = next;
  }
  MapLayer *GetNext()
  {
    return Next;
  }
};

class MapLayersList
{
//
// a class implementing a Layers' linked-list
//
private:
  MapLayer * First;
  MapLayer *Last;
public:
    MapLayersList()
  {
    First = NULL;
    Last = NULL;
  }
   ~MapLayersList();
  void Flush();
  void Add(LayerObject * org);
  MapLayer *GetFirst()
  {
    return First;
  }
  void SetGraphicResources(MyImageList * symbols, MyImageList * patterns);
  void CreateGraphicResources(MyImageList * symbols, MyImageList * patterns);
  void CreateGraphicResources(wxGraphicsContext * gr);
  void UpdateEditMode(wxString & table, wxString & geomColumn, bool mode);
};

class LineLabelItem
{
//
// a class representing a Line Label Item
//
private:
  double X;
  double Y;
  double Rotation;
  LineLabelItem *Next;
public:
    LineLabelItem(double x0, double y0, double x1, double y1);
   ~LineLabelItem()
  {;
  }
  double GetX()
  {
    return X;
  }
  double GetY()
  {
    return Y;
  }
  double GetRotation()
  {
    return Rotation;
  }
  void SetNext(LineLabelItem * next)
  {
    Next = next;
  }
  LineLabelItem *GetNext()
  {
    return Next;
  }
};

class LineLabelAux
{
//
// a class representing a Line Labels List
//
private:
  double PixelRatio;
  LineLabelItem *First;
  LineLabelItem *Last;
  int Count;
public:
    LineLabelAux(double pixelRatio);
   ~LineLabelAux();
  void Feed(class MapLabel * label, gaiaGeomCollPtr geom);
  int GetCount()
  {
    return Count;
  }
  LineLabelItem *GetFirst()
  {
    return First;
  }
  LineLabelItem *GetLast()
  {
    return Last;
  }
  LineLabelItem *GetItem();
};

class MapLabelCandidate
{
//
// a class representing a Map Label Candidate Position
//
private:
  bool Valid;
  double X;
  double Y;
  double Rotation;
  gaiaGeomCollPtr Geometry;
  MapLabelCandidate *Next;
public:
    MapLabelCandidate(double x, double y, double rotation,
                      gaiaGeomCollPtr geom);
   ~MapLabelCandidate();
  void Collision()
  {
    Valid = false;
  }
  bool IsValid()
  {
    return Valid;
  }
  double GetX()
  {
    return X;
  }
  double GetY()
  {
    return Y;
  }
  double GetRotation()
  {
    return Rotation;
  }
  gaiaGeomCollPtr TransferGeometry();
  bool EvaluateCollision(gaiaGeomCollPtr other);
  MapLabelCandidate *GetNext()
  {
    return Next;
  }
  void SetNext(MapLabelCandidate * next)
  {
    Next = next;
  }
};

class MapLabel
{
//
// a class representing a Map Label
//
private:
  MapLayer * Layer;
  wxString Label;
  gaiaGeomCollPtr Geometry;
  double PixelRatio;
  double Width;
  double Height;
  bool NoCollision;
  bool Valid;
  double X;
  double Y;
  double Rotation;
  MapLabelCandidate *First;
  MapLabelCandidate *Last;
  MapLabel *Next;
public:
    MapLabel(MapLayer * layer, wxString & label, double width, double height,
             double pixelRatio, bool noCollision);
   ~MapLabel();
  void AddCandidate(double x, double y, double rotation, gaiaGeomCollPtr geom);
  MapLabelCandidate *GetFirst()
  {
    return First;
  }
  void DeleteCandidates();
  double GetWidth()
  {
    return Width;
  }
  double GetPixelRatio()
  {
    return PixelRatio;
  }
  gaiaGeomCollPtr CreateRectangle(double x, double y, double rotation);
  gaiaGeomCollPtr CreateRectangle(double x, double y);
  void AssignLabelPosition(MapLabelCandidate * p);
  void AssignLabelPosition(double x, double y);
  void AssignLabelPosition(double x, double y, double rotation);
  bool IsNoCollision()
  {
    return NoCollision;
  }
  void Invalidate()
  {
    Valid = false;
  }
  bool IsValid()
  {
    return Valid;
  }
  bool CheckSize(gaiaGeomCollPtr geom);
  bool CheckSize(gaiaGeomCollPtr geom, gaiaGeomCollPtr rect);
  void LineLabelCentered(gaiaGeomCollPtr geom, double pixelRatio);
  void LineLabelMultiple(gaiaGeomCollPtr geom, double pixelRatio);
  MapLayer *GetLayer()
  {
    return Layer;
  }
  wxString & GetLabel()
  {
    return Label;
  }
  double GetX()
  {
    return X;
  }
  double GetY()
  {
    return Y;
  }
  double GetRotation()
  {
    return Rotation;
  }
  bool GetBaseline(double *x0, double *y0, double *x1, double *y1);
  gaiaGeomCollPtr GetGeometry()
  {
    return Geometry;
  }
  MapLabel *GetNext()
  {
    return Next;
  }
  void SetNext(MapLabel * next)
  {
    Next = next;
  }
};

class MapLabelList
{
//
// a class implementing a list of Map Labels
//
private:
  double PixelRatio;
  MapLabel *First;
  MapLabel *Last;
public:
    MapLabelList(double pixelRatio);
   ~MapLabelList();
  void Add(MapLayer * layer, wxString & label, gaiaGeomCollPtr geom,
           double width, double height, bool noCollision);
  MapLabel *GetFirst()
  {
    return First;
  }
  void CheckCollisions();
};

class MyTipWindow:public wxWindow
{
//
// a TipWindow used for on-the-fly Identify
//
private:
  class MyMapView * Parent;
  wxString Text;
  int MouseX;
  int MouseY;
public:
    MyTipWindow(MyMapView * parent, wxString & text, int x, int y);
    virtual ~ MyTipWindow()
  {;
  }
  bool IsToBeErased(int x, int y);
  void OnPaint(wxPaintEvent & event);
  void OnEraseBackground(wxEraseEvent & WXUNUSED(event))
  {;
  }
  void OnMouseEvent(wxMouseEvent & event);
};

class MarkerGraphicResource
{
//
// a class used for marking geometries
//
private:
  bool Ok;
  bool DrawBorder;
  bool ToFill;
  wxColour LineColor;
  int LineThickness;
  wxColour FillColor;
// Graphic resources
  wxGraphicsPen Pen;
  wxGraphicsBrush Brush;
public:
    MarkerGraphicResource()
  {
    Ok = false;
  }
   ~MarkerGraphicResource()
  {;
  }
  void Init(MapLayer * layer);
  void Reset()
  {
    Ok = false;
  }
  bool IsOk()
  {
    return Ok;
  }
  bool OkDrawBorder()
  {
    return DrawBorder;
  }
  bool IsToFill()
  {
    return ToFill;
  }
  wxColour & GetLineColor()
  {
    return LineColor;
  }
  int GetLineThickness()
  {
    return LineThickness;
  }
  wxColour & GetFillColor()
  {
    return FillColor;
  }
  void CreateGraphicResources(wxGraphicsContext * gr);
  wxGraphicsPen & GetPen()
  {
    return Pen;
  }
  wxGraphicsBrush & GetBrush()
  {
    return Brush;
  }
};

class GeometryToMark
{
// a class referencing a single geometry to be marked over the map
private:
  gaiaGeomCollPtr Pointer;
  GeometryToMark *Next;
public:
    GeometryToMark(gaiaGeomCollPtr geom)
  {
    Pointer = geom;
    Next = NULL;
  }
   ~GeometryToMark()
  {;
  }
  gaiaGeomCollPtr Geometry()
  {
    return Pointer;
  }
  void SetNext(GeometryToMark * next)
  {
    Next = next;
  }
  GeometryToMark *GetNext()
  {
    return Next;
  }
};

class GeometriesToMark
{
// a class to implement a list of geometries to be marked over the map
private:
  GeometryToMark * First;
  GeometryToMark *Last;
public:
    GeometriesToMark()
  {
    First = NULL;
    Last = NULL;
  }
   ~GeometriesToMark()
  {
    Flush();
  }
  void Flush();
  void Add(gaiaGeomCollPtr geom);
  GeometryToMark *GetFirst()
  {
    return First;
  }
  bool GetExtent(double *minx, double *miny, double *maxx, double *maxy);
};

class MyMapView:public wxPanel
{
//
// a panel used  to show the Map
//
private:
  class MyFrame * MainFrame;
  MapLayersList LayersList;
  wxBitmap MapBitmap;
  wxBitmap DynamicMapBitmap;
  wxBitmap ScreenBitmap;
  int BitmapWidth;
  int BitmapHeight;
  wxSlider Zoom;
  wxBrush CheckedBrush;
  wxBitmapButton Center;
  wxBitmapButton Up;
  wxBitmapButton Down;
  wxBitmapButton Left;
  wxBitmapButton Right;
  wxBitmapButton ZoomMin;
  wxBitmapButton ZoomMax;
  wxCursor CursorCross;
  wxCursor CursorHand;
  MyTipWindow *MapTip;
  double MapMinX;
  double MapMinY;
  double MapMaxX;
  double MapMaxY;
  bool ValidMapExtent;
  int FrameWidth;
  int FrameHeight;
  double FrameCenterX;
  double FrameCenterY;
  double FrameRadius;
  double FrameMinX;
  double FrameMinY;
  double FrameMaxX;
  double FrameMaxY;
  double PixelRatio;
  int CurrentScale;
  bool ValidMap;
  int DragStartX;
  int DragStartY;
  int LastDragX;
  int LastDragY;
  int LastZoom;
  gaiaDynamicLinePtr CurrentDraw;
  bool SplashMode;
  wxBitmap *SplashLogo;
// Routing current algorithm
  bool IsCurrentRoutingAlgorithmAStar;
// Map Frame selection
  double MapFrame1x;
  double MapFrame1y;
  double MapFrame2x;
  double MapFrame2y;
  bool OkMapFrame1;
  bool OkMapFrame2;
  bool IsCapturedMouse;
// current geometry item for editing
  bool OkCurrentGeometry;
  bool OkCurrentVertex;
  gaiaPointPtr CurrentPoint;
  gaiaLinestringPtr CurrentLinestring;
  gaiaPolygonPtr CurrentPolygon;
  gaiaRingPtr CurrentRing;
  gaiaPoint CurrentVertexCoords;
  int CurrentVertexIndex;
  int CurrentSegmentIndex;
  bool OkMovedVertex;
  bool OkInterpolatedVertex;
  bool OkSplitLine;
// Candidate Entity [for MultiGeometry selection]
  bool OkCandidateEntity;
  sqlite3_int64 CandidateEntityPrimaryKey;
  gaiaGeomCollPtr CandidateEntityGeometry;
// Timers
  int MouseLastX;
  int MouseLastY;
  wxTimer *TimerMouseMove;
  int WheelTics;
  wxTimer *TimerMouseWheel;
  int IdentifyMouseX;
  int IdentifyMouseY;
  wxTimer *TimerIdentify;
  MarkerGraphicResource MarkerGraphic;
  GeometriesToMark GeomsToMark;
  bool MarkerOddEven;
  bool RoutingMarker;
  int MarkerCount;
  wxTimer *TimerMarker;
// current Identify coords
  int MouseIdentifyX;
  int MouseIdentifyY;
  bool GetRaster(void *handle, wxBitmap * bmp);
  double InternalRound(double value);
  int IntRound(double value);
public:
    MyMapView()
  {;
  }
  MyMapView(MyFrame * parent, wxWindowID id = wxID_ANY);
  virtual ~ MyMapView();

  MapLayersList *GetLayersList()
  {
    return &LayersList;
  }
  void SetMapToolsState(bool SplashMode);
  void PrepareMap();

  void ZoomTo(double minx, double miny, double maxx, double maxy);
  void ZoomToMarkedEntities();

  void ComputeMapExtent();
  void SetFrameFullExtent();
  void ClearMapExtent();
  void DragMap(int x, int y);
  void DoZoom();
  bool IsValidMapExtent()
  {
    return ValidMapExtent;
  }
  bool IsValidMapFrame();
  void UpdateFrameExtent(int lastSrid, bool lastGeographic);

  void FeedMapLabels(wxGraphicsContext * gr, MapLayer * layer,
                     MapLabelList * labelList);
  void PrepareLabels(MapLabelList * list, gaiaGeomCollPtr geometry,
                     MapLayer * layer, wxString & label, double width,
                     double height);
  bool OutsideFrame(gaiaPointPtr point);
  bool OutsideFrame(gaiaLinestringPtr line);
  bool OutsideFrame(gaiaPolygonPtr polygon);

  void DrawRasterLayer(wxGraphicsContext * gr, MapLayer * layer);
  void DrawVectorLayer(wxGraphicsContext * gr, MapLayer * layer);
  void DrawPoint(wxGraphicsContext * gr, MapLayer * layer,
                 gaiaGeomCollPtr geom);
  void DrawLinestring(wxGraphicsContext * gr, MapLayer * layer,
                      gaiaGeomCollPtr geom);
  void DrawPolygon(wxGraphicsContext * gr, MapLayer * layer,
                   gaiaGeomCollPtr geom);
  void DrawPoint(wxGraphicsContext * gr, MapSubClass * subClass,
                 gaiaGeomCollPtr geom);
  void DrawLinestring(wxGraphicsContext * gr, MapSubClass * subClass,
                      gaiaGeomCollPtr geom);
  void DrawPolygon(wxGraphicsContext * gr, MapSubClass * subClass,
                   gaiaGeomCollPtr geom);

  void MarkPoint(wxGraphicsContext * gr, gaiaGeomCollPtr geom);
  void MarkLinestring(wxGraphicsContext * gr, gaiaGeomCollPtr geom);
  void MarkPolygon(wxGraphicsContext * gr, gaiaGeomCollPtr);

  void OnTheFlyIdentify(MapLayer * layer, int mouse_x, int mouse_y);
  void SelectNetworkNode(int mouse_x, int mouse_y);
  void Identify(MapLayer * layer, int mouse_x, int mouse_y);
  void ShowMapTip(wxString & label, int x, int y);
  void ClearMapTip();
  bool IsMapTipShown();
  void ResetScreenBitmap();

  int GetCurrentDrawPoints();
  void CopyCurrentDraw(gaiaLinestringPtr line);
  void CopyCurrentDraw(gaiaRingPtr ring);
  void SetCandidateEntity(sqlite3_int64 pk, gaiaGeomCollPtr geom);
  void UnsetMultiGeometry();

  void FlushGeometriesToMark()
  {
    GeomsToMark.Flush();
  }
  void AddGeometryToMark(gaiaGeomCollPtr geom)
  {
    GeomsToMark.Add(geom);
  }
  void StartGeometryMarker(wxString & table, wxString & geomColumn);
  void StartRoutingMarker();
  void StopGeometryMarker();
  void DrawTemporaryMarkers(wxBitmap & bitmap);
  void DynamicFindVertex(double x, double y, bool includePoints);
  void DynamicFindSubGeometry(double x, double y);
  void DynamicFindMultiGeometry(double x, double y);
  void DynamicFindSegment(double x, double y);
  void DynamicFindLineToSplit(double x, double y);
  void DynamicMinDistance(double x, double y, int dims, double *coords,
                          int n_vert, double *dist, int *segmentIndex);
  void DynamicMinDistanceIntersect(double x, double y, int dims, double *coords,
                                   int n_vert, double *dist, int *segmentIndex,
                                   double *xx, double *yy);
  void DynamicMinDistanceVertex(double x, double y, int dims, double *coords,
                                int n_vert, double *dist, int *vertexIndex,
                                double *xx, double *yy);
  void DynamicDrawNetworkNode(wxGraphicsContext * gr);
  void DynamicDrawRoutingSolution(wxGraphicsContext * gr);
  void DynamicDrawElastic(bool ring, double x, double y);
  void DynamicDraw(bool ring);
  void DynamicDrawCommon(bool ring, int points, wxGraphicsContext * gr);
  void DynamicDrawGeometry(wxGraphicsContext * gr, gaiaGeomCollPtr geom);
  void DynamicDrawVertex(wxGraphicsContext * gr);
  void DynamicDrawSegment(wxGraphicsContext * gr);
  bool DynamicDeleteVertex();
  bool DynamicDeleteSubGeometry();
  void DynamicShowMoveVertex(double x, double y);
  void DynamicShowInterpolateVertex(double x, double y);
  bool DynamicDoMoveVertex(double x, double y);
  bool DynamicDoInterpolateVertex(double x, double y);
  bool DynamicSplitLine();
  bool DynamicDoSplitLinestring(gaiaLinestringPtr oldLine, int segmIdx,
                                int vrtxIdx, gaiaPointPtr vrtxCoords,
                                gaiaDynamicLinePtr * newLine1,
                                gaiaDynamicLinePtr * newLine2);
  void DynamicShowMapFrameSelection(double x, double y);
  void DynamicDrawMapFrameSelection(wxGraphicsContext * gr);
  void ResetDynamics(LayerObject * activeLayer);
  void ResetDynamics();
  void ResolveRouting();
  void ZoomIn();
  void ZoomOut();

  void UnsetMapFrameSelection();
  bool IsMapFrameSelection();
  void SetMapFrameFullExtent();
  bool GetMapFrameSelection(double *minX, double *minY, double *maxX,
                            double *maxY);
  bool GetMapFrameSelection(double x, double y, double *minX, double *minY,
                            double *maxX, double *maxY);

  void OnSize(wxSizeEvent & event);
  void OnPaint(wxPaintEvent & event);
  void OnMouseWheel(wxMouseEvent & event);
  void OnMouseMove(wxMouseEvent & event);
  void OnMouseClick(wxMouseEvent & event);
  void OnMouseDoubleClick(wxMouseEvent & event);
  void OnMouseRightClick(wxMouseEvent & event);
  void OnMouseDragStop(wxMouseEvent & event);
  void OnZoom(wxScrollEvent & event);
  void OnCenter(wxCommandEvent & event);
  void OnUp(wxCommandEvent & event);
  void OnDown(wxCommandEvent & event);
  void OnLeft(wxCommandEvent & event);
  void OnRight(wxCommandEvent & event);
  void OnZoomMinus(wxCommandEvent & event);
  void OnZoomPlus(wxCommandEvent & event);
  void OnMicroUp(wxCommandEvent & event);
  void OnMicroDown(wxCommandEvent & event);
  void OnMicroLeft(wxCommandEvent & event);
  void OnMicroRight(wxCommandEvent & event);
  void OnZoomIn(wxCommandEvent & event);
  void OnZoomOut(wxCommandEvent & event);
  void OnZoomMicroIn(wxCommandEvent & event);
  void OnZoomMicroOut(wxCommandEvent & event);
  void OnDrawAbort(wxCommandEvent & event);
  void OnDrawUndo(wxCommandEvent & event);
  void OnDrawStop(wxCommandEvent & event);
  void OnCmdEditMode(wxCommandEvent & event);
  void OnCmdIdentify(wxCommandEvent & event);
  void OnCmdNodeFrom(wxCommandEvent & event);
  void OnCmdNodeTo(wxCommandEvent & event);
  void OnCmdReturnTrip(wxCommandEvent & event);
  void OnCmdRouteClear(wxCommandEvent & event);
  void OnCmdRoutingAlgorithm(wxCommandEvent & event);
  void OnEraseBackground(wxEraseEvent & WXUNUSED(event))
  {;
  }
  void OnTimerMouseMove(wxTimerEvent & event);
  void OnTimerMouseWheel(wxTimerEvent & event);
  void OnTimerIdentify(wxTimerEvent & event);
  void OnTimerMarker(wxTimerEvent & event);
  void OnCapturedMouseLost(wxMouseCaptureLostEvent & event);
};

class MyMapOutput
{
//
// a class implementing Map Output
//
private:
  class MyFrame * MainFrame;
  MapLayersList *LayersList;
  wxBitmap Bitmap;
  int BitmapWidth;
  int BitmapHeight;
  double FrameMinX;
  double FrameMinY;
  double FrameMaxX;
  double FrameMaxY;
  double PixelRatio;
  int CurrentScale;
  int RasterFormat;
  bool IsSvg;
  bool IsPdf;
  bool IsCopyToClipboard;
  bool IsWorldFile;
  wxColour BackgroundColor;
  bool PdfPageSizeA3;
  bool PdfLandscape;
  int PdfDpi;
  double PdfPageWidth;
  double PdfPageHeight;
  bool GetRaster(void *handle, wxBitmap * bmp);
  bool GetPdfRaster(void *handle, wxBitmap * bmp);
  double InternalRound(double value);
  int IntRound(double value);
  void ComputeScale();
  void ComputeScale(HPDF_Page page);
  iconv_t IconvObj;
  bool ToLatin1(wxString & str, char **buf);
public:
    MyMapOutput(MyFrame * parent, MapLayersList * layers, int width, int height,
                double minX, double minY, double maxX, double maxY);
    MyMapOutput(MyFrame * parent, MapLayersList * layers, int width, int height,
                double minX, double minY, double maxX, double maxY, bool a3,
                bool landscape, int dpi);
    MyMapOutput(MyFrame * parent, MapLayersList * layers, int width, int height,
                double minX, double minY, double maxX, double maxY,
                wxColour & background);
    MyMapOutput(MyFrame * parent, MapLayersList * layers, int width, int height,
                int format, double minX, double minY, double maxX, double maxY,
                wxColour & background, bool worldFile);
   ~MyMapOutput();

  void OutputPdfMap();
  void OutputSvgMap();
  void OutputRasterMap();
  void DoCopyToClipboard();
  void DoOutputImage();
  bool GenerateWorldFile(wxString & path);

  void FeedMapLabels(wxGraphicsContext * gr, MapLayer * layer,
                     MapLabelList * labelList);
  void FeedMapLabels(HPDF_Doc pdf, HPDF_Page page, MapLayer * layer,
                     MapLabelList * labelList);
  void PrepareLabels(MapLabelList * list, gaiaGeomCollPtr geometry,
                     MapLayer * layer, wxString & label, double width,
                     double height);
  bool OutsideFrame(gaiaPointPtr point);
  bool OutsideFrame(gaiaLinestringPtr line);
  bool OutsideFrame(gaiaPolygonPtr polygon);
  void DrawRasterLayer(wxGraphicsContext * gr, MapLayer * layer);
  void DrawVectorLayer(wxGraphicsContext * gr, MapLayer * layer);
  void DrawPoint(wxGraphicsContext * gr, MapLayer * layer,
                 gaiaGeomCollPtr geom);
  void DrawLinestring(wxGraphicsContext * gr, MapLayer * layer,
                      gaiaGeomCollPtr geom);
  void DrawPolygon(wxGraphicsContext * gr, MapLayer * layer,
                   gaiaGeomCollPtr geom);
  void DrawPoint(wxGraphicsContext * gr, MapSubClass * subClass,
                 gaiaGeomCollPtr geom);
  void DrawLinestring(wxGraphicsContext * gr, MapSubClass * subClass,
                      gaiaGeomCollPtr geom);
  void DrawPolygon(wxGraphicsContext * gr, MapSubClass * subClass,
                   gaiaGeomCollPtr geom);

  void SvgVectorLayer(FILE * svg, MapLayer * layer);
  void PdfVectorLayer(HPDF_Doc pdf, HPDF_Page page, MapLayer * layer);
  void PdfRasterLayer(HPDF_Doc pdf, HPDF_Page page, MapLayer * layer);
  void PdfPoint(PdfSymbolList * list, HPDF_Page page, MapLayer * layer,
                gaiaGeomCollPtr geom);
  void PdfLinestring(HPDF_Page page, MapLayer * layer, gaiaGeomCollPtr geom);
  void PdfPolygon(HPDF_Page page, MapLayer * layer, gaiaGeomCollPtr geom);
  void PdfPoint(HPDF_Page page, MapSubClass * subClass, gaiaGeomCollPtr geom);
  void PdfLinestring(HPDF_Page page, MapSubClass * subClass,
                     gaiaGeomCollPtr geom);
  void PdfPolygon(HPDF_Page page, MapSubClass * subClass, gaiaGeomCollPtr geom);
};

class NetworkNode
{
//
// Network From/To nodes
//
private:
  wxString NodeText;
  sqlite3_int64 NodeId;
  double X;
  double Y;
  bool Valid;
public:
    NetworkNode()
  {
    Valid = false;
  }
   ~NetworkNode()
  {;
  }
  void Unset()
  {
    Valid = false;
  }
  void Set(NetworkNode * other)
  {
    NodeText = other->NodeText;
    NodeId = other->NodeId;
    X = other->X;
    Y = other->Y;
    Valid = other->Valid;
  }
  void Set(sqlite3_int64 node, double x, double y)
  {
    NodeId = node;
    X = x;
    Y = y;
    Valid = true;
  }
  void Set(const unsigned char *node, double x, double y)
  {
    NodeText = wxString::FromUTF8((const char *) node);
    X = x;
    Y = y;
    Valid = true;
  }
  wxString & GetNodeText()
  {
    return NodeText;
  }
  sqlite3_int64 GetNodeId()
  {
    return NodeId;
  }
  void SetCoords(double x, double y)
  {
    X = x;
    Y = y;
  }
  double GetX()
  {
    return X;
  }
  double GetY()
  {
    return Y;
  }
  bool IsValid()
  {
    return Valid;
  }
};

class NetNodePre
{
//
// a class to store a temporary node for Network
//
private:
  sqlite3_int64 Id;
  wxString Code;
  NetNodePre *Next;
public:
    NetNodePre(sqlite3_int64 id);
    NetNodePre(const char *code);
   ~NetNodePre()
  {;
  }
  sqlite3_int64 GetId()
  {
    return Id;
  }
  wxString & GetCode()
  {
    return Code;
  }
  void SetNext(NetNodePre * next)
  {
    Next = next;
  }
  NetNodePre *GetNext()
  {
    return Next;
  }
};

class NetNode
{
//
// a class to store a final node for Network
//
private:
  int InternalIndex;
  sqlite3_int64 Id;
  wxString Code;
  double X;
  double Y;
  class NetArcRef *First;
  class NetArcRef *Last;
  NetNode *Next;
public:
    NetNode(sqlite3_int64 id);
    NetNode(wxString & code);
   ~NetNode();
  int GetInternalIndex()
  {
    return InternalIndex;
  }
  void SetInternalIndex(int idx)
  {
    InternalIndex = idx;
  }
  sqlite3_int64 GetId()
  {
    return Id;
  }
  wxString & GetCode()
  {
    return Code;
  }
  double GetX()
  {
    return X;
  }
  void SetX(double x)
  {
    X = x;
  }
  double GetY()
  {
    return Y;
  }
  void SetY(double y)
  {
    Y = y;
  }
  void AddOutcoming(class NetArc * pA);
  NetArcRef *GetFirst()
  {
    return First;
  }
  NetArc **PrepareOutcomings(int *count);
  void SetNext(NetNode * next)
  {
    Next = next;
  }
  NetNode *GetNext()
  {
    return Next;
  }
};

class NetArc
{
//
// a class to store an arc for Network
//
private:
  sqlite3_int64 RowId;
  NetNode *From;
  NetNode *To;
  double Cost;
  NetArc *Next;
public:
    NetArc(sqlite3_int64 rowid, NetNode * from, NetNode * to, double cost);
   ~NetArc()
  {;
  }
  sqlite3_int64 GetRowId()
  {
    return RowId;
  }
  NetNode *GetFrom()
  {
    return From;
  }
  NetNode *GetTo()
  {
    return To;
  }
  double GetCost()
  {
    return Cost;
  }
  void SetNext(NetArc * next)
  {
    Next = next;
  }
  NetArc *GetNext()
  {
    return Next;
  }
};

class NetArcRef
{
//
// a class to store a reference to an arc for Network
//
private:
  NetArc * Reference;
  NetArcRef *Next;
public:
    NetArcRef(NetArc * arc)
  {
    Reference = arc;
    Next = NULL;
  }
   ~NetArcRef()
  {;
  }
  NetArc *GetReference()
  {
    return Reference;
  }
  void SetNext(NetArcRef * next)
  {
    Next = next;
  }
  NetArcRef *GetNext()
  {
    return Next;
  }
};

class Network
{
//
// a class representing a Network
//
private:
  NetNodePre * FirstPre;
  NetNodePre *LastPre;
  int NumPreNodes;
  NetNodePre **SortedPreNodes;
  NetArc *FirstArc;
  NetArc *LastArc;
  NetNode *FirstNode;
  NetNode *LastNode;
  int NumNodes;
  NetNode **SortedNodes;
  bool Error;
  bool NodeCode;
  int MaxCodeLength;
public:
    Network();
   ~Network();
  void CleanPreNodes();
  void InsertNode(sqlite3_int64 id);
  void InsertNode(const char *code);
  void AddNode(sqlite3_int64 id);
  void AddNode(wxString & code);
  NetNode *ProcessNode(sqlite3_int64 id, double x, double y, NetNode ** pOther);
  NetNode *ProcessNode(wxString & code, double x, double y, NetNode ** pOther);
  void Sort();
  NetNode *Find(sqlite3_int64 id);
  NetNode *Find(wxString & code);
  NetNode *GetSortedNode(sqlite3_int64 x);
  void AddArc(sqlite3_int64 rowid, sqlite3_int64 id_from, sqlite3_int64 id_to,
              double node_from_x, double node_from_y, double node_to_x,
              double node_to_y, double cost);
  void AddArc(sqlite3_int64 rowid, const char *code_from, const char *code_to,
              double node_from_x, double node_from_y, double node_to_x,
              double node_to_y, double cost);
  void InitNodes();
  void SetError()
  {
    Error = true;
  }
  bool IsError()
  {
    return Error;
  }
  void SetNodeCode(bool mode)
  {
    NodeCode = mode;
  }
  bool IsNodeCode()
  {
    return NodeCode;
  }
  int GetNumNodes()
  {
    return NumNodes;
  }
  int GetMaxCodeLength()
  {
    return MaxCodeLength;
  }
};

class SolutionArc
{
//
// an arc used by the routing solution
//
private:
  sqlite3_int64 ArcId;
  wxString NodeFromText;
  sqlite3_int64 NodeFromId;
  wxString NodeToText;
  sqlite3_int64 NodeToId;
  double Cost;
  wxString Name;
  SolutionArc *Next;
public:
    SolutionArc(sqlite3_int64 id, sqlite3_int64 from, sqlite3_int64 to,
                double cost, const char *name);
    SolutionArc(sqlite3_int64 id, const char *from, const char *to,
                double cost, const char *name);
   ~SolutionArc()
  {;
  }
  sqlite3_int64 GetArcId()
  {
    return ArcId;
  }
  sqlite3_int64 GetNodeFromId()
  {
    return NodeFromId;
  }
  wxString & GetNodeFromText()
  {
    return NodeFromText;
  }
  sqlite3_int64 GetNodeToId()
  {
    return NodeToId;
  }
  wxString & GetNodeToText()
  {
    return NodeToText;
  }
  double GetCost()
  {
    return Cost;
  }
  wxString & GetName()
  {
    return Name;
  }
  void SetNext(SolutionArc * next)
  {
    Next = next;
  }
  SolutionArc *GetNext()
  {
    return Next;
  }
};

class RoutingSolution
{
//
// the routing solution
//
private:
  wxString NodeFromText;
  sqlite3_int64 NodeFromId;
  wxString NodeToText;
  sqlite3_int64 NodeToId;
  SolutionArc *First;
  SolutionArc *Last;
  double Cost;
  gaiaGeomCollPtr Geometry;
  bool Valid;
  wxDateTime StartTime;
  wxDateTime StopTime;
  wxString RoutingAlgorithm;
public:
    RoutingSolution();
   ~RoutingSolution()
  {
    CleanUp();
  }
  void CleanUp();
  void SetFromTo(sqlite3_int64 from, sqlite3_int64 to);
  void SetFromTo(wxString & from, wxString & to);
  void SetGeometry(gaiaGeomCollPtr geom)
  {
    Geometry = geom;
  }
  gaiaGeomCollPtr GetGeometry()
  {
    return Geometry;
  }
  void SetCost(double cost)
  {
    Cost = cost;
  }
  double GetCost()
  {
    return Cost;
  }
  sqlite3_int64 GetNodeFromId()
  {
    return NodeFromId;
  }
  wxString & GetNodeFromText()
  {
    return NodeFromText;
  }
  sqlite3_int64 GetNodeToId()
  {
    return NodeToId;
  }
  wxString & GetNodeToText()
  {
    return NodeToText;
  }
  void Add(sqlite3_int64 id, sqlite3_int64 from, sqlite3_int64 to, double cost,
           const unsigned char *name);
  void Add(sqlite3_int64 id, const unsigned char *from, const unsigned char *to,
           double cost, const unsigned char *name);
  SolutionArc *GetFirst()
  {
    return First;
  }
  SolutionArc *FindByPos(int pos);
  void CheckValid();
  bool IsValid()
  {
    return Valid;
  }
  int GetCount();
  void TimeStart();
  void TimeStop();
  void GetElapsedTime(wxString & str);
  void SetRoutingAlgorithm(wxString & algorithm)
  {
    RoutingAlgorithm = algorithm;
  }
  wxString & GetRoutingAlgorithm()
  {
    return RoutingAlgorithm;
  }
};

class NetworkParams
{
//
// Network Params
//
private:
  wxString MainTable;
  wxString NetworkTable;
  wxString NodesAuxTable;
  wxString NodeFromColumn;
  wxString NodeToColumn;
  wxString GeometryColumn;
  wxString NameColumn;
  int Srid;
  bool TextNodes;
  bool MainRTree;
  bool AuxNodesRTree;
  NetworkNode CurrentNode;
  NetworkNode NodeFrom;
  NetworkNode NodeTo;
  RoutingSolution Solution;
public:
    NetworkParams();
   ~NetworkParams()
  {;
  }
  void SetMainTable(wxString & x)
  {
    MainTable = x;
  }
  wxString & GetMainTable()
  {
    return MainTable;
  }
  void SetNetworkTable(wxString & x)
  {
    NetworkTable = x;
  }
  wxString & GetNetworkTable()
  {
    return NetworkTable;
  }
  void SetNodesAuxTable(wxString & x)
  {
    NodesAuxTable = x;
  }
  wxString & GetNodesAuxTable()
  {
    return NodesAuxTable;
  }
  void SetNodeFromColumn(const char *x)
  {
    NodeFromColumn = wxString::FromUTF8(x);
  }
  wxString & GetNodeFromColumn()
  {
    return NodeFromColumn;
  }
  void SetNodeToColumn(const char *x)
  {
    NodeToColumn = wxString::FromUTF8(x);
  }
  wxString & GetNodeToColumn()
  {
    return NodeToColumn;
  }
  void SetGeometryColumn(const char *x)
  {
    GeometryColumn = wxString::FromUTF8(x);
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  void SetNameColumn(const char *x)
  {
    NameColumn = wxString::FromUTF8(x);
  }
  wxString & GetNameColumn()
  {
    return NameColumn;
  }
  void SetSrid(int x)
  {
    Srid = x;
  }
  int GetSrid()
  {
    return Srid;
  }
  void SetTextNodes(bool x)
  {
    TextNodes = x;
  }
  bool IsTextNodes()
  {
    return TextNodes;
  }
  void SetMainRTree(bool x)
  {
    MainRTree = x;
  }
  bool IsMainRTree()
  {
    return MainRTree;
  }
  void SetAuxNodesRTree(bool x)
  {
    AuxNodesRTree = x;
  }
  bool IsAuxNodesRTree()
  {
    return AuxNodesRTree;
  }
  void UnsetNodeFrom()
  {
    NodeFrom.Unset();
  }
  void UnsetNodeTo()
  {
    NodeTo.Unset();
  }
  void UnsetCurrentNode()
  {
    CurrentNode.Unset();
  }
  void SwapFromTo();
  void SetNodeFrom()
  {
    NodeFrom.Set(&CurrentNode);
  }
  void SetNodeTo()
  {
    NodeTo.Set(&CurrentNode);
  }
  void SetCurrentNode(sqlite3_int64 node, double x, double y)
  {
    CurrentNode.Set(node, x, y);
  }
  void SetCurrentNode(const unsigned char *node, double x, double y)
  {
    CurrentNode.Set(node, x, y);
  }
  NetworkNode *GetNodeFrom()
  {
    return &NodeFrom;
  }
  NetworkNode *GetNodeTo()
  {
    return &NodeTo;
  }
  NetworkNode *GetCurrentNode()
  {
    return &CurrentNode;
  }
  RoutingSolution *GetSolution()
  {
    return &Solution;
  }
  void UnsetSolution()
  {
    Solution.CleanUp();
  }
};

class MapOutliner
{
//
// a class to apply Label Outlines
//
private:
  bool Valid;
  wxFont Font;
  wxBitmap *Bitmap;
  wxMemoryDC *BmpDC;
  wxGraphicsContext *BmpGR;
  int TextColor;
  int TransparentColor;
  int OutlineColor;
  void OutlinePixel(wxImage * img, int x, int y);
public:
    MapOutliner(int width, int height, wxFont & font);
   ~MapOutliner();
  void Draw(MapLayer * layer, wxString & label, double x, double y,
            double rotation);
  void Outline();
  wxBitmap *GetBitmap()
  {
    return Bitmap;
  }
  bool IsValid()
  {
    return Valid;
  }
};

class MyFrame:public wxFrame
{
//
// the main GUI frame
//
private:
  wxAuiManager Manager;         // the GUI manager
  wxString ConfigLayout;        // PERSISTENCY - the layout configuration
  int ConfigPaneX;              // PERSISTENCY - the main pane screen origin X
  int ConfigPaneY;              // PERSISTENCY - the main pane screen origin Y
  int ConfigPaneWidth;          // PERSISTENCY - the main pane screen width
  int ConfigPaneHeight;         // PERSISTENCY - the main pane screen height
  MyLayerTree *LayerTree;       // the layer tree list
  MyMapView *MapView;           // the map panel
  sqlite3 *SqliteHandle;        // handle for SQLite DB
  wxString SqlitePath;          // path of SQLite DB
  wxString ExternalSqlitePath;  // path of external SQLite DB [LOAD/SAVE MEMORY database]
  bool MemoryDatabase;          // TRUE if we are currently working on the MEMORY database
  wxString LastDirectory;       // path of directory used  
  int CharsetsLen;              // # charsets defined
  wxString *Charsets;           // table of charsets [code only]
  wxString *CharsetsNames;      // table of charsets [with description]
  wxString LocaleCharset;       // locale charset
  wxString DefaultCharset;      // default charset
  bool AskCharset;              // switch to set default charset for every output
  wxBitmap *BtnCreateNew;       // button icon for DB CREATE&CONNECT
  wxBitmap *BtnConnect;         // button icon for DB CONNECT
  wxBitmap *BtnDisconnect;      // button icon for DB DISCONNECT
  wxBitmap *BtnMemDbLoad;       // button icon for MEMORY DB LOAD
  wxBitmap *BtnMemDbNew;        // button icon for MEMORY DB NEW
  wxBitmap *BtnMemDbClock;      // button icon for MEMORY DB CLOCK
  wxBitmap *BtnMemDbSave;       // button icon for MEMORY DB SAVE
  wxBitmap *BtnVacuum;          // button icon for DB VACUUM
  wxBitmap *BtnMapFrameSel;     // button icon for Map Frame
  wxBitmap *BtnOutputMap;       // button icon for Output Map
  wxBitmap *BtnCrs;             // button icon for Project CRS
  wxBitmap *BtnLoadShp;         // button icon for LOAD SHP
  wxBitmap *BtnTableAdd;        // button icon for TABLE ADD
  wxBitmap *BtnSrids;           // button icon for SEARCH SRIDs
  wxBitmap *BtnCharset;         // button icon for Default CHARSET
  wxBitmap *BtnLineMeter;       // button icon for Line Meter
  wxBitmap *BtnPolygonMeter;    // button icon for Polygon Meter
  wxBitmap *BtnPencil;          // button icon for Draw
  wxBitmap *BtnPencilAdd;       // button icon for Draw - Interpolate Vertex
  wxBitmap *BtnPencilDelete;    // button icon for Draw - Delete Vertex
  wxBitmap *BtnPencilGo;        // button icon for Draw - Move Vertex
  wxBitmap *BtnDeleteSubGeom;   // button icon for Draw - Delete SubGeometry
  wxBitmap *BtnSplitLine;       // button icon for Draw - Split Line
  wxBitmap *BtnSelectMultiGeom; // button icon for Draw - Select Current MULTI Geometry
  wxBitmap *BtnAbout;           // button icon for ABOUT
  wxBitmap *BtnExit;            // button icon for EXIT
  LayerObject *ActiveLayer;     // ACTIVE LAYER
  int CurrentDrawMode;          // current draw mode
  int LastSrid;
  bool LastGeographic;
  SridInfo ProjectSrid;         // the project SRID infos
  wxString ProjectName;         // the project's Name
  NetworkParams *NetParms;      // supporting Network 
// AutoSave timer
  int AutoSaveInterval;
  int LastTotalChanges;
  wxTimer *TimerAutoSave;
// Current Entity [for geometry editing]
  bool OkCurrentEntity;
  sqlite3_int64 CurrentEntityPrimaryKey;
  gaiaGeomCollPtr CurrentEntityGeometry;
public:
    MyFrame(const wxString & title, const wxPoint & pos, const wxSize & size);
    virtual ~ MyFrame();

  void UpdateReferenceSystem();
  void UpdateScale(wxString & scale);
  void UpdateCoords(wxString & coords);

  bool IsConnected()
  {
    if (SqliteHandle)
      return true;
    else
      return false;
  }
  sqlite3 *GetSqlite()
  {
    return SqliteHandle;
  }
  void SetLastDirectory(wxString & path)
  {
    LastDirectory = path;
  }
  wxString & GetLastDirectory()
  {
    return LastDirectory;
  }
  void SaveConfig();
  void LoadConfig(wxString & externalPath);

  bool OpenDB();
  void CloseDB();
  bool CreateDB();
  bool CreateSpatialMetaData();
  bool CheckMetadata();
  bool CheckSymbolBitmaps(int *invalid);
  bool CheckPatternBitmaps(int *invalid);
  bool CheckLayerParams(int *invalid);
  bool CheckLayerSubClasses(int *invalid);
  void CheckLayerStatistics(int *invalid);
  void CheckVirtsLayerStatistics(int *invalid);
  void CheckViewsLayerStatistics(int *invalid);
  bool CheckRasterPyramids(int *invalid);
  bool CheckProjectDefs(int *invalid);
  bool CheckLayerTableLayout(int *invalid);
  bool CreateSymbolBitmaps();
  bool CreatePatternBitmaps();
  bool CreateLayerParams();
  bool CreateLayerSubClasses();
  bool CreateRasterPyramids();
  bool CreateProjectDefs();
  bool CreateLayerTableLayout();
  void InitLayerTree();
  void ClearLayerTree();
  void ProjectSridChanged();
  bool IsMemoryDatabase()
  {
    return MemoryDatabase;
  }
  wxString & GetSqlitePath()
  {
    return SqlitePath;
  }
  wxString & GetExternalSqlitePath()
  {
    return ExternalSqlitePath;
  }
  void SetExternalSqlitePath(wxString & path)
  {
    ExternalSqlitePath = path;
  }
  MapLayersList *GetLayersList();
  void SetProjectName(wxString & name)
  {
    ProjectName = name;
  }
  wxString & GetProjectName()
  {
    return ProjectName;
  }
  void GetSridInfo(int srid);
  void GetSridInfo(SridInfo * info);
  SridInfo & GetProjectCrs()
  {
    return ProjectSrid;
  }
  void SetProjectCrs(SridInfo & info);
  void SetActiveLayer(LayerObject * p)
  {
    ActiveLayer = p;
    UnsetDrawTools();
    FreeNetworkParams();
  }
  LayerObject *GetActiveLayer()
  {
    return ActiveLayer;
  }
  NetworkParams *GetNetwork()
  {
    return NetParms;
  }
  bool IsCurrentRoutingAlgorithmAStar(wxString & table);
  void SetRoutingAlgorithm(wxString & table, bool aStar);
  void LoadNetworkParams();
  void FreeNetworkParams();
  bool FeedNetworkNodes();
  bool CreateNetworkNodesRTree();
  bool CheckNetworkNodes(int *invalid);
  bool ParseNetworkHeader(NetworkParams * network, const unsigned char *blob,
                          int size);
  void GetColumnList(wxString & table, int *count, wxString ** list);
  void GetColumnList(wxString & table, int *count, wxString ** list,
                     wxString & geomColumn, int geomType);
  MyLayerList *GetLayerList();
  void UpdateLayersList(MapLayersList * list, bool force);
  MyLayerParamsList *GetLayerParamsList();
  void GetSymbolBitmaps(MyImageList * list);
  void GetPatternBitmaps(MyImageList * list);
  void AlignLayerParams();
  bool CheckNetwork(wxString & table);
  bool GetProjParams(int srid, char *proj_params);
  void UpdateLayerParams(LayerObject * layer);
  bool ZoomToLayerExtent(LayerObject * layer);
  void ResetMapDynamics(LayerObject * p)
  {
    MapView->ResetDynamics(p);
  }
  void RefreshMap()
  {
    MapView->PrepareMap();
  }
  void UpdateLayersEditMode()
  {
    LayerTree->UpdateLayersEditMode(MapView->GetLayersList());
  }
  MyMapView *GetMap()
  {
    return MapView;
  }
  void UpdateSubClassesParams(wxTreeItemId & layer,
                              class SubClassesPreview * subClasses,
                              bool uniqueValue, wxString & columnName,
                              int numClasses, double minValue, double maxValue,
                              int symbolType, int minSize, int maxSize,
                              wxColour & minColor, wxColour & maxColor);
  void DropSubClasses(wxTreeItemId & layer);
  void UpdateZOrder();
  void UpdateProjectDefs();
  void LoadProjectDefs();
  void AlignStatistics();
  void UpdateStatistics();
  void UpdateStatistics(wxString & tableName);
  void UpdateStatistics(wxString & tableName, wxString & geometryColumn);
  bool InsertLayerParams(LayerObject * layer);
  bool DeleteLayer(LayerObject * layer);
  bool InsertLayerStatistics(LayerObject * layer, int count, double minx,
                             double miny, double maxx, double maxy);
  int GetSpatialIndexType(wxString & table, wxString & geometry);

  void GetDistinctValues(wxString & TableName, wxString & ClassifyColumn,
                         MyDistinctValueList * list, bool * truncated);
  void GetMaxMinValues(wxString & TableName, wxString & ClassifyColumn,
                       double *min, double *max, bool * invalid);
  bool BestRasterResolution(wxString & prefix, double ratio,
                            double *pixel_x_ratio, double *pixel_y_ratio);

  wxString *GetCharsets()
  {
    return Charsets;
  }
  wxString *GetCharsetsNames()
  {
    return CharsetsNames;
  }
  int GetCharsetsLen()
  {
    return CharsetsLen;
  }
  wxString & GetLocaleCharset()
  {
    return LocaleCharset;
  }
  wxString & GetDefaultCharset()
  {
    return DefaultCharset;
  }
  wxString & GetCharsetName(wxString & charset);
  int GetCharsetIndex(wxString & charset);
  bool IsSetAskCharset()
  {
    return AskCharset;
  }
  bool TableAlreadyExists(wxString & name);
  bool SridNotExists(int srid);
  gaiaDbfFieldPtr GetDbfField(gaiaDbfListPtr list, char *name);
  void LoadShapefile(wxString & path, wxString & table, int srid,
                     wxString & column, wxString & charset, bool coerce2D,
                     bool compressed);
  void DumpShapefile(wxString & path, wxString & table, wxString & column,
                     wxString & charset, bool isView);

  void ConvertString(wxString & str, char *buf, int *len);
  void ReplaceDecimalComma(wxString & str);
  bool FormatBoolean(wxString & value, bool * bool_value);
  void ColorFromRGBA(char *rgba, wxColour & color);
  int LineStyleFromConstant(char *constant);
  int SymbolTypeFromConstant(char *constant);
  void GetRandomColor(int *red, int *green, int *blue);
  void GetRandomColorSature(int *red, int *green, int *blue);
  void GetRandomColorMedium(int *red, int *green, int *blue);
  void GetRandomColorLight(int *red, int *green, int *blue);

  int ColumnTypeFromConstant(char *constant);

  bool ConvertToJulianDate(char *date, double *julian);
  void ConvertFromJulianDate(double julian, char *date);
  bool ConvertToJulianDateTime(char *datetime, double *julian);
  void ConvertFromJulianDateTime(double julian, char *datetime);

  void EnableMeterTools(bool mode);
  void EnableDrawTools();
  void UnsetMeterTools();
  void UnsetDrawTools();
  bool IsMapFrameSelectionEnabled();
  bool IsMeasureLineEnabled();
  bool IsMeasurePolygonEnabled();
  bool IsPencilEnabled();
  bool IsPencilAddEnabled();
  bool IsPencilDeleteEnabled();
  bool IsPencilGoEnabled();
  bool IsCutRedEnabled();
  bool IsCutBlueEnabled();
  bool IsAsteriskEnabled();
  bool IsMapFrameSelectionChecked();
  bool IsMeasureLineChecked();
  bool IsMeasurePolygonChecked();
  bool IsPencilChecked();
  bool IsPencilAddChecked();
  bool IsPencilDeleteChecked();
  bool IsPencilGoChecked();
  bool IsCutRedChecked();
  bool IsCutBlueChecked();
  bool IsAsteriskChecked();
  bool IsAnyDrawModeActive();
  bool IsDrawActive();
  bool IsDrawPointActive();
  bool IsDrawLineActive();
  bool IsDrawRingActive();
  bool IsSelectMultiGeomActive();

  wxString *GetTables(int *cnt, wxString & table, int *sel);
  wxString *GetColumnNames(wxString & table, int *columns, wxString & geom,
                           int *sel);
  bool DestroyNetwork(wxString & table);
  bool BuildNetwork(wxString & table, wxString & from, wxString & to,
                    wxString & geometry, wxString & name, bool cost_length,
                    wxString & cost, bool bidirectional, bool one_way,
                    wxString & one_way_from_to, wxString & one_way_to_from,
                    bool aStarSupported);
  bool CreateNetwork(class Network * net, wxString & table, wxString & from,
                     wxString & to, wxString & geometry, wxString & name,
                     bool aStarSupported, double aStarCoeff);
  void OutputNetNode(unsigned char *auxbuf, int *size, int ind, bool node_code,
                     int max_node_length, class NetNode * pN, int endian_arch,
                     bool aStarSupported);

  bool IsCurrentEntity()
  {
    return OkCurrentEntity;
  }
  void SetCurrentEntity(IdentifyEntity * ptr);
  void SetCurrentEntity(sqlite3_int64 pk, gaiaGeomCollPtr geom);
  sqlite3_int64 GetCurrentEntityPrimaryKey()
  {
    return CurrentEntityPrimaryKey;
  }
  void SetCurrentEntityGeometry(gaiaGeomCollPtr geom)
  {
    CurrentEntityGeometry = geom;
  }
  gaiaGeomCollPtr GetCurrentEntityGeometry()
  {
    return CurrentEntityGeometry;
  }
  gaiaGeomCollPtr CreateNewGeometry();
  int GetActiveLayerDeclaredType();
  bool IsValidInteriorRing(gaiaDynamicLinePtr draw, gaiaPolygonPtr * polyg);
  void AddInteriorRing(gaiaDynamicLinePtr draw, int points,
                       gaiaPolygonPtr polyg);
  void UpdateCurrentEntityGeometry();
  void InsertNewEntity();

  bool MemoryDbSave();
  void LastDitchMemoryDbSave();

  void DbPagesCount(int *total, int *frees);

  void EnableMapOutput();
  bool CheckSvgGraphics();
  bool CheckPdfGraphics();

  void OnQuit(wxCommandEvent & event);
  void OnAbout(wxCommandEvent & event);
  void OnConnect(wxCommandEvent & event);
  void OnCreateNew(wxCommandEvent & event);
  void OnDisconnect(wxCommandEvent & event);
  void OnMemoryDbLoad(wxCommandEvent & event);
  void OnMemoryDbNew(wxCommandEvent & event);
  void OnMemoryDbClock(wxCommandEvent & event);
  void OnMemoryDbSave(wxCommandEvent & event);
  void OnVacuum(wxCommandEvent & event);
  void OnMapFrameSelection(wxCommandEvent & event);
  void OnMapFrameFullExtent(wxCommandEvent & event);
  void OnOutputMap(wxCommandEvent & event);
  void OnLoadShp(wxCommandEvent & event);
  void OnTableAdd(wxCommandEvent & event);
  void OnProjectCrs(wxCommandEvent & event);
  void OnSrids(wxCommandEvent & event);
  void OnCharset(wxCommandEvent & event);
  void OnLineMeter(wxCommandEvent & event);
  void OnPolygonMeter(wxCommandEvent & event);
  void OnDraw(wxCommandEvent & event);
  void OnDrawInterpolate(wxCommandEvent & event);
  void OnDrawDelete(wxCommandEvent & event);
  void OnDrawMove(wxCommandEvent & event);
  void OnDrawDeleteSubGeom(wxCommandEvent & event);
  void OnDrawSplitLine(wxCommandEvent & event);
  void OnDrawSelectMultiGeom(wxCommandEvent & event);
  void OnTimerAutoSave(wxTimerEvent & event);
};

class SearchSridDialog:public wxDialog
{
//
// a dialog preparing a Search SRID by name
//
private:
  MyFrame * MainFrame;
  wxTextCtrl *TextCtrl;
  wxButton *SearchCtrl;
  wxRadioBox *ModeCtrl;
  wxBoxSizer *GridSizer;
  wxGrid *GridCtrl;
public:
    SearchSridDialog()
  {;
  }
  SearchSridDialog(MyFrame * parent);
  bool Create(MyFrame * parent);
  virtual ~ SearchSridDialog()
  {;
  }
  void CreateControls();
  void OnSearch(wxCommandEvent & event);
};

class DefaultCharsetDialog:public wxDialog
{
//
// a dialog for selecting DEFAULT CHARSET
//
private:
  MyFrame * MainFrame;
  wxString Charset;             // the default charset
  bool AskCharset;              // true / false
public:
    DefaultCharsetDialog()
  {;
  }
  DefaultCharsetDialog(MyFrame * parent, wxString & charset, bool ask);
  bool Create(MyFrame * parent, wxString & charset, bool ask);
  virtual ~ DefaultCharsetDialog()
  {;
  }
  void CreateControls();
  wxString & GetCharset()
  {
    return Charset;
  }
  bool IsSetAskCharset()
  {
    return AskCharset;
  }
  void OnOk(wxCommandEvent & event);
};

class ProjectCrsDialog:public wxDialog
{
//
// a dialog to handle Project CRS [Reference System]
//
private:
  MyFrame * MainFrame;
  SridInfo Info;
  wxString DescName;
  bool Dms;
  wxTextCtrl *DescCtrl;
  wxSpinCtrl *SridCtrl;
  wxTextCtrl *UnitCtrl;
  wxRadioBox *DmsCtrl;
public:
    ProjectCrsDialog()
  {;
  }
  ProjectCrsDialog(MyFrame * parent, SridInfo & info, wxString & desc);
  bool Create(MyFrame * parent, SridInfo & info, wxString & desc);
  virtual ~ ProjectCrsDialog()
  {;
  }
  void CreateControls();
  SridInfo & GetInfo()
  {
    return Info;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  void OnOk(wxCommandEvent & event);
  void OnSridChanged(wxCommandEvent & event);
  void OnDmsChanged(wxCommandEvent & event);
};

class VectorCrsDialog:public wxDialog
{
//
// a dialog to handle Vector Layer CRS [Reference System]
//
private:
  MyFrame * MainFrame;
  SridInfo ProjectCrs;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  int Srid;
  bool Reproject;
  wxTextCtrl *DescCtrl;
  wxCheckBox *ReprojectCtrl;
public:
    VectorCrsDialog()
  {;
  }
  VectorCrsDialog(MyFrame * parent, SridInfo & project_info, wxString & table,
                  wxString & geom, wxString & desc, int srid, bool reproject);
  bool Create(MyFrame * parent, SridInfo & project_info, wxString & table,
              wxString & geom, wxString & desc, int srid, bool reproject);
  virtual ~ VectorCrsDialog()
  {;
  }
  void CreateControls();
  bool IsReproject()
  {
    return Reproject;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  void OnOk(wxCommandEvent & event);
};

class RasterCrsDialog:public wxDialog
{
//
// a dialog to handle Raster Layer CRS [Reference System]
//
private:
  MyFrame * MainFrame;
  SridInfo ProjectCrs;
  wxString TableName;
  wxString DescName;
  int Srid;
public:
    RasterCrsDialog()
  {;
  }
  RasterCrsDialog(MyFrame * parent, SridInfo & project_info, wxString & table,
                  wxString & desc, int srid);
  bool Create(MyFrame * parent, SridInfo & project_info, wxString & table,
              wxString & desc, int srid);
  virtual ~ RasterCrsDialog()
  {;
  }
  void CreateControls();
};

class VisibilityRangeDialog:public wxDialog
{
//
// a dialog to handle the Visibility Range
//
private:
  MyFrame * MainFrame;
  bool RasterLayer;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  bool AlwaysVisible;
  int MinScale;
  int MaxScale;
  wxComboBox *LabelCtrl;
  wxRadioBox *VisibilityCtrl;
  wxSpinCtrl *MinScaleCtrl;
  wxSpinCtrl *MaxScaleCtrl;
  wxTextCtrl *DescCtrl;
public:
    VisibilityRangeDialog()
  {;
  }
  VisibilityRangeDialog(MyFrame * parent, int type, wxString & table,
                        wxString & geom, wxString & descName,
                        bool alwaysVisible, int minScale, int maxScale);
  bool Create(MyFrame * parent, int type, wxString & table, wxString & geom,
              wxString & descName, bool alwaysVisible, int minScale,
              int maxScale);
  virtual ~ VisibilityRangeDialog()
  {;
  }
  void CreateControls();
  bool IsAlwaysVisible()
  {
    return AlwaysVisible;
  }
  int GetMinScale()
  {
    return MinScale;
  }
  int GetMaxScale()
  {
    return MaxScale;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  void OnOk(wxCommandEvent & event);
  void OnVisibilityChanged(wxCommandEvent & event);
};

class LabelsDialog:public wxDialog
{
//
// a dialog to handle Labels
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxString LabelColumn;
  bool MapLabeling;
  wxColour TextColor;
  int PointSize;
  int FontWeight;
  int FontStyle;
  bool FontUnderlined;
  bool FontOutlined;
  bool Priority;
  wxString OrderByColumn;
  bool Descending;
  bool AlwaysVisible;
  int MinScale;
  int MaxScale;
  bool AntiOverlap;
  wxBitmap Bitmap;
  wxBitmap *OutlineBitmap;
  wxComboBox *LabelCtrl;
  wxComboBox *OrderByCtrl;
  wxCheckBox *MapLabelingCtrl;
  wxCheckBox *DescendingCtrl;
  wxCheckBox *PriorityCtrl;
  wxRadioBox *VisibilityCtrl;
  wxCheckBox *AntiOverlapCtrl;
  wxSpinCtrl *MinScaleCtrl;
  wxSpinCtrl *MaxScaleCtrl;
  wxSpinCtrl *PointSizeCtrl;
  wxRadioBox *FontWeightCtrl;
  wxRadioBox *FontStyleCtrl;
  wxCheckBox *FontUnderlineCtrl;
  wxCheckBox *FontOutlineCtrl;
  wxTextCtrl *DescCtrl;
  wxBitmapButton *TextColorCtrl;
  wxSlider *AlphaCtrl;
  wxStaticBitmap *ExampleCtrl;
  int NumColumns;
  wxString *ColumnList;
  void GetButtonBitmap(wxColour & color, wxBitmap & bitmap);
  void GetDisabledButtonBitmap(wxBitmap & bitmap);
  void TextOutline();
  void OutlinePixel(wxImage * img, int x, int y);
public:
    LabelsDialog()
  {;
  }
  LabelsDialog(MyFrame * parent, wxString & table, wxString & geom,
               wxString & descName, wxString & labelColumn, bool mapLabeling,
               wxColour & textColor, int pointSize, bool fontBold,
               bool fontItalic, bool fontUnderlined, bool fontOutlined,
               wxString & orderByColumn, bool descending, bool alwaysVisible,
               int minScale, int maxScale, bool antiOverlap);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxString & labelColumn, bool mapLabeling,
              wxColour & textColor, int pointSize, bool fontBold,
              bool fontItalic, bool fontUnderlined, bool fontOutlined,
              wxString & orderByColumn, bool descending, bool alwaysVisible,
              int minScale, int maxScale, bool antiOverlap);
  virtual ~ LabelsDialog();
  void CreateControls();
  void PaintBitmap();
  wxString & GetLabelColumn()
  {
    return LabelColumn;
  }
  bool IsMapLabelingEnabled()
  {
    return MapLabeling;
  }
  wxColour & GetTextColor()
  {
    return TextColor;
  }
  int GetPointSize()
  {
    return PointSize;
  }
  bool IsFontBold()
  {
    if (FontWeight == wxFONTWEIGHT_BOLD)
      return true;
    else
      return false;
  }
  bool IsFontItalic()
  {
    if (FontStyle == wxFONTSTYLE_ITALIC)
      return true;
    else
      return false;
  }
  bool IsFontUnderlined()
  {
    return FontUnderlined;
  }
  bool IsFontOutlined()
  {
    return FontOutlined;
  }
  wxString & GetOrderByColumn()
  {
    return OrderByColumn;
  }
  bool IsDescending()
  {
    return Descending;
  }
  bool IsAlwaysVisible()
  {
    return AlwaysVisible;
  }
  int GetMinScale()
  {
    return MinScale;
  }
  int GetMaxScale()
  {
    return MaxScale;
  }
  bool IsAntiOverlap()
  {
    return AntiOverlap;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  void OnOk(wxCommandEvent & event);
  void OnMapLabelingChanged(wxCommandEvent & event);
  void OnTextColorChanged(wxCommandEvent & event);
  void OnPointSizeChanged(wxCommandEvent & event);
  void OnFontWeightChanged(wxCommandEvent & event);
  void OnFontStyleChanged(wxCommandEvent & event);
  void OnFontUnderlineChanged(wxCommandEvent & event);
  void OnFontOutlineChanged(wxCommandEvent & event);
  void OnVisibilityChanged(wxCommandEvent & event);
  void OnPriorityChanged(wxCommandEvent & event);
  void OnAlphaChanged(wxCommandEvent & event);
  void OnAntiOverlapChanged(wxCommandEvent & event);
};

class PointGraphicsDialog:public wxDialog
{
//
// a dialog to show/set Point Graphics
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  int SymbolId;
  bool ColorSymbol;
  wxTextCtrl *DescCtrl;
  wxColour ForegroundColor;
  wxColour BackgroundColor;
  wxListCtrl *SymbolsCtrl;
  wxStaticBitmap *ExampleCtrl;
  wxBitmapButton *ForegroundCtrl;
  wxBitmapButton *BackgroundCtrl;
  MyImageList SymbolsList;
  wxBitmap Bitmap;
  MyBitmap *CurrentSymbol;
  wxColour CurrentForeground;
  wxColour CurrentBackground;
  void GetButtonBitmap(wxColour & color, wxBitmap & bitmap);
  void GetDisabledButtonBitmap(wxBitmap & bitmap);
public:
    PointGraphicsDialog()
  {;
  }
  PointGraphicsDialog(MyFrame * parent, wxString & table, wxString & geom,
                      wxString & descName, int symbolId, wxColour & foreground,
                      wxColour & background);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, int symbolId, wxColour & foreground,
              wxColour & background);
  virtual ~ PointGraphicsDialog()
  {;
  }
  void CreateControls();
  void PaintBitmap();
  int GetSymbolId()
  {
    return SymbolId;
  }
  bool IsColorSymbol()
  {
    return ColorSymbol;
  }
  wxColour & GetForegroundColor()
  {
    return ForegroundColor;
  }
  wxColour & GetBackgroundColor()
  {
    return BackgroundColor;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  void OnOk(wxCommandEvent & event);
  void OnSymbolSelected(wxCommandEvent & event);
  void OnForeground(wxCommandEvent & event);
  void OnBackground(wxCommandEvent & event);
};

class LineGraphicsDialog:public wxDialog
{
//
// a dialog to show/set Line Graphics
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxColour LineColor;
  int LineThickness;
  int LineStyle;
  wxTextCtrl *DescCtrl;
  wxBitmapButton *ColorCtrl;
  wxSlider *AlphaCtrl;
  wxSpinCtrl *ThicknessCtrl;
  wxListCtrl *StyleCtrl;
  wxStaticBitmap *ExampleCtrl;
  wxBitmap Bitmap;
  wxColour CurrentColor;
  int CurrentThickness;
  int CurrentStyle;
  void GetButtonBitmap(wxColour & color, wxBitmap & bitmap);
  void GetDisabledButtonBitmap(wxBitmap & bitmap);
public:
    LineGraphicsDialog()
  {;
  }
  LineGraphicsDialog(MyFrame * parent, wxString & table, wxString & geom,
                     wxString & descName, wxColour & color, int thickness,
                     int style);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxColour & color, int thickness, int style);
  virtual ~ LineGraphicsDialog()
  {;
  }
  void CreateControls();
  void PaintBitmap();
  int Find(int style_pos);
  int Find();
  wxImageList *BuildStyleList();
  wxColour & GetLineColor()
  {
    return LineColor;
  }
  int GetLineThickness()
  {
    return LineThickness;
  }
  int GetLineStyle()
  {
    return LineStyle;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  void OnOk(wxCommandEvent & event);
  void OnColor(wxCommandEvent & event);
  void OnAlphaChanged(wxCommandEvent & event);
  void OnThicknessChanged(wxCommandEvent & event);
  void OnStyleSelected(wxCommandEvent & event);
};

class PolygonGraphicsDialog:public wxDialog
{
//
// a dialog to show/set Polygon Graphics
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxColour BorderColor;
  int BorderThickness;
  int BorderStyle;
  bool DrawBorder;
  bool ToFill;
  bool SolidFilling;
  wxColour FillColor;
  int PatternId;
  bool ColorPattern;
  wxTextCtrl *DescCtrl;
  wxBitmapButton *BorderColorCtrl;
  wxSlider *BorderAlphaCtrl;
  wxSpinCtrl *ThicknessCtrl;
  wxListCtrl *StyleCtrl;
  wxRadioBox *BorderModeCtrl;
  wxRadioBox *FillingModeCtrl;
  wxBitmapButton *FillColorCtrl;
  wxSlider *FillAlphaCtrl;
  wxListCtrl *PatternsCtrl;
  wxStaticBitmap *ExampleCtrl;
  MyImageList PatternsList;
  wxBitmap Bitmap;
  bool CurrentDrawBorder;
  bool CurrentToFill;
  bool CurrentSolidFilling;
  wxColour CurrentBorderColor;
  int CurrentBorderThickness;
  int CurrentBorderStyle;
  wxColour CurrentFillColor;
  MyBitmap *CurrentPattern;
  void GetButtonBitmap(wxColour & color, wxBitmap & bitmap);
  void GetDisabledButtonBitmap(wxBitmap & bitmap);
public:
    PolygonGraphicsDialog()
  {;
  }
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxColour & fillColor);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxColour & borderColor, int thickness,
              int style, wxColour & fillColor);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxColour & border_color, int thickness,
              int style);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, int patternId, wxColour & fillColor);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxColour & borderColor, int thickness,
              int style, int patternId, wxColour & fillColor);
  virtual ~ PolygonGraphicsDialog()
  {;
  }
  void CreateControls();
  void PaintBitmap();
  int Find(int style_pos);
  int Find();
  wxImageList *BuildStyleList();
  wxColour & GetBorderColor()
  {
    return BorderColor;
  }
  int GetBorderThickness()
  {
    return BorderThickness;
  }
  int GetBorderStyle()
  {
    return BorderStyle;
  }
  bool DrawBorderOk()
  {
    return DrawBorder;
  }
  bool IsToFill()
  {
    return ToFill;
  }
  bool SolidFillingOk()
  {
    return SolidFilling;
  }
  wxColour & GetFillColor()
  {
    return FillColor;
  }
  int GetPatternId()
  {
    return PatternId;
  }
  bool IsColorPattern()
  {
    return ColorPattern;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  void OnOk(wxCommandEvent & event);
  void OnBorderModeChanged(wxCommandEvent & event);
  void OnFillingModeChanged(wxCommandEvent & event);
  void OnBorderColor(wxCommandEvent & event);
  void OnBorderAlphaChanged(wxCommandEvent & event);
  void OnBorderThicknessChanged(wxCommandEvent & event);
  void OnBorderStyleSelected(wxCommandEvent & event);
  void OnFillColor(wxCommandEvent & event);
  void OnFillAlphaChanged(wxCommandEvent & event);
  void OnPatternSelected(wxCommandEvent & event);
};

class LoadShpDialog:public wxDialog
{
//
// a dialog preparing a LOAD SHAPE
//
private:
  MyFrame * MainFrame;
  wxString Path;                // the SHP base path
  wxString Table;               // the table's name to be created
  wxString Column;              // the column's name for Geometry
  wxString Default;             // the default charset
  wxString Charset;             // the SHP charset
  int Srid;                     // the SRID
  bool Coerce2D;                // coercing to 2D [x,y]
  bool Compressed;              // compressed geometries
public:
    LoadShpDialog()
  {;
  }
  LoadShpDialog(MyFrame * parent, wxString & path, wxString & table, int srid,
                wxString & column, wxString & defCs);
  bool Create(MyFrame * parent, wxString & path, wxString & table, int srid,
              wxString & column, wxString & defCs);
  virtual ~ LoadShpDialog()
  {;
  }
  void CreateControls();
  wxString & GetTable()
  {
    return Table;
  }
  wxString & GetColumn()
  {
    return Column;
  }
  wxString & GetCharset()
  {
    return Charset;
  }
  int GetSrid()
  {
    return Srid;
  }
  bool ApplyCoertion2D()
  {
    return Coerce2D;
  }
  bool ApplyCompression()
  {
    return Compressed;
  }
  void OnOk(wxCommandEvent & event);
};

class DumpShpDialog:public wxDialog
{
//
// a dialog preparing a DUMP SHAPE
//
private:
  MyFrame * MainFrame;
  wxString Path;                // the SHP base path
  wxString Table;               // the table's name to be created
  wxString Column;              // the column's name for Geometry
  wxString Default;             // the default charset
  wxString Charset;             // the SHP charset
public:
    DumpShpDialog()
  {;
  }
  DumpShpDialog(MyFrame * parent, wxString & path, wxString & table,
                wxString & column, wxString & defCs);
  bool Create(MyFrame * parent, wxString & path, wxString & table,
              wxString & column, wxString & defCs);
  virtual ~ DumpShpDialog()
  {;
  }
  void CreateControls();
  wxString & GetCharset()
  {
    return Charset;
  }
  void OnOk(wxCommandEvent & event);
};

class NetworkDialog:public wxDialog
{
//
// a dialog preparing a BUILD NETWORK
//
private:
  MyFrame * MainFrame;
  wxString TableName;           // the table name
  wxString FromColumn;          // the NodeFrom column name
  wxString ToColumn;            // the NodeTo column name
  wxString GeomColumn;          // the Geometry column name
  bool GeomLength;              // Cost is Geometry Length
  wxString CostColumn;          // the Cost column name
  bool Bidirectional;           // Bidirectional arcs
  bool OneWays;                 // OneWays columns supported
  wxString OneWayToFrom;        // the OneWay To-From column
  wxString OneWayFromTo;        // the OneWay From-To column
  bool NameEnabled;             // Name column supported
  wxString NameColumn;          // the Name column name
  bool AStarSupported;          // A* algorithm supported
public:
    NetworkDialog()
  {;
  }
  NetworkDialog(MyFrame * parent, wxString & table, wxString & geom);
  bool Create(MyFrame * parent, wxString & table, wxString & geom);
  virtual ~ NetworkDialog()
  {;
  }
  void CreateControls();
  wxString & GetTableName()
  {
    return TableName;
  }
  wxString & GetFromColumn()
  {
    return FromColumn;
  }
  wxString & GetToColumn()
  {
    return ToColumn;
  }
  wxString & GetGeomColumn()
  {
    return GeomColumn;
  }
  wxString & GetNameColumn()
  {
    return NameColumn;
  }
  bool IsGeomLength()
  {
    return GeomLength;
  }
  wxString & GetCostColumn()
  {
    return CostColumn;
  }
  bool IsBidirectional()
  {
    return Bidirectional;
  }
  bool IsOneWays()
  {
    return OneWays;
  }
  wxString & GetOneWayFromTo()
  {
    return OneWayFromTo;
  }
  wxString & GetOneWayToFrom()
  {
    return OneWayToFrom;
  }
  bool IsNameEnabled()
  {
    return NameEnabled;
  }
  bool IsAStarSupported()
  {
    return AStarSupported;
  }
  void OnDirection(wxCommandEvent & event);
  void OnCost(wxCommandEvent & event);
  void OnOneWay(wxCommandEvent & event);
  void OnNameEnabled(wxCommandEvent & event);
  void OnOk(wxCommandEvent & event);
};

class RoutingSolutionDialog:public wxDialog
{
//
// a dialog displaying a Routing Solution
//
private:
  MyMapView * MapView;
  MyFrame *MainFrame;
  class RoutingSolution *Solution;
  bool HasNames;
  bool TextNodes;
  wxBoxSizer *TopSizer;
  wxBoxSizer *HeadSizer;
  wxBoxSizer *FootSizer;
  wxBoxSizer *GridSizer;
  wxGrid *GridCtrl;
  wxBitmapButton *ZoomArcBtn;
  wxBitmapButton *ZoomRouteBtn;
  wxBitmapButton *ZoomInBtn;
  wxBitmapButton *ZoomOutBtn;
  gaiaGeomCollPtr CurrentArc;
public:
    RoutingSolutionDialog()
  {;
  }
  RoutingSolutionDialog(MyMapView * map, MyFrame * parent,
                        RoutingSolution * solution, bool hasNames,
                        bool textNodes);
  bool Create(MyMapView * map, MyFrame * parent, RoutingSolution * solution,
              bool hasNames, bool textNodes);
  virtual ~ RoutingSolutionDialog()
  {
    UnsetCurrentArc();
  }
  void CreateControls();
  void SetCurrentArc(sqlite3_int64 id);
  void UnsetCurrentArc();
  void OnArcSelected(wxGridEvent & event);
  void OnZoomArc(wxCommandEvent & event);
  void OnZoomRoute(wxCommandEvent & event);
  void OnZoomIn(wxCommandEvent & WXUNUSED(event))
  {
    MapView->ZoomIn();
  }
  void OnZoomOut(wxCommandEvent & WXUNUSED(event))
  {
    MapView->ZoomOut();
  }
};

class SubClassObject:public wxTreeItemData
{
//
// a class to store TreeItemData - Layer SubClasses
//
private:
  MyDistinctValue * PtrDistinct;
  MyRangeValue *PtrRange;
  bool Unique;
  bool Text;
  wxString String;
  wxString TextValue;
  double NumValue;
  double MinValue;
  double MaxValue;
  int SymbolType;
  int Size;
  wxColour Color;
  bool RandomizeSkip;
  int IconIndex;
  wxString SymbolTypeAsConstant;
  wxString ColorAsRGBA;
public:
    SubClassObject(MyDistinctValue * ptr);
    SubClassObject(MyRangeValue * ptr);
    virtual ~ SubClassObject()
  {;
  }
  bool IsUnique()
  {
    return Unique;
  }
  bool IsText()
  {
    return Text;
  }
  wxString & GetValueAsString();
  wxString & GetTextValue()
  {
    return TextValue;
  }
  double GetNumValue()
  {
    return NumValue;
  }
  double GetMinValue()
  {
    return MinValue;
  }
  double GetMaxValue()
  {
    return MaxValue;
  }
  void SetSymbolType(int symbol)
  {
    SymbolType = symbol;
  }
  int GetSymbolType()
  {
    return SymbolType;
  }
  void SetSize(int size)
  {
    Size = size;
  }
  int GetSize()
  {
    return Size;
  }
  void SetColor(wxColour & color);
  wxColour & GetColor()
  {
    return Color;
  }
  void SetRandomizeSkip(bool skip);
  bool IsRandomizeSkip()
  {
    return RandomizeSkip;
  }
  int GetIconIndex()
  {
    return IconIndex;
  }
  void SetRange(double min, double max)
  {
    MinValue = min;
    MaxValue = max;
  }
  void UpdateSubClassIcon(wxImageList * imageList, int width, int height,
                          int geomType);

  void PrepareStaticValues();
  wxString & GetSymbolTypeAsConstant()
  {
    return SymbolTypeAsConstant;
  }
  wxString & GetColorAsRGBA()
  {
    return ColorAsRGBA;
  }
};

class SubClassesPreview:public wxTreeCtrl
{
//
// a tree-control used for Map Layers
//
private:
  class PointLayerClassifyDialog * PointParent;
  class LineLayerClassifyDialog *LineParent;
  class PolygonLayerClassifyDialog *PolygonParent;
  wxTreeItemId CurrentItem;     // the tree item holding the current context menu
  int GeometryType;
  double MinValue;
  double MaxValue;
public:
    SubClassesPreview()
  {;
  }
  SubClassesPreview(wxDialog * parent, wxWindowID id = wxID_ANY, int geomType =
                    LAYER_POINT, double min = 0.0, double max = 0.0);
  virtual ~ SubClassesPreview()
  {;
  }
  int GetGeometryType()
  {
    return GeometryType;
  }
  void SetRange(double min, double max)
  {
    MinValue = min;
    MaxValue = max;
  }
  void SetPointParent(PointLayerClassifyDialog * parent)
  {
    PointParent = parent;
  }
  void SetLineParent(LineLayerClassifyDialog * parent)
  {
    LineParent = parent;
  }
  void SetPolygonParent(PolygonLayerClassifyDialog * parent)
  {
    PolygonParent = parent;
  }
  double GetMinValue()
  {
    return MinValue;
  }
  double GetMaxValue()
  {
    return MaxValue;
  }
  void OnRightClick(wxTreeEvent & event);
  void OnCmdEditSymbol(wxCommandEvent & event);
  void OnCmdEditSize(wxCommandEvent & event);
  void OnCmdEditRange(wxCommandEvent & event);
  void OnCmdEditColor(wxCommandEvent & event);
};

class SubClassSymbolTypeDialog:public wxDialog
{
//
// a dialog to show/set SubClasses Symbol Type
//
private:
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxString ClassifyColumn;
  wxString ClassText;
  int SymbolType;
  wxRadioBox *SymbolTypeCtrl;
public:
    SubClassSymbolTypeDialog()
  {;
  }
  SubClassSymbolTypeDialog(wxDialog * parent, wxString & table, wxString & geom,
                           wxString & descName, wxString & column,
                           wxString classText, int symbol);
  bool Create(wxDialog * parent, wxString & table, wxString & geom,
              wxString & descName, wxString & column, wxString classText,
              int symbol);
  virtual ~ SubClassSymbolTypeDialog()
  {;
  }
  void CreateControls();
  int GetSymbolType()
  {
    return SymbolType;
  }
  void OnOk(wxCommandEvent & event);
};

class SubClassSizeDialog:public wxDialog
{
//
// a dialog to show/set SubClasses Size Value
//
private:
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxString ClassifyColumn;
  wxString ClassText;
  int Size;
  wxSpinCtrl *SizeCtrl;
public:
    SubClassSizeDialog()
  {;
  }
  SubClassSizeDialog(wxDialog * parent, wxString & table, wxString & geom,
                     wxString & descName, wxString & column, wxString classText,
                     int size);
  bool Create(wxDialog * parent, wxString & table, wxString & geom,
              wxString & descName, wxString & column, wxString classText,
              int size);
  virtual ~ SubClassSizeDialog()
  {;
  }
  void CreateControls();
  int GetSize()
  {
    return Size;
  }
  void OnOk(wxCommandEvent & event);
};

class SubClassRangeDialog:public wxDialog
{
//
// a dialog to show/set SubClasses Range Values
//
private:
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxString ClassifyColumn;
  wxString ClassText;
  int MinValue;
  int MaxValue;
  int LimitMin;
  int LimitMax;
  wxSpinCtrl *MinValueCtrl;
  wxSpinCtrl *MaxValueCtrl;
public:
    SubClassRangeDialog()
  {;
  }
  SubClassRangeDialog(wxDialog * parent, wxString & table, wxString & geom,
                      wxString & descName, wxString & column,
                      wxString classText, double min, double max,
                      double limitMin, double limitMax);
  bool Create(wxDialog * parent, wxString & table, wxString & geom,
              wxString & descName, wxString & column, wxString classText,
              double min, double max, double limitMin, double limitMax);
  virtual ~ SubClassRangeDialog()
  {;
  }
  void CreateControls();
  int GetMinValue()
  {
    return MinValue;
  }
  int GetMaxValue()
  {
    return MaxValue;
  }
  void OnOk(wxCommandEvent & event);
};

class SubClassColorDialog:public wxDialog
{
//
// a dialog to show/set SubClasses Color
//
private:
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxString ClassifyColumn;
  wxString ClassText;
  wxColour Color;
  bool RandomizeSkip;
  bool SkipEnabled;
  wxBitmapButton *ColorCtrl;
  wxCheckBox *RandomizeSkipCtrl;
  void GetButtonBitmap(wxColour & color, wxBitmap & bitmap);
public:
    SubClassColorDialog()
  {;
  }
  SubClassColorDialog(wxDialog * parent, wxString & table, wxString & geom,
                      wxString & descName, wxString & column,
                      wxString classText, wxColour & color, bool skip,
                      bool skipEnabled);
  bool Create(wxDialog * parent, wxString & table, wxString & geom,
              wxString & descName, wxString & column, wxString classText,
              wxColour & color, bool skip, bool skipEnabled);
  virtual ~ SubClassColorDialog()
  {;
  }
  void CreateControls();
  wxColour & GetColor()
  {
    return Color;
  }
  bool IsRandomizeSkip()
  {
    return RandomizeSkip;
  }
  void OnOk(wxCommandEvent & event);
  void OnColor(wxCommandEvent & event);
};

class PointLayerClassifyDialog:public wxDialog
{
//
// a dialog to show/set Point Layer SubClasses
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxString ClassifyColumn;
  MyDistinctValueList *DistinctList;
  MyRangeValueList *RangeList;
  bool UniqueValue;
  int NumClasses;
  double MinValue;
  double MaxValue;
  int SymbolType;
  int SymbolMinSize;
  int SymbolMaxSize;
  wxColour MinColor;
  wxColour MaxColor;
  int HueMode;
  int TransparencyMode;
  wxComboBox *ColumnCtrl;
  wxRadioBox *ModeCtrl;
  wxSpinCtrl *ClassesCtrl;
  wxRadioBox *SymbolTypeCtrl;
  wxSpinCtrl *MinSizeCtrl;
  wxSpinCtrl *MaxSizeCtrl;
  wxBitmapButton *MinColorCtrl;
  wxBitmapButton *MaxColorCtrl;
  SubClassesPreview *PreviewCtrl;
  wxTextCtrl *DisplayCtrl;
  wxButton *RebuildCtrl;
  wxButton *RandomizeCtrl;
  wxRadioBox *HueCtrl;
  wxRadioBox *TransparencyCtrl;
  int NumColumns;
  wxString *ColumnList;
  wxImageList *Images;

  void GetButtonBitmap(wxColour & color, wxBitmap & bitmap);
  void GetDisabledButtonBitmap(wxBitmap & bitmap);
  void PreviewBuild(SubClassesContainer * subClasses);
  void PreviewLoad();
  void PreviewUpdate();
public:
    PointLayerClassifyDialog()
  {;
  }
  PointLayerClassifyDialog(MyFrame * parent, wxString & table, wxString & geom,
                           wxString & descName, wxString & column, bool unique,
                           int numClasses, double minValue, double maxValue,
                           int symbolType, int minSize, int maxSize,
                           wxColour & minColor, wxColour & maxColor,
                           SubClassesContainer * subClasses);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxString & column, bool unique,
              int numClasses, double minValue, double maxValue, int symbolType,
              int minSize, int maxSize, wxColour & minColor,
              wxColour & maxColor, SubClassesContainer * subClasses);
  virtual ~ PointLayerClassifyDialog();
  void CreateControls();
  wxString & GetTableName()
  {
    return TableName;
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  wxString & GetClassifyColumn()
  {
    return ClassifyColumn;
  }
  bool IsUniqueValue()
  {
    return UniqueValue;
  }
  int GetNumClasses()
  {
    return NumClasses;
  }
  double GetMinValue()
  {
    return MinValue;
  }
  double GetMaxValue()
  {
    return MaxValue;
  }
  int GetSymbolType()
  {
    return SymbolType;
  }
  int GetSymbolMinSize()
  {
    return SymbolMinSize;
  }
  int GetSymbolMaxSize()
  {
    return SymbolMaxSize;
  }
  wxColour & GetMinColor()
  {
    return MinColor;
  }
  wxColour & GetMaxColor()
  {
    return MaxColor;
  }
  SubClassesPreview *GetSubClasses()
  {
    return PreviewCtrl;
  }
  void OnOk(wxCommandEvent & event);
  void OnColumnSelected(wxCommandEvent & event);
  void OnNumClassesChanged(wxCommandEvent & event);
  void OnMinSizeChanged(wxCommandEvent & event);
  void OnMaxSizeChanged(wxCommandEvent & event);
  void OnSymbolSelected(wxCommandEvent & event);
  void OnModeSelected(wxCommandEvent & event);
  void OnMinColor(wxCommandEvent & event);
  void OnMaxColor(wxCommandEvent & event);
  void OnPreviewRefresh(wxCommandEvent & event);
  void OnRandomizeColors(wxCommandEvent & event);
  void OnHueModeChanged(wxCommandEvent & event);
  void OnTransparencyModeChanged(wxCommandEvent & event);
};

class LineLayerClassifyDialog:public wxDialog
{
//
// a dialog to show/set Linestring Layer SubClasses
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxString ClassifyColumn;
  MyDistinctValueList *DistinctList;
  MyRangeValueList *RangeList;
  bool UniqueValue;
  int NumClasses;
  double MinValue;
  double MaxValue;
  int LineMinSize;
  int LineMaxSize;
  wxColour MinColor;
  wxColour MaxColor;
  int HueMode;
  int TransparencyMode;
  wxComboBox *ColumnCtrl;
  wxRadioBox *ModeCtrl;
  wxSpinCtrl *ClassesCtrl;
  wxSpinCtrl *MinSizeCtrl;
  wxSpinCtrl *MaxSizeCtrl;
  wxBitmapButton *MinColorCtrl;
  wxBitmapButton *MaxColorCtrl;
  SubClassesPreview *PreviewCtrl;
  wxTextCtrl *DisplayCtrl;
  wxButton *RebuildCtrl;
  wxButton *RandomizeCtrl;
  wxRadioBox *HueCtrl;
  wxRadioBox *TransparencyCtrl;
  int NumColumns;
  wxString *ColumnList;
  wxImageList *Images;

  void GetButtonBitmap(wxColour & color, wxBitmap & bitmap);
  void GetDisabledButtonBitmap(wxBitmap & bitmap);
  void PreviewBuild(SubClassesContainer * subClasses);
  void PreviewLoad();
  void PreviewUpdate();
public:
    LineLayerClassifyDialog()
  {;
  }
  LineLayerClassifyDialog(MyFrame * parent, wxString & table, wxString & geom,
                          wxString & descName, wxString & column, bool unique,
                          int numClasses, double minValue, double maxValue,
                          int minSize, int maxSize, wxColour & minColor,
                          wxColour & maxColor,
                          SubClassesContainer * subClasses);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxString & column, bool unique,
              int numClasses, double minValue, double maxValue, int minSize,
              int maxSize, wxColour & minColor, wxColour & maxColor,
              SubClassesContainer * subClasses);
  virtual ~ LineLayerClassifyDialog();
  void CreateControls();
  wxString & GetTableName()
  {
    return TableName;
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  wxString & GetClassifyColumn()
  {
    return ClassifyColumn;
  }
  bool IsUniqueValue()
  {
    return UniqueValue;
  }
  int GetNumClasses()
  {
    return NumClasses;
  }
  double GetMinValue()
  {
    return MinValue;
  }
  double GetMaxValue()
  {
    return MaxValue;
  }
  int GetLineMinSize()
  {
    return LineMinSize;
  }
  int GetLineMaxSize()
  {
    return LineMaxSize;
  }
  wxColour & GetMinColor()
  {
    return MinColor;
  }
  wxColour & GetMaxColor()
  {
    return MaxColor;
  }
  SubClassesPreview *GetSubClasses()
  {
    return PreviewCtrl;
  }
  void OnOk(wxCommandEvent & event);
  void OnColumnSelected(wxCommandEvent & event);
  void OnNumClassesChanged(wxCommandEvent & event);
  void OnMinSizeChanged(wxCommandEvent & event);
  void OnMaxSizeChanged(wxCommandEvent & event);
  void OnModeSelected(wxCommandEvent & event);
  void OnMinColor(wxCommandEvent & event);
  void OnMaxColor(wxCommandEvent & event);
  void OnPreviewRefresh(wxCommandEvent & event);
  void OnRandomizeColors(wxCommandEvent & event);
  void OnHueModeChanged(wxCommandEvent & event);
  void OnTransparencyModeChanged(wxCommandEvent & event);
};

class PolygonLayerClassifyDialog:public wxDialog
{
//
// a dialog to show/set Polygon Layer SubClasses
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  wxString ClassifyColumn;
  MyDistinctValueList *DistinctList;
  MyRangeValueList *RangeList;
  bool UniqueValue;
  int NumClasses;
  double MinValue;
  double MaxValue;
  wxColour MinColor;
  wxColour MaxColor;
  int HueMode;
  int TransparencyMode;
  wxComboBox *ColumnCtrl;
  wxRadioBox *ModeCtrl;
  wxSpinCtrl *ClassesCtrl;
  wxBitmapButton *MinColorCtrl;
  wxBitmapButton *MaxColorCtrl;
  SubClassesPreview *PreviewCtrl;
  wxTextCtrl *DisplayCtrl;
  wxButton *RebuildCtrl;
  wxButton *RandomizeCtrl;
  wxRadioBox *HueCtrl;
  wxRadioBox *TransparencyCtrl;
  int NumColumns;
  wxString *ColumnList;
  wxImageList *Images;

  void GetButtonBitmap(wxColour & color, wxBitmap & bitmap);
  void GetDisabledButtonBitmap(wxBitmap & bitmap);
  void PreviewBuild(SubClassesContainer * subClasses);
  void PreviewLoad();
  void PreviewUpdate();
public:
    PolygonLayerClassifyDialog()
  {;
  }
  PolygonLayerClassifyDialog(MyFrame * parent, wxString & table,
                             wxString & geom, wxString & descName,
                             wxString & column, bool unique, int numClasses,
                             double minValue, double maxValue,
                             wxColour & minColor, wxColour & maxColor,
                             SubClassesContainer * subClasses);
  bool Create(MyFrame * parent, wxString & table, wxString & geom,
              wxString & descName, wxString & column, bool unique,
              int numClasses, double minValue, double maxValue,
              wxColour & minColor, wxColour & maxColor,
              SubClassesContainer * subClasses);
  virtual ~ PolygonLayerClassifyDialog();
  void CreateControls();
  wxString & GetTableName()
  {
    return TableName;
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  wxString & GetClassifyColumn()
  {
    return ClassifyColumn;
  }
  bool IsUniqueValue()
  {
    return UniqueValue;
  }
  int GetNumClasses()
  {
    return NumClasses;
  }
  double GetMinValue()
  {
    return MinValue;
  }
  double GetMaxValue()
  {
    return MaxValue;
  }
  wxColour & GetMinColor()
  {
    return MinColor;
  }
  wxColour & GetMaxColor()
  {
    return MaxColor;
  }
  SubClassesPreview *GetSubClasses()
  {
    return PreviewCtrl;
  }
  void OnOk(wxCommandEvent & event);
  void OnColumnSelected(wxCommandEvent & event);
  void OnNumClassesChanged(wxCommandEvent & event);
  void OnModeSelected(wxCommandEvent & event);
  void OnMinColor(wxCommandEvent & event);
  void OnMaxColor(wxCommandEvent & event);
  void OnPreviewRefresh(wxCommandEvent & event);
  void OnRandomizeColors(wxCommandEvent & event);
  void OnHueModeChanged(wxCommandEvent & event);
  void OnTransparencyModeChanged(wxCommandEvent & event);
};

class TableColumn
{
//
// a class to store a Table Column [used by CREATE TABLE and TABLE LAYOUT]
//
private:
  wxString Column;
  wxString DescName;
  int Type;
  bool PrimaryKey;
  bool NotNull;
  int Length;
  int Decimals;
  bool Deleted;
  wxString Defs;
  bool Exists;
  bool ToBeDeleted;
  bool ToBeInserted;
  bool ToBeUpdated;
  wxString ColumnTypeAsConstant;
  int IntegerCount;
  int FloatCount;
  int TextCount;
  int BlobCount;
  int NullCount;
  TableColumn *Next;
public:
    TableColumn(wxString & col, wxString & desc, int type, bool pk,
                bool notNull, int len, int decs);
    TableColumn(wxString & col, bool notNull, bool pk);
   ~TableColumn()
  {;
  }
  void Set(wxString & col, wxString & desc, int type, bool pk, bool notNull,
           int len, int decs);
  wxString & GetColumn()
  {
    return Column;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  int GetType()
  {
    return Type;
  }
  bool IsPrimaryKey()
  {
    return PrimaryKey;
  }
  bool IsNotNull()
  {
    return NotNull;
  }
  int GetLength()
  {
    return Length;
  }
  int GetDecimals()
  {
    return Decimals;
  }
  void Delete()
  {
    Deleted = true;
  }
  bool IsDeleted()
  {
    return Deleted;
  }
  void SetExisting()
  {
    Exists = true;
    ToBeDeleted = true;
  }
  bool IsExisting()
  {
    return Exists;
  }
  void Confirm(bool notNull, bool pk)
  {
    NotNull = notNull;
    PrimaryKey = pk;
    ToBeDeleted = false;
  }
  bool IsToBeDeleted()
  {
    return ToBeDeleted;
  }
  bool IsToBeInserted()
  {
    return ToBeInserted;
  }
  void SetUpdate()
  {
    ToBeUpdated = true;
  }
  bool IsToBeUpdated()
  {
    return ToBeUpdated;
  }
  void Reset();
  wxString & GetColumnDefs();
  wxString & GetColumnTypeAsConstant();
  void AddTypeCount(char *type, int count);
  void GuessType();
  void SetNext(TableColumn * next)
  {
    Next = next;
  }
  TableColumn *GetNext()
  {
    return Next;
  }
};

class TableLayout
{
//
// a class to store the Table Columns list [used by CREATE TABLE and TABLE LAYOUT]
//
private:
  wxString TableName;
  wxString DescName;
  wxString GeometryColumn;
  int GeometryType;
  int Srid;
  TableColumn *First;
  TableColumn *Last;
public:
    TableLayout();
   ~TableLayout();
  void Set(wxString & name, wxString & descName, wxString & geomColumn,
           int type, int srid);
    wxString & GetTableName()
  {
    return TableName;
  }
  wxString & GetDescName()
  {
    return DescName;
  }
  wxString & GetGeometryColumn()
  {
    return GeometryColumn;
  }
  int GetGeometryType()
  {
    return GeometryType;
  }
  int GetSrid()
  {
    return Srid;
  }
  TableColumn *GetFirst()
  {
    return First;
  }
  TableColumn *GetLast()
  {
    return Last;
  }
  bool IsDuplicate(wxString & column);
  bool IsDuplicate(TableColumn * p, wxString & column);
  void Add(wxString & col, wxString & desc, int type, bool pk, bool notNull,
           int len, int decs);
  void AddExisting(wxString & col, wxString & desc, int type, bool pk,
                   bool notNull, int len, int decs);
  void Add(wxString & col, bool notNull, bool pk);
  TableColumn *Find(int index);
  int Find(wxString & column);
  int GetCount();
};

class CreateTableDialog:public wxDialog
{
//
// a dialog to create a new spatial table
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString DescName;
  wxString GeometryColumn;
  wxString GeometryType;
  int Srid;
  wxTextCtrl *TableCtrl;
  wxTextCtrl *DescCtrl;
  wxTextCtrl *GeomCtrl;
  wxSpinCtrl *SridCtrl;
  wxRadioBox *GeoTypeCtrl;
  wxListBox *ListCtrl;
  wxTextCtrl *ColNameCtrl;
  wxTextCtrl *ColDescCtrl;
  wxRadioBox *ColTypeCtrl;
  wxRadioBox *ColNullCtrl;
  wxSpinCtrl *ColLenCtrl;
  wxSpinCtrl *ColDecCtrl;
  wxButton *ClearBtn;
  wxButton *AddBtn;
  wxButton *DeleteBtn;
  TableLayout Table;
  TableColumn *CurrentColumn;
public:
    CreateTableDialog()
  {;
  }
  CreateTableDialog(MyFrame * parent, int srid);
  bool Create(MyFrame * parent, int srid);
  virtual ~ CreateTableDialog()
  {;
  }
  void CreateControls();
  bool DoCreateTable();
  void OnTypeSelected(wxCommandEvent & event);
  void OnColumnSelected(wxCommandEvent & event);
  void OnClear(wxCommandEvent & event);
  void OnAdd(wxCommandEvent & event);
  void OnDelete(wxCommandEvent & event);
  void OnOk(wxCommandEvent & event);
};

class TableLayoutDialog:public wxDialog
{
//
// a dialog to create a new spatial table
//
private:
  MyFrame * MainFrame;
  wxString TableName;
  wxString DescName;
  wxString ModDescName;
  wxString GeometryColumn;
  wxString GeometryType;
  SridInfo Info;
  wxTextCtrl *DescCtrl;
  wxListBox *ListCtrl;
  wxTextCtrl *ColNameCtrl;
  wxTextCtrl *ColDescCtrl;
  wxRadioBox *ColTypeCtrl;
  wxRadioBox *ColNullCtrl;
  wxSpinCtrl *ColLenCtrl;
  wxSpinCtrl *ColDecCtrl;
  wxButton *ClearBtn;
  wxButton *AddBtn;
  wxButton *DeleteBtn;
  TableLayout Table;
  TableColumn *CurrentColumn;
public:
    TableLayoutDialog()
  {;
  }
  TableLayoutDialog(MyFrame * parent, wxString & table, wxString & geomColumn);
  bool Create(MyFrame * parent, wxString & table, wxString & geomColumn);
  virtual ~ TableLayoutDialog()
  {;
  }
  void CreateControls();
  void LoadDefs();
  bool DoUpdateTable();
  void OnTypeSelected(wxCommandEvent & event);
  void OnColumnSelected(wxCommandEvent & event);
  void OnClear(wxCommandEvent & event);
  void OnAdd(wxCommandEvent & event);
  void OnDelete(wxCommandEvent & event);
  void OnOk(wxCommandEvent & event);
};

class GridCellImage:public wxGridCellRenderer
{
//
// a wxGridCellRenderer used for grid cells containing an image / thumbnail
//
private:
  wxImage Image;
  wxSize ImageSize;
  bool Error;
  bool Changed;
public:
    GridCellImage(int maxHeight);
    GridCellImage(unsigned char *blob, int blobSize, int maxHeight);
    GridCellImage(const GridCellImage * org);
    virtual ~ GridCellImage()
  {;
  }
  void SetImage(unsigned char *blob, int blobSize);
  void NullImage();
  void SetError(bool mode)
  {
    Error = mode;
  }
  void SetChanged(bool mode)
  {
    Changed = mode;
  }
  void Draw(wxGrid & grid, wxGridCellAttr & attr, wxDC & dc,
            const wxRect & rect, int row, int col, bool isSelected);
  wxSize GetBestSize(wxGrid & WXUNUSED(grid), wxGridCellAttr & WXUNUSED(attr),
                     wxDC & WXUNUSED(dc), int WXUNUSED(row), int WXUNUSED(col));
  wxGridCellRenderer *Clone() const;
};

class IdentifyDialog:public wxDialog
{
//
// a dialog used by IDENTIFY
//
private:
  MyMapView * Map;
  MyFrame *MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  bool UseAlias;
  IdentifyEntitiesList *Entities;
  bool ReadOnly;
  wxGrid *ListCtrl;
  wxBoxSizer *GridSizer;
  wxGrid *EntityCtrl;
  wxButton *DeleteBtn;
  wxButton *SaveBtn;
  wxButton *RestoreBtn;
  wxCheckBox *AliasCtrl;
  int CurrentEntityRow;
  int CurrentEvtRow;
  int CurrentEvtColumn;
  MyValues *TableBackupValues;
  MyValues *TableValues;
  QueryTable ColumnList;
  IdentifyEntity *CurrentEntity;
  wxColour OkColor;
  wxColour ErrorColor;
public:
    IdentifyDialog()
  {;
  }
  bool Create(MyMapView * map, MyFrame * parent, MapLayer * layer,
              IdentifyEntitiesList * list);
  virtual ~ IdentifyDialog();
  void CreateControls();
  void TableMetadata();
  void ShowEntity();
  int GetNextValidEntity();
  bool CheckChanged();
  void OnAliasSelected(wxCommandEvent & event);
  void OnEntitySelected(wxGridEvent & event);
  void OnRightClick(wxGridEvent & event);
  void OnEntityRightClick(wxGridEvent & event);
  void OnCellValueChanged(wxGridEvent & event);
  void OnCmdClearSelection(wxCommandEvent & event);
  void OnCmdSelectAll(wxCommandEvent & event);
  void OnCmdCopy(wxCommandEvent & event);
  void OnCmdCopyImage(wxCommandEvent & event);
  void OnCmdBlobIn(wxCommandEvent & event);
  void OnCmdBlobOut(wxCommandEvent & event);
  void OnCmdBlobNull(wxCommandEvent & event);
  void OnCmdDelete(wxCommandEvent & event);
  void OnCmdSave(wxCommandEvent & event);
  void OnCmdRestore(wxCommandEvent & event);
};

class InsertEntityDialog:public wxDialog
{
//
// a dialog used by INSERT ENTITY
//
private:
  MyMapView * Map;
  MyFrame *MainFrame;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  bool UseAlias;
  wxBoxSizer *GridSizer;
  wxGrid *EntityCtrl;
  wxCheckBox *AliasCtrl;
  MyValues *TableValues;
  QueryTable ColumnList;
  wxColour OkColor;
  wxColour ErrorColor;
  int CurrentRow;
  int CurrentCol;
public:
    InsertEntityDialog()
  {;
  }
  bool Create(MyMapView * map, MyFrame * parent, LayerObject * layer);
  virtual ~ InsertEntityDialog();
  void CreateControls();
  void TableMetadata();
  void PrepareGrid();
  void OnAliasSelected(wxCommandEvent & event);
  void OnRightClick(wxGridEvent & event);
  void OnCellValueChanged(wxGridEvent & event);
  void OnCmdBlobIn(wxCommandEvent & event);
  void OnCmdBlobNull(wxCommandEvent & event);
  void OnCmdAbort(wxCommandEvent & event);
  void OnCmdInsert(wxCommandEvent & event);
};

class MyRowGroup
{
//
// a class to store a GroupSelection of table rows
//
private:
  int *RowArray;
  int *RelocationArray;
  int MaxIndex;
  int NextIndex;
  bool ApplyRelocation;
public:
    MyRowGroup();
   ~MyRowGroup();
  void Reset();
  void Create(int items);
  void Insert(int row_id);
  bool IsSelected(int row_id);
  void RelocationReset();
  void Relocate(int oldPos, int newPos);
  int GetBaseIndex(int newPos);
  bool IsRelocated()
  {
    return ApplyRelocation;
  }
};

class TableDialog:public wxDialog
{
//
// a dialog used by SHOW TABLE
//
private:
  MyMapView * Map;
  MyFrame *MainFrame;
  MapLayer *Layer;
  wxString TableName;
  wxString GeometryColumn;
  wxString DescName;
  int GeometryType;
  bool UseAlias;
  wxGrid *TableCtrl;
  wxBoxSizer *GridSizer;
  wxBitmapButton *BtnRsFirst;
  wxBitmapButton *BtnRsLast;
  wxBitmapButton *BtnRsNext;
  wxBitmapButton *BtnRsPrevious;
  wxBitmapButton *BtnRsRefresh;
  wxStaticText *RsCurrentBlock;
  wxListBox *ColsCtrl;
  wxComboBox *WhereColCtrl;
  wxRadioBox *WhereModeCtrl;
  wxTextCtrl *WhereValCtrl;
  wxComboBox *Order1Ctrl;
  wxComboBox *Order2Ctrl;
  wxComboBox *Order3Ctrl;
  wxCheckBox *Desc1Ctrl;
  wxCheckBox *Desc2Ctrl;
  wxCheckBox *Desc3Ctrl;
  wxButton *QueryBtn;
  wxBitmapButton *ZoomBtn;
  wxBitmapButton *SaveBtn;
  wxBitmapButton *TopBtn;
  wxBitmapButton *RemoveSelBtn;
  wxCheckBox *AliasCtrl;
  wxBoxSizer *ButtonSizer;
  int RsBlock;
  int RsBeginRow;
  int RsEndRow;
  int RsMaxRow;
  int CurrentEvtRow;
  int CurrentEvtColumn;
  MyValues *TableValues;
  MyValues *TableBackupValues;
  bool ReadOnly;
  QueryTable ColumnList;
  wxString SqlQuery;
  wxColour OkColor;
  wxColour ErrorColor;
  wxColour GroupColor;
  MyRowGroup GroupSelection;
public:
    TableDialog()
  {;
  }
  bool Create(MyFrame * parent, MapLayer * layer, bool readOnly);
  virtual ~ TableDialog();
  void CreateControls();
  void TableMetadata();
  bool IsFunction(wxString & name);
  void PrepareSqlQuery();
  void DoQueryTable(int start);
  void GroupReplace(int row, int col, int dataType, int decimals);
  void GroupHighlight(int row, bool mode);
  void RelocateRow(int newPos);
  bool SelectionExists();
  bool PendingChanges();
  bool IgnorePendingChanges();
  void UpdateButtonStatus();
  void HexBlobValue(unsigned char *blob, int size, wxString & hex);
  void OnAliasSelected(wxCommandEvent & event);
  void OnRsFirst(wxCommandEvent & event);
  void OnRsLast(wxCommandEvent & event);
  void OnRsNext(wxCommandEvent & event);
  void OnRsPrevious(wxCommandEvent & event);
  void OnRefresh(wxCommandEvent & event);
  void OnQuery(wxCommandEvent & event);
  void OnZoomIn(wxCommandEvent & event);
  void OnWhereModeChanged(wxCommandEvent & event);
  void OnRightClick(wxGridEvent & event);
  void OnCellSelection(wxGridEvent & event);
  void OnCellRangeSelection(wxGridRangeSelectEvent & event);
  void OnLabelSelection(wxGridEvent & event);
  void OnCellChanged(wxGridEvent & event);
  void OnCmdClearSelection(wxCommandEvent & event);
  void OnCmdSelectAll(wxCommandEvent & event);
  void OnCmdSelectRow(wxCommandEvent & event);
  void OnCmdSelectColumn(wxCommandEvent & event);
  void OnCmdCopy(wxCommandEvent & event);
  void OnCmdDelete(wxCommandEvent & event);
  void OnCmdBlobIn(wxCommandEvent & event);
  void OnCmdBlobOut(wxCommandEvent & event);
  void OnCmdBlobNull(wxCommandEvent & event);
  void OnSave(wxCommandEvent & event);
  void OnTopSelection(wxCommandEvent & event);
  void OnRemoveSelection(wxCommandEvent & event);
  void OnCancel(wxCommandEvent & event);
};

class AutoSaveDialog:public wxDialog
{
//
// a dialog to manage AutoSave
//
private:
  MyFrame * MainFrame;
  wxString Path;                // the path to save
  int Seconds;                  // interval 
  wxRadioBox *IntervalCtrl;
  wxTextCtrl *PathCtrl;
public:
    AutoSaveDialog()
  {;
  }
  AutoSaveDialog(MyFrame * parent, wxString & path, int secs);
  bool Create(MyFrame * parent, wxString & path, int secs);
  virtual ~ AutoSaveDialog()
  {;
  }
  void CreateControls();
  int GetSeconds()
  {
    return Seconds;
  }
  void OnOk(wxCommandEvent & event);
  wxString & GetPath()
  {
    return Path;
  }
  void OnIntervalChanged(wxCommandEvent & event);
  void OnChangePath(wxCommandEvent & event);
};

class CreateInternalTableDialog:public wxDialog
{
//
// a dialog used to create internal tables [if required]
//
private:
  MyFrame * MainFrame;
  wxString Message;             // the message to be shown
  wxRadioBox *OptionCtrl;
  bool Yes;
  bool YesToAll;
public:
    CreateInternalTableDialog()
  {;
  }
  CreateInternalTableDialog(MyFrame * parent, wxString & msg);
  bool Create();
  virtual ~ CreateInternalTableDialog()
  {;
  }
  void CreateControls();
  void OnOk(wxCommandEvent & event);
  bool IsAnswerYes()
  {
    return Yes;
  }
  bool IsAnswerYesToAll()
  {
    return YesToAll;
  }
};

class OutputMapDialog:public wxDialog
{
//
// a dialog used to set Map Output options
//
private:
  MyFrame * MainFrame;
  double MinX;
  double MinY;
  double MaxX;
  double MaxY;
  double ExtentX;
  double ExtentY;
  double PixelRatio;
  int Width;
  int Height;
  int MaxWidth;
  int MaxHeight;
  bool Svg;
  bool Pdf;
  bool CopyToClipboard;
  bool Jpeg;
  bool Png;
  bool Tiff;
  bool WorldFile;
  bool PdfLandscape;
  bool PdfA3;
  int PdfDpi;
  wxColour BackgroundColor;
  wxRadioBox *FormatCtrl;
  wxRadioBox *ModeCtrl;
  wxSpinCtrl *WidthCtrl;
  wxSpinCtrl *HeightCtrl;
  wxTextCtrl *PixelCtrl;
  wxRadioBox *WorldFileCtrl;
  wxBitmapButton *BackgroundColorCtrl;
  wxRadioBox *PdfLandscapeCtrl;
  wxRadioBox *PdfPageSizeCtrl;
  wxRadioBox *PdfDpiCtrl;
  bool IgnoreWidthEvent;
  bool IgnoreHeightEvent;
  bool IgnorePixelEvent;
  wxTextAttr DefaultPixelStyle;
public:
    OutputMapDialog()
  {;
  }
  OutputMapDialog(MyFrame * parent, double minX, double minY, double maxX,
                  double maxY);
  bool Create(MyFrame * parent, double minX, double minY, double maxX,
              double maxY);
  virtual ~ OutputMapDialog()
  {;
  }
  void CreateControls();
  bool IsSvg()
  {
    return Svg;
  }
  bool IsPdf()
  {
    return Pdf;
  }
  bool IsCopyToClipboard()
  {
    return CopyToClipboard;
  }
  bool IsJpeg()
  {
    return Jpeg;
  }
  bool IsPng()
  {
    return Png;
  }
  bool IsTiff()
  {
    return Tiff;
  }
  bool IsWorldFile()
  {
    return WorldFile;
  }
  bool IsPdfA3()
  {
    return PdfA3;
  }
  bool IsPdfLandscape()
  {
    return PdfLandscape;
  }
  int GetPdfDpi()
  {
    return PdfDpi;
  }
  int GetWidth()
  {
    return Width;
  }
  int GetHeight()
  {
    return Height;
  }
  void GetButtonBitmap(wxBitmap & bitmap);
  void GetDisabledButtonBitmap(wxBitmap & bitmap);
  wxColour & GetBackgroundColor()
  {
    return BackgroundColor;
  }
  void OnFormatChanged(wxCommandEvent & event);
  void OnModeChanged(wxCommandEvent & event);
  void OnWorldFileChanged(wxCommandEvent & event);
  void OnWidthChanged(wxCommandEvent & event);
  void OnHeightChanged(wxCommandEvent & event);
  void OnPixelChanged(wxCommandEvent & event);
  void OnBackgroundColor(wxCommandEvent & event);
  void OnPdfA3Changed(wxCommandEvent & event);
  void OnPdfLandscapeChanged(wxCommandEvent & event);
  void OnPdfDpiChanged(wxCommandEvent & event);
  void OnOk(wxCommandEvent & event);
};

class SvgEntity
{
//
// a class to store an SVG entity
//
private:
  unsigned char *Svg;
  SvgEntity *Next;
public:
    SvgEntity(const unsigned char *svg);
   ~SvgEntity();
  const unsigned char *GetSvg()
  {
    return Svg;
  }
  void SetNext(SvgEntity * next)
  {
    Next = next;
  }
  SvgEntity *GetNext()
  {
    return Next;
  }
};

class SvgClass
{
//
// a class to store a sub-class for an SVG layer
//
private:
  MapSubClass * SubClass;
  SvgEntity *First;
  SvgEntity *Last;
  SvgClass *Next;
public:
    SvgClass(MapSubClass * subClass);
   ~SvgClass();
  MapSubClass *GetSubClass()
  {
    return SubClass;
  }
  void Add(const unsigned char *svg);
  SvgEntity *GetFirst()
  {
    return First;
  }
  void SetNext(SvgClass * next)
  {
    Next = next;
  }
  SvgClass *GetNext()
  {
    return Next;
  }
};

class SvgClasses
{
//
// a class to store sub-classes for an SVG layer
//
private:
  int GeometryType;
  double PixelRatio;
  SvgClass *First;
  SvgClass *Last;
public:
    SvgClasses();
   ~SvgClasses();
  void Set(int geomType, double pixelRatio)
  {
    GeometryType = geomType;
    PixelRatio = pixelRatio;
  }
  void Add(MapSubClass * subClass, const unsigned char *svg);
  void Output(FILE * svg);
};

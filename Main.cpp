/*
/ Main.cpp
/ the main core of spatialite-gis  - the SpatiaLite minimalistic GIS
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

#include "wx/menu.h"
#include "wx/filename.h"
#include "wx/aboutdlg.h"
#include "wx/config.h"

#include <float.h>

#include <hpdf_types.h>

#include <spatialite.h>
#include <spatialite/gaiaaux.h>
#include <proj_api.h>
#include <geos_c.h>

//
// ICONs in XPM format [universally portable]
//
#include "icons/icon.xpm"
#include "icons/icon_info.xpm"
#include "icons/create_new.xpm"
#include "icons/connect.xpm"
#include "icons/disconnect.xpm"
#include "icons/memdb_load.xpm"
#include "icons/memdb_new.xpm"
#include "icons/memdb_clock.xpm"
#include "icons/memdb_save.xpm"
#include "icons/vacuum.xpm"
#include "icons/map_frame.xpm"
#include "icons/output_map.xpm"
#include "icons/crs.xpm"
#include "icons/loadshp.xpm"
#include "icons/table_add.xpm"
#include "icons/srids.xpm"
#include "icons/charset.xpm"
#include "icons/line_meter.xpm"
#include "icons/polygon_meter.xpm"
#include "icons/pencil.xpm"
#include "icons/pencil_add.xpm"
#include "icons/pencil_delete.xpm"
#include "icons/pencil_go.xpm"
#include "icons/cut_red.xpm"
#include "icons/cut_blue.xpm"
#include "icons/asterisk.xpm"
#include "icons/about.xpm"
#include "icons/exit.xpm"

IMPLEMENT_APP(MyApp)
     bool MyApp::OnInit()
{
//
// main APP implementation
//
  wxString path;
  if (argc > 1)
    path = argv[1];
  MyFrame *frame =
    new
    MyFrame(wxT("spatialite-gis      [a minimalistic GIS based on SpatiaLite]"),
            wxPoint(0, 0), wxSize(800, 600));
  frame->Show(true);
  SetTopWindow(frame);
  frame->LoadConfig(path);
  return true;
}

MyFrame::MyFrame(const wxString & title, const wxPoint & pos, const wxSize & size):
wxFrame((wxFrame *) NULL, -1, title, pos,
        size)
{
//
// main GUI frame constructor
//
  srand(time(NULL));            // initializing the Random generator

  CurrentDrawMode = DRAW_MODE_NONE;
  MemoryDatabase = false;
  AutoSaveInterval = 0;
  LastTotalChanges = 0;
  TimerAutoSave = NULL;
  ActiveLayer = NULL;
  NetParms = NULL;
  OkCurrentEntity = false;
  CurrentEntityPrimaryKey = -1;
  CurrentEntityGeometry = NULL;

//
// initializing CHARSET lists
//
  CharsetsLen = 79;
  Charsets = new wxString[CharsetsLen];
  CharsetsNames = new wxString[CharsetsLen];
  *(CharsetsNames + 0) = wxT("ARMSCII-8    Armenian");
  *(CharsetsNames + 1) = wxT("ASCII        US-ASCII");
  *(CharsetsNames + 2) = wxT("BIG5         Chinese/Traditional");
  *(CharsetsNames + 3) = wxT("BIG5-HKSCS   Chinese/Hong Kong");
  *(CharsetsNames + 4) = wxT("BIG5-HKSCS:1999");
  *(CharsetsNames + 5) = wxT("BIG5-HKSCS:2001");
  *(CharsetsNames + 6) = wxT("CP850        DOS/OEM Western Europe");
  *(CharsetsNames + 7) = wxT("CP862        DOS/OEM Hebrew");
  *(CharsetsNames + 8) = wxT("CP866        DOS/OEM Cyrillic");
  *(CharsetsNames + 9) = wxT("CP874        DOS/OEM Thai");
  *(CharsetsNames + 10) = wxT("CP932        DOS/OEM Japanese");
  *(CharsetsNames + 11) = wxT("CP936        DOS/OEM Chinese");
  *(CharsetsNames + 12) = wxT("CP949        DOS/OEM Korean");
  *(CharsetsNames + 13) = wxT("CP950        DOS/OEM Chinese/Big5");
  *(CharsetsNames + 14) = wxT("CP1133       Laotian");
  *(CharsetsNames + 15) = wxT("CP1250       Windows Central Europe");
  *(CharsetsNames + 16) = wxT("CP1251       Windows Cyrillic");
  *(CharsetsNames + 17) = wxT("CP1252       Windows Latin 1");
  *(CharsetsNames + 18) = wxT("CP1253       Windows Greek");
  *(CharsetsNames + 19) = wxT("CP1254       Windows Turkish");
  *(CharsetsNames + 20) = wxT("CP1255       Windows Hebrew");
  *(CharsetsNames + 21) = wxT("CP1256       Windows Arabic");
  *(CharsetsNames + 22) = wxT("CP1257       Windows Baltic");
  *(CharsetsNames + 23) = wxT("CP1258       Windows Vietnamese");
  *(CharsetsNames + 24) = wxT("EUC-CN       Chinese");
  *(CharsetsNames + 25) = wxT("EUC-JP       Japanese");
  *(CharsetsNames + 26) = wxT("EUC-KR       Korean");
  *(CharsetsNames + 27) = wxT("EUC-TW       Taiwan");
  *(CharsetsNames + 28) = wxT("GB18030      Chinese/National Standard");
  *(CharsetsNames + 29) = wxT("GBK          Chinese/Simplified");
  *(CharsetsNames + 30) = wxT("Georgian-Academy");
  *(CharsetsNames + 31) = wxT("Georgian-PS");
  *(CharsetsNames + 32) = wxT("HZ           Chinese");
  *(CharsetsNames + 33) = wxT("ISO-2022-CN  Chinese");
  *(CharsetsNames + 34) = wxT("ISO-2022-CN-EXT");
  *(CharsetsNames + 35) = wxT("ISO-2022-JP  Japanese");
  *(CharsetsNames + 36) = wxT("ISO-2022-JP-1");
  *(CharsetsNames + 37) = wxT("ISO-2022-JP-2");
  *(CharsetsNames + 38) = wxT("ISO-2022-KR  Korean");
  *(CharsetsNames + 39) = wxT("ISO-8859-1   Latin-1 Western European");
  *(CharsetsNames + 40) = wxT("ISO-8859-2   Latin-2 Central European");
  *(CharsetsNames + 41) = wxT("ISO-8859-3   Latin-3 South European");
  *(CharsetsNames + 42) = wxT("ISO-8859-4   Latin-4 North European");
  *(CharsetsNames + 43) = wxT("ISO-8859-5   Latin/Cyrillic");
  *(CharsetsNames + 44) = wxT("ISO-8859-6   Latin/Arabic");
  *(CharsetsNames + 45) = wxT("ISO-8859-7   Latin/Greek");
  *(CharsetsNames + 46) = wxT("ISO-8859-8   Latin/Hebrew");
  *(CharsetsNames + 47) = wxT("ISO-8859-9   Latin-5 Turkish");
  *(CharsetsNames + 48) = wxT("ISO-8859-10  Latin-6 Nordic");
  *(CharsetsNames + 49) = wxT("ISO-8859-11  Latin/Thai");
  *(CharsetsNames + 50) = wxT("ISO-8859-13  Latin-7 Baltic Rim");
  *(CharsetsNames + 51) = wxT("ISO-8859-14  Latin-8 Celtic");
  *(CharsetsNames + 52) = wxT("ISO-8859-15  Latin-9");
  *(CharsetsNames + 53) = wxT("ISO-8859-16  Latin-10 South-Eastern European");
  *(CharsetsNames + 54) = wxT("JOHAB        Korean");
  *(CharsetsNames + 55) = wxT("KOI8-R       Russian");
  *(CharsetsNames + 56) = wxT("KOI8-U       Ukrainian");
  *(CharsetsNames + 57) = wxT("KOI8-RU      Belarusian");
  *(CharsetsNames + 58) = wxT("KOI8-T       Tajik");
  *(CharsetsNames + 59) = wxT("MacArabic    MAC Arabic");
  *(CharsetsNames + 60) = wxT("MacCentralEurope");
  *(CharsetsNames + 61) = wxT("MacCroatian  MAC Croatian");
  *(CharsetsNames + 62) = wxT("MacCyrillic  MAC Cyrillic");
  *(CharsetsNames + 63) = wxT("MacGreek     MAC Greek");
  *(CharsetsNames + 64) = wxT("MacHebrew    MAC Hebrew");
  *(CharsetsNames + 65) = wxT("MacIceland   MAC Iceland");
  *(CharsetsNames + 66) = wxT("Macintosh");
  *(CharsetsNames + 67) = wxT("MacRoman     MAC European/Western languages");
  *(CharsetsNames + 68) = wxT("MacRomania   MAC Romania");
  *(CharsetsNames + 69) = wxT("MacThai      MAC Thai");
  *(CharsetsNames + 70) = wxT("MacTurkish   MAC Turkish");
  *(CharsetsNames + 71) = wxT("MacUkraine   MAC Ukraine");
  *(CharsetsNames + 72) = wxT("MuleLao-1    Laotian");
  *(CharsetsNames + 73) = wxT("PT154        Kazakh");
  *(CharsetsNames + 74) = wxT("RK1048       Kazakh");
  *(CharsetsNames + 75) = wxT("SHIFT_JIS    Japanese");
  *(CharsetsNames + 76) = wxT("TCVN         Vietnamese");
  *(CharsetsNames + 77) = wxT("TIS-620      Thai");
  *(CharsetsNames + 77) = wxT("UTF-8        UNICODE/Universal");
  *(CharsetsNames + 78) = wxT("VISCII       Vietnamese");
  *(Charsets + 0) = wxT("ARMSCII-8");
  *(Charsets + 1) = wxT("ASCII");
  *(Charsets + 2) = wxT("BIG5");
  *(Charsets + 3) = wxT("BIG5-HKSCS");
  *(Charsets + 4) = wxT("BIG5-HKSCS:1999");
  *(Charsets + 5) = wxT("BIG5-HKSCS:2001");
  *(Charsets + 6) = wxT("CP850");
  *(Charsets + 7) = wxT("CP862");
  *(Charsets + 8) = wxT("CP866");
  *(Charsets + 9) = wxT("CP874");
  *(Charsets + 10) = wxT("CP932");
  *(Charsets + 11) = wxT("CP936");
  *(Charsets + 12) = wxT("CP949");
  *(Charsets + 13) = wxT("CP950");
  *(Charsets + 14) = wxT("CP1133");
  *(Charsets + 15) = wxT("CP1250");
  *(Charsets + 16) = wxT("CP1251");
  *(Charsets + 17) = wxT("CP1252");
  *(Charsets + 18) = wxT("CP1253");
  *(Charsets + 19) = wxT("CP1254");
  *(Charsets + 20) = wxT("CP1255");
  *(Charsets + 21) = wxT("CP1256");
  *(Charsets + 22) = wxT("CP1257");
  *(Charsets + 23) = wxT("CP1258");
  *(Charsets + 24) = wxT("EUC-CN");
  *(Charsets + 25) = wxT("EUC-JP");
  *(Charsets + 26) = wxT("EUC-KR");
  *(Charsets + 27) = wxT("EUC-TW");
  *(Charsets + 28) = wxT("GB18030");
  *(Charsets + 29) = wxT("GBK");
  *(Charsets + 30) = wxT("Georgian-Academy");
  *(Charsets + 31) = wxT("Georgian-PS");
  *(Charsets + 32) = wxT("HZ");
  *(Charsets + 33) = wxT("ISO-2022-CN");
  *(Charsets + 34) = wxT("ISO-2022-CN-EXT");
  *(Charsets + 35) = wxT("ISO-2022-JP");
  *(Charsets + 36) = wxT("ISO-2022-JP-1");
  *(Charsets + 37) = wxT("ISO-2022-JP-2");
  *(Charsets + 38) = wxT("ISO-2022-KR");
  *(Charsets + 39) = wxT("ISO-8859-1");
  *(Charsets + 40) = wxT("ISO-8859-2");
  *(Charsets + 41) = wxT("ISO-8859-3");
  *(Charsets + 42) = wxT("ISO-8859-4");
  *(Charsets + 43) = wxT("ISO-8859-5");
  *(Charsets + 44) = wxT("ISO-8859-6");
  *(Charsets + 45) = wxT("ISO-8859-7");
  *(Charsets + 46) = wxT("ISO-8859-8");
  *(Charsets + 47) = wxT("ISO-8859-9");
  *(Charsets + 48) = wxT("ISO-8859-10");
  *(Charsets + 49) = wxT("ISO-8859-11");
  *(Charsets + 50) = wxT("ISO-8859-13");
  *(Charsets + 51) = wxT("ISO-8859-14");
  *(Charsets + 52) = wxT("ISO-8859-15");
  *(Charsets + 53) = wxT("ISO-8859-16");
  *(Charsets + 54) = wxT("JOHAB");
  *(Charsets + 55) = wxT("KOI8-R");
  *(Charsets + 56) = wxT("KOI8-U");
  *(Charsets + 57) = wxT("KOI8-RU");
  *(Charsets + 58) = wxT("KOI8-T");
  *(Charsets + 59) = wxT("MacArabic");
  *(Charsets + 60) = wxT("MacCentralEurope");
  *(Charsets + 61) = wxT("MacCroatian");
  *(Charsets + 62) = wxT("MacCyrillic");
  *(Charsets + 63) = wxT("MacGreek");
  *(Charsets + 64) = wxT("MacHebrew");
  *(Charsets + 65) = wxT("MacIceland");
  *(Charsets + 66) = wxT("Macintosh");
  *(Charsets + 67) = wxT("MacRoman");
  *(Charsets + 68) = wxT("MacRomania");
  *(Charsets + 69) = wxT("MacThai");
  *(Charsets + 70) = wxT("MacTurkish");
  *(Charsets + 71) = wxT("MacUkraine");
  *(Charsets + 72) = wxT("MuleLao-1");
  *(Charsets + 73) = wxT("PT154");
  *(Charsets + 74) = wxT("RK1048");
  *(Charsets + 75) = wxT("SHIFT_JIS");
  *(Charsets + 76) = wxT("TCVN");
  *(Charsets + 77) = wxT("TIS-620");
  *(Charsets + 77) = wxT("UTF-8");
  *(Charsets + 78) = wxT("VISCII");
  LocaleCharset = wxString::FromUTF8(gaiaGetLocaleCharset());
  DefaultCharset = LocaleCharset;
  AskCharset = false;

  spatialite_init(0);           // loading the SpatiaLite extension

  ::wxInitAllImageHandlers();

  LastSrid = -9999;
  LastGeographic = false;
  SqliteHandle = NULL;
  ProjectName = wxT("Anonymous");
  SqlitePath = wxT("");
  LastDirectory = wxT("");
  BtnConnect = new wxBitmap(connect_xpm);
  BtnCreateNew = new wxBitmap(create_new_xpm);
  BtnDisconnect = new wxBitmap(disconnect_xpm);
  BtnMemDbLoad = new wxBitmap(memdb_load_xpm);
  BtnMemDbNew = new wxBitmap(memdb_new_xpm);
  BtnMemDbClock = new wxBitmap(memdb_clock_xpm);
  BtnMemDbSave = new wxBitmap(memdb_save_xpm);
  BtnVacuum = new wxBitmap(vacuum_xpm);
  BtnMapFrameSel = new wxBitmap(map_frame_xpm);
  BtnOutputMap = new wxBitmap(output_map_xpm);
  BtnCrs = new wxBitmap(crs_xpm);
  BtnLoadShp = new wxBitmap(loadshp_xpm);
  BtnTableAdd = new wxBitmap(table_add_xpm);
  BtnSrids = new wxBitmap(srids_xpm);
  BtnCharset = new wxBitmap(charset_xpm);
  BtnLineMeter = new wxBitmap(line_meter_xpm);
  BtnPolygonMeter = new wxBitmap(polygon_meter_xpm);
  BtnPencil = new wxBitmap(pencil_xpm);
  BtnPencilAdd = new wxBitmap(pencil_add_xpm);
  BtnPencilDelete = new wxBitmap(pencil_delete_xpm);
  BtnPencilGo = new wxBitmap(pencil_go_xpm);
  BtnDeleteSubGeom = new wxBitmap(cut_red_xpm);
  BtnSplitLine = new wxBitmap(cut_blue_xpm);
  BtnSelectMultiGeom = new wxBitmap(asterisk_xpm);
  BtnAbout = new wxBitmap(about_xpm);
  BtnExit = new wxBitmap(exit_xpm);

//
// setting up the application icon
//      
  wxIcon MyIcon(icon_xpm);
  SetIcon(MyIcon);

//
// setting up panes
//
  LayerTree = new MyLayerTree(this);
  MapView = new MyMapView(this);
  Manager.SetManagedWindow(this);
  wxAuiPaneInfo paneView = wxAuiPaneInfo().Centre();
  paneView.Name(wxT("map_view"));
  paneView.CaptionVisible(false);
  paneView.Floatable(true);
  paneView.Dockable(true);
  paneView.Movable(true);
  paneView.Gripper(false);
  paneView.CloseButton(false);
  Manager.AddPane(MapView, paneView);
  wxAuiPaneInfo paneTree = wxAuiPaneInfo().Left();
  paneTree.Name(wxT("tree_view"));
  paneTree.CaptionVisible(false);
  paneTree.Floatable(true);
  paneTree.Dockable(true);
  paneTree.Movable(true);
  paneTree.Gripper(true);
  paneTree.CloseButton(false);
  paneTree.BestSize(wxSize(200, 480));
  Manager.AddPane(LayerTree, paneTree, wxPoint(0, 10));
  Manager.Update();
  Centre();

//
// setting up the status bar
//
  wxStatusBar *statusBar = new wxStatusBar(this);
  statusBar->SetFieldsCount(4);
  int fldWidth[3];
  fldWidth[0] = -2;
  fldWidth[1] = -1;
  fldWidth[2] = -3;
  statusBar->SetStatusWidths(3, fldWidth);
  SetStatusBar(statusBar);

//
// setting up the menu bar
//
  wxMenu *menuFile = new wxMenu;
  wxMenuItem *menuItem;
  menuItem =
    new wxMenuItem(menuFile, ID_Connect,
                   wxT("&Connecting an existing SQLite DB"));
  menuItem->SetBitmap(*BtnConnect);
  menuFile->Append(menuItem);
  menuItem =
    new wxMenuItem(menuFile, ID_CreateNew,
                   wxT("Creating a &New (empty) SQLite DB"));
  menuItem->SetBitmap(*BtnCreateNew);
  menuFile->Append(menuItem);
  wxMenu *memoryMenu = new wxMenu();
  menuItem =
    new wxMenuItem(memoryMenu, ID_MemoryDbLoad,
                   wxT("&Loading an existing DB into the MEMORY-DB"));
  menuItem->SetBitmap(*BtnMemDbLoad);
  memoryMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(memoryMenu, ID_MemoryDbNew,
                   wxT("Creating a &New (empty) MEMORY-DB"));
  menuItem->SetBitmap(*BtnMemDbNew);
  memoryMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(memoryMenu, ID_MemoryDbClock,
                   wxT("&AutoSaving the current MEMORY-DB"));
  menuItem->SetBitmap(*BtnMemDbClock);
  memoryMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(memoryMenu, ID_MemoryDbSave,
                   wxT("&Saving the current MEMORY-DB"));
  menuItem->SetBitmap(*BtnMemDbSave);
  memoryMenu->Append(menuItem);
  menuFile->AppendSubMenu(memoryMenu, wxT("&MEMORY-DB"));
  menuItem =
    new wxMenuItem(menuFile, ID_Disconnect,
                   wxT("&Disconnecting current SQLite DB"));
  menuItem->SetBitmap(*BtnDisconnect);
  menuFile->Append(menuItem);
  menuItem =
    new wxMenuItem(menuFile, ID_Vacuum,
                   wxT("&Optimizing current SQLite DB [VACUUM]"));
  menuItem->SetBitmap(*BtnVacuum);
  menuFile->Append(menuItem);
  menuFile->AppendSeparator();
  wxMenu *subMenu = new wxMenu();
  menuItem =
    new wxMenuItem(subMenu, ID_MapFrameSel, wxT("&Map Frame [selection]"),
                   wxT(""), wxITEM_CHECK);
  menuItem->SetBitmap(*BtnMapFrameSel);
  subMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(subMenu, ID_MapFrameAll, wxT("&Map Frame [full extent]"),
                   wxT(""));
  subMenu->Append(menuItem);
  menuItem = new wxMenuItem(subMenu, ID_OutputMap, wxT("&Output Map"));
  menuItem->SetBitmap(*BtnOutputMap);
  subMenu->Append(menuItem);
  menuFile->AppendSubMenu(subMenu, wxT("&Output Map"));
  menuFile->AppendSeparator();
  menuItem =
    new wxMenuItem(menuFile, ID_Crs,
                   wxT("&Project CRS [Coordinate Reference System]"));
  menuItem->SetBitmap(*BtnCrs);
  menuFile->Append(menuItem);
  menuFile->AppendSeparator();
  menuItem = new wxMenuItem(menuFile, ID_LoadShp, wxT("&Load Shapefile"));
  menuItem->SetBitmap(*BtnLoadShp);
  menuFile->Append(menuItem);
  menuItem =
    new wxMenuItem(menuFile, ID_TableAdd, wxT("&Create Spatial Table"));
  menuItem->SetBitmap(*BtnTableAdd);
  menuFile->Append(menuItem);
  menuFile->AppendSeparator();
  menuItem = new wxMenuItem(menuFile, ID_Srids, wxT("&Search SRID by name"));
  menuItem->SetBitmap(*BtnSrids);
  menuFile->Append(menuItem);
  menuItem =
    new wxMenuItem(menuFile, ID_Charset, wxT("&Default Output Charset"));
  menuItem->SetBitmap(*BtnCharset);
  menuFile->Append(menuItem);
  menuFile->AppendSeparator();
  subMenu = new wxMenu();
  menuItem =
    new wxMenuItem(subMenu, ID_LineMeter, wxT("Measure &Length"), wxT(""),
                   wxITEM_CHECK);
  menuItem->SetBitmap(*BtnLineMeter);
  subMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(subMenu, ID_PolygonMeter, wxT("Measure &Area"), wxT(""),
                   wxITEM_CHECK);
  menuItem->SetBitmap(*BtnPolygonMeter);
  subMenu->Append(menuItem);
  subMenu->AppendSeparator();
  menuItem =
    new wxMenuItem(subMenu, ID_Draw, wxT("&Draw"), wxT(""), wxITEM_CHECK);
  menuItem->SetBitmap(*BtnPencil);
  subMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(subMenu, ID_DrawInterpolate, wxT("&Interpolate Vertex"),
                   wxT(""), wxITEM_CHECK);
  menuItem->SetBitmap(*BtnPencilAdd);
  subMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(subMenu, ID_DrawDelete, wxT("&Delete Vertex"), wxT(""),
                   wxITEM_CHECK);
  menuItem->SetBitmap(*BtnPencilDelete);
  subMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(subMenu, ID_DrawMove, wxT("&Move Vertex"), wxT(""),
                   wxITEM_CHECK);
  menuItem->SetBitmap(*BtnPencilGo);
  subMenu->Append(menuItem);
  subMenu->AppendSeparator();
  menuItem =
    new wxMenuItem(subMenu, ID_DrawDeleteSubGeom, wxT("Delete &SubGeometry"),
                   wxT(""), wxITEM_CHECK);
  menuItem->SetBitmap(*BtnDeleteSubGeom);
  subMenu->Append(menuItem);
  menuItem =
    new wxMenuItem(subMenu, ID_DrawSplitLine, wxT("&Split Line"), wxT(""),
                   wxITEM_CHECK);
  menuItem->SetBitmap(*BtnSplitLine);
  subMenu->Append(menuItem);
  subMenu->AppendSeparator();
  menuItem =
    new wxMenuItem(subMenu, ID_DrawSelectMultiGeom,
                   wxT("Select Complex &Geometry"), wxT(""), wxITEM_CHECK);
  menuItem->SetBitmap(*BtnSelectMultiGeom);
  subMenu->Append(menuItem);
  menuFile->AppendSubMenu(subMenu, wxT("Current &draw mode"));
  menuFile->AppendSeparator();
  menuItem = new wxMenuItem(menuFile, wxID_ABOUT, wxT("&About ..."));
  menuItem->SetBitmap(*BtnAbout);
  menuFile->Append(menuItem);
  menuFile->AppendSeparator();
  menuItem = new wxMenuItem(menuFile, wxID_EXIT, wxT("&Quit"));
  menuItem->SetBitmap(*BtnExit);
  menuFile->Append(menuItem);
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, wxT("&Files"));
  SetMenuBar(menuBar);

//
// setting up menu initial state 
//
  menuBar->Enable(ID_Disconnect, false);
  menuBar->Enable(ID_MemoryDbClock, false);
  menuBar->Enable(ID_MemoryDbSave, false);
  menuBar->Enable(ID_Vacuum, false);
  menuBar->Enable(ID_MapFrameSel, false);
  menuBar->Enable(ID_MapFrameAll, false);
  menuBar->Enable(ID_OutputMap, false);
  menuBar->Enable(ID_Crs, false);
  menuBar->Enable(ID_LoadShp, false);
  menuBar->Enable(ID_TableAdd, false);
  menuBar->Enable(ID_Srids, false);
  menuBar->Enable(ID_LineMeter, false);
  menuBar->Enable(ID_PolygonMeter, false);
  menuBar->Enable(ID_Draw, false);
  menuBar->Enable(ID_DrawInterpolate, false);
  menuBar->Enable(ID_DrawDelete, false);
  menuBar->Enable(ID_DrawMove, false);
  menuBar->Enable(ID_DrawDeleteSubGeom, false);
  menuBar->Enable(ID_DrawSplitLine, false);
  menuBar->Enable(ID_DrawSelectMultiGeom, false);

//
// setting up the toolbar
//      
  wxToolBar *toolBar = CreateToolBar();
  toolBar->AddTool(ID_Connect, wxT("Connecting an existing SQLite DB"),
                   *BtnConnect, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Connecting an existing SQLite DB"));
  toolBar->AddTool(ID_CreateNew, wxT("Creating a &New (empty) SQLite DB"),
                   *BtnCreateNew, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Creating a &New (empty) SQLite DB"));
  toolBar->AddTool(ID_MemoryDbLoad,
                   wxT("Loading an existing DB into the MEMORY-DB"),
                   *BtnMemDbLoad, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Loading an existing DB into the MEMORY-DB"));
  toolBar->AddTool(ID_MemoryDbNew, wxT("Creating a New (empty) MEMORY-DB"),
                   *BtnMemDbNew, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Creating a New (empty) MEMORY-DB"));
  toolBar->AddTool(ID_MemoryDbClock, wxT("AutoSaving the current MEMORY-DB"),
                   *BtnMemDbClock, wxNullBitmap, wxITEM_NORMAL,
                   wxT("AutoSaving the current MEMORY-DB"));
  toolBar->AddTool(ID_MemoryDbSave, wxT("Saving the current MEMORY-DB"),
                   *BtnMemDbSave, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Saving the current MEMORY-DB"));
  toolBar->AddTool(ID_Disconnect, wxT("Disconnecting current SQLite DB"),
                   *BtnDisconnect, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Disconnecting current SQLite DB"));
  toolBar->AddTool(ID_Vacuum, wxT("Optimizing current SQLite DB [VACUUM]"),
                   *BtnVacuum, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Optimizing current SQLite DB [VACUUM]"));
  toolBar->AddSeparator();
  toolBar->AddTool(ID_MapFrameSel, wxT("Map Frame [selection]"),
                   *BtnMapFrameSel, wxNullBitmap, wxITEM_CHECK,
                   wxT("Map Frame [selection]"));
  toolBar->AddTool(ID_OutputMap, wxT("Output Map"),
                   *BtnOutputMap, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Output Map"));
  toolBar->AddSeparator();
  toolBar->AddTool(ID_Crs, wxT("Project CRS [Coordinate Reference System]"),
                   *BtnCrs, wxNullBitmap, wxITEM_NORMAL,
                   wxT("Project CRS [Coordinate Reference System]"));
  toolBar->AddSeparator();
  toolBar->AddTool(ID_LoadShp, wxT("Load Shapefile"), *BtnLoadShp, wxNullBitmap,
                   wxITEM_NORMAL, wxT("Load Shapefile"));
  toolBar->AddTool(ID_TableAdd, wxT("Create Spatial Table"), *BtnTableAdd,
                   wxNullBitmap, wxITEM_NORMAL, wxT("Create Spatial Table"));
  toolBar->AddSeparator();
  toolBar->AddTool(ID_Srids, wxT("Search SRID by name"), *BtnSrids,
                   wxNullBitmap, wxITEM_NORMAL, wxT("Search SRID by name"));
  toolBar->AddTool(ID_Charset, wxT("Default Output Charset"), *BtnCharset,
                   wxNullBitmap, wxITEM_NORMAL, wxT("Default Output Charset"));
  toolBar->AddSeparator();
  toolBar->AddTool(ID_LineMeter, wxT("Measure Length"), *BtnLineMeter,
                   wxNullBitmap, wxITEM_CHECK, wxT("Measure Length"));
  toolBar->AddTool(ID_PolygonMeter, wxT("Measure Area"), *BtnPolygonMeter,
                   wxNullBitmap, wxITEM_CHECK, wxT("Measure Area"));
  toolBar->AddSeparator();
  toolBar->AddTool(ID_Draw, wxT("Draw"), *BtnPencil,
                   wxNullBitmap, wxITEM_CHECK, wxT("Draw"));
  toolBar->AddTool(ID_DrawInterpolate, wxT("Interpolate Vertex"), *BtnPencilAdd,
                   wxNullBitmap, wxITEM_CHECK, wxT("Interpolate Vertex"));
  toolBar->AddTool(ID_DrawDelete, wxT("Delete Vertex"), *BtnPencilDelete,
                   wxNullBitmap, wxITEM_CHECK, wxT("Delete Vertex"));
  toolBar->AddTool(ID_DrawMove, wxT("Move Vertex"), *BtnPencilGo,
                   wxNullBitmap, wxITEM_CHECK, wxT("Move Vertx"));
  toolBar->AddSeparator();
  toolBar->AddTool(ID_DrawDeleteSubGeom, wxT("Delete SubGeometry"),
                   *BtnDeleteSubGeom, wxNullBitmap, wxITEM_CHECK,
                   wxT("Delete SubGeometry"));
  toolBar->AddTool(ID_DrawSplitLine, wxT("Split Line"), *BtnSplitLine,
                   wxNullBitmap, wxITEM_CHECK, wxT("Split Line"));
  toolBar->AddSeparator();
  toolBar->AddTool(ID_DrawSelectMultiGeom, wxT("Select Complex Geometry"),
                   *BtnSelectMultiGeom, wxNullBitmap, wxITEM_CHECK,
                   wxT("Select Complex Geometry"));
  toolBar->AddSeparator();
  toolBar->AddTool(wxID_ABOUT, wxT("About ..."), *BtnAbout, wxNullBitmap,
                   wxITEM_NORMAL, wxT("About ..."));
  toolBar->AddSeparator();
  toolBar->AddTool(wxID_EXIT, wxT("Quit"), *BtnExit, wxNullBitmap,
                   wxITEM_NORMAL, wxT("Quit"));
  toolBar->Realize();
  SetToolBar(toolBar);

//
// setting up the toolbar initial state
//
  toolBar->EnableTool(ID_Disconnect, false);
  toolBar->EnableTool(ID_MemoryDbClock, false);
  toolBar->EnableTool(ID_MemoryDbSave, false);
  toolBar->EnableTool(ID_Vacuum, false);
  toolBar->EnableTool(ID_MapFrameSel, false);
  toolBar->EnableTool(ID_OutputMap, false);
  toolBar->EnableTool(ID_Crs, false);
  toolBar->EnableTool(ID_LoadShp, false);
  toolBar->EnableTool(ID_TableAdd, false);
  toolBar->EnableTool(ID_Srids, false);
  toolBar->EnableTool(ID_LineMeter, false);
  toolBar->EnableTool(ID_PolygonMeter, false);
  toolBar->EnableTool(ID_Draw, false);
  toolBar->EnableTool(ID_DrawInterpolate, false);
  toolBar->EnableTool(ID_DrawDelete, false);
  toolBar->EnableTool(ID_DrawMove, false);
  toolBar->EnableTool(ID_DrawDeleteSubGeom, false);
  toolBar->EnableTool(ID_DrawSplitLine, false);
  toolBar->EnableTool(ID_DrawSelectMultiGeom, false);

//
// setting up event handlers for menu and toolbar
//
  Connect(ID_Connect, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnConnect);
  Connect(ID_CreateNew, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnCreateNew);
  Connect(ID_Disconnect, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnDisconnect);
  Connect(ID_MemoryDbLoad, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnMemoryDbLoad);
  Connect(ID_MemoryDbNew, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnMemoryDbNew);
  Connect(ID_MemoryDbClock, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnMemoryDbClock);
  Connect(ID_MemoryDbSave, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnMemoryDbSave);
  Connect(ID_Vacuum, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnVacuum);
  Connect(ID_MapFrameSel, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnMapFrameSelection);
  Connect(ID_MapFrameAll, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnMapFrameFullExtent);
  Connect(ID_OutputMap, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnOutputMap);
  Connect(ID_Crs, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnProjectCrs);
  Connect(ID_LoadShp, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnLoadShp);
  Connect(ID_TableAdd, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnTableAdd);
  Connect(ID_Srids, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnSrids);
  Connect(ID_Charset, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnCharset);
  Connect(ID_LineMeter, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnLineMeter);
  Connect(ID_PolygonMeter, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnPolygonMeter);
  Connect(ID_Draw, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnDraw);
  Connect(ID_DrawInterpolate, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnDrawInterpolate);
  Connect(ID_DrawDelete, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnDrawDelete);
  Connect(ID_DrawMove, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnDrawMove);
  Connect(ID_DrawDeleteSubGeom, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnDrawDeleteSubGeom);
  Connect(ID_DrawSplitLine, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnDrawSplitLine);
  Connect(ID_DrawSelectMultiGeom, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnDrawSelectMultiGeom);
  Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnAbout);
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyFrame::OnQuit);
//
// setting up a Timer event handler for AutoSave
//
  Connect(ID_AUTO_SAVE_TIMER, wxEVT_TIMER,
          wxTimerEventHandler(MyFrame::OnTimerAutoSave), NULL, this);
}

MyFrame::~MyFrame()
{
//
// main GUI frame destructor
//
  LastDitchMemoryDbSave();
  if (TimerAutoSave)
    {
      TimerAutoSave->Stop();
      delete TimerAutoSave;
    }
  ConfigLayout = Manager.SavePerspective();
  GetPosition(&ConfigPaneX, &ConfigPaneY);
  GetSize(&ConfigPaneWidth, &ConfigPaneHeight);
  SaveConfig();
  Manager.UnInit();
  if (SqliteHandle)
    sqlite3_close(SqliteHandle);
  if (BtnConnect != NULL)
    delete BtnConnect;
  if (BtnCreateNew != NULL)
    delete BtnCreateNew;
  if (BtnDisconnect != NULL)
    delete BtnDisconnect;
  if (BtnMemDbLoad != NULL)
    delete BtnMemDbLoad;
  if (BtnMemDbNew != NULL)
    delete BtnMemDbNew;
  if (BtnMemDbClock != NULL)
    delete BtnMemDbClock;
  if (BtnMemDbSave != NULL)
    delete BtnMemDbSave;
  if (BtnVacuum != NULL)
    delete BtnVacuum;
  if (BtnMapFrameSel != NULL)
    delete BtnMapFrameSel;
  if (BtnOutputMap != NULL)
    delete BtnOutputMap;
  if (BtnCrs != NULL)
    delete BtnCrs;
  if (BtnLoadShp != NULL)
    delete BtnLoadShp;
  if (BtnTableAdd != NULL)
    delete BtnTableAdd;
  if (BtnSrids != NULL)
    delete BtnSrids;
  if (BtnCharset != NULL)
    delete BtnCharset;
  if (BtnLineMeter != NULL)
    delete BtnLineMeter;
  if (BtnPolygonMeter != NULL)
    delete BtnPolygonMeter;
  if (BtnPencil != NULL)
    delete BtnPencil;
  if (BtnPencilAdd != NULL)
    delete BtnPencilAdd;
  if (BtnPencilDelete != NULL)
    delete BtnPencilDelete;
  if (BtnPencilGo != NULL)
    delete BtnPencilGo;
  if (BtnDeleteSubGeom != NULL)
    delete BtnDeleteSubGeom;
  if (BtnSplitLine != NULL)
    delete BtnSplitLine;
  if (BtnSelectMultiGeom != NULL)
    delete BtnSelectMultiGeom;
  if (BtnAbout != NULL)
    delete BtnAbout;
  if (BtnExit != NULL)
    delete BtnExit;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  if (NetParms)
    delete NetParms;
}

void MyFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
//
// EXIT - event handler
//
  CloseDB();
  Close(true);
}

void MyFrame::OnAbout(wxCommandEvent & WXUNUSED(event))
{
//
// ABOUT dialog - event handler
//
  char ver[128];
  wxAboutDialogInfo dlg;
  dlg.SetIcon(wxIcon(icon_info_xpm));
  dlg.SetName(wxT("spatialite-gis"));
  const char *version = VERSION;
  dlg.SetVersion(wxString::FromUTF8(version));
  wxString str = wxT("a minimalistic GIS based on SpatiaLite\n\n");
  sprintf(ver, "%d.%d.%d", wxMAJOR_VERSION, wxMINOR_VERSION, wxRELEASE_NUMBER);
  str += wxT("wxWidgets version ") + wxString::FromUTF8(ver) + wxT("\n");
  strcpy(ver, spatialite_version());
  str += wxT("SpatiaLite version ") + wxString::FromUTF8(ver) + wxT("\n");
  strcpy(ver, sqlite3_libversion());
  str += wxT("SQLite version ") + wxString::FromUTF8(ver) + wxT("\n");
  strcpy(ver, GEOSversion());
  str += wxT("GEOS version ") + wxString::FromUTF8(ver) + wxT("\n");
  strcpy(ver, pj_get_release());
  str += wxT("PROJ.4 version ") + wxString::FromUTF8(ver) + wxT("\n\n");
  str += wxT("SQLite's extension 'SpatiaLite' enabled\n");
  str += wxT("SQLite's extension 'VirtualShape' enabled\n");
  str += wxT("SQLite's extension 'VirtualText' enabled\n");
  str += wxT("SQLite's extension 'VirtualNetwork' enabled\n");
  str += wxT("SQLite's extension 'RTree' enabled\n");
  str += wxT("SQLite's extension 'MbrCache' enabled\n");
  str += wxT("SQLite's extension 'VirtualFDO' enabled\n\n");
  dlg.SetDescription(str);
  dlg.SetCopyright(wxT("by Alessandro Furieri - 2009-2011"));
  dlg.SetWebSite(wxT("http://www.gaia-gis.it"));
  wxString license =
    wxT("This program is free software; you can redistribute it\n");
  license +=
    wxT("and/or modify it under the terms of the GNU General Public License\n");
  license += wxT("(GPL) as published by the Free Software Foundation\n\n");
  license +=
    wxT
    ("A copy of the GPL can be found at\nhttp://www.gnu.org/licenses/gpl.txt");
  dlg.SetLicense(license);
  ::wxAboutBox(dlg);
}

void MyFrame::UpdateReferenceSystem()
{
//
// updating the status bar [Coordinate Reference Sysem]
//
  wxString crs = wxT("RefSys: ");
  char dummy[64];
  if (GetStatusBar() == NULL)
    return;
  sprintf(dummy, "%d", ProjectSrid.GetSrid());
  crs += wxString::FromUTF8(dummy);
  if (ProjectSrid.GetSrid() < 0)
    crs += wxT(" [UNDEFINED]");
  else
    {
      crs += wxT(" [");
      crs += ProjectSrid.GetSridName();
      crs += wxT("]");
    }
  GetStatusBar()->SetStatusText(crs, 0);
}

void MyFrame::UpdateScale(wxString & scale)
{
//
// updating the status bar [Scale]
//
  if (GetStatusBar() == NULL)
    return;
  GetStatusBar()->SetStatusText(scale, 1);
}

void MyFrame::UpdateCoords(wxString & coords)
{
//
// updating the status bar [Coordinates]
//
  if (GetStatusBar() == NULL)
    return;
  GetStatusBar()->SetStatusText(coords, 2);
}

void MyFrame::SaveConfig()
{
//
// saves layout configuration
//

  wxConfig *config = new wxConfig(wxT("spatialite-gis"));
  config->Write(wxT("Layout"), ConfigLayout);
  config->Write(wxT("PaneX"), ConfigPaneX);
  config->Write(wxT("PaneY"), ConfigPaneY);
  config->Write(wxT("PaneWidth"), ConfigPaneWidth);
  config->Write(wxT("PaneHeight"), ConfigPaneHeight);
  config->Write(wxT("SqlitePath"), SqlitePath);
  config->Write(wxT("LastDirectory"), LastDirectory);
  delete config;
}

void MyFrame::LoadConfig(wxString & externalPath)
{
//
// loads layout configuration
//
  ConfigLayout = wxT("");
  wxString ConfigDbPath = wxT("");
  wxString ConfigDir = wxT("");
  wxConfig *config = new wxConfig(wxT("spatialite-gis"));
  config->Read(wxT("Layout"), &ConfigLayout);
  config->Read(wxT("PaneX"), &ConfigPaneX, -1);
  config->Read(wxT("PaneY"), &ConfigPaneY, -1);
  config->Read(wxT("PaneWidth"), &ConfigPaneWidth, -1);
  config->Read(wxT("PaneHeight"), &ConfigPaneHeight, -1);
  config->Read(wxT("SqlitePath"), &ConfigDbPath);
  config->Read(wxT("LastDirectory"), &ConfigDir);
  delete config;

  if (externalPath.Len() > 0)
    {
      // applying the external path
      wxFileName file(externalPath);
      ConfigDir = file.GetPath();
      ConfigDbPath = externalPath;
    }
  if (ConfigLayout.Len() > 0)
    Manager.LoadPerspective(ConfigLayout, true);
  if (ConfigPaneX >= 0 && ConfigPaneY >= 0 && ConfigPaneWidth > 0
      && ConfigPaneHeight > 0)
    SetSize(ConfigPaneX, ConfigPaneY, ConfigPaneWidth, ConfigPaneHeight);
  if (ConfigDir.Len() > 0)
    LastDirectory = ConfigDir;
  if (ConfigDbPath.Len() > 0)
    {
      SqlitePath = ConfigDbPath;
      if (OpenDB() == false)
        SqlitePath = wxT("");
      else
        {
          wxMenuBar *menuBar = GetMenuBar();
          menuBar->Enable(ID_Connect, false);
          menuBar->Enable(ID_MemoryDbLoad, false);
          menuBar->Enable(ID_MemoryDbNew, false);
          if (MemoryDatabase == true)
            {
              menuBar->Enable(ID_MemoryDbSave, true);
              menuBar->Enable(ID_MemoryDbClock, true);
          } else
            {
              menuBar->Enable(ID_MemoryDbSave, false);
              menuBar->Enable(ID_MemoryDbClock, false);
            }
          menuBar->Enable(ID_Disconnect, true);
          menuBar->Enable(ID_CreateNew, false);
          menuBar->Enable(ID_Vacuum, true);
          menuBar->Enable(ID_Crs, true);
          menuBar->Enable(ID_LoadShp, true);
          menuBar->Enable(ID_TableAdd, true);
          menuBar->Enable(ID_Srids, true);
          wxToolBar *toolBar = GetToolBar();
          toolBar->EnableTool(ID_Connect, false);
          toolBar->EnableTool(ID_MemoryDbLoad, false);
          toolBar->EnableTool(ID_MemoryDbNew, false);
          if (MemoryDatabase == true)
            {
              toolBar->EnableTool(ID_MemoryDbSave, true);
              toolBar->EnableTool(ID_MemoryDbClock, true);
          } else
            {
              toolBar->EnableTool(ID_MemoryDbSave, false);
              toolBar->EnableTool(ID_MemoryDbClock, false);
            }
          toolBar->EnableTool(ID_Disconnect, true);
          toolBar->EnableTool(ID_CreateNew, false);
          toolBar->EnableTool(ID_Vacuum, true);
          toolBar->EnableTool(ID_Crs, true);
          toolBar->EnableTool(ID_LoadShp, true);
          toolBar->EnableTool(ID_TableAdd, true);
          toolBar->EnableTool(ID_Srids, true);
          SetTitle(ProjectName);
        }
    }
}

void MyFrame::OnConnect(wxCommandEvent & WXUNUSED(event))
{
//
// connecting to an existent SQLite DB
//
  int ret;
  wxString lastDir;
  wxMenuBar *menuBar;
  wxToolBar *toolBar;
  wxFileDialog fileDialog(this, wxT("DB connection"),
                          wxT(""), wxT("db.sqlite"),
                          wxT
                          ("SQLite DB (*.sqlite)|*.sqlite|All files (*.*)|*.*"),
                          wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition,
                          wxDefaultSize, wxT("filedlg"));
  lastDir = GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      MapView->SetMapToolsState(true);
      SqlitePath = fileDialog.GetPath();
      if (OpenDB() == false)
        SqlitePath = wxT("");
      else
        {
          wxFileName file(fileDialog.GetPath());
          lastDir = file.GetPath();
          SetLastDirectory(lastDir);
          menuBar = GetMenuBar();
          menuBar->Enable(ID_Connect, false);
          menuBar->Enable(ID_MemoryDbLoad, false);
          menuBar->Enable(ID_MemoryDbNew, false);
          if (MemoryDatabase == true)
            {
              menuBar->Enable(ID_MemoryDbSave, true);
              menuBar->Enable(ID_MemoryDbClock, true);
          } else
            {
              menuBar->Enable(ID_MemoryDbSave, false);
              menuBar->Enable(ID_MemoryDbClock, false);
            }
          menuBar->Enable(ID_Disconnect, true);
          menuBar->Enable(ID_CreateNew, false);
          menuBar->Enable(ID_Vacuum, true);
          menuBar->Enable(ID_Crs, true);
          menuBar->Enable(ID_LoadShp, true);
          menuBar->Enable(ID_TableAdd, true);
          menuBar->Enable(ID_Srids, true);
          toolBar = GetToolBar();
          toolBar->EnableTool(ID_Connect, false);
          toolBar->EnableTool(ID_MemoryDbLoad, false);
          toolBar->EnableTool(ID_MemoryDbNew, false);
          if (MemoryDatabase == true)
            {
              toolBar->EnableTool(ID_MemoryDbSave, true);
              toolBar->EnableTool(ID_MemoryDbClock, true);
          } else
            {
              toolBar->EnableTool(ID_MemoryDbSave, false);
              toolBar->EnableTool(ID_MemoryDbClock, false);
            }
          toolBar->EnableTool(ID_Disconnect, true);
          toolBar->EnableTool(ID_CreateNew, false);
          toolBar->EnableTool(ID_Vacuum, true);
          toolBar->EnableTool(ID_Crs, true);
          toolBar->EnableTool(ID_LoadShp, true);
          toolBar->EnableTool(ID_TableAdd, true);
          toolBar->EnableTool(ID_Srids, true);
          MapView->SetMapToolsState(false);
        }
    }
  OkCurrentEntity = false;
  CurrentEntityPrimaryKey = -1;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  CurrentEntityGeometry = NULL;
}

void MyFrame::OnMemoryDbLoad(wxCommandEvent & WXUNUSED(event))
{
//
// loading an external DB into the MEMORY-DB
//
  sqlite3 *extSqlite = NULL;
  sqlite3_backup *backup;
  int retdlg;
  int ret;
  wxString lastDir;
  int len;
  int invalid;
  int invalid_stats;
  int invalid_view_stats;
  int invalid_virt_stats;
  char path[1024];
  bool yesToThisOne = false;
  bool yesToAll = false;
  wxString error;
  wxToolBar *toolBar;
  wxMenuBar *menuBar;
  char *errMsg = NULL;
  CreateInternalTableDialog *createDialog;
  wxFileDialog fileDialog(this,
                          wxT("Loading an existing DB into the MEMORY-DB"),
                          wxT(""), wxT("db.sqlite"),
                          wxT
                          ("SQLite DB (*.sqlite)|*.sqlite|All files (*.*)|*.*"),
                          wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition,
                          wxDefaultSize, wxT("filedlg"));
  lastDir = GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  retdlg = fileDialog.ShowModal();
  if (retdlg == wxID_OK)
    {
      // opening the external DB
      ExternalSqlitePath = fileDialog.GetPath();
      ConvertString(ExternalSqlitePath, path, &len);
      ret = sqlite3_open_v2(path, &extSqlite, SQLITE_OPEN_READWRITE, NULL);
      if (ret)
        {
          // an error occurred
          wxString errCause = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          error = wxT("Failure while connecting to DB\n\n");
          error += errCause;
          error += wxT("\n");
          goto stop;
        }
      ret =
        sqlite3_open_v2(":memory:", &SqliteHandle,
                        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
      if (ret)
        {
          // an error occurred
          wxString errCause = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          error = wxT("MEMORY-DB: an error occurred \n\n");
          error += errCause;
          error += +wxT("\n");
          goto stop;
        }
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      SetLastDirectory(lastDir);
      backup = sqlite3_backup_init(SqliteHandle, "main", extSqlite, "main");
      if (!backup)
        goto stop;
      while (1)
        {
          ret = sqlite3_backup_step(backup, 1024);
          if (ret == SQLITE_DONE)
            break;
        }
      ret = sqlite3_backup_finish(backup);
      sqlite3_close(extSqlite);
    }
// activating Foreign Key constraints
  ret = sqlite3_exec(SqliteHandle, "PRAGMA foreign_keys = 1", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("PRAGMA foreign_keys error: ") +
                   wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return;
    }
// checking the DB for sanity
  if (CheckMetadata() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg = wxT("Missing or invalid Spatial Metadata tables:\n");
      msg += wxT("- spatial_ref_sys\n- geometry_columns\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return;
    }
  if (CheckSymbolBitmaps(&invalid) == false)
    {
      if (invalid)
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'symbol_bitmaps' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
      wxString msg = wxT("The 'symbol_bitmaps' table doesn't exists\n\n");
      msg += wxT("Can I create and initialize this table ?");
      createDialog = new CreateInternalTableDialog(this, msg);
      createDialog->Create();
      createDialog->ShowModal();
      if (createDialog->IsAnswerYes() == true)
        yesToThisOne = true;
      else
        yesToThisOne = false;
      if (createDialog->IsAnswerYesToAll() == true)
        yesToAll = true;
      else
        yesToAll = false;
      delete createDialog;
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateSymbolBitmaps();
          if (ok == false)
            {
              MemoryDatabase = false;
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'symbol_bitmaps' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              return;
            }
      } else
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'symbol_bitmaps' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
    }
  if (CheckPatternBitmaps(&invalid) == false)
    {
      if (invalid)
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'pattern_bitmaps' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'pattern_bitmaps' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreatePatternBitmaps();
          if (ok == false)
            {
              MemoryDatabase = false;
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'pattern_bitmaps' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              return;
            }
      } else
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'pattern_bitmaps' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
    }
  if (CheckRasterPyramids(&invalid) == false)
    {
      if (invalid)
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'raster_pyramids' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
      wxString msg = wxT("The 'raster_pyramids' table doesn't exists\n\n");
      msg += wxT("Can I create and initialize this table ?");
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'pattern_bitmaps' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateRasterPyramids();
          if (ok == false)
            {
              MemoryDatabase = false;
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'raster_pyramids' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              return;
            }
      } else
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'raster_pyramids' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
    }
  CheckLayerStatistics(&invalid_stats);
  CheckViewsLayerStatistics(&invalid_view_stats);
  CheckVirtsLayerStatistics(&invalid_virt_stats);
  if (invalid_stats)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT
        ("Table 'layer_statistics' already exists, but has an invalid layout\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      return;
    }
  if (invalid_view_stats)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT
        ("Table 'views_layer_statistics' already exists, but has an invalid layout\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      return;
    }
  if (invalid_virt_stats)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT
        ("Table 'virts_layer_statistics' already exists, but has an invalid layout\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      return;
    }
  if (yesToAll == false)
    {
      wxString msg = wxT("Layer Statistics tables need synchronization\n\n");
      msg += wxT("Can I synchronize these tables ?");
      createDialog = new CreateInternalTableDialog(this, msg);
      createDialog->Create();
      createDialog->ShowModal();
      if (createDialog->IsAnswerYes() == true)
        yesToThisOne = true;
      else
        yesToThisOne = false;
      if (createDialog->IsAnswerYesToAll() == true)
        yesToAll = true;
      else
        yesToAll = false;
      delete createDialog;
    }
  if (yesToThisOne == true || yesToAll == true)
    AlignStatistics();
  else
    {
      sqlite3_close(SqliteHandle);
      wxString msg = wxT("Layer Statistics' tables are out-of-sync\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      return;
    }
  if (CheckLayerTableLayout(&invalid) == false)
    {
      if (invalid)
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'layer_table_layout' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
      wxString msg = wxT("The 'layer_table_layout' table doesn't exists\n\n");
      msg += wxT("Can I create and initialize this table ?");
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'pattern_bitmaps' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateLayerTableLayout();
          if (ok == false)
            {
              MemoryDatabase = false;
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'layer_table_layout' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              return;
            }
      } else
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'layer_table_layout' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
    }
  if (CheckLayerParams(&invalid) == false)
    {
      if (invalid)
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'layer_params' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
      wxString msg = wxT("The 'layer_params' table doesn't exists\n\n");
      msg += wxT("Can I create and initialize this table ?");
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'pattern_bitmaps' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateLayerParams();
          if (ok == false)
            {
              MemoryDatabase = false;
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'layer_params' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              return;
            }
      } else
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'layer_params' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
    }
  if (CheckLayerSubClasses(&invalid) == false)
    {
      if (invalid)
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'layer_sub_classes' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
      wxString msg = wxT("The 'layer_sub_classes' table doesn't exists\n\n");
      msg += wxT("Can I create and initialize this table ?");
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'pattern_bitmaps' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateLayerSubClasses();
          if (ok == false)
            {
              MemoryDatabase = false;
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'layer_sub_classes' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              return;
            }
      } else
        {
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'layer_sub_classes' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
    }
  if (CheckProjectDefs(&invalid) == false)
    {
      if (invalid)
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'project_defs' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
      wxString msg = wxT("The 'project_defs' table doesn't exists\n\n");
      msg += wxT("Can I create and initialize this table ?");
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'pattern_bitmaps' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateProjectDefs();
          if (ok == false)
            {
              MemoryDatabase = false;
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'project_defs' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              return;
            }
      } else
        {
          MemoryDatabase = false;
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'project_defs' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          return;
        }
    }
  MapView->SetMapToolsState(true);
  MemoryDatabase = true;
  AutoSaveInterval = 120;
  InitLayerTree();
  MapView->ComputeMapExtent();
  MapView->SetFrameFullExtent();
  MapView->PrepareMap();
  menuBar = GetMenuBar();
  menuBar->Enable(ID_Connect, false);
  menuBar->Enable(ID_MemoryDbLoad, false);
  menuBar->Enable(ID_MemoryDbNew, false);
  if (MemoryDatabase == true)
    {
      menuBar->Enable(ID_MemoryDbSave, true);
      menuBar->Enable(ID_MemoryDbClock, true);
  } else
    {
      menuBar->Enable(ID_MemoryDbSave, false);
      menuBar->Enable(ID_MemoryDbClock, false);
    }
  menuBar->Enable(ID_Disconnect, true);
  menuBar->Enable(ID_CreateNew, false);
  menuBar->Enable(ID_Vacuum, true);
  menuBar->Enable(ID_Crs, true);
  menuBar->Enable(ID_LoadShp, true);
  menuBar->Enable(ID_TableAdd, true);
  menuBar->Enable(ID_Srids, true);
  toolBar = GetToolBar();
  toolBar->EnableTool(ID_Connect, false);
  toolBar->EnableTool(ID_MemoryDbLoad, false);
  toolBar->EnableTool(ID_MemoryDbNew, false);
  if (MemoryDatabase == true)
    {
      toolBar->EnableTool(ID_MemoryDbSave, true);
      toolBar->EnableTool(ID_MemoryDbClock, true);
  } else
    {
      toolBar->EnableTool(ID_MemoryDbSave, false);
      toolBar->EnableTool(ID_MemoryDbClock, false);
    }
  toolBar->EnableTool(ID_Disconnect, true);
  toolBar->EnableTool(ID_CreateNew, false);
  toolBar->EnableTool(ID_Vacuum, true);
  toolBar->EnableTool(ID_Crs, true);
  toolBar->EnableTool(ID_LoadShp, true);
  toolBar->EnableTool(ID_TableAdd, true);
  toolBar->EnableTool(ID_Srids, true);
  MapView->SetMapToolsState(false);
  if (AutoSaveInterval <= 0)
    {
      if (TimerAutoSave)
        {
          TimerAutoSave->Stop();
          delete TimerAutoSave;
          TimerAutoSave = NULL;
        }
  } else
    {
      //
      // starting the AutoSave timer
      //
      if (!TimerAutoSave)
        TimerAutoSave = new wxTimer(this, ID_AUTO_SAVE_TIMER);
      else
        TimerAutoSave->Stop();
      LastTotalChanges = 0;
      TimerAutoSave->Start(AutoSaveInterval * 1000, wxTIMER_ONE_SHOT);
    }
  OkCurrentEntity = false;
  CurrentEntityPrimaryKey = -1;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  CurrentEntityGeometry = NULL;
  return;
stop:
  MemoryDatabase = false;
  if (SqliteHandle)
    sqlite3_close(SqliteHandle);
  if (extSqlite)
    sqlite3_close(extSqlite);
  wxString msg = wxT("MEMORY-DB wasn't loaded\n\n");
  msg += error;
  wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
  SqliteHandle = NULL;
  ClearLayerTree();
}

void MyFrame::OnMemoryDbNew(wxCommandEvent & WXUNUSED(event))
{
//
//creating a new MEMORY-DB
//
  int ret;
  wxMenuBar *menuBar;
  wxToolBar *toolBar;
  MemoryDatabase = true;
  AutoSaveInterval = 120;
  ExternalSqlitePath = wxT("");
// creating the new MEMORY-DB
  ret = CreateDB();
  if (ret == false)
    goto error;
  menuBar = GetMenuBar();
  menuBar->Enable(ID_Connect, false);
  menuBar->Enable(ID_CreateNew, false);
  menuBar->Enable(ID_MemoryDbLoad, false);
  menuBar->Enable(ID_MemoryDbNew, false);
  menuBar->Enable(ID_MemoryDbSave, true);
  menuBar->Enable(ID_MemoryDbClock, true);
  menuBar->Enable(ID_Disconnect, true);
  menuBar->Enable(ID_Vacuum, true);
  menuBar->Enable(ID_Crs, true);
  menuBar->Enable(ID_LoadShp, true);
  menuBar->Enable(ID_TableAdd, true);
  menuBar->Enable(ID_Srids, true);
  toolBar = GetToolBar();
  toolBar->EnableTool(ID_Connect, false);
  toolBar->EnableTool(ID_CreateNew, false);
  toolBar->EnableTool(ID_MemoryDbLoad, false);
  toolBar->EnableTool(ID_MemoryDbNew, false);
  toolBar->EnableTool(ID_MemoryDbSave, true);
  toolBar->EnableTool(ID_MemoryDbClock, true);
  toolBar->EnableTool(ID_Disconnect, true);
  toolBar->EnableTool(ID_Vacuum, true);
  toolBar->EnableTool(ID_Crs, true);
  toolBar->EnableTool(ID_LoadShp, true);
  toolBar->EnableTool(ID_TableAdd, true);
  toolBar->EnableTool(ID_Srids, true);
  if (AutoSaveInterval <= 0)
    {
      if (TimerAutoSave)
        {
          TimerAutoSave->Stop();
          delete TimerAutoSave;
          TimerAutoSave = NULL;
        }
  } else
    {
      //
      // starting the AutoSave timer
      //
      if (!TimerAutoSave)
        TimerAutoSave = new wxTimer(this, ID_AUTO_SAVE_TIMER);
      else
        TimerAutoSave->Stop();
      LastTotalChanges = 0;
      TimerAutoSave->Start(AutoSaveInterval * 1000, wxTIMER_ONE_SHOT);
    }
  OkCurrentEntity = false;
  CurrentEntityPrimaryKey = -1;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  CurrentEntityGeometry = NULL;
  return;
error:
  wxString msg = wxT("An error occurred\nno MEMORY-DB was created");
  wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
  return;
}

bool MyFrame::MemoryDbSave()
{
//
// trying to export the MEMORY-DB into an external DB
//
  sqlite3 *extSqlite = NULL;
  sqlite3_backup *backup;
  int len;
  char path[1024];
  char bak_path[1024];
  int ret;
  wxString error;
  if (ExternalSqlitePath.Len() == 0)
    return false;
  ::wxBeginBusyCursor();
  ConvertString(ExternalSqlitePath, path, &len);
  strcpy(bak_path, path);
  strcat(bak_path, ".bak");
  unlink(bak_path);
  rename(path, bak_path);
  ret =
    sqlite3_open_v2(path, &extSqlite,
                    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (ret)
    {
      // an error occurred
      wxString errCause = wxString::FromUTF8(sqlite3_errmsg(extSqlite));
      error = wxT("An error occurred\n\n");
      error += errCause;
      error += +wxT("\n");
      error += ExternalSqlitePath;
      goto stop;
    }
  backup = sqlite3_backup_init(extSqlite, "main", SqliteHandle, "main");
  if (!backup)
    goto stop;
  while (1)
    {
      ret = sqlite3_backup_step(backup, 1024);
      if (ret == SQLITE_DONE)
        break;
    }
  ret = sqlite3_backup_finish(backup);
  sqlite3_close(extSqlite);
  unlink(bak_path);
  ::wxEndBusyCursor();
  LastTotalChanges = sqlite3_total_changes(SqliteHandle);
  return true;
stop:
  if (extSqlite)
    sqlite3_close(extSqlite);
  wxString msg = wxT("Backup failure: MEMORY-DB wasn't saved\n\n");
  msg += error;
  wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
  ExternalSqlitePath = wxT("");
  ::wxEndBusyCursor();
  return false;
}

void MyFrame::OnMemoryDbSave(wxCommandEvent & WXUNUSED(event))
{
//
//  exporting the MEMORY-DB into an external DB 
//
  int retdlg;
  wxString lastDir;
  if (ExternalSqlitePath.Len() > 0)
    {
      if (MemoryDbSave() == true)
        {
          wxMessageBox(wxT("Ok, MEMORY-DB was succesfully saved"),
                       wxT("spatialite-gis"), wxOK | wxICON_INFORMATION, this);
          if (AutoSaveInterval <= 0)
            {
              if (TimerAutoSave)
                {
                  TimerAutoSave->Stop();
                  delete TimerAutoSave;
                  TimerAutoSave = NULL;
                }
          } else
            {
              //
              // restarting the AutoSave timer
              //
              if (!TimerAutoSave)
                TimerAutoSave = new wxTimer(this, ID_AUTO_SAVE_TIMER);
              else
                TimerAutoSave->Stop();
              TimerAutoSave->Start(AutoSaveInterval * 1000, wxTIMER_ONE_SHOT);
            }
          return;
        }
    }
  wxFileDialog fileDialog(this, wxT("Saving the MEMORY-DB"),
                          wxT(""), wxT("db.sqlite"),
                          wxT
                          ("SQLite DB (*.sqlite)|*.sqlite|All files (*.*)|*.*"),
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition,
                          wxDefaultSize, wxT("filedlg"));
  lastDir = GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  retdlg = fileDialog.ShowModal();
  if (retdlg == wxID_OK)
    {
      // exporting the external DB
      ExternalSqlitePath = fileDialog.GetPath();
      if (MemoryDbSave() == true)
        {
          wxMessageBox(wxT("Ok, MEMORY-DB was succesfully saved"),
                       wxT("spatialite-gis"), wxOK | wxICON_INFORMATION, this);
          wxFileName file(fileDialog.GetPath());
          lastDir = file.GetPath();
          SetLastDirectory(lastDir);
          if (AutoSaveInterval <= 0)
            {
              if (TimerAutoSave)
                {
                  TimerAutoSave->Stop();
                  delete TimerAutoSave;
                  TimerAutoSave = NULL;
                }
          } else
            {
              //
              // restarting the AutoSave timer
              //
              if (!TimerAutoSave)
                TimerAutoSave = new wxTimer(this, ID_AUTO_SAVE_TIMER);
              else
                TimerAutoSave->Stop();
              TimerAutoSave->Start(AutoSaveInterval * 1000, wxTIMER_ONE_SHOT);
            }
        }
    }
}

void MyFrame::OnMemoryDbClock(wxCommandEvent & WXUNUSED(event))
{
//
//  setting up AutoSave for MEMORY-DB 
//
  AutoSaveDialog dlg;
  dlg.Create(this, ExternalSqlitePath, AutoSaveInterval);
  int ret = dlg.ShowModal();
  if (ret == wxID_OK)
    {
      AutoSaveInterval = dlg.GetSeconds();
      if (AutoSaveInterval <= 0)
        {
          //
          // stopping the AutoSave timer
          //
          if (TimerAutoSave)
            {
              TimerAutoSave->Stop();
              delete TimerAutoSave;
              TimerAutoSave = NULL;
            }
      } else
        {
          if (AutoSaveInterval <= 0)
            {
              if (TimerAutoSave)
                {
                  TimerAutoSave->Stop();
                  delete TimerAutoSave;
                  TimerAutoSave = NULL;
                }
          } else
            {
              //
              // restarting the AutoSave timer
              //
              if (!TimerAutoSave)
                TimerAutoSave = new wxTimer(this, ID_AUTO_SAVE_TIMER);
              else
                TimerAutoSave->Stop();
              TimerAutoSave->Start(AutoSaveInterval * 1000, wxTIMER_ONE_SHOT);
            }
        }
    }
}

void MyFrame::OnDisconnect(wxCommandEvent & WXUNUSED(event))
{
//
// disconnecting current SQLite DB
//
  if (TimerAutoSave)
    {
      TimerAutoSave->Stop();
      delete TimerAutoSave;
      TimerAutoSave = NULL;
    }
  CloseDB();
  ExternalSqlitePath = wxT("");
  wxMenuBar *menuBar = GetMenuBar();
  menuBar->Enable(ID_Connect, true);
  menuBar->Enable(ID_MemoryDbLoad, true);
  menuBar->Enable(ID_MemoryDbNew, true);
  menuBar->Enable(ID_MemoryDbSave, false);
  menuBar->Enable(ID_MemoryDbClock, false);
  menuBar->Enable(ID_Disconnect, false);
  menuBar->Enable(ID_CreateNew, true);
  menuBar->Enable(ID_Vacuum, false);
  menuBar->Enable(ID_Crs, false);
  menuBar->Enable(ID_LoadShp, false);
  menuBar->Enable(ID_TableAdd, false);
  menuBar->Enable(ID_Srids, false);
  wxToolBar *toolBar = GetToolBar();
  toolBar->EnableTool(ID_Connect, true);
  toolBar->EnableTool(ID_MemoryDbLoad, true);
  toolBar->EnableTool(ID_MemoryDbNew, true);
  toolBar->EnableTool(ID_MemoryDbSave, false);
  toolBar->EnableTool(ID_MemoryDbClock, false);
  toolBar->EnableTool(ID_Disconnect, false);
  toolBar->EnableTool(ID_CreateNew, true);
  toolBar->EnableTool(ID_Vacuum, false);
  toolBar->EnableTool(ID_Crs, false);
  toolBar->EnableTool(ID_LoadShp, false);
  toolBar->EnableTool(ID_TableAdd, false);
  toolBar->EnableTool(ID_Srids, false);
  MapView->SetMapToolsState(true);
  OkCurrentEntity = false;
  CurrentEntityPrimaryKey = -1;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  CurrentEntityGeometry = NULL;
}

void MyFrame::OnCreateNew(wxCommandEvent & WXUNUSED(event))
{
//
// creating a new, empty SQLite DB
//
  int retdlg;
  int ret;
  wxString lastDir;
  wxFileDialog fileDialog(this, wxT("Creating a new, empty DB"),
                          wxT(""), wxT("db.sqlite"),
                          wxT
                          ("SQLite DB (*.sqlite)|*.sqlite|All files (*.*)|*.*"),
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition,
                          wxDefaultSize, wxT("filedlg"));
  lastDir = GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  retdlg = fileDialog.ShowModal();
  if (retdlg == wxID_OK)
    {
      // creating the new DB
      SqlitePath = fileDialog.GetPath();
      ret = CreateDB();
      if (ret == false)
        goto error;
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      SetLastDirectory(lastDir);
      wxMenuBar *menuBar = GetMenuBar();
      menuBar->Enable(ID_Connect, false);
      menuBar->Enable(ID_CreateNew, false);
      menuBar->Enable(ID_MemoryDbLoad, false);
      menuBar->Enable(ID_MemoryDbNew, false);
      menuBar->Enable(ID_MemoryDbSave, false);
      menuBar->Enable(ID_MemoryDbClock, false);
      menuBar->Enable(ID_Disconnect, true);
      menuBar->Enable(ID_Vacuum, true);
      menuBar->Enable(ID_Crs, true);
      menuBar->Enable(ID_LoadShp, true);
      menuBar->Enable(ID_TableAdd, true);
      menuBar->Enable(ID_Srids, true);
      wxToolBar *toolBar = GetToolBar();
      toolBar->EnableTool(ID_Connect, false);
      toolBar->EnableTool(ID_CreateNew, false);
      toolBar->EnableTool(ID_MemoryDbLoad, false);
      toolBar->EnableTool(ID_MemoryDbNew, false);
      toolBar->EnableTool(ID_MemoryDbSave, false);
      toolBar->EnableTool(ID_MemoryDbClock, false);
      toolBar->EnableTool(ID_Disconnect, true);
      toolBar->EnableTool(ID_Vacuum, true);
      toolBar->EnableTool(ID_Crs, true);
      toolBar->EnableTool(ID_LoadShp, true);
      toolBar->EnableTool(ID_TableAdd, true);
      toolBar->EnableTool(ID_Srids, true);
      OkCurrentEntity = false;
      CurrentEntityPrimaryKey = -1;
      if (CurrentEntityGeometry)
        gaiaFreeGeomColl(CurrentEntityGeometry);
      CurrentEntityGeometry = NULL;
      return;
  } else
    return;
error:
  unlink(SqlitePath.ToUTF8());
  wxString msg = wxT("An error occurred\nno DB was created");
  wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
  return;
}

void MyFrame::DbPagesCount(int *total, int *frees)
{
//
// computing the DB pages count
//
  int ret;
  char **results;
  int rows;
  int columns;
  int i;
  char *errMsg = NULL;
  wxString sql;
  char *value;
  *total = 0;
  *frees = 0;
  sql = wxT("PRAGMA page_count");
  ret = sqlite3_get_table(GetSqlite(), sql.ToUTF8(), &results,
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
          *total = atoi(value);
        }
    }
  sqlite3_free_table(results);
  sql = wxT("PRAGMA freelist_count");
  ret = sqlite3_get_table(GetSqlite(), sql.ToUTF8(), &results,
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
          *frees = atoi(value);
        }
    }
  sqlite3_free_table(results);
}

void MyFrame::OnVacuum(wxCommandEvent & WXUNUSED(event))
{
//
// performing a VACUUM in order to reorganize the current DB
//
  char *errMsg = NULL;
  int totalPages;
  int freePages;
  int totalPages2;
  int freePages2;
  wxString msg;
  char dummy[128];
  DbPagesCount(&totalPages, &freePages);
  if (!freePages)
    {
      msg = wxT("The current DB doesn't requires to be VACUUMed\n\n");
      msg += wxT("Total Pages: ");
      sprintf(dummy, "%d\n", totalPages);
      msg += wxString::FromUTF8(dummy);
      msg += wxT("Free Pages: 0\n\n");
      msg += wxT("Free Ratio: 0.0%");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION, this);
      return;
  } else
    {
      double ratio = 100.0 / ((double) totalPages / (double) freePages);
      if (ratio >= 33.33)
        msg = wxT("The current DB urgently requires to be VACUUMed\n\n");
      else if (ratio >= 10.0)
        msg = wxT("The current DB may usefully be VACUUMed\n\n");
      else
        msg =
          wxT("The current DB doesn't strictly requires to be VACUUMed\n\n");
      msg += wxT("Total Pages: ");
      sprintf(dummy, "%d\n", totalPages);
      msg += wxString::FromUTF8(dummy);
      msg += wxT("Free Pages: ");
      sprintf(dummy, "%d\n\n", freePages);
      msg += wxString::FromUTF8(dummy);
      msg += wxT("Free Ratio: ");
      sprintf(dummy, "%1.2f%%\n", ratio);
      msg += wxString::FromUTF8(dummy);
      msg += wxT("\n\nDo you confirm VACUUMing the current DB ?");
      int ret =
        wxMessageBox(msg, wxT("spatialite-gis"), wxYES_NO | wxICON_QUESTION,
                     this);
      if (ret != wxYES)
        return;
    }
  ::wxBeginBusyCursor();
  int ret = sqlite3_exec(SqliteHandle, "ANALYZE; VACUUM;", NULL, NULL, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
  } else
    {
      DbPagesCount(&totalPages2, &freePages2);
      msg = wxT("Current DB was succesfully optimized");
      if (totalPages2 < totalPages)
        {
          sprintf(dummy, "\n\n%d unused pages where reclaimed",
                  totalPages - totalPages2);
          msg += wxString::FromUTF8(dummy);
        }
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION, this);
    }
  ::wxEndBusyCursor();
}

bool MyFrame::CreateDB()
{
// creating a new, empty SQLite DB
  int ret;
  int len;
  char path[1024];
  char *errMsg = NULL;
  if (MemoryDatabase == true)
    strcpy(path, ":memory:");
  else
    {
      ConvertString(SqlitePath, path, &len);
      unlink(path);
    }
  ret =
    sqlite3_open_v2(path, &SqliteHandle,
                    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (ret)
    {
      // an error occurred
      wxString errCause;
      errCause = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      sqlite3_close(SqliteHandle);
      wxMessageBox(wxT("An error occurred\n\n") + errCause + wxT("\n") +
                   SqlitePath, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                   this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
// activating Foreign Key constraints
  ret = sqlite3_exec(SqliteHandle, "PRAGMA foreign_keys = 1", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("PRAGMA foreign_keys error: ") +
                   wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CreateSpatialMetaData() == false)
    wxMessageBox(wxT("Spatial Metadata tables creation error\n") +
                 SqlitePath, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
  if (CreateSymbolBitmaps() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg = wxT("Unable to initialize the 'symbol_bitmaps' table\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CreatePatternBitmaps() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT("Unable to initialize the 'pattern_bitmaps' table\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CreateRasterPyramids() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT("Unable to initialize the 'raster_pyramids' table\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CreateLayerTableLayout() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT("Unable to initialize the 'layer_table_layout' table\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CreateLayerParams() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg = wxT("Unable to initialize the 'layer_params' table\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CreateLayerSubClasses() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT("Unable to initialize the 'layer_sub_classes' table\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CreateProjectDefs() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg = wxT("Unable to initialize the 'project_defs' table\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  InitLayerTree();
  MapView->ComputeMapExtent();
  MapView->SetFrameFullExtent();
  MapView->PrepareMap();
  OkCurrentEntity = false;
  CurrentEntityPrimaryKey = -1;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  CurrentEntityGeometry = NULL;
  return true;
}

bool MyFrame::OpenDB()
{
//
// establishing a physical connetion to some DB SQLite
//
  int invalid;
  int invalid_stats;
  int invalid_view_stats;
  int invalid_virt_stats;
  int ret;
  int len;
  char path[1024];
  bool yesToThisOne = false;
  bool yesToAll = false;
  char *errMsg = NULL;
  CreateInternalTableDialog *createDialog;
  if (MemoryDatabase == true)
    strcpy(path, ":memory:");
  else
    ConvertString(SqlitePath, path, &len);
  ret = sqlite3_open_v2(path, &SqliteHandle, SQLITE_OPEN_READWRITE, NULL);
  if (ret)
    {
      // an error occurred
      wxString errCause;
      errCause = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      sqlite3_close(SqliteHandle);
      wxMessageBox(wxT("Failure while connecting to DB\n\n") + errCause +
                   wxT("\n") + SqlitePath, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
// activating Foreign Key constraints
  ret = sqlite3_exec(SqliteHandle, "PRAGMA foreign_keys = 1", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("PRAGMA foreign_keys error: ") +
                   wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CheckMetadata() == false)
    {
      sqlite3_close(SqliteHandle);
      wxString msg = wxT("Missing or invalid Spatial Metadata tables:\n");
      msg += wxT("- spatial_ref_sys\n- geometry_columns\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CheckSymbolBitmaps(&invalid) == false)
    {
      if (invalid)
        {
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'symbol_bitmaps' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
      wxString msg = wxT("The 'symbol_bitmaps' table doesn't exists\n\n");
      msg += wxT("Can I create and initialize this table ?");
      createDialog = new CreateInternalTableDialog(this, msg);
      createDialog->Create();
      createDialog->ShowModal();
      if (createDialog->IsAnswerYes() == true)
        yesToThisOne = true;
      else
        yesToThisOne = false;
      if (createDialog->IsAnswerYesToAll() == true)
        yesToAll = true;
      else
        yesToAll = false;
      delete createDialog;
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateSymbolBitmaps();
          if (ok == false)
            {
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'symbol_bitmaps' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              MemoryDatabase = false;
              return false;
            }
      } else
        {
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'symbol_bitmaps' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
    }
  if (CheckPatternBitmaps(&invalid) == false)
    {
      if (invalid)
        {
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'pattern_bitmaps' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'pattern_bitmaps' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreatePatternBitmaps();
          if (ok == false)
            {
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'pattern_bitmaps' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              MemoryDatabase = false;
              return false;
            }
      } else
        {
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'pattern_bitmaps' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
    }
  if (CheckRasterPyramids(&invalid) == false)
    {
      if (invalid)
        {
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'raster_pyramids' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'raster_pyramids' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateRasterPyramids();
          if (ok == false)
            {
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'raster_pyramids' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              MemoryDatabase = false;
              return false;
            }
      } else
        {
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'raster_pyramids' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
    }
  CheckLayerStatistics(&invalid_stats);
  CheckViewsLayerStatistics(&invalid_view_stats);
  CheckVirtsLayerStatistics(&invalid_virt_stats);
  if (invalid_stats)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT
        ("Table 'layer_statistics' already exists, but has an invalid layout\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (invalid_view_stats)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT
        ("Table 'views_layer_statistics' already exists, but has an invalid layout\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (invalid_virt_stats)
    {
      sqlite3_close(SqliteHandle);
      wxString msg =
        wxT
        ("Table 'virts_layer_statistics' already exists, but has an invalid layout\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (yesToAll == false)
    {
      wxString msg = wxT("Layer Statistics tables need synchronization\n\n");
      msg += wxT("Can I synchronize these tables ?");
      createDialog = new CreateInternalTableDialog(this, msg);
      createDialog->Create();
      createDialog->ShowModal();
      if (createDialog->IsAnswerYes() == true)
        yesToThisOne = true;
      else
        yesToThisOne = false;
      if (createDialog->IsAnswerYesToAll() == true)
        yesToAll = true;
      else
        yesToAll = false;
      delete createDialog;
    }
  if (yesToThisOne == true || yesToAll == true)
    AlignStatistics();
  else
    {
      sqlite3_close(SqliteHandle);
      wxString msg = wxT("Layer Statistics' tables are out-of-sync\n\n");
      msg += wxT("Sorry, cowardly quitting ...\n");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      SqliteHandle = NULL;
      ClearLayerTree();
      MemoryDatabase = false;
      return false;
    }
  if (CheckLayerTableLayout(&invalid) == false)
    {
      if (invalid)
        {
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'layer_table_layout' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
      if (yesToAll == false)
        {
          wxString msg =
            wxT("The 'layer_table_layout' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateLayerTableLayout();
          if (ok == false)
            {
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'layer_table_layout' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              MemoryDatabase = false;
              return false;
            }
      } else
        {
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'layer_table_layout' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
    }
  if (CheckLayerParams(&invalid) == false)
    {
      if (invalid)
        {
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'layer_params' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'layer_params' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateLayerParams();
          if (ok == false)
            {
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'layer_params' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              MemoryDatabase = false;
              return false;
            }
      } else
        {
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'layer_params' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
    }
  if (CheckLayerSubClasses(&invalid) == false)
    {
      if (invalid)
        {
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'layer_sub_classes' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
      if (yesToAll == false)
        {
          wxString msg =
            wxT("The 'layer_sub_classes' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateLayerSubClasses();
          if (ok == false)
            {
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'layer_sub_classes' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              MemoryDatabase = false;
              return false;
            }
      } else
        {
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'layer_sub_classes' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
    }
  if (CheckProjectDefs(&invalid) == false)
    {
      if (invalid)
        {
          sqlite3_close(SqliteHandle);
          wxString msg =
            wxT
            ("Table 'project_defs' already exists, but has an invalid layout\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
      if (yesToAll == false)
        {
          wxString msg = wxT("The 'project_defs' table doesn't exists\n\n");
          msg += wxT("Can I create and initialize this table ?");
          createDialog = new CreateInternalTableDialog(this, msg);
          createDialog->Create();
          createDialog->ShowModal();
          if (createDialog->IsAnswerYes() == true)
            yesToThisOne = true;
          else
            yesToThisOne = false;
          if (createDialog->IsAnswerYesToAll() == true)
            yesToAll = true;
          else
            yesToAll = false;
          delete createDialog;
        }
      if (yesToThisOne == true || yesToAll == true)
        {
          bool ok = CreateProjectDefs();
          if (ok == false)
            {
              sqlite3_close(SqliteHandle);
              wxString msg =
                wxT("Unable to initialize the 'project_defs' table\n\n");
              msg += wxT("Sorry, cowardly quitting ...\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           this);
              SqliteHandle = NULL;
              ClearLayerTree();
              MemoryDatabase = false;
              return false;
            }
      } else
        {
          sqlite3_close(SqliteHandle);
          wxString msg = wxT("Table 'project_defs' is missing\n\n");
          msg += wxT("Sorry, cowardly quitting ...\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          SqliteHandle = NULL;
          ClearLayerTree();
          MemoryDatabase = false;
          return false;
        }
    }
  InitLayerTree();
  MapView->ComputeMapExtent();
  MapView->SetFrameFullExtent();
  MapView->PrepareMap();
  OkCurrentEntity = false;
  CurrentEntityPrimaryKey = -1;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  CurrentEntityGeometry = NULL;
  return true;
}

void MyFrame::LastDitchMemoryDbSave()
{
//
// performing the last desperate attempt to save a MEMORY-DB
//
  int tc;
  int ret;
  wxString lastDir;
  if (MemoryDatabase == false)
    return;
  if (!SqliteHandle)
    return;
  tc = sqlite3_total_changes(SqliteHandle);
  if (tc == LastTotalChanges)
    return;
  while (1)
    {
      // OK, this MEMORY-DB needs to be saved
      if (MemoryDbSave() == true)
        break;
      // we must ask the user
      wxString msg =
        wxT("WARNING: the MEMORY-DB contains uncommitted changes\n\n");
      msg += wxT("The MEMORY_DB is intrinsecally volatile, so these changes\n");
      msg +=
        wxT("will be irremediably lost if you don't export them to some\n");
      msg += wxT("persistent storage [i.e. on the file-system]\n\n");
      msg +=
        wxT
        ("Do you want to export [SAVE] the MEMORY-DB to some external database ?");
      ret =
        wxMessageBox(msg, wxT("spatialite-gis"), wxYES_NO | wxICON_QUESTION,
                     this);
      if (ret != wxYES)
        break;
      // asking a PATHNAME to the user
      wxFileDialog fileDialog(this, wxT("Saving the MEMORY-DB"),
                              wxT(""), wxT("db.sqlite"),
                              wxT
                              ("SQLite DB (*.sqlite)|*.sqlite|All files (*.*)|*.*"),
                              wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
                              wxDefaultPosition, wxDefaultSize, wxT("filedlg"));
      lastDir = GetLastDirectory();
      if (lastDir.Len() >= 1)
        fileDialog.SetDirectory(lastDir);
      ret = fileDialog.ShowModal();
      if (ret == wxID_OK)
        {
          // exporting the external DB
          ExternalSqlitePath = fileDialog.GetPath();
          if (MemoryDbSave() == true)
            {
              wxMessageBox(wxT("Ok, MEMORY-DB was succesfully saved"),
                           wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                           this);
              break;
            }
        }
    }
}

void MyFrame::CloseDB()
{
//
// disconnecting current SQLite DB
//
  if (!SqliteHandle)
    return;
  LastDitchMemoryDbSave();
  MemoryDatabase = false;
  sqlite3_close(SqliteHandle);
  SqliteHandle = NULL;
  SqlitePath = wxT("");
  ClearLayerTree();
  MapView->ClearMapExtent();
  MapView->PrepareMap();
  OkCurrentEntity = false;
  CurrentEntityPrimaryKey = -1;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  CurrentEntityGeometry = NULL;
}

void MyFrame::EnableMeterTools(bool mode)
{
//
// Enabling / Disabling the Meter tools
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (menuBar)
    {
      menuBar->Enable(ID_MapFrameSel, mode);
      menuBar->Enable(ID_MapFrameAll, mode);
      menuBar->Enable(ID_LineMeter, mode);
      menuBar->Enable(ID_PolygonMeter, mode);
    }
  if (toolBar)
    {
      toolBar->EnableTool(ID_MapFrameSel, mode);
      toolBar->EnableTool(ID_LineMeter, mode);
      toolBar->EnableTool(ID_PolygonMeter, mode);
    }
}

void MyFrame::EnableDrawTools()
{
//
// Enabling / Disabling the Drawing tools
//
  bool mode = false;
  bool mode2 = false;
  bool mode3 = false;
  bool mode4 = false;
  bool mode5 = false;
  bool mode6 = false;
  if (ActiveLayer)
    {
      if (ActiveLayer->GetType() == VECTOR_LAYER
          && ActiveLayer->IsEditingEnabled() == true)
        {
          mode = true;
          mode5 = true;
          if (ActiveLayer->GetGeometryType() == LAYER_LINESTRING ||
              ActiveLayer->GetGeometryType() == LAYER_POLYGON)
            mode2 = true;
          if (ActiveLayer->GetGeometryType() == LAYER_LINESTRING)
            mode3 = true;
          if (ActiveLayer->GetGeometryType() == LAYER_POLYGON ||
              ActiveLayer->IsMultiType() == true)
            mode4 = true;
          if (ActiveLayer->GetGeometryType() == LAYER_POINT)
            mode5 = false;
          if (ActiveLayer->IsMultiType() == true)
            mode6 = true;
        }
    }
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (menuBar)
    {
      menuBar->Enable(ID_Draw, mode);
      menuBar->Enable(ID_DrawInterpolate, mode2);
      menuBar->Enable(ID_DrawDelete, mode5);
      menuBar->Enable(ID_DrawMove, mode);
      menuBar->Enable(ID_DrawDeleteSubGeom, mode6);
      menuBar->Enable(ID_DrawSplitLine, mode3);
      menuBar->Enable(ID_DrawSelectMultiGeom, mode4);
    }
  if (toolBar)
    {
      toolBar->EnableTool(ID_Draw, mode);
      toolBar->EnableTool(ID_DrawInterpolate, mode2);
      toolBar->EnableTool(ID_DrawDelete, mode5);
      toolBar->EnableTool(ID_DrawMove, mode);
      toolBar->EnableTool(ID_DrawDeleteSubGeom, mode6);
      toolBar->EnableTool(ID_DrawSplitLine, mode3);
      toolBar->EnableTool(ID_DrawSelectMultiGeom, mode4);
    }
  CurrentDrawMode = DRAW_MODE_NONE;
}

void MyFrame::OnProjectCrs(wxCommandEvent & WXUNUSED(event))
{
//
// setting the Project Reference System
//
  ProjectCrsDialog dlg;
  dlg.Create(this, GetProjectCrs(), GetProjectName());
  int ret = dlg.ShowModal();
  if (ret == wxID_OK)
    {
      UpdateProjectDefs();
      LayerTree->SetChanged();
      RefreshMap();
    }
}

void MyFrame::OnLoadShp(wxCommandEvent & WXUNUSED(event))
{
//
// loading a shapefile
//
  int ret;
  wxString table;
  wxString column = wxT("Geometry");
  wxString charset;
  int srid = ProjectSrid.GetSrid();
  bool coerce2D;
  bool compressed;
  wxString path;
  wxString lastDir;
  wxFileDialog fileDialog(this, wxT("Load Shapefile"),
                          wxT(""),
                          wxT("shapefile.shp"),
                          wxT("Shapefile (*.shp)|*.shp|All files (*.*)|*.*"),
                          wxFD_OPEN | wxFD_FILE_MUST_EXIST,
                          wxDefaultPosition, wxDefaultSize, wxT("filedlg"));
  lastDir = GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      table = file.GetName();
      path = file.GetPath();
      path += file.GetPathSeparator();
      path += file.GetName();
      LoadShpDialog dlg;
      dlg.Create(this, path, table, srid, column, LocaleCharset);
      ret = dlg.ShowModal();
      if (ret == wxID_OK)
        {
          SetLastDirectory(lastDir);
          table = dlg.GetTable();
          srid = dlg.GetSrid();
          column = dlg.GetColumn();
          charset = dlg.GetCharset();
          coerce2D = dlg.ApplyCoertion2D();
          compressed = dlg.ApplyCompression();
          LoadShapefile(path, table, srid, column, charset, coerce2D,
                        compressed);
        }
    }
}

void MyFrame::OnTableAdd(wxCommandEvent & WXUNUSED(event))
{
//
// creating a new spatial table
//
  CreateTableDialog dlg;
  dlg.Create(this, ProjectSrid.GetSrid());
  dlg.ShowModal();
}

void MyFrame::OnSrids(wxCommandEvent & WXUNUSED(event))
{
//
// searching a SRID by name
//
  SearchSridDialog dlg;
  dlg.Create(this);
  dlg.ShowModal();
}

void MyFrame::OnCharset(wxCommandEvent & WXUNUSED(event))
{
//
// setting the default CHARSET
//
  DefaultCharsetDialog dlg;
  int ret;
  dlg.Create(this, DefaultCharset, AskCharset);
  ret = dlg.ShowModal();
  if (ret == wxID_OK)
    {
      DefaultCharset = dlg.GetCharset();
      AskCharset = dlg.IsSetAskCharset();
    }
}

void MyFrame::OnTimerAutoSave(wxTimerEvent & WXUNUSED(event))
{
//
// AutoSave - Timer event handler
// 
  int tc = sqlite3_total_changes(SqliteHandle);
  if (tc != LastTotalChanges)
    MemoryDbSave();
  if (AutoSaveInterval <= 0)
    {
      if (TimerAutoSave)
        {
          TimerAutoSave->Stop();
          delete TimerAutoSave;
          TimerAutoSave = NULL;
        }
  } else
    TimerAutoSave->Start(AutoSaveInterval * 1000, wxTIMER_ONE_SHOT);
}

void MyFrame::OnOutputMap(wxCommandEvent & WXUNUSED(event))
{
//
// Output Map
//
  double minX;
  double minY;
  double maxX;
  double maxY;
  int format;
  OutputMapDialog dlg;
  if (MapView->GetMapFrameSelection(&minX, &minY, &maxX, &maxY) == false)
    return;
  dlg.Create(this, minX, minY, maxX, maxY);
  int ret = dlg.ShowModal();
  if (ret == wxID_OK)
    {
      MapLayersList *layers = new MapLayersList();
      if (dlg.IsSvg() == true || dlg.IsPdf() == true)
        {
          LayerTree->BuildLayersList(layers);
          MyImageList symbols;
          MyImageList patterns;
          GetSymbolBitmaps(&symbols);
          GetPatternBitmaps(&patterns);
          layers->CreateGraphicResources(&symbols, &patterns);
      } else
        UpdateLayersList(layers, true);
      if (dlg.IsSvg() == true)
        {
          MyMapOutput extractor(this, layers, dlg.GetWidth(), dlg.GetHeight(),
                                minX, minY, maxX, maxY);
          extractor.OutputSvgMap();
      } else if (dlg.IsPdf() == true)
        {
          MyMapOutput extractor(this, layers, dlg.GetWidth(), dlg.GetHeight(),
                                minX, minY, maxX, maxY, dlg.IsPdfA3(),
                                dlg.IsPdfLandscape(), dlg.GetPdfDpi());
          extractor.OutputPdfMap();
      } else if (dlg.IsCopyToClipboard() == true)
        {
          MyMapOutput extractor(this, layers, dlg.GetWidth(), dlg.GetHeight(),
                                minX, minY, maxX, maxY,
                                dlg.GetBackgroundColor());
          extractor.OutputRasterMap();
      } else
        {
          format = wxBITMAP_TYPE_JPEG;
          if (dlg.IsPng() == true)
            format = wxBITMAP_TYPE_PNG;
          if (dlg.IsTiff() == true)
            format = wxBITMAP_TYPE_TIF;
          MyMapOutput extractor(this, layers, dlg.GetWidth(), dlg.GetHeight(),
                                format, minX, minY, maxX, maxY,
                                dlg.GetBackgroundColor(), dlg.IsWorldFile());
          extractor.OutputRasterMap();
        }
    }
}

void MyFrame::OnMapFrameFullExtent(wxCommandEvent & WXUNUSED(event))
{
//
// setting Map Frame to Full Extent
//
  MapView->SetMapFrameFullExtent();
}

void MyFrame::OnMapFrameSelection(wxCommandEvent & WXUNUSED(event))
{
//
// starting a Map Frame selection
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_MAP_FRAME)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, true);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, true);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_MAP_FRAME;
      MapView->UnsetMapFrameSelection();
      MapView->DynamicDraw(false);
      EnableMapOutput();
    }
}

void MyFrame::OnLineMeter(wxCommandEvent & WXUNUSED(event))
{
//
// starting a Measure Length
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_LN_METER)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, true);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, true);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_LN_METER;
    }
}

void MyFrame::OnPolygonMeter(wxCommandEvent & WXUNUSED(event))
{
//
// starting a Measure Area
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_PG_METER)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, true);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, true);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_PG_METER;
    }
}

void MyFrame::OnDraw(wxCommandEvent & WXUNUSED(event))
{
//
// Draw Mode
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_DRAW)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, true);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, true);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_DRAW;
    }
  MapView->ResetDynamics();
}

void MyFrame::OnDrawInterpolate(wxCommandEvent & WXUNUSED(event))
{
//
// Interpolate Vertex Mode
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_INTERPOLATE)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, true);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, true);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_INTERPOLATE;
    }
  MapView->ResetDynamics();
}

void MyFrame::OnDrawDelete(wxCommandEvent & WXUNUSED(event))
{
//
//Delete Vertex Mode
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_DELETE)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, true);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, true);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_DELETE;
    }
  MapView->ResetDynamics();
}

void MyFrame::OnDrawMove(wxCommandEvent & WXUNUSED(event))
{
//
// Move Vertex Mode
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_MOVE)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, true);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, true);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_MOVE;
    }
  MapView->ResetDynamics();
}

void MyFrame::OnDrawDeleteSubGeom(wxCommandEvent & WXUNUSED(event))
{
//
// Delete SubGeometry Mode
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_DELETE_SUB)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, true);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, true);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_DELETE_SUB;
    }
  MapView->ResetDynamics();
}

void MyFrame::OnDrawSplitLine(wxCommandEvent & WXUNUSED(event))
{
//
// Split Line Mode
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_SPLIT)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, true);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, true);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_SPLIT;
    }
  MapView->ResetDynamics();
}

void MyFrame::OnDrawSelectMultiGeom(wxCommandEvent & WXUNUSED(event))
{
//
// Select Current Complex Geometry Mode
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (CurrentDrawMode == DRAW_MODE_SELECT)
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, false);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
        }
      CurrentDrawMode = DRAW_MODE_NONE;
  } else
    {
      if (menuBar)
        {
          menuBar->Check(ID_MapFrameSel, false);
          menuBar->Check(ID_LineMeter, false);
          menuBar->Check(ID_PolygonMeter, false);
          menuBar->Check(ID_Draw, false);
          menuBar->Check(ID_DrawInterpolate, false);
          menuBar->Check(ID_DrawDelete, false);
          menuBar->Check(ID_DrawMove, false);
          menuBar->Check(ID_DrawDeleteSubGeom, false);
          menuBar->Check(ID_DrawSplitLine, false);
          menuBar->Check(ID_DrawSelectMultiGeom, true);
        }
      if (toolBar)
        {
          toolBar->ToggleTool(ID_MapFrameSel, false);
          toolBar->ToggleTool(ID_LineMeter, false);
          toolBar->ToggleTool(ID_PolygonMeter, false);
          toolBar->ToggleTool(ID_Draw, false);
          toolBar->ToggleTool(ID_DrawInterpolate, false);
          toolBar->ToggleTool(ID_DrawDelete, false);
          toolBar->ToggleTool(ID_DrawMove, false);
          toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
          toolBar->ToggleTool(ID_DrawSplitLine, false);
          toolBar->ToggleTool(ID_DrawSelectMultiGeom, true);
        }
      MapView->UnsetMultiGeometry();
      CurrentDrawMode = DRAW_MODE_SELECT;
    }
  MapView->ResetDynamics();
}

void MyFrame::ClearLayerTree()
{
// resets the layer TREE list to the empty state
  wxString path = wxT("no current DB");
  LayerTree->SetPath(path);
  LayerTree->Show(false);
  LayerTree->FlushAll();
  LayerTree->Show(true);
}

void MyFrame::UpdateLayersList(MapLayersList * list, bool force)
{
// updating the Map Layers List
  if (LayerTree->IsChanged() == true || force == true)
    {
      MyImageList symbols;
      MyImageList patterns;
      LayerTree->BuildLayersList(list);
      GetSymbolBitmaps(&symbols);
      GetPatternBitmaps(&patterns);
      list->SetGraphicResources(&symbols, &patterns);
    }
}

void MyFrame::ProjectSridChanged()
{
//
// the Project's SRID is changed
//
  if (ProjectSrid.GetSrid() != LastSrid)
    {
      if (MapView->IsValidMapExtent() == true)
        {
          MapView->ComputeMapExtent();
          if (MapView->IsValidMapFrame() == false)
            MapView->SetFrameFullExtent();
          else
            MapView->UpdateFrameExtent(LastSrid, LastGeographic);
          MapView->PrepareMap();
        }
    }
  LastSrid = ProjectSrid.GetSrid();
  LastGeographic = ProjectSrid.IsGeographic();
}

void MyFrame::ConvertString(wxString & str, char *buf, int *len)
{
  strcpy(buf, str.ToUTF8());
  *len = strlen(buf);
}

void MyFrame::ReplaceDecimalComma(wxString & str)
{
  int i;
  char buf[1024];
  strcpy(buf, str.ToUTF8());
  for (i = 0; i < (int) strlen(buf); i++)
    {
      if (buf[i] == ',')
        buf[i] = '.';
    }
  str = wxString::FromUTF8(buf);
}

void MyFrame::ColorFromRGBA(char *buf, wxColour & color)
{
  int i;
  int digit;
  int red = 255;
  int green = 255;
  int blue = 255;
  int alpha = 255;
  if (strlen(buf) != 8)
    goto end;
  for (i = 0; i < 8; i += 2)
    {
      switch (buf[i])
        {
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            digit = (buf[i] - '0') * 16;
            break;
          case 'a':
          case 'b':
          case 'c':
          case 'd':
          case 'e':
          case 'f':
            digit = (10 + (buf[i] - 'a')) * 16;
            break;
          case 'A':
          case 'B':
          case 'C':
          case 'D':
          case 'E':
          case 'F':
            digit = (10 + (buf[i] - 'A')) * 16;
            break;
          default:
            digit = 0;
            break;
        };
      switch (buf[i + 1])
        {
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            digit += buf[i + 1] - '0';
            break;
          case 'a':
          case 'b':
          case 'c':
          case 'd':
          case 'e':
          case 'f':
            digit += 10 + (buf[i + 1] - 'a');
            break;
          case 'A':
          case 'B':
          case 'C':
          case 'D':
          case 'E':
          case 'F':
            digit += 10 + (buf[i + 1] - 'A');
            break;
        };
      if (i == 0)
        red = digit;
      if (i == 2)
        green = digit;
      if (i == 4)
        blue = digit;
      if (i == 6)
        alpha = digit;
    }
end:
  color = wxColour(red, green, blue, alpha);
}

int MyFrame::ColumnTypeFromConstant(char *buf)
{
  if (strcasecmp(buf, "INTEGER") == 0)
    return SQLITE_INTEGER;
  if (strcasecmp(buf, "DOUBLE") == 0)
    return SQLITE_FLOAT;
  if (strcasecmp(buf, "TEXT") == 0)
    return SQLITE_TEXT;
  if (strcasecmp(buf, "DATE") == 0)
    return SQLITE_DATE;
  if (strcasecmp(buf, "DATETIME") == 0)
    return SQLITE_DATETIME;
  if (strcasecmp(buf, "BOOLEAN") == 0)
    return SQLITE_BOOLEAN;
  if (strcasecmp(buf, "IMAGE") == 0)
    return SQLITE_IMAGE;
  if (strcasecmp(buf, "BLOB") == 0)
    return SQLITE_BLOB;
  return SQLITE_TEXT;
}

int MyFrame::LineStyleFromConstant(char *buf)
{
  if (strcasecmp(buf, "DOT") == 0)
    return wxDOT;
  if (strcasecmp(buf, "SHORT_DASH") == 0)
    return wxSHORT_DASH;
  if (strcasecmp(buf, "LONG_DASH") == 0)
    return wxLONG_DASH;
  if (strcasecmp(buf, "DOT_DASH") == 0)
    return wxDOT_DASH;
  return wxSOLID;
}

int MyFrame::SymbolTypeFromConstant(char *buf)
{
  if (strcasecmp(buf, "SQUARE") == 0)
    return CLASSES_SYMBOL_SQUARE;
  if (strcasecmp(buf, "DIAMOND") == 0)
    return CLASSES_SYMBOL_DIAMOND;
  return CLASSES_SYMBOL_CIRCLE;
}

void MyFrame::GetRandomColor(int *red, int *green, int *blue)
{
// generating a random color value [0/255]
  *red = rand() % 256;
  *green = rand() % 256;
  *blue = rand() % 256;
}

void MyFrame::GetRandomColorMedium(int *red, int *green, int *blue)
{
/// generating a random color value [128/255]
  *red = (rand() % 128) + 128;
  *green = (rand() % 128) + 128;
  *blue = (rand() % 128) + 128;
}

void MyFrame::GetRandomColorLight(int *red, int *green, int *blue)
{
// generating a random color value [192/255]
  *red = (rand() % 64) + 192;
  *green = (rand() % 64) + 192;
  *blue = (rand() % 64) + 192;
}

void MyFrame::GetRandomColorSature(int *red, int *green, int *blue)
{
// generating a random color value [sature]
  wxColour colors[38];
  colors[0] = wxColour(255, 0, 0);
  colors[1] = wxColour(0, 255, 0);
  colors[2] = wxColour(0, 0, 255);
  colors[3] = wxColour(255, 255, 0);
  colors[4] = wxColour(255, 0, 255);
  colors[5] = wxColour(0, 255, 255);
  colors[6] = wxColour(192, 0, 0);
  colors[7] = wxColour(0, 192, 0);
  colors[8] = wxColour(0, 0, 192);
  colors[9] = wxColour(255, 192, 0);
  colors[10] = wxColour(192, 255, 0);
  colors[11] = wxColour(192, 192, 0);
  colors[12] = wxColour(255, 0, 192);
  colors[13] = wxColour(192, 0, 255);
  colors[14] = wxColour(192, 0, 192);
  colors[15] = wxColour(0, 255, 192);
  colors[16] = wxColour(0, 192, 255);
  colors[17] = wxColour(0, 192, 192);
  colors[18] = wxColour(128, 0, 0);
  colors[19] = wxColour(0, 128, 0);
  colors[20] = wxColour(0, 0, 128);
  colors[21] = wxColour(128, 255, 0);
  colors[22] = wxColour(128, 192, 0);
  colors[23] = wxColour(255, 128, 0);
  colors[24] = wxColour(192, 128, 0);
  colors[25] = wxColour(128, 128, 0);
  colors[26] = wxColour(128, 0, 255);
  colors[27] = wxColour(128, 0, 192);
  colors[28] = wxColour(255, 0, 128);
  colors[29] = wxColour(192, 0, 128);
  colors[30] = wxColour(128, 0, 128);
  colors[31] = wxColour(0, 128, 255);
  colors[32] = wxColour(0, 128, 192);
  colors[33] = wxColour(0, 255, 128);
  colors[34] = wxColour(0, 192, 128);
  colors[35] = wxColour(0, 128, 128);
  colors[36] = wxColour(192, 192, 192);
  colors[37] = wxColour(128, 128, 128);
  int index = rand() % 38;
  *red = colors[index].Red();
  *green = colors[index].Green();
  *blue = colors[index].Blue();
}

int MyFrame::GetCharsetIndex(wxString & charset)
{
// identifies the INDEX for a given charset
  int i;
  for (i = 0; i < CharsetsLen; i++)
    {
      if (*(Charsets + i) == charset)
        return i;
    }
  return wxNOT_FOUND;
}

wxString & MyFrame::GetCharsetName(wxString & charset)
{
// identifies the full name for a given charset code
  int i;
  for (i = 0; i < CharsetsLen; i++)
    {
      if (*(Charsets + i) == charset)
        return *(CharsetsNames + i);
    }
  return charset;
}

bool MyFrame::ConvertToJulianDate(char *date, double *julian)
{
//
// trying to convert an 'YYYY-MM-DD' date into a JulianDate [double] 
//
  char dummy[8];
  int year;
  int month;
  int day;
  int Y;
  int M;
  int D;
  int A;
  int B;
  int X1;
  int X2;
  if (strlen(date) != 10)
    return false;
  if (date[4] != '-')
    return false;
  if (date[7] != '-')
    return false;
  if (date[0] >= '0' && date[0] <= '9')
    ;
  else
    return false;
  if (date[1] >= '0' && date[1] <= '9')
    ;
  else
    return false;
  if (date[2] >= '0' && date[2] <= '9')
    ;
  else
    return false;
  if (date[3] >= '0' && date[3] <= '9')
    ;
  else
    return false;
  if (date[5] >= '0' && date[5] <= '9')
    ;
  else
    return false;
  if (date[6] >= '0' && date[6] <= '9')
    ;
  else
    return false;
  if (date[8] >= '0' && date[8] <= '9')
    ;
  else
    return false;
  if (date[9] >= '0' && date[9] <= '9')
    ;
  else
    return false;
  dummy[0] = date[0];
  dummy[1] = date[1];
  dummy[2] = date[2];
  dummy[3] = date[3];
  dummy[4] = '\0';
  year = atoi(dummy);
  dummy[0] = date[5];
  dummy[1] = date[6];
  dummy[2] = '\0';
  month = atoi(dummy);
  dummy[0] = date[8];
  dummy[1] = date[9];
  dummy[2] = '\0';
  day = atoi(dummy);
  if (year < 1900 || year > 2400)
    return false;
  if (month < 1 || month > 12)
    return false;
  if (day < 1)
    return false;
  switch (month)
    {
      case 2:
        if ((year / 4) == 0)
          {
            if (day > 29)
              return 0;
        } else
          {
            if (day > 28)
              return false;
          }
        break;
      case 4:
      case 6:
      case 9:
      case 11:
        if (day > 30)
          return false;
        break;
      default:
        if (day > 31)
          return false;
    };
// computing the Julian date
  Y = year;
  M = month;
  D = day;
  if (M <= 2)
    {
      Y--;
      M += 12;
    }
  A = Y / 100;
  B = 2 - A + (A / 4);
  X1 = 36525 * (Y + 4716) / 100;
  X2 = 306001 * (M + 1) / 10000;
  *julian = (double) (X1 + X2 + D + B - 1524.5);
  return true;
}

bool MyFrame::ConvertToJulianDateTime(char *date, double *julian)
{
//
// trying to convert an 'YYYY-MM-DD HH:MM:SS.SSS' date into a JulianDate [double] 
//
  double preJulian;
  char dummy[16];
  int hh = -1;
  int mm = -1;
  int ss = -1;
  int cc = -1;
  if (strlen(date) == 10)
    {
      if (ConvertToJulianDate(date, &preJulian) == false)
        return false;
      *julian = preJulian;
      return true;
    }
  if (strlen(date) == 16)
    {
      memcpy(dummy, date, 10);
      dummy[10] = '\0';
      if (ConvertToJulianDate(dummy, &preJulian) == false)
        return false;
  } else if (strlen(date) == 19)
    {
      memcpy(dummy, date, 10);
      dummy[10] = '\0';
      if (ConvertToJulianDate(dummy, &preJulian) == false)
        return false;
  } else if (strlen(date) == 23)
    {
      memcpy(dummy, date, 10);
      dummy[10] = '\0';
      if (ConvertToJulianDate(dummy, &preJulian) == false)
        return false;
  } else
    return false;
  if (date[10] != ' ')
    return false;
  if (date[11] >= '0' && date[11] <= '9')
    ;
  else
    return false;
  if (date[12] >= '0' && date[12] <= '9')
    ;
  else
    return false;
  if (date[13] != ':')
    return false;
  if (date[14] >= '0' && date[14] <= '9')
    ;
  else
    return false;
  if (date[15] >= '0' && date[15] <= '9')
    ;
  else
    return false;
  dummy[0] = date[11];
  dummy[1] = date[12];
  dummy[2] = '\0';
  hh = atoi(dummy);
  dummy[0] = date[14];
  dummy[1] = date[15];
  dummy[2] = '\0';
  mm = atoi(dummy);
  ss = 0;
  cc = 0;
  if (strlen(date) >= 19)
    {
      if (date[16] != ':')
        return false;
      if (date[17] >= '0' && date[17] <= '9')
        ;
      else
        return false;
      if (date[18] >= '0' && date[18] <= '9')
        ;
      else
        return false;
      dummy[0] = date[17];
      dummy[1] = date[18];
      dummy[2] = '\0';
      ss = atoi(dummy);
    }
  if (strlen(date) == 23)
    {
      if (date[19] != '.')
        return false;
      if (date[20] >= '0' && date[20] <= '9')
        ;
      else
        return false;
      if (date[21] >= '0' && date[21] <= '9')
        ;
      else
        return false;
      if (date[22] >= '0' && date[22] <= '9')
        ;
      else
        return false;
      dummy[0] = date[20];
      dummy[1] = date[21];
      dummy[2] = date[22];
      dummy[3] = '\0';
      cc = atoi(dummy);
    }
  if (hh < 0 || hh > 23)
    return false;
  if (mm < 0 || mm > 59)
    return false;
  if (ss < 0 || ss > 59)
    return false;
  if (cc < 0 || cc > 999)
    return false;
  preJulian += (hh * 3600000.0 + mm * 60000.0 + ss * 1000.0) / 86400000.0;
  *julian = preJulian;
  return true;
}

void MyFrame::ConvertFromJulianDate(double julian, char *date)
{
//
// formats an 'YYYY-MM-DD' date from a Julian data [double]
//
  int year;
  int month;
  int day;
  int Z;
  int A;
  int B;
  int C;
  int D;
  int E;
  int X1;
  sqlite3_int64 mulJulian = (sqlite_int64) (julian * 86400000.0);
  Z = (int) ((mulJulian + 43200000) / 86400000);
  A = (int) ((Z - 1867216.25) / 36524.25);
  A = Z + 1 + A - (A / 4);
  B = A + 1524;
  C = (int) ((B - 122.1) / 365.25);
  D = (36525 * C) / 100;
  E = (int) ((B - D) / 30.6001);
  X1 = (int) (30.6001 * E);
  day = B - D - X1;
  month = E < 14 ? E - 1 : E - 13;
  year = month > 2 ? C - 4716 : C - 4715;
  sprintf(date, "%04d-%02d-%02d", year, month, day);
}

void MyFrame::ConvertFromJulianDateTime(double julian, char *date)
{
//
// formats an 'YYYY-MM-DD HH:MM:SS' date from a Julian data [double]
//
  int s;
  int hh;
  int mm;
  double ss;
  char dummy[64];
  sqlite3_int64 mulJulian = (sqlite_int64) (julian * 86400000.0);
  ConvertFromJulianDate(julian, date);
  s = (int) ((mulJulian + 43200000) % 86400000);
  ss = s / 1000.0;
  s = (int) ss;
  ss -= s;
  hh = s / 3600;
  s -= hh * 3600;
  mm = s / 60;
  ss += s - mm * 60;
  s = (int) ss;
  sprintf(dummy, " %02d:%02d:%02d", hh, mm, s);
  strcat(date, dummy);
}

bool MyFrame::FormatBoolean(wxString & value, bool * bool_value)
{
//
// trying to convert a generic BOOL value into a true BOOL
//
  if (value.CmpNoCase(wxT("true")) == true)
    {
      *bool_value = true;
      return true;
    }
  if (value.CmpNoCase(wxT("false")) == true)
    {
      *bool_value = false;
      return true;
    }
  if (value.CmpNoCase(wxT("yes")) == true)
    {
      *bool_value = true;
      return true;
    }
  if (value.CmpNoCase(wxT("no")) == true)
    {
      *bool_value = false;
      return true;
    }
  if (value.CmpNoCase(wxT("y")) == true)
    {
      *bool_value = true;
      return true;
    }
  if (value.CmpNoCase(wxT("n")) == true)
    {
      *bool_value = false;
      return true;
    }
  if (value.CmpNoCase(wxT("1")) == true)
    {
      *bool_value = true;
      return true;
    }
  if (value.CmpNoCase(wxT("0")) == true)
    {
      *bool_value = false;
      return true;
    }
  return false;
}

bool MyFrame::IsMapFrameSelectionEnabled()
{
// returns the current Enabled state for the MapFrame tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_MapFrameSel);
  return false;
}

bool MyFrame::IsMeasureLineEnabled()
{
// returns the current Enabled state for the MeasureLine tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_LineMeter);
  return false;
}

bool MyFrame::IsMeasurePolygonEnabled()
{
// returns the current Enabled state for the MeasurePolygon tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_PolygonMeter);
  return false;
}

bool MyFrame::IsPencilEnabled()
{
// returns the current Enabled state for the Pencil tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_Draw);
  return false;
}

bool MyFrame::IsPencilAddEnabled()
{
// returns the current Enabled state for the PencilAdd tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_DrawInterpolate);
  return false;
}

bool MyFrame::IsPencilDeleteEnabled()
{
// returns the current Enabled state for the PencilDelete tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_DrawDelete);
  return false;
}

bool MyFrame::IsPencilGoEnabled()
{
// returns the current Enabled state for the PencilGo tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_DrawMove);
  return false;
}

bool MyFrame::IsCutRedEnabled()
{
// returns the current Enabled state for the CutRed tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_DrawDeleteSubGeom);
  return false;
}

bool MyFrame::IsCutBlueEnabled()
{
// returns the current Enabled state for the CutBlue tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_DrawSplitLine);
  return false;
}

bool MyFrame::IsAsteriskEnabled()
{
// returns the current Enabled state for the Asterisk tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolEnabled(ID_DrawSelectMultiGeom);
  return false;
}

bool MyFrame::IsMapFrameSelectionChecked()
{
// returns the current Checked state for the MapFrame tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_MapFrameSel);
  return false;
}

bool MyFrame::IsMeasureLineChecked()
{
// returns the current Checked state for the MeasureLine tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_LineMeter);
  return false;
}

bool MyFrame::IsMeasurePolygonChecked()
{
// returns the current Checked state for the MeasurePolygon tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_PolygonMeter);
  return false;
}

bool MyFrame::IsPencilChecked()
{
// returns the current Checked state for the Pencil tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_Draw);
  return false;
}

bool MyFrame::IsPencilAddChecked()
{
// returns the current Checked state for the PencilAdd tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_DrawInterpolate);
  return false;
}

bool MyFrame::IsPencilDeleteChecked()
{
// returns the current Checked state for the PencilDelete tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_DrawDelete);
  return false;
}

bool MyFrame::IsPencilGoChecked()
{
// returns the current Checked state for the PencilGo tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_DrawMove);
  return false;
}

bool MyFrame::IsCutRedChecked()
{
// returns the current Checked state for the CutRed tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_DrawDeleteSubGeom);
  return false;
}

bool MyFrame::IsCutBlueChecked()
{
// returns the current Checked state for the CutBlue tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_DrawSplitLine);
  return false;
}

bool MyFrame::IsAsteriskChecked()
{
// returns the current Checked state for the Asterisk tool
  wxToolBar *toolBar = GetToolBar();
  if (toolBar)
    return toolBar->GetToolState(ID_DrawSelectMultiGeom);
  return false;
}

bool MyFrame::IsAnyDrawModeActive()
{
// checks if any Draw mode is currently active
  if (IsMeasureLineChecked() == true)
    return true;
  if (IsMeasurePolygonChecked() == true)
    return true;
  if (IsPencilChecked() == true)
    return true;
  if (IsPencilAddChecked() == true)
    return true;
  if (IsPencilDeleteChecked() == true)
    return true;
  if (IsPencilGoChecked() == true)
    return true;
  if (IsCutRedChecked() == true)
    return true;
  if (IsCutBlueChecked() == true)
    return true;
  if (IsAsteriskChecked() == true)
    return true;
  return false;
}

bool MyFrame::IsDrawActive()
{
// checks if some Draw mode is currently active
  if (IsMeasureLineChecked() == true)
    return true;
  if (IsMeasurePolygonChecked() == true)
    return true;
  if (IsPencilChecked() == true)
    return true;
  return false;
}

bool MyFrame::IsDrawPointActive()
{
// checks if Point Draw mode is currently active
  if (!ActiveLayer)
    return false;
  if (ActiveLayer->GetType() == VECTOR_LAYER
      && ActiveLayer->GetGeometryType() == LAYER_POINT)
    {
      if (IsPencilChecked() == true)
        return true;
    }
  return false;
}

bool MyFrame::IsDrawLineActive()
{
// checks if Line Draw mode is currently active
  if (IsMeasureLineChecked() == true)
    return true;
  if (!ActiveLayer)
    return false;
  if (ActiveLayer->GetType() == VECTOR_LAYER
      && ActiveLayer->GetGeometryType() == LAYER_LINESTRING)
    {
      if (IsPencilChecked() == true)
        return true;
    }
  return false;
}

bool MyFrame::IsDrawRingActive()
{
// checks if Ring Draw mode is currently active
  if (IsMeasurePolygonChecked() == true)
    return true;
  if (!ActiveLayer)
    return false;
  if (ActiveLayer->GetType() == VECTOR_LAYER
      && ActiveLayer->GetGeometryType() == LAYER_POLYGON)
    {
      if (IsPencilChecked() == true)
        return true;
    }
  return false;
}

bool MyFrame::IsSelectMultiGeomActive()
{
// checks if Select Complex Geometry mode is currently active
  if (!ActiveLayer)
    return false;
  if (ActiveLayer->GetType() == VECTOR_LAYER
      && (ActiveLayer->GetGeometryType() == LAYER_POLYGON ||
          ActiveLayer->IsMultiType() == true))
    {
      if (IsAsteriskChecked() == true)
        return true;
    }
  return false;
}

void MyFrame::EnableMapOutput()
{
//
// enables/disables Map Output
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (menuBar)
    menuBar->Enable(ID_OutputMap, MapView->IsMapFrameSelection());
  if (toolBar)
    toolBar->EnableTool(ID_OutputMap, MapView->IsMapFrameSelection());
}

void MyFrame::UnsetMeterTools()
{
//
// uncheks the line and polygon meter tools
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (menuBar)
    {
      menuBar->Check(ID_MapFrameSel, false);
      menuBar->Check(ID_LineMeter, false);
      menuBar->Check(ID_PolygonMeter, false);
    }
  if (toolBar)
    {
      toolBar->ToggleTool(ID_MapFrameSel, false);
      toolBar->ToggleTool(ID_LineMeter, false);
      toolBar->ToggleTool(ID_PolygonMeter, false);
    }
  CurrentDrawMode = DRAW_MODE_NONE;
}

void MyFrame::UnsetDrawTools()
{
//
// uncheks the draw tools
//
  wxMenuBar *menuBar = GetMenuBar();
  wxToolBar *toolBar = GetToolBar();
  if (menuBar)
    {
      menuBar->Check(ID_Draw, false);
      menuBar->Check(ID_DrawInterpolate, false);
      menuBar->Check(ID_DrawDelete, false);
      menuBar->Check(ID_DrawMove, false);
      menuBar->Check(ID_DrawDeleteSubGeom, false);
      menuBar->Check(ID_DrawSplitLine, false);
      menuBar->Check(ID_DrawSelectMultiGeom, false);
    }
  if (toolBar)
    {
      toolBar->ToggleTool(ID_Draw, false);
      toolBar->ToggleTool(ID_DrawInterpolate, false);
      toolBar->ToggleTool(ID_DrawDelete, false);
      toolBar->ToggleTool(ID_DrawMove, false);
      toolBar->ToggleTool(ID_DrawDeleteSubGeom, false);
      toolBar->ToggleTool(ID_DrawSplitLine, false);
      toolBar->ToggleTool(ID_DrawSelectMultiGeom, false);
    }
  CurrentDrawMode = DRAW_MODE_NONE;
}

void MyFrame::SetCurrentEntity(IdentifyEntity * ptr)
{
//
// setting up the Current Entity
//
  int iv;
  int ib;
  double x;
  double y;
  double z;
  double m;
  gaiaGeomCollPtr oldGeom;
  gaiaGeomCollPtr newGeom;
  gaiaPointPtr pt;
  gaiaLinestringPtr oldLn;
  gaiaLinestringPtr newLn;
  gaiaPolygonPtr oldPg;
  gaiaPolygonPtr newPg;
  gaiaRingPtr oldRng;
  gaiaRingPtr newRng;
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  OkCurrentEntity = false;
  CurrentEntityGeometry = NULL;
  CurrentEntityPrimaryKey = -1;
  if (ptr)
    {
      OkCurrentEntity = true;
      CurrentEntityPrimaryKey = ptr->GetRowId();
      // cloning the Geometry
      oldGeom = ptr->GetGeometry();
      if (oldGeom->DimensionModel == GAIA_XY_Z)
        newGeom = gaiaAllocGeomCollXYZ();
      else if (oldGeom->DimensionModel == GAIA_XY_M)
        newGeom = gaiaAllocGeomCollXYM();
      else if (oldGeom->DimensionModel == GAIA_XY_Z_M)
        newGeom = gaiaAllocGeomCollXYZM();
      else
        newGeom = gaiaAllocGeomColl();
      CurrentEntityGeometry = newGeom;
      newGeom->Srid = oldGeom->Srid;
      pt = oldGeom->FirstPoint;
      while (pt)
        {
          // cloning any Point
          if (oldGeom->DimensionModel == GAIA_XY_Z)
            gaiaAddPointToGeomCollXYZ(newGeom, pt->X, pt->Y, pt->Z);
          else if (oldGeom->DimensionModel == GAIA_XY_M)
            gaiaAddPointToGeomCollXYM(newGeom, pt->X, pt->Y, pt->M);
          else if (oldGeom->DimensionModel == GAIA_XY_Z_M)
            gaiaAddPointToGeomCollXYZM(newGeom, pt->X, pt->Y, pt->Z, pt->M);
          else
            gaiaAddPointToGeomColl(newGeom, pt->X, pt->Y);
          pt = pt->Next;
        }
      oldLn = oldGeom->FirstLinestring;
      while (oldLn)
        {
          // cloning any Linestring
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
          // cloning any Polygon
          oldRng = oldPg->Exterior;
          newPg =
            gaiaAddPolygonToGeomColl(newGeom, oldRng->Points,
                                     oldPg->NumInteriors);
          newRng = newPg->Exterior;
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
          for (ib = 0; ib < oldPg->NumInteriors; ib++)
            {
              // cloning any INTERIOR RING
              oldRng = oldPg->Interiors + ib;
              newRng = gaiaAddInteriorRing(newPg, ib, oldRng->Points);
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
    }
}

void MyFrame::SetCurrentEntity(sqlite3_int64 pk, gaiaGeomCollPtr geom)
{
//
// setting up the Current Entity
//
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  OkCurrentEntity = false;
  CurrentEntityGeometry = NULL;
  CurrentEntityPrimaryKey = -1;
  if (geom)
    {
      OkCurrentEntity = true;
      CurrentEntityPrimaryKey = pk;
      CurrentEntityGeometry = geom;
    }
}

bool MyFrame::IsValidInteriorRing(gaiaDynamicLinePtr draw,
                                  gaiaPolygonPtr * polyg)
{
//
// checks if the current ring may be a valid Interior Ring
//
  gaiaPointPtr pt;
  gaiaPolygonPtr pg;
  bool ext;
  if (!CurrentEntityGeometry)
    return false;
  if (!draw)
    return false;
  pg = CurrentEntityGeometry->FirstPolygon;
  while (pg)
    {
      ext = false;
      pt = draw->First;
      while (pt)
        {
          // checks if all vertices are internal points to this polygon
          if (gaiaIsPointOnRingSurface(pg->Exterior, pt->X, pt->Y) == 0)
            {
              ext = true;
              break;
            }
          pt = pt->Next;
        }
      if (ext == false)
        {
          *polyg = pg;
          return true;
        }
      pg = pg->Next;
    }
  return false;
}

void MyFrame::AddInteriorRing(gaiaDynamicLinePtr draw, int points,
                              gaiaPolygonPtr polyg)
{
//
// inserts an Interior Ring into the Current Entity Geometry
//
  int iv;
  int ib;
  int numInteriors;
  double x;
  double y;
  double z;
  double m;
  gaiaGeomCollPtr oldGeom = CurrentEntityGeometry;
  gaiaGeomCollPtr newGeom;
  gaiaPointPtr pt;
  gaiaLinestringPtr oldLn;
  gaiaLinestringPtr newLn;
  gaiaPolygonPtr oldPg;
  gaiaPolygonPtr newPg;
  gaiaRingPtr oldRng;
  gaiaRingPtr newRng;
  bool found = false;
  if (!oldGeom)
    return;
  if (!draw)
    return;
  oldPg = oldGeom->FirstPolygon;
  while (oldPg)
    {
      // test if the required Polygon exists
      if (oldPg == polyg)
        {
          found = true;
          break;
        }
      oldPg = oldPg->Next;
    }
  if (found == false)
    return;
// cloning the Geometry
  if (oldGeom->DimensionModel == GAIA_XY_Z)
    newGeom = gaiaAllocGeomCollXYZ();
  else if (oldGeom->DimensionModel == GAIA_XY_M)
    newGeom = gaiaAllocGeomCollXYM();
  else if (oldGeom->DimensionModel == GAIA_XY_Z_M)
    newGeom = gaiaAllocGeomCollXYZM();
  else
    newGeom = gaiaAllocGeomColl();
  newGeom->Srid = oldGeom->Srid;
  newGeom->DeclaredType = oldGeom->DeclaredType;
  pt = oldGeom->FirstPoint;
  while (pt)
    {
      // cloning any Point
      if (oldGeom->DimensionModel == GAIA_XY_Z)
        gaiaAddPointToGeomCollXYZ(newGeom, pt->X, pt->Y, pt->Z);
      else if (oldGeom->DimensionModel == GAIA_XY_M)
        gaiaAddPointToGeomCollXYM(newGeom, pt->X, pt->Y, pt->M);
      else if (oldGeom->DimensionModel == GAIA_XY_Z_M)
        gaiaAddPointToGeomCollXYZM(newGeom, pt->X, pt->Y, pt->Z, pt->M);
      else
        gaiaAddPointToGeomColl(newGeom, pt->X, pt->Y);
      pt = pt->Next;
    }
  oldLn = oldGeom->FirstLinestring;
  while (oldLn)
    {
      // cloning any Linestring
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
      // cloning any Polygon
      oldRng = oldPg->Exterior;
      numInteriors = oldPg->NumInteriors;
      if (oldPg == polyg)
        {
          // this one is the selected Polygon
          numInteriors++;
        }
      newPg = gaiaAddPolygonToGeomColl(newGeom, oldRng->Points, numInteriors);
      newRng = newPg->Exterior;
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
          if (newRng->DimensionModel == GAIA_XY_Z)
            {
              gaiaSetPointXYM(newRng->Coords, iv, x, y, z);
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
      for (ib = 0; ib < oldPg->NumInteriors; ib++)
        {
          // cloning any INTERIOR RING
          oldRng = oldPg->Interiors + ib;
          newRng = gaiaAddInteriorRing(newPg, ib, oldRng->Points);
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
              if (newRng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaSetPointXYM(newRng->Coords, iv, x, y, z);
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
      if (oldPg == polyg)
        {
          // adding the new Interior Ring
          newRng = gaiaAddInteriorRing(newPg, newPg->NumInteriors - 1, points);
          iv = 0;
          pt = draw->First;
          while (pt)
            {
              // copying Interior Ring's Vertices
              if (newRng->DimensionModel == GAIA_XY_Z)
                {
                  gaiaSetPointXYZ(newRng->Coords, iv, pt->X, pt->Y, 0.0);
              } else if (newRng->DimensionModel == GAIA_XY_M)
                {
                  gaiaSetPointXYM(newRng->Coords, iv, pt->X, pt->Y, 0.0);
              } else if (newRng->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaSetPointXYZM(newRng->Coords, iv, pt->X, pt->Y, 0.0, 0.0);
              } else
                {
                  gaiaSetPoint(newRng->Coords, iv, pt->X, pt->Y);
                }
              iv++;
              pt = pt->Next;
            }
          // inserting last vertex
          pt = draw->First;
          if (newRng->DimensionModel == GAIA_XY_Z)
            {
              gaiaSetPointXYZ(newRng->Coords, iv, pt->X, pt->Y, 0.0);
          } else if (newRng->DimensionModel == GAIA_XY_M)
            {
              gaiaSetPointXYM(newRng->Coords, iv, pt->X, pt->Y, 0.0);
          } else if (newRng->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaSetPointXYZM(newRng->Coords, iv, pt->X, pt->Y, 0.0, 0.0);
          } else
            {
              gaiaSetPoint(newRng->Coords, iv, pt->X, pt->Y);
            }
        }
      oldPg = oldPg->Next;
    }
  CurrentEntityGeometry = newGeom;
  gaiaFreeGeomColl(oldGeom);
  return;
}

gaiaGeomCollPtr MyFrame::CreateNewGeometry()
{
//
// creating a new Current Entity Geometry
//
  if (CurrentEntityGeometry)
    gaiaFreeGeomColl(CurrentEntityGeometry);
  CurrentEntityGeometry = gaiaAllocGeomColl();
  return CurrentEntityGeometry;
}

int MyFrame::GetActiveLayerDeclaredType()
{
//
// return the DeclaredType for the current Active Layer
//
  if (!ActiveLayer)
    return GAIA_UNKNOWN;
  if (ActiveLayer->GetGeometryType() == LAYER_POINT)
    {
      if (ActiveLayer->IsMultiType() == true)
        return GAIA_MULTIPOINT;
      else
        return GAIA_POINT;
    }
  if (ActiveLayer->GetGeometryType() == LAYER_LINESTRING)
    {
      if (ActiveLayer->IsMultiType() == true)
        return GAIA_MULTILINESTRING;
      else
        return GAIA_LINESTRING;
    }
  if (ActiveLayer->GetGeometryType() == LAYER_POLYGON)
    {
      if (ActiveLayer->IsMultiType() == true)
        return GAIA_MULTIPOLYGON;
      else
        return GAIA_POLYGON;
    }
  return GAIA_UNKNOWN;
}

void MyFrame::UpdateCurrentEntityGeometry()
{
//
// updating Geometry for the Current Entity
//
  wxString sql;
  char xSql[1024];
  unsigned char *blob;
  int blob_size;
  int len;
  sqlite3_stmt *stmt;
  int ret;
  sql = wxT("UPDATE \"");
  sql += ActiveLayer->GetTableName();
  sql += wxT("\" SET \"");
  sql += ActiveLayer->GetGeometryColumn();
  sql += wxT("\" = ? WHERE ROWID = ?");
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
// binding the Geometry column value
  gaiaToSpatiaLiteBlobWkb(CurrentEntityGeometry, &blob, &blob_size);
  sqlite3_bind_blob(stmt, 1, blob, blob_size, free);
// binding the Primary Key
  sqlite3_bind_int64(stmt, 2, CurrentEntityPrimaryKey);

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
stop:
  return;
}

void MyFrame::InsertNewEntity()
{
//
// inserting a new Entity
//
  InsertEntityDialog dlg;
  dlg.Create(MapView, this, ActiveLayer);
  dlg.ShowModal();
}

void MyFrame::FreeNetworkParams()
{
//
// destroying the Network access class
//
  if (NetParms)
    delete NetParms;
  NetParms = NULL;
}

bool MyFrame::CheckSvgGraphics()
{
//
// checking map graphics for SVG
//
  MapLayer *layer;
  MapSubClass *subClass;
  MapLayersList *list = new MapLayersList();
  LayerTree->BuildLayersList(list);
  UpdateLayersList(list, true);
  layer = list->GetFirst();
  while (layer)
    {
      if (layer->IsVisible() == false)
        {
          // skipping an hidden layer
          layer = layer->GetNext();
          continue;
        }
      if (layer->GetType() == VECTOR_LAYER)
        {
          if (layer->GetClassifyColumn().Len() > 0)
            {
              // using Sub-Classes
              subClass = layer->GetFirst();
              while (subClass)
                {
                  if (layer->GetGeometryType() == LAYER_POINT)
                    return false;
                  subClass = subClass->GetNext();
                }
          } else
            {
              // not using Sub-Classes
              if (layer->GetGeometryType() == LAYER_POINT)
                return false;
              if (layer->GetGeometryType() == LAYER_POLYGON)
                {
                  if (layer->IsToFill() == true)
                    {
                      if (layer->SolidFillingOk() == false)
                        return false;
                    }
                }
            }
        }
      layer = layer->GetNext();
    }
  return true;
}

bool MyFrame::CheckPdfGraphics()
{
//
// checking map graphics for PDF
//
  MapLayer *layer;
  MapSubClass *subClass;
  MapLayersList *list = new MapLayersList();
  LayerTree->BuildLayersList(list);
  UpdateLayersList(list, true);
  layer = list->GetFirst();
  while (layer)
    {
      if (layer->IsVisible() == false)
        {
          // skipping an hidden layer
          layer = layer->GetNext();
          continue;
        }
      if (layer->GetType() == VECTOR_LAYER)
        {
          if (layer->GetClassifyColumn().Len() > 0)
            {
              // using Sub-Classes
              subClass = layer->GetFirst();
              while (subClass)
                {
                  if (layer->GetGeometryType() == LAYER_POLYGON)
                    {
                      if (subClass->GetColor().Alpha() != 255)
                        return false;
                    }
                  subClass = subClass->GetNext();
                }
          } else
            {
              // not using Sub-Classes
              if (layer->GetGeometryType() == LAYER_LINESTRING)
                {
                  if (layer->GetLineColor().Alpha() != 255)
                    return true;
                }
              if (layer->GetGeometryType() == LAYER_POLYGON)
                {
                  if (layer->DrawBorderOk() == true)
                    {
                      if (layer->GetLineColor().Alpha() != 255)
                        return false;
                    }
                  if (layer->IsToFill() == true)
                    {
                      if (layer->SolidFillingOk() == true)
                        {
                          if (layer->GetFillColor().Alpha() != 255)
                            return false;
                      } else
                        return false;
                    }
                }
            }
        }
      layer = layer->GetNext();
    }
  return true;
}

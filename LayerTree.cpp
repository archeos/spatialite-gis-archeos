/*
/ LayerTree.cpp
/ tree control to hadle map layers
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
#include "wx/imaglist.h"

//
// ICONs in XPM format [universally portable]
//
#include "icons/db.xpm"
#include "icons/points_on.xpm"
#include "icons/linestrings_on.xpm"
#include "icons/polygons_on.xpm"
#include "icons/points_off.xpm"
#include "icons/linestrings_off.xpm"
#include "icons/polygons_off.xpm"
#include "icons/raster_on.xpm"
#include "icons/raster_off.xpm"
#include "icons/network_on.xpm"
#include "icons/network_off.xpm"
#include "icons/refresh.xpm"
#include "icons/on.xpm"
#include "icons/off.xpm"
#include "icons/ident_on.xpm"
#include "icons/ident_off.xpm"
#include "icons/crs.xpm"
#include "icons/scale_visibility.xpm"
#include "icons/labels.xpm"
#include "icons/graphics.xpm"
#include "icons/classify.xpm"
#include "icons/cancel.xpm"
#include "icons/statistics.xpm"
#include "icons/spatialidx.xpm"
#include "icons/mbrcache.xpm"
#include "icons/kill_spindex.xpm"
#include "icons/dumpshp.xpm"
#include "icons/remove.xpm"
#include "icons/edit_no.xpm"
#include "icons/edit_yes.xpm"
#include "icons/table.xpm"
#include "icons/table_gear.xpm"
#include "icons/build_network.xpm"
#include "icons/drop_network.xpm"

MyLayerTree::MyLayerTree(MyFrame * parent, wxWindowID id):wxTreeCtrl(parent, id)
{
//
// constructor: TREE control to manage Map Layers
//
  MainFrame = parent;
  Changed = true;
  CurrentItem = wxTreeItemId();
  DraggedItem = wxTreeItemId();
  Root = AddRoot(wxT("No DB connected"));
// setting up icons 
  Images = NULL;
  BaseImages = new wxImageList(16, 16, true);
  wxIcon icons[11];
  icons[0] = wxIcon(db_xpm);
  icons[1] = wxIcon(points_on_xpm);
  icons[2] = wxIcon(linestrings_on_xpm);
  icons[3] = wxIcon(polygons_on_xpm);
  icons[4] = wxIcon(raster_on_xpm);
  icons[5] = wxIcon(network_on_xpm);
  icons[6] = wxIcon(points_off_xpm);
  icons[7] = wxIcon(linestrings_off_xpm);
  icons[8] = wxIcon(polygons_off_xpm);
  icons[9] = wxIcon(raster_off_xpm);
  icons[10] = wxIcon(network_off_xpm);
  BaseImages->Add(icons[0]);
  BaseImages->Add(icons[1]);
  BaseImages->Add(icons[2]);
  BaseImages->Add(icons[3]);
  BaseImages->Add(icons[4]);
  BaseImages->Add(icons[5]);
  BaseImages->Add(icons[6]);
  BaseImages->Add(icons[7]);
  BaseImages->Add(icons[8]);
  BaseImages->Add(icons[9]);
  BaseImages->Add(icons[10]);
  SetItemImage(Root, 0);
// setting up event handlers 
  Connect(wxID_ANY, wxEVT_COMMAND_TREE_SEL_CHANGED,
          (wxObjectEventFunction) & MyLayerTree::OnSelChanged);
  Connect(wxID_ANY, wxEVT_COMMAND_TREE_ITEM_ACTIVATED,
          (wxObjectEventFunction) & MyLayerTree::OnItemActivated);
  Connect(wxID_ANY, wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK,
          (wxObjectEventFunction) & MyLayerTree::OnRightClick);
  Connect(Tree_Refresh, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdRefresh);
  Connect(Tree_ShowAll, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdShowAll);
  Connect(Tree_HideAll, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdHideAll);
  Connect(Tree_Visible, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdVisible);
  Connect(Tree_Identify, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdIdentify);
  Connect(Tree_LayerExtent, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdLayerExtent);
  Connect(Tree_Crs, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdCrs);
  Connect(Tree_ScaleVisibility, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdScaleVisibility);
  Connect(Tree_Labels, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdLabels);
  Connect(Tree_Graphics, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdGraphics);
  Connect(Tree_Classify, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdClassify);
  Connect(Tree_ClassesDrop, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdClassesDrop);
  Connect(Tree_Statistics, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdUpdateStatistics);
  Connect(Tree_SpatialIndex, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdSpatialIndex);
  Connect(Tree_MbrCache, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdMbrCache);
  Connect(Tree_DumpShp, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdDumpShp);
  Connect(Tree_DeleteLayer, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdDeleteLayer);
  Connect(Tree_ShowTable, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdShowTable);
  Connect(Tree_EditMode, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdEditMode);
  Connect(Tree_TableLayout, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdTableLayout);
  Connect(Tree_BuildNetwork, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdBuildNetwork);
  Connect(Tree_DropNetwork, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) & MyLayerTree::OnCmdDropNetwork);
// Drag & Drop event handlers
  Connect(wxID_ANY, wxEVT_COMMAND_TREE_BEGIN_DRAG,
          (wxObjectEventFunction) & MyLayerTree::OnDragStart);
  Connect(wxID_ANY, wxEVT_COMMAND_TREE_BEGIN_RDRAG,
          (wxObjectEventFunction) & MyLayerTree::OnDragStart);
  Connect(wxID_ANY, wxEVT_COMMAND_TREE_END_DRAG,
          (wxObjectEventFunction) & MyLayerTree::OnDragEnd);
}

MyLayerTree::~MyLayerTree()
{
// destructor
  if (BaseImages)
    delete BaseImages;
  if (Images)
    delete Images;
}

void MyLayerTree::AddLayer(MyLayerParams * layer)
{
//
// appends a layer to the TREE list
//
  MyLayerSubClass *pSub;
  wxTreeItemId item;
  bool ok = false;
  wxString name;
  if (layer->IsRasterLayer() == true && layer->GetSrid() != -9999)
    {
      if (layer->GetDescName().Len() > 0)
        name = layer->GetDescName();
      else
        name = layer->GetTableName();
      ok = true;
    }
  if (layer->IsRasterLayer() == false && layer->GetSrid() != -9999 &&
      (layer->GetGeometryType() == LAYER_POINT
       || layer->GetGeometryType() == LAYER_LINESTRING
       || layer->GetGeometryType() == LAYER_POLYGON))
    {
      if (layer->GetDescName().Len() > 0)
        name = layer->GetDescName();
      else
        {
          name = layer->GetTableName();
          name += wxT(".");
          name += layer->GetGeometryColumn();
        }
      ok = true;
    }
  if (ok == false)
    return;
  LayerObject *obj = new LayerObject(layer);
  item = AppendItem(Root, name, GetIconIndex(obj));
  SetItemData(item, (wxTreeItemData *) obj);
  if (obj->GetType() == VECTOR_LAYER)
    {
      // appends the Default [layer Icon]
      LayerObject *objDefault = new LayerObject(obj, true);
      wxTreeItemId defaultItem = AppendItem(item, wxT(""), -1, -1, objDefault);
      pSub = layer->GetFirst();
      while (pSub)
        {
          // appending the SubClasses defs
          LayerObject *newObj = new LayerObject(pSub);
          AppendItem(item, newObj->GetSubClassString(), -1, -1, newObj);
          pSub = pSub->GetNext();
        }
    }
  wxColour color(0, 0, 0);
  if (obj->IsVisible() == false)
    color = wxColour(192, 192, 192);
  SetItemTextColour(item, color);
  Changed = true;
}

void MyLayerTree::MarkCurrentItem()
{
//
// setting the Current Item as BOLD
//
  wxTreeItemId item;
  wxTreeItemIdValue cookie;
  item = GetFirstChild(GetRoot(), cookie);
  while (item.IsOk() == true)
    {
      if (item == CurrentItem)
        SetItemBold(item, true);
      else
        SetItemBold(item, false);
      item = GetNextChild(GetRoot(), cookie);
    }
}

void MyLayerTree::SetLayerIcons()
{
//
// creating the ImageList [with layer Icons]
//
  int count;
  wxTreeItemId item;
  wxTreeItemIdValue cookie;
  LayerObject *layer;

  SetImageList(NULL);
// destroyng the old ImageList
  if (Images)
    delete Images;
  Images = NULL;

  item = GetFirstChild(GetRoot(), cookie);
  count = BaseImages->GetImageCount();  // the fixed Icons
  while (item.IsOk() == true)
    {
      // counting how many Icons we need to insert into the ImageList
      count += GetChildrenCount(item);
      item = GetNextChild(GetRoot(), cookie);
    }

// creating the updated ImageList
  Images = new wxImageList(32, 16, count + 1);
  wxBitmap bmp = BaseImages->GetBitmap(0);
  AddBitmap(bmp);
  bmp = BaseImages->GetBitmap(1);
  AddOnBitmap(bmp);
  bmp = BaseImages->GetBitmap(2);
  AddOnBitmap(bmp);
  bmp = BaseImages->GetBitmap(3);
  AddOnBitmap(bmp);
  bmp = BaseImages->GetBitmap(4);
  AddOnBitmap(bmp);
  bmp = BaseImages->GetBitmap(5);
  AddOnBitmap(bmp);
  bmp = BaseImages->GetBitmap(6);
  AddOffBitmap(bmp);
  bmp = BaseImages->GetBitmap(7);
  AddOffBitmap(bmp);
  bmp = BaseImages->GetBitmap(8);
  AddOffBitmap(bmp);
  bmp = BaseImages->GetBitmap(9);
  AddOffBitmap(bmp);
  bmp = BaseImages->GetBitmap(10);
  AddOffBitmap(bmp);

// creating the Symbol and Pattern lists
  MyImageList symbols;
  MyImageList patterns;
  MainFrame->GetSymbolBitmaps(&symbols);
  MainFrame->GetPatternBitmaps(&patterns);

  item = GetFirstChild(GetRoot(), cookie);
  while (item.IsOk() == true)
    {
      // inserting the Layer Icons
      wxTreeItemId subItem;
      wxTreeItemIdValue subCookie;
      LayerObject *obj = (LayerObject *) GetItemData(item);
      int geomType = obj->GetGeometryType();
      bool hasSubClasses = obj->HasSubClasses();
      subItem = GetFirstChild(item, subCookie);
      while (subItem.IsOk() == true)
        {
          layer = (LayerObject *) GetItemData(subItem);
          if (layer->IsDefault() == true)
            {
              if (hasSubClasses == true)
                SetItemText(subItem, wxT("default"));
              else
                SetItemText(subItem, wxT(""));
              SetItemImage(subItem,
                           layer->AddLayerIcon(Images, 32, 16, &symbols,
                                               &patterns));
          } else if (layer->GetType() == LAYER_SUB_CLASS)
            SetItemImage(subItem,
                         layer->AddSubClassIcon(Images, 32, 16, geomType));
          subItem = GetNextChild(item, subCookie);
        }
      item = GetNextChild(GetRoot(), cookie);
    }
  wxBitmap offBmp(off_xpm);
  AddBitmap(offBmp);
  SetImageList(Images);
}

void MyLayerTree::AddBitmap(wxBitmap & oldBmp)
{
//
// inserting a  Bitmap into the ImageList [centered]
//
  wxBitmap newBmp(32, 16);
  wxMemoryDC *bmp_dc = new wxMemoryDC(newBmp);
  bmp_dc->SetPen(wxColour(255, 255, 255));
  bmp_dc->SetBrush(wxColour(255, 255, 255));
  bmp_dc->DrawRectangle(0, 0, 32, 16);
  bmp_dc->DrawBitmap(oldBmp, 8, 0, true);
  bmp_dc->SetPen(wxNullPen);
  bmp_dc->SetBrush(wxNullBrush);
  delete bmp_dc;
  Images->Add(newBmp, wxColour(255, 255, 255));
}

void MyLayerTree::AddOnBitmap(wxBitmap & oldBmp)
{
//
// inserting a  Bitmap into the ImageList [ON state]
//
  wxBitmap newBmp(32, 16);
  wxMemoryDC *bmp_dc = new wxMemoryDC(newBmp);
  bmp_dc->SetPen(wxColour(255, 255, 255));
  bmp_dc->SetBrush(wxColour(255, 255, 255));
  bmp_dc->DrawRectangle(0, 0, 32, 16);
  bmp_dc->DrawBitmap(on_xpm, 0, 0, true);
  bmp_dc->DrawBitmap(oldBmp, 16, 0, true);
  bmp_dc->SetPen(wxNullPen);
  bmp_dc->SetBrush(wxNullBrush);
  delete bmp_dc;
  Images->Add(newBmp, wxColour(255, 255, 255));
}

void MyLayerTree::AddOffBitmap(wxBitmap & oldBmp)
{
//
// inserting a  Bitmap into the ImageList [OFF state]
//
  wxBitmap newBmp(32, 16);
  wxMemoryDC *bmp_dc = new wxMemoryDC(newBmp);
  bmp_dc->SetPen(wxColour(255, 255, 255));
  bmp_dc->SetBrush(wxColour(255, 255, 255));
  bmp_dc->DrawRectangle(0, 0, 32, 16);
  bmp_dc->DrawBitmap(off_xpm, 0, 0, true);
  bmp_dc->DrawBitmap(oldBmp, 16, 0, true);
  bmp_dc->SetPen(wxNullPen);
  bmp_dc->SetBrush(wxNullBrush);
  delete bmp_dc;
  Images->Add(newBmp, wxColour(255, 255, 255));
}

void MyLayerTree::ResetEditingMode()
{
// resetting the editing permission for any layer
  LayerObject *obj;
  wxTreeItemId layer;
  wxTreeItemIdValue cookie;
  layer = GetFirstChild(Root, cookie);
  while (layer.IsOk() == true)
    {
      // resetting any layer to be "NOT editable"
      obj = (LayerObject *) GetItemData(layer);
      if (obj != NULL)
        obj->SetEditingEnabled(false);
      layer = GetNextChild(Root, cookie);
    }
  MainFrame->UpdateLayersEditMode();
  MainFrame->EnableDrawTools();
}

void MyLayerTree::ResetEditingMode(wxTreeItemId & item)
{
// resetting the editing permission for any layer [excpept the current one]
  LayerObject *obj;
  wxTreeItemId layer;
  wxTreeItemIdValue cookie;
  layer = GetFirstChild(Root, cookie);
  while (layer.IsOk() == true)
    {
      // resetting any layer to be "NOT editable"
      if (layer != item)
        {
          obj = (LayerObject *) GetItemData(layer);
          if (obj != NULL)
            obj->SetEditingEnabled(false);
        }
      layer = GetNextChild(Root, cookie);
    }
  MainFrame->UpdateLayersEditMode();
  MainFrame->EnableDrawTools();
}

void MyLayerTree::OnSelChanged(wxTreeEvent & event)
{
//
// selecting some node [mouse action]
//
  wxTreeItemId item = event.GetItem();
  if (item == Root)
    {
      CurrentItem = wxTreeItemId();
      MarkCurrentItem();
      MainFrame->ResetMapDynamics(NULL);
      MainFrame->EnableDrawTools();
      ResetEditingMode();
      return;
    }
  ResetEditingMode(item);
  CurrentItem = item;
  MarkCurrentItem();
  LayerObject *obj = (LayerObject *) GetItemData(item);
  if (obj == NULL)
    {
      MainFrame->ResetMapDynamics(NULL);
      MainFrame->EnableDrawTools();
  } else
    {
      if (obj->GetType() == VECTOR_LAYER)
        {
          MainFrame->ResetMapDynamics(obj);
          MainFrame->EnableDrawTools();
      } else if (obj->GetType() == LAYER_SUB_CLASS)
        {
          wxTreeItemId parent = GetItemParent(item);
          LayerObject *parentObj = (LayerObject *) GetItemData(parent);
          MainFrame->ResetMapDynamics(parentObj);
          MainFrame->EnableDrawTools();
      } else
        {
          MainFrame->ResetMapDynamics(NULL);
          MainFrame->EnableDrawTools();
        }
    }
  MainFrame->GetMap()->SetMapToolsState(false);
}

void MyLayerTree::OnItemActivated(wxTreeEvent & event)
{
//
// activating some node [mouse action]
//
  wxColour color(0, 0, 0);
  wxTreeItemId item = event.GetItem();
  if (item == Root)
    {
      ResetEditingMode();
      return;
    }
  ResetEditingMode(item);
  LayerObject *obj = (LayerObject *) GetItemData(item);
  if (obj == NULL)
    return;
  if ((obj->GetType() == VECTOR_LAYER && obj->IsDefault() == false)
      || obj->GetType() == RASTER_LAYER)
    {
      if (obj->IsVisible() == true)
        {
          obj->SetVisible(false);
          color = wxColour(192, 192, 192);
      } else
        obj->SetVisible(true);
      MainFrame->UpdateLayerParams(obj);
      SetItemImage(item, GetIconIndex(obj));
      SetItemTextColour(item, color);
      Changed = true;
      MainFrame->RefreshMap();
    }
  if (obj->GetType() == LAYER_SUB_CLASS)
    {
      if (obj->IsVisible() == true)
        {
          obj->SetVisible(false);
          color = wxColour(192, 192, 192);
      } else
        obj->SetVisible(true);
      SetItemImage(item, GetIconIndex(obj));
      SetItemTextColour(item, color);
      Changed = true;
      MainFrame->RefreshMap();
    }
}

void MyLayerTree::OnRightClick(wxTreeEvent & event)
{
//
// right click on some node [mouse action]
//
  wxMenuItem *menuItem;
  wxMenu *menu = new wxMenu;
  wxTreeItemId item = event.GetItem();
  SelectItem(item);
  wxPoint pt = event.GetPoint();
  if (item == Root)
    {
      ResetEditingMode();
      CurrentItem = wxTreeItemId();
      MarkCurrentItem();
      menuItem = new wxMenuItem(menu, Tree_Refresh, wxT("&Refresh Layers"));
      menuItem->SetBitmap(wxBitmap(refresh_xpm));
      menu->Append(menuItem);
      menu->AppendSeparator();
      menuItem =
        new wxMenuItem(menu, Tree_Crs,
                       wxT("Project CRS [Coordinate Reference System]"));
      menuItem->SetBitmap(wxBitmap(crs_xpm));
      menu->Append(menuItem);
      menu->AppendSeparator();
      menuItem =
        new wxMenuItem(menu, Tree_Statistics, wxT("Update Project Statistics"));
      menuItem->SetBitmap(wxBitmap(statistics_xpm));
      menu->Append(menuItem);
      menu->AppendSeparator();
      menuItem = new wxMenuItem(menu, Tree_HideAll, wxT("Hide All"));
      menuItem->SetBitmap(wxBitmap(off_xpm));
      menu->Append(menuItem);
      menuItem = new wxMenuItem(menu, Tree_ShowAll, wxT("Show All"));
      menuItem->SetBitmap(wxBitmap(on_xpm));
      menu->Append(menuItem);
      PopupMenu(menu, pt);
      return;
    }
  ResetEditingMode(item);
  LayerObject *obj = (LayerObject *) GetItemData(item);
  if (obj == NULL)
    {
      CurrentItem = wxTreeItemId();
      MarkCurrentItem();
      menuItem = new wxMenuItem(menu, Tree_Refresh, wxT("&Refresh Layers"));
      menuItem->SetBitmap(wxBitmap(refresh_xpm));
      menu->Append(menuItem);
      menu->AppendSeparator();
      menuItem =
        new wxMenuItem(menu, Tree_Crs, wxT("Project Reference System"));
      menuItem->SetBitmap(wxBitmap(crs_xpm));
      menu->Append(menuItem);
      menu->AppendSeparator();
      menuItem =
        new wxMenuItem(menu, Tree_Statistics, wxT("Update Project Statistics"));
      menuItem->SetBitmap(wxBitmap(statistics_xpm));
      menu->Append(menuItem);
      PopupMenu(menu, pt);
      return;
  } else
    {
      if (obj->GetType() == VECTOR_LAYER)
        {
          // vector layer
          CurrentItem = item;
          MarkCurrentItem();
          wxString title =
            obj->GetTableName() + wxT(".") + obj->GetGeometryColumn();
          if (obj->GetDescName().Len() > 0)
            {
              title += wxT(" [");
              title += obj->GetDescName();
              title += wxT("]");
            }
          if (obj->IsDefault() == true)
            {
              title += wxT(" - default");
            }
          menu->SetTitle(title);
          menuItem = new wxMenuItem(menu, Tree_Refresh, wxT("&Refresh Layers"));
          menuItem->SetBitmap(wxBitmap(refresh_xpm));
          menu->Append(menuItem);
          if (obj->IsDefault() == false)
            {
              menu->AppendSeparator();
              if (obj->IsVisible() == true)
                {
                  menuItem = new wxMenuItem(menu, Tree_Visible, wxT("Hide"));
                  menuItem->SetBitmap(wxBitmap(off_xpm));
                  menu->Append(menuItem);
              } else
                {
                  menuItem = new wxMenuItem(menu, Tree_Visible, wxT("Show"));
                  menuItem->SetBitmap(wxBitmap(on_xpm));
                  menu->Append(menuItem);
                }
              if (obj->IsIdentify() == true)
                {
                  menuItem =
                    new wxMenuItem(menu, Tree_Identify, wxT("Identify On"));
                  menuItem->SetBitmap(wxBitmap(ident_on_xpm));
                  menu->Append(menuItem);
              } else
                {
                  menuItem =
                    new wxMenuItem(menu, Tree_Identify, wxT("Identify Off"));
                  menuItem->SetBitmap(wxBitmap(ident_off_xpm));
                  menu->Append(menuItem);
                }
              menuItem =
                new wxMenuItem(menu, Tree_LayerExtent,
                               wxT("Zoom to layer extent"));
              menu->Append(menuItem);
              menu->AppendSeparator();
              menuItem =
                new wxMenuItem(menu, Tree_ShowTable, wxT("Show DB table"));
              menuItem->SetBitmap(wxBitmap(table_xpm));
              menu->Append(menuItem);
              menu->AppendSeparator();
              if (obj->IsLayerView() == true || obj->IsLayerVirtual() == true)
                {
                  menuItem =
                    new wxMenuItem(menu, Tree_EditMode,
                                   wxT("Editing disabled"));
                  menuItem->SetBitmap(wxBitmap(edit_no_xpm));
                  menu->Append(menuItem);
                  menuItem->Enable(false);
              } else
                {
                  if (obj->IsReadOnly() == true)
                    {
                      menuItem =
                        new wxMenuItem(menu, Tree_EditMode,
                                       wxT("Editing disabled"));
                      menuItem->SetBitmap(wxBitmap(edit_no_xpm));
                      menu->Append(menuItem);
                      menuItem->Enable(false);
                  } else
                    {
                      if (obj->IsEditingEnabled() == true)
                        {
                          menuItem =
                            new wxMenuItem(menu, Tree_EditMode,
                                           wxT("Editing enabled"));
                          menuItem->SetBitmap(wxBitmap(edit_yes_xpm));
                          menu->Append(menuItem);
                      } else
                        {
                          menuItem =
                            new wxMenuItem(menu, Tree_EditMode,
                                           wxT("Editing disabled"));
                          menuItem->SetBitmap(wxBitmap(edit_no_xpm));
                          menu->Append(menuItem);
                        }
                      if (obj->GetGeometryType() == LAYER_LINESTRING
                          && obj->IsNetwork() == true)
                        menuItem->Enable(false);
                    }
                }
              menu->AppendSeparator();
              wxMenu *subMenu1 = new wxMenu();
              menuItem =
                new wxMenuItem(subMenu1, Tree_Graphics, wxT("Graphics"));
              menuItem->SetBitmap(wxBitmap(graphics_xpm));
              subMenu1->Append(menuItem);
              subMenu1->AppendSeparator();
              menuItem =
                new wxMenuItem(subMenu1, Tree_Classify, wxT("Classify"));
              menuItem->SetBitmap(wxBitmap(classify_xpm));
              subMenu1->Append(menuItem);
              if (obj->HasSubClasses() == true)
                {
                  menuItem =
                    new wxMenuItem(subMenu1, Tree_ClassesDrop,
                                   wxT("Drop Classes"));
                  menuItem->SetBitmap(wxBitmap(cancel_xpm));
                  subMenu1->Append(menuItem);
                }
              subMenu1->AppendSeparator();
              menuItem =
                new wxMenuItem(subMenu1, Tree_Crs,
                               wxT("Layer Reference System"));
              menuItem->SetBitmap(wxBitmap(crs_xpm));
              subMenu1->Append(menuItem);
              menuItem =
                new wxMenuItem(subMenu1, Tree_ScaleVisibility,
                               wxT("Visibility Range"));
              menuItem->SetBitmap(wxBitmap(scale_visibility_xpm));
              subMenu1->Append(menuItem);
              menuItem = new wxMenuItem(subMenu1, Tree_Labels, wxT("Labels"));
              menuItem->SetBitmap(wxBitmap(labels_xpm));
              subMenu1->Append(menuItem);
              subMenu1->AppendSeparator();
              menuItem =
                new wxMenuItem(subMenu1, Tree_TableLayout, wxT("Table Layout"));
              menuItem->SetBitmap(wxBitmap(table_gear_xpm));
              subMenu1->Append(menuItem);
              menu->AppendSubMenu(subMenu1, wxT("Layer configuration"));
              menu->AppendSeparator();
              wxMenu *subMenu2 = new wxMenu();
              menuItem =
                new wxMenuItem(subMenu2, Tree_Statistics,
                               wxT("Update Layer Statistics"));
              menuItem->SetBitmap(wxBitmap(statistics_xpm));
              subMenu2->Append(menuItem);
              subMenu2->AppendSeparator();
              if (obj->IsLayerView() == false && obj->IsLayerVirtual() == false)
                {
                  int index_type =
                    MainFrame->GetSpatialIndexType(obj->GetTableName(),
                                                   obj->GetGeometryColumn());
                  if (index_type == SPATIAL_INDEX_NONE)
                    {
                      // currently there is no spatial index defined
                      menuItem =
                        new wxMenuItem(subMenu2, Tree_SpatialIndex,
                                       wxT("&Build Spatial Index"));
                      menuItem->SetBitmap(wxBitmap(spatialidx_xpm));
                      subMenu2->Append(menuItem);
                      menuItem =
                        new wxMenuItem(subMenu2, Tree_MbrCache,
                                       wxT("Build &MBR cache"));
                      menuItem->SetBitmap(wxBitmap(mbrcache_xpm));
                      subMenu2->Append(menuItem);
                  } else if (index_type == SPATIAL_INDEX_RTREE)
                    {
                      // an RTree spatial index is already defined
                      menuItem =
                        new wxMenuItem(subMenu2, Tree_SpatialIndex,
                                       wxT("&Remove Spatial Index"));
                      menuItem->SetBitmap(wxBitmap(kill_spindex_xpm));
                      subMenu2->Append(menuItem);
                  } else if (index_type == SPATIAL_INDEX_CACHED)
                    {
                      // an MBR Cache spatial index is already defined
                      menuItem =
                        new wxMenuItem(subMenu2, Tree_MbrCache,
                                       wxT("&Remove MBR cache"));
                      menuItem->SetBitmap(wxBitmap(kill_spindex_xpm));
                      subMenu2->Append(menuItem);
                    }
                  subMenu2->AppendSeparator();
                }
              if (obj->IsLayerVirtual() == false)
                {
                  menuItem =
                    new wxMenuItem(subMenu2, Tree_DumpShp,
                                   wxT("Export as &Shapefile"));
                  menuItem->SetBitmap(wxBitmap(dumpshp_xpm));
                  subMenu2->Append(menuItem);
                  if (obj->GetGeometryType() == LAYER_LINESTRING)
                    {
                      subMenu2->AppendSeparator();
                      if (obj->IsNetwork() == true)
                        {
                          menuItem =
                            new wxMenuItem(subMenu2, Tree_DropNetwork,
                                           wxT("Drop &Network"));
                          menuItem->SetBitmap(wxBitmap(drop_network_xpm));
                      } else
                        {
                          menuItem =
                            new wxMenuItem(subMenu2, Tree_BuildNetwork,
                                           wxT("Build &Network"));
                          menuItem->SetBitmap(wxBitmap(build_network_xpm));
                        }
                      subMenu2->Append(menuItem);
                    }
                  subMenu2->AppendSeparator();
                }
              menuItem =
                new wxMenuItem(subMenu2, Tree_DeleteLayer,
                               wxT("Delete this &Layer"));
              menuItem->SetBitmap(wxBitmap(remove_xpm));
              subMenu2->Append(menuItem);
              if (obj->GetGeometryType() == LAYER_LINESTRING
                  && obj->IsNetwork() == true)
                menuItem->Enable(false);
              menu->AppendSubMenu(subMenu2, wxT("Advanced"));
            }
          PopupMenu(menu, pt);
          return;
      } else if (obj->GetType() == LAYER_SUB_CLASS)
        {
          // vector layer - SubClass
          CurrentItem = item;
          MarkCurrentItem();
          wxString title = wxT("SubClass: ");
          title += GetItemText(CurrentItem);
          menu->SetTitle(title);
          menuItem = new wxMenuItem(menu, Tree_Refresh, wxT("&Refresh Layers"));
          menuItem->SetBitmap(wxBitmap(refresh_xpm));
          menu->Append(menuItem);
          menu->AppendSeparator();
          if (obj->IsVisible() == true)
            {
              menuItem = new wxMenuItem(menu, Tree_Visible, wxT("Hide"));
              menuItem->SetBitmap(wxBitmap(off_xpm));
              menu->Append(menuItem);
          } else
            {
              menuItem = new wxMenuItem(menu, Tree_Visible, wxT("Show"));
              menuItem->SetBitmap(wxBitmap(on_xpm));
              menu->Append(menuItem);
            }
          menu->AppendSeparator();
          wxMenu *subMenu = new wxMenu();
          menuItem = new wxMenuItem(subMenu, Tree_Classify, wxT("Classify"));
          menuItem->SetBitmap(wxBitmap(classify_xpm));
          subMenu->Append(menuItem);
          menuItem =
            new wxMenuItem(subMenu, Tree_ClassesDrop, wxT("Drop Classes"));
          menuItem->SetBitmap(wxBitmap(cancel_xpm));
          subMenu->Append(menuItem);
          menu->AppendSubMenu(subMenu, wxT("SubClasses"));
          PopupMenu(menu, pt);
          return;
      } else
        {
          // raster layer
          CurrentItem = item;
          MarkCurrentItem();
          wxString title = obj->GetTableName();
          if (obj->GetDescName().Len() > 0)
            {
              title += wxT(" [");
              title += obj->GetDescName();
              title += wxT("]");
            }
          menu->SetTitle(title);
          menuItem = new wxMenuItem(menu, Tree_Refresh, wxT("&Refresh Layers"));
          menuItem->SetBitmap(wxBitmap(refresh_xpm));
          menu->Append(menuItem);
          menu->AppendSeparator();
          if (obj->IsVisible() == true)
            {
              menuItem = new wxMenuItem(menu, Tree_Visible, wxT("Hide"));
              menuItem->SetBitmap(wxBitmap(off_xpm));
              menu->Append(menuItem);
          } else
            {
              menuItem = new wxMenuItem(menu, Tree_Visible, wxT("Show"));
              menuItem->SetBitmap(wxBitmap(on_xpm));
              menu->Append(menuItem);
            }
          menu->AppendSeparator();
          wxMenu *subMenu1 = new wxMenu();
          menuItem =
            new wxMenuItem(subMenu1, Tree_Crs, wxT("Layer Reference System"));
          menuItem->SetBitmap(wxBitmap(crs_xpm));
          subMenu1->Append(menuItem);
          menuItem =
            new wxMenuItem(subMenu1, Tree_ScaleVisibility,
                           wxT("Visibility Range"));
          menuItem->SetBitmap(wxBitmap(scale_visibility_xpm));
          subMenu1->Append(menuItem);
          menu->AppendSubMenu(subMenu1, wxT("Layer configuration"));
          menu->AppendSeparator();
          wxMenu *subMenu2 = new wxMenu();
          menuItem =
            new wxMenuItem(subMenu2, Tree_Statistics,
                           wxT("Update Layer Statistics"));
          menuItem->SetBitmap(wxBitmap(statistics_xpm));
          subMenu2->Append(menuItem);
          subMenu2->AppendSeparator();
          menuItem =
            new wxMenuItem(subMenu2, Tree_DeleteLayer,
                           wxT("Delete this &Layer"));
          menuItem->SetBitmap(wxBitmap(remove_xpm));
          subMenu2->Append(menuItem);
          menu->AppendSubMenu(subMenu2, wxT("Advanced"));
          PopupMenu(menu, pt);
          return;
        }
    }
}

void MyLayerTree::OnCmdSpatialIndex(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - Spatial Index creation-destruction
//
  char *errMsg = NULL;
  int ret;
  wxString sql;
  wxString msg;
  int i;
  char **results;
  int rows;
  int columns;
  int retval = 0;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  int index_type = MainFrame->GetSpatialIndexType(obj->GetTableName(),
                                                  obj->GetGeometryColumn());
  if (index_type == SPATIAL_INDEX_NONE)
    {
      // creating the Spatial Index
      ::wxBeginBusyCursor();
      ret = sqlite3_exec(sqlite, "BEGIN", NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      sql = wxT("SELECT CreateSpatialIndex('");
      sql += obj->GetTableName();
      sql += wxT("', '");
      sql += obj->GetGeometryColumn();
      sql += wxT("')");
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
              if (results[(i * columns) + 0])
                retval = atoi(results[(i * columns) + 0]);
            }
        }
      sqlite3_free_table(results);
      if (!retval)
        goto rollback;
      ret = sqlite3_exec(sqlite, "COMMIT", NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      ::wxEndBusyCursor();
      wxMessageBox(wxT("Spatial Index idx_") + obj->GetTableName() +
                   wxT("_") + obj->GetGeometryColumn() +
                   wxT(" was successfully created"), wxT("spatialite-gis"),
                   wxOK | wxICON_INFORMATION, this);
      MainFrame->InitLayerTree();
  } else if (index_type == SPATIAL_INDEX_RTREE)
    {
      // dropping the Spatial Index
      ::wxBeginBusyCursor();
      ret = sqlite3_exec(sqlite, "BEGIN", NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      sql = wxT("SELECT DisableSpatialIndex('");
      sql += obj->GetTableName();
      sql += wxT("', '");
      sql += obj->GetGeometryColumn();
      sql += wxT("')");
      msg = wxT("Do you really intend to delete the SpatialIndex\n");
      msg += wxT("on column '");
      msg += obj->GetTableName();
      msg += wxT(".");
      msg += obj->GetGeometryColumn();
      msg += wxT("' ?");
      wxMessageDialog confirm(this, msg, wxT("Confirming Delete Spatial Index"),
                              wxOK | wxCANCEL | wxICON_QUESTION);
      ret = confirm.ShowModal();
      if (ret != wxID_OK)
        return;
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
              if (results[(i * columns) + 0])
                retval = atoi(results[(i * columns) + 0]);
            }
        }
      sqlite3_free_table(results);
      if (!retval)
        goto rollback;
      sql = wxT("DROP TABLE IF EXISTS idx_");
      sql += obj->GetTableName();
      sql += wxT("_");
      sql += obj->GetGeometryColumn();
      ret = sqlite3_exec(sqlite, sql.ToUTF8(), NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      ret = sqlite3_exec(sqlite, "COMMIT", NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      ::wxEndBusyCursor();
      wxMessageBox(wxT("Spatial Index idx_") + obj->GetTableName() +
                   wxT("_") + obj->GetGeometryColumn() +
                   wxT(" was successfully removed"), wxT("spatialite-gis"),
                   wxOK | wxICON_INFORMATION, this);
      MainFrame->InitLayerTree();
    }
  return;
rollback:
  ret = sqlite3_exec(sqlite, "ROLLBACK", NULL, NULL, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      ::wxEndBusyCursor();
      return;
    }
  ::wxEndBusyCursor();
  wxMessageBox(wxT
               ("An error occurred\n\na ROLLBACK was automatically performed"),
               wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
}

void MyLayerTree::OnCmdMbrCache(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - MBR cache creation-destruction
//
  char *errMsg = NULL;
  int ret;
  wxString sql;
  wxString msg;
  int i;
  char **results;
  int rows;
  int columns;
  int retval = 0;
  sqlite3 *sqlite = MainFrame->GetSqlite();
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  int index_type = MainFrame->GetSpatialIndexType(obj->GetTableName(),
                                                  obj->GetGeometryColumn());
  if (index_type == SPATIAL_INDEX_NONE)
    {
      // creating the MBR cache
      ::wxBeginBusyCursor();
      ret = sqlite3_exec(sqlite, "BEGIN", NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      sql = wxT("SELECT CreateMbrCache('");
      sql += obj->GetTableName();
      sql += wxT("', '");
      sql += obj->GetGeometryColumn();
      sql += wxT("')");
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
              if (results[(i * columns) + 0])
                retval = atoi(results[(i * columns) + 0]);
            }
        }
      sqlite3_free_table(results);
      if (!retval)
        goto rollback;
      ret = sqlite3_exec(sqlite, "COMMIT", NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      ::wxEndBusyCursor();
      wxMessageBox(wxT("MBR cache cache_") + obj->GetTableName() +
                   wxT("_") + obj->GetGeometryColumn() +
                   wxT(" was successfully created"), wxT("spatialite-gis"),
                   wxOK | wxICON_INFORMATION, this);
      MainFrame->InitLayerTree();
  } else if (index_type == SPATIAL_INDEX_CACHED)
    {
      // dropping the MBR cache
      ::wxBeginBusyCursor();
      ret = sqlite3_exec(sqlite, "BEGIN", NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      sql = wxT("SELECT DisableSpatialIndex('");
      sql += obj->GetTableName();
      sql += wxT("', '");
      sql += obj->GetGeometryColumn();
      sql += wxT("')");
      msg = wxT("Do you really intend to delete the MBR cache\n");
      msg += wxT("on column '");
      msg += obj->GetTableName();
      msg += wxT(".");
      msg += obj->GetGeometryColumn();
      msg += wxT("' ?");
      wxMessageDialog confirm(this, msg, wxT("Confirming Delete MBR cache"),
                              wxOK | wxCANCEL | wxICON_QUESTION);
      ret = confirm.ShowModal();
      if (ret != wxID_OK)
        return;
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
              if (results[(i * columns) + 0])
                retval = atoi(results[(i * columns) + 0]);
            }
        }
      sqlite3_free_table(results);
      if (!retval)
        goto rollback;
      sql = wxT("DROP TABLE IF EXISTS cache_");
      sql += obj->GetTableName();
      sql += wxT("_");
      sql += obj->GetGeometryColumn();
      ret = sqlite3_exec(sqlite, sql.ToUTF8(), NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      ret = sqlite3_exec(sqlite, "COMMIT", NULL, NULL, &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_free(errMsg);
          ::wxEndBusyCursor();
          return;
        }
      ::wxEndBusyCursor();
      wxMessageBox(wxT("MBR cache cache_") + obj->GetTableName() +
                   wxT("_") + obj->GetGeometryColumn() +
                   wxT(" was successfully removed"), wxT("spatialite-gis"),
                   wxOK | wxICON_INFORMATION, this);
      MainFrame->InitLayerTree();
    }
  return;
rollback:
  ret = sqlite3_exec(sqlite, "ROLLBACK", NULL, NULL, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      ::wxEndBusyCursor();
      return;
    }
  ::wxEndBusyCursor();
  wxMessageBox(wxT
               ("An error occurred\n\na ROLLBACK was automatically performed"),
               wxT("spatialite-gis"), wxOK | wxICON_WARNING, this);
}

void MyLayerTree::OnCmdDeleteLayer(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - removing some layer [both Vector or Raster]
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if ((obj->GetType() == VECTOR_LAYER && obj->IsDefault() == false)
      || obj->GetType() == RASTER_LAYER)
    {
      wxString msg;
      if (obj->GetType() == VECTOR_LAYER)
        {
          msg += wxT("Vector layer:\n\n");
          msg += obj->GetTableName();
          msg += wxT(".");
          msg += obj->GetGeometryColumn();
          msg += wxT("\n");
          if (obj->GetDescName().Len() > 0)
            {
              msg += obj->GetDescName();
              msg += wxT("\n");
            }
      } else
        {
          msg += wxT("Raster layer:\n\n");
          msg += obj->GetTableName();
          msg += wxT("\n");
          if (obj->GetDescName().Len() > 0)
            {
              msg += obj->GetDescName();
              msg += wxT("\n");
            }
        }
      msg += wxT("\nDo you really confirm deleting this layer ?");
      wxMessageDialog dlg(this, msg, wxT("spatialite-gis"),
                          wxYES_NO | wxICON_QUESTION);
      int ret = dlg.ShowModal();
      if (ret == wxID_YES)
        {
          if (MainFrame->DeleteLayer(obj) == true)
            {
              MainFrame->InitLayerTree();
              Changed = true;
              MainFrame->RefreshMap();
            }
        }
    }
}

void MyLayerTree::OnCmdShowTable(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - showing the DB table corresponding to some vector layer
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER && obj->IsDefault() == false)
    {
      MapLayer *layer = new MapLayer(obj);
      TableDialog dlg;
      dlg.Create(MainFrame, layer,
                 (obj->IsEditingEnabled() == true) ? false : true);
      dlg.ShowModal();
    }
}

void MyLayerTree::OnCmdEditMode(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the edit mode for some vector layer
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER && obj->IsDefault() == false)
    {
      if (obj->GetGeometryType() == LAYER_LINESTRING
          && obj->IsNetwork() == true)
        ;
      else
        {
          if (obj->IsEditingEnabled() == true)
            obj->SetEditingEnabled(false);
          else
            obj->SetEditingEnabled(true);
        }
    }
  MainFrame->UpdateLayersEditMode();
}

void MyLayerTree::OnCmdTableLayout(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - handling the table layout
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER && obj->IsDefault() == false)
    {
      TableLayoutDialog dlg;
      dlg.Create(MainFrame, obj->GetTableName(), obj->GetGeometryColumn());
      dlg.ShowModal();
    }
}

void MyLayerTree::OnCmdBuildNetwork(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - build Network
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER && obj->IsDefault() == false
      && obj->GetGeometryType() == LAYER_LINESTRING
      && obj->IsNetwork() == false)
    {
      NetworkDialog dlg;
      int ret;
      wxString from;
      wxString to;
      wxString name;
      bool isGeomLength;
      wxString cost;
      bool isBidirectional;
      bool isOneWays;
      wxString oneWayToFrom;
      wxString oneWayFromTo;
      bool aStarSupported;
      dlg.Create(MainFrame, obj->GetTableName(), obj->GetGeometryColumn());
      ret = dlg.ShowModal();
      if (ret == wxID_OK)
        {
          from = dlg.GetFromColumn();
          to = dlg.GetToColumn();
          name = dlg.GetNameColumn();
          isGeomLength = dlg.IsGeomLength();
          cost = dlg.GetCostColumn();
          isBidirectional = dlg.IsBidirectional();
          isOneWays = dlg.IsOneWays();
          oneWayToFrom = dlg.GetOneWayToFrom();
          oneWayFromTo = dlg.GetOneWayFromTo();
          aStarSupported = dlg.IsAStarSupported();
          if (MainFrame->BuildNetwork(obj->GetTableName(), from, to,
                                      obj->GetGeometryColumn(), name,
                                      isGeomLength, cost, isBidirectional,
                                      isOneWays, oneWayFromTo, oneWayToFrom,
                                      aStarSupported) == true)
            {
              bool err = false;
              MainFrame->LoadNetworkParams();
              if (MainFrame->GetNetwork() == NULL)
                {
                  wxString msg = wxT("Internal error: invalid Network\n\n");
                  msg +=
                    wxT
                    ("Sorry, I cannot enable Routing features for this Network ...\n");
                  wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                               this);
                  err = true;
                }
              if (err == false)
                {
                  if (MainFrame->FeedNetworkNodes() == false)
                    {
                      // creating the Network Nodes aux table
                      wxString msg =
                        wxT
                        ("Network Nodes auxiliary table creation failed\n\n");
                      wxMessageBox(msg, wxT("spatialite-gis"),
                                   wxOK | wxICON_WARNING, this);
                      err = true;
                    }
                }
              if (err == false)
                {
                  wxString msg = wxT("Network succesfully created\n");
                  wxMessageBox(msg, wxT("spatialite-gis"),
                               wxOK | wxICON_INFORMATION, this);
                }
              MainFrame->InitLayerTree();
              Changed = true;
              MainFrame->RefreshMap();
            }
        }
    }
}

void MyLayerTree::OnCmdDropNetwork(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - drop Network
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER && obj->IsDefault() == false
      && obj->GetGeometryType() == LAYER_LINESTRING && obj->IsNetwork() == true)
    {
      if (MainFrame->DestroyNetwork(obj->GetTableName()) == true)
        {
          wxString msg = wxT("Network succesfully removed\n");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                       this);
        }
      MainFrame->InitLayerTree();
      Changed = true;
      MainFrame->RefreshMap();
    }
}

void MyLayerTree::OnCmdRefresh(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - refreshing the layers list
//
  MainFrame->InitLayerTree();
  Changed = true;
  MainFrame->RefreshMap();
}

void MyLayerTree::OnCmdShowAll(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the visibility state [SHOW ALL]
//
  LayerObject *obj;
  wxTreeItemId layer;
  wxTreeItemIdValue cookie;
  wxTreeItemId subClass;
  ::wxBeginBusyCursor();
  Hide();
  layer = GetFirstChild(Root, cookie);
  while (layer.IsOk() == true)
    {
      // making a Layer to be visible
      obj = (LayerObject *) GetItemData(layer);
      obj->SetVisible(true);
      SetItemImage(layer, GetIconIndex(obj));
      SetItemTextColour(layer, wxColour(0, 0, 0));
      MainFrame->UpdateLayerParams(obj);
      Expand(layer);
      layer = GetNextChild(Root, cookie);
    }
  Show();
  ::wxEndBusyCursor();
  Changed = true;
  MainFrame->RefreshMap();
}

void MyLayerTree::OnCmdHideAll(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the visibility state [HIDE ALL]
//
  LayerObject *obj;
  wxTreeItemId layer;
  wxTreeItemIdValue cookie;
  wxTreeItemId subClass;
  ::wxBeginBusyCursor();
  Hide();
  layer = GetFirstChild(Root, cookie);
  while (layer.IsOk() == true)
    {
      // making a Layer to be invisible
      obj = (LayerObject *) GetItemData(layer);
      obj->SetVisible(false);
      SetItemImage(layer, GetIconIndex(obj));
      SetItemTextColour(layer, wxColour(192, 192, 192));
      MainFrame->UpdateLayerParams(obj);
      Collapse(layer);
      layer = GetNextChild(Root, cookie);
    }
  Show();
  ::wxEndBusyCursor();
  Changed = true;
  MainFrame->RefreshMap();
}

void MyLayerTree::OnCmdVisible(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the visibility state
//
  wxColour color(0, 0, 0);
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER || obj->GetType() == RASTER_LAYER)
    {
      if (obj->IsVisible() == true)
        {
          obj->SetVisible(false);
          color = wxColour(192, 192, 192);
      } else
        obj->SetVisible(true);

      SetItemImage(CurrentItem, GetIconIndex(obj));
      SetItemTextColour(CurrentItem, color);
      MainFrame->UpdateLayerParams(obj);

      if (obj->IsVisible() == true)
        Expand(CurrentItem);
      else
        Collapse(CurrentItem);
      Changed = true;
      MainFrame->RefreshMap();
  } else if (obj->GetType() == LAYER_SUB_CLASS)
    {
      if (obj->IsVisible() == true)
        {
          obj->SetVisible(false);
          color = wxColour(192, 192, 192);
      } else
        obj->SetVisible(true);

      SetItemImage(CurrentItem, GetIconIndex(obj));
      SetItemTextColour(CurrentItem, color);
      Changed = true;
      MainFrame->RefreshMap();
    }
}

void MyLayerTree::OnCmdIdentify(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - changing the identify state
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER)
    {
      if (obj->IsIdentify() == true)
        obj->SetIdentify(false);
      else
        obj->SetIdentify(true);
      MainFrame->UpdateLayerParams(obj);
      Changed = true;
      MainFrame->RefreshMap();
    }
}

void MyLayerTree::OnCmdLayerExtent(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - Zoom to layer extent
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER)
    {
      if (MainFrame->ZoomToLayerExtent(obj) == TRUE)
        {
          Changed = true;
          MainFrame->RefreshMap();
        }
    }
}

void MyLayerTree::OnCmdCrs(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - setting the Reference System
//
  int ret;
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    {
      ProjectCrsDialog dlg;
      dlg.Create(MainFrame, MainFrame->GetProjectCrs(),
                 MainFrame->GetProjectName());
      ret = dlg.ShowModal();
      if (ret == wxID_OK)
        {
          MainFrame->UpdateProjectDefs();
          Changed = true;
          MainFrame->RefreshMap();
        }
      return;
    }
  if (obj->GetType() == VECTOR_LAYER)
    {
      VectorCrsDialog dlg;
      dlg.Create(MainFrame, MainFrame->GetProjectCrs(), obj->GetTableName(),
                 obj->GetGeometryColumn(), obj->GetDescName(), obj->GetSrid(),
                 obj->IsReproject());
      ret = dlg.ShowModal();
      if (ret == wxID_OK)
        {
          obj->SetDescName(dlg.GetDescName());
          obj->SetReproject(dlg.IsReproject());
          MainFrame->UpdateLayerParams(obj);
          Changed = true;
          MainFrame->RefreshMap();
        }
  } else if (obj->GetType() == RASTER_LAYER)
    {
      RasterCrsDialog dlg;
      dlg.Create(MainFrame, MainFrame->GetProjectCrs(), obj->GetTableName(),
                 obj->GetDescName(), obj->GetSrid());
      ret = dlg.ShowModal();
      if (ret == wxID_OK)
        {
          Changed = true;
        }
  } else
    {
      ProjectCrsDialog dlg;
      dlg.Create(MainFrame, MainFrame->GetProjectCrs(),
                 MainFrame->GetProjectName());
      ret = dlg.ShowModal();
      if (ret == wxID_OK)
        {
          MainFrame->UpdateProjectDefs();
          Changed = true;
          MainFrame->RefreshMap();
        }
    }
}

void MyLayerTree::OnCmdScaleVisibility(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - setting the Layer Visibility Range
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER || obj->GetType() == RASTER_LAYER)
    {
      VisibilityRangeDialog dlg;
      dlg.Create(MainFrame, obj->GetType(), obj->GetTableName(),
                 obj->GetGeometryColumn(), obj->GetDescName(),
                 obj->IsAlwaysVisible(), obj->GetMinScale(),
                 obj->GetMaxScale());
      int ret = dlg.ShowModal();
      if (ret == wxID_OK)
        {
          if (dlg.IsAlwaysVisible() == true)
            obj->SetAlwaysVisible();
          else
            obj->SetScaleVisibility(dlg.GetMinScale(), dlg.GetMaxScale());
          obj->SetDescName(dlg.GetDescName());
          MainFrame->UpdateLayerParams(obj);
          Changed = true;
          MainFrame->RefreshMap();
        }
    }
}

void MyLayerTree::OnCmdLabels(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - setting the Layer Visibility Range
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER)
    {
      LabelsDialog dlg;
      dlg.Create(MainFrame, obj->GetTableName(), obj->GetGeometryColumn(),
                 obj->GetDescName(), obj->GetLabelColumn(),
                 obj->IsMapLabelingEnabled(), obj->GetLabelColor(),
                 obj->GetLabelPointSize(), obj->IsLabelFontBold(),
                 obj->IsLabelFontItalic(), obj->IsLabelFontUnderlined(),
                 obj->IsLabelFontOutlined(), obj->GetLabelOrderByColumn(),
                 obj->IsLabelOrderByDescending(), obj->IsLabelAlwaysVisible(),
                 obj->GetLabelMinScale(), obj->GetLabelMaxScale(),
                 obj->IsLabelAntiOverlapEnabled());
      int ret = dlg.ShowModal();
      if (ret == wxID_OK)
        {
          obj->SetDescName(dlg.GetDescName());
          obj->SetLabelColumn(dlg.GetLabelColumn());
          if (dlg.IsMapLabelingEnabled() == false)
            obj->DisableMapLabeling();
          else
            {
              obj->EnableMapLabeling(dlg.GetTextColor(), dlg.GetPointSize(),
                                     dlg.IsFontBold(), dlg.IsFontItalic(),
                                     dlg.IsFontUnderlined(),
                                     dlg.IsFontOutlined(),
                                     dlg.GetOrderByColumn(), dlg.IsDescending(),
                                     dlg.IsAntiOverlap());
              if (dlg.IsAlwaysVisible() == true)
                obj->SetLabelAlwaysVisible();
              else
                obj->SetLabelScaleVisibility(dlg.GetMinScale(),
                                             dlg.GetMaxScale());
            }
          MainFrame->UpdateLayerParams(obj);
          Changed = true;
          MainFrame->RefreshMap();
        }
    }
}

void MyLayerTree::OnCmdGraphics(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - setting the Layer graphics
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  MyImageList symbols;
  MyImageList patterns;
  MainFrame->GetSymbolBitmaps(&symbols);
  MainFrame->GetPatternBitmaps(&patterns);
  if (obj->GetType() == VECTOR_LAYER)
    {
      if (obj->GetGeometryType() == LAYER_POINT)
        {
          PointGraphicsDialog dlg;
          dlg.Create(MainFrame, obj->GetTableName(), obj->GetGeometryColumn(),
                     obj->GetDescName(), obj->GetSymbolId(),
                     obj->GetForegroundColor(), obj->GetBackgroundColor());
          int ret = dlg.ShowModal();
          if (ret == wxID_OK)
            {
              if (dlg.IsColorSymbol() == true)
                obj->SetPointGraphics(dlg.GetSymbolId());
              else
                obj->SetPointGraphics(dlg.GetSymbolId(),
                                      dlg.GetForegroundColor(),
                                      dlg.GetBackgroundColor());
              obj->SetDescName(dlg.GetDescName());
              MainFrame->UpdateLayerParams(obj);
              SetItemImage(CurrentItem, -1);
              obj->UpdateLayerIcon(Images, 32, 16, &symbols, &patterns);
              SetItemImage(CurrentItem, GetIconIndex(obj));
              UpdateDefault(CurrentItem, Images, &symbols, &patterns);
              Changed = true;
              MainFrame->RefreshMap();
            }
        }
      if (obj->GetGeometryType() == LAYER_LINESTRING)
        {
          LineGraphicsDialog dlg;
          dlg.Create(MainFrame, obj->GetTableName(), obj->GetGeometryColumn(),
                     obj->GetDescName(), obj->GetLineColor(),
                     obj->GetLineThickness(), obj->GetLineStyle());
          int ret = dlg.ShowModal();
          if (ret == wxID_OK)
            {
              obj->SetLineGraphics(dlg.GetLineColor(), dlg.GetLineThickness(),
                                   dlg.GetLineStyle());
              obj->SetDescName(dlg.GetDescName());
              MainFrame->UpdateLayerParams(obj);
              SetItemImage(CurrentItem, -1);
              obj->UpdateLayerIcon(Images, 32, 16, &symbols, &patterns);
              SetItemImage(CurrentItem, GetIconIndex(obj));
              UpdateDefault(CurrentItem, Images, &symbols, &patterns);
              Changed = true;
              MainFrame->RefreshMap();
            }
        }
      if (obj->GetGeometryType() == LAYER_POLYGON)
        {
          PolygonGraphicsDialog dlg;
          if (obj->DrawBorderOk() == false)
            {
              if (obj->SolidFillingOk() == true)
                {
                  dlg.Create(MainFrame, obj->GetTableName(),
                             obj->GetGeometryColumn(), obj->GetDescName(),
                             obj->GetFillColor());
              } else
                {
                  dlg.Create(MainFrame, obj->GetTableName(),
                             obj->GetGeometryColumn(), obj->GetDescName(),
                             obj->GetPatternId(), obj->GetFillColor());
                }
          } else
            {
              if (obj->IsToFill() == false)
                {
                  dlg.Create(MainFrame, obj->GetTableName(),
                             obj->GetGeometryColumn(), obj->GetDescName(),
                             obj->GetLineColor(), obj->GetLineThickness(),
                             obj->GetLineStyle());
              } else
                {
                  if (obj->SolidFillingOk() == true)
                    {
                      dlg.Create(MainFrame, obj->GetTableName(),
                                 obj->GetGeometryColumn(), obj->GetDescName(),
                                 obj->GetLineColor(), obj->GetLineThickness(),
                                 obj->GetLineStyle(), obj->GetFillColor());
                  } else
                    {
                      dlg.Create(MainFrame, obj->GetTableName(),
                                 obj->GetGeometryColumn(), obj->GetDescName(),
                                 obj->GetLineColor(), obj->GetLineThickness(),
                                 obj->GetLineStyle(), obj->GetPatternId(),
                                 obj->GetFillColor());
                    }
                }
            }
          int ret = dlg.ShowModal();
          if (ret == wxID_OK)
            {
              if (dlg.DrawBorderOk() == false)
                {
                  if (dlg.SolidFillingOk() == true)
                    {
                      obj->SetPolygonGraphics(dlg.GetFillColor());
                  } else
                    {
                      obj->SetPolygonGraphics(dlg.GetPatternId(),
                                              dlg.GetFillColor());
                    }
              } else
                {
                  if (dlg.IsToFill() == false)
                    {
                      obj->SetPolygonGraphics(dlg.GetBorderColor(),
                                              dlg.GetBorderThickness(),
                                              dlg.GetBorderStyle());
                  } else
                    {
                      if (dlg.SolidFillingOk() == true)
                        {
                          obj->SetPolygonGraphics(dlg.GetBorderColor(),
                                                  dlg.GetBorderThickness(),
                                                  dlg.GetBorderStyle(),
                                                  dlg.GetFillColor());
                      } else
                        {
                          obj->SetPolygonGraphics(dlg.GetBorderColor(),
                                                  dlg.GetBorderThickness(),
                                                  dlg.GetBorderStyle(),
                                                  dlg.GetPatternId(),
                                                  dlg.GetFillColor());
                        }
                    }
                }
              obj->SetDescName(dlg.GetDescName());
              MainFrame->UpdateLayerParams(obj);
              SetItemImage(CurrentItem, -1);
              obj->UpdateLayerIcon(Images, 32, 16, &symbols, &patterns);
              SetItemImage(CurrentItem, GetIconIndex(obj));
              UpdateDefault(CurrentItem, Images, &symbols, &patterns);
              Changed = true;
              MainFrame->RefreshMap();
            }
        }
    }
}

void MyLayerTree::OnCmdClassify(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - creating SubClasses
//
  SubClassesContainer subClasses;
  wxTreeItemId item;
  wxTreeItemIdValue cookie;
  int count = 0;
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER || obj->GetType() == LAYER_SUB_CLASS)
    {
      wxTreeItemId xItem = CurrentItem;
      if (obj->GetType() == LAYER_SUB_CLASS)
        {
          // SubClass: retrieving the parent Layer
          xItem = GetItemParent(CurrentItem);
          obj = (LayerObject *) GetItemData(xItem);
          if (obj == NULL)
            return;
        }
      item = GetFirstChild(xItem, cookie);
      while (item.IsOk() == true)
        {
          LayerObject *sub = (LayerObject *) GetItemData(item);
          if (sub->GetType() == LAYER_SUB_CLASS)
            count++;
          item = GetNextChild(xItem, cookie);
        }
      if (count)
        {
          // feeding the SubClasses container
          subClasses.Create(count);
          item = GetFirstChild(xItem, cookie);
          while (item.IsOk() == true)
            {
              LayerObject *sub = (LayerObject *) GetItemData(item);
              if (sub->GetType() == LAYER_SUB_CLASS)
                subClasses.Add(sub);
              item = GetNextChild(xItem, cookie);
            }
          subClasses.SetColorsIncluded();
        }
      if (obj->GetGeometryType() == LAYER_POINT)
        {
          PointLayerClassifyDialog dlg;
          dlg.Create(MainFrame, obj->GetTableName(), obj->GetGeometryColumn(),
                     obj->GetDescName(), obj->GetClassifyColumn(),
                     obj->IsUniqueValue(), obj->GetNumClasses(),
                     obj->GetClassesMinValue(), obj->GetClassesMaxValue(),
                     obj->GetClassesSymbolType(), obj->GetClassesMinSize(),
                     obj->GetClassesMaxSize(), obj->GetClassesMinColor(),
                     obj->GetClassesMaxColor(), &subClasses);
          int ret = dlg.ShowModal();
          if (ret == wxID_OK)
            {
              MainFrame->UpdateSubClassesParams(xItem, dlg.GetSubClasses(),
                                                dlg.IsUniqueValue(),
                                                dlg.GetClassifyColumn(),
                                                dlg.GetNumClasses(),
                                                dlg.GetMinValue(),
                                                dlg.GetMaxValue(),
                                                dlg.GetSymbolType(),
                                                dlg.GetSymbolMinSize(),
                                                dlg.GetSymbolMaxSize(),
                                                dlg.GetMinColor(),
                                                dlg.GetMaxColor());
              Changed = true;
              MainFrame->RefreshMap();
            }
        }
      if (obj->GetGeometryType() == LAYER_LINESTRING)
        {
          LineLayerClassifyDialog dlg;
          dlg.Create(MainFrame, obj->GetTableName(), obj->GetGeometryColumn(),
                     obj->GetDescName(), obj->GetClassifyColumn(),
                     obj->IsUniqueValue(), obj->GetNumClasses(),
                     obj->GetClassesMinValue(), obj->GetClassesMaxValue(),
                     obj->GetClassesMinSize(), obj->GetClassesMaxSize(),
                     obj->GetClassesMinColor(), obj->GetClassesMaxColor(),
                     &subClasses);
          int ret = dlg.ShowModal();
          if (ret == wxID_OK)
            {
              MainFrame->UpdateSubClassesParams(xItem, dlg.GetSubClasses(),
                                                dlg.IsUniqueValue(),
                                                dlg.GetClassifyColumn(),
                                                dlg.GetNumClasses(),
                                                dlg.GetMinValue(),
                                                dlg.GetMaxValue(), 0,
                                                dlg.GetLineMinSize(),
                                                dlg.GetLineMaxSize(),
                                                dlg.GetMinColor(),
                                                dlg.GetMaxColor());
              Changed = true;
              MainFrame->RefreshMap();
            }
        }
      if (obj->GetGeometryType() == LAYER_POLYGON)
        {
          PolygonLayerClassifyDialog dlg;
          dlg.Create(MainFrame, obj->GetTableName(), obj->GetGeometryColumn(),
                     obj->GetDescName(), obj->GetClassifyColumn(),
                     obj->IsUniqueValue(), obj->GetNumClasses(),
                     obj->GetClassesMinValue(), obj->GetClassesMaxValue(),
                     obj->GetClassesMinColor(), obj->GetClassesMaxColor(),
                     &subClasses);
          int ret = dlg.ShowModal();
          if (ret == wxID_OK)
            {
              MainFrame->UpdateSubClassesParams(xItem, dlg.GetSubClasses(),
                                                dlg.IsUniqueValue(),
                                                dlg.GetClassifyColumn(),
                                                dlg.GetNumClasses(),
                                                dlg.GetMinValue(),
                                                dlg.GetMaxValue(), 0, 0, 0,
                                                dlg.GetMinColor(),
                                                dlg.GetMaxColor());
              Changed = true;
              MainFrame->RefreshMap();
            }
        }
    }
}

void MyLayerTree::OnCmdClassesDrop(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - dropping SubClasses
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER || obj->GetType() == LAYER_SUB_CLASS)
    {
      wxTreeItemId item = CurrentItem;
      if (obj->GetType() == LAYER_SUB_CLASS)
        {
          // SubClass: retrieving the parent Layer
          item = GetItemParent(CurrentItem);
        }
      MainFrame->DropSubClasses(item);
      Changed = true;
      MainFrame->RefreshMap();
    }
}

void MyLayerTree::OnCmdUpdateStatistics(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - updating statistics
//
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    {
      MainFrame->UpdateStatistics();
      return;
    }
  if (obj->GetType() == VECTOR_LAYER)
    MainFrame->UpdateStatistics(obj->GetTableName(), obj->GetGeometryColumn());
  else if (obj->GetType() == RASTER_LAYER)
    MainFrame->UpdateStatistics(obj->GetTableName());
  else
    MainFrame->UpdateStatistics();
}

void MyLayerTree::OnCmdDumpShp(wxCommandEvent & WXUNUSED(event))
{
//
// menu event - dumping as Shapefile
//
  int ret;
  wxString path;
  wxString lastDir;
  LayerObject *obj = (LayerObject *) GetItemData(CurrentItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER)
    {
      wxFileDialog fileDialog(this, wxT("Dump Shapefile"),
                              wxT(""), wxT("shapefile.shp"),
                              wxT
                              ("Shapefile (*.shp)|*.shp|All files (*.*)|*.*"),
                              wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
                              wxDefaultPosition, wxDefaultSize, wxT("filedlg"));
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
          lastDir = file.GetPath();
          if (MainFrame->IsSetAskCharset() == false)
            {
              // using the default output charset
              MainFrame->SetLastDirectory(lastDir);
              ::wxBeginBusyCursor();
              MainFrame->DumpShapefile(path, obj->GetTableName(),
                                       obj->GetGeometryColumn(),
                                       MainFrame->GetDefaultCharset(),
                                       obj->IsLayerView());
              ::wxEndBusyCursor();
          } else
            {
              // asking the charset to be used
              DumpShpDialog dlg;
              dlg.Create(MainFrame, path, obj->GetTableName(),
                         obj->GetGeometryColumn(),
                         MainFrame->GetDefaultCharset());
              ret = dlg.ShowModal();
              if (ret == wxID_OK)
                {
                  MainFrame->SetLastDirectory(lastDir);
                  ::wxBeginBusyCursor();
                  MainFrame->DumpShapefile(path, obj->GetTableName(),
                                           obj->GetGeometryColumn(),
                                           dlg.GetCharset(),
                                           obj->IsLayerView());
                  ::wxEndBusyCursor();
                }
            }
        }
    }
}

void MyLayerTree::OnDragStart(wxTreeEvent & event)
{
//
// user event: starting DRAG [drag&drop]
//
  DraggedItem = event.GetItem();
  LayerObject *obj = (LayerObject *) GetItemData(DraggedItem);
  if (obj == NULL)
    return;
  if (obj->GetType() == VECTOR_LAYER || obj->GetType() == RASTER_LAYER)
    {
      event.Allow();
  } else
    DraggedItem = wxTreeItemId();
}

void MyLayerTree::OnDragEnd(wxTreeEvent & event)
{
//
// user event: DRAG ended [drag&drop]
//
  LayerObject *obj = (LayerObject *) GetItemData(DraggedItem);
  if (obj == NULL)
    return;
  wxTreeItemId currentItem = event.GetItem();
  if (currentItem == Root)
    ;
  else
    {
      wxTreeItemId parent = GetItemParent(currentItem);
      if (parent == Root)
        ;
      else
        {
          // this is a child node, so the active item is the parent
          currentItem = parent;
        }
    }
// 
// creating the new node
//
  wxTreeItemId position;
  wxString name;
  if (obj->GetDescName().Len() > 0)
    name = obj->GetDescName();
  else
    {
      name = obj->GetTableName();
      if (obj->GetType() == VECTOR_LAYER)
        {
          name += wxT(".");
          name += obj->GetGeometryColumn();
        }
    }
  if (currentItem == Root)
    position = PrependItem(Root, name);
  else if (currentItem == GetLastChild(Root))
    position = AppendItem(Root, name);
  else
    position = InsertItem(Root, currentItem, name);
  SetItemData(position, (wxTreeItemData *) (new LayerObject(obj)));
  Delete(DraggedItem);
  DraggedItem = wxTreeItemId();
  MainFrame->UpdateZOrder();
  MainFrame->InitLayerTree();
  Changed = true;
  MainFrame->RefreshMap();
}

int MyLayerTree::GetIconIndex(LayerObject * obj)
{
//
// identifying the current Icon Index for some layer
//
  if (obj->GetType() == LAYER_SUB_CLASS)
    {
      if (obj->IsVisible() == true)
        return obj->GetIconIndex();
      else
        return Images->GetImageCount() - 1;
    }
  if (obj->IsVisible() == true)
    {
      if (obj->GetType() == RASTER_LAYER)
        return 4;
      if (obj->GetGeometryType() == LAYER_POINT)
        return 1;
      if (obj->GetGeometryType() == LAYER_LINESTRING)
        {
          if (obj->IsNetwork() == true)
            return 5;
          else
            return 2;
        }
      if (obj->GetGeometryType() == LAYER_POLYGON)
        return 3;
  } else
    {
      if (obj->GetType() == RASTER_LAYER)
        return 9;
      if (obj->GetGeometryType() == LAYER_POINT)
        return 6;
      if (obj->GetGeometryType() == LAYER_LINESTRING)
        {
          if (obj->IsNetwork() == true)
            return 10;
          else
            return 7;
        }
      if (obj->GetGeometryType() == LAYER_POLYGON)
        return 8;
    }
  return 0;
}

void MyLayerTree::BuildLayersList(MapLayersList * list)
{
//
// building an updated Layers List
//
  LayerObject *obj;
  wxTreeItemId layer;
  wxTreeItemIdValue cookie;
  wxTreeItemId subClass;
  wxTreeItemIdValue subCookie;
  Changed = false;
  list->Flush();
  layer = GetFirstChild(Root, cookie);
  while (layer.IsOk() == true)
    {
      // inserting a Layer
      obj = (LayerObject *) GetItemData(layer);
      if (obj != NULL)
        list->Add(obj);
      subClass = GetFirstChild(layer, subCookie);
      while (subClass.IsOk() == true)
        {
          obj = (LayerObject *) GetItemData(subClass);
          if (obj != NULL)
            {
              // inserting a Layer Sub Class
              if (obj->GetType() == LAYER_SUB_CLASS)
                list->Add(obj);
            }
          subClass = GetNextChild(layer, subCookie);
        }
      layer = GetNextChild(Root, cookie);
    }
}

void MyLayerTree::UpdateLayersEditMode(MapLayersList * list)
{
//
// updating the Edit Mode for the current Layers List
//
  LayerObject *obj;
  wxTreeItemId layer;
  wxTreeItemIdValue cookie;
  layer = GetFirstChild(Root, cookie);
  while (layer.IsOk() == true)
    {
      // retrieving the layers, one at each time
      obj = (LayerObject *) GetItemData(layer);
      if (obj != NULL)
        {
          if (obj->GetType() == VECTOR_LAYER)
            {
              bool mode = true;
              if (obj->IsEditingEnabled() == true)
                mode = false;
              list->UpdateEditMode(obj->GetTableName(),
                                   obj->GetGeometryColumn(), mode);
              MainFrame->EnableDrawTools();
            }
        }
      layer = GetNextChild(Root, cookie);
    }
}

void MyLayerTree::UpdateDefault(wxTreeItemId item, wxImageList * Images,
                                MyImageList * symbols, MyImageList * patterns)
{
//
// updating the Default child
//
  LayerObject *obj;
  LayerObject *dflt;
  wxTreeItemId subClass;
  wxTreeItemIdValue cookie;
  obj = (LayerObject *) GetItemData(item);
  if (!obj)
    return;
  subClass = GetFirstChild(item, cookie);
  while (subClass.IsOk() == true)
    {
      dflt = (LayerObject *) GetItemData(subClass);
      if (dflt != NULL)
        {
          if (dflt->IsDefault() == true)
            {
              dflt->UpdateDefault(obj);
              dflt->UpdateLayerIcon(Images, 32, 16, symbols, patterns);
              SetItemImage(subClass, dflt->GetIconIndex());
            }
        }
      subClass = GetNextChild(item, cookie);
    }
}

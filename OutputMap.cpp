/*
/ OutputMap.cpp
/ Map output functions
/
/ version 1.0, 2009 October 24
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
#include "wx/filename.h"
#include "wx/clipbrd.h"
#include "wx/strconv.h"

#ifdef HAVE_GEOTIFF_GEOTIFF_H
#include <geotiff/geotiff.h>
#include <geotiff/xtiffio.h>
#include <geotiff/geo_tiffp.h>
#include <geotiff/geo_keyp.h>
#include <geotiff/geovalues.h>
#include <geotiff/geo_normalize.h>
#elif HAVE_LIBGEOTIFF_GEOTIFF_H
#include <libgeotiff/geotiff.h>
#include <libgeotiff/xtiffio.h>
#include <libgeotiff/geo_tiffp.h>
#include <libgeotiff/geo_keyp.h>
#include <libgeotiff/geovalues.h>
#include <libgeotiff/geo_normalize.h>
#else
#include <geotiff.h>
#include <xtiffio.h>
#include <geo_tiffp.h>
#include <geo_keyp.h>
#include <geovalues.h>
#include <geo_normalize.h>
#endif

#include <setjmp.h>

#include <spatialite.h>
#include <spatialite/gaiaexif.h>

jmp_buf pdf_env;

MyMapOutput::MyMapOutput(MyFrame * parent, MapLayersList * layers, int width,
                         int height, double minX, double minY, double maxX,
                         double maxY)
{
// constructor - SVG export
  IconvObj = NULL;
  MainFrame = parent;
  LayersList = layers;
  BitmapWidth = width;
  BitmapHeight = height;
  IsSvg = true;
  IsPdf = false;
  IsCopyToClipboard = false;
  RasterFormat = -1;
  IsWorldFile = false;
  FrameMinX = minX;
  FrameMinY = minY;
  FrameMaxX = maxX;
  FrameMaxY = maxY;
  PixelRatio = 0.0;
  CurrentScale = 0;
  BackgroundColor = wxColour(255, 255, 255);
  ComputeScale();
}

MyMapOutput::MyMapOutput(MyFrame * parent, MapLayersList * layers, int width,
                         int height, double minX, double minY, double maxX,
                         double maxY, bool a3, bool landscape, int dpi)
{
// constructor - PDF export
  IconvObj = iconv_open("CP1252", "UTF-8");
  MainFrame = parent;
  LayersList = layers;
  BitmapWidth = width;
  BitmapHeight = height;
  IsSvg = false;
  IsPdf = true;
  IsCopyToClipboard = false;
  RasterFormat = -1;
  IsWorldFile = false;
  FrameMinX = minX;
  FrameMinY = minY;
  FrameMaxX = maxX;
  FrameMaxY = maxY;
  PdfPageSizeA3 = a3;
  PdfLandscape = landscape;
  PdfDpi = dpi;
  PixelRatio = 0.0;
  CurrentScale = 0;
  BackgroundColor = wxColour(255, 255, 255);
}

MyMapOutput::MyMapOutput(MyFrame * parent, MapLayersList * layers, int width,
                         int height, double minX, double minY, double maxX,
                         double maxY, wxColour & background)
{
// constructor - Copy to Clipboad
  IconvObj = NULL;
  MainFrame = parent;
  LayersList = layers;
  BitmapWidth = width;
  BitmapHeight = height;
  IsSvg = false;
  IsPdf = false;
  IsCopyToClipboard = true;
  RasterFormat = -1;
  IsWorldFile = false;
  FrameMinX = minX;
  FrameMinY = minY;
  FrameMaxX = maxX;
  FrameMaxY = maxY;
  PixelRatio = 0.0;
  CurrentScale = 0;
  BackgroundColor = background;
  ComputeScale();
}

MyMapOutput::MyMapOutput(MyFrame * parent, MapLayersList * layers, int width,
                         int height, int format, double minX, double minY,
                         double maxX, double maxY, wxColour & background,
                         bool worldFile)
{
// constructor - RASTER Image export
  IconvObj = NULL;
  MainFrame = parent;
  LayersList = layers;
  BitmapWidth = width;
  BitmapHeight = height;
  IsSvg = false;
  IsPdf = false;
  IsCopyToClipboard = false;
  RasterFormat = format;
  IsWorldFile = worldFile;
  FrameMinX = minX;
  FrameMinY = minY;
  FrameMaxX = maxX;
  FrameMaxY = maxY;
  PixelRatio = 0.0;
  CurrentScale = 0;
  BackgroundColor = background;
  ComputeScale();
}

void MyMapOutput::ComputeScale()
{
// computing the current Ratio and Scale
  double extentX = FrameMaxX - FrameMinX;
  double extentY = FrameMaxY - FrameMinY;
  if (BitmapHeight > BitmapWidth)
    PixelRatio = extentY / BitmapHeight;
  else
    PixelRatio = extentX / BitmapWidth;
  if (MainFrame->GetProjectCrs().IsGeographic() == true)
    {
      // geographic coordinates
      double cm = PixelRatio * 72.0 * 0.3937;
      CurrentScale = (int) (cm * 11113200.0);
  } else
    {
      // planar coordinates
      double cm = PixelRatio * 72.0 * 0.3937;
      CurrentScale = (int) (cm * 100.0);
    }
}

void MyMapOutput::ComputeScale(HPDF_Page page)
{
// computing the current Ratio and Scale for PDF
  double extentX = FrameMaxX - FrameMinX;
  double extentY = FrameMaxY - FrameMinY;
  PdfPageWidth = HPDF_Page_GetWidth(page);
  PdfPageHeight = HPDF_Page_GetHeight(page);
  if (PdfDpi == 300)
    {
      // setting 300dpi resolution
      HPDF_Page_Concat(page, 72.0 / 300.0, 0, 0, 72.0 / 300.0, 0, 0);
      PdfPageWidth = (PdfPageWidth / 72.0) * 300.0;
      PdfPageHeight = (PdfPageHeight / 72.0) * 300.0;
    }
  if (PdfDpi == 600)
    {
      // setting 600dpi resolution
      HPDF_Page_Concat(page, 72.0 / 600.0, 0, 0, 72.0 / 600.0, 0, 0);
      PdfPageWidth = (PdfPageWidth / 72.0) * 600.0;
      PdfPageHeight = (PdfPageHeight / 72.0) * 600.0;
    }
  double x_ratio = extentX / PdfPageWidth;
  double y_ratio = extentY / PdfPageHeight;
  if (x_ratio > y_ratio)
    PixelRatio = x_ratio;
  else
    PixelRatio = y_ratio;
  if (MainFrame->GetProjectCrs().IsGeographic() == true)
    {
      // geographic coordinates
      double cm = PixelRatio * 72 * 0.3937;
      CurrentScale = (int) (cm * 11113200.0);
  } else
    {
      // planar coordinates
      double cm = PixelRatio * 72 * 0.3937;
      CurrentScale = (int) (cm * 100.0);
    }
// creating a new frame centered on the page
  double centerX = FrameMinX + (extentX / 2.0);
  double centerY = FrameMinY + (extentY / 2.0);
  extentX = PdfPageWidth * PixelRatio;
  extentY = PdfPageHeight * PixelRatio;
  FrameMinX = centerX - (extentX / 2.0);
  FrameMaxX = centerX + (extentX / 2.0);
  FrameMinY = centerY - (extentY / 2.0);
  FrameMaxY = centerY + (extentY / 2.0);
}

MyMapOutput::~MyMapOutput()
{
  if (LayersList)
    delete LayersList;
  if (IconvObj)
    iconv_close(IconvObj);
}

bool MyMapOutput::ToLatin1(wxString & str, char **buf)
{
//
// converting to Latin-1 ISO-8859-1
//
  char utf8buf[1024];
  char latin_buf[1024];
  size_t utf8len;
  size_t latin_len;
#if !defined(__MINGW32__) && defined(_WIN32)
  const char *pUtf8buf;
#else /* not WIN32 */
  char *pUtf8buf;
#endif
  char *pLatinBuf;
  strcpy(utf8buf, str.ToUTF8());
  utf8len = strlen(utf8buf);
  latin_len = 1024;
  pUtf8buf = utf8buf;
  pLatinBuf = latin_buf;
  if (iconv(IconvObj, &pUtf8buf, &utf8len, &pLatinBuf, &latin_len) ==
      (size_t) (-1))
    return false;
  latin_buf[1024 - latin_len] = '\0';
  memcpy(*buf, latin_buf, (1024 - latin_len) + 1);
  return true;
}

void MyMapOutput::OutputSvgMap()
{
//
// exporting an SVG Map
//
  int ret;
  wxString lastDir;
  wxString fileList;
  MapLayer *layer;
  MapLabel *pL;
  int tag;
  char label[1024];
  wxBitmap *bmp;
  wxMemoryDC *dc;
  wxGraphicsContext *gr;
  if (IsSvg == false)
    return;
  fileList = wxT("SVG file (*.svg)|*.svg");
  wxFileDialog fileDialog(MainFrame, wxT("saving the Output Map as SVG"),
                          wxT(""), wxT("OutputMap"), fileList,
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
                          wxDefaultPosition, wxDefaultSize, wxT("filedlg"));
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      bool error = false;
      bool labels = false;
      char path[4096];
      wxString xPath;
      double opacity;
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      MainFrame->SetLastDirectory(lastDir);
      xPath = file.GetPath();
      xPath += file.GetPathSeparator();
      xPath += file.GetName();
      xPath += wxT(".svg");
      strcpy(path, xPath.ToUTF8());

      ::wxBeginBusyCursor();

      FILE *svg = fopen(path, "wb");
      if (!svg)
        {
          error = true;
          goto stop;
        }
      // SVG header
      fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
      fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" ");
      fprintf(svg, "xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
      fprintf(svg, " version=\"1.2\" baseProfile=\"tiny\"");
      fprintf(svg,
              " width=\"%d\" height=\"%d\" viewBox=\"%1.8f %1.8f %1.8f %1.8f\" >\n",
              BitmapWidth, BitmapHeight, FrameMinX, FrameMaxY * -1.0,
              FrameMaxX - FrameMinX, FrameMaxY - FrameMinY);
      fprintf(svg, "<desc>Spatialite-GIS output map</desc>\n");

      layer = LayersList->GetFirst();
      while (layer)
        {
          if (layer->IsVisible() == false)
            {
              // skipping an hidden layer
              layer = layer->GetNext();
              continue;
            }
          if (layer->IsVisible(CurrentScale) == false)
            {
              // hidden at the current scale
              layer = layer->GetNext();
              continue;
            }
          if (layer->GetType() == VECTOR_LAYER)
            {
              SvgVectorLayer(svg, layer);
              if (layer->HasMapLabels() == true)
                labels = true;
            }
          layer = layer->GetNext();
        }

      if (labels == true)
        {
          // creating the Map Label List
          bmp = new wxBitmap(BitmapWidth, BitmapHeight);
          dc = new wxMemoryDC(*bmp);
          if (dc->IsOk() == false)
            {
              delete dc;
              return;
            }
          gr = wxGraphicsContext::Create(*dc);

          // drawing the map Layers [following the zOrder]
          MapLabelList *labelList = new MapLabelList(PixelRatio);
          // feeding the labels into the list
          layer = LayersList->GetFirst();
          while (layer)
            {
              if (layer->GetType() != VECTOR_LAYER)
                {
                  // skipping non-vector layers
                  layer = layer->GetNext();
                  continue;
                }
              if (layer->IsVisible() == false)
                {
                  // skipping an hidden layer
                  layer = layer->GetNext();
                  continue;
                }
              if (layer->IsVisible(CurrentScale) == false)
                {
                  // hidden at the current scale
                  layer = layer->GetNext();
                  continue;
                }
              if (layer->AreLabelsVisible(CurrentScale) == false)
                {
                  // no labels at the current scale
                  layer = layer->GetNext();
                  continue;
                }
              if (layer->HasMapLabels() == true)
                FeedMapLabels(gr, layer, labelList);
              layer = layer->GetNext();
            }
          // placing labels avoiding collisions [when required]
          labelList->CheckCollisions();
          delete gr;
          delete dc;
          delete bmp;
          // drawing the Map Labels
          fprintf(svg, "\t<defs>\n");
          tag = 0;
          pL = labelList->GetFirst();
          while (pL)
            {
              // exporting Label paths
              if (pL->IsValid() == true)
                {
                  double x0;
                  double y0;
                  double x1;
                  double y1;
                  pL->GetBaseline(&x0, &y0, &x1, &y1);
                  sprintf(label, "M %1.6f %1.6f L %1.6f %1.6f", x0, y0 * -1.0,
                          x1, y1 * -1.0);
                  fprintf(svg, "\t\t<path id=\"tp%d\" d=\"%s\" />\n", ++tag,
                          label);
                }
              pL = pL->GetNext();
            }
          fprintf(svg, "\t</defs>\n");
          tag = 0;
          pL = labelList->GetFirst();
          while (pL)
            {
              // drawing Map Labels
              if (pL->IsValid() == true)
                {
                  layer = pL->GetLayer();

                  double sz = layer->GetLabelPointSize() * (PixelRatio / 1.25);
                  fprintf(svg,
                          "\t<text font-family=\"Verdana\" font-size=\"%1.8f\" ",
                          sz);
                  if (layer->IsLabelFontItalic() == true)
                    fprintf(svg, "font-style=\"italic\" ");
                  else
                    fprintf(svg, "font-style=\"normal\" ");
                  if (layer->IsLabelFontBold() == true)
                    fprintf(svg, "font-weight=\"bold\" ");
                  else
                    fprintf(svg, "font-weight=\"normal\" ");
                  opacity = (double) (layer->GetLabelColor().Alpha()) / 255.0;
                  fprintf(svg,
                          "fill=\"#%02x%02x%02x\" fill-opacity=\"%1.2f\" >\n",
                          layer->GetLabelColor().Red(),
                          layer->GetLabelColor().Green(),
                          layer->GetLabelColor().Blue(), opacity);
                  strcpy(label, pL->GetLabel().ToUTF8());
                  fprintf(svg,
                          "\t\t\t<textPath xlink:href = \"#tp%d\">%s</textPath>\n",
                          ++tag, label);
                  fprintf(svg, "\t</text>\n");
                }
              pL = pL->GetNext();
            }
          // destroyng the label list
          delete labelList;
        }

      fprintf(svg, "</svg>\n");
      fclose(svg);

    stop:
      ::wxEndBusyCursor();
      if (error == true)
        {
          wxString msg =
            wxT("An error occurred while saving\nthe Output Map as SVG");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                       MainFrame);
      } else
        {
          wxString msg =
            wxT("The Output Map image was succesfully saved as SVG");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                       MainFrame);
        }
    }
}

static void
pdf_error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
  bool *error = (bool *) user_data;
  *error = true;
  fprintf(stderr, "PDF ERROR: error_no=%04X, detail_no=%u\n",
          (HPDF_UINT) error_no, (HPDF_UINT) detail_no);
  fflush(stderr);
  longjmp(pdf_env, 1);
}

void MyMapOutput::OutputPdfMap()
{
//
// exporting a PDF Map
//
  MapLayer *layer;
  HPDF_Doc pdf;
  HPDF_Page page;
  HPDF_Font font;
  bool error = false;
  wxString fileList;
  wxString lastDir;
  int ret;
  bool labels;
  MapLabel *pL;
  char label[1024];
  char path[4096];
  wxString xPath;
  fileList = wxT("PDF document (*.pdf)|*.pdf");
  wxFileDialog fileDialog(MainFrame, wxT("saving the PDF document"),
                          wxT(""), wxT("OutputMap"), fileList,
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
                          wxDefaultPosition, wxDefaultSize, wxT("filedlg"));

  if (IsPdf == false)
    return;

// creating the PDF context
  pdf = HPDF_New(pdf_error_handler, &error);
  if (!pdf)
    {
      fprintf(stderr, "ERROR: unable to initialize the PDF engine\n");
      goto stop;
      return;
    }
  if (setjmp(pdf_env))
    {
      HPDF_Free(pdf);
      goto stop;
      return;
    }
// setting up the PDF document
  HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);
  page = HPDF_AddPage(pdf);
  if (PdfPageSizeA3 == true)
    {
      if (PdfLandscape == true)
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A3, HPDF_PAGE_LANDSCAPE);
      else
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A3, HPDF_PAGE_PORTRAIT);
  } else
    {
      if (PdfLandscape == true)
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
      else
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    }
  ComputeScale(page);

// drawing the map Layers [following the zOrder]

  ::wxBeginBusyCursor();

  layer = LayersList->GetFirst();
  labels = false;
  while (layer)
    {
      if (layer->IsVisible() == false)
        {
          // skipping an hidden layer
          layer = layer->GetNext();
          continue;
        }
      if (layer->IsVisible(CurrentScale) == false)
        {
          // hidden at the current scale
          layer = layer->GetNext();
          continue;
        }
      if (layer->GetType() == VECTOR_LAYER)
        {
          PdfVectorLayer(pdf, page, layer);
          if (layer->HasMapLabels() == true)
            labels = true;
        }
      if (layer->GetType() == RASTER_LAYER)
        PdfRasterLayer(pdf, page, layer);
      layer = layer->GetNext();
    }

  if (labels == true)
    {
      // drawing the map Layers [following the zOrder]
      MapLabelList *labelList = new MapLabelList(PixelRatio);
      // feeding the labels into the list
      layer = LayersList->GetFirst();
      while (layer)
        {
          if (layer->GetType() != VECTOR_LAYER)
            {
              // skipping non-vector layers
              layer = layer->GetNext();
              continue;
            }
          if (layer->IsVisible() == false)
            {
              // skipping an hidden layer
              layer = layer->GetNext();
              continue;
            }
          if (layer->IsVisible(CurrentScale) == false)
            {
              // hidden at the current scale
              layer = layer->GetNext();
              continue;
            }
          if (layer->AreLabelsVisible(CurrentScale) == false)
            {
              // no labels at the current scale
              layer = layer->GetNext();
              continue;
            }
          if (layer->HasMapLabels() == true)
            FeedMapLabels(pdf, page, layer, labelList);
          layer = layer->GetNext();
        }
      // placing labels avoiding collisions [when required]
      labelList->CheckCollisions();
      // drawing the Map Labels
      pL = labelList->GetFirst();
      while (pL)
        {
          // drawing Map Labels
          if (pL->IsValid() == true)
            {
              char *p = label;
              if (ToLatin1(pL->GetLabel(), &p) == false)
                goto skip_label;
              layer = pL->GetLayer();
              if (layer->IsLabelFontItalic() == true
                  && layer->IsLabelFontBold() == true)
                font = HPDF_GetFont(pdf, "Helvetica-BoldOblique", "CP1252");
              else if (layer->IsLabelFontItalic() == true)
                font = HPDF_GetFont(pdf, "Helvetica-Oblique", "CP1252");
              else if (layer->IsLabelFontBold() == true)
                font = HPDF_GetFont(pdf, "Helvetica-Bold", "CP1252");
              else
                font = HPDF_GetFont(pdf, "Helvetica", "CP1252");
              double szFactor = (72.0 / (double) PdfDpi) * 1.5;
              double sz = layer->GetLabelPointSize() / szFactor;
              HPDF_Page_SetFontAndSize(page, font, sz);
              double r = layer->GetLabelColor().Red() / 255.0;
              double g = layer->GetLabelColor().Green() / 255.0;
              double b = layer->GetLabelColor().Blue() / 255.0;
              HPDF_Page_SetRGBFill(page, r, g, b);
              if (layer->IsLabelFontOutlined() == true)
                {
                  HPDF_Page_SetTextRenderingMode(page, HPDF_FILL_THEN_STROKE);
                  HPDF_Page_SetRGBStroke(page, 1.0, 1.0, 1.0);
              } else
                HPDF_Page_SetTextRenderingMode(page, HPDF_FILL);
              double x0;
              double y0;
              double x1;
              double y1;
              pL->GetBaseline(&x0, &y0, &x1, &y1);
              double x = ((x0 - FrameMinX) / PixelRatio);
              double y = ((y0 - FrameMinY) / PixelRatio);
              HPDF_Page_GSave(page);
              HPDF_Page_Concat(page, cos(pL->GetRotation()),
                               sin(pL->GetRotation()), -sin(pL->GetRotation()),
                               cos(pL->GetRotation()), x, y);
              HPDF_Page_BeginText(page);
              HPDF_Page_ShowText(page, label);
              HPDF_Page_EndText(page);
              HPDF_Page_GRestore(page);
            }
        skip_label:
          pL = pL->GetNext();
        }
      // destroyng the label list
      delete labelList;
    }

  ::wxEndBusyCursor();

// asking an output path
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      MainFrame->SetLastDirectory(lastDir);
      xPath = file.GetPath();
      xPath += file.GetPathSeparator();
      xPath += file.GetName();
      xPath += wxT(".pdf");
      strcpy(path, xPath.ToUTF8());
// saving the PDF document and then exiting
      ::wxBeginBusyCursor();
      HPDF_SaveToFile(pdf, path);
      ::wxEndBusyCursor();
      wxString msg =
        wxT("The Output Map image was succesfully saved as a PDF document");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                   MainFrame);
    }
stop:
  HPDF_Free(pdf);
  if (error == true)
    {
      wxString msg =
        wxT("An error occurred while saving\nthe Output Map as a PDF document");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
    }
}

void MyMapOutput::OutputRasterMap()
{
//
// exporting a Raster Map
//
  if (IsSvg == true || IsPdf == true)
    return;
  wxMemoryDC *dc = NULL;

  Bitmap = wxBitmap(BitmapWidth, BitmapHeight);
  dc = new wxMemoryDC(Bitmap);
  if (dc->IsOk() == false)
    {
      delete dc;
      return;
    }
// initializing the bitmap background
  dc->SetBrush(wxBrush(BackgroundColor));
  dc->DrawRectangle(0, 0, BitmapWidth, BitmapHeight);

// drawing the map Layers [following the zOrder]
  wxGraphicsContext *gr = wxGraphicsContext::Create(*dc);
  LayersList->CreateGraphicResources(gr);

  ::wxBeginBusyCursor();

  MapLayer *layer = LayersList->GetFirst();
  bool labels = false;
  while (layer)
    {
      if (layer->IsVisible() == false)
        {
          // skipping an hidden layer
          layer = layer->GetNext();
          continue;
        }
      if (layer->IsVisible(CurrentScale) == false)
        {
          // hidden at the current scale
          layer = layer->GetNext();
          continue;
        }
      if (layer->GetType() == VECTOR_LAYER)
        {
          DrawVectorLayer(gr, layer);
          if (layer->HasMapLabels() == true)
            labels = true;
        }
      if (layer->GetType() == RASTER_LAYER)
        DrawRasterLayer(gr, layer);
      layer = layer->GetNext();
    }
  if (labels == true)
    {
      // creating the Map Label List
      MapLabelList *labelList = new MapLabelList(PixelRatio);
      // feeding the labels into the list
      layer = LayersList->GetFirst();
      while (layer)
        {
          if (layer->GetType() != VECTOR_LAYER)
            {
              // skipping non-vector layers
              layer = layer->GetNext();
              continue;
            }
          if (layer->IsVisible() == false)
            {
              // skipping an hidden layer
              layer = layer->GetNext();
              continue;
            }
          if (layer->IsVisible(CurrentScale) == false)
            {
              // hidden at the current scale
              layer = layer->GetNext();
              continue;
            }
          if (layer->AreLabelsVisible(CurrentScale) == false)
            {
              // no labels at the current scale
              layer = layer->GetNext();
              continue;
            }
          if (layer->HasMapLabels() == true)
            FeedMapLabels(gr, layer, labelList);
          layer = layer->GetNext();
        }
      // placing labels avoiding collisions [when required]
      labelList->CheckCollisions();
      // drawing the Map Labels
      wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
      MapOutliner *outliner = new MapOutliner(BitmapWidth, BitmapHeight, font);
      MapLabel *pL = labelList->GetFirst();
      while (pL)
        {
          // drawing Map Labels Outlines
          if (pL->IsValid() == true)
            {
              if (pL->GetLayer()->IsLabelFontOutlined() == true)
                {
                  double x = (pL->GetX() - FrameMinX) / PixelRatio;
                  double y =
                    (double) BitmapHeight -
                    ((pL->GetY() - FrameMinY) / PixelRatio);
                  outliner->Draw(pL->GetLayer(), pL->GetLabel(), x, y,
                                 pL->GetRotation());
                }
            }
          pL = pL->GetNext();
        }
      outliner->Outline();
      if (outliner->IsValid() == true)
        gr->DrawBitmap(*(outliner->GetBitmap()), 0, 0, BitmapWidth,
                       BitmapHeight);
      delete outliner;
      pL = labelList->GetFirst();
      while (pL)
        {
          // drawing Map Labels
          if (pL->IsValid() == true)
            {
              MapLayer *layer = pL->GetLayer();
              double x = (pL->GetX() - FrameMinX) / PixelRatio;
              double y =
                (double) BitmapHeight - ((pL->GetY() - FrameMinY) / PixelRatio);
              font.SetPointSize(layer->GetLabelPointSize());
              if (layer->IsLabelFontBold() == true)
                font.SetWeight(wxFONTWEIGHT_BOLD);
              else
                font.SetWeight(wxFONTWEIGHT_NORMAL);
              if (layer->IsLabelFontItalic() == true)
                font.SetStyle(wxFONTSTYLE_ITALIC);
              else
                font.SetStyle(wxFONTSTYLE_NORMAL);
              font.SetUnderlined(layer->IsLabelFontUnderlined());
              gr->SetFont(font, pL->GetLayer()->GetLabelColor());
              gr->DrawText(pL->GetLabel(), x, y, pL->GetRotation());
            }
          pL = pL->GetNext();
        }
      // destroyng the label list
      delete labelList;
    }
  delete gr;
  delete dc;

  ::wxEndBusyCursor();
  if (IsCopyToClipboard == true)
    DoCopyToClipboard();
  else
    DoOutputImage();
}

void MyMapOutput::DoOutputImage()
{
// exporting the image file
  int ret;
  wxString lastDir;
  wxString fileList;
  if (RasterFormat == wxBITMAP_TYPE_PNG)
    fileList = wxT("PNG Image (*.png)|*.png");
  if (RasterFormat == wxBITMAP_TYPE_TIF)
    fileList = wxT("TIFF Image (*.tif)|*.tif");
  if (RasterFormat == wxBITMAP_TYPE_JPEG)
    fileList = wxT("JPEG Image (*.jpg)|*.jpg");
  wxFileDialog fileDialog(MainFrame, wxT("saving the Output Map image"),
                          wxT(""), wxT("OutputMap"), fileList,
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
                          wxDefaultPosition, wxDefaultSize, wxT("filedlg"));
  lastDir = MainFrame->GetLastDirectory();
  if (lastDir.Len() >= 1)
    fileDialog.SetDirectory(lastDir);
  ret = fileDialog.ShowModal();
  if (ret == wxID_OK)
    {
      wxFileName file(fileDialog.GetPath());
      lastDir = file.GetPath();
      MainFrame->SetLastDirectory(lastDir);
      wxString path = file.GetPath();
      path += file.GetPathSeparator();
      path += file.GetName();
      if (RasterFormat == wxBITMAP_TYPE_PNG)
        path += wxT(".png");
      if (RasterFormat == wxBITMAP_TYPE_TIF)
        path += wxT(".tif");
      if (RasterFormat == wxBITMAP_TYPE_JPEG)
        path += wxT(".jpg");

      wxImage img = Bitmap.ConvertToImage();
      ::wxInitAllImageHandlers();
      bool error = false;
      // generating any other image format
      ::wxBeginBusyCursor();
      if (img.SaveFile(path, RasterFormat) == false)
        error = true;
      if (error == false && IsWorldFile == true)
        {
          // generating a World File as well
          wxString worldFilePath = path.Truncate(path.Len() - 4);
          if (RasterFormat == wxBITMAP_TYPE_PNG)
            worldFilePath += wxT(".pgw");
          if (RasterFormat == wxBITMAP_TYPE_TIF)
            worldFilePath += wxT(".tfw");
          if (RasterFormat == wxBITMAP_TYPE_JPEG)
            worldFilePath += wxT(".jgw");
          if (GenerateWorldFile(worldFilePath) == false)
            error = true;
        }
      ::wxEndBusyCursor();
      if (error == true)
        {
          wxString msg =
            wxT("An error occurred while saving\nthe Output Map image");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                       MainFrame);
      } else
        {
          wxString msg = wxT("The Output Map image was succesfully saved");
          wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                       MainFrame);
        }
    }
}

bool MyMapOutput::GenerateWorldFile(wxString & xpath)
{
// generating a World File
  char path[4096];
  FILE *out;
  strcpy(path, xpath.ToUTF8());
  out = fopen(path, "wb");
  if (!out)
    return false;
  fprintf(out, "%1.8f\r\n", PixelRatio);
  fprintf(out, "0.0\r\n");
  fprintf(out, "0.0\r\n");
  fprintf(out, "-%1.8f\r\n", PixelRatio);
  fprintf(out, "%1.8f\r\n", FrameMinX);
  fprintf(out, "%1.8f\r\n", FrameMaxY);
  fclose(out);
  return true;
}

void MyMapOutput::DoCopyToClipboard()
{
// copying into the clipboard
  bool error = false;
  if (wxTheClipboard->Open())
    {
      if (wxTheClipboard->SetData(new wxBitmapDataObject(Bitmap)) == false)
        error = true;
      wxTheClipboard->Close();
  } else
    error = true;
  if (error == true)
    {
      wxString msg =
        wxT
        ("An error occurred while copying\nthe Output Map image into the clipboard");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
  } else
    {
      wxString msg =
        wxT("The Output Map image was succesfully\ncopied into the clipboard");
      wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_INFORMATION,
                   MainFrame);
    }
}

void MyMapOutput::DrawRasterLayer(wxGraphicsContext * gr, MapLayer * layer)
{
//
// drawing a Raster Layer
//
  if (!layer->GetRasterliteHandle())
    {
      // trying to open the RasterLite data source
      char db_path[1024];
      char table_prefix[1024];
      int len;
      void *handle;
      if (MainFrame->IsMemoryDatabase() == true)
        strcpy(db_path, ":memory:");
      else
        MainFrame->ConvertString(MainFrame->GetSqlitePath(), db_path, &len);
      MainFrame->ConvertString(layer->GetTableName(), table_prefix, &len);
      handle = rasterliteOpen(db_path, table_prefix);
      if (rasterliteIsError(handle))
        {
          rasterliteClose(handle);
          return;
        }
      rasterliteSetTransparentColor(handle, 255, 255, 255);
      rasterliteSetBackgroundColor(handle, 255, 255, 255);
      layer->SetRasterliteHandle(handle);
      ::wxInitAllImageHandlers();
    }
// trying to get the raster background image from the RasterLite data source
  wxBitmap bmp(wxImage(BitmapWidth, BitmapHeight));
  if (GetRaster(layer->GetRasterliteHandle(), &bmp) == false)
    {
      // error: marking a Magenta rectangle
      gr->SetBrush(wxBrush(wxColour(255, 0, 192)));
      gr->SetPen(wxPen(wxColour(192, 64, 192)));
      gr->DrawRectangle(0, 0, BitmapWidth, BitmapHeight);
      return;
    }
// drawing the raster background
  gr->DrawBitmap(bmp, 0, 0, BitmapWidth, BitmapHeight);
}

void MyMapOutput::DrawVectorLayer(wxGraphicsContext * gr, MapLayer * layer)
{
//
// drawing a Vector Layer
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  bool hasClasses = false;
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;
  double frameMinX = FrameMinX;
  double frameMaxX = FrameMaxX;
  double frameMinY = FrameMinY;
  double frameMaxY = FrameMaxY;
  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           MainFrame);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMaxY);
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      frameMinX = geom->MinX;
      frameMaxX = geom->MaxX;
      frameMinY = geom->MinY;
      frameMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += layer->GetGeometryColumn();
  if (layer->GetClassifyColumn().Len() > 0)
    {
      sql += wxT("\", \"");
      sql += layer->GetClassifyColumn();
      hasClasses = true;
    }
  sql += wxT("\" FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE ");
  if (layer->IsLayerVirtual() == true)
    {
      // handling a VirtualShape
      sql += wxT("MbrIntersects(\"");
      sql += effectiveGeometry;
      sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  } else
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT("MbrIntersects(\"");
          sql += effectiveGeometry;
          sql += wxT("\", BuildMbr(?, ?, ?, ?))");
        }
    }
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, MainFrame);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 1, frameMaxX);
      sqlite3_bind_double(stmt, 2, frameMinX);
      sqlite3_bind_double(stmt, 3, frameMaxY);
      sqlite3_bind_double(stmt, 4, frameMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 1, frameMinX);
      sqlite3_bind_double(stmt, 2, frameMinY);
      sqlite3_bind_double(stmt, 3, frameMaxX);
      sqlite3_bind_double(stmt, 4, frameMaxY);
    }

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          gaiaGeomCollPtr geom = NULL;
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              if (reproject == true)
                {
                  // applying a reprojection
                  gaiaGeomCollPtr geom2 =
                    gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                              blob_size);
                  geom = gaiaTransform(geom2, proj_from, proj_to);
                  gaiaFreeGeomColl(geom2);
              } else
                geom =
                  gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                            blob_size);
            }
          if (hasClasses == true && geom)
            {
              // testing for SubClass
              int int_value;
              double dbl_value;
              char *str_value;
              wxString value;
              MapSubClass *subClass = NULL;
              if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
                {
                  int_value = sqlite3_column_int(stmt, 1);
                  dbl_value = int_value;
                  subClass = layer->GetSubClass(dbl_value);
                }
              if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
                {
                  dbl_value = sqlite3_column_double(stmt, 1);
                  subClass = layer->GetSubClass(dbl_value);
                }
              if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
                {
                  str_value = (char *) sqlite3_column_text(stmt, 1);
                  value = wxString::FromUTF8(str_value);
                  subClass = layer->GetSubClass(value);
                }
              if (subClass)
                {
                  if (subClass->IsVisible() == true)
                    {
                      // using SubClass
                      if (layer->GetGeometryType() == LAYER_POINT)
                        DrawPoint(gr, subClass, geom);
                      if (layer->GetGeometryType() == LAYER_LINESTRING)
                        DrawLinestring(gr, subClass, geom);
                      if (layer->GetGeometryType() == LAYER_POLYGON)
                        DrawPolygon(gr, subClass, geom);
                    }
                  gaiaFreeGeomColl(geom);
                  geom = NULL;
                }
            }
          if (geom)
            {
              // drawing the Default geometric entity
              if (layer->GetGeometryType() == LAYER_POINT)
                DrawPoint(gr, layer, geom);
              if (layer->GetGeometryType() == LAYER_LINESTRING)
                DrawLinestring(gr, layer, geom);
              if (layer->GetGeometryType() == LAYER_POLYGON)
                DrawPolygon(gr, layer, geom);
              if (geom)
                gaiaFreeGeomColl(geom);
            }
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, MainFrame);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

stop:
  return;
}

void MyMapOutput::FeedMapLabels(wxGraphicsContext * gr, MapLayer * layer,
                                MapLabelList * labelList)
{
//
// extracting Labels from some Layer
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;
  double frameMinX = FrameMinX;
  double frameMaxX = FrameMaxX;
  double frameMinY = FrameMinY;
  double frameMaxY = FrameMaxY;
  double labelWidth;
  double labelHeight;
  double labelDescent;
  double labelExternalLeading;
  wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
  if (layer->HasMapLabels() == false)
    return;
  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           MainFrame);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMaxY);
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      frameMinX = geom->MinX;
      frameMaxX = geom->MaxX;
      frameMinY = geom->MinY;
      frameMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += layer->GetGeometryColumn();
  sql += wxT("\", \"");
  sql += layer->GetLabelColumn();
  sql += wxT("\" FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE ");
  if (layer->IsLayerVirtual() == true)
    {
      // handling a VirtualShape
      sql += wxT("MbrIntersects(\"");
      sql += effectiveGeometry;
      sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  } else
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT("MbrIntersects(\"");
          sql += layer->GetGeometryColumn();
          sql += wxT("\", BuildMbr(?, ?, ?, ?))");
        }
    }
  if (layer->HasLabelPriority() == true)
    {
      sql += wxT(" ORDER BY \"");
      sql += layer->GetLabelOrderByColumn();
      if (layer->IsLabelOrderByDescending() == true)
        sql += wxT("\" DESC");
      else
        sql += wxT("\" ASC");
    }
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, MainFrame);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 1, frameMaxX);
      sqlite3_bind_double(stmt, 2, frameMinX);
      sqlite3_bind_double(stmt, 3, frameMaxY);
      sqlite3_bind_double(stmt, 4, frameMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 1, frameMinX);
      sqlite3_bind_double(stmt, 2, frameMinY);
      sqlite3_bind_double(stmt, 3, frameMaxX);
      sqlite3_bind_double(stmt, 4, frameMaxY);
    }

// setting up the Font
  font.SetPointSize(layer->GetLabelPointSize());
  gr->SetFont(font, layer->GetLabelColor());

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          gaiaGeomCollPtr geom = NULL;
          wxString labelValue;
          char dummy[128];
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              if (reproject == true)
                {
                  // applying a reprojection
                  gaiaGeomCollPtr geom2 =
                    gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                              blob_size);
                  geom = gaiaTransform(geom2, proj_from, proj_to);
                  gaiaFreeGeomColl(geom2);
              } else
                geom =
                  gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                            blob_size);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
            {
              sprintf(dummy, "%d", sqlite3_column_int(stmt, 1));
              labelValue = wxString::FromUTF8(dummy);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
            {
              sprintf(dummy, "%1.6f", sqlite3_column_double(stmt, 1));
              labelValue = wxString::FromUTF8(dummy);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
            {
              labelValue =
                wxString::FromUTF8((char *) sqlite3_column_text(stmt, 1));
            }
          if (geom && labelValue.Len() > 0)
            {
              gaiaMbrGeometry(geom);
              gr->GetTextExtent(labelValue, &labelWidth, &labelHeight,
                                &labelDescent, &labelExternalLeading);
              PrepareLabels(labelList, geom, layer, labelValue, labelWidth,
                            labelHeight);
            }
          if (geom)
            gaiaFreeGeomColl(geom);
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, MainFrame);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

stop:
  return;
}

void MyMapOutput::FeedMapLabels(HPDF_Doc pdf, HPDF_Page page, MapLayer * layer,
                                MapLabelList * labelList)
{
//
// extracting Labels from some Layer
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;
  double frameMinX = FrameMinX;
  double frameMaxX = FrameMaxX;
  double frameMinY = FrameMinY;
  double frameMaxY = FrameMaxY;
  HPDF_REAL labelWidth;
  double szFactor;
  double fontSize;
  if (layer->HasMapLabels() == false)
    return;
  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           MainFrame);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMaxY);
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      frameMinX = geom->MinX;
      frameMaxX = geom->MaxX;
      frameMinY = geom->MinY;
      frameMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += layer->GetGeometryColumn();
  sql += wxT("\", \"");
  sql += layer->GetLabelColumn();
  sql += wxT("\" FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE ");
  if (layer->IsLayerVirtual() == true)
    {
      // handling a VirtualShape
      sql += wxT("MbrIntersects(\"");
      sql += effectiveGeometry;
      sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  } else
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT("MbrIntersects(\"");
          sql += layer->GetGeometryColumn();
          sql += wxT("\", BuildMbr(?, ?, ?, ?))");
        }
    }
  if (layer->HasLabelPriority() == true)
    {
      sql += wxT(" ORDER BY \"");
      sql += layer->GetLabelOrderByColumn();
      if (layer->IsLabelOrderByDescending() == true)
        sql += wxT("\" DESC");
      else
        sql += wxT("\" ASC");
    }
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, MainFrame);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 1, frameMaxX);
      sqlite3_bind_double(stmt, 2, frameMinX);
      sqlite3_bind_double(stmt, 3, frameMaxY);
      sqlite3_bind_double(stmt, 4, frameMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 1, frameMinX);
      sqlite3_bind_double(stmt, 2, frameMinY);
      sqlite3_bind_double(stmt, 3, frameMaxX);
      sqlite3_bind_double(stmt, 4, frameMaxY);
    }

// setting up the Font
  HPDF_Font font;
  if (layer->IsLabelFontItalic() == true && layer->IsLabelFontBold() == true)
    font = HPDF_GetFont(pdf, "Helvetica-BoldOblique", "CP1252");
  else if (layer->IsLabelFontItalic() == true)
    font = HPDF_GetFont(pdf, "Helvetica-Oblique", "CP1252");
  else if (layer->IsLabelFontBold() == true)
    font = HPDF_GetFont(pdf, "Helvetica-Bold", "CP1252");
  else
    font = HPDF_GetFont(pdf, "Helvetica", "CP1252");
  szFactor = (72.0 / (double) PdfDpi) * 1.5;
  fontSize = layer->GetLabelPointSize() / szFactor;
  HPDF_Page_SetFontAndSize(page, font, fontSize);

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          gaiaGeomCollPtr geom = NULL;
          wxString labelValue;
          char text[1024];
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              if (reproject == true)
                {
                  // applying a reprojection
                  gaiaGeomCollPtr geom2 =
                    gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                              blob_size);
                  geom = gaiaTransform(geom2, proj_from, proj_to);
                  gaiaFreeGeomColl(geom2);
              } else
                geom =
                  gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                            blob_size);
            }
          *text = '\0';
          if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
            {
              sprintf(text, "%d", sqlite3_column_int(stmt, 1));
              labelValue = wxString::FromUTF8(text);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
            {
              sprintf(text, "%1.6f", sqlite3_column_double(stmt, 1));
              labelValue = wxString::FromUTF8(text);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
            {
              //strcpy(text, (char *) sqlite3_column_text(stmt, 1));
              labelValue =
                wxString::FromUTF8((char *) sqlite3_column_text(stmt, 1));
              char *p = text;
              if (ToLatin1(labelValue, &p) == false)
                goto skip_label;
            }
          len = strlen(text);
          if (geom && len > 0)
            {
              gaiaMbrGeometry(geom);
              HPDF_Font_MeasureText(font, (HPDF_BYTE *) text, len, 1000000000.0,
                                    fontSize, 0.0, 0.0, HPDF_FALSE,
                                    &labelWidth);
              //labelValue = wxString::FromUTF8(text);
              PrepareLabels(labelList, geom, layer, labelValue, labelWidth,
                            fontSize);
            }
        skip_label:
          if (geom)
            gaiaFreeGeomColl(geom);
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, MainFrame);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

stop:
  return;
}

bool MyMapOutput::OutsideFrame(gaiaPointPtr point)
{
// checking if this POINT is outside the current screen frame
  if (point->X < FrameMinX)
    return true;
  if (point->X > FrameMaxX)
    return true;
  if (point->Y < FrameMinY)
    return true;
  if (point->Y > FrameMaxY)
    return true;
  return false;
}

bool MyMapOutput::OutsideFrame(gaiaLinestringPtr line)
{
// checking if this LINESTRING is outside the current screen frame
  if (line->MaxX < FrameMinX)
    return true;
  if (line->MinX > FrameMaxX)
    return true;
  if (line->MaxY < FrameMinY)
    return true;
  if (line->MinY > FrameMaxY)
    return true;
  return false;
}

bool MyMapOutput::OutsideFrame(gaiaPolygonPtr polygon)
{
// checking if this POLYGON is outside the current screen frame
  if (polygon->MaxX < FrameMinX)
    return true;
  if (polygon->MinX > FrameMaxX)
    return true;
  if (polygon->MaxY < FrameMinY)
    return true;
  if (polygon->MinY > FrameMaxY)
    return true;
  return false;
}

void MyMapOutput::PrepareLabels(MapLabelList * list, gaiaGeomCollPtr geom,
                                MapLayer * layer, wxString & label,
                                double width, double height)
{
// 
// creating Labels
// - separating elementary geometries
//
  gaiaGeomCollPtr newGeom;
  gaiaPointPtr point;
  gaiaLinestringPtr line;
  gaiaLinestringPtr newLine;
  gaiaPolygonPtr polygon;
  gaiaPolygonPtr newPolygon;
  gaiaRingPtr ring;
  gaiaRingPtr newRing;
  int iv;
  double x;
  double y;
  double z;
  double m;
  point = geom->FirstPoint;
  while (point)
    {
      if (OutsideFrame(point) == true)
        {
          point = point->Next;
          continue;
        }
      newGeom = gaiaAllocGeomColl();
      newGeom->DeclaredType = GAIA_POINT;
      gaiaAddPointToGeomColl(newGeom, point->X, point->Y);
      list->Add(layer, label, newGeom, width, height,
                layer->IsLabelAntiOverlapEnabled());
      point = point->Next;
    }
  line = geom->FirstLinestring;
  while (line)
    {
      if (OutsideFrame(line) == true)
        {
          line = line->Next;
          continue;
        }
      newGeom = gaiaAllocGeomColl();
      newGeom->DeclaredType = GAIA_LINESTRING;
      newLine = gaiaAddLinestringToGeomColl(newGeom, line->Points);
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &x, &y, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &x, &y, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &x, &y, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &x, &y);
            }
          gaiaSetPoint(newLine->Coords, iv, x, y);
        }
      list->Add(layer, label, newGeom, width, height,
                layer->IsLabelAntiOverlapEnabled());
      line = line->Next;
    }
  polygon = geom->FirstPolygon;
  while (polygon)
    {
      // NOTE: we are purposely ignoring any Interior Ring
      if (OutsideFrame(polygon) == true)
        {
          polygon = polygon->Next;
          continue;
        }
      ring = polygon->Exterior;
      newGeom = gaiaAllocGeomColl();
      newGeom->DeclaredType = GAIA_POLYGON;
      newPolygon = gaiaAddPolygonToGeomColl(newGeom, ring->Points, 0);
      newRing = newPolygon->Exterior;
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &x, &y, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &x, &y, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &x, &y, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &x, &y);
            }
          gaiaSetPoint(newRing->Coords, iv, x, y);
        }
      list->Add(layer, label, newGeom, width, height,
                layer->IsLabelAntiOverlapEnabled());
      polygon = polygon->Next;
    }
}

void MyMapOutput::DrawPoint(wxGraphicsContext * gr, MapSubClass * subClass,
                            gaiaGeomCollPtr geom)
{
// drawing a POINT/MULTIPOINT geometry
  gr->SetPen(subClass->GetPen());
  gr->SetBrush(subClass->GetBrush());
  gaiaPointPtr point = geom->FirstPoint;
  while (point)
    {
      int x = (int) ((point->X - FrameMinX) / PixelRatio);
      int y = BitmapHeight - (int) ((point->Y - FrameMinY) / PixelRatio);
      if (subClass->GetSymbolType() == CLASSES_SYMBOL_SQUARE)
        gr->DrawRectangle(x - subClass->GetSize(), y - subClass->GetSize(),
                          subClass->GetSize() * 2, subClass->GetSize() * 2);
      else if (subClass->GetSymbolType() == CLASSES_SYMBOL_DIAMOND)
        {
          wxGraphicsPath path = gr->CreatePath();
          path.MoveToPoint(x, y - subClass->GetSize());
          path.AddLineToPoint(x + subClass->GetSize(), y);
          path.AddLineToPoint(x, y + subClass->GetSize());
          path.AddLineToPoint(x - subClass->GetSize(), y);
          path.AddLineToPoint(x, y - subClass->GetSize());
          gr->FillPath(path);
          gr->StrokePath(path);
      } else
        gr->DrawEllipse(x - subClass->GetSize(), y - subClass->GetSize(),
                        subClass->GetSize() * 2, subClass->GetSize() * 2);
      point = point->Next;
    }
}

void MyMapOutput::DrawPoint(wxGraphicsContext * gr, MapLayer * layer,
                            gaiaGeomCollPtr geom)
{
// drawing a POINT/MULTIPOINT geometry
  MyBitmap *symbol = layer->GetSymbol();
  gaiaPointPtr point = geom->FirstPoint;
  while (point)
    {
      int x = (int) ((point->X - FrameMinX) / PixelRatio);
      int y = BitmapHeight - (int) ((point->Y - FrameMinY) / PixelRatio);
      if (symbol == NULL)
        {
          // drawing a default marker
          gr->SetPen(layer->GetPen());
          gr->SetBrush(layer->GetBrush());
          gr->DrawEllipse(x - 2, y - 2, 4, 4);
      } else
        {
          // drawing the symbol
          gr->DrawBitmap(layer->GetBitmap(), x - symbol->GetHotPointX(),
                         y - symbol->GetHotPointY(),
                         layer->GetBitmap().GetWidth(),
                         layer->GetBitmap().GetHeight());
        }
      point = point->Next;
    }
}

void MyMapOutput::DrawLinestring(wxGraphicsContext * gr, MapSubClass * subClass,
                                 gaiaGeomCollPtr geom)
{
// drawing a LINESTRING/MULTILINESTRING geometry
  gr->SetPen(subClass->GetPen());
  gaiaLinestringPtr line = geom->FirstLinestring;
  while (line)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      wxGraphicsPath path = gr->CreatePath();
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &dx, &dy, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &dx, &dy, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = BitmapHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      gr->StrokePath(path);
      line = line->Next;
    }
}

void MyMapOutput::DrawLinestring(wxGraphicsContext * gr, MapLayer * layer,
                                 gaiaGeomCollPtr geom)
{
// drawing a LINESTRING/MULTILINESTRING geometry
  gr->SetPen(layer->GetPen());
  gaiaLinestringPtr line = geom->FirstLinestring;
  while (line)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      wxGraphicsPath path = gr->CreatePath();
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &dx, &dy, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &dx, &dy, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = BitmapHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      gr->StrokePath(path);
      line = line->Next;
    }
}

void MyMapOutput::DrawPolygon(wxGraphicsContext * gr, MapSubClass * subClass,
                              gaiaGeomCollPtr geom)
{
// drawing a POLYGON/MULTIPOLYGON geometry
  gr->SetPen(subClass->GetPen());
  gr->SetBrush(subClass->GetBrush());
  gaiaPolygonPtr polyg = geom->FirstPolygon;
  while (polyg)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      int ib;
      wxGraphicsPath path = gr->CreatePath();
      gaiaRingPtr ring = polyg->Exterior;
      // exterior border
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = BitmapHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      path.CloseSubpath();
      for (ib = 0; ib < polyg->NumInteriors; ib++)
        {
          // interior borders
          ring = polyg->Interiors + ib;
          for (iv = 0; iv < ring->Points; iv++)
            {
              if (ring->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
              } else if (ring->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
              } else if (ring->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
              } else
                {
                  gaiaGetPoint(ring->Coords, iv, &dx, &dy);
                }
              x = (int) ((dx - FrameMinX) / PixelRatio);
              y = BitmapHeight - (int) ((dy - FrameMinY) / PixelRatio);
              if (iv == 0)
                {
                  path.MoveToPoint(x, y);
                  lastX = x;
                  lastY = y;
              } else
                {
                  if (x == lastX && y == lastY)
                    ;
                  else
                    {
                      path.AddLineToPoint(x, y);
                      lastX = x;
                      lastY = y;
                    }
                }
            }
          path.CloseSubpath();
        }
      gr->FillPath(path);
      gr->StrokePath(path);
      polyg = polyg->Next;
    }
}

void MyMapOutput::DrawPolygon(wxGraphicsContext * gr, MapLayer * layer,
                              gaiaGeomCollPtr geom)
{
// drawing a POLYGON/MULTIPOLYGON geometry
  if (layer->DrawBorderOk() == true)
    gr->SetPen(layer->GetPen());
  if (layer->IsToFill() == true)
    gr->SetBrush(layer->GetBrush());
  gaiaPolygonPtr polyg = geom->FirstPolygon;
  while (polyg)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      int x;
      int y;
      int lastX = 0;
      int lastY = 0;
      int ib;
      wxGraphicsPath path = gr->CreatePath();
      gaiaRingPtr ring = polyg->Exterior;
      // exterior border
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &dx, &dy);
            }
          x = (int) ((dx - FrameMinX) / PixelRatio);
          y = BitmapHeight - (int) ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            {
              path.MoveToPoint(x, y);
              lastX = x;
              lastY = y;
          } else
            {
              if (x == lastX && y == lastY)
                ;
              else
                {
                  path.AddLineToPoint(x, y);
                  lastX = x;
                  lastY = y;
                }
            }
        }
      path.CloseSubpath();
      for (ib = 0; ib < polyg->NumInteriors; ib++)
        {
          // interior borders
          ring = polyg->Interiors + ib;
          for (iv = 0; iv < ring->Points; iv++)
            {
              if (ring->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
              } else if (ring->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
              } else if (ring->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
              } else
                {
                  gaiaGetPoint(ring->Coords, iv, &dx, &dy);
                }
              x = (int) ((dx - FrameMinX) / PixelRatio);
              y = BitmapHeight - (int) ((dy - FrameMinY) / PixelRatio);
              if (iv == 0)
                {
                  path.MoveToPoint(x, y);
                  lastX = x;
                  lastY = y;
              } else
                {
                  if (x == lastX && y == lastY)
                    ;
                  else
                    {
                      path.AddLineToPoint(x, y);
                      lastX = x;
                      lastY = y;
                    }
                }
            }
          path.CloseSubpath();
        }
      if (layer->IsToFill() == true)
        gr->FillPath(path);
      if (layer->DrawBorderOk() == true)
        gr->StrokePath(path);
      polyg = polyg->Next;
    }
}

double MyMapOutput::InternalRound(double value)
{
// replacing the C99 round() function 
  double min = floor(value);
  if (fabs(value - min) < 0.5)
    return min;
  return min + 1.0;
}

int MyMapOutput::IntRound(double value)
{
/* replacing the C99 round() function */
  double min = floor(value);
  if (fabs(value - min) < 0.5)
    return (int) min;
  return (int) (min + 1.0);
}

bool MyMapOutput::GetRaster(void *handle, wxBitmap * bmp)
{
//
// trying to build the required raster image from the RasterLite Data Source
//
  int ret;
  double pixel_x_size;
  double pixel_y_size;
  int use_rtree;
  sqlite3_stmt *stmt = NULL;
  double frameCenterX = FrameMinX + ((FrameMaxX - FrameMinX) / 2.0);
  double frameCenterY = FrameMinY + ((FrameMaxY - FrameMinY) / 2.0);
  double map_frame_width = (double) BitmapWidth * PixelRatio;
  double map_frame_height = (double) BitmapHeight * PixelRatio;
  double min_x = frameCenterX - (map_frame_width / 2.0);
  double max_x = frameCenterX + (map_frame_width / 2.0);
  double min_y = frameCenterY - (map_frame_height / 2.0);
  double max_y = frameCenterY + (map_frame_height / 2.0);
  if (handle == NULL)
    {
      fprintf(stderr, "invalid datasource\n");
      fflush(stderr);
      return false;
    }
  if (BitmapWidth < 64 || BitmapWidth > 32768 || BitmapHeight < 64
      || BitmapHeight > 32768)
    {
      fprintf(stderr, "invalid raster dims [%dh X %dv]\n", BitmapWidth,
              BitmapHeight);
      fflush(stderr);
      return false;
    }
  if (rasterliteGetBestAccess
      (handle, PixelRatio, &pixel_x_size, &pixel_y_size, &stmt,
       &use_rtree) != RASTERLITE_OK)
    {
      fprintf(stderr, "invalid Raster access method\n");
      fflush(stderr);
      return false;
    }
  wxMemoryDC *dc = NULL;
  dc = new wxMemoryDC(*bmp);
  if (dc->IsOk() == false)
    {
      delete dc;
      return false;
    }
// setting a white baground
  dc->SetBrush(wxBrush(wxColour(255, 255, 255)));
  dc->SetPen(wxPen(wxColour(255, 255, 255)));
  dc->DrawRectangle(0, 0, BitmapWidth, BitmapHeight);
// binding query params 
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (use_rtree)
    {
      // using the Spatial Index R*Tree 
      sqlite3_bind_double(stmt, 1, max_x);
      sqlite3_bind_double(stmt, 2, min_x);
      sqlite3_bind_double(stmt, 3, max_y);
      sqlite3_bind_double(stmt, 4, min_y);
  } else
    {
      // plain Table Scan 
      sqlite3_bind_double(stmt, 1, min_x);
      sqlite3_bind_double(stmt, 2, min_y);
      sqlite3_bind_double(stmt, 3, max_x);
      sqlite3_bind_double(stmt, 4, max_y);
    }
  sqlite3_bind_double(stmt, 5, pixel_x_size);
  sqlite3_bind_double(stmt, 6, pixel_y_size);
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          // retrieving query values 
          gaiaGeomCollPtr geom = NULL;
          wxImage *img = NULL;
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry 
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              geom =
                gaiaFromSpatiaLiteBlobWkb((const unsigned char *)
                                          blob, blob_size);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_BLOB)
            {
              // fetching Raster Image 
              const unsigned char *blob =
                (const unsigned char *) sqlite3_column_blob(stmt, 1);
              int blob_size = sqlite3_column_bytes(stmt, 1);
              int type = gaiaGuessBlobType(blob, blob_size);
              if (type == GAIA_JPEG_BLOB || type == GAIA_EXIF_BLOB
                  || type == GAIA_EXIF_GPS_BLOB || type == GAIA_PNG_BLOB
                  || type == GAIA_GIF_BLOB || type == GAIA_TIFF_BLOB)
                {
                  wxMemoryInputStream reader(blob, blob_size);
                  img = new wxImage(reader);
                }
            }
          if (geom && img)
            {
              // resizing the image [tile] 
              double pre_FrameWidth =
                InternalRound(((double) (img->GetWidth()) * pixel_x_size) /
                              PixelRatio);
              double pre_FrameHeight =
                InternalRound(((double) (img->GetHeight()) * pixel_y_size) /
                              PixelRatio);
              int new_FrameWidth = (int) pre_FrameWidth + 1;
              int new_FrameHeight = (int) pre_FrameHeight + 1;
              double x = (geom->MinX - min_x) / PixelRatio;
              double y =
                (double) BitmapHeight - ((geom->MaxY - min_y) / PixelRatio);
              if (new_FrameWidth > (BitmapWidth * 2)
                  || new_FrameHeight > (BitmapHeight * 2))
                {
                  // TOO BIG: drawing a gray rectangle 
                  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
                  dc->SetPen(wxPen(wxColour(192, 192, 192)));
                  dc->DrawRectangle(IntRound(x), IntRound(y), new_FrameWidth,
                                    new_FrameHeight);
              } else
                {
                  // resizing the raster tile 
                  wxImage img2(new_FrameWidth, new_FrameHeight);
                  if (new_FrameWidth == BitmapWidth
                      && new_FrameHeight == BitmapHeight)
                    img2 = img->Copy();
                  else
                    img2 =
                      img->Rescale(new_FrameWidth, new_FrameHeight,
                                   wxIMAGE_QUALITY_NORMAL);
                  // drawing the raster tile
                  wxBitmap bitmap = wxBitmap(img2);
                  wxMask *mask = new wxMask(bitmap, wxColour(255, 255, 255));
                  bitmap.SetMask(mask);
                  dc->DrawBitmap(bitmap, (wxCoord) IntRound(x),
                                 (wxCoord) IntRound(y), true);
                }
            }
          if (geom)
            gaiaFreeGeomColl(geom);
          if (img)
            delete img;
      } else
        {
          fprintf(stderr, "Raster: SQL error\n");
          fflush(stderr);
          delete dc;
          return false;
        }
    }
  delete dc;
  return true;
}

bool MyMapOutput::GetPdfRaster(void *handle, wxBitmap * bmp)
{
//
// trying to build the required raster image from the RasterLite Data Source
//
  int ret;
  double pixel_x_size;
  double pixel_y_size;
  int use_rtree;
  sqlite3_stmt *stmt = NULL;
  double frameCenterX = FrameMinX + ((FrameMaxX - FrameMinX) / 2.0);
  double frameCenterY = FrameMinY + ((FrameMaxY - FrameMinY) / 2.0);
  double map_frame_width = PdfPageWidth * PixelRatio;
  double map_frame_height = PdfPageHeight * PixelRatio;
  double min_x = frameCenterX - (map_frame_width / 2.0);
  double max_x = frameCenterX + (map_frame_width / 2.0);
  double min_y = frameCenterY - (map_frame_height / 2.0);
  double max_y = frameCenterY + (map_frame_height / 2.0);
  if (handle == NULL)
    {
      fprintf(stderr, "invalid datasource\n");
      fflush(stderr);
      return false;
    }
  if (PdfPageWidth < 64.0 || PdfPageWidth > 32768.0 || PdfPageHeight < 64.0
      || PdfPageHeight > 32768.0)
    {
      fprintf(stderr, "invalid raster dims [%dh X %dv]\n", (int) PdfPageWidth,
              (int) PdfPageHeight);
      fflush(stderr);
      return false;
    }
  if (rasterliteGetBestAccess
      (handle, PixelRatio, &pixel_x_size, &pixel_y_size, &stmt,
       &use_rtree) != RASTERLITE_OK)
    {
      fprintf(stderr, "invalid Raster access method\n");
      fflush(stderr);
      return false;
    }
  wxMemoryDC *dc = NULL;
  dc = new wxMemoryDC(*bmp);
  if (dc->IsOk() == false)
    {
      delete dc;
      return false;
    }
// setting a white baground
  dc->SetBrush(wxBrush(wxColour(255, 255, 255)));
  dc->SetPen(wxPen(wxColour(255, 255, 255)));
  dc->DrawRectangle(0, 0, (int) PdfPageWidth, (int) PdfPageHeight);
// binding query params 
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (use_rtree)
    {
      // using the Spatial Index R*Tree 
      sqlite3_bind_double(stmt, 1, max_x);
      sqlite3_bind_double(stmt, 2, min_x);
      sqlite3_bind_double(stmt, 3, max_y);
      sqlite3_bind_double(stmt, 4, min_y);
  } else
    {
      // plain Table Scan 
      sqlite3_bind_double(stmt, 1, min_x);
      sqlite3_bind_double(stmt, 2, min_y);
      sqlite3_bind_double(stmt, 3, max_x);
      sqlite3_bind_double(stmt, 4, max_y);
    }
  sqlite3_bind_double(stmt, 5, pixel_x_size);
  sqlite3_bind_double(stmt, 6, pixel_y_size);
  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          // retrieving query values 
          gaiaGeomCollPtr geom = NULL;
          wxImage *img = NULL;
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry 
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              geom =
                gaiaFromSpatiaLiteBlobWkb((const unsigned char *)
                                          blob, blob_size);
            }
          if (sqlite3_column_type(stmt, 1) == SQLITE_BLOB)
            {
              // fetching Raster Image 
              const unsigned char *blob =
                (const unsigned char *) sqlite3_column_blob(stmt, 1);
              int blob_size = sqlite3_column_bytes(stmt, 1);
              int type = gaiaGuessBlobType(blob, blob_size);
              if (type == GAIA_JPEG_BLOB || type == GAIA_EXIF_BLOB
                  || type == GAIA_EXIF_GPS_BLOB || type == GAIA_PNG_BLOB
                  || type == GAIA_GIF_BLOB || type == GAIA_TIFF_BLOB)
                {
                  wxMemoryInputStream reader(blob, blob_size);
                  img = new wxImage(reader);
                }
            }
          if (geom && img)
            {
              // resizing the image [tile] 
              double pre_FrameWidth =
                InternalRound(((double) (img->GetWidth()) * pixel_x_size) /
                              PixelRatio);
              double pre_FrameHeight =
                InternalRound(((double) (img->GetHeight()) * pixel_y_size) /
                              PixelRatio);
              int new_FrameWidth = (int) pre_FrameWidth + 1;
              int new_FrameHeight = (int) pre_FrameHeight + 1;
              double x = (geom->MinX - min_x) / PixelRatio;
              double y = PdfPageHeight - ((geom->MaxY - min_y) / PixelRatio);
              if (new_FrameWidth > (PdfPageWidth * 2)
                  || new_FrameHeight > (PdfPageHeight * 2))
                {
                  // TOO BIG: drawing a gray rectangle 
                  dc->SetBrush(wxBrush(wxColour(240, 240, 240)));
                  dc->SetPen(wxPen(wxColour(192, 192, 192)));
                  dc->DrawRectangle(IntRound(x), IntRound(y), new_FrameWidth,
                                    new_FrameHeight);
              } else
                {
                  // resizing the raster tile 
                  wxImage img2(new_FrameWidth, new_FrameHeight);
                  if (new_FrameWidth == PdfPageWidth
                      && new_FrameHeight == PdfPageHeight)
                    img2 = img->Copy();
                  else
                    img2 =
                      img->Rescale(new_FrameWidth, new_FrameHeight,
                                   wxIMAGE_QUALITY_NORMAL);
                  // drawing the raster tile
                  wxBitmap bitmap = wxBitmap(img2);
                  wxMask *mask = new wxMask(bitmap, wxColour(255, 255, 255));
                  bitmap.SetMask(mask);
                  dc->DrawBitmap(bitmap, (wxCoord) IntRound(x),
                                 (wxCoord) IntRound(y), true);
                }
            }
          if (geom)
            gaiaFreeGeomColl(geom);
          if (img)
            delete img;
      } else
        {
          fprintf(stderr, "Raster: SQL error\n");
          fflush(stderr);
          delete dc;
          return false;
        }
    }
  delete dc;
  return true;
}

void MyMapOutput::SvgVectorLayer(FILE * svg, MapLayer * layer)
{
//
// exporting a Vector Layer
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  bool hasClasses = false;
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;
  double frameMinX = FrameMinX;
  double frameMaxX = FrameMaxX;
  double frameMinY = FrameMinY;
  double frameMaxY = FrameMaxY;
  SvgClasses subSvg;

  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           MainFrame);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMaxY);
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      frameMinX = geom->MinX;
      frameMaxX = geom->MaxX;
      frameMinY = geom->MinY;
      frameMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT ");
  if (reproject == true)
    {
      sql += wxT("AsSvg(Transform(\"");
      sql += layer->GetGeometryColumn();
      char dummy[64];
      sprintf(dummy, "\", %d)", MainFrame->GetProjectCrs().GetSrid());
      sql += wxString::FromUTF8(dummy);
      if (layer->GetGeometryType() == LAYER_POINT)
        sql += wxT(")");
      else
        sql += wxT(", 1)");
  } else
    {
      sql += wxT("AsSvg(\"");
      sql += layer->GetGeometryColumn();
      if (layer->GetGeometryType() == LAYER_POINT)
        sql += wxT("\")");
      else
        sql += wxT("\", 1)");
    }
  if (layer->GetClassifyColumn().Len() > 0)
    {
      sql += wxT(", \"");
      sql += layer->GetClassifyColumn();
      sql += wxT("\"");
      hasClasses = true;
    }
  sql += wxT("FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE ");
  if (layer->IsLayerVirtual() == true)
    {
      // handling a VirtualShape
      sql += wxT("MbrIntersects(\"");
      sql += effectiveGeometry;
      sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  } else
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT("MbrIntersects(\"");
          sql += effectiveGeometry;
          sql += wxT("\", BuildMbr(?, ?, ?, ?))");
        }
    }
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, MainFrame);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 1, frameMaxX);
      sqlite3_bind_double(stmt, 2, frameMinX);
      sqlite3_bind_double(stmt, 3, frameMaxY);
      sqlite3_bind_double(stmt, 4, frameMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 1, frameMinX);
      sqlite3_bind_double(stmt, 2, frameMinY);
      sqlite3_bind_double(stmt, 3, frameMaxX);
      sqlite3_bind_double(stmt, 4, frameMaxY);
    }

// exporting the Layer group
  char table[1024];
  char geom[1024];
  char name[1024];
  double thickness;
  double opacity;
  strcpy(table, layer->GetTableName().ToUTF8());
  strcpy(geom, layer->GetGeometryColumn().ToUTF8());
  strcpy(name, layer->GetDescName().ToUTF8());
  fprintf(svg, "\t<g table=\"%s\" geometry=\"%s\" name=\"%s\" ",
          table, geom, name);
  if (layer->GetGeometryType() == LAYER_POINT)
    {
      int red;
      int green;
      int blue;
      MainFrame->GetRandomColor(&red, &green, &blue);
      wxColour strokeColor(red, green, blue);
      MainFrame->GetRandomColor(&red, &green, &blue);
      wxColour fillColor(red, green, blue);
      MyBitmap *symbol = layer->GetSymbol();
      if (symbol != NULL)
        {
          if (symbol->IsFullColor() == false)
            {
              strokeColor = layer->GetBackgroundColor();
              fillColor = layer->GetForegroundColor();
            }
        }
      fprintf(svg,
              "stroke=\"#%02x%02x%02x\" stroke-width=\"%1.8f\" stroke-opacity=\"1.0\" fill=\"#%02x%02x%02x\" fill-opacity=\"1.0\" >\n",
              strokeColor.Red(), strokeColor.Green(), strokeColor.Blue(),
              PixelRatio / 2.0, fillColor.Red(), fillColor.Green(),
              fillColor.Blue());
    }
  if (layer->GetGeometryType() == LAYER_LINESTRING)
    {
      if (layer->GetLineThickness() < 1)
        thickness = PixelRatio;
      else
        thickness = PixelRatio * layer->GetLineThickness();
      thickness /= 2.0;
      opacity = (double) (layer->GetLineColor().Alpha()) / 255.0;
      if (layer->GetLineStyle() == wxDOT
          || layer->GetLineStyle() == wxSHORT_DASH
          || layer->GetLineStyle() == wxLONG_DASH
          || layer->GetLineStyle() == wxDOT_DASH)
        {
          fprintf(svg,
                  "stroke=\"#%02x%02x%02x\" stroke-width=\"%1.8f\" stroke-opacity=\"%1.2f\" fill=\"none\"",
                  layer->GetLineColor().Red(), layer->GetLineColor().Green(),
                  layer->GetLineColor().Blue(), thickness, opacity);
          if (layer->GetLineStyle() == wxDOT)
            fprintf(svg,
                    " stroke-dasharray=\"3, 3\" stroke-dashoffst=\"0\" >\n");
          else if (layer->GetLineStyle() == wxSHORT_DASH)
            fprintf(svg,
                    " stroke-dasharray=\"6, 3\" stroke-dashoffst=\"0\" >\n");
          else if (layer->GetLineStyle() == wxLONG_DASH)
            fprintf(svg,
                    " stroke-dasharray=\"12, 6\" stroke-dashoffst=\"0\" >\n");
          else if (layer->GetLineStyle() == wxDOT_DASH)
            fprintf(svg,
                    " stroke-dasharray=\"6, 3, 3, 3\" stroke-dashoffst=\"0\" >\n");
      } else
        {
          fprintf(svg,
                  "stroke=\"#%02x%02x%02x\" stroke-width=\"%1.8f\" stroke-opacity=\"%1.2f\" fill=\"none\" >\n",
                  layer->GetLineColor().Red(), layer->GetLineColor().Green(),
                  layer->GetLineColor().Blue(), thickness, opacity);
        }
    }
  if (layer->GetGeometryType() == LAYER_POLYGON)
    {
      if (layer->DrawBorderOk())
        {
          if (layer->GetLineThickness() < 1)
            thickness = PixelRatio;
          else
            thickness = PixelRatio * layer->GetLineThickness();
          thickness /= 2.0;
          opacity = (double) (layer->GetLineColor().Alpha()) / 255.0;
          if (layer->GetLineStyle() == wxDOT
              || layer->GetLineStyle() == wxSHORT_DASH
              || layer->GetLineStyle() == wxLONG_DASH
              || layer->GetLineStyle() == wxDOT_DASH)
            {
              fprintf(svg,
                      "stroke=\"#%02x%02x%02x\" stroke-width=\"%1.8f\" stroke-opacity=\"%1.2f\" ",
                      layer->GetLineColor().Red(),
                      layer->GetLineColor().Green(),
                      layer->GetLineColor().Blue(), thickness, opacity);
              if (layer->GetLineStyle() == wxDOT)
                fprintf(svg,
                        " stroke-dasharray=\"3, 3\" stroke-dashoffst=\"0\" ");
              else if (layer->GetLineStyle() == wxSHORT_DASH)
                fprintf(svg,
                        " stroke-dasharray=\"6, 3\" stroke-dashoffst=\"0\" ");
              else if (layer->GetLineStyle() == wxLONG_DASH)
                fprintf(svg,
                        " stroke-dasharray=\"12, 6\" stroke-dashoffst=\"0\" ");
              else if (layer->GetLineStyle() == wxDOT_DASH)
                fprintf(svg,
                        " stroke-dasharray=\"6, 3, 3, 3\" stroke-dashoffst=\"0\" ");
          } else
            {
              fprintf(svg,
                      "stroke=\"#%02x%02x%02x\" stroke-width=\"%1.8f\" stroke-opacity=\"%1.2f\" ",
                      layer->GetLineColor().Red(),
                      layer->GetLineColor().Green(),
                      layer->GetLineColor().Blue(), thickness, opacity);
            }
      } else
        fprintf(svg, "stroke=\"none\" ");
      if (layer->IsToFill())
        {
          opacity = (double) (layer->GetFillColor().Alpha()) / 255.0;
          fprintf(svg, "fill=\"#%02x%02x%02x\" fill-opacity=\"%1.2f\" >\n",
                  layer->GetFillColor().Red(), layer->GetFillColor().Green(),
                  layer->GetFillColor().Blue(), opacity);
      } else
        fprintf(svg, "fill=\"none\" >\n");
    }
  subSvg.Set(layer->GetGeometryType(), PixelRatio);

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          const unsigned char *svgText = NULL;
          if (sqlite3_column_type(stmt, 0) == SQLITE_TEXT)
            {
              // fetching SVG geometry
              svgText = sqlite3_column_text(stmt, 0);
            }
          if (hasClasses == true && svgText)
            {
              // testing for SubClass
              int int_value;
              double dbl_value;
              char *str_value;
              wxString value;
              MapSubClass *subClass = NULL;
              if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
                {
                  int_value = sqlite3_column_int(stmt, 1);
                  dbl_value = int_value;
                  subClass = layer->GetSubClass(dbl_value);
                }
              if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
                {
                  dbl_value = sqlite3_column_double(stmt, 1);
                  subClass = layer->GetSubClass(dbl_value);
                }
              if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
                {
                  str_value = (char *) sqlite3_column_text(stmt, 1);
                  value = wxString::FromUTF8(str_value);
                  subClass = layer->GetSubClass(value);
                }
              if (subClass)
                {
                  if (subClass->IsVisible() == true)
                    {
                      // using SubClass
                      subSvg.Add(subClass, svgText);
                    }
                  continue;
                }
            }
          if (svgText)
            {
              // exporting the Default geometric entity
              if (layer->GetGeometryType() == LAYER_POINT)
                {
                  double radius = PixelRatio * 2.0;
                  fprintf(svg, "\t\t<circle %s r=\"%1.8f\" />\n", svgText,
                          radius);
                }
              if (layer->GetGeometryType() == LAYER_LINESTRING)
                fprintf(svg, "\t\t<path d=\"%s\" />\n", svgText);
              if (layer->GetGeometryType() == LAYER_POLYGON)
                fprintf(svg, "\t\t<path d=\"%s\" />\n", svgText);
            }
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, MainFrame);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

// outputting the sub-classes
  subSvg.Output(svg);
// closing this group [Layer]
  fprintf(svg, "\t</g>\n");

stop:
  return;
}

SvgEntity::SvgEntity(const unsigned char *svg)
{
// constructor: SVG entity
  int len = strlen((char *) svg);
  Svg = new unsigned char[len + 1];
  memcpy(Svg, svg, len + 1);
  Next = NULL;
}

SvgEntity::~SvgEntity()
{
// destructor: SVG entity
  if (Svg)
    delete[]Svg;
}

SvgClass::SvgClass(MapSubClass * subClass)
{
// constructor: SVG class
  SubClass = subClass;
  First = NULL;
  Last = NULL;
  Next = NULL;
}

SvgClass::~SvgClass()
{
// destructor: SVG class
  SvgEntity *pE;
  SvgEntity *pEn;
  pE = First;
  while (pE)
    {
      pEn = pE->GetNext();
      delete pE;
      pE = pEn;
    }
}

void SvgClass::Add(const unsigned char *svg)
{
// inserting an SVG entity
  SvgEntity *pE = new SvgEntity(svg);
  if (!First)
    First = pE;
  if (Last)
    Last->SetNext(pE);
  Last = pE;
}

SvgClasses::SvgClasses()
{
// constructor: SVG classes container
  First = NULL;
  Last = NULL;
}

SvgClasses::~SvgClasses()
{
// destructor: SVG classes container
  SvgClass *pC;
  SvgClass *pCn;
  pC = First;
  while (pC)
    {
      pCn = pC->GetNext();
      delete pC;
      pC = pCn;
    }
}

void SvgClasses::Add(MapSubClass * subClass, const unsigned char *svg)
{
// inserting an SVG entity
  SvgClass *pC;
  if (Last != NULL)
    {
      if (Last->GetSubClass() == subClass)
        {
          Last->Add(svg);
          return;
        }
    }
  pC = new SvgClass(subClass);
  pC->Add(svg);
  if (!First)
    First = pC;
  if (Last)
    Last->SetNext(pC);
  Last = pC;
}

void SvgClasses::Output(FILE * svg)
{
// outputting the SubClasses
  SvgClass *pC = First;
  while (pC)
    {
      if (pC->GetFirst())
        {
          // opening a new group [SubClass]
          if (GeometryType == LAYER_POINT)
            {
              wxColour strokeColor(255 - pC->GetSubClass()->GetColor().Red(),
                                   255 - pC->GetSubClass()->GetColor().Green(),
                                   255 - pC->GetSubClass()->GetColor().Blue());
              wxColour fillColor = pC->GetSubClass()->GetColor();
              fprintf(svg,
                      "\t\t<g stroke=\"#%02x%02x%02x\" stroke-width=\"%1.8f\" stroke-opacity=\"1.0\" fill=\"#%02x%02x%02x\" fill-opacity=\"1.0\" >\n",
                      strokeColor.Red(), strokeColor.Green(),
                      strokeColor.Blue(), PixelRatio / 2.0, fillColor.Red(),
                      fillColor.Green(), fillColor.Blue());
            }
          if (GeometryType == LAYER_LINESTRING)
            {
              double thickness = PixelRatio;
              if (pC->GetSubClass()->GetSize() >= 1)
                thickness = PixelRatio * pC->GetSubClass()->GetSize();
              thickness /= 2.0;
              double opacity =
                (double) (pC->GetSubClass()->GetColor().Alpha()) / 255.0;
              fprintf(svg,
                      "\t\t<g stroke=\"#%02x%02x%02x\" stroke-width=\"%1.8f\" stroke-opacity=\"%1.2f\" fill=\"none\" >\n",
                      pC->GetSubClass()->GetColor().Red(),
                      pC->GetSubClass()->GetColor().Green(),
                      pC->GetSubClass()->GetColor().Blue(), thickness, opacity);
            }
          if (GeometryType == LAYER_POLYGON)
            {
              fprintf(svg,
                      "\t\t<g stroke=\"#000000\" stroke-width=\"%1.8f\" stroke-opacity=\"1.0\" ",
                      PixelRatio / 2.0);
              double opacity =
                (double) (pC->GetSubClass()->GetColor().Alpha()) / 255.0;
              fprintf(svg, "fill=\"#%02x%02x%02x\" fill-opacity=\"%1.2f\" >\n",
                      pC->GetSubClass()->GetColor().Red(),
                      pC->GetSubClass()->GetColor().Green(),
                      pC->GetSubClass()->GetColor().Blue(), opacity);
            }

          SvgEntity *pE = pC->GetFirst();
          while (pE)
            {
              // exporting SVG entities
              if (GeometryType == LAYER_POINT)
                {
                  double size;
                  if (pC->GetSubClass()->GetSize() < 1)
                    size = PixelRatio;
                  else
                    size = pC->GetSubClass()->GetSize() * PixelRatio;
                  fprintf(svg, "\t\t\t<circle %s r=\"%1.8f\" />\n",
                          pE->GetSvg(), size);
                }
              if (GeometryType == LAYER_LINESTRING)
                fprintf(svg, "\t\t\t<path d=\"%s\" />\n", pE->GetSvg());
              if (GeometryType == LAYER_POLYGON)
                fprintf(svg, "\t\t\t<path d=\"%s\" />\n", pE->GetSvg());
              pE = pE->GetNext();
            }

          // closing this group [SubClass]
          fprintf(svg, "\t\t</g>\n");
        }
      pC = pC->GetNext();
    }
}

void MyMapOutput::PdfVectorLayer(HPDF_Doc pdf, HPDF_Page page, MapLayer * layer)
{
//
// drawing a Vector Layer
//
  sqlite3 *sqlite = MainFrame->GetSqlite();
  int i;
  char **results;
  int rows;
  int columns;
  char *errMsg = NULL;
  int ret;
  wxString sql;
  char *value;
  bool rTreeSpatialIndex = false;
  bool mbrCacheSpatialIndex = false;
  wxString effectiveTable;
  wxString effectiveGeometry;
  sqlite3_stmt *stmt;
  int len;
  char xSql[1024];
  bool hasClasses = false;
  char proj_from[1024];
  char proj_to[1024];
  bool reproject = false;
  double frameMinX = FrameMinX;
  double frameMaxX = FrameMaxX;
  double frameMinY = FrameMinY;
  double frameMaxY = FrameMaxY;
  PdfSymbolList pdfSymbols(pdf);
  if (layer->GetSrid() == MainFrame->GetProjectCrs().GetSrid())
    ;
  else
    {
      // this Layer uses a SRID not identical to the one set for the Project
      if (layer->GetSrid() >= 0 && MainFrame->GetProjectCrs().GetSrid() >= 0
          && layer->IsReproject() == true)
        {
          bool ok_from = MainFrame->GetProjParams(layer->GetSrid(), proj_from);
          bool ok_to =
            MainFrame->GetProjParams(MainFrame->GetProjectCrs().GetSrid(),
                                     proj_to);
          if (ok_from == true && ok_to == true)
            reproject = true;
          else
            {
              wxString msg = wxT("Unable to apply reprojection for layer:\n\n");
              msg += layer->GetTableName();
              msg += wxT(".");
              msg += layer->GetGeometryColumn();
              msg += wxT("\n\n");
              if (ok_from == false)
                msg +=
                  wxT("Please, check the Layer's SRID; it's invalid !!!\n");
              if (ok_to == false)
                msg +=
                  wxT("Please, check the Project's SRID; it's invalid !!!\n");
              wxMessageBox(msg, wxT("spatialite-gis"), wxOK | wxICON_ERROR,
                           MainFrame);
              return;
            }
        }
    }


  if (reproject == true)
    {
      // applying reprojection to current MapFrame
      gaiaGeomCollPtr geom2 = gaiaAllocGeomColl();
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMinY);
      gaiaAddPointToGeomColl(geom2, FrameMaxX, FrameMaxY);
      gaiaAddPointToGeomColl(geom2, FrameMinX, FrameMaxY);
      gaiaGeomCollPtr geom = gaiaTransform(geom2, proj_to, proj_from);
      gaiaFreeGeomColl(geom2);
      frameMinX = geom->MinX;
      frameMaxX = geom->MaxX;
      frameMinY = geom->MinY;
      frameMaxY = geom->MaxY;
      gaiaFreeGeomColl(geom);
    }
// retrieving the SpatialIndex type [if any]
  effectiveTable = layer->GetTableName();
  effectiveGeometry = layer->GetGeometryColumn();
  if (layer->IsLayerView() == false && layer->IsLayerVirtual() == false)
    {
      // layer based on a plain Table
      sql = wxT("SELECT spatial_index_enabled ");
      sql += wxT("FROM geometry_columns ");
      sql += wxT("WHERE f_table_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND f_geometry_column = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
  } else if (layer->IsLayerView() == true)
    {
      // layer based on a SpatialView
      sql =
        wxT("SELECT f_table_name, f_geometry_column, spatial_index_enabled ");
      sql += wxT("FROM views_geometry_columns ");
      sql +=
        wxT("JOIN geometry_columns USING (f_table_name, f_geometry_column) ");
      sql += wxT("WHERE view_name = '");
      sql += layer->GetTableName();
      sql += wxT("' AND view_geometry = '");
      sql += layer->GetGeometryColumn();
      sql += wxT("'");
      ret =
        sqlite3_get_table(sqlite, sql.ToUTF8(), &results, &rows, &columns,
                          &errMsg);
      if (ret != SQLITE_OK)
        {
          wxMessageBox(wxT("SQLite SQL error: ") + wxString::FromUTF8(errMsg),
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, MainFrame);
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
              effectiveTable = wxString::FromUTF8(value);
              value = results[(i * columns) + 1];
              effectiveGeometry = wxString::FromUTF8(value);
              value = results[(i * columns) + 2];
              if (value)
                {
                  if (atoi(value) == 1)
                    rTreeSpatialIndex = true;
                  if (atoi(value) == 2)
                    mbrCacheSpatialIndex = true;
                }
            }
        }
      sqlite3_free_table(results);
    }
// preparing the SQL statement
  sql = wxT("SELECT \"");
  sql += layer->GetGeometryColumn();
  if (layer->GetClassifyColumn().Len() > 0)
    {
      sql += wxT("\", \"");
      sql += layer->GetClassifyColumn();
      hasClasses = true;
    }
  sql += wxT("\" FROM \"");
  sql += layer->GetTableName();
  sql += wxT("\" WHERE ");
  if (layer->IsLayerVirtual() == true)
    {
      // handling a VirtualShape
      sql += wxT("MbrIntersects(\"");
      sql += effectiveGeometry;
      sql += wxT("\", BuildMbr(?, ?, ?, ?))");
  } else
    {
      // a layer based on a plain Table or SpatialView may support some Spatial Index
      if (rTreeSpatialIndex == true)
        {
          // using the R*Tree Spatial Index
          sql += wxT("ROWID IN (SELECT pkid FROM \"idx_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql +=
            wxT
            ("\" WHERE xmin <= ? AND xmax >= ? AND ymin <= ? AND ymax >= ?)");
      } else if (mbrCacheSpatialIndex == true)
        {
          // using the MbrCache Spatial Index
          sql += wxT("ROWID IN (SELECT rowid FROM \"cache_");
          sql += effectiveTable;
          sql += wxT("_");
          sql += effectiveGeometry;
          sql += wxT("\" WHERE mbr = FilterMbrIntersects(?, ?, ?, ?))");
      } else
        {
          // applying simple MBR filtering
          sql += wxT("MbrIntersects(\"");
          sql += effectiveGeometry;
          sql += wxT("\", BuildMbr(?, ?, ?, ?))");
        }
    }
  MainFrame->ConvertString(sql, xSql, &len);
  ret = sqlite3_prepare_v2(sqlite, xSql, len, &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, MainFrame);
      goto stop;
    }
// query params binding
  sqlite3_reset(stmt);
  sqlite3_clear_bindings(stmt);
  if (rTreeSpatialIndex == true)
    {
      // using the R*Tree Spatial Index
      sqlite3_bind_double(stmt, 1, frameMaxX);
      sqlite3_bind_double(stmt, 2, frameMinX);
      sqlite3_bind_double(stmt, 3, frameMaxY);
      sqlite3_bind_double(stmt, 4, frameMinY);
  } else
    {
      // MbrCache or simple Mbr filtering
      sqlite3_bind_double(stmt, 1, frameMinX);
      sqlite3_bind_double(stmt, 2, frameMinY);
      sqlite3_bind_double(stmt, 3, frameMaxX);
      sqlite3_bind_double(stmt, 4, frameMaxY);
    }

  while (1)
    {
      // scrolling the result set 
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE)
        break;                  // end of result set
      if (ret == SQLITE_ROW)
        {
          gaiaGeomCollPtr geom = NULL;
          if (sqlite3_column_type(stmt, 0) == SQLITE_BLOB)
            {
              // fetching Geometry
              const void *blob = sqlite3_column_blob(stmt, 0);
              int blob_size = sqlite3_column_bytes(stmt, 0);
              if (reproject == true)
                {
                  // applying a reprojection
                  gaiaGeomCollPtr geom2 =
                    gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                              blob_size);
                  geom = gaiaTransform(geom2, proj_from, proj_to);
                  gaiaFreeGeomColl(geom2);
              } else
                geom =
                  gaiaFromSpatiaLiteBlobWkb((const unsigned char *) blob,
                                            blob_size);
            }
          if (hasClasses == true && geom)
            {
              // testing for SubClass
              int int_value;
              double dbl_value;
              char *str_value;
              wxString value;
              MapSubClass *subClass = NULL;
              if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
                {
                  int_value = sqlite3_column_int(stmt, 1);
                  dbl_value = int_value;
                  subClass = layer->GetSubClass(dbl_value);
                }
              if (sqlite3_column_type(stmt, 1) == SQLITE_FLOAT)
                {
                  dbl_value = sqlite3_column_double(stmt, 1);
                  subClass = layer->GetSubClass(dbl_value);
                }
              if (sqlite3_column_type(stmt, 1) == SQLITE_TEXT)
                {
                  str_value = (char *) sqlite3_column_text(stmt, 1);
                  value = wxString::FromUTF8(str_value);
                  subClass = layer->GetSubClass(value);
                }
              if (subClass)
                {
                  if (subClass->IsVisible() == true)
                    {
                      // using SubClass
                      if (layer->GetGeometryType() == LAYER_POINT)
                        PdfPoint(page, subClass, geom);
                      if (layer->GetGeometryType() == LAYER_LINESTRING)
                        PdfLinestring(page, subClass, geom);
                      if (layer->GetGeometryType() == LAYER_POLYGON)
                        PdfPolygon(page, subClass, geom);
                    }
                  gaiaFreeGeomColl(geom);
                  geom = NULL;
                }
            }
          if (geom)
            {
              // drawing the Default geometric entity
              if (layer->GetGeometryType() == LAYER_POINT)
                PdfPoint(&pdfSymbols, page, layer, geom);
              if (layer->GetGeometryType() == LAYER_LINESTRING)
                PdfLinestring(page, layer, geom);
              if (layer->GetGeometryType() == LAYER_POLYGON)
                PdfPolygon(page, layer, geom);
              if (geom)
                gaiaFreeGeomColl(geom);
            }
      } else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(sqlite));
          wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                       wxOK | wxICON_ERROR, MainFrame);
          sqlite3_finalize(stmt);
          goto stop;
        }
    }
  sqlite3_finalize(stmt);

stop:
  return;
}

void MyMapOutput::PdfRasterLayer(HPDF_Doc pdf, HPDF_Page page, MapLayer * layer)
{
//
// drawing a Raster Layer
//
  if (!layer->GetRasterliteHandle())
    {
      // trying to open the RasterLite data source
      char db_path[1024];
      char table_prefix[1024];
      int len;
      void *handle;
      if (MainFrame->IsMemoryDatabase() == true)
        strcpy(db_path, ":memory:");
      else
        MainFrame->ConvertString(MainFrame->GetSqlitePath(), db_path, &len);
      MainFrame->ConvertString(layer->GetTableName(), table_prefix, &len);
      handle = rasterliteOpen(db_path, table_prefix);
      if (rasterliteIsError(handle))
        {
          rasterliteClose(handle);
          return;
        }
      rasterliteSetTransparentColor(handle, 255, 255, 255);
      rasterliteSetBackgroundColor(handle, 255, 255, 255);
      layer->SetRasterliteHandle(handle);
      ::wxInitAllImageHandlers();
    }
// trying to get the raster background image from the RasterLite data source
  wxBitmap bmp(wxImage((int) PdfPageWidth, (int) PdfPageHeight));
  if (GetPdfRaster(layer->GetRasterliteHandle(), &bmp) == false)
    {
      // error: marking a Magenta rectangle
      double r = 255 / 255.0;
      double g = 0 / 255.0;
      double b = 192 / 255.0;
      HPDF_Page_SetRGBFill(page, r, g, b);
      r = 192 / 255.0;
      g = 64 / 255.0;
      b = 192 / 255.0;
      HPDF_Page_SetRGBStroke(page, r, g, b);
      HPDF_Page_SetLineWidth(page, 1);
      HPDF_Page_Rectangle(page, 0, 0, PdfPageWidth, PdfPageHeight);
      return;
    }
// drawing the raster background
  wxImage img = bmp.ConvertToImage();
  HPDF_BYTE *buf = new HPDF_BYTE[img.GetWidth() * img.GetHeight() * 3];
  HPDF_BYTE *p = buf;
  int x;
  int y;
  for (y = 0; y < img.GetHeight(); y++)
    {
      for (x = 0; x < img.GetWidth(); x++)
        {
          *(p++) = img.GetRed(x, y);
          *(p++) = img.GetGreen(x, y);
          *(p++) = img.GetBlue(x, y);
        }
    }
  HPDF_Image handle =
    HPDF_LoadRawImageFromMem(pdf, buf, img.GetWidth(), img.GetHeight(),
                             HPDF_CS_DEVICE_RGB, 8);
  delete[]buf;
  HPDF_Page_DrawImage(page, handle, 0, 0, PdfPageWidth, PdfPageHeight);
}

void MyMapOutput::PdfPoint(HPDF_Page page, MapSubClass * subClass,
                           gaiaGeomCollPtr geom)
{
// drawing a POINT/MULTIPOINT geometry
  double r = subClass->GetColor().Red() / 255.0;
  double g = subClass->GetColor().Green() / 255.0;
  double b = subClass->GetColor().Blue() / 255.0;
  double szFactor = (72.0 / (double) PdfDpi) * 2.0;
  double sz = subClass->GetSize() / szFactor;
  HPDF_Page_SetRGBFill(page, r, g, b);
  r = 1.0 - r;
  g = 1.0 - g;
  b = 1.0 - b;
  HPDF_Page_SetRGBStroke(page, r, g, b);
  HPDF_Page_SetLineWidth(page, 1);
  gaiaPointPtr point = geom->FirstPoint;
  while (point)
    {
      double x = ((point->X - FrameMinX) / PixelRatio);
      double y = ((point->Y - FrameMinY) / PixelRatio);
      if (subClass->GetSymbolType() == CLASSES_SYMBOL_SQUARE)
        HPDF_Page_Rectangle(page, x - sz, y - sz, sz * 2, sz * 2);
      else if (subClass->GetSymbolType() == CLASSES_SYMBOL_DIAMOND)
        {
          HPDF_Page_MoveTo(page, x, y - sz);
          HPDF_Page_LineTo(page, x + sz, y);
          HPDF_Page_LineTo(page, x, y + sz);
          HPDF_Page_LineTo(page, x - sz, y);
          HPDF_Page_LineTo(page, x, y - sz);
      } else
        HPDF_Page_Circle(page, x, y, sz);
      HPDF_Page_FillStroke(page);
      point = point->Next;
    }
}

void MyMapOutput::PdfPoint(PdfSymbolList * list, HPDF_Page page,
                           MapLayer * layer, gaiaGeomCollPtr geom)
{
// drawing a POINT/MULTIPOINT geometry
  double szFactor = (72.0 / (double) PdfDpi) * 2.0;
  PdfSymbol *pdfSym = list->Add(layer->GetSymbol());
  gaiaPointPtr point = geom->FirstPoint;
  while (point)
    {
      double x = ((point->X - FrameMinX) / PixelRatio);
      double y = ((point->Y - FrameMinY) / PixelRatio);
      if (pdfSym == NULL)
        {
          double r = layer->GetForegroundColor().Red() / 255.0;
          double g = layer->GetForegroundColor().Green() / 255.0;
          double b = layer->GetForegroundColor().Blue() / 255.0;
          HPDF_Page_SetRGBFill(page, r, g, b);
          r = layer->GetBackgroundColor().Red() / 255.0;
          g = layer->GetBackgroundColor().Green() / 255.0;
          b = layer->GetBackgroundColor().Blue() / 255.0;
          HPDF_Page_SetRGBStroke(page, r, g, b);
          HPDF_Page_SetLineWidth(page, 1);
          double sz = 2.0 / szFactor;
          HPDF_Page_Circle(page, x, y, sz);
          HPDF_Page_FillStroke(page);
      } else
        {
          double hotPointX = layer->GetSymbol()->GetHotPointX() / szFactor;
          double hotPointY = layer->GetSymbol()->GetHotPointY() / szFactor;
          double width = pdfSym->GetWidth() / szFactor;
          double height = pdfSym->GetHeight() / szFactor;
          HPDF_Page_DrawImage(page, pdfSym->GetHandle(), x - hotPointX,
                              y - hotPointY, width, height);
        }
      point = point->Next;
    }
}

void MyMapOutput::PdfLinestring(HPDF_Page page, MapSubClass * subClass,
                                gaiaGeomCollPtr geom)
{
// drawing a LINESTRING/MULTILINESTRING geometry
  double r = subClass->GetColor().Red() / 255.0;
  double g = subClass->GetColor().Green() / 255.0;
  double b = subClass->GetColor().Blue() / 255.0;
  HPDF_Page_SetRGBStroke(page, r, g, b);
  HPDF_Page_SetLineWidth(page, subClass->GetSize());
  gaiaLinestringPtr line = geom->FirstLinestring;
  while (line)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      double x;
      double y;
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &dx, &dy, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &dx, &dy, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &dx, &dy);
            }
          x = ((dx - FrameMinX) / PixelRatio);
          y = ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            HPDF_Page_MoveTo(page, x, y);
          else
            HPDF_Page_LineTo(page, x, y);
        }
      HPDF_Page_Stroke(page);
      line = line->Next;
    }
}

void MyMapOutput::PdfLinestring(HPDF_Page page, MapLayer * layer,
                                gaiaGeomCollPtr geom)
{
// drawing a LINESTRING/MULTILINESTRING geometry
  double r = layer->GetLineColor().Red() / 255.0;
  double g = layer->GetLineColor().Green() / 255.0;
  double b = layer->GetLineColor().Blue() / 255.0;
  HPDF_UINT16 dash_ptn[4];
  HPDF_Page_SetRGBStroke(page, r, g, b);
  HPDF_Page_SetLineWidth(page, layer->GetLineThickness());
  if (layer->GetLineStyle() == wxDOT)
    {
      dash_ptn[0] = 3;
      HPDF_Page_SetDash(page, dash_ptn, 1, 0);
  } else if (layer->GetLineStyle() == wxSHORT_DASH)
    {
      dash_ptn[0] = 6;
      dash_ptn[1] = 3;
      HPDF_Page_SetDash(page, dash_ptn, 2, 0);
  } else if (layer->GetLineStyle() == wxLONG_DASH)
    {
      dash_ptn[0] = 12;
      dash_ptn[1] = 6;
      HPDF_Page_SetDash(page, dash_ptn, 2, 0);
  } else if (layer->GetLineStyle() == wxDOT_DASH)
    {
      dash_ptn[0] = 6;
      dash_ptn[1] = 3;
      dash_ptn[2] = 3;
      dash_ptn[3] = 3;
      HPDF_Page_SetDash(page, dash_ptn, 4, 0);
  } else
    HPDF_Page_SetDash(page, NULL, 0, 0);
  gaiaLinestringPtr line = geom->FirstLinestring;
  while (line)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      double x;
      double y;
      for (iv = 0; iv < line->Points; iv++)
        {
          if (line->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(line->Coords, iv, &dx, &dy, &z);
          } else if (line->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(line->Coords, iv, &dx, &dy, &m);
          } else if (line->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(line->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(line->Coords, iv, &dx, &dy);
            }
          x = ((dx - FrameMinX) / PixelRatio);
          y = ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            HPDF_Page_MoveTo(page, x, y);
          else
            HPDF_Page_LineTo(page, x, y);
        }
      HPDF_Page_Stroke(page);
      line = line->Next;
    }
}

void MyMapOutput::PdfPolygon(HPDF_Page page, MapSubClass * subClass,
                             gaiaGeomCollPtr geom)
{
// drawing a POLYGON/MULTIPOLYGON geometry
  double r;
  double g;
  double b;
  HPDF_Page_SetRGBStroke(page, 0.0, 0.0, 0.0);
  HPDF_Page_SetLineWidth(page, 1.0);
  gaiaPolygonPtr polyg = geom->FirstPolygon;
  while (polyg)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      double x;
      double y;
      int ib;
      gaiaRingPtr ring = polyg->Exterior;
      // exterior border
      r = subClass->GetColor().Red() / 255.0;
      g = subClass->GetColor().Green() / 255.0;
      b = subClass->GetColor().Blue() / 255.0;
      HPDF_Page_SetRGBFill(page, r, g, b);
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &dx, &dy);
            }
          x = ((dx - FrameMinX) / PixelRatio);
          y = ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            HPDF_Page_MoveTo(page, x, y);
          else
            HPDF_Page_LineTo(page, x, y);
        }
      HPDF_Page_FillStroke(page);
      // filling any internal hole in white
      HPDF_Page_SetRGBFill(page, 1.0, 1.0, 1.0);
      for (ib = 0; ib < polyg->NumInteriors; ib++)
        {
          // interior borders
          ring = polyg->Interiors + ib;
          for (iv = 0; iv < ring->Points; iv++)
            {
              if (ring->DimensionModel == GAIA_XY_Z)
                {
                  gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
              } else if (ring->DimensionModel == GAIA_XY_M)
                {
                  gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
              } else if (ring->DimensionModel == GAIA_XY_Z_M)
                {
                  gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
              } else
                {
                  gaiaGetPoint(ring->Coords, iv, &dx, &dy);
                }
              x = ((dx - FrameMinX) / PixelRatio);
              y = ((dy - FrameMinY) / PixelRatio);
              if (iv == 0)
                HPDF_Page_MoveTo(page, x, y);
              else
                HPDF_Page_LineTo(page, x, y);
            }
          HPDF_Page_FillStroke(page);
        }
      polyg = polyg->Next;
    }
}

void MyMapOutput::PdfPolygon(HPDF_Page page, MapLayer * layer,
                             gaiaGeomCollPtr geom)
{
// drawing a POLYGON/MULTIPOLYGON geometry
  double r;
  double g;
  double b;
  HPDF_UINT16 dash_ptn[4];
  if (layer->DrawBorderOk() == true)
    {
      r = layer->GetLineColor().Red() / 255.0;
      g = layer->GetLineColor().Green() / 255.0;
      b = layer->GetLineColor().Blue() / 255.0;
      HPDF_Page_SetRGBStroke(page, r, g, b);
      HPDF_Page_SetLineWidth(page, layer->GetLineThickness());
      if (layer->GetLineStyle() == wxDOT)
        {
          dash_ptn[0] = 3;
          HPDF_Page_SetDash(page, dash_ptn, 1, 0);
      } else if (layer->GetLineStyle() == wxSHORT_DASH)
        {
          dash_ptn[0] = 6;
          dash_ptn[1] = 3;
          HPDF_Page_SetDash(page, dash_ptn, 2, 0);
      } else if (layer->GetLineStyle() == wxLONG_DASH)
        {
          dash_ptn[0] = 12;
          dash_ptn[1] = 6;
          HPDF_Page_SetDash(page, dash_ptn, 2, 0);
      } else if (layer->GetLineStyle() == wxDOT_DASH)
        {
          dash_ptn[0] = 6;
          dash_ptn[1] = 3;
          dash_ptn[2] = 3;
          dash_ptn[3] = 3;
          HPDF_Page_SetDash(page, dash_ptn, 4, 0);
      } else
        HPDF_Page_SetDash(page, NULL, 0, 0);
    }
  gaiaPolygonPtr polyg = geom->FirstPolygon;
  while (polyg)
    {
      int iv;
      double dx;
      double dy;
      double z;
      double m;
      double x;
      double y;
      int ib;
      gaiaRingPtr ring = polyg->Exterior;
      // exterior border
      if (layer->IsToFill() == true)
        {
          r = layer->GetFillColor().Red() / 255.0;
          g = layer->GetFillColor().Green() / 255.0;
          b = layer->GetFillColor().Blue() / 255.0;
          HPDF_Page_SetRGBFill(page, r, g, b);
        }
      for (iv = 0; iv < ring->Points; iv++)
        {
          if (ring->DimensionModel == GAIA_XY_Z)
            {
              gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
          } else if (ring->DimensionModel == GAIA_XY_M)
            {
              gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
          } else if (ring->DimensionModel == GAIA_XY_Z_M)
            {
              gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
          } else
            {
              gaiaGetPoint(ring->Coords, iv, &dx, &dy);
            }
          x = ((dx - FrameMinX) / PixelRatio);
          y = ((dy - FrameMinY) / PixelRatio);
          if (iv == 0)
            HPDF_Page_MoveTo(page, x, y);
          else
            HPDF_Page_LineTo(page, x, y);
        }
      if (layer->IsToFill() == true && layer->DrawBorderOk() == true)
        HPDF_Page_FillStroke(page);
      else if (layer->IsToFill() == true)
        HPDF_Page_Fill(page);
      else if (layer->DrawBorderOk() == true)
        HPDF_Page_Stroke(page);
      if (layer->IsToFill() == true)
        {
          // filling any internal hole in white
          HPDF_Page_SetRGBFill(page, 1.0, 1.0, 1.0);
          for (ib = 0; ib < polyg->NumInteriors; ib++)
            {
              // interior borders
              ring = polyg->Interiors + ib;
              for (iv = 0; iv < ring->Points; iv++)
                {
                  if (ring->DimensionModel == GAIA_XY_Z)
                    {
                      gaiaGetPointXYZ(ring->Coords, iv, &dx, &dy, &z);
                  } else if (ring->DimensionModel == GAIA_XY_M)
                    {
                      gaiaGetPointXYM(ring->Coords, iv, &dx, &dy, &m);
                  } else if (ring->DimensionModel == GAIA_XY_Z_M)
                    {
                      gaiaGetPointXYZM(ring->Coords, iv, &dx, &dy, &z, &m);
                  } else
                    {
                      gaiaGetPoint(ring->Coords, iv, &dx, &dy);
                    }
                  x = ((dx - FrameMinX) / PixelRatio);
                  y = ((dy - FrameMinY) / PixelRatio);
                  if (iv == 0)
                    HPDF_Page_MoveTo(page, x, y);
                  else
                    HPDF_Page_LineTo(page, x, y);
                }
              if (layer->DrawBorderOk() == true)
                HPDF_Page_FillStroke(page);
              else
                HPDF_Page_Fill(page);
            }
        }
      polyg = polyg->Next;
    }
}

PdfSymbol::PdfSymbol(HPDF_Doc pdf, MyBitmap * symbol)
{
//
// creating a PDF symbol
//
  Symbol = symbol;
  Next = NULL;
// preparing the RAW image
  int x;
  int y;
  wxBitmap bmp =
    symbol->GetBitmap().
    GetSubBitmap(wxRect(0, 0, symbol->GetBitmap().GetWidth(),
                        symbol->GetBitmap().GetHeight()));

  wxMask *mask = new wxMask(Symbol->GetMask());
  bmp.SetMask(mask);
  wxImage img = bmp.ConvertToImage();
  Width = img.GetWidth();
  Height = img.GetHeight();
  HPDF_BYTE *buf = new HPDF_BYTE[Width * Height * 3];
  HPDF_BYTE *p = buf;
  for (y = 0; y < Height; y++)
    {
      for (x = 0; x < Width; x++)
        {
          *(p++) = img.GetRed(x, y);
          *(p++) = img.GetGreen(x, y);
          *(p++) = img.GetBlue(x, y);
        }
    }
  Handle =
    HPDF_LoadRawImageFromMem(pdf, buf, Width, Height, HPDF_CS_DEVICE_RGB, 8);
  delete[]buf;
// setting up the image mask
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  img.GetOrFindMaskColour(&red, &green, &blue);
  HPDF_Image_SetColorMask(Handle, red, red, green, green, blue, blue);
}

PdfSymbolList::PdfSymbolList(HPDF_Doc pdf)
{
//
// creating a PDF symbol list
//
  Pdf = pdf;
  First = NULL;
  Last = NULL;
}

PdfSymbolList::~PdfSymbolList()
{
//
// deleting a PDF symbol list
//
  PdfSymbol *pSn;
  PdfSymbol *pS = First;
  while (pS)
    {
      pSn = pS->GetNext();
      delete pS;
      pS = pSn;
    }
}

PdfSymbol *PdfSymbolList::Add(MyBitmap * symbol)
{
// appending (or retrieving) a symbol
  if (!symbol)
    return NULL;
  PdfSymbol *pS = First;
  while (pS)
    {
      if (pS->GetSymbol()->GetId() == symbol->GetId())
        return pS;
      pS = pS->GetNext();
    }
  pS = new PdfSymbol(Pdf, symbol);
  if (!First)
    First = pS;
  if (Last)
    Last->SetNext(pS);
  Last = pS;
  return pS;
}

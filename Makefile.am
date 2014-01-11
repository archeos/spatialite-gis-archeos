ACLOCAL_AMFLAGS = -I m4

CXXFLAGS += @LIBSPATIALITE_CFLAGS@ #LIBRASTERLITA_CFLAGS@ \
	@LIBPNG_CFLAGS@ @LIBFREEXL_LIBS@

bin_PROGRAMS = spatialite_gis

INCLUDES = @CFLAGS@

spatialite_gis_SOURCES = Bitmaps.cpp Classdef.h ClassifyDlgs.cpp \
	Dialogs.cpp GraphicsDlgs.cpp LayerTree.cpp Main.cpp \
	MapDynamic.cpp MapView.cpp MetadataInit.cpp Network.cpp \
	Objects.cpp OutputMap.cpp Shapefiles.cpp SqlHelpers.cpp \
	TableDialogs.cpp

if MINGW
LDADD = @WX_LIBS@ @LIBSPATIALITE_LIBS@ @LIBRASTERLITE_LIBS@ @LIBFREEXL_LIBS@ \
	-lgdiplus
else
LDADD = @WX_LIBS@ @LIBSPATIALITE_LIBS@ @LIBRASTERLITE_LIBS@ @LIBFREEXL_LIBS@
endif

EXTRA_DIST = Makefile-static-MinGW \
        Makefile-static-Linux \
        Makefile-static-MacOsX \
	indent_me

AUTOMAKE_OPTIONS = dist-zip

SUBDIRS = color_symbols icons osm_symbols patterns symbols \
	win_resource  gnome_resource

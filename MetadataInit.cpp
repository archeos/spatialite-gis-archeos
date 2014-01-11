/*
/ MetadataInit.cpp
/ ancillary methods used to create and feed the Spatial Metadata tables
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

bool MyFrame::CreateSpatialMetaData()
{
// creating and feeding the Spatial MetaData tables
  struct epsg_defs
  {
    int srid;
    const char *auth_name;
    int auth_srid;
    const char *ref_sys_name;
    const char *proj4text;
  } epsg[] =
  {
    {
    3819, "epsg", 3819, "HD1909",
        "+proj=longlat +ellps=bessel +towgs84=595.48,121.69,515.35,4.115,-2.9383,0.853,-3.408 +no_defs"},
    {
    3821, "epsg", 3821, "TWD67", "+proj=longlat +ellps=aust_SA +no_defs"},
    {
    3824, "epsg", 3824, "TWD97",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    3889, "epsg", 3889, "IGRS",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    3906, "epsg", 3906, "MGI 1901", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4001, "epsg", 4001, "Unknown datum based upon the Airy 1830 ellipsoid",
        "+proj=longlat +ellps=airy +no_defs"},
    {
    4002, "epsg", 4002,
        "Unknown datum based upon the Airy Modified 1849 ellipsoid",
        "+proj=longlat +ellps=mod_airy +no_defs"},
    {
    4003, "epsg", 4003,
        "Unknown datum based upon the Australian National Spheroid",
        "+proj=longlat +ellps=aust_SA +no_defs"},
    {
    4004, "epsg", 4004, "Unknown datum based upon the Bessel 1841 ellipsoid",
        "+proj=longlat +ellps=bessel +no_defs"},
    {
    4005, "epsg", 4005,
        "Unknown datum based upon the Bessel Modified ellipsoid",
        "+proj=longlat +a=6377492.018 +b=6356173.508712696 +no_defs"},
    {
    4006, "epsg", 4006,
        "Unknown datum based upon the Bessel Namibia ellipsoid",
        "+proj=longlat +ellps=bess_nam +no_defs"},
    {
    4007, "epsg", 4007, "Unknown datum based upon the Clarke 1858 ellipsoid",
        "+proj=longlat +a=6378293.645208759 +b=6356617.987679838 +no_defs"},
    {
    4008, "epsg", 4008, "Unknown datum based upon the Clarke 1866 ellipsoid",
        "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4009, "epsg", 4009,
        "Unknown datum based upon the Clarke 1866 Michigan ellipsoid",
        "+proj=longlat +a=6378450.047548896 +b=6356826.621488444 +no_defs"},
    {
    4010, "epsg", 4010,
        "Unknown datum based upon the Clarke 1880 (Benoit) ellipsoid",
        "+proj=longlat +a=6378300.789 +b=6356566.435 +no_defs"},
    {
    4011, "epsg", 4011,
        "Unknown datum based upon the Clarke 1880 (IGN) ellipsoid",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4012, "epsg", 4012,
        "Unknown datum based upon the Clarke 1880 (RGS) ellipsoid",
        "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4013, "epsg", 4013,
        "Unknown datum based upon the Clarke 1880 (Arc) ellipsoid",
        "+proj=longlat +a=6378249.145 +b=6356514.966398753 +no_defs"},
    {
    4014, "epsg", 4014,
        "Unknown datum based upon the Clarke 1880 (SGA 1922) ellipsoid",
        "+proj=longlat +a=6378249.2 +b=6356514.996941779 +no_defs"},
    {
    4015, "epsg", 4015,
        "Unknown datum based upon the Everest 1830 (1937 Adjustment) ellipsoid",
        "+proj=longlat +a=6377276.345 +b=6356075.41314024 +no_defs"},
    {
    4016, "epsg", 4016,
        "Unknown datum based upon the Everest 1830 (1967 Definition) ellipsoid",
        "+proj=longlat +ellps=evrstSS +no_defs"},
    {
    4018, "epsg", 4018,
        "Unknown datum based upon the Everest 1830 Modified ellipsoid",
        "+proj=longlat +a=6377304.063 +b=6356103.038993155 +no_defs"},
    {
    4019, "epsg", 4019, "Unknown datum based upon the GRS 1980 ellipsoid",
        "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4020, "epsg", 4020, "Unknown datum based upon the Helmert 1906 ellipsoid",
        "+proj=longlat +ellps=helmert +no_defs"},
    {
    4021, "epsg", 4021,
        "Unknown datum based upon the Indonesian National Spheroid",
        "+proj=longlat +a=6378160 +b=6356774.50408554 +no_defs"},
    {
    4022, "epsg", 4022,
        "Unknown datum based upon the International 1924 ellipsoid",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4023, "epsg", 4023, "MOLDREF99", "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4024, "epsg", 4024,
        "Unknown datum based upon the Krassowsky 1940 ellipsoid",
        "+proj=longlat +ellps=krass +no_defs"},
    {
    4025, "epsg", 4025, "Unknown datum based upon the NWL 9D ellipsoid",
        "+proj=longlat +ellps=WGS66 +no_defs"},
    {
    4027, "epsg", 4027, "Unknown datum based upon the Plessis 1817 ellipsoid",
        "+proj=longlat +a=6376523 +b=6355862.933255573 +no_defs"},
    {
    4028, "epsg", 4028, "Unknown datum based upon the Struve 1860 ellipsoid",
        "+proj=longlat +a=6378298.3 +b=6356657.142669561 +no_defs"},
    {
    4029, "epsg", 4029, "Unknown datum based upon the War Office ellipsoid",
        "+proj=longlat +a=6378300 +b=6356751.689189189 +no_defs"},
    {
    4030, "epsg", 4030, "Unknown datum based upon the WGS 84 ellipsoid",
        "+proj=longlat +ellps=WGS84 +no_defs"},
    {
    4031, "epsg", 4031, "Unknown datum based upon the GEM 10C ellipsoid",
        "+proj=longlat +ellps=WGS84 +no_defs"},
    {
    4032, "epsg", 4032, "Unknown datum based upon the OSU86F ellipsoid",
        "+proj=longlat +a=6378136.2 +b=6356751.516927429 +no_defs"},
    {
    4033, "epsg", 4033, "Unknown datum based upon the OSU91A ellipsoid",
        "+proj=longlat +a=6378136.3 +b=6356751.616592146 +no_defs"},
    {
    4034, "epsg", 4034, "Unknown datum based upon the Clarke 1880 ellipsoid",
        "+proj=longlat +a=6378249.144808011 +b=6356514.966204134 +no_defs"},
    {
    4035, "epsg", 4035, "Unknown datum based upon the Authalic Sphere",
        "+proj=longlat +a=6371000 +b=6371000 +no_defs"},
    {
    4036, "epsg", 4036, "Unknown datum based upon the GRS 1967 ellipsoid",
        "+proj=longlat +ellps=GRS67 +no_defs"},
    {
    4041, "epsg", 4041,
        "Unknown datum based upon the Average Terrestrial System 1977 ellipsoid",
        "+proj=longlat +a=6378135 +b=6356750.304921594 +no_defs"},
    {
    4042, "epsg", 4042,
        "Unknown datum based upon the Everest (1830 Definition) ellipsoid",
        "+proj=longlat +a=6377299.36559538 +b=6356098.359005156 +no_defs"},
    {
    4043, "epsg", 4043, "Unknown datum based upon the WGS 72 ellipsoid",
        "+proj=longlat +ellps=WGS72 +no_defs"},
    {
    4044, "epsg", 4044,
        "Unknown datum based upon the Everest 1830 (1962 Definition) ellipsoid",
        "+proj=longlat +a=6377301.243 +b=6356100.230165384 +no_defs"},
    {
    4045, "epsg", 4045,
        "Unknown datum based upon the Everest 1830 (1975 Definition) ellipsoid",
        "+proj=longlat +a=6377299.151 +b=6356098.145120132 +no_defs"},
    {
    4046, "epsg", 4046, "RGRDC 2005",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4047, "epsg", 4047,
        "Unspecified datum based upon the GRS 1980 Authalic Sphere",
        "+proj=longlat +a=6371007 +b=6371007 +no_defs"},
    {
    4052, "epsg", 4052,
        "Unspecified datum based upon the Clarke 1866 Authalic Sphere",
        "+proj=longlat +a=6370997 +b=6370997 +no_defs"},
    {
    4053, "epsg", 4053,
        "Unspecified datum based upon the International 1924 Authalic Sphere",
        "+proj=longlat +a=6371228 +b=6371228 +no_defs"},
    {
    4054, "epsg", 4054,
        "Unspecified datum based upon the Hughes 1980 ellipsoid",
        "+proj=longlat +a=6378273 +b=6356889.449 +no_defs"},
    {
    4055, "epsg", 4055, "Popular Visualisation CRS",
        "+proj=longlat +a=6378137 +b=6378137 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4075, "epsg", 4075, "SREF98",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4081, "epsg", 4081, "REGCAN95",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4120, "epsg", 4120, "Greek", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4121, "epsg", 4121, "GGRS87",
        "+proj=longlat +ellps=GRS80 +datum=GGRS87 +no_defs"},
    {
    4122, "epsg", 4122, "ATS77",
        "+proj=longlat +a=6378135 +b=6356750.304921594 +no_defs"},
    {
    4123, "epsg", 4123, "KKJ", "+proj=longlat +ellps=intl +no_defs"},
    {
    4124, "epsg", 4124, "RT90", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4125, "epsg", 4125, "Samboja",
        "+proj=longlat +ellps=bessel +towgs84=-404.78,685.68,45.47,0,0,0,0 +no_defs"},
    {
    4126, "epsg", 4126, "LKS94 (ETRS89)",
        "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4127, "epsg", 4127, "Tete", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4128, "epsg", 4128, "Madzansua", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4129, "epsg", 4129, "Observatario", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4130, "epsg", 4130, "Moznet",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,-0,-0,-0,0 +no_defs"},
    {
    4131, "epsg", 4131, "Indian 1960",
        "+proj=longlat +a=6377276.345 +b=6356075.41314024 +no_defs"},
    {
    4132, "epsg", 4132, "FD58", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4133, "epsg", 4133, "EST92",
        "+proj=longlat +ellps=GRS80 +towgs84=0.055,-0.541,-0.185,0.0183,-0.0003,-0.007,-0.014 +no_defs"},
    {
    4134, "epsg", 4134, "PSD93", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4135, "epsg", 4135, "Old Hawaiian", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4136, "epsg", 4136, "St. Lawrence Island",
        "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4137, "epsg", 4137, "St. Paul Island",
        "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4138, "epsg", 4138, "St. George Island",
        "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4139, "epsg", 4139, "Puerto Rico",
        "+proj=longlat +ellps=clrk66 +towgs84=11,72,-101,0,0,0,0 +no_defs"},
    {
    4140, "epsg", 4140, "NAD83(CSRS98)",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4141, "epsg", 4141, "Israel",
        "+proj=longlat +ellps=GRS80 +towgs84=-48,55,52,0,0,0,0 +no_defs"},
    {
    4142, "epsg", 4142, "Locodjo 1965",
        "+proj=longlat +ellps=clrk80 +towgs84=-125,53,467,0,0,0,0 +no_defs"},
    {
    4143, "epsg", 4143, "Abidjan 1987",
        "+proj=longlat +ellps=clrk80 +towgs84=-124.76,53,466.79,0,0,0,0 +no_defs"},
    {
    4144, "epsg", 4144, "Kalianpur 1937",
        "+proj=longlat +a=6377276.345 +b=6356075.41314024 +no_defs"},
    {
    4145, "epsg", 4145, "Kalianpur 1962",
        "+proj=longlat +a=6377301.243 +b=6356100.230165384 +no_defs"},
    {
    4146, "epsg", 4146, "Kalianpur 1975",
        "+proj=longlat +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +no_defs"},
    {
    4147, "epsg", 4147, "Hanoi 1972",
        "+proj=longlat +ellps=krass +towgs84=-17.51,-108.32,-62.39,0,0,0,0 +no_defs"},
    {
    4148, "epsg", 4148, "Hartebeesthoek94",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4149, "epsg", 4149, "CH1903",
        "+proj=longlat +ellps=bessel +towgs84=674.374,15.056,405.346,0,0,0,0 +no_defs"},
    {
    4150, "epsg", 4150, "CH1903+",
        "+proj=longlat +ellps=bessel +towgs84=674.374,15.056,405.346,0,0,0,0 +no_defs"},
    {
    4151, "epsg", 4151, "CHTRF95",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4152, "epsg", 4152, "NAD83(HARN)", "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4153, "epsg", 4153, "Rassadiran",
        "+proj=longlat +ellps=intl +towgs84=-133.63,-157.5,-158.62,0,0,0,0 +no_defs"},
    {
    4154, "epsg", 4154, "ED50(ED77)", "+proj=longlat +ellps=intl +no_defs"},
    {
    4155, "epsg", 4155, "Dabola 1981",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=-83,37,124,0,0,0,0 +no_defs"},
    {
    4156, "epsg", 4156, "S-JTSK", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4157, "epsg", 4157, "Mount Dillon",
        "+proj=longlat +a=6378293.645208759 +b=6356617.987679838 +no_defs"},
    {
    4158, "epsg", 4158, "Naparima 1955", "+proj=longlat +ellps=intl +no_defs"},
    {
    4159, "epsg", 4159, "ELD79", "+proj=longlat +ellps=intl +no_defs"},
    {
    4160, "epsg", 4160, "Chos Malal 1914",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4161, "epsg", 4161, "Pampa del Castillo",
        "+proj=longlat +ellps=intl +towgs84=27.5,14,186.4,0,0,0,0 +no_defs"},
    {
    4162, "epsg", 4162, "Korean 1985", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4163, "epsg", 4163, "Yemen NGN96",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4164, "epsg", 4164, "South Yemen",
        "+proj=longlat +ellps=krass +towgs84=-76,-138,67,0,0,0,0 +no_defs"},
    {
    4165, "epsg", 4165, "Bissau",
        "+proj=longlat +ellps=intl +towgs84=-173,253,27,0,0,0,0 +no_defs"},
    {
    4166, "epsg", 4166, "Korean 1995",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4167, "epsg", 4167, "NZGD2000",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4168, "epsg", 4168, "Accra",
        "+proj=longlat +a=6378300 +b=6356751.689189189 +no_defs"},
    {
    4169, "epsg", 4169, "American Samoa 1962",
        "+proj=longlat +ellps=clrk66 +towgs84=-115,118,426,0,0,0,0 +no_defs"},
    {
    4170, "epsg", 4170, "SIRGAS 1995",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4171, "epsg", 4171, "RGF93",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4172, "epsg", 4172, "POSGAR",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4173, "epsg", 4173, "IRENET95",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4174, "epsg", 4174, "Sierra Leone 1924",
        "+proj=longlat +a=6378300 +b=6356751.689189189 +no_defs"},
    {
    4175, "epsg", 4175, "Sierra Leone 1968",
        "+proj=longlat +ellps=clrk80 +towgs84=-88,4,101,0,0,0,0 +no_defs"},
    {
    4176, "epsg", 4176, "Australian Antarctic",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4178, "epsg", 4178, "Pulkovo 1942(83)",
        "+proj=longlat +ellps=krass +no_defs"},
    {
    4179, "epsg", 4179, "Pulkovo 1942(58)",
        "+proj=longlat +ellps=krass +no_defs"},
    {
    4180, "epsg", 4180, "EST97",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4181, "epsg", 4181, "Luxembourg 1930",
        "+proj=longlat +ellps=intl +towgs84=-193,13.7,-39.3,-0.41,-2.933,2.688,0.43 +no_defs"},
    {
    4182, "epsg", 4182, "Azores Occidental 1939",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4183, "epsg", 4183, "Azores Central 1948",
        "+proj=longlat +ellps=intl +towgs84=-104,167,-38,0,0,0,0 +no_defs"},
    {
    4184, "epsg", 4184, "Azores Oriental 1940",
        "+proj=longlat +ellps=intl +towgs84=-203,141,53,0,0,0,0 +no_defs"},
    {
    4185, "epsg", 4185, "Madeira 1936", "+proj=longlat +ellps=intl +no_defs"},
    {
    4188, "epsg", 4188, "OSNI 1952",
        "+proj=longlat +ellps=airy +towgs84=482.5,-130.6,564.6,-1.042,-0.214,-0.631,8.15 +no_defs"},
    {
    4189, "epsg", 4189, "REGVEN",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4190, "epsg", 4190, "POSGAR 98", "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4191, "epsg", 4191, "Albanian 1987", "+proj=longlat +ellps=krass +no_defs"},
    {
    4192, "epsg", 4192, "Douala 1948",
        "+proj=longlat +ellps=intl +towgs84=-206.1,-174.7,-87.7,0,0,0,0 +no_defs"},
    {
    4193, "epsg", 4193, "Manoca 1962",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=-70.9,-151.8,-41.4,0,0,0,0 +no_defs"},
    {
    4194, "epsg", 4194, "Qornoq 1927", "+proj=longlat +ellps=intl +no_defs"},
    {
    4195, "epsg", 4195, "Scoresbysund 1952",
        "+proj=longlat +ellps=intl +towgs84=105,326,-102.5,0,0,0.814,-0.6 +no_defs"},
    {
    4196, "epsg", 4196, "Ammassalik 1958",
        "+proj=longlat +ellps=intl +towgs84=-45,417,-3.5,0,0,0.814,-0.6 +no_defs"},
    {
    4197, "epsg", 4197, "Garoua", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4198, "epsg", 4198, "Kousseri", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4199, "epsg", 4199, "Egypt 1930", "+proj=longlat +ellps=intl +no_defs"},
    {
    4200, "epsg", 4200, "Pulkovo 1995",
        "+proj=longlat +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +no_defs"},
    {
    4201, "epsg", 4201, "Adindan", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4202, "epsg", 4202, "AGD66", "+proj=longlat +ellps=aust_SA +no_defs"},
    {
    4203, "epsg", 4203, "AGD84", "+proj=longlat +ellps=aust_SA +no_defs"},
    {
    4204, "epsg", 4204, "Ain el Abd", "+proj=longlat +ellps=intl +no_defs"},
    {
    4205, "epsg", 4205, "Afgooye",
        "+proj=longlat +ellps=krass +towgs84=-43,-163,45,0,0,0,0 +no_defs"},
    {
    4206, "epsg", 4206, "Agadez",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4207, "epsg", 4207, "Lisbon", "+proj=longlat +ellps=intl +no_defs"},
    {
    4208, "epsg", 4208, "Aratu", "+proj=longlat +ellps=intl +no_defs"},
    {
    4209, "epsg", 4209, "Arc 1950",
        "+proj=longlat +a=6378249.145 +b=6356514.966398753 +no_defs"},
    {
    4210, "epsg", 4210, "Arc 1960", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4211, "epsg", 4211, "Batavia", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4212, "epsg", 4212, "Barbados 1938",
        "+proj=longlat +ellps=clrk80 +towgs84=31.95,300.99,419.19,0,0,0,0 +no_defs"},
    {
    4213, "epsg", 4213, "Beduaram",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=-106,-87,188,0,0,0,0 +no_defs"},
    {
    4214, "epsg", 4214, "Beijing 1954", "+proj=longlat +ellps=krass +no_defs"},
    {
    4215, "epsg", 4215, "Belge 1950", "+proj=longlat +ellps=intl +no_defs"},
    {
    4216, "epsg", 4216, "Bermuda 1957", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4218, "epsg", 4218, "Bogota 1975",
        "+proj=longlat +ellps=intl +towgs84=307,304,-318,0,0,0,0 +no_defs"},
    {
    4219, "epsg", 4219, "Bukit Rimpah",
        "+proj=longlat +ellps=bessel +towgs84=-384,664,-48,0,0,0,0 +no_defs"},
    {
    4220, "epsg", 4220, "Camacupa", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4221, "epsg", 4221, "Campo Inchauspe",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4222, "epsg", 4222, "Cape",
        "+proj=longlat +a=6378249.145 +b=6356514.966398753 +no_defs"},
    {
    4223, "epsg", 4223, "Carthage",
        "+proj=longlat +a=6378249.2 +b=6356515 +datum=carthage +no_defs"},
    {
    4224, "epsg", 4224, "Chua", "+proj=longlat +ellps=intl +no_defs"},
    {
    4225, "epsg", 4225, "Corrego Alegre",
        "+proj=longlat +ellps=intl +towgs84=-206,172,-6,0,0,0,0 +no_defs"},
    {
    4226, "epsg", 4226, "Cote d'Ivoire",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4227, "epsg", 4227, "Deir ez Zor",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4228, "epsg", 4228, "Douala",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4229, "epsg", 4229, "Egypt 1907", "+proj=longlat +ellps=helmert +no_defs"},
    {
    4230, "epsg", 4230, "ED50", "+proj=longlat +ellps=intl +no_defs"},
    {
    4231, "epsg", 4231, "ED87", "+proj=longlat +ellps=intl +no_defs"},
    {
    4232, "epsg", 4232, "Fahud", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4233, "epsg", 4233, "Gandajika 1970",
        "+proj=longlat +ellps=intl +towgs84=-133,-321,50,0,0,0,0 +no_defs"},
    {
    4234, "epsg", 4234, "Garoua",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4235, "epsg", 4235, "Guyane Francaise",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4236, "epsg", 4236, "Hu Tzu Shan 1950",
        "+proj=longlat +ellps=intl +towgs84=-637,-549,-203,0,0,0,0 +no_defs"},
    {
    4237, "epsg", 4237, "HD72", "+proj=longlat +ellps=GRS67 +no_defs"},
    {
    4238, "epsg", 4238, "ID74",
        "+proj=longlat +a=6378160 +b=6356774.50408554 +no_defs"},
    {
    4239, "epsg", 4239, "Indian 1954",
        "+proj=longlat +a=6377276.345 +b=6356075.41314024 +towgs84=217,823,299,0,0,0,0 +no_defs"},
    {
    4240, "epsg", 4240, "Indian 1975",
        "+proj=longlat +a=6377276.345 +b=6356075.41314024 +no_defs"},
    {
    4241, "epsg", 4241, "Jamaica 1875",
        "+proj=longlat +a=6378249.144808011 +b=6356514.966204134 +no_defs"},
    {
    4242, "epsg", 4242, "JAD69", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4243, "epsg", 4243, "Kalianpur 1880",
        "+proj=longlat +a=6377299.36559538 +b=6356098.359005156 +no_defs"},
    {
    4244, "epsg", 4244, "Kandawala",
        "+proj=longlat +a=6377276.345 +b=6356075.41314024 +towgs84=-97,787,86,0,0,0,0 +no_defs"},
    {
    4245, "epsg", 4245, "Kertau 1968",
        "+proj=longlat +a=6377304.063 +b=6356103.038993155 +towgs84=-11,851,5,0,0,0,0 +no_defs"},
    {
    4246, "epsg", 4246, "KOC",
        "+proj=longlat +ellps=clrk80 +towgs84=-294.7,-200.1,525.5,0,0,0,0 +no_defs"},
    {
    4247, "epsg", 4247, "La Canoa",
        "+proj=longlat +ellps=intl +towgs84=-273.5,110.6,-357.9,0,0,0,0 +no_defs"},
    {
    4248, "epsg", 4248, "PSAD56", "+proj=longlat +ellps=intl +no_defs"},
    {
    4249, "epsg", 4249, "Lake", "+proj=longlat +ellps=intl +no_defs"},
    {
    4250, "epsg", 4250, "Leigon",
        "+proj=longlat +ellps=clrk80 +towgs84=-130,29,364,0,0,0,0 +no_defs"},
    {
    4251, "epsg", 4251, "Liberia 1964",
        "+proj=longlat +ellps=clrk80 +towgs84=-90,40,88,0,0,0,0 +no_defs"},
    {
    4252, "epsg", 4252, "Lome",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4253, "epsg", 4253, "Luzon 1911", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4254, "epsg", 4254, "Hito XVIII 1963",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4255, "epsg", 4255, "Herat North",
        "+proj=longlat +ellps=intl +towgs84=-333,-222,114,0,0,0,0 +no_defs"},
    {
    4256, "epsg", 4256, "Mahe 1971",
        "+proj=longlat +ellps=clrk80 +towgs84=41,-220,-134,0,0,0,0 +no_defs"},
    {
    4257, "epsg", 4257, "Makassar",
        "+proj=longlat +ellps=bessel +towgs84=-587.8,519.75,145.76,0,0,0,0 +no_defs"},
    {
    4258, "epsg", 4258, "ETRS89", "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4259, "epsg", 4259, "Malongo 1987", "+proj=longlat +ellps=intl +no_defs"},
    {
    4260, "epsg", 4260, "Manoca",
        "+proj=longlat +ellps=clrk80 +towgs84=-70.9,-151.8,-41.4,0,0,0,0 +no_defs"},
    {
    4261, "epsg", 4261, "Merchich",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=31,146,47,0,0,0,0 +no_defs"},
    {
    4262, "epsg", 4262, "Massawa",
        "+proj=longlat +ellps=bessel +towgs84=639,405,60,0,0,0,0 +no_defs"},
    {
    4263, "epsg", 4263, "Minna", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4264, "epsg", 4264, "Mhast",
        "+proj=longlat +ellps=intl +towgs84=-252.95,-4.11,-96.38,0,0,0,0 +no_defs"},
    {
    4265, "epsg", 4265, "Monte Mario", "+proj=longlat +ellps=intl +no_defs"},
    {
    4266, "epsg", 4266, "M'poraloko",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4267, "epsg", 4267, "NAD27",
        "+proj=longlat +ellps=clrk66 +datum=NAD27 +no_defs"},
    {
    4268, "epsg", 4268, "NAD27 Michigan",
        "+proj=longlat +a=6378450.047548896 +b=6356826.621488444 +no_defs"},
    {
    4269, "epsg", 4269, "NAD83",
        "+proj=longlat +ellps=GRS80 +datum=NAD83 +no_defs"},
    {
    4270, "epsg", 4270, "Nahrwan 1967", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4271, "epsg", 4271, "Naparima 1972", "+proj=longlat +ellps=intl +no_defs"},
    {
    4272, "epsg", 4272, "NZGD49",
        "+proj=longlat +ellps=intl +datum=nzgd49 +no_defs"},
    {
    4273, "epsg", 4273, "NGO 1948",
        "+proj=longlat +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +no_defs"},
    {
    4274, "epsg", 4274, "Datum 73", "+proj=longlat +ellps=intl +no_defs"},
    {
    4275, "epsg", 4275, "NTF",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +no_defs"},
    {
    4276, "epsg", 4276, "NSWC 9Z-2", "+proj=longlat +ellps=WGS66 +no_defs"},
    {
    4277, "epsg", 4277, "OSGB 1936",
        "+proj=longlat +ellps=airy +datum=OSGB36 +no_defs"},
    {
    4278, "epsg", 4278, "OSGB70", "+proj=longlat +ellps=airy +no_defs"},
    {
    4279, "epsg", 4279, "OS(SN)80", "+proj=longlat +ellps=airy +no_defs"},
    {
    4280, "epsg", 4280, "Padang", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4281, "epsg", 4281, "Palestine 1923",
        "+proj=longlat +a=6378300.789 +b=6356566.435 +towgs84=-275.722,94.7824,340.894,-8.001,-4.42,-11.821,1 +no_defs"},
    {
    4282, "epsg", 4282, "Pointe Noire",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4283, "epsg", 4283, "GDA94",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4284, "epsg", 4284, "Pulkovo 1942", "+proj=longlat +ellps=krass +no_defs"},
    {
    4285, "epsg", 4285, "Qatar 1974", "+proj=longlat +ellps=intl +no_defs"},
    {
    4286, "epsg", 4286, "Qatar 1948", "+proj=longlat +ellps=helmert +no_defs"},
    {
    4287, "epsg", 4287, "Qornoq",
        "+proj=longlat +ellps=intl +towgs84=164,138,-189,0,0,0,0 +no_defs"},
    {
    4288, "epsg", 4288, "Loma Quintana", "+proj=longlat +ellps=intl +no_defs"},
    {
    4289, "epsg", 4289, "Amersfoort", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4291, "epsg", 4291, "SAD69", "+proj=longlat +ellps=GRS67 +no_defs"},
    {
    4292, "epsg", 4292, "Sapper Hill 1943",
        "+proj=longlat +ellps=intl +towgs84=-355,21,72,0,0,0,0 +no_defs"},
    {
    4293, "epsg", 4293, "Schwarzeck", "+proj=longlat +ellps=bess_nam +no_defs"},
    {
    4294, "epsg", 4294, "Segora", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4295, "epsg", 4295, "Serindung", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4296, "epsg", 4296, "Sudan",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4297, "epsg", 4297, "Tananarive",
        "+proj=longlat +ellps=intl +towgs84=-189,-242,-91,0,0,0,0 +no_defs"},
    {
    4298, "epsg", 4298, "Timbalai 1948",
        "+proj=longlat +ellps=evrstSS +no_defs"},
    {
    4299, "epsg", 4299, "TM65",
        "+proj=longlat +ellps=mod_airy +datum=ire65 +no_defs"},
    {
    4300, "epsg", 4300, "TM75", "+proj=longlat +ellps=mod_airy +no_defs"},
    {
    4301, "epsg", 4301, "Tokyo", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4302, "epsg", 4302, "Trinidad 1903",
        "+proj=longlat +a=6378293.645208759 +b=6356617.987679838 +no_defs"},
    {
    4303, "epsg", 4303, "TC(1948)", "+proj=longlat +ellps=helmert +no_defs"},
    {
    4304, "epsg", 4304, "Voirol 1875",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=-73,-247,227,0,0,0,0 +no_defs"},
    {
    4306, "epsg", 4306, "Bern 1938", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4307, "epsg", 4307, "Nord Sahara 1959",
        "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4308, "epsg", 4308, "RT38", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4309, "epsg", 4309, "Yacare",
        "+proj=longlat +ellps=intl +towgs84=-155,171,37,0,0,0,0 +no_defs"},
    {
    4310, "epsg", 4310, "Yoff",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4311, "epsg", 4311, "Zanderij",
        "+proj=longlat +ellps=intl +towgs84=-265,120,-358,0,0,0,0 +no_defs"},
    {
    4312, "epsg", 4312, "MGI",
        "+proj=longlat +ellps=bessel +datum=hermannskogel +no_defs"},
    {
    4313, "epsg", 4313, "Belge 1972",
        "+proj=longlat +ellps=intl +towgs84=106.869,-52.2978,103.724,-0.33657,0.456955,-1.84218,1 +no_defs"},
    {
    4314, "epsg", 4314, "DHDN",
        "+proj=longlat +ellps=bessel +datum=potsdam +no_defs"},
    {
    4315, "epsg", 4315, "Conakry 1905",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=-23,259,-9,0,0,0,0 +no_defs"},
    {
    4316, "epsg", 4316, "Dealul Piscului 1930",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4317, "epsg", 4317, "Dealul Piscului 1970",
        "+proj=longlat +ellps=krass +no_defs"},
    {
    4318, "epsg", 4318, "NGN",
        "+proj=longlat +ellps=WGS84 +towgs84=-3.2,-5.7,2.8,0,0,0,0 +no_defs"},
    {
    4319, "epsg", 4319, "KUDAMS", "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4322, "epsg", 4322, "WGS 72", "+proj=longlat +ellps=WGS72 +no_defs"},
    {
    4324, "epsg", 4324, "WGS 72BE",
        "+proj=longlat +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +no_defs"},
    {
    4326, "epsg", 4326, "WGS 84",
        "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs"},
    {
    4600, "epsg", 4600, "Anguilla 1957",
        "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4601, "epsg", 4601, "Antigua 1943", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4602, "epsg", 4602, "Dominica 1945",
        "+proj=longlat +ellps=clrk80 +towgs84=725,685,536,0,0,0,0 +no_defs"},
    {
    4603, "epsg", 4603, "Grenada 1953",
        "+proj=longlat +ellps=clrk80 +towgs84=72,213.7,93,0,0,0,0 +no_defs"},
    {
    4604, "epsg", 4604, "Montserrat 1958",
        "+proj=longlat +ellps=clrk80 +towgs84=174,359,365,0,0,0,0 +no_defs"},
    {
    4605, "epsg", 4605, "St. Kitts 1955",
        "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4606, "epsg", 4606, "St. Lucia 1955",
        "+proj=longlat +ellps=clrk80 +towgs84=-149,128,296,0,0,0,0 +no_defs"},
    {
    4607, "epsg", 4607, "St. Vincent 1945",
        "+proj=longlat +ellps=clrk80 +towgs84=195.671,332.517,274.607,0,0,0,0 +no_defs"},
    {
    4608, "epsg", 4608, "NAD27(76)", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4609, "epsg", 4609, "NAD27(CGQ77)", "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4610, "epsg", 4610, "Xian 1980",
        "+proj=longlat +a=6378140 +b=6356755.288157528 +no_defs"},
    {
    4611, "epsg", 4611, "Hong Kong 1980",
        "+proj=longlat +ellps=intl +towgs84=-162.619,-276.959,-161.764,0.067753,-2.24365,-1.15883,-1.09425 +no_defs"},
    {
    4612, "epsg", 4612, "JGD2000",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4613, "epsg", 4613, "Segara", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4614, "epsg", 4614, "QND95",
        "+proj=longlat +ellps=intl +towgs84=-119.425,-303.659,-11.0006,1.1643,0.174458,1.09626,3.65706 +no_defs"},
    {
    4615, "epsg", 4615, "Porto Santo",
        "+proj=longlat +ellps=intl +towgs84=-499,-249,314,0,0,0,0 +no_defs"},
    {
    4616, "epsg", 4616, "Selvagem Grande",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4617, "epsg", 4617, "NAD83(CSRS)", "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4618, "epsg", 4618, "SAD69", "+proj=longlat +ellps=aust_SA +no_defs"},
    {
    4619, "epsg", 4619, "SWEREF99",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4620, "epsg", 4620, "Point 58",
        "+proj=longlat +ellps=clrk80 +towgs84=-106,-129,165,0,0,0,0 +no_defs"},
    {
    4621, "epsg", 4621, "Fort Marigot",
        "+proj=longlat +ellps=intl +towgs84=137,248,-430,0,0,0,0 +no_defs"},
    {
    4622, "epsg", 4622, "Guadeloupe 1948",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4623, "epsg", 4623, "CSG67",
        "+proj=longlat +ellps=intl +towgs84=-186,230,110,0,0,0,0 +no_defs"},
    {
    4624, "epsg", 4624, "RGFG95",
        "+proj=longlat +ellps=GRS80 +towgs84=2,2,-2,0,0,0,0 +no_defs"},
    {
    4625, "epsg", 4625, "Martinique 1938",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4626, "epsg", 4626, "Reunion 1947", "+proj=longlat +ellps=intl +no_defs"},
    {
    4627, "epsg", 4627, "RGR92",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4628, "epsg", 4628, "Tahiti 52",
        "+proj=longlat +ellps=intl +towgs84=162,117,154,0,0,0,0 +no_defs"},
    {
    4629, "epsg", 4629, "Tahaa 54", "+proj=longlat +ellps=intl +no_defs"},
    {
    4630, "epsg", 4630, "IGN72 Nuku Hiva",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4631, "epsg", 4631, "K0 1949",
        "+proj=longlat +ellps=intl +towgs84=145,-187,103,0,0,0,0 +no_defs"},
    {
    4632, "epsg", 4632, "Combani 1950",
        "+proj=longlat +ellps=intl +towgs84=-382,-59,-262,0,0,0,0 +no_defs"},
    {
    4633, "epsg", 4633, "IGN56 Lifou", "+proj=longlat +ellps=intl +no_defs"},
    {
    4634, "epsg", 4634, "IGN72 Grand Terre",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4635, "epsg", 4635, "ST87 Ouvea",
        "+proj=longlat +ellps=intl +towgs84=-122.383,-188.696,103.344,3.5107,-4.9668,-5.7047,4.4798 +no_defs"},
    {
    4636, "epsg", 4636, "Petrels 1972",
        "+proj=longlat +ellps=intl +towgs84=365,194,166,0,0,0,0 +no_defs"},
    {
    4637, "epsg", 4637, "Perroud 1950",
        "+proj=longlat +ellps=intl +towgs84=325,154,172,0,0,0,0 +no_defs"},
    {
    4638, "epsg", 4638, "Saint Pierre et Miquelon 1950",
        "+proj=longlat +ellps=clrk66 +towgs84=30,430,368,0,0,0,0 +no_defs"},
    {
    4639, "epsg", 4639, "MOP78", "+proj=longlat +ellps=intl +no_defs"},
    {
    4640, "epsg", 4640, "RRAF 1991",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4641, "epsg", 4641, "IGN53 Mare", "+proj=longlat +ellps=intl +no_defs"},
    {
    4642, "epsg", 4642, "ST84 Ile des Pins",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4643, "epsg", 4643, "ST71 Belep",
        "+proj=longlat +ellps=intl +towgs84=-480.26,-438.32,-643.429,16.3119,20.1721,-4.0349,-111.7 +no_defs"},
    {
    4644, "epsg", 4644, "NEA74 Noumea", "+proj=longlat +ellps=intl +no_defs"},
    {
    4645, "epsg", 4645, "RGNC 1991",
        "+proj=longlat +ellps=intl +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4646, "epsg", 4646, "Grand Comoros", "+proj=longlat +ellps=intl +no_defs"},
    {
    4657, "epsg", 4657, "Reykjavik 1900",
        "+proj=longlat +a=6377019.27 +b=6355762.5391 +towgs84=-28,199,5,0,0,0,0 +no_defs"},
    {
    4658, "epsg", 4658, "Hjorsey 1955",
        "+proj=longlat +ellps=intl +towgs84=-73,46,-86,0,0,0,0 +no_defs"},
    {
    4659, "epsg", 4659, "ISN93",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4660, "epsg", 4660, "Helle 1954",
        "+proj=longlat +ellps=intl +towgs84=982.609,552.753,-540.873,32.3934,-153.257,-96.2266,16.805 +no_defs"},
    {
    4661, "epsg", 4661, "LKS92",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4662, "epsg", 4662, "IGN72 Grande Terre",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4663, "epsg", 4663, "Porto Santo 1995",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4664, "epsg", 4664, "Azores Oriental 1995",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4665, "epsg", 4665, "Azores Central 1995",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4666, "epsg", 4666, "Lisbon 1890", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4667, "epsg", 4667, "IKBD-92",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4668, "epsg", 4668, "ED79",
        "+proj=longlat +ellps=intl +towgs84=-86,-98,-119,0,0,0,0 +no_defs"},
    {
    4669, "epsg", 4669, "LKS94",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4670, "epsg", 4670, "IGM95",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4671, "epsg", 4671, "Voirol 1879",
        "+proj=longlat +a=6378249.2 +b=6356515 +no_defs"},
    {
    4672, "epsg", 4672, "Chatham Islands 1971",
        "+proj=longlat +ellps=intl +towgs84=175,-38,113,0,0,0,0 +no_defs"},
    {
    4673, "epsg", 4673, "Chatham Islands 1979",
        "+proj=longlat +ellps=intl +towgs84=174.05,-25.49,112.57,-0,-0,0.554,0.2263 +no_defs"},
    {
    4674, "epsg", 4674, "SIRGAS 2000",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4675, "epsg", 4675, "Guam 1963",
        "+proj=longlat +ellps=clrk66 +towgs84=-100,-248,259,0,0,0,0 +no_defs"},
    {
    4676, "epsg", 4676, "Vientiane 1982",
        "+proj=longlat +ellps=krass +no_defs"},
    {
    4677, "epsg", 4677, "Lao 1993", "+proj=longlat +ellps=krass +no_defs"},
    {
    4678, "epsg", 4678, "Lao 1997",
        "+proj=longlat +ellps=krass +towgs84=44.585,-131.212,-39.544,0,0,0,0 +no_defs"},
    {
    4679, "epsg", 4679, "Jouik 1961",
        "+proj=longlat +ellps=clrk80 +towgs84=-80.01,253.26,291.19,0,0,0,0 +no_defs"},
    {
    4680, "epsg", 4680, "Nouakchott 1965",
        "+proj=longlat +ellps=clrk80 +towgs84=124.5,-63.5,-281,0,0,0,0 +no_defs"},
    {
    4681, "epsg", 4681, "Mauritania 1999",
        "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4682, "epsg", 4682, "Gulshan 303",
        "+proj=longlat +a=6377276.345 +b=6356075.41314024 +no_defs"},
    {
    4683, "epsg", 4683, "PRS92",
        "+proj=longlat +ellps=clrk66 +towgs84=-127.62,-67.24,-47.04,-3.068,4.903,1.578,-1.06 +no_defs"},
    {
    4684, "epsg", 4684, "Gan 1970",
        "+proj=longlat +ellps=intl +towgs84=-133,-321,50,0,0,0,0 +no_defs"},
    {
    4685, "epsg", 4685, "Gandajika", "+proj=longlat +ellps=intl +no_defs"},
    {
    4686, "epsg", 4686, "MAGNA-SIRGAS",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4687, "epsg", 4687, "RGPF", "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4688, "epsg", 4688, "Fatu Iva 72",
        "+proj=longlat +ellps=intl +towgs84=347.103,1078.12,2623.92,-33.8875,70.6773,-9.3943,186.074 +no_defs"},
    {
    4689, "epsg", 4689, "IGN63 Hiva Oa", "+proj=longlat +ellps=intl +no_defs"},
    {
    4690, "epsg", 4690, "Tahiti 79", "+proj=longlat +ellps=intl +no_defs"},
    {
    4691, "epsg", 4691, "Moorea 87",
        "+proj=longlat +ellps=intl +towgs84=215.525,149.593,176.229,-3.2624,-1.692,-1.1571,10.4773 +no_defs"},
    {
    4692, "epsg", 4692, "Maupiti 83",
        "+proj=longlat +ellps=intl +towgs84=217.037,86.959,23.956,0,0,0,0 +no_defs"},
    {
    4693, "epsg", 4693, "Nakhl-e Ghanem",
        "+proj=longlat +ellps=WGS84 +towgs84=0,-0.15,0.68,0,0,0,0 +no_defs"},
    {
    4694, "epsg", 4694, "POSGAR 94",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4695, "epsg", 4695, "Katanga 1955",
        "+proj=longlat +ellps=clrk66 +towgs84=-103.746,-9.614,-255.95,0,0,0,0 +no_defs"},
    {
    4696, "epsg", 4696, "Kasai 1953", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4697, "epsg", 4697, "IGC 1962 6th Parallel South",
        "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4698, "epsg", 4698, "IGN 1962 Kerguelen",
        "+proj=longlat +ellps=intl +towgs84=145,-187,103,0,0,0,0 +no_defs"},
    {
    4699, "epsg", 4699, "Le Pouce 1934",
        "+proj=longlat +ellps=clrk80 +towgs84=-770.1,158.4,-498.2,0,0,0,0 +no_defs"},
    {
    4700, "epsg", 4700, "IGN Astro 1960",
        "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4701, "epsg", 4701, "IGCB 1955",
        "+proj=longlat +ellps=clrk80 +towgs84=-79.9,-158,-168.9,0,0,0,0 +no_defs"},
    {
    4702, "epsg", 4702, "Mauritania 1999",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4703, "epsg", 4703, "Mhast 1951", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4704, "epsg", 4704, "Mhast (onshore)",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4705, "epsg", 4705, "Mhast (offshore)",
        "+proj=longlat +ellps=intl +no_defs"},
    {
    4706, "epsg", 4706, "Egypt Gulf of Suez S-650 TL",
        "+proj=longlat +ellps=helmert +towgs84=-146.21,112.63,4.05,0,0,0,0 +no_defs"},
    {
    4707, "epsg", 4707, "Tern Island 1961",
        "+proj=longlat +ellps=intl +towgs84=114,-116,-333,0,0,0,0 +no_defs"},
    {
    4708, "epsg", 4708, "Cocos Islands 1965",
        "+proj=longlat +ellps=aust_SA +towgs84=-491,-22,435,0,0,0,0 +no_defs"},
    {
    4709, "epsg", 4709, "Iwo Jima 1945",
        "+proj=longlat +ellps=intl +towgs84=145,75,-272,0,0,0,0 +no_defs"},
    {
    4710, "epsg", 4710, "St. Helena 1971",
        "+proj=longlat +ellps=intl +towgs84=-320,550,-494,0,0,0,0 +no_defs"},
    {
    4711, "epsg", 4711, "Marcus Island 1952",
        "+proj=longlat +ellps=intl +towgs84=124,-234,-25,0,0,0,0 +no_defs"},
    {
    4712, "epsg", 4712, "Ascension Island 1958",
        "+proj=longlat +ellps=intl +towgs84=-205,107,53,0,0,0,0 +no_defs"},
    {
    4713, "epsg", 4713, "Ayabelle Lighthouse",
        "+proj=longlat +ellps=clrk80 +towgs84=-79,-129,145,0,0,0,0 +no_defs"},
    {
    4714, "epsg", 4714, "Bellevue",
        "+proj=longlat +ellps=intl +towgs84=-127,-769,472,0,0,0,0 +no_defs"},
    {
    4715, "epsg", 4715, "Camp Area Astro",
        "+proj=longlat +ellps=intl +towgs84=-104,-129,239,0,0,0,0 +no_defs"},
    {
    4716, "epsg", 4716, "Phoenix Islands 1966",
        "+proj=longlat +ellps=intl +towgs84=298,-304,-375,0,0,0,0 +no_defs"},
    {
    4717, "epsg", 4717, "Cape Canaveral",
        "+proj=longlat +ellps=clrk66 +towgs84=-2,151,181,0,0,0,0 +no_defs"},
    {
    4718, "epsg", 4718, "Solomon 1968", "+proj=longlat +ellps=intl +no_defs"},
    {
    4719, "epsg", 4719, "Easter Island 1967",
        "+proj=longlat +ellps=intl +towgs84=211,147,111,0,0,0,0 +no_defs"},
    {
    4720, "epsg", 4720, "Fiji 1986", "+proj=longlat +ellps=WGS72 +no_defs"},
    {
    4721, "epsg", 4721, "Fiji 1956",
        "+proj=longlat +ellps=intl +towgs84=265.025,384.929,-194.046,0,0,0,0 +no_defs"},
    {
    4722, "epsg", 4722, "South Georgia 1968",
        "+proj=longlat +ellps=intl +towgs84=-794,119,-298,0,0,0,0 +no_defs"},
    {
    4723, "epsg", 4723, "Grand Cayman 1959",
        "+proj=longlat +ellps=clrk66 +towgs84=67.8,106.1,138.8,0,0,0,0 +no_defs"},
    {
    4724, "epsg", 4724, "Diego Garcia 1969",
        "+proj=longlat +ellps=intl +towgs84=208,-435,-229,0,0,0,0 +no_defs"},
    {
    4725, "epsg", 4725, "Johnston Island 1961",
        "+proj=longlat +ellps=intl +towgs84=189,-79,-202,0,0,0,0 +no_defs"},
    {
    4726, "epsg", 4726, "Little Cayman 1961",
        "+proj=longlat +ellps=clrk66 +no_defs"},
    {
    4727, "epsg", 4727, "Midway 1961", "+proj=longlat +ellps=intl +no_defs"},
    {
    4728, "epsg", 4728, "Pico de las Nieves 1984",
        "+proj=longlat +ellps=intl +towgs84=-307,-92,127,0,0,0,0 +no_defs"},
    {
    4729, "epsg", 4729, "Pitcairn 1967",
        "+proj=longlat +ellps=intl +towgs84=185,165,42,0,0,0,0 +no_defs"},
    {
    4730, "epsg", 4730, "Santo 1965",
        "+proj=longlat +ellps=intl +towgs84=170,42,84,0,0,0,0 +no_defs"},
    {
    4731, "epsg", 4731, "Viti Levu 1916",
        "+proj=longlat +ellps=clrk80 +towgs84=51,391,-36,0,0,0,0 +no_defs"},
    {
    4732, "epsg", 4732, "Marshall Islands 1960",
        "+proj=longlat +a=6378270 +b=6356794.343434343 +towgs84=102,52,-38,0,0,0,0 +no_defs"},
    {
    4733, "epsg", 4733, "Wake Island 1952",
        "+proj=longlat +ellps=intl +towgs84=276,-57,149,0,0,0,0 +no_defs"},
    {
    4734, "epsg", 4734, "Tristan 1968",
        "+proj=longlat +ellps=intl +towgs84=-632,438,-609,0,0,0,0 +no_defs"},
    {
    4735, "epsg", 4735, "Kusaie 1951",
        "+proj=longlat +ellps=intl +towgs84=647,1777,-1124,0,0,0,0 +no_defs"},
    {
    4736, "epsg", 4736, "Deception Island",
        "+proj=longlat +ellps=clrk80 +towgs84=260,12,-147,0,0,0,0 +no_defs"},
    {
    4737, "epsg", 4737, "Korea 2000",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4738, "epsg", 4738, "Hong Kong 1963",
        "+proj=longlat +a=6378293.645208759 +b=6356617.987679838 +no_defs"},
    {
    4739, "epsg", 4739, "Hong Kong 1963(67)",
        "+proj=longlat +ellps=intl +towgs84=-156,-271,-189,0,0,0,0 +no_defs"},
    {
    4740, "epsg", 4740, "PZ-90",
        "+proj=longlat +a=6378136 +b=6356751.361745712 +no_defs"},
    {
    4741, "epsg", 4741, "FD54", "+proj=longlat +ellps=intl +no_defs"},
    {
    4742, "epsg", 4742, "GDM2000", "+proj=longlat +ellps=GRS80 +no_defs"},
    {
    4743, "epsg", 4743, "Karbala 1979",
        "+proj=longlat +ellps=clrk80 +towgs84=84.1,-320.1,218.7,0,0,0,0 +no_defs"},
    {
    4744, "epsg", 4744, "Nahrwan 1934", "+proj=longlat +ellps=clrk80 +no_defs"},
    {
    4745, "epsg", 4745, "RD/83", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4746, "epsg", 4746, "PD/83", "+proj=longlat +ellps=bessel +no_defs"},
    {
    4747, "epsg", 4747, "GR96",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4748, "epsg", 4748, "Vanua Levu 1915",
        "+proj=longlat +a=6378306.3696 +b=6356571.996 +towgs84=51,391,-36,0,0,0,0 +no_defs"},
    {
    4749, "epsg", 4749, "RGNC91-93",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4750, "epsg", 4750, "ST87 Ouvea",
        "+proj=longlat +ellps=WGS84 +towgs84=-56.263,16.136,-22.856,0,0,0,0 +no_defs"},
    {
    4751, "epsg", 4751, "Kertau (RSO)",
        "+proj=longlat +a=6377295.664 +b=6356094.667915204 +no_defs"},
    {
    4752, "epsg", 4752, "Viti Levu 1912",
        "+proj=longlat +a=6378306.3696 +b=6356571.996 +towgs84=51,391,-36,0,0,0,0 +no_defs"},
    {
    4753, "epsg", 4753, "fk89", "+proj=longlat +ellps=intl +no_defs"},
    {
    4754, "epsg", 4754, "LGD2006",
        "+proj=longlat +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +no_defs"},
    {
    4755, "epsg", 4755, "DGN95",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4756, "epsg", 4756, "VN-2000", "+proj=longlat +ellps=WGS84 +no_defs"},
    {
    4757, "epsg", 4757, "SVY21", "+proj=longlat +ellps=WGS84 +no_defs"},
    {
    4758, "epsg", 4758, "JAD2001",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4759, "epsg", 4759, "NAD83(NSRS2007)",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4760, "epsg", 4760, "WGS 66", "+proj=longlat +ellps=WGS66 +no_defs"},
    {
    4761, "epsg", 4761, "HTRS96",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4762, "epsg", 4762, "BDA2000",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4763, "epsg", 4763, "Pitcairn 2006",
        "+proj=longlat +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4764, "epsg", 4764, "RSRGD2000",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4765, "epsg", 4765, "Slovenia 1996",
        "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs"},
    {
    4801, "epsg", 4801, "Bern 1898 (Bern)",
        "+proj=longlat +ellps=bessel +pm=bern +no_defs"},
    {
    4802, "epsg", 4802, "Bogota 1975 (Bogota)",
        "+proj=longlat +ellps=intl +pm=bogota +no_defs"},
    {
    4803, "epsg", 4803, "Lisbon (Lisbon)",
        "+proj=longlat +ellps=intl +pm=lisbon +no_defs"},
    {
    4804, "epsg", 4804, "Makassar (Jakarta)",
        "+proj=longlat +ellps=bessel +towgs84=-587.8,519.75,145.76,0,0,0,0 +pm=jakarta +no_defs"},
    {
    4805, "epsg", 4805, "MGI (Ferro)",
        "+proj=longlat +ellps=bessel +pm=ferro +no_defs"},
    {
    4806, "epsg", 4806, "Monte Mario (Rome)",
        "+proj=longlat +ellps=intl +pm=rome +no_defs"},
    {
    4807, "epsg", 4807, "NTF (Paris)",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +no_defs"},
    {
    4808, "epsg", 4808, "Padang (Jakarta)",
        "+proj=longlat +ellps=bessel +pm=jakarta +no_defs"},
    {
    4809, "epsg", 4809, "Belge 1950 (Brussels)",
        "+proj=longlat +ellps=intl +pm=brussels +no_defs"},
    {
    4810, "epsg", 4810, "Tananarive (Paris)",
        "+proj=longlat +ellps=intl +towgs84=-189,-242,-91,0,0,0,0 +pm=paris +no_defs"},
    {
    4811, "epsg", 4811, "Voirol 1875 (Paris)",
        "+proj=longlat +a=6378249.2 +b=6356515 +towgs84=-73,-247,227,0,0,0,0 +pm=paris +no_defs"},
    {
    4813, "epsg", 4813, "Batavia (Jakarta)",
        "+proj=longlat +ellps=bessel +pm=jakarta +no_defs"},
    {
    4814, "epsg", 4814, "RT38 (Stockholm)",
        "+proj=longlat +ellps=bessel +pm=stockholm +no_defs"},
    {
    4815, "epsg", 4815, "Greek (Athens)",
        "+proj=longlat +ellps=bessel +pm=athens +no_defs"},
    {
    4816, "epsg", 4816, "Carthage (Paris)",
        "+proj=longlat +a=6378249.2 +b=6356515 +pm=paris +no_defs"},
    {
    4817, "epsg", 4817, "NGO 1948 (Oslo)",
        "+proj=longlat +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +no_defs"},
    {
    4818, "epsg", 4818, "S-JTSK (Ferro)",
        "+proj=longlat +ellps=bessel +pm=ferro +no_defs"},
    {
    4819, "epsg", 4819, "Nord Sahara 1959 (Paris)",
        "+proj=longlat +ellps=clrk80 +pm=paris +no_defs"},
    {
    4820, "epsg", 4820, "Segara (Jakarta)",
        "+proj=longlat +ellps=bessel +pm=jakarta +no_defs"},
    {
    4821, "epsg", 4821, "Voirol 1879 (Paris)",
        "+proj=longlat +a=6378249.2 +b=6356515 +pm=paris +no_defs"},
    {
    4901, "epsg", 4901, "unnamed ellipse",
        "+proj=longlat +a=6376523 +b=6355862.933255573 +pm=2.3372291666985 +no_defs"},
    {
    4902, "epsg", 4902, "NDG (Paris)",
        "+proj=longlat +a=6376523 +b=6355862.933255573 +pm=paris +no_defs"},
    {
    4903, "epsg", 4903, "Madrid 1870 (Madrid)",
        "+proj=longlat +a=6378298.3 +b=6356657.142669561 +pm=madrid +no_defs"},
    {
    4904, "epsg", 4904, "Lisbon 1890 (Lisbon)",
        "+proj=longlat +ellps=bessel +pm=lisbon +no_defs"},
    {
    2000, "epsg", 2000, "Anguilla 1957 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +units=m +no_defs"},
    {
    2001, "epsg", 2001, "Antigua 1943 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +units=m +no_defs"},
    {
    2002, "epsg", 2002, "Dominica 1945 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +towgs84=725,685,536,0,0,0,0 +units=m +no_defs"},
    {
    2003, "epsg", 2003, "Grenada 1953 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +towgs84=72,213.7,93,0,0,0,0 +units=m +no_defs"},
    {
    2004, "epsg", 2004, "Montserrat 1958 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +towgs84=174,359,365,0,0,0,0 +units=m +no_defs"},
    {
    2005, "epsg", 2005, "St. Kitts 1955 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +units=m +no_defs"},
    {
    2006, "epsg", 2006, "St. Lucia 1955 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +towgs84=-149,128,296,0,0,0,0 +units=m +no_defs"},
    {
    2007, "epsg", 2007, "St. Vincent 45 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +towgs84=195.671,332.517,274.607,0,0,0,0 +units=m +no_defs"},
    {
    2008, "epsg", 2008, "NAD27(CGQ77) / SCoPQ zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=-55.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2009, "epsg", 2009, "NAD27(CGQ77) / SCoPQ zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=-58.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2010, "epsg", 2010, "NAD27(CGQ77) / SCoPQ zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=-61.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2011, "epsg", 2011, "NAD27(CGQ77) / SCoPQ zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=-64.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2012, "epsg", 2012, "NAD27(CGQ77) / SCoPQ zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=-67.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2013, "epsg", 2013, "NAD27(CGQ77) / SCoPQ zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=-70.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2014, "epsg", 2014, "NAD27(CGQ77) / SCoPQ zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=-73.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2015, "epsg", 2015, "NAD27(CGQ77) / SCoPQ zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=-76.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2016, "epsg", 2016, "NAD27(CGQ77) / SCoPQ zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=-79.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2017, "epsg", 2017, "NAD27(76) / MTM zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=-73.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2018, "epsg", 2018, "NAD27(76) / MTM zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=-76.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2019, "epsg", 2019, "NAD27(76) / MTM zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=-79.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2020, "epsg", 2020, "NAD27(76) / MTM zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=-82.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2021, "epsg", 2021, "NAD27(76) / MTM zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=-81 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2022, "epsg", 2022, "NAD27(76) / MTM zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=-84 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2023, "epsg", 2023, "NAD27(76) / MTM zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=-87 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2024, "epsg", 2024, "NAD27(76) / MTM zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=-90 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2025, "epsg", 2025, "NAD27(76) / MTM zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=-93 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2026, "epsg", 2026, "NAD27(76) / MTM zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=-96 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2027, "epsg", 2027, "NAD27(76) / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=clrk66 +units=m +no_defs"},
    {
    2028, "epsg", 2028, "NAD27(76) / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=clrk66 +units=m +no_defs"},
    {
    2029, "epsg", 2029, "NAD27(76) / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=clrk66 +units=m +no_defs"},
    {
    2030, "epsg", 2030, "NAD27(76) / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=clrk66 +units=m +no_defs"},
    {
    2031, "epsg", 2031, "NAD27(CGQ77) / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=clrk66 +units=m +no_defs"},
    {
    2032, "epsg", 2032, "NAD27(CGQ77) / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=clrk66 +units=m +no_defs"},
    {
    2033, "epsg", 2033, "NAD27(CGQ77) / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=clrk66 +units=m +no_defs"},
    {
    2034, "epsg", 2034, "NAD27(CGQ77) / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=clrk66 +units=m +no_defs"},
    {
    2035, "epsg", 2035, "NAD27(CGQ77) / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=clrk66 +units=m +no_defs"},
    {
    2036, "epsg", 2036, "NAD83(CSRS98) / New Brunswick Stereo (deprecated)",
        "+proj=sterea +lat_0=46.5 +lon_0=-66.5 +k=0.999912 +x_0=2500000 +y_0=7500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2037, "epsg", 2037, "NAD83(CSRS98) / UTM zone 19N (deprecated)",
        "+proj=utm +zone=19 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2038, "epsg", 2038, "NAD83(CSRS98) / UTM zone 20N (deprecated)",
        "+proj=utm +zone=20 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2039, "epsg", 2039, "Israel / Israeli TM Grid",
        "+proj=tmerc +lat_0=31.73439361111111 +lon_0=35.20451694444445 +k=1.0000067 +x_0=219529.584 +y_0=626907.39 +ellps=GRS80 +towgs84=-48,55,52,0,0,0,0 +units=m +no_defs"},
    {
    2040, "epsg", 2040, "Locodjo 1965 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=clrk80 +towgs84=-125,53,467,0,0,0,0 +units=m +no_defs"},
    {
    2041, "epsg", 2041, "Abidjan 1987 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=clrk80 +towgs84=-124.76,53,466.79,0,0,0,0 +units=m +no_defs"},
    {
    2042, "epsg", 2042, "Locodjo 1965 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=clrk80 +towgs84=-125,53,467,0,0,0,0 +units=m +no_defs"},
    {
    2043, "epsg", 2043, "Abidjan 1987 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=clrk80 +towgs84=-124.76,53,466.79,0,0,0,0 +units=m +no_defs"},
    {
    2044, "epsg", 2044, "Hanoi 1972 / Gauss-Kruger zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=18500000 +y_0=0 +ellps=krass +towgs84=-17.51,-108.32,-62.39,0,0,0,0 +units=m +no_defs"},
    {
    2045, "epsg", 2045, "Hanoi 1972 / Gauss-Kruger zone 19",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=19500000 +y_0=0 +ellps=krass +towgs84=-17.51,-108.32,-62.39,0,0,0,0 +units=m +no_defs"},
    {
    2056, "epsg", 2056, "CH1903+ / LV95",
        "+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 +k_0=1 +x_0=2600000 +y_0=1200000 +ellps=bessel +towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs"},
    {
    2057, "epsg", 2057, "Rassadiran / Nakhl e Taqi",
        "+proj=omerc +lat_0=27.51882880555555 +lonc=52.60353916666667 +alpha=0.5716611944444444 +k=0.999895934 +x_0=658377.437 +y_0=3044969.194 +ellps=intl +towgs84=-133.63,-157.5,-158.62,0,0,0,0 +units=m +no_defs"},
    {
    2058, "epsg", 2058, "ED50(ED77) / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=intl +units=m +no_defs"},
    {
    2059, "epsg", 2059, "ED50(ED77) / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=intl +units=m +no_defs"},
    {
    2060, "epsg", 2060, "ED50(ED77) / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=intl +units=m +no_defs"},
    {
    2061, "epsg", 2061, "ED50(ED77) / UTM zone 41N",
        "+proj=utm +zone=41 +ellps=intl +units=m +no_defs"},
    {
    2062, "epsg", 2062, "Madrid 1870 (Madrid) / Spain",
        "+proj=lcc +lat_1=40 +lat_0=40 +lon_0=0 +k_0=0.9988085293 +x_0=600000 +y_0=600000 +a=6378298.3 +b=6356657.142669561 +pm=madrid +units=m +no_defs"},
    {
    2063, "epsg", 2063, "Dabola 1981 / UTM zone 28N (deprecated)",
        "+proj=utm +zone=28 +a=6378249.2 +b=6356515 +towgs84=-23,259,-9,0,0,0,0 +units=m +no_defs"},
    {
    2064, "epsg", 2064, "Dabola 1981 / UTM zone 29N (deprecated)",
        "+proj=utm +zone=29 +a=6378249.2 +b=6356515 +towgs84=-23,259,-9,0,0,0,0 +units=m +no_defs"},
    {
    2065, "epsg", 2065, "S-JTSK (Ferro) / Krovak",
        "+proj=krovak +lat_0=49.5 +lon_0=42.5 +alpha=30.28813972222222 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    2066, "epsg", 2066, "Mount Dillon / Tobago Grid",
        "+proj=cass +lat_0=11.25217861111111 +lon_0=-60.68600888888889 +x_0=37718.66159325 +y_0=36209.91512952 +a=6378293.645208759 +b=6356617.987679838 +to_meter=0.201166195164 +no_defs"},
    {
    2067, "epsg", 2067, "Naparima 1955 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=intl +units=m +no_defs"},
    {
    2068, "epsg", 2068, "ELD79 / Libya zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2069, "epsg", 2069, "ELD79 / Libya zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=11 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2070, "epsg", 2070, "ELD79 / Libya zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=13 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2071, "epsg", 2071, "ELD79 / Libya zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2072, "epsg", 2072, "ELD79 / Libya zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=17 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2073, "epsg", 2073, "ELD79 / Libya zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=19 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2074, "epsg", 2074, "ELD79 / Libya zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2075, "epsg", 2075, "ELD79 / Libya zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=23 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2076, "epsg", 2076, "ELD79 / Libya zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=25 +k=0.9999 +x_0=200000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2077, "epsg", 2077, "ELD79 / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=intl +units=m +no_defs"},
    {
    2078, "epsg", 2078, "ELD79 / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=intl +units=m +no_defs"},
    {
    2079, "epsg", 2079, "ELD79 / UTM zone 34N",
        "+proj=utm +zone=34 +ellps=intl +units=m +no_defs"},
    {
    2080, "epsg", 2080, "ELD79 / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=intl +units=m +no_defs"},
    {
    2081, "epsg", 2081, "Chos Malal 1914 / Argentina zone 2",
        "+proj=tmerc +lat_0=-90 +lon_0=-69 +k=1 +x_0=2500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2082, "epsg", 2082, "Pampa del Castillo / Argentina zone 2",
        "+proj=tmerc +lat_0=-90 +lon_0=-69 +k=1 +x_0=2500000 +y_0=0 +ellps=intl +towgs84=27.5,14,186.4,0,0,0,0 +units=m +no_defs"},
    {
    2083, "epsg", 2083, "Hito XVIII 1963 / Argentina zone 2",
        "+proj=tmerc +lat_0=-90 +lon_0=-69 +k=1 +x_0=2500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2084, "epsg", 2084, "Hito XVIII 1963 / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=intl +units=m +no_defs"},
    {
    2085, "epsg", 2085, "NAD27 / Cuba Norte (deprecated)",
        "+proj=lcc +lat_1=22.35 +lat_0=22.35 +lon_0=-81 +k_0=0.99993602 +x_0=500000 +y_0=280296.016 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    2086, "epsg", 2086, "NAD27 / Cuba Sur (deprecated)",
        "+proj=lcc +lat_1=20.71666666666667 +lat_0=20.71666666666667 +lon_0=-76.83333333333333 +k_0=0.99994848 +x_0=500000 +y_0=229126.939 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    2087, "epsg", 2087, "ELD79 / TM 12 NE",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=0.9996 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2088, "epsg", 2088, "Carthage / TM 11 NE",
        "+proj=tmerc +lat_0=0 +lon_0=11 +k=0.9996 +x_0=500000 +y_0=0 +a=6378249.2 +b=6356515 +datum=carthage +units=m +no_defs"},
    {
    2089, "epsg", 2089, "Yemen NGN96 / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2090, "epsg", 2090, "Yemen NGN96 / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2091, "epsg", 2091, "South Yemen / Gauss Kruger zone 8 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=8500000 +y_0=0 +ellps=krass +towgs84=-76,-138,67,0,0,0,0 +units=m +no_defs"},
    {
    2092, "epsg", 2092, "South Yemen / Gauss Kruger zone 9 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=9500000 +y_0=0 +ellps=krass +towgs84=-76,-138,67,0,0,0,0 +units=m +no_defs"},
    {
    2093, "epsg", 2093, "Hanoi 1972 / GK 106 NE",
        "+proj=tmerc +lat_0=0 +lon_0=106 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=-17.51,-108.32,-62.39,0,0,0,0 +units=m +no_defs"},
    {
    2094, "epsg", 2094, "WGS 72BE / TM 106 NE",
        "+proj=tmerc +lat_0=0 +lon_0=106 +k=0.9996 +x_0=500000 +y_0=0 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    2095, "epsg", 2095, "Bissau / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=intl +towgs84=-173,253,27,0,0,0,0 +units=m +no_defs"},
    {
    2096, "epsg", 2096, "Korean 1985 / Korea East Belt",
        "+proj=tmerc +lat_0=38 +lon_0=129 +k=1 +x_0=200000 +y_0=500000 +ellps=bessel +units=m +no_defs"},
    {
    2097, "epsg", 2097, "Korean 1985 / Korea Central Belt",
        "+proj=tmerc +lat_0=38 +lon_0=127 +k=1 +x_0=200000 +y_0=500000 +ellps=bessel +units=m +no_defs"},
    {
    2098, "epsg", 2098, "Korean 1985 / Korea West Belt",
        "+proj=tmerc +lat_0=38 +lon_0=125 +k=1 +x_0=200000 +y_0=500000 +ellps=bessel +units=m +no_defs"},
    {
    2099, "epsg", 2099, "Qatar 1948 / Qatar Grid",
        "+proj=cass +lat_0=25.38236111111111 +lon_0=50.76138888888889 +x_0=100000 +y_0=100000 +ellps=helmert +units=m +no_defs"},
    {
    2100, "epsg", 2100, "GGRS87 / Greek Grid",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9996 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=GGRS87 +units=m +no_defs"},
    {
    2101, "epsg", 2101, "Lake / Maracaibo Grid M1",
        "+proj=lcc +lat_1=10.16666666666667 +lat_0=10.16666666666667 +lon_0=-71.60561777777777 +k_0=1 +x_0=0 +y_0=-52684.972 +ellps=intl +units=m +no_defs"},
    {
    2102, "epsg", 2102, "Lake / Maracaibo Grid",
        "+proj=lcc +lat_1=10.16666666666667 +lat_0=10.16666666666667 +lon_0=-71.60561777777777 +k_0=1 +x_0=200000 +y_0=147315.028 +ellps=intl +units=m +no_defs"},
    {
    2103, "epsg", 2103, "Lake / Maracaibo Grid M3",
        "+proj=lcc +lat_1=10.16666666666667 +lat_0=10.16666666666667 +lon_0=-71.60561777777777 +k_0=1 +x_0=500000 +y_0=447315.028 +ellps=intl +units=m +no_defs"},
    {
    2104, "epsg", 2104, "Lake / Maracaibo La Rosa Grid",
        "+proj=lcc +lat_1=10.16666666666667 +lat_0=10.16666666666667 +lon_0=-71.60561777777777 +k_0=1 +x_0=-17044 +y_0=-23139.97 +ellps=intl +units=m +no_defs"},
    {
    2105, "epsg", 2105, "NZGD2000 / Mount Eden 2000",
        "+proj=tmerc +lat_0=-36.87972222222222 +lon_0=174.7641666666667 +k=0.9999 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2106, "epsg", 2106, "NZGD2000 / Bay of Plenty 2000",
        "+proj=tmerc +lat_0=-37.76111111111111 +lon_0=176.4661111111111 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2107, "epsg", 2107, "NZGD2000 / Poverty Bay 2000",
        "+proj=tmerc +lat_0=-38.62444444444444 +lon_0=177.8855555555556 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2108, "epsg", 2108, "NZGD2000 / Hawkes Bay 2000",
        "+proj=tmerc +lat_0=-39.65083333333333 +lon_0=176.6736111111111 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2109, "epsg", 2109, "NZGD2000 / Taranaki 2000",
        "+proj=tmerc +lat_0=-39.13555555555556 +lon_0=174.2277777777778 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2110, "epsg", 2110, "NZGD2000 / Tuhirangi 2000",
        "+proj=tmerc +lat_0=-39.51222222222222 +lon_0=175.64 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2111, "epsg", 2111, "NZGD2000 / Wanganui 2000",
        "+proj=tmerc +lat_0=-40.24194444444444 +lon_0=175.4880555555555 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2112, "epsg", 2112, "NZGD2000 / Wairarapa 2000",
        "+proj=tmerc +lat_0=-40.92527777777777 +lon_0=175.6472222222222 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2113, "epsg", 2113, "NZGD2000 / Wellington 2000",
        "+proj=tmerc +lat_0=-41.3011111111111 +lon_0=174.7763888888889 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2114, "epsg", 2114, "NZGD2000 / Collingwood 2000",
        "+proj=tmerc +lat_0=-40.71472222222223 +lon_0=172.6719444444444 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2115, "epsg", 2115, "NZGD2000 / Nelson 2000",
        "+proj=tmerc +lat_0=-41.27444444444444 +lon_0=173.2991666666667 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2116, "epsg", 2116, "NZGD2000 / Karamea 2000",
        "+proj=tmerc +lat_0=-41.28972222222222 +lon_0=172.1088888888889 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2117, "epsg", 2117, "NZGD2000 / Buller 2000",
        "+proj=tmerc +lat_0=-41.81055555555555 +lon_0=171.5811111111111 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2118, "epsg", 2118, "NZGD2000 / Grey 2000",
        "+proj=tmerc +lat_0=-42.33361111111111 +lon_0=171.5497222222222 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2119, "epsg", 2119, "NZGD2000 / Amuri 2000",
        "+proj=tmerc +lat_0=-42.68888888888888 +lon_0=173.01 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2120, "epsg", 2120, "NZGD2000 / Marlborough 2000",
        "+proj=tmerc +lat_0=-41.54444444444444 +lon_0=173.8019444444444 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2121, "epsg", 2121, "NZGD2000 / Hokitika 2000",
        "+proj=tmerc +lat_0=-42.88611111111111 +lon_0=170.9797222222222 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2122, "epsg", 2122, "NZGD2000 / Okarito 2000",
        "+proj=tmerc +lat_0=-43.11 +lon_0=170.2608333333333 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2123, "epsg", 2123, "NZGD2000 / Jacksons Bay 2000",
        "+proj=tmerc +lat_0=-43.97777777777778 +lon_0=168.6061111111111 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2124, "epsg", 2124, "NZGD2000 / Mount Pleasant 2000",
        "+proj=tmerc +lat_0=-43.59055555555556 +lon_0=172.7269444444445 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2125, "epsg", 2125, "NZGD2000 / Gawler 2000",
        "+proj=tmerc +lat_0=-43.74861111111111 +lon_0=171.3605555555555 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2126, "epsg", 2126, "NZGD2000 / Timaru 2000",
        "+proj=tmerc +lat_0=-44.40194444444445 +lon_0=171.0572222222222 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2127, "epsg", 2127, "NZGD2000 / Lindis Peak 2000",
        "+proj=tmerc +lat_0=-44.735 +lon_0=169.4675 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2128, "epsg", 2128, "NZGD2000 / Mount Nicholas 2000",
        "+proj=tmerc +lat_0=-45.13277777777778 +lon_0=168.3986111111111 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2129, "epsg", 2129, "NZGD2000 / Mount York 2000",
        "+proj=tmerc +lat_0=-45.56361111111111 +lon_0=167.7386111111111 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2130, "epsg", 2130, "NZGD2000 / Observation Point 2000",
        "+proj=tmerc +lat_0=-45.81611111111111 +lon_0=170.6283333333333 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2131, "epsg", 2131, "NZGD2000 / North Taieri 2000",
        "+proj=tmerc +lat_0=-45.86138888888889 +lon_0=170.2825 +k=0.99996 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2132, "epsg", 2132, "NZGD2000 / Bluff 2000",
        "+proj=tmerc +lat_0=-46.6 +lon_0=168.3427777777778 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2133, "epsg", 2133, "NZGD2000 / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2134, "epsg", 2134, "NZGD2000 / UTM zone 59S",
        "+proj=utm +zone=59 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2135, "epsg", 2135, "NZGD2000 / UTM zone 60S",
        "+proj=utm +zone=60 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2136, "epsg", 2136, "Accra / Ghana National Grid",
        "+proj=tmerc +lat_0=4.666666666666667 +lon_0=-1 +k=0.99975 +x_0=274319.7391633579 +y_0=0 +a=6378300 +b=6356751.689189189 +to_meter=0.3047997101815088 +no_defs"},
    {
    2137, "epsg", 2137, "Accra / TM 1 NW",
        "+proj=tmerc +lat_0=0 +lon_0=-1 +k=0.9996 +x_0=500000 +y_0=0 +a=6378300 +b=6356751.689189189 +units=m +no_defs"},
    {
    2138, "epsg", 2138, "NAD27(CGQ77) / Quebec Lambert",
        "+proj=lcc +lat_1=60 +lat_2=46 +lat_0=44 +lon_0=-68.5 +x_0=0 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    2139, "epsg", 2139, "NAD83(CSRS98) / SCoPQ zone 2 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-55.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2140, "epsg", 2140, "NAD83(CSRS98) / MTM zone 3 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-58.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2141, "epsg", 2141, "NAD83(CSRS98) / MTM zone 4 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-61.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2142, "epsg", 2142, "NAD83(CSRS98) / MTM zone 5 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-64.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2143, "epsg", 2143, "NAD83(CSRS98) / MTM zone 6 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-67.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2144, "epsg", 2144, "NAD83(CSRS98) / MTM zone 7 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-70.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2145, "epsg", 2145, "NAD83(CSRS98) / MTM zone 8 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-73.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2146, "epsg", 2146, "NAD83(CSRS98) / MTM zone 9 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-76.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2147, "epsg", 2147, "NAD83(CSRS98) / MTM zone 10 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-79.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2148, "epsg", 2148, "NAD83(CSRS98) / UTM zone 21N (deprecated)",
        "+proj=utm +zone=21 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2149, "epsg", 2149, "NAD83(CSRS98) / UTM zone 18N (deprecated)",
        "+proj=utm +zone=18 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2150, "epsg", 2150, "NAD83(CSRS98) / UTM zone 17N (deprecated)",
        "+proj=utm +zone=17 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2151, "epsg", 2151, "NAD83(CSRS98) / UTM zone 13N (deprecated)",
        "+proj=utm +zone=13 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2152, "epsg", 2152, "NAD83(CSRS98) / UTM zone 12N (deprecated)",
        "+proj=utm +zone=12 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2153, "epsg", 2153, "NAD83(CSRS98) / UTM zone 11N (deprecated)",
        "+proj=utm +zone=11 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2154, "epsg", 2154, "RGF93 / Lambert-93",
        "+proj=lcc +lat_1=49 +lat_2=44 +lat_0=46.5 +lon_0=3 +x_0=700000 +y_0=6600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2155, "epsg", 2155,
        "American Samoa 1962 / American Samoa Lambert (deprecated)",
        "+proj=lcc +lat_1=-14.26666666666667 +lat_0=-14.26666666666667 +lon_0=170 +k_0=1 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +towgs84=-115,118,426,0,0,0,0 +units=us-ft +no_defs"},
    {
    2156, "epsg", 2156, "NAD83(HARN) / UTM zone 59S (deprecated)",
        "+proj=utm +zone=59 +south +ellps=GRS80 +units=m +no_defs"},
    {
    2157, "epsg", 2157, "IRENET95 / Irish Transverse Mercator",
        "+proj=tmerc +lat_0=53.5 +lon_0=-8 +k=0.99982 +x_0=600000 +y_0=750000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2158, "epsg", 2158, "IRENET95 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2159, "epsg", 2159, "Sierra Leone 1924 / New Colony Grid",
        "+proj=tmerc +lat_0=6.666666666666667 +lon_0=-12 +k=1 +x_0=152399.8550907544 +y_0=0 +a=6378300 +b=6356751.689189189 +to_meter=0.3047997101815088 +no_defs"},
    {
    2160, "epsg", 2160, "Sierra Leone 1924 / New War Office Grid",
        "+proj=tmerc +lat_0=6.666666666666667 +lon_0=-12 +k=1 +x_0=243839.7681452071 +y_0=182879.8261089053 +a=6378300 +b=6356751.689189189 +to_meter=0.3047997101815088 +no_defs"},
    {
    2161, "epsg", 2161, "Sierra Leone 1968 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=clrk80 +towgs84=-88,4,101,0,0,0,0 +units=m +no_defs"},
    {
    2162, "epsg", 2162, "Sierra Leone 1968 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=clrk80 +towgs84=-88,4,101,0,0,0,0 +units=m +no_defs"},
    {
    2163, "epsg", 2163, "unnamed",
        "+proj=laea +lat_0=45 +lon_0=-100 +x_0=0 +y_0=0 +a=6370997 +b=6370997 +units=m +no_defs"},
    {
    2164, "epsg", 2164, "Locodjo 1965 / TM 5 NW",
        "+proj=tmerc +lat_0=0 +lon_0=-5 +k=0.9996 +x_0=500000 +y_0=0 +ellps=clrk80 +towgs84=-125,53,467,0,0,0,0 +units=m +no_defs"},
    {
    2165, "epsg", 2165, "Abidjan 1987 / TM 5 NW",
        "+proj=tmerc +lat_0=0 +lon_0=-5 +k=0.9996 +x_0=500000 +y_0=0 +ellps=clrk80 +towgs84=-124.76,53,466.79,0,0,0,0 +units=m +no_defs"},
    {
    2166, "epsg", 2166, "Pulkovo 1942(83) / Gauss Kruger zone 3 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=3500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2167, "epsg", 2167, "Pulkovo 1942(83) / Gauss Kruger zone 4 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2168, "epsg", 2168, "Pulkovo 1942(83) / Gauss Kruger zone 5 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=5500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2169, "epsg", 2169, "Luxembourg 1930 / Gauss",
        "+proj=tmerc +lat_0=49.83333333333334 +lon_0=6.166666666666667 +k=1 +x_0=80000 +y_0=100000 +ellps=intl +towgs84=-193,13.7,-39.3,-0.41,-2.933,2.688,0.43 +units=m +no_defs"},
    {
    2170, "epsg", 2170, "MGI / Slovenia Grid (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9999 +x_0=500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    2171, "epsg", 2171, "Pulkovo 1942(58) / Poland zone I (deprecated)",
        "+proj=sterea +lat_0=50.625 +lon_0=21.08333333333333 +k=0.9998 +x_0=4637000 +y_0=5647000 +ellps=krass +units=m +no_defs"},
    {
    2172, "epsg", 2172, "Pulkovo 1942(58) / Poland zone II",
        "+proj=sterea +lat_0=53.00194444444445 +lon_0=21.50277777777778 +k=0.9998 +x_0=4603000 +y_0=5806000 +ellps=krass +units=m +no_defs"},
    {
    2173, "epsg", 2173, "Pulkovo 1942(58) / Poland zone III",
        "+proj=sterea +lat_0=53.58333333333334 +lon_0=17.00833333333333 +k=0.9998 +x_0=3501000 +y_0=5999000 +ellps=krass +units=m +no_defs"},
    {
    2174, "epsg", 2174, "Pulkovo 1942(58) / Poland zone IV",
        "+proj=sterea +lat_0=51.67083333333333 +lon_0=16.67222222222222 +k=0.9998 +x_0=3703000 +y_0=5627000 +ellps=krass +units=m +no_defs"},
    {
    2175, "epsg", 2175, "Pulkovo 1942(58) / Poland zone V",
        "+proj=tmerc +lat_0=0 +lon_0=18.95833333333333 +k=0.999983 +x_0=237000 +y_0=-4700000 +ellps=krass +units=m +no_defs"},
    {
    2176, "epsg", 2176, "ETRS89 / Poland CS2000 zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.999923 +x_0=5500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2177, "epsg", 2177, "ETRS89 / Poland CS2000 zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=0.999923 +x_0=6500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2178, "epsg", 2178, "ETRS89 / Poland CS2000 zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=0.999923 +x_0=7500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2179, "epsg", 2179, "ETRS89 / Poland CS2000 zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.999923 +x_0=8500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2180, "epsg", 2180, "ETRS89 / Poland CS92",
        "+proj=tmerc +lat_0=0 +lon_0=19 +k=0.9993 +x_0=500000 +y_0=-5300000 +ellps=GRS80 +units=m +no_defs"},
    {
    2188, "epsg", 2188, "Azores Occidental 1939 / UTM zone 25N",
        "+proj=utm +zone=25 +ellps=intl +units=m +no_defs"},
    {
    2189, "epsg", 2189, "Azores Central 1948 / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=intl +towgs84=-104,167,-38,0,0,0,0 +units=m +no_defs"},
    {
    2190, "epsg", 2190, "Azores Oriental 1940 / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=intl +towgs84=-203,141,53,0,0,0,0 +units=m +no_defs"},
    {
    2191, "epsg", 2191, "Madeira 1936 / UTM zone 28N (deprecated)",
        "+proj=utm +zone=28 +ellps=intl +units=m +no_defs"},
    {
    2192, "epsg", 2192, "ED50 / France EuroLambert",
        "+proj=lcc +lat_1=46.8 +lat_0=46.8 +lon_0=2.337229166666667 +k_0=0.99987742 +x_0=600000 +y_0=2200000 +ellps=intl +units=m +no_defs"},
    {
    2193, "epsg", 2193, "NZGD2000 / New Zealand Transverse Mercator 2000",
        "+proj=tmerc +lat_0=0 +lon_0=173 +k=0.9996 +x_0=1600000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2194, "epsg", 2194,
        "American Samoa 1962 / American Samoa Lambert (deprecated)",
        "+proj=lcc +lat_1=-14.26666666666667 +lat_0=-14.26666666666667 +lon_0=-170 +k_0=1 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +towgs84=-115,118,426,0,0,0,0 +units=us-ft +no_defs"},
    {
    2195, "epsg", 2195, "NAD83(HARN) / UTM zone 2S",
        "+proj=utm +zone=2 +south +ellps=GRS80 +units=m +no_defs"},
    {
    2196, "epsg", 2196, "ETRS89 / Kp2000 Jutland",
        "+proj=tmerc +lat_0=0 +lon_0=9.5 +k=0.99995 +x_0=200000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2197, "epsg", 2197, "ETRS89 / Kp2000 Zealand",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=0.99995 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2198, "epsg", 2198, "ETRS89 / Kp2000 Bornholm",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=900000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2199, "epsg", 2199, "Albanian 1987 / Gauss Kruger zone 4 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2200, "epsg", 2200, "ATS77 / New Brunswick Stereographic (ATS77)",
        "+proj=sterea +lat_0=46.5 +lon_0=-66.5 +k=0.999912 +x_0=300000 +y_0=800000 +a=6378135 +b=6356750.304921594 +units=m +no_defs"},
    {
    2201, "epsg", 2201, "REGVEN / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2202, "epsg", 2202, "REGVEN / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2203, "epsg", 2203, "REGVEN / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2204, "epsg", 2204, "NAD27 / Tennessee",
        "+proj=lcc +lat_1=35.25 +lat_2=36.41666666666666 +lat_0=34.66666666666666 +lon_0=-86 +x_0=609601.2192024384 +y_0=30480.06096012192 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    2205, "epsg", 2205, "NAD83 / Kentucky North",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=38.96666666666667 +lat_0=37.5 +lon_0=-84.25 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    2206, "epsg", 2206, "ED50 / 3-degree Gauss-Kruger zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=9500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2207, "epsg", 2207, "ED50 / 3-degree Gauss-Kruger zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=10500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2208, "epsg", 2208, "ED50 / 3-degree Gauss-Kruger zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=11500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2209, "epsg", 2209, "ED50 / 3-degree Gauss-Kruger zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=36 +k=1 +x_0=12500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2210, "epsg", 2210, "ED50 / 3-degree Gauss-Kruger zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=13500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2211, "epsg", 2211, "ED50 / 3-degree Gauss-Kruger zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=42 +k=1 +x_0=14500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2212, "epsg", 2212, "ED50 / 3-degree Gauss-Kruger zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=15500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2213, "epsg", 2213, "ETRS89 / TM 30 NE",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=0.9996 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2214, "epsg", 2214, "Douala 1948 / AOF west (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=10.5 +k=0.999 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=-206.1,-174.7,-87.7,0,0,0,0 +units=m +no_defs"},
    {
    2215, "epsg", 2215, "Manoca 1962 / UTM zone 32N",
        "+proj=utm +zone=32 +a=6378249.2 +b=6356515 +towgs84=-70.9,-151.8,-41.4,0,0,0,0 +units=m +no_defs"},
    {
    2216, "epsg", 2216, "Qornoq 1927 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=intl +units=m +no_defs"},
    {
    2217, "epsg", 2217, "Qornoq 1927 / UTM zone 23N",
        "+proj=utm +zone=23 +ellps=intl +units=m +no_defs"},
    {
    2219, "epsg", 2219, "ATS77 / UTM zone 19N",
        "+proj=utm +zone=19 +a=6378135 +b=6356750.304921594 +units=m +no_defs"},
    {
    2220, "epsg", 2220, "ATS77 / UTM zone 20N",
        "+proj=utm +zone=20 +a=6378135 +b=6356750.304921594 +units=m +no_defs"},
    {
    2222, "epsg", 2222, "NAD83 / Arizona East (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-110.1666666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2223, "epsg", 2223, "NAD83 / Arizona Central (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-111.9166666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2224, "epsg", 2224, "NAD83 / Arizona West (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-113.75 +k=0.999933333 +x_0=213360 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2225, "epsg", 2225, "NAD83 / California zone 1 (ftUS)",
        "+proj=lcc +lat_1=41.66666666666666 +lat_2=40 +lat_0=39.33333333333334 +lon_0=-122 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2226, "epsg", 2226, "NAD83 / California zone 2 (ftUS)",
        "+proj=lcc +lat_1=39.83333333333334 +lat_2=38.33333333333334 +lat_0=37.66666666666666 +lon_0=-122 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2227, "epsg", 2227, "NAD83 / California zone 3 (ftUS)",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.06666666666667 +lat_0=36.5 +lon_0=-120.5 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2228, "epsg", 2228, "NAD83 / California zone 4 (ftUS)",
        "+proj=lcc +lat_1=37.25 +lat_2=36 +lat_0=35.33333333333334 +lon_0=-119 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2229, "epsg", 2229, "NAD83 / California zone 5 (ftUS)",
        "+proj=lcc +lat_1=35.46666666666667 +lat_2=34.03333333333333 +lat_0=33.5 +lon_0=-118 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2230, "epsg", 2230, "NAD83 / California zone 6 (ftUS)",
        "+proj=lcc +lat_1=33.88333333333333 +lat_2=32.78333333333333 +lat_0=32.16666666666666 +lon_0=-116.25 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2231, "epsg", 2231, "NAD83 / Colorado North (ftUS)",
        "+proj=lcc +lat_1=40.78333333333333 +lat_2=39.71666666666667 +lat_0=39.33333333333334 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2232, "epsg", 2232, "NAD83 / Colorado Central (ftUS)",
        "+proj=lcc +lat_1=39.75 +lat_2=38.45 +lat_0=37.83333333333334 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2233, "epsg", 2233, "NAD83 / Colorado South (ftUS)",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.23333333333333 +lat_0=36.66666666666666 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2234, "epsg", 2234, "NAD83 / Connecticut (ftUS)",
        "+proj=lcc +lat_1=41.86666666666667 +lat_2=41.2 +lat_0=40.83333333333334 +lon_0=-72.75 +x_0=304800.6096012192 +y_0=152400.3048006096 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2235, "epsg", 2235, "NAD83 / Delaware (ftUS)",
        "+proj=tmerc +lat_0=38 +lon_0=-75.41666666666667 +k=0.999995 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2236, "epsg", 2236, "NAD83 / Florida East (ftUS)",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-81 +k=0.999941177 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2237, "epsg", 2237, "NAD83 / Florida West (ftUS)",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-82 +k=0.999941177 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2238, "epsg", 2238, "NAD83 / Florida North (ftUS)",
        "+proj=lcc +lat_1=30.75 +lat_2=29.58333333333333 +lat_0=29 +lon_0=-84.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2239, "epsg", 2239, "NAD83 / Georgia East (ftUS)",
        "+proj=tmerc +lat_0=30 +lon_0=-82.16666666666667 +k=0.9999 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2240, "epsg", 2240, "NAD83 / Georgia West (ftUS)",
        "+proj=tmerc +lat_0=30 +lon_0=-84.16666666666667 +k=0.9999 +x_0=699999.9998983998 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2241, "epsg", 2241, "NAD83 / Idaho East (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-112.1666666666667 +k=0.9999473679999999 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2242, "epsg", 2242, "NAD83 / Idaho Central (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-114 +k=0.9999473679999999 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2243, "epsg", 2243, "NAD83 / Idaho West (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-115.75 +k=0.999933333 +x_0=800000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2244, "epsg", 2244, "NAD83 / Indiana East (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=99999.99989839978 +y_0=249364.9987299975 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2245, "epsg", 2245, "NAD83 / Indiana West (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=900000 +y_0=249364.9987299975 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2246, "epsg", 2246, "NAD83 / Kentucky North (ftUS)",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=38.96666666666667 +lat_0=37.5 +lon_0=-84.25 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2247, "epsg", 2247, "NAD83 / Kentucky South (ftUS)",
        "+proj=lcc +lat_1=37.93333333333333 +lat_2=36.73333333333333 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=500000.0001016001 +y_0=500000.0001016001 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2248, "epsg", 2248, "NAD83 / Maryland (ftUS)",
        "+proj=lcc +lat_1=39.45 +lat_2=38.3 +lat_0=37.66666666666666 +lon_0=-77 +x_0=399999.9998983998 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2249, "epsg", 2249, "NAD83 / Massachusetts Mainland (ftUS)",
        "+proj=lcc +lat_1=42.68333333333333 +lat_2=41.71666666666667 +lat_0=41 +lon_0=-71.5 +x_0=200000.0001016002 +y_0=750000 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2250, "epsg", 2250, "NAD83 / Massachusetts Island (ftUS)",
        "+proj=lcc +lat_1=41.48333333333333 +lat_2=41.28333333333333 +lat_0=41 +lon_0=-70.5 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2251, "epsg", 2251, "NAD83 / Michigan North (ft)",
        "+proj=lcc +lat_1=47.08333333333334 +lat_2=45.48333333333333 +lat_0=44.78333333333333 +lon_0=-87 +x_0=7999999.999968001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2252, "epsg", 2252, "NAD83 / Michigan Central (ft)",
        "+proj=lcc +lat_1=45.7 +lat_2=44.18333333333333 +lat_0=43.31666666666667 +lon_0=-84.36666666666666 +x_0=5999999.999976001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2253, "epsg", 2253, "NAD83 / Michigan South (ft)",
        "+proj=lcc +lat_1=43.66666666666666 +lat_2=42.1 +lat_0=41.5 +lon_0=-84.36666666666666 +x_0=3999999.999984 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2254, "epsg", 2254, "NAD83 / Mississippi East (ftUS)",
        "+proj=tmerc +lat_0=29.5 +lon_0=-88.83333333333333 +k=0.99995 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2255, "epsg", 2255, "NAD83 / Mississippi West (ftUS)",
        "+proj=tmerc +lat_0=29.5 +lon_0=-90.33333333333333 +k=0.99995 +x_0=699999.9998983998 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2256, "epsg", 2256, "NAD83 / Montana (ft)",
        "+proj=lcc +lat_1=49 +lat_2=45 +lat_0=44.25 +lon_0=-109.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2257, "epsg", 2257, "NAD83 / New Mexico East (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-104.3333333333333 +k=0.999909091 +x_0=165000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2258, "epsg", 2258, "NAD83 / New Mexico Central (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-106.25 +k=0.9999 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2259, "epsg", 2259, "NAD83 / New Mexico West (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-107.8333333333333 +k=0.999916667 +x_0=830000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2260, "epsg", 2260, "NAD83 / New York East (ftUS)",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2261, "epsg", 2261, "NAD83 / New York Central (ftUS)",
        "+proj=tmerc +lat_0=40 +lon_0=-76.58333333333333 +k=0.9999375 +x_0=249999.9998983998 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2262, "epsg", 2262, "NAD83 / New York West (ftUS)",
        "+proj=tmerc +lat_0=40 +lon_0=-78.58333333333333 +k=0.9999375 +x_0=350000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2263, "epsg", 2263, "NAD83 / New York Long Island (ftUS)",
        "+proj=lcc +lat_1=41.03333333333333 +lat_2=40.66666666666666 +lat_0=40.16666666666666 +lon_0=-74 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2264, "epsg", 2264, "NAD83 / North Carolina (ftUS)",
        "+proj=lcc +lat_1=36.16666666666666 +lat_2=34.33333333333334 +lat_0=33.75 +lon_0=-79 +x_0=609601.2192024384 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2265, "epsg", 2265, "NAD83 / North Dakota North (ft)",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.43333333333333 +lat_0=47 +lon_0=-100.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2266, "epsg", 2266, "NAD83 / North Dakota South (ft)",
        "+proj=lcc +lat_1=47.48333333333333 +lat_2=46.18333333333333 +lat_0=45.66666666666666 +lon_0=-100.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2267, "epsg", 2267, "NAD83 / Oklahoma North (ftUS)",
        "+proj=lcc +lat_1=36.76666666666667 +lat_2=35.56666666666667 +lat_0=35 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2268, "epsg", 2268, "NAD83 / Oklahoma South (ftUS)",
        "+proj=lcc +lat_1=35.23333333333333 +lat_2=33.93333333333333 +lat_0=33.33333333333334 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2269, "epsg", 2269, "NAD83 / Oregon North (ft)",
        "+proj=lcc +lat_1=46 +lat_2=44.33333333333334 +lat_0=43.66666666666666 +lon_0=-120.5 +x_0=2500000.0001424 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2270, "epsg", 2270, "NAD83 / Oregon South (ft)",
        "+proj=lcc +lat_1=44 +lat_2=42.33333333333334 +lat_0=41.66666666666666 +lon_0=-120.5 +x_0=1500000.0001464 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2271, "epsg", 2271, "NAD83 / Pennsylvania North (ftUS)",
        "+proj=lcc +lat_1=41.95 +lat_2=40.88333333333333 +lat_0=40.16666666666666 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2272, "epsg", 2272, "NAD83 / Pennsylvania South (ftUS)",
        "+proj=lcc +lat_1=40.96666666666667 +lat_2=39.93333333333333 +lat_0=39.33333333333334 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2273, "epsg", 2273, "NAD83 / South Carolina (ft)",
        "+proj=lcc +lat_1=34.83333333333334 +lat_2=32.5 +lat_0=31.83333333333333 +lon_0=-81 +x_0=609600 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2274, "epsg", 2274, "NAD83 / Tennessee (ftUS)",
        "+proj=lcc +lat_1=36.41666666666666 +lat_2=35.25 +lat_0=34.33333333333334 +lon_0=-86 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2275, "epsg", 2275, "NAD83 / Texas North (ftUS)",
        "+proj=lcc +lat_1=36.18333333333333 +lat_2=34.65 +lat_0=34 +lon_0=-101.5 +x_0=200000.0001016002 +y_0=999999.9998983998 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2276, "epsg", 2276, "NAD83 / Texas North Central (ftUS)",
        "+proj=lcc +lat_1=33.96666666666667 +lat_2=32.13333333333333 +lat_0=31.66666666666667 +lon_0=-98.5 +x_0=600000 +y_0=2000000.0001016 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2277, "epsg", 2277, "NAD83 / Texas Central (ftUS)",
        "+proj=lcc +lat_1=31.88333333333333 +lat_2=30.11666666666667 +lat_0=29.66666666666667 +lon_0=-100.3333333333333 +x_0=699999.9998983998 +y_0=3000000 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2278, "epsg", 2278, "NAD83 / Texas South Central (ftUS)",
        "+proj=lcc +lat_1=30.28333333333333 +lat_2=28.38333333333333 +lat_0=27.83333333333333 +lon_0=-99 +x_0=600000 +y_0=3999999.9998984 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2279, "epsg", 2279, "NAD83 / Texas South (ftUS)",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.66666666666667 +lon_0=-98.5 +x_0=300000.0000000001 +y_0=5000000.0001016 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2280, "epsg", 2280, "NAD83 / Utah North (ft)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000.0001504 +y_0=999999.9999960001 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2281, "epsg", 2281, "NAD83 / Utah Central (ft)",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000.0001504 +y_0=1999999.999992 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2282, "epsg", 2282, "NAD83 / Utah South (ft)",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000.0001504 +y_0=2999999.999988 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2283, "epsg", 2283, "NAD83 / Virginia North (ftUS)",
        "+proj=lcc +lat_1=39.2 +lat_2=38.03333333333333 +lat_0=37.66666666666666 +lon_0=-78.5 +x_0=3500000.0001016 +y_0=2000000.0001016 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2284, "epsg", 2284, "NAD83 / Virginia South (ftUS)",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=36.76666666666667 +lat_0=36.33333333333334 +lon_0=-78.5 +x_0=3500000.0001016 +y_0=999999.9998983998 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2285, "epsg", 2285, "NAD83 / Washington North (ftUS)",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.5 +lat_0=47 +lon_0=-120.8333333333333 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2286, "epsg", 2286, "NAD83 / Washington South (ftUS)",
        "+proj=lcc +lat_1=47.33333333333334 +lat_2=45.83333333333334 +lat_0=45.33333333333334 +lon_0=-120.5 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2287, "epsg", 2287, "NAD83 / Wisconsin North (ftUS)",
        "+proj=lcc +lat_1=46.76666666666667 +lat_2=45.56666666666667 +lat_0=45.16666666666666 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2288, "epsg", 2288, "NAD83 / Wisconsin Central (ftUS)",
        "+proj=lcc +lat_1=45.5 +lat_2=44.25 +lat_0=43.83333333333334 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2289, "epsg", 2289, "NAD83 / Wisconsin South (ftUS)",
        "+proj=lcc +lat_1=44.06666666666667 +lat_2=42.73333333333333 +lat_0=42 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2290, "epsg", 2290, "ATS77 / Prince Edward Isl. Stereographic (ATS77)",
        "+proj=sterea +lat_0=47.25 +lon_0=-63 +k=0.999912 +x_0=700000 +y_0=400000 +a=6378135 +b=6356750.304921594 +units=m +no_defs"},
    {
    2291, "epsg", 2291,
        "NAD83(CSRS98) / Prince Edward Isl. Stereographic (NAD83) (deprecated)",
        "+proj=sterea +lat_0=47.25 +lon_0=-63 +k=0.999912 +x_0=400000 +y_0=800000 +a=6378135 +b=6356750.304921594 +units=m +no_defs"},
    {
    2292, "epsg", 2292,
        "NAD83(CSRS98) / Prince Edward Isl. Stereographic (NAD83) (deprecated)",
        "+proj=sterea +lat_0=47.25 +lon_0=-63 +k=0.999912 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2294, "epsg", 2294, "ATS77 / MTM Nova Scotia zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=-61.5 +k=0.9999 +x_0=4500000 +y_0=0 +a=6378135 +b=6356750.304921594 +units=m +no_defs"},
    {
    2295, "epsg", 2295, "ATS77 / MTM Nova Scotia zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=-64.5 +k=0.9999 +x_0=5500000 +y_0=0 +a=6378135 +b=6356750.304921594 +units=m +no_defs"},
    {
    2308, "epsg", 2308, "Batavia / TM 109 SE",
        "+proj=tmerc +lat_0=0 +lon_0=109 +k=0.9996 +x_0=500000 +y_0=10000000 +ellps=bessel +units=m +no_defs"},
    {
    2309, "epsg", 2309, "WGS 84 / TM 116 SE",
        "+proj=tmerc +lat_0=0 +lon_0=116 +k=0.9996 +x_0=500000 +y_0=10000000 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    2310, "epsg", 2310, "WGS 84 / TM 132 SE",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=0.9996 +x_0=500000 +y_0=10000000 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    2311, "epsg", 2311, "WGS 84 / TM 6 NE",
        "+proj=tmerc +lat_0=0 +lon_0=6 +k=0.9996 +x_0=500000 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    2312, "epsg", 2312, "Garoua / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=clrk80 +units=m +no_defs"},
    {
    2313, "epsg", 2313, "Kousseri / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=clrk80 +units=m +no_defs"},
    {
    2314, "epsg", 2314, "Trinidad 1903 / Trinidad Grid (ftCla)",
        "+proj=cass +lat_0=10.44166666666667 +lon_0=-61.33333333333334 +x_0=86501.46392052001 +y_0=65379.0134283 +a=6378293.645208759 +b=6356617.987679838 +to_meter=0.3047972654 +no_defs"},
    {
    2315, "epsg", 2315, "Campo Inchauspe / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=intl +units=m +no_defs"},
    {
    2316, "epsg", 2316, "Campo Inchauspe / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=intl +units=m +no_defs"},
    {
    2317, "epsg", 2317, "PSAD56 / ICN Regional",
        "+proj=lcc +lat_1=9 +lat_2=3 +lat_0=6 +lon_0=-66 +x_0=1000000 +y_0=1000000 +ellps=intl +units=m +no_defs"},
    {
    2318, "epsg", 2318, "Ain el Abd / Aramco Lambert",
        "+proj=lcc +lat_1=17 +lat_2=33 +lat_0=25.08951 +lon_0=48 +x_0=0 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2319, "epsg", 2319, "ED50 / TM27",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2320, "epsg", 2320, "ED50 / TM30",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2321, "epsg", 2321, "ED50 / TM33",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2322, "epsg", 2322, "ED50 / TM36",
        "+proj=tmerc +lat_0=0 +lon_0=36 +k=1 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2323, "epsg", 2323, "ED50 / TM39",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2324, "epsg", 2324, "ED50 / TM42",
        "+proj=tmerc +lat_0=0 +lon_0=42 +k=1 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2325, "epsg", 2325, "ED50 / TM45",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2326, "epsg", 2326, "Hong Kong 1980 Grid System",
        "+proj=tmerc +lat_0=22.31213333333334 +lon_0=114.1785555555556 +k=1 +x_0=836694.05 +y_0=819069.8 +ellps=intl +towgs84=-162.619,-276.959,-161.764,0.067753,-2.24365,-1.15883,-1.09425 +units=m +no_defs"},
    {
    2327, "epsg", 2327, "Xian 1980 / Gauss-Kruger zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=13500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2328, "epsg", 2328, "Xian 1980 / Gauss-Kruger zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=14500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2329, "epsg", 2329, "Xian 1980 / Gauss-Kruger zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=15500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2330, "epsg", 2330, "Xian 1980 / Gauss-Kruger zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=16500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2331, "epsg", 2331, "Xian 1980 / Gauss-Kruger zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=17500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2332, "epsg", 2332, "Xian 1980 / Gauss-Kruger zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=18500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2333, "epsg", 2333, "Xian 1980 / Gauss-Kruger zone 19",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=19500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2334, "epsg", 2334, "Xian 1980 / Gauss-Kruger zone 20",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=20500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2335, "epsg", 2335, "Xian 1980 / Gauss-Kruger zone 21",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=21500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2336, "epsg", 2336, "Xian 1980 / Gauss-Kruger zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=22500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2337, "epsg", 2337, "Xian 1980 / Gauss-Kruger zone 23",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=23500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2338, "epsg", 2338, "Xian 1980 / Gauss-Kruger CM 75E",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2339, "epsg", 2339, "Xian 1980 / Gauss-Kruger CM 81E",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2340, "epsg", 2340, "Xian 1980 / Gauss-Kruger CM 87E",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2341, "epsg", 2341, "Xian 1980 / Gauss-Kruger CM 93E",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2342, "epsg", 2342, "Xian 1980 / Gauss-Kruger CM 99E",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2343, "epsg", 2343, "Xian 1980 / Gauss-Kruger CM 105E",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2344, "epsg", 2344, "Xian 1980 / Gauss-Kruger CM 111E",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2345, "epsg", 2345, "Xian 1980 / Gauss-Kruger CM 117E",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2346, "epsg", 2346, "Xian 1980 / Gauss-Kruger CM 123E",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2347, "epsg", 2347, "Xian 1980 / Gauss-Kruger CM 129E",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2348, "epsg", 2348, "Xian 1980 / Gauss-Kruger CM 135E",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2349, "epsg", 2349, "Xian 1980 / 3-degree Gauss-Kruger zone 25",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=25500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2350, "epsg", 2350, "Xian 1980 / 3-degree Gauss-Kruger zone 26",
        "+proj=tmerc +lat_0=0 +lon_0=78 +k=1 +x_0=26500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2351, "epsg", 2351, "Xian 1980 / 3-degree Gauss-Kruger zone 27",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=27500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2352, "epsg", 2352, "Xian 1980 / 3-degree Gauss-Kruger zone 28",
        "+proj=tmerc +lat_0=0 +lon_0=84 +k=1 +x_0=28500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2353, "epsg", 2353, "Xian 1980 / 3-degree Gauss-Kruger zone 29",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=29500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2354, "epsg", 2354, "Xian 1980 / 3-degree Gauss-Kruger zone 30",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=1 +x_0=30500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2355, "epsg", 2355, "Xian 1980 / 3-degree Gauss-Kruger zone 31",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=31500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2356, "epsg", 2356, "Xian 1980 / 3-degree Gauss-Kruger zone 32",
        "+proj=tmerc +lat_0=0 +lon_0=96 +k=1 +x_0=32500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2357, "epsg", 2357, "Xian 1980 / 3-degree Gauss-Kruger zone 33",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=33500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2358, "epsg", 2358, "Xian 1980 / 3-degree Gauss-Kruger zone 34",
        "+proj=tmerc +lat_0=0 +lon_0=102 +k=1 +x_0=34500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2359, "epsg", 2359, "Xian 1980 / 3-degree Gauss-Kruger zone 35",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=35500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2360, "epsg", 2360, "Xian 1980 / 3-degree Gauss-Kruger zone 36",
        "+proj=tmerc +lat_0=0 +lon_0=108 +k=1 +x_0=36500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2361, "epsg", 2361, "Xian 1980 / 3-degree Gauss-Kruger zone 37",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=37500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2362, "epsg", 2362, "Xian 1980 / 3-degree Gauss-Kruger zone 38",
        "+proj=tmerc +lat_0=0 +lon_0=114 +k=1 +x_0=38500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2363, "epsg", 2363, "Xian 1980 / 3-degree Gauss-Kruger zone 39",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=39500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2364, "epsg", 2364, "Xian 1980 / 3-degree Gauss-Kruger zone 40",
        "+proj=tmerc +lat_0=0 +lon_0=120 +k=1 +x_0=40500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2365, "epsg", 2365, "Xian 1980 / 3-degree Gauss-Kruger zone 41",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=41500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2366, "epsg", 2366, "Xian 1980 / 3-degree Gauss-Kruger zone 42",
        "+proj=tmerc +lat_0=0 +lon_0=126 +k=1 +x_0=42500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2367, "epsg", 2367, "Xian 1980 / 3-degree Gauss-Kruger zone 43",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=43500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2368, "epsg", 2368, "Xian 1980 / 3-degree Gauss-Kruger zone 44",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=1 +x_0=44500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2369, "epsg", 2369, "Xian 1980 / 3-degree Gauss-Kruger zone 45",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=45500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2370, "epsg", 2370, "Xian 1980 / 3-degree Gauss-Kruger CM 75E",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2371, "epsg", 2371, "Xian 1980 / 3-degree Gauss-Kruger CM 78E",
        "+proj=tmerc +lat_0=0 +lon_0=78 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2372, "epsg", 2372, "Xian 1980 / 3-degree Gauss-Kruger CM 81E",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2373, "epsg", 2373, "Xian 1980 / 3-degree Gauss-Kruger CM 84E",
        "+proj=tmerc +lat_0=0 +lon_0=84 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2374, "epsg", 2374, "Xian 1980 / 3-degree Gauss-Kruger CM 87E",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2375, "epsg", 2375, "Xian 1980 / 3-degree Gauss-Kruger CM 90E",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2376, "epsg", 2376, "Xian 1980 / 3-degree Gauss-Kruger CM 93E",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2377, "epsg", 2377, "Xian 1980 / 3-degree Gauss-Kruger CM 96E",
        "+proj=tmerc +lat_0=0 +lon_0=96 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2378, "epsg", 2378, "Xian 1980 / 3-degree Gauss-Kruger CM 99E",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2379, "epsg", 2379, "Xian 1980 / 3-degree Gauss-Kruger CM 102E",
        "+proj=tmerc +lat_0=0 +lon_0=102 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2380, "epsg", 2380, "Xian 1980 / 3-degree Gauss-Kruger CM 105E",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2381, "epsg", 2381, "Xian 1980 / 3-degree Gauss-Kruger CM 108E",
        "+proj=tmerc +lat_0=0 +lon_0=108 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2382, "epsg", 2382, "Xian 1980 / 3-degree Gauss-Kruger CM 111E",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2383, "epsg", 2383, "Xian 1980 / 3-degree Gauss-Kruger CM 114E",
        "+proj=tmerc +lat_0=0 +lon_0=114 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2384, "epsg", 2384, "Xian 1980 / 3-degree Gauss-Kruger CM 117E",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2385, "epsg", 2385, "Xian 1980 / 3-degree Gauss-Kruger CM 120E",
        "+proj=tmerc +lat_0=0 +lon_0=120 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2386, "epsg", 2386, "Xian 1980 / 3-degree Gauss-Kruger CM 123E",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2387, "epsg", 2387, "Xian 1980 / 3-degree Gauss-Kruger CM 126E",
        "+proj=tmerc +lat_0=0 +lon_0=126 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2388, "epsg", 2388, "Xian 1980 / 3-degree Gauss-Kruger CM 129E",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2389, "epsg", 2389, "Xian 1980 / 3-degree Gauss-Kruger CM 132E",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2390, "epsg", 2390, "Xian 1980 / 3-degree Gauss-Kruger CM 135E",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +a=6378140 +b=6356755.288157528 +units=m +no_defs"},
    {
    2391, "epsg", 2391, "KKJ / Finland zone 1",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=1500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2392, "epsg", 2392, "KKJ / Finland zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=1 +x_0=2500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2393, "epsg", 2393, "KKJ / Finland Uniform Coordinate System",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=3500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2394, "epsg", 2394, "KKJ / Finland zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=4500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    2395, "epsg", 2395, "South Yemen / Gauss-Kruger zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=8500000 +y_0=0 +ellps=krass +towgs84=-76,-138,67,0,0,0,0 +units=m +no_defs"},
    {
    2396, "epsg", 2396, "South Yemen / Gauss-Kruger zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=9500000 +y_0=0 +ellps=krass +towgs84=-76,-138,67,0,0,0,0 +units=m +no_defs"},
    {
    2397, "epsg", 2397, "Pulkovo 1942(83) / 3-degree Gauss-Kruger zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=3500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2398, "epsg", 2398, "Pulkovo 1942(83) / 3-degree Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2399, "epsg", 2399, "Pulkovo 1942(83) / 3-degree Gauss-Kruger zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=5500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2400, "epsg", 2400, "RT90 2.5 gon W (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15.80827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    2401, "epsg", 2401, "Beijing 1954 / 3-degree Gauss-Kruger zone 25",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=25500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2402, "epsg", 2402, "Beijing 1954 / 3-degree Gauss-Kruger zone 26",
        "+proj=tmerc +lat_0=0 +lon_0=78 +k=1 +x_0=26500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2403, "epsg", 2403, "Beijing 1954 / 3-degree Gauss-Kruger zone 27",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=27500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2404, "epsg", 2404, "Beijing 1954 / 3-degree Gauss-Kruger zone 28",
        "+proj=tmerc +lat_0=0 +lon_0=84 +k=1 +x_0=28500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2405, "epsg", 2405, "Beijing 1954 / 3-degree Gauss-Kruger zone 29",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=29500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2406, "epsg", 2406, "Beijing 1954 / 3-degree Gauss-Kruger zone 30",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=1 +x_0=30500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2407, "epsg", 2407, "Beijing 1954 / 3-degree Gauss-Kruger zone 31",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=31500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2408, "epsg", 2408, "Beijing 1954 / 3-degree Gauss-Kruger zone 32",
        "+proj=tmerc +lat_0=0 +lon_0=96 +k=1 +x_0=32500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2409, "epsg", 2409, "Beijing 1954 / 3-degree Gauss-Kruger zone 33",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=33500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2410, "epsg", 2410, "Beijing 1954 / 3-degree Gauss-Kruger zone 34",
        "+proj=tmerc +lat_0=0 +lon_0=102 +k=1 +x_0=34500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2411, "epsg", 2411, "Beijing 1954 / 3-degree Gauss-Kruger zone 35",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=35500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2412, "epsg", 2412, "Beijing 1954 / 3-degree Gauss-Kruger zone 36",
        "+proj=tmerc +lat_0=0 +lon_0=108 +k=1 +x_0=36500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2413, "epsg", 2413, "Beijing 1954 / 3-degree Gauss-Kruger zone 37",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=37500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2414, "epsg", 2414, "Beijing 1954 / 3-degree Gauss-Kruger zone 38",
        "+proj=tmerc +lat_0=0 +lon_0=114 +k=1 +x_0=38500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2415, "epsg", 2415, "Beijing 1954 / 3-degree Gauss-Kruger zone 39",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=39500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2416, "epsg", 2416, "Beijing 1954 / 3-degree Gauss-Kruger zone 40",
        "+proj=tmerc +lat_0=0 +lon_0=120 +k=1 +x_0=40500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2417, "epsg", 2417, "Beijing 1954 / 3-degree Gauss-Kruger zone 41",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=41500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2418, "epsg", 2418, "Beijing 1954 / 3-degree Gauss-Kruger zone 42",
        "+proj=tmerc +lat_0=0 +lon_0=126 +k=1 +x_0=42500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2419, "epsg", 2419, "Beijing 1954 / 3-degree Gauss-Kruger zone 43",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=43500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2420, "epsg", 2420, "Beijing 1954 / 3-degree Gauss-Kruger zone 44",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=1 +x_0=44500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2421, "epsg", 2421, "Beijing 1954 / 3-degree Gauss-Kruger zone 45",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=45500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2422, "epsg", 2422, "Beijing 1954 / 3-degree Gauss-Kruger CM 75E",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2423, "epsg", 2423, "Beijing 1954 / 3-degree Gauss-Kruger CM 78E",
        "+proj=tmerc +lat_0=0 +lon_0=78 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2424, "epsg", 2424, "Beijing 1954 / 3-degree Gauss-Kruger CM 81E",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2425, "epsg", 2425, "Beijing 1954 / 3-degree Gauss-Kruger CM 84E",
        "+proj=tmerc +lat_0=0 +lon_0=84 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2426, "epsg", 2426, "Beijing 1954 / 3-degree Gauss-Kruger CM 87E",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2427, "epsg", 2427, "Beijing 1954 / 3-degree Gauss-Kruger CM 90E",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2428, "epsg", 2428, "Beijing 1954 / 3-degree Gauss-Kruger CM 93E",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2429, "epsg", 2429, "Beijing 1954 / 3-degree Gauss-Kruger CM 96E",
        "+proj=tmerc +lat_0=0 +lon_0=96 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2430, "epsg", 2430, "Beijing 1954 / 3-degree Gauss-Kruger CM 99E",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2431, "epsg", 2431, "Beijing 1954 / 3-degree Gauss-Kruger CM 102E",
        "+proj=tmerc +lat_0=0 +lon_0=102 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2432, "epsg", 2432, "Beijing 1954 / 3-degree Gauss-Kruger CM 105E",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2433, "epsg", 2433, "Beijing 1954 / 3-degree Gauss-Kruger CM 108E",
        "+proj=tmerc +lat_0=0 +lon_0=108 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2434, "epsg", 2434, "Beijing 1954 / 3-degree Gauss-Kruger CM 111E",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2435, "epsg", 2435, "Beijing 1954 / 3-degree Gauss-Kruger CM 114E",
        "+proj=tmerc +lat_0=0 +lon_0=114 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2436, "epsg", 2436, "Beijing 1954 / 3-degree Gauss-Kruger CM 117E",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2437, "epsg", 2437, "Beijing 1954 / 3-degree Gauss-Kruger CM 120E",
        "+proj=tmerc +lat_0=0 +lon_0=120 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2438, "epsg", 2438, "Beijing 1954 / 3-degree Gauss-Kruger CM 123E",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2439, "epsg", 2439, "Beijing 1954 / 3-degree Gauss-Kruger CM 126E",
        "+proj=tmerc +lat_0=0 +lon_0=126 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2440, "epsg", 2440, "Beijing 1954 / 3-degree Gauss-Kruger CM 129E",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2441, "epsg", 2441, "Beijing 1954 / 3-degree Gauss-Kruger CM 132E",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2442, "epsg", 2442, "Beijing 1954 / 3-degree Gauss-Kruger CM 135E",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2443, "epsg", 2443, "JGD2000 / Japan Plane Rectangular CS I",
        "+proj=tmerc +lat_0=33 +lon_0=129.5 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2444, "epsg", 2444, "JGD2000 / Japan Plane Rectangular CS II",
        "+proj=tmerc +lat_0=33 +lon_0=131 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2445, "epsg", 2445, "JGD2000 / Japan Plane Rectangular CS III",
        "+proj=tmerc +lat_0=36 +lon_0=132.1666666666667 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2446, "epsg", 2446, "JGD2000 / Japan Plane Rectangular CS IV",
        "+proj=tmerc +lat_0=33 +lon_0=133.5 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2447, "epsg", 2447, "JGD2000 / Japan Plane Rectangular CS V",
        "+proj=tmerc +lat_0=36 +lon_0=134.3333333333333 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2448, "epsg", 2448, "JGD2000 / Japan Plane Rectangular CS VI",
        "+proj=tmerc +lat_0=36 +lon_0=136 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2449, "epsg", 2449, "JGD2000 / Japan Plane Rectangular CS VII",
        "+proj=tmerc +lat_0=36 +lon_0=137.1666666666667 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2450, "epsg", 2450, "JGD2000 / Japan Plane Rectangular CS VIII",
        "+proj=tmerc +lat_0=36 +lon_0=138.5 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2451, "epsg", 2451, "JGD2000 / Japan Plane Rectangular CS IX",
        "+proj=tmerc +lat_0=36 +lon_0=139.8333333333333 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2452, "epsg", 2452, "JGD2000 / Japan Plane Rectangular CS X",
        "+proj=tmerc +lat_0=40 +lon_0=140.8333333333333 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2453, "epsg", 2453, "JGD2000 / Japan Plane Rectangular CS XI",
        "+proj=tmerc +lat_0=44 +lon_0=140.25 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2454, "epsg", 2454, "JGD2000 / Japan Plane Rectangular CS XII",
        "+proj=tmerc +lat_0=44 +lon_0=142.25 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2455, "epsg", 2455, "JGD2000 / Japan Plane Rectangular CS XIII",
        "+proj=tmerc +lat_0=44 +lon_0=144.25 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2456, "epsg", 2456, "JGD2000 / Japan Plane Rectangular CS XIV",
        "+proj=tmerc +lat_0=26 +lon_0=142 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2457, "epsg", 2457, "JGD2000 / Japan Plane Rectangular CS XV",
        "+proj=tmerc +lat_0=26 +lon_0=127.5 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2458, "epsg", 2458, "JGD2000 / Japan Plane Rectangular CS XVI",
        "+proj=tmerc +lat_0=26 +lon_0=124 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2459, "epsg", 2459, "JGD2000 / Japan Plane Rectangular CS XVII",
        "+proj=tmerc +lat_0=26 +lon_0=131 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2460, "epsg", 2460, "JGD2000 / Japan Plane Rectangular CS XVIII",
        "+proj=tmerc +lat_0=20 +lon_0=136 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2461, "epsg", 2461, "JGD2000 / Japan Plane Rectangular CS XIX",
        "+proj=tmerc +lat_0=26 +lon_0=154 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2462, "epsg", 2462, "Albanian 1987 / Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2463, "epsg", 2463, "Pulkovo 1995 / Gauss-Kruger CM 21E",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2464, "epsg", 2464, "Pulkovo 1995 / Gauss-Kruger CM 27E",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2465, "epsg", 2465, "Pulkovo 1995 / Gauss-Kruger CM 33E",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2466, "epsg", 2466, "Pulkovo 1995 / Gauss-Kruger CM 39E",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2467, "epsg", 2467, "Pulkovo 1995 / Gauss-Kruger CM 45E",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2468, "epsg", 2468, "Pulkovo 1995 / Gauss-Kruger CM 51E",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2469, "epsg", 2469, "Pulkovo 1995 / Gauss-Kruger CM 57E",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2470, "epsg", 2470, "Pulkovo 1995 / Gauss-Kruger CM 63E",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2471, "epsg", 2471, "Pulkovo 1995 / Gauss-Kruger CM 69E",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2472, "epsg", 2472, "Pulkovo 1995 / Gauss-Kruger CM 75E",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2473, "epsg", 2473, "Pulkovo 1995 / Gauss-Kruger CM 81E",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2474, "epsg", 2474, "Pulkovo 1995 / Gauss-Kruger CM 87E",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2475, "epsg", 2475, "Pulkovo 1995 / Gauss-Kruger CM 93E",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2476, "epsg", 2476, "Pulkovo 1995 / Gauss-Kruger CM 99E",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2477, "epsg", 2477, "Pulkovo 1995 / Gauss-Kruger CM 105E",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2478, "epsg", 2478, "Pulkovo 1995 / Gauss-Kruger CM 111E",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2479, "epsg", 2479, "Pulkovo 1995 / Gauss-Kruger CM 117E",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2480, "epsg", 2480, "Pulkovo 1995 / Gauss-Kruger CM 123E",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2481, "epsg", 2481, "Pulkovo 1995 / Gauss-Kruger CM 129E",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2482, "epsg", 2482, "Pulkovo 1995 / Gauss-Kruger CM 135E",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2483, "epsg", 2483, "Pulkovo 1995 / Gauss-Kruger CM 141E",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2484, "epsg", 2484, "Pulkovo 1995 / Gauss-Kruger CM 147E",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2485, "epsg", 2485, "Pulkovo 1995 / Gauss-Kruger CM 153E",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2486, "epsg", 2486, "Pulkovo 1995 / Gauss-Kruger CM 159E",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2487, "epsg", 2487, "Pulkovo 1995 / Gauss-Kruger CM 165E",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2488, "epsg", 2488, "Pulkovo 1995 / Gauss-Kruger CM 171E",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2489, "epsg", 2489, "Pulkovo 1995 / Gauss-Kruger CM 177E",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2490, "epsg", 2490, "Pulkovo 1995 / Gauss-Kruger CM 177W",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2491, "epsg", 2491, "Pulkovo 1995 / Gauss-Kruger CM 171W",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2492, "epsg", 2492, "Pulkovo 1942 / Gauss-Kruger CM 9E (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2493, "epsg", 2493, "Pulkovo 1942 / Gauss-Kruger CM 15E (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2494, "epsg", 2494, "Pulkovo 1942 / Gauss-Kruger CM 21E",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2495, "epsg", 2495, "Pulkovo 1942 / Gauss-Kruger CM 27E",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2496, "epsg", 2496, "Pulkovo 1942 / Gauss-Kruger CM 33E",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2497, "epsg", 2497, "Pulkovo 1942 / Gauss-Kruger CM 39E",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2498, "epsg", 2498, "Pulkovo 1942 / Gauss-Kruger CM 45E",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2499, "epsg", 2499, "Pulkovo 1942 / Gauss-Kruger CM 51E",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2500, "epsg", 2500, "Pulkovo 1942 / Gauss-Kruger CM 57E",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2501, "epsg", 2501, "Pulkovo 1942 / Gauss-Kruger CM 63E",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2502, "epsg", 2502, "Pulkovo 1942 / Gauss-Kruger CM 69E",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2503, "epsg", 2503, "Pulkovo 1942 / Gauss-Kruger CM 75E",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2504, "epsg", 2504, "Pulkovo 1942 / Gauss-Kruger CM 81E",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2505, "epsg", 2505, "Pulkovo 1942 / Gauss-Kruger CM 87E",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2506, "epsg", 2506, "Pulkovo 1942 / Gauss-Kruger CM 93E",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2507, "epsg", 2507, "Pulkovo 1942 / Gauss-Kruger CM 99E",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2508, "epsg", 2508, "Pulkovo 1942 / Gauss-Kruger CM 105E",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2509, "epsg", 2509, "Pulkovo 1942 / Gauss-Kruger CM 111E",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2510, "epsg", 2510, "Pulkovo 1942 / Gauss-Kruger CM 117E",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2511, "epsg", 2511, "Pulkovo 1942 / Gauss-Kruger CM 123E",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2512, "epsg", 2512, "Pulkovo 1942 / Gauss-Kruger CM 129E",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2513, "epsg", 2513, "Pulkovo 1942 / Gauss-Kruger CM 135E",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2514, "epsg", 2514, "Pulkovo 1942 / Gauss-Kruger CM 141E",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2515, "epsg", 2515, "Pulkovo 1942 / Gauss-Kruger CM 147E",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2516, "epsg", 2516, "Pulkovo 1942 / Gauss-Kruger CM 153E",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2517, "epsg", 2517, "Pulkovo 1942 / Gauss-Kruger CM 159E",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2518, "epsg", 2518, "Pulkovo 1942 / Gauss-Kruger CM 165E",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2519, "epsg", 2519, "Pulkovo 1942 / Gauss-Kruger CM 171E",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2520, "epsg", 2520, "Pulkovo 1942 / Gauss-Kruger CM 177E",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2521, "epsg", 2521, "Pulkovo 1942 / Gauss-Kruger CM 177W",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2522, "epsg", 2522, "Pulkovo 1942 / Gauss-Kruger CM 171W",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2523, "epsg", 2523, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=7500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2524, "epsg", 2524, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=1 +x_0=8500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2525, "epsg", 2525, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=9500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2526, "epsg", 2526, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=10500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2527, "epsg", 2527, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=11500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2528, "epsg", 2528, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=36 +k=1 +x_0=12500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2529, "epsg", 2529, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=13500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2530, "epsg", 2530, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=42 +k=1 +x_0=14500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2531, "epsg", 2531, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=15500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2532, "epsg", 2532, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=48 +k=1 +x_0=16500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2533, "epsg", 2533, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=17500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2534, "epsg", 2534, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=54 +k=1 +x_0=18500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2535, "epsg", 2535, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 19",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=19500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2536, "epsg", 2536, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 20",
        "+proj=tmerc +lat_0=0 +lon_0=60 +k=1 +x_0=20500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2537, "epsg", 2537, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 21",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=21500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2538, "epsg", 2538, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=66 +k=1 +x_0=22500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2539, "epsg", 2539, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 23",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=23500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2540, "epsg", 2540, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 24",
        "+proj=tmerc +lat_0=0 +lon_0=72 +k=1 +x_0=24500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2541, "epsg", 2541, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 25",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=25500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2542, "epsg", 2542, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 26",
        "+proj=tmerc +lat_0=0 +lon_0=78 +k=1 +x_0=26500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2543, "epsg", 2543, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 27",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=27500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2544, "epsg", 2544, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 28",
        "+proj=tmerc +lat_0=0 +lon_0=84 +k=1 +x_0=28500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2545, "epsg", 2545, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 29",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=29500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2546, "epsg", 2546, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 30",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=1 +x_0=30500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2547, "epsg", 2547, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 31",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=31500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2548, "epsg", 2548, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 32",
        "+proj=tmerc +lat_0=0 +lon_0=96 +k=1 +x_0=32500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2549, "epsg", 2549, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 33",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=33500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2550, "epsg", 2550, "Samboja / UTM zone 50S (deprecated)",
        "+proj=utm +zone=50 +south +ellps=bessel +towgs84=-404.78,685.68,45.47,0,0,0,0 +units=m +no_defs"},
    {
    2551, "epsg", 2551, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 34",
        "+proj=tmerc +lat_0=0 +lon_0=102 +k=1 +x_0=34500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2552, "epsg", 2552, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 35",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=35500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2553, "epsg", 2553, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 36",
        "+proj=tmerc +lat_0=0 +lon_0=108 +k=1 +x_0=36500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2554, "epsg", 2554, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 37",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=37500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2555, "epsg", 2555, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 38",
        "+proj=tmerc +lat_0=0 +lon_0=114 +k=1 +x_0=38500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2556, "epsg", 2556, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 39",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=39500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2557, "epsg", 2557, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 40",
        "+proj=tmerc +lat_0=0 +lon_0=120 +k=1 +x_0=40500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2558, "epsg", 2558, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 41",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=41500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2559, "epsg", 2559, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 42",
        "+proj=tmerc +lat_0=0 +lon_0=126 +k=1 +x_0=42500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2560, "epsg", 2560, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 43",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=43500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2561, "epsg", 2561, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 44",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=1 +x_0=44500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2562, "epsg", 2562, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 45",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=45500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2563, "epsg", 2563, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 46",
        "+proj=tmerc +lat_0=0 +lon_0=138 +k=1 +x_0=46500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2564, "epsg", 2564, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 47",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=47500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2565, "epsg", 2565, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 48",
        "+proj=tmerc +lat_0=0 +lon_0=144 +k=1 +x_0=48500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2566, "epsg", 2566, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 49",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=49500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2567, "epsg", 2567, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 50",
        "+proj=tmerc +lat_0=0 +lon_0=150 +k=1 +x_0=50500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2568, "epsg", 2568, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 51",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=51500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2569, "epsg", 2569, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 52",
        "+proj=tmerc +lat_0=0 +lon_0=156 +k=1 +x_0=52500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2570, "epsg", 2570, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 53",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=53500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2571, "epsg", 2571, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 54",
        "+proj=tmerc +lat_0=0 +lon_0=162 +k=1 +x_0=54500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2572, "epsg", 2572, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 55",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=55500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2573, "epsg", 2573, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 56",
        "+proj=tmerc +lat_0=0 +lon_0=168 +k=1 +x_0=56500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2574, "epsg", 2574, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 57",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=57500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2575, "epsg", 2575, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 58",
        "+proj=tmerc +lat_0=0 +lon_0=174 +k=1 +x_0=58500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2576, "epsg", 2576, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 59",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=59500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2577, "epsg", 2577,
        "Pulkovo 1942 / 3-degree Gauss-Kruger zone 60 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=180 +k=1 +x_0=60000000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2578, "epsg", 2578, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 61",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=61500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2579, "epsg", 2579, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 62",
        "+proj=tmerc +lat_0=0 +lon_0=-174 +k=1 +x_0=62500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2580, "epsg", 2580, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 63",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=63500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2581, "epsg", 2581, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 64",
        "+proj=tmerc +lat_0=0 +lon_0=-168 +k=1 +x_0=64500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2582, "epsg", 2582, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 21E",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2583, "epsg", 2583, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 24E",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2584, "epsg", 2584, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 27E",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2585, "epsg", 2585, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 30E",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2586, "epsg", 2586, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 33E",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2587, "epsg", 2587, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 36E",
        "+proj=tmerc +lat_0=0 +lon_0=36 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2588, "epsg", 2588, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 39E",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2589, "epsg", 2589, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 42E",
        "+proj=tmerc +lat_0=0 +lon_0=42 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2590, "epsg", 2590, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 45E",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2591, "epsg", 2591, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 48E",
        "+proj=tmerc +lat_0=0 +lon_0=48 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2592, "epsg", 2592, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 51E",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2593, "epsg", 2593, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 54E",
        "+proj=tmerc +lat_0=0 +lon_0=54 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2594, "epsg", 2594, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 57E",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2595, "epsg", 2595, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 60E",
        "+proj=tmerc +lat_0=0 +lon_0=60 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2596, "epsg", 2596, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 63E",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2597, "epsg", 2597, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 66E",
        "+proj=tmerc +lat_0=0 +lon_0=66 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2598, "epsg", 2598, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 69E",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2599, "epsg", 2599, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 72E",
        "+proj=tmerc +lat_0=0 +lon_0=72 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2600, "epsg", 2600, "Lietuvos Koordinoei Sistema 1994 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9998 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2601, "epsg", 2601, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 75E",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2602, "epsg", 2602, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 78E",
        "+proj=tmerc +lat_0=0 +lon_0=78 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2603, "epsg", 2603, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 81E",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2604, "epsg", 2604, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 84E",
        "+proj=tmerc +lat_0=0 +lon_0=84 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2605, "epsg", 2605, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 87E",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2606, "epsg", 2606, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 90E",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2607, "epsg", 2607, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 93E",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2608, "epsg", 2608, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 96E",
        "+proj=tmerc +lat_0=0 +lon_0=96 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2609, "epsg", 2609, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 99E",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2610, "epsg", 2610, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 102E",
        "+proj=tmerc +lat_0=0 +lon_0=102 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2611, "epsg", 2611, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 105E",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2612, "epsg", 2612, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 108E",
        "+proj=tmerc +lat_0=0 +lon_0=108 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2613, "epsg", 2613, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 111E",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2614, "epsg", 2614, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 114E",
        "+proj=tmerc +lat_0=0 +lon_0=114 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2615, "epsg", 2615, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 117E",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2616, "epsg", 2616, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 120E",
        "+proj=tmerc +lat_0=0 +lon_0=120 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2617, "epsg", 2617, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 123E",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2618, "epsg", 2618, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 126E",
        "+proj=tmerc +lat_0=0 +lon_0=126 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2619, "epsg", 2619, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 129E",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2620, "epsg", 2620, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 132E",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2621, "epsg", 2621, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 135E",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2622, "epsg", 2622, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 138E",
        "+proj=tmerc +lat_0=0 +lon_0=138 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2623, "epsg", 2623, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 141E",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2624, "epsg", 2624, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 144E",
        "+proj=tmerc +lat_0=0 +lon_0=144 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2625, "epsg", 2625, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 147E",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2626, "epsg", 2626, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 150E",
        "+proj=tmerc +lat_0=0 +lon_0=150 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2627, "epsg", 2627, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 153E",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2628, "epsg", 2628, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 156E",
        "+proj=tmerc +lat_0=0 +lon_0=156 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2629, "epsg", 2629, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 159E",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2630, "epsg", 2630, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 162E",
        "+proj=tmerc +lat_0=0 +lon_0=162 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2631, "epsg", 2631, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 165E",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2632, "epsg", 2632, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 168E",
        "+proj=tmerc +lat_0=0 +lon_0=168 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2633, "epsg", 2633, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 171E",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2634, "epsg", 2634, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 174E",
        "+proj=tmerc +lat_0=0 +lon_0=174 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2635, "epsg", 2635, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 177E",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2636, "epsg", 2636, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 180E",
        "+proj=tmerc +lat_0=0 +lon_0=180 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2637, "epsg", 2637, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 177W",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2638, "epsg", 2638, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 174W",
        "+proj=tmerc +lat_0=0 +lon_0=-174 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2639, "epsg", 2639, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 171W",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2640, "epsg", 2640, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 168W",
        "+proj=tmerc +lat_0=0 +lon_0=-168 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2641, "epsg", 2641, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=7500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2642, "epsg", 2642, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=1 +x_0=8500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2643, "epsg", 2643, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=9500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2644, "epsg", 2644, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=10500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2645, "epsg", 2645, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=11500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2646, "epsg", 2646, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=36 +k=1 +x_0=12500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2647, "epsg", 2647, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=13500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2648, "epsg", 2648, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=42 +k=1 +x_0=14500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2649, "epsg", 2649, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=15500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2650, "epsg", 2650, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=48 +k=1 +x_0=16500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2651, "epsg", 2651, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=17500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2652, "epsg", 2652, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=54 +k=1 +x_0=18500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2653, "epsg", 2653, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 19",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=19500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2654, "epsg", 2654, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 20",
        "+proj=tmerc +lat_0=0 +lon_0=60 +k=1 +x_0=20500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2655, "epsg", 2655, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 21",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=21500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2656, "epsg", 2656, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=66 +k=1 +x_0=22500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2657, "epsg", 2657, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 23",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=23500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2658, "epsg", 2658, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 24",
        "+proj=tmerc +lat_0=0 +lon_0=72 +k=1 +x_0=24500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2659, "epsg", 2659, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 25",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=25500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2660, "epsg", 2660, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 26",
        "+proj=tmerc +lat_0=0 +lon_0=78 +k=1 +x_0=26500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2661, "epsg", 2661, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 27",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=27500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2662, "epsg", 2662, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 28",
        "+proj=tmerc +lat_0=0 +lon_0=84 +k=1 +x_0=28500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2663, "epsg", 2663, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 29",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=29500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2664, "epsg", 2664, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 30",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=1 +x_0=30500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2665, "epsg", 2665, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 31",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=31500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2666, "epsg", 2666, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 32",
        "+proj=tmerc +lat_0=0 +lon_0=96 +k=1 +x_0=32500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2667, "epsg", 2667, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 33",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=33500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2668, "epsg", 2668, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 34",
        "+proj=tmerc +lat_0=0 +lon_0=102 +k=1 +x_0=34500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2669, "epsg", 2669, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 35",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=35500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2670, "epsg", 2670, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 36",
        "+proj=tmerc +lat_0=0 +lon_0=108 +k=1 +x_0=36500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2671, "epsg", 2671, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 37",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=37500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2672, "epsg", 2672, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 38",
        "+proj=tmerc +lat_0=0 +lon_0=114 +k=1 +x_0=38500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2673, "epsg", 2673, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 39",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=39500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2674, "epsg", 2674, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 40",
        "+proj=tmerc +lat_0=0 +lon_0=120 +k=1 +x_0=40500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2675, "epsg", 2675, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 41",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=41500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2676, "epsg", 2676, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 42",
        "+proj=tmerc +lat_0=0 +lon_0=126 +k=1 +x_0=42500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2677, "epsg", 2677, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 43",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=43500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2678, "epsg", 2678, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 44",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=1 +x_0=44500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2679, "epsg", 2679, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 45",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=45500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2680, "epsg", 2680, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 46",
        "+proj=tmerc +lat_0=0 +lon_0=138 +k=1 +x_0=46500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2681, "epsg", 2681, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 47",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=47500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2682, "epsg", 2682, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 48",
        "+proj=tmerc +lat_0=0 +lon_0=144 +k=1 +x_0=48500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2683, "epsg", 2683, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 49",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=49500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2684, "epsg", 2684, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 50",
        "+proj=tmerc +lat_0=0 +lon_0=150 +k=1 +x_0=50500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2685, "epsg", 2685, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 51",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=51500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2686, "epsg", 2686, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 52",
        "+proj=tmerc +lat_0=0 +lon_0=156 +k=1 +x_0=52500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2687, "epsg", 2687, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 53",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=53500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2688, "epsg", 2688, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 54",
        "+proj=tmerc +lat_0=0 +lon_0=162 +k=1 +x_0=54500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2689, "epsg", 2689, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 55",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=55500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2690, "epsg", 2690, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 56",
        "+proj=tmerc +lat_0=0 +lon_0=168 +k=1 +x_0=56500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2691, "epsg", 2691, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 57",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=57500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2692, "epsg", 2692, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 58",
        "+proj=tmerc +lat_0=0 +lon_0=174 +k=1 +x_0=58500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2693, "epsg", 2693, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 59",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=59500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2694, "epsg", 2694,
        "Pulkovo 1995 / 3-degree Gauss-Kruger zone 60 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=180 +k=1 +x_0=60000000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2695, "epsg", 2695, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 61",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=61500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2696, "epsg", 2696, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 62",
        "+proj=tmerc +lat_0=0 +lon_0=-174 +k=1 +x_0=62500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2697, "epsg", 2697, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 63",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=63500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2698, "epsg", 2698, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 64",
        "+proj=tmerc +lat_0=0 +lon_0=-168 +k=1 +x_0=64500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2699, "epsg", 2699, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 21E",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2700, "epsg", 2700, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 24E",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2701, "epsg", 2701, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 27E",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2702, "epsg", 2702, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 30E",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2703, "epsg", 2703, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 33E",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2704, "epsg", 2704, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 36E",
        "+proj=tmerc +lat_0=0 +lon_0=36 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2705, "epsg", 2705, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 39E",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2706, "epsg", 2706, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 42E",
        "+proj=tmerc +lat_0=0 +lon_0=42 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2707, "epsg", 2707, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 45E",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2708, "epsg", 2708, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 48E",
        "+proj=tmerc +lat_0=0 +lon_0=48 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2709, "epsg", 2709, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 51E",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2710, "epsg", 2710, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 54E",
        "+proj=tmerc +lat_0=0 +lon_0=54 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2711, "epsg", 2711, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 57E",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2712, "epsg", 2712, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 60E",
        "+proj=tmerc +lat_0=0 +lon_0=60 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2713, "epsg", 2713, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 63E",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2714, "epsg", 2714, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 66E",
        "+proj=tmerc +lat_0=0 +lon_0=66 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2715, "epsg", 2715, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 69E",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2716, "epsg", 2716, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 72E",
        "+proj=tmerc +lat_0=0 +lon_0=72 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2717, "epsg", 2717, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 75E",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2718, "epsg", 2718, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 78E",
        "+proj=tmerc +lat_0=0 +lon_0=78 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2719, "epsg", 2719, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 81E",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2720, "epsg", 2720, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 84E",
        "+proj=tmerc +lat_0=0 +lon_0=84 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2721, "epsg", 2721, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 87E",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2722, "epsg", 2722, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 90E",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2723, "epsg", 2723, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 93E",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2724, "epsg", 2724, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 96E",
        "+proj=tmerc +lat_0=0 +lon_0=96 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2725, "epsg", 2725, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 99E",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2726, "epsg", 2726, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 102E",
        "+proj=tmerc +lat_0=0 +lon_0=102 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2727, "epsg", 2727, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 105E",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2728, "epsg", 2728, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 108E",
        "+proj=tmerc +lat_0=0 +lon_0=108 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2729, "epsg", 2729, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 111E",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2730, "epsg", 2730, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 114E",
        "+proj=tmerc +lat_0=0 +lon_0=114 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2731, "epsg", 2731, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 117E",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2732, "epsg", 2732, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 120E",
        "+proj=tmerc +lat_0=0 +lon_0=120 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2733, "epsg", 2733, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 123E",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2734, "epsg", 2734, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 126E",
        "+proj=tmerc +lat_0=0 +lon_0=126 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2735, "epsg", 2735, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 129E",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2736, "epsg", 2736, "Tete / UTM zone 36S",
        "+proj=utm +zone=36 +south +ellps=clrk66 +units=m +no_defs"},
    {
    2737, "epsg", 2737, "Tete / UTM zone 37S",
        "+proj=utm +zone=37 +south +ellps=clrk66 +units=m +no_defs"},
    {
    2738, "epsg", 2738, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 132E",
        "+proj=tmerc +lat_0=0 +lon_0=132 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2739, "epsg", 2739, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 135E",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2740, "epsg", 2740, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 138E",
        "+proj=tmerc +lat_0=0 +lon_0=138 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2741, "epsg", 2741, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 141E",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2742, "epsg", 2742, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 144E",
        "+proj=tmerc +lat_0=0 +lon_0=144 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2743, "epsg", 2743, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 147E",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2744, "epsg", 2744, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 150E",
        "+proj=tmerc +lat_0=0 +lon_0=150 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2745, "epsg", 2745, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 153E",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2746, "epsg", 2746, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 156E",
        "+proj=tmerc +lat_0=0 +lon_0=156 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2747, "epsg", 2747, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 159E",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2748, "epsg", 2748, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 162E",
        "+proj=tmerc +lat_0=0 +lon_0=162 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2749, "epsg", 2749, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 165E",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2750, "epsg", 2750, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 168E",
        "+proj=tmerc +lat_0=0 +lon_0=168 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2751, "epsg", 2751, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 171E",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2752, "epsg", 2752, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 174E",
        "+proj=tmerc +lat_0=0 +lon_0=174 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2753, "epsg", 2753, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 177E",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2754, "epsg", 2754, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 180E",
        "+proj=tmerc +lat_0=0 +lon_0=180 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2755, "epsg", 2755, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 177W",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2756, "epsg", 2756, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 174W",
        "+proj=tmerc +lat_0=0 +lon_0=-174 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2757, "epsg", 2757, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 171W",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2758, "epsg", 2758, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 168W",
        "+proj=tmerc +lat_0=0 +lon_0=-168 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    2759, "epsg", 2759, "NAD83(HARN) / Alabama East",
        "+proj=tmerc +lat_0=30.5 +lon_0=-85.83333333333333 +k=0.99996 +x_0=200000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2760, "epsg", 2760, "NAD83(HARN) / Alabama West",
        "+proj=tmerc +lat_0=30 +lon_0=-87.5 +k=0.999933333 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2761, "epsg", 2761, "NAD83(HARN) / Arizona East",
        "+proj=tmerc +lat_0=31 +lon_0=-110.1666666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2762, "epsg", 2762, "NAD83(HARN) / Arizona Central",
        "+proj=tmerc +lat_0=31 +lon_0=-111.9166666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2763, "epsg", 2763, "NAD83(HARN) / Arizona West",
        "+proj=tmerc +lat_0=31 +lon_0=-113.75 +k=0.999933333 +x_0=213360 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2764, "epsg", 2764, "NAD83(HARN) / Arkansas North",
        "+proj=lcc +lat_1=36.23333333333333 +lat_2=34.93333333333333 +lat_0=34.33333333333334 +lon_0=-92 +x_0=400000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2765, "epsg", 2765, "NAD83(HARN) / Arkansas South",
        "+proj=lcc +lat_1=34.76666666666667 +lat_2=33.3 +lat_0=32.66666666666666 +lon_0=-92 +x_0=400000 +y_0=400000 +ellps=GRS80 +units=m +no_defs"},
    {
    2766, "epsg", 2766, "NAD83(HARN) / California zone 1",
        "+proj=lcc +lat_1=41.66666666666666 +lat_2=40 +lat_0=39.33333333333334 +lon_0=-122 +x_0=2000000 +y_0=500000 +ellps=GRS80 +units=m +no_defs"},
    {
    2767, "epsg", 2767, "NAD83(HARN) / California zone 2",
        "+proj=lcc +lat_1=39.83333333333334 +lat_2=38.33333333333334 +lat_0=37.66666666666666 +lon_0=-122 +x_0=2000000 +y_0=500000 +ellps=GRS80 +units=m +no_defs"},
    {
    2768, "epsg", 2768, "NAD83(HARN) / California zone 3",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.06666666666667 +lat_0=36.5 +lon_0=-120.5 +x_0=2000000 +y_0=500000 +ellps=GRS80 +units=m +no_defs"},
    {
    2769, "epsg", 2769, "NAD83(HARN) / California zone 4",
        "+proj=lcc +lat_1=37.25 +lat_2=36 +lat_0=35.33333333333334 +lon_0=-119 +x_0=2000000 +y_0=500000 +ellps=GRS80 +units=m +no_defs"},
    {
    2770, "epsg", 2770, "NAD83(HARN) / California zone 5",
        "+proj=lcc +lat_1=35.46666666666667 +lat_2=34.03333333333333 +lat_0=33.5 +lon_0=-118 +x_0=2000000 +y_0=500000 +ellps=GRS80 +units=m +no_defs"},
    {
    2771, "epsg", 2771, "NAD83(HARN) / California zone 6",
        "+proj=lcc +lat_1=33.88333333333333 +lat_2=32.78333333333333 +lat_0=32.16666666666666 +lon_0=-116.25 +x_0=2000000 +y_0=500000 +ellps=GRS80 +units=m +no_defs"},
    {
    2772, "epsg", 2772, "NAD83(HARN) / Colorado North",
        "+proj=lcc +lat_1=40.78333333333333 +lat_2=39.71666666666667 +lat_0=39.33333333333334 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +units=m +no_defs"},
    {
    2773, "epsg", 2773, "NAD83(HARN) / Colorado Central",
        "+proj=lcc +lat_1=39.75 +lat_2=38.45 +lat_0=37.83333333333334 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +units=m +no_defs"},
    {
    2774, "epsg", 2774, "NAD83(HARN) / Colorado South",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.23333333333333 +lat_0=36.66666666666666 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +units=m +no_defs"},
    {
    2775, "epsg", 2775, "NAD83(HARN) / Connecticut",
        "+proj=lcc +lat_1=41.86666666666667 +lat_2=41.2 +lat_0=40.83333333333334 +lon_0=-72.75 +x_0=304800.6096 +y_0=152400.3048 +ellps=GRS80 +units=m +no_defs"},
    {
    2776, "epsg", 2776, "NAD83(HARN) / Delaware",
        "+proj=tmerc +lat_0=38 +lon_0=-75.41666666666667 +k=0.999995 +x_0=200000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2777, "epsg", 2777, "NAD83(HARN) / Florida East",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-81 +k=0.999941177 +x_0=200000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2778, "epsg", 2778, "NAD83(HARN) / Florida West",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-82 +k=0.999941177 +x_0=200000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2779, "epsg", 2779, "NAD83(HARN) / Florida North",
        "+proj=lcc +lat_1=30.75 +lat_2=29.58333333333333 +lat_0=29 +lon_0=-84.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2780, "epsg", 2780, "NAD83(HARN) / Georgia East",
        "+proj=tmerc +lat_0=30 +lon_0=-82.16666666666667 +k=0.9999 +x_0=200000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2781, "epsg", 2781, "NAD83(HARN) / Georgia West",
        "+proj=tmerc +lat_0=30 +lon_0=-84.16666666666667 +k=0.9999 +x_0=700000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2782, "epsg", 2782, "NAD83(HARN) / Hawaii zone 1",
        "+proj=tmerc +lat_0=18.83333333333333 +lon_0=-155.5 +k=0.999966667 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2783, "epsg", 2783, "NAD83(HARN) / Hawaii zone 2",
        "+proj=tmerc +lat_0=20.33333333333333 +lon_0=-156.6666666666667 +k=0.999966667 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2784, "epsg", 2784, "NAD83(HARN) / Hawaii zone 3",
        "+proj=tmerc +lat_0=21.16666666666667 +lon_0=-158 +k=0.99999 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2785, "epsg", 2785, "NAD83(HARN) / Hawaii zone 4",
        "+proj=tmerc +lat_0=21.83333333333333 +lon_0=-159.5 +k=0.99999 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2786, "epsg", 2786, "NAD83(HARN) / Hawaii zone 5",
        "+proj=tmerc +lat_0=21.66666666666667 +lon_0=-160.1666666666667 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2787, "epsg", 2787, "NAD83(HARN) / Idaho East",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-112.1666666666667 +k=0.9999473679999999 +x_0=200000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2788, "epsg", 2788, "NAD83(HARN) / Idaho Central",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-114 +k=0.9999473679999999 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2789, "epsg", 2789, "NAD83(HARN) / Idaho West",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-115.75 +k=0.999933333 +x_0=800000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2790, "epsg", 2790, "NAD83(HARN) / Illinois East",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-88.33333333333333 +k=0.9999749999999999 +x_0=300000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2791, "epsg", 2791, "NAD83(HARN) / Illinois West",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-90.16666666666667 +k=0.999941177 +x_0=700000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2792, "epsg", 2792, "NAD83(HARN) / Indiana East",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=100000 +y_0=250000 +ellps=GRS80 +units=m +no_defs"},
    {
    2793, "epsg", 2793, "NAD83(HARN) / Indiana West",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=900000 +y_0=250000 +ellps=GRS80 +units=m +no_defs"},
    {
    2794, "epsg", 2794, "NAD83(HARN) / Iowa North",
        "+proj=lcc +lat_1=43.26666666666667 +lat_2=42.06666666666667 +lat_0=41.5 +lon_0=-93.5 +x_0=1500000 +y_0=1000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2795, "epsg", 2795, "NAD83(HARN) / Iowa South",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.61666666666667 +lat_0=40 +lon_0=-93.5 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2796, "epsg", 2796, "NAD83(HARN) / Kansas North",
        "+proj=lcc +lat_1=39.78333333333333 +lat_2=38.71666666666667 +lat_0=38.33333333333334 +lon_0=-98 +x_0=400000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2797, "epsg", 2797, "NAD83(HARN) / Kansas South",
        "+proj=lcc +lat_1=38.56666666666667 +lat_2=37.26666666666667 +lat_0=36.66666666666666 +lon_0=-98.5 +x_0=400000 +y_0=400000 +ellps=GRS80 +units=m +no_defs"},
    {
    2798, "epsg", 2798, "NAD83(HARN) / Kentucky North",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=38.96666666666667 +lat_0=37.5 +lon_0=-84.25 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2799, "epsg", 2799, "NAD83(HARN) / Kentucky South",
        "+proj=lcc +lat_1=37.93333333333333 +lat_2=36.73333333333333 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=500000 +y_0=500000 +ellps=GRS80 +units=m +no_defs"},
    {
    2800, "epsg", 2800, "NAD83(HARN) / Louisiana North",
        "+proj=lcc +lat_1=32.66666666666666 +lat_2=31.16666666666667 +lat_0=30.5 +lon_0=-92.5 +x_0=1000000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2801, "epsg", 2801, "NAD83(HARN) / Louisiana South",
        "+proj=lcc +lat_1=30.7 +lat_2=29.3 +lat_0=28.5 +lon_0=-91.33333333333333 +x_0=1000000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2802, "epsg", 2802, "NAD83(HARN) / Maine East",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2803, "epsg", 2803, "NAD83(HARN) / Maine West",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2804, "epsg", 2804, "NAD83(HARN) / Maryland",
        "+proj=lcc +lat_1=39.45 +lat_2=38.3 +lat_0=37.66666666666666 +lon_0=-77 +x_0=400000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2805, "epsg", 2805, "NAD83(HARN) / Massachusetts Mainland",
        "+proj=lcc +lat_1=42.68333333333333 +lat_2=41.71666666666667 +lat_0=41 +lon_0=-71.5 +x_0=200000 +y_0=750000 +ellps=GRS80 +units=m +no_defs"},
    {
    2806, "epsg", 2806, "NAD83(HARN) / Massachusetts Island",
        "+proj=lcc +lat_1=41.48333333333333 +lat_2=41.28333333333333 +lat_0=41 +lon_0=-70.5 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2807, "epsg", 2807, "NAD83(HARN) / Michigan North",
        "+proj=lcc +lat_1=47.08333333333334 +lat_2=45.48333333333333 +lat_0=44.78333333333333 +lon_0=-87 +x_0=8000000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2808, "epsg", 2808, "NAD83(HARN) / Michigan Central",
        "+proj=lcc +lat_1=45.7 +lat_2=44.18333333333333 +lat_0=43.31666666666667 +lon_0=-84.36666666666666 +x_0=6000000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2809, "epsg", 2809, "NAD83(HARN) / Michigan South",
        "+proj=lcc +lat_1=43.66666666666666 +lat_2=42.1 +lat_0=41.5 +lon_0=-84.36666666666666 +x_0=4000000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2810, "epsg", 2810, "NAD83(HARN) / Minnesota North",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000 +y_0=100000 +ellps=GRS80 +units=m +no_defs"},
    {
    2811, "epsg", 2811, "NAD83(HARN) / Minnesota Central",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000 +y_0=100000 +ellps=GRS80 +units=m +no_defs"},
    {
    2812, "epsg", 2812, "NAD83(HARN) / Minnesota South",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000 +y_0=100000 +ellps=GRS80 +units=m +no_defs"},
    {
    2813, "epsg", 2813, "NAD83(HARN) / Mississippi East",
        "+proj=tmerc +lat_0=29.5 +lon_0=-88.83333333333333 +k=0.99995 +x_0=300000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2814, "epsg", 2814, "NAD83(HARN) / Mississippi West",
        "+proj=tmerc +lat_0=29.5 +lon_0=-90.33333333333333 +k=0.99995 +x_0=700000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2815, "epsg", 2815, "NAD83(HARN) / Missouri East",
        "+proj=tmerc +lat_0=35.83333333333334 +lon_0=-90.5 +k=0.999933333 +x_0=250000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2816, "epsg", 2816, "NAD83(HARN) / Missouri Central",
        "+proj=tmerc +lat_0=35.83333333333334 +lon_0=-92.5 +k=0.999933333 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2817, "epsg", 2817, "NAD83(HARN) / Missouri West",
        "+proj=tmerc +lat_0=36.16666666666666 +lon_0=-94.5 +k=0.999941177 +x_0=850000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2818, "epsg", 2818, "NAD83(HARN) / Montana",
        "+proj=lcc +lat_1=49 +lat_2=45 +lat_0=44.25 +lon_0=-109.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2819, "epsg", 2819, "NAD83(HARN) / Nebraska",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2820, "epsg", 2820, "NAD83(HARN) / Nevada East",
        "+proj=tmerc +lat_0=34.75 +lon_0=-115.5833333333333 +k=0.9999 +x_0=200000 +y_0=8000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2821, "epsg", 2821, "NAD83(HARN) / Nevada Central",
        "+proj=tmerc +lat_0=34.75 +lon_0=-116.6666666666667 +k=0.9999 +x_0=500000 +y_0=6000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2822, "epsg", 2822, "NAD83(HARN) / Nevada West",
        "+proj=tmerc +lat_0=34.75 +lon_0=-118.5833333333333 +k=0.9999 +x_0=800000 +y_0=4000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2823, "epsg", 2823, "NAD83(HARN) / New Hampshire",
        "+proj=tmerc +lat_0=42.5 +lon_0=-71.66666666666667 +k=0.999966667 +x_0=300000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2824, "epsg", 2824, "NAD83(HARN) / New Jersey",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2825, "epsg", 2825, "NAD83(HARN) / New Mexico East",
        "+proj=tmerc +lat_0=31 +lon_0=-104.3333333333333 +k=0.999909091 +x_0=165000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2826, "epsg", 2826, "NAD83(HARN) / New Mexico Central",
        "+proj=tmerc +lat_0=31 +lon_0=-106.25 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2827, "epsg", 2827, "NAD83(HARN) / New Mexico West",
        "+proj=tmerc +lat_0=31 +lon_0=-107.8333333333333 +k=0.999916667 +x_0=830000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2828, "epsg", 2828, "NAD83(HARN) / New York East",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2829, "epsg", 2829, "NAD83(HARN) / New York Central",
        "+proj=tmerc +lat_0=40 +lon_0=-76.58333333333333 +k=0.9999375 +x_0=250000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2830, "epsg", 2830, "NAD83(HARN) / New York West",
        "+proj=tmerc +lat_0=40 +lon_0=-78.58333333333333 +k=0.9999375 +x_0=350000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2831, "epsg", 2831, "NAD83(HARN) / New York Long Island",
        "+proj=lcc +lat_1=41.03333333333333 +lat_2=40.66666666666666 +lat_0=40.16666666666666 +lon_0=-74 +x_0=300000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2832, "epsg", 2832, "NAD83(HARN) / North Dakota North",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.43333333333333 +lat_0=47 +lon_0=-100.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2833, "epsg", 2833, "NAD83(HARN) / North Dakota South",
        "+proj=lcc +lat_1=47.48333333333333 +lat_2=46.18333333333333 +lat_0=45.66666666666666 +lon_0=-100.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2834, "epsg", 2834, "NAD83(HARN) / Ohio North",
        "+proj=lcc +lat_1=41.7 +lat_2=40.43333333333333 +lat_0=39.66666666666666 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2835, "epsg", 2835, "NAD83(HARN) / Ohio South",
        "+proj=lcc +lat_1=40.03333333333333 +lat_2=38.73333333333333 +lat_0=38 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2836, "epsg", 2836, "NAD83(HARN) / Oklahoma North",
        "+proj=lcc +lat_1=36.76666666666667 +lat_2=35.56666666666667 +lat_0=35 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2837, "epsg", 2837, "NAD83(HARN) / Oklahoma South",
        "+proj=lcc +lat_1=35.23333333333333 +lat_2=33.93333333333333 +lat_0=33.33333333333334 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2838, "epsg", 2838, "NAD83(HARN) / Oregon North",
        "+proj=lcc +lat_1=46 +lat_2=44.33333333333334 +lat_0=43.66666666666666 +lon_0=-120.5 +x_0=2500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2839, "epsg", 2839, "NAD83(HARN) / Oregon South",
        "+proj=lcc +lat_1=44 +lat_2=42.33333333333334 +lat_0=41.66666666666666 +lon_0=-120.5 +x_0=1500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2840, "epsg", 2840, "NAD83(HARN) / Rhode Island",
        "+proj=tmerc +lat_0=41.08333333333334 +lon_0=-71.5 +k=0.99999375 +x_0=100000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2841, "epsg", 2841, "NAD83(HARN) / South Dakota North",
        "+proj=lcc +lat_1=45.68333333333333 +lat_2=44.41666666666666 +lat_0=43.83333333333334 +lon_0=-100 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2842, "epsg", 2842, "NAD83(HARN) / South Dakota South",
        "+proj=lcc +lat_1=44.4 +lat_2=42.83333333333334 +lat_0=42.33333333333334 +lon_0=-100.3333333333333 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2843, "epsg", 2843, "NAD83(HARN) / Tennessee",
        "+proj=lcc +lat_1=36.41666666666666 +lat_2=35.25 +lat_0=34.33333333333334 +lon_0=-86 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2844, "epsg", 2844, "NAD83(HARN) / Texas North",
        "+proj=lcc +lat_1=36.18333333333333 +lat_2=34.65 +lat_0=34 +lon_0=-101.5 +x_0=200000 +y_0=1000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2845, "epsg", 2845, "NAD83(HARN) / Texas North Central",
        "+proj=lcc +lat_1=33.96666666666667 +lat_2=32.13333333333333 +lat_0=31.66666666666667 +lon_0=-98.5 +x_0=600000 +y_0=2000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2846, "epsg", 2846, "NAD83(HARN) / Texas Central",
        "+proj=lcc +lat_1=31.88333333333333 +lat_2=30.11666666666667 +lat_0=29.66666666666667 +lon_0=-100.3333333333333 +x_0=700000 +y_0=3000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2847, "epsg", 2847, "NAD83(HARN) / Texas South Central",
        "+proj=lcc +lat_1=30.28333333333333 +lat_2=28.38333333333333 +lat_0=27.83333333333333 +lon_0=-99 +x_0=600000 +y_0=4000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2848, "epsg", 2848, "NAD83(HARN) / Texas South",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.66666666666667 +lon_0=-98.5 +x_0=300000 +y_0=5000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2849, "epsg", 2849, "NAD83(HARN) / Utah North",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000 +y_0=1000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2850, "epsg", 2850, "NAD83(HARN) / Utah Central",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000 +y_0=2000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2851, "epsg", 2851, "NAD83(HARN) / Utah South",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000 +y_0=3000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2852, "epsg", 2852, "NAD83(HARN) / Vermont",
        "+proj=tmerc +lat_0=42.5 +lon_0=-72.5 +k=0.999964286 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2853, "epsg", 2853, "NAD83(HARN) / Virginia North",
        "+proj=lcc +lat_1=39.2 +lat_2=38.03333333333333 +lat_0=37.66666666666666 +lon_0=-78.5 +x_0=3500000 +y_0=2000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2854, "epsg", 2854, "NAD83(HARN) / Virginia South",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=36.76666666666667 +lat_0=36.33333333333334 +lon_0=-78.5 +x_0=3500000 +y_0=1000000 +ellps=GRS80 +units=m +no_defs"},
    {
    2855, "epsg", 2855, "NAD83(HARN) / Washington North",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.5 +lat_0=47 +lon_0=-120.8333333333333 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2856, "epsg", 2856, "NAD83(HARN) / Washington South",
        "+proj=lcc +lat_1=47.33333333333334 +lat_2=45.83333333333334 +lat_0=45.33333333333334 +lon_0=-120.5 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2857, "epsg", 2857, "NAD83(HARN) / West Virginia North",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2858, "epsg", 2858, "NAD83(HARN) / West Virginia South",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2859, "epsg", 2859, "NAD83(HARN) / Wisconsin North",
        "+proj=lcc +lat_1=46.76666666666667 +lat_2=45.56666666666667 +lat_0=45.16666666666666 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2860, "epsg", 2860, "NAD83(HARN) / Wisconsin Central",
        "+proj=lcc +lat_1=45.5 +lat_2=44.25 +lat_0=43.83333333333334 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2861, "epsg", 2861, "NAD83(HARN) / Wisconsin South",
        "+proj=lcc +lat_1=44.06666666666667 +lat_2=42.73333333333333 +lat_0=42 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2862, "epsg", 2862, "NAD83(HARN) / Wyoming East",
        "+proj=tmerc +lat_0=40.5 +lon_0=-105.1666666666667 +k=0.9999375 +x_0=200000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2863, "epsg", 2863, "NAD83(HARN) / Wyoming East Central",
        "+proj=tmerc +lat_0=40.5 +lon_0=-107.3333333333333 +k=0.9999375 +x_0=400000 +y_0=100000 +ellps=GRS80 +units=m +no_defs"},
    {
    2864, "epsg", 2864, "NAD83(HARN) / Wyoming West Central",
        "+proj=tmerc +lat_0=40.5 +lon_0=-108.75 +k=0.9999375 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2865, "epsg", 2865, "NAD83(HARN) / Wyoming West",
        "+proj=tmerc +lat_0=40.5 +lon_0=-110.0833333333333 +k=0.9999375 +x_0=800000 +y_0=100000 +ellps=GRS80 +units=m +no_defs"},
    {
    2866, "epsg", 2866, "NAD83(HARN) / Puerto Rico and Virgin Is.",
        "+proj=lcc +lat_1=18.43333333333333 +lat_2=18.03333333333333 +lat_0=17.83333333333333 +lon_0=-66.43333333333334 +x_0=200000 +y_0=200000 +ellps=GRS80 +units=m +no_defs"},
    {
    2867, "epsg", 2867, "NAD83(HARN) / Arizona East (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-110.1666666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2868, "epsg", 2868, "NAD83(HARN) / Arizona Central (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-111.9166666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2869, "epsg", 2869, "NAD83(HARN) / Arizona West (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-113.75 +k=0.999933333 +x_0=213360 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2870, "epsg", 2870, "NAD83(HARN) / California zone 1 (ftUS)",
        "+proj=lcc +lat_1=41.66666666666666 +lat_2=40 +lat_0=39.33333333333334 +lon_0=-122 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2871, "epsg", 2871, "NAD83(HARN) / California zone 2 (ftUS)",
        "+proj=lcc +lat_1=39.83333333333334 +lat_2=38.33333333333334 +lat_0=37.66666666666666 +lon_0=-122 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2872, "epsg", 2872, "NAD83(HARN) / California zone 3 (ftUS)",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.06666666666667 +lat_0=36.5 +lon_0=-120.5 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2873, "epsg", 2873, "NAD83(HARN) / California zone 4 (ftUS)",
        "+proj=lcc +lat_1=37.25 +lat_2=36 +lat_0=35.33333333333334 +lon_0=-119 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2874, "epsg", 2874, "NAD83(HARN) / California zone 5 (ftUS)",
        "+proj=lcc +lat_1=35.46666666666667 +lat_2=34.03333333333333 +lat_0=33.5 +lon_0=-118 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2875, "epsg", 2875, "NAD83(HARN) / California zone 6 (ftUS)",
        "+proj=lcc +lat_1=33.88333333333333 +lat_2=32.78333333333333 +lat_0=32.16666666666666 +lon_0=-116.25 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2876, "epsg", 2876, "NAD83(HARN) / Colorado North (ftUS)",
        "+proj=lcc +lat_1=40.78333333333333 +lat_2=39.71666666666667 +lat_0=39.33333333333334 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2877, "epsg", 2877, "NAD83(HARN) / Colorado Central (ftUS)",
        "+proj=lcc +lat_1=39.75 +lat_2=38.45 +lat_0=37.83333333333334 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2878, "epsg", 2878, "NAD83(HARN) / Colorado South (ftUS)",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.23333333333333 +lat_0=36.66666666666666 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2879, "epsg", 2879, "NAD83(HARN) / Connecticut (ftUS)",
        "+proj=lcc +lat_1=41.86666666666667 +lat_2=41.2 +lat_0=40.83333333333334 +lon_0=-72.75 +x_0=304800.6096012192 +y_0=152400.3048006096 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2880, "epsg", 2880, "NAD83(HARN) / Delaware (ftUS)",
        "+proj=tmerc +lat_0=38 +lon_0=-75.41666666666667 +k=0.999995 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2881, "epsg", 2881, "NAD83(HARN) / Florida East (ftUS)",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-81 +k=0.999941177 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2882, "epsg", 2882, "NAD83(HARN) / Florida West (ftUS)",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-82 +k=0.999941177 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2883, "epsg", 2883, "NAD83(HARN) / Florida North (ftUS)",
        "+proj=lcc +lat_1=30.75 +lat_2=29.58333333333333 +lat_0=29 +lon_0=-84.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2884, "epsg", 2884, "NAD83(HARN) / Georgia East (ftUS)",
        "+proj=tmerc +lat_0=30 +lon_0=-82.16666666666667 +k=0.9999 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2885, "epsg", 2885, "NAD83(HARN) / Georgia West (ftUS)",
        "+proj=tmerc +lat_0=30 +lon_0=-84.16666666666667 +k=0.9999 +x_0=699999.9998983998 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2886, "epsg", 2886, "NAD83(HARN) / Idaho East (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-112.1666666666667 +k=0.9999473679999999 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2887, "epsg", 2887, "NAD83(HARN) / Idaho Central (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-114 +k=0.9999473679999999 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2888, "epsg", 2888, "NAD83(HARN) / Idaho West (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-115.75 +k=0.999933333 +x_0=800000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2889, "epsg", 2889, "NAD83(HARN) / Indiana East (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=99999.99989839978 +y_0=249364.9987299975 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2890, "epsg", 2890, "NAD83(HARN) / Indiana West (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=900000 +y_0=249364.9987299975 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2891, "epsg", 2891, "NAD83(HARN) / Kentucky North (ftUS)",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=38.96666666666667 +lat_0=37.5 +lon_0=-84.25 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2892, "epsg", 2892, "NAD83(HARN) / Kentucky South (ftUS)",
        "+proj=lcc +lat_1=37.93333333333333 +lat_2=36.73333333333333 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=500000.0001016001 +y_0=500000.0001016001 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2893, "epsg", 2893, "NAD83(HARN) / Maryland (ftUS)",
        "+proj=lcc +lat_1=39.45 +lat_2=38.3 +lat_0=37.66666666666666 +lon_0=-77 +x_0=399999.9998983998 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2894, "epsg", 2894, "NAD83(HARN) / Massachusetts Mainland (ftUS)",
        "+proj=lcc +lat_1=42.68333333333333 +lat_2=41.71666666666667 +lat_0=41 +lon_0=-71.5 +x_0=200000.0001016002 +y_0=750000 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2895, "epsg", 2895, "NAD83(HARN) / Massachusetts Island (ftUS)",
        "+proj=lcc +lat_1=41.48333333333333 +lat_2=41.28333333333333 +lat_0=41 +lon_0=-70.5 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2896, "epsg", 2896, "NAD83(HARN) / Michigan North (ft)",
        "+proj=lcc +lat_1=47.08333333333334 +lat_2=45.48333333333333 +lat_0=44.78333333333333 +lon_0=-87 +x_0=7999999.999968001 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2897, "epsg", 2897, "NAD83(HARN) / Michigan Central (ft)",
        "+proj=lcc +lat_1=45.7 +lat_2=44.18333333333333 +lat_0=43.31666666666667 +lon_0=-84.36666666666666 +x_0=5999999.999976001 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2898, "epsg", 2898, "NAD83(HARN) / Michigan South (ft)",
        "+proj=lcc +lat_1=43.66666666666666 +lat_2=42.1 +lat_0=41.5 +lon_0=-84.36666666666666 +x_0=3999999.999984 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2899, "epsg", 2899, "NAD83(HARN) / Mississippi East (ftUS)",
        "+proj=tmerc +lat_0=29.5 +lon_0=-88.83333333333333 +k=0.99995 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2900, "epsg", 2900, "NAD83(HARN) / Mississippi West (ftUS)",
        "+proj=tmerc +lat_0=29.5 +lon_0=-90.33333333333333 +k=0.99995 +x_0=699999.9998983998 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2901, "epsg", 2901, "NAD83(HARN) / Montana (ft)",
        "+proj=lcc +lat_1=49 +lat_2=45 +lat_0=44.25 +lon_0=-109.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2902, "epsg", 2902, "NAD83(HARN) / New Mexico East (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-104.3333333333333 +k=0.999909091 +x_0=165000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2903, "epsg", 2903, "NAD83(HARN) / New Mexico Central (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-106.25 +k=0.9999 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2904, "epsg", 2904, "NAD83(HARN) / New Mexico West (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-107.8333333333333 +k=0.999916667 +x_0=830000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2905, "epsg", 2905, "NAD83(HARN) / New York East (ftUS)",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2906, "epsg", 2906, "NAD83(HARN) / New York Central (ftUS)",
        "+proj=tmerc +lat_0=40 +lon_0=-76.58333333333333 +k=0.9999375 +x_0=249999.9998983998 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2907, "epsg", 2907, "NAD83(HARN) / New York West (ftUS)",
        "+proj=tmerc +lat_0=40 +lon_0=-78.58333333333333 +k=0.9999375 +x_0=350000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2908, "epsg", 2908, "NAD83(HARN) / New York Long Island (ftUS)",
        "+proj=lcc +lat_1=41.03333333333333 +lat_2=40.66666666666666 +lat_0=40.16666666666666 +lon_0=-74 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2909, "epsg", 2909, "NAD83(HARN) / North Dakota North (ft)",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.43333333333333 +lat_0=47 +lon_0=-100.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2910, "epsg", 2910, "NAD83(HARN) / North Dakota South (ft)",
        "+proj=lcc +lat_1=47.48333333333333 +lat_2=46.18333333333333 +lat_0=45.66666666666666 +lon_0=-100.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2911, "epsg", 2911, "NAD83(HARN) / Oklahoma North (ftUS)",
        "+proj=lcc +lat_1=36.76666666666667 +lat_2=35.56666666666667 +lat_0=35 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2912, "epsg", 2912, "NAD83(HARN) / Oklahoma South (ftUS)",
        "+proj=lcc +lat_1=35.23333333333333 +lat_2=33.93333333333333 +lat_0=33.33333333333334 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2913, "epsg", 2913, "NAD83(HARN) / Oregon North (ft)",
        "+proj=lcc +lat_1=46 +lat_2=44.33333333333334 +lat_0=43.66666666666666 +lon_0=-120.5 +x_0=2500000.0001424 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2914, "epsg", 2914, "NAD83(HARN) / Oregon South (ft)",
        "+proj=lcc +lat_1=44 +lat_2=42.33333333333334 +lat_0=41.66666666666666 +lon_0=-120.5 +x_0=1500000.0001464 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2915, "epsg", 2915, "NAD83(HARN) / Tennessee (ftUS)",
        "+proj=lcc +lat_1=36.41666666666666 +lat_2=35.25 +lat_0=34.33333333333334 +lon_0=-86 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2916, "epsg", 2916, "NAD83(HARN) / Texas North (ftUS)",
        "+proj=lcc +lat_1=36.18333333333333 +lat_2=34.65 +lat_0=34 +lon_0=-101.5 +x_0=200000.0001016002 +y_0=999999.9998983998 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2917, "epsg", 2917, "NAD83(HARN) / Texas North Central (ftUS)",
        "+proj=lcc +lat_1=33.96666666666667 +lat_2=32.13333333333333 +lat_0=31.66666666666667 +lon_0=-98.5 +x_0=600000 +y_0=2000000.0001016 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2918, "epsg", 2918, "NAD83(HARN) / Texas Central (ftUS)",
        "+proj=lcc +lat_1=31.88333333333333 +lat_2=30.11666666666667 +lat_0=29.66666666666667 +lon_0=-100.3333333333333 +x_0=699999.9998983998 +y_0=3000000 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2919, "epsg", 2919, "NAD83(HARN) / Texas South Central (ftUS)",
        "+proj=lcc +lat_1=30.28333333333333 +lat_2=28.38333333333333 +lat_0=27.83333333333333 +lon_0=-99 +x_0=600000 +y_0=3999999.9998984 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2920, "epsg", 2920, "NAD83(HARN) / Texas South (ftUS)",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.66666666666667 +lon_0=-98.5 +x_0=300000.0000000001 +y_0=5000000.0001016 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2921, "epsg", 2921, "NAD83(HARN) / Utah North (ft)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000.0001504 +y_0=999999.9999960001 +ellps=GRS80 +units=ft +no_defs"},
    {
    2922, "epsg", 2922, "NAD83(HARN) / Utah Central (ft)",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000.0001504 +y_0=1999999.999992 +ellps=GRS80 +units=ft +no_defs"},
    {
    2923, "epsg", 2923, "NAD83(HARN) / Utah South (ft)",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000.0001504 +y_0=2999999.999988 +ellps=GRS80 +units=ft +no_defs"},
    {
    2924, "epsg", 2924, "NAD83(HARN) / Virginia North (ftUS)",
        "+proj=lcc +lat_1=39.2 +lat_2=38.03333333333333 +lat_0=37.66666666666666 +lon_0=-78.5 +x_0=3500000.0001016 +y_0=2000000.0001016 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2925, "epsg", 2925, "NAD83(HARN) / Virginia South (ftUS)",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=36.76666666666667 +lat_0=36.33333333333334 +lon_0=-78.5 +x_0=3500000.0001016 +y_0=999999.9998983998 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2926, "epsg", 2926, "NAD83(HARN) / Washington North (ftUS)",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.5 +lat_0=47 +lon_0=-120.8333333333333 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2927, "epsg", 2927, "NAD83(HARN) / Washington South (ftUS)",
        "+proj=lcc +lat_1=47.33333333333334 +lat_2=45.83333333333334 +lat_0=45.33333333333334 +lon_0=-120.5 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2928, "epsg", 2928, "NAD83(HARN) / Wisconsin North (ftUS)",
        "+proj=lcc +lat_1=46.76666666666667 +lat_2=45.56666666666667 +lat_0=45.16666666666666 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2929, "epsg", 2929, "NAD83(HARN) / Wisconsin Central (ftUS)",
        "+proj=lcc +lat_1=45.5 +lat_2=44.25 +lat_0=43.83333333333334 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2930, "epsg", 2930, "NAD83(HARN) / Wisconsin South (ftUS)",
        "+proj=lcc +lat_1=44.06666666666667 +lat_2=42.73333333333333 +lat_0=42 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2931, "epsg", 2931, "Beduaram / TM 13 NE",
        "+proj=tmerc +lat_0=0 +lon_0=13 +k=0.9996 +x_0=500000 +y_0=0 +a=6378249.2 +b=6356515 +towgs84=-106,-87,188,0,0,0,0 +units=m +no_defs"},
    {
    2932, "epsg", 2932, "QND95 / Qatar National Grid",
        "+proj=tmerc +lat_0=24.45 +lon_0=51.21666666666667 +k=0.99999 +x_0=200000 +y_0=300000 +ellps=intl +towgs84=-119.425,-303.659,-11.0006,1.1643,0.174458,1.09626,3.65706 +units=m +no_defs"},
    {
    2933, "epsg", 2933, "Segara / UTM zone 50S",
        "+proj=utm +zone=50 +south +ellps=bessel +units=m +no_defs"},
    {
    2934, "epsg", 2934, "Segara (Jakarta) / NEIEZ (deprecated)",
        "+proj=merc +lon_0=110 +k=0.997 +x_0=3900000 +y_0=900000 +ellps=bessel +pm=jakarta +units=m +no_defs"},
    {
    2935, "epsg", 2935, "Pulkovo 1942 / CS63 zone A1",
        "+proj=tmerc +lat_0=0.1166666666666667 +lon_0=41.53333333333333 +k=1 +x_0=1300000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2936, "epsg", 2936, "Pulkovo 1942 / CS63 zone A2",
        "+proj=tmerc +lat_0=0.1166666666666667 +lon_0=44.53333333333333 +k=1 +x_0=2300000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2937, "epsg", 2937, "Pulkovo 1942 / CS63 zone A3",
        "+proj=tmerc +lat_0=0.1166666666666667 +lon_0=47.53333333333333 +k=1 +x_0=3300000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2938, "epsg", 2938, "Pulkovo 1942 / CS63 zone A4",
        "+proj=tmerc +lat_0=0.1166666666666667 +lon_0=50.53333333333333 +k=1 +x_0=4300000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2939, "epsg", 2939, "Pulkovo 1942 / CS63 zone K2",
        "+proj=tmerc +lat_0=0.1333333333333333 +lon_0=50.76666666666667 +k=1 +x_0=2300000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2940, "epsg", 2940, "Pulkovo 1942 / CS63 zone K3",
        "+proj=tmerc +lat_0=0.1333333333333333 +lon_0=53.76666666666667 +k=1 +x_0=3300000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2941, "epsg", 2941, "Pulkovo 1942 / CS63 zone K4",
        "+proj=tmerc +lat_0=0.1333333333333333 +lon_0=56.76666666666667 +k=1 +x_0=4300000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    2942, "epsg", 2942, "Porto Santo / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=intl +towgs84=-499,-249,314,0,0,0,0 +units=m +no_defs"},
    {
    2943, "epsg", 2943, "Selvagem Grande / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=intl +units=m +no_defs"},
    {
    2944, "epsg", 2944, "NAD83(CSRS) / SCoPQ zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=-55.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2945, "epsg", 2945, "NAD83(CSRS) / MTM zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=-58.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2946, "epsg", 2946, "NAD83(CSRS) / MTM zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=-61.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2947, "epsg", 2947, "NAD83(CSRS) / MTM zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=-64.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2948, "epsg", 2948, "NAD83(CSRS) / MTM zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=-67.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2949, "epsg", 2949, "NAD83(CSRS) / MTM zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=-70.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2950, "epsg", 2950, "NAD83(CSRS) / MTM zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=-73.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2951, "epsg", 2951, "NAD83(CSRS) / MTM zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=-76.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2952, "epsg", 2952, "NAD83(CSRS) / MTM zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=-79.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2953, "epsg", 2953, "NAD83(CSRS) / New Brunswick Stereographic",
        "+proj=sterea +lat_0=46.5 +lon_0=-66.5 +k=0.999912 +x_0=2500000 +y_0=7500000 +ellps=GRS80 +units=m +no_defs"},
    {
    2954, "epsg", 2954,
        "NAD83(CSRS) / Prince Edward Isl. Stereographic (NAD83)",
        "+proj=sterea +lat_0=47.25 +lon_0=-63 +k=0.999912 +x_0=400000 +y_0=800000 +ellps=GRS80 +units=m +no_defs"},
    {
    2955, "epsg", 2955, "NAD83(CSRS) / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=GRS80 +units=m +no_defs"},
    {
    2956, "epsg", 2956, "NAD83(CSRS) / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=GRS80 +units=m +no_defs"},
    {
    2957, "epsg", 2957, "NAD83(CSRS) / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=GRS80 +units=m +no_defs"},
    {
    2958, "epsg", 2958, "NAD83(CSRS) / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=GRS80 +units=m +no_defs"},
    {
    2959, "epsg", 2959, "NAD83(CSRS) / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=GRS80 +units=m +no_defs"},
    {
    2960, "epsg", 2960, "NAD83(CSRS) / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=GRS80 +units=m +no_defs"},
    {
    2961, "epsg", 2961, "NAD83(CSRS) / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=GRS80 +units=m +no_defs"},
    {
    2962, "epsg", 2962, "NAD83(CSRS) / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=GRS80 +units=m +no_defs"},
    {
    2964, "epsg", 2964, "NAD27 / Alaska Albers",
        "+proj=aea +lat_1=55 +lat_2=65 +lat_0=50 +lon_0=-154 +x_0=0 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    2965, "epsg", 2965, "NAD83 / Indiana East (ftUS)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=99999.99989839978 +y_0=249999.9998983998 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2966, "epsg", 2966, "NAD83 / Indiana West (ftUS)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=900000 +y_0=249999.9998983998 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    2967, "epsg", 2967, "NAD83(HARN) / Indiana East (ftUS)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=99999.99989839978 +y_0=249999.9998983998 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2968, "epsg", 2968, "NAD83(HARN) / Indiana West (ftUS)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=900000 +y_0=249999.9998983998 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    2969, "epsg", 2969, "Fort Marigot / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=intl +towgs84=137,248,-430,0,0,0,0 +units=m +no_defs"},
    {
    2970, "epsg", 2970, "Guadeloupe 1948 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=intl +units=m +no_defs"},
    {
    2971, "epsg", 2971, "CSG67 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=intl +towgs84=-186,230,110,0,0,0,0 +units=m +no_defs"},
    {
    2972, "epsg", 2972, "RGFG95 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=GRS80 +towgs84=2,2,-2,0,0,0,0 +units=m +no_defs"},
    {
    2973, "epsg", 2973, "Martinique 1938 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=intl +units=m +no_defs"},
    {
    2975, "epsg", 2975, "RGR92 / UTM zone 40S",
        "+proj=utm +zone=40 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2976, "epsg", 2976, "Tahiti 52 / UTM zone 6S",
        "+proj=utm +zone=6 +south +ellps=intl +towgs84=162,117,154,0,0,0,0 +units=m +no_defs"},
    {
    2977, "epsg", 2977, "Tahaa 54 / UTM zone 5S",
        "+proj=utm +zone=5 +south +ellps=intl +units=m +no_defs"},
    {
    2978, "epsg", 2978, "IGN72 Nuku Hiva / UTM zone 7S",
        "+proj=utm +zone=7 +south +ellps=intl +units=m +no_defs"},
    {
    2979, "epsg", 2979, "K0 1949 / UTM zone 42S (deprecated)",
        "+proj=utm +zone=42 +south +ellps=intl +towgs84=145,-187,103,0,0,0,0 +units=m +no_defs"},
    {
    2980, "epsg", 2980, "Combani 1950 / UTM zone 38S",
        "+proj=utm +zone=38 +south +ellps=intl +towgs84=-382,-59,-262,0,0,0,0 +units=m +no_defs"},
    {
    2981, "epsg", 2981, "IGN56 Lifou / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=intl +units=m +no_defs"},
    {
    2982, "epsg", 2982, "IGN72 Grand Terre / UTM zone 58S (deprecated)",
        "+proj=utm +zone=58 +south +ellps=intl +units=m +no_defs"},
    {
    2983, "epsg", 2983, "ST87 Ouvea / UTM zone 58S (deprecated)",
        "+proj=utm +zone=58 +south +ellps=intl +towgs84=-122.383,-188.696,103.344,3.5107,-4.9668,-5.7047,4.4798 +units=m +no_defs"},
    {
    2984, "epsg", 2984, "RGNC 1991 / Lambert New Caledonia (deprecated)",
        "+proj=lcc +lat_1=-20.66666666666667 +lat_2=-22.33333333333333 +lat_0=-21.5 +lon_0=166 +x_0=400000 +y_0=300000 +ellps=intl +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2987, "epsg", 2987, "Saint Pierre et Miquelon 1950 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=clrk66 +towgs84=30,430,368,0,0,0,0 +units=m +no_defs"},
    {
    2988, "epsg", 2988, "MOP78 / UTM zone 1S",
        "+proj=utm +zone=1 +south +ellps=intl +units=m +no_defs"},
    {
    2989, "epsg", 2989, "RRAF 1991 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    2990, "epsg", 2990, "Reunion 1947 / TM Reunion (deprecated)",
        "+proj=tmerc +lat_0=-21.11666666666667 +lon_0=55.53333333333333 +k=1 +x_0=50000 +y_0=160000 +ellps=intl +units=m +no_defs"},
    {
    2991, "epsg", 2991, "NAD83 / Oregon Lambert",
        "+proj=lcc +lat_1=43 +lat_2=45.5 +lat_0=41.75 +lon_0=-120.5 +x_0=400000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    2992, "epsg", 2992, "NAD83 / Oregon Lambert (ft)",
        "+proj=lcc +lat_1=43 +lat_2=45.5 +lat_0=41.75 +lon_0=-120.5 +x_0=399999.9999984 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=ft +no_defs"},
    {
    2993, "epsg", 2993, "NAD83(HARN) / Oregon Lambert",
        "+proj=lcc +lat_1=43 +lat_2=45.5 +lat_0=41.75 +lon_0=-120.5 +x_0=400000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    2994, "epsg", 2994, "NAD83(HARN) / Oregon Lambert (ft)",
        "+proj=lcc +lat_1=43 +lat_2=45.5 +lat_0=41.75 +lon_0=-120.5 +x_0=399999.9999984 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    2995, "epsg", 2995, "IGN53 Mare / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=intl +units=m +no_defs"},
    {
    2996, "epsg", 2996, "ST84 Ile des Pins / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=intl +units=m +no_defs"},
    {
    2997, "epsg", 2997, "ST71 Belep / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=intl +towgs84=-480.26,-438.32,-643.429,16.3119,20.1721,-4.0349,-111.7 +units=m +no_defs"},
    {
    2998, "epsg", 2998, "NEA74 Noumea / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=intl +units=m +no_defs"},
    {
    2999, "epsg", 2999, "Grand Comoros / UTM zone 38S",
        "+proj=utm +zone=38 +south +ellps=intl +units=m +no_defs"},
    {
    3000, "epsg", 3000, "Segara / NEIEZ",
        "+proj=merc +lon_0=110 +k=0.997 +x_0=3900000 +y_0=900000 +ellps=bessel +units=m +no_defs"},
    {
    3001, "epsg", 3001, "Batavia / NEIEZ",
        "+proj=merc +lon_0=110 +k=0.997 +x_0=3900000 +y_0=900000 +ellps=bessel +units=m +no_defs"},
    {
    3002, "epsg", 3002, "Makassar / NEIEZ",
        "+proj=merc +lon_0=110 +k=0.997 +x_0=3900000 +y_0=900000 +ellps=bessel +towgs84=-587.8,519.75,145.76,0,0,0,0 +units=m +no_defs"},
    {
    3003, "epsg", 3003, "Monte Mario / Italy zone 1",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=1500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    3004, "epsg", 3004, "Monte Mario / Italy zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9996 +x_0=2520000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    3005, "epsg", 3005, "NAD83 / BC Albers",
        "+proj=aea +lat_1=50 +lat_2=58.5 +lat_0=45 +lon_0=-126 +x_0=1000000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3006, "epsg", 3006, "SWEREF99 TM",
        "+proj=utm +zone=33 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3007, "epsg", 3007, "SWEREF99 12 00",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3008, "epsg", 3008, "SWEREF99 13 30",
        "+proj=tmerc +lat_0=0 +lon_0=13.5 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3009, "epsg", 3009, "SWEREF99 15 00",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3010, "epsg", 3010, "SWEREF99 16 30",
        "+proj=tmerc +lat_0=0 +lon_0=16.5 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3011, "epsg", 3011, "SWEREF99 18 00",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3012, "epsg", 3012, "SWEREF99 14 15",
        "+proj=tmerc +lat_0=0 +lon_0=14.25 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3013, "epsg", 3013, "SWEREF99 15 45",
        "+proj=tmerc +lat_0=0 +lon_0=15.75 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3014, "epsg", 3014, "SWEREF99 17 15",
        "+proj=tmerc +lat_0=0 +lon_0=17.25 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3015, "epsg", 3015, "SWEREF99 18 45",
        "+proj=tmerc +lat_0=0 +lon_0=18.75 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3016, "epsg", 3016, "SWEREF99 20 15",
        "+proj=tmerc +lat_0=0 +lon_0=20.25 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3017, "epsg", 3017, "SWEREF99 21 45",
        "+proj=tmerc +lat_0=0 +lon_0=21.75 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3018, "epsg", 3018, "SWEREF99 23 15",
        "+proj=tmerc +lat_0=0 +lon_0=23.25 +k=1 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3019, "epsg", 3019, "RT90 7.5 gon V",
        "+proj=tmerc +lat_0=0 +lon_0=11.30827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3020, "epsg", 3020, "RT90 5 gon V",
        "+proj=tmerc +lat_0=0 +lon_0=13.55827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3021, "epsg", 3021, "RT90 2.5 gon V",
        "+proj=tmerc +lat_0=0 +lon_0=15.80827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3022, "epsg", 3022, "RT90 0 gon",
        "+proj=tmerc +lat_0=0 +lon_0=18.05827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3023, "epsg", 3023, "RT90 2.5 gon O",
        "+proj=tmerc +lat_0=0 +lon_0=20.30827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3024, "epsg", 3024, "RT90 5 gon O",
        "+proj=tmerc +lat_0=0 +lon_0=22.55827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3025, "epsg", 3025, "RT38 7.5 gon V",
        "+proj=tmerc +lat_0=0 +lon_0=11.30827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3026, "epsg", 3026, "RT38 5 gon V",
        "+proj=tmerc +lat_0=0 +lon_0=13.55827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3027, "epsg", 3027, "RT38 2.5 gon V",
        "+proj=tmerc +lat_0=0 +lon_0=15.80827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3028, "epsg", 3028, "RT38 0 gon",
        "+proj=tmerc +lat_0=0 +lon_0=18.05827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3029, "epsg", 3029, "RT38 2.5 gon O",
        "+proj=tmerc +lat_0=0 +lon_0=20.30827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3030, "epsg", 3030, "RT38 5 gon O",
        "+proj=tmerc +lat_0=0 +lon_0=22.55827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3031, "epsg", 3031, "WGS 84 / Antarctic Polar Stereographic",
        "+proj=stere +lat_0=-90 +lat_ts=-71 +lon_0=0 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3032, "epsg", 3032, "WGS 84 / Australian Antarctic Polar Stereographic",
        "+proj=stere +lat_0=-90 +lat_ts=-71 +lon_0=70 +k=1 +x_0=6000000 +y_0=6000000 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3033, "epsg", 3033, "WGS 84 / Australian Antarctic Lambert",
        "+proj=lcc +lat_1=-68.5 +lat_2=-74.5 +lat_0=-50 +lon_0=70 +x_0=6000000 +y_0=6000000 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3034, "epsg", 3034, "ETRS89 / ETRS-LCC",
        "+proj=lcc +lat_1=35 +lat_2=65 +lat_0=52 +lon_0=10 +x_0=4000000 +y_0=2800000 +ellps=GRS80 +units=m +no_defs"},
    {
    3035, "epsg", 3035, "ETRS89 / ETRS-LAEA",
        "+proj=laea +lat_0=52 +lon_0=10 +x_0=4321000 +y_0=3210000 +ellps=GRS80 +units=m +no_defs"},
    {
    3036, "epsg", 3036, "Moznet / UTM zone 36S",
        "+proj=utm +zone=36 +south +ellps=WGS84 +towgs84=0,0,0,-0,-0,-0,0 +units=m +no_defs"},
    {
    3037, "epsg", 3037, "Moznet / UTM zone 37S",
        "+proj=utm +zone=37 +south +ellps=WGS84 +towgs84=0,0,0,-0,-0,-0,0 +units=m +no_defs"},
    {
    3038, "epsg", 3038, "ETRS89 / ETRS-TM26",
        "+proj=utm +zone=26 +ellps=GRS80 +units=m +no_defs"},
    {
    3039, "epsg", 3039, "ETRS89 / ETRS-TM27",
        "+proj=utm +zone=27 +ellps=GRS80 +units=m +no_defs"},
    {
    3040, "epsg", 3040, "ETRS89 / ETRS-TM28",
        "+proj=utm +zone=28 +ellps=GRS80 +units=m +no_defs"},
    {
    3041, "epsg", 3041, "ETRS89 / ETRS-TM29",
        "+proj=utm +zone=29 +ellps=GRS80 +units=m +no_defs"},
    {
    3042, "epsg", 3042, "ETRS89 / ETRS-TM30",
        "+proj=utm +zone=30 +ellps=GRS80 +units=m +no_defs"},
    {
    3043, "epsg", 3043, "ETRS89 / ETRS-TM31",
        "+proj=utm +zone=31 +ellps=GRS80 +units=m +no_defs"},
    {
    3044, "epsg", 3044, "ETRS89 / ETRS-TM32",
        "+proj=utm +zone=32 +ellps=GRS80 +units=m +no_defs"},
    {
    3045, "epsg", 3045, "ETRS89 / ETRS-TM33",
        "+proj=utm +zone=33 +ellps=GRS80 +units=m +no_defs"},
    {
    3046, "epsg", 3046, "ETRS89 / ETRS-TM34",
        "+proj=utm +zone=34 +ellps=GRS80 +units=m +no_defs"},
    {
    3047, "epsg", 3047, "ETRS89 / ETRS-TM35",
        "+proj=utm +zone=35 +ellps=GRS80 +units=m +no_defs"},
    {
    3048, "epsg", 3048, "ETRS89 / ETRS-TM36",
        "+proj=utm +zone=36 +ellps=GRS80 +units=m +no_defs"},
    {
    3049, "epsg", 3049, "ETRS89 / ETRS-TM37",
        "+proj=utm +zone=37 +ellps=GRS80 +units=m +no_defs"},
    {
    3050, "epsg", 3050, "ETRS89 / ETRS-TM38",
        "+proj=utm +zone=38 +ellps=GRS80 +units=m +no_defs"},
    {
    3051, "epsg", 3051, "ETRS89 / ETRS-TM39",
        "+proj=utm +zone=39 +ellps=GRS80 +units=m +no_defs"},
    {
    3054, "epsg", 3054, "Hjorsey 1955 / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=intl +towgs84=-73,46,-86,0,0,0,0 +units=m +no_defs"},
    {
    3055, "epsg", 3055, "Hjorsey 1955 / UTM zone 27N",
        "+proj=utm +zone=27 +ellps=intl +towgs84=-73,46,-86,0,0,0,0 +units=m +no_defs"},
    {
    3056, "epsg", 3056, "Hjorsey 1955 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=intl +towgs84=-73,46,-86,0,0,0,0 +units=m +no_defs"},
    {
    3057, "epsg", 3057, "ISN93 / Lambert 1993",
        "+proj=lcc +lat_1=64.25 +lat_2=65.75 +lat_0=65 +lon_0=-19 +x_0=500000 +y_0=500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3058, "epsg", 3058, "Helle 1954 / Jan Mayen Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-8.5 +k=1 +x_0=50000 +y_0=-7800000 +ellps=intl +towgs84=982.609,552.753,-540.873,32.3934,-153.257,-96.2266,16.805 +units=m +no_defs"},
    {
    3059, "epsg", 3059, "LKS92 / Latvia TM",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9996 +x_0=500000 +y_0=-6000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3060, "epsg", 3060, "IGN72 Grande Terre / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=intl +units=m +no_defs"},
    {
    3061, "epsg", 3061, "Porto Santo 1995 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=intl +units=m +no_defs"},
    {
    3062, "epsg", 3062, "Azores Oriental 1995 / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=intl +units=m +no_defs"},
    {
    3063, "epsg", 3063, "Azores Central 1995 / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=intl +units=m +no_defs"},
    {
    3064, "epsg", 3064, "IGM95 / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3065, "epsg", 3065, "IGM95 / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3066, "epsg", 3066, "ED50 / Jordan TM",
        "+proj=tmerc +lat_0=0 +lon_0=37 +k=0.9998 +x_0=500000 +y_0=-3000000 +ellps=intl +units=m +no_defs"},
    {
    3067, "epsg", 3067, "ETRS89 / ETRS-TM35FIN",
        "+proj=utm +zone=35 +ellps=GRS80 +units=m +no_defs"},
    {
    3068, "epsg", 3068, "DHDN / Soldner Berlin",
        "+proj=cass +lat_0=52.41864827777778 +lon_0=13.62720366666667 +x_0=40000 +y_0=10000 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    3069, "epsg", 3069, "NAD27 / Wisconsin Transverse Mercator",
        "+proj=tmerc +lat_0=0 +lon_0=-90 +k=0.9996 +x_0=500000 +y_0=-4500000 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3070, "epsg", 3070, "NAD83 / Wisconsin Transverse Mercator",
        "+proj=tmerc +lat_0=0 +lon_0=-90 +k=0.9996 +x_0=520000 +y_0=-4480000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3071, "epsg", 3071, "NAD83(HARN) / Wisconsin Transverse Mercator",
        "+proj=tmerc +lat_0=0 +lon_0=-90 +k=0.9996 +x_0=520000 +y_0=-4480000 +ellps=GRS80 +units=m +no_defs"},
    {
    3072, "epsg", 3072, "NAD83 / Maine CS2000 East",
        "+proj=tmerc +lat_0=43.83333333333334 +lon_0=-67.875 +k=0.99998 +x_0=700000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3073, "epsg", 3073, "NAD83 / Maine CS2000 Central (deprecated)",
        "+proj=tmerc +lat_0=43 +lon_0=-69.125 +k=0.99998 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3074, "epsg", 3074, "NAD83 / Maine CS2000 West",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.375 +k=0.99998 +x_0=300000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3075, "epsg", 3075, "NAD83(HARN) / Maine CS2000 East",
        "+proj=tmerc +lat_0=43.83333333333334 +lon_0=-67.875 +k=0.99998 +x_0=700000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3076, "epsg", 3076, "NAD83(HARN) / Maine CS2000 Central (deprecated)",
        "+proj=tmerc +lat_0=43 +lon_0=-69.125 +k=0.99998 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3077, "epsg", 3077, "NAD83(HARN) / Maine CS2000 West",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.375 +k=0.99998 +x_0=300000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3078, "epsg", 3078, "NAD83 / Michigan Oblique Mercator",
        "+proj=omerc +lat_0=45.30916666666666 +lonc=-86 +alpha=337.25556 +k=0.9996 +x_0=2546731.496 +y_0=-4354009.816 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3079, "epsg", 3079, "NAD83(HARN) / Michigan Oblique Mercator",
        "+proj=omerc +lat_0=45.30916666666666 +lonc=-86 +alpha=337.25556 +k=0.9996 +x_0=2546731.496 +y_0=-4354009.816 +ellps=GRS80 +units=m +no_defs"},
    {
    3080, "epsg", 3080, "NAD27 / Shackleford",
        "+proj=lcc +lat_1=27.41666666666667 +lat_2=34.91666666666666 +lat_0=31.16666666666667 +lon_0=-100 +x_0=914400 +y_0=914400 +ellps=clrk66 +datum=NAD27 +units=ft +no_defs"},
    {
    3081, "epsg", 3081, "NAD83 / Texas State Mapping System",
        "+proj=lcc +lat_1=27.41666666666667 +lat_2=34.91666666666666 +lat_0=31.16666666666667 +lon_0=-100 +x_0=1000000 +y_0=1000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3082, "epsg", 3082, "NAD83 / Texas Centric Lambert Conformal",
        "+proj=lcc +lat_1=27.5 +lat_2=35 +lat_0=18 +lon_0=-100 +x_0=1500000 +y_0=5000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3083, "epsg", 3083, "NAD83 / Texas Centric Albers Equal Area",
        "+proj=aea +lat_1=27.5 +lat_2=35 +lat_0=18 +lon_0=-100 +x_0=1500000 +y_0=6000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3084, "epsg", 3084, "NAD83(HARN) / Texas Centric Lambert Conformal",
        "+proj=lcc +lat_1=27.5 +lat_2=35 +lat_0=18 +lon_0=-100 +x_0=1500000 +y_0=5000000 +ellps=GRS80 +units=m +no_defs"},
    {
    3085, "epsg", 3085, "NAD83(HARN) / Texas Centric Albers Equal Area",
        "+proj=aea +lat_1=27.5 +lat_2=35 +lat_0=18 +lon_0=-100 +x_0=1500000 +y_0=6000000 +ellps=GRS80 +units=m +no_defs"},
    {
    3086, "epsg", 3086, "NAD83 / Florida GDL Albers",
        "+proj=aea +lat_1=24 +lat_2=31.5 +lat_0=24 +lon_0=-84 +x_0=400000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3087, "epsg", 3087, "NAD83(HARN) / Florida GDL Albers",
        "+proj=aea +lat_1=24 +lat_2=31.5 +lat_0=24 +lon_0=-84 +x_0=400000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3088, "epsg", 3088, "NAD83 / Kentucky Single Zone",
        "+proj=lcc +lat_1=37.08333333333334 +lat_2=38.66666666666666 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=1500000 +y_0=1000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3089, "epsg", 3089, "NAD83 / Kentucky Single Zone (ftUS)",
        "+proj=lcc +lat_1=37.08333333333334 +lat_2=38.66666666666666 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=1500000 +y_0=999999.9998983998 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3090, "epsg", 3090, "NAD83(HARN) / Kentucky Single Zone",
        "+proj=lcc +lat_1=37.08333333333334 +lat_2=38.66666666666666 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=1500000 +y_0=1000000 +ellps=GRS80 +units=m +no_defs"},
    {
    3091, "epsg", 3091, "NAD83(HARN) / Kentucky Single Zone (ftUS)",
        "+proj=lcc +lat_1=37.08333333333334 +lat_2=38.66666666666666 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=1500000 +y_0=999999.9998983998 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3092, "epsg", 3092, "Tokyo / UTM zone 51N",
        "+proj=utm +zone=51 +ellps=bessel +units=m +no_defs"},
    {
    3093, "epsg", 3093, "Tokyo / UTM zone 52N",
        "+proj=utm +zone=52 +ellps=bessel +units=m +no_defs"},
    {
    3094, "epsg", 3094, "Tokyo / UTM zone 53N",
        "+proj=utm +zone=53 +ellps=bessel +units=m +no_defs"},
    {
    3095, "epsg", 3095, "Tokyo / UTM zone 54N",
        "+proj=utm +zone=54 +ellps=bessel +units=m +no_defs"},
    {
    3096, "epsg", 3096, "Tokyo / UTM zone 55N",
        "+proj=utm +zone=55 +ellps=bessel +units=m +no_defs"},
    {
    3097, "epsg", 3097, "JGD2000 / UTM zone 51N",
        "+proj=utm +zone=51 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3098, "epsg", 3098, "JGD2000 / UTM zone 52N",
        "+proj=utm +zone=52 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3099, "epsg", 3099, "JGD2000 / UTM zone 53N",
        "+proj=utm +zone=53 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3100, "epsg", 3100, "JGD2000 / UTM zone 54N",
        "+proj=utm +zone=54 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3101, "epsg", 3101, "JGD2000 / UTM zone 55N",
        "+proj=utm +zone=55 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3102, "epsg", 3102, "American Samoa 1962 / American Samoa Lambert",
        "+proj=lcc +lat_1=-14.26666666666667 +lat_0=-14.26666666666667 +lon_0=-170 +k_0=1 +x_0=152400.3048006096 +y_0=95169.31165862332 +ellps=clrk66 +towgs84=-115,118,426,0,0,0,0 +units=us-ft +no_defs"},
    {
    3103, "epsg", 3103, "Mauritania 1999 / UTM zone 28N (deprecated)",
        "+proj=utm +zone=28 +ellps=clrk80 +units=m +no_defs"},
    {
    3104, "epsg", 3104, "Mauritania 1999 / UTM zone 29N (deprecated)",
        "+proj=utm +zone=29 +ellps=clrk80 +units=m +no_defs"},
    {
    3105, "epsg", 3105, "Mauritania 1999 / UTM zone 30N (deprecated)",
        "+proj=utm +zone=30 +ellps=clrk80 +units=m +no_defs"},
    {
    3106, "epsg", 3106, "Gulshan 303 / Bangladesh Transverse Mercator",
        "+proj=tmerc +lat_0=0 +lon_0=90 +k=0.9996 +x_0=500000 +y_0=0 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    3107, "epsg", 3107, "GDA94 / SA Lambert",
        "+proj=lcc +lat_1=-28 +lat_2=-36 +lat_0=-32 +lon_0=135 +x_0=1000000 +y_0=2000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3108, "epsg", 3108, "ETRS89 / Guernsey Grid",
        "+proj=tmerc +lat_0=49.5 +lon_0=-2.416666666666667 +k=0.999997 +x_0=47000 +y_0=50000 +ellps=GRS80 +units=m +no_defs"},
    {
    3109, "epsg", 3109, "ETRS89 / Jersey Transverse Mercator",
        "+proj=tmerc +lat_0=49.225 +lon_0=-2.135 +k=0.9999999000000001 +x_0=40000 +y_0=70000 +ellps=GRS80 +units=m +no_defs"},
    {
    3110, "epsg", 3110, "AGD66 / Vicgrid66",
        "+proj=lcc +lat_1=-36 +lat_2=-38 +lat_0=-37 +lon_0=145 +x_0=2500000 +y_0=4500000 +ellps=aust_SA +units=m +no_defs"},
    {
    3111, "epsg", 3111, "GDA94 / Vicgrid94",
        "+proj=lcc +lat_1=-36 +lat_2=-38 +lat_0=-37 +lon_0=145 +x_0=2500000 +y_0=2500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3112, "epsg", 3112, "GDA94 / Geoscience Australia Lambert",
        "+proj=lcc +lat_1=-18 +lat_2=-36 +lat_0=0 +lon_0=134 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3113, "epsg", 3113, "GDA94 / BCSG02",
        "+proj=tmerc +lat_0=-28 +lon_0=153 +k=0.99999 +x_0=50000 +y_0=100000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3114, "epsg", 3114, "MAGNA-SIRGAS / Colombia Far West zone",
        "+proj=tmerc +lat_0=4.596200416666666 +lon_0=-80.07750791666666 +k=1 +x_0=1000000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3115, "epsg", 3115, "MAGNA-SIRGAS / Colombia West zone",
        "+proj=tmerc +lat_0=4.596200416666666 +lon_0=-77.07750791666666 +k=1 +x_0=1000000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3116, "epsg", 3116, "MAGNA-SIRGAS / Colombia Bogota zone",
        "+proj=tmerc +lat_0=4.596200416666666 +lon_0=-74.07750791666666 +k=1 +x_0=1000000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3117, "epsg", 3117, "MAGNA-SIRGAS / Colombia East Central zone",
        "+proj=tmerc +lat_0=4.596200416666666 +lon_0=-71.07750791666666 +k=1 +x_0=1000000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3118, "epsg", 3118, "MAGNA-SIRGAS / Colombia East zone",
        "+proj=tmerc +lat_0=4.596200416666666 +lon_0=-68.07750791666666 +k=1 +x_0=1000000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3119, "epsg", 3119, "Douala 1948 / AEF west",
        "+proj=tmerc +lat_0=0 +lon_0=10.5 +k=0.999 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=-206.1,-174.7,-87.7,0,0,0,0 +units=m +no_defs"},
    {
    3120, "epsg", 3120, "Pulkovo 1942(58) / Poland zone I",
        "+proj=sterea +lat_0=50.625 +lon_0=21.08333333333333 +k=0.9998 +x_0=4637000 +y_0=5467000 +ellps=krass +units=m +no_defs"},
    {
    3121, "epsg", 3121, "PRS92 / Philippines zone 1",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +towgs84=-127.62,-67.24,-47.04,-3.068,4.903,1.578,-1.06 +units=m +no_defs"},
    {
    3122, "epsg", 3122, "PRS92 / Philippines zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=119 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +towgs84=-127.62,-67.24,-47.04,-3.068,4.903,1.578,-1.06 +units=m +no_defs"},
    {
    3123, "epsg", 3123, "PRS92 / Philippines zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=121 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +towgs84=-127.62,-67.24,-47.04,-3.068,4.903,1.578,-1.06 +units=m +no_defs"},
    {
    3124, "epsg", 3124, "PRS92 / Philippines zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +towgs84=-127.62,-67.24,-47.04,-3.068,4.903,1.578,-1.06 +units=m +no_defs"},
    {
    3125, "epsg", 3125, "PRS92 / Philippines zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=125 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +towgs84=-127.62,-67.24,-47.04,-3.068,4.903,1.578,-1.06 +units=m +no_defs"},
    {
    3126, "epsg", 3126, "ETRS89 / ETRS-GK19FIN",
        "+proj=tmerc +lat_0=0 +lon_0=19 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3127, "epsg", 3127, "ETRS89 / ETRS-GK20FIN",
        "+proj=tmerc +lat_0=0 +lon_0=20 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3128, "epsg", 3128, "ETRS89 / ETRS-GK21FIN",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3129, "epsg", 3129, "ETRS89 / ETRS-GK22FIN",
        "+proj=tmerc +lat_0=0 +lon_0=22 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3130, "epsg", 3130, "ETRS89 / ETRS-GK23FIN",
        "+proj=tmerc +lat_0=0 +lon_0=23 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3131, "epsg", 3131, "ETRS89 / ETRS-GK24FIN",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3132, "epsg", 3132, "ETRS89 / ETRS-GK25FIN",
        "+proj=tmerc +lat_0=0 +lon_0=25 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3133, "epsg", 3133, "ETRS89 / ETRS-GK26FIN",
        "+proj=tmerc +lat_0=0 +lon_0=26 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3134, "epsg", 3134, "ETRS89 / ETRS-GK27FIN",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3135, "epsg", 3135, "ETRS89 / ETRS-GK28FIN",
        "+proj=tmerc +lat_0=0 +lon_0=28 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3136, "epsg", 3136, "ETRS89 / ETRS-GK29FIN",
        "+proj=tmerc +lat_0=0 +lon_0=29 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3137, "epsg", 3137, "ETRS89 / ETRS-GK30FIN",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3138, "epsg", 3138, "ETRS89 / ETRS-GK31FIN",
        "+proj=tmerc +lat_0=0 +lon_0=31 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3140, "epsg", 3140, "Viti Levu 1912 / Viti Levu Grid",
        "+proj=cass +lat_0=-18 +lon_0=178 +x_0=109435.392 +y_0=141622.272 +a=6378306.3696 +b=6356571.996 +towgs84=51,391,-36,0,0,0,0 +to_meter=0.201168 +no_defs"},
    {
    3141, "epsg", 3141, "Fiji 1956 / UTM zone 60S",
        "+proj=utm +zone=60 +south +ellps=intl +towgs84=265.025,384.929,-194.046,0,0,0,0 +units=m +no_defs"},
    {
    3142, "epsg", 3142, "Fiji 1956 / UTM zone 1S",
        "+proj=utm +zone=1 +south +ellps=intl +towgs84=265.025,384.929,-194.046,0,0,0,0 +units=m +no_defs"},
    {
    3143, "epsg", 3143, "Fiji 1986 / Fiji Map Grid (deprecated)",
        "+proj=tmerc +lat_0=-17 +lon_0=178.75 +k=0.99985 +x_0=2000000 +y_0=4000000 +ellps=WGS72 +units=m +no_defs"},
    {
    3146, "epsg", 3146, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=6500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3147, "epsg", 3147, "Pulkovo 1942 / 3-degree Gauss-Kruger CM 18E",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3148, "epsg", 3148, "Indian 1960 / UTM zone 48N",
        "+proj=utm +zone=48 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    3149, "epsg", 3149, "Indian 1960 / UTM zone 49N",
        "+proj=utm +zone=49 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    3150, "epsg", 3150, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=6500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    3151, "epsg", 3151, "Pulkovo 1995 / 3-degree Gauss-Kruger CM 18E",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    3152, "epsg", 3152, "ST74",
        "+proj=tmerc +lat_0=0 +lon_0=18.05779 +k=0.99999425 +x_0=100178.1808 +y_0=-6500614.7836 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3153, "epsg", 3153, "NAD83(CSRS) / BC Albers",
        "+proj=aea +lat_1=50 +lat_2=58.5 +lat_0=45 +lon_0=-126 +x_0=1000000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3154, "epsg", 3154, "NAD83(CSRS) / UTM zone 7N",
        "+proj=utm +zone=7 +ellps=GRS80 +units=m +no_defs"},
    {
    3155, "epsg", 3155, "NAD83(CSRS) / UTM zone 8N",
        "+proj=utm +zone=8 +ellps=GRS80 +units=m +no_defs"},
    {
    3156, "epsg", 3156, "NAD83(CSRS) / UTM zone 9N",
        "+proj=utm +zone=9 +ellps=GRS80 +units=m +no_defs"},
    {
    3157, "epsg", 3157, "NAD83(CSRS) / UTM zone 10N",
        "+proj=utm +zone=10 +ellps=GRS80 +units=m +no_defs"},
    {
    3158, "epsg", 3158, "NAD83(CSRS) / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=GRS80 +units=m +no_defs"},
    {
    3159, "epsg", 3159, "NAD83(CSRS) / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=GRS80 +units=m +no_defs"},
    {
    3160, "epsg", 3160, "NAD83(CSRS) / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=GRS80 +units=m +no_defs"},
    {
    3161, "epsg", 3161, "NAD83 / Ontario MNR Lambert",
        "+proj=lcc +lat_1=44.5 +lat_2=53.5 +lat_0=0 +lon_0=-85 +x_0=930000 +y_0=6430000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3162, "epsg", 3162, "NAD83(CSRS) / Ontario MNR Lambert",
        "+proj=lcc +lat_1=44.5 +lat_2=53.5 +lat_0=0 +lon_0=-85 +x_0=930000 +y_0=6430000 +ellps=GRS80 +units=m +no_defs"},
    {
    3163, "epsg", 3163, "RGNC91-93 / Lambert New Caledonia",
        "+proj=lcc +lat_1=-20.66666666666667 +lat_2=-22.33333333333333 +lat_0=-21.5 +lon_0=166 +x_0=400000 +y_0=300000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3164, "epsg", 3164, "ST87 Ouvea / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=WGS84 +towgs84=-56.263,16.136,-22.856,0,0,0,0 +units=m +no_defs"},
    {
    3165, "epsg", 3165, "NEA74 Noumea / Noumea Lambert",
        "+proj=lcc +lat_1=-22.24469175 +lat_2=-22.29469175 +lat_0=-22.26969175 +lon_0=166.44242575 +x_0=0.66 +y_0=1.02 +ellps=intl +units=m +no_defs"},
    {
    3166, "epsg", 3166, "NEA74 Noumea / Noumea Lambert 2",
        "+proj=lcc +lat_1=-22.24472222222222 +lat_2=-22.29472222222222 +lat_0=-22.26972222222222 +lon_0=166.4425 +x_0=8.313000000000001 +y_0=-2.354 +ellps=intl +units=m +no_defs"},
    {
    3167, "epsg", 3167, "Kertau (RSO) / RSO Malaya (ch)",
        "+proj=omerc +lat_0=4 +lonc=102.25 +alpha=323.0257905 +k=0.99984 +x_0=40000 +y_0=0 +a=6377295.664 +b=6356094.667915204 +to_meter=20.116756 +no_defs"},
    {
    3168, "epsg", 3168, "Kertau (RSO) / RSO Malaya (m)",
        "+proj=omerc +lat_0=4 +lonc=102.25 +alpha=323.0257905 +k=0.99984 +x_0=804670.24 +y_0=0 +a=6377295.664 +b=6356094.667915204 +units=m +no_defs"},
    {
    3169, "epsg", 3169, "RGNC91-93 / UTM zone 57S",
        "+proj=utm +zone=57 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3170, "epsg", 3170, "RGNC91-93 / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3171, "epsg", 3171, "RGNC91-93 / UTM zone 59S",
        "+proj=utm +zone=59 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3172, "epsg", 3172, "IGN53 Mare / UTM zone 59S",
        "+proj=utm +zone=59 +south +ellps=intl +units=m +no_defs"},
    {
    3174, "epsg", 3174, "NAD83 / Great Lakes Albers",
        "+proj=aea +lat_1=42.122774 +lat_2=49.01518 +lat_0=45.568977 +lon_0=-84.455955 +x_0=1000000 +y_0=1000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3175, "epsg", 3175, "NAD83 / Great Lakes and St Lawrence Albers",
        "+proj=aea +lat_1=42.122774 +lat_2=49.01518 +lat_0=45.568977 +lon_0=-83.248627 +x_0=1000000 +y_0=1000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3176, "epsg", 3176, "Indian 1960 / TM 106 NE",
        "+proj=tmerc +lat_0=0 +lon_0=106 +k=0.9996 +x_0=500000 +y_0=0 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    3177, "epsg", 3177, "LGD2006 / Libya TM",
        "+proj=tmerc +lat_0=0 +lon_0=17 +k=0.9965000000000001 +x_0=1000000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3178, "epsg", 3178, "GR96 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3179, "epsg", 3179, "GR96 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3180, "epsg", 3180, "GR96 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3181, "epsg", 3181, "GR96 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3182, "epsg", 3182, "GR96 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3183, "epsg", 3183, "GR96 / UTM zone 23N",
        "+proj=utm +zone=23 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3184, "epsg", 3184, "GR96 / UTM zone 24N",
        "+proj=utm +zone=24 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3185, "epsg", 3185, "GR96 / UTM zone 25N",
        "+proj=utm +zone=25 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3186, "epsg", 3186, "GR96 / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3187, "epsg", 3187, "GR96 / UTM zone 27N",
        "+proj=utm +zone=27 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3188, "epsg", 3188, "GR96 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3189, "epsg", 3189, "GR96 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3190, "epsg", 3190, "LGD2006 / Libya TM zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3191, "epsg", 3191, "LGD2006 / Libya TM zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=11 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3192, "epsg", 3192, "LGD2006 / Libya TM zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=13 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3193, "epsg", 3193, "LGD2006 / Libya TM zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3194, "epsg", 3194, "LGD2006 / Libya TM zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=17 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3195, "epsg", 3195, "LGD2006 / Libya TM zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=19 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3196, "epsg", 3196, "LGD2006 / Libya TM zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3197, "epsg", 3197, "LGD2006 / Libya TM zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=23 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3198, "epsg", 3198, "LGD2006 / Libya TM zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=25 +k=0.99995 +x_0=200000 +y_0=0 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3199, "epsg", 3199, "LGD2006 / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3200, "epsg", 3200, "FD58 / Iraq zone",
        "+proj=lcc +lat_1=32.5 +lat_0=32.5 +lon_0=45 +k_0=0.9987864078000001 +x_0=1500000 +y_0=1166200 +ellps=clrk80 +units=m +no_defs"},
    {
    3201, "epsg", 3201, "LGD2006 / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3202, "epsg", 3202, "LGD2006 / UTM zone 34N",
        "+proj=utm +zone=34 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3203, "epsg", 3203, "LGD2006 / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=intl +towgs84=-208.406,-109.878,-2.5764,0,0,0,0 +units=m +no_defs"},
    {
    3204, "epsg", 3204, "WGS 84 / SCAR IMW SP19-20",
        "+proj=lcc +lat_1=-60.66666666666666 +lat_2=-63.33333333333334 +lat_0=-90 +lon_0=-66 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3205, "epsg", 3205, "WGS 84 / SCAR IMW SP21-22",
        "+proj=lcc +lat_1=-60.66666666666666 +lat_2=-63.33333333333334 +lat_0=-90 +lon_0=-54 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3206, "epsg", 3206, "WGS 84 / SCAR IMW SP23-24",
        "+proj=lcc +lat_1=-60.66666666666666 +lat_2=-63.33333333333334 +lat_0=-90 +lon_0=-42 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3207, "epsg", 3207, "WGS 84 / SCAR IMW SQ01-02",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=-174 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3208, "epsg", 3208, "WGS 84 / SCAR IMW SQ19-20",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=-66 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3209, "epsg", 3209, "WGS 84 / SCAR IMW SQ21-22",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=-54 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3210, "epsg", 3210, "WGS 84 / SCAR IMW SQ37-38",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=42 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3211, "epsg", 3211, "WGS 84 / SCAR IMW SQ39-40",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=54 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3212, "epsg", 3212, "WGS 84 / SCAR IMW SQ41-42",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=66 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3213, "epsg", 3213, "WGS 84 / SCAR IMW SQ43-44",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=78 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3214, "epsg", 3214, "WGS 84 / SCAR IMW SQ45-46",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=90 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3215, "epsg", 3215, "WGS 84 / SCAR IMW SQ47-48",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=102 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3216, "epsg", 3216, "WGS 84 / SCAR IMW SQ49-50",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=114 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3217, "epsg", 3217, "WGS 84 / SCAR IMW SQ51-52",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=126 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3218, "epsg", 3218, "WGS 84 / SCAR IMW SQ53-54",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=138 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3219, "epsg", 3219, "WGS 84 / SCAR IMW SQ55-56",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=150 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3220, "epsg", 3220, "WGS 84 / SCAR IMW SQ57-58",
        "+proj=lcc +lat_1=-64.66666666666667 +lat_2=-67.33333333333333 +lat_0=-90 +lon_0=162 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3221, "epsg", 3221, "WGS 84 / SCAR IMW SR13-14",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=-102 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3222, "epsg", 3222, "WGS 84 / SCAR IMW SR15-16",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=-90 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3223, "epsg", 3223, "WGS 84 / SCAR IMW SR17-18",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=-78 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3224, "epsg", 3224, "WGS 84 / SCAR IMW SR19-20",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=-66 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3225, "epsg", 3225, "WGS 84 / SCAR IMW SR27-28",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=-18 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3226, "epsg", 3226, "WGS 84 / SCAR IMW SR29-30",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=-6 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3227, "epsg", 3227, "WGS 84 / SCAR IMW SR31-32",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=6 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3228, "epsg", 3228, "WGS 84 / SCAR IMW SR33-34",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=18 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3229, "epsg", 3229, "WGS 84 / SCAR IMW SR35-36",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=30 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3230, "epsg", 3230, "WGS 84 / SCAR IMW SR37-38",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=42 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3231, "epsg", 3231, "WGS 84 / SCAR IMW SR39-40",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=54 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3232, "epsg", 3232, "WGS 84 / SCAR IMW SR41-42",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=66 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3233, "epsg", 3233, "WGS 84 / SCAR IMW SR43-44",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=78 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3234, "epsg", 3234, "WGS 84 / SCAR IMW SR45-46",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=90 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3235, "epsg", 3235, "WGS 84 / SCAR IMW SR47-48",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=102 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3236, "epsg", 3236, "WGS 84 / SCAR IMW SR49-50",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=114 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3237, "epsg", 3237, "WGS 84 / SCAR IMW SR51-52",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=126 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3238, "epsg", 3238, "WGS 84 / SCAR IMW SR53-54",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=138 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3239, "epsg", 3239, "WGS 84 / SCAR IMW SR55-56",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=150 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3240, "epsg", 3240, "WGS 84 / SCAR IMW SR57-58",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=162 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3241, "epsg", 3241, "WGS 84 / SCAR IMW SR59-60",
        "+proj=lcc +lat_1=-68.66666666666667 +lat_2=-71.33333333333333 +lat_0=-90 +lon_0=174 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3242, "epsg", 3242, "WGS 84 / SCAR IMW SS04-06",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=-153 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3243, "epsg", 3243, "WGS 84 / SCAR IMW SS07-09",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=-135 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3244, "epsg", 3244, "WGS 84 / SCAR IMW SS10-12",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=-117 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3245, "epsg", 3245, "WGS 84 / SCAR IMW SS13-15",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=-99 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3246, "epsg", 3246, "WGS 84 / SCAR IMW SS16-18",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=-81 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3247, "epsg", 3247, "WGS 84 / SCAR IMW SS19-21",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=-63 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3248, "epsg", 3248, "WGS 84 / SCAR IMW SS25-27",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=-27 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3249, "epsg", 3249, "WGS 84 / SCAR IMW SS28-30",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=-9 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3250, "epsg", 3250, "WGS 84 / SCAR IMW SS31-33",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=9 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3251, "epsg", 3251, "WGS 84 / SCAR IMW SS34-36",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=27 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3252, "epsg", 3252, "WGS 84 / SCAR IMW SS37-39",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=45 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3253, "epsg", 3253, "WGS 84 / SCAR IMW SS40-42",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=63 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3254, "epsg", 3254, "WGS 84 / SCAR IMW SS43-45",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=81 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3255, "epsg", 3255, "WGS 84 / SCAR IMW SS46-48",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=99 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3256, "epsg", 3256, "WGS 84 / SCAR IMW SS49-51",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=117 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3257, "epsg", 3257, "WGS 84 / SCAR IMW SS52-54",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=135 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3258, "epsg", 3258, "WGS 84 / SCAR IMW SS55-57",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=153 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3259, "epsg", 3259, "WGS 84 / SCAR IMW SS58-60",
        "+proj=lcc +lat_1=-72.66666666666667 +lat_2=-75.33333333333333 +lat_0=-90 +lon_0=171 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3260, "epsg", 3260, "WGS 84 / SCAR IMW ST01-04",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=-168 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3261, "epsg", 3261, "WGS 84 / SCAR IMW ST05-08",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=-144 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3262, "epsg", 3262, "WGS 84 / SCAR IMW ST09-12",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=-120 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3263, "epsg", 3263, "WGS 84 / SCAR IMW ST13-16",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=-96 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3264, "epsg", 3264, "WGS 84 / SCAR IMW ST17-20",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=-72 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3265, "epsg", 3265, "WGS 84 / SCAR IMW ST21-24",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=-48 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3266, "epsg", 3266, "WGS 84 / SCAR IMW ST25-28",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=-24 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3267, "epsg", 3267, "WGS 84 / SCAR IMW ST29-32",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=0 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3268, "epsg", 3268, "WGS 84 / SCAR IMW ST33-36",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=24 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3269, "epsg", 3269, "WGS 84 / SCAR IMW ST37-40",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=48 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3270, "epsg", 3270, "WGS 84 / SCAR IMW ST41-44",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=72 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3271, "epsg", 3271, "WGS 84 / SCAR IMW ST45-48",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=96 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3272, "epsg", 3272, "WGS 84 / SCAR IMW ST49-52",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=120 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3273, "epsg", 3273, "WGS 84 / SCAR IMW ST53-56",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=144 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3274, "epsg", 3274, "WGS 84 / SCAR IMW ST57-60",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=168 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3275, "epsg", 3275, "WGS 84 / SCAR IMW SU01-05",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-165 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3276, "epsg", 3276, "WGS 84 / SCAR IMW SU06-10",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-135 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3277, "epsg", 3277, "WGS 84 / SCAR IMW SU11-15",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-105 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3278, "epsg", 3278, "WGS 84 / SCAR IMW SU16-20",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-75 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3279, "epsg", 3279, "WGS 84 / SCAR IMW SU21-25",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-45 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3280, "epsg", 3280, "WGS 84 / SCAR IMW SU26-30",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-15 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3281, "epsg", 3281, "WGS 84 / SCAR IMW SU31-35",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=15 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3282, "epsg", 3282, "WGS 84 / SCAR IMW SU36-40",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=45 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3283, "epsg", 3283, "WGS 84 / SCAR IMW SU41-45",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=75 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3284, "epsg", 3284, "WGS 84 / SCAR IMW SU46-50",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=105 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3285, "epsg", 3285, "WGS 84 / SCAR IMW SU51-55",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=135 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3286, "epsg", 3286, "WGS 84 / SCAR IMW SU56-60",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=165 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3287, "epsg", 3287, "WGS 84 / SCAR IMW SV01-10",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-150 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3288, "epsg", 3288, "WGS 84 / SCAR IMW SV11-20",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-90 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3289, "epsg", 3289, "WGS 84 / SCAR IMW SV21-30",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=-30 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3290, "epsg", 3290, "WGS 84 / SCAR IMW SV31-40",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=30 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3291, "epsg", 3291, "WGS 84 / SCAR IMW SV41-50",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=90 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3292, "epsg", 3292, "WGS 84 / SCAR IMW SV51-60",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=150 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3293, "epsg", 3293, "WGS 84 / SCAR IMW SW01-60",
        "+proj=stere +lat_0=-90 +lat_ts=-80.23861111111111 +lon_0=0 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3294, "epsg", 3294, "WGS 84 / USGS Transantarctic Mountains",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-78 +lon_0=162 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3296, "epsg", 3296, "RGPF / UTM zone 5S",
        "+proj=utm +zone=5 +south +ellps=GRS80 +units=m +no_defs"},
    {
    3297, "epsg", 3297, "RGPF / UTM zone 6S",
        "+proj=utm +zone=6 +south +ellps=GRS80 +units=m +no_defs"},
    {
    3298, "epsg", 3298, "RGPF / UTM zone 7S",
        "+proj=utm +zone=7 +south +ellps=GRS80 +units=m +no_defs"},
    {
    3299, "epsg", 3299, "RGPF / UTM zone 8S",
        "+proj=utm +zone=8 +south +ellps=GRS80 +units=m +no_defs"},
    {
    3300, "epsg", 3300, "Estonian Coordinate System of 1992",
        "+proj=lcc +lat_1=59.33333333333334 +lat_2=58 +lat_0=57.51755393055556 +lon_0=24 +x_0=500000 +y_0=6375000 +ellps=GRS80 +towgs84=0.055,-0.541,-0.185,0.0183,-0.0003,-0.007,-0.014 +units=m +no_defs"},
    {
    3301, "epsg", 3301, "Estonian Coordinate System of 1997",
        "+proj=lcc +lat_1=59.33333333333334 +lat_2=58 +lat_0=57.51755393055556 +lon_0=24 +x_0=500000 +y_0=6375000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3302, "epsg", 3302, "IGN63 Hiva Oa / UTM zone 7S",
        "+proj=utm +zone=7 +south +ellps=intl +units=m +no_defs"},
    {
    3303, "epsg", 3303, "Fatu Iva 72 / UTM zone 7S",
        "+proj=utm +zone=7 +south +ellps=intl +towgs84=347.103,1078.12,2623.92,-33.8875,70.6773,-9.3943,186.074 +units=m +no_defs"},
    {
    3304, "epsg", 3304, "Tahiti 79 / UTM zone 6S",
        "+proj=utm +zone=6 +south +ellps=intl +units=m +no_defs"},
    {
    3305, "epsg", 3305, "Moorea 87 / UTM zone 6S",
        "+proj=utm +zone=6 +south +ellps=intl +towgs84=215.525,149.593,176.229,-3.2624,-1.692,-1.1571,10.4773 +units=m +no_defs"},
    {
    3306, "epsg", 3306, "Maupiti 83 / UTM zone 5S",
        "+proj=utm +zone=5 +south +ellps=intl +towgs84=217.037,86.959,23.956,0,0,0,0 +units=m +no_defs"},
    {
    3307, "epsg", 3307, "Nakhl-e Ghanem / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=WGS84 +towgs84=0,-0.15,0.68,0,0,0,0 +units=m +no_defs"},
    {
    3308, "epsg", 3308, "GDA94 / NSW Lambert",
        "+proj=lcc +lat_1=-30.75 +lat_2=-35.75 +lat_0=-33.25 +lon_0=147 +x_0=9300000 +y_0=4500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3309, "epsg", 3309, "NAD27 / California Albers",
        "+proj=aea +lat_1=34 +lat_2=40.5 +lat_0=0 +lon_0=-120 +x_0=0 +y_0=-4000000 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3310, "epsg", 3310, "NAD83 / California Albers",
        "+proj=aea +lat_1=34 +lat_2=40.5 +lat_0=0 +lon_0=-120 +x_0=0 +y_0=-4000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3311, "epsg", 3311, "NAD83(HARN) / California Albers",
        "+proj=aea +lat_1=34 +lat_2=40.5 +lat_0=0 +lon_0=-120 +x_0=0 +y_0=-4000000 +ellps=GRS80 +units=m +no_defs"},
    {
    3312, "epsg", 3312, "CSG67 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=intl +towgs84=-186,230,110,0,0,0,0 +units=m +no_defs"},
    {
    3313, "epsg", 3313, "RGFG95 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=GRS80 +towgs84=2,2,-2,0,0,0,0 +units=m +no_defs"},
    {
    3314, "epsg", 3314, "Katanga 1955 / Katanga Lambert (deprecated)",
        "+proj=lcc +lat_1=-6.5 +lat_2=-11.5 +lat_0=0 +lon_0=26 +x_0=0 +y_0=0 +ellps=clrk66 +towgs84=-103.746,-9.614,-255.95,0,0,0,0 +units=m +no_defs"},
    {
    3315, "epsg", 3315, "Katanga 1955 / Katanga TM (deprecated)",
        "+proj=tmerc +lat_0=-9 +lon_0=26 +k=0.9998 +x_0=0 +y_0=0 +ellps=clrk66 +towgs84=-103.746,-9.614,-255.95,0,0,0,0 +units=m +no_defs"},
    {
    3316, "epsg", 3316, "Kasai 1953 / Congo TM zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=22 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3317, "epsg", 3317, "Kasai 1953 / Congo TM zone 24",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3318, "epsg", 3318, "IGC 1962 / Congo TM zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3319, "epsg", 3319, "IGC 1962 / Congo TM zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=14 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3320, "epsg", 3320, "IGC 1962 / Congo TM zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=16 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3321, "epsg", 3321, "IGC 1962 / Congo TM zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3322, "epsg", 3322, "IGC 1962 / Congo TM zone 20",
        "+proj=tmerc +lat_0=0 +lon_0=20 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3323, "epsg", 3323, "IGC 1962 / Congo TM zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=22 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3324, "epsg", 3324, "IGC 1962 / Congo TM zone 24",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3325, "epsg", 3325, "IGC 1962 / Congo TM zone 26",
        "+proj=tmerc +lat_0=0 +lon_0=26 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3326, "epsg", 3326, "IGC 1962 / Congo TM zone 28",
        "+proj=tmerc +lat_0=0 +lon_0=28 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3327, "epsg", 3327, "IGC 1962 / Congo TM zone 30",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    3328, "epsg", 3328, "Pulkovo 1942(58) / GUGiK-80",
        "+proj=sterea +lat_0=52.16666666666666 +lon_0=19.16666666666667 +k=0.999714 +x_0=500000 +y_0=500000 +ellps=krass +units=m +no_defs"},
    {
    3329, "epsg", 3329, "Pulkovo 1942(58) / 3-degree Gauss-Kruger zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=5500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3330, "epsg", 3330, "Pulkovo 1942(58) / 3-degree Gauss-Kruger zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=6500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3331, "epsg", 3331, "Pulkovo 1942(58) / 3-degree Gauss-Kruger zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=7500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3332, "epsg", 3332, "Pulkovo 1942(58) / 3-degree Gauss-Kruger zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=1 +x_0=8500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3333, "epsg", 3333, "Pulkovo 1942(58) / Gauss-Kruger zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=3500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3334, "epsg", 3334, "Pulkovo 1942(58) / Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3335, "epsg", 3335, "Pulkovo 1942(58) / Gauss-Kruger zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=5500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3336, "epsg", 3336, "IGN 1962 Kerguelen / UTM zone 42S",
        "+proj=utm +zone=42 +south +ellps=intl +towgs84=145,-187,103,0,0,0,0 +units=m +no_defs"},
    {
    3337, "epsg", 3337, "Le Pouce 1934 / Mauritius Grid",
        "+proj=lcc +lat_1=-20.19506944444445 +lat_0=-20.19506944444445 +lon_0=57.52182777777778 +k_0=1 +x_0=1000000 +y_0=1000000 +ellps=clrk80 +towgs84=-770.1,158.4,-498.2,0,0,0,0 +units=m +no_defs"},
    {
    3338, "epsg", 3338, "NAD83 / Alaska Albers",
        "+proj=aea +lat_1=55 +lat_2=65 +lat_0=50 +lon_0=-154 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3339, "epsg", 3339, "IGCB 1955 / Congo TM zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +towgs84=-79.9,-158,-168.9,0,0,0,0 +units=m +no_defs"},
    {
    3340, "epsg", 3340, "IGCB 1955 / Congo TM zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=14 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +towgs84=-79.9,-158,-168.9,0,0,0,0 +units=m +no_defs"},
    {
    3341, "epsg", 3341, "IGCB 1955 / Congo TM zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=16 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=clrk80 +towgs84=-79.9,-158,-168.9,0,0,0,0 +units=m +no_defs"},
    {
    3342, "epsg", 3342, "IGCB 1955 / UTM zone 33S",
        "+proj=utm +zone=33 +south +ellps=clrk80 +towgs84=-79.9,-158,-168.9,0,0,0,0 +units=m +no_defs"},
    {
    3343, "epsg", 3343, "Mauritania 1999 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3344, "epsg", 3344, "Mauritania 1999 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3345, "epsg", 3345, "Mauritania 1999 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3346, "epsg", 3346, "LKS94 / Lithuania TM",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9998 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3347, "epsg", 3347, "NAD83 / Statistics Canada Lambert",
        "+proj=lcc +lat_1=49 +lat_2=77 +lat_0=63.390675 +lon_0=-91.86666666666666 +x_0=6200000 +y_0=3000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3348, "epsg", 3348, "NAD83(CSRS) / Statistics Canada Lambert",
        "+proj=lcc +lat_1=49 +lat_2=77 +lat_0=63.390675 +lon_0=-91.86666666666666 +x_0=6200000 +y_0=3000000 +ellps=GRS80 +units=m +no_defs"},
    {
    3349, "epsg", 3349, "WGS 84 / PDC Mercator (deprecated)",
        "+proj=merc +lon_0=-150 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3350, "epsg", 3350, "Pulkovo 1942 / CS63 zone C0",
        "+proj=tmerc +lat_0=0.1 +lon_0=21.95 +k=1 +x_0=250000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3351, "epsg", 3351, "Pulkovo 1942 / CS63 zone C1",
        "+proj=tmerc +lat_0=0.1 +lon_0=24.95 +k=1 +x_0=1250000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3352, "epsg", 3352, "Pulkovo 1942 / CS63 zone C2",
        "+proj=tmerc +lat_0=0.1 +lon_0=27.95 +k=1 +x_0=2250000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3353, "epsg", 3353, "Mhast (onshore) / UTM zone 32S",
        "+proj=utm +zone=32 +south +ellps=intl +units=m +no_defs"},
    {
    3354, "epsg", 3354, "Mhast (offshore) / UTM zone 32S",
        "+proj=utm +zone=32 +south +ellps=intl +units=m +no_defs"},
    {
    3355, "epsg", 3355, "Egypt Gulf of Suez S-650 TL / Red Belt",
        "+proj=tmerc +lat_0=30 +lon_0=31 +k=1 +x_0=615000 +y_0=810000 +ellps=helmert +towgs84=-146.21,112.63,4.05,0,0,0,0 +units=m +no_defs"},
    {
    3356, "epsg", 3356, "Grand Cayman 1959 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=clrk66 +towgs84=67.8,106.1,138.8,0,0,0,0 +units=m +no_defs"},
    {
    3357, "epsg", 3357, "Little Cayman 1961 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=clrk66 +units=m +no_defs"},
    {
    3358, "epsg", 3358, "NAD83(HARN) / North Carolina",
        "+proj=lcc +lat_1=36.16666666666666 +lat_2=34.33333333333334 +lat_0=33.75 +lon_0=-79 +x_0=609601.22 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3359, "epsg", 3359, "NAD83(HARN) / North Carolina (ftUS) (deprecated)",
        "+proj=lcc +lat_1=36.16666666666666 +lat_2=34.33333333333334 +lat_0=33.75 +lon_0=-79 +x_0=609601.2192024385 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    3360, "epsg", 3360, "NAD83(HARN) / South Carolina",
        "+proj=lcc +lat_1=34.83333333333334 +lat_2=32.5 +lat_0=31.83333333333333 +lon_0=-81 +x_0=609600 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3361, "epsg", 3361, "NAD83(HARN) / South Carolina (ft)",
        "+proj=lcc +lat_1=34.83333333333334 +lat_2=32.5 +lat_0=31.83333333333333 +lon_0=-81 +x_0=609600 +y_0=0 +ellps=GRS80 +units=ft +no_defs"},
    {
    3362, "epsg", 3362, "NAD83(HARN) / Pennsylvania North",
        "+proj=lcc +lat_1=41.95 +lat_2=40.88333333333333 +lat_0=40.16666666666666 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3363, "epsg", 3363, "NAD83(HARN) / Pennsylvania North (ftUS)",
        "+proj=lcc +lat_1=41.95 +lat_2=40.88333333333333 +lat_0=40.16666666666666 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3364, "epsg", 3364, "NAD83(HARN) / Pennsylvania South",
        "+proj=lcc +lat_1=40.96666666666667 +lat_2=39.93333333333333 +lat_0=39.33333333333334 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3365, "epsg", 3365, "NAD83(HARN) / Pennsylvania South (ftUS)",
        "+proj=lcc +lat_1=40.96666666666667 +lat_2=39.93333333333333 +lat_0=39.33333333333334 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3366, "epsg", 3366, "Hong Kong 1963 Grid System (deprecated)",
        "+proj=cass +lat_0=22.31213333333334 +lon_0=114.1785555555556 +x_0=40243.57775604237 +y_0=19069.93351512578 +a=6378293.645208759 +b=6356617.987679838 +units=m +no_defs"},
    {
    3367, "epsg", 3367, "IGN Astro 1960 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=clrk80 +units=m +no_defs"},
    {
    3368, "epsg", 3368, "IGN Astro 1960 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=clrk80 +units=m +no_defs"},
    {
    3369, "epsg", 3369, "IGN Astro 1960 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=clrk80 +units=m +no_defs"},
    {
    3370, "epsg", 3370, "NAD27 / UTM zone 59N",
        "+proj=utm +zone=59 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3371, "epsg", 3371, "NAD27 / UTM zone 60N",
        "+proj=utm +zone=60 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3372, "epsg", 3372, "NAD83 / UTM zone 59N",
        "+proj=utm +zone=59 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3373, "epsg", 3373, "NAD83 / UTM zone 60N",
        "+proj=utm +zone=60 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3374, "epsg", 3374, "FD54 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=intl +units=m +no_defs"},
    {
    3375, "epsg", 3375, "GDM2000 / Peninsula RSO",
        "+proj=omerc +lat_0=4 +lonc=102.25 +alpha=323.0257964666666 +k=0.99984 +x_0=804671 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3376, "epsg", 3376, "GDM2000 / East Malaysia BRSO",
        "+proj=omerc +lat_0=4 +lonc=115 +alpha=53.31580995 +k=0.99984 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3377, "epsg", 3377, "GDM2000 / Johor Grid",
        "+proj=cass +lat_0=2.121679744444445 +lon_0=103.4279362361111 +x_0=-14810.562 +y_0=8758.32 +ellps=GRS80 +units=m +no_defs"},
    {
    3378, "epsg", 3378, "GDM2000 / Sembilan and Melaka Grid",
        "+proj=cass +lat_0=2.682347636111111 +lon_0=101.9749050416667 +x_0=3673.785 +y_0=-4240.573 +ellps=GRS80 +units=m +no_defs"},
    {
    3379, "epsg", 3379, "GDM2000 / PahangGrid",
        "+proj=cass +lat_0=3.769388088888889 +lon_0=102.3682989833333 +x_0=-7368.228 +y_0=6485.858 +ellps=GRS80 +units=m +no_defs"},
    {
    3380, "epsg", 3380, "GDM2000 / Selangor Grid",
        "+proj=cass +lat_0=3.68464905 +lon_0=101.3891079138889 +x_0=-34836.161 +y_0=56464.049 +ellps=GRS80 +units=m +no_defs"},
    {
    3381, "epsg", 3381, "GDM2000 / Terengganu Grid",
        "+proj=cass +lat_0=4.9762852 +lon_0=103.070275625 +x_0=19594.245 +y_0=3371.895 +ellps=GRS80 +units=m +no_defs"},
    {
    3382, "epsg", 3382, "GDM2000 / Pinang Grid",
        "+proj=cass +lat_0=5.421517541666667 +lon_0=100.3443769638889 +x_0=-23.414 +y_0=62.283 +ellps=GRS80 +units=m +no_defs"},
    {
    3383, "epsg", 3383, "GDM2000 / Kedah and Perlis Grid",
        "+proj=cass +lat_0=5.964672713888889 +lon_0=100.6363711111111 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3384, "epsg", 3384, "GDM2000 / Perak Grid",
        "+proj=cass +lat_0=4.859063022222222 +lon_0=100.8154105861111 +x_0=-1.769 +y_0=133454.779 +ellps=GRS80 +units=m +no_defs"},
    {
    3385, "epsg", 3385, "GDM2000 / Kelantan Grid",
        "+proj=cass +lat_0=5.972543658333334 +lon_0=102.2952416694444 +x_0=13227.851 +y_0=8739.894 +ellps=GRS80 +units=m +no_defs"},
    {
    3386, "epsg", 3386, "KKJ / Finland zone 0",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    3387, "epsg", 3387, "KKJ / Finland zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=5500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    3388, "epsg", 3388, "Pulkovo 1942 / Caspian Sea Mercator",
        "+proj=merc +lon_0=51 +k=1 +x_0=0 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3389, "epsg", 3389, "Pulkovo 1942 / 3-degree Gauss-Kruger zone 60",
        "+proj=tmerc +lat_0=0 +lon_0=180 +k=1 +x_0=60500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3390, "epsg", 3390, "Pulkovo 1995 / 3-degree Gauss-Kruger zone 60",
        "+proj=tmerc +lat_0=0 +lon_0=180 +k=1 +x_0=60500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    3391, "epsg", 3391, "Karbala 1979 / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=clrk80 +towgs84=84.1,-320.1,218.7,0,0,0,0 +units=m +no_defs"},
    {
    3392, "epsg", 3392, "Karbala 1979 / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=clrk80 +towgs84=84.1,-320.1,218.7,0,0,0,0 +units=m +no_defs"},
    {
    3393, "epsg", 3393, "Karbala 1979 / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=clrk80 +towgs84=84.1,-320.1,218.7,0,0,0,0 +units=m +no_defs"},
    {
    3394, "epsg", 3394, "Nahrwan 1934 / Iraq zone",
        "+proj=lcc +lat_1=32.5 +lat_0=32.5 +lon_0=45 +k_0=0.9987864078000001 +x_0=1500000 +y_0=1166200 +ellps=clrk80 +units=m +no_defs"},
    {
    3395, "epsg", 3395, "WGS 84 / World Mercator",
        "+proj=merc +lon_0=0 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3396, "epsg", 3396, "PD/83 / 3-degree Gauss-Kruger zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=3500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3397, "epsg", 3397, "PD/83 / 3-degree Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=1 +x_0=4500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3398, "epsg", 3398, "RD/83 / 3-degree Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=1 +x_0=4500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3399, "epsg", 3399, "RD/83 / 3-degree Gauss-Kruger zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=5500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3400, "epsg", 3400, "NAD83 / Alberta 10-TM (Forest)",
        "+proj=tmerc +lat_0=0 +lon_0=-115 +k=0.9992 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3401, "epsg", 3401, "NAD83 / Alberta 10-TM (Resource)",
        "+proj=tmerc +lat_0=0 +lon_0=-115 +k=0.9992 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3402, "epsg", 3402, "NAD83(CSRS) / Alberta 10-TM (Forest)",
        "+proj=tmerc +lat_0=0 +lon_0=-115 +k=0.9992 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3403, "epsg", 3403, "NAD83(CSRS) / Alberta 10-TM (Resource)",
        "+proj=tmerc +lat_0=0 +lon_0=-115 +k=0.9992 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3404, "epsg", 3404, "NAD83(HARN) / North Carolina (ftUS)",
        "+proj=lcc +lat_1=36.16666666666666 +lat_2=34.33333333333334 +lat_0=33.75 +lon_0=-79 +x_0=609601.2192024384 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3405, "epsg", 3405, "VN-2000 / UTM zone 48N",
        "+proj=utm +zone=48 +ellps=WGS84 +units=m +no_defs"},
    {
    3406, "epsg", 3406, "VN-2000 / UTM zone 49N",
        "+proj=utm +zone=49 +ellps=WGS84 +units=m +no_defs"},
    {
    3407, "epsg", 3407, "Hong Kong 1963 Grid System",
        "+proj=cass +lat_0=22.31213333333334 +lon_0=114.1785555555556 +x_0=40243.57775604237 +y_0=19069.93351512578 +a=6378293.645208759 +b=6356617.987679838 +to_meter=0.3047972654 +no_defs"},
    {
    3408, "epsg", 3408, "unnamed",
        "+proj=laea +lat_0=90 +lon_0=0 +x_0=0 +y_0=0 +a=6371228 +b=6371228 +units=m +no_defs"},
    {
    3409, "epsg", 3409, "unnamed",
        "+proj=laea +lat_0=-90 +lon_0=0 +x_0=0 +y_0=0 +a=6371228 +b=6371228 +units=m +no_defs"},
    {
    3410, "epsg", 3410, "NSIDC EASE-Grid Global",
        "+proj=cea +lon_0=0 +lat_ts=30 +x_0=0 +y_0=0 +a=6371228 +b=6371228 +units=m +no_defs"},
    {
    3411, "epsg", 3411, "NSIDC Sea Ice Polar Stereographic North",
        "+proj=stere +lat_0=90 +lat_ts=70 +lon_0=-45 +k=1 +x_0=0 +y_0=0 +a=6378273 +b=6356889.449 +units=m +no_defs"},
    {
    3412, "epsg", 3412, "NSIDC Sea Ice Polar Stereographic South",
        "+proj=stere +lat_0=-90 +lat_ts=-70 +lon_0=0 +k=1 +x_0=0 +y_0=0 +a=6378273 +b=6356889.449 +units=m +no_defs"},
    {
    3413, "epsg", 3413, "WGS 84 / NSIDC Sea Ice Polar Stereographic North",
        "+proj=stere +lat_0=90 +lat_ts=70 +lon_0=-45 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3414, "epsg", 3414, "SVY21 / Singapore TM",
        "+proj=tmerc +lat_0=1.366666666666667 +lon_0=103.8333333333333 +k=1 +x_0=28001.642 +y_0=38744.572 +ellps=WGS84 +units=m +no_defs"},
    {
    3415, "epsg", 3415, "WGS 72BE / South China Sea Lambert",
        "+proj=lcc +lat_1=18 +lat_2=24 +lat_0=21 +lon_0=114 +x_0=500000 +y_0=500000 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    3416, "epsg", 3416, "ETRS89 / Austria Lambert",
        "+proj=lcc +lat_1=49 +lat_2=46 +lat_0=47.5 +lon_0=13.33333333333333 +x_0=400000 +y_0=400000 +ellps=GRS80 +units=m +no_defs"},
    {
    3417, "epsg", 3417, "NAD83 / Iowa North (ft US)",
        "+proj=lcc +lat_1=43.26666666666667 +lat_2=42.06666666666667 +lat_0=41.5 +lon_0=-93.5 +x_0=1500000 +y_0=999999.9999898402 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3418, "epsg", 3418, "NAD83 / Iowa South (ft US)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.61666666666667 +lat_0=40 +lon_0=-93.5 +x_0=500000.00001016 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3419, "epsg", 3419, "NAD83 / Kansas North (ft US)",
        "+proj=lcc +lat_1=39.78333333333333 +lat_2=38.71666666666667 +lat_0=38.33333333333334 +lon_0=-98 +x_0=399999.99998984 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3420, "epsg", 3420, "NAD83 / Kansas South (ft US)",
        "+proj=lcc +lat_1=38.56666666666667 +lat_2=37.26666666666667 +lat_0=36.66666666666666 +lon_0=-98.5 +x_0=399999.99998984 +y_0=399999.99998984 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3421, "epsg", 3421, "NAD83 / Nevada East (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-115.5833333333333 +k=0.9999 +x_0=200000.00001016 +y_0=8000000.000010163 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3422, "epsg", 3422, "NAD83 / Nevada Central (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-116.6666666666667 +k=0.9999 +x_0=500000.00001016 +y_0=6000000 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3423, "epsg", 3423, "NAD83 / Nevada West (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-118.5833333333333 +k=0.9999 +x_0=800000.0000101599 +y_0=3999999.99998984 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3424, "epsg", 3424, "NAD83 / New Jersey (ft US)",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3425, "epsg", 3425, "NAD83(HARN) / Iowa North (ft US)",
        "+proj=lcc +lat_1=43.26666666666667 +lat_2=42.06666666666667 +lat_0=41.5 +lon_0=-93.5 +x_0=1500000 +y_0=999999.9999898402 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3426, "epsg", 3426, "NAD83(HARN) / Iowa South (ft US)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.61666666666667 +lat_0=40 +lon_0=-93.5 +x_0=500000.00001016 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3427, "epsg", 3427, "NAD83(HARN) / Kansas North (ft US)",
        "+proj=lcc +lat_1=39.78333333333333 +lat_2=38.71666666666667 +lat_0=38.33333333333334 +lon_0=-98 +x_0=399999.99998984 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3428, "epsg", 3428, "NAD83(HARN) / Kansas South (ft US)",
        "+proj=lcc +lat_1=38.56666666666667 +lat_2=37.26666666666667 +lat_0=36.66666666666666 +lon_0=-98.5 +x_0=399999.99998984 +y_0=399999.99998984 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3429, "epsg", 3429, "NAD83(HARN) / Nevada East (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-115.5833333333333 +k=0.9999 +x_0=200000.00001016 +y_0=8000000.000010163 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3430, "epsg", 3430, "NAD83(HARN) / Nevada Central (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-116.6666666666667 +k=0.9999 +x_0=500000.00001016 +y_0=6000000 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3431, "epsg", 3431, "NAD83(HARN) / Nevada West (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-118.5833333333333 +k=0.9999 +x_0=800000.0000101599 +y_0=3999999.99998984 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3432, "epsg", 3432, "NAD83(HARN) / New Jersey (ft US)",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3433, "epsg", 3433, "NAD83 / Arkansas North (ftUS)",
        "+proj=lcc +lat_1=36.23333333333333 +lat_2=34.93333333333333 +lat_0=34.33333333333334 +lon_0=-92 +x_0=399999.99998984 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3434, "epsg", 3434, "NAD83 / Arkansas South (ftUS)",
        "+proj=lcc +lat_1=34.76666666666667 +lat_2=33.3 +lat_0=32.66666666666666 +lon_0=-92 +x_0=399999.99998984 +y_0=399999.99998984 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3435, "epsg", 3435, "NAD83 / Illinois East (ftUS)",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-88.33333333333333 +k=0.9999749999999999 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3436, "epsg", 3436, "NAD83 / Illinois West (ftUS)",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-90.16666666666667 +k=0.999941177 +x_0=699999.9999898402 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3437, "epsg", 3437, "NAD83 / New Hampshire (ftUS)",
        "+proj=tmerc +lat_0=42.5 +lon_0=-71.66666666666667 +k=0.999966667 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3438, "epsg", 3438, "NAD83 / Rhode Island (ftUS)",
        "+proj=tmerc +lat_0=41.08333333333334 +lon_0=-71.5 +k=0.99999375 +x_0=99999.99998983997 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3439, "epsg", 3439, "PSD93 / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=clrk80 +units=m +no_defs"},
    {
    3440, "epsg", 3440, "PSD93 / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=clrk80 +units=m +no_defs"},
    {
    3441, "epsg", 3441, "NAD83(HARN) / Arkansas North (ftUS)",
        "+proj=lcc +lat_1=36.23333333333333 +lat_2=34.93333333333333 +lat_0=34.33333333333334 +lon_0=-92 +x_0=399999.99998984 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3442, "epsg", 3442, "NAD83(HARN) / Arkansas South (ftUS)",
        "+proj=lcc +lat_1=34.76666666666667 +lat_2=33.3 +lat_0=32.66666666666666 +lon_0=-92 +x_0=399999.99998984 +y_0=399999.99998984 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3443, "epsg", 3443, "NAD83(HARN) / Illinois East (ftUS)",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-88.33333333333333 +k=0.9999749999999999 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3444, "epsg", 3444, "NAD83(HARN) / Illinois West (ftUS)",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-90.16666666666667 +k=0.999941177 +x_0=699999.9999898402 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3445, "epsg", 3445, "NAD83(HARN) / New Hampshire (ftUS)",
        "+proj=tmerc +lat_0=42.5 +lon_0=-71.66666666666667 +k=0.999966667 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3446, "epsg", 3446, "NAD83(HARN) / Rhode Island (ftUS)",
        "+proj=tmerc +lat_0=41.08333333333334 +lon_0=-71.5 +k=0.99999375 +x_0=99999.99998983997 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3447, "epsg", 3447, "ETRS89 / Belgian Lambert 2005",
        "+proj=lcc +lat_1=49.83333333333334 +lat_2=51.16666666666666 +lat_0=50.797815 +lon_0=4.359215833333333 +x_0=150328 +y_0=166262 +ellps=GRS80 +units=m +no_defs"},
    {
    3448, "epsg", 3448, "JAD2001 / Jamaica Metric Grid",
        "+proj=lcc +lat_1=18 +lat_0=18 +lon_0=-77 +k_0=1 +x_0=750000 +y_0=650000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3449, "epsg", 3449, "JAD2001 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3450, "epsg", 3450, "JAD2001 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3451, "epsg", 3451, "NAD83 / Louisiana North (ftUS)",
        "+proj=lcc +lat_1=32.66666666666666 +lat_2=31.16666666666667 +lat_0=30.5 +lon_0=-92.5 +x_0=999999.9999898402 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3452, "epsg", 3452, "NAD83 / Louisiana South (ftUS)",
        "+proj=lcc +lat_1=30.7 +lat_2=29.3 +lat_0=28.5 +lon_0=-91.33333333333333 +x_0=999999.9999898402 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3453, "epsg", 3453, "NAD83 / Louisiana Offshore (ftUS)",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.5 +lon_0=-91.33333333333333 +x_0=999999.9999898402 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3454, "epsg", 3454, "NAD83 / South Dakota North (ftUS)",
        "+proj=lcc +lat_1=44.4 +lat_2=42.83333333333334 +lat_0=42.33333333333334 +lon_0=-100.3333333333333 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3455, "epsg", 3455, "NAD83 / South Dakota South (ftUS)",
        "+proj=lcc +lat_1=44.4 +lat_2=42.83333333333334 +lat_0=42.33333333333334 +lon_0=-100.3333333333333 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3456, "epsg", 3456, "NAD83(HARN) / Louisiana North (ftUS)",
        "+proj=lcc +lat_1=32.66666666666666 +lat_2=31.16666666666667 +lat_0=30.5 +lon_0=-92.5 +x_0=999999.9999898402 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3457, "epsg", 3457, "NAD83(HARN) / Louisiana South (ftUS)",
        "+proj=lcc +lat_1=30.7 +lat_2=29.3 +lat_0=28.5 +lon_0=-91.33333333333333 +x_0=999999.9999898402 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3458, "epsg", 3458, "NAD83(HARN) / South Dakota North (ftUS)",
        "+proj=lcc +lat_1=45.68333333333333 +lat_2=44.41666666666666 +lat_0=43.83333333333334 +lon_0=-100 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3459, "epsg", 3459, "NAD83(HARN) / South Dakota South (ftUS)",
        "+proj=lcc +lat_1=44.4 +lat_2=42.83333333333334 +lat_0=42.33333333333334 +lon_0=-100.3333333333333 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3460, "epsg", 3460, "Fiji 1986 / Fiji Map Grid",
        "+proj=tmerc +lat_0=-17 +lon_0=178.75 +k=0.99985 +x_0=2000000 +y_0=4000000 +ellps=WGS72 +units=m +no_defs"},
    {
    3461, "epsg", 3461, "Dabola 1981 / UTM zone 28N",
        "+proj=utm +zone=28 +a=6378249.2 +b=6356515 +towgs84=-83,37,124,0,0,0,0 +units=m +no_defs"},
    {
    3462, "epsg", 3462, "Dabola 1981 / UTM zone 29N",
        "+proj=utm +zone=29 +a=6378249.2 +b=6356515 +towgs84=-83,37,124,0,0,0,0 +units=m +no_defs"},
    {
    3463, "epsg", 3463, "NAD83 / Maine CS2000 Central",
        "+proj=tmerc +lat_0=43.5 +lon_0=-69.125 +k=0.99998 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3464, "epsg", 3464, "NAD83(HARN) / Maine CS2000 Central",
        "+proj=tmerc +lat_0=43.5 +lon_0=-69.125 +k=0.99998 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3465, "epsg", 3465, "NAD83(NSRS2007) / Alabama East",
        "+proj=tmerc +lat_0=30.5 +lon_0=-85.83333333333333 +k=0.99996 +x_0=200000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3466, "epsg", 3466, "NAD83(NSRS2007) / Alabama West",
        "+proj=tmerc +lat_0=30 +lon_0=-87.5 +k=0.999933333 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3467, "epsg", 3467, "NAD83(NSRS2007) / Alaska Albers",
        "+proj=aea +lat_1=55 +lat_2=65 +lat_0=50 +lon_0=-154 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3468, "epsg", 3468, "NAD83(NSRS2007) / Alaska zone 1",
        "+proj=omerc +lat_0=57 +lonc=-133.6666666666667 +alpha=323.1301023611111 +k=0.9999 +x_0=5000000 +y_0=-5000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3469, "epsg", 3469, "NAD83(NSRS2007) / Alaska zone 2",
        "+proj=tmerc +lat_0=54 +lon_0=-142 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3470, "epsg", 3470, "NAD83(NSRS2007) / Alaska zone 3",
        "+proj=tmerc +lat_0=54 +lon_0=-146 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3471, "epsg", 3471, "NAD83(NSRS2007) / Alaska zone 4",
        "+proj=tmerc +lat_0=54 +lon_0=-150 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3472, "epsg", 3472, "NAD83(NSRS2007) / Alaska zone 5",
        "+proj=tmerc +lat_0=54 +lon_0=-154 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3473, "epsg", 3473, "NAD83(NSRS2007) / Alaska zone 6",
        "+proj=tmerc +lat_0=54 +lon_0=-158 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3474, "epsg", 3474, "NAD83(NSRS2007) / Alaska zone 7",
        "+proj=tmerc +lat_0=54 +lon_0=-162 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3475, "epsg", 3475, "NAD83(NSRS2007) / Alaska zone 8",
        "+proj=tmerc +lat_0=54 +lon_0=-166 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3476, "epsg", 3476, "NAD83(NSRS2007) / Alaska zone 9",
        "+proj=tmerc +lat_0=54 +lon_0=-170 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3477, "epsg", 3477, "NAD83(NSRS2007) / Alaska zone 10",
        "+proj=lcc +lat_1=53.83333333333334 +lat_2=51.83333333333334 +lat_0=51 +lon_0=-176 +x_0=1000000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3478, "epsg", 3478, "NAD83(NSRS2007) / Arizona Central",
        "+proj=tmerc +lat_0=31 +lon_0=-111.9166666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3479, "epsg", 3479, "NAD83(NSRS2007) / Arizona Central (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-111.9166666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3480, "epsg", 3480, "NAD83(NSRS2007) / Arizona East",
        "+proj=tmerc +lat_0=31 +lon_0=-110.1666666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3481, "epsg", 3481, "NAD83(NSRS2007) / Arizona East (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-110.1666666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3482, "epsg", 3482, "NAD83(NSRS2007) / Arizona West",
        "+proj=tmerc +lat_0=31 +lon_0=-113.75 +k=0.999933333 +x_0=213360 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3483, "epsg", 3483, "NAD83(NSRS2007) / Arizona West (ft)",
        "+proj=tmerc +lat_0=31 +lon_0=-113.75 +k=0.999933333 +x_0=213360 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3484, "epsg", 3484, "NAD83(NSRS2007) / Arkansas North",
        "+proj=lcc +lat_1=36.23333333333333 +lat_2=34.93333333333333 +lat_0=34.33333333333334 +lon_0=-92 +x_0=400000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3485, "epsg", 3485, "NAD83(NSRS2007) / Arkansas North (ftUS)",
        "+proj=lcc +lat_1=36.23333333333333 +lat_2=34.93333333333333 +lat_0=34.33333333333334 +lon_0=-92 +x_0=399999.99998984 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3486, "epsg", 3486, "NAD83(NSRS2007) / Arkansas South",
        "+proj=lcc +lat_1=34.76666666666667 +lat_2=33.3 +lat_0=32.66666666666666 +lon_0=-92 +x_0=400000 +y_0=400000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3487, "epsg", 3487, "NAD83(NSRS2007) / Arkansas South (ftUS)",
        "+proj=lcc +lat_1=34.76666666666667 +lat_2=33.3 +lat_0=32.66666666666666 +lon_0=-92 +x_0=399999.99998984 +y_0=399999.99998984 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3488, "epsg", 3488, "NAD83(NSRS2007) / California Albers",
        "+proj=aea +lat_1=34 +lat_2=40.5 +lat_0=0 +lon_0=-120 +x_0=0 +y_0=-4000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3489, "epsg", 3489, "NAD83(NSRS2007) / California zone 1",
        "+proj=lcc +lat_1=41.66666666666666 +lat_2=40 +lat_0=39.33333333333334 +lon_0=-122 +x_0=2000000 +y_0=500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3490, "epsg", 3490, "NAD83(NSRS2007) / California zone 1 (ftUS)",
        "+proj=lcc +lat_1=41.66666666666666 +lat_2=40 +lat_0=39.33333333333334 +lon_0=-122 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3491, "epsg", 3491, "NAD83(NSRS2007) / California zone 2",
        "+proj=lcc +lat_1=39.83333333333334 +lat_2=38.33333333333334 +lat_0=37.66666666666666 +lon_0=-122 +x_0=2000000 +y_0=500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3492, "epsg", 3492, "NAD83(NSRS2007) / California zone 2 (ftUS)",
        "+proj=lcc +lat_1=39.83333333333334 +lat_2=38.33333333333334 +lat_0=37.66666666666666 +lon_0=-122 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3493, "epsg", 3493, "NAD83(NSRS2007) / California zone 3",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.06666666666667 +lat_0=36.5 +lon_0=-120.5 +x_0=2000000 +y_0=500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3494, "epsg", 3494, "NAD83(NSRS2007) / California zone 3 (ftUS)",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.06666666666667 +lat_0=36.5 +lon_0=-120.5 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3495, "epsg", 3495, "NAD83(NSRS2007) / California zone 4",
        "+proj=lcc +lat_1=37.25 +lat_2=36 +lat_0=35.33333333333334 +lon_0=-119 +x_0=2000000 +y_0=500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3496, "epsg", 3496, "NAD83(NSRS2007) / California zone 4 (ftUS)",
        "+proj=lcc +lat_1=37.25 +lat_2=36 +lat_0=35.33333333333334 +lon_0=-119 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3497, "epsg", 3497, "NAD83(NSRS2007) / California zone 5",
        "+proj=lcc +lat_1=35.46666666666667 +lat_2=34.03333333333333 +lat_0=33.5 +lon_0=-118 +x_0=2000000 +y_0=500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3498, "epsg", 3498, "NAD83(NSRS2007) / California zone 5 (ftUS)",
        "+proj=lcc +lat_1=35.46666666666667 +lat_2=34.03333333333333 +lat_0=33.5 +lon_0=-118 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3499, "epsg", 3499, "NAD83(NSRS2007) / California zone 6",
        "+proj=lcc +lat_1=33.88333333333333 +lat_2=32.78333333333333 +lat_0=32.16666666666666 +lon_0=-116.25 +x_0=2000000 +y_0=500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3500, "epsg", 3500, "NAD83(NSRS2007) / California zone 6 (ftUS)",
        "+proj=lcc +lat_1=33.88333333333333 +lat_2=32.78333333333333 +lat_0=32.16666666666666 +lon_0=-116.25 +x_0=2000000.0001016 +y_0=500000.0001016001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3501, "epsg", 3501, "NAD83(NSRS2007) / Colorado Central",
        "+proj=lcc +lat_1=39.75 +lat_2=38.45 +lat_0=37.83333333333334 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3502, "epsg", 3502, "NAD83(NSRS2007) / Colorado Central (ftUS)",
        "+proj=lcc +lat_1=39.75 +lat_2=38.45 +lat_0=37.83333333333334 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3503, "epsg", 3503, "NAD83(NSRS2007) / Colorado North",
        "+proj=lcc +lat_1=40.78333333333333 +lat_2=39.71666666666667 +lat_0=39.33333333333334 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3504, "epsg", 3504, "NAD83(NSRS2007) / Colorado North (ftUS)",
        "+proj=lcc +lat_1=40.78333333333333 +lat_2=39.71666666666667 +lat_0=39.33333333333334 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3505, "epsg", 3505, "NAD83(NSRS2007) / Colorado South",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.23333333333333 +lat_0=36.66666666666666 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3506, "epsg", 3506, "NAD83(NSRS2007) / Colorado South (ftUS)",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.23333333333333 +lat_0=36.66666666666666 +lon_0=-105.5 +x_0=914401.8288036576 +y_0=304800.6096012192 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3507, "epsg", 3507, "NAD83(NSRS2007) / Connecticut",
        "+proj=lcc +lat_1=41.86666666666667 +lat_2=41.2 +lat_0=40.83333333333334 +lon_0=-72.75 +x_0=304800.6096 +y_0=152400.3048 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3508, "epsg", 3508, "NAD83(NSRS2007) / Connecticut (ftUS)",
        "+proj=lcc +lat_1=41.86666666666667 +lat_2=41.2 +lat_0=40.83333333333334 +lon_0=-72.75 +x_0=304800.6096012192 +y_0=152400.3048006096 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3509, "epsg", 3509, "NAD83(NSRS2007) / Delaware",
        "+proj=tmerc +lat_0=38 +lon_0=-75.41666666666667 +k=0.999995 +x_0=200000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3510, "epsg", 3510, "NAD83(NSRS2007) / Delaware (ftUS)",
        "+proj=tmerc +lat_0=38 +lon_0=-75.41666666666667 +k=0.999995 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3511, "epsg", 3511, "NAD83(NSRS2007) / Florida East",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-81 +k=0.999941177 +x_0=200000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3512, "epsg", 3512, "NAD83(NSRS2007) / Florida East (ftUS)",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-81 +k=0.999941177 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3513, "epsg", 3513, "NAD83(NSRS2007) / Florida GDL Albers",
        "+proj=aea +lat_1=24 +lat_2=31.5 +lat_0=24 +lon_0=-84 +x_0=400000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3514, "epsg", 3514, "NAD83(NSRS2007) / Florida North",
        "+proj=lcc +lat_1=30.75 +lat_2=29.58333333333333 +lat_0=29 +lon_0=-84.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3515, "epsg", 3515, "NAD83(NSRS2007) / Florida North (ftUS)",
        "+proj=lcc +lat_1=30.75 +lat_2=29.58333333333333 +lat_0=29 +lon_0=-84.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3516, "epsg", 3516, "NAD83(NSRS2007) / Florida West",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-82 +k=0.999941177 +x_0=200000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3517, "epsg", 3517, "NAD83(NSRS2007) / Florida West (ftUS)",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-82 +k=0.999941177 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3518, "epsg", 3518, "NAD83(NSRS2007) / Georgia East",
        "+proj=tmerc +lat_0=30 +lon_0=-82.16666666666667 +k=0.9999 +x_0=200000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3519, "epsg", 3519, "NAD83(NSRS2007) / Georgia East (ftUS)",
        "+proj=tmerc +lat_0=30 +lon_0=-82.16666666666667 +k=0.9999 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3520, "epsg", 3520, "NAD83(NSRS2007) / Georgia West",
        "+proj=tmerc +lat_0=30 +lon_0=-84.16666666666667 +k=0.9999 +x_0=700000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3521, "epsg", 3521, "NAD83(NSRS2007) / Georgia West (ftUS)",
        "+proj=tmerc +lat_0=30 +lon_0=-84.16666666666667 +k=0.9999 +x_0=699999.9998983998 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3522, "epsg", 3522, "NAD83(NSRS2007) / Idaho Central",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-114 +k=0.9999473679999999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3523, "epsg", 3523, "NAD83(NSRS2007) / Idaho Central (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-114 +k=0.9999473679999999 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3524, "epsg", 3524, "NAD83(NSRS2007) / Idaho East",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-112.1666666666667 +k=0.9999473679999999 +x_0=200000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3525, "epsg", 3525, "NAD83(NSRS2007) / Idaho East (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-112.1666666666667 +k=0.9999473679999999 +x_0=200000.0001016002 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3526, "epsg", 3526, "NAD83(NSRS2007) / Idaho West",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-115.75 +k=0.999933333 +x_0=800000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3527, "epsg", 3527, "NAD83(NSRS2007) / Idaho West (ftUS)",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-115.75 +k=0.999933333 +x_0=800000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3528, "epsg", 3528, "NAD83(NSRS2007) / Illinois East",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-88.33333333333333 +k=0.9999749999999999 +x_0=300000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3529, "epsg", 3529, "NAD83(NSRS2007) / Illinois East (ftUS)",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-88.33333333333333 +k=0.9999749999999999 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3530, "epsg", 3530, "NAD83(NSRS2007) / Illinois West",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-90.16666666666667 +k=0.999941177 +x_0=700000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3531, "epsg", 3531, "NAD83(NSRS2007) / Illinois West (ftUS)",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-90.16666666666667 +k=0.999941177 +x_0=699999.9999898402 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3532, "epsg", 3532, "NAD83(NSRS2007) / Indiana East",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=100000 +y_0=250000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3533, "epsg", 3533, "NAD83(NSRS2007) / Indiana East (ftUS)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=99999.99989839978 +y_0=249999.9998983998 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3534, "epsg", 3534, "NAD83(NSRS2007) / Indiana West",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=900000 +y_0=250000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3535, "epsg", 3535, "NAD83(NSRS2007) / Indiana West (ftUS)",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=900000 +y_0=249999.9998983998 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3536, "epsg", 3536, "NAD83(NSRS2007) / Iowa North",
        "+proj=lcc +lat_1=43.26666666666667 +lat_2=42.06666666666667 +lat_0=41.5 +lon_0=-93.5 +x_0=1500000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3537, "epsg", 3537, "NAD83(NSRS2007) / Iowa North (ft US)",
        "+proj=lcc +lat_1=43.26666666666667 +lat_2=42.06666666666667 +lat_0=41.5 +lon_0=-93.5 +x_0=1500000 +y_0=999999.9999898402 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3538, "epsg", 3538, "NAD83(NSRS2007) / Iowa South",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.61666666666667 +lat_0=40 +lon_0=-93.5 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3539, "epsg", 3539, "NAD83(NSRS2007) / Iowa South (ft US)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.61666666666667 +lat_0=40 +lon_0=-93.5 +x_0=500000.00001016 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3540, "epsg", 3540, "NAD83(NSRS2007) / Kansas North",
        "+proj=lcc +lat_1=39.78333333333333 +lat_2=38.71666666666667 +lat_0=38.33333333333334 +lon_0=-98 +x_0=400000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3541, "epsg", 3541, "NAD83(NSRS2007) / Kansas North (ft US)",
        "+proj=lcc +lat_1=39.78333333333333 +lat_2=38.71666666666667 +lat_0=38.33333333333334 +lon_0=-98 +x_0=399999.99998984 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3542, "epsg", 3542, "NAD83(NSRS2007) / Kansas South",
        "+proj=lcc +lat_1=38.56666666666667 +lat_2=37.26666666666667 +lat_0=36.66666666666666 +lon_0=-98.5 +x_0=400000 +y_0=400000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3543, "epsg", 3543, "NAD83(NSRS2007) / Kansas South (ft US)",
        "+proj=lcc +lat_1=38.56666666666667 +lat_2=37.26666666666667 +lat_0=36.66666666666666 +lon_0=-98.5 +x_0=399999.99998984 +y_0=399999.99998984 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3544, "epsg", 3544, "NAD83(NSRS2007) / Kentucky North",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=38.96666666666667 +lat_0=37.5 +lon_0=-84.25 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3545, "epsg", 3545, "NAD83(NSRS2007) / Kentucky North (ftUS)",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=38.96666666666667 +lat_0=37.5 +lon_0=-84.25 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3546, "epsg", 3546, "NAD83(NSRS2007) / Kentucky Single Zone",
        "+proj=lcc +lat_1=37.08333333333334 +lat_2=38.66666666666666 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=1500000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3547, "epsg", 3547, "NAD83(NSRS2007) / Kentucky Single Zone (ftUS)",
        "+proj=lcc +lat_1=37.08333333333334 +lat_2=38.66666666666666 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=1500000 +y_0=999999.9998983998 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3548, "epsg", 3548, "NAD83(NSRS2007) / Kentucky South",
        "+proj=lcc +lat_1=37.93333333333333 +lat_2=36.73333333333333 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=500000 +y_0=500000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3549, "epsg", 3549, "NAD83(NSRS2007) / Kentucky South (ftUS)",
        "+proj=lcc +lat_1=37.93333333333333 +lat_2=36.73333333333333 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=500000.0001016001 +y_0=500000.0001016001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3550, "epsg", 3550, "NAD83(NSRS2007) / Louisiana North",
        "+proj=lcc +lat_1=32.66666666666666 +lat_2=31.16666666666667 +lat_0=30.5 +lon_0=-92.5 +x_0=1000000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3551, "epsg", 3551, "NAD83(NSRS2007) / Louisiana North (ftUS)",
        "+proj=lcc +lat_1=32.66666666666666 +lat_2=31.16666666666667 +lat_0=30.5 +lon_0=-92.5 +x_0=999999.9999898402 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3552, "epsg", 3552, "NAD83(NSRS2007) / Louisiana South",
        "+proj=lcc +lat_1=30.7 +lat_2=29.3 +lat_0=28.5 +lon_0=-91.33333333333333 +x_0=1000000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3553, "epsg", 3553, "NAD83(NSRS2007) / Louisiana South (ftUS)",
        "+proj=lcc +lat_1=30.7 +lat_2=29.3 +lat_0=28.5 +lon_0=-91.33333333333333 +x_0=999999.9999898402 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3554, "epsg", 3554, "NAD83(NSRS2007) / Maine CS2000 Central",
        "+proj=tmerc +lat_0=43.5 +lon_0=-69.125 +k=0.99998 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3555, "epsg", 3555, "NAD83(NSRS2007) / Maine CS2000 East",
        "+proj=tmerc +lat_0=43.83333333333334 +lon_0=-67.875 +k=0.99998 +x_0=700000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3556, "epsg", 3556, "NAD83(NSRS2007) / Maine CS2000 West",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.375 +k=0.99998 +x_0=300000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3557, "epsg", 3557, "NAD83(NSRS2007) / Maine East",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3558, "epsg", 3558, "NAD83(NSRS2007) / Maine West",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3559, "epsg", 3559, "NAD83(NSRS2007) / Maryland",
        "+proj=lcc +lat_1=39.45 +lat_2=38.3 +lat_0=37.66666666666666 +lon_0=-77 +x_0=400000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3560, "epsg", 3560, "NAD83 / Utah North (ftUS)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000.00001016 +y_0=999999.9999898402 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3561, "epsg", 3561, "Old Hawaiian / Hawaii zone 1",
        "+proj=tmerc +lat_0=18.83333333333333 +lon_0=-155.5 +k=0.999966667 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +units=us-ft +no_defs"},
    {
    3562, "epsg", 3562, "Old Hawaiian / Hawaii zone 2",
        "+proj=tmerc +lat_0=20.33333333333333 +lon_0=-156.6666666666667 +k=0.999966667 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +units=us-ft +no_defs"},
    {
    3563, "epsg", 3563, "Old Hawaiian / Hawaii zone 3",
        "+proj=tmerc +lat_0=21.16666666666667 +lon_0=-158 +k=0.99999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +units=us-ft +no_defs"},
    {
    3564, "epsg", 3564, "Old Hawaiian / Hawaii zone 4",
        "+proj=tmerc +lat_0=21.83333333333333 +lon_0=-159.5 +k=0.99999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +units=us-ft +no_defs"},
    {
    3565, "epsg", 3565, "Old Hawaiian / Hawaii zone 5",
        "+proj=tmerc +lat_0=21.66666666666667 +lon_0=-160.1666666666667 +k=1 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +units=us-ft +no_defs"},
    {
    3566, "epsg", 3566, "NAD83 / Utah Central (ftUS)",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000.00001016 +y_0=2000000.00001016 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3567, "epsg", 3567, "NAD83 / Utah South (ftUS)",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000.00001016 +y_0=3000000 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3568, "epsg", 3568, "NAD83(HARN) / Utah North (ftUS)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000.00001016 +y_0=999999.9999898402 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3569, "epsg", 3569, "NAD83(HARN) / Utah Central (ftUS)",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000.00001016 +y_0=2000000.00001016 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3570, "epsg", 3570, "NAD83(HARN) / Utah South (ftUS)",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000.00001016 +y_0=3000000 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3571, "epsg", 3571, "WGS 84 / North Pole LAEA Bering Sea",
        "+proj=laea +lat_0=90 +lon_0=180 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3572, "epsg", 3572, "WGS 84 / North Pole LAEA Alaska",
        "+proj=laea +lat_0=90 +lon_0=-150 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3573, "epsg", 3573, "WGS 84 / North Pole LAEA Canada",
        "+proj=laea +lat_0=90 +lon_0=-100 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3574, "epsg", 3574, "WGS 84 / North Pole LAEA Atlantic",
        "+proj=laea +lat_0=90 +lon_0=-40 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3575, "epsg", 3575, "WGS 84 / North Pole LAEA Europe",
        "+proj=laea +lat_0=90 +lon_0=10 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3576, "epsg", 3576, "WGS 84 / North Pole LAEA Russia",
        "+proj=laea +lat_0=90 +lon_0=90 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3577, "epsg", 3577, "GDA94 / Australian Albers",
        "+proj=aea +lat_1=-18 +lat_2=-36 +lat_0=0 +lon_0=132 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3578, "epsg", 3578, "NAD83 / Yukon Albers",
        "+proj=aea +lat_1=61.66666666666666 +lat_2=68 +lat_0=59 +lon_0=-132.5 +x_0=500000 +y_0=500000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3579, "epsg", 3579, "NAD83(CSRS) / Yukon Albers",
        "+proj=aea +lat_1=61.66666666666666 +lat_2=68 +lat_0=59 +lon_0=-132.5 +x_0=500000 +y_0=500000 +ellps=GRS80 +units=m +no_defs"},
    {
    3580, "epsg", 3580, "NAD83 / NWT Lambert",
        "+proj=lcc +lat_1=62 +lat_2=70 +lat_0=0 +lon_0=-112 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3581, "epsg", 3581, "NAD83(CSRS) / NWT Lambert",
        "+proj=lcc +lat_1=62 +lat_2=70 +lat_0=0 +lon_0=-112 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3582, "epsg", 3582, "NAD83(NSRS2007) / Maryland (ftUS)",
        "+proj=lcc +lat_1=39.45 +lat_2=38.3 +lat_0=37.66666666666666 +lon_0=-77 +x_0=399999.9998983998 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3583, "epsg", 3583, "NAD83(NSRS2007) / Massachusetts Island",
        "+proj=lcc +lat_1=41.48333333333333 +lat_2=41.28333333333333 +lat_0=41 +lon_0=-70.5 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3584, "epsg", 3584, "NAD83(NSRS2007) / Massachusetts Island (ftUS)",
        "+proj=lcc +lat_1=41.48333333333333 +lat_2=41.28333333333333 +lat_0=41 +lon_0=-70.5 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3585, "epsg", 3585, "NAD83(NSRS2007) / Massachusetts Mainland",
        "+proj=lcc +lat_1=42.68333333333333 +lat_2=41.71666666666667 +lat_0=41 +lon_0=-71.5 +x_0=200000 +y_0=750000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3586, "epsg", 3586, "NAD83(NSRS2007) / Massachusetts Mainland (ftUS)",
        "+proj=lcc +lat_1=42.68333333333333 +lat_2=41.71666666666667 +lat_0=41 +lon_0=-71.5 +x_0=200000.0001016002 +y_0=750000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3587, "epsg", 3587, "NAD83(NSRS2007) / Michigan Central",
        "+proj=lcc +lat_1=45.7 +lat_2=44.18333333333333 +lat_0=43.31666666666667 +lon_0=-84.36666666666666 +x_0=6000000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3588, "epsg", 3588, "NAD83(NSRS2007) / Michigan Central (ft)",
        "+proj=lcc +lat_1=45.7 +lat_2=44.18333333333333 +lat_0=43.31666666666667 +lon_0=-84.36666666666666 +x_0=5999999.999976001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3589, "epsg", 3589, "NAD83(NSRS2007) / Michigan North",
        "+proj=lcc +lat_1=47.08333333333334 +lat_2=45.48333333333333 +lat_0=44.78333333333333 +lon_0=-87 +x_0=8000000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3590, "epsg", 3590, "NAD83(NSRS2007) / Michigan North (ft)",
        "+proj=lcc +lat_1=47.08333333333334 +lat_2=45.48333333333333 +lat_0=44.78333333333333 +lon_0=-87 +x_0=7999999.999968001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3591, "epsg", 3591, "NAD83(NSRS2007) / Michigan Oblique Mercator",
        "+proj=omerc +lat_0=45.30916666666666 +lonc=-86 +alpha=337.25556 +k=0.9996 +x_0=2546731.496 +y_0=-4354009.816 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3592, "epsg", 3592, "NAD83(NSRS2007) / Michigan South",
        "+proj=lcc +lat_1=43.66666666666666 +lat_2=42.1 +lat_0=41.5 +lon_0=-84.36666666666666 +x_0=4000000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3593, "epsg", 3593, "NAD83(NSRS2007) / Michigan South (ft)",
        "+proj=lcc +lat_1=43.66666666666666 +lat_2=42.1 +lat_0=41.5 +lon_0=-84.36666666666666 +x_0=3999999.999984 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3594, "epsg", 3594, "NAD83(NSRS2007) / Minnesota Central",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000 +y_0=100000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3595, "epsg", 3595, "NAD83(NSRS2007) / Minnesota North",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000 +y_0=100000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3596, "epsg", 3596, "NAD83(NSRS2007) / Minnesota South",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000 +y_0=100000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3597, "epsg", 3597, "NAD83(NSRS2007) / Mississippi East",
        "+proj=tmerc +lat_0=29.5 +lon_0=-88.83333333333333 +k=0.99995 +x_0=300000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3598, "epsg", 3598, "NAD83(NSRS2007) / Mississippi East (ftUS)",
        "+proj=tmerc +lat_0=29.5 +lon_0=-88.83333333333333 +k=0.99995 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3599, "epsg", 3599, "NAD83(NSRS2007) / Mississippi West",
        "+proj=tmerc +lat_0=29.5 +lon_0=-90.33333333333333 +k=0.99995 +x_0=700000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3600, "epsg", 3600, "NAD83(NSRS2007) / Mississippi West (ftUS)",
        "+proj=tmerc +lat_0=29.5 +lon_0=-90.33333333333333 +k=0.99995 +x_0=699999.9998983998 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3601, "epsg", 3601, "NAD83(NSRS2007) / Missouri Central",
        "+proj=tmerc +lat_0=35.83333333333334 +lon_0=-92.5 +k=0.999933333 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3602, "epsg", 3602, "NAD83(NSRS2007) / Missouri East",
        "+proj=tmerc +lat_0=35.83333333333334 +lon_0=-90.5 +k=0.999933333 +x_0=250000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3603, "epsg", 3603, "NAD83(NSRS2007) / Missouri West",
        "+proj=tmerc +lat_0=36.16666666666666 +lon_0=-94.5 +k=0.999941177 +x_0=850000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3604, "epsg", 3604, "NAD83(NSRS2007) / Montana",
        "+proj=lcc +lat_1=49 +lat_2=45 +lat_0=44.25 +lon_0=-109.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3605, "epsg", 3605, "NAD83(NSRS2007) / Montana (ft)",
        "+proj=lcc +lat_1=49 +lat_2=45 +lat_0=44.25 +lon_0=-109.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3606, "epsg", 3606, "NAD83(NSRS2007) / Nebraska",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3607, "epsg", 3607, "NAD83(NSRS2007) / Nevada Central",
        "+proj=tmerc +lat_0=34.75 +lon_0=-116.6666666666667 +k=0.9999 +x_0=500000 +y_0=6000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3608, "epsg", 3608, "NAD83(NSRS2007) / Nevada Central (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-116.6666666666667 +k=0.9999 +x_0=500000.00001016 +y_0=6000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3609, "epsg", 3609, "NAD83(NSRS2007) / Nevada East",
        "+proj=tmerc +lat_0=34.75 +lon_0=-115.5833333333333 +k=0.9999 +x_0=200000 +y_0=8000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3610, "epsg", 3610, "NAD83(NSRS2007) / Nevada East (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-115.5833333333333 +k=0.9999 +x_0=200000.00001016 +y_0=8000000.000010163 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3611, "epsg", 3611, "NAD83(NSRS2007) / Nevada West",
        "+proj=tmerc +lat_0=34.75 +lon_0=-118.5833333333333 +k=0.9999 +x_0=800000 +y_0=4000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3612, "epsg", 3612, "NAD83(NSRS2007) / Nevada West (ft US)",
        "+proj=tmerc +lat_0=34.75 +lon_0=-118.5833333333333 +k=0.9999 +x_0=800000.0000101599 +y_0=3999999.99998984 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3613, "epsg", 3613, "NAD83(NSRS2007) / New Hampshire",
        "+proj=tmerc +lat_0=42.5 +lon_0=-71.66666666666667 +k=0.999966667 +x_0=300000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3614, "epsg", 3614, "NAD83(NSRS2007) / New Hampshire (ftUS)",
        "+proj=tmerc +lat_0=42.5 +lon_0=-71.66666666666667 +k=0.999966667 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3615, "epsg", 3615, "NAD83(NSRS2007) / New Jersey",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3616, "epsg", 3616, "NAD83(NSRS2007) / New Jersey (ft US)",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3617, "epsg", 3617, "NAD83(NSRS2007) / New Mexico Central",
        "+proj=tmerc +lat_0=31 +lon_0=-106.25 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3618, "epsg", 3618, "NAD83(NSRS2007) / New Mexico Central (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-106.25 +k=0.9999 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3619, "epsg", 3619, "NAD83(NSRS2007) / New Mexico East",
        "+proj=tmerc +lat_0=31 +lon_0=-104.3333333333333 +k=0.999909091 +x_0=165000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3620, "epsg", 3620, "NAD83(NSRS2007) / New Mexico East (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-104.3333333333333 +k=0.999909091 +x_0=165000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3621, "epsg", 3621, "NAD83(NSRS2007) / New Mexico West",
        "+proj=tmerc +lat_0=31 +lon_0=-107.8333333333333 +k=0.999916667 +x_0=830000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3622, "epsg", 3622, "NAD83(NSRS2007) / New Mexico West (ftUS)",
        "+proj=tmerc +lat_0=31 +lon_0=-107.8333333333333 +k=0.999916667 +x_0=830000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3623, "epsg", 3623, "NAD83(NSRS2007) / New York Central",
        "+proj=tmerc +lat_0=40 +lon_0=-76.58333333333333 +k=0.9999375 +x_0=250000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3624, "epsg", 3624, "NAD83(NSRS2007) / New York Central (ftUS)",
        "+proj=tmerc +lat_0=40 +lon_0=-76.58333333333333 +k=0.9999375 +x_0=249999.9998983998 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3625, "epsg", 3625, "NAD83(NSRS2007) / New York East",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3626, "epsg", 3626, "NAD83(NSRS2007) / New York East (ftUS)",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3627, "epsg", 3627, "NAD83(NSRS2007) / New York Long Island",
        "+proj=lcc +lat_1=41.03333333333333 +lat_2=40.66666666666666 +lat_0=40.16666666666666 +lon_0=-74 +x_0=300000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3628, "epsg", 3628, "NAD83(NSRS2007) / New York Long Island (ftUS)",
        "+proj=lcc +lat_1=41.03333333333333 +lat_2=40.66666666666666 +lat_0=40.16666666666666 +lon_0=-74 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3629, "epsg", 3629, "NAD83(NSRS2007) / New York West",
        "+proj=tmerc +lat_0=40 +lon_0=-78.58333333333333 +k=0.9999375 +x_0=350000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3630, "epsg", 3630, "NAD83(NSRS2007) / New York West (ftUS)",
        "+proj=tmerc +lat_0=40 +lon_0=-78.58333333333333 +k=0.9999375 +x_0=350000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3631, "epsg", 3631, "NAD83(NSRS2007) / North Carolina",
        "+proj=lcc +lat_1=36.16666666666666 +lat_2=34.33333333333334 +lat_0=33.75 +lon_0=-79 +x_0=609601.22 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3632, "epsg", 3632, "NAD83(NSRS2007) / North Carolina (ftUS)",
        "+proj=lcc +lat_1=36.16666666666666 +lat_2=34.33333333333334 +lat_0=33.75 +lon_0=-79 +x_0=609601.2192024384 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3633, "epsg", 3633, "NAD83(NSRS2007) / North Dakota North",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.43333333333333 +lat_0=47 +lon_0=-100.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3634, "epsg", 3634, "NAD83(NSRS2007) / North Dakota North (ft)",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.43333333333333 +lat_0=47 +lon_0=-100.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3635, "epsg", 3635, "NAD83(NSRS2007) / North Dakota South",
        "+proj=lcc +lat_1=47.48333333333333 +lat_2=46.18333333333333 +lat_0=45.66666666666666 +lon_0=-100.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3636, "epsg", 3636, "NAD83(NSRS2007) / North Dakota South (ft)",
        "+proj=lcc +lat_1=47.48333333333333 +lat_2=46.18333333333333 +lat_0=45.66666666666666 +lon_0=-100.5 +x_0=599999.9999976 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3637, "epsg", 3637, "NAD83(NSRS2007) / Ohio North",
        "+proj=lcc +lat_1=41.7 +lat_2=40.43333333333333 +lat_0=39.66666666666666 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3638, "epsg", 3638, "NAD83(NSRS2007) / Ohio South",
        "+proj=lcc +lat_1=40.03333333333333 +lat_2=38.73333333333333 +lat_0=38 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3639, "epsg", 3639, "NAD83(NSRS2007) / Oklahoma North",
        "+proj=lcc +lat_1=36.76666666666667 +lat_2=35.56666666666667 +lat_0=35 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3640, "epsg", 3640, "NAD83(NSRS2007) / Oklahoma North (ftUS)",
        "+proj=lcc +lat_1=36.76666666666667 +lat_2=35.56666666666667 +lat_0=35 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3641, "epsg", 3641, "NAD83(NSRS2007) / Oklahoma South",
        "+proj=lcc +lat_1=35.23333333333333 +lat_2=33.93333333333333 +lat_0=33.33333333333334 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3642, "epsg", 3642, "NAD83(NSRS2007) / Oklahoma South (ftUS)",
        "+proj=lcc +lat_1=35.23333333333333 +lat_2=33.93333333333333 +lat_0=33.33333333333334 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3643, "epsg", 3643, "NAD83(NSRS2007) / Oregon Lambert",
        "+proj=lcc +lat_1=43 +lat_2=45.5 +lat_0=41.75 +lon_0=-120.5 +x_0=400000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3644, "epsg", 3644, "NAD83(NSRS2007) / Oregon Lambert (ft)",
        "+proj=lcc +lat_1=43 +lat_2=45.5 +lat_0=41.75 +lon_0=-120.5 +x_0=399999.9999984 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3645, "epsg", 3645, "NAD83(NSRS2007) / Oregon North",
        "+proj=lcc +lat_1=46 +lat_2=44.33333333333334 +lat_0=43.66666666666666 +lon_0=-120.5 +x_0=2500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3646, "epsg", 3646, "NAD83(NSRS2007) / Oregon North (ft)",
        "+proj=lcc +lat_1=46 +lat_2=44.33333333333334 +lat_0=43.66666666666666 +lon_0=-120.5 +x_0=2500000.0001424 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3647, "epsg", 3647, "NAD83(NSRS2007) / Oregon South",
        "+proj=lcc +lat_1=44 +lat_2=42.33333333333334 +lat_0=41.66666666666666 +lon_0=-120.5 +x_0=1500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3648, "epsg", 3648, "NAD83(NSRS2007) / Oregon South (ft)",
        "+proj=lcc +lat_1=44 +lat_2=42.33333333333334 +lat_0=41.66666666666666 +lon_0=-120.5 +x_0=1500000.0001464 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3649, "epsg", 3649, "NAD83(NSRS2007) / Pennsylvania North",
        "+proj=lcc +lat_1=41.95 +lat_2=40.88333333333333 +lat_0=40.16666666666666 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3650, "epsg", 3650, "NAD83(NSRS2007) / Pennsylvania North (ftUS)",
        "+proj=lcc +lat_1=41.95 +lat_2=40.88333333333333 +lat_0=40.16666666666666 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3651, "epsg", 3651, "NAD83(NSRS2007) / Pennsylvania South",
        "+proj=lcc +lat_1=40.96666666666667 +lat_2=39.93333333333333 +lat_0=39.33333333333334 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3652, "epsg", 3652, "NAD83(NSRS2007) / Pennsylvania South (ftUS)",
        "+proj=lcc +lat_1=40.96666666666667 +lat_2=39.93333333333333 +lat_0=39.33333333333334 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3653, "epsg", 3653, "NAD83(NSRS2007) / Rhode Island",
        "+proj=tmerc +lat_0=41.08333333333334 +lon_0=-71.5 +k=0.99999375 +x_0=100000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3654, "epsg", 3654, "NAD83(NSRS2007) / Rhode Island (ftUS)",
        "+proj=tmerc +lat_0=41.08333333333334 +lon_0=-71.5 +k=0.99999375 +x_0=99999.99998983997 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3655, "epsg", 3655, "NAD83(NSRS2007) / South Carolina",
        "+proj=lcc +lat_1=34.83333333333334 +lat_2=32.5 +lat_0=31.83333333333333 +lon_0=-81 +x_0=609600 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3656, "epsg", 3656, "NAD83(NSRS2007) / South Carolina (ft)",
        "+proj=lcc +lat_1=34.83333333333334 +lat_2=32.5 +lat_0=31.83333333333333 +lon_0=-81 +x_0=609600 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3657, "epsg", 3657, "NAD83(NSRS2007) / South Dakota North",
        "+proj=lcc +lat_1=45.68333333333333 +lat_2=44.41666666666666 +lat_0=43.83333333333334 +lon_0=-100 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3658, "epsg", 3658, "NAD83(NSRS2007) / South Dakota North (ftUS)",
        "+proj=lcc +lat_1=45.68333333333333 +lat_2=44.41666666666666 +lat_0=43.83333333333334 +lon_0=-100 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3659, "epsg", 3659, "NAD83(NSRS2007) / South Dakota South",
        "+proj=lcc +lat_1=44.4 +lat_2=42.83333333333334 +lat_0=42.33333333333334 +lon_0=-100.3333333333333 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3660, "epsg", 3660, "NAD83(NSRS2007) / South Dakota South (ftUS)",
        "+proj=lcc +lat_1=44.4 +lat_2=42.83333333333334 +lat_0=42.33333333333334 +lon_0=-100.3333333333333 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3661, "epsg", 3661, "NAD83(NSRS2007) / Tennessee",
        "+proj=lcc +lat_1=36.41666666666666 +lat_2=35.25 +lat_0=34.33333333333334 +lon_0=-86 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3662, "epsg", 3662, "NAD83(NSRS2007) / Tennessee (ftUS)",
        "+proj=lcc +lat_1=36.41666666666666 +lat_2=35.25 +lat_0=34.33333333333334 +lon_0=-86 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3663, "epsg", 3663, "NAD83(NSRS2007) / Texas Central",
        "+proj=lcc +lat_1=31.88333333333333 +lat_2=30.11666666666667 +lat_0=29.66666666666667 +lon_0=-100.3333333333333 +x_0=700000 +y_0=3000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3664, "epsg", 3664, "NAD83(NSRS2007) / Texas Central (ftUS)",
        "+proj=lcc +lat_1=31.88333333333333 +lat_2=30.11666666666667 +lat_0=29.66666666666667 +lon_0=-100.3333333333333 +x_0=699999.9998983998 +y_0=3000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3665, "epsg", 3665, "NAD83(NSRS2007) / Texas Centric Albers Equal Area",
        "+proj=aea +lat_1=27.5 +lat_2=35 +lat_0=18 +lon_0=-100 +x_0=1500000 +y_0=6000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3666, "epsg", 3666, "NAD83(NSRS2007) / Texas Centric Lambert Conformal",
        "+proj=lcc +lat_1=27.5 +lat_2=35 +lat_0=18 +lon_0=-100 +x_0=1500000 +y_0=5000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3667, "epsg", 3667, "NAD83(NSRS2007) / Texas North",
        "+proj=lcc +lat_1=36.18333333333333 +lat_2=34.65 +lat_0=34 +lon_0=-101.5 +x_0=200000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3668, "epsg", 3668, "NAD83(NSRS2007) / Texas North (ftUS)",
        "+proj=lcc +lat_1=36.18333333333333 +lat_2=34.65 +lat_0=34 +lon_0=-101.5 +x_0=200000.0001016002 +y_0=999999.9998983998 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3669, "epsg", 3669, "NAD83(NSRS2007) / Texas North Central",
        "+proj=lcc +lat_1=33.96666666666667 +lat_2=32.13333333333333 +lat_0=31.66666666666667 +lon_0=-98.5 +x_0=600000 +y_0=2000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3670, "epsg", 3670, "NAD83(NSRS2007) / Texas North Central (ftUS)",
        "+proj=lcc +lat_1=33.96666666666667 +lat_2=32.13333333333333 +lat_0=31.66666666666667 +lon_0=-98.5 +x_0=600000 +y_0=2000000.0001016 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3671, "epsg", 3671, "NAD83(NSRS2007) / Texas South",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.66666666666667 +lon_0=-98.5 +x_0=300000 +y_0=5000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3672, "epsg", 3672, "NAD83(NSRS2007) / Texas South (ftUS)",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.66666666666667 +lon_0=-98.5 +x_0=300000.0000000001 +y_0=5000000.0001016 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3673, "epsg", 3673, "NAD83(NSRS2007) / Texas South Central",
        "+proj=lcc +lat_1=30.28333333333333 +lat_2=28.38333333333333 +lat_0=27.83333333333333 +lon_0=-99 +x_0=600000 +y_0=4000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3674, "epsg", 3674, "NAD83(NSRS2007) / Texas South Central (ftUS)",
        "+proj=lcc +lat_1=30.28333333333333 +lat_2=28.38333333333333 +lat_0=27.83333333333333 +lon_0=-99 +x_0=600000 +y_0=3999999.9998984 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3675, "epsg", 3675, "NAD83(NSRS2007) / Utah Central",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000 +y_0=2000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3676, "epsg", 3676, "NAD83(NSRS2007) / Utah Central (ft)",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000.0001504 +y_0=1999999.999992 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3677, "epsg", 3677, "NAD83(NSRS2007) / Utah Central (ftUS)",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000.00001016 +y_0=2000000.00001016 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3678, "epsg", 3678, "NAD83(NSRS2007) / Utah North",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3679, "epsg", 3679, "NAD83(NSRS2007) / Utah North (ft)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000.0001504 +y_0=999999.9999960001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3680, "epsg", 3680, "NAD83(NSRS2007) / Utah North (ftUS)",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000.00001016 +y_0=999999.9999898402 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3681, "epsg", 3681, "NAD83(NSRS2007) / Utah South",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000 +y_0=3000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3682, "epsg", 3682, "NAD83(NSRS2007) / Utah South (ft)",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000.0001504 +y_0=2999999.999988 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=ft +no_defs"},
    {
    3683, "epsg", 3683, "NAD83(NSRS2007) / Utah South (ftUS)",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000.00001016 +y_0=3000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3684, "epsg", 3684, "NAD83(NSRS2007) / Vermont",
        "+proj=tmerc +lat_0=42.5 +lon_0=-72.5 +k=0.999964286 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3685, "epsg", 3685, "NAD83(NSRS2007) / Virginia North",
        "+proj=lcc +lat_1=39.2 +lat_2=38.03333333333333 +lat_0=37.66666666666666 +lon_0=-78.5 +x_0=3500000 +y_0=2000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3686, "epsg", 3686, "NAD83(NSRS2007) / Virginia North (ftUS)",
        "+proj=lcc +lat_1=39.2 +lat_2=38.03333333333333 +lat_0=37.66666666666666 +lon_0=-78.5 +x_0=3500000.0001016 +y_0=2000000.0001016 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3687, "epsg", 3687, "NAD83(NSRS2007) / Virginia South",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=36.76666666666667 +lat_0=36.33333333333334 +lon_0=-78.5 +x_0=3500000 +y_0=1000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3688, "epsg", 3688, "NAD83(NSRS2007) / Virginia South (ftUS)",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=36.76666666666667 +lat_0=36.33333333333334 +lon_0=-78.5 +x_0=3500000.0001016 +y_0=999999.9998983998 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3689, "epsg", 3689, "NAD83(NSRS2007) / Washington North",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.5 +lat_0=47 +lon_0=-120.8333333333333 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3690, "epsg", 3690, "NAD83(NSRS2007) / Washington North (ftUS)",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.5 +lat_0=47 +lon_0=-120.8333333333333 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3691, "epsg", 3691, "NAD83(NSRS2007) / Washington South",
        "+proj=lcc +lat_1=47.33333333333334 +lat_2=45.83333333333334 +lat_0=45.33333333333334 +lon_0=-120.5 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3692, "epsg", 3692, "NAD83(NSRS2007) / Washington South (ftUS)",
        "+proj=lcc +lat_1=47.33333333333334 +lat_2=45.83333333333334 +lat_0=45.33333333333334 +lon_0=-120.5 +x_0=500000.0001016001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3693, "epsg", 3693, "NAD83(NSRS2007) / West Virginia North",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3694, "epsg", 3694, "NAD83(NSRS2007) / West Virginia South",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3695, "epsg", 3695, "NAD83(NSRS2007) / Wisconsin Central",
        "+proj=lcc +lat_1=45.5 +lat_2=44.25 +lat_0=43.83333333333334 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3696, "epsg", 3696, "NAD83(NSRS2007) / Wisconsin Central (ftUS)",
        "+proj=lcc +lat_1=45.5 +lat_2=44.25 +lat_0=43.83333333333334 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3697, "epsg", 3697, "NAD83(NSRS2007) / Wisconsin North",
        "+proj=lcc +lat_1=46.76666666666667 +lat_2=45.56666666666667 +lat_0=45.16666666666666 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3698, "epsg", 3698, "NAD83(NSRS2007) / Wisconsin North (ftUS)",
        "+proj=lcc +lat_1=46.76666666666667 +lat_2=45.56666666666667 +lat_0=45.16666666666666 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3699, "epsg", 3699, "NAD83(NSRS2007) / Wisconsin South",
        "+proj=lcc +lat_1=44.06666666666667 +lat_2=42.73333333333333 +lat_0=42 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3700, "epsg", 3700, "NAD83(NSRS2007) / Wisconsin South (ftUS)",
        "+proj=lcc +lat_1=44.06666666666667 +lat_2=42.73333333333333 +lat_0=42 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3701, "epsg", 3701, "NAD83(NSRS2007) / Wisconsin Transverse Mercator",
        "+proj=tmerc +lat_0=0 +lon_0=-90 +k=0.9996 +x_0=520000 +y_0=-4480000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3702, "epsg", 3702, "NAD83(NSRS2007) / Wyoming East",
        "+proj=tmerc +lat_0=40.5 +lon_0=-105.1666666666667 +k=0.9999375 +x_0=200000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3703, "epsg", 3703, "NAD83(NSRS2007) / Wyoming East Central",
        "+proj=tmerc +lat_0=40.5 +lon_0=-107.3333333333333 +k=0.9999375 +x_0=400000 +y_0=100000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3704, "epsg", 3704, "NAD83(NSRS2007) / Wyoming West Central",
        "+proj=tmerc +lat_0=40.5 +lon_0=-108.75 +k=0.9999375 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3705, "epsg", 3705, "NAD83(NSRS2007) / Wyoming West",
        "+proj=tmerc +lat_0=40.5 +lon_0=-110.0833333333333 +k=0.9999375 +x_0=800000 +y_0=100000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3706, "epsg", 3706, "NAD83(NSRS2007) / UTM zone 59N",
        "+proj=utm +zone=59 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3707, "epsg", 3707, "NAD83(NSRS2007) / UTM zone 60N",
        "+proj=utm +zone=60 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3708, "epsg", 3708, "NAD83(NSRS2007) / UTM zone 1N",
        "+proj=utm +zone=1 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3709, "epsg", 3709, "NAD83(NSRS2007) / UTM zone 2N",
        "+proj=utm +zone=2 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3710, "epsg", 3710, "NAD83(NSRS2007) / UTM zone 3N",
        "+proj=utm +zone=3 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3711, "epsg", 3711, "NAD83(NSRS2007) / UTM zone 4N",
        "+proj=utm +zone=4 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3712, "epsg", 3712, "NAD83(NSRS2007) / UTM zone 5N",
        "+proj=utm +zone=5 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3713, "epsg", 3713, "NAD83(NSRS2007) / UTM zone 6N",
        "+proj=utm +zone=6 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3714, "epsg", 3714, "NAD83(NSRS2007) / UTM zone 7N",
        "+proj=utm +zone=7 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3715, "epsg", 3715, "NAD83(NSRS2007) / UTM zone 8N",
        "+proj=utm +zone=8 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3716, "epsg", 3716, "NAD83(NSRS2007) / UTM zone 9N",
        "+proj=utm +zone=9 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3717, "epsg", 3717, "NAD83(NSRS2007) / UTM zone 10N",
        "+proj=utm +zone=10 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3718, "epsg", 3718, "NAD83(NSRS2007) / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3719, "epsg", 3719, "NAD83(NSRS2007) / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3720, "epsg", 3720, "NAD83(NSRS2007) / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3721, "epsg", 3721, "NAD83(NSRS2007) / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3722, "epsg", 3722, "NAD83(NSRS2007) / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3723, "epsg", 3723, "NAD83(NSRS2007) / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3724, "epsg", 3724, "NAD83(NSRS2007) / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3725, "epsg", 3725, "NAD83(NSRS2007) / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3726, "epsg", 3726, "NAD83(NSRS2007) / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3727, "epsg", 3727, "Reunion 1947 / TM Reunion",
        "+proj=tmerc +lat_0=-21.11666666666667 +lon_0=55.53333333333333 +k=1 +x_0=160000 +y_0=50000 +ellps=intl +units=m +no_defs"},
    {
    3728, "epsg", 3728, "NAD83(NSRS2007) / Ohio North (ftUS)",
        "+proj=lcc +lat_1=41.7 +lat_2=40.43333333333333 +lat_0=39.66666666666666 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3729, "epsg", 3729, "NAD83(NSRS2007) / Ohio South (ftUS)",
        "+proj=lcc +lat_1=40.03333333333333 +lat_2=38.73333333333333 +lat_0=38 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3730, "epsg", 3730, "NAD83(NSRS2007) / Wyoming East (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-105.1666666666667 +k=0.9999375 +x_0=200000.00001016 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3731, "epsg", 3731, "NAD83(NSRS2007) / Wyoming East Central (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-107.3333333333333 +k=0.9999375 +x_0=399999.99998984 +y_0=99999.99998983997 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3732, "epsg", 3732, "NAD83(NSRS2007) / Wyoming West Central (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-108.75 +k=0.9999375 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3733, "epsg", 3733, "NAD83(NSRS2007) / Wyoming West (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-110.0833333333333 +k=0.9999375 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    3734, "epsg", 3734, "NAD83 / Ohio North (ftUS)",
        "+proj=lcc +lat_1=41.7 +lat_2=40.43333333333333 +lat_0=39.66666666666666 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3735, "epsg", 3735, "NAD83 / Ohio South (ftUS)",
        "+proj=lcc +lat_1=40.03333333333333 +lat_2=38.73333333333333 +lat_0=38 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3736, "epsg", 3736, "NAD83 / Wyoming East (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-105.1666666666667 +k=0.9999375 +x_0=200000.00001016 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3737, "epsg", 3737, "NAD83 / Wyoming East Central (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-107.3333333333333 +k=0.9999375 +x_0=399999.99998984 +y_0=99999.99998983997 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3738, "epsg", 3738, "NAD83 / Wyoming West Central (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-108.75 +k=0.9999375 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3739, "epsg", 3739, "NAD83 / Wyoming West (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-110.0833333333333 +k=0.9999375 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3740, "epsg", 3740, "NAD83(HARN) / UTM zone 10N",
        "+proj=utm +zone=10 +ellps=GRS80 +units=m +no_defs"},
    {
    3741, "epsg", 3741, "NAD83(HARN) / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=GRS80 +units=m +no_defs"},
    {
    3742, "epsg", 3742, "NAD83(HARN) / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=GRS80 +units=m +no_defs"},
    {
    3743, "epsg", 3743, "NAD83(HARN) / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=GRS80 +units=m +no_defs"},
    {
    3744, "epsg", 3744, "NAD83(HARN) / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=GRS80 +units=m +no_defs"},
    {
    3745, "epsg", 3745, "NAD83(HARN) / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=GRS80 +units=m +no_defs"},
    {
    3746, "epsg", 3746, "NAD83(HARN) / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=GRS80 +units=m +no_defs"},
    {
    3747, "epsg", 3747, "NAD83(HARN) / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=GRS80 +units=m +no_defs"},
    {
    3748, "epsg", 3748, "NAD83(HARN) / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=GRS80 +units=m +no_defs"},
    {
    3749, "epsg", 3749, "NAD83(HARN) / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=GRS80 +units=m +no_defs"},
    {
    3750, "epsg", 3750, "NAD83(HARN) / UTM zone 4N",
        "+proj=utm +zone=4 +ellps=GRS80 +units=m +no_defs"},
    {
    3751, "epsg", 3751, "NAD83(HARN) / UTM zone 5N",
        "+proj=utm +zone=5 +ellps=GRS80 +units=m +no_defs"},
    {
    3752, "epsg", 3752, "WGS 84 / Mercator 41 (deprecated)",
        "+proj=merc +lon_0=100 +lat_ts=-41 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3753, "epsg", 3753, "NAD83(HARN) / Ohio North (ftUS)",
        "+proj=lcc +lat_1=41.7 +lat_2=40.43333333333333 +lat_0=39.66666666666666 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3754, "epsg", 3754, "NAD83(HARN) / Ohio South (ftUS)",
        "+proj=lcc +lat_1=40.03333333333333 +lat_2=38.73333333333333 +lat_0=38 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3755, "epsg", 3755, "NAD83(HARN) / Wyoming East (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-105.1666666666667 +k=0.9999375 +x_0=200000.00001016 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3756, "epsg", 3756, "NAD83(HARN) / Wyoming East Central (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-107.3333333333333 +k=0.9999375 +x_0=399999.99998984 +y_0=99999.99998983997 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3757, "epsg", 3757, "NAD83(HARN) / Wyoming West Central (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-108.75 +k=0.9999375 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3758, "epsg", 3758, "NAD83(HARN) / Wyoming West (ftUS)",
        "+proj=tmerc +lat_0=40.5 +lon_0=-110.0833333333333 +k=0.9999375 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3759, "epsg", 3759, "NAD83 / Hawaii zone 3 (ftUS)",
        "+proj=tmerc +lat_0=21.16666666666667 +lon_0=-158 +k=0.99999 +x_0=500000.00001016 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    3760, "epsg", 3760, "NAD83(HARN) / Hawaii zone 3 (ftUS)",
        "+proj=tmerc +lat_0=21.16666666666667 +lon_0=-158 +k=0.99999 +x_0=500000.00001016 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    3761, "epsg", 3761, "NAD83(CSRS) / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=GRS80 +units=m +no_defs"},
    {
    3762, "epsg", 3762, "WGS 84 / South Georgia Lambert",
        "+proj=lcc +lat_1=-54 +lat_2=-54.75 +lat_0=-55 +lon_0=-37 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3763, "epsg", 3763, "ETRS89 / Portugal TM06",
        "+proj=tmerc +lat_0=39.66825833333333 +lon_0=-8.133108333333334 +k=1 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3764, "epsg", 3764, "NZGD2000 / Chatham Island Circuit 2000",
        "+proj=tmerc +lat_0=-44 +lon_0=-176.5 +k=1 +x_0=400000 +y_0=800000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3765, "epsg", 3765, "HTRS96 / Croatia TM",
        "+proj=tmerc +lat_0=0 +lon_0=16.5 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3766, "epsg", 3766, "HTRS96 / Croatia LCC",
        "+proj=lcc +lat_1=45.91666666666666 +lat_2=43.08333333333334 +lat_0=0 +lon_0=16.5 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3767, "epsg", 3767, "HTRS96 / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3768, "epsg", 3768, "HTRS96 / UTM zone 34N",
        "+proj=utm +zone=34 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3769, "epsg", 3769, "Bermuda 1957 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=clrk66 +units=m +no_defs"},
    {
    3770, "epsg", 3770, "BDA2000 / Bermuda 2000 National Grid",
        "+proj=tmerc +lat_0=32 +lon_0=-64.75 +k=1 +x_0=550000 +y_0=100000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3771, "epsg", 3771, "NAD27 / Alberta 3TM ref merid 111 W",
        "+proj=tmerc +lat_0=0 +lon_0=-111 +k=0.9999 +x_0=0 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3772, "epsg", 3772, "NAD27 / Alberta 3TM ref merid 114 W",
        "+proj=tmerc +lat_0=0 +lon_0=-114 +k=0.9999 +x_0=0 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3773, "epsg", 3773, "NAD27 / Alberta 3TM ref merid 117 W",
        "+proj=tmerc +lat_0=0 +lon_0=-117 +k=0.9999 +x_0=0 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3774, "epsg", 3774, "NAD27 / Alberta 3TM ref merid 120 W (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-120 +k=0.9999 +x_0=0 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3775, "epsg", 3775, "NAD83 / Alberta 3TM ref merid 111 W",
        "+proj=tmerc +lat_0=0 +lon_0=-111 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3776, "epsg", 3776, "NAD83 / Alberta 3TM ref merid 114 W",
        "+proj=tmerc +lat_0=0 +lon_0=-114 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3777, "epsg", 3777, "NAD83 / Alberta 3TM ref merid 117 W",
        "+proj=tmerc +lat_0=0 +lon_0=-117 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3778, "epsg", 3778, "NAD83 / Alberta 3TM ref merid 120 W (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-120 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3779, "epsg", 3779, "NAD83(CSRS) / Alberta 3TM ref merid 111 W",
        "+proj=tmerc +lat_0=0 +lon_0=-111 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3780, "epsg", 3780, "NAD83(CSRS) / Alberta 3TM ref merid 114 W",
        "+proj=tmerc +lat_0=0 +lon_0=-114 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3781, "epsg", 3781, "NAD83(CSRS) / Alberta 3TM ref merid 117 W",
        "+proj=tmerc +lat_0=0 +lon_0=-117 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3782, "epsg", 3782,
        "NAD83(CSRS) / Alberta 3TM ref merid 120 W (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-120 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3783, "epsg", 3783, "Pitcairn 2006 / Pitcairn TM 2006",
        "+proj=tmerc +lat_0=-25.06855261111111 +lon_0=-130.1129671111111 +k=1 +x_0=14200 +y_0=15500 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3784, "epsg", 3784, "Pitcairn 1967 / UTM zone 9S",
        "+proj=utm +zone=9 +south +ellps=intl +towgs84=185,165,42,0,0,0,0 +units=m +no_defs"},
    {
    3785, "epsg", 3785, "Popular Visualisation CRS / Mercator (deprecated)",
        "+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs"},
    {
    3786, "epsg", 3786, "World Equidistant Cylindrical (Sphere) (deprecated)",
        "+proj=eqc +lat_ts=0 +lat_0=0 +lon_0=0 +x_0=0 +y_0=0 +a=6371007 +b=6371007 +units=m +no_defs"},
    {
    3787, "epsg", 3787, "MGI / Slovene National Grid (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9999 +x_0=500000 +y_0=-5000000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    3788, "epsg", 3788, "NZGD2000 / Auckland Islands TM 2000",
        "+proj=tmerc +lat_0=0 +lon_0=166 +k=1 +x_0=3500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3789, "epsg", 3789, "NZGD2000 / Campbell Island TM 2000",
        "+proj=tmerc +lat_0=0 +lon_0=169 +k=1 +x_0=3500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3790, "epsg", 3790, "NZGD2000 / Antipodes Islands TM 2000",
        "+proj=tmerc +lat_0=0 +lon_0=179 +k=1 +x_0=3500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3791, "epsg", 3791, "NZGD2000 / Raoul Island TM 2000",
        "+proj=tmerc +lat_0=0 +lon_0=-178 +k=1 +x_0=3500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3793, "epsg", 3793, "NZGD2000 / Chatham Islands TM 2000",
        "+proj=tmerc +lat_0=0 +lon_0=-176.5 +k=1 +x_0=3500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3794, "epsg", 3794, "Slovenia 1996 / Slovene National Grid",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9999 +x_0=500000 +y_0=-5000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3795, "epsg", 3795, "NAD27 / Cuba Norte",
        "+proj=lcc +lat_1=23 +lat_2=21.7 +lat_0=22.35 +lon_0=-81 +x_0=500000 +y_0=280296.016 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3796, "epsg", 3796, "NAD27 / Cuba Sur",
        "+proj=lcc +lat_1=21.3 +lat_2=20.13333333333333 +lat_0=20.71666666666667 +lon_0=-76.83333333333333 +x_0=500000 +y_0=229126.939 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3797, "epsg", 3797, "NAD27 / MTQ Lambert",
        "+proj=lcc +lat_1=50 +lat_2=46 +lat_0=44 +lon_0=-70 +x_0=800000 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3798, "epsg", 3798, "NAD83 / MTQ Lambert",
        "+proj=lcc +lat_1=50 +lat_2=46 +lat_0=44 +lon_0=-70 +x_0=800000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3799, "epsg", 3799, "NAD83(CSRS) / MTQ Lambert",
        "+proj=lcc +lat_1=50 +lat_2=46 +lat_0=44 +lon_0=-70 +x_0=800000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3800, "epsg", 3800, "NAD27 / Alberta 3TM ref merid 120 W",
        "+proj=tmerc +lat_0=0 +lon_0=-120 +k=0.9999 +x_0=0 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    3801, "epsg", 3801, "NAD83 / Alberta 3TM ref merid 120 W",
        "+proj=tmerc +lat_0=0 +lon_0=-120 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3802, "epsg", 3802, "NAD83(CSRS) / Alberta 3TM ref merid 120 W",
        "+proj=tmerc +lat_0=0 +lon_0=-120 +k=0.9999 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3812, "epsg", 3812, "ETRS89 / Belgian Lambert 2008",
        "+proj=lcc +lat_1=49.83333333333334 +lat_2=51.16666666666666 +lat_0=50.797815 +lon_0=4.359215833333333 +x_0=649328 +y_0=665262 +ellps=GRS80 +units=m +no_defs"},
    {
    3814, "epsg", 3814, "NAD83 / Mississippi TM",
        "+proj=tmerc +lat_0=32.5 +lon_0=-89.75 +k=0.9998335 +x_0=500000 +y_0=1300000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3815, "epsg", 3815, "NAD83(HARN) / Mississippi TM",
        "+proj=tmerc +lat_0=32.5 +lon_0=-89.75 +k=0.9998335 +x_0=500000 +y_0=1300000 +ellps=GRS80 +units=m +no_defs"},
    {
    3816, "epsg", 3816, "NAD83(NSRS2007) / Mississippi TM",
        "+proj=tmerc +lat_0=32.5 +lon_0=-89.75 +k=0.9998335 +x_0=500000 +y_0=1300000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3825, "epsg", 3825, "TWD97 / TM2 zone 119",
        "+proj=tmerc +lat_0=0 +lon_0=119 +k=0.9999 +x_0=250000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3826, "epsg", 3826, "TWD97 / TM2 zone 121",
        "+proj=tmerc +lat_0=0 +lon_0=121 +k=0.9999 +x_0=250000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3827, "epsg", 3827, "TWD67 / TM2 zone 119",
        "+proj=tmerc +lat_0=0 +lon_0=119 +k=0.9999 +x_0=250000 +y_0=0 +ellps=aust_SA +units=m +no_defs"},
    {
    3828, "epsg", 3828, "TWD67 / TM2 zone 121",
        "+proj=tmerc +lat_0=0 +lon_0=121 +k=0.9999 +x_0=250000 +y_0=0 +ellps=aust_SA +units=m +no_defs"},
    {
    3829, "epsg", 3829, "Hu Tzu Shan / UTM zone 51N",
        "+proj=utm +zone=51 +ellps=intl +towgs84=-637,-549,-203,0,0,0,0 +units=m +no_defs"},
    {
    3832, "epsg", 3832, "WGS 84 / PDC Mercator",
        "+proj=merc +lon_0=150 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3833, "epsg", 3833, "Pulkovo 1942(58) / Gauss-Kruger zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=2500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3834, "epsg", 3834, "Pulkovo 1942(83) / Gauss-Kruger zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=2500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3835, "epsg", 3835, "Pulkovo 1942(83) / Gauss-Kruger zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=3500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3836, "epsg", 3836, "Pulkovo 1942(83) / Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3837, "epsg", 3837, "Pulkovo 1942(58) / 3-degree Gauss-Kruger zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=3500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3838, "epsg", 3838, "Pulkovo 1942(58) / 3-degree Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3839, "epsg", 3839, "Pulkovo 1942(58) / 3-degree Gauss-Kruger zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=9500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3840, "epsg", 3840, "Pulkovo 1942(58) / 3-degree Gauss-Kruger zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=30 +k=1 +x_0=10500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3841, "epsg", 3841, "Pulkovo 1942(83) / 3-degree Gauss-Kruger zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=6500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3842, "epsg", 3842, "Pulkovo 1942(83) / 3-degree Gauss-Kruger zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=6500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3843, "epsg", 3843, "Pulkovo 1942(83) / 3-degree Gauss-Kruger zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=6500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    3844, "epsg", 3844, "Pulkovo 1942(58) / Stereo70",
        "+proj=sterea +lat_0=46 +lon_0=25 +k=0.99975 +x_0=500000 +y_0=500000 +ellps=krass +units=m +no_defs"},
    {
    3845, "epsg", 3845, "SWEREF99 / RT90 7.5 gon V emulation",
        "+proj=tmerc +lat_0=0 +lon_0=11.30625 +k=1.000006 +x_0=1500025.141 +y_0=-667.282 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3846, "epsg", 3846, "SWEREF99 / RT90 5 gon V emulation",
        "+proj=tmerc +lat_0=0 +lon_0=13.55626666666667 +k=1.0000058 +x_0=1500044.695 +y_0=-667.13 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3847, "epsg", 3847, "SWEREF99 / RT90 2.5 gon V emulation",
        "+proj=tmerc +lat_0=0 +lon_0=15.80628452944445 +k=1.00000561024 +x_0=1500064.274 +y_0=-667.711 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3848, "epsg", 3848, "SWEREF99 / RT90 0 gon emulation",
        "+proj=tmerc +lat_0=0 +lon_0=18.0563 +k=1.0000054 +x_0=1500083.521 +y_0=-668.8440000000001 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3849, "epsg", 3849, "SWEREF99 / RT90 2.5 gon O emulation",
        "+proj=tmerc +lat_0=0 +lon_0=20.30631666666667 +k=1.0000052 +x_0=1500102.765 +y_0=-670.706 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3850, "epsg", 3850, "SWEREF99 / RT90 5 gon O emulation",
        "+proj=tmerc +lat_0=0 +lon_0=22.55633333333333 +k=1.0000049 +x_0=1500121.846 +y_0=-672.557 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3851, "epsg", 3851, "NZGD2000 / NZCS2000",
        "+proj=lcc +lat_1=-37.5 +lat_2=-44.5 +lat_0=-41 +lon_0=173 +x_0=3000000 +y_0=7000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3852, "epsg", 3852, "RSRGD2000 / DGLC2000",
        "+proj=lcc +lat_1=-76.66666666666667 +lat_2=-79.33333333333333 +lat_0=-90 +lon_0=157 +x_0=500000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3854, "epsg", 3854, "County ST74",
        "+proj=tmerc +lat_0=0 +lon_0=18.05787 +k=0.99999506 +x_0=100182.7406 +y_0=-6500620.1207 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3857, "epsg", 3857, "WGS 84 / Pseudo-Mercator",
        "+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs"},
    {
    3890, "epsg", 3890, "IGRS / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3891, "epsg", 3891, "IGRS / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3892, "epsg", 3892, "IGRS / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3893, "epsg", 3893, "ED50 / Iraq National Grid",
        "+proj=tmerc +lat_0=29.02626833333333 +lon_0=46.5 +k=0.9994 +x_0=800000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    3907, "epsg", 3907, "MGI 1901 / Balkans zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9999 +x_0=5500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3908, "epsg", 3908, "MGI 1901 / Balkans zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=0.9999 +x_0=6500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3909, "epsg", 3909, "MGI 1901 / Balkans zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=0.9999 +x_0=7500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3910, "epsg", 3910, "MGI 1901 / Balkans zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9999 +x_0=8500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3911, "epsg", 3911, "MGI 1901 / Slovenia Grid",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9999 +x_0=500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    3912, "epsg", 3912, "MGI 1901 / Slovene National Grid",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9999 +x_0=500000 +y_0=-5000000 +ellps=bessel +units=m +no_defs"},
    {
    3920, "epsg", 3920, "Puerto Rico / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=clrk66 +towgs84=11,72,-101,0,0,0,0 +units=m +no_defs"},
    {
    3942, "epsg", 3942, "RGF93 / CC42",
        "+proj=lcc +lat_1=41.25 +lat_2=42.75 +lat_0=42 +lon_0=3 +x_0=1700000 +y_0=1200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3943, "epsg", 3943, "RGF93 / CC43",
        "+proj=lcc +lat_1=42.25 +lat_2=43.75 +lat_0=43 +lon_0=3 +x_0=1700000 +y_0=2200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3944, "epsg", 3944, "RGF93 / CC44",
        "+proj=lcc +lat_1=43.25 +lat_2=44.75 +lat_0=44 +lon_0=3 +x_0=1700000 +y_0=3200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3945, "epsg", 3945, "RGF93 / CC45",
        "+proj=lcc +lat_1=44.25 +lat_2=45.75 +lat_0=45 +lon_0=3 +x_0=1700000 +y_0=4200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3946, "epsg", 3946, "RGF93 / CC46",
        "+proj=lcc +lat_1=45.25 +lat_2=46.75 +lat_0=46 +lon_0=3 +x_0=1700000 +y_0=5200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3947, "epsg", 3947, "RGF93 / CC47",
        "+proj=lcc +lat_1=46.25 +lat_2=47.75 +lat_0=47 +lon_0=3 +x_0=1700000 +y_0=6200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3948, "epsg", 3948, "RGF93 / CC48",
        "+proj=lcc +lat_1=47.25 +lat_2=48.75 +lat_0=48 +lon_0=3 +x_0=1700000 +y_0=7200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3949, "epsg", 3949, "RGF93 / CC49",
        "+proj=lcc +lat_1=48.25 +lat_2=49.75 +lat_0=49 +lon_0=3 +x_0=1700000 +y_0=8200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3950, "epsg", 3950, "RGF93 / CC50",
        "+proj=lcc +lat_1=49.25 +lat_2=50.75 +lat_0=50 +lon_0=3 +x_0=1700000 +y_0=9200000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3968, "epsg", 3968, "NAD83 / Virginia Lambert",
        "+proj=lcc +lat_1=37 +lat_2=39.5 +lat_0=36 +lon_0=-79.5 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3969, "epsg", 3969, "NAD83(HARN) / Virginia Lambert",
        "+proj=lcc +lat_1=37 +lat_2=39.5 +lat_0=36 +lon_0=-79.5 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3970, "epsg", 3970, "NAD83(NSRS2007) / Virginia Lambert",
        "+proj=lcc +lat_1=37 +lat_2=39.5 +lat_0=36 +lon_0=-79.5 +x_0=0 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    3975, "epsg", 3975, "WGS 84 / NSIDC EASE-Grid Global",
        "+proj=cea +lon_0=0 +lat_ts=30 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3976, "epsg", 3976, "WGS 84 / NSIDC Sea Ice Polar Stereographic South",
        "+proj=stere +lat_0=-90 +lat_ts=-70 +lon_0=0 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3978, "epsg", 3978, "NAD83 / Canada Atlas Lambert",
        "+proj=lcc +lat_1=49 +lat_2=77 +lat_0=49 +lon_0=-95 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    3979, "epsg", 3979, "NAD83(CSRS) / Canada Atlas Lambert",
        "+proj=lcc +lat_1=49 +lat_2=77 +lat_0=49 +lon_0=-95 +x_0=0 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    3985, "epsg", 3985, "Katanga 1955 / Katanga Lambert",
        "+proj=lcc +lat_1=-6.5 +lat_2=-11.5 +lat_0=9 +lon_0=26 +x_0=500000 +y_0=500000 +ellps=clrk66 +towgs84=-103.746,-9.614,-255.95,0,0,0,0 +units=m +no_defs"},
    {
    3986, "epsg", 3986, "Katanga 1955 / Katanga Gauss zone A",
        "+proj=tmerc +lat_0=-9 +lon_0=30 +k=1 +x_0=200000 +y_0=500000 +ellps=clrk66 +towgs84=-103.746,-9.614,-255.95,0,0,0,0 +units=m +no_defs"},
    {
    3987, "epsg", 3987, "Katanga 1955 / Katanga Gauss zone B",
        "+proj=tmerc +lat_0=-9 +lon_0=28 +k=1 +x_0=200000 +y_0=500000 +ellps=clrk66 +towgs84=-103.746,-9.614,-255.95,0,0,0,0 +units=m +no_defs"},
    {
    3988, "epsg", 3988, "Katanga 1955 / Katanga Gauss zone C",
        "+proj=tmerc +lat_0=-9 +lon_0=26 +k=1 +x_0=200000 +y_0=500000 +ellps=clrk66 +towgs84=-103.746,-9.614,-255.95,0,0,0,0 +units=m +no_defs"},
    {
    3989, "epsg", 3989, "Katanga 1955 / Katanga Gauss zone D",
        "+proj=tmerc +lat_0=-9 +lon_0=24 +k=1 +x_0=200000 +y_0=500000 +ellps=clrk66 +towgs84=-103.746,-9.614,-255.95,0,0,0,0 +units=m +no_defs"},
    {
    3991, "epsg", 3991, "Puerto Rico State Plane CS of 1927",
        "+proj=lcc +lat_1=18.43333333333333 +lat_2=18.03333333333333 +lat_0=17.83333333333333 +lon_0=-66.43333333333334 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +towgs84=11,72,-101,0,0,0,0 +units=us-ft +no_defs"},
    {
    3992, "epsg", 3992, "Puerto Rico / St. Croix",
        "+proj=lcc +lat_1=18.43333333333333 +lat_2=18.03333333333333 +lat_0=17.83333333333333 +lon_0=-66.43333333333334 +x_0=152400.3048006096 +y_0=30480.06096012192 +ellps=clrk66 +towgs84=11,72,-101,0,0,0,0 +units=us-ft +no_defs"},
    {
    3994, "epsg", 3994, "WGS 84 / Mercator 41",
        "+proj=merc +lon_0=100 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3995, "epsg", 3995, "WGS 84 / Arctic Polar Stereographic",
        "+proj=stere +lat_0=90 +lat_ts=71 +lon_0=0 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3996, "epsg", 3996, "WGS 84 / IBCAO Polar Stereographic",
        "+proj=stere +lat_0=90 +lat_ts=75 +lon_0=0 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    3997, "epsg", 3997, "WGS 84 / Dubai Local TM",
        "+proj=tmerc +lat_0=0 +lon_0=55.33333333333334 +k=1 +x_0=500000 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    4026, "epsg", 4026, "MOLDREF99 / Moldova TM",
        "+proj=tmerc +lat_0=0 +lon_0=28.4 +k=0.9999400000000001 +x_0=200000 +y_0=-5000000 +ellps=GRS80 +units=m +no_defs"},
    {
    4037, "epsg", 4037, "WGS 84 / TMzn35N",
        "+proj=utm +zone=35 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    4038, "epsg", 4038, "WGS 84 / TMzn36N",
        "+proj=utm +zone=36 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    4048, "epsg", 4048, "RGRDC 2005 / Congo TM zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4049, "epsg", 4049, "RGRDC 2005 / Congo TM zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=14 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4050, "epsg", 4050, "RGRDC 2005 / Congo TM zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=16 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4051, "epsg", 4051, "RGRDC 2005 / Congo TM zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4056, "epsg", 4056, "RGRDC 2005 / Congo TM zone 20",
        "+proj=tmerc +lat_0=0 +lon_0=20 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4057, "epsg", 4057, "RGRDC 2005 / Congo TM zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=22 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4058, "epsg", 4058, "RGRDC 2005 / Congo TM zone 24",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4059, "epsg", 4059, "RGRDC 2005 / Congo TM zone 26",
        "+proj=tmerc +lat_0=0 +lon_0=26 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4060, "epsg", 4060, "RGRDC 2005 / Congo TM zone 28",
        "+proj=tmerc +lat_0=0 +lon_0=28 +k=0.9999 +x_0=500000 +y_0=10000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4061, "epsg", 4061, "RGRDC 2005 / UTM zone 33S",
        "+proj=utm +zone=33 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4062, "epsg", 4062, "RGRDC 2005 / UTM zone 34S",
        "+proj=utm +zone=34 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4063, "epsg", 4063, "RGRDC 2005 / UTM zone 35S",
        "+proj=utm +zone=35 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4071, "epsg", 4071, "Chua / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=intl +units=m +no_defs"},
    {
    4082, "epsg", 4082, "REGCAN95 / UTM zone 27N",
        "+proj=utm +zone=27 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    4083, "epsg", 4083, "REGCAN95 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    20004, "epsg", 20004, "Pulkovo 1995 / Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20005, "epsg", 20005, "Pulkovo 1995 / Gauss-Kruger zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=5500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20006, "epsg", 20006, "Pulkovo 1995 / Gauss-Kruger zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=6500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20007, "epsg", 20007, "Pulkovo 1995 / Gauss-Kruger zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=7500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20008, "epsg", 20008, "Pulkovo 1995 / Gauss-Kruger zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=8500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20009, "epsg", 20009, "Pulkovo 1995 / Gauss-Kruger zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=9500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20010, "epsg", 20010, "Pulkovo 1995 / Gauss-Kruger zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=10500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20011, "epsg", 20011, "Pulkovo 1995 / Gauss-Kruger zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=11500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20012, "epsg", 20012, "Pulkovo 1995 / Gauss-Kruger zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=12500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20013, "epsg", 20013, "Pulkovo 1995 / Gauss-Kruger zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=13500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20014, "epsg", 20014, "Pulkovo 1995 / Gauss-Kruger zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=14500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20015, "epsg", 20015, "Pulkovo 1995 / Gauss-Kruger zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=15500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20016, "epsg", 20016, "Pulkovo 1995 / Gauss-Kruger zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=16500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20017, "epsg", 20017, "Pulkovo 1995 / Gauss-Kruger zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=17500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20018, "epsg", 20018, "Pulkovo 1995 / Gauss-Kruger zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=18500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20019, "epsg", 20019, "Pulkovo 1995 / Gauss-Kruger zone 19",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=19500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20020, "epsg", 20020, "Pulkovo 1995 / Gauss-Kruger zone 20",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=20500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20021, "epsg", 20021, "Pulkovo 1995 / Gauss-Kruger zone 21",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=21500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20022, "epsg", 20022, "Pulkovo 1995 / Gauss-Kruger zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=22500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20023, "epsg", 20023, "Pulkovo 1995 / Gauss-Kruger zone 23",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=23500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20024, "epsg", 20024, "Pulkovo 1995 / Gauss-Kruger zone 24",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=24500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20025, "epsg", 20025, "Pulkovo 1995 / Gauss-Kruger zone 25",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=25500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20026, "epsg", 20026, "Pulkovo 1995 / Gauss-Kruger zone 26",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=26500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20027, "epsg", 20027, "Pulkovo 1995 / Gauss-Kruger zone 27",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=27500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20028, "epsg", 20028, "Pulkovo 1995 / Gauss-Kruger zone 28",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=28500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20029, "epsg", 20029, "Pulkovo 1995 / Gauss-Kruger zone 29",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=29500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20030, "epsg", 20030, "Pulkovo 1995 / Gauss-Kruger zone 30",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=30500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20031, "epsg", 20031, "Pulkovo 1995 / Gauss-Kruger zone 31",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=31500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20032, "epsg", 20032, "Pulkovo 1995 / Gauss-Kruger zone 32",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=32500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20064, "epsg", 20064, "Pulkovo 1995 / Gauss-Kruger 4N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20065, "epsg", 20065, "Pulkovo 1995 / Gauss-Kruger 5N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20066, "epsg", 20066, "Pulkovo 1995 / Gauss-Kruger 6N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20067, "epsg", 20067, "Pulkovo 1995 / Gauss-Kruger 7N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20068, "epsg", 20068, "Pulkovo 1995 / Gauss-Kruger 8N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20069, "epsg", 20069, "Pulkovo 1995 / Gauss-Kruger 9N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20070, "epsg", 20070, "Pulkovo 1995 / Gauss-Kruger 10N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20071, "epsg", 20071, "Pulkovo 1995 / Gauss-Kruger 11N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20072, "epsg", 20072, "Pulkovo 1995 / Gauss-Kruger 12N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20073, "epsg", 20073, "Pulkovo 1995 / Gauss-Kruger 13N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20074, "epsg", 20074, "Pulkovo 1995 / Gauss-Kruger 14N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20075, "epsg", 20075, "Pulkovo 1995 / Gauss-Kruger 15N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20076, "epsg", 20076, "Pulkovo 1995 / Gauss-Kruger 16N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20077, "epsg", 20077, "Pulkovo 1995 / Gauss-Kruger 17N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20078, "epsg", 20078, "Pulkovo 1995 / Gauss-Kruger 18N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20079, "epsg", 20079, "Pulkovo 1995 / Gauss-Kruger 19N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20080, "epsg", 20080, "Pulkovo 1995 / Gauss-Kruger 20N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20081, "epsg", 20081, "Pulkovo 1995 / Gauss-Kruger 21N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20082, "epsg", 20082, "Pulkovo 1995 / Gauss-Kruger 22N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20083, "epsg", 20083, "Pulkovo 1995 / Gauss-Kruger 23N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20084, "epsg", 20084, "Pulkovo 1995 / Gauss-Kruger 24N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20085, "epsg", 20085, "Pulkovo 1995 / Gauss-Kruger 25N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20086, "epsg", 20086, "Pulkovo 1995 / Gauss-Kruger 26N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20087, "epsg", 20087, "Pulkovo 1995 / Gauss-Kruger 27N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20088, "epsg", 20088, "Pulkovo 1995 / Gauss-Kruger 28N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20089, "epsg", 20089, "Pulkovo 1995 / Gauss-Kruger 29N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20090, "epsg", 20090, "Pulkovo 1995 / Gauss-Kruger 30N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20091, "epsg", 20091, "Pulkovo 1995 / Gauss-Kruger 31N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20092, "epsg", 20092, "Pulkovo 1995 / Gauss-Kruger 32N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=24.82,-131.21,-82.66,-0,-0,0.16,-0.12 +units=m +no_defs"},
    {
    20135, "epsg", 20135, "Adindan / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=clrk80 +units=m +no_defs"},
    {
    20136, "epsg", 20136, "Adindan / UTM zone 36N",
        "+proj=utm +zone=36 +ellps=clrk80 +units=m +no_defs"},
    {
    20137, "epsg", 20137, "Adindan / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=clrk80 +units=m +no_defs"},
    {
    20138, "epsg", 20138, "Adindan / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=clrk80 +units=m +no_defs"},
    {
    20248, "epsg", 20248, "AGD66 / AMG zone 48",
        "+proj=utm +zone=48 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20249, "epsg", 20249, "AGD66 / AMG zone 49",
        "+proj=utm +zone=49 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20250, "epsg", 20250, "AGD66 / AMG zone 50",
        "+proj=utm +zone=50 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20251, "epsg", 20251, "AGD66 / AMG zone 51",
        "+proj=utm +zone=51 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20252, "epsg", 20252, "AGD66 / AMG zone 52",
        "+proj=utm +zone=52 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20253, "epsg", 20253, "AGD66 / AMG zone 53",
        "+proj=utm +zone=53 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20254, "epsg", 20254, "AGD66 / AMG zone 54",
        "+proj=utm +zone=54 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20255, "epsg", 20255, "AGD66 / AMG zone 55",
        "+proj=utm +zone=55 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20256, "epsg", 20256, "AGD66 / AMG zone 56",
        "+proj=utm +zone=56 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20257, "epsg", 20257, "AGD66 / AMG zone 57",
        "+proj=utm +zone=57 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20258, "epsg", 20258, "AGD66 / AMG zone 58",
        "+proj=utm +zone=58 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20348, "epsg", 20348, "AGD84 / AMG zone 48",
        "+proj=utm +zone=48 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20349, "epsg", 20349, "AGD84 / AMG zone 49",
        "+proj=utm +zone=49 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20350, "epsg", 20350, "AGD84 / AMG zone 50",
        "+proj=utm +zone=50 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20351, "epsg", 20351, "AGD84 / AMG zone 51",
        "+proj=utm +zone=51 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20352, "epsg", 20352, "AGD84 / AMG zone 52",
        "+proj=utm +zone=52 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20353, "epsg", 20353, "AGD84 / AMG zone 53",
        "+proj=utm +zone=53 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20354, "epsg", 20354, "AGD84 / AMG zone 54",
        "+proj=utm +zone=54 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20355, "epsg", 20355, "AGD84 / AMG zone 55",
        "+proj=utm +zone=55 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20356, "epsg", 20356, "AGD84 / AMG zone 56",
        "+proj=utm +zone=56 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20357, "epsg", 20357, "AGD84 / AMG zone 57",
        "+proj=utm +zone=57 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20358, "epsg", 20358, "AGD84 / AMG zone 58",
        "+proj=utm +zone=58 +south +ellps=aust_SA +units=m +no_defs"},
    {
    20436, "epsg", 20436, "Ain el Abd / UTM zone 36N",
        "+proj=utm +zone=36 +ellps=intl +units=m +no_defs"},
    {
    20437, "epsg", 20437, "Ain el Abd / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=intl +units=m +no_defs"},
    {
    20438, "epsg", 20438, "Ain el Abd / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=intl +units=m +no_defs"},
    {
    20439, "epsg", 20439, "Ain el Abd / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=intl +units=m +no_defs"},
    {
    20440, "epsg", 20440, "Ain el Abd / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=intl +units=m +no_defs"},
    {
    20499, "epsg", 20499, "Ain el Abd / Bahrain Grid",
        "+proj=utm +zone=39 +ellps=intl +units=m +no_defs"},
    {
    20538, "epsg", 20538, "Afgooye / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=krass +towgs84=-43,-163,45,0,0,0,0 +units=m +no_defs"},
    {
    20539, "epsg", 20539, "Afgooye / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=krass +towgs84=-43,-163,45,0,0,0,0 +units=m +no_defs"},
    {
    20790, "epsg", 20790, "Lisbon (Lisbon) / Portuguese National Grid",
        "+proj=tmerc +lat_0=39.66666666666666 +lon_0=1 +k=1 +x_0=200000 +y_0=300000 +ellps=intl +pm=lisbon +units=m +no_defs"},
    {
    20791, "epsg", 20791, "Lisbon (Lisbon) / Portuguese Grid",
        "+proj=tmerc +lat_0=39.66666666666666 +lon_0=1 +k=1 +x_0=0 +y_0=0 +ellps=intl +pm=lisbon +units=m +no_defs"},
    {
    20822, "epsg", 20822, "Aratu / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=intl +units=m +no_defs"},
    {
    20823, "epsg", 20823, "Aratu / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=intl +units=m +no_defs"},
    {
    20824, "epsg", 20824, "Aratu / UTM zone 24S",
        "+proj=utm +zone=24 +south +ellps=intl +units=m +no_defs"},
    {
    20934, "epsg", 20934, "Arc 1950 / UTM zone 34S",
        "+proj=utm +zone=34 +south +a=6378249.145 +b=6356514.966398753 +units=m +no_defs"},
    {
    20935, "epsg", 20935, "Arc 1950 / UTM zone 35S",
        "+proj=utm +zone=35 +south +a=6378249.145 +b=6356514.966398753 +units=m +no_defs"},
    {
    20936, "epsg", 20936, "Arc 1950 / UTM zone 36S",
        "+proj=utm +zone=36 +south +a=6378249.145 +b=6356514.966398753 +units=m +no_defs"},
    {
    21035, "epsg", 21035, "Arc 1960 / UTM zone 35S",
        "+proj=utm +zone=35 +south +ellps=clrk80 +units=m +no_defs"},
    {
    21036, "epsg", 21036, "Arc 1960 / UTM zone 36S",
        "+proj=utm +zone=36 +south +ellps=clrk80 +units=m +no_defs"},
    {
    21037, "epsg", 21037, "Arc 1960 / UTM zone 37S",
        "+proj=utm +zone=37 +south +ellps=clrk80 +units=m +no_defs"},
    {
    21095, "epsg", 21095, "Arc 1960 / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=clrk80 +units=m +no_defs"},
    {
    21096, "epsg", 21096, "Arc 1960 / UTM zone 36N",
        "+proj=utm +zone=36 +ellps=clrk80 +units=m +no_defs"},
    {
    21097, "epsg", 21097, "Arc 1960 / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=clrk80 +units=m +no_defs"},
    {
    21100, "epsg", 21100, "Batavia (Jakarta) / NEIEZ (deprecated)",
        "+proj=merc +lon_0=110 +k=0.997 +x_0=3900000 +y_0=900000 +ellps=bessel +pm=jakarta +units=m +no_defs"},
    {
    21148, "epsg", 21148, "Batavia / UTM zone 48S",
        "+proj=utm +zone=48 +south +ellps=bessel +units=m +no_defs"},
    {
    21149, "epsg", 21149, "Batavia / UTM zone 49S",
        "+proj=utm +zone=49 +south +ellps=bessel +units=m +no_defs"},
    {
    21150, "epsg", 21150, "Batavia / UTM zone 50S",
        "+proj=utm +zone=50 +south +ellps=bessel +units=m +no_defs"},
    {
    21291, "epsg", 21291, "Barbados 1938 / British West Indies Grid",
        "+proj=tmerc +lat_0=0 +lon_0=-62 +k=0.9995000000000001 +x_0=400000 +y_0=0 +ellps=clrk80 +towgs84=31.95,300.99,419.19,0,0,0,0 +units=m +no_defs"},
    {
    21292, "epsg", 21292, "Barbados 1938 / Barbados National Grid",
        "+proj=tmerc +lat_0=13.17638888888889 +lon_0=-59.55972222222222 +k=0.9999986 +x_0=30000 +y_0=75000 +ellps=clrk80 +towgs84=31.95,300.99,419.19,0,0,0,0 +units=m +no_defs"},
    {
    21413, "epsg", 21413, "Beijing 1954 / Gauss-Kruger zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=13500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21414, "epsg", 21414, "Beijing 1954 / Gauss-Kruger zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=14500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21415, "epsg", 21415, "Beijing 1954 / Gauss-Kruger zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=15500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21416, "epsg", 21416, "Beijing 1954 / Gauss-Kruger zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=16500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21417, "epsg", 21417, "Beijing 1954 / Gauss-Kruger zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=17500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21418, "epsg", 21418, "Beijing 1954 / Gauss-Kruger zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=18500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21419, "epsg", 21419, "Beijing 1954 / Gauss-Kruger zone 19",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=19500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21420, "epsg", 21420, "Beijing 1954 / Gauss-Kruger zone 20",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=20500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21421, "epsg", 21421, "Beijing 1954 / Gauss-Kruger zone 21",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=21500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21422, "epsg", 21422, "Beijing 1954 / Gauss-Kruger zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=22500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21423, "epsg", 21423, "Beijing 1954 / Gauss-Kruger zone 23",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=23500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21453, "epsg", 21453, "Beijing 1954 / Gauss-Kruger CM 75E",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21454, "epsg", 21454, "Beijing 1954 / Gauss-Kruger CM 81E",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21455, "epsg", 21455, "Beijing 1954 / Gauss-Kruger CM 87E",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21456, "epsg", 21456, "Beijing 1954 / Gauss-Kruger CM 93E",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21457, "epsg", 21457, "Beijing 1954 / Gauss-Kruger CM 99E",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21458, "epsg", 21458, "Beijing 1954 / Gauss-Kruger CM 105E",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21459, "epsg", 21459, "Beijing 1954 / Gauss-Kruger CM 111E",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21460, "epsg", 21460, "Beijing 1954 / Gauss-Kruger CM 117E",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21461, "epsg", 21461, "Beijing 1954 / Gauss-Kruger CM 123E",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21462, "epsg", 21462, "Beijing 1954 / Gauss-Kruger CM 129E",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21463, "epsg", 21463, "Beijing 1954 / Gauss-Kruger CM 135E",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21473, "epsg", 21473, "Beijing 1954 / Gauss-Kruger 13N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21474, "epsg", 21474, "Beijing 1954 / Gauss-Kruger 14N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21475, "epsg", 21475, "Beijing 1954 / Gauss-Kruger 15N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21476, "epsg", 21476, "Beijing 1954 / Gauss-Kruger 16N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21477, "epsg", 21477, "Beijing 1954 / Gauss-Kruger 17N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21478, "epsg", 21478, "Beijing 1954 / Gauss-Kruger 18N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21479, "epsg", 21479, "Beijing 1954 / Gauss-Kruger 19N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21480, "epsg", 21480, "Beijing 1954 / Gauss-Kruger 20N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21481, "epsg", 21481, "Beijing 1954 / Gauss-Kruger 21N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21482, "epsg", 21482, "Beijing 1954 / Gauss-Kruger 22N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21483, "epsg", 21483, "Beijing 1954 / Gauss-Kruger 23N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    21500, "epsg", 21500, "Belge 1950 (Brussels) / Belge Lambert 50",
        "+proj=lcc +lat_1=49.83333333333334 +lat_2=51.16666666666666 +lat_0=90 +lon_0=0 +x_0=150000 +y_0=5400000 +ellps=intl +pm=brussels +units=m +no_defs"},
    {
    21780, "epsg", 21780, "Bern 1898 (Bern) / LV03C",
        "+proj=somerc +lat_0=46.95240555555556 +lon_0=0 +k_0=1 +x_0=0 +y_0=0 +ellps=bessel +pm=bern +units=m +no_defs"},
    {
    21781, "epsg", 21781, "CH1903 / LV03",
        "+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 +k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel +towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs"},
    {
    21782, "epsg", 21782, "CH1903 / LV03C-G",
        "+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 +k_0=1 +x_0=0 +y_0=0 +ellps=bessel +towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs"},
    {
    21817, "epsg", 21817, "Bogota 1975 / UTM zone 17N (deprecated)",
        "+proj=utm +zone=17 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21818, "epsg", 21818, "Bogota 1975 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21891, "epsg", 21891, "Bogota 1975 / Colombia West zone (deprecated)",
        "+proj=tmerc +lat_0=4.599047222222222 +lon_0=-77.08091666666667 +k=1 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21892, "epsg", 21892, "Bogota 1975 / Colombia Bogota zone (deprecated)",
        "+proj=tmerc +lat_0=4.599047222222222 +lon_0=-74.08091666666667 +k=1 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21893, "epsg", 21893,
        "Bogota 1975 / Colombia East Central zone (deprecated)",
        "+proj=tmerc +lat_0=4.599047222222222 +lon_0=-71.08091666666667 +k=1 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21894, "epsg", 21894, "Bogota 1975 / Colombia East (deprecated)",
        "+proj=tmerc +lat_0=4.599047222222222 +lon_0=-68.08091666666667 +k=1 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21896, "epsg", 21896, "Bogota 1975 / Colombia West zone",
        "+proj=tmerc +lat_0=4.599047222222222 +lon_0=-77.08091666666667 +k=1 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21897, "epsg", 21897, "Bogota 1975 / Colombia Bogota zone",
        "+proj=tmerc +lat_0=4.599047222222222 +lon_0=-74.08091666666667 +k=1 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21898, "epsg", 21898, "Bogota 1975 / Colombia East Central zone",
        "+proj=tmerc +lat_0=4.599047222222222 +lon_0=-71.08091666666667 +k=1 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    21899, "epsg", 21899, "Bogota 1975 / Colombia East",
        "+proj=tmerc +lat_0=4.599047222222222 +lon_0=-68.08091666666667 +k=1 +x_0=1000000 +y_0=1000000 +ellps=intl +towgs84=307,304,-318,0,0,0,0 +units=m +no_defs"},
    {
    22032, "epsg", 22032, "Camacupa / UTM zone 32S",
        "+proj=utm +zone=32 +south +ellps=clrk80 +units=m +no_defs"},
    {
    22033, "epsg", 22033, "Camacupa / UTM zone 33S",
        "+proj=utm +zone=33 +south +ellps=clrk80 +units=m +no_defs"},
    {
    22091, "epsg", 22091, "Camacupa / TM 11.30 SE",
        "+proj=tmerc +lat_0=0 +lon_0=11.5 +k=0.9996 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    22092, "epsg", 22092, "Camacupa / TM 12 SE",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=0.9996 +x_0=500000 +y_0=10000000 +ellps=clrk80 +units=m +no_defs"},
    {
    22171, "epsg", 22171, "POSGAR 98 / Argentina 1",
        "+proj=tmerc +lat_0=-90 +lon_0=-72 +k=1 +x_0=1500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    22172, "epsg", 22172, "POSGAR 98 / Argentina 2",
        "+proj=tmerc +lat_0=-90 +lon_0=-69 +k=1 +x_0=2500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    22173, "epsg", 22173, "POSGAR 98 / Argentina 3",
        "+proj=tmerc +lat_0=-90 +lon_0=-66 +k=1 +x_0=3500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    22174, "epsg", 22174, "POSGAR 98 / Argentina 4",
        "+proj=tmerc +lat_0=-90 +lon_0=-63 +k=1 +x_0=4500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    22175, "epsg", 22175, "POSGAR 98 / Argentina 5",
        "+proj=tmerc +lat_0=-90 +lon_0=-60 +k=1 +x_0=5500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    22176, "epsg", 22176, "POSGAR 98 / Argentina 6",
        "+proj=tmerc +lat_0=-90 +lon_0=-57 +k=1 +x_0=6500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    22177, "epsg", 22177, "POSGAR 98 / Argentina 7",
        "+proj=tmerc +lat_0=-90 +lon_0=-54 +k=1 +x_0=7500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    22181, "epsg", 22181, "POSGAR 94 / Argentina 1",
        "+proj=tmerc +lat_0=-90 +lon_0=-72 +k=1 +x_0=1500000 +y_0=0 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    22182, "epsg", 22182, "POSGAR 94 / Argentina 2",
        "+proj=tmerc +lat_0=-90 +lon_0=-69 +k=1 +x_0=2500000 +y_0=0 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    22183, "epsg", 22183, "POSGAR 94 / Argentina 3",
        "+proj=tmerc +lat_0=-90 +lon_0=-66 +k=1 +x_0=3500000 +y_0=0 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    22184, "epsg", 22184, "POSGAR 94 / Argentina 4",
        "+proj=tmerc +lat_0=-90 +lon_0=-63 +k=1 +x_0=4500000 +y_0=0 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    22185, "epsg", 22185, "POSGAR 94 / Argentina 5",
        "+proj=tmerc +lat_0=-90 +lon_0=-60 +k=1 +x_0=5500000 +y_0=0 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    22186, "epsg", 22186, "POSGAR 94 / Argentina 6",
        "+proj=tmerc +lat_0=-90 +lon_0=-57 +k=1 +x_0=6500000 +y_0=0 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    22187, "epsg", 22187, "POSGAR 94 / Argentina 7",
        "+proj=tmerc +lat_0=-90 +lon_0=-54 +k=1 +x_0=7500000 +y_0=0 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    22191, "epsg", 22191, "Campo Inchauspe / Argentina 1",
        "+proj=tmerc +lat_0=-90 +lon_0=-72 +k=1 +x_0=1500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    22192, "epsg", 22192, "Campo Inchauspe / Argentina 2",
        "+proj=tmerc +lat_0=-90 +lon_0=-69 +k=1 +x_0=2500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    22193, "epsg", 22193, "Campo Inchauspe / Argentina 3",
        "+proj=tmerc +lat_0=-90 +lon_0=-66 +k=1 +x_0=3500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    22194, "epsg", 22194, "Campo Inchauspe / Argentina 4",
        "+proj=tmerc +lat_0=-90 +lon_0=-63 +k=1 +x_0=4500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    22195, "epsg", 22195, "Campo Inchauspe / Argentina 5",
        "+proj=tmerc +lat_0=-90 +lon_0=-60 +k=1 +x_0=5500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    22196, "epsg", 22196, "Campo Inchauspe / Argentina 6",
        "+proj=tmerc +lat_0=-90 +lon_0=-57 +k=1 +x_0=6500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    22197, "epsg", 22197, "Campo Inchauspe / Argentina 7",
        "+proj=tmerc +lat_0=-90 +lon_0=-54 +k=1 +x_0=7500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    22234, "epsg", 22234, "Cape / UTM zone 34S",
        "+proj=utm +zone=34 +south +a=6378249.145 +b=6356514.966398753 +units=m +no_defs"},
    {
    22235, "epsg", 22235, "Cape / UTM zone 35S",
        "+proj=utm +zone=35 +south +a=6378249.145 +b=6356514.966398753 +units=m +no_defs"},
    {
    22236, "epsg", 22236, "Cape / UTM zone 36S",
        "+proj=utm +zone=36 +south +a=6378249.145 +b=6356514.966398753 +units=m +no_defs"},
    {
    22332, "epsg", 22332, "Carthage / UTM zone 32N",
        "+proj=utm +zone=32 +a=6378249.2 +b=6356515 +datum=carthage +units=m +no_defs"},
    {
    22391, "epsg", 22391, "Carthage / Nord Tunisie",
        "+proj=lcc +lat_1=36 +lat_0=36 +lon_0=9.9 +k_0=0.999625544 +x_0=500000 +y_0=300000 +a=6378249.2 +b=6356515 +datum=carthage +units=m +no_defs"},
    {
    22392, "epsg", 22392, "Carthage / Sud Tunisie",
        "+proj=lcc +lat_1=33.3 +lat_0=33.3 +lon_0=9.9 +k_0=0.999625769 +x_0=500000 +y_0=300000 +a=6378249.2 +b=6356515 +datum=carthage +units=m +no_defs"},
    {
    22521, "epsg", 22521, "Corrego Alegre / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=intl +towgs84=-206,172,-6,0,0,0,0 +units=m +no_defs"},
    {
    22522, "epsg", 22522, "Corrego Alegre / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=intl +towgs84=-206,172,-6,0,0,0,0 +units=m +no_defs"},
    {
    22523, "epsg", 22523, "Corrego Alegre / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=intl +towgs84=-206,172,-6,0,0,0,0 +units=m +no_defs"},
    {
    22524, "epsg", 22524, "Corrego Alegre / UTM zone 24S",
        "+proj=utm +zone=24 +south +ellps=intl +towgs84=-206,172,-6,0,0,0,0 +units=m +no_defs"},
    {
    22525, "epsg", 22525, "Corrego Alegre / UTM zone 25S",
        "+proj=utm +zone=25 +south +ellps=intl +towgs84=-206,172,-6,0,0,0,0 +units=m +no_defs"},
    {
    22700, "epsg", 22700, "Deir ez Zor / Levant Zone",
        "+proj=lcc +lat_1=34.65 +lat_0=34.65 +lon_0=37.35 +k_0=0.9996256 +x_0=300000 +y_0=300000 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    22770, "epsg", 22770, "Deir ez Zor / Syria Lambert",
        "+proj=lcc +lat_1=34.65 +lat_0=34.65 +lon_0=37.35 +k_0=0.9996256 +x_0=300000 +y_0=300000 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    22780, "epsg", 22780, "Deir ez Zor / Levant Stereographic",
        "+proj=sterea +lat_0=34.2 +lon_0=39.15 +k=0.9995341 +x_0=0 +y_0=0 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    22832, "epsg", 22832, "Douala / UTM zone 32N (deprecated)",
        "+proj=utm +zone=32 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    22991, "epsg", 22991, "Egypt 1907 / Blue Belt",
        "+proj=tmerc +lat_0=30 +lon_0=35 +k=1 +x_0=300000 +y_0=1100000 +ellps=helmert +units=m +no_defs"},
    {
    22992, "epsg", 22992, "Egypt 1907 / Red Belt",
        "+proj=tmerc +lat_0=30 +lon_0=31 +k=1 +x_0=615000 +y_0=810000 +ellps=helmert +units=m +no_defs"},
    {
    22993, "epsg", 22993, "Egypt 1907 / Purple Belt",
        "+proj=tmerc +lat_0=30 +lon_0=27 +k=1 +x_0=700000 +y_0=200000 +ellps=helmert +units=m +no_defs"},
    {
    22994, "epsg", 22994, "Egypt 1907 / Extended Purple Belt",
        "+proj=tmerc +lat_0=30 +lon_0=27 +k=1 +x_0=700000 +y_0=1200000 +ellps=helmert +units=m +no_defs"},
    {
    23028, "epsg", 23028, "ED50 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=intl +units=m +no_defs"},
    {
    23029, "epsg", 23029, "ED50 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=intl +units=m +no_defs"},
    {
    23030, "epsg", 23030, "ED50 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=intl +units=m +no_defs"},
    {
    23031, "epsg", 23031, "ED50 / UTM zone 31N",
        "+proj=utm +zone=31 +ellps=intl +units=m +no_defs"},
    {
    23032, "epsg", 23032, "ED50 / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=intl +units=m +no_defs"},
    {
    23033, "epsg", 23033, "ED50 / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=intl +units=m +no_defs"},
    {
    23034, "epsg", 23034, "ED50 / UTM zone 34N",
        "+proj=utm +zone=34 +ellps=intl +units=m +no_defs"},
    {
    23035, "epsg", 23035, "ED50 / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=intl +units=m +no_defs"},
    {
    23036, "epsg", 23036, "ED50 / UTM zone 36N",
        "+proj=utm +zone=36 +ellps=intl +units=m +no_defs"},
    {
    23037, "epsg", 23037, "ED50 / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=intl +units=m +no_defs"},
    {
    23038, "epsg", 23038, "ED50 / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=intl +units=m +no_defs"},
    {
    23090, "epsg", 23090, "ED50 / TM 0 N",
        "+proj=tmerc +lat_0=0 +lon_0=0 +k=0.9996 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    23095, "epsg", 23095, "ED50 / TM 5 NE",
        "+proj=tmerc +lat_0=0 +lon_0=5 +k=0.9996 +x_0=500000 +y_0=0 +ellps=intl +units=m +no_defs"},
    {
    23239, "epsg", 23239, "Fahud / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=clrk80 +units=m +no_defs"},
    {
    23240, "epsg", 23240, "Fahud / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=clrk80 +units=m +no_defs"},
    {
    23433, "epsg", 23433, "Garoua / UTM zone 33N (deprecated)",
        "+proj=utm +zone=33 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    23700, "epsg", 23700, "HD72 / EOV",
        "+proj=somerc +lat_0=47.14439372222222 +lon_0=19.04857177777778 +k_0=0.99993 +x_0=650000 +y_0=200000 +ellps=GRS67 +units=m +no_defs"},
    {
    23830, "epsg", 23830, "DGN95 / Indonesia TM-3 zone 46.2",
        "+proj=tmerc +lat_0=0 +lon_0=94.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23831, "epsg", 23831, "DGN95 / Indonesia TM-3 zone 47.1",
        "+proj=tmerc +lat_0=0 +lon_0=97.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23832, "epsg", 23832, "DGN95 / Indonesia TM-3 zone 47.2",
        "+proj=tmerc +lat_0=0 +lon_0=100.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23833, "epsg", 23833, "DGN95 / Indonesia TM-3 zone 48.1",
        "+proj=tmerc +lat_0=0 +lon_0=103.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23834, "epsg", 23834, "DGN95 / Indonesia TM-3 zone 48.2",
        "+proj=tmerc +lat_0=0 +lon_0=106.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23835, "epsg", 23835, "DGN95 / Indonesia TM-3 zone 49.1",
        "+proj=tmerc +lat_0=0 +lon_0=109.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23836, "epsg", 23836, "DGN95 / Indonesia TM-3 zone 49.2",
        "+proj=tmerc +lat_0=0 +lon_0=112.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23837, "epsg", 23837, "DGN95 / Indonesia TM-3 zone 50.1",
        "+proj=tmerc +lat_0=0 +lon_0=115.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23838, "epsg", 23838, "DGN95 / Indonesia TM-3 zone 50.2",
        "+proj=tmerc +lat_0=0 +lon_0=118.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23839, "epsg", 23839, "DGN95 / Indonesia TM-3 zone 51.1",
        "+proj=tmerc +lat_0=0 +lon_0=121.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23840, "epsg", 23840, "DGN95 / Indonesia TM-3 zone 51.2",
        "+proj=tmerc +lat_0=0 +lon_0=124.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23841, "epsg", 23841, "DGN95 / Indonesia TM-3 zone 52.1",
        "+proj=tmerc +lat_0=0 +lon_0=127.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23842, "epsg", 23842, "DGN95 / Indonesia TM-3 zone 52.2",
        "+proj=tmerc +lat_0=0 +lon_0=130.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23843, "epsg", 23843, "DGN95 / Indonesia TM-3 zone 53.1",
        "+proj=tmerc +lat_0=0 +lon_0=133.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23844, "epsg", 23844, "DGN95 / Indonesia TM-3 zone 53.2",
        "+proj=tmerc +lat_0=0 +lon_0=136.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23845, "epsg", 23845, "DGN95 / Indonesia TM-3 zone 54.1",
        "+proj=tmerc +lat_0=0 +lon_0=139.5 +k=0.9999 +x_0=200000 +y_0=1500000 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23846, "epsg", 23846, "ID74 / UTM zone 46N",
        "+proj=utm +zone=46 +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23847, "epsg", 23847, "ID74 / UTM zone 47N",
        "+proj=utm +zone=47 +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23848, "epsg", 23848, "ID74 / UTM zone 48N",
        "+proj=utm +zone=48 +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23849, "epsg", 23849, "ID74 / UTM zone 49N",
        "+proj=utm +zone=49 +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23850, "epsg", 23850, "ID74 / UTM zone 50N",
        "+proj=utm +zone=50 +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23851, "epsg", 23851, "ID74 / UTM zone 51N",
        "+proj=utm +zone=51 +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23852, "epsg", 23852, "ID74 / UTM zone 52N",
        "+proj=utm +zone=52 +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23853, "epsg", 23853, "ID74 / UTM zone 53N (deprecated)",
        "+proj=utm +zone=53 +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23866, "epsg", 23866, "DGN95 / UTM zone 46N",
        "+proj=utm +zone=46 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23867, "epsg", 23867, "DGN95 / UTM zone 47N",
        "+proj=utm +zone=47 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23868, "epsg", 23868, "DGN95 / UTM zone 48N",
        "+proj=utm +zone=48 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23869, "epsg", 23869, "DGN95 / UTM zone 49N",
        "+proj=utm +zone=49 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23870, "epsg", 23870, "DGN95 / UTM zone 50N",
        "+proj=utm +zone=50 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23871, "epsg", 23871, "DGN95 / UTM zone 51N",
        "+proj=utm +zone=51 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23872, "epsg", 23872, "DGN95 / UTM zone 52N",
        "+proj=utm +zone=52 +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23877, "epsg", 23877, "DGN95 / UTM zone 47S",
        "+proj=utm +zone=47 +south +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23878, "epsg", 23878, "DGN95 / UTM zone 48S",
        "+proj=utm +zone=48 +south +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23879, "epsg", 23879, "DGN95 / UTM zone 49S",
        "+proj=utm +zone=49 +south +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23880, "epsg", 23880, "DGN95 / UTM zone 50S",
        "+proj=utm +zone=50 +south +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23881, "epsg", 23881, "DGN95 / UTM zone 51S",
        "+proj=utm +zone=51 +south +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23882, "epsg", 23882, "DGN95 / UTM zone 52S",
        "+proj=utm +zone=52 +south +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23883, "epsg", 23883, "DGN95 / UTM zone 53S",
        "+proj=utm +zone=53 +south +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23884, "epsg", 23884, "DGN95 / UTM zone 54S",
        "+proj=utm +zone=54 +south +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    23886, "epsg", 23886, "ID74 / UTM zone 46S (deprecated)",
        "+proj=utm +zone=46 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23887, "epsg", 23887, "ID74 / UTM zone 47S",
        "+proj=utm +zone=47 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23888, "epsg", 23888, "ID74 / UTM zone 48S",
        "+proj=utm +zone=48 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23889, "epsg", 23889, "ID74 / UTM zone 49S",
        "+proj=utm +zone=49 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23890, "epsg", 23890, "ID74 / UTM zone 50S",
        "+proj=utm +zone=50 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23891, "epsg", 23891, "ID74 / UTM zone 51S",
        "+proj=utm +zone=51 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23892, "epsg", 23892, "ID74 / UTM zone 52S",
        "+proj=utm +zone=52 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23893, "epsg", 23893, "ID74 / UTM zone 53S",
        "+proj=utm +zone=53 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23894, "epsg", 23894, "ID74 / UTM zone 54S",
        "+proj=utm +zone=54 +south +a=6378160 +b=6356774.50408554 +units=m +no_defs"},
    {
    23946, "epsg", 23946, "Indian 1954 / UTM zone 46N",
        "+proj=utm +zone=46 +a=6377276.345 +b=6356075.41314024 +towgs84=217,823,299,0,0,0,0 +units=m +no_defs"},
    {
    23947, "epsg", 23947, "Indian 1954 / UTM zone 47N",
        "+proj=utm +zone=47 +a=6377276.345 +b=6356075.41314024 +towgs84=217,823,299,0,0,0,0 +units=m +no_defs"},
    {
    23948, "epsg", 23948, "Indian 1954 / UTM zone 48N",
        "+proj=utm +zone=48 +a=6377276.345 +b=6356075.41314024 +towgs84=217,823,299,0,0,0,0 +units=m +no_defs"},
    {
    24047, "epsg", 24047, "Indian 1975 / UTM zone 47N",
        "+proj=utm +zone=47 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    24048, "epsg", 24048, "Indian 1975 / UTM zone 48N",
        "+proj=utm +zone=48 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    24100, "epsg", 24100, "Jamaica 1875 / Jamaica (Old Grid)",
        "+proj=lcc +lat_1=18 +lat_0=18 +lon_0=-77 +k_0=1 +x_0=167638.49597 +y_0=121918.90616 +a=6378249.144808011 +b=6356514.966204134 +to_meter=0.3047972654 +no_defs"},
    {
    24200, "epsg", 24200, "JAD69 / Jamaica National Grid",
        "+proj=lcc +lat_1=18 +lat_0=18 +lon_0=-77 +k_0=1 +x_0=250000 +y_0=150000 +ellps=clrk66 +units=m +no_defs"},
    {
    24305, "epsg", 24305, "Kalianpur 1937 / UTM zone 45N",
        "+proj=utm +zone=45 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    24306, "epsg", 24306, "Kalianpur 1937 / UTM zone 46N",
        "+proj=utm +zone=46 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    24311, "epsg", 24311, "Kalianpur 1962 / UTM zone 41N",
        "+proj=utm +zone=41 +a=6377301.243 +b=6356100.230165384 +units=m +no_defs"},
    {
    24312, "epsg", 24312, "Kalianpur 1962 / UTM zone 42N",
        "+proj=utm +zone=42 +a=6377301.243 +b=6356100.230165384 +units=m +no_defs"},
    {
    24313, "epsg", 24313, "Kalianpur 1962 / UTM zone 43N",
        "+proj=utm +zone=43 +a=6377301.243 +b=6356100.230165384 +units=m +no_defs"},
    {
    24342, "epsg", 24342, "Kalianpur 1975 / UTM zone 42N",
        "+proj=utm +zone=42 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24343, "epsg", 24343, "Kalianpur 1975 / UTM zone 43N",
        "+proj=utm +zone=43 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24344, "epsg", 24344, "Kalianpur 1975 / UTM zone 44N",
        "+proj=utm +zone=44 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24345, "epsg", 24345, "Kalianpur 1975 / UTM zone 45N",
        "+proj=utm +zone=45 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24346, "epsg", 24346, "Kalianpur 1975 / UTM zone 46N",
        "+proj=utm +zone=46 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24347, "epsg", 24347, "Kalianpur 1975 / UTM zone 47N",
        "+proj=utm +zone=47 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24370, "epsg", 24370, "Kalianpur 1880 / India zone 0",
        "+proj=lcc +lat_1=39.5 +lat_0=39.5 +lon_0=68 +k_0=0.99846154 +x_0=2153865.73916853 +y_0=2368292.194628102 +a=6377299.36559538 +b=6356098.359005156 +to_meter=0.9143985307444408 +no_defs"},
    {
    24371, "epsg", 24371, "Kalianpur 1880 / India zone I",
        "+proj=lcc +lat_1=32.5 +lat_0=32.5 +lon_0=68 +k_0=0.99878641 +x_0=2743195.592233322 +y_0=914398.5307444407 +a=6377299.36559538 +b=6356098.359005156 +to_meter=0.9143985307444408 +no_defs"},
    {
    24372, "epsg", 24372, "Kalianpur 1880 / India zone IIa",
        "+proj=lcc +lat_1=26 +lat_0=26 +lon_0=74 +k_0=0.99878641 +x_0=2743195.592233322 +y_0=914398.5307444407 +a=6377299.36559538 +b=6356098.359005156 +to_meter=0.9143985307444408 +no_defs"},
    {
    24373, "epsg", 24373, "Kalianpur 1880 / India zone III",
        "+proj=lcc +lat_1=19 +lat_0=19 +lon_0=80 +k_0=0.99878641 +x_0=2743195.592233322 +y_0=914398.5307444407 +a=6377299.36559538 +b=6356098.359005156 +to_meter=0.9143985307444408 +no_defs"},
    {
    24374, "epsg", 24374, "Kalianpur 1880 / India zone IV",
        "+proj=lcc +lat_1=12 +lat_0=12 +lon_0=80 +k_0=0.99878641 +x_0=2743195.592233322 +y_0=914398.5307444407 +a=6377299.36559538 +b=6356098.359005156 +to_meter=0.9143985307444408 +no_defs"},
    {
    24375, "epsg", 24375, "Kalianpur 1937 / India zone IIb",
        "+proj=lcc +lat_1=26 +lat_0=26 +lon_0=90 +k_0=0.99878641 +x_0=2743185.69 +y_0=914395.23 +a=6377276.345 +b=6356075.41314024 +units=m +no_defs"},
    {
    24376, "epsg", 24376, "Kalianpur 1962 / India zone I",
        "+proj=lcc +lat_1=32.5 +lat_0=32.5 +lon_0=68 +k_0=0.99878641 +x_0=2743196.4 +y_0=914398.8 +a=6377301.243 +b=6356100.230165384 +units=m +no_defs"},
    {
    24377, "epsg", 24377, "Kalianpur 1962 / India zone IIa",
        "+proj=lcc +lat_1=26 +lat_0=26 +lon_0=74 +k_0=0.99878641 +x_0=2743196.4 +y_0=914398.8 +a=6377301.243 +b=6356100.230165384 +units=m +no_defs"},
    {
    24378, "epsg", 24378, "Kalianpur 1975 / India zone I",
        "+proj=lcc +lat_1=32.5 +lat_0=32.5 +lon_0=68 +k_0=0.99878641 +x_0=2743195.5 +y_0=914398.5 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24379, "epsg", 24379, "Kalianpur 1975 / India zone IIa",
        "+proj=lcc +lat_1=26 +lat_0=26 +lon_0=74 +k_0=0.99878641 +x_0=2743195.5 +y_0=914398.5 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24380, "epsg", 24380, "Kalianpur 1975 / India zone IIb",
        "+proj=lcc +lat_1=26 +lat_0=26 +lon_0=90 +k_0=0.99878641 +x_0=2743195.5 +y_0=914398.5 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24381, "epsg", 24381, "Kalianpur 1975 / India zone III",
        "+proj=lcc +lat_1=19 +lat_0=19 +lon_0=80 +k_0=0.99878641 +x_0=2743195.5 +y_0=914398.5 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24382, "epsg", 24382, "Kalianpur 1880 / India zone IIb",
        "+proj=lcc +lat_1=26 +lat_0=26 +lon_0=90 +k_0=0.99878641 +x_0=2743195.592233322 +y_0=914398.5307444407 +a=6377299.36559538 +b=6356098.359005156 +to_meter=0.9143985307444408 +no_defs"},
    {
    24383, "epsg", 24383, "Kalianpur 1975 / India zone IV",
        "+proj=lcc +lat_1=12 +lat_0=12 +lon_0=80 +k_0=0.99878641 +x_0=2743195.5 +y_0=914398.5 +a=6377299.151 +b=6356098.145120132 +towgs84=295,736,257,0,0,0,0 +units=m +no_defs"},
    {
    24500, "epsg", 24500, "Kertau 1968 / Singapore Grid",
        "+proj=cass +lat_0=1.287646666666667 +lon_0=103.8530022222222 +x_0=30000 +y_0=30000 +a=6377304.063 +b=6356103.038993155 +towgs84=-11,851,5,0,0,0,0 +units=m +no_defs"},
    {
    24547, "epsg", 24547, "Kertau 1968 / UTM zone 47N",
        "+proj=utm +zone=47 +a=6377304.063 +b=6356103.038993155 +towgs84=-11,851,5,0,0,0,0 +units=m +no_defs"},
    {
    24548, "epsg", 24548, "Kertau 1968 / UTM zone 48N",
        "+proj=utm +zone=48 +a=6377304.063 +b=6356103.038993155 +towgs84=-11,851,5,0,0,0,0 +units=m +no_defs"},
    {
    24571, "epsg", 24571, "Kertau / R.S.O. Malaya (ch) (deprecated)",
        "+proj=omerc +lat_0=4 +lonc=102.25 +alpha=323.0257905 +k=0.99984 +x_0=804671.2997750348 +y_0=0 +a=6377304.063 +b=6356103.038993155 +towgs84=-11,851,5,0,0,0,0 +to_meter=20.11678249437587 +no_defs"},
    {
    24600, "epsg", 24600, "KOC Lambert",
        "+proj=lcc +lat_1=32.5 +lat_0=32.5 +lon_0=45 +k_0=0.9987864078000001 +x_0=1500000 +y_0=1166200 +ellps=clrk80 +towgs84=-294.7,-200.1,525.5,0,0,0,0 +units=m +no_defs"},
    {
    24718, "epsg", 24718, "La Canoa / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=intl +towgs84=-273.5,110.6,-357.9,0,0,0,0 +units=m +no_defs"},
    {
    24719, "epsg", 24719, "La Canoa / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=intl +towgs84=-273.5,110.6,-357.9,0,0,0,0 +units=m +no_defs"},
    {
    24720, "epsg", 24720, "La Canoa / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=intl +towgs84=-273.5,110.6,-357.9,0,0,0,0 +units=m +no_defs"},
    {
    24817, "epsg", 24817, "PSAD56 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=intl +units=m +no_defs"},
    {
    24818, "epsg", 24818, "PSAD56 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=intl +units=m +no_defs"},
    {
    24819, "epsg", 24819, "PSAD56 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=intl +units=m +no_defs"},
    {
    24820, "epsg", 24820, "PSAD56 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=intl +units=m +no_defs"},
    {
    24821, "epsg", 24821, "PSAD56 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=intl +units=m +no_defs"},
    {
    24877, "epsg", 24877, "PSAD56 / UTM zone 17S",
        "+proj=utm +zone=17 +south +ellps=intl +units=m +no_defs"},
    {
    24878, "epsg", 24878, "PSAD56 / UTM zone 18S",
        "+proj=utm +zone=18 +south +ellps=intl +units=m +no_defs"},
    {
    24879, "epsg", 24879, "PSAD56 / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=intl +units=m +no_defs"},
    {
    24880, "epsg", 24880, "PSAD56 / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=intl +units=m +no_defs"},
    {
    24881, "epsg", 24881, "PSAD56 / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=intl +units=m +no_defs"},
    {
    24882, "epsg", 24882, "PSAD56 / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=intl +units=m +no_defs"},
    {
    24891, "epsg", 24891, "PSAD56 / Peru west zone",
        "+proj=tmerc +lat_0=-6 +lon_0=-80.5 +k=0.99983008 +x_0=222000 +y_0=1426834.743 +ellps=intl +units=m +no_defs"},
    {
    24892, "epsg", 24892, "PSAD56 / Peru central zone",
        "+proj=tmerc +lat_0=-9.5 +lon_0=-76 +k=0.99932994 +x_0=720000 +y_0=1039979.159 +ellps=intl +units=m +no_defs"},
    {
    24893, "epsg", 24893, "PSAD56 / Peru east zone",
        "+proj=tmerc +lat_0=-9.5 +lon_0=-70.5 +k=0.99952992 +x_0=1324000 +y_0=1040084.558 +ellps=intl +units=m +no_defs"},
    {
    25000, "epsg", 25000, "Leigon / Ghana Metre Grid",
        "+proj=tmerc +lat_0=4.666666666666667 +lon_0=-1 +k=0.99975 +x_0=274319.51 +y_0=0 +ellps=clrk80 +towgs84=-130,29,364,0,0,0,0 +units=m +no_defs"},
    {
    25231, "epsg", 25231, "Lome / UTM zone 31N",
        "+proj=utm +zone=31 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    25391, "epsg", 25391, "Luzon 1911 / Philippines zone I",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    25392, "epsg", 25392, "Luzon 1911 / Philippines zone II",
        "+proj=tmerc +lat_0=0 +lon_0=119 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    25393, "epsg", 25393, "Luzon 1911 / Philippines zone III",
        "+proj=tmerc +lat_0=0 +lon_0=121 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    25394, "epsg", 25394, "Luzon 1911 / Philippines zone IV",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    25395, "epsg", 25395, "Luzon 1911 / Philippines zone V",
        "+proj=tmerc +lat_0=0 +lon_0=125 +k=0.99995 +x_0=500000 +y_0=0 +ellps=clrk66 +units=m +no_defs"},
    {
    25700, "epsg", 25700, "Makassar (Jakarta) / NEIEZ (deprecated)",
        "+proj=merc +lon_0=110 +k=0.997 +x_0=3900000 +y_0=900000 +ellps=bessel +towgs84=-587.8,519.75,145.76,0,0,0,0 +pm=jakarta +units=m +no_defs"},
    {
    25828, "epsg", 25828, "ETRS89 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=GRS80 +units=m +no_defs"},
    {
    25829, "epsg", 25829, "ETRS89 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=GRS80 +units=m +no_defs"},
    {
    25830, "epsg", 25830, "ETRS89 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=GRS80 +units=m +no_defs"},
    {
    25831, "epsg", 25831, "ETRS89 / UTM zone 31N",
        "+proj=utm +zone=31 +ellps=GRS80 +units=m +no_defs"},
    {
    25832, "epsg", 25832, "ETRS89 / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=GRS80 +units=m +no_defs"},
    {
    25833, "epsg", 25833, "ETRS89 / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=GRS80 +units=m +no_defs"},
    {
    25834, "epsg", 25834, "ETRS89 / UTM zone 34N",
        "+proj=utm +zone=34 +ellps=GRS80 +units=m +no_defs"},
    {
    25835, "epsg", 25835, "ETRS89 / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=GRS80 +units=m +no_defs"},
    {
    25836, "epsg", 25836, "ETRS89 / UTM zone 36N",
        "+proj=utm +zone=36 +ellps=GRS80 +units=m +no_defs"},
    {
    25837, "epsg", 25837, "ETRS89 / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=GRS80 +units=m +no_defs"},
    {
    25838, "epsg", 25838, "ETRS89 / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=GRS80 +units=m +no_defs"},
    {
    25884, "epsg", 25884, "ETRS89 / TM Baltic93",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9996 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    25932, "epsg", 25932, "Malongo 1987 / UTM zone 32S",
        "+proj=utm +zone=32 +south +ellps=intl +units=m +no_defs"},
    {
    26191, "epsg", 26191, "Merchich / Nord Maroc",
        "+proj=lcc +lat_1=33.3 +lat_0=33.3 +lon_0=-5.4 +k_0=0.999625769 +x_0=500000 +y_0=300000 +a=6378249.2 +b=6356515 +towgs84=31,146,47,0,0,0,0 +units=m +no_defs"},
    {
    26192, "epsg", 26192, "Merchich / Sud Maroc",
        "+proj=lcc +lat_1=29.7 +lat_0=29.7 +lon_0=-5.4 +k_0=0.9996155960000001 +x_0=500000 +y_0=300000 +a=6378249.2 +b=6356515 +towgs84=31,146,47,0,0,0,0 +units=m +no_defs"},
    {
    26193, "epsg", 26193, "Merchich / Sahara (deprecated)",
        "+proj=lcc +lat_1=26.1 +lat_0=26.1 +lon_0=-5.4 +k_0=0.9996 +x_0=1200000 +y_0=400000 +a=6378249.2 +b=6356515 +towgs84=31,146,47,0,0,0,0 +units=m +no_defs"},
    {
    26194, "epsg", 26194, "Merchich / Sahara Nord",
        "+proj=lcc +lat_1=26.1 +lat_0=26.1 +lon_0=-5.4 +k_0=0.999616304 +x_0=1200000 +y_0=400000 +a=6378249.2 +b=6356515 +towgs84=31,146,47,0,0,0,0 +units=m +no_defs"},
    {
    26195, "epsg", 26195, "Merchich / Sahara Sud",
        "+proj=lcc +lat_1=22.5 +lat_0=22.5 +lon_0=-5.4 +k_0=0.999616437 +x_0=1500000 +y_0=400000 +a=6378249.2 +b=6356515 +towgs84=31,146,47,0,0,0,0 +units=m +no_defs"},
    {
    26237, "epsg", 26237, "Massawa / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=bessel +towgs84=639,405,60,0,0,0,0 +units=m +no_defs"},
    {
    26331, "epsg", 26331, "Minna / UTM zone 31N",
        "+proj=utm +zone=31 +ellps=clrk80 +units=m +no_defs"},
    {
    26332, "epsg", 26332, "Minna / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=clrk80 +units=m +no_defs"},
    {
    26391, "epsg", 26391, "Minna / Nigeria West Belt",
        "+proj=tmerc +lat_0=4 +lon_0=4.5 +k=0.99975 +x_0=230738.26 +y_0=0 +ellps=clrk80 +units=m +no_defs"},
    {
    26392, "epsg", 26392, "Minna / Nigeria Mid Belt",
        "+proj=tmerc +lat_0=4 +lon_0=8.5 +k=0.99975 +x_0=670553.98 +y_0=0 +ellps=clrk80 +units=m +no_defs"},
    {
    26393, "epsg", 26393, "Minna / Nigeria East Belt",
        "+proj=tmerc +lat_0=4 +lon_0=12.5 +k=0.99975 +x_0=1110369.7 +y_0=0 +ellps=clrk80 +units=m +no_defs"},
    {
    26432, "epsg", 26432, "Mhast / UTM zone 32S (deprecated)",
        "+proj=utm +zone=32 +south +ellps=intl +towgs84=-252.95,-4.11,-96.38,0,0,0,0 +units=m +no_defs"},
    {
    26591, "epsg", 26591, "Monte Mario (Rome) / Italy zone 1 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-3.45233333333333 +k=0.9996 +x_0=1500000 +y_0=0 +ellps=intl +pm=rome +units=m +no_defs"},
    {
    26592, "epsg", 26592, "Monte Mario (Rome) / Italy zone 2 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=2.54766666666666 +k=0.9996 +x_0=2520000 +y_0=0 +ellps=intl +pm=rome +units=m +no_defs"},
    {
    26632, "epsg", 26632, "M'poraloko / UTM zone 32N",
        "+proj=utm +zone=32 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    26692, "epsg", 26692, "M'poraloko / UTM zone 32S",
        "+proj=utm +zone=32 +south +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    26701, "epsg", 26701, "NAD27 / UTM zone 1N",
        "+proj=utm +zone=1 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26702, "epsg", 26702, "NAD27 / UTM zone 2N",
        "+proj=utm +zone=2 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26703, "epsg", 26703, "NAD27 / UTM zone 3N",
        "+proj=utm +zone=3 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26704, "epsg", 26704, "NAD27 / UTM zone 4N",
        "+proj=utm +zone=4 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26705, "epsg", 26705, "NAD27 / UTM zone 5N",
        "+proj=utm +zone=5 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26706, "epsg", 26706, "NAD27 / UTM zone 6N",
        "+proj=utm +zone=6 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26707, "epsg", 26707, "NAD27 / UTM zone 7N",
        "+proj=utm +zone=7 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26708, "epsg", 26708, "NAD27 / UTM zone 8N",
        "+proj=utm +zone=8 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26709, "epsg", 26709, "NAD27 / UTM zone 9N",
        "+proj=utm +zone=9 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26710, "epsg", 26710, "NAD27 / UTM zone 10N",
        "+proj=utm +zone=10 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26711, "epsg", 26711, "NAD27 / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26712, "epsg", 26712, "NAD27 / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26713, "epsg", 26713, "NAD27 / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26714, "epsg", 26714, "NAD27 / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26715, "epsg", 26715, "NAD27 / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26716, "epsg", 26716, "NAD27 / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26717, "epsg", 26717, "NAD27 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26718, "epsg", 26718, "NAD27 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26719, "epsg", 26719, "NAD27 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26720, "epsg", 26720, "NAD27 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26721, "epsg", 26721, "NAD27 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26722, "epsg", 26722, "NAD27 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    26729, "epsg", 26729, "NAD27 / Alabama East",
        "+proj=tmerc +lat_0=30.5 +lon_0=-85.83333333333333 +k=0.99996 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26730, "epsg", 26730, "NAD27 / Alabama West",
        "+proj=tmerc +lat_0=30 +lon_0=-87.5 +k=0.999933333 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26731, "epsg", 26731, "NAD27 / Alaska zone 1",
        "+proj=omerc +lat_0=57 +lonc=-133.6666666666667 +alpha=323.1301023611111 +k=0.9999 +x_0=5000000.001016002 +y_0=-5000000.001016002 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26732, "epsg", 26732, "NAD27 / Alaska zone 2",
        "+proj=tmerc +lat_0=54 +lon_0=-142 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26733, "epsg", 26733, "NAD27 / Alaska zone 3",
        "+proj=tmerc +lat_0=54 +lon_0=-146 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26734, "epsg", 26734, "NAD27 / Alaska zone 4",
        "+proj=tmerc +lat_0=54 +lon_0=-150 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26735, "epsg", 26735, "NAD27 / Alaska zone 5",
        "+proj=tmerc +lat_0=54 +lon_0=-154 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26736, "epsg", 26736, "NAD27 / Alaska zone 6",
        "+proj=tmerc +lat_0=54 +lon_0=-158 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26737, "epsg", 26737, "NAD27 / Alaska zone 7",
        "+proj=tmerc +lat_0=54 +lon_0=-162 +k=0.9999 +x_0=213360.4267208534 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26738, "epsg", 26738, "NAD27 / Alaska zone 8",
        "+proj=tmerc +lat_0=54 +lon_0=-166 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26739, "epsg", 26739, "NAD27 / Alaska zone 9",
        "+proj=tmerc +lat_0=54 +lon_0=-170 +k=0.9999 +x_0=182880.3657607315 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26740, "epsg", 26740, "NAD27 / Alaska zone 10",
        "+proj=lcc +lat_1=53.83333333333334 +lat_2=51.83333333333334 +lat_0=51 +lon_0=-176 +x_0=914401.8288036576 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26741, "epsg", 26741, "NAD27 / California zone I",
        "+proj=lcc +lat_1=41.66666666666666 +lat_2=40 +lat_0=39.33333333333334 +lon_0=-122 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26742, "epsg", 26742, "NAD27 / California zone II",
        "+proj=lcc +lat_1=39.83333333333334 +lat_2=38.33333333333334 +lat_0=37.66666666666666 +lon_0=-122 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26743, "epsg", 26743, "NAD27 / California zone III",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.06666666666667 +lat_0=36.5 +lon_0=-120.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26744, "epsg", 26744, "NAD27 / California zone IV",
        "+proj=lcc +lat_1=37.25 +lat_2=36 +lat_0=35.33333333333334 +lon_0=-119 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26745, "epsg", 26745, "NAD27 / California zone V",
        "+proj=lcc +lat_1=35.46666666666667 +lat_2=34.03333333333333 +lat_0=33.5 +lon_0=-118 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26746, "epsg", 26746, "NAD27 / California zone VI",
        "+proj=lcc +lat_1=33.88333333333333 +lat_2=32.78333333333333 +lat_0=32.16666666666666 +lon_0=-116.25 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26747, "epsg", 26747, "NAD27 / California zone VII (deprecated)",
        "+proj=lcc +lat_1=34.41666666666666 +lat_2=33.86666666666667 +lat_0=34.13333333333333 +lon_0=-118.3333333333333 +x_0=1276106.450596901 +y_0=127079.524511049 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26748, "epsg", 26748, "NAD27 / Arizona East",
        "+proj=tmerc +lat_0=31 +lon_0=-110.1666666666667 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26749, "epsg", 26749, "NAD27 / Arizona Central",
        "+proj=tmerc +lat_0=31 +lon_0=-111.9166666666667 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26750, "epsg", 26750, "NAD27 / Arizona West",
        "+proj=tmerc +lat_0=31 +lon_0=-113.75 +k=0.999933333 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26751, "epsg", 26751, "NAD27 / Arkansas North",
        "+proj=lcc +lat_1=36.23333333333333 +lat_2=34.93333333333333 +lat_0=34.33333333333334 +lon_0=-92 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26752, "epsg", 26752, "NAD27 / Arkansas South",
        "+proj=lcc +lat_1=34.76666666666667 +lat_2=33.3 +lat_0=32.66666666666666 +lon_0=-92 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26753, "epsg", 26753, "NAD27 / Colorado North",
        "+proj=lcc +lat_1=39.71666666666667 +lat_2=40.78333333333333 +lat_0=39.33333333333334 +lon_0=-105.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26754, "epsg", 26754, "NAD27 / Colorado Central",
        "+proj=lcc +lat_1=39.75 +lat_2=38.45 +lat_0=37.83333333333334 +lon_0=-105.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26755, "epsg", 26755, "NAD27 / Colorado South",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.23333333333333 +lat_0=36.66666666666666 +lon_0=-105.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26756, "epsg", 26756, "NAD27 / Connecticut",
        "+proj=lcc +lat_1=41.86666666666667 +lat_2=41.2 +lat_0=40.83333333333334 +lon_0=-72.75 +x_0=182880.3657607315 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26757, "epsg", 26757, "NAD27 / Delaware",
        "+proj=tmerc +lat_0=38 +lon_0=-75.41666666666667 +k=0.999995 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26758, "epsg", 26758, "NAD27 / Florida East",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-81 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26759, "epsg", 26759, "NAD27 / Florida West",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-82 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26760, "epsg", 26760, "NAD27 / Florida North",
        "+proj=lcc +lat_1=30.75 +lat_2=29.58333333333333 +lat_0=29 +lon_0=-84.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26766, "epsg", 26766, "NAD27 / Georgia East",
        "+proj=tmerc +lat_0=30 +lon_0=-82.16666666666667 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26767, "epsg", 26767, "NAD27 / Georgia West",
        "+proj=tmerc +lat_0=30 +lon_0=-84.16666666666667 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26768, "epsg", 26768, "NAD27 / Idaho East",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-112.1666666666667 +k=0.9999473679999999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26769, "epsg", 26769, "NAD27 / Idaho Central",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-114 +k=0.9999473679999999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26770, "epsg", 26770, "NAD27 / Idaho West",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-115.75 +k=0.999933333 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26771, "epsg", 26771, "NAD27 / Illinois East",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-88.33333333333333 +k=0.9999749999999999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26772, "epsg", 26772, "NAD27 / Illinois West",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-90.16666666666667 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26773, "epsg", 26773, "NAD27 / Indiana East",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26774, "epsg", 26774, "NAD27 / Indiana West",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26775, "epsg", 26775, "NAD27 / Iowa North",
        "+proj=lcc +lat_1=43.26666666666667 +lat_2=42.06666666666667 +lat_0=41.5 +lon_0=-93.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26776, "epsg", 26776, "NAD27 / Iowa South",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.61666666666667 +lat_0=40 +lon_0=-93.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26777, "epsg", 26777, "NAD27 / Kansas North",
        "+proj=lcc +lat_1=39.78333333333333 +lat_2=38.71666666666667 +lat_0=38.33333333333334 +lon_0=-98 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26778, "epsg", 26778, "NAD27 / Kansas South",
        "+proj=lcc +lat_1=38.56666666666667 +lat_2=37.26666666666667 +lat_0=36.66666666666666 +lon_0=-98.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26779, "epsg", 26779, "NAD27 / Kentucky North",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=38.96666666666667 +lat_0=37.5 +lon_0=-84.25 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26780, "epsg", 26780, "NAD27 / Kentucky South",
        "+proj=lcc +lat_1=36.73333333333333 +lat_2=37.93333333333333 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26781, "epsg", 26781, "NAD27 / Louisiana North",
        "+proj=lcc +lat_1=31.16666666666667 +lat_2=32.66666666666666 +lat_0=30.66666666666667 +lon_0=-92.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26782, "epsg", 26782, "NAD27 / Louisiana South",
        "+proj=lcc +lat_1=29.3 +lat_2=30.7 +lat_0=28.66666666666667 +lon_0=-91.33333333333333 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26783, "epsg", 26783, "NAD27 / Maine East",
        "+proj=tmerc +lat_0=43.83333333333334 +lon_0=-68.5 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26784, "epsg", 26784, "NAD27 / Maine West",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26785, "epsg", 26785, "NAD27 / Maryland",
        "+proj=lcc +lat_1=38.3 +lat_2=39.45 +lat_0=37.83333333333334 +lon_0=-77 +x_0=243840.4876809754 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26786, "epsg", 26786, "NAD27 / Massachusetts Mainland",
        "+proj=lcc +lat_1=41.71666666666667 +lat_2=42.68333333333333 +lat_0=41 +lon_0=-71.5 +x_0=182880.3657607315 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26787, "epsg", 26787, "NAD27 / Massachusetts Island",
        "+proj=lcc +lat_1=41.28333333333333 +lat_2=41.48333333333333 +lat_0=41 +lon_0=-70.5 +x_0=60960.12192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26791, "epsg", 26791, "NAD27 / Minnesota North",
        "+proj=lcc +lat_1=47.03333333333333 +lat_2=48.63333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26792, "epsg", 26792, "NAD27 / Minnesota Central",
        "+proj=lcc +lat_1=45.61666666666667 +lat_2=47.05 +lat_0=45 +lon_0=-94.25 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26793, "epsg", 26793, "NAD27 / Minnesota South",
        "+proj=lcc +lat_1=43.78333333333333 +lat_2=45.21666666666667 +lat_0=43 +lon_0=-94 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26794, "epsg", 26794, "NAD27 / Mississippi East",
        "+proj=tmerc +lat_0=29.66666666666667 +lon_0=-88.83333333333333 +k=0.99996 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26795, "epsg", 26795, "NAD27 / Mississippi West",
        "+proj=tmerc +lat_0=30.5 +lon_0=-90.33333333333333 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26796, "epsg", 26796, "NAD27 / Missouri East",
        "+proj=tmerc +lat_0=35.83333333333334 +lon_0=-90.5 +k=0.999933333 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26797, "epsg", 26797, "NAD27 / Missouri Central",
        "+proj=tmerc +lat_0=35.83333333333334 +lon_0=-92.5 +k=0.999933333 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26798, "epsg", 26798, "NAD27 / Missouri West",
        "+proj=tmerc +lat_0=36.16666666666666 +lon_0=-94.5 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26799, "epsg", 26799, "NAD27 / California zone VII",
        "+proj=lcc +lat_1=34.41666666666666 +lat_2=33.86666666666667 +lat_0=34.13333333333333 +lon_0=-118.3333333333333 +x_0=1276106.450596901 +y_0=1268253.006858014 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    26801, "epsg", 26801, "NAD Michigan / Michigan East",
        "+proj=tmerc +lat_0=41.5 +lon_0=-83.66666666666667 +k=0.999942857 +x_0=152400.3048006096 +y_0=0 +a=6378450.047548896 +b=6356826.621488444 +units=us-ft +no_defs"},
    {
    26802, "epsg", 26802, "NAD Michigan / Michigan Old Central",
        "+proj=tmerc +lat_0=41.5 +lon_0=-85.75 +k=0.999909091 +x_0=152400.3048006096 +y_0=0 +a=6378450.047548896 +b=6356826.621488444 +units=us-ft +no_defs"},
    {
    26803, "epsg", 26803, "NAD Michigan / Michigan West",
        "+proj=tmerc +lat_0=41.5 +lon_0=-88.75 +k=0.999909091 +x_0=152400.3048006096 +y_0=0 +a=6378450.047548896 +b=6356826.621488444 +units=us-ft +no_defs"},
    {
    26811, "epsg", 26811, "NAD Michigan / Michigan North",
        "+proj=lcc +lat_1=45.48333333333333 +lat_2=47.08333333333334 +lat_0=44.78333333333333 +lon_0=-87 +x_0=609601.2192024384 +y_0=0 +a=6378450.047548896 +b=6356826.621488444 +units=us-ft +no_defs"},
    {
    26812, "epsg", 26812, "NAD Michigan / Michigan Central",
        "+proj=lcc +lat_1=44.18333333333333 +lat_2=45.7 +lat_0=43.31666666666667 +lon_0=-84.33333333333333 +x_0=609601.2192024384 +y_0=0 +a=6378450.047548896 +b=6356826.621488444 +units=us-ft +no_defs"},
    {
    26813, "epsg", 26813, "NAD Michigan / Michigan South",
        "+proj=lcc +lat_1=42.1 +lat_2=43.66666666666666 +lat_0=41.5 +lon_0=-84.33333333333333 +x_0=609601.2192024384 +y_0=0 +a=6378450.047548896 +b=6356826.621488444 +units=us-ft +no_defs"},
    {
    26814, "epsg", 26814, "NAD83 / Maine East (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26815, "epsg", 26815, "NAD83 / Maine West (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26819, "epsg", 26819, "NAD83 / Minnesota North (ftUS) (deprecated)",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26820, "epsg", 26820, "NAD83 / Minnesota Central (ftUS) (deprecated)",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26821, "epsg", 26821, "NAD83 / Minnesota South (ftUS) (deprecated)",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26822, "epsg", 26822, "NAD83 / Nebraska (ftUS) (deprecated)",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000.0000101601 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26823, "epsg", 26823, "NAD83 / West Virginia North (ftUS) (deprecated)",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=1968500 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26824, "epsg", 26824, "NAD83 / West Virginia South (ftUS) (deprecated)",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=1968500 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26825, "epsg", 26825, "NAD83(HARN) / Maine East (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26826, "epsg", 26826, "NAD83(HARN) / Maine West (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26830, "epsg", 26830, "NAD83(HARN) / Minnesota North (ftUS) (deprecated)",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +units=m +no_defs"},
    {
    26831, "epsg", 26831,
        "NAD83(HARN) / Minnesota Central (ftUS) (deprecated)",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +units=m +no_defs"},
    {
    26832, "epsg", 26832, "NAD83(HARN) / Minnesota South (ftUS) (deprecated)",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +units=m +no_defs"},
    {
    26833, "epsg", 26833, "NAD83(HARN) / Nebraska (ftUS) (deprecated)",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000.0000101601 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26834, "epsg", 26834,
        "NAD83(HARN) / West Virginia North (ftUS) (deprecated)",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=1968500 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26835, "epsg", 26835,
        "NAD83(HARN) / West Virginia South (ftUS) (deprecated)",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=1968500 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26836, "epsg", 26836, "NAD83(NSRS2007) / Maine East (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    26837, "epsg", 26837, "NAD83(NSRS2007) / Maine West (ftUS) (deprecated)",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    26841, "epsg", 26841,
        "NAD83(NSRS2007) / Minnesota North (ftUS) (deprecated)",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    26842, "epsg", 26842,
        "NAD83(NSRS2007) / Minnesota Central (ftUS) (deprecated)",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    26843, "epsg", 26843,
        "NAD83(NSRS2007) / Minnesota South (ftUS) (deprecated)",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000.0000101601 +y_0=99999.99998984 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    26844, "epsg", 26844, "NAD83(NSRS2007) / Nebraska (ftUS) (deprecated)",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000.0000101601 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    26845, "epsg", 26845,
        "NAD83(NSRS2007) / West Virginia North (ftUS) (deprecated)",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=1968500 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    26846, "epsg", 26846,
        "NAD83(NSRS2007) / West Virginia South (ftUS) (deprecated)",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=1968500 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    26847, "epsg", 26847, "NAD83 / Maine East (ftUS)",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    26848, "epsg", 26848, "NAD83 / Maine West (ftUS)",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    26849, "epsg", 26849, "NAD83 / Minnesota North (ftUS)",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    26850, "epsg", 26850, "NAD83 / Minnesota Central (ftUS)",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    26851, "epsg", 26851, "NAD83 / Minnesota South (ftUS)",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    26852, "epsg", 26852, "NAD83 / Nebraska (ftUS)",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000.00001016 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    26853, "epsg", 26853, "NAD83 / West Virginia North (ftUS)",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    26854, "epsg", 26854, "NAD83 / West Virginia South (ftUS)",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    26855, "epsg", 26855, "NAD83(HARN) / Maine East (ftUS)",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    26856, "epsg", 26856, "NAD83(HARN) / Maine West (ftUS)",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    26857, "epsg", 26857, "NAD83(HARN) / Minnesota North (ftUS)",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    26858, "epsg", 26858, "NAD83(HARN) / Minnesota Central (ftUS)",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    26859, "epsg", 26859, "NAD83(HARN) / Minnesota South (ftUS)",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    26860, "epsg", 26860, "NAD83(HARN) / Nebraska (ftUS)",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000.00001016 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    26861, "epsg", 26861, "NAD83(HARN) / West Virginia North (ftUS)",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    26862, "epsg", 26862, "NAD83(HARN) / West Virginia South (ftUS)",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=600000 +y_0=0 +ellps=GRS80 +units=us-ft +no_defs"},
    {
    26863, "epsg", 26863, "NAD83(NSRS2007) / Maine East (ftUS)",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000.0000000001 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    26864, "epsg", 26864, "NAD83(NSRS2007) / Maine West (ftUS)",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    26865, "epsg", 26865, "NAD83(NSRS2007) / Minnesota North (ftUS)",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    26866, "epsg", 26866, "NAD83(NSRS2007) / Minnesota Central (ftUS)",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    26867, "epsg", 26867, "NAD83(NSRS2007) / Minnesota South (ftUS)",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    26868, "epsg", 26868, "NAD83(NSRS2007) / Nebraska (ftUS)",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000.00001016 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    26869, "epsg", 26869, "NAD83(NSRS2007) / West Virginia North (ftUS)",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    26870, "epsg", 26870, "NAD83(NSRS2007) / West Virginia South (ftUS)",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=600000 +y_0=0 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs"},
    {
    26891, "epsg", 26891, "NAD83(CSRS) / MTM zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=-82.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26892, "epsg", 26892, "NAD83(CSRS) / MTM zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=-81 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26893, "epsg", 26893, "NAD83(CSRS) / MTM zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=-84 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26894, "epsg", 26894, "NAD83(CSRS) / MTM zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=-87 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26895, "epsg", 26895, "NAD83(CSRS) / MTM zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=-90 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26896, "epsg", 26896, "NAD83(CSRS) / MTM zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=-93 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26897, "epsg", 26897, "NAD83(CSRS) / MTM zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=-96 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26898, "epsg", 26898, "NAD83(CSRS) / MTM zone 1",
        "+proj=tmerc +lat_0=0 +lon_0=-53 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26899, "epsg", 26899, "NAD83(CSRS) / MTM zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=-56 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    26901, "epsg", 26901, "NAD83 / UTM zone 1N",
        "+proj=utm +zone=1 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26902, "epsg", 26902, "NAD83 / UTM zone 2N",
        "+proj=utm +zone=2 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26903, "epsg", 26903, "NAD83 / UTM zone 3N",
        "+proj=utm +zone=3 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26904, "epsg", 26904, "NAD83 / UTM zone 4N",
        "+proj=utm +zone=4 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26905, "epsg", 26905, "NAD83 / UTM zone 5N",
        "+proj=utm +zone=5 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26906, "epsg", 26906, "NAD83 / UTM zone 6N",
        "+proj=utm +zone=6 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26907, "epsg", 26907, "NAD83 / UTM zone 7N",
        "+proj=utm +zone=7 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26908, "epsg", 26908, "NAD83 / UTM zone 8N",
        "+proj=utm +zone=8 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26909, "epsg", 26909, "NAD83 / UTM zone 9N",
        "+proj=utm +zone=9 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26910, "epsg", 26910, "NAD83 / UTM zone 10N",
        "+proj=utm +zone=10 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26911, "epsg", 26911, "NAD83 / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26912, "epsg", 26912, "NAD83 / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26913, "epsg", 26913, "NAD83 / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26914, "epsg", 26914, "NAD83 / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26915, "epsg", 26915, "NAD83 / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26916, "epsg", 26916, "NAD83 / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26917, "epsg", 26917, "NAD83 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26918, "epsg", 26918, "NAD83 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26919, "epsg", 26919, "NAD83 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26920, "epsg", 26920, "NAD83 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26921, "epsg", 26921, "NAD83 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26922, "epsg", 26922, "NAD83 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26923, "epsg", 26923, "NAD83 / UTM zone 23N",
        "+proj=utm +zone=23 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26929, "epsg", 26929, "NAD83 / Alabama East",
        "+proj=tmerc +lat_0=30.5 +lon_0=-85.83333333333333 +k=0.99996 +x_0=200000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26930, "epsg", 26930, "NAD83 / Alabama West",
        "+proj=tmerc +lat_0=30 +lon_0=-87.5 +k=0.999933333 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26931, "epsg", 26931, "NAD83 / Alaska zone 1",
        "+proj=omerc +lat_0=57 +lonc=-133.6666666666667 +alpha=323.1301023611111 +k=0.9999 +x_0=5000000 +y_0=-5000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26932, "epsg", 26932, "NAD83 / Alaska zone 2",
        "+proj=tmerc +lat_0=54 +lon_0=-142 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26933, "epsg", 26933, "NAD83 / Alaska zone 3",
        "+proj=tmerc +lat_0=54 +lon_0=-146 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26934, "epsg", 26934, "NAD83 / Alaska zone 4",
        "+proj=tmerc +lat_0=54 +lon_0=-150 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26935, "epsg", 26935, "NAD83 / Alaska zone 5",
        "+proj=tmerc +lat_0=54 +lon_0=-154 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26936, "epsg", 26936, "NAD83 / Alaska zone 6",
        "+proj=tmerc +lat_0=54 +lon_0=-158 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26937, "epsg", 26937, "NAD83 / Alaska zone 7",
        "+proj=tmerc +lat_0=54 +lon_0=-162 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26938, "epsg", 26938, "NAD83 / Alaska zone 8",
        "+proj=tmerc +lat_0=54 +lon_0=-166 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26939, "epsg", 26939, "NAD83 / Alaska zone 9",
        "+proj=tmerc +lat_0=54 +lon_0=-170 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26940, "epsg", 26940, "NAD83 / Alaska zone 10",
        "+proj=lcc +lat_1=53.83333333333334 +lat_2=51.83333333333334 +lat_0=51 +lon_0=-176 +x_0=1000000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26941, "epsg", 26941, "NAD83 / California zone 1",
        "+proj=lcc +lat_1=41.66666666666666 +lat_2=40 +lat_0=39.33333333333334 +lon_0=-122 +x_0=2000000 +y_0=500000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26942, "epsg", 26942, "NAD83 / California zone 2",
        "+proj=lcc +lat_1=39.83333333333334 +lat_2=38.33333333333334 +lat_0=37.66666666666666 +lon_0=-122 +x_0=2000000 +y_0=500000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26943, "epsg", 26943, "NAD83 / California zone 3",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.06666666666667 +lat_0=36.5 +lon_0=-120.5 +x_0=2000000 +y_0=500000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26944, "epsg", 26944, "NAD83 / California zone 4",
        "+proj=lcc +lat_1=37.25 +lat_2=36 +lat_0=35.33333333333334 +lon_0=-119 +x_0=2000000 +y_0=500000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26945, "epsg", 26945, "NAD83 / California zone 5",
        "+proj=lcc +lat_1=35.46666666666667 +lat_2=34.03333333333333 +lat_0=33.5 +lon_0=-118 +x_0=2000000 +y_0=500000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26946, "epsg", 26946, "NAD83 / California zone 6",
        "+proj=lcc +lat_1=33.88333333333333 +lat_2=32.78333333333333 +lat_0=32.16666666666666 +lon_0=-116.25 +x_0=2000000 +y_0=500000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26948, "epsg", 26948, "NAD83 / Arizona East",
        "+proj=tmerc +lat_0=31 +lon_0=-110.1666666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26949, "epsg", 26949, "NAD83 / Arizona Central",
        "+proj=tmerc +lat_0=31 +lon_0=-111.9166666666667 +k=0.9999 +x_0=213360 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26950, "epsg", 26950, "NAD83 / Arizona West",
        "+proj=tmerc +lat_0=31 +lon_0=-113.75 +k=0.999933333 +x_0=213360 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26951, "epsg", 26951, "NAD83 / Arkansas North",
        "+proj=lcc +lat_1=36.23333333333333 +lat_2=34.93333333333333 +lat_0=34.33333333333334 +lon_0=-92 +x_0=400000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26952, "epsg", 26952, "NAD83 / Arkansas South",
        "+proj=lcc +lat_1=34.76666666666667 +lat_2=33.3 +lat_0=32.66666666666666 +lon_0=-92 +x_0=400000 +y_0=400000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26953, "epsg", 26953, "NAD83 / Colorado North",
        "+proj=lcc +lat_1=40.78333333333333 +lat_2=39.71666666666667 +lat_0=39.33333333333334 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26954, "epsg", 26954, "NAD83 / Colorado Central",
        "+proj=lcc +lat_1=39.75 +lat_2=38.45 +lat_0=37.83333333333334 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26955, "epsg", 26955, "NAD83 / Colorado South",
        "+proj=lcc +lat_1=38.43333333333333 +lat_2=37.23333333333333 +lat_0=36.66666666666666 +lon_0=-105.5 +x_0=914401.8289 +y_0=304800.6096 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26956, "epsg", 26956, "NAD83 / Connecticut",
        "+proj=lcc +lat_1=41.86666666666667 +lat_2=41.2 +lat_0=40.83333333333334 +lon_0=-72.75 +x_0=304800.6096 +y_0=152400.3048 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26957, "epsg", 26957, "NAD83 / Delaware",
        "+proj=tmerc +lat_0=38 +lon_0=-75.41666666666667 +k=0.999995 +x_0=200000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26958, "epsg", 26958, "NAD83 / Florida East",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-81 +k=0.999941177 +x_0=200000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26959, "epsg", 26959, "NAD83 / Florida West",
        "+proj=tmerc +lat_0=24.33333333333333 +lon_0=-82 +k=0.999941177 +x_0=200000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26960, "epsg", 26960, "NAD83 / Florida North",
        "+proj=lcc +lat_1=30.75 +lat_2=29.58333333333333 +lat_0=29 +lon_0=-84.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26961, "epsg", 26961, "NAD83 / Hawaii zone 1",
        "+proj=tmerc +lat_0=18.83333333333333 +lon_0=-155.5 +k=0.999966667 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26962, "epsg", 26962, "NAD83 / Hawaii zone 2",
        "+proj=tmerc +lat_0=20.33333333333333 +lon_0=-156.6666666666667 +k=0.999966667 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26963, "epsg", 26963, "NAD83 / Hawaii zone 3",
        "+proj=tmerc +lat_0=21.16666666666667 +lon_0=-158 +k=0.99999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26964, "epsg", 26964, "NAD83 / Hawaii zone 4",
        "+proj=tmerc +lat_0=21.83333333333333 +lon_0=-159.5 +k=0.99999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26965, "epsg", 26965, "NAD83 / Hawaii zone 5",
        "+proj=tmerc +lat_0=21.66666666666667 +lon_0=-160.1666666666667 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26966, "epsg", 26966, "NAD83 / Georgia East",
        "+proj=tmerc +lat_0=30 +lon_0=-82.16666666666667 +k=0.9999 +x_0=200000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26967, "epsg", 26967, "NAD83 / Georgia West",
        "+proj=tmerc +lat_0=30 +lon_0=-84.16666666666667 +k=0.9999 +x_0=700000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26968, "epsg", 26968, "NAD83 / Idaho East",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-112.1666666666667 +k=0.9999473679999999 +x_0=200000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26969, "epsg", 26969, "NAD83 / Idaho Central",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-114 +k=0.9999473679999999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26970, "epsg", 26970, "NAD83 / Idaho West",
        "+proj=tmerc +lat_0=41.66666666666666 +lon_0=-115.75 +k=0.999933333 +x_0=800000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26971, "epsg", 26971, "NAD83 / Illinois East",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-88.33333333333333 +k=0.9999749999999999 +x_0=300000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26972, "epsg", 26972, "NAD83 / Illinois West",
        "+proj=tmerc +lat_0=36.66666666666666 +lon_0=-90.16666666666667 +k=0.999941177 +x_0=700000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26973, "epsg", 26973, "NAD83 / Indiana East",
        "+proj=tmerc +lat_0=37.5 +lon_0=-85.66666666666667 +k=0.999966667 +x_0=100000 +y_0=250000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26974, "epsg", 26974, "NAD83 / Indiana West",
        "+proj=tmerc +lat_0=37.5 +lon_0=-87.08333333333333 +k=0.999966667 +x_0=900000 +y_0=250000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26975, "epsg", 26975, "NAD83 / Iowa North",
        "+proj=lcc +lat_1=43.26666666666667 +lat_2=42.06666666666667 +lat_0=41.5 +lon_0=-93.5 +x_0=1500000 +y_0=1000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26976, "epsg", 26976, "NAD83 / Iowa South",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.61666666666667 +lat_0=40 +lon_0=-93.5 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26977, "epsg", 26977, "NAD83 / Kansas North",
        "+proj=lcc +lat_1=39.78333333333333 +lat_2=38.71666666666667 +lat_0=38.33333333333334 +lon_0=-98 +x_0=400000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26978, "epsg", 26978, "NAD83 / Kansas South",
        "+proj=lcc +lat_1=38.56666666666667 +lat_2=37.26666666666667 +lat_0=36.66666666666666 +lon_0=-98.5 +x_0=400000 +y_0=400000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26979, "epsg", 26979, "NAD83 / Kentucky North (deprecated)",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=37.96666666666667 +lat_0=37.5 +lon_0=-84.25 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26980, "epsg", 26980, "NAD83 / Kentucky South",
        "+proj=lcc +lat_1=37.93333333333333 +lat_2=36.73333333333333 +lat_0=36.33333333333334 +lon_0=-85.75 +x_0=500000 +y_0=500000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26981, "epsg", 26981, "NAD83 / Louisiana North",
        "+proj=lcc +lat_1=32.66666666666666 +lat_2=31.16666666666667 +lat_0=30.5 +lon_0=-92.5 +x_0=1000000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26982, "epsg", 26982, "NAD83 / Louisiana South",
        "+proj=lcc +lat_1=30.7 +lat_2=29.3 +lat_0=28.5 +lon_0=-91.33333333333333 +x_0=1000000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26983, "epsg", 26983, "NAD83 / Maine East",
        "+proj=tmerc +lat_0=43.66666666666666 +lon_0=-68.5 +k=0.9999 +x_0=300000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26984, "epsg", 26984, "NAD83 / Maine West",
        "+proj=tmerc +lat_0=42.83333333333334 +lon_0=-70.16666666666667 +k=0.999966667 +x_0=900000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26985, "epsg", 26985, "NAD83 / Maryland",
        "+proj=lcc +lat_1=39.45 +lat_2=38.3 +lat_0=37.66666666666666 +lon_0=-77 +x_0=400000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26986, "epsg", 26986, "NAD83 / Massachusetts Mainland",
        "+proj=lcc +lat_1=42.68333333333333 +lat_2=41.71666666666667 +lat_0=41 +lon_0=-71.5 +x_0=200000 +y_0=750000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26987, "epsg", 26987, "NAD83 / Massachusetts Island",
        "+proj=lcc +lat_1=41.48333333333333 +lat_2=41.28333333333333 +lat_0=41 +lon_0=-70.5 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26988, "epsg", 26988, "NAD83 / Michigan North",
        "+proj=lcc +lat_1=47.08333333333334 +lat_2=45.48333333333333 +lat_0=44.78333333333333 +lon_0=-87 +x_0=8000000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26989, "epsg", 26989, "NAD83 / Michigan Central",
        "+proj=lcc +lat_1=45.7 +lat_2=44.18333333333333 +lat_0=43.31666666666667 +lon_0=-84.36666666666666 +x_0=6000000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26990, "epsg", 26990, "NAD83 / Michigan South",
        "+proj=lcc +lat_1=43.66666666666666 +lat_2=42.1 +lat_0=41.5 +lon_0=-84.36666666666666 +x_0=4000000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26991, "epsg", 26991, "NAD83 / Minnesota North",
        "+proj=lcc +lat_1=48.63333333333333 +lat_2=47.03333333333333 +lat_0=46.5 +lon_0=-93.09999999999999 +x_0=800000 +y_0=100000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26992, "epsg", 26992, "NAD83 / Minnesota Central",
        "+proj=lcc +lat_1=47.05 +lat_2=45.61666666666667 +lat_0=45 +lon_0=-94.25 +x_0=800000 +y_0=100000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26993, "epsg", 26993, "NAD83 / Minnesota South",
        "+proj=lcc +lat_1=45.21666666666667 +lat_2=43.78333333333333 +lat_0=43 +lon_0=-94 +x_0=800000 +y_0=100000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26994, "epsg", 26994, "NAD83 / Mississippi East",
        "+proj=tmerc +lat_0=29.5 +lon_0=-88.83333333333333 +k=0.99995 +x_0=300000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26995, "epsg", 26995, "NAD83 / Mississippi West",
        "+proj=tmerc +lat_0=29.5 +lon_0=-90.33333333333333 +k=0.99995 +x_0=700000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26996, "epsg", 26996, "NAD83 / Missouri East",
        "+proj=tmerc +lat_0=35.83333333333334 +lon_0=-90.5 +k=0.999933333 +x_0=250000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26997, "epsg", 26997, "NAD83 / Missouri Central",
        "+proj=tmerc +lat_0=35.83333333333334 +lon_0=-92.5 +k=0.999933333 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    26998, "epsg", 26998, "NAD83 / Missouri West",
        "+proj=tmerc +lat_0=36.16666666666666 +lon_0=-94.5 +k=0.999941177 +x_0=850000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    27037, "epsg", 27037, "Nahrwan 1967 / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=clrk80 +units=m +no_defs"},
    {
    27038, "epsg", 27038, "Nahrwan 1967 / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=clrk80 +units=m +no_defs"},
    {
    27039, "epsg", 27039, "Nahrwan 1967 / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=clrk80 +units=m +no_defs"},
    {
    27040, "epsg", 27040, "Nahrwan 1967 / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=clrk80 +units=m +no_defs"},
    {
    27120, "epsg", 27120, "Naparima 1972 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=intl +units=m +no_defs"},
    {
    27200, "epsg", 27200, "NZGD49 / New Zealand Map Grid",
        "+proj=nzmg +lat_0=-41 +lon_0=173 +x_0=2510000 +y_0=6023150 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27205, "epsg", 27205, "NZGD49 / Mount Eden Circuit",
        "+proj=tmerc +lat_0=-36.87986527777778 +lon_0=174.7643393611111 +k=0.9999 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27206, "epsg", 27206, "NZGD49 / Bay of Plenty Circuit",
        "+proj=tmerc +lat_0=-37.76124980555556 +lon_0=176.46619725 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27207, "epsg", 27207, "NZGD49 / Poverty Bay Circuit",
        "+proj=tmerc +lat_0=-38.62470277777778 +lon_0=177.8856362777778 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27208, "epsg", 27208, "NZGD49 / Hawkes Bay Circuit",
        "+proj=tmerc +lat_0=-39.65092930555556 +lon_0=176.6736805277778 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27209, "epsg", 27209, "NZGD49 / Taranaki Circuit",
        "+proj=tmerc +lat_0=-39.13575830555556 +lon_0=174.22801175 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27210, "epsg", 27210, "NZGD49 / Tuhirangi Circuit",
        "+proj=tmerc +lat_0=-39.51247038888889 +lon_0=175.6400368055556 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27211, "epsg", 27211, "NZGD49 / Wanganui Circuit",
        "+proj=tmerc +lat_0=-40.24194713888889 +lon_0=175.4880996111111 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27212, "epsg", 27212, "NZGD49 / Wairarapa Circuit",
        "+proj=tmerc +lat_0=-40.92553263888889 +lon_0=175.6473496666667 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27213, "epsg", 27213, "NZGD49 / Wellington Circuit",
        "+proj=tmerc +lat_0=-41.30131963888888 +lon_0=174.7766231111111 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27214, "epsg", 27214, "NZGD49 / Collingwood Circuit",
        "+proj=tmerc +lat_0=-40.71475905555556 +lon_0=172.6720465 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27215, "epsg", 27215, "NZGD49 / Nelson Circuit",
        "+proj=tmerc +lat_0=-41.27454472222222 +lon_0=173.2993168055555 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27216, "epsg", 27216, "NZGD49 / Karamea Circuit",
        "+proj=tmerc +lat_0=-41.28991152777778 +lon_0=172.1090281944444 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27217, "epsg", 27217, "NZGD49 / Buller Circuit",
        "+proj=tmerc +lat_0=-41.81080286111111 +lon_0=171.5812600555556 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27218, "epsg", 27218, "NZGD49 / Grey Circuit",
        "+proj=tmerc +lat_0=-42.33369427777778 +lon_0=171.5497713055556 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27219, "epsg", 27219, "NZGD49 / Amuri Circuit",
        "+proj=tmerc +lat_0=-42.68911658333333 +lon_0=173.0101333888889 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27220, "epsg", 27220, "NZGD49 / Marlborough Circuit",
        "+proj=tmerc +lat_0=-41.54448666666666 +lon_0=173.8020741111111 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27221, "epsg", 27221, "NZGD49 / Hokitika Circuit",
        "+proj=tmerc +lat_0=-42.88632236111111 +lon_0=170.9799935 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27222, "epsg", 27222, "NZGD49 / Okarito Circuit",
        "+proj=tmerc +lat_0=-43.11012813888889 +lon_0=170.2609258333333 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27223, "epsg", 27223, "NZGD49 / Jacksons Bay Circuit",
        "+proj=tmerc +lat_0=-43.97780288888889 +lon_0=168.606267 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27224, "epsg", 27224, "NZGD49 / Mount Pleasant Circuit",
        "+proj=tmerc +lat_0=-43.59063758333333 +lon_0=172.7271935833333 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27225, "epsg", 27225, "NZGD49 / Gawler Circuit",
        "+proj=tmerc +lat_0=-43.74871155555556 +lon_0=171.3607484722222 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27226, "epsg", 27226, "NZGD49 / Timaru Circuit",
        "+proj=tmerc +lat_0=-44.40222036111111 +lon_0=171.0572508333333 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27227, "epsg", 27227, "NZGD49 / Lindis Peak Circuit",
        "+proj=tmerc +lat_0=-44.73526797222222 +lon_0=169.4677550833333 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27228, "epsg", 27228, "NZGD49 / Mount Nicholas Circuit",
        "+proj=tmerc +lat_0=-45.13290258333333 +lon_0=168.3986411944444 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27229, "epsg", 27229, "NZGD49 / Mount York Circuit",
        "+proj=tmerc +lat_0=-45.56372616666666 +lon_0=167.7388617777778 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27230, "epsg", 27230, "NZGD49 / Observation Point Circuit",
        "+proj=tmerc +lat_0=-45.81619661111111 +lon_0=170.6285951666667 +k=1 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27231, "epsg", 27231, "NZGD49 / North Taieri Circuit",
        "+proj=tmerc +lat_0=-45.86151336111111 +lon_0=170.2825891111111 +k=0.99996 +x_0=300000 +y_0=700000 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27232, "epsg", 27232, "NZGD49 / Bluff Circuit",
        "+proj=tmerc +lat_0=-46.60000961111111 +lon_0=168.342872 +k=1 +x_0=300002.66 +y_0=699999.58 +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27258, "epsg", 27258, "NZGD49 / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27259, "epsg", 27259, "NZGD49 / UTM zone 59S",
        "+proj=utm +zone=59 +south +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27260, "epsg", 27260, "NZGD49 / UTM zone 60S",
        "+proj=utm +zone=60 +south +ellps=intl +datum=nzgd49 +units=m +no_defs"},
    {
    27291, "epsg", 27291, "NZGD49 / North Island Grid",
        "+proj=tmerc +lat_0=-39 +lon_0=175.5 +k=1 +x_0=274319.5243848086 +y_0=365759.3658464114 +ellps=intl +datum=nzgd49 +to_meter=0.9143984146160287 +no_defs"},
    {
    27292, "epsg", 27292, "NZGD49 / South Island Grid",
        "+proj=tmerc +lat_0=-44 +lon_0=171.5 +k=1 +x_0=457199.2073080143 +y_0=457199.2073080143 +ellps=intl +datum=nzgd49 +to_meter=0.9143984146160287 +no_defs"},
    {
    27391, "epsg", 27391, "NGO 1948 (Oslo) / NGO zone I",
        "+proj=tmerc +lat_0=58 +lon_0=-4.666666666666667 +k=1 +x_0=0 +y_0=0 +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +units=m +no_defs"},
    {
    27392, "epsg", 27392, "NGO 1948 (Oslo) / NGO zone II",
        "+proj=tmerc +lat_0=58 +lon_0=-2.333333333333333 +k=1 +x_0=0 +y_0=0 +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +units=m +no_defs"},
    {
    27393, "epsg", 27393, "NGO 1948 (Oslo) / NGO zone III",
        "+proj=tmerc +lat_0=58 +lon_0=0 +k=1 +x_0=0 +y_0=0 +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +units=m +no_defs"},
    {
    27394, "epsg", 27394, "NGO 1948 (Oslo) / NGO zone IV",
        "+proj=tmerc +lat_0=58 +lon_0=2.5 +k=1 +x_0=0 +y_0=0 +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +units=m +no_defs"},
    {
    27395, "epsg", 27395, "NGO 1948 (Oslo) / NGO zone V",
        "+proj=tmerc +lat_0=58 +lon_0=6.166666666666667 +k=1 +x_0=0 +y_0=0 +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +units=m +no_defs"},
    {
    27396, "epsg", 27396, "NGO 1948 (Oslo) / NGO zone VI",
        "+proj=tmerc +lat_0=58 +lon_0=10.16666666666667 +k=1 +x_0=0 +y_0=0 +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +units=m +no_defs"},
    {
    27397, "epsg", 27397, "NGO 1948 (Oslo) / NGO zone VII",
        "+proj=tmerc +lat_0=58 +lon_0=14.16666666666667 +k=1 +x_0=0 +y_0=0 +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +units=m +no_defs"},
    {
    27398, "epsg", 27398, "NGO 1948 (Oslo) / NGO zone VIII",
        "+proj=tmerc +lat_0=58 +lon_0=18.33333333333333 +k=1 +x_0=0 +y_0=0 +a=6377492.018 +b=6356173.508712696 +towgs84=278.3,93,474.5,7.889,0.05,-6.61,6.21 +pm=oslo +units=m +no_defs"},
    {
    27429, "epsg", 27429, "Datum 73 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=intl +units=m +no_defs"},
    {
    27492, "epsg", 27492, "Datum 73 / Modified Portuguese Grid (deprecated)",
        "+proj=tmerc +lat_0=39.66666666666666 +lon_0=-8.131906111111112 +k=1 +x_0=180.598 +y_0=-86.98999999999999 +ellps=intl +units=m +no_defs"},
    {
    27493, "epsg", 27493, "Datum 73 / Modified Portuguese Grid",
        "+proj=tmerc +lat_0=39.66666666666666 +lon_0=-8.131906111111112 +k=1 +x_0=180.598 +y_0=-86.98999999999999 +ellps=intl +units=m +no_defs"},
    {
    27500, "epsg", 27500, "unnamed",
        "+proj=lcc +lat_1=49.5 +lat_0=49.5 +lon_0=5.4 +k_0=0.99950908 +x_0=500000 +y_0=300000 +a=6376523 +b=6355862.933255573 +pm=2.3372291666985 +units=m +no_defs"},
    {
    27561, "epsg", 27561, "NTF (Paris) / Lambert Nord France",
        "+proj=lcc +lat_1=49.50000000000001 +lat_0=49.50000000000001 +lon_0=0 +k_0=0.999877341 +x_0=600000 +y_0=200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27562, "epsg", 27562, "NTF (Paris) / Lambert Centre France",
        "+proj=lcc +lat_1=46.8 +lat_0=46.8 +lon_0=0 +k_0=0.99987742 +x_0=600000 +y_0=200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27563, "epsg", 27563, "NTF (Paris) / Lambert Sud France",
        "+proj=lcc +lat_1=44.10000000000001 +lat_0=44.10000000000001 +lon_0=0 +k_0=0.999877499 +x_0=600000 +y_0=200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27564, "epsg", 27564, "NTF (Paris) / Lambert Corse",
        "+proj=lcc +lat_1=42.16500000000001 +lat_0=42.16500000000001 +lon_0=0 +k_0=0.99994471 +x_0=234.358 +y_0=185861.369 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27571, "epsg", 27571, "NTF (Paris) / Lambert zone I",
        "+proj=lcc +lat_1=49.50000000000001 +lat_0=49.50000000000001 +lon_0=0 +k_0=0.999877341 +x_0=600000 +y_0=1200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27572, "epsg", 27572, "NTF (Paris) / Lambert zone II",
        "+proj=lcc +lat_1=46.8 +lat_0=46.8 +lon_0=0 +k_0=0.99987742 +x_0=600000 +y_0=2200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27573, "epsg", 27573, "NTF (Paris) / Lambert zone III",
        "+proj=lcc +lat_1=44.10000000000001 +lat_0=44.10000000000001 +lon_0=0 +k_0=0.999877499 +x_0=600000 +y_0=3200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27574, "epsg", 27574, "NTF (Paris) / Lambert zone IV",
        "+proj=lcc +lat_1=42.16500000000001 +lat_0=42.16500000000001 +lon_0=0 +k_0=0.99994471 +x_0=234.358 +y_0=4185861.369 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27581, "epsg", 27581, "NTF (Paris) / France I (deprecated)",
        "+proj=lcc +lat_1=49.50000000000001 +lat_0=49.50000000000001 +lon_0=0 +k_0=0.999877341 +x_0=600000 +y_0=1200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27582, "epsg", 27582, "NTF (Paris) / France II (deprecated)",
        "+proj=lcc +lat_1=46.8 +lat_0=46.8 +lon_0=0 +k_0=0.99987742 +x_0=600000 +y_0=2200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27583, "epsg", 27583, "NTF (Paris) / France III (deprecated)",
        "+proj=lcc +lat_1=44.10000000000001 +lat_0=44.10000000000001 +lon_0=0 +k_0=0.999877499 +x_0=600000 +y_0=3200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27584, "epsg", 27584, "NTF (Paris) / France IV (deprecated)",
        "+proj=lcc +lat_1=42.16500000000001 +lat_0=42.16500000000001 +lon_0=0 +k_0=0.99994471 +x_0=234.358 +y_0=4185861.369 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27591, "epsg", 27591, "NTF (Paris) / Nord France (deprecated)",
        "+proj=lcc +lat_1=49.50000000000001 +lat_0=49.50000000000001 +lon_0=0 +k_0=0.999877341 +x_0=600000 +y_0=200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27592, "epsg", 27592, "NTF (Paris) / Centre France (deprecated)",
        "+proj=lcc +lat_1=46.8 +lat_0=46.8 +lon_0=0 +k_0=0.99987742 +x_0=600000 +y_0=200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27593, "epsg", 27593, "NTF (Paris) / Sud France (deprecated)",
        "+proj=lcc +lat_1=44.10000000000001 +lat_0=44.10000000000001 +lon_0=0 +k_0=0.999877499 +x_0=600000 +y_0=200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27594, "epsg", 27594, "NTF (Paris) / Corse (deprecated)",
        "+proj=lcc +lat_1=42.16500000000001 +lat_0=42.16500000000001 +lon_0=0 +k_0=0.99994471 +x_0=234.358 +y_0=185861.369 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    27700, "epsg", 27700, "OSGB 1936 / British National Grid",
        "+proj=tmerc +lat_0=49 +lon_0=-2 +k=0.9996012717 +x_0=400000 +y_0=-100000 +ellps=airy +datum=OSGB36 +units=m +no_defs"},
    {
    28191, "epsg", 28191, "Palestine 1923 / Palestine Grid",
        "+proj=cass +lat_0=31.73409694444445 +lon_0=35.21208055555556 +x_0=170251.555 +y_0=126867.909 +a=6378300.789 +b=6356566.435 +towgs84=-275.722,94.7824,340.894,-8.001,-4.42,-11.821,1 +units=m +no_defs"},
    {
    28192, "epsg", 28192, "Palestine 1923 / Palestine Belt",
        "+proj=tmerc +lat_0=31.73409694444445 +lon_0=35.21208055555556 +k=1 +x_0=170251.555 +y_0=1126867.909 +a=6378300.789 +b=6356566.435 +towgs84=-275.722,94.7824,340.894,-8.001,-4.42,-11.821,1 +units=m +no_defs"},
    {
    28193, "epsg", 28193, "Palestine 1923 / Israeli CS Grid",
        "+proj=cass +lat_0=31.73409694444445 +lon_0=35.21208055555556 +x_0=170251.555 +y_0=1126867.909 +a=6378300.789 +b=6356566.435 +towgs84=-275.722,94.7824,340.894,-8.001,-4.42,-11.821,1 +units=m +no_defs"},
    {
    28232, "epsg", 28232, "Pointe Noire / UTM zone 32S",
        "+proj=utm +zone=32 +south +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    28348, "epsg", 28348, "GDA94 / MGA zone 48",
        "+proj=utm +zone=48 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28349, "epsg", 28349, "GDA94 / MGA zone 49",
        "+proj=utm +zone=49 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28350, "epsg", 28350, "GDA94 / MGA zone 50",
        "+proj=utm +zone=50 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28351, "epsg", 28351, "GDA94 / MGA zone 51",
        "+proj=utm +zone=51 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28352, "epsg", 28352, "GDA94 / MGA zone 52",
        "+proj=utm +zone=52 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28353, "epsg", 28353, "GDA94 / MGA zone 53",
        "+proj=utm +zone=53 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28354, "epsg", 28354, "GDA94 / MGA zone 54",
        "+proj=utm +zone=54 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28355, "epsg", 28355, "GDA94 / MGA zone 55",
        "+proj=utm +zone=55 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28356, "epsg", 28356, "GDA94 / MGA zone 56",
        "+proj=utm +zone=56 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28357, "epsg", 28357, "GDA94 / MGA zone 57",
        "+proj=utm +zone=57 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28358, "epsg", 28358, "GDA94 / MGA zone 58",
        "+proj=utm +zone=58 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    28402, "epsg", 28402, "Pulkovo 1942 / Gauss-Kruger zone 2 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=2500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28403, "epsg", 28403, "Pulkovo 1942 / Gauss-Kruger zone 3 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=3500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28404, "epsg", 28404, "Pulkovo 1942 / Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=4500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28405, "epsg", 28405, "Pulkovo 1942 / Gauss-Kruger zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=5500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28406, "epsg", 28406, "Pulkovo 1942 / Gauss-Kruger zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=6500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28407, "epsg", 28407, "Pulkovo 1942 / Gauss-Kruger zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=7500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28408, "epsg", 28408, "Pulkovo 1942 / Gauss-Kruger zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=8500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28409, "epsg", 28409, "Pulkovo 1942 / Gauss-Kruger zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=9500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28410, "epsg", 28410, "Pulkovo 1942 / Gauss-Kruger zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=10500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28411, "epsg", 28411, "Pulkovo 1942 / Gauss-Kruger zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=11500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28412, "epsg", 28412, "Pulkovo 1942 / Gauss-Kruger zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=12500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28413, "epsg", 28413, "Pulkovo 1942 / Gauss-Kruger zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=13500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28414, "epsg", 28414, "Pulkovo 1942 / Gauss-Kruger zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=14500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28415, "epsg", 28415, "Pulkovo 1942 / Gauss-Kruger zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=15500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28416, "epsg", 28416, "Pulkovo 1942 / Gauss-Kruger zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=16500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28417, "epsg", 28417, "Pulkovo 1942 / Gauss-Kruger zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=17500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28418, "epsg", 28418, "Pulkovo 1942 / Gauss-Kruger zone 18",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=18500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28419, "epsg", 28419, "Pulkovo 1942 / Gauss-Kruger zone 19",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=19500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28420, "epsg", 28420, "Pulkovo 1942 / Gauss-Kruger zone 20",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=20500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28421, "epsg", 28421, "Pulkovo 1942 / Gauss-Kruger zone 21",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=21500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28422, "epsg", 28422, "Pulkovo 1942 / Gauss-Kruger zone 22",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=22500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28423, "epsg", 28423, "Pulkovo 1942 / Gauss-Kruger zone 23",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=23500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28424, "epsg", 28424, "Pulkovo 1942 / Gauss-Kruger zone 24",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=24500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28425, "epsg", 28425, "Pulkovo 1942 / Gauss-Kruger zone 25",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=25500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28426, "epsg", 28426, "Pulkovo 1942 / Gauss-Kruger zone 26",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=26500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28427, "epsg", 28427, "Pulkovo 1942 / Gauss-Kruger zone 27",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=27500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28428, "epsg", 28428, "Pulkovo 1942 / Gauss-Kruger zone 28",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=28500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28429, "epsg", 28429, "Pulkovo 1942 / Gauss-Kruger zone 29",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=29500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28430, "epsg", 28430, "Pulkovo 1942 / Gauss-Kruger zone 30",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=30500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28431, "epsg", 28431, "Pulkovo 1942 / Gauss-Kruger zone 31",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=31500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28432, "epsg", 28432, "Pulkovo 1942 / Gauss-Kruger zone 32",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=32500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28462, "epsg", 28462, "Pulkovo 1942 / Gauss-Kruger 2N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28463, "epsg", 28463, "Pulkovo 1942 / Gauss-Kruger 3N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28464, "epsg", 28464, "Pulkovo 1942 / Gauss-Kruger 4N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28465, "epsg", 28465, "Pulkovo 1942 / Gauss-Kruger 5N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=27 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28466, "epsg", 28466, "Pulkovo 1942 / Gauss-Kruger 6N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=33 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28467, "epsg", 28467, "Pulkovo 1942 / Gauss-Kruger 7N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=39 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28468, "epsg", 28468, "Pulkovo 1942 / Gauss-Kruger 8N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=45 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28469, "epsg", 28469, "Pulkovo 1942 / Gauss-Kruger 9N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=51 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28470, "epsg", 28470, "Pulkovo 1942 / Gauss-Kruger 10N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=57 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28471, "epsg", 28471, "Pulkovo 1942 / Gauss-Kruger 11N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=63 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28472, "epsg", 28472, "Pulkovo 1942 / Gauss-Kruger 12N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=69 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28473, "epsg", 28473, "Pulkovo 1942 / Gauss-Kruger 13N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=75 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28474, "epsg", 28474, "Pulkovo 1942 / Gauss-Kruger 14N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=81 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28475, "epsg", 28475, "Pulkovo 1942 / Gauss-Kruger 15N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=87 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28476, "epsg", 28476, "Pulkovo 1942 / Gauss-Kruger 16N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=93 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28477, "epsg", 28477, "Pulkovo 1942 / Gauss-Kruger 17N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=99 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28478, "epsg", 28478, "Pulkovo 1942 / Gauss-Kruger 18N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=105 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28479, "epsg", 28479, "Pulkovo 1942 / Gauss-Kruger 19N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=111 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28480, "epsg", 28480, "Pulkovo 1942 / Gauss-Kruger 20N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28481, "epsg", 28481, "Pulkovo 1942 / Gauss-Kruger 21N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=123 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28482, "epsg", 28482, "Pulkovo 1942 / Gauss-Kruger 22N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=129 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28483, "epsg", 28483, "Pulkovo 1942 / Gauss-Kruger 23N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=135 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28484, "epsg", 28484, "Pulkovo 1942 / Gauss-Kruger 24N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=141 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28485, "epsg", 28485, "Pulkovo 1942 / Gauss-Kruger 25N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=147 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28486, "epsg", 28486, "Pulkovo 1942 / Gauss-Kruger 26N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=153 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28487, "epsg", 28487, "Pulkovo 1942 / Gauss-Kruger 27N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=159 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28488, "epsg", 28488, "Pulkovo 1942 / Gauss-Kruger 28N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=165 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28489, "epsg", 28489, "Pulkovo 1942 / Gauss-Kruger 29N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28490, "epsg", 28490, "Pulkovo 1942 / Gauss-Kruger 30N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28491, "epsg", 28491, "Pulkovo 1942 / Gauss-Kruger 31N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-177 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28492, "epsg", 28492, "Pulkovo 1942 / Gauss-Kruger 32N (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-171 +k=1 +x_0=500000 +y_0=0 +ellps=krass +units=m +no_defs"},
    {
    28600, "epsg", 28600, "Qatar 1974 / Qatar National Grid",
        "+proj=tmerc +lat_0=24.45 +lon_0=51.21666666666667 +k=0.99999 +x_0=200000 +y_0=300000 +ellps=intl +units=m +no_defs"},
    {
    28991, "epsg", 28991, "Amersfoort / RD Old",
        "+proj=sterea +lat_0=52.15616055555555 +lon_0=5.38763888888889 +k=0.9999079 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    28992, "epsg", 28992, "Amersfoort / RD New",
        "+proj=sterea +lat_0=52.15616055555555 +lon_0=5.38763888888889 +k=0.9999079 +x_0=155000 +y_0=463000 +ellps=bessel +units=m +no_defs"},
    {
    29100, "epsg", 29100, "SAD69 / Brazil Polyconic (deprecated)",
        "+proj=poly +lat_0=0 +lon_0=-54 +x_0=5000000 +y_0=10000000 +ellps=GRS67 +units=m +no_defs"},
    {
    29101, "epsg", 29101, "SAD69 / Brazil Polyconic",
        "+proj=poly +lat_0=0 +lon_0=-54 +x_0=5000000 +y_0=10000000 +ellps=aust_SA +units=m +no_defs"},
    {
    29118, "epsg", 29118, "SAD69 / UTM zone 18N (deprecated)",
        "+proj=utm +zone=18 +ellps=GRS67 +units=m +no_defs"},
    {
    29119, "epsg", 29119, "SAD69 / UTM zone 19N (deprecated)",
        "+proj=utm +zone=19 +ellps=GRS67 +units=m +no_defs"},
    {
    29120, "epsg", 29120, "SAD69 / UTM zone 20N (deprecated)",
        "+proj=utm +zone=20 +ellps=GRS67 +units=m +no_defs"},
    {
    29121, "epsg", 29121, "SAD69 / UTM zone 21N (deprecated)",
        "+proj=utm +zone=21 +ellps=GRS67 +units=m +no_defs"},
    {
    29122, "epsg", 29122, "SAD69 / UTM zone 22N (deprecated)",
        "+proj=utm +zone=22 +ellps=GRS67 +units=m +no_defs"},
    {
    29168, "epsg", 29168, "SAD69 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=aust_SA +units=m +no_defs"},
    {
    29169, "epsg", 29169, "SAD69 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=aust_SA +units=m +no_defs"},
    {
    29170, "epsg", 29170, "SAD69 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=aust_SA +units=m +no_defs"},
    {
    29171, "epsg", 29171, "SAD69 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=aust_SA +units=m +no_defs"},
    {
    29172, "epsg", 29172, "SAD69 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=aust_SA +units=m +no_defs"},
    {
    29177, "epsg", 29177, "SAD69 / UTM zone 17S (deprecated)",
        "+proj=utm +zone=17 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29178, "epsg", 29178, "SAD69 / UTM zone 18S (deprecated)",
        "+proj=utm +zone=18 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29179, "epsg", 29179, "SAD69 / UTM zone 19S (deprecated)",
        "+proj=utm +zone=19 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29180, "epsg", 29180, "SAD69 / UTM zone 20S (deprecated)",
        "+proj=utm +zone=20 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29181, "epsg", 29181, "SAD69 / UTM zone 21S (deprecated)",
        "+proj=utm +zone=21 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29182, "epsg", 29182, "SAD69 / UTM zone 22S (deprecated)",
        "+proj=utm +zone=22 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29183, "epsg", 29183, "SAD69 / UTM zone 23S (deprecated)",
        "+proj=utm +zone=23 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29184, "epsg", 29184, "SAD69 / UTM zone 24S (deprecated)",
        "+proj=utm +zone=24 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29185, "epsg", 29185, "SAD69 / UTM zone 25S (deprecated)",
        "+proj=utm +zone=25 +south +ellps=GRS67 +units=m +no_defs"},
    {
    29187, "epsg", 29187, "SAD69 / UTM zone 17S",
        "+proj=utm +zone=17 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29188, "epsg", 29188, "SAD69 / UTM zone 18S",
        "+proj=utm +zone=18 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29189, "epsg", 29189, "SAD69 / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29190, "epsg", 29190, "SAD69 / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29191, "epsg", 29191, "SAD69 / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29192, "epsg", 29192, "SAD69 / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29193, "epsg", 29193, "SAD69 / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29194, "epsg", 29194, "SAD69 / UTM zone 24S",
        "+proj=utm +zone=24 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29195, "epsg", 29195, "SAD69 / UTM zone 25S",
        "+proj=utm +zone=25 +south +ellps=aust_SA +units=m +no_defs"},
    {
    29220, "epsg", 29220, "Sapper Hill 1943 / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=intl +towgs84=-355,21,72,0,0,0,0 +units=m +no_defs"},
    {
    29221, "epsg", 29221, "Sapper Hill 1943 / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=intl +towgs84=-355,21,72,0,0,0,0 +units=m +no_defs"},
    {
    29333, "epsg", 29333, "Schwarzeck / UTM zone 33S",
        "+proj=utm +zone=33 +south +ellps=bess_nam +units=m +no_defs"},
    {
    29635, "epsg", 29635, "Sudan / UTM zone 35N (deprecated)",
        "+proj=utm +zone=35 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    29636, "epsg", 29636, "Sudan / UTM zone 36N (deprecated)",
        "+proj=utm +zone=36 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    29700, "epsg", 29700, "Tananarive (Paris) / Laborde Grid (deprecated)",
        "+proj=omerc +lat_0=-18.9 +lonc=44.10000000000001 +alpha=18.9 +k=0.9995000000000001 +x_0=400000 +y_0=800000 +ellps=intl +towgs84=-189,-242,-91,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    29702, "epsg", 29702, "Tananarive (Paris) / Laborde Grid approximation",
        "+proj=omerc +lat_0=-18.9 +lonc=44.10000000000001 +alpha=18.9 +k=0.9995000000000001 +x_0=400000 +y_0=800000 +ellps=intl +towgs84=-189,-242,-91,0,0,0,0 +pm=paris +units=m +no_defs"},
    {
    29738, "epsg", 29738, "Tananarive / UTM zone 38S",
        "+proj=utm +zone=38 +south +ellps=intl +towgs84=-189,-242,-91,0,0,0,0 +units=m +no_defs"},
    {
    29739, "epsg", 29739, "Tananarive / UTM zone 39S",
        "+proj=utm +zone=39 +south +ellps=intl +towgs84=-189,-242,-91,0,0,0,0 +units=m +no_defs"},
    {
    29849, "epsg", 29849, "Timbalai 1948 / UTM zone 49N",
        "+proj=utm +zone=49 +ellps=evrstSS +units=m +no_defs"},
    {
    29850, "epsg", 29850, "Timbalai 1948 / UTM zone 50N",
        "+proj=utm +zone=50 +ellps=evrstSS +units=m +no_defs"},
    {
    29871, "epsg", 29871, "Timbalai 1948 / RSO Borneo (ch)",
        "+proj=omerc +lat_0=4 +lonc=115 +alpha=53.31582047222222 +k=0.99984 +x_0=590476.8714630401 +y_0=442857.653094361 +ellps=evrstSS +to_meter=20.11676512155263 +no_defs"},
    {
    29872, "epsg", 29872, "Timbalai 1948 / RSO Borneo (ft)",
        "+proj=omerc +lat_0=4 +lonc=115 +alpha=53.31582047222222 +k=0.99984 +x_0=590476.8727431979 +y_0=442857.6545573985 +ellps=evrstSS +to_meter=0.3047994715386762 +no_defs"},
    {
    29873, "epsg", 29873, "Timbalai 1948 / RSO Borneo (m)",
        "+proj=omerc +lat_0=4 +lonc=115 +alpha=53.31582047222222 +k=0.99984 +x_0=590476.87 +y_0=442857.65 +ellps=evrstSS +units=m +no_defs"},
    {
    29900, "epsg", 29900, "TM65 / Irish National Grid (deprecated)",
        "+proj=tmerc +lat_0=53.5 +lon_0=-8 +k=1.000035 +x_0=200000 +y_0=250000 +ellps=mod_airy +datum=ire65 +units=m +no_defs"},
    {
    29901, "epsg", 29901, "OSNI 1952 / Irish National Grid",
        "+proj=tmerc +lat_0=53.5 +lon_0=-8 +k=1 +x_0=200000 +y_0=250000 +ellps=airy +towgs84=482.5,-130.6,564.6,-1.042,-0.214,-0.631,8.15 +units=m +no_defs"},
    {
    29902, "epsg", 29902, "TM65 / Irish Grid",
        "+proj=tmerc +lat_0=53.5 +lon_0=-8 +k=1.000035 +x_0=200000 +y_0=250000 +ellps=mod_airy +datum=ire65 +units=m +no_defs"},
    {
    29903, "epsg", 29903, "TM75 / Irish Grid",
        "+proj=tmerc +lat_0=53.5 +lon_0=-8 +k=1.000035 +x_0=200000 +y_0=250000 +ellps=mod_airy +units=m +no_defs"},
    {
    30161, "epsg", 30161, "Tokyo / Japan Plane Rectangular CS I",
        "+proj=tmerc +lat_0=33 +lon_0=129.5 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30162, "epsg", 30162, "Tokyo / Japan Plane Rectangular CS II",
        "+proj=tmerc +lat_0=33 +lon_0=131 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30163, "epsg", 30163, "Tokyo / Japan Plane Rectangular CS III",
        "+proj=tmerc +lat_0=36 +lon_0=132.1666666666667 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30164, "epsg", 30164, "Tokyo / Japan Plane Rectangular CS IV",
        "+proj=tmerc +lat_0=33 +lon_0=133.5 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30165, "epsg", 30165, "Tokyo / Japan Plane Rectangular CS V",
        "+proj=tmerc +lat_0=36 +lon_0=134.3333333333333 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30166, "epsg", 30166, "Tokyo / Japan Plane Rectangular CS VI",
        "+proj=tmerc +lat_0=36 +lon_0=136 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30167, "epsg", 30167, "Tokyo / Japan Plane Rectangular CS VII",
        "+proj=tmerc +lat_0=36 +lon_0=137.1666666666667 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30168, "epsg", 30168, "Tokyo / Japan Plane Rectangular CS VIII",
        "+proj=tmerc +lat_0=36 +lon_0=138.5 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30169, "epsg", 30169, "Tokyo / Japan Plane Rectangular CS IX",
        "+proj=tmerc +lat_0=36 +lon_0=139.8333333333333 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30170, "epsg", 30170, "Tokyo / Japan Plane Rectangular CS X",
        "+proj=tmerc +lat_0=40 +lon_0=140.8333333333333 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30171, "epsg", 30171, "Tokyo / Japan Plane Rectangular CS XI",
        "+proj=tmerc +lat_0=44 +lon_0=140.25 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30172, "epsg", 30172, "Tokyo / Japan Plane Rectangular CS XII",
        "+proj=tmerc +lat_0=44 +lon_0=142.25 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30173, "epsg", 30173, "Tokyo / Japan Plane Rectangular CS XIII",
        "+proj=tmerc +lat_0=44 +lon_0=144.25 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30174, "epsg", 30174, "Tokyo / Japan Plane Rectangular CS XIV",
        "+proj=tmerc +lat_0=26 +lon_0=142 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30175, "epsg", 30175, "Tokyo / Japan Plane Rectangular CS XV",
        "+proj=tmerc +lat_0=26 +lon_0=127.5 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30176, "epsg", 30176, "Tokyo / Japan Plane Rectangular CS XVI",
        "+proj=tmerc +lat_0=26 +lon_0=124 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30177, "epsg", 30177, "Tokyo / Japan Plane Rectangular CS XVII",
        "+proj=tmerc +lat_0=26 +lon_0=131 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30178, "epsg", 30178, "Tokyo / Japan Plane Rectangular CS XVIII",
        "+proj=tmerc +lat_0=20 +lon_0=136 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30179, "epsg", 30179, "Tokyo / Japan Plane Rectangular CS XIX",
        "+proj=tmerc +lat_0=26 +lon_0=154 +k=0.9999 +x_0=0 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    30200, "epsg", 30200, "Trinidad 1903 / Trinidad Grid",
        "+proj=cass +lat_0=10.44166666666667 +lon_0=-61.33333333333334 +x_0=86501.46392051999 +y_0=65379.0134283 +a=6378293.645208759 +b=6356617.987679838 +to_meter=0.201166195164 +no_defs"},
    {
    30339, "epsg", 30339, "TC(1948) / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=helmert +units=m +no_defs"},
    {
    30340, "epsg", 30340, "TC(1948) / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=helmert +units=m +no_defs"},
    {
    30491, "epsg", 30491, "Voirol 1875 / Nord Algerie (ancienne)",
        "+proj=lcc +lat_1=36 +lat_0=36 +lon_0=2.7 +k_0=0.999625544 +x_0=500000 +y_0=300000 +a=6378249.2 +b=6356515 +towgs84=-73,-247,227,0,0,0,0 +units=m +no_defs"},
    {
    30492, "epsg", 30492, "Voirol 1875 / Sud Algerie (ancienne)",
        "+proj=lcc +lat_1=33.3 +lat_0=33.3 +lon_0=2.7 +k_0=0.999625769 +x_0=500000 +y_0=300000 +a=6378249.2 +b=6356515 +towgs84=-73,-247,227,0,0,0,0 +units=m +no_defs"},
    {
    30493, "epsg", 30493, "Voirol 1879 / Nord Algerie (ancienne)",
        "+proj=lcc +lat_1=36 +lat_0=36 +lon_0=2.7 +k_0=0.999625544 +x_0=500000 +y_0=300000 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    30494, "epsg", 30494, "Voirol 1879 / Sud Algerie (ancienne)",
        "+proj=lcc +lat_1=33.3 +lat_0=33.3 +lon_0=2.7 +k_0=0.999625769 +x_0=500000 +y_0=300000 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    30729, "epsg", 30729, "Nord Sahara 1959 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=clrk80 +units=m +no_defs"},
    {
    30730, "epsg", 30730, "Nord Sahara 1959 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=clrk80 +units=m +no_defs"},
    {
    30731, "epsg", 30731, "Nord Sahara 1959 / UTM zone 31N",
        "+proj=utm +zone=31 +ellps=clrk80 +units=m +no_defs"},
    {
    30732, "epsg", 30732, "Nord Sahara 1959 / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=clrk80 +units=m +no_defs"},
    {
    30791, "epsg", 30791, "Nord Sahara 1959 / Voirol Unifie Nord",
        "+proj=lcc +lat_1=36 +lat_0=36 +lon_0=2.7 +k_0=0.999625544 +x_0=500135 +y_0=300090 +ellps=clrk80 +units=m +no_defs"},
    {
    30792, "epsg", 30792, "Nord Sahara 1959 / Voirol Unifie Sud",
        "+proj=lcc +lat_1=33.3 +lat_0=33.3 +lon_0=2.7 +k_0=0.999625769 +x_0=500135 +y_0=300090 +ellps=clrk80 +units=m +no_defs"},
    {
    30800, "epsg", 30800, "RT38 2.5 gon W (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15.80827777777778 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +units=m +no_defs"},
    {
    31028, "epsg", 31028, "Yoff / UTM zone 28N",
        "+proj=utm +zone=28 +a=6378249.2 +b=6356515 +units=m +no_defs"},
    {
    31121, "epsg", 31121, "Zanderij / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=intl +towgs84=-265,120,-358,0,0,0,0 +units=m +no_defs"},
    {
    31154, "epsg", 31154, "Zanderij / TM 54 NW",
        "+proj=tmerc +lat_0=0 +lon_0=-54 +k=0.9996 +x_0=500000 +y_0=0 +ellps=intl +towgs84=-265,120,-358,0,0,0,0 +units=m +no_defs"},
    {
    31170, "epsg", 31170, "Zanderij / Suriname Old TM",
        "+proj=tmerc +lat_0=0 +lon_0=-55.68333333333333 +k=0.9996 +x_0=500000 +y_0=0 +ellps=intl +towgs84=-265,120,-358,0,0,0,0 +units=m +no_defs"},
    {
    31171, "epsg", 31171, "Zanderij / Suriname TM",
        "+proj=tmerc +lat_0=0 +lon_0=-55.68333333333333 +k=0.9999 +x_0=500000 +y_0=0 +ellps=intl +towgs84=-265,120,-358,0,0,0,0 +units=m +no_defs"},
    {
    31251, "epsg", 31251, "MGI (Ferro) / Austria GK West Zone",
        "+proj=tmerc +lat_0=0 +lon_0=28 +k=1 +x_0=0 +y_0=-5000000 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31252, "epsg", 31252, "MGI (Ferro) / Austria GK Central Zone",
        "+proj=tmerc +lat_0=0 +lon_0=31 +k=1 +x_0=0 +y_0=-5000000 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31253, "epsg", 31253, "MGI (Ferro) / Austria GK East Zone",
        "+proj=tmerc +lat_0=0 +lon_0=34 +k=1 +x_0=0 +y_0=-5000000 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31254, "epsg", 31254, "MGI / Austria GK West",
        "+proj=tmerc +lat_0=0 +lon_0=10.33333333333333 +k=1 +x_0=0 +y_0=-5000000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31255, "epsg", 31255, "MGI / Austria GK Central",
        "+proj=tmerc +lat_0=0 +lon_0=13.33333333333333 +k=1 +x_0=0 +y_0=-5000000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31256, "epsg", 31256, "MGI / Austria GK East",
        "+proj=tmerc +lat_0=0 +lon_0=16.33333333333333 +k=1 +x_0=0 +y_0=-5000000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31257, "epsg", 31257, "MGI / Austria GK M28",
        "+proj=tmerc +lat_0=0 +lon_0=10.33333333333333 +k=1 +x_0=150000 +y_0=-5000000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31258, "epsg", 31258, "MGI / Austria GK M31",
        "+proj=tmerc +lat_0=0 +lon_0=13.33333333333333 +k=1 +x_0=450000 +y_0=-5000000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31259, "epsg", 31259, "MGI / Austria GK M34",
        "+proj=tmerc +lat_0=0 +lon_0=16.33333333333333 +k=1 +x_0=750000 +y_0=-5000000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31265, "epsg", 31265, "MGI / 3-degree Gauss zone 5 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=5500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31266, "epsg", 31266, "MGI / 3-degree Gauss zone 6 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=1 +x_0=6500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31267, "epsg", 31267, "MGI / 3-degree Gauss zone 7 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=1 +x_0=7500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31268, "epsg", 31268, "MGI / 3-degree Gauss zone 8 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=1 +x_0=8500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31275, "epsg", 31275, "MGI / Balkans zone 5 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=0.9999 +x_0=5500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31276, "epsg", 31276, "MGI / Balkans zone 6 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=18 +k=0.9999 +x_0=6500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31277, "epsg", 31277, "MGI / Balkans zone 7 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=0.9999 +x_0=7500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31278, "epsg", 31278, "MGI / Balkans zone 8 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=21 +k=0.9999 +x_0=7500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31279, "epsg", 31279, "MGI / Balkans zone 8 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=24 +k=0.9999 +x_0=8500000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31281, "epsg", 31281, "MGI (Ferro) / Austria West Zone",
        "+proj=tmerc +lat_0=0 +lon_0=28 +k=1 +x_0=0 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31282, "epsg", 31282, "MGI (Ferro) / Austria Central Zone",
        "+proj=tmerc +lat_0=0 +lon_0=31 +k=1 +x_0=0 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31283, "epsg", 31283, "MGI (Ferro) / Austria East Zone",
        "+proj=tmerc +lat_0=0 +lon_0=34 +k=1 +x_0=0 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31284, "epsg", 31284, "MGI / Austria M28",
        "+proj=tmerc +lat_0=0 +lon_0=10.33333333333333 +k=1 +x_0=150000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31285, "epsg", 31285, "MGI / Austria M31",
        "+proj=tmerc +lat_0=0 +lon_0=13.33333333333333 +k=1 +x_0=450000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31286, "epsg", 31286, "MGI / Austria M34",
        "+proj=tmerc +lat_0=0 +lon_0=16.33333333333333 +k=1 +x_0=750000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31287, "epsg", 31287, "MGI / Austria Lambert",
        "+proj=lcc +lat_1=49 +lat_2=46 +lat_0=47.5 +lon_0=13.33333333333333 +x_0=400000 +y_0=400000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31288, "epsg", 31288, "MGI (Ferro) / M28",
        "+proj=tmerc +lat_0=0 +lon_0=28 +k=1 +x_0=150000 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31289, "epsg", 31289, "MGI (Ferro) / M31",
        "+proj=tmerc +lat_0=0 +lon_0=31 +k=1 +x_0=450000 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31290, "epsg", 31290, "MGI (Ferro) / M34",
        "+proj=tmerc +lat_0=0 +lon_0=34 +k=1 +x_0=750000 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31291, "epsg", 31291, "MGI (Ferro) / Austria West Zone (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=28 +k=1 +x_0=0 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31292, "epsg", 31292, "MGI (Ferro) / Austria Central Zone (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=31 +k=1 +x_0=0 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31293, "epsg", 31293, "MGI (Ferro) / Austria East Zone (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=34 +k=1 +x_0=0 +y_0=0 +ellps=bessel +pm=ferro +units=m +no_defs"},
    {
    31294, "epsg", 31294, "MGI / M28 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=10.33333333333333 +k=1 +x_0=150000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31295, "epsg", 31295, "MGI / M31 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=13.33333333333333 +k=1 +x_0=450000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31296, "epsg", 31296, "MGI / M34 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=16.33333333333333 +k=1 +x_0=750000 +y_0=0 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31297, "epsg", 31297, "MGI / Austria Lambert (deprecated)",
        "+proj=lcc +lat_1=49 +lat_2=46 +lat_0=47.5 +lon_0=13.33333333333333 +x_0=400000 +y_0=400000 +ellps=bessel +datum=hermannskogel +units=m +no_defs"},
    {
    31300, "epsg", 31300, "Belge 1972 / Belge Lambert 72",
        "+proj=lcc +lat_1=49.83333333333334 +lat_2=51.16666666666666 +lat_0=90 +lon_0=4.356939722222222 +x_0=150000.01256 +y_0=5400088.4378 +ellps=intl +towgs84=106.869,-52.2978,103.724,-0.33657,0.456955,-1.84218,1 +units=m +no_defs"},
    {
    31370, "epsg", 31370, "Belge 1972 / Belgian Lambert 72",
        "+proj=lcc +lat_1=51.16666723333333 +lat_2=49.8333339 +lat_0=90 +lon_0=4.367486666666666 +x_0=150000.013 +y_0=5400088.438 +ellps=intl +towgs84=106.869,-52.2978,103.724,-0.33657,0.456955,-1.84218,1 +units=m +no_defs"},
    {
    31461, "epsg", 31461, "DHDN / 3-degree Gauss zone 1 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=3 +k=1 +x_0=1500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31462, "epsg", 31462, "DHDN / 3-degree Gauss zone 2 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=6 +k=1 +x_0=2500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31463, "epsg", 31463, "DHDN / 3-degree Gauss zone 3 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=3500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31464, "epsg", 31464, "DHDN / 3-degree Gauss zone 4 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=1 +x_0=4500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31465, "epsg", 31465, "DHDN / 3-degree Gauss zone 5 (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=5500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31466, "epsg", 31466, "DHDN / 3-degree Gauss-Kruger zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=6 +k=1 +x_0=2500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31467, "epsg", 31467, "DHDN / 3-degree Gauss-Kruger zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=9 +k=1 +x_0=3500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31468, "epsg", 31468, "DHDN / 3-degree Gauss-Kruger zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=12 +k=1 +x_0=4500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31469, "epsg", 31469, "DHDN / 3-degree Gauss-Kruger zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=15 +k=1 +x_0=5500000 +y_0=0 +ellps=bessel +datum=potsdam +units=m +no_defs"},
    {
    31528, "epsg", 31528, "Conakry 1905 / UTM zone 28N",
        "+proj=utm +zone=28 +a=6378249.2 +b=6356515 +towgs84=-23,259,-9,0,0,0,0 +units=m +no_defs"},
    {
    31529, "epsg", 31529, "Conakry 1905 / UTM zone 29N",
        "+proj=utm +zone=29 +a=6378249.2 +b=6356515 +towgs84=-23,259,-9,0,0,0,0 +units=m +no_defs"},
    {
    31600, "epsg", 31600, "Dealul Piscului 1930 / Stereo 33",
        "+proj=sterea +lat_0=45.9 +lon_0=25.39246588888889 +k=0.9996667 +x_0=500000 +y_0=500000 +ellps=intl +units=m +no_defs"},
    {
    31700, "epsg", 31700, "Dealul Piscului 1970/ Stereo 70 (deprecated)",
        "+proj=sterea +lat_0=46 +lon_0=25 +k=0.99975 +x_0=500000 +y_0=500000 +ellps=krass +units=m +no_defs"},
    {
    31838, "epsg", 31838, "NGN / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=WGS84 +towgs84=-3.2,-5.7,2.8,0,0,0,0 +units=m +no_defs"},
    {
    31839, "epsg", 31839, "NGN / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=WGS84 +towgs84=-3.2,-5.7,2.8,0,0,0,0 +units=m +no_defs"},
    {
    31900, "epsg", 31900, "KUDAMS / KTM (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=48 +k=0.9996 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    31901, "epsg", 31901, "KUDAMS / KTM",
        "+proj=tmerc +lat_0=0 +lon_0=48 +k=1 +x_0=500000 +y_0=0 +ellps=GRS80 +units=m +no_defs"},
    {
    31965, "epsg", 31965, "SIRGAS 2000 / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31966, "epsg", 31966, "SIRGAS 2000 / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31967, "epsg", 31967, "SIRGAS 2000 / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31968, "epsg", 31968, "SIRGAS 2000 / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31969, "epsg", 31969, "SIRGAS 2000 / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31970, "epsg", 31970, "SIRGAS 2000 / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31971, "epsg", 31971, "SIRGAS 2000 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31972, "epsg", 31972, "SIRGAS 2000 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31973, "epsg", 31973, "SIRGAS 2000 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31974, "epsg", 31974, "SIRGAS 2000 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31975, "epsg", 31975, "SIRGAS 2000 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31976, "epsg", 31976, "SIRGAS 2000 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31977, "epsg", 31977, "SIRGAS 2000 / UTM zone 17S",
        "+proj=utm +zone=17 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31978, "epsg", 31978, "SIRGAS 2000 / UTM zone 18S",
        "+proj=utm +zone=18 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31979, "epsg", 31979, "SIRGAS 2000 / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31980, "epsg", 31980, "SIRGAS 2000 / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31981, "epsg", 31981, "SIRGAS 2000 / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31982, "epsg", 31982, "SIRGAS 2000 / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31983, "epsg", 31983, "SIRGAS 2000 / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31984, "epsg", 31984, "SIRGAS 2000 / UTM zone 24S",
        "+proj=utm +zone=24 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31985, "epsg", 31985, "SIRGAS 2000 / UTM zone 25S",
        "+proj=utm +zone=25 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31986, "epsg", 31986, "SIRGAS 1995 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31987, "epsg", 31987, "SIRGAS 1995 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31988, "epsg", 31988, "SIRGAS 1995 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31989, "epsg", 31989, "SIRGAS 1995 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31990, "epsg", 31990, "SIRGAS 1995 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31991, "epsg", 31991, "SIRGAS 1995 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31992, "epsg", 31992, "SIRGAS 1995 / UTM zone 17S",
        "+proj=utm +zone=17 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31993, "epsg", 31993, "SIRGAS 1995 / UTM zone 18S",
        "+proj=utm +zone=18 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31994, "epsg", 31994, "SIRGAS 1995 / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31995, "epsg", 31995, "SIRGAS 1995 / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31996, "epsg", 31996, "SIRGAS 1995 / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31997, "epsg", 31997, "SIRGAS 1995 / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31998, "epsg", 31998, "SIRGAS 1995 / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    31999, "epsg", 31999, "SIRGAS 1995 / UTM zone 24S",
        "+proj=utm +zone=24 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    32000, "epsg", 32000, "SIRGAS 1995 / UTM zone 25S",
        "+proj=utm +zone=25 +south +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"},
    {
    32001, "epsg", 32001, "NAD27 / Montana North",
        "+proj=lcc +lat_1=48.71666666666667 +lat_2=47.85 +lat_0=47 +lon_0=-109.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32002, "epsg", 32002, "NAD27 / Montana Central",
        "+proj=lcc +lat_1=47.88333333333333 +lat_2=46.45 +lat_0=45.83333333333334 +lon_0=-109.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32003, "epsg", 32003, "NAD27 / Montana South",
        "+proj=lcc +lat_1=46.4 +lat_2=44.86666666666667 +lat_0=44 +lon_0=-109.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32005, "epsg", 32005, "NAD27 / Nebraska North",
        "+proj=lcc +lat_1=41.85 +lat_2=42.81666666666667 +lat_0=41.33333333333334 +lon_0=-100 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32006, "epsg", 32006, "NAD27 / Nebraska South",
        "+proj=lcc +lat_1=40.28333333333333 +lat_2=41.71666666666667 +lat_0=39.66666666666666 +lon_0=-99.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32007, "epsg", 32007, "NAD27 / Nevada East",
        "+proj=tmerc +lat_0=34.75 +lon_0=-115.5833333333333 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32008, "epsg", 32008, "NAD27 / Nevada Central",
        "+proj=tmerc +lat_0=34.75 +lon_0=-116.6666666666667 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32009, "epsg", 32009, "NAD27 / Nevada West",
        "+proj=tmerc +lat_0=34.75 +lon_0=-118.5833333333333 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32010, "epsg", 32010, "NAD27 / New Hampshire",
        "+proj=tmerc +lat_0=42.5 +lon_0=-71.66666666666667 +k=0.999966667 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32011, "epsg", 32011, "NAD27 / New Jersey",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.66666666666667 +k=0.9999749999999999 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32012, "epsg", 32012, "NAD27 / New Mexico East",
        "+proj=tmerc +lat_0=31 +lon_0=-104.3333333333333 +k=0.999909091 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32013, "epsg", 32013, "NAD27 / New Mexico Central",
        "+proj=tmerc +lat_0=31 +lon_0=-106.25 +k=0.9999 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32014, "epsg", 32014, "NAD27 / New Mexico West",
        "+proj=tmerc +lat_0=31 +lon_0=-107.8333333333333 +k=0.999916667 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32015, "epsg", 32015, "NAD27 / New York East",
        "+proj=tmerc +lat_0=40 +lon_0=-74.33333333333333 +k=0.999966667 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32016, "epsg", 32016, "NAD27 / New York Central",
        "+proj=tmerc +lat_0=40 +lon_0=-76.58333333333333 +k=0.9999375 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32017, "epsg", 32017, "NAD27 / New York West",
        "+proj=tmerc +lat_0=40 +lon_0=-78.58333333333333 +k=0.9999375 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32018, "epsg", 32018, "NAD27 / New York Long Island",
        "+proj=lcc +lat_1=41.03333333333333 +lat_2=40.66666666666666 +lat_0=40.5 +lon_0=-74 +x_0=304800.6096012192 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32019, "epsg", 32019, "NAD27 / North Carolina",
        "+proj=lcc +lat_1=34.33333333333334 +lat_2=36.16666666666666 +lat_0=33.75 +lon_0=-79 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32020, "epsg", 32020, "NAD27 / North Dakota North",
        "+proj=lcc +lat_1=47.43333333333333 +lat_2=48.73333333333333 +lat_0=47 +lon_0=-100.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32021, "epsg", 32021, "NAD27 / North Dakota South",
        "+proj=lcc +lat_1=46.18333333333333 +lat_2=47.48333333333333 +lat_0=45.66666666666666 +lon_0=-100.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32022, "epsg", 32022, "NAD27 / Ohio North",
        "+proj=lcc +lat_1=40.43333333333333 +lat_2=41.7 +lat_0=39.66666666666666 +lon_0=-82.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32023, "epsg", 32023, "NAD27 / Ohio South",
        "+proj=lcc +lat_1=38.73333333333333 +lat_2=40.03333333333333 +lat_0=38 +lon_0=-82.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32024, "epsg", 32024, "NAD27 / Oklahoma North",
        "+proj=lcc +lat_1=35.56666666666667 +lat_2=36.76666666666667 +lat_0=35 +lon_0=-98 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32025, "epsg", 32025, "NAD27 / Oklahoma South",
        "+proj=lcc +lat_1=33.93333333333333 +lat_2=35.23333333333333 +lat_0=33.33333333333334 +lon_0=-98 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32026, "epsg", 32026, "NAD27 / Oregon North",
        "+proj=lcc +lat_1=44.33333333333334 +lat_2=46 +lat_0=43.66666666666666 +lon_0=-120.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32027, "epsg", 32027, "NAD27 / Oregon South",
        "+proj=lcc +lat_1=42.33333333333334 +lat_2=44 +lat_0=41.66666666666666 +lon_0=-120.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32028, "epsg", 32028, "NAD27 / Pennsylvania North",
        "+proj=lcc +lat_1=40.88333333333333 +lat_2=41.95 +lat_0=40.16666666666666 +lon_0=-77.75 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32029, "epsg", 32029, "NAD27 / Pennsylvania South",
        "+proj=lcc +lat_1=39.93333333333333 +lat_2=40.8 +lat_0=39.33333333333334 +lon_0=-77.75 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32030, "epsg", 32030, "NAD27 / Rhode Island",
        "+proj=tmerc +lat_0=41.08333333333334 +lon_0=-71.5 +k=0.9999938 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32031, "epsg", 32031, "NAD27 / South Carolina North",
        "+proj=lcc +lat_1=33.76666666666667 +lat_2=34.96666666666667 +lat_0=33 +lon_0=-81 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32033, "epsg", 32033, "NAD27 / South Carolina South",
        "+proj=lcc +lat_1=32.33333333333334 +lat_2=33.66666666666666 +lat_0=31.83333333333333 +lon_0=-81 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32034, "epsg", 32034, "NAD27 / South Dakota North",
        "+proj=lcc +lat_1=44.41666666666666 +lat_2=45.68333333333333 +lat_0=43.83333333333334 +lon_0=-100 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32035, "epsg", 32035, "NAD27 / South Dakota South",
        "+proj=lcc +lat_1=42.83333333333334 +lat_2=44.4 +lat_0=42.33333333333334 +lon_0=-100.3333333333333 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32036, "epsg", 32036, "NAD27 / Tennessee (deprecated)",
        "+proj=lcc +lat_1=35.25 +lat_2=36.41666666666666 +lat_0=34.66666666666666 +lon_0=-86 +x_0=30480.06096012192 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32037, "epsg", 32037, "NAD27 / Texas North",
        "+proj=lcc +lat_1=34.65 +lat_2=36.18333333333333 +lat_0=34 +lon_0=-101.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32038, "epsg", 32038, "NAD27 / Texas North Central",
        "+proj=lcc +lat_1=32.13333333333333 +lat_2=33.96666666666667 +lat_0=31.66666666666667 +lon_0=-97.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32039, "epsg", 32039, "NAD27 / Texas Central",
        "+proj=lcc +lat_1=30.11666666666667 +lat_2=31.88333333333333 +lat_0=29.66666666666667 +lon_0=-100.3333333333333 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32040, "epsg", 32040, "NAD27 / Texas South Central",
        "+proj=lcc +lat_1=28.38333333333333 +lat_2=30.28333333333333 +lat_0=27.83333333333333 +lon_0=-99 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32041, "epsg", 32041, "NAD27 / Texas South",
        "+proj=lcc +lat_1=26.16666666666667 +lat_2=27.83333333333333 +lat_0=25.66666666666667 +lon_0=-98.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32042, "epsg", 32042, "NAD27 / Utah North",
        "+proj=lcc +lat_1=40.71666666666667 +lat_2=41.78333333333333 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32043, "epsg", 32043, "NAD27 / Utah Central",
        "+proj=lcc +lat_1=39.01666666666667 +lat_2=40.65 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32044, "epsg", 32044, "NAD27 / Utah South",
        "+proj=lcc +lat_1=37.21666666666667 +lat_2=38.35 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32045, "epsg", 32045, "NAD27 / Vermont",
        "+proj=tmerc +lat_0=42.5 +lon_0=-72.5 +k=0.999964286 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32046, "epsg", 32046, "NAD27 / Virginia North",
        "+proj=lcc +lat_1=38.03333333333333 +lat_2=39.2 +lat_0=37.66666666666666 +lon_0=-78.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32047, "epsg", 32047, "NAD27 / Virginia South",
        "+proj=lcc +lat_1=36.76666666666667 +lat_2=37.96666666666667 +lat_0=36.33333333333334 +lon_0=-78.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32048, "epsg", 32048, "NAD27 / Washington North",
        "+proj=lcc +lat_1=47.5 +lat_2=48.73333333333333 +lat_0=47 +lon_0=-120.8333333333333 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32049, "epsg", 32049, "NAD27 / Washington South",
        "+proj=lcc +lat_1=45.83333333333334 +lat_2=47.33333333333334 +lat_0=45.33333333333334 +lon_0=-120.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32050, "epsg", 32050, "NAD27 / West Virginia North",
        "+proj=lcc +lat_1=39 +lat_2=40.25 +lat_0=38.5 +lon_0=-79.5 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32051, "epsg", 32051, "NAD27 / West Virginia South",
        "+proj=lcc +lat_1=37.48333333333333 +lat_2=38.88333333333333 +lat_0=37 +lon_0=-81 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32052, "epsg", 32052, "NAD27 / Wisconsin North",
        "+proj=lcc +lat_1=45.56666666666667 +lat_2=46.76666666666667 +lat_0=45.16666666666666 +lon_0=-90 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32053, "epsg", 32053, "NAD27 / Wisconsin Central",
        "+proj=lcc +lat_1=44.25 +lat_2=45.5 +lat_0=43.83333333333334 +lon_0=-90 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32054, "epsg", 32054, "NAD27 / Wisconsin South",
        "+proj=lcc +lat_1=42.73333333333333 +lat_2=44.06666666666667 +lat_0=42 +lon_0=-90 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32055, "epsg", 32055, "NAD27 / Wyoming East",
        "+proj=tmerc +lat_0=40.66666666666666 +lon_0=-105.1666666666667 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32056, "epsg", 32056, "NAD27 / Wyoming East Central",
        "+proj=tmerc +lat_0=40.66666666666666 +lon_0=-107.3333333333333 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32057, "epsg", 32057, "NAD27 / Wyoming West Central",
        "+proj=tmerc +lat_0=40.66666666666666 +lon_0=-108.75 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32058, "epsg", 32058, "NAD27 / Wyoming West",
        "+proj=tmerc +lat_0=40.66666666666666 +lon_0=-110.0833333333333 +k=0.999941177 +x_0=152400.3048006096 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32061, "epsg", 32061, "NAD27 / Guatemala Norte",
        "+proj=lcc +lat_1=16.81666666666667 +lat_0=16.81666666666667 +lon_0=-90.33333333333333 +k_0=0.99992226 +x_0=500000 +y_0=292209.579 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32062, "epsg", 32062, "NAD27 / Guatemala Sur",
        "+proj=lcc +lat_1=14.9 +lat_0=14.9 +lon_0=-90.33333333333333 +k_0=0.99989906 +x_0=500000 +y_0=325992.681 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32064, "epsg", 32064, "NAD27 / BLM 14N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-99 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32065, "epsg", 32065, "NAD27 / BLM 15N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-93 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32066, "epsg", 32066, "NAD27 / BLM 16N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-87 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32067, "epsg", 32067, "NAD27 / BLM 17N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-81 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32074, "epsg", 32074, "NAD27 / BLM 14N (feet) (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-99 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32075, "epsg", 32075, "NAD27 / BLM 15N (feet) (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-93 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32076, "epsg", 32076, "NAD27 / BLM 16N (feet) (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-87 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32077, "epsg", 32077, "NAD27 / BLM 17N (feet) (deprecated)",
        "+proj=tmerc +lat_0=0 +lon_0=-81 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32081, "epsg", 32081, "NAD27 / MTM zone 1",
        "+proj=tmerc +lat_0=0 +lon_0=-53 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32082, "epsg", 32082, "NAD27 / MTM zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=-56 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32083, "epsg", 32083, "NAD27 / MTM zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=-58.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32084, "epsg", 32084, "NAD27 / MTM zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=-61.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32085, "epsg", 32085, "NAD27 / MTM zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=-64.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32086, "epsg", 32086, "NAD27 / MTM zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=-67.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32098, "epsg", 32098, "NAD27 / Quebec Lambert",
        "+proj=lcc +lat_1=60 +lat_2=46 +lat_0=44 +lon_0=-68.5 +x_0=0 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=m +no_defs"},
    {
    32099, "epsg", 32099, "NAD27 / Louisiana Offshore",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.66666666666667 +lon_0=-91.33333333333333 +x_0=609601.2192024384 +y_0=0 +ellps=clrk66 +datum=NAD27 +units=us-ft +no_defs"},
    {
    32100, "epsg", 32100, "NAD83 / Montana",
        "+proj=lcc +lat_1=49 +lat_2=45 +lat_0=44.25 +lon_0=-109.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32104, "epsg", 32104, "NAD83 / Nebraska",
        "+proj=lcc +lat_1=43 +lat_2=40 +lat_0=39.83333333333334 +lon_0=-100 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32107, "epsg", 32107, "NAD83 / Nevada East",
        "+proj=tmerc +lat_0=34.75 +lon_0=-115.5833333333333 +k=0.9999 +x_0=200000 +y_0=8000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32108, "epsg", 32108, "NAD83 / Nevada Central",
        "+proj=tmerc +lat_0=34.75 +lon_0=-116.6666666666667 +k=0.9999 +x_0=500000 +y_0=6000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32109, "epsg", 32109, "NAD83 / Nevada West",
        "+proj=tmerc +lat_0=34.75 +lon_0=-118.5833333333333 +k=0.9999 +x_0=800000 +y_0=4000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32110, "epsg", 32110, "NAD83 / New Hampshire",
        "+proj=tmerc +lat_0=42.5 +lon_0=-71.66666666666667 +k=0.999966667 +x_0=300000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32111, "epsg", 32111, "NAD83 / New Jersey",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32112, "epsg", 32112, "NAD83 / New Mexico East",
        "+proj=tmerc +lat_0=31 +lon_0=-104.3333333333333 +k=0.999909091 +x_0=165000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32113, "epsg", 32113, "NAD83 / New Mexico Central",
        "+proj=tmerc +lat_0=31 +lon_0=-106.25 +k=0.9999 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32114, "epsg", 32114, "NAD83 / New Mexico West",
        "+proj=tmerc +lat_0=31 +lon_0=-107.8333333333333 +k=0.999916667 +x_0=830000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32115, "epsg", 32115, "NAD83 / New York East",
        "+proj=tmerc +lat_0=38.83333333333334 +lon_0=-74.5 +k=0.9999 +x_0=150000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32116, "epsg", 32116, "NAD83 / New York Central",
        "+proj=tmerc +lat_0=40 +lon_0=-76.58333333333333 +k=0.9999375 +x_0=250000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32117, "epsg", 32117, "NAD83 / New York West",
        "+proj=tmerc +lat_0=40 +lon_0=-78.58333333333333 +k=0.9999375 +x_0=350000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32118, "epsg", 32118, "NAD83 / New York Long Island",
        "+proj=lcc +lat_1=41.03333333333333 +lat_2=40.66666666666666 +lat_0=40.16666666666666 +lon_0=-74 +x_0=300000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32119, "epsg", 32119, "NAD83 / North Carolina",
        "+proj=lcc +lat_1=36.16666666666666 +lat_2=34.33333333333334 +lat_0=33.75 +lon_0=-79 +x_0=609601.22 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32120, "epsg", 32120, "NAD83 / North Dakota North",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.43333333333333 +lat_0=47 +lon_0=-100.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32121, "epsg", 32121, "NAD83 / North Dakota South",
        "+proj=lcc +lat_1=47.48333333333333 +lat_2=46.18333333333333 +lat_0=45.66666666666666 +lon_0=-100.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32122, "epsg", 32122, "NAD83 / Ohio North",
        "+proj=lcc +lat_1=41.7 +lat_2=40.43333333333333 +lat_0=39.66666666666666 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32123, "epsg", 32123, "NAD83 / Ohio South",
        "+proj=lcc +lat_1=40.03333333333333 +lat_2=38.73333333333333 +lat_0=38 +lon_0=-82.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32124, "epsg", 32124, "NAD83 / Oklahoma North",
        "+proj=lcc +lat_1=36.76666666666667 +lat_2=35.56666666666667 +lat_0=35 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32125, "epsg", 32125, "NAD83 / Oklahoma South",
        "+proj=lcc +lat_1=35.23333333333333 +lat_2=33.93333333333333 +lat_0=33.33333333333334 +lon_0=-98 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32126, "epsg", 32126, "NAD83 / Oregon North",
        "+proj=lcc +lat_1=46 +lat_2=44.33333333333334 +lat_0=43.66666666666666 +lon_0=-120.5 +x_0=2500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32127, "epsg", 32127, "NAD83 / Oregon South",
        "+proj=lcc +lat_1=44 +lat_2=42.33333333333334 +lat_0=41.66666666666666 +lon_0=-120.5 +x_0=1500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32128, "epsg", 32128, "NAD83 / Pennsylvania North",
        "+proj=lcc +lat_1=41.95 +lat_2=40.88333333333333 +lat_0=40.16666666666666 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32129, "epsg", 32129, "NAD83 / Pennsylvania South",
        "+proj=lcc +lat_1=40.96666666666667 +lat_2=39.93333333333333 +lat_0=39.33333333333334 +lon_0=-77.75 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32130, "epsg", 32130, "NAD83 / Rhode Island",
        "+proj=tmerc +lat_0=41.08333333333334 +lon_0=-71.5 +k=0.99999375 +x_0=100000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32133, "epsg", 32133, "NAD83 / South Carolina",
        "+proj=lcc +lat_1=34.83333333333334 +lat_2=32.5 +lat_0=31.83333333333333 +lon_0=-81 +x_0=609600 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32134, "epsg", 32134, "NAD83 / South Dakota North",
        "+proj=lcc +lat_1=45.68333333333333 +lat_2=44.41666666666666 +lat_0=43.83333333333334 +lon_0=-100 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32135, "epsg", 32135, "NAD83 / South Dakota South",
        "+proj=lcc +lat_1=44.4 +lat_2=42.83333333333334 +lat_0=42.33333333333334 +lon_0=-100.3333333333333 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32136, "epsg", 32136, "NAD83 / Tennessee",
        "+proj=lcc +lat_1=36.41666666666666 +lat_2=35.25 +lat_0=34.33333333333334 +lon_0=-86 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32137, "epsg", 32137, "NAD83 / Texas North",
        "+proj=lcc +lat_1=36.18333333333333 +lat_2=34.65 +lat_0=34 +lon_0=-101.5 +x_0=200000 +y_0=1000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32138, "epsg", 32138, "NAD83 / Texas North Central",
        "+proj=lcc +lat_1=33.96666666666667 +lat_2=32.13333333333333 +lat_0=31.66666666666667 +lon_0=-98.5 +x_0=600000 +y_0=2000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32139, "epsg", 32139, "NAD83 / Texas Central",
        "+proj=lcc +lat_1=31.88333333333333 +lat_2=30.11666666666667 +lat_0=29.66666666666667 +lon_0=-100.3333333333333 +x_0=700000 +y_0=3000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32140, "epsg", 32140, "NAD83 / Texas South Central",
        "+proj=lcc +lat_1=30.28333333333333 +lat_2=28.38333333333333 +lat_0=27.83333333333333 +lon_0=-99 +x_0=600000 +y_0=4000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32141, "epsg", 32141, "NAD83 / Texas South",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.66666666666667 +lon_0=-98.5 +x_0=300000 +y_0=5000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32142, "epsg", 32142, "NAD83 / Utah North",
        "+proj=lcc +lat_1=41.78333333333333 +lat_2=40.71666666666667 +lat_0=40.33333333333334 +lon_0=-111.5 +x_0=500000 +y_0=1000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32143, "epsg", 32143, "NAD83 / Utah Central",
        "+proj=lcc +lat_1=40.65 +lat_2=39.01666666666667 +lat_0=38.33333333333334 +lon_0=-111.5 +x_0=500000 +y_0=2000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32144, "epsg", 32144, "NAD83 / Utah South",
        "+proj=lcc +lat_1=38.35 +lat_2=37.21666666666667 +lat_0=36.66666666666666 +lon_0=-111.5 +x_0=500000 +y_0=3000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32145, "epsg", 32145, "NAD83 / Vermont",
        "+proj=tmerc +lat_0=42.5 +lon_0=-72.5 +k=0.999964286 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32146, "epsg", 32146, "NAD83 / Virginia North",
        "+proj=lcc +lat_1=39.2 +lat_2=38.03333333333333 +lat_0=37.66666666666666 +lon_0=-78.5 +x_0=3500000 +y_0=2000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32147, "epsg", 32147, "NAD83 / Virginia South",
        "+proj=lcc +lat_1=37.96666666666667 +lat_2=36.76666666666667 +lat_0=36.33333333333334 +lon_0=-78.5 +x_0=3500000 +y_0=1000000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32148, "epsg", 32148, "NAD83 / Washington North",
        "+proj=lcc +lat_1=48.73333333333333 +lat_2=47.5 +lat_0=47 +lon_0=-120.8333333333333 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32149, "epsg", 32149, "NAD83 / Washington South",
        "+proj=lcc +lat_1=47.33333333333334 +lat_2=45.83333333333334 +lat_0=45.33333333333334 +lon_0=-120.5 +x_0=500000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32150, "epsg", 32150, "NAD83 / West Virginia North",
        "+proj=lcc +lat_1=40.25 +lat_2=39 +lat_0=38.5 +lon_0=-79.5 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32151, "epsg", 32151, "NAD83 / West Virginia South",
        "+proj=lcc +lat_1=38.88333333333333 +lat_2=37.48333333333333 +lat_0=37 +lon_0=-81 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32152, "epsg", 32152, "NAD83 / Wisconsin North",
        "+proj=lcc +lat_1=46.76666666666667 +lat_2=45.56666666666667 +lat_0=45.16666666666666 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32153, "epsg", 32153, "NAD83 / Wisconsin Central",
        "+proj=lcc +lat_1=45.5 +lat_2=44.25 +lat_0=43.83333333333334 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32154, "epsg", 32154, "NAD83 / Wisconsin South",
        "+proj=lcc +lat_1=44.06666666666667 +lat_2=42.73333333333333 +lat_0=42 +lon_0=-90 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32155, "epsg", 32155, "NAD83 / Wyoming East",
        "+proj=tmerc +lat_0=40.5 +lon_0=-105.1666666666667 +k=0.9999375 +x_0=200000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32156, "epsg", 32156, "NAD83 / Wyoming East Central",
        "+proj=tmerc +lat_0=40.5 +lon_0=-107.3333333333333 +k=0.9999375 +x_0=400000 +y_0=100000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32157, "epsg", 32157, "NAD83 / Wyoming West Central",
        "+proj=tmerc +lat_0=40.5 +lon_0=-108.75 +k=0.9999375 +x_0=600000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32158, "epsg", 32158, "NAD83 / Wyoming West",
        "+proj=tmerc +lat_0=40.5 +lon_0=-110.0833333333333 +k=0.9999375 +x_0=800000 +y_0=100000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32161, "epsg", 32161, "NAD83 / Puerto Rico & Virgin Is.",
        "+proj=lcc +lat_1=18.43333333333333 +lat_2=18.03333333333333 +lat_0=17.83333333333333 +lon_0=-66.43333333333334 +x_0=200000 +y_0=200000 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32164, "epsg", 32164, "NAD83 / BLM 14N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-99 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    32165, "epsg", 32165, "NAD83 / BLM 15N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-93 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    32166, "epsg", 32166, "NAD83 / BLM 16N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-87 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    32167, "epsg", 32167, "NAD83 / BLM 17N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-81 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=us-ft +no_defs"},
    {
    32180, "epsg", 32180, "NAD83 / SCoPQ zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=-55.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32181, "epsg", 32181, "NAD83 / MTM zone 1",
        "+proj=tmerc +lat_0=0 +lon_0=-53 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32182, "epsg", 32182, "NAD83 / MTM zone 2",
        "+proj=tmerc +lat_0=0 +lon_0=-56 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32183, "epsg", 32183, "NAD83 / MTM zone 3",
        "+proj=tmerc +lat_0=0 +lon_0=-58.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32184, "epsg", 32184, "NAD83 / MTM zone 4",
        "+proj=tmerc +lat_0=0 +lon_0=-61.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32185, "epsg", 32185, "NAD83 / MTM zone 5",
        "+proj=tmerc +lat_0=0 +lon_0=-64.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32186, "epsg", 32186, "NAD83 / MTM zone 6",
        "+proj=tmerc +lat_0=0 +lon_0=-67.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32187, "epsg", 32187, "NAD83 / MTM zone 7",
        "+proj=tmerc +lat_0=0 +lon_0=-70.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32188, "epsg", 32188, "NAD83 / MTM zone 8",
        "+proj=tmerc +lat_0=0 +lon_0=-73.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32189, "epsg", 32189, "NAD83 / MTM zone 9",
        "+proj=tmerc +lat_0=0 +lon_0=-76.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32190, "epsg", 32190, "NAD83 / MTM zone 10",
        "+proj=tmerc +lat_0=0 +lon_0=-79.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32191, "epsg", 32191, "NAD83 / MTM zone 11",
        "+proj=tmerc +lat_0=0 +lon_0=-82.5 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32192, "epsg", 32192, "NAD83 / MTM zone 12",
        "+proj=tmerc +lat_0=0 +lon_0=-81 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32193, "epsg", 32193, "NAD83 / MTM zone 13",
        "+proj=tmerc +lat_0=0 +lon_0=-84 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32194, "epsg", 32194, "NAD83 / MTM zone 14",
        "+proj=tmerc +lat_0=0 +lon_0=-87 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32195, "epsg", 32195, "NAD83 / MTM zone 15",
        "+proj=tmerc +lat_0=0 +lon_0=-90 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32196, "epsg", 32196, "NAD83 / MTM zone 16",
        "+proj=tmerc +lat_0=0 +lon_0=-93 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32197, "epsg", 32197, "NAD83 / MTM zone 17",
        "+proj=tmerc +lat_0=0 +lon_0=-96 +k=0.9999 +x_0=304800 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32198, "epsg", 32198, "NAD83 / Quebec Lambert",
        "+proj=lcc +lat_1=60 +lat_2=46 +lat_0=44 +lon_0=-68.5 +x_0=0 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32199, "epsg", 32199, "NAD83 / Louisiana Offshore",
        "+proj=lcc +lat_1=27.83333333333333 +lat_2=26.16666666666667 +lat_0=25.5 +lon_0=-91.33333333333333 +x_0=1000000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs"},
    {
    32201, "epsg", 32201, "WGS 72 / UTM zone 1N",
        "+proj=utm +zone=1 +ellps=WGS72 +units=m +no_defs"},
    {
    32202, "epsg", 32202, "WGS 72 / UTM zone 2N",
        "+proj=utm +zone=2 +ellps=WGS72 +units=m +no_defs"},
    {
    32203, "epsg", 32203, "WGS 72 / UTM zone 3N",
        "+proj=utm +zone=3 +ellps=WGS72 +units=m +no_defs"},
    {
    32204, "epsg", 32204, "WGS 72 / UTM zone 4N",
        "+proj=utm +zone=4 +ellps=WGS72 +units=m +no_defs"},
    {
    32205, "epsg", 32205, "WGS 72 / UTM zone 5N",
        "+proj=utm +zone=5 +ellps=WGS72 +units=m +no_defs"},
    {
    32206, "epsg", 32206, "WGS 72 / UTM zone 6N",
        "+proj=utm +zone=6 +ellps=WGS72 +units=m +no_defs"},
    {
    32207, "epsg", 32207, "WGS 72 / UTM zone 7N",
        "+proj=utm +zone=7 +ellps=WGS72 +units=m +no_defs"},
    {
    32208, "epsg", 32208, "WGS 72 / UTM zone 8N",
        "+proj=utm +zone=8 +ellps=WGS72 +units=m +no_defs"},
    {
    32209, "epsg", 32209, "WGS 72 / UTM zone 9N",
        "+proj=utm +zone=9 +ellps=WGS72 +units=m +no_defs"},
    {
    32210, "epsg", 32210, "WGS 72 / UTM zone 10N",
        "+proj=utm +zone=10 +ellps=WGS72 +units=m +no_defs"},
    {
    32211, "epsg", 32211, "WGS 72 / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=WGS72 +units=m +no_defs"},
    {
    32212, "epsg", 32212, "WGS 72 / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=WGS72 +units=m +no_defs"},
    {
    32213, "epsg", 32213, "WGS 72 / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=WGS72 +units=m +no_defs"},
    {
    32214, "epsg", 32214, "WGS 72 / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=WGS72 +units=m +no_defs"},
    {
    32215, "epsg", 32215, "WGS 72 / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=WGS72 +units=m +no_defs"},
    {
    32216, "epsg", 32216, "WGS 72 / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=WGS72 +units=m +no_defs"},
    {
    32217, "epsg", 32217, "WGS 72 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=WGS72 +units=m +no_defs"},
    {
    32218, "epsg", 32218, "WGS 72 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=WGS72 +units=m +no_defs"},
    {
    32219, "epsg", 32219, "WGS 72 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=WGS72 +units=m +no_defs"},
    {
    32220, "epsg", 32220, "WGS 72 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=WGS72 +units=m +no_defs"},
    {
    32221, "epsg", 32221, "WGS 72 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=WGS72 +units=m +no_defs"},
    {
    32222, "epsg", 32222, "WGS 72 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=WGS72 +units=m +no_defs"},
    {
    32223, "epsg", 32223, "WGS 72 / UTM zone 23N",
        "+proj=utm +zone=23 +ellps=WGS72 +units=m +no_defs"},
    {
    32224, "epsg", 32224, "WGS 72 / UTM zone 24N",
        "+proj=utm +zone=24 +ellps=WGS72 +units=m +no_defs"},
    {
    32225, "epsg", 32225, "WGS 72 / UTM zone 25N",
        "+proj=utm +zone=25 +ellps=WGS72 +units=m +no_defs"},
    {
    32226, "epsg", 32226, "WGS 72 / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=WGS72 +units=m +no_defs"},
    {
    32227, "epsg", 32227, "WGS 72 / UTM zone 27N",
        "+proj=utm +zone=27 +ellps=WGS72 +units=m +no_defs"},
    {
    32228, "epsg", 32228, "WGS 72 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=WGS72 +units=m +no_defs"},
    {
    32229, "epsg", 32229, "WGS 72 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=WGS72 +units=m +no_defs"},
    {
    32230, "epsg", 32230, "WGS 72 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=WGS72 +units=m +no_defs"},
    {
    32231, "epsg", 32231, "WGS 72 / UTM zone 31N",
        "+proj=utm +zone=31 +ellps=WGS72 +units=m +no_defs"},
    {
    32232, "epsg", 32232, "WGS 72 / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=WGS72 +units=m +no_defs"},
    {
    32233, "epsg", 32233, "WGS 72 / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=WGS72 +units=m +no_defs"},
    {
    32234, "epsg", 32234, "WGS 72 / UTM zone 34N",
        "+proj=utm +zone=34 +ellps=WGS72 +units=m +no_defs"},
    {
    32235, "epsg", 32235, "WGS 72 / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=WGS72 +units=m +no_defs"},
    {
    32236, "epsg", 32236, "WGS 72 / UTM zone 36N",
        "+proj=utm +zone=36 +ellps=WGS72 +units=m +no_defs"},
    {
    32237, "epsg", 32237, "WGS 72 / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=WGS72 +units=m +no_defs"},
    {
    32238, "epsg", 32238, "WGS 72 / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=WGS72 +units=m +no_defs"},
    {
    32239, "epsg", 32239, "WGS 72 / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=WGS72 +units=m +no_defs"},
    {
    32240, "epsg", 32240, "WGS 72 / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=WGS72 +units=m +no_defs"},
    {
    32241, "epsg", 32241, "WGS 72 / UTM zone 41N",
        "+proj=utm +zone=41 +ellps=WGS72 +units=m +no_defs"},
    {
    32242, "epsg", 32242, "WGS 72 / UTM zone 42N",
        "+proj=utm +zone=42 +ellps=WGS72 +units=m +no_defs"},
    {
    32243, "epsg", 32243, "WGS 72 / UTM zone 43N",
        "+proj=utm +zone=43 +ellps=WGS72 +units=m +no_defs"},
    {
    32244, "epsg", 32244, "WGS 72 / UTM zone 44N",
        "+proj=utm +zone=44 +ellps=WGS72 +units=m +no_defs"},
    {
    32245, "epsg", 32245, "WGS 72 / UTM zone 45N",
        "+proj=utm +zone=45 +ellps=WGS72 +units=m +no_defs"},
    {
    32246, "epsg", 32246, "WGS 72 / UTM zone 46N",
        "+proj=utm +zone=46 +ellps=WGS72 +units=m +no_defs"},
    {
    32247, "epsg", 32247, "WGS 72 / UTM zone 47N",
        "+proj=utm +zone=47 +ellps=WGS72 +units=m +no_defs"},
    {
    32248, "epsg", 32248, "WGS 72 / UTM zone 48N",
        "+proj=utm +zone=48 +ellps=WGS72 +units=m +no_defs"},
    {
    32249, "epsg", 32249, "WGS 72 / UTM zone 49N",
        "+proj=utm +zone=49 +ellps=WGS72 +units=m +no_defs"},
    {
    32250, "epsg", 32250, "WGS 72 / UTM zone 50N",
        "+proj=utm +zone=50 +ellps=WGS72 +units=m +no_defs"},
    {
    32251, "epsg", 32251, "WGS 72 / UTM zone 51N",
        "+proj=utm +zone=51 +ellps=WGS72 +units=m +no_defs"},
    {
    32252, "epsg", 32252, "WGS 72 / UTM zone 52N",
        "+proj=utm +zone=52 +ellps=WGS72 +units=m +no_defs"},
    {
    32253, "epsg", 32253, "WGS 72 / UTM zone 53N",
        "+proj=utm +zone=53 +ellps=WGS72 +units=m +no_defs"},
    {
    32254, "epsg", 32254, "WGS 72 / UTM zone 54N",
        "+proj=utm +zone=54 +ellps=WGS72 +units=m +no_defs"},
    {
    32255, "epsg", 32255, "WGS 72 / UTM zone 55N",
        "+proj=utm +zone=55 +ellps=WGS72 +units=m +no_defs"},
    {
    32256, "epsg", 32256, "WGS 72 / UTM zone 56N",
        "+proj=utm +zone=56 +ellps=WGS72 +units=m +no_defs"},
    {
    32257, "epsg", 32257, "WGS 72 / UTM zone 57N",
        "+proj=utm +zone=57 +ellps=WGS72 +units=m +no_defs"},
    {
    32258, "epsg", 32258, "WGS 72 / UTM zone 58N",
        "+proj=utm +zone=58 +ellps=WGS72 +units=m +no_defs"},
    {
    32259, "epsg", 32259, "WGS 72 / UTM zone 59N",
        "+proj=utm +zone=59 +ellps=WGS72 +units=m +no_defs"},
    {
    32260, "epsg", 32260, "WGS 72 / UTM zone 60N",
        "+proj=utm +zone=60 +ellps=WGS72 +units=m +no_defs"},
    {
    32301, "epsg", 32301, "WGS 72 / UTM zone 1S",
        "+proj=utm +zone=1 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32302, "epsg", 32302, "WGS 72 / UTM zone 2S",
        "+proj=utm +zone=2 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32303, "epsg", 32303, "WGS 72 / UTM zone 3S",
        "+proj=utm +zone=3 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32304, "epsg", 32304, "WGS 72 / UTM zone 4S",
        "+proj=utm +zone=4 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32305, "epsg", 32305, "WGS 72 / UTM zone 5S",
        "+proj=utm +zone=5 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32306, "epsg", 32306, "WGS 72 / UTM zone 6S",
        "+proj=utm +zone=6 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32307, "epsg", 32307, "WGS 72 / UTM zone 7S",
        "+proj=utm +zone=7 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32308, "epsg", 32308, "WGS 72 / UTM zone 8S",
        "+proj=utm +zone=8 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32309, "epsg", 32309, "WGS 72 / UTM zone 9S",
        "+proj=utm +zone=9 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32310, "epsg", 32310, "WGS 72 / UTM zone 10S",
        "+proj=utm +zone=10 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32311, "epsg", 32311, "WGS 72 / UTM zone 11S",
        "+proj=utm +zone=11 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32312, "epsg", 32312, "WGS 72 / UTM zone 12S",
        "+proj=utm +zone=12 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32313, "epsg", 32313, "WGS 72 / UTM zone 13S",
        "+proj=utm +zone=13 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32314, "epsg", 32314, "WGS 72 / UTM zone 14S",
        "+proj=utm +zone=14 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32315, "epsg", 32315, "WGS 72 / UTM zone 15S",
        "+proj=utm +zone=15 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32316, "epsg", 32316, "WGS 72 / UTM zone 16S",
        "+proj=utm +zone=16 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32317, "epsg", 32317, "WGS 72 / UTM zone 17S",
        "+proj=utm +zone=17 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32318, "epsg", 32318, "WGS 72 / UTM zone 18S",
        "+proj=utm +zone=18 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32319, "epsg", 32319, "WGS 72 / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32320, "epsg", 32320, "WGS 72 / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32321, "epsg", 32321, "WGS 72 / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32322, "epsg", 32322, "WGS 72 / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32323, "epsg", 32323, "WGS 72 / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32324, "epsg", 32324, "WGS 72 / UTM zone 24S",
        "+proj=utm +zone=24 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32325, "epsg", 32325, "WGS 72 / UTM zone 25S",
        "+proj=utm +zone=25 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32326, "epsg", 32326, "WGS 72 / UTM zone 26S",
        "+proj=utm +zone=26 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32327, "epsg", 32327, "WGS 72 / UTM zone 27S",
        "+proj=utm +zone=27 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32328, "epsg", 32328, "WGS 72 / UTM zone 28S",
        "+proj=utm +zone=28 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32329, "epsg", 32329, "WGS 72 / UTM zone 29S",
        "+proj=utm +zone=29 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32330, "epsg", 32330, "WGS 72 / UTM zone 30S",
        "+proj=utm +zone=30 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32331, "epsg", 32331, "WGS 72 / UTM zone 31S",
        "+proj=utm +zone=31 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32332, "epsg", 32332, "WGS 72 / UTM zone 32S",
        "+proj=utm +zone=32 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32333, "epsg", 32333, "WGS 72 / UTM zone 33S",
        "+proj=utm +zone=33 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32334, "epsg", 32334, "WGS 72 / UTM zone 34S",
        "+proj=utm +zone=34 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32335, "epsg", 32335, "WGS 72 / UTM zone 35S",
        "+proj=utm +zone=35 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32336, "epsg", 32336, "WGS 72 / UTM zone 36S",
        "+proj=utm +zone=36 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32337, "epsg", 32337, "WGS 72 / UTM zone 37S",
        "+proj=utm +zone=37 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32338, "epsg", 32338, "WGS 72 / UTM zone 38S",
        "+proj=utm +zone=38 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32339, "epsg", 32339, "WGS 72 / UTM zone 39S",
        "+proj=utm +zone=39 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32340, "epsg", 32340, "WGS 72 / UTM zone 40S",
        "+proj=utm +zone=40 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32341, "epsg", 32341, "WGS 72 / UTM zone 41S",
        "+proj=utm +zone=41 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32342, "epsg", 32342, "WGS 72 / UTM zone 42S",
        "+proj=utm +zone=42 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32343, "epsg", 32343, "WGS 72 / UTM zone 43S",
        "+proj=utm +zone=43 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32344, "epsg", 32344, "WGS 72 / UTM zone 44S",
        "+proj=utm +zone=44 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32345, "epsg", 32345, "WGS 72 / UTM zone 45S",
        "+proj=utm +zone=45 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32346, "epsg", 32346, "WGS 72 / UTM zone 46S",
        "+proj=utm +zone=46 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32347, "epsg", 32347, "WGS 72 / UTM zone 47S",
        "+proj=utm +zone=47 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32348, "epsg", 32348, "WGS 72 / UTM zone 48S",
        "+proj=utm +zone=48 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32349, "epsg", 32349, "WGS 72 / UTM zone 49S",
        "+proj=utm +zone=49 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32350, "epsg", 32350, "WGS 72 / UTM zone 50S",
        "+proj=utm +zone=50 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32351, "epsg", 32351, "WGS 72 / UTM zone 51S",
        "+proj=utm +zone=51 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32352, "epsg", 32352, "WGS 72 / UTM zone 52S",
        "+proj=utm +zone=52 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32353, "epsg", 32353, "WGS 72 / UTM zone 53S",
        "+proj=utm +zone=53 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32354, "epsg", 32354, "WGS 72 / UTM zone 54S",
        "+proj=utm +zone=54 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32355, "epsg", 32355, "WGS 72 / UTM zone 55S",
        "+proj=utm +zone=55 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32356, "epsg", 32356, "WGS 72 / UTM zone 56S",
        "+proj=utm +zone=56 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32357, "epsg", 32357, "WGS 72 / UTM zone 57S",
        "+proj=utm +zone=57 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32358, "epsg", 32358, "WGS 72 / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32359, "epsg", 32359, "WGS 72 / UTM zone 59S",
        "+proj=utm +zone=59 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32360, "epsg", 32360, "WGS 72 / UTM zone 60S",
        "+proj=utm +zone=60 +south +ellps=WGS72 +units=m +no_defs"},
    {
    32401, "epsg", 32401, "WGS 72BE / UTM zone 1N",
        "+proj=utm +zone=1 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32402, "epsg", 32402, "WGS 72BE / UTM zone 2N",
        "+proj=utm +zone=2 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32403, "epsg", 32403, "WGS 72BE / UTM zone 3N",
        "+proj=utm +zone=3 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32404, "epsg", 32404, "WGS 72BE / UTM zone 4N",
        "+proj=utm +zone=4 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32405, "epsg", 32405, "WGS 72BE / UTM zone 5N",
        "+proj=utm +zone=5 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32406, "epsg", 32406, "WGS 72BE / UTM zone 6N",
        "+proj=utm +zone=6 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32407, "epsg", 32407, "WGS 72BE / UTM zone 7N",
        "+proj=utm +zone=7 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32408, "epsg", 32408, "WGS 72BE / UTM zone 8N",
        "+proj=utm +zone=8 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32409, "epsg", 32409, "WGS 72BE / UTM zone 9N",
        "+proj=utm +zone=9 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32410, "epsg", 32410, "WGS 72BE / UTM zone 10N",
        "+proj=utm +zone=10 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32411, "epsg", 32411, "WGS 72BE / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32412, "epsg", 32412, "WGS 72BE / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32413, "epsg", 32413, "WGS 72BE / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32414, "epsg", 32414, "WGS 72BE / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32415, "epsg", 32415, "WGS 72BE / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32416, "epsg", 32416, "WGS 72BE / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32417, "epsg", 32417, "WGS 72BE / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32418, "epsg", 32418, "WGS 72BE / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32419, "epsg", 32419, "WGS 72BE / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32420, "epsg", 32420, "WGS 72BE / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32421, "epsg", 32421, "WGS 72BE / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32422, "epsg", 32422, "WGS 72BE / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32423, "epsg", 32423, "WGS 72BE / UTM zone 23N",
        "+proj=utm +zone=23 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32424, "epsg", 32424, "WGS 72BE / UTM zone 24N",
        "+proj=utm +zone=24 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32425, "epsg", 32425, "WGS 72BE / UTM zone 25N",
        "+proj=utm +zone=25 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32426, "epsg", 32426, "WGS 72BE / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32427, "epsg", 32427, "WGS 72BE / UTM zone 27N",
        "+proj=utm +zone=27 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32428, "epsg", 32428, "WGS 72BE / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32429, "epsg", 32429, "WGS 72BE / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32430, "epsg", 32430, "WGS 72BE / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32431, "epsg", 32431, "WGS 72BE / UTM zone 31N",
        "+proj=utm +zone=31 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32432, "epsg", 32432, "WGS 72BE / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32433, "epsg", 32433, "WGS 72BE / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32434, "epsg", 32434, "WGS 72BE / UTM zone 34N",
        "+proj=utm +zone=34 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32435, "epsg", 32435, "WGS 72BE / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32436, "epsg", 32436, "WGS 72BE / UTM zone 36N",
        "+proj=utm +zone=36 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32437, "epsg", 32437, "WGS 72BE / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32438, "epsg", 32438, "WGS 72BE / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32439, "epsg", 32439, "WGS 72BE / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32440, "epsg", 32440, "WGS 72BE / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32441, "epsg", 32441, "WGS 72BE / UTM zone 41N",
        "+proj=utm +zone=41 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32442, "epsg", 32442, "WGS 72BE / UTM zone 42N",
        "+proj=utm +zone=42 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32443, "epsg", 32443, "WGS 72BE / UTM zone 43N",
        "+proj=utm +zone=43 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32444, "epsg", 32444, "WGS 72BE / UTM zone 44N",
        "+proj=utm +zone=44 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32445, "epsg", 32445, "WGS 72BE / UTM zone 45N",
        "+proj=utm +zone=45 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32446, "epsg", 32446, "WGS 72BE / UTM zone 46N",
        "+proj=utm +zone=46 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32447, "epsg", 32447, "WGS 72BE / UTM zone 47N",
        "+proj=utm +zone=47 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32448, "epsg", 32448, "WGS 72BE / UTM zone 48N",
        "+proj=utm +zone=48 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32449, "epsg", 32449, "WGS 72BE / UTM zone 49N",
        "+proj=utm +zone=49 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32450, "epsg", 32450, "WGS 72BE / UTM zone 50N",
        "+proj=utm +zone=50 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32451, "epsg", 32451, "WGS 72BE / UTM zone 51N",
        "+proj=utm +zone=51 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32452, "epsg", 32452, "WGS 72BE / UTM zone 52N",
        "+proj=utm +zone=52 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32453, "epsg", 32453, "WGS 72BE / UTM zone 53N",
        "+proj=utm +zone=53 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32454, "epsg", 32454, "WGS 72BE / UTM zone 54N",
        "+proj=utm +zone=54 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32455, "epsg", 32455, "WGS 72BE / UTM zone 55N",
        "+proj=utm +zone=55 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32456, "epsg", 32456, "WGS 72BE / UTM zone 56N",
        "+proj=utm +zone=56 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32457, "epsg", 32457, "WGS 72BE / UTM zone 57N",
        "+proj=utm +zone=57 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32458, "epsg", 32458, "WGS 72BE / UTM zone 58N",
        "+proj=utm +zone=58 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32459, "epsg", 32459, "WGS 72BE / UTM zone 59N",
        "+proj=utm +zone=59 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32460, "epsg", 32460, "WGS 72BE / UTM zone 60N",
        "+proj=utm +zone=60 +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32501, "epsg", 32501, "WGS 72BE / UTM zone 1S",
        "+proj=utm +zone=1 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32502, "epsg", 32502, "WGS 72BE / UTM zone 2S",
        "+proj=utm +zone=2 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32503, "epsg", 32503, "WGS 72BE / UTM zone 3S",
        "+proj=utm +zone=3 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32504, "epsg", 32504, "WGS 72BE / UTM zone 4S",
        "+proj=utm +zone=4 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32505, "epsg", 32505, "WGS 72BE / UTM zone 5S",
        "+proj=utm +zone=5 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32506, "epsg", 32506, "WGS 72BE / UTM zone 6S",
        "+proj=utm +zone=6 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32507, "epsg", 32507, "WGS 72BE / UTM zone 7S",
        "+proj=utm +zone=7 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32508, "epsg", 32508, "WGS 72BE / UTM zone 8S",
        "+proj=utm +zone=8 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32509, "epsg", 32509, "WGS 72BE / UTM zone 9S",
        "+proj=utm +zone=9 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32510, "epsg", 32510, "WGS 72BE / UTM zone 10S",
        "+proj=utm +zone=10 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32511, "epsg", 32511, "WGS 72BE / UTM zone 11S",
        "+proj=utm +zone=11 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32512, "epsg", 32512, "WGS 72BE / UTM zone 12S",
        "+proj=utm +zone=12 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32513, "epsg", 32513, "WGS 72BE / UTM zone 13S",
        "+proj=utm +zone=13 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32514, "epsg", 32514, "WGS 72BE / UTM zone 14S",
        "+proj=utm +zone=14 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32515, "epsg", 32515, "WGS 72BE / UTM zone 15S",
        "+proj=utm +zone=15 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32516, "epsg", 32516, "WGS 72BE / UTM zone 16S",
        "+proj=utm +zone=16 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32517, "epsg", 32517, "WGS 72BE / UTM zone 17S",
        "+proj=utm +zone=17 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32518, "epsg", 32518, "WGS 72BE / UTM zone 18S",
        "+proj=utm +zone=18 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32519, "epsg", 32519, "WGS 72BE / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32520, "epsg", 32520, "WGS 72BE / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32521, "epsg", 32521, "WGS 72BE / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32522, "epsg", 32522, "WGS 72BE / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32523, "epsg", 32523, "WGS 72BE / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32524, "epsg", 32524, "WGS 72BE / UTM zone 24S",
        "+proj=utm +zone=24 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32525, "epsg", 32525, "WGS 72BE / UTM zone 25S",
        "+proj=utm +zone=25 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32526, "epsg", 32526, "WGS 72BE / UTM zone 26S",
        "+proj=utm +zone=26 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32527, "epsg", 32527, "WGS 72BE / UTM zone 27S",
        "+proj=utm +zone=27 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32528, "epsg", 32528, "WGS 72BE / UTM zone 28S",
        "+proj=utm +zone=28 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32529, "epsg", 32529, "WGS 72BE / UTM zone 29S",
        "+proj=utm +zone=29 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32530, "epsg", 32530, "WGS 72BE / UTM zone 30S",
        "+proj=utm +zone=30 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32531, "epsg", 32531, "WGS 72BE / UTM zone 31S",
        "+proj=utm +zone=31 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32532, "epsg", 32532, "WGS 72BE / UTM zone 32S",
        "+proj=utm +zone=32 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32533, "epsg", 32533, "WGS 72BE / UTM zone 33S",
        "+proj=utm +zone=33 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32534, "epsg", 32534, "WGS 72BE / UTM zone 34S",
        "+proj=utm +zone=34 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32535, "epsg", 32535, "WGS 72BE / UTM zone 35S",
        "+proj=utm +zone=35 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32536, "epsg", 32536, "WGS 72BE / UTM zone 36S",
        "+proj=utm +zone=36 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32537, "epsg", 32537, "WGS 72BE / UTM zone 37S",
        "+proj=utm +zone=37 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32538, "epsg", 32538, "WGS 72BE / UTM zone 38S",
        "+proj=utm +zone=38 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32539, "epsg", 32539, "WGS 72BE / UTM zone 39S",
        "+proj=utm +zone=39 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32540, "epsg", 32540, "WGS 72BE / UTM zone 40S",
        "+proj=utm +zone=40 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32541, "epsg", 32541, "WGS 72BE / UTM zone 41S",
        "+proj=utm +zone=41 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32542, "epsg", 32542, "WGS 72BE / UTM zone 42S",
        "+proj=utm +zone=42 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32543, "epsg", 32543, "WGS 72BE / UTM zone 43S",
        "+proj=utm +zone=43 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32544, "epsg", 32544, "WGS 72BE / UTM zone 44S",
        "+proj=utm +zone=44 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32545, "epsg", 32545, "WGS 72BE / UTM zone 45S",
        "+proj=utm +zone=45 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32546, "epsg", 32546, "WGS 72BE / UTM zone 46S",
        "+proj=utm +zone=46 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32547, "epsg", 32547, "WGS 72BE / UTM zone 47S",
        "+proj=utm +zone=47 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32548, "epsg", 32548, "WGS 72BE / UTM zone 48S",
        "+proj=utm +zone=48 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32549, "epsg", 32549, "WGS 72BE / UTM zone 49S",
        "+proj=utm +zone=49 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32550, "epsg", 32550, "WGS 72BE / UTM zone 50S",
        "+proj=utm +zone=50 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32551, "epsg", 32551, "WGS 72BE / UTM zone 51S",
        "+proj=utm +zone=51 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32552, "epsg", 32552, "WGS 72BE / UTM zone 52S",
        "+proj=utm +zone=52 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32553, "epsg", 32553, "WGS 72BE / UTM zone 53S",
        "+proj=utm +zone=53 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32554, "epsg", 32554, "WGS 72BE / UTM zone 54S",
        "+proj=utm +zone=54 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32555, "epsg", 32555, "WGS 72BE / UTM zone 55S",
        "+proj=utm +zone=55 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32556, "epsg", 32556, "WGS 72BE / UTM zone 56S",
        "+proj=utm +zone=56 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32557, "epsg", 32557, "WGS 72BE / UTM zone 57S",
        "+proj=utm +zone=57 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32558, "epsg", 32558, "WGS 72BE / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32559, "epsg", 32559, "WGS 72BE / UTM zone 59S",
        "+proj=utm +zone=59 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32560, "epsg", 32560, "WGS 72BE / UTM zone 60S",
        "+proj=utm +zone=60 +south +ellps=WGS72 +towgs84=0,0,1.9,0,0,0.814,-0.38 +units=m +no_defs"},
    {
    32601, "epsg", 32601, "WGS 84 / UTM zone 1N",
        "+proj=utm +zone=1 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32602, "epsg", 32602, "WGS 84 / UTM zone 2N",
        "+proj=utm +zone=2 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32603, "epsg", 32603, "WGS 84 / UTM zone 3N",
        "+proj=utm +zone=3 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32604, "epsg", 32604, "WGS 84 / UTM zone 4N",
        "+proj=utm +zone=4 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32605, "epsg", 32605, "WGS 84 / UTM zone 5N",
        "+proj=utm +zone=5 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32606, "epsg", 32606, "WGS 84 / UTM zone 6N",
        "+proj=utm +zone=6 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32607, "epsg", 32607, "WGS 84 / UTM zone 7N",
        "+proj=utm +zone=7 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32608, "epsg", 32608, "WGS 84 / UTM zone 8N",
        "+proj=utm +zone=8 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32609, "epsg", 32609, "WGS 84 / UTM zone 9N",
        "+proj=utm +zone=9 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32610, "epsg", 32610, "WGS 84 / UTM zone 10N",
        "+proj=utm +zone=10 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32611, "epsg", 32611, "WGS 84 / UTM zone 11N",
        "+proj=utm +zone=11 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32612, "epsg", 32612, "WGS 84 / UTM zone 12N",
        "+proj=utm +zone=12 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32613, "epsg", 32613, "WGS 84 / UTM zone 13N",
        "+proj=utm +zone=13 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32614, "epsg", 32614, "WGS 84 / UTM zone 14N",
        "+proj=utm +zone=14 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32615, "epsg", 32615, "WGS 84 / UTM zone 15N",
        "+proj=utm +zone=15 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32616, "epsg", 32616, "WGS 84 / UTM zone 16N",
        "+proj=utm +zone=16 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32617, "epsg", 32617, "WGS 84 / UTM zone 17N",
        "+proj=utm +zone=17 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32618, "epsg", 32618, "WGS 84 / UTM zone 18N",
        "+proj=utm +zone=18 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32619, "epsg", 32619, "WGS 84 / UTM zone 19N",
        "+proj=utm +zone=19 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32620, "epsg", 32620, "WGS 84 / UTM zone 20N",
        "+proj=utm +zone=20 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32621, "epsg", 32621, "WGS 84 / UTM zone 21N",
        "+proj=utm +zone=21 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32622, "epsg", 32622, "WGS 84 / UTM zone 22N",
        "+proj=utm +zone=22 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32623, "epsg", 32623, "WGS 84 / UTM zone 23N",
        "+proj=utm +zone=23 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32624, "epsg", 32624, "WGS 84 / UTM zone 24N",
        "+proj=utm +zone=24 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32625, "epsg", 32625, "WGS 84 / UTM zone 25N",
        "+proj=utm +zone=25 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32626, "epsg", 32626, "WGS 84 / UTM zone 26N",
        "+proj=utm +zone=26 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32627, "epsg", 32627, "WGS 84 / UTM zone 27N",
        "+proj=utm +zone=27 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32628, "epsg", 32628, "WGS 84 / UTM zone 28N",
        "+proj=utm +zone=28 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32629, "epsg", 32629, "WGS 84 / UTM zone 29N",
        "+proj=utm +zone=29 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32630, "epsg", 32630, "WGS 84 / UTM zone 30N",
        "+proj=utm +zone=30 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32631, "epsg", 32631, "WGS 84 / UTM zone 31N",
        "+proj=utm +zone=31 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32632, "epsg", 32632, "WGS 84 / UTM zone 32N",
        "+proj=utm +zone=32 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32633, "epsg", 32633, "WGS 84 / UTM zone 33N",
        "+proj=utm +zone=33 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32634, "epsg", 32634, "WGS 84 / UTM zone 34N",
        "+proj=utm +zone=34 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32635, "epsg", 32635, "WGS 84 / UTM zone 35N",
        "+proj=utm +zone=35 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32636, "epsg", 32636, "WGS 84 / UTM zone 36N",
        "+proj=utm +zone=36 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32637, "epsg", 32637, "WGS 84 / UTM zone 37N",
        "+proj=utm +zone=37 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32638, "epsg", 32638, "WGS 84 / UTM zone 38N",
        "+proj=utm +zone=38 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32639, "epsg", 32639, "WGS 84 / UTM zone 39N",
        "+proj=utm +zone=39 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32640, "epsg", 32640, "WGS 84 / UTM zone 40N",
        "+proj=utm +zone=40 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32641, "epsg", 32641, "WGS 84 / UTM zone 41N",
        "+proj=utm +zone=41 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32642, "epsg", 32642, "WGS 84 / UTM zone 42N",
        "+proj=utm +zone=42 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32643, "epsg", 32643, "WGS 84 / UTM zone 43N",
        "+proj=utm +zone=43 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32644, "epsg", 32644, "WGS 84 / UTM zone 44N",
        "+proj=utm +zone=44 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32645, "epsg", 32645, "WGS 84 / UTM zone 45N",
        "+proj=utm +zone=45 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32646, "epsg", 32646, "WGS 84 / UTM zone 46N",
        "+proj=utm +zone=46 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32647, "epsg", 32647, "WGS 84 / UTM zone 47N",
        "+proj=utm +zone=47 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32648, "epsg", 32648, "WGS 84 / UTM zone 48N",
        "+proj=utm +zone=48 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32649, "epsg", 32649, "WGS 84 / UTM zone 49N",
        "+proj=utm +zone=49 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32650, "epsg", 32650, "WGS 84 / UTM zone 50N",
        "+proj=utm +zone=50 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32651, "epsg", 32651, "WGS 84 / UTM zone 51N",
        "+proj=utm +zone=51 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32652, "epsg", 32652, "WGS 84 / UTM zone 52N",
        "+proj=utm +zone=52 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32653, "epsg", 32653, "WGS 84 / UTM zone 53N",
        "+proj=utm +zone=53 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32654, "epsg", 32654, "WGS 84 / UTM zone 54N",
        "+proj=utm +zone=54 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32655, "epsg", 32655, "WGS 84 / UTM zone 55N",
        "+proj=utm +zone=55 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32656, "epsg", 32656, "WGS 84 / UTM zone 56N",
        "+proj=utm +zone=56 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32657, "epsg", 32657, "WGS 84 / UTM zone 57N",
        "+proj=utm +zone=57 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32658, "epsg", 32658, "WGS 84 / UTM zone 58N",
        "+proj=utm +zone=58 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32659, "epsg", 32659, "WGS 84 / UTM zone 59N",
        "+proj=utm +zone=59 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32660, "epsg", 32660, "WGS 84 / UTM zone 60N",
        "+proj=utm +zone=60 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32661, "epsg", 32661, "WGS 84 / UPS North",
        "+proj=stere +lat_0=90 +lat_ts=90 +lon_0=0 +k=0.994 +x_0=2000000 +y_0=2000000 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32662, "epsg", 32662, "WGS 84 / Plate Carree (deprecated)",
        "+proj=eqc +lat_ts=0 +lat_0=0 +lon_0=0 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32664, "epsg", 32664, "WGS 84 / BLM 14N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-99 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=us-ft +no_defs"},
    {
    32665, "epsg", 32665, "WGS 84 / BLM 15N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-93 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=us-ft +no_defs"},
    {
    32666, "epsg", 32666, "WGS 84 / BLM 16N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-87 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=us-ft +no_defs"},
    {
    32667, "epsg", 32667, "WGS 84 / BLM 17N (ftUS)",
        "+proj=tmerc +lat_0=0 +lon_0=-81 +k=0.9996 +x_0=500000.001016002 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=us-ft +no_defs"},
    {
    32701, "epsg", 32701, "WGS 84 / UTM zone 1S",
        "+proj=utm +zone=1 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32702, "epsg", 32702, "WGS 84 / UTM zone 2S",
        "+proj=utm +zone=2 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32703, "epsg", 32703, "WGS 84 / UTM zone 3S",
        "+proj=utm +zone=3 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32704, "epsg", 32704, "WGS 84 / UTM zone 4S",
        "+proj=utm +zone=4 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32705, "epsg", 32705, "WGS 84 / UTM zone 5S",
        "+proj=utm +zone=5 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32706, "epsg", 32706, "WGS 84 / UTM zone 6S",
        "+proj=utm +zone=6 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32707, "epsg", 32707, "WGS 84 / UTM zone 7S",
        "+proj=utm +zone=7 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32708, "epsg", 32708, "WGS 84 / UTM zone 8S",
        "+proj=utm +zone=8 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32709, "epsg", 32709, "WGS 84 / UTM zone 9S",
        "+proj=utm +zone=9 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32710, "epsg", 32710, "WGS 84 / UTM zone 10S",
        "+proj=utm +zone=10 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32711, "epsg", 32711, "WGS 84 / UTM zone 11S",
        "+proj=utm +zone=11 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32712, "epsg", 32712, "WGS 84 / UTM zone 12S",
        "+proj=utm +zone=12 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32713, "epsg", 32713, "WGS 84 / UTM zone 13S",
        "+proj=utm +zone=13 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32714, "epsg", 32714, "WGS 84 / UTM zone 14S",
        "+proj=utm +zone=14 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32715, "epsg", 32715, "WGS 84 / UTM zone 15S",
        "+proj=utm +zone=15 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32716, "epsg", 32716, "WGS 84 / UTM zone 16S",
        "+proj=utm +zone=16 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32717, "epsg", 32717, "WGS 84 / UTM zone 17S",
        "+proj=utm +zone=17 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32718, "epsg", 32718, "WGS 84 / UTM zone 18S",
        "+proj=utm +zone=18 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32719, "epsg", 32719, "WGS 84 / UTM zone 19S",
        "+proj=utm +zone=19 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32720, "epsg", 32720, "WGS 84 / UTM zone 20S",
        "+proj=utm +zone=20 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32721, "epsg", 32721, "WGS 84 / UTM zone 21S",
        "+proj=utm +zone=21 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32722, "epsg", 32722, "WGS 84 / UTM zone 22S",
        "+proj=utm +zone=22 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32723, "epsg", 32723, "WGS 84 / UTM zone 23S",
        "+proj=utm +zone=23 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32724, "epsg", 32724, "WGS 84 / UTM zone 24S",
        "+proj=utm +zone=24 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32725, "epsg", 32725, "WGS 84 / UTM zone 25S",
        "+proj=utm +zone=25 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32726, "epsg", 32726, "WGS 84 / UTM zone 26S",
        "+proj=utm +zone=26 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32727, "epsg", 32727, "WGS 84 / UTM zone 27S",
        "+proj=utm +zone=27 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32728, "epsg", 32728, "WGS 84 / UTM zone 28S",
        "+proj=utm +zone=28 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32729, "epsg", 32729, "WGS 84 / UTM zone 29S",
        "+proj=utm +zone=29 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32730, "epsg", 32730, "WGS 84 / UTM zone 30S",
        "+proj=utm +zone=30 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32731, "epsg", 32731, "WGS 84 / UTM zone 31S",
        "+proj=utm +zone=31 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32732, "epsg", 32732, "WGS 84 / UTM zone 32S",
        "+proj=utm +zone=32 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32733, "epsg", 32733, "WGS 84 / UTM zone 33S",
        "+proj=utm +zone=33 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32734, "epsg", 32734, "WGS 84 / UTM zone 34S",
        "+proj=utm +zone=34 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32735, "epsg", 32735, "WGS 84 / UTM zone 35S",
        "+proj=utm +zone=35 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32736, "epsg", 32736, "WGS 84 / UTM zone 36S",
        "+proj=utm +zone=36 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32737, "epsg", 32737, "WGS 84 / UTM zone 37S",
        "+proj=utm +zone=37 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32738, "epsg", 32738, "WGS 84 / UTM zone 38S",
        "+proj=utm +zone=38 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32739, "epsg", 32739, "WGS 84 / UTM zone 39S",
        "+proj=utm +zone=39 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32740, "epsg", 32740, "WGS 84 / UTM zone 40S",
        "+proj=utm +zone=40 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32741, "epsg", 32741, "WGS 84 / UTM zone 41S",
        "+proj=utm +zone=41 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32742, "epsg", 32742, "WGS 84 / UTM zone 42S",
        "+proj=utm +zone=42 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32743, "epsg", 32743, "WGS 84 / UTM zone 43S",
        "+proj=utm +zone=43 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32744, "epsg", 32744, "WGS 84 / UTM zone 44S",
        "+proj=utm +zone=44 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32745, "epsg", 32745, "WGS 84 / UTM zone 45S",
        "+proj=utm +zone=45 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32746, "epsg", 32746, "WGS 84 / UTM zone 46S",
        "+proj=utm +zone=46 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32747, "epsg", 32747, "WGS 84 / UTM zone 47S",
        "+proj=utm +zone=47 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32748, "epsg", 32748, "WGS 84 / UTM zone 48S",
        "+proj=utm +zone=48 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32749, "epsg", 32749, "WGS 84 / UTM zone 49S",
        "+proj=utm +zone=49 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32750, "epsg", 32750, "WGS 84 / UTM zone 50S",
        "+proj=utm +zone=50 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32751, "epsg", 32751, "WGS 84 / UTM zone 51S",
        "+proj=utm +zone=51 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32752, "epsg", 32752, "WGS 84 / UTM zone 52S",
        "+proj=utm +zone=52 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32753, "epsg", 32753, "WGS 84 / UTM zone 53S",
        "+proj=utm +zone=53 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32754, "epsg", 32754, "WGS 84 / UTM zone 54S",
        "+proj=utm +zone=54 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32755, "epsg", 32755, "WGS 84 / UTM zone 55S",
        "+proj=utm +zone=55 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32756, "epsg", 32756, "WGS 84 / UTM zone 56S",
        "+proj=utm +zone=56 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32757, "epsg", 32757, "WGS 84 / UTM zone 57S",
        "+proj=utm +zone=57 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32758, "epsg", 32758, "WGS 84 / UTM zone 58S",
        "+proj=utm +zone=58 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32759, "epsg", 32759, "WGS 84 / UTM zone 59S",
        "+proj=utm +zone=59 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32760, "epsg", 32760, "WGS 84 / UTM zone 60S",
        "+proj=utm +zone=60 +south +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32761, "epsg", 32761, "WGS 84 / UPS South",
        "+proj=stere +lat_0=-90 +lat_ts=-90 +lon_0=0 +k=0.994 +x_0=2000000 +y_0=2000000 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
    32766, "epsg", 32766, "WGS 84 / TM 36 SE",
        "+proj=tmerc +lat_0=0 +lon_0=36 +k=0.9996 +x_0=500000 +y_0=10000000 +ellps=WGS84 +datum=WGS84 +units=m +no_defs"},
    {
  -1, NULL, -1, NULL, NULL}};
  struct epsg_defs *p = epsg;
  char sql[1024];
  char *errMsg = NULL;
  int ret;
  sqlite3_stmt *stmt;
  ::wxBeginBusyCursor();
//
// starting a transaction
//
  ret = sqlite3_exec(SqliteHandle, "BEGIN", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("CreateSpatialMetaData error: ") +
                   wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto error;
    }
// creating the Spatial Metadata Tables
  strcpy(sql, "SELECT InitSpatialMetaData()");
  ret = sqlite3_exec(SqliteHandle, sql, NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("CreateSpatialMetaData error: ") +
                   wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto error;
    }
// preparing the SQL parameterized statement
  strcpy(sql, "INSERT INTO spatial_ref_sys ");
  strcat(sql, "(srid, auth_name, auth_srid, ref_sys_name, proj4text) ");
  strcat(sql, "VALUES (?, ?, ?, ?, ?)");
  ret = sqlite3_prepare_v2(SqliteHandle, sql, strlen(sql), &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("CreateSpatialMetaData error: ") + err,
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      goto error;
    }
  while (1)
    {
      if (p->srid < 0 || p->auth_name == NULL)
        break;
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      sqlite3_bind_int(stmt, 1, p->srid);
      sqlite3_bind_text(stmt, 2, p->auth_name, strlen(p->auth_name),
                        SQLITE_STATIC);
      sqlite3_bind_int(stmt, 3, p->auth_srid);
      sqlite3_bind_text(stmt, 4, p->ref_sys_name, strlen(p->ref_sys_name),
                        SQLITE_STATIC);
      sqlite3_bind_text(stmt, 5, p->proj4text, strlen(p->proj4text),
                        SQLITE_STATIC);
      ret = sqlite3_step(stmt);
      if (ret == SQLITE_DONE || ret == SQLITE_ROW)
        ;
      else
        {
          wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
          wxMessageBox(wxT("CreateSpatialMetaData error: ") + err,
                       wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
          sqlite3_finalize(stmt);
          goto error;
        }
      p++;
    }
  sqlite3_finalize(stmt);
//
// confirming the transaction
//
  ret = sqlite3_exec(SqliteHandle, "COMMIT", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("CreateSpatialMetaData error: ") +
                   wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto error;
    }
  ::wxEndBusyCursor();
  return true;
error:
//
// trying to perform a ROLLBACK anyway
//
  ret = sqlite3_exec(SqliteHandle, "ROLLBACK", NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("CreateSpatialMetaData error: ") +
                   wxString::FromUTF8(errMsg), wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto error;
    }
  ::wxEndBusyCursor();
  return false;
}

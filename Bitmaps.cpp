/*
/ Bitmaps.cpp
/ mothods related to 'bitmaps' tables
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

//
// ICONs in XPM format [universally portable]
//
#include "symbols/small_point.xpm"
#include "symbols/medium_point.xpm"
#include "symbols/large_point.xpm"
#include "symbols/huge_point.xpm"
#include "symbols/small_square.xpm"
#include "symbols/medium_square.xpm"
#include "symbols/large_square.xpm"
#include "symbols/huge_square.xpm"
#include "symbols/square_diamond.xpm"
#include "symbols/small_diamond.xpm"
#include "symbols/medium_diamond.xpm"
#include "symbols/large_diamond.xpm"
#include "symbols/small_cross.xpm"
#include "symbols/medium_cross.xpm"
#include "symbols/large_cross.xpm"
#include "symbols/huge_cross.xpm"
#include "symbols/small_andrew.xpm"
#include "symbols/medium_andrew.xpm"
#include "symbols/large_andrew.xpm"
#include "symbols/huge_andrew.xpm"
#include "symbols/small_tri_up.xpm"
#include "symbols/medium_tri_up.xpm"
#include "symbols/large_tri_up.xpm"
#include "symbols/huge_tri_up.xpm"
#include "symbols/small_tri_down.xpm"
#include "symbols/medium_tri_down.xpm"
#include "symbols/large_tri_down.xpm"
#include "symbols/huge_tri_down.xpm"
#include "symbols/small_tri_left.xpm"
#include "symbols/medium_tri_left.xpm"
#include "symbols/large_tri_left.xpm"
#include "symbols/huge_tri_left.xpm"
#include "symbols/small_tri_right.xpm"
#include "symbols/medium_tri_right.xpm"
#include "symbols/large_tri_right.xpm"
#include "symbols/huge_tri_right.xpm"
#include "symbols/small_arrow_up.xpm"
#include "symbols/large_arrow_up.xpm"
#include "symbols/small_arrow_down.xpm"
#include "symbols/large_arrow_down.xpm"
#include "symbols/small_arrow_left.xpm"
#include "symbols/large_arrow_left.xpm"
#include "symbols/small_arrow_right.xpm"
#include "symbols/large_arrow_right.xpm"
#include "symbols/small_arrow_up_left.xpm"
#include "symbols/large_arrow_up_left.xpm"
#include "symbols/small_arrow_up_right.xpm"
#include "symbols/large_arrow_up_right.xpm"
#include "symbols/small_arrow_down_left.xpm"
#include "symbols/large_arrow_down_left.xpm"
#include "symbols/small_arrow_down_right.xpm"
#include "symbols/large_arrow_down_right.xpm"
#include "color_symbols/white_flag.xpm"
#include "color_symbols/yellow_flag.xpm"
#include "color_symbols/red_flag.xpm"
#include "color_symbols/green_flag.xpm"
#include "color_symbols/blue_flag.xpm"
#include "color_symbols/flag_blue.xpm"
#include "color_symbols/flag_green.xpm"
#include "color_symbols/flag_orange.xpm"
#include "color_symbols/flag_pink.xpm"
#include "color_symbols/flag_purple.xpm"
#include "color_symbols/flag_red.xpm"
#include "color_symbols/flag_yellow.xpm"
#include "color_symbols/bullet_add.xpm"
#include "color_symbols/bullet_delete.xpm"
#include "color_symbols/bullet_star.xpm"
#include "color_symbols/bullet_picture.xpm"
#include "color_symbols/bullet_error.xpm"
#include "color_symbols/bullet_arrow_up.xpm"
#include "color_symbols/bullet_arrow_down.xpm"
#include "color_symbols/bullet_black.xpm"
#include "color_symbols/bullet_white.xpm"
#include "color_symbols/bullet_yellow.xpm"
#include "color_symbols/bullet_orange.xpm"
#include "color_symbols/bullet_pink.xpm"
#include "color_symbols/bullet_red.xpm"
#include "color_symbols/bullet_green.xpm"
#include "color_symbols/bullet_blue.xpm"
#include "color_symbols/asterisk_yellow.xpm"
#include "color_symbols/accept.xpm"
#include "color_symbols/add.xpm"
#include "color_symbols/delete.xpm"
#include "color_symbols/exclamation.xpm"
#include "color_symbols/information1.xpm"
#include "color_symbols/help.xpm"
#include "color_symbols/action_stop.xpm"
#include "color_symbols/icon_accept.xpm"
#include "color_symbols/icon_alert.xpm"
#include "color_symbols/icon_info.xpm"
#include "color_symbols/time.xpm"
#include "color_symbols/icon_clock.xpm"
#include "color_symbols/money1.xpm"
#include "color_symbols/money_dollar.xpm"
#include "color_symbols/money_euro.xpm"
#include "color_symbols/icon_email.xpm"
#include "color_symbols/email.xpm"
#include "color_symbols/icon_home.xpm"
#include "color_symbols/house.xpm"
#include "color_symbols/icon_key.xpm"
#include "color_symbols/icon_security.xpm"
#include "color_symbols/icon_user.xpm"
#include "color_symbols/icon_world.xpm"
#include "color_symbols/camera.xpm"
#include "color_symbols/camera_small.xpm"
#include "color_symbols/photo.xpm"
#include "color_symbols/photos.xpm"
#include "color_symbols/picture.xpm"
#include "color_symbols/picture_empty.xpm"
#include "color_symbols/pictures.xpm"
#include "color_symbols/chart_bar.xpm"
#include "color_symbols/color_wheel.xpm"
#include "color_symbols/rainbow.xpm"
#include "color_symbols/palette.xpm"
#include "color_symbols/rosette.xpm"
#include "color_symbols/music.xpm"
#include "color_symbols/male.xpm"
#include "color_symbols/female.xpm"
#include "color_symbols/drink.xpm"
#include "color_symbols/drink_empty.xpm"
#include "color_symbols/bell.xpm"
#include "color_symbols/book_open.xpm"
#include "color_symbols/brick.xpm"
#include "color_symbols/cog.xpm"
#include "color_symbols/heart.xpm"
#include "color_symbols/cart.xpm"
#include "color_symbols/new.xpm"
#include "osm_symbols/camping.xpm"
#include "osm_symbols/guest_house.xpm"
#include "osm_symbols/hostel.xpm"
#include "osm_symbols/hotel.xpm"
#include "osm_symbols/caravan.xpm"
#include "osm_symbols/trash.xpm"
#include "osm_symbols/hospital.xpm"
#include "osm_symbols/pharmacy.xpm"
#include "osm_symbols/crane.xpm"
#include "osm_symbols/lighthouse.xpm"
#include "osm_symbols/mine.xpm"
#include "osm_symbols/plant.xpm"
#include "osm_symbols/trees.xpm"
#include "osm_symbols/works.xpm"
#include "osm_symbols/emergency.xpm"
#include "osm_symbols/danger.xpm"
#include "osm_symbols/information.xpm"
#include "osm_symbols/proposed.xpm"
#include "osm_symbols/tap_drinking.xpm"
#include "osm_symbols/exchange.xpm"
#include "osm_symbols/anchor.xpm"
#include "osm_symbols/island.xpm"
#include "osm_symbols/firebrigade.xpm"
#include "osm_symbols/post_box.xpm"
#include "osm_symbols/recycling.xpm"
#include "osm_symbols/telephone.xpm"
#include "osm_symbols/toilets.xpm"
#include "osm_symbols/bicycling.xpm"
#include "osm_symbols/garden.xpm"
#include "osm_symbols/park.xpm"
#include "osm_symbols/picnic.xpm"
#include "osm_symbols/theater.xpm"
#include "osm_symbols/zoo.xpm"
#include "osm_symbols/castle.xpm"
#include "osm_symbols/museum.xpm"
#include "osm_symbols/viewpoint.xpm"
#include "osm_symbols/helipad.xpm"
#include "osm_symbols/airport.xpm"
#include "osm_symbols/bus.xpm"
#include "osm_symbols/car.xpm"
#include "osm_symbols/handicapped.xpm"
#include "osm_symbols/pedestrian.xpm"
#include "osm_symbols/railway.xpm"
#include "osm_symbols/park_car.xpm"
#include "osm_symbols/garage.xpm"
#include "osm_symbols/emergency_phone.xpm"
#include "osm_symbols/fuel_station.xpm"
#include "osm_symbols/motorbike.xpm"
#include "osm_symbols/parking.xpm"
#include "osm_symbols/repair_shop.xpm"
#include "osm_symbols/restrictions.xpm"
#include "osm_symbols/incline.xpm"
#include "osm_symbols/parking2.xpm"
#include "osm_symbols/motorbike2.xpm"
#include "osm_symbols/right_of_way.xpm"
#include "osm_symbols/road_works.xpm"
#include "osm_symbols/roundabout_left.xpm"
#include "osm_symbols/roundabout_right.xpm"
#include "osm_symbols/stop.xpm"
#include "osm_symbols/traffic_jam.xpm"
#include "osm_symbols/traffic_light.xpm"
#include "osm_symbols/health.xpm"
#include "osm_symbols/money.xpm"
#include "osm_symbols/nautical.xpm"
#include "osm_symbols/people.xpm"
#include "osm_symbols/shopping.xpm"
#include "osm_symbols/sports.xpm"
#include "osm_symbols/vehicle.xpm"
#include "osm_symbols/wpttemp.xpm"
#include "osm_symbols/wpttemp_green.xpm"
#include "osm_symbols/wpttemp_red.xpm"
#include "osm_symbols/wpttemp_yellow.xpm"
#include "color_symbols/tux.xpm"
#include "patterns/dense1.xpm"
#include "patterns/dense2.xpm"
#include "patterns/dense3.xpm"
#include "patterns/dense4.xpm"
#include "patterns/dense5.xpm"
#include "patterns/dense6.xpm"
#include "patterns/dots1.xpm"
#include "patterns/dots2.xpm"
#include "patterns/dots3.xpm"
#include "patterns/dots5.xpm"
#include "patterns/dots6.xpm"
#include "patterns/brickwall.xpm"
#include "patterns/horz0.xpm"
#include "patterns/horz01.xpm"
#include "patterns/horz1.xpm"
#include "patterns/horz2.xpm"
#include "patterns/vert0.xpm"
#include "patterns/vert01.xpm"
#include "patterns/vert1.xpm"
#include "patterns/vert2.xpm"
#include "patterns/diag1_0.xpm"
#include "patterns/diag1_01.xpm"
#include "patterns/diag1_1.xpm"
#include "patterns/diag1_2.xpm"
#include "patterns/diag2_0.xpm"
#include "patterns/diag2_01.xpm"
#include "patterns/diag2_1.xpm"
#include "patterns/diag2_2.xpm"
#include "patterns/cross0.xpm"
#include "patterns/cross01.xpm"
#include "patterns/cross1.xpm"
#include "patterns/cross2.xpm"
#include "patterns/diag_cross_0.xpm"
#include "patterns/diag_cross_01.xpm"
#include "patterns/diag_cross_1.xpm"
#include "patterns/diag_cross_2.xpm"
#include "patterns/sea1.xpm"
#include "patterns/sea2.xpm"
#include "patterns/sea3.xpm"
#include "patterns/land1.xpm"
#include "patterns/land2.xpm"
#include "patterns/land3.xpm"
#include "patterns/land4.xpm"
#include "patterns/land5.xpm"
#include "patterns/land6.xpm"
#include "patterns/land7.xpm"
#include "patterns/land8.xpm"
#include "patterns/land9.xpm"
#include "patterns/land10.xpm"

bool MyFrame::CreateSymbolBitmaps()
{
//
// creating and initializing the 'symbol_bitmaps' table 
//
  int ret;
  char *errMsg = NULL;
  wxString sql;
  sqlite3_stmt *stmt;
  int ind;
  int row;
  int col;
  int blob_size;
  unsigned char *blob;
  unsigned char *p_blob;
  int full_color[200];
  wxImage images[200];
  int hot_x[200];
  int hot_y[200];

  for (ind = 0; ind < 200; ind++)
    {
      // standard settings
      if (ind <= 51)
        full_color[ind] = 0;
      else
        full_color[ind] = 1;
      hot_x[ind] = 8;
      hot_y[ind] = 8;
    }

  images[0] = wxImage(small_point_xpm);
  images[1] = wxImage(medium_point_xpm);
  images[2] = wxImage(large_point_xpm);
  images[3] = wxImage(huge_point_xpm);
  images[4] = wxImage(small_square_xpm);
  images[5] = wxImage(medium_square_xpm);
  images[6] = wxImage(large_square_xpm);
  images[7] = wxImage(huge_square_xpm);
  images[8] = wxImage(square_diamond_xpm);
  images[9] = wxImage(small_diamond_xpm);
  hot_x[9] = 7;
  hot_y[9] = 7;
  images[10] = wxImage(medium_diamond_xpm);
  images[11] = wxImage(large_diamond_xpm);
  images[12] = wxImage(small_cross_xpm);
  hot_x[12] = 7;
  hot_y[12] = 7;
  images[13] = wxImage(medium_cross_xpm);
  images[14] = wxImage(large_cross_xpm);
  images[15] = wxImage(huge_cross_xpm);
  images[16] = wxImage(small_andrew_xpm);
  images[17] = wxImage(medium_andrew_xpm);
  images[18] = wxImage(large_andrew_xpm);
  images[19] = wxImage(huge_andrew_xpm);
  images[20] = wxImage(small_tri_up_xpm);
  hot_y[20] = 9;
  images[21] = wxImage(medium_tri_up_xpm);
  hot_y[21] = 9;
  images[22] = wxImage(large_tri_up_xpm);
  hot_y[22] = 9;
  images[23] = wxImage(huge_tri_up_xpm);
  hot_y[23] = 9;
  images[24] = wxImage(small_tri_down_xpm);
  hot_y[24] = 6;
  images[25] = wxImage(medium_tri_down_xpm);
  hot_y[25] = 6;
  images[26] = wxImage(large_tri_down_xpm);
  hot_y[26] = 6;
  images[27] = wxImage(huge_tri_down_xpm);
  hot_y[27] = 6;
  images[28] = wxImage(small_tri_left_xpm);
  hot_x[28] = 9;
  hot_y[28] = 9;
  images[29] = wxImage(medium_tri_left_xpm);
  hot_x[29] = 9;
  images[30] = wxImage(large_tri_left_xpm);
  hot_x[30] = 10;
  images[31] = wxImage(huge_tri_left_xpm);
  hot_x[31] = 11;
  images[32] = wxImage(small_tri_right_xpm);
  hot_x[32] = 7;
  images[33] = wxImage(medium_tri_right_xpm);
  hot_x[33] = 6;
  images[34] = wxImage(large_tri_right_xpm);
  hot_x[34] = 5;
  images[35] = wxImage(huge_tri_right_xpm);
  hot_x[35] = 4;
  images[36] = wxImage(small_arrow_up_xpm);
  hot_y[36] = 4;
  images[37] = wxImage(large_arrow_up_xpm);
  hot_y[37] = 2;
  images[38] = wxImage(small_arrow_down_xpm);
  hot_y[38] = 13;
  images[39] = wxImage(large_arrow_down_xpm);
  hot_y[39] = 15;
  images[40] = wxImage(small_arrow_left_xpm);
  hot_x[40] = 4;
  hot_y[40] = 9;
  images[41] = wxImage(large_arrow_left_xpm);
  hot_x[41] = 2;
  hot_y[41] = 9;
  images[42] = wxImage(small_arrow_right_xpm);
  hot_x[42] = 13;
  hot_y[42] = 9;
  images[43] = wxImage(large_arrow_right_xpm);
  hot_x[43] = 15;
  hot_y[43] = 9;
  images[44] = wxImage(small_arrow_up_left_xpm);
  hot_x[44] = 6;
  hot_y[44] = 7;
  images[45] = wxImage(large_arrow_up_left_xpm);
  hot_x[45] = 4;
  hot_y[45] = 4;
  images[46] = wxImage(small_arrow_up_right_xpm);
  hot_x[46] = 9;
  hot_y[46] = 7;
  images[47] = wxImage(large_arrow_up_right_xpm);
  hot_x[47] = 12;
  hot_y[47] = 4;
  images[48] = wxImage(small_arrow_down_left_xpm);
  hot_x[48] = 6;
  hot_y[48] = 9;
  images[49] = wxImage(large_arrow_down_left_xpm);
  hot_x[49] = 4;
  hot_y[49] = 12;
  images[50] = wxImage(small_arrow_down_right_xpm);
  hot_x[50] = 9;
  hot_y[50] = 9;
  images[51] = wxImage(large_arrow_down_right_xpm);
  hot_x[51] = 12;
  hot_y[51] = 12;
  images[52] = wxImage(white_flag_xpm);
  hot_x[52] = 13;
  hot_y[52] = 14;
  images[53] = wxImage(yellow_flag_xpm);
  hot_x[53] = 13;
  hot_y[53] = 14;
  images[54] = wxImage(red_flag_xpm);
  hot_x[54] = 13;
  hot_y[54] = 14;
  images[55] = wxImage(green_flag_xpm);
  hot_x[55] = 13;
  hot_y[55] = 14;
  images[56] = wxImage(blue_flag_xpm);
  hot_x[56] = 13;
  hot_y[56] = 14;
  images[57] = wxImage(flag_blue_xpm);
  hot_x[57] = 10;
  hot_y[57] = 14;
  images[58] = wxImage(flag_green_xpm);
  hot_x[58] = 10;
  hot_y[58] = 14;
  images[59] = wxImage(flag_orange_xpm);
  hot_x[59] = 10;
  hot_y[59] = 14;
  images[60] = wxImage(flag_pink_xpm);
  hot_x[60] = 10;
  hot_y[60] = 14;
  images[61] = wxImage(flag_purple_xpm);
  hot_x[61] = 10;
  hot_y[61] = 14;
  images[62] = wxImage(flag_red_xpm);
  hot_x[62] = 10;
  hot_y[62] = 14;
  images[63] = wxImage(flag_yellow_xpm);
  hot_x[63] = 10;
  hot_y[63] = 14;
  images[64] = wxImage(bullet_add_xpm);
  images[65] = wxImage(bullet_delete_xpm);
  images[66] = wxImage(bullet_star_xpm);
  images[67] = wxImage(bullet_picture_xpm);
  images[68] = wxImage(bullet_error_xpm);
  images[69] = wxImage(bullet_arrow_up_xpm);
  images[70] = wxImage(bullet_arrow_down_xpm);
  images[71] = wxImage(bullet_black_xpm);
  images[72] = wxImage(bullet_white_xpm);
  images[73] = wxImage(bullet_yellow_xpm);
  images[74] = wxImage(bullet_orange_xpm);
  images[75] = wxImage(bullet_pink_xpm);
  images[76] = wxImage(bullet_red_xpm);
  images[77] = wxImage(bullet_green_xpm);
  images[78] = wxImage(bullet_blue_xpm);
  images[79] = wxImage(asterisk_yellow_xpm);
  images[80] = wxImage(accept_xpm);
  images[81] = wxImage(add_xpm);
  images[82] = wxImage(delete_xpm);
  images[83] = wxImage(exclamation_xpm);
  images[84] = wxImage(information1_xpm);
  images[85] = wxImage(help_xpm);
  images[86] = wxImage(action_stop_xpm);
  images[87] = wxImage(icon_accept_xpm);
  images[88] = wxImage(icon_alert_xpm);
  images[89] = wxImage(icon_info_xpm);
  images[90] = wxImage(time_xpm);
  images[91] = wxImage(icon_clock_xpm);
  images[92] = wxImage(money1_xpm);
  images[93] = wxImage(money_dollar_xpm);
  images[94] = wxImage(money_euro_xpm);
  images[95] = wxImage(icon_email_xpm);
  images[96] = wxImage(email_xpm);
  images[97] = wxImage(icon_home_xpm);
  images[98] = wxImage(house_xpm);
  images[99] = wxImage(icon_key_xpm);
  images[100] = wxImage(icon_security_xpm);
  images[101] = wxImage(icon_user_xpm);
  images[102] = wxImage(icon_world_xpm);
  images[103] = wxImage(camera_xpm);
  images[104] = wxImage(camera_small_xpm);
  images[105] = wxImage(photo_xpm);
  images[106] = wxImage(photos_xpm);
  images[107] = wxImage(picture_xpm);
  images[108] = wxImage(picture_empty_xpm);
  images[109] = wxImage(pictures_xpm);
  images[110] = wxImage(chart_bar_xpm);
  images[111] = wxImage(color_wheel_xpm);
  images[112] = wxImage(rainbow_xpm);
  images[113] = wxImage(palette_xpm);
  images[114] = wxImage(rosette_xpm);
  images[115] = wxImage(music_xpm);
  images[116] = wxImage(male_xpm);
  images[117] = wxImage(female_xpm);
  images[118] = wxImage(drink_xpm);
  images[119] = wxImage(drink_empty_xpm);
  images[120] = wxImage(bell_xpm);
  images[121] = wxImage(book_open_xpm);
  images[122] = wxImage(brick_xpm);
  images[123] = wxImage(cog_xpm);
  images[124] = wxImage(heart_xpm);
  images[125] = wxImage(cart_xpm);
  images[126] = wxImage(new_xpm);
  images[127] = wxImage(camping_xpm);
  images[128] = wxImage(guest_house_xpm);
  images[129] = wxImage(hostel_xpm);
  images[130] = wxImage(hotel_xpm);
  images[131] = wxImage(caravan_xpm);
  images[132] = wxImage(trash_xpm);
  full_color[132] = 0;
  images[133] = wxImage(hospital_xpm);
  images[134] = wxImage(pharmacy_xpm);
  images[135] = wxImage(emergency_xpm);
  images[136] = wxImage(firebrigade_xpm);
  images[137] = wxImage(crane_xpm);
  hot_x[137] = 6;
  hot_y[137] = 10;
  images[138] = wxImage(lighthouse_xpm);
  hot_x[138] = 5;
  hot_y[138] = 14;
  images[139] = wxImage(mine_xpm);
  images[140] = wxImage(plant_xpm);
  hot_y[140] = 14;
  images[141] = wxImage(trees_xpm);
  images[142] = wxImage(works_xpm);
  hot_y[142] = 12;
  images[143] = wxImage(danger_xpm);
  images[144] = wxImage(information_xpm);
  images[145] = wxImage(proposed_xpm);
  images[146] = wxImage(tap_drinking_xpm);
  images[147] = wxImage(exchange_xpm);
  images[148] = wxImage(anchor_xpm);
  images[149] = wxImage(island_xpm);
  hot_y[149] = 12;
  images[150] = wxImage(post_box_xpm);
  full_color[150] = 0;
  images[151] = wxImage(recycling_xpm);
  hot_y[151] = 6;
  images[152] = wxImage(telephone_xpm);
  hot_x[152] = 5;
  hot_y[152] = 9;
  images[153] = wxImage(toilets_xpm);
  images[154] = wxImage(bicycling_xpm);
  full_color[154] = 0;
  images[155] = wxImage(garden_xpm);
  images[156] = wxImage(park_xpm);
  images[157] = wxImage(picnic_xpm);
  images[158] = wxImage(theater_xpm);
  images[159] = wxImage(zoo_xpm);
  images[160] = wxImage(castle_xpm);
  images[161] = wxImage(museum_xpm);
  images[162] = wxImage(viewpoint_xpm);
  images[163] = wxImage(helipad_xpm);
  images[164] = wxImage(airport_xpm);
  images[165] = wxImage(bus_xpm);
  images[166] = wxImage(car_xpm);
  images[167] = wxImage(handicapped_xpm);
  full_color[167] = 0;
  images[168] = wxImage(pedestrian_xpm);
  images[169] = wxImage(railway_xpm);
  images[170] = wxImage(park_car_xpm);
  images[171] = wxImage(garage_xpm);
  images[172] = wxImage(parking_xpm);
  images[173] = wxImage(emergency_phone_xpm);
  images[174] = wxImage(fuel_station_xpm);
  images[175] = wxImage(motorbike_xpm);
  full_color[175] = 0;
  images[176] = wxImage(repair_shop_xpm);
  full_color[176] = 0;
  images[177] = wxImage(restrictions_xpm);
  images[178] = wxImage(incline_xpm);
  images[179] = wxImage(parking2_xpm);
  images[180] = wxImage(motorbike2_xpm);
  images[181] = wxImage(right_of_way_xpm);
  images[182] = wxImage(road_works_xpm);
  images[183] = wxImage(roundabout_left_xpm);
  images[184] = wxImage(roundabout_right_xpm);
  images[185] = wxImage(stop_xpm);
  images[186] = wxImage(traffic_jam_xpm);
  images[187] = wxImage(traffic_light_xpm);
  images[188] = wxImage(health_xpm);
  images[189] = wxImage(money_xpm);
  full_color[189] = 0;
  images[190] = wxImage(nautical_xpm);
  hot_y[190] = 9;
  full_color[190] = 0;
  images[191] = wxImage(people_xpm);
  full_color[191] = 0;
  images[192] = wxImage(shopping_xpm);
  images[193] = wxImage(sports_xpm);
  images[194] = wxImage(vehicle_xpm);
  images[195] = wxImage(wpttemp_xpm);
  hot_x[195] = 1;
  hot_y[195] = 15;
  images[196] = wxImage(wpttemp_green_xpm);
  hot_x[196] = 1;
  hot_y[196] = 15;
  images[197] = wxImage(wpttemp_red_xpm);
  hot_x[197] = 1;
  hot_y[197] = 15;
  images[198] = wxImage(wpttemp_yellow_xpm);
  hot_x[198] = 1;
  hot_y[198] = 15;
  images[199] = wxImage(tux_xpm);

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
  sql = wxT("CREATE TABLE symbol_bitmaps (\n");
  sql += wxT("symbol_id INTEGER PRIMARY KEY AUTOINCREMENT,\n");
  sql += wxT("full_color INTEGER NOT NULL,\n");
  sql += wxT("bitmap BLOB NOT NULL,\n");
  sql += wxT("hotpoint_x INTEGER NOT NULL,\n");
  sql += wxT("hotpoint_y INTEGER NOT NULL)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// preparing the SQL statement
//
  sql =
    wxT
    ("INSERT INTO symbol_bitmaps (symbol_id, full_color, bitmap, hotpoint_x, hotpoint_y) ");
  sql += wxT("VALUES (NULL, ?, ?, ?, ?)");
  ret = sqlite3_prepare_v2(SqliteHandle, sql.ToUTF8(), sql.Len(), &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  for (ind = 0; ind < 200; ind++)
    {
      // inserting symbols
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      blob_size = images[ind].GetWidth() * images[ind].GetHeight() * 4;
      blob = (unsigned char *) malloc(blob_size);
      p_blob = blob;
      for (row = 0; row < images[ind].GetHeight(); row++)
        {
          for (col = 0; col < images[ind].GetWidth(); col++)
            {
              if (images[ind].IsTransparent(col, row) == true)
                {
                  *(p_blob++) = images[ind].GetRed(col, row);
                  *(p_blob++) = images[ind].GetGreen(col, row);
                  *(p_blob++) = images[ind].GetBlue(col, row);
                  *(p_blob++) = 0x00;
              } else
                {
                  *(p_blob++) = images[ind].GetRed(col, row);
                  *(p_blob++) = images[ind].GetGreen(col, row);
                  *(p_blob++) = images[ind].GetBlue(col, row);
                  *(p_blob++) = 0xff;
                }
            }
        }
      sqlite3_bind_int(stmt, 1, full_color[ind]);
      sqlite3_bind_blob(stmt, 2, blob, blob_size, free);
      sqlite3_bind_int(stmt, 3, hot_x[ind]);
      sqlite3_bind_int(stmt, 4, hot_y[ind]);

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

bool MyFrame::CreatePatternBitmaps()
{
//
// creating and initializing the 'pattern_bitmaps' table 
//
  int ret;
  char *errMsg = NULL;
  wxString sql;
  sqlite3_stmt *stmt;
  int ind;
  int row;
  int col;
  int blob_size;
  unsigned char *blob;
  unsigned char *p_blob;
  int full_color[49];
  wxImage images[49];

  for (ind = 0; ind < 49; ind++)
    {
      // standard settings
      if (ind <= 35)
        full_color[ind] = 0;
      else
        full_color[ind] = 1;
    }

  images[0] = wxImage(dense1_xpm);
  images[1] = wxImage(dense2_xpm);
  images[2] = wxImage(dense3_xpm);
  images[3] = wxImage(dense4_xpm);
  images[4] = wxImage(dense5_xpm);
  images[5] = wxImage(dense6_xpm);
  images[6] = wxImage(dots1_xpm);
  images[7] = wxImage(dots2_xpm);
  images[8] = wxImage(dots3_xpm);
  images[9] = wxImage(dots5_xpm);
  images[10] = wxImage(dots6_xpm);
  images[11] = wxImage(brickwall_xpm);
  images[12] = wxImage(horz0_xpm);
  images[13] = wxImage(horz01_xpm);
  images[14] = wxImage(horz1_xpm);
  images[15] = wxImage(horz2_xpm);
  images[16] = wxImage(vert0_xpm);
  images[17] = wxImage(vert01_xpm);
  images[18] = wxImage(vert1_xpm);
  images[19] = wxImage(vert2_xpm);
  images[20] = wxImage(diag1_0_xpm);
  images[21] = wxImage(diag1_01_xpm);
  images[22] = wxImage(diag1_1_xpm);
  images[23] = wxImage(diag1_2_xpm);
  images[24] = wxImage(diag2_0_xpm);
  images[25] = wxImage(diag2_01_xpm);
  images[26] = wxImage(diag2_1_xpm);
  images[26] = wxImage(diag2_2_xpm);
  images[27] = wxImage(cross0_xpm);
  images[28] = wxImage(cross01_xpm);
  images[29] = wxImage(cross1_xpm);
  images[31] = wxImage(cross2_xpm);
  images[32] = wxImage(diag_cross_0_xpm);
  images[33] = wxImage(diag_cross_01_xpm);
  images[34] = wxImage(diag_cross_1_xpm);
  images[35] = wxImage(diag_cross_2_xpm);
  images[36] = wxImage(sea1_xpm);
  images[37] = wxImage(sea2_xpm);
  images[38] = wxImage(sea3_xpm);
  images[39] = wxImage(land1_xpm);
  images[40] = wxImage(land2_xpm);
  images[41] = wxImage(land3_xpm);
  images[42] = wxImage(land4_xpm);
  images[43] = wxImage(land5_xpm);
  images[44] = wxImage(land6_xpm);
  images[45] = wxImage(land7_xpm);
  images[46] = wxImage(land8_xpm);
  images[47] = wxImage(land9_xpm);
  images[48] = wxImage(land10_xpm);

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
  sql = wxT("CREATE TABLE pattern_bitmaps (\n");
  sql += wxT("pattern_id INTEGER PRIMARY KEY AUTOINCREMENT,\n");
  sql += wxT("full_color INTEGER NOT NULL,\n");
  sql += wxT("bitmap BLOB NOT NULL)");
  ret = sqlite3_exec(SqliteHandle, sql.ToUTF8(), NULL, 0, &errMsg);
  if (ret != SQLITE_OK)
    {
      wxMessageBox(wxT("SQL error:") + wxString::FromUTF8(errMsg),
                   wxT("spatialite-gis"), wxOK | wxICON_ERROR, this);
      sqlite3_free(errMsg);
      goto stop;
    }
//
// preparing the SQL statement
//
  sql = wxT("INSERT INTO pattern_bitmaps (pattern_id, full_color, bitmap) ");
  sql += wxT("VALUES (NULL, ?, ?)");
  ret = sqlite3_prepare_v2(SqliteHandle, sql.ToUTF8(), sql.Len(), &stmt, NULL);
  if (ret != SQLITE_OK)
    {
      wxString err = wxString::FromUTF8(sqlite3_errmsg(SqliteHandle));
      wxMessageBox(wxT("SQL error:") + err, wxT("spatialite-gis"),
                   wxOK | wxICON_ERROR, this);
      goto stop;
    }

  for (ind = 0; ind < 49; ind++)
    {
      // inserting symbols
      sqlite3_reset(stmt);
      sqlite3_clear_bindings(stmt);
      blob_size = images[ind].GetWidth() * images[ind].GetHeight() * 4;
      blob = (unsigned char *) malloc(blob_size);
      p_blob = blob;
      for (row = 0; row < images[ind].GetHeight(); row++)
        {
          for (col = 0; col < images[ind].GetWidth(); col++)
            {
              if (images[ind].IsTransparent(col, row) == true)
                {
                  *(p_blob++) = images[ind].GetRed(col, row);
                  *(p_blob++) = images[ind].GetGreen(col, row);
                  *(p_blob++) = images[ind].GetBlue(col, row);
                  *(p_blob++) = 0x00;
              } else
                {
                  *(p_blob++) = images[ind].GetRed(col, row);
                  *(p_blob++) = images[ind].GetGreen(col, row);
                  *(p_blob++) = images[ind].GetBlue(col, row);
                  *(p_blob++) = 0xff;
                }
            }
        }
      sqlite3_bind_int(stmt, 1, full_color[ind]);
      sqlite3_bind_blob(stmt, 2, blob, blob_size, free);

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

void MyFrame::GetSymbolBitmaps(MyImageList * list)
{
//
// loading the 'symbol_bitmaps' image list 
//
  wxString sql;
  int ret;
  sqlite3_stmt *stmt;
  int width = 16;               // required bitmap width
  int height = 16;              // required bitmap height
  wxColour foreground(192, 96, 64);
  wxColour background(64, 127, 96);

  sql = wxT("SELECT symbol_id, full_color, bitmap, hotpoint_x, hotpoint_y ");
  sql += wxT("FROM symbol_bitmaps");
  ret = sqlite3_prepare_v2(SqliteHandle, sql.ToUTF8(), sql.Len(), &stmt, NULL);
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
          int id = -1;
          int full_color = 0;
          const void *blob = NULL;
          int blob_size = -1;
          int hotpoint_x = -1;
          int hotpoint_y = -1;
          bool err = false;
          if (sqlite3_column_type(stmt, 0) == SQLITE_INTEGER)
            id = sqlite3_column_int(stmt, 0);
          else
            err = true;
          if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
            full_color = sqlite3_column_int(stmt, 1);
          else
            err = true;
          if (sqlite3_column_type(stmt, 2) == SQLITE_BLOB)
            {
              blob = sqlite3_column_blob(stmt, 2);
              blob_size = sqlite3_column_bytes(stmt, 2);
              if (blob_size == 0 || blob == NULL)
                err = true;
          } else
            err = true;
          if (sqlite3_column_type(stmt, 3) == SQLITE_INTEGER)
            hotpoint_x = sqlite3_column_int(stmt, 3);
          else
            err = true;
          if (sqlite3_column_type(stmt, 4) == SQLITE_INTEGER)
            hotpoint_y = sqlite3_column_int(stmt, 4);
          else
            err = true;
          if (err == false)
            {
              if (full_color == 0)
                {
                  // adding a BiColor Symbol
                  if (blob_size == (width * height * 4))
                    list->Add(id, width, height, (unsigned char *) blob,
                              hotpoint_x, hotpoint_y, foreground, background);
              } else
                {
                  // adding a FullColor Symbol
                  if (blob_size == (width * height * 4))
                    list->Add(id, width, height, (unsigned char *) blob,
                              hotpoint_x, hotpoint_y);
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

stop:
  return;
}

void MyFrame::GetPatternBitmaps(MyImageList * list)
{
//
// loading the 'pattern_bitmaps' image list 
//
  wxString sql;
  int ret;
  sqlite3_stmt *stmt;
  int width = 16;               // required bitmap width
  int height = 16;              // required bitmap height
  wxColour color(64, 127, 96);

  sql = wxT("SELECT pattern_id, full_color, bitmap ");
  sql += wxT("FROM pattern_bitmaps");
  ret = sqlite3_prepare_v2(SqliteHandle, sql.ToUTF8(), sql.Len(), &stmt, NULL);
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
          int id = -1;
          int full_color = 0;
          const void *blob = NULL;
          int blob_size = -1;
          bool err = false;
          if (sqlite3_column_type(stmt, 0) == SQLITE_INTEGER)
            id = sqlite3_column_int(stmt, 0);
          else
            err = true;
          if (sqlite3_column_type(stmt, 1) == SQLITE_INTEGER)
            full_color = sqlite3_column_int(stmt, 1);
          else
            err = true;
          if (sqlite3_column_type(stmt, 2) == SQLITE_BLOB)
            {
              blob = sqlite3_column_blob(stmt, 2);
              blob_size = sqlite3_column_bytes(stmt, 2);
              if (blob_size == 0 || blob == NULL)
                err = true;
          } else
            err = true;
          if (err == false)
            {
              if (full_color == 0)
                {
                  // adding a MonoColor Pattern
                  if (blob_size == (width * height * 4))
                    list->Add(id, width, height, (unsigned char *) blob, color);
              } else
                {
                  // adding a FullColor Pattern
                  if (blob_size == (width * height * 4))
                    list->Add(id, width, height, (unsigned char *) blob);
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

stop:
  return;
}

/*    This file is part of fractal
      Copyright (C) 2016  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "h_block_worker.h"
#include <iostream>
#include <chrono>
namespace fractal
{
  //----------------------------------------------------------------------------
  h_block_worker::h_block_worker(simple_gui::simple_gui & p_gui,
				 const unsigned int & p_id,
				 const unsigned int & p_width,
				 const unsigned int & p_height,
				 const uint32_t & p_color_code,
				 const unsigned int & p_total_worker):
    worker("h_block",p_gui,p_id,p_width,p_height,p_color_code,p_total_worker)
  {
  }

  //----------------------------------------------------------------------------
  void h_block_worker::specialised_run()
  {
    unsigned int l_worker_height = get_height() / get_total_worker();
    for(unsigned int l_y = 0; l_y < l_worker_height ; ++l_y)
      {
   	for(unsigned int l_x = 0 ; l_x < get_width() ; ++l_x)
          {
	    treat_pixel(l_x,l_y + l_worker_height * get_id(),/*m_color_code*/0);
          }
      }
  }
}


//EOF

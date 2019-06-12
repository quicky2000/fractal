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
#include "horizontal_worker.h"
#include <iostream>
#include <chrono>
namespace fractal
{
  //----------------------------------------------------------------------------
  horizontal_worker::horizontal_worker(simple_gui::simple_gui & p_gui,
				       const unsigned int & p_id,
				       const unsigned int & p_width,
				       const unsigned int & p_height,
				       const uint32_t & p_color_code,
				       const unsigned int & p_total_worker):
    worker("horizontal",p_gui,p_id,p_width,p_height,p_color_code,p_total_worker)
  {
  }

  //----------------------------------------------------------------------------
  void horizontal_worker::specialised_run()
  {
    //    std::chrono::milliseconds l_wait(10);
    for(unsigned int l_y = 0 + get_id(); l_y < get_height() ; l_y+= get_total_worker())
      {
   	for(unsigned int l_x = 0 ; l_x < get_width() ; ++l_x)
	  {
	    treat_pixel(l_x,l_y,/*m_color_code*/0);
   	  }
	//	std::this_thread::sleep_for(l_wait);
      }
  }
}


//EOF

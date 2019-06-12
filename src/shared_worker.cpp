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
#include "shared_worker.h"
#include <iostream>
#include <chrono>
#include <iomanip>

namespace fractal
{
	//----------------------------------------------------------------------------
	shared_worker::shared_worker(simple_gui::simple_gui & p_gui
	                            ,const unsigned int & p_id
	                            ,const unsigned int & p_width
	                            ,const unsigned int & p_height
	                            ,const uint32_t & p_color_code
	                            ,const unsigned int & p_total_worker
	                            ,const unsigned int & p_slot_size
	                            )
    :worker("shared", p_gui, p_id, p_width, p_height, p_color_code, p_total_worker)
    ,m_fail(0)
    ,m_total(0)
    ,m_slot_size(p_slot_size)
    {
    }

    //----------------------------------------------------------------------------
    void shared_worker::specialised_run()
    {
	    unsigned int l_max = get_width() * get_height();
	    while(m_index.load() < l_max)
	    {
	        ++m_total;
	        uint32_t l_old_value = m_index.load();
	        while(!m_index.compare_exchange_strong(l_old_value,l_old_value + m_slot_size))
	        {
	            ++m_fail;
	        }
	        if(l_old_value < l_max)
	        {
	            for(unsigned int l_index = l_old_value ; l_index < l_old_value + m_slot_size && l_index < l_max ; ++l_index)
	            {
	                treat_pixel(l_index % get_width(),l_index / get_width(),/*m_color_code*/0);
	            }
	        }
	    }
    }

    //----------------------------------------------------------------------------
    void shared_worker::report(std::ostream & p_stream)
    {
	    p_stream << " and " << m_fail << " compare exchange_fails for " << m_total << " slots ie " << std::setprecision(3) << (100.0 * m_fail) / m_total << "%";
    }

    std::atomic<uint32_t> shared_worker::m_index(0);
}
//EOF

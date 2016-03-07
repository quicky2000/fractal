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
#include "worker.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

namespace fractal
{
  //----------------------------------------------------------------------------
  worker::worker(const std::string & p_name,
		 simple_gui & p_gui,
		 const unsigned int & p_id,
		 const unsigned int & p_width,
		 const unsigned int & p_height,
		 const uint32_t & p_color_code,
		 const unsigned int & p_total_worker):
    m_name(p_name),
    m_gui(p_gui),
    m_id(p_id),
    m_width(p_width),
    m_height(p_height),
    m_nb_iter(0),
    m_nb_pixels(0),
    m_color_code(p_color_code),
    m_total_worker(p_total_worker)
  {
    std::cout << "Building worker " << m_name << std::endl ;
  }

  //----------------------------------------------------------------------------
  worker::~worker(void)
  {
    std::cout << "Destroying worker " << m_name << std::endl ;
  }
  
  //----------------------------------------------------------------------------
  const std::string & worker::get_name(void)const
  {
    return m_name;
  }

  //----------------------------------------------------------------------------
  void worker::run(void)
  {
    assert(1 == m_total_worker);
    std::cout << "Worker " << m_name << " running" << std::endl ;
    std::chrono::milliseconds l_wait(10);
    for(unsigned int l_y = 0 ; l_y < m_height ; ++l_y)
      {
	for(unsigned int l_x = 0 ; l_x < m_width ; ++l_x)
	  {
	    treat_pixel(l_x,l_y,m_color_code);
	  }
	std::this_thread::sleep_for(l_wait);
      }
    std::cout << "Worker " << m_name << " end of run" << std::endl ;
  }
  //----------------------------------------------------------------------------
  void worker::launch_worker(worker & p_worker)
  {
    std::cout << "Launch worker " << p_worker.get_name() << std::endl ;
    p_worker.run();
  }
}
//EOF

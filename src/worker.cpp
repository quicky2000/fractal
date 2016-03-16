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
#include "quicky_exception.h"
#include <iostream>
#include <thread>
#include <cassert>
#include <sstream>

namespace fractal
{
  //----------------------------------------------------------------------------
  worker::worker(const std::string & p_name,
		 simple_gui::simple_gui & p_gui,
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
    m_total_worker(p_total_worker),
    m_elapsed_seconds(0)
  {
    std::stringstream l_id_stream;
    l_id_stream << p_id;
    m_name += "[" + l_id_stream.str() + "]";
    std::cout << "Building worker " << m_name << std::endl ;
    if(p_id >= p_total_worker)
      {
	throw quicky_exception::quicky_logic_exception("Id is greater than total number of worker",__LINE__,__FILE__);
      }
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
    std::chrono::time_point<std::chrono::system_clock> l_start = std::chrono::system_clock::now();
    this->specialised_run();
    std::chrono::time_point<std::chrono::system_clock> l_end = std::chrono::system_clock::now();
    m_elapsed_seconds = l_end - l_start;
    std::cout << get_name() << " end of run" << std::endl ;
#if 0
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
#endif // 0
  }
  //----------------------------------------------------------------------------
  void worker::launch_worker(worker & p_worker)
  {
    std::cout << "Launch worker " << p_worker.get_name() << std::endl ;
    p_worker.run();
  }

  //----------------------------------------------------------------------------
  void worker::report(std::ostream & p_stream)
  {
  }
}
//EOF

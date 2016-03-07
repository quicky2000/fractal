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
#ifndef _WORKER_H_
#define _WORKER_H_

#include "simple_gui.h"
#include <string>
#include <complex>

namespace fractal
{
  class worker
  {
  public:
    worker(const std::string & p_name,
	   simple_gui & p_gui,
	   const unsigned int & p_id,
	   const unsigned int & p_width,
	   const unsigned int & p_height,
	   const uint32_t & p_color_code,
	   const unsigned int & p_total_worker);
    ~worker(void);
    virtual void run(void);
    const std::string & get_name(void)const;
    static void launch_worker(worker & p_worker);
    typedef void (*launcher_type)(worker&);
  protected:
    inline void treat_pixel(const unsigned int & p_x,
			    const unsigned int & p_y,
			    const uint32_t & p_color_code);
  private:
    std::string m_name;
    simple_gui & m_gui;
    unsigned int m_id;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_nb_iter;
    unsigned int m_nb_pixels;
    uint32_t m_color_code;
    unsigned int m_total_worker;
  };

  //------------------------------------------------------------------------------
  void worker::treat_pixel(const unsigned int & p_x,
			   const unsigned int & p_y,
			   const uint32_t & p_color_code)
  {
    unsigned int l_nb_iter = 50;
    std::complex<float> l_point(3.0 * p_x / (m_width - 1.0) - 2,- 2.0 * p_y / (m_height -1.0) + 1);
    std::complex<float> l_tmp(0,0);
    do
      {
	l_tmp = l_tmp * l_tmp + l_point;
	++m_nb_iter;
      } while(norm(l_tmp) < 4 && l_nb_iter--);
    if(norm(l_tmp) < 4)
      {
	m_gui.set_pixel_without_lock(p_x,p_y,p_color_code);
      }
    ++m_nb_pixels;
  }
}


#endif // _WORKER_H_H
//EOF

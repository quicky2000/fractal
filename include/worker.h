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
#include <chrono>

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
    virtual ~worker(void);
    void run(void);
    const std::string & get_name(void)const;
    static void launch_worker(worker & p_worker);
    typedef void (*launcher_type)(worker&);
    inline const unsigned int & get_nb_iter(void)const;
    inline const unsigned int & get_nb_pixels(void)const;
    virtual void report(std::ostream & p_stream);
    inline const std::chrono::duration<double> & get_duration(void)const;
  protected:
    inline void treat_pixel(const unsigned int & p_x,
			    const unsigned int & p_y,
			    const uint32_t & p_color_code);
    inline const unsigned int & get_id(void)const;
    inline const unsigned int & get_width(void)const;
    inline const unsigned int & get_height(void)const;
    inline const unsigned int & get_total_worker(void)const;
  private:
    virtual void specialised_run(void)=0;

    std::string m_name;
    simple_gui & m_gui;
    unsigned int m_id;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_nb_iter;
    unsigned int m_nb_pixels;
    uint32_t m_color_code;
    unsigned int m_total_worker;
    std::chrono::duration<double> m_elapsed_seconds;
  };

  //------------------------------------------------------------------------------
  void worker::treat_pixel(const unsigned int & p_x,
			   const unsigned int & p_y,
			   const uint32_t & p_color_code)
  {
    unsigned int l_nb_iter = 500;
    std::complex<float> l_point(3.0 * p_x / (m_width - 1.0) - 2,- 2.0 * p_y / (m_height -1.0) + 1);
    std::complex<float> l_tmp(0,0);
    do
      {
	l_tmp = l_tmp * l_tmp + l_point;
	++m_nb_iter;
      } while(norm(l_tmp) < 4 && l_nb_iter--);
    if(norm(l_tmp) < 4)
      {
	m_gui.set_pixel_without_lock(p_x,p_y,m_color_code);
      }
    ++m_nb_pixels;
  }

  //------------------------------------------------------------------------------
  const unsigned int & worker::get_id(void)const
    {
      return m_id;
    }

  //------------------------------------------------------------------------------
  const unsigned int & worker::get_width(void)const
    {
      return m_width;
    }

  //------------------------------------------------------------------------------
  const unsigned int & worker::get_height(void)const
    {
      return m_height;
    }

  //------------------------------------------------------------------------------
  const unsigned int & worker::get_total_worker(void)const
  {
    return m_total_worker;
  }

  //------------------------------------------------------------------------------
  const unsigned int & worker::get_nb_iter(void)const
  {
    return m_nb_iter;
  }

  //------------------------------------------------------------------------------
  const unsigned int & worker::get_nb_pixels(void)const
  {
    return m_nb_pixels;
  }

  //------------------------------------------------------------------------------
  const std::chrono::duration<double> & worker::get_duration(void)const
  {
    return m_elapsed_seconds;
  }
}


#endif // _WORKER_H_
//EOF

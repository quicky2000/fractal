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
    /**
     * Base class for thread
     */
    class worker
    {
      public:
        /**
         * Constructor
         * @param p_gui GUI in which computed pixel will be displayed
         * @param p_id thread id
         * @param p_width resolution width
         * @param p_height resolution height
         * @param p_color_code color code attributed to this thread
         * @param p_total_worker total number of threads
         */
        worker(const std::string & p_name
              ,simple_gui::simple_gui & p_gui
              ,unsigned int p_id
              ,unsigned int p_width
              ,unsigned int p_height
              ,uint32_t p_color_code
              ,unsigned int p_total_worker
              );

        /**
         * Destructor
         */
        virtual ~worker();

        /**
         * Computation code
         */
        void run();

        /**
         * Return thread implementation type name
         * @return thread implementation type name
         */
        const std::string & get_name()const;

        /**
         * Start a thread provided as parameter
         * @param p_worker Thread to launch
         */
        static void launch_worker(worker & p_worker);

        /**
         * Accessor to number of pixel computation iteration
         * @return number of pixel computation iteration
         */
        inline
        unsigned int get_nb_iter()const;

        /**
         * Accessor to number of computed pixels
         * @return number of computed pixels
         */
        inline
        unsigned int get_nb_pixels()const;

        /**
         * Report osme information about thread execution
         * @param p_stream stream on which information is reported
         */
        virtual void report(std::ostream & p_stream);

        /**
         * Return duration of thread execution
         * @return duration of thread execution
         */
        inline
        const std::chrono::duration<double> & get_duration()const;

      protected:
        /**
         * Pixel computation and display
         * @param p_x Pixel x coordinate
         * @param p_y Pixel y coordinate
         * @param p_color_code color of pixel
         */
        inline
        void treat_pixel(unsigned int p_x
                        ,unsigned int p_y
                        ,uint32_t p_color_code
                        );
        /**
         * Accessor to thread Id
         * @return Thread Id
         */
        inline
        unsigned int get_id()const;

        /**
         * Accessor to resolution width
         * @return resolution width
         */
        inline
        unsigned int get_width()const;

        /**
         * Accessor to resolution height
         * @return resolution height
         */
        inline
        unsigned int get_height()const;

        /**
         * Accessor to number of thread
         * @return number of thread
         */
        inline
        unsigned int get_total_worker()const;

      private:
        /**
         * Specialised hread implementation
         */
        virtual void specialised_run() = 0;

        /**
         * name of thread implementation
         */
        std::string m_name;

        /**
         * Graphical interface where pixels are displayed
         */
        simple_gui::simple_gui & m_gui;

        /**
         * Thread Id
         */
        unsigned int m_id;

        /**
         * Resolution width
         */
        unsigned int m_width;

        /**
         * Resolution height
         */
        unsigned int m_height;

        /**
         * Number of pixel computation iteration
         */
        unsigned int m_nb_iter;

        /**
         * Number of computed pixels
         */
        unsigned int m_nb_pixels;

        /**
         * Color code assigned to this thread
         */
        uint32_t m_color_code;

        /**
         * Number of threads
         */
        unsigned int m_total_worker;

        /**
         * Execution time of thread
         */
        std::chrono::duration<double> m_elapsed_seconds;
    };

    //------------------------------------------------------------------------------
    void worker::treat_pixel(unsigned int p_x
                            ,unsigned int p_y
                            ,uint32_t p_color_code
                            )
    {
        unsigned int l_nb_iter = 500;
        std::complex<float> l_point((float)(3.0 * p_x / (m_width - 1.0) - 2),(float)(- 2.0 * p_y / (m_height -1.0) + 1));
        std::complex<float> l_tmp(0,0);
        do
        {
            l_tmp = l_tmp * l_tmp + l_point;
            ++m_nb_iter;
        }
        while(norm(l_tmp) < 4 && l_nb_iter--);

        if(norm(l_tmp) < 4)
        {
            m_gui.set_pixel_without_lock(p_x,p_y,m_color_code);
        }
        ++m_nb_pixels;
    }

    //------------------------------------------------------------------------------
    unsigned int worker::get_id() const
    {
        return m_id;
    }

    //------------------------------------------------------------------------------
    unsigned int worker::get_width() const
    {
        return m_width;
    }

    //------------------------------------------------------------------------------
    unsigned int worker::get_height() const
    {
        return m_height;
    }

    //------------------------------------------------------------------------------
    unsigned int worker::get_total_worker() const
    {
        return m_total_worker;
    }

    //------------------------------------------------------------------------------
    unsigned int worker::get_nb_iter() const
    {
        return m_nb_iter;
    }

    //------------------------------------------------------------------------------
    unsigned int worker::get_nb_pixels() const
    {
        return m_nb_pixels;
    }

    //------------------------------------------------------------------------------
    const std::chrono::duration<double> & worker::get_duration() const
    {
        return m_elapsed_seconds;
    }
}


#endif // _WORKER_H_
//EOF

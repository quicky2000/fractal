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
#ifndef _WORKER_FACTORY_H_
#define _WORKER_FACTORY_H_

#include "worker.h"
#include "simple_gui.h"
#include <cinttypes>

namespace fractal
{
    /**
     * Class used to create various worker types
     */
	class worker_factory
    {
      public:
        /**
         * Create a thread with some parameter
         * @param p_type typeof thread
         * @param p_gui GUI in which computed pixel will be displayed
         * @param p_id thread id
         * @param p_width resolution width
         * @param p_height resolution height
         * @param p_color_code color code attributed to this thread
         * @param p_total_worker total number of threads
         * @param p_slot_size number of ocnsecutive pixels to compute
         */
        static
        worker * create_worker(const std::string & p_type
                              ,simple_gui::simple_gui & p_gui
                              ,unsigned int p_id
                              ,unsigned int p_width
                              ,unsigned int p_height
                              ,uint32_t p_color_code
                              ,unsigned int p_total_worker
                              ,unsigned int p_slot_size
                              );

      private:
    };
}
#endif // _WORKER_FACTORY_H_
//EOF

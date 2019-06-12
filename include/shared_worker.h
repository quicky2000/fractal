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
#ifndef _SHARED_WORKER_H_
#define _SHARED_WORKER_H_

#include "worker.h"
#include <atomic>
#include <cinttypes>

namespace fractal
{
    /**
     * Thread implementation where thread compute some consecutive pixels
     * A common index is shared by all threads that try to acquire it
     */
	class shared_worker: public worker
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
         * @param p_slot_size number of ocnsecutive pixels to compute
         */
        shared_worker(simple_gui::simple_gui & p_gui
                     ,const unsigned int & p_id
                     ,const unsigned int & p_width
                     ,const unsigned int & p_height
                     ,const uint32_t & p_color_code
                     ,const unsigned int & p_total_worker
                     ,const unsigned int & p_slot_size
                     );

        /**
         * Computation code
         */
        void specialised_run() override;

        /**
         * Provide some information about thread execution like compare and
         * exchange stats etc
         * @param p_stream stream on which information is displayed
         */
        void report(std::ostream & p_stream) override;

	  private:
	    /**
	     * Number of failed compare and exchange
	     */
	    unsigned int m_fail;

	    /**
	     * Number of compare and exchange
	     */
	    unsigned int m_total;

	    /**
	     * Number of consecutive pixels to compute
	     */
	    unsigned int m_slot_size;

	    /**
	     * Index of pixel to be computed
	     */
	    static std::atomic<uint32_t> m_index;
	};

}


#endif // _SHARED_WORKER_H_
//EOF

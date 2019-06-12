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
#include "worker_factory.h"
#include "horizontal_worker.h"
#include "h_block_worker.h"
#include "shared_worker.h"
#include "quicky_exception.h"

namespace fractal
{
    //-------------------------------------------------------------------------
    worker * worker_factory::create_worker(const std::string & p_type
                                          ,simple_gui::simple_gui & p_gui
                                          ,const unsigned int & p_id
                                          ,const unsigned int & p_width
                                          ,const unsigned int & p_height
                                          ,const uint32_t & p_color_code
                                          ,const unsigned int & p_total_worker
                                          ,const unsigned int & p_slot_size
                                          )
    {
        if("horizontal" == p_type)
        {
            return new horizontal_worker(p_gui,p_id,p_width,p_height,p_color_code,p_total_worker);
        }
        else if("h_block" == p_type)
        {
            return new h_block_worker(p_gui,p_id,p_width,p_height,p_color_code,p_total_worker);
        }
        else if("shared" == p_type)
        {
            return new shared_worker(p_gui,p_id,p_width,p_height,p_color_code,p_total_worker,p_slot_size);
        }
        else
        {
            throw quicky_exception::quicky_logic_exception("worker_factory: Unkown worker type : \""+p_type+"\"",__LINE__,__FILE__);
        }
    }
}
//EOF

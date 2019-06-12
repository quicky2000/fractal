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
#ifndef _H_BLOCK_WORKER_H_
#define _H_BLOCK_WORKER_H_

#include "worker.h"

namespace fractal
{
  class h_block_worker: public worker
  {
  public:
    h_block_worker(simple_gui::simple_gui & p_gui,
		   const unsigned int & p_id,
		   const unsigned int & p_width,
		   const unsigned int & p_height,
		   const uint32_t & p_color_code,
		   const unsigned int & p_total_worker);
    void specialised_run() override;
  private:
  };

}


#endif // _H_BLOCK_WORKER_H_
//EOF

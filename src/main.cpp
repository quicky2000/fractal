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
#include "simple_gui.h"
#include "quicky_exception.h"
#include <thread>
#include <iostream>
#include <atomic>
#include <chrono>
#include <vector>

using namespace fractal;

void periodic_refresh(const std::atomic<bool> & p_stop,simple_gui & p_gui)
{
  std::cout << "Create refresh thread" << std::endl ;
  while(!static_cast<bool>(p_stop))
    {
      p_gui.refresh();
      std::this_thread::sleep_for(std::chrono::duration<int>(1));
      std::cout << "Refresh" << std::endl ;
    }
}

//------------------------------------------------------------------------------
int main(int argc,char ** argv)
{
  simple_gui l_gui;
  unsigned int l_width = 640;
  unsigned int l_height = 480;

  l_gui.createWindow(l_width,l_height);

  // Create color tables
  uint8_t l_component_values[] = {0xFF,0xF,0x0};
  std::vector<uint32_t> l_color_tables;
  for(auto l_iter_red : l_component_values)
    {
      for(auto l_iter_green : l_component_values)
	{
	  for(auto l_iter_blue : l_component_values)
	    {
	      l_color_tables.push_back(l_gui.getColorCode(l_iter_red,l_iter_green,l_iter_blue));
	    }
	}
    }

  l_gui.refresh();
  std::cout << "Hardware concurrency : " << std::thread::hardware_concurrency() << std::endl ;

  worker l_worker("toto worker",l_gui,0,l_width,l_height,l_color_tables[0],1);
  std::cout << "Create worker thread" << std::endl ;
  std::thread l_thread(worker::launch_worker,std::ref(l_worker));

  std::atomic<bool> l_stop(false);
  std::thread l_refresh_thread(periodic_refresh,std::ref(l_stop),std::ref(l_gui));

  std::cout <<"Join worker thread" << std::endl ;
  l_thread.join();

  std::cout <<"Wait 10 seconds" << std::endl ;
  std::this_thread::sleep_for(std::chrono::duration<int>(10));

  std::cout << "Ask to stop" << std::endl ;
  l_stop.store(true,std::memory_order_relaxed);

  std::cout << "Join refresh thread" << std::endl ;
  l_refresh_thread.join();

  return 0;  
}
//EOF

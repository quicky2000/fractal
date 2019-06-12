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
#include "worker_factory.h"
#include "simple_gui.h"
#include "quicky_exception.h"
#include "parameter_manager.h"
#include <thread>
#include <iostream>
#include <atomic>
#include <chrono>
#include <vector>
#include <iomanip>

using namespace fractal;

void periodic_refresh(const std::atomic<bool> & p_stop
                     ,simple_gui::simple_gui & p_gui
                     )
{
    std::cout << "Create refresh thread" << std::endl;
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
    try
    {
        // Defining application command line parameters
        parameter_manager::parameter_manager l_param_manager("fractal.exe", "--", 0);
        parameter_manager::parameter_if l_width_param("width", true);
        parameter_manager::parameter_if l_height_param("height", true);
        parameter_manager::parameter_if l_type_param("type", true);
        parameter_manager::parameter_if l_nb_param("nb", true);
        parameter_manager::parameter_if l_slot_size_param("slot-size", true);

        l_param_manager.add(l_width_param);
        l_param_manager.add(l_height_param);
        l_param_manager.add(l_type_param);
        l_param_manager.add(l_nb_param);
        l_param_manager.add(l_slot_size_param);

        // Treating parameters
        l_param_manager.treat_parameters(argc,argv);
        unsigned int l_width = l_width_param.value_set() ? l_width_param.get_value<uint32_t>() : 1600;
        unsigned int l_height = l_height_param.value_set() ? l_height_param.get_value<uint32_t>() : 1200;
        std::string l_worker_type = l_type_param.value_set() ? l_type_param.get_value<std::string>() : "horizontal";
        unsigned int l_worker_nb = l_nb_param.value_set() ? l_nb_param.get_value<uint32_t>() : std::thread::hardware_concurrency();
        unsigned int l_slot_size = l_slot_size_param.value_set() ? l_slot_size_param.get_value<uint32_t>() : 1;

        simple_gui::simple_gui l_gui;
        l_gui.create_window(l_width, l_height);

        // Create color tables
        std::vector<uint32_t> l_color_tables;
        l_color_tables.push_back(l_gui.get_color_code(0xFF,0xFF,0xFF));
        l_color_tables.push_back(l_gui.get_color_code(0xFF,0x0,0x0));
        l_color_tables.push_back(l_gui.get_color_code(0x0,0xFF,0x0));
        l_color_tables.push_back(l_gui.get_color_code(0x0,0x0,0xFF));
        l_color_tables.push_back(l_gui.get_color_code(0xFF,0xFF,0x0));
        l_color_tables.push_back(l_gui.get_color_code(0xFF,0x0,0xFF));
        l_color_tables.push_back(l_gui.get_color_code(0x0,0xFF,0xFF));
        l_color_tables.push_back(l_gui.get_color_code(0xF0,0x0,0x0));
        l_color_tables.push_back(l_gui.get_color_code(0x0,0xF0,0x0));
        l_color_tables.push_back(l_gui.get_color_code(0x0,0x0,0xF0));

        l_gui.refresh();

        std::cout << "Hardware concurrency : " << l_worker_nb << std::endl ;
        if(l_height % l_worker_nb)
        {
            throw quicky_exception::quicky_logic_exception("Height % number of worker should be 0",__LINE__,__FILE__);
        }
        if(l_width % l_worker_nb)
        {
            throw quicky_exception::quicky_logic_exception("Width % number of worker should be 0",__LINE__,__FILE__);
        }

        // Create workers
        std::vector<worker*> l_workers;
        for(unsigned int l_index = 0 ; l_index < l_worker_nb ; ++l_index)
        {
            worker * l_worker = worker_factory::create_worker(l_worker_type,l_gui,l_index,l_width,l_height,l_color_tables[l_index],l_worker_nb,l_slot_size);
            l_workers.push_back(l_worker);
        }

        // Create threads
        std::vector<std::thread*> l_threads;
        for(unsigned int l_index = 0 ; l_index < l_worker_nb ; ++l_index)
        {
            std::thread * l_thread = new std::thread(worker::launch_worker,std::ref(*(l_workers[l_index])));
            l_threads.push_back(l_thread);
        }

        //  worker l_worker("toto_worker",l_gui,0,l_width,l_height,l_color_tables[0],1);
        //  std::cout << "Create worker thread" << std::endl ;
        //  std::thread l_thread(worker::launch_worker,std::ref(l_worker));

        std::atomic<bool> l_stop(false);
        std::thread l_refresh_thread(periodic_refresh,std::ref(l_stop),std::ref(l_gui));

        // Wait for the end of worker threads
        std::cout <<"Join worker threads" << std::endl ;
        for(auto l_iter: l_threads)
        {
            l_iter->join();
            delete l_iter;
        }

        // Maintain display
        std::cout <<"Wait 3 seconds" << std::endl ;
        std::this_thread::sleep_for(std::chrono::duration<int>(3));

        std::cout << "Ask to stop" << std::endl ;
        l_stop.store(true,std::memory_order_relaxed);

        std::cout << "Join refresh thread" << std::endl ;
        l_refresh_thread.join();

        unsigned int l_total_iter = 0;
        for(auto l_iter: l_workers)
        {
            l_total_iter += l_iter->get_nb_iter();
        }

        for(auto l_iter:l_workers)
        {
            std::cout << l_iter->get_name() << " : " << l_iter->get_nb_pixels() << " pixels and " << l_iter->get_nb_iter() << " iterations representing " << std::setw(4) << std::setprecision(3) << (100.0 *(l_iter->get_nb_iter())) / l_total_iter << "% in " ;
            std::cout << l_iter->get_duration().count() << "s";
            l_iter->report(std::cout);
            std::cout << std::endl ;
        }
        for(auto l_iter:l_workers)
        {
            delete l_iter;
        }
    }
    catch(quicky_exception::quicky_runtime_exception & e)
    {
        std::cout << "ERROR : " << e.what() << std::endl ;
        return(-1);
    }
    catch(quicky_exception::quicky_logic_exception & e)
    {
        std::cout << "ERROR : " << e.what() << std::endl ;
        return(-1);
    }
    return 0;
}
//EOF

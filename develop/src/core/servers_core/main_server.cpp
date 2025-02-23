/*
 * Copyright (c) 2025 Andreas Åkerberg.
 * All rights reserved.
 *
 * This file is part of Forradia World.
 *
 * Licensed under the MIT License (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "main_server.hpp"
#include "core/conf/app_properties.hpp"
#include "socket_server/socket_server.hpp"
#include "web_server/web_server.hpp"

namespace fw {
  volatile sig_atomic_t flag = 0;
  
  void
  sig_int_handler(int signum) {
    flag = 1;
  }
  
  void
  main_server::start() const {
    generate_ws_conn_string();
    
    std::thread t_web_server([]{
                               web_server::get_instance().start();
                           });
    
    std::thread t_socket_server([]{
                                  socket_server::get_instance().start();
                              });
    
    signal(SIGINT, sig_int_handler);
    
    while (!flag) {
      std::cout << "Server started.\n";
      pause();
    }
    
    web_server::get_instance().stop();
    socket_server::get_instance().stop();
    
    t_socket_server.join();
    t_web_server.join();
    
    std::cout << "Game server exited gracefully.\n";
  }
  
  void
  main_server::generate_ws_conn_string() const {
    std::fstream out_file;
    
    auto app_path = std::string(app_properties::get_instance().get_app_path());
    auto full_path_str = std::string(app_path);
    auto last_slash = full_path_str.find_last_of("/");
    auto app_base_path = full_path_str.substr(0, last_slash + 1);
    auto file_path = app_base_path + "../html/js/wsConnString.generated.js";
    
    std::cout <<
        "Try opening file for writing the WS connection string at:\n"
              << file_path << std::endl;
    
    out_file.open(file_path, std::fstream::out | std::fstream::trunc);
    
    if (!out_file) {
      std::cout <<
          "Error opening file for writing the WS connection string.\n";
    }
    
    auto fw_env = std::getenv("FW_ENV");
    
    if (fw_env != nullptr && std::string(fw_env) == "dev") {
      std::cout << "Running in development mode.\n";
      
      out_file << "export const wsConnString = 'ws://localhost:8081';";
      app_properties::get_instance().set_http_port(81);
      app_properties::get_instance().set_sockets_port(8081);
    }
    else {
      std::cout << "Running in production mode.\n";
      
      out_file <<
          "export const wsConnString = 'wss://forradia-world-ws.ngrok.io:443';";
    }
    
    out_file.close();
  }
}

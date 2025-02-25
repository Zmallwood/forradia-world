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

#include "socket_server.hpp"
#include "core/conf/app_properties.hpp"
#include "core/servers_core/socket_server/event_handlers/on_socket_message.hpp"
#include "core/servers_core/socket_server/event_handlers/on_socket_open.hpp"

namespace fw {
using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

void
socket_server::start() {
  std::cout << "Starting socket server.\n";
  
  try {
    // Set logging settings.
    m_server.set_access_channels(websocketpp::log::alevel::none);
    m_server.clear_access_channels(
        websocketpp::log::alevel::frame_payload);
    
    m_server.init_asio();
    
    m_server.set_open_handler(bind(&on_socket_open, &m_server, _1));
    m_server.set_message_handler(
        bind(
            &on_socket_message, &m_server, _1,
            _2));
    
    m_server.listen(app_properties::get_instance().get_sockets_port());
    
    // Start the server accept loop.
    m_server.start_accept();
    
    // Start the ASIO io_service run loop.
    m_server.run();
  }
  catch (websocketpp::exception const& e) {
    std::cout << e.what() << std::endl;
  }
  catch (...) {
    std::cout << "Other exception.\n";
  }
}

void
socket_server::stop() {
  m_server.stop();
}
}

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

#include "on_socket_open.hpp"
#include "core/servers_core/socket_server/socket_clients_manager.hpp"

namespace fw {
void on_socket_open(
    wspp_server* server,
    connection_handle handle) {
  std::cout << std::format(
      "{}: A new client has connected.\n",
      get_current_time());
  
  socket_clients_manager::get_instance().add_socket_client(
      server,
      handle);
}
}

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

#include "socket_clients_manager.hpp"
#include "socket_client.hpp"

namespace fw {
void
socket_clients_manager::add_socket_client(
    wspp_server* server,
    connection_handle handle) {
  auto new_socket_client = std::make_shared<socket_client>(
      server,
      handle);
  
  if (auto shared_ptr = handle.lock()) {
    auto raw_ptr = shared_ptr.get();
    
    m_clients.insert({ raw_ptr, new_socket_client});
  }
}

std::shared_ptr<socket_client>
socket_clients_manager::get_socket_client(
    connection_handle handle) const {
  if (auto shared_ptr = handle.lock()) {
    auto raw_ptr = shared_ptr.get();
    
    if (m_clients.contains(raw_ptr))
      return m_clients.at(raw_ptr);
  }
  
  return nullptr;
}
}

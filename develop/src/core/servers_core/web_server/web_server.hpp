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

#pragma once

namespace fw {
class web_server 
: public singleton<web_server> {
  friend class singleton<web_server>;
  
 public:
  void start();
  
  void stop();
  
 private:
  web_server() = default;
  
  void setup_endpoints();
  
  void start_listen();
  
  // Const
  const std::string k_host_name {"localhost"};
  
  // State
  httplib::Server m_server;
};
}

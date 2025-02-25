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
class app_properties
: public singleton<app_properties> {
  friend class singleton<app_properties>;
    
  public:
    auto get_http_port() const {
      return m_http_port;
    }
    
    void set_http_port(
        int value) {
      m_http_port = value;
    }
    
    void set_sockets_port(
        int value) {
      m_sockets_port = value;
    }
    
    auto get_sockets_port() const {
      return m_sockets_port;
    }
    
    std::string_view get_app_path() const {
      return m_appPath;
    }
    
    void set_app_path(
        std::string_view value) {
      m_appPath = value.data();
    }
    
  private:
    app_properties() = default;
    
    // State
    int m_http_port{ 80 };
    int m_sockets_port{ 8080 };
    std::string m_appPath;
};
}

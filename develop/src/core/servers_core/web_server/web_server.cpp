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

#include "web_server.hpp"
#include "core/conf/app_properties.hpp"

namespace fw {
void
web_server::start() {
  std::cout << "Starting web server.\n";
  
  setup_endpoints();
  
  start_listen();
}

void
web_server::stop() {
  m_server.stop();
}

void
web_server::setup_endpoints() {
  using namespace httplib;
  
  auto app_path = std::string(app_properties::get_instance().get_app_path());
  auto full_path_str = std::string(app_path);
  auto last_slash = full_path_str.find_last_of("/");
  auto app_base_path = full_path_str.substr(0, last_slash + 1);
  
  m_server.Get(
    "/", [this, app_base_path](const Request& req, Response& res){
        std::ifstream t(app_base_path + "../html/index.html");
        std::string str(
            (std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
        
        res.set_content(str, "text/html");
    });
  
  m_server.Get(
    "/js/(.*)", [this, app_base_path](const Request& req, Response& res){
        auto filename = req.matches[1].str();
        std::ifstream t(app_base_path + "../html/js/" + filename);
        std::string str(
            (std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
        
        res.set_content(str, "application/javascript");
    });
  
  m_server.Get(
    "/img/(.*)", [this, app_base_path](const Request& req, Response& res){
        auto filename = req.matches[1].str();
        std::ifstream t(
            app_base_path + "../html/resources/images/" +
            filename);
        std::string str(
            (std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
        
        res.set_content(str, "image/png");
    });
  
  m_server.Get(
    "/stop", [&](const Request& req, Response& res){
        m_server.stop();
    });
}

void
web_server::start_listen() {
  m_server.listen(k_host_name, app_properties::get_instance().get_http_port());
}
}

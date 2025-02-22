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

#include "Web_Server.hpp"

#include "Conf/App_Properties.hpp"

namespace FW
{
    void Web_Server::Start()
    {
        std::cout << "Starting web server.\n";
        
        SetupEndpoints();
        
        StartListen();
    }
    
    void Web_Server::Stop()
    {
        m_server.stop();
    }
    
    void Web_Server::SetupEndpoints()
    {
        using namespace httplib;
        
        auto appPath = std::string(App_Properties::GetInstance().GetAppPath());
        auto fullPathStr = std::string(appPath);
        auto lastSlash = fullPathStr.find_last_of("/");
        auto appBasePath = fullPathStr.substr(0, lastSlash + 1);
        
        m_server.Get(
            "/", [this, appBasePath](const Request& req, Response& res){
                std::ifstream t(appBasePath + "../html/index.html");
                std::string str(
                    (std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
                
                res.set_content(str, "text/html");
            });
        
        m_server.Get(
            "/js/(.*)", [this, appBasePath](const Request& req, Response& res){
                auto filename = req.matches[1].str();
                std::ifstream t(appBasePath + "../html/js/" + filename);
                std::string str(
                    (std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
                
                res.set_content(str, "application/javascript");
            });
        
        m_server.Get(
            "/img/(.*)", [this, appBasePath](const Request& req, Response& res){
                auto filename = req.matches[1].str();
                std::ifstream t(
                    appBasePath + "../html/resources/images/" +
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
    
    void Web_Server::StartListen()
    {
        m_server.listen(k_hostName, App_Properties::GetInstance().GetHTTPPort());
    }
}

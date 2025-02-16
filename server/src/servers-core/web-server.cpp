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

#include "web-server.h"

namespace FW
{
    WebServer::WebServer()
    {
        std::ifstream t("server/html/index.html");
        std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

        m_html = str;
    }

    void WebServer::Start()
    {
        std::cout << "Starting web server.\n";

        SetupEndpoints();

        StartListen();
    }

    void WebServer::Stop()
    {
        m_server.stop();
    }

    void WebServer::SetupEndpoints()
    {
        using namespace httplib;

        m_server.Get("/", [this](const Request& req, Response& res)
            { res.set_content(m_html, "text/html"); });

        m_server.Get("/js/(.*)", [this](const Request& req, Response& res)
            {
                auto filename = req.matches[1].str();
                std::ifstream t("server/html/js/" + filename);
                std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

                res.set_content(str, "application/javascript"); });

        m_server.Get("/img/(.*)", [this](const Request& req, Response& res)
            {
                auto filename = req.matches[1].str();
                std::ifstream t("server/html/resources/images/" + filename);
                std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

                res.set_content(str, "image/png"); });

        m_server.Get("/stop", [&](const Request& req, Response& res)
            { m_server.stop(); });
    }

    void WebServer::StartListen()
    {
        m_server.listen(k_hostName, k_port);
    }
}

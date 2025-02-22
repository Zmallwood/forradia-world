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

#include "Socket_Server.hpp"

#include "Conf/App_Properties.hpp"
#include "OnSocketMessage.hpp"
#include "OnSocketOpen.hpp"

namespace FW
{
    using websocketpp::lib::bind;
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::placeholders::_2;
    
    void Socket_Server::Start()
    {
        std::cout << "Starting socket server.\n";
        
        try
        {
            // Set logging settings.
            m_server.set_access_channels(websocketpp::log::alevel::none);
            m_server.clear_access_channels(
                websocketpp::log::alevel::frame_payload);
            
            m_server.init_asio();
            
            m_server.set_open_handler(bind(&OnSocketOpen, &m_server, _1));
            m_server.set_message_handler(
                bind(
                    &OnSocketMessage, &m_server, _1,
                    _2));
            
            m_server.listen(App_Properties::GetInstance().GetSocketsPort());
            
            // Start the server accept loop.
            m_server.start_accept();
            
            // Start the ASIO io_service run loop.
            m_server.run();
        }
        catch (websocketpp::exception const& e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Other exception.\n";
        }
    }
    
    void Socket_Server::Stop()
    {
        m_server.stop();
    }
}

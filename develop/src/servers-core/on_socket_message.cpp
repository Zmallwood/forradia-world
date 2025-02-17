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

#include "on_socket_message.h"

#include "socket_client.h"
#include "socket_clients_manager.h"
#include "app_properties.h"

namespace FW
{
    void OnSocketMessage(
        WSPPServer* server, ConnectionHandle handle,
        MessagePtr message)
    {
        auto& messageText = message->get_payload();
        
        try
        {
            if (messageText == "FrameFinished")
            {
                auto socketClient =
                    _<SocketClientsManager>().GetSocketClient(handle);
                
                if (socketClient)
                {
                    socketClient->ProcessFrame();
                }
            }
            else if (messageText == "CanvasSize")
            {
                auto parts = Split(messageText, ';');
                auto width = std::stoi(parts[1]);
                auto height = std::stoi(parts[2]);
                
                _<AppProperties>().SetCanvasSize({width, height});
            }
        }
        catch (websocketpp::exception const& e)
        {
            std::cout << std::format("Echo failed because: {}\n", e.what());
        }
    }
}

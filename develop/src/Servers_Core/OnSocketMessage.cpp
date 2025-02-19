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

#include "OnSocketMessage.h"

#include "Socket_Client.h"
#include "Socket_Clients_Manager.h"
#include "Conf/App_Properties.h"
#include "Engine/Image_Info_Store.h"
#include "Input/Keyboard_Input.h"
#include "Engine/Engine.h"
#include "Input/Mouse_Input.h"

namespace FW
{
    void OnSocketMessage(
        WSPP_Server* server, Connection_Handle handle,
        Message_Ptr message)
    {
        auto& messageText = message->get_payload();
        
        try
        {
            auto parts = Split(messageText, ';');
            
            if (parts[0] == "FrameFinished")
            {
                auto socketClient =
                    _<Socket_Clients_Manager>().GetSocketClient(handle);
                
                if (socketClient)
                {
                    socketClient->ProcessFrame();
                }
            }
            else if (parts[0] == "CanvasSize")
            {
                auto width = std::stoi(parts[1]);
                auto height = std::stoi(parts[2]);
                
                _<App_Properties>().SetCanvasSize({width, height});
            }
            else if (parts[0] == "ProvideImageDimensions")
            {
                auto imageName = parts[1];
                auto width = std::stoi(parts[2]);
                auto height = std::stoi(parts[3]);
                _<Image_Info_Store>().AddImageDimensions(
                    imageName,
                    {width, height});
            }
            else if (parts[0] == "KeyPress")
            {
                auto key = std::stoi(parts[1]);
                
                auto socketClient =
                    _<Socket_Clients_Manager>().GetSocketClient(handle);
                
                auto engine = socketClient->GetEngine();
                
                auto keyboardInput = engine->GetKeyboardInput();
                
                keyboardInput->RegisterKeyPress(key);
            }
            else if (parts[0] == "KeyRelease")
            {
                auto key = std::stoi(parts[1]);
                
                auto socketClient =
                    _<Socket_Clients_Manager>().GetSocketClient(handle);
                
                auto engine = socketClient->GetEngine();
                
                auto keyboardInput = engine->GetKeyboardInput();
                
                keyboardInput->RegisterKeyRelease(key);
            }
            else if (parts[0] == "MouseButtonPress")
            {
                auto buttonCode = std::stoi(parts[1]);
                auto button = static_cast<Mouse_Buttons>(buttonCode);

                _<Mouse_Input>().RegisterButtonPress(button);
            }
            else if (parts[0] == "MouseButtonRelease")
            {
                auto buttonCode = std::stoi(parts[1]);
                auto button = static_cast<Mouse_Buttons>(buttonCode);

                _<Mouse_Input>().RegisterButtonRelease(button);
            }
        }
        catch (websocketpp::exception const& e)
        {
            std::cout << std::format("Echo failed because: {}\n", e.what());
        }
    }
}

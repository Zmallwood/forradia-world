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
        
        constexpr auto k_frameFinished = Hash("FrameFinished");
        constexpr auto k_canvasSize = Hash("CanvasSize");
        constexpr auto k_provideImageDimensions = Hash("ProvideImageDimensions");
        constexpr auto k_keyPress = Hash("KeyPress");
        constexpr auto k_keyRelease = Hash("KeyRelease");
        constexpr auto k_mouseButtonPress = Hash("MouseButtonPress");
        constexpr auto k_mouseButtonRelease = Hash("MouseButtonRelease");
        
        try
        {
            auto parts = Split(messageText, ';');
            
            auto messageCode = Hash(parts[0]);
            
            switch(messageCode)
            {
            case k_frameFinished:
            {
                auto socketClient =
                    _<Socket_Clients_Manager>().GetSocketClient(handle);
                
                if (socketClient)
                {
                    socketClient->ProcessFrame();
                }
            }
                
            break;
                
            case k_canvasSize:
            {
                auto width = std::stoi(parts[1]);
                auto height = std::stoi(parts[2]);
                
                _<App_Properties>().SetCanvasSize({width, height});
            }
                
            break;
                
            case k_provideImageDimensions:
            {
                auto imageName = parts[1];
                auto width = std::stoi(parts[2]);
                auto height = std::stoi(parts[3]);
                _<Image_Info_Store>().AddImageDimensions(
                    imageName,
                    {width, height});
            }
                
            break;
                
            case k_keyPress:
            {
                auto key = std::stoi(parts[1]);
                
                auto socketClient =
                    _<Socket_Clients_Manager>().GetSocketClient(handle);
                
                auto engine = socketClient->GetEngine();
                
                auto keyboardInput = engine->GetKeyboardInput();
                
                keyboardInput->RegisterKeyPress(key);
            }
                
            break;
                
            case k_keyRelease:
            {
                auto key = std::stoi(parts[1]);
                
                auto socketClient =
                    _<Socket_Clients_Manager>().GetSocketClient(handle);
                
                auto engine = socketClient->GetEngine();
                
                auto keyboardInput = engine->GetKeyboardInput();
                
                keyboardInput->RegisterKeyRelease(key);
            }
                
            break;
                
            case k_mouseButtonPress:
            {
                auto buttonCode = std::stoi(parts[1]);
                auto button = static_cast<Mouse_Buttons>(buttonCode);
                
                _<Mouse_Input>().RegisterButtonPress(button);
            }
                
            break;
                
            case k_mouseButtonRelease:
            {
                auto buttonCode = std::stoi(parts[1]);
                auto button = static_cast<Mouse_Buttons>(buttonCode);
                
                _<Mouse_Input>().RegisterButtonRelease(button);
            }
                
            break;
                
            }
        }
        catch (websocketpp::exception const& e)
        {
            std::cout << std::format("Echo failed because: {}\n", e.what());
        }
    }
}

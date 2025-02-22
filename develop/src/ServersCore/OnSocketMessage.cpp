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

#include "OnSocketMessage.hpp"

#include "SocketClient.hpp"
#include "SocketClientsManager.hpp"
#include "Conf/AppProperties.hpp"
#include "Engine/ImageInfoStore.hpp"
#include "Input/KeyboardInput.hpp"
#include "Input/MouseInput.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Graphics.hpp"
#include "Input/MouseInput.hpp"

namespace FW
{
    void OnSocketMessage(
        WSPPServer* server, ConnectionHandle handle,
        MessagePtr message)
    {
        auto& messageText = message->get_payload();
        
        constexpr auto k_frameFinished = Hash("FrameFinished");
        constexpr auto k_canvasSize = Hash("CanvasSize");
        constexpr auto k_provideImageDimensions =
            Hash("ProvideImageDimensions");
        constexpr auto k_keyPress = Hash("KeyPress");
        constexpr auto k_keyRelease = Hash("KeyRelease");
        constexpr auto k_mouseButtonPress = Hash("MouseButtonPress");
        constexpr auto k_mouseButtonRelease = Hash("MouseButtonRelease");
        constexpr auto k_mouseMove = Hash("MouseMove");
        
        try
        {
            auto parts = Split(messageText, ';');
            
            auto messageCode = Hash(parts[0]);
            
            switch(messageCode)
            {
            case k_frameFinished:
            {
                auto socketClient =
                    SocketClientsManager::GetInstance().GetSocketClient(handle);

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

                auto socketClient =
                    SocketClientsManager::GetInstance().GetSocketClient(handle);
                
                auto engine = socketClient->GetEngine();
                
                auto graphics = engine->GetGraphics();
                
                graphics->SetCanvasSize({width, height});
            }
                
            break;
                
            case k_provideImageDimensions:
            {
                auto imageName = parts[1];
                auto width = std::stoi(parts[2]);
                auto height = std::stoi(parts[3]);
                ImageInfoStore::GetInstance().AddImageDimensions(
                    imageName,
                    {width, height});
            }
                
            break;
                
            case k_keyPress:
            {
                auto key = std::stoi(parts[1]);
                
                auto socketClient =
                    SocketClientsManager::GetInstance().GetSocketClient(handle);
                
                auto engine = socketClient->GetEngine();
                
                auto keyboardInput = engine->GetKeyboardInput();
                
                keyboardInput->RegisterKeyPress(key);
            }
                
            break;
                
            case k_keyRelease:
            {
                auto key = std::stoi(parts[1]);
                
                auto socketClient =
                    SocketClientsManager::GetInstance().GetSocketClient(handle);
                
                auto engine = socketClient->GetEngine();
                
                auto keyboardInput = engine->GetKeyboardInput();
                
                keyboardInput->RegisterKeyRelease(key);
            }
                
            break;
                
            case k_mouseButtonPress:
            {
                auto buttonCode = std::stoi(parts[1]);
                auto button = static_cast<MouseButtons>(buttonCode);

                auto socketClient =
                    SocketClientsManager::GetInstance().GetSocketClient(handle);

                auto engine = socketClient->GetEngine();

                auto mouseInput = engine->GetMouseInput();
                
                mouseInput->RegisterButtonPress(button);
            }
                
            break;
                
            case k_mouseButtonRelease:
            {
                auto buttonCode = std::stoi(parts[1]);
                auto button = static_cast<MouseButtons>(buttonCode);

                auto socketClient =
                    SocketClientsManager::GetInstance().GetSocketClient(handle);

                auto engine = socketClient->GetEngine();

                auto mouseInput = engine->GetMouseInput();
                
                mouseInput->RegisterButtonRelease(button);
            }
                
            break;
                
            case k_mouseMove:
            {
                auto x = std::stoi(parts[1]);
                auto y = std::stoi(parts[2]);
                
                auto socketClient =
                    SocketClientsManager::GetInstance().GetSocketClient(handle);
                
                auto engine = socketClient->GetEngine();
                
                auto graphics = engine->GetGraphics();
                
                auto canvasSize = graphics->GetCanvasSize();
                
                auto xNorm = static_cast<float>(x) / canvasSize.w;
                auto yNorm = static_cast<float>(y) / canvasSize.h;

                auto mouseInput = engine->GetMouseInput();
                
                mouseInput->SetMousePosition({xNorm, yNorm});
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

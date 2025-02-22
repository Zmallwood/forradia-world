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

#include "SocketClientsManager.hpp"

#include "SocketClient.hpp"

namespace FW
{
    void Socket_Clients_Manager::AddSocketClient(
        WSPP_Server* server,
        Connection_Handle handle)
    {
        auto newSocketClient = std::make_shared<Socket_Client>(
            server,
            handle);
        
        if (auto sharedPtr = handle.lock())
        {
            auto rawPtr = sharedPtr.get();
            
            m_clients.insert({ rawPtr, newSocketClient });
        }
    }
    
    std::shared_ptr<Socket_Client> Socket_Clients_Manager::GetSocketClient(
        Connection_Handle handle) const
    {
        if (auto sharedPtr = handle.lock())
        {
            auto rawPtr = sharedPtr.get();
            
            if (m_clients.contains(rawPtr))
            {
                return m_clients.at(rawPtr);
            }
        }
        
        return nullptr;
    }
}

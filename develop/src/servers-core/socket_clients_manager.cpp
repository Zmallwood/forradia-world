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

#include "socket_clients_manager.h"
#include "socket_client.h"

namespace FW
{
    void SocketClientsManager::AddSocketClient(server* server, connection_hdl handle)
    {
        auto newSocketClient = std::make_shared<SocketClient>(server, handle);

        if (auto sharedPtr = handle.lock())
        {
            auto rawPtr = sharedPtr.get();

            m_clients.insert({ rawPtr, newSocketClient });
        }
    }

    std::shared_ptr<SocketClient> SocketClientsManager::GetSocketClient(connection_hdl handle) const
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

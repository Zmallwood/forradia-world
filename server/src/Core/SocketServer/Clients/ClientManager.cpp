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

#include "ClientManager.hpp"
#include "Client.hpp"

namespace FW
{
    void ClientManager::AddClient(connection_hdl* handle)
    {
        auto newClient = std::make_shared<Client>();
        m_clients.insert({ handle, newClient });
    }

    std::shared_ptr<Client> ClientManager::GetClient(connection_hdl* handle) const
    {
        if (m_clients.contains(handle))
        {
            return m_clients.at(handle);
        }

        return nullptr;
    }
}

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

#include "graphics.h"

namespace FW
{
    Graphics::Graphics(WSPPServer* server, ConnectionHandle handle)
        : m_server(server)
        , m_handle(handle)
    {}
    
    void Graphics::ClearCanvas() const
    {
        m_server->send(
            m_handle, "Clear;0;150;255;",
            websocketpp::frame::opcode::TEXT);
    }
    
    void Graphics::PresentCanvas() const
    {
        m_server->send(m_handle, "Present", websocketpp::frame::opcode::TEXT);
    }
    
    void Graphics::DrawImage(std::string_view imageName, float x, float y,
                             float w,
                             float h) const
    {
        m_server->send(
            m_handle,
            "DrawImage;" + std::string(imageName) + ";" + std::to_string(x) +
            ";" +
            std::to_string(y) + ";" + std::to_string(w) + ";" +
            std::to_string(h) +
            ";", websocketpp::frame::opcode::TEXT);
    }
    
    void Graphics::DrawText(std::string_view text, float x, float y) const
    {
        m_server->send(
            m_handle,
            "DrawText;" + std::string(text) + ";" + std::to_string(x) + ";" +
            std::to_string(y) + ";", websocketpp::frame::opcode::TEXT);
    }
}

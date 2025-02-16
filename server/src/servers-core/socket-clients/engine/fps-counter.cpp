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

#include "fps-counter.h"

namespace FW
{
    void FPSCounter::Update()
    {
        auto now = GetTicks();

        if (now > m_ticksLastUpdate + 1000)
        {
            m_fps = m_framesCount;
            m_framesCount = 0;
            m_ticksLastUpdate = now;
        }

        m_framesCount++;
    }

    void FPSCounter::Render(server* server, websocketpp::connection_hdl handle) const
    {
        server->send(handle, "draw_text;FPS: " + std::to_string(m_fps) + ";0.9;0.05;", websocketpp::frame::opcode::TEXT);
    }
}

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

#include "engine.h"
#include "fps-counter.h"

namespace FW
{
    Engine::Engine()
        : m_fpsCounter(std::make_shared<FPSCounter>())
    {
    }

    void Engine::ProcessFrame(server* server, websocketpp::connection_hdl handle)
    {
        m_fpsCounter->Update();

        server->send(handle, "clear;0;150;255;", websocketpp::frame::opcode::TEXT);
        server->send(handle, "draw_image;default-scene-background;0.0;0.0;1.0;1.0;", websocketpp::frame::opcode::TEXT);

        m_fpsCounter->Render(server, handle);

        server->send(handle, "present", websocketpp::frame::opcode::TEXT);
    }
}

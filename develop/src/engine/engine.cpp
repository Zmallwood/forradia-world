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
#include "scene-manager.h"
#include "graphics.h"

namespace FW
{
    Engine::Engine(std::shared_ptr<Graphics> graphics)
        : m_fpsCounter(std::make_shared<FPSCounter>())
        , m_sceneManager(std::make_shared<SceneManager>())
        , m_graphics(graphics)
    {
    }

    void Engine::ProcessFrame()
    {
        auto server = m_graphics->GetServer();
        auto handle = m_graphics->GetHandle();

        m_sceneManager->UpdateCurrentScene();
        m_fpsCounter->Update();

        m_graphics->ClearCanvas();

        server->send(handle, "DrawImage;default-scene-background;0.0;0.0;1.0;1.0;", websocketpp::frame::opcode::TEXT);
        server->send(handle, "DrawImage;forradia-world-logo;0.3;0.1;0.4;0.4;", websocketpp::frame::opcode::TEXT);

        m_sceneManager->RenderCurrentScene();
        m_fpsCounter->Render(server, handle);

        m_graphics->PresentCanvas();
    }
}

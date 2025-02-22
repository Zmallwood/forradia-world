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

#include "Engine.hpp"

#include "FPS_Counter.hpp"
#include "Graphics.hpp"
#include "Scene_Manager.hpp"
#include "Input/Keyboard_Input.hpp"
#include "Input/Mouse_Input.hpp"
#include "Cursor.hpp"

namespace FW
{
    Engine::Engine(std::shared_ptr<Graphics> graphics)
        : m_keyboardInput(std::make_shared<Keyboard_Input>())
        , m_mouseInput(std::make_shared<Mouse_Input>())
        , m_graphics(graphics)
        , m_sceneManager(std::make_shared<Scene_Manager>(
                             *graphics,
                             *m_keyboardInput, *m_mouseInput))
        , m_fpsCounter(std::make_shared<FPS_Counter>(*graphics))
        , m_cursor(std::make_shared<Cursor>(*m_mouseInput, *graphics))
    {}
    
    void Engine::Initialize()
    {
        m_sceneManager->InitializeScenes();
    }
    
    void Engine::ProcessFrame()
    {
        m_cursor->Reset();
        
        m_sceneManager->UpdateCurrentScene();
        m_fpsCounter->Update();
        
        m_graphics->ClearCanvas();
        m_sceneManager->RenderCurrentScene();
        m_fpsCounter->Render();
        m_cursor->Render();
        m_graphics->PresentCanvas();
    }
}

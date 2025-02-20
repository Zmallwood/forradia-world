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

#include "I_Scene.h"

#include "GUI_Core/GUI.h"

namespace FW
{
    I_Scene::I_Scene(Graphics& graphics,
                     Scene_Manager& sceneManager,
                     Keyboard_Input& keyboardInput,
                     Mouse_Input& mouseInput)
        : m_graphics(graphics),
        m_sceneManager(sceneManager),
        m_keyboardInput(keyboardInput),
        m_mouseInput(mouseInput),
        m_gui(std::make_shared<GUI>(graphics))
    {}
    
    void I_Scene::Update()
    {
        m_gui->Update();
        UpdateDerived();
    }
    
    void I_Scene::Render() const
    {
        RenderDerived();
        m_gui->Render();
    }
}

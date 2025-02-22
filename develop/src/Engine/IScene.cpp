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

#include "IScene.hpp"

#include "GUICore/GUI.hpp"

namespace FW
{
    IScene::IScene(Graphics& graphics,
                     SceneManager& sceneManager,
                     KeyboardInput& keyboardInput,
                     MouseInput& mouseInput)
        : m_graphics(graphics),
        m_sceneManager(sceneManager),
        m_keyboardInput(keyboardInput),
        m_mouseInput(mouseInput),
        m_gui(std::make_shared<GUI>(graphics))
    {}
    
    void IScene::Update()
    {
        m_gui->Update();
        UpdateDerived();
    }
    
    void IScene::Render() const
    {
        RenderDerived();
        m_gui->Render();
    }
}

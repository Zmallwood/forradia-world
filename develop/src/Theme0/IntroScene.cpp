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

#include "IntroScene.hpp"

#include "Engine/Graphics.hpp"
#include "GUICore/GUI.hpp"
#include "GUICore/GUILabel.hpp"
#include "Input/KeyboardInput.hpp"
#include "Input/MouseInput.hpp"
#include "Engine/SceneManager.hpp"

namespace FW
{
    void IntroScene::Initialize()
    {
        m_startTextComponent = GetGUI()->AddComponent(
            std::make_shared<GUILabel>(
                GetGraphicsRef(),
                "Press to start",
                0.5f, 0.5f, true));
    }
    
    void IntroScene::UpdateDerived()
    {
        if (GetKeyboardInputRef().AnyKeyIsPressedPickResult() ||
            GetMouseInputRef().AnyButtonIsPressed())
        {
            GetSceneManagerRef().ChangeScene("main-menu-scene");
        }
        
        auto startTextVisible = GetTicks() % 1200 > 600;
        
        m_startTextComponent->SetVisible(startTextVisible);
    }
    
    void IntroScene::RenderDerived() const
    {
        GetGraphicsRef().DrawBackground("DefaultSceneBackground");
        GetGraphicsRef().DrawImage(
            "ForradiaWorldLogo", 0.3f, 0.1f, 0.4f,
            -1.0f);
    }
}

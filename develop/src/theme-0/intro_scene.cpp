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

#include "intro_scene.h"

#include "engine/graphics.h"
#include "gui-core/gui.h"
#include "gui-core/gui_label.h"

namespace FW
{
    IntroScene::IntroScene()
    {
        m_startTextComponent = GetGUI()->AddComponent(
            std::make_shared<GUILabel>(
                "Press to start",
                0.5f, 0.5f));
    }
    
    void IntroScene::UpdateDerived()
    {
        auto startTextVisible = GetTicks() % 1200 > 600;
        
        m_startTextComponent->SetVisible(startTextVisible);
    }
    
    void IntroScene::RenderDerived(std::shared_ptr<Graphics> graphics) const
    {
        graphics->DrawBackground("default-scene-background");
        graphics->DrawImage("forradia-world-logo", 0.3f, 0.1f, 0.4f, -1.0f);
    }
}

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

#include "Main_Menu_Scene.h"

#include "Engine/Graphics.h"
#include "GUI_Core/GUI.h"
#include "GUI_Core/GUI_Panel.h"

namespace FW
{
    void Main_Menu_Scene::Initialize()
    {
        GetGUI()->AddComponent(
            std::make_shared<GUI_Panel>(
                GetGraphicsRef(),
                0.3f, 0.4f, 0.4f, 0.4f));
    }
    
    void Main_Menu_Scene::UpdateDerived()
    {}
    
    void Main_Menu_Scene::RenderDerived() const
    {
        GetGraphicsRef().DrawBackground("DefaultSceneBackground");
        GetGraphicsRef().DrawImage(
            "ForradiaWorldLogo", 0.35f, 0.05f, 0.3f,
            -1.0f);
    }
}

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

#include "GUI_Label.h"

#include "Engine/Graphics.h"

namespace FW
{
    GUI_Label::GUI_Label(std::string_view text, float x, float y,
                         bool centerAlign)
        : GUI_Component(x, y), m_text(text), m_centerAlign(centerAlign)
    {}
    
    void GUI_Label::RenderDerived(Graphics& graphics) const
    {
        auto position = GetPosition();
        
        graphics.DrawText(
            m_text, position.x, position.y,
            Colors::Wheat, m_centerAlign);
    }
}

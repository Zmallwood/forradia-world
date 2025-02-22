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

#include "GUIButton.hpp"

#include "Engine/Graphics.hpp"
#include "Input/MouseInput.hpp"

namespace FW
{
    GUIButton::GUIButton(const Graphics& graphics, MouseInput& mouseInput, std::string_view text, std::function<void()> action, float x, float y, float w, float h)
        : GUIComponent(graphics, x, y), m_mouseInput(mouseInput), m_text(text), m_action(action), m_size({w, h})
    {
    }

    void GUIButton::UpdateDerived() {
        auto bounds = GetBounds();
        auto mousePosition = m_mouseInput.GetMousePosition();

        if (bounds.Contains(mousePosition))
        {
            if (m_mouseInput.GetLeftMouseButtonRef().GetIsPressed())
            {
                m_action();
            }
        }
    }

    void GUIButton::RenderDerived() const {

        auto bounds = GetBounds();

        GetGraphicsRef().DrawImage(
            "GUIButtonDefaultBackground", bounds.x, bounds.y, bounds.w,
            bounds.h);
        }

    RectF GUIButton::GetBounds() const {
        auto position = GetPosition();

        return {position.x, position.y, m_size.w, m_size.h};
    }
}

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

#pragma once

#include "GUIComponent.hpp"

namespace FW
{
    class MouseInput;

    class GUIButton : public GUIComponent
    {
        public:
            GUIButton(const Graphics& graphics, MouseInput& mouseInput, std::string_view text, std::function<void()> action, float x, float y, float w, float h);

            void UpdateDerived() override;

            void RenderDerived() const override;

        private:
            RectF GetBounds() const;

            // State
            SizeF m_size {0.0f, 0.0f};
            std::string m_text;
            std::function<void()> m_action;

            // Dependencies
            MouseInput& m_mouseInput;
    };
}

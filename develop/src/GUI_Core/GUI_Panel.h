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

#include "GUI_Component.h"

namespace FW
{
    class GUI_Panel : public GUI_Component
    {
      public:
        GUI_Panel(const Graphics& graphics, float x, float y, float w, float h);
        
        virtual void RenderDerived() const override;
        
      private:
        // Const
        const float k_borderWidth {0.03f};
        
        // State
        Size_F m_size {0.0f, 0.0f};
    };
}

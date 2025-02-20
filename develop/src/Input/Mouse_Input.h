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

#include "Mouse_Button.h"
#include "Mouse_Buttons.h"

namespace FW
{
    class Mouse_Input
    {
      public:
        void RegisterButtonPress(Mouse_Buttons button);
        
        void RegisterButtonRelease(Mouse_Buttons button);
        
        bool AnyButtonIsPressed() const;
        
        auto& GetLeftMouseButtonRef()
        {
            return m_leftMouseButton;
        }
        
        auto& GetRightMouseButtonRef()
        {
            return m_leftMouseButton;
        }
        
        auto GetMousePosition() const
        {
            return m_mousePosition;
        }
        
        void SetMousePosition(Point_F value)
        {
            m_mousePosition = value;
        }
        
      private:
        // State
        Mouse_Button m_leftMouseButton;
        Mouse_Button m_rightMouseButton;
        Point_F m_mousePosition {-1.0f, -1.0f};
    };
}

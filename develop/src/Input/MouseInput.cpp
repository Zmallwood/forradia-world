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

#include "MouseInput.hpp"

namespace FW
{
    void MouseInput::RegisterButtonPress(MouseButtons button)
    {
        switch (button)
        {
        case MouseButtons::Left:
        
            m_leftMouseButton.RegisterPress();
            
            break;
            
        case MouseButtons::Right:
        
            m_leftMouseButton.RegisterRelease();
            
            break;
        }
    }
    
    void MouseInput::RegisterButtonRelease(MouseButtons button)
    {
        switch (button)
        {
        case MouseButtons::Left:
        
            m_leftMouseButton.RegisterRelease();
            
            break;
            
        case MouseButtons::Right:
        
            m_leftMouseButton.RegisterRelease();
            
            break;
        }
    }
    
    bool MouseInput::AnyButtonIsPressed() const
    {
        return m_leftMouseButton.GetIsPressed() ||
               m_rightMouseButton.GetIsPressed();
    }
}

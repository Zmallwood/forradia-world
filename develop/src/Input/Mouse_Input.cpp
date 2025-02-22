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

#include "Mouse_Input.hpp"

namespace FW
{
    void Mouse_Input::RegisterButtonPress(Mouse_Buttons button)
    {
        switch (button)
        {
        case Mouse_Buttons::Left:
        
            m_leftMouseButton.RegisterPress();
            
            break;
            
        case Mouse_Buttons::Right:
        
            m_leftMouseButton.RegisterRelease();
            
            break;
        }
    }
    
    void Mouse_Input::RegisterButtonRelease(Mouse_Buttons button)
    {
        switch (button)
        {
        case Mouse_Buttons::Left:
        
            m_leftMouseButton.RegisterRelease();
            
            break;
            
        case Mouse_Buttons::Right:
        
            m_leftMouseButton.RegisterRelease();
            
            break;
        }
    }
    
    bool Mouse_Input::AnyButtonIsPressed() const
    {
        return m_leftMouseButton.GetIsPressed() ||
               m_rightMouseButton.GetIsPressed();
    }
}

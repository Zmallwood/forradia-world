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

#include "Keyboard_Input.h"

namespace FW
{
    void Keyboard_Input::RegisterKeyPress(int key)
    {
        m_pressedKeys.insert(key);
    }
    
    void Keyboard_Input::RegisterKeyRelease(int key)
    {
        m_pressedKeys.erase(key);
    }
    
    bool Keyboard_Input::AnyKeyIsPressedPickResult()
    {
        auto result = m_pressedKeys.size() > 0;
        m_pressedKeys.clear();
        
        return result;
    }
}

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

#include "Cursor_Styles.hpp"

namespace FW
{
    class Graphics;
    class Mouse_Input;
    
    class Cursor
    {
      public:
        Cursor(Mouse_Input& mouseInput, Graphics& graphics);
        
        void Reset();
        
        void Render() const;
        
      private:
        // Const
        const float k_cursorSize {0.05f};
        
        // State
        Cursor_Styles m_currentStyle {Cursor_Styles::Default};
        
        // Dependencies
        Mouse_Input& m_mouseInput;
        Graphics& m_graphics;
    };
}

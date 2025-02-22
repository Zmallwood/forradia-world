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

#include "Cursor.hpp"

#include "Graphics.hpp"
#include "Input/MouseInput.hpp"

namespace FW
{
    Cursor::Cursor(MouseInput& mouseInput, Graphics& graphics)
        : m_mouseInput(mouseInput), m_graphics(graphics)
    {}
    
    void Cursor::Reset()
    {
        m_currentStyle = CursorStyles::Default;
    }
    
    void Cursor::Render() const
    {
        auto mousePosition = m_mouseInput.GetMousePosition();
        
        if (mousePosition.x != -1.0f && mousePosition.y != -1.0)
        {
            auto cursorWidth = k_cursorSize;
            auto cursorHeight = ConvertWidthToHeight(
                m_graphics.GetCanvasSize(),
                cursorWidth);
            
            m_graphics.DrawImage(
                "CursorDefault", mousePosition.x - cursorWidth/2,
                mousePosition.y - cursorHeight/2, cursorWidth, cursorHeight);
        }
    }
}

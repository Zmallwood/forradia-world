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

#include "GUI_Panel.h"

#include "Engine/Graphics.h"

namespace FW
{
    GUI_Panel::GUI_Panel(const Graphics& graphics, float x, float y, float w,
                         float h)
        : GUI_Component(graphics, x, y), m_size({w, h})
    {}
    
    void GUI_Panel::RenderDerived() const
    {
        RenderBackground();
        RenderBorders();
    }
    
    void GUI_Panel::RenderBackground() const
    {
        auto position = GetPosition();
        
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBackground", position.x, position.y,
            m_size.w, m_size.h, true);
    }
    
    void GUI_Panel::RenderBorders() const
    {
        auto p = GetPosition();
        auto s = m_size;
        auto bX = k_borderWidthPx/CalcAspectRatio(GetGraphicsRef().GetCanvasSize());
        auto bY =  ConvertWidthToHeight(GetGraphicsRef().GetCanvasSize(), bX);
        
        // Sides
        auto topBorderRect = Rect_F {p.x, p.y - bY, s.w, bY};
        auto rightBorderRect = Rect_F {p.x + s.w, p.y, bX, s.h};
        auto bottomBorderRect = Rect_F {p.x, p.y + s.h, s.w, bY};
        auto leftBorderRect = Rect_F {p.x - bX, p.y, bX, s.h};
        
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBorderHorizontal", topBorderRect);
        
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBorderVertical", rightBorderRect);
        
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBorderHorizontal", bottomBorderRect);
        
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBorderVertical", leftBorderRect);
        
        // Corners
        auto topBorderCornerTopRightRect = Rect_F {p.x + s.w, p.y - bY, bX, bY};
        auto topBorderCornerBottomRightRect = Rect_F {p.x + s.w, p.y + s.h, bX,
                                                      bY};
        auto topBorderCornerBottomLeftRect = Rect_F {p.x - bX, p.y  + s.h, bX,
                                                     bY};
        auto topBorderCornerTopLeftRect = Rect_F {p.x - bX, p.y - bY, bX, bY};
        
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBorderCornerTopRight", topBorderCornerTopRightRect);
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBorderCornerBottomRight",
            topBorderCornerBottomRightRect);
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBorderCornerBottomLeft",
            topBorderCornerBottomLeftRect);
        GetGraphicsRef().DrawImage(
            "GUIPanelDefaultBorderCornerTopLeft", topBorderCornerTopLeftRect);
        
    }
}

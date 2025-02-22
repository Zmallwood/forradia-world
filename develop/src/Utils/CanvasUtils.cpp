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

#include "CanvasUtils.hpp"

namespace FW
{
    
    float CalcAspectRatio(Size canvasSize)
    {
        if (canvasSize.h)
        {
            return static_cast<float>(canvasSize.w) / canvasSize.h;
        }
        
        return 0.0f;
    }
    
    float ConvertWidthToHeight(Size canvasSize, float width)
    {
        auto aspectRatio = CalcAspectRatio(canvasSize);
        
        return width * aspectRatio;
    }
    
    float ConvertHeightToWidth(Size canvasSize, float height)
    {
        auto aspectRatio = CalcAspectRatio(canvasSize);
        
        return height / aspectRatio;
    }
}

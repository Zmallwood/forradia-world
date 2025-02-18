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

#include "FPS_Counter.h"

#include "Graphics.h"

namespace FW
{
    void FPS_Counter::Update()
    {
        auto now = GetTicks();
        
        if (now > m_ticksLastUpdate + 1000)
        {
            m_fps = m_framesCount;
            m_framesCount = 0;
            m_ticksLastUpdate = now;
        }
        
        m_framesCount++;
    }
    
    void FPS_Counter::Render(std::shared_ptr<Graphics> graphics) const
    {
        graphics->DrawText(std::format("Fps: {}", m_fps), 0.85, 0.05);
    }
}

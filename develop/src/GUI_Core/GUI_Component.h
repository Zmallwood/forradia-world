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

namespace FW
{
    class Graphics;
    
    class GUI_Component
    {
      public:
        GUI_Component() = default;
        
        GUI_Component(float x, float y);
        
        void Update();
        
        void Render(Graphics& graphics) const;
        
        std::shared_ptr<GUI_Component> AddComponent(
            std::shared_ptr<GUI_Component> component);
        
        void SetVisible(bool value)
        {
            m_visible = value;
        }
        
      protected:
        virtual void UpdateDerived()
        {}
        
        virtual void RenderDerived(Graphics& graphics) const
        {}
        
        auto GetPosition() const
        {
            return m_position;
        }
        
      private:
        // State
        std::vector<std::shared_ptr<GUI_Component>> m_childComponents;
        Point_F m_position {0.0f, 0.0f};
        bool m_visible {true};
    };
}

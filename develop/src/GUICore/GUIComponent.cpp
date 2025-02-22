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

#include "GUIComponent.hpp"

namespace FW
{
    GUIComponent::GUIComponent(const Graphics& graphics, float x, float y)
        : m_graphics(graphics), m_position({x, y})
    {}
    
    void GUIComponent::Update()
    {
        if (!m_visible)
        {
            return;
        }
        
        UpdateDerived();
        
        for (auto child : m_childComponents)
        {
            child->Update();
        }
    }
    
    void GUIComponent::Render() const
    {
        if (!m_visible)
        {
            return;
        }
        
        RenderDerived();
        
        for (auto child : m_childComponents)
        {
            child->Render();
        }
    }
    
    std::shared_ptr<GUIComponent> GUIComponent::AddComponent(
        std::shared_ptr<GUIComponent> component)
    {
        m_childComponents.push_back(component);
        
        return component;
    }
}

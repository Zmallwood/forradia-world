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

#include "gui_component.hpp"

namespace fw {
  gui_component::gui_component(
      const graphics& graphics,
      float x,
      float y,
      float w,
      float h) :
  m_graphics(graphics),
  m_position({x, y}),
  m_size({w, h}) {}
  
  void
  gui_component::update() {
    if (!m_visible)
      return;
    
    update_derived();
    
    for (auto child : m_child_components)
      child->update();
  }
  
  void
  gui_component::render() const {
    if (!m_visible)
      return;
    
    render_derived();
    
    for (auto child : m_child_components)
      child->render();
  }
  
  std::shared_ptr<gui_component>
  gui_component::add_component(
      std::shared_ptr<gui_component> component) {
    component->set_parent(shared_from_this());
    m_child_components.push_back(component);
    
    return component;
  }

  point_f gui_component::get_absolute_position() const {
    point_f p {0.0f, 0.0f};

    if (m_parent) {
      p = m_parent->get_position();
    }

    p += get_position();

    return p;
  }
}

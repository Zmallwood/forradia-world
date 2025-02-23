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

#include "gui_label.hpp"
#include "core/graphics/graphics.hpp"

namespace fw {
  gui_label::gui_label(
      const graphics& graphics,
      std::string_view text,
      float x,
      float y,
      bool center_align) :
  gui_component(graphics, x, y),
  m_text(text),
  m_center_align(center_align) {}
  
  void
  gui_label::render_derived() const {
    auto position = get_position();
    
    get_graphics_ref().draw_text(
        m_text, position.x, position.y,
        colors::wheat, m_center_align);
  }
}

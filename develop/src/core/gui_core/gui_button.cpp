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

#include "gui_button.hpp"
#include "core/graphics/graphics.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace fw {
  gui_button::gui_button(
      const graphics& graphics,
      mouse_input& mouse_input,
      std::string_view text,
      std::function<void()> action,
      float x,
      float y,
      float w,
      float h) :
  gui_component(graphics, x, y, w, h), 
  m_mouse_input(mouse_input),
  m_text(text),
  m_action(action) {}

  void gui_button::update_derived() {
    auto bounds = get_absolute_bounds();
    auto mouse_position = m_mouse_input.get_mouse_position();

    if (bounds.contains(mouse_position))
      if (m_mouse_input.get_left_mouse_button_ref().get_is_pressed())
          m_action();
  }

  void gui_button::render_derived() const {
    auto bounds = get_absolute_bounds();
    auto center = bounds.get_center();

    get_graphics_ref().draw_image(
        "GUIButtonDefaultBackground", bounds.x, bounds.y,
        bounds.w, bounds.h);

    get_graphics_ref().draw_text(
        m_text,
        center.x,
        center.y,
        colors::wheat,
        true);
  }
}

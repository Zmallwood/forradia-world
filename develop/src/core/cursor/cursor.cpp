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

#include "cursor.hpp"
#include "core/graphics/graphics.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace fw
{
cursor::cursor(
    mouse_input& mouse_input,
    graphics& graphics)
    : m_mouse_input(mouse_input), m_graphics(graphics) {}

void
cursor::reset() {
  m_current_style = cursor_styles::normal;
}

void
cursor::render() const {
  auto mouse_position = m_mouse_input.get_mouse_position();

  if (mouse_position.x != -1.0f && mouse_position.y != -1.0) {
    auto cursor_width = k_cursor_size;
    auto cursor_height = convert_width_to_height(
        m_graphics.get_canvas_size(),
        cursor_width);
    
    m_graphics.draw_image(
        "CursorDefault", mouse_position.x - cursor_width/2,
        mouse_position.y - cursor_height/2, cursor_width, cursor_height);
  }
}
}

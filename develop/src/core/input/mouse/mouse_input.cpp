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

#include "mouse_input.hpp"

namespace fw {
void
mouse_input::register_button_press(
    mouse_buttons button) {
  switch (button) {
  case mouse_buttons::left:
    m_left_mouse_button.register_press();
    break;
  case mouse_buttons::right:
    m_right_mouse_button.register_press();
    break;
  }
}

void
mouse_input::register_button_release(
    mouse_buttons button) {
  switch (button) {
  case mouse_buttons::left:
    m_left_mouse_button.register_release();
    break;
  case mouse_buttons::right:
    m_right_mouse_button.register_release();
    break;
  }
}

bool
mouse_input::any_button_is_pressed() const {
  return m_left_mouse_button.get_is_pressed() ||
         m_right_mouse_button.get_is_pressed();
}
}

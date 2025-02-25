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
#include "mouse_button.hpp"
#include "mouse_buttons.hpp"

namespace fw {
class mouse_input {
 public:
  void register_button_press(mouse_buttons button);
  
  void register_button_release(mouse_buttons button);
  
  bool any_button_is_pressed() const;
  
  auto& get_left_mouse_button_ref() {
      return m_left_mouse_button;
  }
  
  auto& get_right_mouse_button_ref() {
      return m_right_mouse_button;
  }
  
  auto get_mouse_position() const {
      return m_mouse_position;
  }
  
  void set_mouse_position(point_f value) {
      m_mouse_position = value;
  }
  
 private:
  // State
  mouse_button m_left_mouse_button;
  mouse_button m_right_mouse_button;
  point_f m_mouse_position {-1.0f, -1.0f};
};
}

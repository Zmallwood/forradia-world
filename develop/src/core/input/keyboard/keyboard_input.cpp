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

#include "keyboard_input.hpp"

namespace fw {
  void keyboard_input::register_key_press(int key) {
    m_pressed_keys.insert(key);
  }
  
  void keyboard_input::register_key_release(int key) {
    m_pressed_keys.erase(key);
  }
  
  bool keyboard_input::any_key_is_pressed_pick_result() {
    auto result = m_pressed_keys.size() > 0;
    m_pressed_keys.clear();
    
    return result;
  }
}

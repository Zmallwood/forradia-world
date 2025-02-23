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

#include "i_scene.hpp"
#include "core/gui_core/gui.hpp"

namespace fw {
  i_scene::i_scene(
      graphics& graphics,
      scene_manager& scene_manager,
      keyboard_input& keyboard_input,
      mouse_input& mouse_input) :
  m_graphics(graphics),
  m_scene_manager(scene_manager),
  m_keyboard_input(keyboard_input),
  m_mouse_input(mouse_input),
  m_gui(std::make_shared<gui>(graphics)) {}
  
  void
  i_scene::update() {
    m_gui->update();
    update_derived();
  }
  
  void
  i_scene::render() const {
    render_derived();
    m_gui->render();
  }
}

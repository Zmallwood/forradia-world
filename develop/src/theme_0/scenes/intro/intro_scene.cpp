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

#include "intro_scene.hpp"
#include "core/graphics/graphics.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_label.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/scenes_core/scene_manager.hpp"

namespace fw {
  void
  intro_scene::initialize()
  {
    m_start_text_component = get_gui()->add_component(
        std::make_shared<gui_label>(
            get_graphics_ref(),
            "Press to start",
            0.5f, 0.5f, true));
  }
  
  void
  intro_scene::update_derived() {
    if (get_keyboard_input_ref().any_key_is_pressed_pick_result() ||
        get_mouse_input_ref().any_button_is_pressed())
      get_scene_manager_ref().change_scene("main-menu-scene");
    
    auto start_text_visible = get_ticks() % 1200 > 600;
    
    m_start_text_component->set_visible(start_text_visible);
  }
  
  void
  intro_scene::render_derived() const {
    get_graphics_ref().draw_background("DefaultSceneBackground");
    get_graphics_ref().draw_image(
        "ForradiaWorldLogo", 0.3f, 0.1f, 0.4f,
        -1.0f);
  }
}

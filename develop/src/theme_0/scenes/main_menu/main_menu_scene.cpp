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

#include "main_menu_scene.hpp"
#include "core/graphics/graphics.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_panel.hpp"
#include "core/gui_core/gui_button.hpp"
#include "core/scenes_core/scene_manager.hpp"

namespace fw {
  void
  main_menu_scene::initialize() {
    auto panel = get_gui()->add_component(
      std::make_shared<gui_panel>(
        get_graphics_ref(),
        0.3f, 0.4f, 0.4f, 0.4f));

    panel->add_component(
      std::make_shared<gui_button>(
          get_graphics_ref(),
          get_mouse_input_ref(),
          "Login",
          [this] {
            get_scene_manager_ref().change_scene("main-scene");
          },
          0.3f, 0.3f, 0.1f, 0.05f
          )
      );
  }
  
  void
  main_menu_scene::update_derived() {}
  
  void
  main_menu_scene::render_derived() const {
    get_graphics_ref().draw_background("DefaultSceneBackground");
    get_graphics_ref().draw_image(
      "ForradiaWorldLogo", 0.35f, 0.05f, 0.3f,
      -1.0f);
  }
}

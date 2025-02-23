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

namespace fw {
  class i_scene;
  class graphics;
  class keyboard_input;
  class mouse_input;
  
  class scene_manager {
   public:
    scene_manager(graphics& graphics, keyboard_input& keyboard_input,
                  mouse_input& mouse_input);
    
    void initialize_scenes();
    
    void update_current_scene();
    
    void render_current_scene() const;
    
    void change_scene(std::string_view scene_name);
    
   private:
    void add_scene(
        std::string_view scene_name,
        std::shared_ptr<i_scene> scene);
    
    // State
    int m_current_scene {0};
    std::map<int, std::shared_ptr<i_scene>> m_scenes;

    // Dependencies
    graphics& m_graphics;
    keyboard_input& m_keyboard_input;
    mouse_input& m_mouse_input;
  };
}

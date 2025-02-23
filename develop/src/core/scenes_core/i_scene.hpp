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
  class graphics;
  class gui;
  class scene_manager;
  class keyboard_input;
  class mouse_input;
  
  class i_scene {
   public:
    i_scene(graphics& graphics,
            scene_manager& scene_manager,
            keyboard_input& keyboard_input,
            mouse_input& mouse_input);
    
    virtual void initialize() {}
    
    void update();
    
    void render() const;
    
   protected:
    virtual void update_derived() {}
    
    virtual void render_derived() const {}
    
    auto get_gui() const {
      return m_gui;
    }
    
    const auto& get_graphics_ref() const {
      return m_graphics;
    }
    
    auto& get_scene_manager_ref() {
      return m_scene_manager;
    }
    
    auto& get_keyboard_input_ref() {
      return m_keyboard_input;
    }
    
    auto& get_mouse_input_ref() {
      return m_mouse_input;
    }
    
   private:
    // State
    std::shared_ptr<gui> m_gui;

    // Dependencies
    graphics& m_graphics;
    scene_manager& m_scene_manager;
    keyboard_input& m_keyboard_input;
    mouse_input& m_mouse_input;
  };
}

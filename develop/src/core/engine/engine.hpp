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
  class scene_manager;
  class fps_counter;
  class graphics;
  class keyboard_input;
  class mouse_input;
  class cursor;
  
  class engine {
   public:
    engine(
        std::shared_ptr<graphics> graphics);
    
    void initialize();
    
    void process_frame();
    
    auto get_keyboard_input() const {
        return m_keyboard_input;
    }
    
    auto get_graphics() const {
        return m_graphics;
    }
    
    auto get_mouse_input() const {
        return m_mouse_input;
    }
    
   private:
    // State
    std::shared_ptr<keyboard_input> m_keyboard_input;
    std::shared_ptr<mouse_input> m_mouse_input;
    std::shared_ptr<graphics> m_graphics;
    std::shared_ptr<scene_manager> m_scene_manager;
    std::shared_ptr<fps_counter> m_fps_counter;
    std::shared_ptr<cursor> m_cursor;
  };
}

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
  
  class gui_component
  {
   public:
    gui_component(
        const graphics& graphics,
        float x = 0.0f,
        float y = 0.0f);
    
    void update();
    
    void render() const;
    
    std::shared_ptr<gui_component> add_component(
        std::shared_ptr<gui_component> component);
    
    void set_visible(bool value) {
        m_visible = value;
    }
    
   protected:
    virtual void update_derived() {}
    
    virtual void render_derived() const {}
    
    auto get_position() const {
        return m_position;
    }
    
    const auto& get_graphics_ref() const {
        return m_graphics;
    }
    
   private:
    // State
    std::vector<std::shared_ptr<gui_component>> m_child_components;
    point_f m_position {0.0f, 0.0f};
    bool m_visible {true};
    
    // Dependencies
    const graphics& m_graphics;
  };
}

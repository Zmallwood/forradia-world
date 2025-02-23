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
    : public std::enable_shared_from_this<gui_component>
  {
   public:
    gui_component(
        const graphics& graphics,
        float x = 0.0f,
        float y = 0.0f,
        float w = -1.0f,
        float h = -1.0f);
    
    void update();
    
    void render() const;
    
    std::shared_ptr<gui_component> add_component(
        std::shared_ptr<gui_component> component);
    
    void set_parent(std::shared_ptr<gui_component> value) {
      m_parent = value;
    }
    
    void set_visible(bool value) {
        m_visible = value;
    }

    auto get_position() const {
        return m_position;
    }
    
   protected:
    virtual void update_derived() {}
    
    virtual void render_derived() const {}

    point_f get_absolute_position() const;

    rect_f get_absolute_bounds() const;

    auto get_size() const {
      return m_size;
    }
    
    const auto& get_graphics_ref() const {
        return m_graphics;
    }
    
   private:
    // State
    std::vector<std::shared_ptr<gui_component>> m_child_components;
    point_f m_position {0.0f, 0.0f};
    bool m_visible {true};
    size_f m_size {-1, -1};
    
    // Dependencies
    std::shared_ptr<gui_component> m_parent;
    const graphics& m_graphics;
  };
}

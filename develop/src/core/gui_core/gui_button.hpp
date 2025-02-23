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
#include "gui_component.hpp"

namespace fw {
  class mouse_input;

  class gui_button : public gui_component  {
   public:
    gui_button(
        const graphics& graphics,
        mouse_input& mouse_input,
        std::string_view text,
        std::function<void()> action,
        float x,
        float y,
        float w,
        float h);

    void update_derived() override;

    void render_derived() const override;
 
   private:
    // State
    std::string m_text;
    std::function<void()> m_action;

    // Dependencies
    mouse_input& m_mouse_input;
  };
}

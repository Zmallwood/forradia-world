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
  class gui_panel 
  : public gui_component{
   public:
    gui_panel(
        const graphics& graphics,
        float x,
        float y,
        float w,
        float h);
    
    virtual void render_derived() const override;
    
   private:
    void render_background() const;

    void render_borders() const;

    // Const
    const float k_border_width_px {0.015f};
  };
}

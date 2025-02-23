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

#include "gui_panel.hpp"
#include "core/graphics/graphics.hpp"

namespace fw {
  gui_panel::gui_panel(
      const graphics& graphics,
      float x,
      float y,
      float w,
      float h) : 
      gui_component(graphics, x, y, w, h) {}
  
  void
  gui_panel::render_derived() const {
    render_background();
    render_borders();
  }
  
  void
  gui_panel::render_background() const {
    auto position = get_position();
    auto size = get_size();
    
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBackground", position.x, position.y,
        size.w, size.h, true);
  }
  
  void
  gui_panel::render_borders() const {
    auto p = get_position();
    auto s = get_size();
    auto b_x = k_border_width_px/calc_aspect_ratio(get_graphics_ref().get_canvas_size());
    auto b_y =  convert_width_to_height(get_graphics_ref().get_canvas_size(), b_x);
    
    // Sides
    auto top_border_rect = rect_f {p.x, p.y - b_y, s.w, b_y};
    auto right_border_rect = rect_f {p.x + s.w, p.y, b_x, s.h};
    auto bottom_border_rect = rect_f {p.x, p.y + s.h, s.w, b_y};
    auto left_border_rect = rect_f {p.x - b_x, p.y, b_x, s.h};
    
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBorderHorizontal", top_border_rect);
    
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBorderVertical", right_border_rect);
    
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBorderHorizontal", bottom_border_rect);
    
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBorderVertical", left_border_rect);
    
    // Corners
    auto top_border_corner_top_right_rect = rect_f {p.x + s.w, p.y - b_y, b_x, b_y};
    auto top_border_corner_bottom_right_rect = rect_f {p.x + s.w, p.y + s.h, b_x,
                                                  b_y};
    auto top_border_corner_bottom_left_rect = rect_f {p.x - b_x, p.y  + s.h, b_x,
                                                 b_y};
    auto top_border_corner_top_left_rect = rect_f {p.x - b_x, p.y - b_y, b_x, b_y};
    
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBorderCornerTopRight", top_border_corner_top_right_rect);
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBorderCornerBottomRight",
        top_border_corner_bottom_right_rect);
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBorderCornerBottomLeft",
        top_border_corner_bottom_left_rect);
    get_graphics_ref().draw_image(
        "GUIPanelDefaultBorderCornerTopLeft", top_border_corner_top_left_rect);
  }
}

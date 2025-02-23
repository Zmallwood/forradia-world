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

#include "main_scene.hpp"
#include "core/graphics/graphics.hpp"

namespace fw {
  void
  main_scene::update_derived() {}
  
  void
  main_scene::render_derived() const {
    auto tile_height= 0.09f;
    auto tile_width= convert_height_to_width(get_graphics_ref().get_canvas_size(), tile_height);
    for(auto y = 0; y < 11; y++) {
      for (auto x = 0; x < 11; x++) {
        get_graphics_ref().draw_image("GroundGrass", x*tile_width, y*tile_height, tile_width, tile_height);

        if (x == 5 && y == 5)
          get_graphics_ref().draw_image("Player", x*tile_width, y*tile_height, tile_width, tile_height);
      }
    }
  }
}

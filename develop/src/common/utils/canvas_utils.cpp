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

#include "canvas_utils.hpp"

namespace fw {
  float
  calc_aspect_ratio(
      size canvas_size) {
    if (canvas_size.h)
        return static_cast<float>(canvas_size.w) / canvas_size.h;

    return 0.0f;
  }
  
  float
  convert_width_to_height(
      size canvas_size,
      float width) {
    auto aspect_ratio = calc_aspect_ratio(canvas_size);

    return width * aspect_ratio;
  }
  
  float
  convert_height_to_width(
      size canvas_size,
      float height) {
    auto aspect_ratio = calc_aspect_ratio(canvas_size);

    return height / aspect_ratio;
  }
}

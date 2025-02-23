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

#include "fps_counter.hpp"
#include "core/graphics/graphics.hpp"

namespace fw {
  fps_counter::fps_counter(
      graphics& graphics)
      : m_graphics(graphics) {}
  
  void
  fps_counter::update() {
    auto now = get_ticks();
    
    if (now > m_ticks_last_update + 1000) {
      m_fps = m_frames_count;
      m_frames_count = 0;
      m_ticks_last_update = now;
    }
    
    m_frames_count++;
  }
  
  void
  fps_counter::render() const {
    m_graphics.draw_text(
        std::format("Fps: {}", m_fps),
        0.85,
        0.05,
        colors::black);
  }
}

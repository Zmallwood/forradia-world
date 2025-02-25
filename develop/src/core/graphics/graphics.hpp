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
class graphics {
 public:
  graphics(
      wspp_server& server,
      connection_handle handle);
  
  void clear_canvas() const;
  
  void present_canvas() const;

  void draw_image(
      std::string_view image_name,
      float x,
      float y,
      float w,
      float h,
      bool repeat = false) const;

  void draw_image(
      std::string_view image_name,
      rect_f rect,
      bool repeat = false) const;
  
  void draw_text(
      std::string_view text,
      float x,
      float y,
      color color = colors::wheat,
      bool center_align = false) const;
  
  void draw_background(
      std::string_view image_name 
      ) const;
  
  auto get_canvas_size() const {
      return m_canvas_size;
  }
  
  void set_canvas_size(size value) {
      m_canvas_size = value;
  }
  
 private:
  // State
  size m_canvas_size {0, 0};
  
  // Dependencies
  wspp_server& m_server;
  connection_handle m_handle;
};
}

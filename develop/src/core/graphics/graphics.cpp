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

#include "graphics.hpp"
#include "core/assets/image_info_store.hpp"

namespace fw {
graphics::graphics(
    wspp_server& server,
    connection_handle handle)
    : m_server(server)
    , m_handle(handle) {}

void
graphics::clear_canvas() const {
  m_server.send(
      m_handle, "Clear;0;150;255;",
      websocketpp::frame::opcode::TEXT);
}

void
graphics::present_canvas() const {
  m_server.send(m_handle, "Present", websocketpp::frame::opcode::TEXT);
}

void
graphics::draw_image(
    std::string_view image_name,
    float x,
    float y,
    float w,
    float h,
    bool repeat) const {
  if (w < 0 || h < 0) {
    auto image_dimensions =
        image_info_store::get_instance().get_image_dimensions(image_name);
    auto canvas_aspect_ratio = calc_aspect_ratio(m_canvas_size);
    auto image_aspect_ratio = static_cast<float>(image_dimensions.w)/
                            image_dimensions.h;
    
    if (w < 0) {
      y = y - (h * canvas_aspect_ratio - h) / 2.0f;
      h = h * canvas_aspect_ratio;
      w = h * image_aspect_ratio/canvas_aspect_ratio;
    }
    else if (h < 0) {
      x = x - (w / canvas_aspect_ratio - w) / 2.0f;
      w = w / canvas_aspect_ratio;
      h = w / image_aspect_ratio * canvas_aspect_ratio;
    }
  }
  
  m_server.send(
      m_handle,
      std::format(
          "DrawImage;{};{};{};{};{};{};", 
          image_name, x, y, w, h, repeat),
      websocketpp::frame::opcode::TEXT);
}

void
graphics::draw_image(
    std::string_view image_name,
    rect_f rect,
    bool repeat) const {
  draw_image(
      image_name, rect.x, rect.y, rect.w, rect.h, repeat);
}

void
graphics::draw_text(
    std::string_view text,
    float x,
    float y,
    color color,
    bool center_align) const {
  m_server.send(
      m_handle,
      std::format(
          "DrawText;{};{};{};{};{};{};{};",
          text, x, y, color.r,
          color.g, color.b, center_align),
      websocketpp::frame::opcode::TEXT);
}


void
graphics::draw_background(
    std::string_view image_name 
    ) const {
  if (!image_info_store::get_instance().image_dimensions_exist(image_name)) {
    m_server.send(
        m_handle,
        std::format("RequestImageDimensions;{};", image_name),
        websocketpp::frame::opcode::TEXT);
    return;
  }
  else {
    auto canvas_aspect_ratio = calc_aspect_ratio(m_canvas_size);
    
    auto image_dimensions =
        image_info_store::get_instance().get_image_dimensions(image_name);
    
    auto image_aspect_ratio = static_cast<float>(image_dimensions.w) /
                            image_dimensions.h;
    
    float x, y, w, h;
    
    if (image_aspect_ratio > canvas_aspect_ratio) {
      x = 0.0f;
      w = 1.0f;
      
      h = 1.0f / image_aspect_ratio * canvas_aspect_ratio;
      y = -(1.0f / image_aspect_ratio * canvas_aspect_ratio - 1.0f) / 2.0f;
      
      auto k = (1.0f - h) / 2.0f;
      
      x -= k;
      y -= k;
      w += 2 * k;
      h += 2 * k;
    }
    else {
      x = 0.0f;
      w = 1.0f;
      
      h = 1.0f / image_aspect_ratio * canvas_aspect_ratio;
      y = -(1.0f / image_aspect_ratio * canvas_aspect_ratio - 1.0f) / 2.0f;
    }
    
    m_server.send(
        m_handle,
        std::format("DrawImage;{};{};{};{};{};", image_name, x, y, w, h),
        websocketpp::frame::opcode::TEXT);
  }
}
}

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

#include "image_info_store.hpp"

namespace fw {
  void
  image_info_store::add_image_dimensions(
      std::string_view image_name,
      size dimension) {
    m_image_dimensions[fw::hash(image_name)] = dimension;
  }
  
  bool
  image_info_store::image_dimensions_exist(
      std::string_view image_name) const {
    return m_image_dimensions.contains(fw::hash(image_name));
  }
  
  size
  image_info_store::get_image_dimensions(
      std::string_view image_name) const {
    auto image_name_hash = fw::hash(image_name);

    if (m_image_dimensions.contains(image_name_hash))
        return m_image_dimensions.at(image_name_hash);

    return {-1, -1};
  }
}

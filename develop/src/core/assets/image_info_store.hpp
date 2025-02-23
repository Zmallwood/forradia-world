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
  class image_info_store 
  : public singleton<image_info_store> {
    friend class singleton<image_info_store>;
    
   public:
    void add_image_dimensions(
        std::string_view image_name,
        size dimension);
    
    bool image_dimensions_exist(
        std::string_view image_name) const;
    
    size get_image_dimensions(
        std::string_view image_name) const;
    
   private:
    image_info_store() = default;
    
    // State
    std::map<int, size> m_image_dimensions;
  };
}

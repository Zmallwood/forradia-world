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

namespace FW
{
    class Image_Info_Store : public Singleton<Image_Info_Store>
    {
        friend class Singleton<Image_Info_Store>;
        
      public:
        void AddImageDimensions(std::string_view imageName, Size dimension);
        
        bool ImageDimensionsExists(std::string_view imageName) const;
        
        Size GetImageDimensions(std::string_view imageName) const;
        
      private:
        Image_Info_Store() = default;
        
        // State
        std::map<int, Size> m_imageDimensions;
    };
}

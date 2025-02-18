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

#include "Image_Info_Store.h"

namespace FW
{
    void Image_Info_Store::AddImageDimensions(std::string_view imageName,
                                              Size dimension)
    {
        m_imageDimensions[Hash(imageName)] = dimension;
    }
    
    
    bool Image_Info_Store::ImageDimensionsExists(
        std::string_view imageName) const
    {
        return m_imageDimensions.contains(Hash(imageName));
    }
    
    Size Image_Info_Store::GetImageDimensions(std::string_view imageName) const
    {
        auto imageNameHash = Hash(imageName);
        
        if (m_imageDimensions.contains(imageNameHash))
        {
            return m_imageDimensions.at(imageNameHash);
        }
        
        return {-1, -1};
    }
}

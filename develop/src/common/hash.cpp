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

#include "hash.h"

namespace FW
{
    int Hash(std::string_view text)
    {
        unsigned long hash{ 5381 };                    // Initialize hash to a prime value.
        
        // Iterate through each character of the input string.
        for (size_t i { 0 }; i < text.size(); ++i){
            // Update the hash using a common hash function (djb2).
            hash = 33 * hash + (unsigned char)text[i];
        }
        
        // Return the computed hash as an integer.
        return static_cast<int>(hash);
    }
}

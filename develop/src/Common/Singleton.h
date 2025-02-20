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
    template <typename T>
    class Singleton
    {
      public:
        // Delete copy and move constructors/operators
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(Singleton&&) = delete;
        
        // Access the singleton instance
        static T& GetInstance()
        {
            static std::once_flag flag;
            std::call_once(
                flag, []() {
                    instance_.reset(new T());
                });
            return *instance_;
        }
        
      protected:
        Singleton() = default;
        virtual ~Singleton() = default;
        
      private:
        static inline std::unique_ptr<T> instance_; // Unique instance
    };
}

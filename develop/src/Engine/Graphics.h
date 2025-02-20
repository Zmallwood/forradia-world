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
    class Graphics
    {
      public:
        Graphics(
            WSPP_Server* server,
            Connection_Handle handle);
        
        void ClearCanvas() const;
        
        void PresentCanvas() const;
        
        void DrawImage(
            std::string_view imageName,
            float x,
            float y,
            float w,
            float h,
            bool repeat = false) const;
        
        void DrawText(
            std::string_view text,
            float x,
            float y,
            Color color = Colors::Wheat,
            bool centerAlign = false) const;
        
        void DrawBackground(
            std::string_view imageName
            ) const;
        
        auto GetServer() const
        {
            return m_server;
        }
        
        auto GetHandle() const
        {
            return m_handle;
        }
        
        auto GetCanvasSize() const
        {
            return m_canvasSize;
        }
        
        void SetCanvasSize(Size value)
        {
            m_canvasSize = value;
        }
        
      private:
        // State
        Size m_canvasSize {0, 0};
        
        // Dependencies
        WSPP_Server* m_server{ nullptr };
        Connection_Handle m_handle;
    };
}

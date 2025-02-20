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

#include "Graphics.h"

#include "Utils/Canvas_Utils.h"
#include "Image_Info_Store.h"
#include "Conf/App_Properties.h"

namespace FW
{
    Graphics::Graphics(
        WSPP_Server* server,
        Connection_Handle handle)
        : m_server(server)
        , m_handle(handle)
    {}
    
    void Graphics::ClearCanvas() const
    {
        m_server->send(
            m_handle, "Clear;0;150;255;",
            websocketpp::frame::opcode::TEXT);
    }
    
    void Graphics::PresentCanvas() const
    {
        m_server->send(m_handle, "Present", websocketpp::frame::opcode::TEXT);
    }
    
    void Graphics::DrawImage(
        std::string_view imageName,
        float x,
        float y,
        float w,
        float h,
        bool repeat) const
    {
        if (w < 0 || h < 0)
        {
            auto imageDimensions =
                _<Image_Info_Store>().GetImageDimensions(imageName);
            auto canvasAspectRatio = CalcAspectRatio(m_canvasSize);
            auto imageAspectRatio = static_cast<float>(imageDimensions.w)/
                                    imageDimensions.h;
            
            if (w < 0)
            {
                y = y - (h*canvasAspectRatio - h)/2.0f;
                h = h*canvasAspectRatio;
                w = h*imageAspectRatio/canvasAspectRatio;
            }
            else if (h < 0)
            {
                x = x - (w/canvasAspectRatio - w)/2.0f;
                w = w/canvasAspectRatio;
                h = w/imageAspectRatio*canvasAspectRatio;
            }
        }
        
        m_server->send(
            m_handle,
            std::format(
                "DrawImage;{};{};{};{};{};{};", imageName, x, y, w, h,
                repeat),
            websocketpp::frame::opcode::TEXT);
    }
    
    void Graphics::DrawText(
        std::string_view text,
        float x,
        float y,
        Color color,
        bool centerAlign) const
    {
        m_server->send(
            m_handle,
            std::format(
                "DrawText;{};{};{};{};{};{};{};", text, x, y, color.r,
                color.g, color.b, centerAlign),
            websocketpp::frame::opcode::TEXT);
    }
    
    
    void Graphics::DrawBackground(
        std::string_view imageName
        ) const
    {
        if (!_<Image_Info_Store>().ImageDimensionsExists(imageName))
        {
            m_server->send(
                m_handle,
                std::format("RequestImageDimensions;{};", imageName),
                websocketpp::frame::opcode::TEXT);
            return;
        }
        else
        {
            auto canvasAspectRatio = CalcAspectRatio(m_canvasSize);
            
            auto imageDimensions =
                _<Image_Info_Store>().GetImageDimensions(imageName);
            
            auto imageAspectRatio = static_cast<float>(imageDimensions.w) /
                                    imageDimensions.h;
            
            float x, y, w, h;
            
            if (imageAspectRatio > canvasAspectRatio)
            {
                x = 0.0f;
                w = 1.0f;
                
                h = 1.0f/imageAspectRatio*canvasAspectRatio;
                y = -(1.0f/imageAspectRatio*canvasAspectRatio - 1.0f)/2.0f;
                
                auto k = (1.0f - h)/2.0f;
                
                x -= k;
                y -= k;
                w += 2*k;
                h += 2*k;
            }
            else
            {
                x = 0.0f;
                w = 1.0f;
                
                h = 1.0f/imageAspectRatio*canvasAspectRatio;
                y = -(1.0f/imageAspectRatio*canvasAspectRatio - 1.0f)/2.0f;
            }
            
            m_server->send(
                m_handle,
                std::format("DrawImage;{};{};{};{};{};", imageName, x, y, w, h),
                websocketpp::frame::opcode::TEXT);
        }
    }
}

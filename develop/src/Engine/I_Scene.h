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
    class Graphics;
    class GUI;
    class Scene_Manager;
    class Keyboard_Input;
    
    class I_Scene
    {
      public:
        I_Scene();
        
        void Update(std::shared_ptr<Scene_Manager> sceneManager,
                    std::shared_ptr<Keyboard_Input> keyboardInput);
        
        void Render(std::shared_ptr<Graphics> graphics) const;
        
      protected:
        virtual void UpdateDerived(std::shared_ptr<Scene_Manager> sceneManager,
                                   std::shared_ptr<Keyboard_Input> keyboardInput)
        {}
        
        virtual void RenderDerived(std::shared_ptr<Graphics> graphics) const
        {}
        
        auto GetGUI() const
        {
            return m_gui;
        }
        
      private:
        std::shared_ptr<GUI> m_gui;
    };
}

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
    class SceneManager;
    class KeyboardInput;
    class MouseInput;
    
    class IScene
    {
      public:
        IScene(Graphics& graphics,
                SceneManager& sceneManager,
                KeyboardInput& keyboardInput,
                MouseInput& mouseInput);
        
        virtual void Initialize()
        {}
        
        void Update();
        
        void Render() const;
        
      protected:
        virtual void UpdateDerived()
        {}
        
        virtual void RenderDerived() const
        {}
        
        auto GetGUI() const
        {
            return m_gui;
        }
        
        const auto& GetGraphicsRef() const
        {
            return m_graphics;
        }
        
        auto& GetSceneManagerRef()
        {
            return m_sceneManager;
        }
        
        auto& GetKeyboardInputRef()
        {
            return m_keyboardInput;
        }
        
        auto& GetMouseInputRef()
        {
            return m_mouseInput;
        }
        
      private:
        // State
        std::shared_ptr<GUI> m_gui;

        // Dependencies
        Graphics& m_graphics;
        SceneManager& m_sceneManager;
        KeyboardInput& m_keyboardInput;
        MouseInput& m_mouseInput;
    };
}

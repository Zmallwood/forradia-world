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
    class Scene_Manager;
    class FPS_Counter;
    class Graphics;
    class Keyboard_Input;
    class Mouse_Input;
    class Cursor;
    
    class Engine
    {
      public:
        Engine(std::shared_ptr<Graphics> graphics);
        
        void Initialize();
        
        void ProcessFrame();
        
        auto GetKeyboardInput() const
        {
            return m_keyboardInput;
        }
        
        auto GetGraphics() const
        {
            return m_graphics;
        }
        
        auto GetMouseInput() const
        {
            return m_mouseInput;
        }
        
      private:
        // State
        std::shared_ptr<Keyboard_Input> m_keyboardInput;
        std::shared_ptr<Mouse_Input> m_mouseInput;
        std::shared_ptr<Graphics> m_graphics;
        std::shared_ptr<Scene_Manager> m_sceneManager;
        std::shared_ptr<FPS_Counter> m_fpsCounter;
        std::shared_ptr<Cursor> m_cursor;
    };
}

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

#include "Engine/I_Scene.h"

namespace FW
{
    class GUI_Component;
    
    class Intro_Scene : public I_Scene
    {
      public:
        Intro_Scene();
        
      protected:
        void UpdateDerived(std::shared_ptr<Scene_Manager> sceneManager,
                           std::shared_ptr<Keyboard_Input> keyboardInput,
                           std::shared_ptr<Mouse_Input> mouseInput)
        override;
        
        void RenderDerived(std::shared_ptr<Graphics> graphics) const override;
        
      private:
        // State
        std::shared_ptr<GUI_Component> m_startTextComponent;
    };
}

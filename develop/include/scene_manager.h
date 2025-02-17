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
    class IScene;
    class Graphics;
    
    class SceneManager
    {
      public:
        SceneManager();
        
        void UpdateCurrentScene();

        void RenderCurrentScene(std::shared_ptr<Graphics> graphics) const;

        void ChangeScene(std::string_view sceneName);
        
      private:
        void AddScene(
            std::string_view sceneName,
            std::shared_ptr<IScene> scene);
        
        int m_currentScene{ 0 };
        std::map<int, std::shared_ptr<IScene>> m_scenes;
    };
}

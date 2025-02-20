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

#include "Scene_Manager.h"

#include "Theme_0/Intro_Scene.h"
#include "Theme_0/Main_Menu_Scene.h"
#include "Theme_0/Main_Scene.h"
#include "Theme_0/World_Generation_Scene.h"

namespace FW
{
    Scene_Manager::Scene_Manager()
    {
        AddScene("intro-scene", std::make_shared<Intro_Scene>());
        AddScene("main-menu-scene", std::make_shared<Main_Menu_Scene>());
        AddScene(
            "world-generation-scene",
            std::make_shared<World_Generation_Scene>());
        AddScene("main-scene", std::make_shared<Main_Scene>());
        
        ChangeScene("intro-scene");
    }
    
    void Scene_Manager::UpdateCurrentScene(
        std::shared_ptr<Scene_Manager> sceneManager,
        std::shared_ptr<Keyboard_Input> keyboardInput,
        std::shared_ptr<Mouse_Input> mouseInput)
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene)->Update(sceneManager, keyboardInput, mouseInput);
        }
    }
    
    void Scene_Manager::RenderCurrentScene(
        std::shared_ptr<Graphics> graphics) const
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene)->Render(graphics);
        }
    }
    
    void Scene_Manager::ChangeScene(std::string_view sceneName)
    {
        m_currentScene = Hash(sceneName);
    }
    
    void Scene_Manager::AddScene(
        std::string_view sceneName,
        std::shared_ptr<I_Scene> scene)
    {
        m_scenes.insert({ Hash(sceneName), scene });
    }
}

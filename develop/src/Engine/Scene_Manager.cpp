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

#include "Scene_Manager.hpp"

#include "Theme0/Intro_Scene.hpp"
#include "Theme0/Main_Menu_Scene.hpp"
#include "Theme0/Main_Scene.hpp"
#include "Theme0/World_Generation_Scene.hpp"

namespace FW
{
    Scene_Manager::Scene_Manager(Graphics& graphics,
                                 Keyboard_Input& keyboardInput,
                                 Mouse_Input& mouseInput)
        : m_graphics(graphics), m_keyboardInput(keyboardInput),
        m_mouseInput(mouseInput)
    {}
    
    void Scene_Manager::InitializeScenes()
    {
        AddScene(
            "intro-scene",
            std::make_shared<Intro_Scene>(
                m_graphics, *this, m_keyboardInput,
                m_mouseInput));
        AddScene(
            "main-menu-scene", std::make_shared<Main_Menu_Scene>(
                m_graphics, *this, m_keyboardInput,
                m_mouseInput));
        AddScene(
            "world-generation-scene",
            std::make_shared<World_Generation_Scene>(
                m_graphics, *this, m_keyboardInput,
                m_mouseInput));
        AddScene(
            "main-scene", std::make_shared<Main_Scene>(
                m_graphics, *this, m_keyboardInput,
                m_mouseInput));
        
        ChangeScene("intro-scene");
    }
    
    void Scene_Manager::UpdateCurrentScene()
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene)->Update();
        }
    }
    
    void Scene_Manager::RenderCurrentScene() const
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene)->Render();
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
        scene->Initialize();
        
        m_scenes.insert({ Hash(sceneName), scene });
    }
}

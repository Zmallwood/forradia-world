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

#include "SceneManager.hpp"

#include "Theme0/IntroScene.hpp"
#include "Theme0/MainMenuScene.hpp"
#include "Theme0/MainScene.hpp"
#include "Theme0/WorldGenerationScene.hpp"

namespace FW
{
    SceneManager::SceneManager(Graphics& graphics,
                                 KeyboardInput& keyboardInput,
                                 MouseInput& mouseInput)
        : m_graphics(graphics), m_keyboardInput(keyboardInput),
        m_mouseInput(mouseInput)
    {}
    
    void SceneManager::InitializeScenes()
    {
        AddScene(
            "intro-scene",
            std::make_shared<IntroScene>(
                m_graphics, *this, m_keyboardInput,
                m_mouseInput));
        AddScene(
            "main-menu-scene", std::make_shared<MainMenuScene>(
                m_graphics, *this, m_keyboardInput,
                m_mouseInput));
        AddScene(
            "world-generation-scene",
            std::make_shared<WorldGenerationScene>(
                m_graphics, *this, m_keyboardInput,
                m_mouseInput));
        AddScene(
            "main-scene", std::make_shared<MainScene>(
                m_graphics, *this, m_keyboardInput,
                m_mouseInput));
        
        ChangeScene("intro-scene");
    }
    
    void SceneManager::UpdateCurrentScene()
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene)->Update();
        }
    }
    
    void SceneManager::RenderCurrentScene() const
    {
        if (m_scenes.contains(m_currentScene))
        {
            m_scenes.at(m_currentScene)->Render();
        }
    }
    
    void SceneManager::ChangeScene(std::string_view sceneName)
    {
        m_currentScene = Hash(sceneName);
    }
    
    void SceneManager::AddScene(
        std::string_view sceneName,
        std::shared_ptr<IScene> scene)
    {
        scene->Initialize();
        
        m_scenes.insert({ Hash(sceneName), scene });
    }
}

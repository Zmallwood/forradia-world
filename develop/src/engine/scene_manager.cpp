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

#include "scene_manager.h"
#include "intro_scene.h"
#include "main_menu_scene.h"
#include "main_scene.h"
#include "world_generation_scene.h"

namespace FW
{
    SceneManager::SceneManager()
    {
        AddScene("intro-scene", std::make_shared<IntroScene>());
        AddScene("main-menu-scene", std::make_shared<MainMenuScene>());
        AddScene("world-generation-scene", std::make_shared<WorldGenerationScene>());
        AddScene("main-scene", std::make_shared<MainScene>());

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

    void SceneManager::AddScene(std::string_view sceneName, std::shared_ptr<IScene> scene)
    {
        m_scenes.insert({ Hash(sceneName), scene });
    }
}

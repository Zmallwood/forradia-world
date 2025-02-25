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

#include "scene_manager.hpp"
#include "theme_0/scenes/intro/intro_scene.hpp"
#include "theme_0/scenes/main_menu/main_menu_scene.hpp"
#include "theme_0/scenes/main/main_scene.hpp"
#include "theme_0/scenes/world_generation/world_generation_scene.hpp"

namespace fw {
scene_manager::scene_manager(
    graphics& graphics,
    keyboard_input& keyboard_input,
    mouse_input& mouse_input) :
  m_graphics(graphics),
  m_keyboard_input(keyboard_input),
  m_mouse_input(mouse_input) {}

void
scene_manager::initialize_scenes() {
  add_scene(
      "intro-scene",
      std::make_shared<intro_scene>(
          m_graphics, *this, m_keyboard_input,
          m_mouse_input));
  add_scene(
      "main-menu-scene", std::make_shared<main_menu_scene>(
          m_graphics, *this, m_keyboard_input,
          m_mouse_input));
  add_scene(
      "world-generation-scene",
      std::make_shared<world_generation_scene>(
          m_graphics, *this, m_keyboard_input,
          m_mouse_input));
  add_scene(
      "main-scene", std::make_shared<main_scene>(
          m_graphics, *this, m_keyboard_input,
          m_mouse_input));
  
  change_scene("intro-scene");
}

void
scene_manager::update_current_scene() {
  if (m_scenes.contains(m_current_scene))
    m_scenes.at(m_current_scene)->update();
}

void
scene_manager::render_current_scene() const {
  if (m_scenes.contains(m_current_scene))
    m_scenes.at(m_current_scene)->render();
}

void
scene_manager::change_scene(std::string_view scene_name) {
  m_current_scene = hash(scene_name);
}

void
scene_manager::add_scene(
    std::string_view scene_name,
    std::shared_ptr<i_scene> scene) {
  scene->initialize();
  
  m_scenes.insert({ hash(scene_name), scene });
}
}

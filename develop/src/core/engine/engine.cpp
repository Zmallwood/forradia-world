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

#include "engine.hpp"
#include "core/fps_counter/fps_counter.hpp"
#include "core/graphics/graphics.hpp"
#include "core/scenes_core/scene_manager.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/cursor/cursor.hpp"

namespace fw {
engine::engine(
    std::shared_ptr<graphics> graphics)
: m_keyboard_input(
    std::make_shared<keyboard_input>())
, m_mouse_input (
    std::make_shared<mouse_input>())
, m_graphics(
    graphics)
, m_scene_manager(
    std::make_shared<scene_manager>(
    *graphics,
    *m_keyboard_input, 
    *m_mouse_input))
, m_fps_counter(
    std::make_shared<fps_counter>(
      *graphics))
, m_cursor(
    std::make_shared<cursor>(
      *m_mouse_input,
      *graphics)) {}

void
engine::initialize() {
  m_scene_manager->initialize_scenes();
}

void
engine::process_frame() {
  m_cursor->reset();
  
  m_scene_manager->update_current_scene();
  m_fps_counter->update();
  
  m_graphics->clear_canvas();
  m_scene_manager->render_current_scene();
  m_fps_counter->render();
  m_cursor->render();
  m_graphics->present_canvas();
}
}

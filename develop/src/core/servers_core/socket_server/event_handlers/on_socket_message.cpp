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

#include "on_socket_message.hpp"
#include "core/servers_core/socket_server/socket_client.hpp"
#include "core/servers_core/socket_server/socket_clients_manager.hpp"
#include "core/conf/app_properties.hpp"
#include "core/assets/image_info_store.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/engine/engine.hpp"
#include "core/graphics/graphics.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace fw {
  void
  on_socket_message(
      wspp_server* server,
      connection_handle handle,
      message_ptr message) {
    auto& message_text = message->get_payload();
    
    constexpr auto k_frame_finished = fw::hash("FrameFinished");
    constexpr auto k_canvas_size = fw::hash("CanvasSize");
    constexpr auto k_provide_image_dimensions = fw::hash("ProvideImageDimensions");
    constexpr auto k_key_press = fw::hash("KeyPress");
    constexpr auto k_key_release = fw::hash("KeyRelease");
    constexpr auto k_mouse_button_press = fw::hash("MouseButtonPress");
    constexpr auto k_mouse_button_release = fw::hash("MouseButtonRelease");
    constexpr auto k_mouse_move = fw::hash("MouseMove");
    
    try {
      auto parts = split(message_text, ';');
      auto message_code = fw::hash(parts[0]);
      
      switch(message_code) {
      case k_frame_finished: {
        auto socket_client =
            socket_clients_manager::get_instance().get_socket_client(handle);

        if (socket_client)
          socket_client->process_frame();
      }
      break;
      case k_canvas_size: {
        auto width = std::stoi(parts[1]);
        auto height = std::stoi(parts[2]);

        auto socket_client =
            socket_clients_manager::get_instance().get_socket_client(handle);
        auto engine = socket_client->get_engine();
        auto graphics = engine->get_graphics();
        
        graphics->set_canvas_size({width, height});
      }
      break;
      case k_provide_image_dimensions: {
        auto image_name = parts[1];
        auto width = std::stoi(parts[2]);
        auto height = std::stoi(parts[3]);
        image_info_store::get_instance().add_image_dimensions(
            image_name,
            {width, height});
      }
      break;
      case k_key_press: {
        auto key = std::stoi(parts[1]);
        
        auto socket_client =
            socket_clients_manager::get_instance().get_socket_client(handle);
        auto engine = socket_client->get_engine();
        auto keyboard_input = engine->get_keyboard_input();
        
        keyboard_input->register_key_press(key);
      }
      break;
      case k_key_release: {
        auto key = std::stoi(parts[1]);
        
        auto socket_client =
            socket_clients_manager::get_instance().get_socket_client(handle);
        auto engine = socket_client->get_engine();
        auto keyboard_input = engine->get_keyboard_input();
        
        keyboard_input->register_key_release(key);
      }
      break;
      case k_mouse_button_press: {
        auto button_code = std::stoi(parts[1]);
        auto button = static_cast<mouse_buttons>(button_code);

        auto socket_client =
            socket_clients_manager::get_instance().get_socket_client(handle);
        auto engine = socket_client->get_engine();
        auto mouse_input = engine->get_mouse_input();
        
        mouse_input->register_button_press(button);
      }
      break;
      case k_mouse_button_release: {
        auto button_code = std::stoi(parts[1]);
        auto button = static_cast<mouse_buttons>(button_code);

        auto socket_client =
            socket_clients_manager::get_instance().get_socket_client(handle);
        auto engine = socket_client->get_engine();
        auto mouse_input = engine->get_mouse_input();
        
        mouse_input->register_button_release(button);
      }
      break;
      case k_mouse_move: {
        auto x = std::stoi(parts[1]);
        auto y = std::stoi(parts[2]);
        
        auto socket_client =
            socket_clients_manager::get_instance().get_socket_client(handle);
        auto engine = socket_client->get_engine();
        auto graphics = engine->get_graphics();
        auto canvas_size = graphics->get_canvas_size();
        
        auto x_norm = static_cast<float>(x) / canvas_size.w;
        auto y_norm = static_cast<float>(y) / canvas_size.h;

        auto mouse_input = engine->get_mouse_input();
        
        mouse_input->set_mouse_position({x_norm, y_norm});
      }
      break;
      }
    }
    catch (websocketpp::exception const& e) {
      std::cout << std::format("Echo failed because: {}\n", e.what());
    }
  }
}

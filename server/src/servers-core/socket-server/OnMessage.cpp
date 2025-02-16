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

#include "OnMessage.hpp"
#include "clients/ClientManager.hpp"

namespace FW
{
    void OnMessage(server* server, websocketpp::connection_hdl handle, message_ptr message)
    {
        // std::cout << "OnMessage called with hdl: " << hdl.lock().get()
        //           << " and message: " << msg->get_payload()
        //           << std::endl;

        auto& message_text = message->get_payload();

        if (message_text == "stop-listening")
        {
            server->stop_listening();

            return;
        }

        try
        {
            if (message_text == "frame_finished")
            {
                server->send(handle, "clear;0;150;255;", message->get_opcode());
                server->send(handle, "draw_image;GroundGrass;0.0;0.0;0.5;0.5;", message->get_opcode());
                server->send(handle, "present", message->get_opcode());

                auto client = _<ClientManager>().GetClient(&handle);
            }
        }
        catch (websocketpp::exception const& e)
        {
            std::cout << "Echo failed because: "
                      << "(" << e.what() << ")" << std::endl;
        }
    }
}

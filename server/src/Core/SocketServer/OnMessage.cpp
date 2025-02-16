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

namespace FW
{
    void OnMessage(server* s, websocketpp::connection_hdl hdl, message_ptr msg)
    {
        // std::cout << "OnMessage called with hdl: " << hdl.lock().get()
        //           << " and message: " << msg->get_payload()
        //           << std::endl;

        // Check for a special command to instruct the server to stop listening so
        // it can be cleanly exited.
        if (msg->get_payload() == "stop-listening")
        {
            s->stop_listening();

            return;
        }

        try
        {
            //s->send(hdl, msg->get_payload(), msg->get_opcode());
            s->send(hdl, "clear;0;150;255;", msg->get_opcode());
            s->send(hdl, "draw_image;GroundGrass;0.0;0.0;0.5;0.5;", msg->get_opcode());
            s->send(hdl, "present", msg->get_opcode());
        }
        catch (websocketpp::exception const& e)
        {
            std::cout << "Echo failed because: "
                      << "(" << e.what() << ")" << std::endl;
        }
    }
}

/*
 * Copyright (c) 2025 Andreas Åkerberg.
 * All rights reserved.
 *
 * This file is part of Forradia World.
 *
 * Licensed under the MIT License (the "License");
 * wsyou may not use this file except in compliance with the License.
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

import {image_names} from './image_names.js';
import {process_message} from './process_message.js';

var images = {};

for (const image_name of image_names)
{
    var image = new Image();

    image.src = "./img/" + image_name + ".png";
    images[image_name] = image;
}


var connect = function (port)
{
    var current_buffer = 1;

    const canvas = document.getElementById("canvas_buffer_1");

    const ctx = canvas.getContext("2d");

    ctx.canvas.width = window.innerWidth;
    ctx.canvas.height = window.innerHeight;

    ctx.font = "38px serif";

    var draw_commands = [];

    var ws = new WebSocket("https://forradia-world-ws.ngrok-free.app:" + port);

    ws.onopen = function ()
    {
        ws.send("canvas_size;" + ctx.canvas.width + ";" + ctx.canvas.height); // send a message
    };

    ws.onmessage = function (evt)
    {
        process_message(ws, evt, ctx, draw_commands);
    };

    ws.onclose = function ()
    {
        console.log("Connection closed.");
    };

    document.onkeydown = function (e)
    {
        e = e || window.event;
        ws.send("key_press;" + e.keyCode);
    };

    document.onkeyup = function (e)
    {
        e = e || window.event;
        ws.send("key_release;" + e.keyCode);
    }

    var draw_frame = function ()
    {
        requestAnimationFrame(draw_frame);
        ctx.save();

        for (let cmd of draw_commands)
        {
            eval(cmd);
        }

        ctx.restore();

        if (ws.readyState === WebSocket.OPEN)
        {
            ws.send("frame_finished");
        }
    };

    draw_frame();
};

var init = function ()
{
    connect(443);
};

window.init = init;

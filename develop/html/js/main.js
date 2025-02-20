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

import { ProcessMessage } from './ProcessMessage.js';
import { wsConnString } from './wsConnString.generated.js';

var images = {};

function IsTouchDevice() {
    return window.matchMedia("(pointer: coarse)").matches;
}

function Connect()
{
    const canvas = document.getElementById("canvas_buffer_1");
    const ctx = canvas.getContext("2d");
    
    ctx.canvas.width = window.innerWidth;
    ctx.canvas.height = window.innerHeight;
    ctx.font = "100% sans-serif";
    
    let drawCommands = [];
    
    const ws = new WebSocket(wsConnString);
    
    ws.onopen = function()
    {
        ws.send("CanvasSize;" + ctx.canvas.width + ";" + ctx.canvas.height);     // send a message
    };
    
    ws.onmessage = function(evt)
    {
        ProcessMessage(ws, evt, ctx, images, drawCommands);
    };
    
    ws.onclose = function()
    {
        console.log("Connection closed.");
    };
    
    document.addEventListener(
        "keydown", function(e) {
        if (ws && ws.readyState === WebSocket.OPEN)
        {
            ws.send("KeyPress;" + e.keyCode);
        }
    });
    
    document.addEventListener(
        "keyup", function(e) {
        if (ws && ws.readyState === WebSocket.OPEN)
        {
            ws.send("KeyRelease;" + e.keyCode);
        }
    });
    
    document.addEventListener(
        "mousedown", function(e) {
        if (ws && ws.readyState === WebSocket.OPEN)
        {
            ws.send("MouseButtonPress;" + e.button);
        }
    });
    
    document.addEventListener(
        "mouseup", function(e) {
        if (ws && ws.readyState === WebSocket.OPEN)
        {
            ws.send("MouseButtonRelease;" + e.button);
        }
    });
    
    document.addEventListener(
        "touchstart", function(e) {
        if (ws && ws.readyState === WebSocket.OPEN)
        {
            const leftButtonCode = 0;
            ws.send("MouseButtonPress;" + leftButtonCode);
        }
    });
    
    document.addEventListener(
        "touchend", function(e) {
        if (ws && ws.readyState === WebSocket.OPEN)
        {
            const leftButtonCode = 0;
            ws.send("MouseButtonRelease;" + leftButtonCode);
        }
    });
    
    document.addEventListener(
        "mousemove", function(e) {
        if (ws && ws.readyState === WebSocket.OPEN && !IsTouchDevice())
        {
            ws.send("MouseMove;" + e.clientX + ";" + e.clientY + ";");
        }
    });
    
    var timeout;
    
    window.addEventListener(
        'resize', function() {
        
        clearTimeout(timeout);
        
        timeout = setTimeout(
            function() {
            ctx.canvas.width = window.innerWidth;
            ctx.canvas.height = window.innerHeight;
            ws.send("CanvasSize;" + ctx.canvas.width + ";" + ctx.canvas.height); // send a message
            ctx.font = "100% serif";
        }, 250);
    });
    
    function DrawFrame()
    {
        requestAnimationFrame(DrawFrame);
        ctx.save();
        
        for (const cmd of drawCommands)
        {
            eval(cmd);
        }
        
        ctx.restore();
        
        if (ws.readyState === WebSocket.OPEN)
        {
            ws.send("FrameFinished");
        }
    };
    
    DrawFrame();
};

function Init()
{
    Connect();
};

window.Init = Init;

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

var newDrawCommands = [];

export function ProcessMessage(
    ws,
    evt,
    ctx,
    drawCommands)
{
    var msg = evt.data;
    var parts = msg.split(";");

    switch (parts[0])
    {
        case "clear":
        {
            var r = parts[1];
            var g = parts[2];
            var b = parts[3];

            newDrawCommands.push(
                "ctx.fillStyle = 'rgb(" + r + "," + g + "," + b + ")';",
            );

            newDrawCommands.push(
                "ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);",
            );

            break;
        }
        case "draw_image":
        {
            var imageName = parts[1];

            var x = parts[2];
            var y = parts[3];
            var w = parts[4];
            var h = parts[5];

            var xPx = x * ctx.canvas.width;
            var yPx = y * ctx.canvas.height;
            var wPx = w * ctx.canvas.width;
            var hPx = h * ctx.canvas.height;

            newDrawCommands.push(
                "ctx.drawImage(images['" +
                imageName +
                "'], " +
                xPx +
                "," +
                yPx +
                "," +
                wPx +
                "," +
                hPx +
                ");",
            );

            break;
        }
        case "draw_text":
        {
            var text = parts[1];

            var x = parts[2];
            var y = parts[3];

            var xPx = x * ctx.canvas.width;
            var yPx = y * ctx.canvas.height;

            if (parts.length >= 7)
            {
                var r = parts[4];
                var g = parts[5];
                var b = parts[6];

                newDrawCommands.push(
                    "ctx.fillStyle = 'rgb(" + r + "," + g + "," + b + ")';",
                );
            }
            else
            {
                newDrawCommands.push("ctx.fillStyle = 'rgb(0,0,0)';");
            }

            let metrics = ctx.measureText(text);

            let textHeight =
                metrics.actualBoundingBoxAscent + metrics.actualBoundingBoxDescent;

            var xOffset = 0;

            if (parts.length >= 8)
            {
                var centerAlign = parts[7];

                if (centerAlign == true)
                {
                    var textWidth = ctx.measureText(text).width;
                    xOffset = -textWidth / 2;
                }
            }
            var yOffset = textHeight;

            newDrawCommands.push(
                "ctx.fillText('" +
                text +
                "'," +
                (xPx + xOffset) +
                "," +
                (yPx + yOffset) +
                ");",
            );

            break;
        }
        case "present":
        {
            drawCommands.length = 0;

            for (let entry of newDrawCommands)
            {
                drawCommands.push(entry);
            }

            newDrawCommands.length = 0;

            break;
        }
    }
};

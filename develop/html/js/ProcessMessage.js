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
    images,
    drawCommands)
{
    const msg = evt.data;
    const parts = msg.split(";");
    
    switch (parts[0]){
    case "Clear":
    {
        const r = parts[1];
        const g = parts[2];
        const b = parts[3];
        
        newDrawCommands.push(
            "ctx.fillStyle = 'rgb(" + r + "," + g + "," + b + ")';",
            );
        
        newDrawCommands.push(
            "ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);",
            );
        
        break;
    }
    case "DrawImage":
    {
        const imageName = parts[1];
        
        const x = parts[2];
        const y = parts[3];
        const w = parts[4];
        const h = parts[5];
        
        const xPx = x * ctx.canvas.width;
        const yPx = y * ctx.canvas.height;
        const wPx = w * ctx.canvas.width;
        const hPx = h * ctx.canvas.height;
        
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
    case "DrawText":
    {
        const text = parts[1];
        
        const x = parts[2];
        const y = parts[3];
        
        const xPx = x * ctx.canvas.width;
        const yPx = y * ctx.canvas.height;
        
        if (parts.length >= 7)
        {
            const r = parts[4];
            const g = parts[5];
            const b = parts[6];
            
            newDrawCommands.push(
                "ctx.fillStyle = 'rgb(" + r + "," + g + "," + b + ")';",
                );
        }
        else
        {
            newDrawCommands.push("ctx.fillStyle = 'rgb(0,0,0)';");
        }
        
        const metrics = ctx.measureText(text);
        
        const textHeight =
            metrics.actualBoundingBoxAscent + metrics.actualBoundingBoxDescent;
        
        let xOffset = 0;
        
        if (parts.length >= 8)
        {
            const centerAlign = parts[7];
            
            if (centerAlign == true)
            {
                const textWidth = ctx.measureText(text).width;
                xOffset = -textWidth / 2;
            }
        }
        const yOffset = textHeight;
        
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
    case "RequestImageDimensions":
    {
        const imageName = parts[1];
        
        const image = images[imageName];
        
        var width = image.width;
        var height = image.height;
        
        ws.send(
            "ProvideImageDimensions;" + imageName + ";" + width + ";" +
            height + ";");
        
        break;
    }
    case "Present":
    {
        drawCommands.length = 0;
        
        for (const entry of newDrawCommands){
            drawCommands.push(entry);
        }
        
        newDrawCommands.length = 0;
        
        break;
    }
    }
};

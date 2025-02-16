import {image_names} from './image_names.js';


var new_draw_commands = [];

var process_message = function (
    ws,
    evt,
    ctx,
    draw_commands)
{
    var msg = evt.data;
    var parts = msg.split(";");

    switch (parts[0])
    {
        case "clear":

            var r = parts[1];
            var g = parts[2];
            var b = parts[3];

            new_draw_commands.push(
                "ctx.fillStyle = 'rgb(" + r + "," + g + "," + b + ")';",
            );

            new_draw_commands.push(
                "ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);",
            );

            break;

        case "draw_image":

            var image_name = parts[1];

            var x = parts[2];
            var y = parts[3];
            var w = parts[4];
            var h = parts[5];

            var xpx = x * ctx.canvas.width;
            var ypx = y * ctx.canvas.height;
            var wpx = w * ctx.canvas.width;
            var hpx = h * ctx.canvas.height;

            new_draw_commands.push(
                "ctx.drawImage(images['" +
                image_name +
                "'], " +
                xpx +
                "," +
                ypx +
                "," +
                wpx +
                "," +
                hpx +
                ");",
            );

        break;

        case "draw_text":

            var text = parts[1];

            var x = parts[2];
            var y = parts[3];

            var xpx = x * ctx.canvas.width;
            var ypx = y * ctx.canvas.height;

            if (parts.length >= 7)
            {
                var r = parts[4];
                var g = parts[5];
                var b = parts[6];

                new_draw_commands.push(
                "ctx.fillStyle = 'rgb(" + r + "," + g + "," + b + ")';",
                );
            }
            else
            {
                new_draw_commands.push("ctx.fillStyle = 'rgb(0,0,0)';");
            }

            let metrics = ctx.measureText(text);

            let text_height =
                metrics.actualBoundingBoxAscent + metrics.actualBoundingBoxDescent;

            var x_offset = 0;

            if (parts.length >= 8)
            {
                var center_align = parts[7];

                if (center_align == true)
                {
                    var text_width = ctx.measureText(text).width;
                    x_offset = -text_width / 2;
                }
            }
            var y_offset = text_height;

            new_draw_commands.push(
                "ctx.fillText('" +
                text +
                "'," +
                (xpx + x_offset) +
                "," +
                (ypx + y_offset) +
                ");",
            );

        break;

        case "present":

            draw_commands.length = 0;

            for (let entry of new_draw_commands)
            {
                draw_commands.push(entry);
            }

            new_draw_commands.length = 0;

            break;

        case "redirect":

            ws.close();
            var port = parts[1];
            connect(port);

            break;
    }
};


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
        console.log("socket connection opened properly");
        ws.send("canvas_size;" + ctx.canvas.width + ";" + ctx.canvas.height); // send a message
    };

    ws.onmessage = function (evt)
    {
        process_message(ws, evt, ctx, draw_commands);
    };

    ws.onclose = function ()
    {
        console.log("Connection closed...");
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
        ws.send("frame_finished");
    };

    draw_frame();
};

var init = function ()
{
    connect(443);
};

window.init = init;

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

#include "main-server.h"
#include "socket-server.h"
#include "web-server.h"

namespace FW
{
    volatile sig_atomic_t flag = 0;

    void SigIntHandler(int signum)
    {
        flag = 1;
    }

    void MainServer::Start() const
    {
        GenerateWSConnString();

        std::thread tWebServer([]
            { _<WebServer>().Start(); });

        std::thread tSocketServer([]
            { _<SocketServer>().Start(); });

        signal(SIGINT, SigIntHandler);

        while (!flag)
        {
            std::cout << "Server started.\n";
            pause();
        }

        _<WebServer>().Stop();
        _<SocketServer>().Stop();

        tSocketServer.join();
        tWebServer.join();

        std::cout << "Game server exited gracefully.\n";
    }

    void MainServer::GenerateWSConnString() const
    {
        std::fstream outFile;

        // The following code is Linux specific to obtain directory of the application file,
        // instead of using the directory from where it was run.
        char buffer[PATH_MAX];
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (len != -1)
        {
            buffer[len] = '\0';
            auto fullPathStr = std::string(buffer);
            auto lastSlash = fullPathStr.find_last_of("/");
            auto appBasePath = fullPathStr.substr(0, lastSlash + 1);
            outFile.open(appBasePath + "../html/js/wsConnString.generated.js", std::fstream::out | std::fstream::trunc);
        }

        if (!outFile)
        {
            std::cout << "Error opening file for writing the WS connection string.\n";
        }

        auto fw_env = std::getenv("FW_ENV");

        if (fw_env != nullptr && std::string(fw_env) == "dev")
        {
            std::cout << "Running in development mode.\n";

            outFile << "export const wsConnString = 'ws://localhost:8080';";
        }
        else
        {
            std::cout << "Running in production mode.\n";

            outFile << "export const wsConnString = 'wss://forradia-world-ws.ngrok-free.app:443';";
        }

        outFile.close();
    }
}

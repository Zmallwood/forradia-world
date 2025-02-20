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

#include "Main_Server.h"

#include "Conf/App_Properties.h"
#include "Socket_Server.h"
#include "Web_Server.h"

namespace FW
{
    volatile sig_atomic_t flag = 0;
    
    void SigIntHandler(int signum)
    {
        flag = 1;
    }
    
    void Main_Server::Start() const
    {
        GenerateWSConnString();
        
        std::thread tWebServer([]{
                                   Web_Server::GetInstance().Start();
                               });
        
        std::thread tSocketServer([]{
                                      Socket_Server::GetInstance().Start();
                                  });
        
        signal(SIGINT, SigIntHandler);
        
        while (!flag)
        {
            std::cout << "Server started.\n";
            pause();
        }
        
        Web_Server::GetInstance().Stop();
        Socket_Server::GetInstance().Stop();
        
        tSocketServer.join();
        tWebServer.join();
        
        std::cout << "Game server exited gracefully.\n";
    }
    
    void Main_Server::GenerateWSConnString() const
    {
        std::fstream outFile;
        
        auto appPath = std::string(App_Properties::GetInstance().GetAppPath());
        auto fullPathStr = std::string(appPath);
        auto lastSlash = fullPathStr.find_last_of("/");
        auto appBasePath = fullPathStr.substr(0, lastSlash + 1);
        auto filePath = appBasePath + "../html/js/wsConnString.generated.js";
        
        std::cout <<
            "Try opening file for writing the WS connection string at:\n"
                  << filePath << std::endl;
        
        outFile.open(filePath, std::fstream::out | std::fstream::trunc);
        
        if (!outFile)
        {
            std::cout <<
                "Error opening file for writing the WS connection string.\n";
        }
        
        auto fw_env = std::getenv("FW_ENV");
        
        if (fw_env != nullptr && std::string(fw_env) == "dev")
        {
            std::cout << "Running in development mode.\n";
            
            outFile << "export const wsConnString = 'ws://localhost:8081';";
            App_Properties::GetInstance().SetHTTPPort(81);
            App_Properties::GetInstance().SetSocketsPort(8081);
        }
        else
        {
            std::cout << "Running in production mode.\n";
            
            outFile <<
                "export const wsConnString = 'wss://forradia-world-ws.ngrok.io:443';";
        }
        
        outFile.close();
    }
}

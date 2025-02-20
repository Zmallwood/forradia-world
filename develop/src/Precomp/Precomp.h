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

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <filesystem>
#include <algorithm>
#include <set>
#include <vector>
#include <functional>
#include <string>
#include <fstream>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <chrono>
#include <cstdlib>
#include <sstream>
#include <format>

#include <httplib.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "Math_Lib/Size.h"
#include "Math_Lib/Size_F.h"
#include "Math_Lib/Point_F.h"
#include "Math_Lib/Rect_F.h"
#include "Math_Lib/Color.h"
#include "Math_Lib/Colors.h"

#include "Common/Get_Singleton.h"
#include "Common/Aliases.h"
#include "Utils/Time_Utils.h"
#include "Utils/String_Utils.h"
#include "Utils/Canvas_Utils.h"
#include "Utils/Hash.h"

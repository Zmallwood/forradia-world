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
#include <mutex>

#include <httplib.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "common/math_lib/size.hpp"
#include "common/math_lib/size_f.hpp"
#include "common/math_lib/point_f.hpp"
#include "common/math_lib/rect_f.hpp"
#include "common/math_lib/color.hpp"
#include "common/math_lib/colors.hpp"

#include "common/singleton.hpp"
#include "common/aliases.hpp"
#include "common/utils/time_utils.hpp"
#include "common/utils/string_utils.hpp"
#include "common/utils/canvas_utils.hpp"
#include "common/utils/hash.hpp"

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

#include "intro_scene.h"
#include "graphics.h"

namespace FW
{
    void IntroScene::UpdateDerived()
    {
    }

    void IntroScene::RenderDerived(std::shared_ptr<Graphics> graphics) const
    {
        graphics->DrawImage("default-scene-background", 0.0f, 0.0f, 1.0f, 1.0f);
        graphics->DrawImage("forradia-world-logo", 0.3f, 0.1f, 0.4f, 0.4f);
    }
}

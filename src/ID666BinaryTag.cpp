// ID666BinaryTag.cpp - Defines the ID666BinaryTag class.
//
// Copyright (C) 2025 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ID666BinaryTag.h"

ID666BinaryTag::ID666BinaryTag()
{
    spcFields.push_back(&songTitle);
    spcFields.push_back(&gameTitle);
    spcFields.push_back(&dumperName);
    spcFields.push_back(&comments);
    spcFields.push_back(&dateDumped);
    spcFields.push_back(&songLength);
    spcFields.push_back(&fadeLength);
    spcFields.push_back(&songArtist);
    spcFields.push_back(&defaultChannelState);
    spcFields.push_back(&emulatorUsed);
    spcFields.push_back(&reserved);
}
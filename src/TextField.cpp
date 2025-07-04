// TextField.cpp - Defines the TextField class.
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

#include "TextField.h"

using namespace Spc;

void TextField::SetValue(std::string value)
{
    for (int i = 0; i < size; i++)
    {
        if (i < value.size())
            data[i] = value[i];
        else
            data[i] = 0;
    }
}
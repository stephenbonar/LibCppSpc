// SpcHeader.h - Defines the SpcHeader struct.
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

#include "SpcHeader.h"

SpcHeader::SpcHeader()
{
    spcFields.push_back(&ID);
    spcFields.push_back(&separator);
    spcFields.push_back(&containsTag);
    spcFields.push_back(&versionMinor);
    spcFields.push_back(&pcRegister);
    spcFields.push_back(&aRegister);
    spcFields.push_back(&xRegister);
    spcFields.push_back(&yRegister);
    spcFields.push_back(&pswRegister);
    spcFields.push_back(&spRegister);
    spcFields.push_back(&reserved);
}

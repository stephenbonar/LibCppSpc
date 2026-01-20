// File.h - Declares the File class.
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

#ifndef SPC_FILE_H
#define SPC_FILE_H

#include <string>
#include <LibCppBinary.h>
#include "Spc/Header.h"
#include "Spc/Id666/Tag.h"

namespace Spc
{
    class File
    {
    public:
        File(std::string path) {}

        File(std::string path, 
             std::shared_ptr<Binary::FileStream> stream) {}

        std::string Path() const {}

        Spc::Header Header() { return header; }

        Spc::Id666::Tag Tag() { return tag; }

        void SetHeader(Spc::Header header) {  }

        void SetTag(Spc::Id666::Tag tag) {  }

        void Load();

        void Save();
    private:
        std::string path;
        Spc::Header header;
        Spc::Id666::Tag tag;
        Binary::BufferStream ram;
        Binary::BufferStream dspRegisters;
        Binary::BufferStream unused;
        Binary::BufferStream extraRam;
        std::shared_ptr<Binary::FileStream> fileStream;
    };
}

#endif
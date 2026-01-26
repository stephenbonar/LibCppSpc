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
        File(std::string path) : 
            path{ path }, 
            ram{ ramInfo.size }, 
            dspRegisters{ dspRegistersInfo.size }, 
            unused{ unusedInfo.size }, 
            extraRam{ extraRamInfo.size }
        { }

        File(std::string path, 
             std::shared_ptr<Binary::FileStream> stream) :
             path{ path },
             ram{ ramInfo.size },
             dspRegisters{ dspRegistersInfo.size }, 
             unused{ unusedInfo.size }, 
             extraRam{ extraRamInfo.size }
        { }

        std::string Path() const { return path; }

        Spc::Header Header() const { return header; }

        Spc::Id666::Tag Tag() { return tag; }

        Binary::BufferStream Ram() const { return ram; }

        Binary::BufferStream DspRegisters() const { return dspRegisters; }

        Binary::BufferStream Unused() const { return unused; }

        Binary::BufferStream ExtraRam() const { return extraRam; }

        void SetHeader(Spc::Header h) {  }

        void SetTag(Spc::Id666::Tag t) {  }

        void SetRam(Binary::BufferStream r) {  }

        void SetDspRegisters(Binary::BufferStream r) {  }

        void SetUnused(Binary::BufferStream u) {  }

        void SetExtraRam(Binary::BufferStream e) {  }

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
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
#include <vector>
#include <LibCppBinary.h>
#include <filesystem>
#include "Spc/Header.h"
#include "Spc/Id666/Tag.h"
#include "Spc/Id666/PatternLexer.h"
#include "Spc/Id666/PatternParser.h"
#include "Spc/FileCorruptException.h"

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
            extraRam{ extraRamInfo.size },
            fileStream{ nullptr }
        { }

        File(std::string path, 
             std::shared_ptr<Binary::FileStream> stream) :
             path{ path },
             ram{ ramInfo.size },
             dspRegisters{ dspRegistersInfo.size }, 
             unused{ unusedInfo.size }, 
             extraRam{ extraRamInfo.size },
             fileStream{ stream }
        { }

        std::string Path() const { return path; }

        Spc::Header Header() const { return header; }

        Spc::Id666::Tag Tag() { return tag; }

        Binary::BufferStream Ram() const { return ram; }

        Binary::BufferStream DspRegisters() const { return dspRegisters; }

        Binary::BufferStream Unused() const { return unused; }

        Binary::BufferStream ExtraRam() const { return extraRam; }

        void SetHeader(Spc::Header h) { header = h; }

        void SetTag(Spc::Id666::Tag t) { tag = t; }

        void SetRam(Binary::BufferStream r) { ram = r; }

        void SetDspRegisters(Binary::BufferStream r) { dspRegisters = r; }

        void SetUnused(Binary::BufferStream u) { unused = u; }

        void SetExtraRam(Binary::BufferStream e) { extraRam = e; }

        void Load();

        void Save();

        bool TagToFileName(std::string pattern);

        bool FileNameToTag(std::string pattern);
    private:
        std::string path;
        Spc::Header header;
        Spc::Id666::Tag tag;
        Binary::BufferStream ram;
        Binary::BufferStream dspRegisters;
        Binary::BufferStream unused;
        Binary::BufferStream extraRam;
        std::shared_ptr<Binary::FileStream> fileStream;

        void LoadStringItem(std::shared_ptr<Id666::Extended::Item> item,
                            size_t& sizeRemaining);

        void LoadPadding(std::shared_ptr<Id666::Extended::Item> item,
                         size_t& sizeRemaining);

        void LoadLengthItem(std::shared_ptr<Id666::Extended::Item> item);

        void LoadIntegerItem(std::shared_ptr<Id666::Extended::Item> item,
                             size_t& sizeRemaining);

        bool MatchNumeric(std::stringstream& stream, 
                          Id666::PatternNode node,
                          Id666::PatternNode* nextNode);

        bool MatchText(std::stringstream& stream,
                       Id666::PatternNode node,
                       Id666::PatternNode* nextNode);
    };

    bool MatchLiteral(std::stringstream& stream, Id666::PatternNode node);

    bool MatchEnd(std::stringstream& stream);
}

#endif
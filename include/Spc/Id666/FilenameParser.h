// FilenameParser.h - Declares the FilenameParser class.
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

#ifndef SPC_ID666_FILENAME_PARSER_H
#define SPC_ID666_FILENAME_PARSER_H

#include <string>
#include "PatternPlaceholder.h"
#include "PatternParser.h"

namespace Spc::Id666
{
    class FilenameParser
    {
    public:
        FilenameParser();

        bool Parse(std::string filename, std::string pattern);

        PatternPlaceholder Song() const { return song; }

        PatternPlaceholder Game() const { return game; }

        PatternPlaceholder Artist() const { return artist; }

        PatternPlaceholder Track() const { return track; }

        PatternPlaceholder Disc() const { return disc; }
    private:
        PatternPlaceholder song{ "song" };
        PatternPlaceholder game{ "game" };
        PatternPlaceholder artist{ "artist" };
        PatternPlaceholder disc{ "disc" };
        PatternPlaceholder track{ "track" };
    };
}

#endif
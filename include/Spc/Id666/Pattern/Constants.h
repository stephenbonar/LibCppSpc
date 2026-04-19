// Constants.h - Declares the constants for the pattern lexer.
//
// Copyright (C) 2026 Stephen Bonar
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

#ifndef SPC_ID666_PATTERN_CONSTANTS_H
#define SPC_ID666_PATTERN_CONSTANTS_H

namespace Spc::Id666::Pattern
{
    /// @brief The character used to denote the start and end of a placeholder.
    inline const char placeholderChar{ '%' };

    /// @brief The placeholder for the song title in the pattern.  
    extern const char* songPlaceholder;

    /// @brief The placeholder for the artist name in the pattern.
    extern const char* artistPlaceholder;

    /// @brief The placeholder for the game title in the pattern.
    extern const char* gamePlaceholder;

    /// @brief The placeholder for the disc number in the pattern.
    extern const char* discPlaceholder;

    /// @brief The placeholder for the track number in the pattern.
    extern const char* trackPlaceholder;
}

#endif
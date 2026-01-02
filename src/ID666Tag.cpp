// ID666Tag.cpp - Defines the ID666Tag class.
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

#include "ID666Tag.h"

using namespace Spc;

ID666Tag::ID666Tag()
{
    data = std::make_shared<Binary::BufferStream>(id666TagSize);
    extendedData = std::make_shared<ID666ExtendedData>();
}

TextField ID666Tag::SongTitle() const 
{
    return ReadField<TextField>("Song Title", 
                                Spc::songTitleInfo, 
                                extendedData->songName.get());
}

TextField ID666Tag::GameTitle() const 
{
    return ReadField<TextField>("Game Title", 
                                Spc::gameTitleInfo, 
                                extendedData->gameName.get());
}

TextField ID666Tag::DumperName() const 
{
    return ReadField<TextField>("Dumper Name", 
                                Spc::dumperNameInfo, 
                                extendedData->dumperName.get());
}

TextField ID666Tag::Comments() const 
{
    return ReadField<TextField>("Comments", 
                                Spc::commentsInfo, 
                                extendedData->comments.get());
}

DateField ID666Tag::DateDumped() const 
{
    return DateField{ "Date Dumped", 0xC6, 11 };
}

NumericField ID666Tag::SongLength() const 
{   
    return NumericField{ "Song Length", 0xD1, 4 }; 
}

NumericField ID666Tag::FadeLength() const 
{
    return NumericField{ "Fade Length", 0xD5, 4 };
}

TextField ID666Tag::SongArtist() const 
{
    return TextField{ "Song Artist", 0xD9, 32 };
}

NumericField ID666Tag::DefaultChannelState() const 
{
    return NumericField{ "Default Channel State", 0xF9, 2 };
}

EmulatorField ID666Tag::EmulatorUsed() const
{
    return EmulatorField{ "Emulator Used", 0xFB, 2 };
}

TextField ID666Tag::OstTitle() const 
{
    return TextField{ "OST Title", 0xFD, 32 };
}

NumericField ID666Tag::OstDisc() const
{
    return NumericField{ "OST Disc", 0x11D, 2 };
}

TrackField ID666Tag::OstTrack() const
{
    return TrackField{ "OST Track", 0x11F, 3 };
}

TextField ID666Tag::PublisherName() const 
{
    return TextField{ "Publisher Name", 0x122, 32 };
}

NumericField ID666Tag::CopyrightYear() const
{
    return NumericField{ "Copyright Year", 0x142, 4 };
}

NumericField ID666Tag::IntroLength() const 
{
    return NumericField{ "Intro Length", 0x146, 4 };
}

NumericField ID666Tag::LoopLength() const 
{
    return NumericField{ "Loop Length", 0x14A, 4 };
}

NumericField ID666Tag::EndLength() const 
{
    return NumericField{ "End Length", 0x14E, 4 };
}

BinaryField ID666Tag::MutedVoices() const 
{
    return BinaryField{ "Muted Voices", 0x152, 2 };
}

NumericField ID666Tag::LoopTimes() const 
{
    return NumericField{ "Loop Times", 0x154, 4 };
}

NumericField ID666Tag::PreampLevel() const 
{
    return NumericField{ "Preamp Level", 0x158, 4 };
}

void ID666Tag::SetSongTitle(std::string value) {}

void ID666Tag::SetGameTitle(std::string value) {}

void ID666Tag::SetDumperName(std::string value) {}

void ID666Tag::SetComments(std::string value) {}

void ID666Tag::SetDateDumped(std::string value) {}

void ID666Tag::SetSongLength(std::string value) {}

void ID666Tag::SetFadeLength(std::string value) {}

void ID666Tag::SetSongArtist(std::string value) {}

void ID666Tag::SetDefaultChannelState(std::string value) {}

void ID666Tag::SetEmulatorUsed(std::string value) {}

void ID666Tag::SetOstTitle(std::string value) {}

void ID666Tag::SetOstDisc(std::string value) {}

void ID666Tag::SetOstTrack(std::string value) {}

void ID666Tag::SetPublisherName(std::string value) {}

void ID666Tag::SetCopyrightYear(std::string value) {}

void ID666Tag::SetIntroLength(std::string value) {}

void ID666Tag::SetLoopLength(std::string value) {}

void ID666Tag::SetEndLength(std::string value) {}

void ID666Tag::SetMutedVoices(std::string value) {}

void ID666Tag::SetLoopTimes(std::string value) {}

void ID666Tag::SetPreampLevel(std::string value) {}
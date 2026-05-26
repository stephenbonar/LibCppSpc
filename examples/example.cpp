// example.cpp - Demonstrates usage of the Spc::File class.
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

#include <LibCppSpc.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Must specify .SPC file to modify." << std::endl;
        return 1;
    }

    Spc::File spcFile(argv[1]);

    // Load SPC file from disk.
    spcFile.Load();
    std::cout << "Loaded " << spcFile.Path() << std::endl;

    // Retrieve metadata tag values.
    Spc::Id666::Tag tag = spcFile.Tag();
    std::cout << "Song Name : " << tag.SongTitle().ToString() << std::endl;
    std::cout << "Track No  : " << tag.OstTrack().ToString() << std::endl;

    // Change metadata tag values.
    tag.SetSongTitle("New Song Name");
    tag.SetOstTrack("1");
    spcFile.SetTag(tag);

    // Persist changes.
    spcFile.Save();

    // Convert metadata to file name using a pattern.
    spcFile.TagToFileName("%track% - %song%.spc");
    std::cout << "Copied file to new name based on pattern" << std::endl;

    return 0;
}
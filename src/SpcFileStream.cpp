// SpcFileStream.cpp - Defines the SpcFile class.
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

#include "SpcFileStream.h"

ID666TagType SpcFileStream::TagType()
{
    // Preserve the existing position as we have to jump around in the file to
    // determine if the tag is binary and we need to get back to where we were.
    uintmax_t previousPosition = Position();

    ID666BinaryTag tag;

    //ID666DateField dateDumped;
    //ID666NumericField songLength{ 3 };

    // The fade length is the first field that has a different size depending
    // on if the tag is text or binary. With binary it's 4 but with text it's
    // 5. However, for the purposes of detecting tag type, we don't need the
    // last byte even if it's text as the last char should be the null char.
    //ID666NumericField fadeLength{ 4 };

    SetPosition(tag.songTitle.Offset());
    Read(&tag);

    if (!tag.dateDumped.IsText() || 
        !tag.songLength.IsText() || 
        !tag.fadeLength.IsText())
    {
        // While we're pretty sure we're binary at this point, let's make 
        // absolutely sure. Some older dumps use text offsets but still store
        // times as binary. Let's check the bytes that are normally unused in
        // a binary tag for any non-zero values.
        if (tag.dateDumped.IsSet())
        {
            if (!tag.dateDumped.HasUnusedArea())
            {
                SetPosition(previousPosition);
                return ID666TagType::TextMixed;
            }
        }

        /*
        SetPosition(artistBinaryOffset);
        Binary::RawField artistBytes{ 32 };
        Read(&artistBytes);
        */

        // If the first byte of artist is 0 but the byte immediately
        // following is non-zero, this suggests the artist value was shifted
        // over by 1, which means we're using text tag offsets.
        if (tag.songArtist.Data()[0] == 0 && tag.songArtist.Data()[1] != 0)
        {
            SetPosition(previousPosition);
            return ID666TagType::TextMixed;
        }

        /*
        SetPosition(reservedBinaryOffset);
        Binary::RawField reservedBytes{ 46 };
        Read(&reservedBytes);
        */

        // The reserved bytes should also be empty if the offsets are
        // for a binary tag.
        for (int i = 0; i < tag.reserved.Size(); i++)
        {
            if (tag.reserved.Data()[i] != 0)
            {
                SetPosition(previousPosition);
                return ID666TagType::TextMixed;
            }
        }

        // If we've made it this far, we can be pretty sure we're using
        // binary offsets.
        SetPosition(previousPosition);
        return ID666TagType::Binary;
    }

    SetPosition(previousPosition);
    return ID666TagType::Text;
}

bool SpcFileStream::HeaderContainsTag()
{
    uintmax_t previousPosition = Position();
    SetPosition(0);
    SpcHeader header;
    Read(&header);
    SetPosition(previousPosition);

    if (header.containsTag.Value() == headerContainsTag)
        return true;
    
    return false;
}

bool SpcFileStream::HasExtendedTag()
{
    if (FileSize() > extendedTagOffset)
    {
        uintmax_t previousPosition = Position();
        SetPosition(extendedTagOffset);
        std::shared_ptr<Binary::ChunkHeader> headerPtr 
            = FindNextChunk("xid6");
        SetPosition(previousPosition);

        if (headerPtr == nullptr)
            return false;

        return true;
    }

    return false;
}

void SpcFileStream::SeekExtendedTag()
{
    SetPosition(extendedTagOffset);
}

// Tag.h - Declares the Tag class.
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

#ifndef SPC_ID666_TAG_H
#define SPC_ID666_TAG_H

#include <memory>
#include <string>
#include "Spc/Id666/TagType.h"
#include "Spc/Id666/TagFieldInfo.h"
#include "Spc/TextField.h"
#include "Spc/Id666/Extended/ItemInfo.h"
#include "Spc/Id666/Extended/Data.h"
#include "Spc/Id666/Extended/Item.h"

namespace Spc::Id666
{
    /// @brief The number of bits in a byte.
    inline constexpr size_t bitsPerByte{ 8 };

    /// @brief The size of an ID666 tag in bytes.
    inline constexpr size_t tagSize{ 210 };

    /// @brief The offset in the file where the ID666 tag begins.
    inline constexpr size_t tagOffset{ 0x2E };

    /// @brief The minimum value for numeric fields in the tag.
    inline constexpr size_t minNumeric{ 0 };

    /// @brief The minimum value for preamp level field in the tag.
    inline constexpr size_t minPreampLevel{ 32768 };

    /// @brief The maximum length of a song, in seconds, allowed.
    inline constexpr size_t maxSongLength{ 959 };

    /// @brief The maximum length of a fade, in milliseconds, allowed.
    inline constexpr size_t maxFadeLength{ 59999 };

    /// @brief The maximum disc number allowed.
    inline constexpr size_t maxDiscNumber{ 9 };

    /// @brief The maximum track number allowed.
    inline constexpr size_t maxTrackNumber{ 99 };

    /// @brief The maximum number of song loops allowed.
    inline constexpr size_t maxLoopTimes{ 9 };

    /// @brief The maximum preamp level allowed.
    inline constexpr size_t maxPreampLevel{ 524288 };

    /// @brief The maximum number of ticks used for extended tag timings.
    inline constexpr size_t maxTicks{ 383999999 };

    /// @brief The maximum length of a string field allowed.
    inline constexpr size_t maxStringSize{ 256 };

    /// @brief Represents an ID666 tag in an SPC file.
    /// @invariant Pointers read from tag should never be nullptr.
    /// @invariant If a tag's field is empty or unused, returns an empty field.
    class Tag
    {
    public:
        /// @brief Default constructor; creates a new instance of Tag.
        Tag();

        /// @brief Gets a pointer to the raw field data of the tag.
        ///
        /// The tag stores its field data in a Binary::BufferStream rather
        /// than a series of Binary::Fields because the offsets and formats of
        /// the fields can vary depending on the tag type. The BufferStream
        /// allows for more flexible reading and writing of the field data.
        ///
        /// @return A pointer to the tag's field data.
        std::shared_ptr<Binary::BufferStream> FieldData() const
        {
            return fieldData;
        }

        /// @brief Gets a pointer to the extended data structure of the tag.
        /// @return A pointer if the tag has extended data, otherwise nullptr.
        std::shared_ptr<Extended::Data> ExtendedData() const
        {
            return extendedData;
        }

        /// @brief Determines if the tag has text, binary, or mixed type values.
        ///
        /// The tag type determines the offsets and formats of the fields in the
        /// tag. The field accessor and mutator methods will use the tag type to
        /// determine how to read and write the fields.
        ///
        /// @return The type of the tag.
        TagType DetermineType() const;

        /// @brief Gets the title of the song.
        /// @return A TextField representing the song title.
        ///         If the song title is stored in both the header and the 
        ///         extended tag data, the extended version will be returned 
        ///         according to the SPC file format specification.
        TextField SongTitle() const;

        /// @brief Gets the title of the game.
        /// @return A TextField representing the game title.
        ///         If the game title is stored in both the header and the 
        ///         extended tag data, the extended version will be returned 
        ///         according to the SPC file format specification.
        TextField GameTitle() const;

        /// @brief Gets the name of the person who dumped the SPC file.
        /// @return A TextField representing the dumper name.
        ///         If the dumper name is stored in both the header and the 
        ///         extended tag data, the extended version will be returned 
        ///         according to the SPC file format specification.
        TextField DumperName() const;

        /// @brief Gets the comments the tagger included in the tag.
        /// @return A TextField representing the comments.
        ///         If the comments are stored in both the header and the 
        ///         extended tag data, the extended version will be returned 
        ///         according to the SPC file format specification.
        TextField Comments() const;

        /// @brief Gets the date the SPC file was dumped.
        /// @return A DateField representing the date the SPC file was dumped.
        DateField DateDumped() const;

        /// @brief Gets the length of the song, in seconds.
        /// @return A NumericField representing the song length.
        NumericField SongLength() const;

        /// @brief Gets the length of the song fade out, in milliseconds.
        /// @return A NumericField representing the fade length.
        NumericField FadeLength() const;

        /// @brief Gets the name of the song artist.
        /// @return A TextField representing the song artist.
        ///         If the song artist is stored in both the header and the 
        ///         extended tag data, the extended version will be returned 
        ///         according to the SPC file format specification.
        TextField SongArtist() const;

        /// @brief Gets which channels are disabled at startup.
        ///
        /// Similar to muted channels, this field is a bitmask representing
        /// which channels are in a muted state, where each bit corresponds to 
        /// a channel, with 0 indicating enabled and 1 indicating disabled.
        /// However, unlike muted channels, this is just the state the channels
        /// are initialized to and can be changed by the SPC program.
        ///
        /// @return A BinaryField representing the disabled channels.
        BinaryField DefaultDisabledChannels() const;

        /// @brief Gets the emulator used to dump the SPC file.
        /// @return An EmulatorField representing the emulator used.
        EmulatorField EmulatorUsed() const;

        /// @brief Gets the title of the original soundtrack (OST) album.
        ///
        /// The original soundtrack (OST) album title is an extended tag item
        /// representing the title of the corresponding official soundtrack the
        /// SPC album is based on, if applicable.
        ///
        /// @return A TextField representing the OST album title.
        TextField OstTitle() const;

        /// @brief Gets the disc number of the original soundtrack (OST) album.
        ///
        /// The original soundtrack (OST) album disc number is an extended tag 
        /// item representing the disc number of the song can be found on 
        /// in the corresponding official soundtrack, if applicable.
        ///
        /// @return A NumericField representing the OST album disc number.
        NumericField OstDisc() const;

        /// @brief Gets the track number of the original soundtrack (OST) album.
        ///
        /// The original soundtrack (OST) album track number is an extended tag 
        /// item representing the track number of the song in the corresponding 
        /// official soundtrack, if applicable.
        ///
        /// @return A TrackField representing the OST album track number.
        TrackField OstTrack() const;

        /// @brief Gets the name of the publisher of the game.
        ///
        /// The publisher name is an extended tag item representing the company 
        /// that published the game.
        ///
        /// @return A TextField representing the publisher of the game.
        TextField PublisherName() const;

        /// @brief Gets the year the game was copyrighted.
        ///
        /// The copyright year is an extended tag item representing the year 
        /// the game was copyrighted.
        ///
        /// @return A NumericField representing the copyright year.
        NumericField CopyrightYear() const;

        /// @brief Gets the length of the song intro, in ticks.
        ///
        /// The intro length is an extended tag item representing the length of
        /// the beginning portion of the song before the looped portion begins.
        /// The intro length is represented in ticks, which are 1/64000th of a
        /// second.
        ///
        /// @return A NumericField representing the length of the song intro.
        NumericField IntroLength() const;

        /// @brief Gets the length of the looped portion of the song, in ticks.
        ///
        /// The loop length is an extended tag item representing the length of 
        /// the looped portion of the song. The loop length is represented in 
        /// ticks, which are 1/64000th of a second.
        ///
        /// @return A NumericField representing the length of looped portion.
        NumericField LoopLength() const;

        /// @brief Gets the length of the song after the loop, in ticks.
        ///
        /// The end length is an extended tag item representing the length of 
        /// the ending portion of the song. The end length is represented in 
        /// ticks, which are 1/64000th of a second. 
        ///
        /// @return A NumericField representing the length of song after loop.
        NumericField EndLength() const;

        /// @brief Gets the muted voices of the song.
        ///
        /// The muted voices field is a bitmask representing which channels are 
        /// in a muted state, where each bit corresponds to a channel, with 0 
        /// indicating unmuted and 1 indicating muted.
        ///
        /// @return A BinaryField representing the muted voices of the song.
        BinaryField MutedVoices() const;

        /// @brief Get the number of times the song loops.
        ///
        /// The loop times field is an extended tag item representing the number
        /// of times the song loops before it stops.
        ///
        /// @return A NumericField representing number of times the song loops.
        NumericField LoopTimes() const;

        /// @brief Gets amplification level to apply to the output of the song.
        ///
        /// The preamp level is an extended tag item representing the
        /// amplification level to apply to the output of the song.
        ///
        /// @return A NumericField representing the preamp level.
        NumericField PreampLevel() const;

        /// @brief Sets the title of the song.
        /// @param value The value to set the song title to.
        /// @pre Value must be <= 256 characters.
        /// @post The first 32 characters are stored in the non-extended field.
        /// @post If value > 32 characters, full value stored in extended data.
        /// @throws std::out_of_range if value exceeds maximum string size.
        void SetSongTitle(std::string value);

        /// @brief Sets the title of the game.
        ///
        /// If the game title is greater than 32 characters, it will set a
        /// truncated version in the header and the full version in the extended
        /// tag data according to the SPC file format specification.
        ///
        /// @param value The value to set the game title to.
        /// @pre Value must be <= 256 characters.
        /// @post The first 32 characters are stored in the non-extended field.
        /// @post If value > 32 characters, full value stored in extended data.
        /// @throws std::out_of_range if value exceeds maximum string size.
        void SetGameTitle(std::string value);

        /// @brief Sets the name of the person who dumped the SPC file.
        ///
        /// If the dumper name is greater than 16 characters, it will set a
        /// truncated version in the header and the full version in the extended
        /// tag data according to the SPC file format specification.
        ///
        /// @param value The value to set the dumper name to.
        /// @pre Value must be <= 256 characters.
        /// @post The first 32 characters are stored in the non-extended field.
        /// @post If value > 32 characters, full value stored in extended data.
        /// @throws std::out_of_range if value exceeds maximum string size.
        void SetDumperName(std::string value);

        /// @brief Sets the comments the tagger included in the tag.
        ///
        /// If the comments are greater than 32 characters, it will set a
        /// truncated version in the header and the full version in the extended
        /// tag data according to the SPC file format specification.
        ///
        /// @param value The value to set the comments to.
        /// @pre Value must be <= 256 characters.
        /// @post The first 32 characters are stored in the non-extended field.
        /// @post If value > 32 characters, full value stored in extended data.
        /// @throws std::out_of_range if value exceeds maximum string size.
        void SetComments(std::string value);

        /// @brief Sets the date the SPC file was dumped.
        /// @param value The value to set the date dumped to.
        /// @pre Value must be in MM/DD/YYYY format.
        /// @throws std::invalid_argument if value is not in correct format.
        void SetDateDumped(std::string value);

        /// @brief Sets the length of the song, in seconds.
        /// @param value The value to set the song length to.
        /// @pre Value must be between 0 and 959 seconds.
        /// @throws std::out_of_range if value is out of range.
        void SetSongLength(std::string value);

        /// @brief Sets the length of the fade, in milliseconds.
        /// @param value The value to set the fade length to.
        /// @pre Value must be between 0 and 59999 milliseconds.
        void SetFadeLength(std::string value);

        /// @brief Sets the artist of the song. 
        ///
        /// If the song artist is greater than 32 characters, it will set a
        /// truncated version in the header and the full version in the extended
        /// tag data according to the SPC file format specification.
        ///
        /// @param value The value to set the song artist to.
        /// @pre Value must be <= 256 characters.
        /// @post The first 32 characters are stored in the non-extended field.
        /// @post If value > 32 characters, full value stored in extended data.
        void SetSongArtist(std::string value);

        /// @brief Sets which channels are disabled at startup.
        ///
        /// Similar to muted channels, this field is a bitmask representing
        /// which channels are in a disabled state, where each bit corresponds
        /// to a channel, with 0 indicating enabled and 1 indicating disabled. 
        /// However, unlike muted channels, this is just the state the channels
        /// are initialized to and can be changed by the SPC program.
        ///
        /// @param value The value to set the default disabled channels to.
        ///     Examples:
        ///     @code 00000000 = All channels enabled
        ///     @code 11110000 = First four channels disabled
        /// @pre Value must be an 8-character string of 0s and 1s.
        void SetDefaultDisabledChannels(std::string value);

        /// @brief Sets the emulator used to dump the SPC file.
        /// @param value The value to set the emulator used to.
        ///     Examples:
        ///     @code "ZSNES" = ZSNES emulator
        ///     @code "SNES9X" = Snes9x emulator  
        ///     @code "UNKNOWN" or any other value = Unknown emulator
        void SetEmulatorUsed(std::string value);

        /// @brief Sets the title of the original soundtrack (OST) album.
        ///
        /// The original soundtrack (OST) album title is an extended tag item
        /// representing the title of the corresponding official soundtrack the
        /// SPC album is based on, if applicable.
        ///
        /// @param value The value to set the OST title to.
        /// @pre Value must be <= 256 characters.
        void SetOstTitle(std::string value);

        /// @brief Sets the disc number of the original soundtrack (OST) album.
        ///
        /// The original soundtrack (OST) album disc number is an extended tag 
        /// item representing the disc number of the song can be found on in 
        /// the corresponding official soundtrack, if applicable.
        ///
        /// @param value The value to set the OST disc number to.
        /// @pre Value must be between 0 and 9.
        void SetOstDisc(std::string value);

        /// @brief Sets the track number of the original soundtrack (OST) album.
        ///
        /// The original soundtrack (OST) album track number is an extended tag 
        /// item representing the track number of the song in the corresponding 
        /// official soundtrack, if applicable.
        ///
        /// @param value The value to set the OST track number to.
        ///     Examples:
        ///     @code "1" = Track 1
        ///     @code "2a" = Track 2, Subtrack A
        /// @pre Track must be 0 - 99 followed by an optional ASCII character.
        void SetOstTrack(std::string value);

        /// @brief Sets the name of the publisher.
        ///
        /// The publisher name is an extended tag item representing the company 
        /// that published the game.
        ///
        /// @param value The value to set the publisher name to.
        void SetPublisherName(std::string value);

        /// @brief Sets the copyright year.
        ///
        /// The copyright year is an extended tag item representing the year 
        /// the game was copyrighted.
        ///
        /// @param value The value to set the copyright year to.
        /// @pre Value must be >= 0.
        void SetCopyrightYear(std::string value);

        /// @brief Sets the length of the song intro, in ticks.
        ///
        /// The intro length is an extended tag item representing the length of
        /// the beginning portion of the song before the looped portion begins.
        /// The intro length is represented in ticks, which are 1/64000th of a
        /// second.
        ///
        /// @param value The value to set the intro length to.
        /// @pre Value must be between 0 and 383999999 ticks.
        void SetIntroLength(std::string value);

        /// @brief Sets the length of the song loop, in ticks.
        ///
        /// The loop length is an extended tag item representing the length of
        /// the looped portion of the song. The loop length is represented in
        /// ticks, which are 1/64000th of a second.
        ///
        /// @param value The value to set the loop length to.
        /// @pre Value must be between 0 and 383999999 ticks.
        void SetLoopLength(std::string value);

        /// @brief Sets the length of the song ending, in ticks.
        ///
        /// The end length is an extended tag item representing the length of
        /// the ending portion of the song after the looped portion ends. The
        /// end length is represented in ticks, which are 1/64000th of a
        /// second.
        ///
        /// @param value The value to set the end length to.
        /// @pre Value must be between 0 and 383999999 ticks.
        void SetEndLength(std::string value);

        /// @brief Sets which voices are muted.
        ///
        /// The muted voices field is an extended tag item representing which
        /// voices are muted in the song. This is represented as a bitmask,
        /// where each bit corresponds to a voice, with 0 indicating unmuted
        /// and 1 indicating muted.
        ///
        /// @param value The value to set the muted voices to.
        ///    Examples:
        ///    @code "00000000" = No voices muted
        ///    @code "11110000" = First four voices muted
        /// @pre Value must be an 8-character string of 0s and 1s.
        void SetMutedVoices(std::string value);

        /// @brief Sets the number of times the song loops.
        ///
        /// The loop times field is an extended tag item representing the number
        /// of times the song loops before it stops.
        ///
        /// @param value The value to set the loop times to.
        /// @pre Value must be between 1 and 9.
        void SetLoopTimes(std::string value);

        /// @brief Sets the preamp level.
        ///
        /// The preamp level is an extended tag item representing the level of
        /// preamplification applied to the audio (65536 is normal SNES).
        ///
        /// @param value The value to set the preamp level to.
        /// @pre Value must be between 32768 and 524288.
        /// @throws std::invalid_argument if value is out of range.
        void SetPreampLevel(std::string value);

    private:
        std::shared_ptr<Binary::BufferStream> fieldData;
        std::shared_ptr<Extended::Data> extendedData;

        /// @brief Reads a field from the binary buffer stream of the tag.
        ///
        /// This method preserves the position of the buffer stream so it
        /// doesn't change positions. Use this method to read a field from the
        /// buffer stream using random access rather than sequential reads.
        /// The specified field's offset is used to determine where to read from
        /// in the buffer stream.
        ///
        /// @param field The field to read from the buffer stream.
        /// @pre The field's offset must be the correct position in the tag.
        /// @post The field will contain the value read from the buffer stream.
        void ReadField(Field* field) const;

        /// @brief Writes a field to the binary buffer stream of the tag.
        ///
        /// This method preserves the position of the buffer stream so it
        /// doesn't change positions. Use this method to write a field to the
        /// buffer stream using random access rather than sequential writes.
        /// The specified field's offset is used to determine where to write to
        /// in the buffer stream.
        ///
        /// @param field The field to write to the buffer stream.
        /// @pre The field's offset must be the correct position in the tag.
        /// @post The field's value is written to buffer stream at the offset.
        /// @post The buffer stream's position is unchanged.
        void WriteField(Field* field);

        /// @brief Reads a text field from the non-extended tag data only.
        ///
        /// This method provides a common way for reading text fields from the
        /// non-extended tag data, automatically selecting the correct offsets
        /// and sizes based on the tag type. This method should be used when
        /// only the non-extended tag data should be read.
        ///
        /// @tparam T The type of the field to read.
        /// @param label The label the read field should have.
        /// @param info The offset / sizes of both text and binary versions.
        /// @return A shared pointer to the field read from the tag.
        /// @pre The specified field info is correct for the desired field.
        template<typename T>
        std::shared_ptr<T> ReadTextField(std::string label, 
                                         TagFieldInfo info) const
        {
            std::shared_ptr<T> field;

            if (DetermineType() == TagType::Binary)
            {
                field = std::make_shared<T>(label, info.binary);
            }
            else
            {
                field = std::make_shared<T>(label, info.text);
            }

            ReadField(field.get());
            return field;
        }

        /// @brief Reads a numeric field from the non-extended tag only.
        ///
        /// This method provides a common way for reading numeric fields from
        /// the non-extended tag data, automatically selecting the correct 
        /// offsets, sizes, and numeric types based on the tag type. This method
        /// should be used when only the non-extended tag data should be read.
        ///
        /// @tparam T The type of the field to read.
        /// @param label The label the read field should have.
        /// @param info The offset / sizes of both text and binary versions.
        /// @return A shared pointer to the field read from the tag.
        /// @pre The specified field info is correct for the desired field.
        template<typename T>
        std::shared_ptr<T> ReadNumericField(std::string label, 
                                            TagFieldInfo info) const
        {
            std::shared_ptr<T> field;

            TagType type = DetermineType();

            if (type == TagType::Binary)
            {
                field = std::make_shared<T>(label, info.binary);
                field->SetType(NumericType::Binary);
            }
            else if (type == TagType::TextMixed)
            {
                field = std::make_shared<T>(label, info.text);
                field->SetType(NumericType::Binary);
            }
            else
            {
                field = std::make_shared<T>(label, info.text);
                field->SetType(NumericType::Text);
            }

            ReadField(field.get());
            return field;
        }

        /// @brief Reads a text field from extended or non-extended tag data.
        ///
        /// This method provides a common way for reading text fields from 
        /// either the non-extended tag data or the extended tag data, 
        /// automatically selecting the correct offsets and sizes based on the 
        /// tag type and whether the extended item is available. If the extended
        /// item is available, the extended tag data will be used instead of the
        /// non-extended tag data. This method should be used to read fields
        /// that exist in both the non-extended tag data and the extended tag 
        /// data.
        ///
        /// @tparam T The type of the field to read.
        /// @param label The label the read field should have.
        /// @param info The offset / sizes of both text and binary versions.
        /// @param item The extended item to read from, if available.
        /// @return A shared pointer to the field read from the tag.
        /// @pre The specified field info is correct for the desired field.
        template<typename T>
        std::shared_ptr<T> ReadExtendedTextField(
            std::string label, 
            TagFieldInfo info, 
            Extended::Item* item) const
        {
            std::shared_ptr<T> field;

            if (item != nullptr)
            {
                field = ReadExtendedField<T>(label, item);
            }
            else
            {
                field = ReadTextField<T>(label, info);
            }

            if (field == nullptr)
            {
                field = std::make_shared<T>(label, info.text);
                return field;
            }
            
            return field;
        }

        /// @brief Reads a numeric field from extended or non-extended tag data.
        ///
        /// This method provides a common way for reading numeric fields from 
        /// either the non-extended tag data or the extended tag data, 
        /// automatically selecting the correct offsets and sizes based on the 
        /// tag type and whether the extended item is available. If the extended
        /// item is available, the extended tag data will be used instead of the
        /// non-extended tag data. This method should be used to read fields
        /// that exist in both the non-extended tag data and the extended tag 
        /// data.
        ///
        /// @tparam T The type of the field to read.
        /// @param label The label the read field should have.
        /// @param info The offset / sizes of both text and binary versions.
        /// @param item The extended item to read from, if available.
        /// @return A shared pointer to the field read from the tag.
        /// @pre The specified field info is correct for the desired field.
        template<typename T>
        std::shared_ptr<T> ReadExtendedNumericField(
            std::string label, 
            TagFieldInfo info, 
            Extended::Item* item) const
        {
            std::shared_ptr<T> field;

            if (item != nullptr)
            {
                field = ReadExtendedField<T>(label, item);
            }
            else
            {
                field = ReadNumericField<T>(label, info);
            }

            if (field == nullptr)
            {
                field = std::make_shared<T>(label, info.text);
                return field;
            }
            
            return field;
        }

        /// @brief Reads a field from an extended tag item only.
        ///
        /// This method provides a common way for reading fields from the
        /// extended tag data. This should be used to read fields that only
        /// exist in the extended tag data. 
        ///
        /// @tparam T The type of the field to read.
        /// @param label The label the read field should have.
        /// @param item The extended item to read from.
        /// @return A shared pointer to the field read from extended tag item.
        template<typename T>
        std::shared_ptr<T> ReadExtendedField(std::string label, 
                                             Extended::Item* item) const
        {
            std::shared_ptr<T> field;

            if (item != nullptr)
            {
                if (item->type->ToInt32() == Extended::lengthType)
                {
                    // Copy the raw data to a new field to ensure it is
                    // interpreted according to the correct type T as item->data
                    // is created as a NumericField, but may represent a
                    // BinaryField or other type and needs to be recreated as
                    // such. 
                    field = std::make_shared<T>(label, Extended::dataInfo);
                    item->data->CopyRawDataTo(field.get());
                }
                else if (item->extendedData != nullptr)
                {
                    field = std::static_pointer_cast<T>(item->extendedData);
                }
                else
                {
                    field = std::make_shared<T>(label, Extended::dataInfo);
                }
            }
            else
            {
                field = std::make_shared<T>(label, Extended::dataInfo);
            }

            return field;
        }

        /// @brief Writes to a text field in the non-extended tag data.
        ///
        /// This method provides a common way for writing text fields to the 
        /// non-extended tag data. This ensures that the value is written to
        /// the correct offsets and sizes depending on the tag type. This 
        /// should be used to write fields that only exist in the non-extended
        /// tag data.
        ///
        /// @tparam T The type of the field to write.
        /// @param info The offset / sizes of both text and binary versions.
        /// @param value The string value to write.
        /// @pre The specified field info is correct for the desired field.
        /// @post The value is written to correct offset in the buffer stream.
        template<typename T>
        void WriteTextField(TagFieldInfo info, std::string value)
        {
            std::shared_ptr<T> field;

            if (DetermineType() == TagType::Binary)
            {
                field = std::make_shared<T>("Temp", info.binary);
            }
            else
            {
                field = std::make_shared<T>("Temp", info.text);
            }

            field->SetValue(value);
            WriteField(field.get());
        }

        /// @brief Writes to a numeric field in the non-extended tag data.
        ///
        /// This method provides a common way for writing numeric fields to the 
        /// non-extended tag data. This ensures that the value is written to
        /// the correct offsets and sizes depending on the tag type. This 
        /// should be used to write fields that only exist in the non-extended
        /// tag data.
        ///
        /// @tparam T The type of the field to write.
        /// @param info The offset / sizes of both text and binary versions.
        /// @param value The string value to write.
        /// @pre The specified field info is correct for the desired field.
        /// @post The value is written to correct offset in the buffer stream.
        template<typename T>
        void WriteNumericField(TagFieldInfo info, 
                               std::string value)
        {
            std::shared_ptr<T> field;

            TagType type = DetermineType();

            if (type == TagType::Binary)
            {
                field = std::make_shared<T>("Temp", info.binary);
                field->SetType(Spc::NumericType::Binary);
            }
            else if (type == TagType::TextMixed)
            {
                field = std::make_shared<T>("Temp", info.text);
                field->SetType(Spc::NumericType::Either);
            }
            else
            {
                field = std::make_shared<T>("Temp", info.text);
                field->SetType(Spc::NumericType::Text);
            }

            field->SetValue(value);
            WriteField(field.get());
        }

        /// @brief Writes to text field in extended or non-extended tag data.
        ///
        /// This method provides a common way for writing text values to 
        /// either the non-extended tag data or the extended tag data, 
        /// automatically selecting the correct offsets and sizes based on the
        /// tag type and whether the extended item is available. If the extended
        /// item is available, the value will be written to the extended tag 
        /// data and a truncated version will be written to the non-extended tag
        /// data.
        ///
        /// @tparam T The type of the field to write.
        /// @param info The offset / sizes of both text and binary versions.
        /// @param extendedInfo The extended item id and type.
        /// @param itemPtrPtr A pointer to the extended item shared pointer.
        ///                   A pointer to a pointer is used so the pointer
        ///                   itself can be updated to point to a new extended
        ///                   item if the extended item does not already exist.
        /// @param value The string value to write.
        /// @pre The specified field info is correct for the desired field.
        /// @post The value is written to correct offset in the buffer stream.
        /// @post The extended item is created if it does not already exist
        /// @post The extended item value is updated if it does exist.
        template<typename T>
        void WriteExtendedTextField(
            TagFieldInfo info,
            Extended::ItemInfo extendedInfo, 
            std::shared_ptr<Extended::Item>* itemPtrPtr, 
            std::string value)
        {
                size_t fieldSize;

                if (DetermineType() == TagType::Binary)
                    fieldSize = info.binary.size;
                else
                    fieldSize = info.text.size;

                if (value.size() > fieldSize)
                {
                    WriteExtendedStringField<T>(extendedInfo, 
                                                itemPtrPtr, 
                                                value);
                    WriteTextField<T>(info, value);
                }
                else
                {
                    WriteTextField<T>(info, value);
                }
        }

        /// @brief Writes a length value to extended tag data only.
        ///
        /// This method provides a common way for writing fields to the extended
        /// tag data. This should be used to write fields that only exist in the
        /// extended tag data.
        ///
        /// @tparam T The type of the field to write.
        /// @param extendedInfo The extended item id and type.
        /// @param itemPtrPtr A pointer to the extended item shared pointer.
        ///                   A pointer to a pointer is used so the pointer
        ///                   itself can be updated to point to a new extended
        ///                   item if the extended item does not already exist.
        /// @param value The length value to write.
        /// @pre The specified field info is correct for the desired field.
        /// @post The extended item is created if it does not already exist
        /// @post The extended item value is updated if it does exist.
        template<typename T>
        void WriteExtendedLengthField(
            Extended::ItemInfo extendedInfo,
            std::shared_ptr<Extended::Item>* itemPtrPtr, 
            std::string value)
        {
            if (*(itemPtrPtr) == nullptr)
            {
                auto item = std::make_shared<Extended::Item>();
                item->id->SetInt32(extendedInfo.id);
                item->type->SetInt32(extendedInfo.type);

                auto field = std::make_shared<T>("Temp", Extended::dataInfo);
                field->SetType(Spc::NumericType::Binary);
                field->SetValue(value);
                field->CopyRawDataTo(item->data.get());

                *(itemPtrPtr) = item;
            }
            else
            {
                auto item = *(itemPtrPtr);
                auto field = std::make_shared<T>("Temp", Extended::dataInfo);
                field->SetType(Spc::NumericType::Binary);
                field->SetValue(value);
                field->CopyRawDataTo(item->data.get());
            }
        }

        /// @brief Writes integer value to extended tag data only.
        ///
        /// This method provides a common way for writing fields to the 
        /// extended tag data. This should be used to write fields that only 
        /// exist in the extended tag data.
        ///
        /// @tparam T The type of the field to write.
        /// @param extendedInfo The extended item information.
        /// @param itemPtrPtr A pointer to the extended item shared pointer.
        ///                   A pointer to a pointer is used so the pointer
        ///                   itself can be updated to point to a new extended
        ///                   item if the extended item does not already exist.
        /// @param value The integer value to write.
        /// @pre The specified field info is correct for the desired field.
        /// @post The extended item is created if it does not already exist
        /// @post The extended item value is updated if it does exist.
        template<typename T>
        void WriteExtendedIntField(Extended::ItemInfo extendedInfo,
                                   std::shared_ptr<Extended::Item>* itemPtrPtr, 
                                   std::string value)
        {
            if (*(itemPtrPtr) == nullptr)
            {
                auto item = std::make_shared<Extended::Item>();
                item->id->SetInt32(extendedInfo.id);
                item->type->SetInt32(extendedInfo.type);

                auto data = std::static_pointer_cast<NumericField>(item->data);
                data->SetInt32(Extended::integerSize);

                Spc::FieldInfo info;
                info.offset = Extended::dataOffset;
                info.size = Extended::integerSize;
                auto field = std::make_shared<T>("Temp", info);
                field->SetType(Spc::NumericType::Binary);
                field->SetValue(value);
                item->extendedData = field;

                *(itemPtrPtr) = item; 
            }
            else
            {
                auto item = *(itemPtrPtr);

                std::shared_ptr<NumericField> data = item->data;

                data->SetInt32(Extended::integerSize);
                Spc::FieldInfo info;
                info.offset = Extended::dataOffset;
                info.size = Extended::integerSize;
                item->extendedData = std::make_shared<T>("Temp", info);

                auto extData = std::static_pointer_cast<T>(item->extendedData);
                extData->SetType(Spc::NumericType::Binary);
                extData->SetValue(value);
            }
        }

        /// @brief Writes string value to extended tag data only.
        ///
        /// This method provides a common way for writing fields to the extended
        /// tag data. This should be used to write fields that only exist in the
        /// extended tag data.
        ///
        /// @tparam T The type of the field to write.
        /// @param extendedInfo The extended item information.
        /// @param itemPtrPtr A pointer to the extended item shared pointer.
        ///                   A pointer to a pointer is used so the pointer
        ///                   itself can be updated to point to a new extended
        ///                   item if the extended item does not already exist.
        /// @param value The string value to write.
        /// @pre The specified field info is correct for the desired field.
        /// @post The extended item is created if it does not already exist
        /// @post The extended item value is updated if it does exist.
        /// @throws std::invalid_argument if value exceeds maximum string size.
        template<typename T>
        void WriteExtendedStringField(
            Extended::ItemInfo extendedInfo,
            std::shared_ptr<Extended::Item>* itemPtrPtr, 
            std::string value)
        {
            if (value.size() > maxStringSize)
            {
                throw std::invalid_argument(
                    "Value exceeds maximum string size for extended data.");
            }

            if (*(itemPtrPtr) == nullptr)
            {
                auto item = std::make_shared<Extended::Item>();
                item->id->SetInt32(extendedInfo.id);
                item->type->SetInt32(extendedInfo.type);

                auto data = std::static_pointer_cast<NumericField>(item->data);

                data->SetUInt32(static_cast<uint32_t>(value.size()));
                Spc::FieldInfo info{ Extended::dataOffset, value.size() };
                auto field = std::make_shared<T>("Temp", info);
                field->SetValue(value);
                item->extendedData = field;

                *(itemPtrPtr) = item;  
            }
            else
            {
                auto item = *(itemPtrPtr);

                auto data = std::static_pointer_cast<NumericField>(item->data);

                data->SetUInt32(static_cast<uint32_t>(value.size()));
                Spc::FieldInfo info{ Extended::dataOffset,  value.size() };
                item->extendedData = std::make_shared<T>("Temp", info);
                item->extendedData->SetValue(value);
            }
        }
    };

    /// @brief Throws an exception if the specified value is out of range.
    /// @param value A string representation of the numeric value to check.
    /// @param min The minimum value of the range.
    /// @param max The maximum value of the range.
    /// @throws std::invalid_argument if the value is out of range.
    void CheckRange(std::string value, int min, int max);
}

#endif
// SpcFile.h - Declares the SpcFile class.
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
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include "SpcHeader.h"
#include "ID666BinaryTag.h"
#include "ID666TextTag.h"
#include "ID666ExtendedTag.h"
#include "ID666ExtendedItem.h"
#include "ID666TagType.h"
#include "SetCommand.h"
#include "SpcFileStream.h"
#include "StringTokenizer.h"

/// @brief Initalizes an SpcField with the correct extended item label.
/// @tparam T The type of SpcFile to initialize.
/// @param extendedID The extended item ID used to determine the label.
/// @param size The size of the SpcField to initialize.
/// @return A shared pointer to the newly initialized field.
template<typename T>
std::shared_ptr<T> InitExtendedField(int extendedID, size_t size)
{
    // Initialize to default value in case the label is not found.
    std::string label = "<Unknown Field>";

    // All extended item fields should have the extended tag offset.
    constexpr uintmax_t offset{ extendedTagOffset };

    if (extendedFieldLabels.find(extendedID) != extendedFieldLabels.end())
        label = extendedFieldLabels.at(extendedID);

    return std::make_shared<T>(label, offset, size);
}

/// @brief Allocates the correct number of padding bytes on the specified item.
/// @param item The item to allocate padding bytes for.
void PadItem(ID666ExtendedItem* item);

/// @brief Represents an SPC file.
class SpcFile
{
public:
    /// @brief Constructor; creates a new instance of ScpFile.
    /// @param fileName The file name / path to the SpcFile.
    SpcFile(std::string fileName) : 
        fileName{ fileName }, 
        hasLoaded{ false }, 
        tagType{ ID666TagType::Text },
        hasExtendedTag{ false },
        headerContainsTag{ false },
        spcRam{ 65536 },
        dspRegisters{ 128 },
        unused{ 64 },
        extraRam{ 64 }
    {}

    std::string FileName() const { return fileName; }

    bool HasLoaded() const { return hasLoaded; }

    bool HasExtendedTag() const { return hasExtendedTag; }

    bool HeaderContainsTag() const { return headerContainsTag; }

    SpcHeader Header() const { return header; }

    ID666TagType TagType() const { return tagType; }

    ID666BinaryTag BinaryTag() const { return binaryTag; }

    ID666TextTag TextTag() const { return textTag; }

    Binary::ChunkHeader ExtendedTagHeader() const { return extendedTagHeader; }

    ID666ExtendedTag ExtendedTag() const { return extendedTag; }

    SpcTextField SongTitle() const;

    SpcTextField GameTitle() const;

    SpcTextField DumperName() const;

    SpcTextField Comments() const;

    SpcDateField DateDumped() const;

    SpcNumericField SongLength() const;

    SpcNumericField FadeLength() const;

    SpcTextField SongArtist() const;

    SpcNumericField DefaultChannelState() const;

    SpcEmulatorField EmulatorUsed() const;

    SpcTextField OstTitle() const;

    SpcNumericField OstDisc() const;

    SpcTrackField OstTrack() const;

    SpcTextField PublisherName() const;

    SpcNumericField CopyrightYear() const;

    SpcNumericField IntroLength() const;

    SpcNumericField LoopLength() const;

    SpcNumericField EndLength() const;

    SpcBinaryField MutedVoices() const;

    SpcNumericField LoopTimes() const;

    SpcNumericField PreampLevel() const;

    void SetSongTitle(std::string value);

    void SetGameTitle(std::string value);

    void SetDumperName(std::string value);

    void SetComments(std::string value);

    void SetDateDumped(std::string value);

    void SetSongLength(std::string value);

    void SetFadeLength(std::string value);

    void SetSongArtist(std::string value);

    void SetDefaultChannelState(std::string value);

    void SetEmulatorUsed(std::string value);

    void SetOstTitle(std::string value);

    void SetOstDisc(std::string value);

    void SetOstTrack(std::string value);

    void SetPublisherName(std::string value);

    void SetCopyrightYear(std::string value);

    void SetIntroLength(std::string value);

    void SetLoopLength(std::string value);

    void SetEndLength(std::string value);

    void SetMutedVoices(std::string value);

    void SetLoopTimes(std::string value);

    void SetPreampLevel(std::string value);

    bool Load();

    bool Save();

    bool Save(std::string outFileName);

    void FileNameToTag(std::string pattern);

    void TagToFileName(std::string pattern);
private:
    std::string fileName;
    bool hasLoaded;
    bool hasExtendedTag;
    bool headerContainsTag;
    SpcHeader header;
    ID666BinaryTag binaryTag;
    ID666TextTag textTag;
    ID666TagType tagType;
    Binary::RawField spcRam;
    Binary::RawField dspRegisters;
    Binary::RawField unused;
    Binary::RawField extraRam;
    Binary::ChunkHeader extendedTagHeader;
    ID666ExtendedTag extendedTag;

    /// @brief Gets the correct field based on the file's tag type.
    /// @tparam T The type of the field.
    /// @param binaryField A reference to the binary version of the field.
    /// @param textField A reference to the text version of the field.
    /// @return The correct version of the field.
    template<typename T>
    T GetField(const T& binaryField, const T& textField) const
    {
        if (tagType == ID666TagType::Binary)
            return binaryField;
        else
            return textField;
    }

    /// @brief Gets the field associated with the specified extended item.
    /// @tparam T The type of the field.
    /// @param item The item to get the field from.
    /// @param id The extended item ID.
    /// @param defaultSize The size to use if no existing item is found.
    /// @return The field to get.
    template<typename T>
    T GetField(ID666ExtendedItem* item, int id, int defaultSize) const
    {
        if (item != nullptr)
        {
            // When the value is stored in the item's data field (in the item's
            // header), we have to create a new field with the correct label 
            // and copy the data over to it.
            if (item->type->Value() == extendedTypeDataInHeader)
            {
                auto field = InitExtendedField<T>(id, extendedTagDataSize);

                for (int i = 0; i < extendedTagDataSize; i++)
                    field->Data()[i] = item->data->Data()[i];

                return *field;
            }

            // In contrast, if the value is stored beyond the header, it will
            // have already been initialized with the proper label and we
            // simply need to cast it to the correct type.
            if (item->extendedData != nullptr)
            {
                SpcField* field = item->extendedData.get();
                T* convertedField = dynamic_cast<T*>(field);
                return *convertedField;
            }
        }

        // If we reach this point, no existing data was found so we initalize
        // an empty field with a default size.
        return *InitExtendedField<T>(id, defaultSize);
    }

    /// @brief Gets the correct field out of the specified fields / items.
    /// @tparam T The type of the field to get.
    /// @param binaryField The binary version of the field.
    /// @param textField The extended version of the field.
    /// @param item The extended item.
    /// @return The correct field.
    template<typename T>
    T GetField(const T& binaryField, 
               const T& textField, 
               ID666ExtendedItem* item) const
    {
        // If the item is not null, the extended version of the field should
        // be used.
        if (item != nullptr)
        {
            if (item->extendedData != nullptr)
            {
                SpcField* field = item->extendedData.get();
                T* convertedField = dynamic_cast<T*>(field);
                return *convertedField;
            }
        }
        
        // Otherwise, determine whether the binary or text version should be
        // used based on the tag type.
        if (tagType == ID666TagType::Binary)
        {
            return binaryField;
        }
        else
        {
            return textField;
        }
    }

    /// @brief Sets the correct field based on tag type.
    /// @tparam T The type of the field being set.
    /// @param cmd The parameters used to set the field.
    /// @param field A reference to the field pointer to set.
    template<typename T>
    void SetField(SetCommand<T> cmd, T*& field)
    {
        if (tagType == ID666TagType::Binary)
            field = cmd.binaryField;
        else
            field = cmd.textField;

        field->SetValue(cmd.value);
    }

    /// @brief Sets the correct field on both regular and extended tags.
    /// @tparam T The type of field to set.
    /// @param cmd The parameters used to set the field.
    /// @param item The extended item to set.
    template<typename T>
    void SetField(SetCommand<T> cmd, std::shared_ptr<ID666ExtendedItem>& item)
    {
        T* field;
        SetField(cmd, field);

        if (cmd.value.size() > field->Size())
            SetExtendedItem(cmd, item);
        else if (item != nullptr)
            item = nullptr;
    }

    /// @brief Sets only the extended item field.
    /// @tparam T The type of field to set.
    /// @param cmd The parameters used to set the field.
    /// @param item The extended item to set the field on.
    template<typename T>
    void SetExtendedItem(SetCommand<T> cmd, 
                         std::shared_ptr<ID666ExtendedItem>& item)
    {
        // If we're setting an extended tag item, it means the file now has
        // extended tag data even if it didn't before.
        hasExtendedTag = true;

        // Initialize a new extended tag item and set it to the correct id and
        // type so it can be written to the file properly.
        item = std::make_shared<ID666ExtendedItem>();
        item->id->SetValue(cmd.extendedID);
        item->type->SetValue(cmd.extendedType);

        if (cmd.extendedType == extendedTypeDataInHeader)
        {
            if (cmd.extendedID == extendedOSTTrackID)
            {
                auto data = InitExtendedField<SpcTrackField>(cmd.extendedID, 
                                                             2);
                data->SetValue(cmd.value);
                item->data = data;
            }
            else if (cmd.extendedID == extendedMutedVoicesID)
            {
                auto data = 
                    InitExtendedField<SpcBinaryField>(cmd.extendedID, 2);
                data->SetValue(cmd.value);
                item->data = data;
            }
            else
            {
                auto data = 
                    InitExtendedField<SpcNumericField>(cmd.extendedID, 2);
                data->SetType(SpcNumericType::Binary);
                data->SetValue(cmd.value);
                item->data = data;
            }
        }
        else
        {
            // Convert the data field pointer to a numeric field (assumes the
            // data is not stored in the extended area).
            auto size = std::static_pointer_cast<SpcNumericField>(item->data);
            size->SetType(SpcNumericType::Binary);

            if (cmd.extendedType == extendedTypeString)
            {
                auto field = 
                    InitExtendedField<SpcTextField>(cmd.extendedID, 
                                                    cmd.value.size());

                // Set the size / data to the size of the value as they should match.
                size->SetValue(cmd.value.size());

                // Allocate padding bytes to ensure we're 32-bit aligned.
                PadItem(item.get());

                field->SetValue(cmd.value);
                item->extendedData = field;
            }
            else if (cmd.extendedType == extendedTypeInteger)
            {
                auto field =
                    InitExtendedField<SpcNumericField>(cmd.extendedID, 4);
                size->SetValue(4);
                field->SetType(SpcNumericType::Binary);
                field->SetValue(cmd.value);
                item->extendedData = field;
            }
        }
    }

    void LoadHeaderItem(std::shared_ptr<ID666ExtendedItem> item);

    void LoadTextItem(std::shared_ptr<ID666ExtendedItem> item, 
                      SpcFileStream& stream);

    void LoadNumericItem(std::shared_ptr<ID666ExtendedItem> item, 
                         SpcFileStream& stream);
};

std::string RemoveInvalidChars(std::string filename);

#endif
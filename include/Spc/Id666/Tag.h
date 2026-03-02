// Tag.h - Declares the Tag class.
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

#ifndef SPC_ID666_TAG_H
#define SPC_ID666_TAG_H

#include <memory>
#include <string>
#include "Spc/Id666/TagType.h"
#include "Spc/Id666/TagFieldInfo.h"
#include "Spc/TextField.h"
#include "Spc/Id666/Extended/FieldInfo.h"
#include "Spc/Id666/Extended/Data.h"
#include "Spc/Id666/Extended/Item.h"

namespace Spc::Id666
{
    inline constexpr size_t tagSize{ 210 };
    inline constexpr size_t tagOffset{ 0x2E };

    class Tag
    {
    public:
        Tag();

        std::shared_ptr<Binary::BufferStream> FieldData() const
        {
            return fieldData;
        }

        std::shared_ptr<Extended::Data> ExtendedData() const
        {
            return extendedData;
        }

        TagType DetermineType() const;

        TextField SongTitle() const;

        TextField GameTitle() const;

        TextField DumperName() const;

        TextField Comments() const;

        DateField DateDumped() const;

        NumericField SongLength() const;

        NumericField FadeLength() const;

        TextField SongArtist() const;

        NumericField DefaultChannelState() const;

        EmulatorField EmulatorUsed() const;

        TextField OstTitle() const;

        NumericField OstDisc() const;

        TrackField OstTrack() const;

        TextField PublisherName() const;

        NumericField CopyrightYear() const;

        NumericField IntroLength() const;

        NumericField LoopLength() const;

        NumericField EndLength() const;

        BinaryField MutedVoices() const;

        NumericField LoopTimes() const;

        NumericField PreampLevel() const;

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

    private:
        std::shared_ptr<Binary::BufferStream> fieldData;
        std::shared_ptr<Extended::Data> extendedData;

        template<typename T>
        std::shared_ptr<T> ReadField(
            std::string label, 
            TagFieldInfo info, 
            Extended::Item* item) const
        {
            std::shared_ptr<T> field;

            if (item != nullptr)
            {
                field = ReadField<T>(label, item);
            }
            else
            {
                field = ReadField<T>(label, info);
            }

            if (field == nullptr)
            {
                field = std::make_shared<T>(label, info.text);
                return field;
            }
            
            return field;
        }

        template<typename T>
        std::shared_ptr<T> ReadField(std::string label, TagFieldInfo info) const
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

            size_t originalPosition = fieldData->Position();
            fieldData->SetPosition(field->Offset() - tagOffset);
            fieldData->Read(field.get());
            fieldData->SetPosition(originalPosition);
            return field;
        }

        template<typename T>
        std::shared_ptr<T> ReadField(std::string label, Extended::Item* item)
            const
        {
            std::shared_ptr<T> field;

            if (item != nullptr)
            {
                if (item->type->ToInt32() == Extended::lengthType)
                {
                    field = std::make_shared<T>(label, Extended::dataInfo);
                    std::memcpy(field->RawData(), 
                                item->data->RawData(), 
                                item->data->Size());
                }
                else if (item->extendedData != nullptr)
                {
                    field = std::static_pointer_cast<T>(item->extendedData);
                }
                else
                {
                    field = std::make_shared<T>(label, Extended::dataInfo);
                }

                // Redundant?
                //field->SetLabel(label);
            }
            else
            {
                field = std::make_shared<T>(label, Extended::dataInfo);
            }

            return field;
        }

        template<typename T>
        void WriteFieldExtendedString(
            TagFieldInfo info,
            Extended::FieldInfo extendedInfo, 
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
                    WriteFieldExtendedString<T>(extendedInfo, 
                                                itemPtrPtr, 
                                                value);
                    WriteField<T>(info, value);
                }
                else
                {
                    WriteField<T>(info, value);
                }
        }

        template<typename T>
        void WriteField(TagFieldInfo info, std::string value)
        {
            std::shared_ptr<T> field;

            if (DetermineType() == TagType::Binary)
            {
                field = std::make_shared<T>("Temp Field", info.binary);
            }
            else
            {
                field = std::make_shared<T>("Temp Field", info.text);
            }

            field->SetValue(value);

            size_t originalPosition = fieldData->Position();
            fieldData->SetPosition(field->Offset() - tagOffset);
            fieldData->Write(field.get());
            fieldData->SetPosition(originalPosition);
        }

        template<typename T>
        void WriteFieldExtended(Extended::FieldInfo extendedInfo,
                                std::shared_ptr<Extended::Item>* itemPtrPtr, 
                                std::string value)
        {
            if (*(itemPtrPtr) == nullptr)
            {
                auto item = std::make_shared<Extended::Item>();
                item->id->SetInt32(extendedInfo.id);
                item->type->SetInt32(extendedInfo.type);

                auto field = std::make_shared<T>("Temp Field", 
                                                 Extended::dataInfo);
                field->SetType(Spc::NumericType::Binary);
                field->SetValue(value);
                std::memcpy(item->data->RawData(), 
                            field->RawData(), 
                            field->Size());

                *(itemPtrPtr) = item;
            }
            else
            {
                auto item = *(itemPtrPtr);
                auto field = std::make_shared<T>("Temp Field", 
                                                 Extended::dataInfo);
                field->SetType(Spc::NumericType::Binary);
                field->SetValue(value);
                std::memcpy(item->data->RawData(), 
                            field->RawData(), 
                            field->Size()); 
            }
        }

        template<typename T>
        void WriteFieldExtendedInt(Extended::FieldInfo extendedInfo,
                                   std::shared_ptr<Extended::Item>* itemPtrPtr, 
                                   std::string value)
        {
            if (*(itemPtrPtr) == nullptr)
            {
                auto item = std::make_shared<Extended::Item>();
                item->id->SetInt32(extendedInfo.id);
                item->type->SetInt32(extendedInfo.type);

                auto data = std::static_pointer_cast<NumericField>(
                    item->data);

                data->SetInt32(Extended::integerSize);
                Spc::FieldInfo info{ Extended::dataOffset, 
                                     Extended::integerSize };
                auto field = std::make_shared<T>("Temp Field", info);
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
                Spc::FieldInfo info{ Extended::dataOffset, 
                                     Extended::integerSize };
                item->extendedData = std::make_shared<T>("Temp Field", 
                                                         info);

                auto extData = std::static_pointer_cast<T>(
                    item->extendedData);
                extData->SetType(Spc::NumericType::Binary);
                extData->SetValue(value);
            }
        }

        template<typename T>
        void WriteFieldExtendedString(
            Extended::FieldInfo extendedInfo,
            std::shared_ptr<Extended::Item>* itemPtrPtr, 
            std::string value)
        {
            if (*(itemPtrPtr) == nullptr)
            {
                auto item = std::make_shared<Extended::Item>();
                item->id->SetInt32(extendedInfo.id);
                item->type->SetInt32(extendedInfo.type);

                auto data = std::static_pointer_cast<NumericField>(
                    item->data);

                data->SetUInt32(static_cast<uint32_t>(value.size()));
                Spc::FieldInfo info{ Extended::dataOffset, 
                                             value.size() };
                auto field = std::make_shared<T>("Temp Field", info);
                field->SetValue(value);
                item->extendedData = field;

                *(itemPtrPtr) = item;  
            }
            else
            {
                auto item = *(itemPtrPtr);

                auto data = std::static_pointer_cast<NumericField>(
                    item->data);

                data->SetUInt32(static_cast<uint32_t>(value.size()));
                Spc::FieldInfo info{ Extended::dataOffset, 
                                             value.size() };
                item->extendedData = std::make_shared<T>("Temp Field", 
                                                         info);
                item->extendedData->SetValue(value);
            }
        }
    };
}

#endif
// ID666Tag.h - Declares the ID666Tag class.
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
#include "Spc/Id666/FieldInfo.h"
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
            FieldInfo info, 
            Extended::Item* item) const
        {
            if (item != nullptr)
                return ReadField<T>(label, item);
            else
                return ReadField<T>(label, info);
        }

        template<typename T>
        std::shared_ptr<T> ReadField(std::string label, FieldInfo info) const
        {
            std::shared_ptr<T> field;

            if (DetermineType() == TagType::Binary)
            {
                field = std::make_shared<T>(label, 
                                            info.binaryOffset, 
                                            info.binarySize);
            }
            else
            {
                field = std::make_shared<T>(label, 
                                            info.textOffset, 
                                            info.textSize);
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
                if (item->type->Value() == Extended::lengthType)
                    field = std::static_pointer_cast<T>(item->data);
                else
                    field = std::static_pointer_cast<T>(item->extendedData);

                field->SetLabel(label);
            }

            return field;
        }

        template<typename T>
        void WriteField(FieldInfo info,
                        Extended::FieldInfo extendedInfo, 
                        std::shared_ptr<Extended::Item>* itemPtrPtr, 
                        std::string value)
        {
            if (extendedInfo.type == Extended::stringType)
            {
                size_t fieldSize;

                if (DetermineType() == TagType::Binary)
                    fieldSize = info.binarySize;
                else
                    fieldSize = info.textSize;

                if (value.size() > fieldSize)
                {
                    WriteField<T>(extendedInfo, itemPtrPtr, value);
                    WriteField<T>(info, value);
                }
                else
                {
                    WriteField<T>(info, value);
                }
            }
            else
            {
                WriteField<T>(extendedInfo, itemPtrPtr, value);
                WriteField<T>(info, value);
            }
        }

        template<typename T>
        void WriteField(FieldInfo info, std::string value)
        {
            std::shared_ptr<T> field;

            if (DetermineType() == TagType::Binary)
            {
                field = std::make_shared<T>("Temp Field", 
                                            info.binaryOffset, 
                                            info.binarySize);
            }
            else
            {
                field = std::make_shared<T>("Temp Field", 
                                            info.textOffset, 
                                            info.textSize);
            }

            field->SetValue(value);

            size_t originalPosition = fieldData->Position();
            fieldData->SetPosition(field->Offset() - tagOffset);
            fieldData->Write(field.get());
            fieldData->SetPosition(originalPosition);
        }

        template<typename T>
        void WriteField(Extended::FieldInfo extendedInfo,
                        std::shared_ptr<Extended::Item>* itemPtrPtr, 
                        std::string value)
        {
            if (*(itemPtrPtr) == nullptr)
            {
                auto item = std::make_shared<Extended::Item>();
                item->id->SetValue(extendedInfo.id);
                item->type->SetValue(extendedInfo.type);

                if (item->type->Value() == Extended::lengthType)
                {
                    auto field = std::make_shared<T>("Temp Field",
                                                     Extended::dataOffset, 
                                                     Extended::dataSize);
                    field->SetValue(value);
                    std::memcpy(item->data->RawData(), 
                                field->RawData(), 
                                field->Size());
                }
                else
                {
                    auto data = std::static_pointer_cast<NumericField>(
                        item->data);

                    if (item->type->Value() == Extended::stringType)
                        data->SetValue(value.size());
                    else
                        data->SetValue(Extended::integerSize);

                    auto field = std::make_shared<T>("Temp Field", 
                                                     Extended::dataOffset, 
                                                     value.size());
                    field->SetValue(value);
                    item->extendedData = field;
                }

                *(itemPtrPtr) = item;
            }
            else
            {
                auto item = *(itemPtrPtr);

                if (item->type->Value() == Extended::lengthType)
                {
                    auto field = std::static_pointer_cast<T>(item->data);
                    field->SetValue(value);
                }
                else
                {
                    auto data = std::static_pointer_cast<NumericField>(
                        item->data);

                    if (item->type->Value() == Extended::stringType)
                        data->SetValue(value.size());
                    else
                        data->SetValue(Extended::integerSize);

                    auto field = std::static_pointer_cast<T>(
                        item->extendedData);
                    field->SetValue(value);
                }
            }
        }
    };
}

#endif
// MockFileStream.h - Declares the MockFileStream class.
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

#ifndef MOCK_FILE_STREAM_H
#define MOCK_FILE_STREAM_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "LibCppBinary.h"

class MockFileStream : public Binary::FileStream 
{
public:
    // FileStream methods
    MOCK_METHOD(std::string, FileName, (), (const, override));
    MOCK_METHOD(std::string, FilePath, (), (const, override));
    MOCK_METHOD(bool, IsOpen, (), (const, override));
    MOCK_METHOD(bool, FileExists, (), (const, override));
    MOCK_METHOD(uintmax_t, FileSize, (), (const, override));
    MOCK_METHOD(Binary::FileMode, Mode, (), (const, override));
    MOCK_METHOD(void, Open, (Binary::FileMode mode), (override));
    MOCK_METHOD(void, Close, (), (override));

    // Stream methods (from Binary::Stream)
    MOCK_METHOD(void, Read, (Binary::DataField* field), (const, override));
    MOCK_METHOD(void, Read, (Binary::DataStructure* structure), (const, override));
    MOCK_METHOD(std::shared_ptr<Binary::ChunkHeader>, FindNextChunk, (std::string ID), (const override));
    MOCK_METHOD(void, Write, (Binary::DataField* field), (override));
    MOCK_METHOD(void, Write, (Binary::DataStructure* structure), (override));
    MOCK_METHOD(uintmax_t, Position, (), (const, override));
    MOCK_METHOD(void, SetPosition, (uintmax_t position), (const, override));
    MOCK_METHOD(uintmax_t, Beginning, (), (const, override));
    MOCK_METHOD(uintmax_t, End, (), (const, override));
};

#endif

/*
 /// @brief Gets the name of the file.
        /// @return A string representing the name of the file.
        virtual std::string FileName() const = 0;

        /// @brief Gets the full path to the file on disk.
        /// @return A string representing the full path to the file.
        virtual std::string FilePath() const = 0;

        /// @brief Determines whether or not the file is open.
        /// @return True if it is open, otherwise false.
        virtual bool IsOpen() const = 0;

        /// @brief Determines whether or not the file exists on disk.
        /// @return True if it exists, otherwise false.
        virtual bool FileExists() const = 0;

        /// @brief Gets the size of the file associated with the stream.
        /// @return The size of the file, in bytes.
        virtual uintmax_t FileSize() const = 0;
        
        /// @brief Determines the mode the file is set to open in.
        /// @return The file mode.
        virtual FileMode Mode() const = 0;

        /// @brief Opens the file in the specified mode.
        /// @param mode The mode to open the file in.
        virtual void Open(FileMode mode) = 0;

        /// @brief Closes the file. 
        virtual void Close() = 0;
*/
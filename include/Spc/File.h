// File.h - Declares the Spc::File class.
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

#ifndef SPC_FILE_H
#define SPC_FILE_H

#include <string>
#include <vector>
#include <LibCppBinary.h>
#include <filesystem>
#include "Spc/Header.h"
#include "Spc/Id666/Tag.h"
#include "Spc/Id666/Pattern/Lexer.h"
#include "Spc/Id666/Pattern/Constants.h"
#include "Spc/Id666/Pattern/Parser.h"
#include "Spc/Id666/Extended/Data.h"
#include "Spc/Id666/Extended/Item.h"
#include "Spc/FileCorruptException.h"
#include "Spc/FileOperationException.h"

namespace Spc
{
    /// @brief Represents an SPC file.
    ///
    /// This class is used for reading and writing to and from SPC files.
    class File
    {
    public:
        /// @brief Constructor; creates a new instance of SPC file.
        ///
        /// This constructor initializes the file with a default 
        /// Binary::FileStream instance.
        ///
        /// @param path The path to the SPC file on disk.
        File(const std::string& path) : 
            path{ path }, 
            ram{ ramInfo.size }, 
            dspRegisters{ dspRegistersInfo.size }, 
            unused{ unusedInfo.size }, 
            extraRam{ extraRamInfo.size },
            fileStream{ nullptr }
        { 
            fileStream = std::make_shared<Binary::StandardFileStream>(path);
        }

        /// @brief Constructor; creates a new instance of SPC file.
        ///
        /// This constructor allows for dependency injection of a custom
        /// Binary::FileStream, which can be useful for testing or for using
        /// different file stream implementations.
        ///
        /// @param path The path to the SPC file on disk.
        /// @param stream The Binary::FileStream to use.
        File(const std::string& path, 
             std::shared_ptr<Binary::FileStream> stream) :
             path{ path },
             ram{ ramInfo.size },
             dspRegisters{ dspRegistersInfo.size }, 
             unused{ unusedInfo.size }, 
             extraRam{ extraRamInfo.size },
             fileStream{ stream }
        { }

        /// @brief Gets the path to the SPC file on disk.
        /// @return The string representation of the file path.
        std::string Path() const { return path; }

        /// @brief Gets the header of the SPC file.
        /// @return A Spc::Header object representing the header.
        Spc::Header Header() const { return header; }

        /// @brief Gets the ID666 tag of the SPC file.
        /// @return A Spc::Id666::Tag object representing the tag.
        Spc::Id666::Tag Tag() const { return tag; }

        /// @brief Gets the SPC RAM dump contained within the file.
        /// @return A Binary::BufferStream containing the RAM dump.
        Binary::BufferStream Ram() const { return ram; }

        /// @brief Gets the DSP registers contained within the SPC file.
        /// @return A Binary::BufferStream containing the DSP registers.
        Binary::BufferStream DspRegisters() const { return dspRegisters; }

        /// @brief Gets the unused portion of the SPC file.
        /// @return A Binary::BufferStream containing the unused portion.
        Binary::BufferStream Unused() const { return unused; }

        /// @brief Gets the extra RAM contained within the SPC file.
        /// @return A Binary::BufferStream containing the extra RAM.
        Binary::BufferStream ExtraRam() const { return extraRam; }

        /// @brief Sets the header of the SPC file.
        /// @param h The Spc::Header object to set.
        void SetHeader(const Spc::Header& h) { header = h; }

        /// @brief Sets the ID666 tag of the SPC file.
        /// @param t The Spc::Id666::Tag object to set.
        void SetTag(const Spc::Id666::Tag& t) { tag = t; }

        /// @brief Sets the SPC RAM dump contained within the file.
        /// @param r The Binary::BufferStream containing the RAM dump.
        void SetRam(const Binary::BufferStream& r) { ram = r; }

        /// @brief Sets the DSP registers contained within the SPC file.
        /// @param d The Binary::BufferStream containing the DSP registers.
        void SetDspRegisters(const Binary::BufferStream& d) 
        {
            dspRegisters = d; 
        }

        /// @brief Sets the unused portion of the SPC file.
        /// @param u The Binary::BufferStream containing the unused portion.
        void SetUnused(const Binary::BufferStream& u) { unused = u; }

        /// @brief Sets the extra RAM contained within the SPC file.
        /// @param e The Binary::BufferStream containing the extra RAM.
        void SetExtraRam(const Binary::BufferStream& e) { extraRam = e; }

        /// @brief Loads the SPC file from disk.
        /// @pre The file path points to a valid SPC file that exists.
        /// @post The file's data is loaded into the class data.
        /// @throws FileOperationException if the file cannot be opened or read.
        /// @throws FileCorruptException if the file is not a valid SPC file.
        void Load();

        /// @brief Saves the SPC file to disk.
        /// @pre The file path points to a valid SPC file that exists.
        /// @post The file on disk is overwritten with the class data.
        /// @throws FileOperationException if the file cannot open or write.
        void Save();

        /// @brief Creates a copy of the file with a new name based on metadata.
        ///
        /// Uses the specified pattern to determine what the copy file should be
        /// named based on the tag metadata. The pattern consists of 
        /// literal characters and placeholders that bring in values from the
        /// tag. For example, if the tag has a track number of 02 and a song
        /// title of "Intro", you would use the following pattern to get the
        /// file name "02 - Intro.spc":
        ///
        /// %track% - %song%.spc
        ///
        /// Supported placeholders currently include:
        ///
        /// %song% - The song title.
        /// %game% - The game title.
        /// %artist% - The name of the person who dumped the SPC file.
        /// %disc% - The OST disc number.
        /// %track% - The OST track number.
        ///
        /// @param pattern The pattern to select the metadata.
        /// @return True if the file was successfully copied, false otherwise.
        /// @pre Must be a valid pattern with supported placeholders.
        /// @post The file on disk is copied to match the pattern if valid.
        bool TagToFileName(const std::string& pattern);

        /// @brief Updates the tag based on the file name.
        ///
        /// Uses the specified pattern to determine what metadata to set in the 
        /// tag based on the file name. The pattern consists of literal 
        /// characters and placeholders that correspond to tag fields. For 
        /// example, if the file name is "02 - Intro.spc", you would use the
        /// pattern "%track% - %song%.spc" to extract the track number and 
        /// song title from the file name and set them in the tag.
        ///
        /// Supported placeholders currently include:
        ///
        /// %song% - The song title.
        /// %game% - The game title.
        /// %artist% - The name of the person who dumped the SPC file.
        /// %disc% - The OST disc number.
        /// %track% - The OST track number.
        ///
        /// @param pattern The pattern to select the metadata.
        /// @return True if the tag was successfully updated, false otherwise.
        /// @pre Must be a valid pattern with supported placeholders.
        /// @post The tag is updated based on the file name if pattern is valid.
        bool FileNameToTag(const std::string& pattern);
    private:
        std::string path;
        Spc::Header header;
        Spc::Id666::Tag tag;
        Binary::BufferStream ram;
        Binary::BufferStream dspRegisters;
        Binary::BufferStream unused;
        Binary::BufferStream extraRam;
        std::shared_ptr<Binary::FileStream> fileStream;


        /// @brief Loads a string type item from the extended tag data.
        /// @param item The extended tag item to load into.
        /// @param sizeRemaining The number of bytes remaining to be read.
        /// @post The item is populated with the string data
        /// @post sizeRemaining is updated.
        /// @throws FileCorruptException if the file appears corrupt.
        void LoadStringItem(std::shared_ptr<Id666::Extended::Item> item,
                            size_t& sizeRemaining);


        /// @brief Loads padding bytes from the extended tag data.
        /// @param item The extended tag item to load padding into.
        /// @param sizeRemaining The number of bytes remaining to be read.
        /// @post The item is updated to reflect the padding
        /// @post sizeRemaining is updated.
        /// @throws FileCorruptException if the file appears corrupt.
        void LoadPadding(std::shared_ptr<Id666::Extended::Item> item,
                         size_t& sizeRemaining);


        /// @brief Loads a length type item from the extended tag data.
        /// @param item The extended tag item to load into.
        /// @post The item is populated with the length type data.
        /// @post sizeRemaining is updated.
        /// @throws FileCorruptException if the file appears corrupt.
        void LoadLengthItem(std::shared_ptr<Id666::Extended::Item> item);


        /// @brief Loads an integer type item from the extended tag data.
        /// @param item The extended tag item to load into.
        /// @param sizeRemaining The number of bytes remaining.
        /// @post The item is populated with the integer type data.
        /// @post sizeRemaining is updated.
        /// @throws FileCorruptException if the file appears corrupt.
        void LoadIntegerItem(std::shared_ptr<Id666::Extended::Item> item,
                             size_t& sizeRemaining);


        /// @brief Matches a numeric pattern node against the string stream.
        /// @param stream The string stream to match against.
        /// @param fileName The full file name being matched.
        /// @param node The current pattern node to match.
        /// @param nextNode Pointer to the next pattern node.
        /// @param numericString The parsed numeric string value.
        /// @return True if the numeric pattern matches, false otherwise.
        bool MatchNumeric(std::stringstream& stream, 
                  const std::string& fileName,
                  Id666::Pattern::Node node,
                  Id666::Pattern::Node* nextNode,
                  std::string& numericString);


        /// @brief Matches a text pattern node against the string stream.
        /// @param stream The string stream to match against.
        /// @param fileName The full file name being matched.
        /// @param node The current pattern node to match.
        /// @param nextNode Pointer to the next pattern node.
        /// @param textString The parsed text string value.
        /// @return True if the text pattern matches, false otherwise.
        bool MatchText(std::stringstream& stream,
                   const std::string& fileName,
                   Id666::Pattern::Node node,
                   Id666::Pattern::Node* nextNode,
                   std::string& textString);
    };

    /// @brief Matches a literal pattern node against the string stream.
    /// @param stream The string stream to match against.
    /// @param node The pattern node representing the literal to match.
    /// @return True if the literal matches the stream, false otherwise.
    bool MatchLiteral(std::stringstream& stream, Id666::Pattern::Node node);

    /// @brief Checks if the end of the string stream has been reached.
    /// @param stream The string stream to check.
    /// @return True if the stream is at the end, false otherwise.
    bool MatchEnd(std::stringstream& stream);

    /// @brief Parses a pattern string into a sequence of pattern nodes.
    /// @param pattern The pattern string to parse.
    /// @return A vector of pattern nodes representing the parsed pattern.
    std::vector<Id666::Pattern::Node> ParsePattern(std::string_view pattern);
}

#endif
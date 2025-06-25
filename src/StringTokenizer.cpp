// StringTokenizer.cpp - Defines the StringTokenizer class.
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

#include "StringTokenizer.h"

using namespace Spc;

void StringTokenizer::ParsePattern(std::string pattern)
{
    constexpr char noMoreChars{ -1 };
    std::stringstream patternStream{ pattern };
    std::stringstream delimiterStream;
    std::stringstream tokenNameStream;
    bool isTokenName{ false };

    while (!patternStream.eof())
    {
        char next = patternStream.get();

        if (next == noMoreChars)
        {
            AddDelimiter(delimiterStream);
            break;
        }

        if (!isTokenName)
        {
            if (next == '%')
            {
                isTokenName = true;
                AddDelimiter(delimiterStream);
            }
            else
            {
                delimiterStream << next;
            }
        }
        else
        {
            if (next == '%')
            {
                isTokenName = false;
                AddToken(tokenNameStream);
            }
            else
            {
                tokenNameStream << next;
            }
        }
    }
}

std::vector<std::shared_ptr<StringToken>> StringTokenizer::Tokenize(
    std::string text)
{
    std::string remainingText{ text };
    std::vector<std::shared_ptr<StringToken>> tokens;

    for (int i = 0; i < segments.size(); i++)
    {
        std::shared_ptr<StringSegment> segment = segments[i];
        std::shared_ptr<StringSegment> nextSegment;

        if (i + 1 < segments.size())
            nextSegment = segments[i + 1];

        if (segment->SegmentType() == StringSegmentType::Token)
        {
            auto token = std::static_pointer_cast<StringToken>(segment);

            if (nextSegment != nullptr)
                ParseToken(token, nextSegment, remainingText);
            else
                ParseToken(token, remainingText);

            tokens.push_back(token);
        }
        else
        {
            auto delim = std::static_pointer_cast<StringDelimiter>(segment);
            ParseDelimiter(delim, remainingText);
        }
    }

    if (remainingText.length() > 0 || tokens.size() == 0)
        throw std::invalid_argument{ "Text does not match pattern" };

    return tokens;
}

void StringTokenizer::AddDelimiter(std::stringstream& stream)
{
    std::string delimiter = stream.str();

    if (delimiter.length() > 0)
    {
        segments.push_back(std::make_shared<StringDelimiter>(delimiter));
        stream = std::stringstream{ };
    }
}

void StringTokenizer::AddToken(std::stringstream& stream)
{
    std::string tokenName = stream.str();
    auto token = InitToken(tokenName);
    stream = std::stringstream{ };
    
    if (token != nullptr)
        segments.push_back(token);
    else
        throw std::invalid_argument{ "Invalid token name" };
}

std::shared_ptr<StringToken> StringTokenizer::InitToken(std::string name)
{
    if (name == "song")
        return std::make_shared<StringToken>("song", StringValueType::Text);
    else if (name == "game")
        return std::make_shared<StringToken>("game", StringValueType::Text);
    else if (name == "artist")
        return std::make_shared<StringToken>("artist", StringValueType::Text);
    else if (name == "track")
        return std::make_shared<StringToken>("track", StringValueType::Numeric);
    else
        return nullptr;
}

void StringTokenizer::ParseToken(std::shared_ptr<StringToken> token, 
                                 std::string& text)
{
    std::stringstream valueStream;
    int nextIndex = 0;

    for (int i = 0; i < text.length(); i++)
    {
        if (token->ValueType() == StringValueType::Numeric)
        {
            if (text[i] >= 0x30 && text[i] <= 0x39)
            {
                valueStream << text[i];
            }
            else
            {
                nextIndex = i;
                break;
            }
        }
        else
        {
            if (text[i] >= 0x30 && text[i] <= 0x39)
            {
                nextIndex = i;
                break;
            }
            else
            {
                valueStream << text[i];
            }
        }

        if (i == text.length() - 1)
            nextIndex = i;
    }

    token->SetValue(valueStream.str());
    text = text.substr(nextIndex);
}

void StringTokenizer::ParseToken(std::shared_ptr<StringToken> token,
                                 std::shared_ptr<StringSegment> next,
                                 std::string& text)
{
    if (next->SegmentType() == StringSegmentType::Delimiter)
    {
        auto delimiter = std::static_pointer_cast<StringDelimiter>(next);
        int index = delimiter->GetIndex(text);

        if (index == -1)
            throw std::invalid_argument{ "Text does not match pattern" };

        std::string tokenString = text.substr(0, index);
        token->SetValue(tokenString);
        text = text.substr(index);
        return;
    }
    else
    {
        ParseToken(token, text);
    }
}

void StringTokenizer::ParseDelimiter(
    std::shared_ptr<StringDelimiter> delimiter,
    std::string& text)
{
    std::string value = delimiter->Value();

    if (value.length() > text.length())
        throw std::invalid_argument{ "Text does not match pattern" };

    for (int i = 0; i < value.length(); i++)
    {
        if (text[i] != value[i])
            throw std::invalid_argument{ "Text does not match pattern" };
    }

    text = text.substr(value.length());
}
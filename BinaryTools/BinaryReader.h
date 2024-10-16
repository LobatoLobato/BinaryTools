#pragma once
#include "MemoryBuffer.h"
#include <fstream>
#include <string>
#include <span>
#include <vector>
#include <string_view>

struct MemoryBuffer;


//Class that can read binary data either from a file or from a fixed size buffer
//depending on the constructor used.
class BinaryReader
{
public:
    //Reads binary data from file at path
    explicit BinaryReader(std::string_view inputPath);
    //Reads binary data from fixed size memory buffer
    BinaryReader(char* buffer, uint32_t sizeInBytes);
    //Reads binary data from fixed size memory buffer
    [[maybe_unused]] explicit BinaryReader(std::span<const uint8_t> buffer);
    ~BinaryReader();

    [[maybe_unused]] [[nodiscard]] uint8_t ReadUint8();

    [[maybe_unused]] [[nodiscard]] uint16_t ReadUint16();
    [[nodiscard]] uint32_t ReadUint32();

    [[maybe_unused]] [[nodiscard]] uint64_t ReadUint64();

    [[maybe_unused]] [[nodiscard]] int8_t ReadInt8();

    [[maybe_unused]] [[nodiscard]] int16_t ReadInt16();
    [[nodiscard]] int32_t ReadInt32();

    [[maybe_unused]] [[nodiscard]] int64_t ReadInt64();

    [[nodiscard]] char ReadChar();
    [[nodiscard]] wchar_t ReadCharWide();
    [[nodiscard]] std::string ReadNullTerminatedString();

    [[maybe_unused]] [[nodiscard]] std::string ReadFixedLengthString(size_t length);

    [[maybe_unused]] [[nodiscard]] std::wstring ReadNullTerminatedStringWide();

    [[maybe_unused]] [[nodiscard]] std::wstring ReadFixedLengthStringWide(size_t length);

    [[maybe_unused]] [[nodiscard]] std::vector<std::string> ReadSizedStringList(size_t listSize);
    [[nodiscard]] char PeekChar();

    [[maybe_unused]] [[nodiscard]] uint32_t PeekUint32();
    [[nodiscard]] wchar_t PeekCharWide();

    [[nodiscard]] float ReadFloat();

    [[maybe_unused]] [[nodiscard]] double ReadDouble();

    [[maybe_unused]] [[nodiscard]] std::vector<uint8_t> ReadBytes(size_t count);
    void ReadToMemory(void* destination, size_t size);

    [[maybe_unused]] void ReadToMemory(std::vector<uint8_t>& destination, size_t size);

    void SeekBeg(size_t absoluteOffset);

    [[maybe_unused]] void SeekCur(size_t relativeOffset);
    void SeekReverse(size_t relativeOffset); //Move backwards from the current stream position
    void Skip(size_t bytesToSkip);

    [[maybe_unused]] size_t Align(size_t alignmentValue = 2048);

    [[nodiscard]] size_t Position() const;

    [[maybe_unused]] size_t Length();

private:
    std::istream* stream_ = nullptr;
    basic_memstreambuf* buffer_ = nullptr;
};


#pragma once

#include <string>
#include <fstream>
#include <span>
#include <sstream>
#include <vector>

struct MemoryBuffer;

//Class that can write binary data either from a file or from a fixed size buffer
//depending on the constructor used.
class BinaryWriter {
public:
    //Writes binary data from file at path. If truncate == true any existing file contents will be cleared
    BinaryWriter();

    [[maybe_unused]] explicit BinaryWriter(const std::string& inputPath, bool truncate = true);

    //Writes binary data from fixed size memory buffer
    [[maybe_unused]] BinaryWriter(char* buffer, uint32_t sizeInBytes);

    ~BinaryWriter();

    [[maybe_unused]] void Flush();

    void WriteUint8(uint8_t value);

    [[maybe_unused]] void WriteUint16(uint16_t value);

    void WriteUint32(uint32_t value);

    [[maybe_unused]] void WriteUint64(uint64_t value);

    [[maybe_unused]] void WriteInt8(int8_t value);

    [[maybe_unused]] void WriteInt16(int16_t value);

    void WriteInt32(int32_t value);

    [[maybe_unused]] void WriteInt64(int64_t value);

    void WriteChar(char value);

    //Write string to output with null terminator
    [[maybe_unused]] void WriteNullTerminatedString(const std::string& value);

    //Write string to output without null terminator
    [[maybe_unused]] void WriteFixedLengthString(const std::string& value);

    void WriteFloat(float value);

    [[maybe_unused]] void WriteDouble(double value);

    void WriteFromMemory(const void* data, size_t size);

    template<typename T>
    [[maybe_unused]] void Write(const T& data) {
      //Don't allow T to be a pointer to avoid accidentally writing the value of a pointer instead of what it points to.
      static_assert(!std::is_pointer<T>(), "BinaryWriter::Write<T> requires T to be a non pointer type.");
      WriteFromMemory(&data, sizeof(T));
    }

    template<typename T>
    [[maybe_unused]] void Write(const std::vector<T>& data) {
      WriteFromMemory(data.data(), data.size());
    }

    template<typename T>
    [[maybe_unused]] void WriteSpan(std::span<const T> data) {
      WriteFromMemory(data.data(), data.size_bytes());
    }

    template<typename T>
    [[maybe_unused]] void WriteSpan(std::span<T> data) {
      WriteFromMemory(data.data(), data.size_bytes());
    }

    void SeekBeg(size_t absoluteOffset);

    [[maybe_unused]] void SeekCur(size_t relativeOffset);

    void Skip(size_t bytesToSkip);

    void WriteNullBytes(size_t bytesToWrite);

    //Static method for calculating alignment pad from pos and alignment. Does not change position since static
    static size_t CalcAlign(size_t position, size_t alignmentValue = 2048);

    //Aligns stream to alignment value. Returns padding byte count
    [[maybe_unused]] size_t Align(size_t alignmentValue = 2048);

    [[nodiscard]] size_t Position() const;

    size_t Length();

    [[maybe_unused]] std::vector<uint8_t> GetBuffer() {
      auto* ss = dynamic_cast<std::stringstream*>(stream_);
      if (ss == nullptr) { return {}; }

      return {
        std::istreambuf_iterator<char>{*ss},
        std::istreambuf_iterator<char>{}
      };
    }

    [[maybe_unused]] const std::ostream* GetStream() {
      return stream_;
    }

private:
    std::ostream* stream_ = nullptr;
    MemoryBuffer* buffer_ = nullptr;
};


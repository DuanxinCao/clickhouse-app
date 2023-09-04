#pragma once

#include <memory>
#include <string>

#include "Noncopyable.h"
#include "clickhouse/block.h"

namespace clickhouse {
class LocalBlock : public Noncopyable {
public:
    static LocalBlock &instance() {
        static LocalBlock localBlock;
        return localBlock;
    }
    int64_t getLong(Block *block, uint64_t row_id, uint64_t column_id);
    std::string getString(Block *block, uint64_t row_id, uint64_t column_id);
    bool getBool(Block *block, uint64_t row_id, uint64_t column_id);
    int8_t getByte(Block *block, uint64_t row_id, uint64_t column_id);
    int16_t getShort(Block *block, uint64_t row_id, uint64_t column_id);
    int32_t getInt(Block *block, uint64_t row_id, uint64_t column_id);
    float_t getFloat32(Block *block, uint64_t row_id, uint64_t column_id);
    double_t getFloat64(Block *block, uint64_t row_id, uint64_t column_id);
    bool hasNull(Block *block, uint64_t column_id);
    uint64_t numNull(Block *block, uint64_t column_id);
    bool isNullAt(Block *block, uint64_t row_id, uint64_t column_id);

private:
    ~LocalBlock();
    LocalBlock();
};
} // namespace clickhouse
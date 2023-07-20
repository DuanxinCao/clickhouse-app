#pragma once

#include <string>
#include <memory>

#include "clickhouse/block.h"
#include "Noncopyable.h"

namespace clickhouse {
class LocalBlock :public Noncopyable{
public:
    static LocalBlock& instance(){
        static LocalBlock localBlock;
        return localBlock;
    }
    uint64_t getUint64(Block* block,uint64_t row_id,uint64_t column_id);
    std::string getString(Block* block,uint64_t row_id,uint64_t column_id);
    bool getBool(Block* block,uint64_t row_id,uint64_t column_id);
    int8_t getByte(Block* block,uint64_t row_id,uint64_t column_id);
    int16_t getShort(Block* block,uint64_t row_id,uint64_t column_id);
    int32_t getInt(Block* block,uint64_t row_id,uint64_t column_id);
    float_t getFloat32(Block* block,uint64_t row_id,uint64_t column_id);
    double_t getFloat64(Block* block,uint64_t row_id,uint64_t column_id);


private:
    ~LocalBlock();
    LocalBlock();

};
} // namespace clickhouse
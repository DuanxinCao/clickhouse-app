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

private:
    ~LocalBlock();
    LocalBlock();

};
} // namespace clickhouse
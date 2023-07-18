#include "LocalBlock.h"
#include <clickhouse/client.h>

namespace clickhouse {

LocalBlock::LocalBlock() {
}

LocalBlock::~LocalBlock() {
}

uint64_t LocalBlock::getUint64(Block *block, uint64_t row_id, uint64_t column_id) {
    return block->operator[](column_id)->As<ColumnUInt64>()->At(row_id);
}
std::string LocalBlock::getString(Block *block, uint64_t row_id, uint64_t column_id) {
    return std::string(block->operator[](column_id)->As<ColumnString>()->At(row_id));
}

} // namespace clickhouse
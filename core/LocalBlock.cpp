#include "LocalBlock.h"
#include <clickhouse/client.h>
#include <iostream>

namespace clickhouse {

LocalBlock::LocalBlock() {
}

LocalBlock::~LocalBlock() {
}

int64_t LocalBlock::getLong(Block *block, uint64_t row_id, uint64_t column_id) {
    return block->operator[](column_id)->As<ColumnInt64>()->At(row_id);
}
std::string LocalBlock::getString(Block *block, uint64_t row_id, uint64_t column_id) {
    return std::string(block->operator[](column_id)->As<ColumnString>()->At(row_id));
}

bool LocalBlock::getBool(clickhouse::Block *block, uint64_t row_id, uint64_t column_id) {
    return block->operator[](column_id)->As<ColumnUInt8>()->At(row_id);
}

int8_t LocalBlock::getByte(Block *block, uint64_t row_id, uint64_t column_id) {
    return block->operator[](column_id)->As<ColumnInt8>()->At(row_id);
}
int16_t LocalBlock::getShort(Block *block, uint64_t row_id, uint64_t column_id) {
    return block->operator[](column_id)->As<ColumnInt16>()->At(row_id);
}
int32_t LocalBlock::getInt(Block *block, uint64_t row_id, uint64_t column_id) {
    return block->operator[](column_id)->As<ColumnInt32>()->At(row_id);
}
float_t LocalBlock::getFloat32(Block *block, uint64_t row_id, uint64_t column_id){
    return block->operator[](column_id)->As<ColumnFloat32>()->At(row_id);
}
double_t LocalBlock::getFloat64(Block *block, uint64_t row_id, uint64_t column_id){
    return block->operator[](column_id)->As<ColumnFloat64>()->At(row_id);
}
bool LocalBlock::hasNull(clickhouse::Block *block, uint64_t column_id) {
    return false;
}

uint64_t LocalBlock::numNull(clickhouse::Block *block,  uint64_t column_id) {
    return 0;
}

bool LocalBlock::isNullAt(clickhouse::Block *block, uint64_t row_id, uint64_t column_id) {
    return false;
}


} // namespace clickhouse
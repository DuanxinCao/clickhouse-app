#include "Executor.h"

#include <iostream>

namespace clickhouse {
Executor::Executor(std::shared_ptr<Client> client) {
    this->client_ = client;
}

Executor::~Executor() {
}

void Executor::selectQuery(const std::string &query) {
    client_->Select(query, [&](std::shared_ptr<Block> block) {
        if(block->GetColumnCount()==0 || block->GetRowCount() ==0){

        }else{
            blocks_.emplace(block);
            std::cout << "------block from clickhouse start " << std::endl;
//            for (size_t i = 0; i < block->GetRowCount(); ++i) {
//                std::cout << block->operator[](0)->As<ColumnUInt64>()->At(i) << " "
//                          << block->operator[](1)->As<ColumnString>()->At(i) << "\n";
//            }
            std::cout << "------block from clickhouse end " << std::endl;
        }
    });
}

bool Executor::hasNext() {
    return !blocks_.empty();
}

Block *Executor::next() {
    std::shared_ptr<Block> block = blocks_.front();
    blocks_poped_.emplace(block);
    blocks_.pop();
    return &*block;
}

} // namespace clickhouse
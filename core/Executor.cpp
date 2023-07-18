#include "Executor.h"

#include <iostream>

namespace clickhouse {
Executor::Executor(std::shared_ptr<Client> client) {
    this->client_ = client;
    block_ = nullptr;
}

Executor::~Executor() {
}

std::shared_ptr<Block> Executor::selectQuery(const std::string &query) {
    client_->Select(query, [&](std::shared_ptr<Block> block) {
        if (block_ == nullptr || block_->GetRowCount() == 0) {
            block_ = block;
        }
        for (size_t i = 0; i < block_->GetRowCount(); ++i) {
//            std::cout << block_->operator[](0)->As<ColumnUInt64>()->At(i) << " "
//                      << block_->operator[](1)->As<ColumnString>()->At(i) << "\n";
        }
    });

    return block_;
}

bool Executor::hasNext() {
    return false;
}

Block *Executor::next() {
    return &*block_;
}

} // namespace clickhouse
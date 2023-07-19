#pragma once

#include <clickhouse/client.h>

#include <memory>
#include <queue>

namespace clickhouse {

class Executor {
public:
    Executor() = default;
    explicit Executor(const std::shared_ptr<Client> client);
    ~Executor();

    void selectQuery(const std::string &query);
    bool hasNext();
    Block* next();

private:
    std::queue<std::shared_ptr<Block>> blocks_;
    std::queue<std::shared_ptr<Block>> blocks_poped_;
    std::shared_ptr<Client> client_;
};

} // namespace clickhouse

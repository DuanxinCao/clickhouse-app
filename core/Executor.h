#pragma once

#include <clickhouse/client.h>

#include <memory>

namespace clickhouse {

class Executor {
public:
    Executor() = default;
    explicit Executor(const std::shared_ptr<Client> client);
    ~Executor();

    std::shared_ptr<Block>selectQuery(const std::string &query);
    bool hasNext();
    Block* next();

private:
    std::shared_ptr<Block> block_;
    std::shared_ptr<Client> client_;
};

} // namespace clickhouse

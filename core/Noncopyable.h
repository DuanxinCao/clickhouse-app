#pragma once

namespace clickhouse {

class Noncopyable {
protected:
    Noncopyable() = default;
    ~Noncopyable() = default;

private:
    Noncopyable(const Noncopyable &) = delete;
    const Noncopyable &operator=(const Noncopyable &) = delete;
};

} // namespace tair::common
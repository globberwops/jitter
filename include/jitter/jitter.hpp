#ifndef JITTER_JITTER_HPP_
#define JITTER_JITTER_HPP_

#include <filesystem>

namespace jitter
{

class Jitter
{
  public:
    Jitter() = default;
    ~Jitter() = default;

    auto Compile(const std::filesystem::path &file_path) -> bool;
};

} // namespace jitter

#endif // JITTER_JITTER_HPP_

#ifndef DYNAMIC_LOADER_HPP_
#define DYNAMIC_LOADER_HPP_

#include <dlfcn.h>
#include <filesystem>

namespace jitter
{

namespace fs = std::filesystem;

class DynamicLoader
{
    const fs::path m_library_path{};
    const int m_flags{};
    void *m_handle{nullptr};

    auto Lookup(const std::string &symbol) -> void *;

  public:
    explicit DynamicLoader(fs::path library_path, int flags = RTLD_NOW);
    DynamicLoader(const DynamicLoader &other) = delete;
    ~DynamicLoader();

    auto Open() -> bool;
    void Close();
    auto operator()() -> bool;
};

} // namespace jitter

#endif // DYNAMIC_LOADER_HPP_

#include "dynamic_loader.hpp"

#include <dlfcn.h>
#include <iostream>
#include <utility>

namespace jitter
{

DynamicLoader::DynamicLoader(fs::path library_path, int flags) : m_library_path(std::move(library_path)), m_flags(flags)
{
}

DynamicLoader::~DynamicLoader()
{
    Close();
}

auto DynamicLoader::Open() -> bool
{
    m_handle = dlopen(m_library_path.c_str(), m_flags);

    if (m_handle == nullptr)
    {
        std::cerr << dlerror() << '\n';
        return false;
    }

    dlerror();

    return true;
}

void DynamicLoader::Close()
{
    if (m_handle != nullptr)
    {
        dlclose(m_handle);
    }
}

auto DynamicLoader::Lookup(const std::string &symbol) -> void *
{
    void *test_func = nullptr;
    test_func = dlsym(m_handle, symbol.c_str());

    if (test_func == nullptr)
    {
        std::cerr << dlerror() << '\n';
    }

    return test_func;
}

auto DynamicLoader::operator()() -> bool
{
    using func_t = bool (*)();
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<func_t>(Lookup(m_library_path.stem()));
}

} // namespace jitter

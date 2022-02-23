#ifndef DYNAMIC_LOADER_HPP_
#define DYNAMIC_LOADER_HPP_

#include <dlfcn.h>
#include <exception>
#include <filesystem>
#include <memory>
#include <utility>

namespace jitter
{

/// \brief The exception class for the DynamicLoader
class DynamicLoaderException : public std::exception
{
    std::string m_description;

  public:
    explicit DynamicLoaderException(std::string description) : m_description(std::move(description))
    {
    }

    [[nodiscard]] auto what() const noexcept -> const char * override
    {
        return m_description.c_str();
    }
};

/// \brief A dynamic loader for shared libraries
class DynamicLoader
{
    struct Deleter
    {
        void operator()(void *handle)
        {
            if (handle != nullptr)
            {
                dlclose(handle);
            }
        }
    };

    std::filesystem::path m_library_path;
    int m_flags{};
    std::unique_ptr<void, Deleter> m_handle;

  public:
    /// \brief The destructor
    ~DynamicLoader() = default;

    /// \brief The default constructor
    DynamicLoader() = default;

    /// \brief The parameterized constructor
    /// \param[in] library_path The path of the shared library to load
    /// \param[in] flags The flags used by dlopen()
    explicit DynamicLoader(std::filesystem::path library_path, int flags = RTLD_NOW)
        : m_library_path(std::move(library_path)), m_flags(flags)
    {
    }

    /// \brief The copy constructor
    DynamicLoader(const DynamicLoader &other) = delete;

    /// \brief The move constructor
    DynamicLoader(DynamicLoader &&other) noexcept
        : m_library_path(std::move(other.m_library_path)), m_flags(other.m_flags), m_handle(std::move(other.m_handle))
    {
    }

    /// \brief The copy assignment operator
    auto operator=(const DynamicLoader &other) -> DynamicLoader & = delete;

    /// \brief The move assignment operator
    auto operator=(DynamicLoader &&other) noexcept -> DynamicLoader &
    {
        m_library_path = other.m_library_path;
        m_flags = other.m_flags;
        m_handle = std::move(other.m_handle);
        return *this;
    }

    /// \brief Set the library path
    /// \param[in] library_path The library path
    void SetLibraryPath(std::filesystem::path library_path) noexcept
    {
        m_library_path = std::move(library_path);
    }

    /// \brief Get the library path
    /// \return The library path
    [[nodiscard]] auto GetLibraryPath() const noexcept -> std::filesystem::path
    {
        return m_library_path;
    }

    /// \brief Set the flags used by dlopen()
    /// \param[in] flags The flags
    void SetFlags(int flags) noexcept
    {
        m_flags = flags;
    }

    /// \brief Set the flags used by dlopen()
    /// \return The flags
    [[nodiscard]] auto GetFlags() const noexcept -> int
    {
        return m_flags;
    }

    /// \brief Dynamically open the shared library
    /// \throw DynamicLoaderException
    void Open() noexcept(false)
    {
        m_handle = std::unique_ptr<void, Deleter>(dlopen(m_library_path.c_str(), m_flags), Deleter());

        if (m_handle == nullptr)
        {
            throw DynamicLoaderException(dlerror());
        }
    }

    /// \brief Close the shared library
    void Close() noexcept
    {
        m_handle.reset();
    }

    /// \brief Lookup a symbol in the open library
    /// \tparam T The function signature of the symbol
    /// \param[in] symbol The name of the symbol
    /// \return The function pointer of the symbol, if found
    /// \throws DynamicLoaderException
    template <typename T> auto Lookup(std::string_view symbol) noexcept(false) -> T
    {
        void *func = nullptr;
        func = dlsym(m_handle.get(), symbol.data());

        if (func == nullptr)
        {
            throw DynamicLoaderException(dlerror());
        }

        return reinterpret_cast<T>(func); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }
};

} // namespace jitter

#endif // DYNAMIC_LOADER_HPP_

#include "jitter/jitter.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>

#include <dlfcn.h>

#include "jitter/dynamic_loader.hpp"

namespace jitter
{

namespace fs = std::filesystem;

auto Jitter::Compile(const fs::path &file_path) -> bool
{
    if (!fs::exists(file_path))
    {
        std::cerr << "Cannot open file: " << file_path << '\n';
        return false;
    }

    // compile the file
    auto out_file_path = file_path;
    out_file_path.replace_extension("so");

    auto compile_command = std::stringstream{};
    compile_command << "g++ -shared -fPIC -g -o " << out_file_path << " " << file_path;

    auto compilation_result = std::system(compile_command.str().c_str());

    if (compilation_result != 0)
    {
        std::cerr << "Cannot compile file: " << file_path << '\n';
        return false;
    };

    // open the library
    auto loader = DynamicLoader{out_file_path.c_str(), RTLD_LAZY};

    try
    {
        loader.Open();
        {
            auto func = loader.Lookup<void()>("jitter_test_file");
            func();
        }
        {
            auto func = loader.Lookup<bool()>("jitter_test_file_return");
            func();
        }
        {
            auto func = loader.Lookup<void(int)>("jitter_test_file_args");
            func(42);
        }
    }
    catch (const DynamicLoaderException &ex)
    {
        std::cerr << ex.what() << '\n';
        return false;
    }

    return true;
}

} // namespace jitter

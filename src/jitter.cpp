#include "jitter/jitter.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>

#include <dlfcn.h>

#include "dynamic_loader.hpp"

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
    if (!loader.Open())
    {
        return false;
    }

    return loader();
}

} // namespace jitter

#include <core/filesystem/filemanip.hpp>

namespace rythe::core::filesystem::literals
{
    byte_vec RYTHE_FUNC operator""_readfile(const char* str, std::size_t len)
    {
        return ::rythe::core::filesystem::read_file(std::string_view(str, len));
    }

    auto RYTHE_FUNC operator""_writefile(const char* str, std::size_t len)
    {
        return[path = std::string_view(str, len)](const byte_vec& container)
        {
            ::rythe::core::filesystem::write_file(path, container);
        };
    }

    bool RYTHE_FUNC operator""_exists(const char* str, std::size_t len)
    {
        return ::rythe::core::filesystem::exists(std::string_view(str, len));
    }
}

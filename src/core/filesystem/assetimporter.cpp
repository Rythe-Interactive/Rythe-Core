#include <core/filesystem/assetimporter.hpp>

namespace rythe::core::filesystem
{
    sparse_map<rsl::id_type, std::vector<std::unique_ptr<detail::resource_converter_base>>> AssetImporter::m_converters;
}

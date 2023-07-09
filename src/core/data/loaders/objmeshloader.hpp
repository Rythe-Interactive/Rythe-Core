#pragma once
#include <core/assets/assets.hpp>
#include <core/data/mesh.hpp>

namespace rythe::core
{
    class ObjMeshLoader : public assets::AssetLoader<mesh>
    {
    public:
        using base = assets::AssetLoader<mesh>;
        using base::asset_ptr;
        using base::import_cfg;
        using base::progress_type;

    private:
        common::result<asset_ptr> loadImpl(rsl::id_type nameHash, const fs::view& file, const import_cfg& settings, progress_type* progress);

    public:
        virtual bool canLoad(const fs::view& file) override;

        virtual common::result<asset_ptr> load(rsl::id_type nameHash, const fs::view& file, const import_cfg& settings) override;
        virtual common::result<asset_ptr> loadAsync(rsl::id_type nameHash, const fs::view& file, const import_cfg& settings, progress_type& progress) override;
    };
}

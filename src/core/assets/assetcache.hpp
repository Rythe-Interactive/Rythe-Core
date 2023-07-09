#pragma once
#include <unordered_map>
#include <vector>
#include <memory>

#include <rsl/type_util>
#include <core/filesystem/filesystem.hpp>
#include <core/common/result.hpp>
#include <core/async/async_operation.hpp>
#include <core/engine/engine.hpp>
#include <core/engine/enginesubsystem.hpp>

#include <core/assets/asset.hpp>
#include <core/assets/assetloader.hpp>
#include <core/assets/import_settings.hpp>

namespace rythe::core::assets
{
    namespace detail
    {
        struct asset_info
        {
            std::string name;
            std::string path;
            rsl::size_type assetLoader;
        };
    }

    template<typename AssetType>
    class AssetCache : public EngineSubSystem<AssetCache<AssetType>>
    {
        AllowPrivateOnShutdown;
        SubSystemInstance(AssetCache);

        template<typename Asset>
        friend class AssetLoader;

        template<typename Asset>
        friend struct asset;

        using base = EngineSubSystem<AssetCache<AssetType>>;
        using asset_ptr = asset<AssetType>;
        using import_cfg = import_settings<AssetType>;
        using loader_type = AssetLoader<AssetType>;
        using progress_type = async::async_progress<common::result<asset_ptr>>;

    private:
        std::unordered_map<rsl::id_type, AssetType> m_cache;
        std::unordered_map<rsl::id_type, detail::asset_info> m_info;

        std::vector<std::unique_ptr<loader_type>> m_loaders;
        std::unordered_map<rsl::id_type, rsl::id_type> m_loaderIds;

        static void onShutdown();

        template<typename... Args>
        static common::result<asset_ptr> createInternal(rsl::id_type nameHash, Args&&... args);

        static const detail::asset_info& info(rsl::id_type nameHash);

        static common::result<asset_ptr> retryLoad(rsl::id_type previousLoader, rsl::id_type nameHash, const std::string& name, const fs::view& file, const import_cfg& settings);
        static common::result<asset_ptr> retryLoadAsync(rsl::id_type previousLoader, rsl::id_type nameHash, const std::string& name, const fs::view& file, const import_cfg& settings, progress_type& progress);

        static void asyncLoadJob(rsl::id_type nameHash, const std::string& name, const fs::view& file, const import_cfg& settings, const std::shared_ptr<progress_type>& progress);

    public:

        static byte reportAssetToEngine();

        template<typename LoaderType>
        static bool hasLoader();

        static bool hasLoaders() noexcept;

        static void addLoader(std::unique_ptr<loader_type>&& loader);
        template<typename LoaderType, typename... Arguments>
        static void addLoader(Arguments&&... args);

        template<typename LoaderType, typename... Arguments>
        static asset_ptr createAsLoader(rsl::id_type nameHash, const std::string& name, const std::string& path, Arguments&&... args);

        static common::result<asset_ptr> load(const fs::view& file);
        static common::result<asset_ptr> load(const fs::view& file, const import_cfg& settings);
        static common::result<asset_ptr> load(const std::string& name, const fs::view& file);
        static common::result<asset_ptr> load(const std::string& name, const fs::view& file, const import_cfg& settings);
        static common::result<asset_ptr> load(rsl::id_type nameHash, const std::string& name, const fs::view& file);
        static common::result<asset_ptr> load(rsl::id_type nameHash, const std::string& name, const fs::view& file, const import_cfg& settings);
        static async::async_operation<common::result<asset_ptr>> loadAsync(const fs::view& file);
        static async::async_operation<common::result<asset_ptr>> loadAsync(const fs::view& file, const import_cfg& settings);
        static async::async_operation<common::result<asset_ptr>> loadAsync(const std::string& name, const fs::view& file);
        static async::async_operation<common::result<asset_ptr>> loadAsync(const std::string& name, const fs::view& file, const import_cfg& settings);
        static async::async_operation<common::result<asset_ptr>> loadAsync(rsl::id_type nameHash, const std::string& name, const fs::view& file);
        static async::async_operation<common::result<asset_ptr>> loadAsync(rsl::id_type nameHash, const std::string& name, const fs::view& file, const import_cfg& settings);

        static asset_ptr create(const std::string& name);
        static asset_ptr create(rsl::id_type nameHash, const std::string& name);
        static asset_ptr create(rsl::id_type nameHash, const std::string& name, const std::string& path);

        static asset_ptr create(const std::string& name, const AssetType& src);
        static asset_ptr create(rsl::id_type nameHash, const std::string& name, const AssetType& src);
        static asset_ptr create(rsl::id_type nameHash, const std::string& name, const std::string& path, const AssetType& src);

        template<typename... Arguments>
        static asset_ptr create(const std::string& name, Arguments&&... args);
        template<typename... Arguments>
        static asset_ptr create(rsl::id_type nameHash, const std::string& name, Arguments&&... args);
        template<typename... Arguments>
        static asset_ptr createWithPath(rsl::id_type nameHash, const std::string& name, const std::string& path, Arguments&&... args);

        static bool has(const std::string& name);
        static bool has(rsl::id_type nameHash);

        static asset_ptr get(const std::string& name);
        static asset_ptr get(rsl::id_type nameHash);

        static void destroy(const std::string& name);
        static void destroy(rsl::id_type nameHash);
        static void destroy(asset_ptr asset);
    };
}

#define ReportAssetType(Type) ANON_VAR(byte, CONCAT(_reportAsset_, Type)) = rythe::core::assets::AssetCache< Type >::reportAssetToEngine();

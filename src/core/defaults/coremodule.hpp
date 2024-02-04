#pragma once
#include "core/data/loaders/gltfmeshloader.hpp"
#include "core/data/loaders/objmeshloader.hpp"
#include "core/data/loaders/stbimageloader.hpp"
#include "core/engine/module.hpp"
#include "core/engine/module.inl"
#include "core/filesystem/basic_resolver.hpp"
#include "core/filesystem/provider_registry.hpp"
// #include <core/compute/context.hpp>

/**
 * @file coremodule.hpp
 */
namespace rythe::core
{
	/**@class CoreModule
	 * @brief Custom module.
	 */
	class CoreModule final : public Module
	{
	public:
		virtual void setup() override
		{
			filesystem::provider_registry::domain_create_resolver<filesystem::basic_resolver>("assets://", "./assets");
			filesystem::provider_registry::domain_create_resolver<filesystem::basic_resolver>("engine://", "./engine");

			assets::AssetCache<mesh>::addLoader<ObjMeshLoader>();
			assets::AssetCache<mesh>::addLoader<GltfMeshLoader>();

			assets::AssetCache<image>::addLoader<GltfFauxImageLoader>();
			assets::AssetCache<image>::addLoader<StbImageLoader>();

			createProcessChain("Update");
		}

		virtual rsl::priority_type priority() override
		{
			return PRIORITY_MAX;
		}
	};
} // namespace rythe::core

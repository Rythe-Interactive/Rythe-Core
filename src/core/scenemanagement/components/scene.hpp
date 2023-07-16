#pragma once
#include <core/engine/system.hpp>
#include <core/scenemanagement/scenemanager.hpp>

namespace rythe::core::scenemanagement
{
    struct scene
    {
    public:
        rsl::id_type id = invalid_id;

        template<typename Archive>
        void serialize(Archive& archive);
    };

    template<typename Archive>
    inline void scene::serialize(Archive& archive)
    {
        std::string name = SceneManager::sceneNames[id];
        archive(cereal::make_nvp("NAME", name));
        id = rsl::nameHash(name);
        SceneManager::sceneNames[id] = name;
    }
}

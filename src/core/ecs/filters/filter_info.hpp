#pragma once
#include <array>
#include <unordered_set>
#include <functional>

#include <core/common/hash.hpp>

/**
 * @file filter_info.hpp
 */

namespace rythe::core::ecs
{
    /**@struct filter_info_base
     * @brief Common base class of all filter_info variants.
     */
    struct filter_info_base
    {
        /**@brief Get variant id through polymorphism.
         */
        virtual rsl::id_type id() RYTHE_PURE;

        /**@brief Check if the filter variant contains a component type.
         * @tparam component_type Type of the component.
         */
        template<typename component_type>
        bool contains() { return contains(make_hash<component_type>()); }

        /**@brief Polymorphically check whether the filter variant contains a certain component type.
         * @param id Local id of the component type.
         */
        virtual bool contains(rsl::id_type id) RYTHE_PURE;

        /**@brief Polymorphically check whether the filter variant overlaps a certain combination of component types.
         * @param components Unordered set of component type ids.
         */
        virtual bool contains(const std::unordered_set<rsl::id_type>& components) RYTHE_PURE;

        virtual ~filter_info_base() = default;
    };

    template<typename... component_types>
    struct filter_info : public filter_info_base
    {
    private:
        template<typename component_type>
        constexpr static rsl::id_type generateId() noexcept
        {
            return make_hash<component_type>();
        }

        template<typename component_type0, typename component_type1, typename... component_typeN>
        constexpr static rsl::id_type generateId() noexcept
        {
            return combine_hash(make_hash<component_type0>(), generateId<component_type1, component_typeN...>());
        }

    public:
        /**@brief The actual id of the filter variant.
         */
        static constexpr rsl::id_type filter_id = generateId<component_types...>();

        /**@brief Array of the individual component type ids.
         */
        static constexpr std::array<rsl::id_type, sizeof...(component_types)> composition = { make_hash<component_types>()... };

        virtual rsl::id_type id();

        virtual bool contains(rsl::id_type id) noexcept;

        virtual bool contains(const std::unordered_set<rsl::id_type>& components);

        constexpr static bool contains_direct(rsl::id_type id) noexcept;
    };
}

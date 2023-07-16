#pragma once
#include <rsl/math>
#include <core/ecs/ecs.hpp>
#include <core/data/mesh.hpp>
#include <rsl/logging>


namespace rythe::core
{
    struct position : public rsl::math::float3
    {
        position() : rsl::math::float3(0, 0, 0) {}
        position(const position&) = default;
        position(position&&) = default;
        position(const rsl::math::float3& src) : rsl::math::float3(src) {}
        position(float x, float y, float z) : rsl::math::float3(x, y, z) {}
        position(float v) : rsl::math::float3(v) {}
        position& operator=(const position&) = default;
        position& operator=(position&&) = default;
        position& operator=(const rsl::math::float3& src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
            return *this;
        }
        position& operator=(rsl::math::float3&& src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
            return *this;
        }
    };

    struct rotation : public rsl::math::quat
    {
        rotation() : rsl::math::quat(1, 0, 0, 0) {}
        rotation(float w, float x, float y, float z) : rsl::math::quat(w, x, y, z) {}
        rotation(const rotation&) = default;
        rotation(rotation&&) = default;
        rotation(const rsl::math::quat& src) : rsl::math::quat(src) {}
        rotation& operator=(const rotation&) = default;
        rotation& operator=(rotation&&) = default;
        rotation& operator=(const rsl::math::quat& src)
        {
            i = src.i;
            j = src.j;
            k = src.k;
            w = src.w;
            return *this;
        }
        rotation& operator=(rsl::math::quat&& src)
        {
            i = src.i;
            j = src.j;
            k = src.k;
            w = src.w;
            return *this;
        }

        R_NODISCARD rsl::math::float3 right() const
        {
            return rsl::math::float3x3(*this) * rsl::math::float3::right;
        }

        R_NODISCARD rsl::math::float3 up() const
        {
            return rsl::math::float3x3(*this) * rsl::math::float3::up;
        }

        R_NODISCARD rsl::math::float3 forward() const
        {
            return rsl::math::float3x3(*this) * rsl::math::float3::forward;
        }

        R_NODISCARD rsl::math::float3x3 matrix() const
        {
            return rsl::math::float3x3(*this);
        }

        R_NODISCARD static rotation lookat(rsl::math::float3 position, rsl::math::float3 center, rsl::math::float3 up = rsl::math::float3::up);
    };

    R_NODISCARD inline rotation rotation::lookat(rsl::math::float3 position, rsl::math::float3 center, rsl::math::float3 up)
    {
        return rsl::math::quat::conjugate(rsl::math::normalize(rsl::math::quat::look_at(position, center, up)));
    }

    struct scale : public rsl::math::float3
    {
        scale() : rsl::math::float3(1, 1, 1) {}
        scale(float x, float y, float z) : rsl::math::float3(x, y, z) {}
        scale(float v) : rsl::math::float3(v) {}
        scale(const scale&) = default;
        scale(scale&&) = default;
        scale(const rsl::math::float3& src) : rsl::math::float3(src) {}
        scale& operator=(const scale&) = default;
        scale& operator=(scale&&) = default;
        scale& operator=(const rsl::math::float3& src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
            return *this;
        }
        scale& operator=(rsl::math::float3&& src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
            return *this;
        }

    };

    struct transform : public ecs::archetype<position, rotation, scale>
    {
        using base = ecs::archetype<position, rotation, scale>;
        using base::archetype;

        R_NODISCARD rsl::math::float4x4 from_world_matrix()
        {
            return rsl::math::inverse(to_world_matrix());
        }

        R_NODISCARD rsl::math::float4x4 to_world_matrix()
        {
            if (owner->parent)
            {
                transform parentTrans = owner->parent.get_component<transform>();
                if (parentTrans)
                    return parentTrans.to_world_matrix() * to_parent_matrix();
            }
            return to_parent_matrix();
        }

        R_NODISCARD rsl::math::float4x4 from_parent_matrix()
        {
            return rsl::math::inverse(to_parent_matrix());
        }

        R_NODISCARD rsl::math::float4x4 to_parent_matrix()
        {
            auto [position, rotation, scale] = values();
            return rsl::math::compose(scale, rotation, position);
        }

    };

    struct velocity : public rsl::math::float3
    {
        velocity() : rsl::math::float3(0, 0, 0) {}
        velocity(const velocity&) = default;
        velocity(velocity&&) = default;
        velocity(const rsl::math::float3& src) : rsl::math::float3(src) {}
        velocity(float x, float y, float z) : rsl::math::float3(x, y, z) {}
        velocity(float v) : rsl::math::float3(v) {}
        velocity& operator=(const velocity&) = default;
        velocity& operator=(velocity&&) = default;
        velocity& operator=(const rsl::math::float3& src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
            return *this;
        }
        velocity& operator=(rsl::math::float3&& src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
            return *this;
        }
    };

    struct mesh_filter
    {
        assets::asset<mesh> shared_mesh;

        explicit mesh_filter(const assets::asset<mesh>& src) : shared_mesh(src) {}

        RULE_OF_5_NOEXCEPT(mesh_filter);

        bool operator==(const mesh_filter& other) const { return shared_mesh == other.shared_mesh; }
    };
}

//ManualReflector(rythe::core::position, x, y, z);
//ManualReflector(rythe::core::rotation, x, y, z, w);
//ManualReflector(rythe::core::scale, x, y, z);
//ManualReflector(rythe::core::velocity, x, y, z);
//ManualReflector(rythe::core::mesh_filter, shared_mesh);

#if !defined(DOXY_EXCLUDE)
namespace std // NOLINT(cert-dcl58-cpp)
{
    template <::std::size_t I>
    struct tuple_element<I, rythe::core::transform>
    {
        using type = typename rsl::element_at_t<I, rythe::core::position, rythe::core::rotation, rythe::core::scale>;
    };

    template<>
    struct tuple_size<rythe::core::transform>
        : public std::integral_constant<std::size_t, 3>
    {
    };

    template<>
    struct tuple_size<const rythe::core::transform>
        : public std::integral_constant<std::size_t, 3>
    {
    };

    template<>
    struct tuple_size<volatile rythe::core::transform>
        : public std::integral_constant<std::size_t, 3>
    {
    };

    template<>
    struct tuple_size<const volatile rythe::core::transform>
        : public std::integral_constant<std::size_t, 3>
    {
    };

}
#endif

#if !defined(DOXY_EXCLUDE)
namespace fmt
{
    using namespace rythe::core;

    template <>
    struct fmt::formatter<position> {
        char presentation = 'f';

        constexpr auto parse(format_parse_context& ctx) {

            auto it = ctx.begin(), end = ctx.end();
            if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

            if (it != end && *it != '}')
                throw format_error("invalid format");

            return it;
        }

        template <typename FormatContext>
        auto format(const position& p, FormatContext& ctx) {
            return format_to(
                ctx.out(),

                presentation == 'f' ? "{:f}" : "{:e}",
                static_cast<rsl::math::float3>(p));
        }
    };

    template <>
    struct fmt::formatter<velocity> {
        char presentation = 'f';

        constexpr auto parse(format_parse_context& ctx) {

            auto it = ctx.begin(), end = ctx.end();
            if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

            if (it != end && *it != '}')
                throw format_error("invalid format");

            return it;
        }

        template <typename FormatContext>
        auto format(const velocity& p, FormatContext& ctx) {
            return format_to(
                ctx.out(),

                presentation == 'f' ? "{:f}" : "{:e}",
                static_cast<rsl::math::float3>(p));
        }
    };

    template <>
    struct fmt::formatter<rotation> {
        char presentation = 'f';

        constexpr auto parse(format_parse_context& ctx) {

            auto it = ctx.begin(), end = ctx.end();
            if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

            if (it != end && *it != '}')
                throw format_error("invalid format");

            return it;
        }

        template <typename FormatContext>
        auto format(const rotation& r, FormatContext& ctx) {
            return format_to(
                ctx.out(),

                presentation == 'f' ? "{:f}" : "{:e}",
                static_cast<rsl::math::quat>(r));
        }
    };

    template <>
    struct fmt::formatter<scale> {
        char presentation = 'f';

        constexpr auto parse(format_parse_context& ctx) {

            auto it = ctx.begin(), end = ctx.end();
            if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

            if (it != end && *it != '}')
                throw format_error("invalid format");

            return it;
        }

        template <typename FormatContext>
        auto format(const scale& s, FormatContext& ctx) {
            return format_to(
                ctx.out(),

                presentation == 'f' ? "{:f}" : "{:e}",
                static_cast<rsl::math::float3>(s));
        }
    };
}
#endif

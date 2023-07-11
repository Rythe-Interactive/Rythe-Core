#pragma once
#include <rsl/type_util>
#include <rsl/primitives>
#include <rsl/math>
#include <rsl/containers>

#include "core/containers/containers.hpp"
#include "core/filesystem/filesystem.hpp"
#include "core/assets/assets.hpp"


/**
 * @file image.hpp
 */

namespace rythe::core
{
    /**@brief Internal binary data representation per color channel.
     */
    enum struct channel_format : rsl::uint
    {
        depth_stencil = 0,
        eight_bit = 1,
        sixteen_bit = 2,
        float_hdr = 4
    };

    /**@brief Internal channel layout of the colors.
     */
    enum struct image_components : int
    {
        grey = 1,
        grey_alpha = 2,
        rgb = 3,
        rgba = 4,
        depth = 5,
        stencil = 6,
        depth_stencil = 7
    };

    /**@class image
     * @brief Object encapsulating the binary representation of an image.
     */
    struct image final
    {
        image(const rsl::math::int2& res, channel_format format, image_components comp, const data_view<rsl::byte>& data);

        NO_DEF_CTOR_RULE5_NOEXCEPT(image);

        const rsl::math::int2& resolution() const noexcept;
        const channel_format& format() const noexcept;
        const image_components& components() const noexcept;

        /**@brief Get the binary representation of the image with different pointer types.
         *        Each pointer type is only enabled if the channel format is the same.
         *        The void* type is always enabled.
         */
        template<typename T>
        data_view<T> raw_data();

        template<typename T>
        const data_view<T> raw_data() const;

        common::result<void> apply_raw(bool lazyApply = true);

        /**@brief Convert the binary image representation to a more usable representation if it hasn't been converted before and return the new representation.
         * @return const std::vector<math::color>& List with all the colors in the image.
         */
        common::result<std::reference_wrapper<const std::vector<rsl::math::color>>> read_colors() const;
        common::result<void> write_colors(const std::vector<rsl::math::color>& colors);

        /**@brief Get the data size of the binary data.
         */
        rsl::size_type data_size() const;

        bool operator==(const image& other) const noexcept;

        rsl::byte* data() noexcept;

    private:
        common::result<void> _apply_raw_impl() const;

        rsl::math::int2 m_resolution;
        channel_format m_format;
        image_components m_components;

        mutable data_view<rsl::byte> m_data;
        mutable std::optional<std::vector<rsl::math::color>> m_colors = std::nullopt;
    };

    ReportAssetType(image);

    namespace assets
    {
        template<>
        struct import_settings<image>
        {
            bool detectFormat : 1;
            bool detectComponents : 1;
            bool flipVertical : 1;
            channel_format fileFormat;
            image_components components;

            constexpr import_settings(bool dform = true, bool dcomp = true, bool flipv = true, channel_format format = channel_format::eight_bit, image_components comp = image_components::rgba) noexcept :
                detectFormat(dform),
                detectComponents(dcomp),
                flipVertical(flipv),
                fileFormat(format),
                components(comp)
            {}

            NO_DEF_CTOR_RULE5_NOEXCEPT(import_settings);
        };
    }
}

#include <core/data/image.inl>

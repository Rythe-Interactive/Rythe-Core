#pragma once
#include <semver.hpp>

#include <rsl/hashed_string>
#include <rsl/memory>
#include <rsl/primitives>
#include <rsl/type_traits>
#include <rsl/utilities>

namespace rythe::core
{
	struct feature_desc
	{
		std::string_view name;
		rsl::id_type id;
		semver::version version;
	};

	struct feature_base
	{
		[[nodiscard]] virtual std::string_view get_name() const noexcept = 0;
		[[nodiscard]] virtual rsl::id_type get_id() const noexcept = 0;
		[[nodiscard]] virtual rsl::hashed_string get_hashed_name() const noexcept = 0;
		[[nodiscard]] virtual semver::version get_version() const noexcept = 0;

		template <typename T>
		const T* try_cast() const noexcept
		{
			if (T::feature_id == get_id())
			{
				return static_cast<T*>(this);
			}

			return nullptr;
		}

		template <typename T>
		T* try_cast() noexcept
		{
			return const_cast<T*>(rsl::as_const(*this).template try_cast<T>());
		}

		template <typename T>
		const T& cast() const
		{
			const T* ptr = try_cast<T>();
			rsl_assert_invalid_cast(ptr);
			return ptr;
		}

		template <typename T>
		T& cast()
		{
			return const_cast<T&>(rsl::as_const(*this).template cast<T>());
		}
	};

	namespace internal
	{
		template <typename T>
		struct get_feature_name
		{
			constexpr static auto value = rsl::type_name<T>();
		};

		template <typename T>
			requires requires {
				{ T::feature_name } -> rsl::constexpr_string_type;
			}
		struct get_feature_name<T>
		{
			constexpr static auto value = T::feature_name;
		};

		template <typename T>
		struct get_feature_version
		{
			constexpr static semver::version value = semver::version();
		};

		template <typename T>
			requires requires {
				{ T::feature_version } -> rsl::convertible_to<semver::version>;
			}
		struct get_feature_version<T>
		{
			constexpr static semver::version value = T::feature_version;
		};
	} // namespace internal

	template <typename Impl>
	struct feature : public feature_base
	{
		constexpr static rsl::id_type feature_id = rsl::hash_string(internal::get_feature_name<Impl>::value);
		constexpr static rsl::hashed_string feature_hashed_name =
			rsl::hashed_string(internal::get_feature_name<Impl>::value);

		[[nodiscard]] std::string_view get_name() const noexcept override
		{
			return internal::get_feature_name<Impl>::value;
		}
		[[nodiscard]] rsl::id_type get_id() const noexcept override { return feature_id; }
		[[nodiscard]] rsl::hashed_string get_hashed_name() const noexcept override { return feature_hashed_name; }
		[[nodiscard]] semver::version get_version() const noexcept override
		{
			return internal::get_feature_version<Impl>::value;
		}
	};

	class engine;

	class module_base
	{
	public:
		virtual rsl::result<void> initialize() noexcept = 0;
		virtual std::span<const feature_desc> get_features_descriptions() const noexcept = 0;

		virtual const feature_base* try_get_feature(rsl::id_type id) const noexcept = 0;
		feature_base* try_get_feature(rsl::id_type id) noexcept;
		const feature_base& get_feature(rsl::id_type id) const;
		feature_base& get_feature(rsl::id_type id);

		[[nodiscard]] const engine& get_engine() const noexcept;
		[[nodiscard]] engine& get_engine() noexcept;

		rsl::pmu_allocator& get_allocator() noexcept;
		const rsl::pmu_allocator& get_allocator() const noexcept;

		module_base(engine& engine);

	private:
		engine* m_engine{};
	};

	class module : public module_base
	{
	public:
		template <typename T, typename... Args>
		void add_feature(Args&&... args)
		{
			add_feature(std::unique_ptr<feature_base, rsl::stl_pmu_deleter<feature_base>>(
				rsl::allocate<T>(get_allocator(), 1, rsl::forward<Args>(args)...),
				rsl::make_stl_pmu_deleter(&get_allocator())
			));
		}

		void add_feature(std::unique_ptr<feature_base, rsl::stl_pmu_deleter<feature_base>>&& featurePtr);

		std::span<const feature_desc> get_features_descriptions() const noexcept override;
		const feature_base* try_get_feature(rsl::id_type id) const noexcept override;

	private:
		std::vector<feature_desc> m_featureDescriptions;
		std::vector<std::unique_ptr<feature_base, rsl::stl_pmu_deleter<feature_base>>> m_features;
	};
} // namespace rythe::core

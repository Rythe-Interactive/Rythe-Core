#pragma once
#include <exception>
#include <rsl/primitives>
#include <rsl/type_util>

#define SPDLOG_HEADER_ONLY
#define FMT_CONSTEVAL
#include <rsl/logging>

/**
 * @file exception.hpp
 */

/**@def rythe_exception
 * @brief Args generic exception with file name, line number, and function name.
 */
#define rythe_exception rythe::core::exception(__FILE__, __LINE__, __FUNC__)

/**@def rythe_exception_msg
 * @brief Args generic exception with message, file name, line number, and function name.
 */
#define rythe_exception_msg(msg) rythe::core::exception(msg, __FILE__, __LINE__, __FUNC__)


#pragma region fetch
/**@def rythe_invalid_fetch_error
 * @brief Args generic fetch exception with file name, line number, and function name.
 */
#define rythe_invalid_fetch_error rythe::core::invalid_fetch_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_invalid_fetch_msg
 * @brief Args generic fetch exception with message, file name, line number, and function name.
 */
#define rythe_invalid_fetch_msg(msg) rythe::core::invalid_fetch_error(msg, __FILE__, __LINE__, __FUNC__)


/**@def rythe_invalid_component_error
 * @brief Args invalid component fetch exception with file name, line number, and function name.
 */
#define rythe_invalid_component_error rythe::core::invalid_component_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_invalid_component_msg
 * @brief Args invalid component fetch exception with message, file name, line number, and function name.
 */
#define rythe_invalid_component_msg(msg) rythe::core::invalid_component_error(msg, __FILE__, __LINE__, __FUNC__)


/**@def rythe_component_destroyed_error
 * @brief Args destroyed component fetch exception with file name, line number, and function name.
 */
#define rythe_component_destroyed_error rythe::core::component_destroyed_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_component_destroyed_msg
 * @brief Args destroyed component fetch exception with message, file name, line number, and function name.
 */
#define rythe_component_destroyed_msg(msg) rythe::core::component_destroyed_error(msg, __FILE__, __LINE__, __FUNC__)


/**@def rythe_invalid_entity_error
 * @brief Args invalid entity fetch exception with file name, line number, and function name.
 */
#define rythe_invalid_entity_error rythe::core::invalid_entity_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_invalid_entity_msg
 * @brief Args invalid entity fetch exception with message, file name, line number, and function name.
 */
#define rythe_invalid_entity_msg(msg) rythe::core::invalid_entity_error(msg, __FILE__, __LINE__, __FUNC__)


/**@def rythe_entity_not_found_error
 * @brief Args non-existent entity fetch exception with file name, line number, and function name.
 */
#define rythe_entity_not_found_error rythe::core::entity_not_found_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_entity_not_found_msg
 * @brief Args non-existent entity fetch exception with message, file name, line number, and function name.
 */
#define rythe_entity_not_found_msg(msg) rythe::core::entity_not_found_error(msg, __FILE__, __LINE__, __FUNC__)
#pragma endregion

#pragma region creation
/**@def rythe_invalid_creation_error
 * @brief Args generic creation exception with file name, line number, and function name.
 */
#define rythe_invalid_creation_error rythe::core::invalid_creation_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_invalid_creation_msg
 * @brief Args generic creation exception with message, file name, line number, and function name.
 */
#define rythe_invalid_creation_msg(msg) rythe::core::invalid_creation_error(msg, __FILE__, __LINE__, __FUNC__)


/**@def rythe_entity_exists_error
 * @brief Args duplicate entity creation exception with file name, line number, and function name.
 */
#define rythe_entity_exists_error rythe::core::entity_exists_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_entity_exists_msg
 * @brief Args duplicate entity creation exception with message, file name, line number, and function name.
 */
#define rythe_entity_exists_msg(msg) rythe::core::entity_exists_error(msg, __FILE__, __LINE__, __FUNC__)


/**@def rythe_component_exists_error
 * @brief Args duplicate component creation exception with file name, line number, and function name.
 */
#define rythe_component_exists_error rythe::core::component_exists_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_component_exists_msg
 * @brief Args duplicate component creation exception with message, file name, line number, and function name.
 */
#define rythe_component_exists_msg(msg) rythe::core::component_exists_error(msg, __FILE__, __LINE__, __FUNC__)
#pragma endregion

#pragma region type
/**@def rythe_invalid_type_error
 * @brief Args generic invalid type exception with file name, line number, and function name.
 */
#define rythe_invalid_type_error rythe::core::invalid_type_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_invalid_type_msg
 * @brief Args generic invalid type exception with message, file name, line number, and function name.
 */
#define rythe_invalid_type_msg(msg) rythe::core::invalid_type_error(msg, __FILE__, __LINE__, __FUNC__)


/**@def rythe_unknown_component_error
 * @brief Args invalid component type exception with file name, line number, and function name.
 */
#define rythe_unknown_component_error rythe::core::unknown_component_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_unknown_component_msg
 * @brief Args invalid component type exception with message, file name, line number, and function name.
 */
#define rythe_unknown_component_msg(msg) rythe::core::unknown_component_error(msg, __FILE__, __LINE__, __FUNC__)


/**@def rythe_unknown_system_error
 * @brief Args invalid system type exception with file name, line number, and function name.
 */
#define rythe_unknown_system_error rythe::core::unknown_system_error(__FILE__, __LINE__, __FUNC__)

/**@def rythe_unknown_system_msg
 * @brief Args invalid system type exception with message, file name, line number, and function name.
 */
#define rythe_unknown_system_msg(msg) rythe::core::unknown_system_error(msg, __FILE__, __LINE__, __FUNC__)

/**@def rythe_fs_error
 * @brief Args filesystem Error with message, signifies something went wrong with
 *        requesting a resource from the virtual filesystem
 * @note catch rythe::core::fs_error if you need to filter for this exception
 */
#define rythe_fs_error(msg) rythe::core::fs_error(msg, __FILE__, __LINE__, __FUNC__)
#pragma endregion



namespace rythe::core
{
	/**@class exception
	 * @brief Args generic exception with file name, line number, and function name.
	 */
	class exception
	{
	private:
		rsl::cstring m_file;
		rsl::uint m_line;
		rsl::cstring m_func;
		std::string m_message;

	public:
		RULE_OF_5(exception);

		exception(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: m_file(file),
			  m_line(line),
			  m_func(func),
			  m_message("Args generic exception occurred.")
		{
		}
		exception(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: m_file(file),
			  m_line(line),
			  m_func(func),
			  m_message(msg)
		{
		}

		const std::string& what() const noexcept { return m_message; }
		rsl::cstring file() const noexcept { return m_file; }
		rsl::uint line() const noexcept { return m_line; }
		rsl::cstring func() const noexcept { return m_func; }
	};

#pragma region invalid fetch
	/**@class invalid_fetch_error
	 * @brief Args generic fetch exception.
	 */
	class invalid_fetch_error : public exception
	{
	public:
		RULE_OF_5(invalid_fetch_error);

		invalid_fetch_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: exception("Invalid fetch occurred.", file, line, func)
		{
		}
		invalid_fetch_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: exception(msg, file, line, func)
		{
		}
	};

	class invalid_component_error : public invalid_fetch_error
	{
	public:
		RULE_OF_5(invalid_component_error);

		invalid_component_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_fetch_error("Component invalid.", file, line, func)
		{
		}
		invalid_component_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_fetch_error(msg, file, line, func)
		{
		}
	};

	class component_destroyed_error : public invalid_component_error
	{
	public:
		RULE_OF_5(component_destroyed_error);

		component_destroyed_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_component_error("Component no longer exists.", file, line, func)
		{
		}
		component_destroyed_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_component_error(msg, file, line, func)
		{
		}
	};

	class invalid_entity_error : public invalid_fetch_error
	{
	public:
		RULE_OF_5(invalid_entity_error);

		invalid_entity_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_fetch_error("Entity invalid.", file, line, func)
		{
		}
		invalid_entity_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_fetch_error(msg, file, line, func)
		{
		}
	};

	class entity_not_found_error : public invalid_entity_error
	{
	public:
		RULE_OF_5(entity_not_found_error);

		entity_not_found_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_entity_error("Entity does not exist.", file, line, func)
		{
		}
		entity_not_found_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_entity_error(msg, file, line, func)
		{
		}
	};
#pragma endregion

#pragma region invalid creation
	/**@class invalid_creation_error
	 * @brief Args generic creation exception.
	 */
	class invalid_creation_error : public exception
	{
	public:
		RULE_OF_5(invalid_creation_error);

		invalid_creation_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: exception("Creation invalid.", file, line, func)
		{
		}
		invalid_creation_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: exception(msg, file, line, func)
		{
		}
	};

	class entity_exists_error : public invalid_creation_error
	{
	public:
		RULE_OF_5(entity_exists_error);

		entity_exists_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_creation_error("Entity already exist.", file, line, func)
		{
		}
		entity_exists_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_creation_error(msg, file, line, func)
		{
		}
	};

	class component_exists_error : public invalid_creation_error
	{
	public:
		RULE_OF_5(component_exists_error);

		component_exists_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_creation_error("Component already exist.", file, line, func)
		{
		}
		component_exists_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_creation_error(msg, file, line, func)
		{
		}
	};
#pragma endregion

#pragma region invalid type
	/**@classinvalid_type_error
	 * @brief Args generic type exception.
	 */
	class invalid_type_error : public exception
	{
	public:
		RULE_OF_5(invalid_type_error);

		invalid_type_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: exception("Type invalid.", file, line, func)
		{
		}
		invalid_type_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: exception(msg, file, line, func)
		{
		}
	};

	class unknown_component_error : public invalid_type_error
	{
	public:
		RULE_OF_5(unknown_component_error);

		unknown_component_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_type_error("Unknown component type.", file, line, func)
		{
		}
		unknown_component_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_type_error(msg, file, line, func)
		{
		}
	};

	class unknown_system_error : public invalid_type_error
	{
	public:
		RULE_OF_5(unknown_system_error);

		unknown_system_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_type_error("Unknown system type.", file, line, func)
		{
		}
		unknown_system_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: invalid_type_error(msg, file, line, func)
		{
		}
	};
#pragma endregion

#pragma region filesystem
	class fs_error : public exception
	{
	public:
		RULE_OF_5(fs_error);

		fs_error(rsl::cstring file, rsl::uint line, rsl::cstring func)
			: exception("Filesystem Adapter failed", file, line, func)
		{
		}
		fs_error(const std::string& msg, rsl::cstring file, rsl::uint line, rsl::cstring func)
			: exception(msg, file, line, func)
		{
		}
	};
#pragma endregion

} // namespace rythe::core

namespace fmt
{
	template <>
	struct formatter<rythe::core::exception>
	{
		char presentation = 'f';

		constexpr const char* parse(format_parse_context& ctx)
		{
			auto it = ctx.begin(), end = ctx.end();

			if (!it)
				return nullptr;

			if (it != end && (*it == 'f' || *it == 'e'))
				presentation = *it++;

			if (it != end && *it != '}')
				throw format_error("invalid format");

			return it;
		}

		template <typename FormatContext>
		auto format(const rythe::core::exception& e, FormatContext& ctx)
		{
			return v8::format_to(ctx.out(), "{}-[{}]({}):{}", e.file(), e.line(), e.func(), e.what());
		}
	};
} // namespace fmt

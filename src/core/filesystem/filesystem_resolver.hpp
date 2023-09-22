#pragma once

#include <string>                       // std::string
#include <set>                          // set::set

#include <rsl/type_util>   // R_NODISCARD
#include <core/filesystem/resource.hpp> // basic_resource
#include <core/common/inteface_traits.hpp>
#include <core/common/result.hpp>
#include <core/common/exception.hpp>

#include "detail/meta.hpp"
#include "detail/traits.hpp"            // file_traits
#include "detail/strpath_manip.hpp"     // strpath_manip::separator


/**
 * @file filesystem_resolver.hpp
 */

namespace rythe::core::filesystem {

    /**@class filesystem_resolver
     * @brief Abstract class that should represent and implement all functions of your
     *        filesystem, note in particular the pure virtual functions.
     */
    class filesystem_resolver : public filesystem_resolver_common_base {
    public:
        filesystem_resolver() = default;

        filesystem_resolver(const filesystem_resolver&) = default;
        filesystem_resolver(filesystem_resolver&&) noexcept = default;

        filesystem_resolver& operator=(const filesystem_resolver&) = default;
        filesystem_resolver& operator=(filesystem_resolver&&) = default;

        virtual ~filesystem_resolver() = default;

        /** @brief Gets all traits of a particular file.
         *  @note Same as calling @ref set_target and then calling all the individual traits manually.
         *  @param [in] path The location identifier to the resource.
         *  @return file_traits All traits of the file bunched together.
         */
        R_NODISCARD file_traits resolve(const std::string& path) noexcept;

        /** @brief Gets all traits of a particular file.
         *  @note Same as getting all the individual traits manually.
         *  @return file_traits All traits of the file bunched together.
         */
        R_NODISCARD file_traits get_traits() noexcept;

        
        /** @brief Sets the identifier of the filesystem.
         *  @note If this filesystem is nested it should be the path to the root of the fs otherwise it can be arbitrary.
         *  @param [in] ident The identifier of the filesystem.
         */
        void set_identifier(const std::string& ident) { m_identifier = ident; }


        /** @brief Sets the target path of the resolver.
         *  @param [in] target The location identifier to the resource.
         */
        void set_target(const std::string& target) { m_target = target; }

        /** @note (implementation details)
         *        Certain traits obviously overrule others.
         *        The progression here works like this:
         *        - if is_file cannot be directory
         *        - if is_directory cannot be written and cannot be read
         *        - if exists cannot be created and is valid
         *        - if exists and is file can be read
         */

         /** @brief Checks if target points to a file.*/
        R_NODISCARD virtual bool is_file()      const noexcept = 0;
        /** @brief Checks if target points to a directory.*/
        R_NODISCARD virtual bool is_directory() const noexcept = 0;
        /** @brief Checks if target points to a valid location.*/
        R_NODISCARD virtual bool is_valid_path()     const noexcept = 0;
        /** @brief Checks if the target location can be written to.*/
        R_NODISCARD virtual bool writeable()    const noexcept = 0;
        /** @brief Checks if the target location can be read from.*/
        R_NODISCARD virtual bool readable()     const noexcept = 0;
        /** @brief Checks if the target location can be created.*/
        R_NODISCARD virtual bool creatable()    const noexcept = 0;
        /** @brief Checks if the target location exists.*/
        R_NODISCARD virtual bool exists()       const noexcept = 0;

        /** @brief Gets all entries in a directory or similar concept (assume -a).
         *  @note When not is_directory this should return an empty set.
         *  @ref set_target
         *  @return A set of strings of entries at the current pointed at location.
         */
        R_NODISCARD virtual std::set<std::string> ls() const noexcept = 0;

        /** @brief Get the contents of the file pointed at.
         *  @note When not readable this should return an fs_error using Err().
         *  @ref set_target
         *  @return basic_resource wrapped in Ok() or fs_error wrapped in Err().
         */
        R_NODISCARD common::result<basic_resource, fs_error> get() noexcept;
        R_NODISCARD common::result<const basic_resource, fs_error> get() const noexcept;
        virtual common::result<basic_resource, fs_error> get(interfaces::implement_signal_t) noexcept = 0;
        virtual common::result<const basic_resource, fs_error> get(interfaces::implement_signal_t) const noexcept = 0;

        /** @brief Sets the contents of the file pointed at.
         *  @note When not writeable should do nothing and return false.
         *  @note When attempting to create a directory res must be empty.
         *  @param [in] res The resource you want to set at location.
         *  @ref set_target
         *  @return result<void,fs_error>, has_error == true when the file could not be read.
         */
        R_NODISCARD common::result<void, fs_error> set(const basic_resource& res);
        virtual common::result<void, fs_error> set(interfaces::implement_signal_t, const basic_resource& res) = 0;

        /** @brief Gets the delimiter of the filesystem.
         *  @return char single character for the delimiter of the filesystem (default: strpath_manip::separator()).
         */
        R_NODISCARD virtual char get_delimiter() const noexcept RYTHE_IMPURE_RETURN(strpath_manip::separator());


        /** @brief Destroys the file pointed to.
         *  @note when the files does not exists (traits.valid = false) this has no effect.
         */
        void erase() const noexcept;
        virtual void erase(interfaces::implement_signal_t) const noexcept = 0;

        R_NODISCARD const filesystem_traits& get_fs_traits() const { return m_traits; }
        void inherit(filesystem_resolver& outer)
        {
            inherit_traits(outer.m_traits,m_traits);    
        }

        /** @brief Required to create new instances of the provider, similar to a surrogate constructor
         *         if required arguments must be copied over.
         */
        R_NODISCARD virtual filesystem_resolver* make() = 0;

        /** @brief Gets the identifier of the filesystem for tl resolvers this is the same as the root-domains.
         */
        R_NODISCARD const std::string& get_identifier() const { return m_identifier; }

        /** @brief Gets the targeted file of the filesystem.
         */
        R_NODISCARD const std::string& get_target() const { return m_target; }

    private:
        std::string m_identifier;
        std::string m_target;
        filesystem_traits m_traits{ false,true };

    };
}

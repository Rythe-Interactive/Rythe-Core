#pragma once
#include <memory>
#include <unordered_set>

#include <rsl/primitives>
#include <rsl/utilities>

#include "core/containers/hashed_sparse_set.hpp"
#include "core/ecs/meta/meta.hpp"

/**
 * @file entity.hpp
 */

namespace rythe::core
{
	namespace ecs
	{
		struct component_base;

		template <typename component_type>
		struct component;

		struct entity;
	} // namespace ecs

	namespace serialization
	{
		template <typename T>
		struct prototype;
	}
} // namespace rythe::core

#if !defined(DOXY_EXCLUDE)
namespace std
{
	template <>
	struct hash<rythe::core::ecs::entity>
	{
		std::size_t operator()(rythe::core::ecs::entity const& handle) const noexcept;
	};
} // namespace std
#endif

namespace rythe::core::ecs
{
	using entity_set = hashed_sparse_set<entity>;

	static constexpr rsl::id_type world_entity_id = 1;

	struct entity_data;

#pragma region Child Iterators
	struct child_iterator
	{
		friend struct entity;

	private:
		struct impl;

		std::shared_ptr<impl> m_pimpl;
		child_iterator(impl* implptr);

	public:
		friend bool operator==(const child_iterator& lhs, const child_iterator& rhs);

		friend bool operator!=(const child_iterator& lhs, const child_iterator& rhs) { return !(lhs == rhs); }

		entity& operator*();

		entity* operator->();

		child_iterator& operator++();
		child_iterator& operator--();
		child_iterator operator++(int);
		child_iterator operator--(int);
	};

	struct const_child_iterator
	{
		friend struct entity;

	private:
		struct impl;

		std::shared_ptr<impl> m_pimpl;
		const_child_iterator(impl* implptr);

	public:
		friend bool operator==(const const_child_iterator& lhs, const const_child_iterator& rhs);

		friend bool operator!=(const const_child_iterator& lhs, const const_child_iterator& rhs) { return !(lhs == rhs); }

		const entity& operator*();

		const entity* operator->();

		const_child_iterator& operator++();
		const_child_iterator& operator--();
		const_child_iterator operator++(int);
		const_child_iterator operator--(int);
	};

	struct child_reverse_iterator
	{
		friend struct entity;

	private:
		struct impl;

		std::shared_ptr<impl> m_pimpl;
		child_reverse_iterator(impl* implptr);

	public:
		friend bool operator==(const child_reverse_iterator& lhs, const child_reverse_iterator& rhs);

		friend bool operator!=(const child_reverse_iterator& lhs, const child_reverse_iterator& rhs) { return !(lhs == rhs); }

		entity& operator*();

		entity* operator->();

		child_reverse_iterator& operator++();
		child_reverse_iterator& operator--();
		child_reverse_iterator operator++(int);
		child_reverse_iterator operator--(int);
	};

	struct const_child_reverse_iterator
	{
		friend struct entity;

	private:
		struct impl;

		std::shared_ptr<impl> m_pimpl;
		const_child_reverse_iterator(impl* implptr);

	public:
		friend bool operator==(const const_child_reverse_iterator& lhs, const const_child_reverse_iterator& rhs);

		friend bool operator!=(const const_child_reverse_iterator& lhs, const const_child_reverse_iterator& rhs) { return !(lhs == rhs); }

		const entity& operator*();

		const entity* operator->();

		const_child_reverse_iterator& operator++();
		const_child_reverse_iterator& operator--();
		const_child_reverse_iterator operator++(int);
		const_child_reverse_iterator operator--(int);
	};
#pragma endregion

	/**@struct entity
	 * @brief Handle to an entity.
	 */
	struct entity
	{
	public:
		/**@brief Pointer to entity specific data.
		 */
		entity_data* data;

		/**@brief Equal operator with any numerical types or other entities.
		 *        Specializations are for: nullptr_t, rsl::id_type, entity.
		 */
		template <typename T>
		[[nodiscard]] bool operator==(T val) const;

		/**@brief Not equal operator with any numerical types or other entities.
		 *        Specializations are for: nullptr_t, rsl::id_type, entity.
		 */
		template <typename T>
		[[nodiscard]] bool operator!=(T val) const;

		/**@brief Allows entity handles to act like an entity ID.
		 * @return ID of the entity.
		 */
		[[nodiscard]] operator rsl::id_type() const noexcept;

		/**@brief Checks if the entity is alive and valid.
		 * @return True if the entity is alive and valid, otherwise false.
		 * @note There might be more convenient alternatives like: `if(entity)` or `if(entity != nullptr)`
		 */
		[[nodiscard]] bool valid() const noexcept;

		/**@brief Directly access the entity specific data.
		 * @return Returns entity.data
		 */
		[[nodiscard]] entity_data* operator->() noexcept;
		[[nodiscard]] const entity_data* operator->() const noexcept;

		[[nodiscard]] std::unordered_set<rsl::id_type>& component_composition();
		[[nodiscard]] const std::unordered_set<rsl::id_type>& component_composition() const;

		/**@brief Replaces current parent with a new one.
		 */
		void set_parent(rsl::id_type parent);
		void set_parent(entity parent);

		/**@brief Fetches the current parent.
		 * @note You could also use entity->parent or entity.data->parent. This will avoid a possible function call.
		 *       This function exists for legacy reasons and for API completeness.
		 */
		[[nodiscard]] entity get_parent() const;

		/**@brief Adds a new child to this entity and thus makes this entity replace the child's current parent.
		 */
		void add_child(rsl::id_type child);
		void add_child(entity child);

		/**@brief Removes a child from this entity, the world will be the new parent of the child.
		 * @note This does NOT destroy the child!
		 */
		void remove_child(rsl::id_type child);
		void remove_child(entity child);

		/**@brief Removes all children from this entity, the world will be the new parent of the children.
		 * @note This does NOT destroy the children!
		 */
		void remove_children();

		/**@brief Destroys all children from this entity. This destroys all of the children's components and may destroy their children recursively.
		 * @param recurse Whether deeper layers of hierarchy should be destroyed as well or just the upper layers.
		 * @note Orphaned children from any child that may have been destroyed will receive the world as their new parent.
		 */
		void destroy_children(bool recurse = true);

		/**@brief Fetches set of all child entities of this entity.
		 */
		[[nodiscard]] entity_set& children();
		[[nodiscard]] const entity_set& children() const;

		/**@brief Fetches a specific child in the children list of this entity.
		 * @note Children in the list are in no specific ordering due to memory pooling.
		 */
		[[nodiscard]] entity get_child(rsl::size_type index) const;

		/**@brief Gets iterator to the first child.
		 */
		[[nodiscard]] child_iterator begin();
		[[nodiscard]] const_child_iterator begin() const;
		[[nodiscard]] const_child_iterator cbegin() const;

		/**@brief Gets reverse iterator to the last child.
		 */
		[[nodiscard]] child_reverse_iterator rbegin();
		[[nodiscard]] const_child_reverse_iterator rbegin() const;
		[[nodiscard]] const_child_reverse_iterator crbegin() const;

		/**@brief Gets iterator to the last child.
		 */
		[[nodiscard]] child_iterator end();
		[[nodiscard]] const_child_iterator end() const;
		[[nodiscard]] const_child_iterator cend() const;

		/**@brief Gets reverse iterator to the first child.
		 */
		[[nodiscard]] child_reverse_iterator rend();
		[[nodiscard]] const_child_reverse_iterator rend() const;
		[[nodiscard]] const_child_reverse_iterator crend() const;

		/**@brief Destroys the entity and it's components. May Destroy all children recursively.
		 * @param recurse Whether deeper layers of hierarchy should be destroyed as well or just this entity.
		 * @note Orphaned children that aren't destroyed will receive the world as their new parent.
		 */
		void destroy(bool recurse = true);

		/**@brief Creates and adds a new component of a certain type to this entity.
		 * @tparam component_type Type of the component to add.
		 * @return Component handle to the component.
		 */
		template <typename component_type>
		wrap_component_t<component_type> add_component();

		template <typename component_type0, typename component_type1, typename... component_typeN>
		component_tuple<component_type0, component_type1, component_typeN...> add_component();

		/**@brief Adds a precreated component of a certain type to this entity.
		 * @tparam component_type Type of the component to add.
		 * @param value Component value to use.
		 * @return Component handle to the component.
		 */
		template <typename component_type>
		wrap_component_t<component_type> add_component(component_type&& value);
		template <typename component_type>
		wrap_component_t<component_type> add_component(const component_type& value);

		template <typename component_type0, typename component_type1, typename... component_typeN>
		component_tuple<component_type0, component_type1, component_typeN...> add_component(component_type0&& value0, component_type1&& value1, component_typeN&&... valueN);
		template <typename component_type0, typename component_type1, typename... component_typeN>
		component_tuple<component_type0, component_type1, component_typeN...> add_component(const component_type0& value0, const component_type1& value1, const component_typeN&... valueN);

		template <typename archetype_type, typename component_type0, typename component_type1, typename... component_typeN>
		typename archetype_type::handle_group add_component(component_type0&& value0, component_type1&& value1, component_typeN&&... valueN);

		/**@brief Creates and adds a new component of a certain type to this entity. Component is serialized from a prototype.
		 * @tparam component_type Type of the component to add.
		 * @param prot Prototype to serialize component from.
		 * @return Component handle to the component.
		 */
		template <typename component_type>
		component<component_type> add_component(const serialization::prototype<component<component_type>>& prot);
		template <typename component_type>
		component<component_type> add_component(serialization::prototype<component<component_type>>&& prot);

		/**@brief Checks whether this entity has a certain component.
		 * @tparam component_type Type of the component to check for.
		 * @return True if the entity has the component, false if not.
		 */
		template <typename component_type>
		[[nodiscard]] bool has_component() const;
		template <typename component_type0, typename component_type1, typename... component_typeN>
		[[nodiscard]] bool has_component() const;

		/**@brief Gets a component handle to a certain component on this entity.
		 * @tparam component_type Type of the component to get.
		 * @return Component handle to the component.
		 */
		template <typename component_type>
		[[nodiscard]] wrap_component_t<component_type> get_component();
		template <typename component_type>
		[[nodiscard]] const_wrap_component_t<component_type> get_component() const;

		template <typename component_type0, typename component_type1, typename... component_typeN>
		[[nodiscard]] component_tuple<component_type0, component_type1, component_typeN...> get_component();
		template <typename component_type0, typename component_type1, typename... component_typeN>
		[[nodiscard]] const_component_tuple<component_type0, component_type1, component_typeN...> get_component() const;

		/**@brief Removes and destroys a component from this entity.
		 * @tparam component_type Type of the component to remove.
		 */
		template <typename component_type>
		void remove_component();
		template <typename component_type0, typename component_type1, typename... component_typeN>
		void remove_component();
	};
} // namespace rythe::core::ecs

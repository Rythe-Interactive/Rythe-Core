#pragma once
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <algorithm>
#include <stdexcept>
#include <core/async/rw_spinlock.hpp>
#include <core/platform/platform.hpp>
#include <core/types/primitives.hpp>
#include <core/containers/iterator_tricks.hpp>

/**
 * @file atomic_sparse_map.hpp
 */

namespace legion::core
{
    /**@class atomic_sparse_map
     * @brief Atomic quick lookup contiguous map.
     *        A specialized version of sparse_map that uses legion::core::async::transferable_atomic and legion::core::async::rw_spinlock.
     * @tparam key_type The type to be used as the key.
     * @tparam value_type The type to be used as the value.
     * @tparam dense_type Container to be used to store the values.
     * @tparam sparse_type Container to be used to store the keys.
     * @note With default container parameters iterators may be invalidated upon resize. See reference of std::vector.
     * @note Removing item might invalidate the iterator of the last item in the dense container.
     */
    template <typename key_type, typename value_type, template<typename...> typename dense_type = std::vector, template<typename...> typename sparse_type = std::unordered_map>
    class atomic_sparse_map
    {
    public:
        using self_type = atomic_sparse_map<key_type, value_type, dense_type, sparse_type>;
        using self_reference = self_type&;
        using self_const_reference = const self_type&;

        using key_reference = key_type&;
        using key_const_reference = const key_type&;
        using key_pointer = key_type*;

        using value_reference = value_type&;
        using value_const_reference = const value_type&;
        using value_pointer = value_type*;

        using sparse_container = sparse_type<key_type, size_type>;
        using dense_value_container = dense_type<value_type>;
        using dense_key_container = dense_type<key_type>;

        using iterator = core::key_value_pair_iterator<typename dense_key_container::iterator, typename dense_value_container::iterator>;
        using const_iterator = core::key_value_pair_iterator<typename dense_key_container::const_iterator, typename dense_value_container::const_iterator>;

    private:
        mutable async::rw_spinlock m_container_lock;

        dense_value_container m_dense_value;
        dense_key_container m_dense_key;
        sparse_container m_sparse;

        std::atomic<size_type> m_size = 0;
        std::atomic<size_type> m_capacity = 0;

    public:
        L_NODISCARD async::rw_spinlock& get_lock() const { return m_container_lock; }
        L_NODISCARD dense_value_container& values() { return m_dense_value; }
        L_NODISCARD const dense_value_container& values() const { return m_dense_value; }

        L_NODISCARD dense_key_container& keys() { return m_dense_key; }
        L_NODISCARD const dense_key_container& keys() const { return m_dense_key; }

        L_NODISCARD iterator begin()
        {
            async::readonly_guard lock(m_container_lock);
            return iterator(m_dense_key.begin(), m_dense_value.begin());
        }
        L_NODISCARD const_iterator begin() const
        {
            async::readonly_guard lock(m_container_lock);
            return const_iterator(m_dense_key.cbegin(), m_dense_value.cbegin());
        }
        L_NODISCARD const_iterator cbegin() const
        {
            async::readonly_guard lock(m_container_lock);
            return const_iterator(m_dense_key.cbegin(), m_dense_value.cbegin());
        }

        L_NODISCARD iterator end()
        {
            async::readonly_guard lock(m_container_lock);
            return iterator(m_dense_key.begin() + m_size, m_dense_value.begin() + m_size);
        }
        L_NODISCARD const_iterator end() const
        {
            async::readonly_guard lock(m_container_lock);
            return const_iterator(m_dense_key.cbegin() + m_size, m_dense_value.cbegin() + m_size);
        }
        L_NODISCARD const_iterator cend() const
        {
            async::readonly_guard lock(m_container_lock);
            return const_iterator(m_dense_key.cbegin() + m_size, m_dense_value.cbegin() + m_size);
        }


        /**@brief Returns the amount of items in the sparse_map.
         * @returns size_type Current amount of items contained in sparse_map.
         */
        L_NODISCARD inline size_type size(std::memory_order order = std::memory_order_acquire) const noexcept { return m_size.load(order); }

        /**@brief Returns the capacity of items the sparse_map could at least store without invalidating the iterators.
         * @returns size_type Current capacity of the dense container.
         */
        L_NODISCARD inline size_type capacity(std::memory_order order = std::memory_order_acquire) const noexcept { return m_capacity.load(order); }

        /**@brief Returns the maximum number of items the atomic_sparse_map could at most store without crashing.
         * @note This value typically reflects the theoretical limit on the size of the container, at most std::numeric_limits<difference_type>::max().
         *       At runtime, the size of the container may be limited to a value smaller than max_size() by the amount of RAM available.
         * @returns size_type
         */
        L_NODISCARD size_type max_size() const noexcept { async::readonly_guard lock(m_container_lock); return m_dense_value.max_size(); }

        /**@brief Returns whether the sparse_map is empty.
         * @returns bool True if the sparse_map is empty, otherwise false.
         */
        L_NODISCARD inline bool empty(std::memory_order order = std::memory_order_acquire) const noexcept { return m_size.load(order) == 0; }

        /**@brief Clears sparse_map.
         * @note Will not update capacity.
         */
        inline void clear(std::memory_order order = std::memory_order_release) noexcept { m_size.store(0, order); }

        /**@brief Reserves space in dense container for more items.
         * @param size Amount of items to reserve space for (would be the new capacity).
         * @note Will update capacity if resize happened.
         */
        inline void reserve(size_type size, std::memory_order loadOrder = std::memory_order_acquire, std::memory_order storeOrder = std::memory_order_release)
        {
            if (size > m_capacity.load(loadOrder))
            {
                async::readwrite_guard lock(m_container_lock);
                m_dense_value.resize(size);
                m_dense_key.resize(size);
                m_capacity.store(size, storeOrder);
            }
        }

#pragma region count
        /**@brief Returns the amount of items linked to a certain key.
         * @param key Key to look for.
         * @returns size_type Amount of items linked to the key (either 0 or 1).
         * @note Function is only available for compatibility reasons, it is advised to use contains instead.
         * @ref legion::core::sparse_map::contains
         */
        L_NODISCARD inline size_type count(key_const_reference key) const
        {
            return contains(key);
        }

        /**@brief Returns the amount of items linked to a certain key.
         * @param key Key to look for.
         * @returns size_type Amount of items linked to the key (either 0 or 1).
         * @note Function is only available for compatibility reasons, it is advised to use contains instead.
         * @ref legion::core::sparse_map::contains
         */
        L_NODISCARD inline size_type count(key_type&& key) const
        {
            return contains(key);
        }
#pragma endregion

#pragma region contains
        /**@brief Checks whether a certain key is contained in the sparse_map.
         * @param key Key to check for.
         * @returns bool true if the key was found, otherwise false.
         */
        L_NODISCARD inline bool contains(key_const_reference key)
        {
            async::readonly_guard lock(m_container_lock);
            return m_sparse[key] >= 0 && m_sparse[key] < m_size && m_dense_key[m_sparse[key]] == key;
        }

        /**@brief Checks whether a certain key is contained in the sparse_map.
         * @param key Key to check for.
         * @returns bool true if the key was found, otherwise false.
         */
        L_NODISCARD inline bool contains(key_type&& key)
        {
            async::readonly_guard lock(m_container_lock);
            return m_sparse[key] >= 0 && m_sparse[key] < m_size && m_dense_key[m_sparse[key]] == key;
        }

        /**@brief Checks whether a certain key is contained in the sparse_map.
         * @param key Key to check for.
         * @returns bool true if the key was found, otherwise false.
         */
        L_NODISCARD inline bool contains(key_const_reference key) const
        {
            async::readonly_guard lock(m_container_lock);
            return m_sparse.count(key) && m_sparse.at(key) >= 0 && m_sparse.at(key) < m_size && m_dense_key[m_sparse.at(key)] == key;
        }

        /**@brief Checks whether a certain key is contained in the sparse_map.
         * @param key Key to check for.
         * @returns bool true if the key was found, otherwise false.
         */
        L_NODISCARD inline bool contains(key_type&& key) const
        {
            async::readonly_guard lock(m_container_lock);
            return m_sparse.count(key) && m_sparse.at(key) >= 0 && m_sparse.at(key) < m_size && m_dense_key[m_sparse.at(key)] == key;
        }
#pragma endregion

#pragma region find
        /**@brief Finds the iterator of a value using std::find.
         * @param val Value to find.
         * @returns Iterator to the value if found, otherwise end.
         */
        L_NODISCARD inline iterator find(value_const_reference val)
        {
            async::readonly_guard lock(m_container_lock);
            return std::find(begin(), end(), val);
        }

        /**@brief Finds the iterator of a value using std::find.
         * @param val Value to find.
         * @returns Iterator to the value if found, otherwise end.
         */
        L_NODISCARD inline const_iterator find(value_const_reference val) const
        {
            async::readonly_guard lock(m_container_lock);
            return std::find(begin(), end(), val);
        }
#pragma endregion

#pragma region insert
        /**@brief Inserts new item into sparse_map
         * @param key Key to insert the new item to.
         * @param val Value to insert and link to the key.
         * @returns std::pair<iterator, bool> Iterator at the location of the key and true if succeeded, end and false if it didn't succeed.
         */
        inline std::pair<iterator, bool> insert(key_const_reference key, value_const_reference val, std::memory_order incrementOrder = std::memory_order_acq_rel)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = val;

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = key;

                m_sparse[key] = m_size.fetch_add(1, incrementOrder);
                return std::make_pair(iterator(itr_key, itr_value), true);
            }
            return std::make_pair(end(), false);
        }

        /**@brief Inserts new item into sparse_map
         * @param key Key to insert the new item to.
         * @param val Value to insert and link to the key.
         * @returns std::pair<iterator, bool> Iterator at the location of the key and true if succeeded, end and false if it didn't succeed.
         */
        inline std::pair<iterator, bool> insert(key_type&& key, value_const_reference val, std::memory_order incrementOrder = std::memory_order_acq_rel)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = val;

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = std::move(key);

                m_sparse[*itr_key] = m_size.fetch_add(1, incrementOrder);
                return std::make_pair(iterator(itr_key, itr_value), true);
            }
            return std::make_pair(end(), false);
        }

        /**@brief Inserts new item into sparse_map
         * @param key Key to insert the new item to.
         * @param val Value to insert and link to the key.
         * @returns std::pair<iterator, bool> Iterator at the location of the key and true if succeeded, end and false if it didn't succeed.
         */
        inline std::pair<iterator, bool> insert(key_const_reference key, value_type&& val, std::memory_order incrementOrder = std::memory_order_acq_rel)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = val;

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = key;

                m_sparse[key] = m_size.fetch_add(1, incrementOrder);
                return std::make_pair(iterator(itr_key, itr_value), true);
            }
            return std::make_pair(end(), false);
        }

        /**@brief Inserts new item into sparse_map
         * @param key Key to insert the new item to.
         * @param val Value to insert and link to the key.
         * @returns std::pair<iterator, bool> Iterator at the location of the key and true if succeeded, end and false if it didn't succeed.
         */
        inline std::pair<iterator, bool> insert(key_type&& key, value_type&& val, std::memory_order incrementOrder = std::memory_order_acq_rel)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = val;

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = key;

                m_sparse[key] = m_size.fetch_add(1, incrementOrder);
                return std::make_pair(iterator(itr_key, itr_value), true);
            }
            return std::make_pair(end(), false);
        }
#pragma endregion

#pragma region emplace
        /**@brief Construct item in place.
         * @param key Key to which the item should be created.
         * @param incrementOrer Memory order for incrementing the size.
         * @param arguments Arguments to pass to the item constructor.
         */
        template<typename... Arguments>
        inline std::pair<iterator, bool> emplace(key_const_reference key, std::memory_order incrementOrder, Arguments&&... arguments)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = value_type(arguments...);

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = key;

                m_sparse[key] = m_size.fetch_add(1, incrementOrder);

                return std::make_pair(iterator(itr_key, itr_value), true);
            }

            return std::make_pair(end(), false);
        }

        /**@brief Construct item in place.
         * @param key Key to which the item should be created.
         * @param incrementOrer Memory order for incrementing the size.
         * @param arguments Arguments to pass to the item constructor.
         */
        template<typename... Arguments>
        inline std::pair<iterator, bool> emplace(key_type&& key, std::memory_order incrementOrder, Arguments&&... arguments)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = value_type(arguments...);

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = key;

                m_sparse[*itr_key] = m_size.fetch_add(1, incrementOrder);

                return std::make_pair(iterator(itr_key, itr_value), true);
            }

            return std::make_pair(end(), false);
        }

        /**@brief Construct item in place.
         * @param key Key to which the item should be created.
         * @param arguments Arguments to pass to the item constructor.
         */
        template<typename... Arguments>
        inline std::pair<iterator, bool> emplace(key_const_reference key, Arguments&&... arguments)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = value_type(arguments...);

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = key;

                m_sparse[key] = m_size.fetch_add(1, std::memory_order_acq_rel);

                return std::make_pair(iterator(itr_key, itr_value), true);
            }

            return std::make_pair(end(), false);
        }

        /**@brief Construct item in place.
         * @param key Key to which the item should be created.
         * @param arguments Arguments to pass to the item constructor.
         */
        template<typename... Arguments>
        inline std::pair<iterator, bool> emplace(key_type&& key, Arguments&&... arguments)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = value_type(arguments...);

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = key;

                m_sparse[*itr_key] = m_size.fetch_add(1, std::memory_order_acq_rel);

                return std::make_pair(iterator(itr_key, itr_value), true);
            }

            return std::make_pair(end(), false);
        }
#pragma endregion

#pragma region operator[]
        /**@brief Thread unsafe retrieve item from sparse_map, inserts default value if it doesn't exist yet.
         * @param key Key value that needs to be retrieved.
         */
        inline value_reference operator[](key_type&& key)
        {
            key_type k;
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = value_type();

                auto itr_key = m_dense_key.begin() + m_size; // Find iterator location at which to store the key.
                *itr_key = std::move(key); // Move the key into the location.
                k = *itr_key; // Fetch a copy of the key for reuse in the rest of the function.
                m_sparse[k] = m_size.fetch_add(1, std::memory_order_acq_rel);
            }
            else
                k = key;

            async::readonly_guard readonlyLock(m_container_lock);

            return m_dense_value[m_sparse[k]];
        }

        /**@brief Thread unsafe retrieve item from sparse_map, inserts default value if it doesn't exist yet.
         * @param key Key value that needs to be retrieved.
         */
        inline value_reference operator[](key_const_reference key)
        {
            if (!contains(key))
            {
                if (m_size >= m_capacity)
                    reserve(m_size + 1);

                async::readwrite_guard lock(m_container_lock);

                auto itr_value = m_dense_value.begin() + m_size;
                *itr_value = value_type();

                auto itr_key = m_dense_key.begin() + m_size;
                *itr_key = key;

                m_sparse[key] = m_size.fetch_add(1, std::memory_order_acq_rel);
            }

            async::readonly_guard readonlyLock(m_container_lock);

            return m_dense_value[m_sparse[key]];
        }

        /**@brief Thread unsafe retrieve const item from const sparse_map.
         * @param key Key value that needs to be retrieved.
         */
        inline value_const_reference operator[](key_type&& key) const
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key and is non modifiable.");

            async::readonly_guard lock(m_container_lock);

            return m_dense_value[m_sparse.at(key)];
        }

        /**@brief Thread unsafe retrieve const item from const sparse_map.
         * @param key Key value that needs to be retrieved.
         */
        inline value_const_reference operator[](key_const_reference key) const
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key and is non modifiable.");

            async::readonly_guard lock(m_container_lock);

            return m_dense_value[m_sparse.at(key)];
        }
#pragma endregion

#pragma region get
        /**@brief Returns item from sparse_map, throws exception if it doesn't exist yet.
         * @param key Key value that needs to be retrieved.
         */
        inline value_type get(key_type&& key)
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key.");

            async::readonly_guard lock(m_container_lock);

            return m_dense_value[m_sparse[key]];
        }

        /**@brief Returns item from sparse_map, throws exception if it doesn't exist yet.
         * @param key Key value that needs to be retrieved.
         */
        inline value_type get(key_const_reference key)
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key.");

            async::readonly_guard lock(m_container_lock);

            return m_dense_value[m_sparse[key]];
        }

        /**@brief Returns const item from const sparse_map.
         * @param key Key value that needs to be retrieved.
         */
        inline value_type get(key_type&& key) const
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key and is non modifiable.");

            async::readonly_guard lock(m_container_lock);

            return m_dense_value[m_sparse.at(key)];
        }

        /**@brief Returns const item from const sparse_map.
         * @param key Key value that needs to be retrieved.
         */
        inline value_type get(key_const_reference key) const
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key and is non modifiable.");

            async::readonly_guard lock(m_container_lock);

            return m_dense_value[m_sparse.at(key)];
        }
#pragma endregion

#pragma region set
        /**@brief Sets item in sparse_map, throws exception if it doesn't exist yet.
         * @param key Key of value that needs to be set.
         * @param val New value for the item that needs to be set.
         */
        inline void set(key_type&& key, value_const_reference val)
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key.");

            async::readonly_guard lock(m_container_lock);

            m_dense_value[m_sparse[key]] = val;
        }

        /**@brief Sets item in sparse_map, throws exception if it doesn't exist yet.
         * @param key Key of value that needs to be set.
         * @param val New value for the item that needs to be set.
         */
        inline void set(key_const_reference key, value_const_reference val)
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key.");

            async::readonly_guard lock(m_container_lock);

            m_dense_value[m_sparse[key]] = val;
        }

        /**@brief Sets item in sparse_map, throws exception if it doesn't exist yet.
         * @param key Key of value that needs to be set.
         * @param val New value for the item that needs to be set.
         */
        inline void set(key_type&& key, value_type&& val)
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key and is non modifiable.");

            async::readonly_guard lock(m_container_lock);

            m_dense_value[m_sparse[key]] = val;
        }

        /**@brief Sets item in sparse_map, throws exception if it doesn't exist yet.
         * @param key Key of value that needs to be set.
         * @param val New value for the item that needs to be set.
         */
        inline void set(key_const_reference key, value_type&& val)
        {
            if (!contains(key))
                throw std::out_of_range("Sparse map does not contain this key and is non modifiable.");

            async::readonly_guard lock(m_container_lock);

            m_dense_value[m_sparse[key]] = val;
        }
#pragma endregion

        /**@brief Erases item from sparse_map.
         * @param key Key value that needs to be erased.
         * @returns size_type Number of items removed from the map.
         */
        inline size_type erase(key_const_reference key)
        {
            if (contains(key))
            {
                async::readwrite_guard lock(m_container_lock);
                if (m_size - 1 != m_sparse[key])
                {
                    m_dense_value[m_sparse[key]] = std::move(m_dense_value[m_size - 1]);
                    m_dense_key[m_sparse[key]] = std::move(m_dense_key[m_size - 1]);
                    m_sparse[m_dense_key[m_size - 1]] = std::move(m_sparse[key]);
                }
                --m_size;
                return true;
            }
            return false;
        }
    };
}

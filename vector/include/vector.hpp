#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>  // for std::size_t - utility library
#include "../../std2/std2.hpp" // for std2::move, std2::forward

namespace std2 {

template <typename T>
class vector {
public:
    // TODO: provide allocator felxibility
    vector() {
        // allocate memory in cosntructor
        reallocate(4); // initial capacity of 2
    }

    ~vector() {
        delete[] m_data; // free memory in destructor
    }

    /**
     *  @brief  Add an element to the end of the vector.
     *  @param  value  The value to add to the end of the vector.
     *  @return void.
     */
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity * 2); // double the capacity - TODO: use an allcoater to be dynamic
        }

        // add element to the end of the vector
        m_data[m_size] = value;
        m_size++;
    }

    /**
     *  @brief  Add an element to the end of the vector.
     *  @param  value  The (R-value ref) value to add to the end of the vector.
     *  @return void.
     */
    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity * 2); // double the capacity - TODO: use an allcoater to be dynamic
        }

        // add element to the end of the vector
        m_data[m_size] = std2::move(value);
        m_size++;
    }

    /**
     *  @brief  Add an element to the end of the vector.
     *  @param  args  Arguments to forward to the constructor of T.
     *  @return T reference.
     */
    template <typename... Args> //variadic template
    T& emplace_back(Args&&... args) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity * 2); // double the capacity - TODO: use an allcoater to be dynamic
        }

        // add element to the end of the vector
        m_data[m_size] = T(std2::forward<Args>(args)...);
        return m_data[m_size++];
    }

    /**
     *  @brief  Remove the last element from the vector.
     *  @return void.
     */
    void pop_back() {
        if (m_size > 0) {
            m_size--;
            m_data[m_size].~T(); // call destructor explicitly
        }
    }

    /**
     *  @brief  Clear the vector - remove all elements.
     *  @return void.
     */
    void clear() {
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i].~T(); // call destructor explicitly
        }
        m_size = 0;
    }

    /**
     *  @brief  Get the number of elements in the vector.
     *  @return the number of elements in the vector.
     */
    size_t size() const {
        return m_size;
    }

    /**
     *  @brief  Index operator - access element at the given index.
     *  @param  index  The index of the element to access.
     *  @return the value at the index.
     */
    const T& operator[](std::size_t index) const {
        return m_data[index];
    }

    /**
     *  @brief  Index operator - access element at the given index.
     *  @param  index  The index of the element to access.
     *  @return the referecne to the value at the index.
     */
    T& operator[](std::size_t index) {
        return m_data[index];
    }

private:

    /* @brief  Reallocate the internal storage to a new capacity.
     * @param  new_capacity  The new capacity for the vector.
     * @return void.
     */
    void reallocate(std::size_t new_capacity) {

        // TODO: handle reallocation for shrinking
        if (new_capacity <= m_size) {
            m_size = new_capacity;
        }

        // allocate a new block of heap memory
        T* new_block = new T[new_capacity];

        for (std::size_t i = 0; i < m_size; ++i) {
            new_block[i] = std2::move(m_data[i]);
            // new_block[i] = m_data[i];
        }

        delete[] m_data; // free old memory block
        m_data = new_block;
        m_capacity = new_capacity;
    }

    T* m_data = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};

} // namespace std2

#endif // VECTOR_HPP
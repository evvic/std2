#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>  // for std::size_t - utility library
#include "../../std2/std2.hpp" // for std2::move, std2::forward

namespace std2 {

template <typename T, typename Allocator = std::allocator<T>>
class vector {
public:

    vector() : m_alloc(Allocator()) {
        reallocate(INITIAL_CAPACITY);
    }

    explicit vector(const Allocator& alloc) : m_alloc(alloc) {
        reallocate(INITIAL_CAPACITY);
    }

    ~vector() {
        // delete[] m_data; // free memory in destructor
        m_alloc.deallocate(m_data, m_capacity);
    }

    /**
     *  @brief  Set the capacity of the vector.
     *  @param  new_capacity The new capacity for the vector.
     *  @return void.
     */
    void reserve(const std::size_t new_capacity) {
        // reserve only affects capacity not size
        // therefore a reserving an amount smaller than size will be ignored

        if (new_capacity > m_capacity) {
            reallocate(new_capacity);
        }
    }

    /**
     *  @brief  Set the size of the vector.
     *  @param  new_size The new size for the vector.
     *  @return void.
     */
    void resize(const std::size_t new_size) {
        // resize affects size and capacity
        // therefore a resizing an amount smaller than size will shrink the vector

        // reserve more space if needed
        if (new_size > m_capacity) reallocate(new_size);

        // shrink if needed
        for (std::size_t i = new_size; i < m_size; ++i) {
            m_data[i].~T(); // call destructor explicitly
        }

        // if growing, initialize new elements with default constructor
        for (std::size_t i = m_size; i < new_size; ++i) {
            new (&m_data[i]) T();
        }
        
        m_size = new_size;
    }

    /**
     *  @brief  Set the size of the vector.
     *  @param  new_size The new size for the vector.
     *  @param  val The value to initialize new elements with.
     *  @return void.
     */
    void resize(const std::size_t new_size, const T& val) {

        // reserve more space if needed
        if (new_size > m_capacity) reallocate(new_size);

        // shrink if needed
        for (std::size_t i = new_size; i < m_size; ++i) {
            m_data[i].~T(); // call destructor explicitly
        }

        // if growing, initialize new elements with val
        for (std::size_t i = m_size; i < new_size; ++i) {
            new (&m_data[i]) T(val);
        }
        
        m_size = new_size;
    }

    /**
     *  @brief  Add an element to the end of the vector.
     *  @param  value  The value to add to the end of the vector.
     *  @return void.
     */
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity * GROWTH_FACTOR); // double the capacity - TODO: use an allcoater to be dynamic
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
            reallocate(m_capacity * GROWTH_FACTOR); // double the capacity - TODO: use an allcoater to be dynamic
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
            reallocate(m_capacity * GROWTH_FACTOR); // double the capacity - TODO: use an allcoater to be dynamic
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

        // reserc

        // TODO: handle reallocation for shrinking
        if (new_capacity <= m_size) {
            m_size = new_capacity;
        }

        // allocate a new block of heap memory
        T* new_block = m_alloc.allocate(new_capacity);

        for (std::size_t i = 0; i < m_size; ++i) {
            new_block[i] = std2::move(m_data[i]);
        }

        // delete[] m_data; // free old memory block
        m_alloc.deallocate(m_data, m_capacity);
        m_data = new_block;
        m_capacity = new_capacity;
    }

    T* m_data = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
    Allocator m_alloc;

    const std::size_t INITIAL_CAPACITY = 4;
    const std::size_t GROWTH_FACTOR = 2;
};

} // namespace std2

#endif // VECTOR_HPP
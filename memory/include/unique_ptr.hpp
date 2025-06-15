#ifndef UNIQUE_POINTER_HPP
#define UNIQUE_POINTER_HPP

#include "../../std2/std2.hpp"

// Custom implementation of default_delete
template <typename T>
struct default_delete {
    void operator()(T* ptr) const {
        delete ptr;
    }
};

template <typename T, typename Deleter = default_delete<T>>
class unique_ptr {
public:
    /**
     *  @brief  Constructor - creates a unique_ptr that manages a pointer.
     *  @param  ptr  a pointer to the object to manage (default is nullptr).
     *  @param  deleter  a deleter object to delete the managed object (default is Deleter()).
     *  @return void.
     */
    constexpr unique_ptr(T* ptr = nullptr, Deleter deleter = Deleter()) 
        : ptr_(ptr), deleter_(deleter) {}

    /**
     *  @brief  Destructor - calls the deleter on the managed object.
     *  @return void.
     */
    constexpr ~unique_ptr() { deleter_(ptr_); }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    /**
     *  @brief  Move constructor.
     *  @param  other  another unique_ptr to move from.
     *  @return a new unique_ptr that takes ownership of the other unique_ptr.
     */
    constexpr unique_ptr(unique_ptr&& other) noexcept 
        : ptr_(bbp::exchange(other.ptr_, nullptr)),
        deleter_(bbp::move(other.deleter_))
    {}

    /**
     *  @brief  Move assignment operator.
     *  @param  other  another unique_ptr to move from.
     *  @return a reference to this unique_ptr.
     */
    constexpr unique_ptr& operator=(unique_ptr&& other) noexcept
    {
        if (this != &other) {
            reset();
            this->ptr_ = bbp::exchange(other.ptr_, nullptr);
            deleter_ = bbp::move(other.deleter_);
        }
        return *this;
    }

    /**
     *  @brief  Dereference operator.
     *  @return a reference to the managed object.
     */
    constexpr T& operator*() const { return *ptr_; }

    /**
     *  @brief  Member access operator.
     *  @return a pointer to the managed object.
     */
    constexpr T* operator->() const { return ptr_; }

    /**
     *  @brief  Get the managed object.
     *  @return a pointer to the managed object.
     */
    constexpr T* get() const { return ptr_; }

    /**
     *  @brief  Release the ownership of the managed object without deleting it.
     *  @return a pointer to the managed object.
     */
    constexpr T* release() 
    {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    /**
     *  @brief  Reset the managed object - release the ownership of the 
     *          current object and take ownership of a new object, if provided.
     *  @param  ptr  a pointer to the new object to manage (optional).
     *  @return void.
     */
    constexpr void reset(T* ptr = nullptr) 
    {
        deleter_(ptr_);
        ptr_ = ptr;
    }

private:
    T* ptr_;
    Deleter deleter_;
};

namespace bbp {

/**
 *  @brief  Custom implementation of make_unique - create a unique_ptr.
 *  @param  args  Arguments to pass to the constructor of T.
 *  @return A unique_ptr that owns and manages a new object of type T.
*/
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(bbp::forward<Args>(args)...));
}

} // namespace bbp

#endif // UNIQUE_POINTER_HPP

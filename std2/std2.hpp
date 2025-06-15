#ifndef STD2_H
#define STD2_H

namespace std2 {

// remove_reference type trait
template <typename T>
struct remove_reference {
    using type = T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
};

template <typename T>
struct remove_reference<T&&> {
    using type = T;
};

// forward function template
template <typename T>
T&& forward(typename remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

template <typename T>
T&& forward(typename remove_reference<T>::type&& t) noexcept {
    return static_cast<T&&>(t);
}

/**
 *  @brief  Custom implementation of move - convert a value to an rvalue.
 *  @param  t  A thing of arbitrary type.
 *  @return The parameter cast to an rvalue-reference to allow moving it.
*/
template <typename T>
constexpr typename remove_reference<T>::type&&
move(T&& t) noexcept {
    return static_cast<typename remove_reference<T>::type&&>(t);
}

/**
 *  @brief  Replaces the value of an object with a new value and returns the old value.
 *  @param  obj  The object whose value will be replaced.
 *  @param  new_value  The new value to assign to obj.
 *  @return The old value of obj.
*/
template <typename T, typename U = T>
constexpr T exchange(T& obj, U&& new_value) {
    T old_value = std2::move(obj);
    obj = std2::move(new_value);
    return old_value;
}

} // namespace std2

#endif // STD2_H

#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <cstddef>

namespace s21 {

template <typename Type, size_t N>
class array {
 public:
  using value_type = Type;
  using reference = Type&;
  using const_reference = const Type&;
  using iterator = Type*;
  using const_iterator = const Type*;
  using size_type = size_t;

  array() noexcept;
  explicit array(const std::initializer_list<value_type>& items) noexcept;
  explicit array(const array& other) noexcept;
  array(array&& other) noexcept;
  ~array() noexcept;

  inline array& operator=(array&& other) noexcept;

  inline reference at(size_type pos) noexcept;
  inline reference operator[](size_type pos) noexcept;
  inline const_reference front() const noexcept;
  inline const_reference back() const noexcept;
  inline iterator data() noexcept;

  inline iterator begin() noexcept;
  inline iterator end() noexcept;

  inline bool empty() const noexcept;
  inline size_type size() const noexcept;
  inline size_type max_size() const noexcept;

  inline void swap(array& other) noexcept;
  inline void fill(const_reference value) noexcept;

 private:
  value_type array_[N]{};
};

template <typename Type, size_t N>
array<Type, N>::array() noexcept {}

template <typename Type, size_t N>
array<Type, N>::array(std::initializer_list<value_type> const& items) noexcept
    : array() {
  size_type i = 0;
  for (typename std::initializer_list<value_type>::iterator it = items.begin();
       it != items.end(); ++it) {
    array_[i] = *it;
    i++;
  }
}

template <typename Type, size_t N>
array<Type, N>::array(const array& other) noexcept : array() {
  if (other.array_ != nullptr) {
    for (size_type i = 0; i != N; ++i) {
      array_[i] = other.array_[i];
    }
  }
}

template <typename Type, size_t N>
array<Type, N>::array(array&& other) noexcept : array() {
  std::move(other.array_, other.array_ + N, array_);
}

template <typename Type, size_t N>
array<Type, N>::~array() noexcept {}

template <typename Type, size_t N>
inline array<Type, N>& array<Type, N>::operator=(array&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  std::move(other.array_, other.array_ + N, array_);
  return *this;
}

template <typename Type, size_t N>
inline typename array<Type, N>::reference array<Type, N>::at(
    size_type pos) noexcept {
  return *(array_ + pos);
}

template <typename Type, size_t N>
inline typename array<Type, N>::reference array<Type, N>::operator[](
    size_type pos) noexcept {
  return at(pos);
}

template <typename Type, size_t N>
inline typename array<Type, N>::const_reference array<Type, N>::front()
    const noexcept {
  return array_[0];
}

template <typename Type, size_t N>
inline typename array<Type, N>::const_reference array<Type, N>::back()
    const noexcept {
  return array_[N - 1];
}

template <typename Type, size_t N>
inline typename array<Type, N>::iterator array<Type, N>::data() noexcept {
  return array_;
}

template <typename Type, size_t N>
inline typename array<Type, N>::iterator array<Type, N>::begin() noexcept {
  return &(array_[0]);
}

template <typename Type, size_t N>
inline typename array<Type, N>::iterator array<Type, N>::end() noexcept {
  return &(array_[N - 1]);
}

template <typename Type, size_t N>
inline bool array<Type, N>::empty() const noexcept {
  return N == static_cast<size_type>(0) ? true : false;
}

template <typename Type, size_t N>
inline typename array<Type, N>::size_type array<Type, N>::size()
    const noexcept {
  return N;
}

template <typename Type, size_t N>
inline typename array<Type, N>::size_type array<Type, N>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() / (sizeof(value_type));
}

template <typename Type, size_t N>
inline void array<Type, N>::swap(array& other) noexcept {
  std::swap(array_, other.array_);
}

template <typename Type, size_t N>
inline void array<Type, N>::fill(const_reference value) noexcept {
  for (size_type i = 0; i != N; ++i) {
    array_[i] = value;
  }
}

}  // namespace s21

#endif

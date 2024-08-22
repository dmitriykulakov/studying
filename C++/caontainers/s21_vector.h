#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <string>

namespace s21 {

template <class T>
class Vector {
 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  void reserve_more_capacity(size_type size);

 public:
  Vector();
  explicit Vector(size_type n);
  explicit Vector(std::initializer_list<value_type> const &items);
  explicit Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector();
  Vector<T> &operator=(Vector &v);
  Vector<T> &operator=(Vector &&v);
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data();
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();
  void clear();
  iterator insert(iterator pos, const_reference value);
  iterator erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
};

template <typename T>
void Vector<T>::reserve_more_capacity(size_t size) {
  if (size > m_capacity) {
    value_type *buff = new value_type[size]{};
    for (size_t i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);
    delete[] arr;
    arr = buff;
    m_capacity = size;
  }
}

template <typename T>
Vector<T>::Vector() {
  m_size = 0U;
  m_capacity = 0U;
  arr = nullptr;
}

template <typename T>
Vector<T>::Vector(size_type n) {
  m_size = n;
  m_capacity = n;
  if (n > 0) {
    arr = new T[n]{};
  } else
    arr = nullptr;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> const &items) {
  arr = new value_type[items.size()]{};
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;
    i++;
  }
  m_size = items.size();
  m_capacity = items.size();
}

template <typename T>
Vector<T>::Vector(const Vector &v) {
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  if (v.m_size > 0) {
    arr = new T[v.m_capacity + 1]{};
    for (size_t i{}; i < v.m_size; i++) {
      arr[i] = v.arr[i];
    }
  } else
    arr = nullptr;
}

template <typename T>
Vector<T>::Vector(Vector &&v) {
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  arr = v.arr;
  v.arr = nullptr;
  v.m_size = 0;
  v.m_capacity = 0;
}

template <typename T>
Vector<T>::~Vector() {
  if (m_capacity) {
    delete[] arr;
    m_capacity = 0;
    m_size = 0;
  }
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &v) {
  if (this == &v) return *this;
  this->~Vector();
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  if (v.m_size > 0) {
    arr = new T[v.m_capacity + 1]{};
    for (size_t i{}; i < v.m_size; i++) {
      arr[i] = v.arr[i];
    }
  } else
    arr = nullptr;
  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&v) {
  if (this == &v) return *this;
  this->~Vector();
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  arr = v.arr;
  v.arr = nullptr;
  v.m_size = 0;
  v.m_capacity = 0;
  return *this;
}

template <typename T>
T &Vector<T>::at(size_type pos) {
  if (pos >= m_size) throw std::out_of_range("ERROR");
  return arr[pos];
}

template <typename T>
T &Vector<T>::operator[](size_type pos) {
  return arr[pos];
}

template <typename T>
const T &Vector<T>::front() const {
  return arr[0];
}

template <typename T>
const T &Vector<T>::back() const {
  return arr[(m_size - 1)];
}

template <typename T>
T *Vector<T>::data() {
  return arr;
}

template <typename T>
T *Vector<T>::begin() {
  return &(arr[0]);
}

template <typename T>
T *Vector<T>::end() {
  return &(arr[m_size]);
}

template <typename T>
bool Vector<T>::empty() {
  if (m_size)
    return 0;
  else
    return 1;
}

template <typename T>
size_t Vector<T>::size() {
  return m_size;
}

template <typename T>
size_t Vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T>
void Vector<T>::reserve(size_type size) {
  reserve_more_capacity(size);
}

template <typename T>
size_t Vector<T>::capacity() {
  return m_capacity;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  m_capacity = m_size;
}

template <typename T>
void Vector<T>::clear() {
  m_size = 0;
}

template <typename T>
T *Vector<T>::insert(iterator pos, const_reference value) {
  int position{};
  if (end() == pos) {
    position = m_size;
  } else {
    for (auto it = begin(); it != pos; it++) {
      position++;
    }
  }
  if (m_size == m_capacity) {
    reserve_more_capacity(m_size + 2);
  }
  m_size++;
  for (int i = m_size - 1; i != position; i--) {
    at(i) = at(i - 1);
  }
  at(position) = value;
  return &(at(position));
}

template <typename T>
T *Vector<T>::erase(iterator pos) {
  for (auto it = pos; it != end() - 1; it++) {
    *it = *(it + 1);
  }
  m_size--;
  return pos;
}

template <typename T>
void Vector<T>::push_back(const T &v) {
  if (m_size == m_capacity) {
    reserve_more_capacity(m_size + 2);
  }
  arr[m_size++] = v;
}

template <typename T>
void Vector<T>::pop_back() {
  if (m_size) m_size--;
}

template <typename T>
void Vector<T>::swap(Vector &other) {
  std::swap(this->m_size, other.m_size);
  std::swap(this->m_capacity, other.m_capacity);
  std::swap(this->arr, other.arr);
}

template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args &&...args) {
  for (auto arg : {std::forward<Args>(args)...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
T *Vector<T>::insert_many(const_iterator pos, Args &&...args) {
  T *tmp_pos = const_cast<T *>(pos);
  for (auto arg : {std::forward<Args>(args)...}) {
    tmp_pos = insert(tmp_pos, arg);
  }
  return tmp_pos;
}

}  // namespace s21

#endif
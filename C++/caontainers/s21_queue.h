#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <cstddef>
#include <new>
#include <stdexcept>

namespace s21 {

template <typename Type>

class queue {
 public:
  using value_type = Type;
  using reference = Type&;
  using const_reference = const Type&;
  using size_type = size_t;

  queue() noexcept;
  explicit queue(std::initializer_list<value_type> const& items);
  queue(const queue& other);
  queue(queue&& other) noexcept;
  ~queue() noexcept;

  inline queue& operator=(const queue& other);
  inline queue& operator=(queue&& other) noexcept;

  inline const_reference front() const;
  inline const_reference back() const;

  inline bool empty() const noexcept;
  inline size_type size() const noexcept;
  inline void push(const_reference value);
  inline void pop() noexcept;
  inline void swap(queue& other) noexcept;

  template <typename... Args>
  inline void insert_many_back(Args&&... args);

 private:
  typedef struct Data {
    value_type value_;
    Data* next_node_;
  } Node;
  size_type size_;
  Node* front_node_;
  Node* back_node_;
};

template <typename Type>
queue<Type>::queue() noexcept
    : size_(static_cast<size_type>(0)),
      front_node_(nullptr),
      back_node_(nullptr) {}

template <typename Type>
queue<Type>::queue(std::initializer_list<value_type> const& items) : queue() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename Type>
queue<Type>::queue(const queue& other) : queue() {
  Node* runner = other.back_node_;

  queue<Type> tmp_queue;
  while (runner != nullptr) {
    tmp_queue.push(runner->value_);
    runner = runner->next_node_;
  }

  runner = tmp_queue.back_node_;
  while (runner != nullptr) {
    this->push(runner->value_);
    runner = runner->next_node_;
  }

  size_ = other.size_;
}

template <typename Type>
queue<Type>::queue(queue&& other) noexcept : queue() {
  this->~queue();

  this->size_ = other.size_;
  this->front_node_ = other.front_node_;
  this->back_node_ = other.back_node_;
  other.size_ = static_cast<size_type>(0);
  other.front_node_ = nullptr;
  other.back_node_ = nullptr;
}

template <typename Type>
queue<Type>::~queue() noexcept {
  while (front_node_ != nullptr) {
    pop();
  }
}

template <typename Type>
inline queue<Type>& queue<Type>::operator=(const queue& other) {
  if (this == &other) {
    return *this;
  }

  this->~queue();

  Node* runner = other.back_node_;

  queue<Type> tmp_queue;
  while (runner != nullptr) {
    tmp_queue.push(runner->value_);
    runner = runner->next_node_;
  }

  runner = tmp_queue.back_node_;
  while (runner != nullptr) {
    this->push(runner->value_);
    runner = runner->next_node_;
  }

  size_ = other.size_;

  return *this;
}

template <typename Type>
inline queue<Type>& queue<Type>::operator=(queue&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  this->~queue();

  this->size_ = other.size_;
  this->front_node_ = other.front_node_;
  this->back_node_ = other.back_node_;
  other.size_ = static_cast<size_type>(0);
  other.front_node_ = nullptr;
  other.back_node_ = nullptr;

  return *this;
}

template <typename Type>
inline typename queue<Type>::const_reference queue<Type>::front() const {
  if (front_node_ == nullptr) {
    throw std::out_of_range("queue is empty");
  }
  return static_cast<const_reference>(front_node_->value_);
}

template <typename Type>
inline typename queue<Type>::const_reference queue<Type>::back() const {
  if (back_node_ == nullptr) {
    throw std::out_of_range("queue is empty");
  }
  return static_cast<const_reference>(back_node_->value_);
}

template <typename Type>
inline bool queue<Type>::empty() const noexcept {
  return size_ == static_cast<size_type>(0) ? true : false;
}

template <typename Type>
inline typename queue<Type>::size_type queue<Type>::size() const noexcept {
  return size_;
}

template <typename Type>
inline void queue<Type>::push(const_reference value) {
  Node* new_node = new Node;
  new_node->value_ = value;
  new_node->next_node_ = back_node_;
  back_node_ = new_node;
  if (size_ == 0) {
    front_node_ = new_node;
  }
  ++size_;
}

template <typename Type>
inline void queue<Type>::pop() noexcept {
  if (size_ != 0) {
    Node* runner = back_node_;
    while (runner != front_node_ && runner->next_node_ != front_node_) {
      runner = runner->next_node_;
    }

    if (runner == front_node_) {
      front_node_ = nullptr;
      back_node_ = nullptr;
      --size_;
      delete runner;
    } else {
      Node* tmp_node = runner->next_node_;
      front_node_ = runner;
      --size_;
      delete tmp_node;
    }
  }
}

template <typename Type>
inline void queue<Type>::swap(queue& other) noexcept {
  queue<Type> tmp_queue;
  tmp_queue = other;
  other = *this;
  *this = tmp_queue;
}

template <typename Type>
template <typename... Args>
inline void queue<Type>::insert_many_back(Args&&... args) {
  for (auto arg : {std::forward<Args>(args)...}) {
    push(arg);
  }
}

}  // namespace s21

#endif

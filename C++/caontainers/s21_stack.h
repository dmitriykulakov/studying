#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <cstddef>
#include <new>
#include <stdexcept>

namespace s21 {

template <typename Type>

class stack {
 public:
  using value_type = Type;
  using reference = Type&;
  using const_reference = const Type&;
  using size_type = size_t;

  stack() noexcept;
  explicit stack(std::initializer_list<value_type> const& items);
  stack(const stack& other);
  stack(stack&& other) noexcept;
  ~stack() noexcept;

  inline stack& operator=(const stack& other);
  inline stack& operator=(stack&& other) noexcept;

  inline const_reference top() const;

  inline bool empty() const noexcept;
  inline size_type size() const noexcept;
  inline void push(const_reference value);
  inline void pop() noexcept;
  inline void swap(stack& other) noexcept;

  template <typename... Args>
  inline void insert_many_front(Args&&... args);

 private:
  typedef struct Data {
    value_type value_;
    Data* next_node_;
  } Node;
  size_type size_;
  Node* top_node_;
};

template <typename Type>
stack<Type>::stack() noexcept
    : size_(static_cast<size_type>(0)), top_node_(nullptr) {}

template <typename Type>
stack<Type>::stack(std::initializer_list<value_type> const& items) : stack() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename Type>
stack<Type>::stack(const stack& other) : stack() {
  Node* runner = other.top_node_;

  stack<Type> tmp_stack;
  while (runner != nullptr) {
    tmp_stack.push(runner->value_);
    runner = runner->next_node_;
  }

  runner = tmp_stack.top_node_;
  while (runner != nullptr) {
    this->push(runner->value_);
    runner = runner->next_node_;
  }

  size_ = other.size_;
}

template <typename Type>
stack<Type>::stack(stack&& other) noexcept : stack() {
  this->~stack();

  this->size_ = other.size_;
  this->top_node_ = other.top_node_;
  other.size_ = static_cast<size_type>(0);
  other.top_node_ = nullptr;
}

template <typename Type>
stack<Type>::~stack() noexcept {
  while (top_node_ != nullptr) {
    pop();
  }
}

template <typename Type>
inline stack<Type>& stack<Type>::operator=(const stack& other) {
  if (this == &other) {
    return *this;
  }

  this->~stack();

  Node* runner = other.top_node_;

  stack<Type> tmp_stack;
  while (runner != nullptr) {
    tmp_stack.push(runner->value_);
    runner = runner->next_node_;
  }

  runner = tmp_stack.top_node_;
  while (runner != nullptr) {
    this->push(runner->value_);
    runner = runner->next_node_;
  }

  size_ = other.size_;

  return *this;
}

template <typename Type>
inline stack<Type>& stack<Type>::operator=(stack&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  this->~stack();

  this->size_ = other.size_;
  this->top_node_ = other.top_node_;
  other.size_ = static_cast<size_type>(0);
  other.top_node_ = nullptr;

  return *this;
}

template <typename Type>
inline typename stack<Type>::const_reference stack<Type>::top() const {
  if (top_node_ == nullptr) {
    throw std::out_of_range("stack is empty");
  }
  return static_cast<const_reference>(top_node_->value_);
}

template <typename Type>
inline bool stack<Type>::empty() const noexcept {
  return size_ == static_cast<size_type>(0) ? true : false;
}

template <typename Type>
inline typename stack<Type>::size_type stack<Type>::size() const noexcept {
  return size_;
}

template <typename Type>
inline void stack<Type>::push(const_reference value) {
  Node* new_node = new Node;
  new_node->value_ = value;
  new_node->next_node_ = top_node_;
  top_node_ = new_node;
  ++size_;
}

template <typename Type>
inline void stack<Type>::pop() noexcept {
  if (size_ != 0) {
    Node* tmp_node = top_node_;
    top_node_ = top_node_->next_node_;
    --size_;
    delete tmp_node;
  }
}

template <typename Type>
inline void stack<Type>::swap(stack& other) noexcept {
  stack<Type> tmp_stack;
  tmp_stack = other;
  other = *this;
  *this = tmp_stack;
}

template <typename Type>
template <typename... Args>
inline void stack<Type>::insert_many_front(Args&&... args) {
  for (auto arg : {std::forward<Args>(args)...}) {
    push(arg);
  }
}

}  // namespace s21

#endif

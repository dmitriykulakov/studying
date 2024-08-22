#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstddef>
#include <limits>
#include <new>
#include <stdexcept>

namespace s21 {

template <typename Type>
class list {
  class ListConstIterator;
  class ListIterator;

 public:
  using value_type = Type;
  using reference = Type&;
  using const_reference = const Type&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  list() noexcept;
  explicit list(const size_type n);
  explicit list(const std::initializer_list<value_type>& items);
  list(const list& other);
  list(list&& other) noexcept;
  ~list() noexcept;

  inline list& operator=(const list& other);
  inline list& operator=(list&& other) noexcept;

  inline const_reference front() const;
  inline const_reference back() const;

  inline iterator begin() const noexcept;
  inline iterator end() const noexcept;

  inline bool empty() const noexcept;
  inline size_type size() const noexcept;
  inline size_type max_size() const noexcept;

  inline void clear() noexcept;
  inline iterator insert(iterator pos, const_reference value);
  inline void erase(const iterator& pos) noexcept;

  inline void push_back(const_reference value);
  inline void pop_back();
  inline void push_front(const_reference value);
  inline void pop_front();
  inline void swap(list& other) noexcept;

  inline void merge(list& other);
  inline void splice(const const_iterator& pos, list& other);
  inline void reverse();
  inline void unique() noexcept;
  inline void sort() noexcept;

  template <typename... Args>
  inline iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  inline void insert_many_back(Args&&... args);
  template <typename... Args>
  inline void insert_many_front(Args&&... args);

 private:
  typedef struct Data {
    value_type value_;
    Data* next_node_;
    Data* prev_node_;
  } Node;
  size_type size_;
  Node* front_node_;
  Node* back_node_;
  Node* end_node_;

  // ##################################
  // Iterators begin
  // ##################################

  class ListConstIterator {
   protected:
    Node* ptr_;
    value_type zero_value_;
    reference zero_ = zero_value_;

   public:
    ListConstIterator() noexcept : ptr_(nullptr), zero_value_(0) {}
    explicit ListConstIterator(Node* ptr) noexcept
        : ptr_(ptr), zero_value_(0) {}
    ListConstIterator(const ListConstIterator& other) noexcept
        : ptr_(other.ptr_), zero_value_(0) {}

    ListConstIterator& operator=(const ListConstIterator& other) noexcept {
      if (this == &other) {
        return *this;
      }

      ptr_ = other.ptr_;
      zero_value_ = other.zero_value_;
      zero_ = zero_value_;

      return *this;
    }

    const_reference operator*() const noexcept {
      return ptr_ != nullptr ? ptr_->value_ : zero_;
    }

    bool operator==(const ListConstIterator& other) const noexcept {
      bool result;
      if (this->ptr_ == other.ptr_) {
        result = true;
      } else {
        result = false;
      }
      return result;
    }

    bool operator!=(const ListConstIterator& other) const noexcept {
      return !(*this == other);
    }

    ListConstIterator& operator++() noexcept {
      ptr_ = ptr_->next_node_;
      return *this;
    }

    ListConstIterator operator++(int) noexcept {
      ListConstIterator tmp_iterator = *this;
      ptr_ = ptr_->next_node_;
      return tmp_iterator;
    }

    ListConstIterator& operator--() noexcept {
      ptr_ = ptr_->prev_node_;
      return *this;
    }

    ListConstIterator operator--(int) noexcept {
      ListConstIterator tmp_iterator = *this;
      ptr_ = ptr_->prev_node_;
      return tmp_iterator;
    }

    Node* get_iterator_node() const noexcept { return ptr_; }
  };

  class ListIterator : public ListConstIterator {
   public:
    ListIterator() noexcept : ListConstIterator() {}
    explicit ListIterator(Node* ptr) noexcept : ListConstIterator(ptr) {}
    ListIterator(const ListIterator& other) noexcept
        : ListConstIterator(other) {}

    ListIterator& operator=(const ListIterator& other) noexcept {
      if (this == &other) {
        return *this;
      }

      ListIterator::ptr_ = other.ptr_;
      ListIterator::zero_value_ = other.zero_value_;
      ListIterator::zero_ = ListIterator::zero_value_;

      return *this;
    }

    reference operator*() const noexcept {
      return ListIterator::ptr_ != nullptr ? ListIterator::ptr_->value_
                                           : ListIterator::zero_;
    }

    ListIterator& operator++() noexcept {
      ListIterator::ptr_ = ListIterator::ptr_->next_node_;
      return *this;
    }

    ListIterator operator++(int) noexcept {
      ListIterator tmp_iterator = *this;
      ListIterator::ptr_ = ListIterator::ptr_->next_node_;
      return tmp_iterator;
    }

    ListIterator& operator--() noexcept {
      ListIterator::ptr_ = ListIterator::ptr_->prev_node_;
      return *this;
    }

    ListIterator operator--(int) noexcept {
      ListIterator tmp_iterator = *this;
      ListIterator::ptr_ = ListIterator::ptr_->prev_node_;
      return tmp_iterator;
    }
  };
};

// ##################################
// Iterators end
// ##################################

template <typename Type>
list<Type>::list() noexcept
    : size_(static_cast<size_type>(0)),
      front_node_(nullptr),
      back_node_(nullptr),
      end_node_(nullptr) {}

template <typename Type>
list<Type>::list(const list<Type>::size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_back(0);
  }
}

template <typename Type>
list<Type>::list(std::initializer_list<value_type> const& items) : list() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push_back(*it);
  }
}

template <typename Type>
list<Type>::list(const list& other) : list() {
  Node* runner = other.back_node_;
  while (runner != nullptr) {
    push_front(runner->value_);
    runner = runner->prev_node_;
  }

  size_ = other.size_;
}

template <typename Type>
list<Type>::list(list&& other) noexcept : list() {
  this->~list();

  this->size_ = other.size_;
  this->front_node_ = other.front_node_;
  this->back_node_ = other.back_node_;
  this->end_node_ = other.end_node_;

  other.size_ = static_cast<size_type>(0);
  other.front_node_ = nullptr;
  other.back_node_ = nullptr;
  other.end_node_ = nullptr;
}

template <typename Type>
list<Type>::~list() noexcept {
  while (front_node_ != nullptr) {
    pop_front();
  }
}

template <typename Type>
inline list<Type>& list<Type>::operator=(const list& other) {
  if (this == &other) {
    return *this;
  }

  this->~list();

  Node* runner = other.back_node_;
  while (runner != nullptr) {
    push_front(runner->value_);
    runner = runner->prev_node_;
  }

  size_ = other.size_;

  return *this;
}

template <typename Type>
inline list<Type>& list<Type>::operator=(list&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  this->~list();

  this->size_ = other.size_;
  this->front_node_ = other.front_node_;
  this->back_node_ = other.back_node_;
  this->end_node_ = other.end_node_;

  other.size_ = static_cast<size_type>(0);
  other.front_node_ = nullptr;
  other.back_node_ = nullptr;
  other.end_node_ = nullptr;

  return *this;
}

template <typename Type>
inline typename list<Type>::const_reference list<Type>::front() const {
  if (front_node_ == nullptr) {
    throw std::out_of_range("list is empty");
  }
  return static_cast<const_reference>(front_node_->value_);
}

template <typename Type>
inline typename list<Type>::const_reference list<Type>::back() const {
  if (back_node_ == nullptr) {
    throw std::out_of_range("list is empty");
  }
  return static_cast<const_reference>(back_node_->value_);
}

template <typename Type>
inline typename list<Type>::iterator list<Type>::begin() const noexcept {
  return list<Type>::iterator(front_node_);
}

template <typename Type>
inline typename list<Type>::iterator list<Type>::end() const noexcept {
  return list<Type>::iterator(end_node_);
}

template <typename Type>
inline bool list<Type>::empty() const noexcept {
  return size_ == static_cast<size_type>(0) ? true : false;
}

template <typename Type>
inline typename list<Type>::size_type list<Type>::size() const noexcept {
  return size_;
}
template <typename Type>
inline typename list<Type>::size_type list<Type>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename Type>
inline void list<Type>::clear() noexcept {
  this->~list();
}

template <typename Type>
inline void list<Type>::erase(const iterator& pos) noexcept {
  Node* tmp_node = pos.get_iterator_node();
  if (size_ == 0) {
    return;
  } else {
    if (tmp_node == front_node_) {
      pop_front();
    } else if (tmp_node == end_node_) {
      pop_back();
    } else {
      (tmp_node->prev_node_)->next_node_ = tmp_node->next_node_;
      (tmp_node->next_node_)->prev_node_ = tmp_node->prev_node_;
      --size_;
      delete tmp_node;
    }
  }
}
template <typename Type>
inline typename list<Type>::iterator list<Type>::insert(iterator pos,
                                                        const_reference value) {
  Node* tmp_node = pos.get_iterator_node();
  list<Type>::iterator result;
  if (tmp_node == front_node_) {
    push_front(value);
    if (size_ == 1) {
      pos = begin();
    } else {
      --pos;
    }
  } else if (tmp_node == back_node_) {
    push_back(value);
    ++pos;
  } else {
    Node* new_node = new Node;
    new_node->value_ = value;
    new_node->next_node_ = tmp_node;
    new_node->prev_node_ = tmp_node->prev_node_;
    (new_node->prev_node_)->next_node_ = new_node;
    tmp_node->prev_node_ = new_node;
    ++size_;
    --pos;
  }
  return pos;
}

template <typename Type>
inline void list<Type>::push_back(const_reference value) {
  Node* new_node = new Node;
  new_node->value_ = value;

  if (size_ == 0) {
    end_node_ = new Node;
    end_node_->next_node_ = nullptr;
    end_node_->prev_node_ = nullptr;

    end_node_->prev_node_ = new_node;
    new_node->next_node_ = end_node_;
    new_node->prev_node_ = nullptr;
    front_node_ = new_node;
    back_node_ = new_node;
  } else {
    end_node_->prev_node_ = new_node;
    new_node->next_node_ = end_node_;
    new_node->prev_node_ = back_node_;
    back_node_->next_node_ = new_node;
    back_node_ = new_node;
  }

  ++size_;
}

template <typename Type>
inline void list<Type>::pop_back() {
  if (size_ != 0) {
    Node* tmp_node = back_node_;
    back_node_ = back_node_->prev_node_;
    end_node_->prev_node_ = end_node_;

    if (back_node_ != nullptr) {
      back_node_->next_node_ = end_node_;
    }
    --size_;
    if (size_ == 0) {
      front_node_ = nullptr;
      back_node_ = nullptr;
      end_node_->next_node_ = nullptr;
      end_node_->prev_node_ = nullptr;
      delete end_node_;
      end_node_ = nullptr;
    }
    delete tmp_node;
  }
}

template <typename Type>
inline void list<Type>::push_front(const_reference value) {
  Node* new_node = new Node;
  new_node->value_ = value;

  if (size_ == 0) {
    end_node_ = new Node;
    end_node_->next_node_ = nullptr;
    end_node_->prev_node_ = nullptr;

    end_node_->prev_node_ = new_node;
    new_node->next_node_ = end_node_;
    new_node->prev_node_ = nullptr;
    front_node_ = new_node;
    back_node_ = new_node;
  } else {
    new_node->prev_node_ = nullptr;
    new_node->next_node_ = front_node_;
    front_node_->prev_node_ = new_node;
    front_node_ = new_node;
  }

  ++size_;
}

template <typename Type>
inline void list<Type>::pop_front() {
  if (size_ != 0) {
    Node* tmp_node = front_node_;
    front_node_ = front_node_->next_node_;
    if (front_node_ != nullptr) {
      front_node_->prev_node_ = nullptr;
    }
    --size_;
    if (size_ == 0) {
      front_node_ = nullptr;
      back_node_ = nullptr;
      end_node_->next_node_ = nullptr;
      end_node_->prev_node_ = nullptr;
      delete end_node_;
      end_node_ = nullptr;
    }
    delete tmp_node;
  }
}

template <typename Type>
inline void list<Type>::swap(list& other) noexcept {
  list<Type> tmp_list;
  tmp_list = other;
  other = *this;
  *this = tmp_list;
}

template <typename Type>
inline void list<Type>::merge(list& other) {
  if (this == &other) {
    return;
  }

  list<Type> tmp_list;
  for (typename list<Type>::iterator i = begin(); i != end(); ++i) {
    tmp_list.push_front(*i);
  }

  for (typename list<Type>::iterator i = other.begin(); i != other.end(); ++i) {
    tmp_list.push_front(*i);
  }

  other.~list();
  tmp_list.sort();
  *this = std::move(tmp_list);

  return;
}

template <typename Type>
inline void list<Type>::splice(const const_iterator& pos, list& other) {
  if (this == &other) {
    return;
  }

  typename list<Type>::iterator it(pos.get_iterator_node());

  for (typename list<Type>::iterator i = other.begin(); i != other.end(); ++i) {
    insert(it, *i);
  }
  other.~list();

  return;
}

template <typename Type>
inline void list<Type>::reverse() {
  list<Type> tmp_list;
  Node* runner = back_node_;
  while (runner != nullptr) {
    tmp_list.push_back(runner->value_);
    runner = runner->prev_node_;
  }
  *this = std::move(tmp_list);
}

template <typename Type>
inline void list<Type>::unique() noexcept {
  for (typename list<Type>::iterator i = begin(); i != end(); ++i) {
    for (typename list<Type>::iterator j = i; j != end(); ++j) {
      if ((i != j) && (*i == *j)) {
        typename list<Type>::iterator it_erase = j;
        --j;
        erase(it_erase);
      }
    }
  }
}

template <typename Type>
inline void list<Type>::sort() noexcept {
  for (typename list<Type>::iterator i = begin(); i != end(); ++i) {
    for (typename list<Type>::iterator j = i; j != end(); ++j) {
      if ((i != j) && (*i > *j)) {
        std::swap(*i, *j);
      }
    }
  }
}

template <typename Type>
template <typename... Args>
inline typename list<Type>::iterator list<Type>::insert_many(
    typename list<Type>::const_iterator pos, Args&&... args) {
  for (auto arg : {std::forward<Args>(args)...}) {
    insert(iterator(pos.get_iterator_node()), arg);
  }
  return iterator(pos.get_iterator_node());
}

template <typename Type>
template <typename... Args>
inline void list<Type>::insert_many_back(Args&&... args) {
  for (auto arg : {std::forward<Args>(args)...}) {
    push_back(arg);
  }
}

template <typename Type>
template <typename... Args>
inline void list<Type>::insert_many_front(Args&&... args) {
  for (auto arg : {std::forward<Args>(args)...}) {
    push_front(arg);
  }
}

}  // namespace s21

#endif

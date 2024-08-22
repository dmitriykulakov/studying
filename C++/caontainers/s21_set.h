#ifndef S21_SET_H_
#define S21_SET_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

#include "./s21_vector.h"

namespace s21 {

template <typename Key>
struct NodeS {
  struct NodeS* parent = nullptr;
  struct NodeS* left = nullptr;
  struct NodeS* right = nullptr;
  bool end_flag = false;
  Key item{};
};

template <class Key>
class Set {
  class SetConstIterator;
  class SetIterator;

 public:
  using value_type = Key;
  using reference = Key&;
  using const_reference = const Key&;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;
  using size_type = size_t;

  Set();
  explicit Set(std::initializer_list<value_type> const& items);
  NodeS<Key>* createNodeS(Key item);
  void cleanMemory(NodeS<Key>* tmp);
  Set(const Set& s);
  void copyFunction(NodeS<Key>* tmp);
  Set(Set&& s);
  ~Set();
  Set<Key>& operator=(Set& v);
  Set<Key>& operator=(Set&& v);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const Key& item);
  std::pair<iterator, bool> addNodeS(const Key& item);
  iterator erase(iterator pos);
  void swap(Set& other);
  void merge(Set& other);
  iterator find(const Key& key);
  bool contains(const Key& key);

  template <typename... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  size_t m_size = 0U;
  struct NodeS<Key>* begin_NodeS = nullptr;
  struct NodeS<Key>* end_NodeS = nullptr;
  struct NodeS<Key>* root = nullptr;

  class SetConstIterator {
   public:
    struct NodeS<Key>* ptr_;

   public:
    SetConstIterator() noexcept : ptr_(nullptr) {}
    explicit SetConstIterator(NodeS<Key>* ptr) noexcept : ptr_(ptr) {}
    SetConstIterator(const SetConstIterator& other) noexcept
        : ptr_(other.ptr_) {}

    const_reference operator*() const noexcept { return ptr_->item; }

    SetConstIterator& operator=(const SetConstIterator& other) noexcept {
      if (this == &other) {
        return *this;
      }
      ptr_ = other.ptr_;
      return *this;
    }

    bool operator==(const SetConstIterator& other) const noexcept {
      bool result;
      if (this->ptr_ == other.ptr_) {
        result = true;
      } else {
        result = false;
      }
      return result;
    }

    bool operator!=(const SetConstIterator& other) const noexcept {
      return !(*this == other);
    }

    SetConstIterator& operator++() noexcept {
      if (ptr_->end_flag) return *this;
      if (ptr_->right != nullptr) {
        ptr_ = ptr_->right;
        while (ptr_->left != nullptr) ptr_ = ptr_->left;
      } else {
        while (ptr_->parent->item < ptr_->item && !(ptr_->parent->end_flag))
          ptr_ = ptr_->parent;
        ptr_ = ptr_->parent;
      }
      return *this;
    }

    SetConstIterator& operator--() noexcept {
      if (ptr_->left != nullptr) {
        ptr_ = ptr_->left;
        while (ptr_->right != nullptr) ptr_ = ptr_->right;
      } else if (ptr_->end_flag && ptr_->parent != nullptr) {
        ptr_ = ptr_->parent;
      } else {
        while (ptr_->parent != nullptr && ptr_->parent->item > ptr_->item)
          ptr_ = ptr_->parent;
        ptr_ = ptr_->parent;
      }
      return *this;
    }
  };

  class SetIterator : public SetConstIterator {
   public:
    SetIterator() noexcept : SetConstIterator() {}
    explicit SetIterator(NodeS<Key>* ptr) noexcept : SetConstIterator(ptr) {}
    SetIterator(const SetIterator& other) noexcept : SetConstIterator(other) {}

    reference operator*() const noexcept { return SetIterator::ptr_->item; }

    SetIterator& operator=(const SetIterator& other) noexcept {
      if (this == &other) {
        return *this;
      }
      SetIterator::ptr_ = other.ptr_;
      return *this;
    }
  };
};

template <typename Key>
void Set<Key>::cleanMemory(NodeS<Key>* tmp) {
  if (tmp->left != nullptr) {
    cleanMemory(tmp->left);
  }
  if (tmp->right != nullptr) {
    cleanMemory(tmp->right);
  }
  if (tmp != end_NodeS) delete tmp;
}

template <typename Key>
Set<Key>::Set() {
  m_size = 0U;
  Key tmp{};
  end_NodeS = createNodeS(tmp);
  end_NodeS->end_flag = true;
  begin_NodeS = end_NodeS;
  root = end_NodeS;
}

template <typename Key>
NodeS<Key>* Set<Key>::createNodeS(value_type item) {
  NodeS<value_type>* tmp = new struct NodeS<Key>;
  tmp->parent = nullptr;
  tmp->left = nullptr;
  tmp->right = nullptr;
  tmp->item = item;
  return tmp;
}

template <typename Key>
Set<Key>::Set(std::initializer_list<Key> const& items) {
  Key tmp{};
  end_NodeS = createNodeS(tmp);
  end_NodeS->end_flag = true;
  begin_NodeS = end_NodeS;
  root = end_NodeS;
  for (auto it = items.begin(); it != items.end(); it++) insert(*it);
}

template <typename Key>
Set<Key>::Set(const Set& s) : Set() {
  clear();
  if (s.m_size > 0) {
    copyFunction(s.root);
    m_size = s.m_size;
  }
}

template <typename Key>
void Set<Key>::copyFunction(NodeS<Key>* tmp) {
  insert(tmp->item);
  if (tmp->left != nullptr) {
    copyFunction(tmp->left);
  }
  if (tmp->right != nullptr && !(tmp->right->end_flag)) {
    copyFunction(tmp->right);
  }
}

template <typename Key>
Set<Key>::Set(Set&& s) {
  if (end_NodeS != nullptr) clear();
  m_size = s.m_size;
  begin_NodeS = s.begin_NodeS;
  end_NodeS = s.end_NodeS;
  root = s.root;
  s.m_size = 0;
  s.begin_NodeS = nullptr;
  s.end_NodeS = nullptr;
  s.root = nullptr;
}

template <typename Key>
Set<Key>::~Set() {
  if (end_NodeS != nullptr) {
    cleanMemory(root);
    delete end_NodeS;
  }
}

template <typename Key>
Set<Key>& Set<Key>::operator=(Set& v) {
  if (this == &v) return *this;
  if (end_NodeS != nullptr) clear();
  copyFunction(v.root);
  return *this;
}

template <typename Key>
Set<Key>& Set<Key>::operator=(Set&& v) {
  if (this == &v) return *this;
  if (end_NodeS != nullptr) {
    clear();
    delete end_NodeS;
  }
  m_size = v.m_size;
  begin_NodeS = v.begin_NodeS;
  end_NodeS = v.end_NodeS;
  root = v.root;
  v.m_size = 0;
  v.begin_NodeS = nullptr;
  v.end_NodeS = nullptr;
  v.root = nullptr;
  return *this;
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() {
  return Set<Key>::iterator(begin_NodeS);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::end() {
  return Set<Key>::iterator(end_NodeS);
}

template <typename Key>
bool Set<Key>::empty() {
  return begin() == end();
}

template <typename Key>
size_t Set<Key>::size() {
  return m_size;
}

template <typename Key>
size_t Set<Key>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(struct NodeS<Key>);
}

template <typename Key>
void Set<Key>::clear() {
  cleanMemory(root);
  m_size = 0;
  end_NodeS->parent = nullptr;
  end_NodeS->left = nullptr;
  begin_NodeS = end_NodeS;
  root = end_NodeS;
}

template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(const Key& item) {
  std::pair<Set<Key>::iterator, bool> result{nullptr, 1};
  if (root == end_NodeS) {
    root = createNodeS(item);
    begin_NodeS = root;
    root->right = end_NodeS;
    end_NodeS->parent = root;
    result.first = Set<Key>::iterator(root);
    m_size++;
  } else {
    result = addNodeS(item);
  }
  return result;
}

template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::addNodeS(
    const Key& item) {
  NodeS<Key>* tmp_NodeS = root;
  NodeS<Key>* next = createNodeS(item);
  std::pair<Set<Key>::iterator, bool> result{nullptr, 1};
  for (int FLAG = 0; !FLAG;) {
    if (next->item == tmp_NodeS->item) {
      FLAG = 1;
      delete next;
      result.first = Set<Key>::iterator(tmp_NodeS);
      result.second = 0;
    } else if (next->item > tmp_NodeS->item) {
      if (tmp_NodeS->right != end_NodeS && tmp_NodeS->right != nullptr)
        tmp_NodeS = tmp_NodeS->right;
      else {
        if (tmp_NodeS->right == end_NodeS) {
          next->right = end_NodeS;
          end_NodeS->parent = next;
        }
        tmp_NodeS->right = next;
        next->parent = tmp_NodeS;
        FLAG = 1;
      }
    } else {
      if (tmp_NodeS->left != nullptr)
        tmp_NodeS = tmp_NodeS->left;
      else {
        next->parent = tmp_NodeS;
        tmp_NodeS->left = next;
        FLAG = 1;
        if (tmp_NodeS == begin_NodeS) begin_NodeS = next;
      }
    }
  }
  if (result.second) {
    result.first = Set<Key>::iterator(next);
    m_size++;
  }
  return result;
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::erase(iterator pos) {
  if (pos.ptr_ == end_NodeS) return pos;
  auto tmp1 = pos;
  ++pos;
  if (tmp1.ptr_->right != nullptr) {
    tmp1.ptr_->right->parent = tmp1.ptr_->parent;
    auto tmp2 = tmp1.ptr_->right;
    while (tmp2->left != nullptr) tmp2 = tmp2->left;
    tmp2->left = tmp1.ptr_->left;
    if (tmp1.ptr_->left != nullptr) tmp1.ptr_->left->parent = tmp2;
    if (tmp1.ptr_ == root) {
      root = root->right;
    } else if (tmp1.ptr_->parent->item > tmp1.ptr_->item)
      tmp1.ptr_->parent->left = tmp1.ptr_->right;
    else
      tmp1.ptr_->parent->right = tmp1.ptr_->right;
  } else if (tmp1.ptr_->left != nullptr) {
    tmp1.ptr_->left->parent = tmp1.ptr_->parent;
    if (tmp1.ptr_->parent->item > tmp1.ptr_->item)
      tmp1.ptr_->parent->left = tmp1.ptr_->left;
    else
      tmp1.ptr_->parent->right = tmp1.ptr_->left;
  } else if (tmp1.ptr_->parent->item > tmp1.ptr_->item) {
    tmp1.ptr_->parent->left = nullptr;
  } else
    tmp1.ptr_->parent->right = nullptr;
  if (tmp1.ptr_ == begin_NodeS) {
    begin_NodeS = pos.ptr_;
  }
  delete tmp1.ptr_;
  m_size--;
  return pos;
}

template <typename Key>
void Set<Key>::swap(Set& other) {
  std::swap(this->m_size, other.m_size);
  std::swap(this->begin_NodeS, other.begin_NodeS);
  std::swap(this->end_NodeS, other.end_NodeS);
  std::swap(this->root, other.root);
}

template <typename Key>
void Set<Key>::merge(Set& other) {
  if (!(other.empty())) {
    for (auto it = other.begin(); it != other.end();) {
      if (contains(*it)) {
        ++it;
      } else {
        insert(*it);
        it = other.erase(it);
      }
    }
  }
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const Key& key) {
  for (Set<Key>::iterator it = begin(); it != end(); ++it) {
    if (*it == key) return it;
  }
  return end();
}

template <typename Key>
bool Set<Key>::contains(const Key& key) {
  bool result = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) result = 1;
  }
  return result;
}

template <typename Key>
template <typename... Args>
Vector<std::pair<typename Set<Key>::iterator, bool>> Set<Key>::insert_many(
    Args&&... args) {
  Vector<std::pair<Set<Key>::iterator, bool>> tmp{};
  for (auto arg : {std::forward<Args>(args)...}) {
    tmp.push_back(insert(arg));
  }
  return tmp;
}

}  // namespace s21

#endif
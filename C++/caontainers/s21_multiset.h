#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

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
struct NodeM {
  struct NodeM* parent = nullptr;
  struct NodeM* left = nullptr;
  struct NodeM* right = nullptr;
  struct NodeM* back = nullptr;
  struct NodeM* front = nullptr;
  bool end_flag = false;
  Key item{};
};

template <class Key>
class Multiset {
  class MultisetConstIterator;
  class MultisetIterator;

 public:
  using value_type = Key;
  using reference = Key&;
  using const_reference = const Key&;
  using iterator = MultisetIterator;
  using const_iterator = MultisetConstIterator;
  using size_type = size_t;

  Multiset();
  explicit Multiset(std::initializer_list<value_type> const& items);
  NodeM<Key>* createNodeM(Key item);
  void cleanMemory(NodeM<Key>* tmp);
  Multiset(const Multiset& s);
  void copyFunction(NodeM<Key>* tmp);
  Multiset(Multiset&& s);
  ~Multiset();
  Multiset<Key>& operator=(Multiset& v);
  Multiset<Key>& operator=(Multiset&& v);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  iterator insert(const Key& item);
  iterator addNodeM(const Key& item);
  iterator erase(iterator pos);
  void swap(Multiset& other);
  void merge(Multiset& other);
  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  template <typename... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  size_t m_size = 0U;
  struct NodeM<Key>* begin_NodeM = nullptr;
  struct NodeM<Key>* end_NodeM = nullptr;
  struct NodeM<Key>* root = nullptr;

  class MultisetConstIterator {
   public:
    struct NodeM<Key>* ptr_;

   public:
    MultisetConstIterator() noexcept : ptr_(nullptr) {}
    explicit MultisetConstIterator(NodeM<Key>* ptr) noexcept : ptr_(ptr) {}
    MultisetConstIterator(const MultisetConstIterator& other) noexcept
        : ptr_(other.ptr_) {}

    const_reference operator*() const noexcept { return ptr_->item; }

    MultisetConstIterator& operator=(
        const MultisetConstIterator& other) noexcept {
      if (this == &other) {
        return *this;
      }
      ptr_ = other.ptr_;
      return *this;
    }

    bool operator==(const MultisetConstIterator& other) const noexcept {
      bool result;
      if (this->ptr_ == other.ptr_) {
        result = true;
      } else {
        result = false;
      }
      return result;
    }

    bool operator!=(const MultisetConstIterator& other) const noexcept {
      return !(*this == other);
    }

    MultisetConstIterator& operator++() noexcept {
      if (ptr_->end_flag) return *this;
      if (ptr_->front != nullptr)
        ptr_ = ptr_->front;
      else {
        while (ptr_->back != nullptr) ptr_ = ptr_->back;
        if (ptr_->right != nullptr) {
          ptr_ = ptr_->right;
          while (ptr_->left != nullptr) ptr_ = ptr_->left;
        } else {
          while (ptr_->parent->item < ptr_->item && !(ptr_->parent->end_flag))
            ptr_ = ptr_->parent;
          ptr_ = ptr_->parent;
        }
      }
      return *this;
    }

    MultisetConstIterator& operator--() noexcept {
      if (ptr_->back != nullptr)
        ptr_ = ptr_->back;
      else if (ptr_->left != nullptr) {
        ptr_ = ptr_->left;
        while (ptr_->right != nullptr) ptr_ = ptr_->right;
        while (ptr_->front != nullptr) ptr_ = ptr_->front;
      } else if (ptr_->end_flag && ptr_->parent != nullptr) {
        ptr_ = ptr_->parent;
        while (ptr_->front != nullptr) ptr_ = ptr_->front;
      } else {
        while (ptr_->parent != nullptr && ptr_->parent->item > ptr_->item)
          ptr_ = ptr_->parent;
        if (ptr_->parent != nullptr) ptr_ = ptr_->parent;
        while (ptr_->front != nullptr) ptr_ = ptr_->front;
      }
      return *this;
    }
  };

  class MultisetIterator : public MultisetConstIterator {
   public:
    MultisetIterator() noexcept : MultisetConstIterator() {}
    explicit MultisetIterator(NodeM<Key>* ptr) noexcept
        : MultisetConstIterator(ptr) {}
    MultisetIterator(const MultisetIterator& other) noexcept
        : MultisetConstIterator(other) {}

    reference operator*() const noexcept {
      return MultisetIterator::ptr_->item;
    }

    MultisetIterator& operator=(const MultisetIterator& other) noexcept {
      if (this == &other) {
        return *this;
      }
      MultisetIterator::ptr_ = other.ptr_;
      return *this;
    }
  };
};

template <typename Key>
void Multiset<Key>::cleanMemory(NodeM<Key>* tmp) {
  if (tmp->left != nullptr) {
    cleanMemory(tmp->left);
  }
  if (tmp->right != nullptr) {
    cleanMemory(tmp->right);
  }
  if (tmp->front != nullptr) {
    cleanMemory(tmp->front);
  }
  if (tmp != end_NodeM) delete tmp;
}

template <typename Key>
Multiset<Key>::Multiset() {
  m_size = 0U;
  Key tmp{};
  end_NodeM = createNodeM(tmp);
  end_NodeM->end_flag = true;
  begin_NodeM = end_NodeM;
  root = end_NodeM;
}

template <typename Key>
NodeM<Key>* Multiset<Key>::createNodeM(value_type item) {
  NodeM<value_type>* tmp = new struct NodeM<Key>;
  tmp->parent = nullptr;
  tmp->left = nullptr;
  tmp->right = nullptr;
  tmp->front = nullptr;
  tmp->back = nullptr;
  tmp->item = item;
  return tmp;
}

template <typename Key>
Multiset<Key>::Multiset(std::initializer_list<Key> const& items) {
  Key tmp{};
  end_NodeM = createNodeM(tmp);
  end_NodeM->end_flag = true;
  begin_NodeM = end_NodeM;
  root = end_NodeM;
  for (auto it = items.begin(); it != items.end(); it++) insert(*it);
}

template <typename Key>
Multiset<Key>::Multiset(const Multiset& s) : Multiset() {
  clear();
  if (s.m_size > 0) {
    copyFunction(s.root);
    m_size = s.m_size;
  }
}

template <typename Key>
void Multiset<Key>::copyFunction(NodeM<Key>* tmp) {
  insert(tmp->item);
  if (tmp->left != nullptr) {
    copyFunction(tmp->left);
  }
  if (tmp->right != nullptr && !(tmp->right->end_flag)) {
    copyFunction(tmp->right);
  }
  if (tmp->front != nullptr) {
    copyFunction(tmp->front);
  }
}

template <typename Key>
Multiset<Key>::Multiset(Multiset&& s) {
  if (end_NodeM != nullptr) clear();
  m_size = s.m_size;
  begin_NodeM = s.begin_NodeM;
  end_NodeM = s.end_NodeM;
  root = s.root;
  s.m_size = 0;
  s.begin_NodeM = nullptr;
  s.end_NodeM = nullptr;
  s.root = nullptr;
}

template <typename Key>
Multiset<Key>::~Multiset() {
  if (end_NodeM != nullptr) {
    cleanMemory(root);
    delete end_NodeM;
  }
}

template <typename Key>
Multiset<Key>& Multiset<Key>::operator=(Multiset& v) {
  if (this == &v) return *this;
  if (end_NodeM != nullptr) clear();
  copyFunction(v.root);
  return *this;
}

template <typename Key>
Multiset<Key>& Multiset<Key>::operator=(Multiset&& v) {
  if (this == &v) return *this;
  if (end_NodeM != nullptr) {
    clear();
    delete end_NodeM;
  }
  m_size = v.m_size;
  begin_NodeM = v.begin_NodeM;
  end_NodeM = v.end_NodeM;
  root = v.root;
  v.m_size = 0;
  v.begin_NodeM = nullptr;
  v.end_NodeM = nullptr;
  v.root = nullptr;
  return *this;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::begin() {
  return Multiset<Key>::iterator(begin_NodeM);
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::end() {
  return Multiset<Key>::iterator(end_NodeM);
}

template <typename Key>
bool Multiset<Key>::empty() {
  return begin() == end();
}

template <typename Key>
size_t Multiset<Key>::size() {
  return m_size;
}

template <typename Key>
size_t Multiset<Key>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(struct NodeM<Key>);
}

template <typename Key>
void Multiset<Key>::clear() {
  cleanMemory(root);
  m_size = 0;
  end_NodeM->parent = nullptr;
  end_NodeM->left = nullptr;
  begin_NodeM = end_NodeM;
  root = end_NodeM;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::insert(const Key& item) {
  Multiset<Key>::iterator result{};
  if (root == end_NodeM) {
    root = createNodeM(item);
    begin_NodeM = root;
    root->right = end_NodeM;
    end_NodeM->parent = root;
    result = Multiset<Key>::iterator(root);
    m_size++;
  } else {
    result = addNodeM(item);
  }
  return result;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::addNodeM(const Key& item) {
  NodeM<Key>* tmp_NodeM = root;
  NodeM<Key>* next = createNodeM(item);
  Multiset<Key>::iterator result{nullptr};
  for (int FLAG = 0; !FLAG;) {
    if (next->item == tmp_NodeM->item) {
      FLAG = 1;
      tmp_NodeM->front = next;
      next->back = tmp_NodeM;
      result = Multiset<Key>::iterator(next);
    } else if (next->item > tmp_NodeM->item) {
      if (tmp_NodeM->right != end_NodeM && tmp_NodeM->right != nullptr)
        tmp_NodeM = tmp_NodeM->right;
      else {
        if (tmp_NodeM->right == end_NodeM) {
          next->right = end_NodeM;
          end_NodeM->parent = next;
        }
        tmp_NodeM->right = next;
        next->parent = tmp_NodeM;
        FLAG = 1;
      }
    } else {
      if (tmp_NodeM->left != nullptr)
        tmp_NodeM = tmp_NodeM->left;
      else {
        next->parent = tmp_NodeM;
        tmp_NodeM->left = next;
        FLAG = 1;
        if (tmp_NodeM == begin_NodeM) begin_NodeM = next;
      }
    }
  }
  result = Multiset<Key>::iterator(next);
  m_size++;
  return result;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::erase(iterator pos) {
  if (pos.ptr_ == end_NodeM) return pos;
  auto tmp = pos;
  ++pos;
  if (tmp.ptr_->back != nullptr) {
    tmp.ptr_->back->front = tmp.ptr_->front;
    if (tmp.ptr_->front != nullptr) tmp.ptr_->front->back = tmp.ptr_->back;
  } else if (tmp.ptr_->front != nullptr) {
    tmp.ptr_->front->parent = tmp.ptr_->parent;
    tmp.ptr_->front->left = tmp.ptr_->left;
    tmp.ptr_->front->right = tmp.ptr_->right;
    tmp.ptr_->front->back = tmp.ptr_->back;
    if (tmp.ptr_->left != nullptr) tmp.ptr_->left->parent = tmp.ptr_->front;
    if (tmp.ptr_->right != nullptr) tmp.ptr_->right->parent = tmp.ptr_->front;
    if (tmp.ptr_ != root) {
      if (tmp.ptr_->parent->item > tmp.ptr_->item)
        tmp.ptr_->parent->left = tmp.ptr_->front;
      else
        tmp.ptr_->parent->right = tmp.ptr_->front;
    }
  } else if (tmp.ptr_->right != nullptr) {
    tmp.ptr_->right->parent = tmp.ptr_->parent;
    auto tmp2 = tmp.ptr_->right;
    while (tmp2->left != nullptr) tmp2 = tmp2->left;
    tmp2->left = tmp.ptr_->left;
    if (tmp.ptr_->left != nullptr) tmp.ptr_->left->parent = tmp2;
    if (tmp.ptr_ == root) {
      root = root->right;
    } else if (tmp.ptr_->parent->item > tmp.ptr_->item)
      tmp.ptr_->parent->left = tmp.ptr_->right;
    else
      tmp.ptr_->parent->right = tmp.ptr_->right;
  } else if (tmp.ptr_->left != nullptr) {
    tmp.ptr_->left->parent = tmp.ptr_->parent;
    if (tmp.ptr_->parent->item > tmp.ptr_->item)
      tmp.ptr_->parent->left = tmp.ptr_->left;
    else
      tmp.ptr_->parent->right = tmp.ptr_->left;
  } else if (tmp.ptr_->parent->item > tmp.ptr_->item) {
    tmp.ptr_->parent->left = nullptr;
  } else
    tmp.ptr_->parent->right = nullptr;
  if (tmp.ptr_ == begin_NodeM) {
    begin_NodeM = pos.ptr_;
  }
  delete tmp.ptr_;
  m_size--;
  return pos;
}

template <typename Key>
void Multiset<Key>::swap(Multiset& other) {
  std::swap(this->m_size, other.m_size);
  std::swap(this->begin_NodeM, other.begin_NodeM);
  std::swap(this->end_NodeM, other.end_NodeM);
  std::swap(this->root, other.root);
}

template <typename Key>
void Multiset<Key>::merge(Multiset& other) {
  if (!(other.empty())) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
    other.clear();
  }
}

template <typename Key>
size_t Multiset<Key>::count(const Key& key) {
  size_t result{};
  auto it = find(key);
  if (it != end()) {
    result++;
    while (it.ptr_->front != nullptr) {
      it.ptr_ = it.ptr_->front;
      result++;
    }
  }
  return result;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::find(const Key& key) {
  for (Multiset<Key>::iterator it = begin(); it != end(); ++it) {
    if (*it == key) return it;
  }
  return end();
}

template <typename Key>
bool Multiset<Key>::contains(const Key& key) {
  bool result = 0;
  for (auto it = begin(); it != end() && result == 0; ++it) {
    if (*it == key) result = 1;
  }
  return result;
}

template <typename Key>
std::pair<typename Multiset<Key>::iterator, typename Multiset<Key>::iterator>
Multiset<Key>::equal_range(const Key& key) {
  std::pair<Multiset<Key>::iterator, Multiset<Key>::iterator> tmp{};
  tmp.first = lower_bound(key);
  tmp.second = upper_bound(key);
  return tmp;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::lower_bound(const Key& key) {
  auto it = begin();
  for (; it != end(); ++it) {
    if (*it == key || *it > key) return it;
  }
  return it;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::upper_bound(const Key& key) {
  auto it = begin();
  for (; it != end(); ++it) {
    if (*it > key) return it;
  }
  return it;
}

template <typename Key>
template <typename... Args>
Vector<std::pair<typename Multiset<Key>::iterator, bool>>
Multiset<Key>::insert_many(Args&&... args) {
  Vector<std::pair<Multiset<Key>::iterator, bool>> tmp_v{};
  for (auto arg : {std::forward<Args>(args)...}) {
    std::pair<Multiset<Key>::iterator, bool> tmp{nullptr, 1};
    tmp.first = insert(arg);
    tmp_v.push_back(tmp);
  }
  return tmp_v;
}

}  // namespace s21

#endif
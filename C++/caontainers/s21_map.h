#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

#include "./s21_vector.h"

namespace s21 {

template <typename Key, typename T>
struct NodeMap {
  struct NodeMap* parent = nullptr;
  struct NodeMap* left = nullptr;
  struct NodeMap* right = nullptr;
  bool end_flag = false;
  std::pair<Key, T> item;
};

template <typename Key, typename T>
class Map {
  class MapConstIterator;
  class MapIterator;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using size_type = size_t;

  Map();
  explicit Map(std::initializer_list<value_type> const& items);
  NodeMap<Key, T>* createNodeMap(value_type value);
  void cleanMemory(NodeMap<Key, T>* tmp);
  Map(const Map& s);
  void copyFunction(NodeMap<Key, T>* tmp);
  Map(Map&& s);
  ~Map();
  Map<Key, T>& operator=(Map& v);
  Map<Key, T>& operator=(Map&& v);
  mapped_type& at(const Key& key);
  mapped_type& operator[](const Key& key);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const value_type& item);
  std::pair<iterator, bool> addNodeMap(const value_type& item);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  iterator erase(iterator pos);
  void swap(Map& other);
  void merge(Map& other);
  bool contains(const Key& key);

  template <typename... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  size_t m_size = 0U;
  NodeMap<Key, T>* begin_NodeMap = nullptr;
  NodeMap<Key, T>* end_NodeMap = nullptr;
  NodeMap<Key, T>* root = nullptr;

  class MapConstIterator {
   public:
    NodeMap<Key, T>* ptr_;

   public:
    MapConstIterator() noexcept : ptr_(nullptr) {}
    explicit MapConstIterator(NodeMap<Key, T>* ptr) noexcept : ptr_(ptr) {}
    MapConstIterator(const MapConstIterator& other) noexcept
        : ptr_(other.ptr_) {}

    const std::pair<Key, T>& operator*() const noexcept { return ptr_->item; }

    MapConstIterator& operator=(const MapConstIterator& other) noexcept {
      if (this == &other) {
        return *this;
      }
      ptr_ = other.ptr_;
      return *this;
    }

    bool operator==(const MapConstIterator& other) const noexcept {
      bool result;
      if (this->ptr_ == other.ptr_) {
        result = true;
      } else {
        result = false;
      }
      return result;
    }

    bool operator!=(const MapConstIterator& other) const noexcept {
      return !(*this == other);
    }

    MapConstIterator& operator++() noexcept {
      if (ptr_->end_flag) return *this;
      if (ptr_->right != nullptr) {
        ptr_ = ptr_->right;
        while (ptr_->left != nullptr) ptr_ = ptr_->left;
      } else {
        while (ptr_->parent->item.first < ptr_->item.first &&
               !(ptr_->parent->end_flag))
          ptr_ = ptr_->parent;
        ptr_ = ptr_->parent;
      }
      return *this;
    }

    MapConstIterator& operator--() noexcept {
      if (ptr_->left != nullptr) {
        ptr_ = ptr_->left;
        while (ptr_->right != nullptr) ptr_ = ptr_->right;
      } else if (ptr_->end_flag && ptr_->parent != nullptr) {
        ptr_ = ptr_->parent;
      } else {
        while (ptr_->parent != nullptr &&
               ptr_->parent->item.first > ptr_->item.first)
          ptr_ = ptr_->parent;
        ptr_ = ptr_->parent;
      }
      return *this;
    }
  };

  class MapIterator : public MapConstIterator {
   public:
    MapIterator() noexcept : MapConstIterator() {}
    explicit MapIterator(NodeMap<Key, T>* ptr) noexcept
        : MapConstIterator(ptr) {}
    MapIterator(const MapIterator& other) noexcept : MapConstIterator(other) {}

    std::pair<Key, T>& operator*() const noexcept {
      return MapIterator::ptr_->item;
    }

    MapIterator& operator=(const MapIterator& other) noexcept {
      if (this == &other) {
        return *this;
      }
      MapIterator::ptr_ = other.ptr_;
      return *this;
    }
  };
};

template <typename Key, typename T>
void Map<Key, T>::cleanMemory(NodeMap<Key, T>* tmp) {
  if (tmp->left != nullptr) {
    cleanMemory(tmp->left);
  }
  if (tmp->right != nullptr) {
    cleanMemory(tmp->right);
  }
  if (tmp != end_NodeMap) delete tmp;
}

template <typename Key, typename T>
Map<Key, T>::Map() {
  m_size = 0U;
  std::pair<const Key, T> tmp{};
  end_NodeMap = createNodeMap(tmp);
  end_NodeMap->end_flag = true;
  begin_NodeMap = end_NodeMap;
  root = end_NodeMap;
}

template <typename Key, typename T>
NodeMap<Key, T>* Map<Key, T>::createNodeMap(value_type value) {
  NodeMap<Key, T>* tmp = new struct NodeMap<Key, T>;
  tmp->parent = nullptr;
  tmp->left = nullptr;
  tmp->right = nullptr;
  tmp->item = value;
  return tmp;
}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const& items) {
  std::pair<const Key, T> tmp{};
  end_NodeMap = createNodeMap(tmp);
  end_NodeMap->end_flag = true;
  begin_NodeMap = end_NodeMap;
  root = end_NodeMap;
  for (auto it = items.begin(); it != items.end(); it++) insert(*it);
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map& s) : Map() {
  clear();
  copyFunction(s.root);
}

template <typename Key, typename T>
void Map<Key, T>::copyFunction(NodeMap<Key, T>* tmp) {
  insert(tmp->item);
  if (tmp->left != nullptr) {
    copyFunction(tmp->left);
  }
  if (tmp->right != nullptr && !(tmp->right->end_flag)) {
    copyFunction(tmp->right);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(Map&& s) {
  if (end_NodeMap != nullptr) clear();
  m_size = s.m_size;
  begin_NodeMap = s.begin_NodeMap;
  end_NodeMap = s.end_NodeMap;
  root = s.root;
  s.m_size = 0;
  s.begin_NodeMap = nullptr;
  s.end_NodeMap = nullptr;
  s.root = nullptr;
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  if (end_NodeMap != nullptr) {
    cleanMemory(root);
    delete end_NodeMap;
  }
}

template <typename Key, typename T>
Map<Key, T>& Map<Key, T>::operator=(Map& v) {
  if (this == &v) return *this;
  if (end_NodeMap != nullptr) clear();
  copyFunction(v.root);
  return *this;
}

template <typename Key, typename T>
Map<Key, T>& Map<Key, T>::operator=(Map&& v) {
  if (this == &v) return *this;
  if (end_NodeMap != nullptr) {
    clear();
    delete end_NodeMap;
  }
  m_size = v.m_size;
  begin_NodeMap = v.begin_NodeMap;
  end_NodeMap = v.end_NodeMap;
  root = v.root;
  v.m_size = 0;
  v.begin_NodeMap = nullptr;
  v.end_NodeMap = nullptr;
  v.root = nullptr;
  return *this;
}

template <typename Key, typename T>
T& Map<Key, T>::at(const Key& key) {
  for (auto it = begin(); it != end(); ++it) {
    if ((*it).first == key) return (*it).second;
  }
  throw std::out_of_range("ERROR");
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
  for (auto it = begin(); it != end(); ++it) {
    if ((*it).first == key) return (*it).second;
  }
  std::pair<Key, T> tmp{};
  tmp.first = key;
  insert(tmp);
  auto it = begin();
  int FLAG = 0;
  for (; it != end() && FLAG == 0; ++it) {
    if ((*it).first == key) FLAG = 1;
  }
  --it;
  return (*it).second;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return Map<Key, T>::iterator(begin_NodeMap);
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return Map<Key, T>::iterator(end_NodeMap);
}

template <typename Key, typename T>
bool Map<Key, T>::empty() {
  return begin() == end();
}

template <typename Key, typename T>
size_t Map<Key, T>::size() {
  return m_size;
}

template <typename Key, typename T>
size_t Map<Key, T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(struct NodeMap<Key, T>);
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
  cleanMemory(root);
  m_size = 0;
  end_NodeMap->parent = nullptr;
  end_NodeMap->left = nullptr;
  begin_NodeMap = end_NodeMap;
  root = end_NodeMap;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type& item) {
  std::pair<Map<Key, T>::iterator, bool> result{nullptr, 1};
  if (root == end_NodeMap) {
    root = createNodeMap(item);
    begin_NodeMap = root;
    root->right = end_NodeMap;
    end_NodeMap->parent = root;
    result.first = Map<Key, T>::iterator(root);
    m_size++;
  } else {
    result = addNodeMap(item);
  }
  return result;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::addNodeMap(
    const value_type& item) {
  NodeMap<Key, T>* tmp_NodeMap = root;
  NodeMap<Key, T>* next = createNodeMap(item);
  std::pair<Map<Key, T>::iterator, bool> result{nullptr, 1};
  for (int FLAG = 0; !FLAG;) {
    if (next->item.first == tmp_NodeMap->item.first) {
      FLAG = 1;
      delete next;
      result.first = Map<Key, T>::iterator(tmp_NodeMap);
      result.second = 0;
    } else if (next->item.first > tmp_NodeMap->item.first) {
      if (tmp_NodeMap->right != end_NodeMap && tmp_NodeMap->right != nullptr)
        tmp_NodeMap = tmp_NodeMap->right;
      else {
        if (tmp_NodeMap->right == end_NodeMap) {
          next->right = end_NodeMap;
          end_NodeMap->parent = next;
        }
        tmp_NodeMap->right = next;
        next->parent = tmp_NodeMap;
        FLAG = 1;
      }
    } else {
      if (tmp_NodeMap->left != nullptr)
        tmp_NodeMap = tmp_NodeMap->left;
      else {
        next->parent = tmp_NodeMap;
        tmp_NodeMap->left = next;
        FLAG = 1;
        if (tmp_NodeMap == begin_NodeMap) begin_NodeMap = next;
      }
    }
  }
  if (result.second) {
    result.first = Map<Key, T>::iterator(next);
    m_size++;
  }
  return result;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key& key, const T& obj) {
  std::pair<const Key, T> tmp{key, obj};
  return insert(tmp);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  std::pair<typename Map<Key, T>::iterator, bool> tmp = insert(key, obj);
  if (!(tmp.second) && (*(tmp.first)).second != obj) {
    this->at(key) = obj;
    tmp.second = true;
  }
  return tmp;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::erase(iterator pos) {
  if (pos.ptr_ == end_NodeMap) return pos;
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
    if (tmp1.ptr_->parent->item.first > tmp1.ptr_->item.first)
      tmp1.ptr_->parent->left = tmp1.ptr_->left;
    else
      tmp1.ptr_->parent->right = tmp1.ptr_->left;
  } else if (tmp1.ptr_->parent->item.first > tmp1.ptr_->item.first) {
    tmp1.ptr_->parent->left = nullptr;
  } else
    tmp1.ptr_->parent->right = nullptr;
  if (tmp1.ptr_ == begin_NodeMap) {
    begin_NodeMap = pos.ptr_;
  }
  delete tmp1.ptr_;
  m_size--;
  return pos;
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map& other) {
  std::swap(m_size, other.m_size);
  std::swap(begin_NodeMap, other.begin_NodeMap);
  std::swap(end_NodeMap, other.end_NodeMap);
  std::swap(root, other.root);
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map& other) {
  if (!(other.empty())) {
    for (auto it = other.begin(); it != other.end();) {
      if (contains((*it).first)) {
        ++it;
      } else {
        insert(*it);
        it = other.erase(it);
      }
    }
  }
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key& key) {
  bool result = 0;
  for (auto it = begin(); it != end(); ++it) {
    if ((*it).first == key) result = 1;
  }
  return result;
}

template <typename Key, typename T>
template <typename... Args>
Vector<std::pair<typename Map<Key, T>::iterator, bool>>
Map<Key, T>::insert_many(Args&&... args) {
  Vector<std::pair<Map<Key, T>::iterator, bool>> tmp{};
  for (auto arg : {std::forward<Args>(args)...}) {
    tmp.push_back(insert(arg));
  }
  return tmp;
}

}  // namespace s21

#endif
#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    if(find(key, root_) == nullptr) {
      return std::nullopt;
    }
    return find(key, root_) -> value;
  }

  bool BinarySearchTree::Contains(int key) const {
    if(find(key, root_) == nullptr){
      return false;
    }
    return true;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if(root_ == nullptr){
      return std::nullopt;
    }
    return find_min(root_) -> key;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if(root_ == nullptr) {
      return std::nullopt;
    }
    return find_max(root_) -> key;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if(node == nullptr){
      node = new Node(key,value);
      node -> key = key;
      node -> value = value;
    }
    if(node -> key == key){
      node -> value = value;
    }
    if(node -> key > key){
      insert(key, value, node -> left);
    }
    if(node -> key < key){
      insert(key, value, node -> right);
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if(Contains(key)){
      if(key == node -> key){
        if(node -> left != nullptr && node -> right != nullptr){
          node -> key = (find_min(node -> right)) -> key;
          node -> value = (find_min(node -> right)) -> value;
          return remove(node -> key, node -> right);
        }else if(node -> right != nullptr){
          node = node -> right;
          return true;
        }
        else{
          node = node -> left;
          return true;
        }
      }
      if(key < node -> key){
        return remove(key, node -> left);
      }
      if(key > node -> key){
        return remove(key, node -> right);
      }
    }
    return false;
  }

  void BinarySearchTree::clear(Node* node) {
    if(node != nullptr){
      clear(node -> left);
      clear(node -> right);
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if(node == nullptr){
      return nullptr;
    }
    if(key > node -> key){
      return find(key, node -> right);
    }
    if(key < node -> key){
      return find(key, node -> left);
    }
    return node;
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    Node* minNode = node;
    int minKey = minNode -> key;
    while(node != nullptr){
      if(minKey > node -> key){
        minNode = node;
        minKey = minNode -> key;
      }else{
        node = node -> left;
      }
    }
    return minNode;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    Node* maxNode = node;
    int maxKey = maxNode -> key;
    while(node != nullptr){
      if(maxKey < node -> key){
        maxNode = node;
        maxKey = maxNode -> key;
      }else{
        node = node -> right;
      }
    }
    return maxNode;
  }

}  // namespace assignment
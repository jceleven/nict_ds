//
// Created by kaxns on 7/10/22.
//

#pragma once

#include <exception>
#include <cassert>

template <typename T>
class DbListNode
{
public:
  DbListNode() = default;
  explicit DbListNode(T d) : data_(d)
  {
  }
  T data_;
  DbListNode<T>* left_;
  DbListNode<T>* right_;
};

template <typename T>
class DbList
{
public:
  typedef DbListNode<T> Node;
  DbList();
  ~DbList();
  void erase(Node* x);
  void insert(Node* p, Node* x);
  Node* first_;  // points to head node
};

template <typename T>
void DbList<T>::erase(DbList::Node* x)
{
  if (x == first_)
    throw std::exception{};
  else
  {
    x->left_->right_ = x->right_;
    if (x->right_ != nullptr)
      x->right_->left_ = x->left_;
    delete x;
  }
}

/**
 * @brief insert node p to the right of node x
 */
template <typename T>
void DbList<T>::insert(DbList::Node* p, DbList::Node* x)
{
  assert(x != nullptr);
  p->left_ = x;
  p->right_ = x->right_;
  if (x->right_ != nullptr)
    // the following 2 lines can not be exchanged
    x->right_->left_ = p;
  x->right_ = p;
}

template <typename T>
DbList<T>::DbList()
{
  first_ = new Node;
  first_->left_ = nullptr;
  first_->right_ = nullptr;
}

template <typename T>
DbList<T>::~DbList()
{
  Node* x = first_;
  Node* y;
  while (x->right_ != nullptr)
  {
    y = x;
    x = x->right_;
    delete y;
  }
}

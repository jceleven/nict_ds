//
// Created by kaxns on 7/6/22.
//

#include <iostream>
#include "double_list.h"

int main()
{
  DbList<int> my_list{};
  auto p1 = new DbList<int>::Node(8);
  auto p2 = new DbList<int>::Node(10);
  auto p3 = new DbList<int>::Node(9);
  my_list.insert(p1, my_list.first_);
  my_list.insert(p2, p1);
  my_list.insert(p3, p1);
  // check
  auto x = my_list.first_->right_;
  while (x != nullptr)
  {
    std::cout << x->data_ << "\t";
    x = x->right_;
  }
  std::cout << "\n";

  my_list.erase(p1);
  my_list.erase(p2);
  x = my_list.first_->right_;
  while (x != nullptr)
  {
    std::cout << x->data_ << "\t";
    x = x->right_;
  }
}
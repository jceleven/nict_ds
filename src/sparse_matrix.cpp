//
// Created by kaxns on 7/5/22.
//

#include <iostream>

struct Triple
{
  int row_;
  int col_;
  int value_;
};

class MatrixNode
{
public:
  MatrixNode* down_{};
  MatrixNode* right_;
  __attribute__((unused)) bool head_;
  union
  {
    MatrixNode* next_;
    Triple triple_{};
  };
  MatrixNode(bool is_head, Triple* triple);
//  std::istream& operator>>(Matrix&);
};

MatrixNode::MatrixNode(bool is_head, Triple* triple)
{
  head_ = is_head;
  if (is_head)
    right_ = next_ = this;
  else
    triple_ = *triple;
}

class Matrix
{
public:
  std::istream& operator>>(std::istream&);
  std::ostream& operator<<(std::ostream&) const;
  ~Matrix();
  MatrixNode* header_;
};

/**
 * @note Computing time:
 * @note all head nodes: O(max(m, n)) ~ O(m + n)
 * @note all typical nodes: O(r)
 * @note Total: O(m + n + r)
 */
std::istream& Matrix::operator>>(std::istream& istream)
{
  Triple s{};
  std::cout << "input dimensions:\n";
  istream >> s.row_ >> s.col_ >> s.value_;
  int p = std::max(s.row_, s.col_);
  // set up the header
  this->header_ = new MatrixNode(false, &s);
  if (p == 0)
    this->header_->right_ = this->header_;
  else  // at least one row or column
  {
    MatrixNode* head[p];
    for (int i = 0; i < p; ++i)
      head[i] = new MatrixNode(true, nullptr);

    int current_row = 0;
    MatrixNode* last = head[0];  // track the last node in current row
    for (int i = 0; i < s.value_; ++i)
    {
      std::cout << "input data:\n";
      Triple t{};
      istream >> t.row_ >> t.col_ >> t.value_;
      if (t.row_ > current_row)
      {
        last->right_ = head[current_row];  // close current row
        current_row = t.row_;
        last = head[current_row];
      }
      last = last->right_ = new MatrixNode(false, &t);   // into row
      // next_ is temporally used to track the last node in current column
      head[t.col_]->next_ = head[t.col_]->next_->down_ = last;  // into column
    }

    last->right_ = head[current_row];  // no more input, close the last row

    // close all column lists
    for (int i = 0; i < s.col_; ++i)
      // remember that next_ is temporally used to track the last node in current column
      head[i]->next_->down_ = head[i];

    // link the head nodes together
    for (int i = 0; i < p - 1; ++i)
      head[i]->next_ = head[i + 1];
    head[p - 1]->next_ = this->header_;
    this->header_->right_ = head[0];
  }
  return istream;
}

/**
 * @brief Erase a matrix by rows.
 */
Matrix::~Matrix()
{
  if (header_ == nullptr)
    return;
  if (this->header_->right_ == this->header_)
  {
    delete this->header_;
    return;
  }

  MatrixNode* begin = this->header_->right_;
  MatrixNode* temp;
  MatrixNode* y;
  while (begin != header_)
  {
    temp = begin;
    y = begin;
    begin = begin->next_;
    while (y->right_ != temp)
    {
      auto x = y;
      y = y->right_;
      delete x;
    }
  }
  delete this->header_;
}

std::ostream& Matrix::operator<<(std::ostream& ostream) const
{
  auto begin = this->header_->right_;
  MatrixNode* temp;
  MatrixNode* y;
  while (begin != this->header_)
  {
    temp = begin;
    y = begin->right_;
    begin = begin->next_;
    while (y != temp)
    {
      ostream << "(" << y->triple_.row_ << ", " << y->triple_.col_ << ", " << y->triple_.value_ << ")\n";
      y = y->right_;
    }
  }
  return ostream;
}

int main()
{
  Matrix mat{};
  mat.operator>>(std::cin);
  mat.operator<<(std::cout);
  return 0;
}

#include <cassert>
#include "Matrix.hpp"

using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {

  assert(width > 0 && width <= MAX_MATRIX_WIDTH);
  assert(height > 0 && height <= MAX_MATRIX_HEIGHT);
  (*mat).width = width;
  (*mat).height = height; 

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {

  os << Matrix_width(mat) << " " << Matrix_height(mat) << endl;
  
  int index = 0;
  for (int row = 0; row < Matrix_height(mat); row++) {
    for (int col = 0; col < Matrix_width(mat); col++) {
      os << (*mat).data[index] << " "; //90% sure this is wrong, i can't figure out how to print elements of a matrix TT
      index++;
    }
    os << endl;
  } 

}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  
  return (*mat).width;

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  
  return (*mat).height;

}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {

  int index = ptr - (*mat).data;
  return index/Matrix_width(mat);

}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  
  int index = ptr - (*mat).data;
  return index - (Matrix_row(mat, ptr)) * Matrix_width(mat);

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {

  assert(row >= 0 && row < Matrix_height(mat));
  assert(column >= 0 && column < Matrix_width(mat));

  int mat_index = 0;
  mat_index = row * Matrix_width(mat) + column;
  return (*mat).data + mat_index;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column >= 0 && column < Matrix_width(mat));

  int mat_index = 0;
  mat_index = row * Matrix_width(mat) + column;
  const int* index_element = (*mat).data + mat_index;
  return index_element;

  //really iffy about this one 
  
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {

  int index = 0;
  for (int row = 0; row < Matrix_height(mat); row++) {
    for (int col = 0; col < Matrix_width(mat); col++) {
      (*mat).data[index] = value;
      index++;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {

  int index = 0;
  for (int row = 0; row < Matrix_height(mat); row++) {
    for (int col = 0; col < Matrix_width(mat); col++) {
      while ((row == 0 || row == Matrix_height(mat) - 1) && (col == 0 || col == Matrix_width(mat) - 1)) {
        (*mat).data[index] = value;
        index++;
      }
    }
  }
  
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {

  int max = 0; 
  int index = 0;
  for (int row = 0; row < Matrix_height(mat); row++) {
    for (int col = 0; col < Matrix_width(mat); col++) {
      if ((*mat).data[index] > max){
        max = (*mat).data[index];
      }
    }
  }

  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column_start >= 0 && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int start_index = row * Matrix_width(mat) + column_start;
  int min_element = (*mat).data[start_index];
  int min_col = 0;
  int min_index = 0;

  for (int col = column_start; col < column_end; col++) {
    int index = row * Matrix_width(mat) + col;
    if ((*mat).data[index] < min_element) {
      min_element = (*mat).data[index];
      min_index = index;
    }
  }

  min_col = min_index - (row * Matrix_width(mat));
  return min_col;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column_start >= 0 && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int start_index = row * Matrix_width(mat) + column_start;
  int min_element = (*mat).data[start_index];

  for (int col = column_start; col < column_end; col++) {
    int index = row * Matrix_width(mat) + col;
    if ((*mat).data[index] < min_element) {
      min_element = (*mat).data[index];
    }
  }

  return min_element;
}

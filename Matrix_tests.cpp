#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST(test_init_matrix) {
  Matrix mat;
  Matrix_init(&mat, 3, 3); // Initialize the matrix with width 3 and height 3

  // Check if width and height are correctly set
  ASSERT_EQUAL(Matrix_width(&mat), 3);
  ASSERT_EQUAL(Matrix_height(&mat), 3);
}
TEST(test_fill_matrix) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);

  Matrix_fill(&mat, 42);

  // Verify all elements are filled with the specified value
  for (int row = 0; row < Matrix_height(&mat); ++row) {
    for (int col = 0; col < Matrix_width(&mat); ++col) {
      ASSERT_EQUAL(*Matrix_at(&mat, row, col), 42);
    }
  }
}

TEST(test_fill_border) {
  Matrix mat;
  Matrix_init(&mat, 4, 4);

  Matrix_fill_border(&mat, 99);

  // Verify border elements are filled with the specified value
  for (int row = 0; row < Matrix_height(&mat); ++row) {
    for (int col = 0; col < Matrix_width(&mat); ++col) {
      if (row == 0 || row == 3 || col == 0 || col == 3) {
        ASSERT_EQUAL(*Matrix_at(&mat, row, col), 99);
      } else {
        // Verify non-border elements are not changed
        ASSERT_EQUAL(*Matrix_at(&mat, row, col), 0);
      }
    }
  }
}
TEST(test_matrix_max) {
  Matrix *mat = new Matrix; // Create a dynamic Matrix
  Matrix_init(mat, 3, 3);
  
  // Your test code here

  delete mat; // Destroy the dynamic Matrix to release memory
}

TEST(test_matrix_column_of_min_value_in_row) {
  Matrix *mat = new Matrix; // Create a dynamic Matrix
  Matrix_init(mat, 3, 3);

  // Your test code here

  delete mat; // Destroy the dynamic Matrix to release memory
}


TEST(test_matrix_min_value_in_row) {
  Matrix *mat = new Matrix; // Create a dynamic Matrix
  Matrix_init(mat, 3, 3);

  // Your test code here

  delete mat; // Destroy the dynamic Matrix to release memory
}
TEST(test_print_matrix) {
  Matrix mat;
  Matrix_init(&mat, 3, 3); // Initialize a 3x3 matrix

  // Fill the matrix with some sample data
  for (int row = 0; row < Matrix_height(&mat); row++) {
    for (int col = 0; col < Matrix_width(&mat); col++) {
      *Matrix_at(&mat, row, col) = row * Matrix_width(&mat) + col;
    }
  }

  // Redirect output to a string stream
  stringstream output;
  Matrix_print(&mat, output);

  // Define the expected output
  const string expectedOutput =
    "3 3\n"
    "0 1 2 \n"
    "3 4 5 \n"
    "6 7 8 \n";

  // Compare the generated output with the expected output
  ASSERT_EQUAL(output.str(), expectedOutput);
}
TEST(test_matrix_width) {
  Matrix mat;
  Matrix_init(&mat, 4, 3); // Create a 4x3 matrix

  // Check if the width matches the expected value
  ASSERT_EQUAL(Matrix_width(&mat), 4);
}
TEST(test_matrix_height) {
  Matrix mat;
  Matrix_init(&mat, 4, 3); // Create a 4x3 matrix

  // Check if the height matches the expected value
  ASSERT_EQUAL(Matrix_height(&mat), 3);
}
TEST(test_matrix_row) {
  Matrix mat;
  Matrix_init(&mat, 4, 3); // Create a 4x3 matrix

  // Get a pointer to an element in the matrix (e.g., the element at row 2, column 1)
  int* element_ptr = Matrix_at(&mat, 2, 1);

  // Check if the row calculated by Matrix_row matches the expected value (in this case, 2)
  ASSERT_EQUAL(Matrix_row(&mat, element_ptr), 2);
}
TEST(test_matrix_column) {
  Matrix mat;
  Matrix_init(&mat, 4, 3); // Create a 4x3 matrix

  // Get a pointer to an element in the matrix (e.g., the element at row 2, column 1)
  int* element_ptr = Matrix_at(&mat, 2, 1);

  // Check if the column calculated by Matrix_column matches the expected value (in this case, 1)
  ASSERT_EQUAL(Matrix_column(&mat, element_ptr), 1);
}
TEST(test_matrix_at) {
  Matrix mat;
  Matrix_init(&mat, 4, 3); // Create a 4x3 matrix

  // Get a pointer to an element in the matrix (e.g., the element at row 2, column 1)
  int* element_ptr = Matrix_at(&mat, 2, 1);

  // Check if the value of the element matches the expected value
  *element_ptr = 42; // Set the element value to 42
  ASSERT_EQUAL(*element_ptr, 42);
}
TEST(test_const_matrix_at) {
  Matrix mat;
  Matrix_init(&mat, 3, 4); // Create a 3x4 matrix

  // Get a pointer to a constant element in the matrix (e.g., the element at row 1, column 2)
  const int* element_ptr = Matrix_at(&mat, 1, 2);

  // Check if the value of the element matches the expected value
  ASSERT_EQUAL(*element_ptr, 0); // Assuming the element is initialized to 0
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

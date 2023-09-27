#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.
// Test case for Image_init

TEST(test_image_init) {
    Image img;
    Image_init(&img, 4, 3); // Initialize with width 4 and height 3

    // Check that width and height are correctly set
    ASSERT_EQUAL(Image_width(&img), 4);
    ASSERT_EQUAL(Image_height(&img), 3);
}



TEST(test_image_width) {
  Image img; // Create an Image object

  // Initialize the Image with a known width
  const int expectedWidth = 4;
  img.width = expectedWidth;

  // Call the Image_width function and store the result
  const int actualWidth = Image_width(&img);

  // Check if the actual width matches the expected width
  ASSERT_EQUAL(actualWidth, expectedWidth);
}
TEST(test_image_height) {
  Image img; // Create an Image object

  // Initialize the Image with a known height
  const int expectedHeight = 5;
  img.height = expectedHeight;

  // Call the Image_height function and store the result
  const int actualHeight = Image_height(&img);

  // Check if the actual height matches the expected height
  ASSERT_EQUAL(actualHeight, expectedHeight);
}
TEST(test_image_get_pixel) {
  Image img; // Create an Image object

  // Initialize the Image with known dimensions
  const int width = 3;
  const int height = 3;
  Image_init(&img, width, height);

  // Set specific pixels in the color channels
  const Pixel expectedPixel = {100, 150, 200};
  const int row = 1;
  const int column = 1;
  *Matrix_at(&img.red_channel, row, column) = expectedPixel.r;
  *Matrix_at(&img.green_channel, row, column) = expectedPixel.g;
  *Matrix_at(&img.blue_channel, row, column) = expectedPixel.b;

  // Call the Image_get_pixel function to retrieve the pixel
  Pixel actualPixel = Image_get_pixel(&img, row, column);

  // Check if the actual pixel matches the expected pixel
  ASSERT_EQUAL(actualPixel.r, expectedPixel.r);
  ASSERT_EQUAL(actualPixel.g, expectedPixel.g);
  ASSERT_EQUAL(actualPixel.b, expectedPixel.b);
}
TEST(test_image_fill) {
  Image img; // Create an Image object

  // Initialize the Image with known dimensions
  const int width = 4;
  const int height = 4;
  Image_init(&img, width, height);

  // Define the fill color
  const Pixel fillColor = {100, 150, 200};

  // Call the Image_fill function to fill the Image with the specified color
  Image_fill(&img, fillColor);

  // Check if all pixels in the Image have the same color as the fill color
  for (int i = 0; i < Image_height(&img); i++) {
    for (int j = 0; j < Image_width(&img); j++) {
      Pixel actualPixel = Image_get_pixel(&img, i, j);
      ASSERT_EQUAL(actualPixel.r, fillColor.r);
      ASSERT_EQUAL(actualPixel.g, fillColor.g);
      ASSERT_EQUAL(actualPixel.b, fillColor.b);
    }
  }
}
TEST(test_image_set_pixel) {
  Image img; // Create an Image object

  // Initialize the Image with known dimensions
  const int width = 3;
  const int height = 3;
  Image_init(&img, width, height);

  // Define the row, column, and color for the pixel
  const int row = 1;
  const int column = 1;
  const Pixel expectedPixel = {100, 150, 200};

  // Call the Image_set_pixel function to set the pixel
  Image_set_pixel(&img, row, column, expectedPixel);

  // Retrieve the actual pixel from the Image
  Pixel actualPixel = Image_get_pixel(&img, row, column);

  // Check if the actual pixel matches the expected pixel
  ASSERT_EQUAL(actualPixel.r, expectedPixel.r);
  ASSERT_EQUAL(actualPixel.g, expectedPixel.g);
  ASSERT_EQUAL(actualPixel.b, expectedPixel.b);
}



// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
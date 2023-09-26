#include <iostream>
#include "Matrix.hpp"
#include "Image.hpp"
#include "processing.hpp"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 4) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
  }
  string filename = argv[1];
  string resized_file = argv[2];
  int new_width = atoi(argv[3]);
  int new_height = atoi(argv[4]);

  std::ifstream file(filename);
  if (!(file.is_open())) {
    cout << "Error opening file: " << filename << endl;
  }

  Image* img = new Image;
  Image_init(img, file);
  file.close();

  if (argc == 5) {
    new_height = atoi(argv[4]);
  }
  else {
    new_height = Image_height(img);
  }

  if (new_width <= 0 || new_width > Image_width(img) || new_height <= 0 || new_height > Image_height(img)) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
  }
    
    seam_carve(img, new_width, new_height);
    ofstream print_file;
    print_file.open(resized_file);
    Image_print(img, print_file);
    delete img;
    print_file.close();
    
    return 0;

}
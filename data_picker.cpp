#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <algorithm>

using namespace std;

struct Image {
	int num_rows;
	int num_cols;
	vector<vector<int> > image_matrix;
};

std::istream& operator>>(std::istream &in, Image &image) {
	for (int i = 0; i < image.num_rows; i++) {
		for (int j = 0; j < image.num_cols; j++) {
			in >> image.image_matrix[i][j];
		}
	}
	return in;
}

void execute_images(const int num_images_, vector<Image> &image_vector_,
	std::istream &in) {
	for (int i = 0; i < int(num_images_); i++) {
		in >> image_vector_[i];
	}
	return;
}

void reverse_endianness(std::uint32_t *ptr) {
	char* arr = reinterpret_cast<char*>(ptr);
	std::reverse(arr, arr + (sizeof(*ptr)));
}

int main(int argc, char** argv) {
	ifstream fileInput;
	fileInput.open(argv[1]);

	vector<Image> image_vector;
	std::uint32_t magic_number, num_images, num_rows, num_cols;

	fileInput.read(reinterpret_cast<char*>(&magic_number), sizeof magic_number);
	fileInput.read(reinterpret_cast<char*>(&num_images), sizeof num_images);
	fileInput.read(reinterpret_cast<char*>(&num_rows), sizeof num_rows);
	fileInput.read(reinterpret_cast<char*>(&num_cols), sizeof num_cols);

	reverse_endianness(&magic_number);
	reverse_endianness(&num_images);
	reverse_endianness(&num_rows);
	reverse_endianness(&num_cols);

	cout << "Magic Number:\t\t\t" << magic_number << "\n";
	cout << "Number of Images:\t\t" << num_images << "\n";
	cout << "Rows:\t\t\t\t" << num_rows  << "\n";
	cout << "Columns:\t\t\t" << num_cols << "\n";

	// if (string(argv[2]) == "images") {
	// 	fileInput >> magic_number >> num_images >> num_rows >> num_cols;
	// 	execute_images(num_images, image_vector, fileInput);
	// }
	// else if (string(argv[2]) == "labels") {
	// 	fileInput >> magic_number >> num_items;
	// 	// execute_labels(num_items);
	// }
	// else {
	// 	cout << "ERROR: Usage: ./executable filename [images/label]\n";
	// 	return 1;
	// }

	return 0;
}

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
std::ostream& operator<<(std::ostream &os, Image &image) {
	for (int i = 0; i < image.num_rows; i++) {
		for (int j = 0; j < image.num_cols; j++) {
			os << image.image_matrix[i][j] << " ";
		}
		os << "\n";
	}
	return os;
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
void read_and_reverse(std::istream &in, std::uint32_t *ptr) {
	in.read(reinterpret_cast<char*>(ptr), sizeof *ptr);
	reverse_endianness(ptr);
	return;
}

int main(int argc, char** argv) {

	ifstream fileInput(argv[1]);

	vector<Image> image_vector;
	std::uint32_t magic_number, num_images, num_rows, num_cols, num_items;

	if (string(argv[2]) == "images") {
		read_and_reverse(fileInput, &magic_number);
		read_and_reverse(fileInput, &num_images);
		read_and_reverse(fileInput, &num_rows);
		read_and_reverse(fileInput, &num_cols);
		execute_images(num_images, image_vector, fileInput);

		cout << "Magic Number:\t\t\t" << magic_number << "\n";
		cout << "Number of Images:\t\t" << num_images << "\n";
		cout << "Rows:\t\t\t\t" << num_rows  << "\n";
		cout << "Columns:\t\t\t" << num_cols << "\n";

		for (int i = 0; i < int(num_rows); i++) {
			for (int j = 0; j < int(num_cols); j++) {
				cout << image_vector[i] << " ";
			}
			cout << "\n";
		}
	}
	else if (string(argv[2]) == "labels") {
		read_and_reverse(fileInput, &magic_number);
		read_and_reverse(fileInput, &num_items);
		// execute_labels(num_items);

		cout << "Magic Number:\t\t\t" << magic_number << "\n";
		cout << "Numbers of Items:\t\t" << num_items << "\n";
	}
	else {
		cout << "ERROR: Usage: ./executable filename [images/label]\n";
		return 1;
	}

	return 0;
}

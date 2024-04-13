#include "Image_Class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

string InputFilePath() {
    string filename;
    while (true) {
        cout << "Enter the file path you want to include: ";
        getline(cin, filename);

        if (fileExists(filename)) {
            break;
        } else {
            cout << "Error: File does not exist. Please try again." << endl;
        }
    }
    return filename;
}

string OutputFilePath() {
    string filename;

    cout << "Enter the filename to save the filtered image (include extension): ";
    getline(cin, filename);

    // Check if the filename is empty
    if (filename.empty()) {
        cout << "File cannot be empty." << endl;
        return "";
    }

    // Extract the extension
    size_t dotPosition = filename.find_last_of(".");
    if (dotPosition == string::npos) {
        cout << "Please include the file extension (e.g., '.png', '.jpg')" << endl;
        return "";
    }

    string extension = filename.substr(dotPosition);
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // Check if the extension is supported
    if (extension != ".jpg" && extension != ".jpeg" && extension != ".bmp" && extension != ".png") {
        cout << "Unsupported file extension. Supported extensions are '.jpg', '.jpeg', '.bmp', '.png'" << endl;
        return "";
    }
    if (extension != filename.substr(dotPosition)) {
        filename.replace(dotPosition, extension.length(), extension);
    }

    return filename;
}

void ApplyTVFilter(Image& pic) {
    srand(time(nullptr));

    for (int i = 0; i < pic.height; ++i) {
        if (i % 2 == 0) {
            int subtract_value = rand() % 11;
            for (int j = 0; j < pic.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned int pixel_value = pic(j, i, k);
                    if (pixel_value >= subtract_value) {
                        pic(j, i, k) -= subtract_value;
                    } else {
                        pic(j, i, k) = 0;
                    }
                }
            }
        } else {
            int add_value = rand() % 11;
            for (int j = 0; j < pic.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned int pixel_value = pic(j, i, k);
                    if (pixel_value + add_value <= 255) {
                        pic(j, i, k) += add_value;
                    } else {
                        pic(j, i, k) = 255;
                    }
                }
            }
        }
    }

    for (int i = 0; i < pic.height; ++i) {
        for (int j = 0; j < pic.width; ++j) {
            if (rand() % 10 == 0) {
                int r = rand() % 256;
                int g = rand() % 256;
                int b = rand() % 256;
                pic(j, i, 0) = (pic(j, i, 0) + r) / 2;
                pic(j, i, 1) = (pic(j, i, 1) + g) / 2;
                pic(j, i, 2) = (pic(j, i, 2) + b) / 2;
            }
        }
    }
}

int main() {
    string inputFilename = InputFilePath();

    Image pic(inputFilename);
    if (!pic.loadNewImage(inputFilename)) {
        cout << "Unable to load the image" << endl;
        return 1;
    }

    ApplyTVFilter(pic);

    string outputFilename = OutputFilePath();

    // Save the image
    if (pic.saveImage(outputFilename)) {
        cout << "Image saved as " << outputFilename << endl;
    } else {
        cout << "Failed to save the image. Please try again." << endl;
        return 1;
    }

    return 0;
}

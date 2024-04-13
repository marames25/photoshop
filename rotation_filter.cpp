#include "Image_Class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <vector>

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

    cout << "Enter the filename to save the filtered image (include extension):\n ";

    while (true) {
        getline(cin, filename);

        // Check if the filename is empty
        if (filename.empty()) {
            cout << "File cannot be empty." << endl;
            continue;
        }

        // Extract the extension
        size_t dotPosition = filename.find_last_of(".");
        if (dotPosition == string::npos) {
            cout << "Please include the file extension (e.g., '.png', '.jpg')" << endl;
            continue;
        }

        string extension = filename.substr(dotPosition);
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        // Check if the extension is supported
        if (extension == ".jpg" || extension == ".jpeg" || extension == ".bmp" || extension == ".png") {
            // Check if the extension is already lowercase
            if (extension != filename.substr(dotPosition)) {
                filename.replace(dotPosition, extension.length(), extension);
            }
            break;
        } else {
            cout << "Unsupported file extension. Supported extensions are '.jpg', '.jpeg', '.bmp', '.png'" << endl;
        }
    }

    return filename;
}

void rotateImage(const string& filename, int choice) {
    Image pic(filename);
    unsigned int width = pic.width;
    unsigned int height = pic.height;
    string outputFilename;

    switch (choice) {
        case 1: {
            // Rotate 180 degrees clockwise
            Image rotated(pic.width, pic.height);
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        rotated(width - j - 1, height - i - 1, k) = pic(j, i, k);
                    }
                }
            }
            outputFilename = OutputFilePath();
            rotated.saveImage(outputFilename);
            break;
        }
        case 2: {
            // Rotate 90 degrees clockwise
            Image rotated(pic.height, pic.width);
            for (int i = 0; i < pic.height; ++i) {
                for (int j = 0; j < pic.width; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        rotated(pic.height - i - 1, j, k) = pic(j, i, k);
                    }
                }
            }
            outputFilename = OutputFilePath();
            rotated.saveImage(outputFilename);
            break;
        }
        case 3: {
            // Rotate 270 degrees clockwise
            Image rotated(pic.height, pic.width);
            for (int i = 0; i < pic.width; ++i) {
                for (int j = 0; j < pic.height; ++j) {
                    rotated(j, pic.width - i - 1, 0) = pic(i, j, 0);
                    rotated(j, pic.width - i - 1, 1) = pic(i, j, 1);
                    rotated(j, pic.width - i - 1, 2) = pic(i, j, 2);
                }
            }
            outputFilename = OutputFilePath();
            rotated.saveImage(outputFilename);
            break;
        }
        default:
            cout << "Invalid choice\n";
            return; // Exit function
    }

    // Open the rotated image using system default image viewer
    system(outputFilename.c_str());

    if (fileExists(outputFilename)) {
        cout << "Image rotated and saved as " << outputFilename << endl;
    } else {
        cout << "Failed to save the image. Please try again." << endl;
    }
}

int main() {
    string filename = InputFilePath();

    int choice;
    cout << "Choose rotation:\n";
    cout << "1. 180 degrees\n";
    cout << "2. 90 degrees\n";
    cout << "3. 270 degrees\n";
    cout << "Enter your choice: ";
    cin >> choice;

    rotateImage(filename, choice);

    return 0;
}

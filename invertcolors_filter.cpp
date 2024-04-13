#include "Image_Class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>

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
void ApplyFilter(Image& pic) {
    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < pic.height; ++j) {
            unsigned int red = pic(i, j, 0);
            unsigned int green = pic(i, j, 1);
            unsigned int blue = pic(i, j, 2);

            pic(i, j, 0) = 255 - red;
            pic(i, j, 1) = 255 - green;
            pic(i, j, 2) = 255 - blue;
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

    ApplyFilter(pic);

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

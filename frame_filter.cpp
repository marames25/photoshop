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

    cout << "Enter the filename to save the image with frame (include extension): ";

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

void UserFrameColor(unsigned int& red, unsigned int& green, unsigned int& blue) {
    while (true) {
        cout << "Enter the RGB values for the frame color (0-255):\n";
        cout << "Red: ";
        cin >> red;
        if (red < 0 || red > 255) {
            cout << "Invalid input. Red value must be between 0 and 255. Please try again." << endl;
            continue;
        }

        cout << "Green: ";
        cin >> green;
        if (green < 0 || green > 255) {
            cout << "Invalid input. Green value must be between 0 and 255. Please try again." << endl;
            continue;
        }

        cout << "Blue: ";
        cin >> blue;
        if (blue < 0 || blue > 255) {
            cout << "Invalid input. Blue value must be between 0 and 255. Please try again." << endl;
            continue;
        }
        // If all inputs are within the valid range, break the loop
        break;
    }
}


void PlainFrame(Image& pic, unsigned int red, unsigned int green, unsigned int blue, int frameWidth) {
    // Add top and bottom frame
    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < frameWidth; ++j) {
            pic(i, j, 0) = red;
            pic(i, j, 1) = green;
            pic(i, j, 2) = blue;

            pic(i, pic.height - 1 - j, 0) = red;
            pic(i, pic.height - 1 - j, 1) = green;
            pic(i, pic.height - 1 - j, 2) = blue;
        }
    }

    // Add left and right frame
    for (int j = 0; j < pic.height; ++j) {
        for (int i = 0; i < frameWidth; ++i) {
            pic(i, j, 0) = red;
            pic(i, j, 1) = green;
            pic(i, j, 2) = blue;

            pic(pic.width - 1 - i, j, 0) = red;
            pic(pic.width - 1 - i, j, 1) = green;
            pic(pic.width - 1 - i, j, 2) = blue;
        }
    }
}

void DecorativeFrame(Image& pic, unsigned int red, unsigned int green, unsigned int blue) {
    int patternFrequency = 40; // Adjust this value for the frequency of the pattern
    // Calculate frame width as a percentage of image dimensions
    int frameWidth = min(pic.width, pic.height) * 0.05; // Adjust the percentage as needed (5%)

    // Apply the pattern to the top and bottom frames
    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < frameWidth; ++j) {
            // Calculate the pattern based on the frequency
            if ((i / patternFrequency + j / patternFrequency) % 2 == 0) {
                // Apply the user-selected color for the pattern
                pic(i, j, 0) = red;
                pic(i, j, 1) = green;
                pic(i, j, 2) = blue;

                // Apply the same pattern to the bottom frame
                pic(i, pic.height - 1 - j, 0) = red;
                pic(i, pic.height - 1 - j, 1) = green;
                pic(i, pic.height - 1 - j, 2) = blue;
            } else {
                // Apply white for the background
                pic(i, j, 0) = 255; // White
                pic(i, j, 1) = 255; // White
                pic(i, j, 2) = 255; // White

                // Apply the same pattern to the bottom frame
                pic(i, pic.height - 1 - j, 0) = 255; // White
                pic(i, pic.height - 1 - j, 1) = 255; // White
                pic(i, pic.height - 1 - j, 2) = 255; // White
            }
        }
    }

    // Apply the pattern to the left and right frames
    for (int j = 0; j < pic.height; ++j) {
        for (int i = 0; i < frameWidth; ++i) {
            // Calculate the pattern based on the frequency
            if ((i / patternFrequency + j / patternFrequency) % 2 == 0) {
                // Apply the user-selected color for the pattern
                pic(i, j, 0) = red;
                pic(i, j, 1) = green;
                pic(i, j, 2) = blue;

                // Apply the same pattern to the right frame
                pic(pic.width - 1 - i, j, 0) = red;
                pic(pic.width - 1 - i, j, 1) = green;
                pic(pic.width - 1 - i, j, 2) = blue;
            } else {
                // Apply white for the background
                pic(i, j, 0) = 255; // White
                pic(i, j, 1) = 255; // White
                pic(i, j, 2) = 255; // White

                // Apply the same pattern to the right frame
                pic(pic.width - 1 - i, j, 0) = 255; // White
                pic(pic.width - 1 - i, j, 1) = 255; // White
                pic(pic.width - 1 - i, j, 2) = 255; // White
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

    // Get frame color from user
    unsigned int red, green, blue;
    UserFrameColor(red, green, blue);

    // Choose frame type
    int frameChoice;
    // Loop until a valid choice (1 or 2) is made
    while (true) {
        cout << "Choose the frame type:\n";
        cout << "1. Plain\n";
        cout << "2. Decorative\n";
        cout << "Enter your choice: ";
        cin >> frameChoice;

        if (frameChoice == 1) {
            // Calculate frame width as a percentage of image dimensions
            int frameWidth = min(pic.width, pic.height) * 0.05; // Adjust the percentage as needed (e.g., 0.05 for 5%)
            PlainFrame(pic, red, green, blue, frameWidth);
            break; // Exit the loop if a valid choice is made
        } else if (frameChoice == 2) {
            // Apply the decorative frame
            DecorativeFrame(pic, red, green, blue);
            break; // Exit the loop if a valid choice is made
        } else {
            cout << "Invalid choice. Please choose again." << endl;
        }
    }

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

#include "Image_Class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
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
vector<vector<vector<long long>>> calculatePrefixSum(Image& pic) {
    vector<vector<vector<long long>>> prefixSum(pic.width, vector<vector<long long>>(pic.height, vector<long long>(3)));

    for (long long i = 1; i < pic.width; ++i) {
        prefixSum[i][0][0] = pic(i, 0, 0) + prefixSum[i-1][0][0];
        prefixSum[i][0][1] = pic(i, 0, 1) + prefixSum[i-1][0][1];
        prefixSum[i][0][2] = pic(i, 0, 2) + prefixSum[i-1][0][2];
    }
    for (long long j = 1; j < pic.height; ++j) {
        prefixSum[0][j][0] = pic(0, j, 0) + prefixSum[0][j-1][0];
        prefixSum[0][j][1] = pic(0, j, 1) + prefixSum[0][j-1][1];
        prefixSum[0][j][2] = pic(0, j, 2) + prefixSum[0][j-1][2];
    }

    for (int channel = 0; channel < 3; ++channel) {
        for (int i = 1; i < pic.width; ++i) {
            for (int j = 1; j < pic.height; ++j) {
                prefixSum[i][j][channel] = pic(i, j, channel) +
                                           prefixSum[i - 1][j][channel] +
                                           prefixSum[i][j - 1][channel] -
                                           prefixSum[i - 1][j - 1][channel];
            }
        }
    }
    return prefixSum;
}

Image BlurFilter(Image& pic, int radius) {
    vector<vector<vector<long long>>> prefixSum = calculatePrefixSum(pic);
    int count = (radius * 2 + 1) * (radius * 2 + 1);
    Image temp(pic.width, pic.height);
    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < pic.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                long long x1, x2, y1, y2;
                (i - radius - 1 < 0) ? x1 = 0 : x1 = i - radius - 1;
                (j - radius - 1 < 0) ? y1 = 0 : y1 = j - radius - 1;
                (i + radius >= pic.width-1) ? x2 = pic.width-1 : x2 = i + radius;
                (j + radius >= pic.height-1) ? y2 = pic.height-1 : y2 = j + radius;

                long long Sum = prefixSum[x2][y2][k] - prefixSum[x1][y2][k] - prefixSum[x2][y1][k] + prefixSum[x1][y1][k];
                temp(i, j, k) = Sum / count;
            }
        }
    }
    return temp;
}

int main() {
    string inputFilename = InputFilePath();

    Image pic(inputFilename);
    if (!pic.loadNewImage(inputFilename)) {
        cout << "Unable to load the image" << endl;
        return 1;
    }

    int radius ;
    cout<<"Please enter the percentage of the blur you want (10 : 30): \n";
    cin>>radius;
    while (radius < 10 || radius > 30) {
        cout << "Radius better to be between 10 and 30." << endl;
        cout << "Please enter the percentage of the blur you want (15 : 30): ";
        cin >> radius;
    }

    Image filteredImage = BlurFilter(pic, radius);

    string outputFilename = OutputFilePath();

    // Save the image
    if (filteredImage.saveImage(outputFilename)) {
        cout << "Image saved as " << outputFilename << endl;
    } else {
        cout << "Failed to save the image. Please try again." << endl;
        return 1;
    }

    return 0;
}

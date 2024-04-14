#include "Image_Class.h"
#include<iostream>
#include <cstdlib>
using namespace std;
void edge_detection()
{
    string filename;
    cout << "enter the image name you want to apply the edge detection filter to it : " << endl;
    cin >> filename;
    Image image(filename);
    Image image2(image.width , image.height);
    for (int i = 0 ; i < image.width ; i++)
    {
        for (int j = 0 ; j < image.height ; j++)
        {
            unsigned average = 0;
            for (int k = 0 ; k < 3 ; k++)
                average += image(i , j , k);
            average /= 3;
            for (int k = 0 ; k < 3 ; k++)
            {
                image.setPixel(i , j , 0 , average);
                image.setPixel(i , j , 1 , average);
                image.setPixel(i , j , 2 , average);
            }
        }
    }

    for (int i = 1 ; i < image.width - 1 ; i++)
    {
        for (int j = 1 ; j < image.height - 1 ; j++)
        {
            for (int k = 0 ; k < 3 ; k++)
            {
                int x = image.getPixel(i + 1 , j , k) - image.getPixel(i - 1 , j , k);
                int y = image.getPixel(i , j + 1 , k) - image.getPixel(i , j - 1 , k);
                int gradient = abs(x) + abs(y);

                (gradient > 60)? image2.setPixel(i , j , k , 0) : image2.setPixel(i , j , k , 255);
            }
        }
    }
    cout << "please enter the image name you want to store \n";
    cout << " and specify the extension of the image format : .jpg , .bmp , .png , .jpeg \n";
    cin >> filename;
    image2.saveImage(filename);
    system(filename.c_str());
}
int main()
{
    edge_detection();
}

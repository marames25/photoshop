#include "Image_Class.h"
#include<iostream>
#include <cstdlib>
using namespace std;
void merge(Image & image1 , Image & image2 , Image & image3)
{
        unsigned r1,r2,g1,g2,b1,b2,r3,g3,b3,avgr,avgg,avgb;
        for (int i = 0 ; i < image1.width ; i++ )
        {
            for (int j = 0 ; j < image1.height ; j++)
            {
                for (int k = 0 ; k < 3 ; k++)
                {
                   r1 = image1(i , j , 0);
                   g1 = image1(i , j , 1);
                   b1 = image1(i , j , 2);

                   r2 = image2(i , j , 0);
                   g2 = image2(i , j , 1);
                   b2 = image2(i , j , 2);

                   unsigned avgr = (r1 + r2) / 2;
                   unsigned avgg = (g1 + g2) / 2;
                   unsigned avgb = (b1 + b2) / 2;

                   image3.setPixel(i , j , 0 , avgr);
                   image3.setPixel(i , j , 1 , avgg);
                   image3.setPixel(i , j , 2 , avgb);
                }
            }
        }
        cout << "please enter the image name you want to store \n";
        cout << " and specify the extension of the image format : .jpg , .bmp , .png , .jpeg \n";
        cin >> filename;
        image3.saveImage(filename);
        system(filename.c_str());
}
void resize(Image& image, Image& resized, int newWidth, int newHeight)
{
    double widthRatio = (double)image.width / newWidth;
    double heightRatio = (double)image.height / newHeight;

    for (int i = 0; i < newWidth; ++i)
    {
        for (int j = 0; j < newHeight; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                // Calculate the corresponding pixel coordinates in the original image
                int originalX = int(i * widthRatio);
                int originalY = int(j * heightRatio);

                // Assign the pixel value from the original image to the resized image
                resized(i, j, k) = image(originalX, originalY, k);
            }
        }
    }
}
int main()
{
            string filename1,filenam2;
            cout << "enter the first image name you want to merge : " << endl;
            cin >> filename1;
            Image image1(filename1);
            cout << "enter the second image name to merge : " << endl;
            cin >> filename2;
            Image image2(filename2);
            int A1 = image1.width * image1.height;
            int A2 = image2.width * image2.height;
            if (A1 > A2)
            {
                Image resized_output(image1.width , image1.height);
                resize (image2 , resized_output ,image1.width , image1.height);
                Image image3(image1.width , image1.height);
                merge(image1 , resized_output , image3);
            }
            else if (A2 > A1)
            {
                Image resized_output(image2.width , image2.height);
                resize (image1 , resized_output ,image2.width , image2.height);
                Image image3(image2.width , image2.height);
                merge(resized_output , image2 , image3);
            }
            else
            {
                Image image3(image1.width , image1.height);
                merge(image1 , image2 , image3);
            }
        }
}

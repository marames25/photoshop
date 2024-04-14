#include "Image_Class.h"
#include<iostream>
#include <cstdlib>
using namespace std;
void infrared()
{
    string filename;
    cout << "enter the image name you want to apply the infrared filter to it : " << endl;
    cin >> filename;
    Image image(filename);
    for (int i = 0 ; i < image.width ; i++)
    {
        for (int j = 0 ; j < image.height ; j++)
        {
            unsigned r = image(i , j , 0);
            unsigned g = image(i , j , 1);
            unsigned b = image(i , j , 2);
            for (int k = 0 ; k < 3 ; k++)
            {
                image.setPixel(i , j , 0 , 255);
                image.setPixel(i , j , 1 , 255 - g);
                image.setPixel(i , j , 2 , 255 - b);
            }

        }
    }
    cout << "please enter the image name you want to store \n";
    cout << " and specify the extension of the image format : .jpg , .bmp , .png , .jpeg \n";
    cin >> filename;
    image.saveImage(filename);
    system(filename.c_str());

}
int main()
{
    infrared();
}

#include "Image_Class.h"
#include<iostream>
#include <cstdlib>
using namespace std;
void gray_scale ()
{
    string filename;
    cout << "enter the image name you want to apply the gray scale filter to it : " << endl;
    cin >> filename;
    Image pic(filename);
    for (int i = 0 ; i < pic.width ; i++)
    {
        for (int j = 0 ; j < pic.height ; j++)
        {
            unsigned average = 0;
            for (int k = 0 ; k < 3 ; k++)
                average += pic(i , j , k);
            average /= 3;
            for (int k = 0 ; k < 3 ; k++)
            {
                pic.setPixel(i , j , 0 , average);
                pic.setPixel(i , j , 1 , average);
                pic.setPixel(i , j , 2 , average);
            }
        }
    }
    cout << "please enter the image name you want to store \n";
    cout << " and specify the extension of the image format : .jpg , .bmp , .png , .jpeg \n";
    cin >> filename;
    pic.saveImage(filename);
    system(filename.c_str());
}
int main()
{
    gray_scale();
}

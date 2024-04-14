#include "Image_Class.h"
#include<iostream>
#include <cstdlib>
using namespace std;
void lighter ()
{
    string filename;
    cout << "enter the image name you want to make it lighter : " << endl;
    cin >> filename;
    Image pic(filename);
    for (int i = 0 ; i < pic.width ; i++)
    {
        for (int j = 0 ; j < pic.height ; j++ )
        {
            unsigned r = pic(i , j , 0);
            unsigned g = pic(i , j , 1);
            unsigned b = pic(i , j , 2);
            for (int k = 0 ; k < 3 ; k++)
            {
                r *= 1.25;
                g *= 1.25;
                b *= 1.25;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;

            }
            pic.setPixel(i , j , 0 , r);
            pic.setPixel(i , j , 1 , g);
            pic.setPixel(i , j , 2 , b);
        }
    }
    cout << "please enter the image name you want to store \n";
    cout << " and specify the extension of the image format : .jpg , .bmp , .png , .jpeg \n";
    cin >> filename;
    pic.saveImage(filename);
    system(filename.c_str());
}
void darker ()
{
    string filename;
    cout << "enter the image name you want to make it darker : " << endl;
    cin >> filename;
    Image pic(filename);
    for (int i = 0 ; i < pic.width ; i++)
    {
        for (int j = 0 ; j < pic.height ; j++ )
        {
            unsigned r = pic(i , j , 0);
            unsigned g = pic(i , j , 1);
            unsigned b = pic(i , j , 2);
            for (int k = 0 ; k < 3 ; k++)
            {
                r *= 0.75;
                g *= 0.75;
                b *= 0.75;
                if (r < 0)
                    r = 0;
                if (g < 0)
                    g = 0;
                if (b < 0)
                    b = 0;

            }
            pic.setPixel(i , j , 0 , r);
            pic.setPixel(i , j , 1 , g);
            pic.setPixel(i , j , 2 , b);
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
    cout << "do you want to make the image darker or lighter ? " << endl;
    cout << "1)lighter\n2)darker" << endl;
    char op;
    cin >> op;
    if (op != '1' && op != '2')
    {
        cout << "please enter a valid option " << endl;
        cin >> op;
    }
    if (op == '1')
        lighter();
    else
        darker();
}

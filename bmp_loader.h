#ifndef BMP_LOADER_H
#define BMP_LOADER_H

#include <windows.h>

unsigned char* textureData;
        int imgHeight, imgWidth;
class bmp_loader
{
    public:
        unsigned char* textureData;
        int imgHeight, imgWidth;

        bmp_loader(const char*);
        virtual ~bmp_loader();

    protected:

    private:
        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;
};

#endif // BMP_LOADER_H

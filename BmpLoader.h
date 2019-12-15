#ifndef BMPLOADER_H
#define BMPLOADER_H

#include <windows.h>

class BmpLoader
{
    public:
        unsigned char* textureData;
        int imgHeight, imgWidth;


        BmpLoader(const char*);
        virtual ~BmpLoader();

    protected:

    private:
        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;
};

#endif // BMPLOADER_H

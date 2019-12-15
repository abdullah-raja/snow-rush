#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>

class ImageLoader
{
    public:

         GLuint id;
         unsigned char* textureData;
         int iHeight, iWidth;

        ImageLoader(const char* fileName);
        virtual ~ImageLoader();

    protected:
            BITMAPFILEHEADER bfh;
            BITMAPINFOHEADER bih;
    private:
};

#endif // IMAGELOADER_H

#include "ImageLoader.h"
#include <iostream>

ImageLoader::ImageLoader(const char* fileName)
{


    FILE* file;
    file = fopen(fileName, "rb"); // rb = readbinary
    if(!file)
        std::cout << "File not found";
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
    if(bfh.bfType != 0x4D42)
        std::cout << "Invalid bitmap";

    fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);
    if(bih.biSizeImage == 0)
        bih.biSizeImage = bih.biHeight * bih.biWidth * 3;

    textureData = new unsigned char[bih.biSizeImage];
    fseek(file, bfh.bfOffBits, SEEK_SET);

    fread(textureData, bih.biSizeImage ,1 , file);
    // converting BGR to RGB

    unsigned char temp;

    for(int i = 0; i < bih.biSizeImage - 2; i+= 3)
    {

        temp = textureData[i];
        textureData[i] = textureData[i+2];
        textureData[i+2] = temp;

    }

    iHeight = bih.biHeight;
    iWidth = bih.biWidth;
    fclose(file);

}

ImageLoader::~ImageLoader()
{
    //dtor
}

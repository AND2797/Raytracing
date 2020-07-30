#ifndef IMAGE_H
#define IMAGE_H
#include "Color.hpp"

class Image{
    public:
        int height;
        int width;
    
    public:
        Image(int height_val, int width_val);
        int*** create_image();
        void put_pixel(Color color,int row, int column, int*** image);
        void write_image(const char *filename, int*** canvas);
};

#endif
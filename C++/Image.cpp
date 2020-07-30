#include "Image.hpp"
#include "Color.hpp"
#include <string>
#include <fstream>
#include <algorithm>
Image::Image(int height_val, int width_val){

    this->height = height_val;
    this->width = width_val;
};

int*** Image::create_image(){

    int*** canvas = new int**[this->height];
    for (int i = 0; i < this-> height; ++i){
        canvas[i] = new int*[this->width];
        for (int j = 0; j< this->width; ++j){
            canvas[i][j] = new int[3];
        }
    }
    return canvas; 
};

void Image::write_image(const char* filename, int*** canvas){
    
    std::ofstream image_file;
    image_file.open(filename);
    image_file << "P3" << ' ' << this->width << ' ' << this->height << std::endl;
    image_file << 255 << std::endl;
    for (int h = 0; h < this->height; ++h){
        for (int w = 0; w< this->width; ++w){
           
            for(int e = 0; e < 3; ++e)
            {
                image_file  << canvas[h][w][e] << ' ';
            }

        }
        image_file << "\n";
    }
}

void Image::put_pixel(Color color, int column, int row, int*** image){
            double pixel[] = {std::min(255.0, std::max(color.r,0.0)),
                           std::min(255.0, std::max(color.g,0.0)),
                           std::min(255.0, std::max(color.b,0.0))};

            for (int i = 0; i < 3; i++){
                image[row][column][i] = int(pixel[i]);
            }
}

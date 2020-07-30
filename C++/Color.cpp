#include "Color.hpp"

Color::Color(){
    this->r = 0.0;
    this->g = 0.0;
    this->b = 0.0;
}
Color::Color(double r_val, double g_val, double b_val)
        :r{r_val}, g{g_val}, b{b_val}{}

Color Color::add(Color col1, Color col2){

    Color new_col(col1.r + col2.r, col1.g + col2.g, col1.b + col2.b);

    return new_col;
}

Color Color::scalar_mul(Color col1, double scalar){

    Color new_col(col1.r * scalar, col1.g * scalar, col1.b * scalar);

    return new_col;
}
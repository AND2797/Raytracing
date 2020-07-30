#include "Vec3.hpp"
#include <cmath>
#include <iostream>

Vec3::Vec3(){
    this->x = 0; 
    this->y = 0; 
    this->z = 0; 
}
Vec3::Vec3(double x_val, double y_val, double z_val)
     :x{x_val}, y{y_val}, z{z_val}{}

// Vec3::Vec3(double x_val, double y_val, double z_val, double x_d, double y_d, double z_d)
//      :x{x_val}, y{y_val}, z{z_val}, x_dir{x_d}, y_dir{y_d}, z_dir{z_d}{}
double Vec3::magnitude(Vec3 vec){

    double mag = std::sqrt(std::pow(vec.x,2) + std::pow(vec.y, 2) + std::pow(vec.z, 2));
    return mag;
}

Vec3 Vec3::normalize(Vec3 vec){
    
    double mag = Vec3:: magnitude(vec);
    Vec3 norm_vec = Vec3::scalar_div(vec, mag);
    return norm_vec;

}

double Vec3::dot(Vec3 vec1, Vec3 vec2){

    double dot_prod = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
    return dot_prod;
}

Vec3 Vec3::add(Vec3 vec1, Vec3 vec2){

   Vec3 added(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
   return added;
}

Vec3 Vec3::sub(Vec3 vec1, Vec3 vec2){

    Vec3 subbed(vec1.x - vec2.x, vec1.y - vec2.y,vec1.z - vec2.z);
    return subbed;
}

Vec3 Vec3::scalar_sub(Vec3 vec1, double scalar){

    return Vec3(vec1.x - scalar, vec1.y - scalar, vec1.z - scalar);
}

Vec3 Vec3::scalar_mul(Vec3 vec, double val){

    Vec3 s_mulled(vec.x * val, vec.y * val, vec.z * val);

    return s_mulled;
}

Vec3 Vec3::scalar_div(Vec3 vec, double val){

    Vec3 s_divved(vec.x / val, vec.y / val, vec.z / val);
    return s_divved;
}

void Vec3::print(Vec3 vec){
    std::cout << '[' << vec.x << ' ' << vec.y << ' ' << vec.z << ']' << std::endl;

}
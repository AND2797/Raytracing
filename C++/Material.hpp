#ifndef MATERIAL_H
#define MATERIAL_H
#include "Color.hpp"
class Material{

    public:
        Color color;
        double ambient;
        double diffuse;
        double specular;
        double reflection;
    public:
        Material();
        Material(Color col_val);
        Material(Color col_val,double ambient, double diff_val, double spec_val, double ref_val); 
        Color color_at_surface(Vec3 hit_pos)const;

};

#endif
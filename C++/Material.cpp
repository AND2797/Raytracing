#include "Color.hpp"
#include "Material.hpp"
Material::Material(){}
Material::Material(Color col_value)
         :color{col_value},ambient{0.05}, diffuse{1.0}, specular{1.0}, reflection{0.5}{}

Material::Material(Color col_value, double amb_val, double diff_val, double spec_val, double ref_val)
         :color{col_value}, ambient{amb_val}, diffuse{diff_val}, specular{spec_val}, reflection{ref_val}{}


Color Material::color_at_surface(Vec3 hit_pos)const
{

    return this->color;
}
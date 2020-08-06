#include "Color.hpp"
#include "Material.hpp"
Material::Material(){}
Material::Material(Color col_value)
         :color{col_value},ambient{0.05}, diffuse{1.0}, specular{1.0}, reflection{0.5}{}

Material::Material(Color col_value, double amb_val, double diff_val, double spec_val, double ref_val)
         :color{col_value}, ambient{amb_val}, diffuse{diff_val}, specular{spec_val}, reflection{ref_val}{}


Chequered_Material::Chequered_Material(Color col1, Color col2)
                   :Material{col1}, color2{col2}{}

Color Material::color_at_surface(Vec3 hit_pos)const
{

    return this->color;
}

Color Chequered_Material::color_at_surface(Vec3 hit_pos)const
{
    if (int((hit_pos.x + 5.0)* 3.0) % 2 == int(hit_pos.z * 3.0)%2)
    {
        return this->color;
    }
    else
    {
        return this->color2;
    }

}

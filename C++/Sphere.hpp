#ifndef SPHERE_H
#define SPHERE_H
#include "Color.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
class Sphere{
    public:
        Vec3  sp_center;
        double radius;
        Material sp_mat;
    public:
        Sphere();
        Sphere(Vec3 center, double r_val, Material mat);
        double ray_sphere (Vec3 ray, Vec3 ray_dir) const;
        Vec3 sphere_normal(Vec3 hit_pos) const;
};

#endif 
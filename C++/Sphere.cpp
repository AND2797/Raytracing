#include "Sphere.hpp"

Sphere::Sphere(){};
Sphere::Sphere(Vec3 center, double r_val, Material mat)
        :sp_center{center}, radius{r_val}, sp_mat{mat}{}

double Sphere::ray_sphere(Vec3 ray, Vec3 ray_dir) const
{
        
        Vec3 ray_to_sphere = Vec3::sub(ray, this->sp_center);

        double b = 2*(Vec3::dot(ray_dir, ray_to_sphere));
        double c = Vec3::dot(ray_to_sphere, ray_to_sphere) - pow(this->radius, 2);
        double discr = pow(b, 2) - 4*c;

        if (discr >= 0)
        {
                double dist = (-b - sqrt(discr))/2;

                if (dist > 0)
                {
                        return dist;
                }
        }
        
        return -1;       
}

Vec3 Sphere::sphere_normal(Vec3 hit_pos) const
{
        return Vec3::normalize((Vec3::sub(hit_pos, this->sp_center)));
}
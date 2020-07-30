
#include "REngine.hpp"
#include <float.h>
#include <iostream>
#include <algorithm>

REngine::REngine()
        :delta{0.0001}, max_depth{5}{};
REngine::REngine(double del_val, double max_depth_val)
        :delta{del_val}, max_depth{max_depth_val}{};

int*** REngine::render(Environment& env){

    Image im = env.im;
   
    double height = im.height;
    double width = im.width;
    double ar = width / height;
    double x_0 = -1.0;
    double x_1 = 1.0;
    double y_0 = x_0 / ar;
    double y_1 = x_1 / ar;
    double x_step = (x_1 - x_0)/(width - 1);
    double y_step = (y_1 - y_0)/(height - 1);

    Vec3 camera = env.camera;
    // std::vector<Sphere>objs = env.objects;
    // std::vector<Light>lights = env.lights;
    int ***canvas = im.create_image();
    std::cout << "Here Render" << std::endl;
    for (int j = 0; j < height; ++j)
    {
        double y = y_0 + j*y_step;
        for (int i = 0; i < width; ++i)
        {
            double depth = 0; // make this defautl
            // std::cout << "Here";
            double x = x_0 + i*x_step;
            Vec3 point(x, y, 0);
            Vec3 ray_start = camera;
            Vec3 ray_dir = Vec3::normalize(Vec3::sub(point, camera));
            // std::cout << i << ' ' << j << std::endl;
            im.put_pixel(ray_trace(ray_start, ray_dir, env), i, j, canvas);
            // im.put_pixel(ray_trace(ray_start, ray_dir, env), i, j, canvas);

              
        }
    }
    return canvas;
};

auto REngine::find_nearest(Vec3 ray, Vec3 ray_dir, const Environment& env)
{
    struct ray_hit{
        const Sphere* obj_hit = nullptr;
        double min_dist = DBL_MAX;
    };

    ray_hit ray_params;
    for (const auto& i: (env).objects)
    {   

        double calc_dist = i.ray_sphere(ray, ray_dir);
        if ((calc_dist != -1) && ( ray_params.obj_hit == nullptr || calc_dist < ray_params.min_dist))
        {
            ray_params.min_dist = calc_dist;
            ray_params.obj_hit  = &i;
        }
    }
    return ray_params;
}


Color REngine::ray_trace(Vec3 ray, Vec3 ray_dir, const Environment&  env, double depth)
{
    
    // Environment* ptr = &env;
    Color def(0, 0, 0);
    auto hit = find_nearest(ray, ray_dir, env);
    if (hit.obj_hit == nullptr)
    {
        return def;
    }
    Vec3 hit_pos = Vec3::add(ray, Vec3::scalar_mul(ray_dir,hit.min_dist));
    Vec3 hit_normal = hit.obj_hit->sphere_normal(hit_pos);
    def = Color::add(def, find_color(hit.obj_hit, hit_pos, hit_normal, env));
    if (depth < this->max_depth)
    {
        Vec3 ref_ray_pos = Vec3::add(hit_pos, Vec3::scalar_mul(hit_normal, this->delta));
        Vec3 ray_fac = Vec3::scalar_mul(hit_normal, 2 * Vec3::dot(ray_dir, hit_normal));
        Vec3 ref_ray_dir = Vec3::sub(ray_dir, ray_fac);
        def = Color::add(def, Color::scalar_mul(ray_trace(ref_ray_pos, ref_ray_dir, env, depth + 1),hit.obj_hit->sp_mat.reflection));
    }
    return def; 

}


Color REngine::find_color(const Sphere* obj, Vec3 hit_pos,  Vec3 hit_normal, const Environment& env){
    // std::cout << "Here" << std::endl;
    Color obj_color = obj->sp_mat.color_at_surface(hit_pos);
    Vec3 cam_ray = Vec3::sub(env.camera, hit_pos);
    Color color = Color::scalar_mul(Color(255, 255, 255), obj->sp_mat.ambient); // ambient colour

    for (auto& i : env.lights)
    {
        Vec3 light_ray_dir = Vec3::normalize(Vec3::sub(i.source, hit_pos));
        // lambert_color -> diffuse light shading based on colour of obect
        // Color lambert_color = Color::add(color, lambert(obj->sp_mat.diffuse, obj_color, hit_normal, light_ray_dir));
        color = Color::add(color, lambert(obj->sp_mat.diffuse, obj_color, hit_normal, light_ray_dir));
        Vec3 half_vector = Vec3::normalize(Vec3::add(light_ray_dir, cam_ray));
        double specular_k = 50;

        // phong_color -> shine based on frac of light colour
        // Color phong_color = Color::add(color, phong_blinn(obj->sp_mat.specular, i.color, hit_normal, half_vector, specular_k));
        color = Color::add(color, phong_blinn(obj->sp_mat.specular, i.color, hit_normal, half_vector, specular_k));
        // color = Color::add(lambert_color, phong_color);
        
    }
    return color;
}

Color REngine::lambert(double diffuse, Color obj_color, Vec3 hit_normal, Vec3 light_dir)
{


    double lambert_factor = diffuse * std::max(Vec3::dot(hit_normal, light_dir), 0.0);
    Color lambert_color = Color::scalar_mul(obj_color, lambert_factor);

    return lambert_color;

}

Color REngine::phong_blinn(double specular, Color light_color, Vec3 hit_normal, Vec3 half_vector, double specular_k)
{


    double phong_blinn_factor = specular * pow(std::max(Vec3::dot(hit_normal, half_vector), 0.0), specular_k);
    Color phong_color = Color::scalar_mul(light_color, phong_blinn_factor);

    return phong_color;
}
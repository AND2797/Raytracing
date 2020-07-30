#include "Image.hpp"
#include "Environment.hpp"

class REngine
{
    public:
        double delta;
        double max_depth;
    public:
        REngine();
        REngine(double del_val, double max_depth_val);
        int*** render(Environment& env);
        Color ray_trace(Vec3 ray, Vec3 ray_dir, const Environment& env, double depth = 0);
        // auto find_nearest(Vec3 ray, Vec3 ray_dir, Environment* env;
        auto find_nearest(Vec3 ray, Vec3 ray_dir, const Environment& env);
        Color find_color(const Sphere *obj_hit, Vec3 hit, Vec3 hit_normal, const Environment& env);
        Color lambert(double diffuse, Color obj_color, Vec3 hit_normal, Vec3 light_dir);
        Color phong_blinn(double specular, Color light_color, Vec3 hit_normal, Vec3 half_vector, double specular_k);
};
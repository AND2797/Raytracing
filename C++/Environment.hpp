#ifndef ENV_H
#define ENV_H
#include <vector>
#include "Sphere.hpp"
#include "Image.hpp"
#include "Light.hpp"

class Environment{
    public:
        Vec3 camera;
        std::vector<Sphere>objects;
        Image im;
        std::vector<Light>lights;
    public:
        Environment(Vec3 env_cam, std::vector<Sphere>env_obj, Image env_im, std::vector<Light>env_lights);
};

#endif
#include "Environment.hpp"

Environment::Environment(Vec3 env_cam, std::vector<Sphere>env_obj, Image env_im, std::vector<Light> env_lights)
            :camera{env_cam}, objects{env_obj}, im{env_im}, lights{env_lights}{}
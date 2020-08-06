#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <complex>

#include "Vec3.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "Sphere.hpp"
#include "REngine.hpp"
#include "Environment.hpp"
#include "Material.hpp"
int main(int argc, char **argv)
{
    Image im(1080, 1920);

    auto start = std::chrono::system_clock::now();
    Vec3 camera(0, -0.35, -1);
    Sphere ground(Vec3(0, 10000.5, 1), 10000.0, Chequered_Material(Color(0,0,0),Color(255,255,255)));
    Sphere blue_ball(Vec3(0.75, -0.1, 1), 0.6, Material(Color(0, 0, 255)));
    Sphere red_ball(Vec3(-0.75,-0.1,1), 0.6, Material(Color(255, 0, 0)));
    std::vector<Sphere>objects{ground, blue_ball, red_ball};

    Light light1(Vec3(1.5,-0.5,-10.0),Color(255,255,255));

    std::vector<Light>lights{light1};
    Environment env(camera, objects, im, lights);
    REngine engine;
    int*** canvas = engine.render(env);
    im.write_image("test1.ppm", canvas);
    auto end = std::chrono::system_clock::now();
    auto diff = end - start;
    auto diff_sec = std::chrono::duration_cast<std::chrono::microseconds>(diff);
    std::cout << diff_sec.count() << std::endl;

    return 0;
}
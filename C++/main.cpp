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
    
    Vec3 camera(1, 1, 1);
    
    // std::vector<Sphere>spheres;
    // for (int i = 0; i < 200; ++i){

    //     spheres.push_back(Sphere(Vec3(0.1*(i/2), 0.1*(i/2), 0.1*(i/2)), 0.05*5, Material(Color(255-i, 0, 0))));

    // }
    Sphere green_ball(Vec3(0.75, -1.20, 1.0), 0.5, Material(Color(0, 255, 0)));
    Sphere red_sphere(Vec3(0.75, -0.50, 1.0), 0.4, Material(Color(255, 0, 0)));
    Sphere black_sphere(Vec3(0, 0, 0), 0.3, Material(Color(125, 156, 0)));
    Sphere blue_sphere(Vec3(-0.75, -0.50, 1.0), 0.4, Material(Color(255, 0, 255)));
    Sphere ground(Vec3(0, 10000.5, 1), 10000.0, Material(Color(0, 255, 0),0.5, 0.5, 0.0, 0.0));
    std::vector<Sphere>objects{blue_sphere, black_sphere, red_sphere};
    Light light1(Vec3(1.5,-0.5,-10.0),Color(255,255,255));
    Light light2(Vec3(-0.5, -10.5, 0), Color(230, 230, 230));

    // std::vector<Light>lights{light1, light2};
    std::vector<Light>lights{light1, light2};
    Environment env(camera, objects, im, lights);
    REngine engine;
    int*** canvas = engine.render(env);
    im.write_image("test1.ppm", canvas);
    // constexpr auto max_row = 22, max_column = 78, max_iteration = 20;

    // 	for(auto row = 0; row < max_row; ++row)
    //     {
	// 	for(auto column = 0; column < max_column; ++column)
    //     {
	// 		std::complex<float> z, c = {
	// 			(float)column * 2 / max_column - 1.5f,
	// 			(float)row * 2 / max_row - 1				
	// 		};
	// 		int iteration = 0;
	// 		while(abs(z) < 2 && ++iteration < max_iteration)
	// 			z = pow(z, 2) + c;
	// 		std::cout << (iteration == max_iteration ? '#' : '.');
	// 	}
	// 	std::cout << '\n';
	// }
    auto end = std::chrono::system_clock::now();
    auto diff = end - start;
    auto diff_sec = std::chrono::duration_cast<std::chrono::microseconds>(diff);
    std::cout << diff_sec.count() << std::endl;

    return 0;
}
# -*- coding: utf-8 -*-
"""
Created on Sun May 24 21:12:17 2020

@author: Aditya
"""
import numpy as np
import math

#CAMERA = 0, 0, -1
#BALL = 0,0,0
#COLOR = RED
r = np.array([255, 0, 0])
g = np.array([0, 255, 0])
b = np.array([0, 0, 255])

def create_PPM(height, width):
    image = np.zeros((height,width,3))
    def put_pixel(image, row, column, color):
        # import pdb; pdb.set_trace()
        image[row][column] = color
    
    camera = np.array([0, 0, -1])
    
    aspect_ratio = float(width) / height
    x0 = -1.0 ; x1 = 1.0
    xstep = (x1 - x0) / (width - 1)
    y0 = -1.0 / aspect_ratio
    y1 = 1.0 / aspect_ratio
    ystep = (y1 - y0) / (height - 1)
    
    for h in range(height):
        y = y0 + h*ystep 
        for w in range(width):
            x = x0 + w*xstep
            ray = np.array([x, y, -1])
            # put_pixel(image,h, w, b - np.array([0, 0, h])) 
            put_pixel(image, h, w, r)
            

        
    return image

def write_PPM(image, filename):
    # import pdb; pdb.set_trace()
    file = open(filename, "w")
    width = image.shape[0]
    column = image.shape[1]
    file.write(f"P3 {width} {column}\n")
    file.write("255\n")
    for w in range(width):
        for c in range(column):
            for comp in image[w][c]:
                file.write(str(int(comp)))
                file.write(" ")
        file.write("\n")
            

def calc_dist(origin,center,ray, radius):
    ray_dir = np.linalg.norm(ray)
    sphere_to_ray = origin - center
    b = np.dot(2*ray_dir, sphere_to_ray)
    c = np.dot(sphere_to_ray, sphere_to_ray) - radius * radius
    
    disc = b**2 - 4*c
    if disc >= 0:
        dist = (-b - math.sqrt(disc))/2
        if dist > 0:
            return 
    
    return None

def calc_hit(origin, dist, ray):
    return origin + np.linalg.norm(ray)*dist


    
    
# if __name__ == "__main__":
#     WIDTH = 320;
#     HEIGHT = 200;
#     camera_pos = np.array([0, 0, -1])
#     image = create_PPM(255,255)
#     write_PPM(image, "test.ppm")
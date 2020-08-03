# -*- coding: utf-8 -*-
"""
Created on Fri May 29 11:56:46 2020

@author: Aditya
"""
from PIL import Image
from Geometry import *
from Image import *
from Scene import * 
from Render import *
from Material import *
# from test_par import *
import cv2
import concurrent.futures
import time


def create_PPM(canvas):
    count = 0
    for h in range(canvas.shape[0]):
        count+=1
        for w in range(canvas.shape[1]):
            col  = b - np.array([0, 0, count])
            canvas[h][w] = col
            
    return canvas

    
def write_PPM(canvas, filename):
    # import pdb; pdb.set_trace()
    file = open(filename, "w")
    file.write(f"P3 {canvas.shape[1]} {canvas.shape[0]}\n255\n")
    for w in range(canvas.shape[0]):
        for row in canvas[w]:
            for color in row:
                file.write(str(int(color))+" ")
        
        file.write("\n")
            
def export(canvas, filename):
    cv2.imwrite(filename, canvas)

if __name__ == '__main__':
    start_time = time.time()
    r = color([255, 0, 0])
    g = color([0, 255, 0])
    b = color([0, 0, 255])
    WIDTH = 320
    HEIGHT = 200
    camera = vector([0, -0.35, -1])
    green_ball = sphere(vector([-2.75, -0.1, 3]), 0.6,material(color= g, reflectivity = 0.5))
    blue_ball = sphere(vector([0.75, -0.1, 1]), 0.6, material(color = b,reflectivity = 0.5))
    red_ball = sphere(vector([-0.75, -0.1, 2.25]), 0.6, material(color = r, reflectivity = 0.5))
    blue_ish_ball = sphere(vector([-0.75, -0.1, 0.8]), 0.25, material(color = (b)-150, reflectivity = 0.5))
    red_ish_ball = sphere(vector([-2.75, -0.1, 2.75]), 0.25, material(color = (r)-150, reflectivity = 0.5))
    green_ish_ball = sphere(vector([-0.75, -0.1, 2.00]), 0.25, material(color = (g)-150, reflectivity = 0.5))
    color1 = color([62,5,0])
    color2 = color([230, 184, 125])
    ground = sphere(vector([0, 300000.5, 1]), 300000.0, material_check(color1 = color1, color2 = color2))
    ground.material.reflectivity = 0.2
    light1 = light(vector([1.5, -0.5, -10.0]), r+g+b)
    light2 = light(vector([-0.5, -10.5, 0.0]), color([230, 230, 230]))
    objects = [blue_ball, red_ball, green_ball, blue_ish_ball,red_ish_ball, green_ish_ball, ground]
    lights = [light1, light2]
    scene_ = scene(camera, objects, WIDTH, HEIGHT, lights)
    engine = RenderEngine()
    render_img = engine.render(scene_)
    # print(render_img)
    cv2.imwrite("ball_notsampled.png", render_img)
    total_time = time.time() - start_time
    print(f'time taken - {total_time}')
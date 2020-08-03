# -*- coding: utf-8 -*-
"""
Created on Fri May 29 23:46:02 2020

@author: Aditya
"""

from Image import *
from Geometry import *
from Material import *
import time
import cv2
from tqdm import tqdm
import multiprocessing as mp
import concurrent.futures
import itertools

class RenderEngine:
    def __init__(self, SS = 1, mp_flag = 0):
        self.SS = SS
        self.mp_flag = mp_flag
        
    max_depth = 5
    delta = 0.0001
    def render(self, scene):
        #supersample
        width = scene.width * self.SS
        height = scene.height * self.SS
        ar = float(width) / height
        x0 = -1.0
        x1 =  1.0
        xstep = (x1 - x0) / (width - 1)
        y0 = -1.0 / ar
        y1 = 1.0/ ar
        ystep = (y1 - y0) / (height - 1)
        
        camera = scene.camera
        canvas = image(np.zeros((height, width, 3)))
        

        ht_iterator = range(height)
        wt_iterator = range(width)
        paramlist = list(itertools.product(ht_iterator, wt_iterator))
        scene_list = [i for i in itertools.repeat(scene, len(paramlist))]

        if (self.mp_flag):
            with concurrent.futures.ProcessPoolExecutor() as executor:
                ret = executor.map(self.process_single_pixel, paramlist, scene_list)
                
                # for result in ret:
                # canvas = np.sum(np.array(ret))
                for result in ret:
                     canvas = np.add(canvas, result)
        else:        
            for j in tqdm(range(height), position = 0, leave = True):
                y = y0  + j * ystep
                
                for i in range(width):
                    x = x0 + i * xstep
                    ray_ = vector(camera) #origin
                    ray_direction = vector([x, y, 0] - camera)
                    ray_direction = ray_direction / np.linalg.norm(ray_direction)
                    # ray_ = ray([camera, vector([x, y, camera[2]]) - camera])
                    set_the_color = self.ray_trace(ray_, scene, ray_direction)
    
                    # file.write(f"{ray_} {ray_direction} {set_the_color}\n")
                    
                    # check = 2
                    canvas.set_pixel(i, j, set_the_color) #assiging color
  
                
        return canvas
    
    def process_single_pixel(self, params, scene):
        # import pdb; pdb.set_trace()
        canvas = image(np.zeros((scene.height, scene.width, 3)))
        ht = params[0]; wt = params[1]
        ar = float(scene.width) / scene.height
        x0 = -1.0
        x1 =  1.0
        xstep = (x1 - x0) / (scene.width - 1)
        y0 = -1.0 / ar
        y1 = 1.0/ ar
        ystep = (y1 - y0) / (scene.height - 1)
        y = y0 + ht * ystep
        x = x0 + wt * xstep
        # print('doing')
        ray_ = vector(scene.camera) #origin
        ray_direction = vector([x, y, 0] - scene.camera)
        ray_direction = ray_direction / np.linalg.norm(ray_direction)
        set_the_color = self.ray_trace(ray_, scene, ray_direction)
        canvas.set_pixel(wt, ht, set_the_color) #assiging color
        
        return canvas
    
    def ray_trace(self, ray_, scene, ray_direction, depth = 0):
        color_calc = color([0, 0, 0])
        #find nearest object hit by ray
        dist_hit, obj_hit = self.find_nearest(ray_, scene, ray_direction)
        if obj_hit is None:
            return color_calc
        hit_pos = ray_ + ray_direction*dist_hit
        hit_normal = obj_hit.normal(hit_pos) 
        # import pdb; pdb.set_trace()
        color_calc = np.add(color_calc,self.color_at(obj_hit, hit_pos, hit_normal, scene))
        if depth < self.max_depth:
            reflection_hit = hit_pos + hit_normal*self.delta
            reflection_ray_dir = ray_direction - 2*(np.dot(ray_direction, hit_normal))*hit_normal
            color_calc = np.add(color_calc,self.ray_trace(reflection_hit, scene, reflection_ray_dir, depth + 1)*obj_hit.material.reflectivity)
            
            
        # color_calc += self.color_at(obj_hit, hit_pos, hit_normal, scene)
        return color_calc
    
    def find_nearest(self, ray_, scene, ray_direction):
        dist_min = None
        obj_hit = None
        for obj in scene.objects:
            dist = obj.intersects(ray_, ray_direction)
            if dist is not None and (obj_hit is None or dist < dist_min):
                dist_min = dist
                obj_hit = obj
        return (dist_min, obj_hit)
    
    def color_at(self, obj_hit, hit_pos, hit_normal, scene):
        material = obj_hit.material
        obj_color = material.find_color(hit_pos)
        camera_to_hit = scene.camera - hit_pos #viewer
        specular_k = 50
        color_ = material.ambient * color([0, 0, 0])
        for light in scene.lights:
            light_ray_dir = (light.position - hit_pos) / np.linalg.norm(light.position - hit_pos)
            color_ = np.add(color_, self.lambert(light_ray_dir, hit_normal, material.diffuse, obj_color))
            color_ = np.add(color_, self.phong_blinn(light_ray_dir, camera_to_hit, hit_normal, material.specular, specular_k, light.color))        
        return color_
    
    
    def lambert(self, light_ray_dir, hit_normal, diffuse, obj_color):
        color = obj_color * diffuse * max(np.dot(light_ray_dir, hit_normal), 0)
        return color
    
    def phong_blinn(self, light_ray_dir, camera_to_hit, hit_normal, specular, specular_k, light_color):
        H = light_ray_dir + camera_to_hit
        H = H / np.linalg.norm(H)
        color = (light_color*specular*max(np.dot(H, hit_normal),0)**specular_k)
        return color
    
    def dummy(self, params):
        return np.array([params[0], params[1]])
# -*- coding: utf-8 -*-
"""
Created on Fri May 29 11:57:03 2020

@author: Aditya
"""
import math
import numpy as np


class vector(np.ndarray):
    def __new__(cls, input_array):
        obj = np.asarray(input_array).view(cls)
        return obj
    
    def __array_finalize__(self, obj):
        if obj is None: return
        


class ray(vector):
    pass
    
class sphere:
     
    def __init__(self, center, radius, material):
        self.center = center
        self.radius = radius
        self.material = material
    
    def intersects(self, ray, ray_direction):
          # import pdb; pdb.set_trace()
          sphere_to_ray = ray - self.center
          b = np.dot(2*ray_direction, sphere_to_ray)
          c = np.dot(sphere_to_ray, sphere_to_ray) - self.radius*self.radius
          disc = b * b - 4 * c
          
          if disc >= 0:
              
              dist = (-b - math.sqrt(disc)) / 2
              if dist > 0:
                  return dist
             
          return None
     
    def normal(self, hit_pos):
        return (hit_pos - self.center) / np.linalg.norm(hit_pos - self.center)

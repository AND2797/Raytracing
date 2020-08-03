# -*- coding: utf-8 -*-
"""
Created on Fri May 29 23:39:01 2020

@author: Aditya
"""
from Geometry import vector
from Image import color
class scene:
    def __init__(self, camera, objects, width, height, lights):
        self.camera = camera
        self.objects = objects
        self.width = width
        self.height = height
        self.lights = lights
        
class light:
    def __init__(self, position, color):
        self.position = position
        self.color = color
        

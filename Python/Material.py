# -*- coding: utf-8 -*-
"""
Created on Sat Jun  6 22:00:40 2020

@author: Aditya
"""
class material:
    def __init__(self, color = None, ambient = 0.05, diffuse = 1.0, specular = 1.0, reflectivity = 0.5):
        self.color = color
        self.ambient = ambient
        self.diffuse = diffuse
        self.specular = specular
        self.reflectivity = reflectivity
    
    def find_color(self, position):
        return self.color


class material_check(material):
    def __init__(self, color1, color2):
        super().__init__()
        self.color1 = color1;
        self.color2 = color2;
        
    def find_color(self, position):
        # import pdb; pdb.set_trace()
        if int((position[0] + 5.0)*3.0)%2 == int(position[2]*3.0)%2:
            return self.color1
        else:
            return self.color2

# -*- coding: utf-8 -*-
"""
Created on Fri May 29 12:38:16 2020

@author: Aditya
"""

import numpy as np
from Geometry import vector
import inspect

class color(vector):
    pass

class image(vector):
    
    def set_pixel(self, x, y, color_):
        self[y][x] = color_


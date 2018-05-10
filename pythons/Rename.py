#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import sys
path = sys.getcwd()
print (path)
sys.path.append(path)

files = os.listdir(path)

for filename in files:
    portion = os.path.splitext(filename)
    if portion[1] == ".cc":
        newname = portion[0] + ".cpp"
        os.rename(filename,newname)

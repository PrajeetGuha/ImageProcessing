from PIL import Image
import numpy as np
import subprocess
import os
import time

real_image = 'greyscale.jpg'
unit_program = 'kmeans_clustering.c'
output_image = 'output.jpg'

img = Image.open('images/'+real_image).convert('L')
header = img.size
ar = np.asarray(img)
with open('input.txt',"w") as f:
    f.write(f'{header[1]} {header[0]}\n')
    for r in ar:
        for c in r:
            f.write(f'{c} ')
        f.write('\n')

subprocess.call(["gcc", 'algorithms/'+unit_program])
subprocess.call("a.exe")

arr = []
with open('output.txt','r') as f:
    next(f)
    for line in f:
        arr.append(list(map(int,line.strip().split())))

ar = np.array(arr)
img = Image.fromarray(ar).convert('RGB')
img.save(output_image)

delete = ['a.exe','input.txt','output.txt']
for k in delete:
    os.remove(k)
import os
import subprocess
import time

import numpy as np
from PIL import Image

real_image = 'vertebral.jpg'
processing_pipeline = ['fuzzy_cmeans']
output_image = 'output.jpg'

delete = ['input.txt', 'output.txt', 'a.exe', 'output.jpg']
for k in delete:
    try:
        os.remove(k)
    except FileNotFoundError:
        pass
img = Image.open('images/'+real_image).convert('L')
header = img.size
ar = np.asarray(img)
with open('input.txt', "w") as f:
    f.write(f'{header[1]} {header[0]}\n')
    for r in ar:
        for c in r:
            f.write(f'{c} ')
        f.write('\n')

for p in processing_pipeline:
    subprocess.call(["gcc", 'algorithms/'+p+'.c'])
    subprocess.call("a.exe")
    os.remove('input.txt')
    os.rename('output.txt', 'input.txt')

arr = []
with open('input.txt', 'r') as f:
    next(f)
    for line in f:
        arr.append(list(map(int, line.strip().split())))

ar = np.array(arr)
img = Image.fromarray(ar).convert('RGB')
img.save('output/'+output_image)

delete = ['a.exe', 'input.txt']
for k in delete:
    os.remove(k)

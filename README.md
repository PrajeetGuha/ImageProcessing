# ImageProcessing
Most of the programs are done using C.
The `driver.py` file is driver file that converts any image into B/W image in .txt format which is used by the C program to do image processing and gives an output .txt file. This file is then used by this program to convert .txt to .jpg image which is the output image. This is ahieved by the driver using threading.<br/>

Directory structure - 
* `images` folder contains input image
* `algorithms` folder contains algorithms

Image Processing techniques - 
1. Negative Processing
2. Linear Contrast Stretching
3. Histogram Equalization
4. Non-linear Contrast Stretching ( Logarithmic, Gama )
5. Neigbourhood Processing
6. Clustering techniques( K-means, Fuzzy C-means )
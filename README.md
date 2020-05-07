# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://github.com/CS126SP20/project-proposal-notSarish) to understand the project
layout.

**Author**: Sarish Deotale - [`sarishd2@illinois.edu`](mailto:sarishd2@illinois.edu)

# Image Altering App

##Image Compression

For my image compression algorithm, I used a lossy low rank SVD approximation to compress the image. This is done by using the highest rank singular values and their corresponding left and right singular vectors. My algorithm takes in how much the user wants to compress the image in terms of a percent of the original image.

![alt text](https://d3i71xaburhd42.cloudfront.net/6d3c3acb5e020bb13eb64194b4456e7550197ed8/5-Figure3-1.png)

This image shows how using greater ranks results in a less compressed but better image. My algorithm works in very similar way but is more friendly to newer user by allowing them to choose a percentage of the image.
###Issues:
I found that I had a lot of issues when it came to run time. Eigen's SVD function has a running time approximated by O(n^3), and when using large matrices for images (some as large as 1000 x 1000), the running time was especially high. This lead me to try to approximate the SVD using a randomized SVD algorithm. You can read more about this here
1. [Facebook Research Blog](https://research.fb.com/blog/2014/09/fast-randomized-svd/)
2. [Research Paper](https://arxiv.org/pdf/1907.06470.pdf)
3. [Google REDSVD Algorithm](https://code.google.com/archive/p/redsvd/)

Unfortunately, while these algorithms did help my code run a little quicker by using techniques such as QR decomposition and Gram-Schmidt decomposition, they lacked somewhat in accuracy. Also they used other techniques that still had high running times such as matrix multiplication which also has a O(n^3) running time. This meant these algorithms were already fairly slow. I later found out that there were some workarounds to this by using  

```
g++ -I/path/to/eigen -O3 -DEIGEN_NO_DEBUG -fopenmp program.cpp
```

to compile code as it makes Eigen run quicker. Another solution is using OpenMP which is a multiprocessing library. 
##Image Sharpening

My image sharpening algorithm is based on common edge detection techniques through the Laplacian filter. First, I reduce the noise of the image through gaussian blurring, and then I use the Laplacian filter to give me a matrix that highlights the edges of an image. Then, I subtract this new matrix from the original to essentially sharpen the image. However some problems arise with how Laplacian filter and how potent it is. To workaround this, I create a slider that would allow the user to change how sharp they want the image in real time.

![unsharp](file:///Users/sarishdeotale/Desktop/Screen%20Shot%202020-05-06%20at%2011.53.42%20PM.png)
![sharp](file:///Users/sarishdeotale/Desktop/Screen%20Shot%202020-05-06%20at%2011.53.30%20PM.png)

To make this even more user friendly I give the user the option to rewrite the file or make a new one with a similar name.




##Dependencies:
[Cmake](https://cmake.org/)  
[Eigen](https://gitlab.com/libeigen/eigen.git)  
[Cinder-ImGui](https://github.com/simongeilfus/Cinder-ImGui)  
[OpenCV](https://github.com/opencv/opencv/tree/4.3.0)  

####MacOS
```
cd opencv
mkdir build
```

Then through the Cmake-gui fill the source and build directory. Then configure, and finally fill extra_modules with opencv_contrib/modules. Then,

```
make -j4
sudo make install
```
and 

```
find_package(OpenCV REQUIRED) # after project()
add_library(opencv INTERFACE)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv INTERFACE ${OpenCV_LIBS})
```
for your CMakeLists.txt file

##Future Plans:
I plan on working more on writing a more efficient algorithm to computed an approximate SVD. I also plan on incorporating multithreading processing into my program to make the running time quicker. I am also interested in other applications of linear algebra and images and would love to research more on the topic.


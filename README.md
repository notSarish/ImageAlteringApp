# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://github.com/CS126SP20/project-proposal-notSarish) to understand the project
layout.

**Author**: Sarish Deotale - [`sarishd2@illinois.edu`](mailto:sarishd2@illinois.edu)

# Image Altering App

Image Compression:

For my image compression algorithm, I used a lossy low rank SVD approximation to compress the image. This is done by using the highest rank singular values and their corresponding left and right singular vectors. My algorithm takes in how much the user wants to compress the image in terms of a percent of the original image.

![alt text](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.semanticscholar.org%2Fpaper%2FLossy-image-compression-using-SVD-coding-algorithm-Aishwarya-Ramesh%2F6d3c3acb5e020bb13eb64194b4456e7550197ed8%2Ffigure%2F0&psig=AOvVaw1Ye4Ym9sguzHT45tTtf5Ug&ust=1588909579057000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCJiBz8vroOkCFQAAAAAdAAAAABAO)

This image shows how using greater ranks results in a less compressed but better image. My algorithm works in very similar way but is more friendly to newer user by allowing them to choose a percentage of the image.


//show slider off and how it changes image sharpening
//math behind laplacian
//talk about running time
//talk about randomized SVD algorithm
//talk about future plans

Dependencies:
Cmake
Eigen
OpenCV
Cinder ImGui



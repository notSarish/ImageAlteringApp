# Development

---

# Week 1 Progress
In week 1, I successfully implemented the libraries I planned on using in my project(Eigen and OpenCV). I also made a quick demo that showed how OpenCV processed the image and converted it to an Eigen matrix. 

# Week 2 Progress
In week 2, I finished creating a model for sharpening grayscale images using a laplacian filter. I also implemented the Cinder-Block ImGui to help create a nice UI for the user. With the help of ImGui, so far I have made an application that allows the user to enter a file path, and choose how sharp they want the image to be through a slider. I also plan on making a feature where the user can rewrite the current image or make a new file of the sharpened image. I also want to make a feature where the user can compress the file if they want to. In terms of next week, I plan on implementing a similar model for colored images, but this may pose some issues as colored images are represented in terms of 3 matrices (each representing either red, green, or blue).

# Week 3 Progress
05/01/20: Began and finished image compression algorithm using SVD low rank approximation. Still needs testing to check if accurate

05/03/20: Began testing code, but found that Eigen::BDCSVD took over 6 minutes to calculate SVD of image. Instead decided to work on writing my own randomized SVD algorithm based on [this research article by Facebook Research](https://research.fb.com/blog/2014/09/fast-randomized-svd/). I may however decided to just use the ARPACK++ library if this implementation takes too long. I also decided against generalizing my model for colored images as I could not find much research online other than models that were based on chrome, hue, and intensity of the image rather than RGB values.

05/06/20: After writing the randomized SVD approximation algorithm, I found slight improvements in run time, but it was still pretty slow. I plan on simply using the Arpack++ library as even after compiling there is a huge loss in quality in the image.

05/06/20: After debugging the randomized SVD approximation, I found out that while fairly accurate, it lacked the accuracy to create a truly compressed image as the image just ended up with a lot of noise. Decided to just use the Eigen SVD on a smaller pixel image as the run times was a lot quicker for smaller images. 

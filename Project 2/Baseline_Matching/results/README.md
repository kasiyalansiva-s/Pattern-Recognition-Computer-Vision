# Baseline Image Matching 

## Overview
This project implements a basic image-matching pipeline designed to match images from a specified directory to a target image. The matching process involves the following steps:

1. **Feature Extraction:**
   - A 7x7 pixel window is extracted from the center of each image in the dataset, forming a feature vector.

2. **Comparison Metric:**
   - Feature vectors are compared using the sum-of-squared distance metric. This metric measures the overall similarity between feature vectors.

3. **Matching Process:**
   - The images with the most similar feature vectors to the target image are identified as matches.

## Matching Results
### Target Image
![Target_Image_1](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/111852df-21b6-44c5-87aa-a2162af378c8)

### Top 5 Matched Images
1. ![Similar_1](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/27cecfb6-5628-47d9-bcba-94da1e8ea067)
2. ![Similar_2](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/1183a5d4-8cfb-4198-921d-c37b444a28ce)
3. ![Similar_3](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/14d0db02-3bdc-4a06-b073-4a8f8db8f9cc)

### Match Distance Scores
1. Matched Image 1 Distance: 0
2. Matched Image 2 Distance: 1273
3. Matched Image 3 Distance: 1344


#### Terminal Image
![Distance Score](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/96116008-032d-48e7-8e42-0257a5fe5556)

### Note: Lower scores indicate greater similarity to the target image.


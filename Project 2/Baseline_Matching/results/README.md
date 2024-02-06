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
![Screenshot 2024-02-05 214800](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/8ee003b9-70f9-49ba-92c7-9c17114898c0)

### Top 5 Matched Images
1. ![Screenshot 2024-02-05 221242](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/f24c5256-c765-4bf8-98c2-7d36263a3fe4)
2. ![Matched Image 2](path/to/matched/image_2.png)
3. ![Matched Image 3](path/to/matched/image_3.png)
4. ![Matched Image 4](path/to/matched/image_4.png)
5. ![Matched Image 5](path/to/matched/image_5.png)

### Match Scores
1. Matched Image 1: 0.123
2. Matched Image 2: 0.178
3. Matched Image 3: 0.201
4. Matched Image 4: 0.215
5. Matched Image 5: 0.231

Note: Lower scores indicate greater similarity to the target image.


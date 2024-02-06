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
2. ![Screenshot 2024-02-05 221255](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/5c67dbc6-92dc-489a-a08d-4a93b76c07bc)
3. ![Screenshot 2024-02-05 221303](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/f4b64099-8bd5-4dd0-bcb1-746ab0aafc33)
4. ![Screenshot 2024-02-05 221314](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/131b8dff-e1c5-4e78-ba73-a91dc8308a28)
5. ![Screenshot 2024-02-05 221326](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/87bd2760-c8aa-43c0-990b-b71c92cee771)

### Match Distance Scores
1. Matched Image 1 Distance: 0
2. Matched Image 2 Distance: 8199
3. Matched Image 3 Distance: 8388
4. Matched Image 4 Distance: 8411
5. Matched Image 5 Distance: 8584

#### Terminal Image
![Screenshot 2024-02-05 215106](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/a2e6e5f0-cee0-4a0c-8454-d53bdbb9db3c)

### Note: Lower scores indicate greater similarity to the target image.


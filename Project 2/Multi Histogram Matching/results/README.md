# Multi-histogram Matching

## Introduction
Multi-histogram matching is a technique used in image processing and computer vision to compare and match images based on multiple color histograms representing different spatial parts of the image.

## Methodology
1. **Feature Vector Selection:** Two color histograms were chosen to represent different spatial parts of the image: one for the top half and another for the bottom half.
   
2. **Histogram Construction:** The histograms were constructed using 8 bins for each of the Red, Green, and Blue (RGB) channels.
  
3. **Distance Metric:** Histogram intersection was employed as the distance metric to compare the corresponding histograms.

4. **Matching Algorithm:** The matching algorithm involved comparing the histograms of the target image with the histograms of other images in the dataset. The top three matches were selected based on the smallest histogram intersection distances.

## Results

The top three matches for the target image pic.0274.jpg:
### Target Image [pic.0274.jpg]
![pic 0274](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/332f6083-979b-414d-af6e-b58bbf1cc422)

### 1. pic.0228.jpg
![pic 0228](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/08f6f931-5db1-47c6-bcac-490958ebfb25)
 
  
### 2. pic.0511.jpg
![pic 0511](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/b8f8ace9-530e-4a50-ad36-a6344352f533) 
  
 
### 3. pic.0558.jpg
![pic 0558](https://github.com/kasiyalansiva-s/Pattern-Recognition-Computer-Vision/assets/156709412/233606d2-1a29-4a74-ab9c-4411ece8e9b5) 
 
 
## Discussion
The results demonstrate the effectiveness of using multi-histogram matching with distinct spatial representations to find similar images. By dividing the image into top and bottom halves, the algorithm can capture nuanced color variations across different regions. The choice of 8 bins for each RGB channel balances computational complexity and information richness. Additionally, histogram intersection provides a robust measure of similarity between histograms.

## Conclusion
Multi-histogram matching, employing multiple color histograms representing different spatial parts of the image, is a viable approach for image matching tasks. Further experimentation with different histogram configurations and distance metrics could enhance the algorithm's performance.


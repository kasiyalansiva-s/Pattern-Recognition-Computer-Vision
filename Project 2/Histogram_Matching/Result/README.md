# Histogram-Based Image Matching Pipeline

## Overview
This project implements a basic image-matching pipeline designed to match images from a specified directory to a target image. The matching process involves the following steps, with a focus on histogram-based features:

1. **Feature Extraction:**
   - Utilizes a chosen histogram (e.g., RG Chromaticity or RGB) as a feature vector for each image in the dataset.

2. **Comparison Metric:**
   - Feature vectors are compared using the histogram intersection distance metric. This metric measures the similarity between histogram-based feature vectors.

3. **Matching Process:**
   - The images with the most similar histogram-based feature vectors to the target image are identified as matches.

## Execution Results

### Target Image
![Target Image](path/to/target/pic.0164.jpg)

### Top 3 Matches with RG Chromaticity Histogram (16 bins for each of R and G)
1. ![Matched Image 1](path/to/matched/pic.0164.jpg)
2. ![Matched Image 2](path/to/matched/pic.0080-1.jpg)
3. ![Matched Image 3](path/to/matched/pic.1032.jpg)

### Top 3 Matches with RGB Histogram (8 bins for each of R, G, and B)
1. ![Matched Image 1](path/to/matched/pic.0164.jpg)
2. ![Matched Image 2](path/to/matched/pic.0110-1.jpg)
3. ![Matched Image 3](path/to/matched/pic.1032.jpg)

Note: The results for the query pic.0164 were obtained using different histograms (RG Chromaticity and RGB) with histogram intersection as the distance metric. These are sample results for illustration, and you can experiment with various histogram types and distance metrics for different outcomes.

## Code Implementation Details
1. **Histogram Calculation:**
   - The code calculates histograms for each image using the specified histogram type and bin configurations.

2. **Distance Metric:**
   - A custom distance metric (histogram intersection) is implemented to measure the similarity between histogram-based feature vectors.

Feel free to adapt and expand upon this baseline to experiment with different histogram types and configurations for your image matching pipeline. Good luck!

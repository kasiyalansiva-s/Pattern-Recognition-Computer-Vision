#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

// Define a structure to hold the feature vectors
struct FeatureVector {
    std::string filename;
    std::vector<double> values;
};

// Function to load feature vectors from the CSV file
std::vector<FeatureVector> loadFeatureVectors(const std::string& filename) {
    std::vector<FeatureVector> featureVectors;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        FeatureVector fv;
        std::string value;
        std::getline(iss, fv.filename, ',');
        while (std::getline(iss, value, ',')) {
            fv.values.push_back(std::stod(value));
        }
        featureVectors.push_back(fv);
    }

    return featureVectors;
}

// Function to calculate the cosine distance between two vectors
double cosineDistance(const std::vector<double>& v1, const std::vector<double>& v2) {
    double dotProduct = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
    double v1Norm = std::sqrt(std::inner_product(v1.begin(), v1.end(), v1.begin(), 0.0));
    double v2Norm = std::sqrt(std::inner_product(v2.begin(), v2.end(), v2.begin(), 0.0));
    return (1.0 - (dotProduct / (v1Norm * v2Norm)));
}

// Function to find the top 3 most similar images
void findSimilarImages(const std::vector<FeatureVector>& featureVectors, const std::string& targetImage) {
    // Find the target feature vector
    auto targetIt = std::find_if(featureVectors.begin(), featureVectors.end(),
        [&targetImage](const FeatureVector& fv) { return fv.filename == targetImage; });
    if (targetIt == featureVectors.end()) {
        std::cerr << "Target image not found in feature vectors.\n";
        return;
    }

    const auto& targetVector = targetIt->values;
    
    // Calculate distances and rank images
    std::vector<std::pair<std::string, double>> distances;
    for (const auto& fv : featureVectors) {
        if (fv.filename != targetImage) {
            double dist = cosineDistance(targetVector, fv.values);
            distances.emplace_back(fv.filename, dist);
        }
    }

    // Sort distances based on distance values
    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
        return a.second < b.second; // Sort in ascending order based on distance values
    });

    // Output top 3 results
    std::cout << "Top 3 results for " << targetImage << ":\n";
    for (int i = 0; i < std::min(5, static_cast<int>(distances.size())); ++i) {
        std::cout << i+1 << ". " << distances[i].first << " - Cosine Distance: " << distances[i].second << "\n";
    }
}



int main() {
    std::vector<FeatureVector> featureVectors = loadFeatureVectors("/media/sakiran/Internal/2nd Semester/PRCV/Project/Project_2/ResNet18_olym.csv");
    
    // Define target images
    std::vector<std::string> targetImages = {"pic.0893.jpg", "pic.0164.jpg"};

    // Find similar images for each target image
    for (const auto& targetImage : targetImages) {
        findSimilarImages(featureVectors, targetImage);
    }

    return 0;
}

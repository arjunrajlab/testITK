#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono> // Include chrono for high-resolution timing

int main() {
    // Load the image as a grayscale image
    cv::Mat img = cv::imread("circle_mask_binary.tif", cv::IMREAD_GRAYSCALE);

    if (img.empty()) {
        std::cerr << "Error: Image not found." << std::endl;
        return -1;
    }

    // Start timing findContours
    auto start = std::chrono::high_resolution_clock::now();

    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Stop timing findContours
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // Print contours
    std::cout << "Found contours:" << std::endl;
    for (int i = 0; i < contours.size(); i++) {
        std::cout << "Contour #" << i << ": " << std::endl;
        for (int j = 0; j < contours[i].size(); j++) {
            std::cout << "(" << contours[i][j].x << ", " << contours[i][j].y << ")" << std::endl;
        }
    }

    std::cout << "Time taken for findContours: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}

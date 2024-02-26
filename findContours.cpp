//g++ -std=c++11 -o findContours findContours.cpp `pkg-config --cflags --libs opencv4`
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <fstream> // Include for file I/O

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

    // Open CSV file for writing
    std::ofstream outFile("contours.csv");

    // Check if file is open
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open contours.csv for writing." << std::endl;
        return -1;
    }

    // Write contours to CSV
    for (size_t i = 0; i < contours.size(); i++) {
        for (size_t j = 0; j < contours[i].size(); j++) {
            outFile << contours[i][j].x << "," << contours[i][j].y << "\n";
        }
        // Optionally, add a line to separate contours
        outFile << "\n"; // Separate each contour by a blank line
    }

    // Close the file
    outFile.close();

    std::cout << "Found contours and wrote them to contours.csv" << std::endl;
    std::cout << "Time taken for findContours: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}

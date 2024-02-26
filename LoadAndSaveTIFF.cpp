// cmake ..
// make

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryContourImageFilter.h"
#include "itkImageRegionIterator.h"
#include <iostream>
#include <chrono> // Include the chrono library

int main()
{
    // Define the image type
    typedef itk::Image<unsigned char, 2> ImageType;

    // Reader and filter types
    typedef itk::ImageFileReader<ImageType> ReaderType;
    typedef itk::BinaryContourImageFilter<ImageType, ImageType> ContourFilterType;
    typedef itk::ImageFileWriter<ImageType> WriterType;

    // Create reader and filter
    ReaderType::Pointer reader = ReaderType::New();
    ContourFilterType::Pointer contourFilter = ContourFilterType::New();
    WriterType::Pointer writer = WriterType::New();

    // Set the input file name
    reader->SetFileName("circle_mask_binary.tif");

    // Setup contour filter
    contourFilter->SetInput(reader->GetOutput());
    contourFilter->SetForegroundValue(1); // Adjusted for mask's objects being represented as 1
    contourFilter->SetBackgroundValue(0); // Background remains 0

    // Start timing the contour generation
    auto startContourGeneration = std::chrono::high_resolution_clock::now();

    // Process the image pipeline for contour generation
    contourFilter->Update();

    // End timing the contour generation
    auto endContourGeneration = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationContourGeneration = endContourGeneration - startContourGeneration;
    std::cout << "Contour generation took: " << durationContourGeneration.count() << " seconds." << std::endl;

    // Set up the writer
    writer->SetInput(contourFilter->GetOutput());
    writer->SetFileName("boundary_image.tif");

    try
    {
        writer->Update();
        std::cout << "Boundary image has been written successfully." << std::endl;
    }
    catch (const itk::ExceptionObject &error)
    {
        std::cerr << "Error: " << error << std::endl;
        return EXIT_FAILURE;
    }

    // Start timing the iteration over the image
    auto startIteration = std::chrono::high_resolution_clock::now();

    // Create an iterator to go over the output contour image
    itk::ImageRegionIterator<ImageType> imageIterator(contourFilter->GetOutput(), contourFilter->GetOutput()->GetRequestedRegion());

    std::cout << "Contour Pixel Coordinates:" << std::endl;

    // Iterate over the image
    for (imageIterator.GoToBegin(); !imageIterator.IsAtEnd(); ++imageIterator)
    {
        if (imageIterator.Get() != 0)
        {
            ImageType::IndexType idx = imageIterator.GetIndex();
            unsigned char pixelValue = imageIterator.Get();
            std::cout << "Coordinate: (" << idx[0] << ", " << idx[1] << "), Value: " << static_cast<int>(pixelValue) << std::endl;
        }
    }

    // End timing the iteration over the image
    auto endIteration = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationIteration = endIteration - startIteration;
    std::cout << "Iteration over the image took: " << durationIteration.count() << " seconds." << std::endl;

    return EXIT_SUCCESS;
}

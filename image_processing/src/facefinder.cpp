#include <opencv2/opencv.hpp>
#include <string>

// Define the C wrapper function
extern "C"
{

    // Implement the C++ function to blur the image
    const uint8_t *blurImage(const uint8_t *imgptr, int32_t width, int32_t height, int32_t channels)
    {
        // Convert image data to OpenCV Mat
        cv::Mat img(height, width, CV_8UC(channels), (uchar *)imgptr);

        // Convert RGBA to BGR
        if (channels == 4)
        {
            cv::cvtColor(img, img, cv::COLOR_RGBA2BGR);
        }

        // Blur the image
        cv::GaussianBlur(img, img, cv::Size(15, 15), 0);

        // Convert the blurred image back to RGBA if it was originally RGBA
        if (channels == 4)
        {
            cv::cvtColor(img, img, cv::COLOR_BGR2RGBA);
        }

        Return the pointer to the image data

            return imgptr;
    }
}

std::vector<int> _detectFaces(const std::vector<int> &image, int width, int height)
{
    // Convert vector to OpenCV image
    cv::Mat img(height, width, CV_8UC1, (void *)image.data());

    // Load Haar cascade classifier for face detection
    cv::CascadeClassifier faceCascade;
    faceCascade.load("/path/to/haarcascade_frontalface_default.xml");

    // Convert image to grayscale
    cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);

    // Detect faces
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // Draw bounding boxes around detected faces
    for (size_t i = 0; i < faces.size(); ++i)
    {
        cv::rectangle(img, faces[i], cv::Scalar(255, 0, 0), 2);
    }

    // Convert modified image to vector
    std::vector<int> modifiedImage;
    if (!img.empty())
    {
        modifiedImage.assign(img.datastart, img.dataend);
    }

    return modifiedImage;
}

std::string _hello(std::string input)
{
    if (input == "good")
    {
        return "good sent";
    }
    else
    {
        return "not good sent";
    }
}

extern "C"
{
    const char *hello(const char *input)
    {
        std::string inputStr(input);

        std::string result = _hello(inputStr);

        // Allocate memory for the result string
        char *resultStr = static_cast<char *>(malloc(result.length() + 1));
        strcpy(resultStr, result.c_str());
        return resultStr;
    }

    // Remember to free the memory allocated by the C function
    void free_string(const char *str)
    {
        free((void *)str);
    }
}

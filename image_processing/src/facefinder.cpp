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
        cv::GaussianBlur(img, img, cv::Size(49, 49), 0);

        // Convert the blurred image back to RGBA if it was originally RGBA
        if (channels == 4)
        {
            cv::cvtColor(img, img, cv::COLOR_BGR2RGBA);
        }

        // Copy the blurred image data back to the original memory location
        memcpy((void *)imgptr, img.data, width * height * channels);

        return imgptr;
    }
}

std::string _hello(std::string input)
{
    if (input == "hello c++")
    {
        return "hello from c++";
    }
    else
    {
        return "who are you?";
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

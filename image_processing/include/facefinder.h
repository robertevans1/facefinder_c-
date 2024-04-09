#pragma once

#include <vector>

std::vector<int> _detectFaces(const std::vector<int> &image, int width, int height);
std::string _hello(std::string input);

uint8_t *blurImage(uint8_t *imgptr, int32_t width, int32_t height, int32_t channels);

const char *hello(const char *input);
void free_string(const char *str);
#include <iostream>
#include <string>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Load texture from file probably will be used in multiple places and need some updates for that.
bool loadTexture(const char* path, GLuint& textureID) {
    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    if (!image) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);
    return true;
}
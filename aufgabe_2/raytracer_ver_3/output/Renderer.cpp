#include "Renderer.h"

#include <iostream>
#include <stdexcept>
#define  SDL_RENDERER_ACCELERATED 0x00000002 // for test
Renderer::Renderer(int width, int height) : width(width), height(height), window(nullptr), sdlrenderer(nullptr), texture(nullptr), pixelBuffer(width * height, VectorColor{0,0,0}) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }

    window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        throw std::runtime_error("Failed to create window");
    }

    sdlrenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdlrenderer) {
        fprintf(stderr, "could not create renderer: %s\n", SDL_GetError());
    }

    texture = SDL_CreateTexture(sdlrenderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture) {
        throw std::runtime_error("Failed to create texture");
    }
}

Renderer::~Renderer() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(sdlrenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::displaySDL(const std::vector<VectorColor>& pixels) {
    updateImage(pixels);
    SDL_RenderPresent(sdlrenderer);
}

void Renderer::updateImage(const std::vector<VectorColor>& pixels) {
    if (((int) pixels.size()) != (int) width * height) {
        throw std::runtime_error("Pixel data size does not match the window size");
    }

    pixelBuffer = pixels;
    void* pixelsData;
    int pitch;

    SDL_RenderClear(sdlrenderer);
    //SDL_LockTexture(texture, nullptr, &pixelsData, &pitch);
    for (int i=0;i<pixels.size();i++) {
        auto pixel = pixels[i];
        int x = i%width;
        int y = i/width;
        SDL_SetRenderDrawColor(sdlrenderer, pixel[0], pixel[1], pixel[2], 0xFF);
        SDL_RenderDrawPoint(sdlrenderer, x, y);
    }
    /*
    if (pixelsData != nullptr) {
        memcpy(pixelsData, pixelBuffer.data(), sizeof(pixelBuffer));
    } else {
        SDL_UnlockTexture(texture);
        throw std::runtime_error("pixelsData is null");
    }
    SDL_UnlockTexture(texture);
    SDL_RenderCopy(sdlrenderer, texture, nullptr, nullptr);
*/
    SDL_RenderPresent(sdlrenderer);

}

void Renderer::updatePixel(int x, int y, const VectorColor& pixel) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates are out of bounds");
    }

    pixelBuffer[y * width + x] = pixel;

    void* pixelsData;
    int pitch;
    if (SDL_LockTexture(texture, nullptr, &pixelsData, &pitch) != 0) {
        throw std::runtime_error("Failed to lock texture");
    }

    SDL_SetRenderDrawColor(sdlrenderer, pixel[0], pixel[1], pixel[2], 0xFF);
    SDL_RenderDrawPoint(sdlrenderer, x, y);

    SDL_UnlockTexture(texture);
    SDL_RenderPresent(sdlrenderer);
}
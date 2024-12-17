#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "../math/math.h"

class Renderer {

    int width;
    int height;
    SDL_Renderer* sdlrenderer;
    SDL_Texture* texture;
    std::vector<VectorColor> pixelBuffer;

    std::string title;
    int window_width;
    int window_height;
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    // render methods for the specific game objects, score, and free ships

public:
    Renderer(int width, int height);
    ~Renderer();
    void displaySDL(const std::vector<VectorColor>& pixels);
    void updateImage(const std::vector<VectorColor>& pixels);
    void updatePixel(int x, int y, const VectorColor& color);
};

#endif //RENDERER_H
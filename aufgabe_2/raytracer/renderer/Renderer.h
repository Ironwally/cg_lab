//
// Created by blackrat on 09.11.24.
//

#ifndef OUTPUT_GENERATOR_H
#define OUTPUT_GENERATOR_H
#include <fstream>


#include <stdlib.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600

class Renderer {

public:
    auto renderSDL(Camera camera) const{
            SDL_Event event;
            SDL_Renderer *renderer;
            SDL_Window *window;
            int i;

            SDL_Init(SDL_INIT_VIDEO);
            SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            auto pixels = camera.screen.getAllPixels();
            for (i = 0; i < pixels.size(); ++i) {
                // first pixel gets ignored I don't know why
                Vectorclr pixel = pixels[i];
                int x = i%camera.screen.width;
                int y = i/camera.screen.width;
                SDL_SetRenderDrawColor(renderer, pixel[0], pixel[1], pixel[2], 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
            SDL_RenderPresent(renderer);

            SDL_Delay(80000);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_SUCCESS;
        // TODO
        // Prepare sdl stuff
        // Generate sdl image
        // output sdl image

        //fenster aufbau aus sdl library
        //setrenderdracolor
        //setrender...

        //sdl2renderer übernehmen
        //save render via sdl library
    }

    static void savePPM(const Screen& screen, const std::string& filename) {
        std::ofstream file(filename, std::ios::out | std::ios::binary);
        file << "P6\n" << screen.width << " " << screen.height << "\n255\n";

        for (auto& pixel : screen.getAllPixels()) {
            file.put(static_cast<char>(static_cast<unsigned char>(std::min(1.0f, pixel[0]) * 255)))
                .put(static_cast<char>(static_cast<unsigned char>(std::min(1.0f, pixel[1]) * 255)))
                .put(static_cast<char>(static_cast<unsigned char>(std::min(1.0f, pixel[2]) * 255)));
        }

        file.close();
    }
};

#endif //OUTPUT_GENERATOR_H

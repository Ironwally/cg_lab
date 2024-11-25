//
// Created by blackrat on 09.11.24.
//

#ifndef OUTPUT_GENERATOR_H
#define OUTPUT_GENERATOR_H
#include <fstream>

class Output_generator {

public:
    auto openSDL(Screen screen) const{
        // TODO
        // Prepare sdl stuff
        // Generate sdl image
        // output sdl image

        //fenster aufbau aus sdl library
        //setrenderdracolor
        //setrender...

        //sdl2renderer übernehmen
        //save render via sdl library

        return "TODO";
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

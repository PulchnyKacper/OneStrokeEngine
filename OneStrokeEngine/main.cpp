#define GLM_FORCE_RADIANS
#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>
#include "game_handler.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {

    ose::GameHandler game{};
    try {
        game.run();
    }
    catch (const std::exception & e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
        }
    return EXIT_SUCCESS;

}
#include "Utils.h"

#include <cstdlib>
#include <fstream> 
#include <iostream>
int Random(int max)
{
    return int(float(rand()) / (RAND_MAX + 1) * float(max));
}

std::ifstream openFile(std::string filepath) {
    std::ifstream stream(filepath);

    if (!stream){
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return stream;
}
#include <iostream>
#include <filesystem>
#include "extractor.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    // Setting default folder as the folder where the program was called
    fs::path folder = "./";

    // Change folder if the user specified one
    if (argc > 1) {

        // Checking if the path specified ends with "/"
        string path = argv[1];
        if (path[path.size() - 1] != '/') {
            // If not, append the "/" at the end
            path += "/";
        }
        folder = path;
    }

    // Creating output folder
    fs::path output_folder("./Output/");
    fs::create_directory(output_folder);

    extract_folders(folder, output_folder);
}
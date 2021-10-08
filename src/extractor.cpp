#include <iostream>
#include <filesystem>
#include "extractor.h"
#include "racer.h"
#include "course.h"

using namespace std;
namespace fs = std::filesystem;

// Checks if the current directory has the specified folder in it
bool check_directory(fs::path root, string folder_name) {

    for (const auto& entry : fs::directory_iterator(root)) {
        string file_name = entry.path().filename().string();

        if (file_name == folder_name) {
            return true;
        }
    }

    return false;
}

void extract_folders(fs::path game_folder, fs::path output_root) {

    int NUM_FOLDERS = 4;
    string folders[NUM_FOLDERS] = {"RACERS", "COURSE_A", "COURSE_B", "COURSE_C"};
    fs::path output_folder;
    fs::path input_folder;

    for (int i = 0; i < NUM_FOLDERS; i++) {

        // Checking if the specified folder is valid
        if (check_directory(game_folder, folders[i])) {

            // Giving user feedback about the software progress
            cout << "Extracting " << folders[i] << "/..." << endl;

            // Creating a folder to store the extraction output
            output_folder = output_root / folders[i];
            fs::create_directory(output_folder);

            // Searching for every known file in the folders
            input_folder = game_folder / folders[i];
            for (const auto& entry : fs::directory_iterator(input_folder)) {
                string file_name = entry.path().filename().string();
                string file_extension = entry.path().extension().string();

                if (file_extension == ".MDL") {
                    if (mdl_to_obj(input_folder / file_name, output_folder / file_name.substr(0, file_name.size() - 4))) {
                        cout << file_name << " extracted successfully." << endl;
                    } else {
                        cout << "Error when extracting " << file_name << ": Wrong polygon data." << endl;
                    }
                }

                if (file_extension == ".RAW") {
                    fs::path raw_output = output_folder / file_name.substr(0, file_name.size() - 4);
                    fs::create_directory(raw_output);
                    decompress_raw(input_folder / file_name, raw_output);
                    cout << file_name << " extracted successfully." << endl;
                }
            }

            cout << folders[i] << "/ extracted successfully." << endl << endl;

        } else {

            // Alert user that the specified folder is wrong
            cout << "ERROR: Couldn't find " << folders[i] << "/ in the specified folder. Please extract the Toy Story Racer ISO and make sure that they're in the specified folder." << endl;
        }
    }
}
#include <iostream>
#include <fstream>
#include "racer.h"

using namespace std;
namespace fs = std::filesystem;

bool check_dir(fs::path game_folder) {

    // Checking if the current directory has RACERS/ folder in it
    for (const auto& entry : fs::directory_iterator(game_folder)) {
        string file_name = entry.path().filename().string();

        if (file_name == "RACERS") {
            return true;
        }
    }

    return false;
}

void mdl_to_obj(fs::path mdl_path, fs::path output_path) {

    // Reading the raw character file
    ifstream racer_model(mdl_path, ios::in | ios::binary);

    // Getting the number of bytes which contain vertexes
    MODEL_HEADER header;
    racer_model.read((char *) &header, sizeof(header));
    header.size *= 2;

    // Creating structures to read the vertex information
    VERTEX_COLOR vc;
    VERTEX v;
    // Creating the .obj output file
    ofstream output_file(output_path.string() + ".obj", ios::out);

    // Current number of edges in the face
    int edges = 1;
    // Total number of edges that the face has
    int polygon;
    // Index to keep track of the number of vertexes found
    int num_vertex = 0;
    // Index to keep track of the number of meshes found
    int num_meshes = 1;
    // Bool to keep track the creating of new meshes objects
    bool new_obj = true;

    // While there are vertexes bytes to be read
    while (racer_model.tellg() < header.size) {

        /* Read the color command that goes to the GTE. They encoded
        in these bytes whether the polygon is a triangle or a quad. Also,
        they encoded the end of a mesh in the color command as well. */
        racer_model.read((char *) &vc, sizeof(vc));

        // If it's the first edge of the face
        if (edges == 1) {

            // Checking if it belongs to this mesh
            if ((vc.color & 0x38000000) == 0) {

                // If not, then the next vertex will belong to a new mesh
                new_obj = true;
                continue;
            }

            // Checking if the polygon is a quad
            if ((vc.color & 0x38000000) == 0x38000000) {
                polygon = 4;
            } else {
                // Set the polygon as a triangle
                polygon = 3;
            }

            // Checking if this vertex belongs to a new object
            if (new_obj) {

                // Create new mesh in the .obj
                output_file << "o MESH_" << num_meshes++ << endl;
                new_obj = false;
            }
        }

        // Read the vertex positions and write them to the .obj
        racer_model.read((char *) &v, sizeof(v));
        num_vertex += 1;
        output_file << "v " << v.x * -1 << " " << v.y * -1 << " " << v.z * -1 << endl;

        // If the vertex is the last of the face, write the face to the .obj
        if (polygon == edges) {
            edges = 1;
            output_file << "f";
            for (int j = polygon - 1; j > -1; j--) {
                output_file << " " << num_vertex - j;
            }
            output_file << endl;
        } else {
            edges += 1;
        }
    }
}

void extract_racer_models(fs::path game_folder, fs::path output_folder) {

    // Checking if the specified folder is valid
    if (check_dir(game_folder)) {

        // Giving user feedback about the software progress
        cout << "Extracting RACERS/ models..." << endl;

        // Creating a folder to store the 3D models in the output
        output_folder = output_folder / "RACERS/";
        fs::create_directory(output_folder);

        // Searching for every .MDL file in the RACERS/ folder
        game_folder = game_folder / "RACERS/";
        for (const auto& entry : fs::directory_iterator(game_folder)) {
            string file_name = entry.path().filename().string();
            string file_extension = entry.path().extension().string();

            if (file_extension == ".MDL") {

                // Convert the .MDL to .obj
                mdl_to_obj(game_folder / file_name, output_folder / file_name.substr(0, file_name.size() - 4));
                cout << file_name << " extracted successfully." << endl;
            }
        }

        cout << "RACERS/ extracted successfully..." << endl;

    } else {

        // Alert user that the specified folder is wrong
        cout << "ERROR: Couldn't find RACERS/ in the specified folder. Please extract the Toy Story Racer game files and make sure that they're in the specified folder." << endl;
    }
}
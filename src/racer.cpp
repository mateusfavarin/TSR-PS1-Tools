#include <fstream>
#include "racer.h"

using namespace std;

void mdl_to_obj(fs::path mdl_path, fs::path output_path) {

    // Reading the raw character file
    ifstream racer_model(mdl_path, ios::in | ios::binary);

    // Getting the number of bytes which contain vertexes
    MODEL_HEADER header;
    racer_model.read((char *) &header, sizeof(header));
    header.size *= 2;

    // Saving seek position to read the mesh data later
    streampos temp = racer_model.tellg();

    // Reading mesh count
    MESH_HEADER mh;
    racer_model.seekg(header.size, ios::beg);
    racer_model.read((char *) &mh, sizeof(mh));

    // Reading mesh metadata
    MESH_METADATA metadata[mh.mesh_count];
    for (int i = 0; i < mh.mesh_count; i++) {
        racer_model.read((char *) &metadata[i], sizeof(metadata[i]));
    }

    // Restoring the seek position to read the mesh data
    racer_model.seekg(temp, ios::beg);

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
    int num_meshes = 0;
    // Bool to keep track of when to create new meshes objects
    bool new_obj = true;

    // While there are vertexes bytes to be read
    while (num_meshes < mh.mesh_count * 2) {

        /* Read the color command that goes to the GTE. They encoded
        in these bytes whether the polygon is a triangle or a quad. Also,
        they encoded the end of a mesh in the color command as well. */
        racer_model.read((char *) &vc, sizeof(vc));

        // If it's the first edge of the face
        if (edges == 1) {
            // Checking if it belongs to this mesh
            if ((vc.cmd & 0x38) == 0) {
                // If not, then the next vertex will belong to a new mesh
                new_obj = true;
                num_meshes++;
                continue;
            }

            // Checking if the polygon is a quad
            if ((vc.cmd & 0x38) == 0x38) {
                polygon = 4;
            } else {
                // Set the polygon as a triangle
                polygon = 3;
            }

            // Checking if this vertex belongs to a new object
            if (new_obj) {
                // Create new mesh in the .obj
                output_file << "o MESH_" << num_meshes << endl;
                new_obj = false;
            }
        }

        // Read the vertex positions and write them to the .obj
        racer_model.read((char *) &v, sizeof(v));
        num_vertex += 1;
        output_file << "v "
                    << ((v.x + metadata[num_meshes / 2].trans_x) * -1) / 127.0 << " "
                    << ((v.y + metadata[num_meshes / 2].trans_y) * -1) / 127.0 << " "
                    << ((v.z + metadata[num_meshes / 2].trans_z) * -1) / 127.0 << " "
                    << vc.r / 255.0 << " " << vc.g / 255.0 << " " << vc.b / 255.0 << endl;

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
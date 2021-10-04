#include <fstream>
#include "racer.h"
using namespace std;

bool mdl_to_obj(fs::path mdl_path, fs::path output_path) {

    // Reading the raw character file
    ifstream racer_model(mdl_path, ios::in | ios::binary);

    // Getting the number of bytes which contain vertexes
    MODEL_HEADER header;
    racer_model.read((char *) &header, sizeof(header));
    header.size *= 2;

    // Saving seek position to read the mesh data later
    streampos temp = racer_model.tellg();

    // Reading mesh count
    MESH_HEADER mesh_header;
    racer_model.seekg(header.size, ios::beg);
    racer_model.read((char *) &mesh_header, sizeof(mesh_header));

    // Reading mesh metadata
    MESH_METADATA metadata[mesh_header.obj_count];
    for (int i = 0; i < mesh_header.obj_count; i++) {
        racer_model.read((char *) &metadata[i], sizeof(metadata[i]));
        metadata[i].obj_size *= 2;
    }

    // Restoring the seek position to read the mesh data
    racer_model.seekg(temp, ios::beg);

    // Structures to read the vertex information
    VERTEX_COLOR vc;
    VERTEX v;

    // Creating the .obj output file
    ofstream output_file(output_path.string() + ".obj", ios::out);

    // Current number of vertexes in the polygon
    int num_vertexes;
    // Index to keep track the total number of vertexes found
    int tot_vertexes = 0;
    // Index to keep track the total number of objects found
    int num_objects = 0;

    // Creating the first mesh by default
    output_file << "o OBJ_" << num_objects << "_high" << endl;

    // While we haven't read every single object in the file
    while (true) {

        /* Read the color command that goes to the GTE. They encoded
        in these bytes whether the polygon is a triangle or a quad. Also,
        they encoded the end of a mesh in the color command as well. */
        racer_model.read((char *) &vc, sizeof(vc));

        // If it's a new mesh
        if ((vc.cmd & 0x38) == 0) {
            // Checking if the new mesh is a low LOD mesh of the previous high LOD mesh
            if ((vc.r == 2) && (vc.g == 0) && (vc.b == 0) && (vc.cmd == 0)) {
                output_file << "o OBJ_" << num_objects << "_low" << endl;
            }
            // If not, then the new mesh belongs to a new object
            else {
                output_file << "o OBJ_" << ++num_objects << "_high" << endl;
                // If we read every single object in the file, we're done
                if (num_objects > mesh_header.obj_count) {
                    return true;
                }
            }
            continue;
        }

        // If it's a new polygon
        if ((vc.cmd & 0x30) == 0x30) {
            // Checking if the polygon is a quad
            if ((vc.cmd & 0x38) == 0x38) {
                num_vertexes = 4;
            } else {
                num_vertexes = 3;
            }
        }
        // This should be unreacheable
        else {
            return false;
        }

        // Correcting the seek position since we needed to read the vertex color ahead of time
        temp = racer_model.tellg();
        temp -= sizeof(vc);
        racer_model.seekg(temp, ios::beg);

        // Read the polygon and write it to the .obj
        tot_vertexes += num_vertexes;
        for (int i = 0; i < num_vertexes; i++) {
            racer_model.read((char *) &v, sizeof(v));
            output_file << "v "
                        << ((v.x + metadata[num_objects].trans_x) * -1) / 127.0 << " "
                        << ((v.y + metadata[num_objects].trans_y) * -1) / 127.0 << " "
                        << ((v.z + metadata[num_objects].trans_z) * -1) / 127.0 << " "
                        << v.vc.r / 255.0 << " " << v.vc.g / 255.0 << " " << v.vc.b / 255.0 << endl;
        }

        // Writing the face with its respective vertexes to the .obj
        output_file << "f";
        for (int j = num_vertexes - 1; j > -1; j--) {
            output_file << " " << tot_vertexes - j;
        }
        output_file << endl;
    }
}
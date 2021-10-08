#include <fstream>
#include "course.h"
#include "raw.h"
using namespace std;

int swap_endianess(int n) {
    return ((n & 0xFF) << 24) | (((n >> 8) & 0xFF) << 16) | (((n >> 16) & 0xFF) << 8) | ((n >> 24) & 0xFF);
}

void decompress_raw(fs::path mdl_path, fs::path output_path) {
    // Reading the raw file
    ifstream raw(mdl_path, ios::in | ios::binary | ios::ate);
    int file_size = raw.tellg();
    raw.seekg(0, ios::beg);

    // Storing the file in a buffer
    uint8_t * buffer = new uint8_t[file_size];
    raw.read((char *) buffer, file_size);
    int sections_found = 0;

    while (true) {
        // Decompressing the next section of the file
        int section_size = swap_endianess(*(int *) (buffer));
        if (section_size == -1) {
            break;
        }
        int compressed_size = swap_endianess(*(int *) (buffer + 4)) + 0xE;
        uint8_t * unpacked_section = new uint8_t[section_size];
        unpack_section(buffer, unpacked_section);

        // Saving the unpacked file
        string path = output_path.string() + "/RAW";
        if (sections_found < 10) {
            path += "0" + to_string(sections_found++);
        }
        else {
            path += to_string(sections_found++);
        }
        path += ".PART";
        ofstream output_file(path, ios::out | ios::binary);
        output_file.write((char *) unpacked_section, section_size);
        output_file.close();

        // Go to the next section and delete the old dynamic buffer to store the next unpacked section
        buffer += compressed_size;
        delete[] unpacked_section;
    }
}
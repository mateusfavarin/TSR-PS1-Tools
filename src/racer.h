#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

struct MODEL_HEADER {
    uint32_t size;
};

struct VERTEX_COLOR {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t cmd;
};

struct VERTEX {
    int16_t x;
    int16_t y;
    int16_t z;
    uint16_t palette;
};

struct MESH_HEADER {
    uint32_t mesh_count;
};

struct MESH_METADATA {
    uint32_t mesh_size;
    int32_t trans_x;
    int32_t trans_y;
    int32_t trans_z;
    uint32_t unknown[15];
};

void mdl_to_obj(fs::path mdl_path, fs::path output_path);
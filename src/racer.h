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

bool check_dir(fs::path game_folder);
void mdl_to_obj(fs::path mdl_path, fs::path output_path);
void extract_racer_models(fs::path game_folder, fs::path output_folder);
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int swap_endianess(int n);
void decompress_raw(fs::path mdl_path, fs::path output_path);
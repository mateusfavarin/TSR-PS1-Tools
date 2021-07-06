#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

bool check_directory(fs::path root, string folder_name);
void extract_folders(fs::path game_folder, fs::path output_root);
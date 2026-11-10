#include <vector>
#include <string>

using namespace std;

vector<string> read_file(string patch);
bool append_to_file(string path, string text);
bool overwrite_file(string path, string text);
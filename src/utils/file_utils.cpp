#include <vector>
#include <string>
#include <fstream>
#include "./file_utils.h"


using namespace std;

// ------------file ultilites------------
vector<string> read_file(string patch){
    ifstream file(patch);
    vector<string> lines;
    if (file.is_open()){
        string line;
        while (getline(file, line))
            lines.push_back(line);
};
    return lines;
}


bool append_to_file(string path, string text) {
    ofstream file(path, ios::app);
    if (file.is_open()) {
        file << text << endl; 
        file.close();
        return true; 
    }
    return false;
}



bool overwrite_file(string path, string text) {
    ofstream file(path); 
    if (file.is_open()) {
        file << text; 
        file.close();
        return true;
    }
    return false;
}
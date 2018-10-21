#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & v) {
  //s << "[";
  for (size_t i = 0; i < v.size(); i++) {
    if (i > 0) {
      s << "\n";
    }
    s << v[i];
  }
  //s << "]";
  return s;
}

vector<string> read_input(istream & in) {
  string line;
  vector<string> input;
  while (getline(in, line)) {
    input.push_back(line);
    line = line.erase();
  }
  return input;
}

int main(int argc, char * argv[]) {
  vector<string> lines;
  if (argc < 2) {
    lines = read_input(cin);
    sort(lines.begin(), lines.end());
    cout << lines << endl;
  }
  else {
    for (int i = 1; i < argc; i++) {
      ifstream file;
      file.open(argv[i], istream::in);
      if (!file.fail()) {
        lines = read_input(file);
        sort(lines.begin(), lines.end());
        cout << lines << endl;
      }
      else {
        cerr << "Can't open file" << endl;
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}

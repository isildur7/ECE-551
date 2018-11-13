#include <dirent.h>
#include <sys/types.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

std::vector<std::string> getFile(std::string path) {
  DIR * dir;
  struct dirent * dirf;
  char convPath[1024];
  std::vector<std::string> files;
  std::strcpy(convPath, path.c_str());
  if ((dir = opendir(convPath)) != NULL) {
    while ((dirf = readdir(dir)) != NULL) {
      if (dirf->d_type == DT_REG) {
        std::string name = path;
        if (*(name.end()) != '/') {
          name.append("/");
        }
        name.append(dirf->d_name);
        files.push_back(name);
      }
      else if (dirf->d_type == DT_DIR) {
        if (strcmp(dirf->d_name, "..") == 0 || strcmp(dirf->d_name, ".") == 0) {
          continue;
        }
        else {
          std::string name = path;
          if (*(name.end()) != '/') {
            name.append("/");
          }
          name.append(dirf->d_name);
          std::vector<std::string> inDir = getFile(name);
          files.insert(files.end(), inDir.begin(), inDir.end());
        }
      }
      else
        ;
    }
  }
  else {
    std::perror("Failed! ");
    exit(EXIT_FAILURE);
  }
  if (closedir(dir) != 0) {
    std::perror("Failed! ");
    exit(EXIT_FAILURE);
  }
  return files;
}

std::string read_input(std::istream & in) {
  std::string line;
  std::stringstream input;
  while (std::getline(in, line)) {
    input << line;
    line = line.erase();
  }
  return input.str();
}

void hashAndAddFiles(std::vector<std::string> files) {
  std::vector<std::string>::iterator ptr;
  std::unordered_map<std::string, std::string, std::hash<std::string> > map;
  for (ptr = files.begin(); ptr < files.end(); ++ptr) {
    std::ifstream input;
    input.open(*ptr, std::istream::in);
    if (!input.fail()) {
      std::string contents = read_input(input);
      std::unordered_map<std::string, std::string, std::hash<std::string> >::const_iterator got =
          map.find(contents);
      if (got == map.end()) {
        std::pair<std::string, std::string> newfile(contents, *ptr);
        map.insert(newfile);
      }
      else {
        std::cout << "#Removing " << *ptr << " (duplicate of";
        std::cout << (*got).second << ")." << std::endl;
        std::cout << "\nrm " << *ptr << std::endl;
      }
    }
    else {
      std::cerr << "Can't open file" << std::endl;
      exit(EXIT_FAILURE);
    }
    input.close();
    // if (input.fail()){
    //   std::cerr << "Error closing file\n";
    //   exit(EXIT_FAILURE);
    // }
  }
}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    std::cerr << "Not enough arguments\n";
    exit(EXIT_FAILURE);
  }
  std::cout << "#!/bin/bash\n";
  for (int i = 0; i < argc; i++) {
    std::vector<std::string> fileVec = getFile(argv[1]);
    hashAndAddFiles(fileVec);
  }
}

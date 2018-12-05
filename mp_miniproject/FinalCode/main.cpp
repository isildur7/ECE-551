#include "define.h"
#include "mcint.h"
#include "numint.h"
#include "parsing.h"
#include "test.h"

void deleteFuncmap(funcmap_t & funcmap) {
  // iteratively delete each allocated function
  for (funcmap_t::iterator it = funcmap.begin(); it != funcmap.end(); ++it) {
    delete (*it).second;
  }
}

int main(void) {
  std::string line;
  funcmap_t fmap;
  while (std::getline(std::cin, line)) {
    // ignore blank lines
    if (line.size() != 0) {
      line = removeExtraSpaces(line);
      // If the line is just comments, its size will be zero after this
      if (line.size() != 0) {
        if (!line.compare(0, 6, "define")) {
          line = line.substr(6);
          parse_define(line, fmap);
        }
        else if (!line.compare(0, 4, "test")) {
          line = line.substr(4);
          parse_test(line, fmap);
        }
        else if (!line.compare(0, 6, "numint")) {
          line = line.substr(6);
          parse_numint(line, fmap);
        }
        else if (!line.compare(0, 5, "mcint")) {
          line = line.substr(5);
          parse_mcint(line, fmap);
        }
        else {
          std::cerr << "Error: Unknown Command passed\n";
          std::cerr << "Available commands are define, test, numint, mcint\n";
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  deleteFuncmap(fmap);
}

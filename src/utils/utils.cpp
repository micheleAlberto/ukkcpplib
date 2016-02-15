#include "utils.hpp"
#include <stdlib.h>
int save(std::string name,std::string what){
  std::string dotFilename="graphs/"+name+".dot";
  std::string imageFilename="graphs/"+name+".jpg";
  std::ofstream myfile(dotFilename,std::ofstream::out);
  myfile<<what;
  myfile.close();
  std::string command="dot -Tpng:cairo -O "+dotFilename;
  return system(command.c_str());
};

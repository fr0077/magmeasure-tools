#include <iostream>
#include <cstdlib>
#include <fstream>
#include <boost/algorithm/string.hpp>

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cerr << "invalid number of arguments" << std::endl;
    exit(1);
  }

  std::ifstream ifs(argv[1]);
  if(ifs.fail()){
    std::cerr << "couldn't open file" << std::endl;
    exit(1);
  }

  std::string line;

  double oldAxis1 = 0;
  double oldAxis2 = 0;
  double oldAxis3 = 0;

  while(std::getline(ifs, line)){
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of("\t"));

    if(tokens.at(0) == "#"){
      if(tokens.at(1) == "1")
        oldAxis1 = 0;
      else if(tokens.at(1) == "2"){
        oldAxis2 = 0;
      }else if(tokens.at(1) == "3"){
        oldAxis3 = 0;
      }else{
        std::cerr << "Bad format" << std::endl;
        exit(1);
      }
      std::cout << line << std::endl;
    }else{
      double axis1 = std::stoi(tokens.at(0));
      double axis2 = std::stoi(tokens.at(1));
      double axis3 = std::stoi(tokens.at(2));
      std::cout << axis1 - oldAxis1 << '\t' << axis2 - oldAxis2 << '\t' << axis3 - oldAxis3 << '\t' << std::endl;
      oldAxis1 = axis1;
      oldAxis2 = axis2;
      oldAxis3 = axis3;
    }
  }

  return 0;
}

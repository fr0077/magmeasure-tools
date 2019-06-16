#include <iostream>
#include <cstdlib>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

template<typename T>
T getValue(std::string sessionName, std::string propertyName, boost::property_tree::ptree pt){
  if (boost::optional<T> value = pt.get_optional<T>(sessionName + "." + propertyName)) {
    return value.get();
  } else {
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cerr << "invalid number of arguments" << std::endl;
    exit(1);
  }

  std::string filename = std::string(argv[1]) + "_actmesh";
  std::ifstream ifs(filename.c_str());
  if(ifs.fail()){
    std::cerr << "couldn't open file" << std::endl;
    exit(1);
  }

  boost::property_tree::ptree pt;
  boost::property_tree::read_ini("sessions.ini", pt);

  double actuator_origin_x = getValue<double>(argv[1], "actuator_origin_override_X", pt);
  double actuator_origin_y = getValue<double>(argv[1], "actuator_origin_override_Y", pt);
  double actuator_origin_z = getValue<double>(argv[1], "actuator_origin_override_Z", pt);
  std::string axis_order = getValue<std::string>(argv[1], "axis_order", pt);

  std::map<std::string,double> axis_origin_map;

  if(axis_order == "xyz"){
    axis_origin_map["1"] = actuator_origin_x;
    axis_origin_map["2"] = actuator_origin_y;
    axis_origin_map["3"] = actuator_origin_z;
  }else if(axis_order == "xzy"){
    axis_origin_map["1"] = actuator_origin_x;
    axis_origin_map["2"] = actuator_origin_z;
    axis_origin_map["3"] = actuator_origin_y;
  }else if(axis_order == "yxz"){
    axis_origin_map["1"] = actuator_origin_y;
    axis_origin_map["2"] = actuator_origin_x;
    axis_origin_map["3"] = actuator_origin_z;
  }else if(axis_order == "yzx"){
    axis_origin_map["1"] = actuator_origin_y;
    axis_origin_map["2"] = actuator_origin_z;
    axis_origin_map["3"] = actuator_origin_x;
  }else if(axis_order == "zxy"){
    axis_origin_map["1"] = actuator_origin_z;
    axis_origin_map["2"] = actuator_origin_x;
    axis_origin_map["3"] = actuator_origin_y;
  }else if(axis_order == "zyx"){
    axis_origin_map["1"] = actuator_origin_z;
    axis_origin_map["2"] = actuator_origin_y;
    axis_origin_map["3"] = actuator_origin_x;
  }

  std::string line;

  double oldAxis1 = axis_origin_map["1"];
  double oldAxis2 = axis_origin_map["2"];
  double oldAxis3 = axis_origin_map["3"];

  while(std::getline(ifs, line)){
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of("\t"));

    if(tokens.at(0) == "#"){
      if(tokens.at(1) == "1")
        oldAxis1 = axis_origin_map["1"];
      else if(tokens.at(1) == "2"){
        oldAxis2 = axis_origin_map["2"];
      }else if(tokens.at(1) == "3"){
        oldAxis3 = axis_origin_map["3"];
      }else{
        std::cerr << "Bad format" << std::endl;
        exit(1);
      }
      std::cout << line << std::endl;
    }else{
      double axis1 = std::stoi(tokens.at(0));
      double axis2 = std::stoi(tokens.at(1));
      double axis3 = std::stoi(tokens.at(2));
      std::cout << axis1 - oldAxis1 << '\t' << axis2 - oldAxis2 << '\t' << axis3 - oldAxis3 << std::endl;
      oldAxis1 = axis1;
      oldAxis2 = axis2;
      oldAxis3 = axis3;
    }
  }

  return 0;
}

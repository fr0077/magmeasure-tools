#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "e42region.hpp"

int main(void)
{
  double axis1_min = -300;
  double axis2_min = -300;
  double axis3_min = -300;
  double axis1_max= 300;
  double axis2_max= 300;
  double axis3_max= 300;

  double axis1 = axis1_min;
  double axis2 = axis2_min;
  double axis3 = axis3_min;

  Region *region = new E42Region();

  while(axis1 <= axis1_max){
    while(axis2 <= axis2_max){
      while(axis3 <= axis3_max){
        if(region->isIncluded(axis1, axis2, axis3)){
          std::cout << axis1 << '\t' << axis2 << '\t' << axis3 << std::endl;
        }
        axis3 += 20;
      }
      //std::cout << '!' << std::endl;
      axis3 = axis3_min;
      axis2 += 20;
    }
    //std::cout << '@' << std::endl;
    axis2 = axis2_min;
    axis1 += 20;
  }

  return 0;
}


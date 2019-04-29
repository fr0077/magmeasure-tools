#include <iostream>
#include <cstdlib>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "e42region.hpp"

void getXYZ(double *x, double *y, double *z, double axis1, double axis2, double axis3){
  std::string axisOrder = "xyz";
  if(axisOrder == "xyz"){
    *x = axis1;
    *y = axis2;
    *z = axis3;
  }else if(axisOrder == "xzy"){
    *x = axis1;
    *y = axis3;
    *z = axis2;
  }else if(axisOrder == "yxz"){
    *x = axis2;
    *y = axis1;
    *z = axis3;
  }else if(axisOrder == "yzx"){
    *x = axis3;
    *y = axis1;
    *z = axis2;
  }else if(axisOrder == "zxy"){
    *x = axis2;
    *y = axis3;
    *z = axis1;
  }else if(axisOrder == "zyx"){
    *x = axis3;
    *y = axis2;
    *z = axis1;
  }else{
    std::cerr << "Invalid axis order" << std::endl;
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cerr << "Invalid number of arguments" << std::endl;
    return 1;
  }

  //1 -> 磁石座標系を出力
  //2 -> ステージ座標を出力
  int flag_stage_coordinate = std::atoi(argv[1]);

  if(flag_stage_coordinate != 1 && flag_stage_coordinate != 2){
    std::cerr << "Invalid flag_stage_coordinate" << std::endl;
    return 1;
  }


  double stage_axis1_zero = -300;
  double stage_axis2_zero = -300;
  double stage_axis3_zero = -300;

  if(flag_stage_coordinate == 1){
    stage_axis1_zero = 0;
    stage_axis2_zero = 0;
    stage_axis3_zero = 0;
  }

  double axis1_min = -300;
  double axis2_min = -300;
  double axis3_min = -300;
  double axis1_max= 300;
  double axis2_max= 300;
  double axis3_max= 300;

  if(flag_stage_coordinate == 2){
    axis1_min -= stage_axis1_zero;
    axis2_min -= stage_axis2_zero;
    axis3_min -= stage_axis3_zero;
    axis1_max -= stage_axis1_zero;
    axis2_max -= stage_axis2_zero;
    axis3_max -= stage_axis3_zero;
  }

  double daxis1 = 50;
  double daxis2 = 50;
  double daxis3 = 50;

  double axis1 = axis1_min;
  double axis2 = axis2_min;
  double axis3 = axis3_min;

  Region *region = new E42Region();
  std::cout << "# axis1" << std::endl;
  std::cout << "# axis2" << std::endl;
  std::cout << "# axis3" << std::endl;

  while(axis3 <= axis3_max){
    while(axis2 <= axis2_max){
      while(axis1 <= axis1_max){
        double x,y,z;
        getXYZ(&x, &y, &z, axis1 + stage_axis1_zero, axis2 + stage_axis2_zero, axis3 + stage_axis3_zero);
        if(region->isIncluded(x,y,z)){
          std::cout << axis1 << '\t' << axis2 << '\t' << axis3 << std::endl;
        }
        axis1 += daxis1;
      }
      std::cout << "# axis1" << std::endl;

      axis1 = axis1_min;
      axis2 += daxis2;
    }
    std::cout << "# axis2" << std::endl;

    axis2 = axis2_min;
    axis3 += daxis3;
  }

  return 0;
}

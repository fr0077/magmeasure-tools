#include <iostream>
#include <cstdlib>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "fmregion.hpp"

void getXYZ(double *x, double *y, double *z, double axis1, double axis2, double axis3, std::string axisOrder){
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

  if(argc != 3){
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

  //セッション名
  std::string session_name = std::string(argv[2]);

  boost::property_tree::ptree pt;
  boost::property_tree::read_ini("sessions.ini", pt);
  std::string axisOrder = pt.get<std::string>(session_name + ".axis_order");

  double stage_axis1_zero;
  double stage_axis2_zero;
  double stage_axis3_zero;
  double stage_x_zero = pt.get<int>(session_name + ".actuator_origin_x");
  double stage_y_zero = pt.get<int>(session_name + ".actuator_origin_y");
  double stage_z_zero = pt.get<int>(session_name + ".actuator_origin_z");


  double axis1_min;
  double axis2_min;
  double axis3_min;
  double axis1_max;
  double axis2_max;
  double axis3_max;
  double xmin = pt.get<int>(session_name + ".xmin");
  double ymin = pt.get<int>(session_name + ".ymin");
  double zmin = pt.get<int>(session_name + ".zmin");
  double xmax = pt.get<int>(session_name + ".xmax");
  double ymax = pt.get<int>(session_name + ".ymax");
  double zmax = pt.get<int>(session_name + ".zmax");
  double daxis1;
  double daxis2;
  double daxis3;
  double dx, dy, dz;
  double x = xmin;
  double y = ymin;
  double z = zmin;
  double axis1;
  double axis2;
  double axis3;

  dx = pt.get<double>(session_name + ".deltax");
  dy = pt.get<double>(session_name + ".deltay");
  dz = pt.get<double>(session_name + ".deltaz");

  std::string actuator_sign_x = pt.get<std::string>(session_name + ".actuator_sign_x");
  std::string actuator_sign_y = pt.get<std::string>(session_name + ".actuator_sign_y");
  std::string actuator_sign_z = pt.get<std::string>(session_name + ".actuator_sign_z");
  std::string axis1_sign;
  std::string axis2_sign;
  std::string axis3_sign;

  if(actuator_sign_x == "-"){
    x = xmax;
    dx = -dx;
  }
  if(actuator_sign_y == "-"){
    y = ymax;
    dy = -dy;
  }
  if(actuator_sign_z == "-"){
    z = zmax;
    dz = -dz;
  }

  if(axisOrder == "xyz"){
    axis1 = x;
    axis2 = y;
    axis3 = z;
    axis1_min = xmin;
    axis2_min = ymin;
    axis3_min = zmin;
    axis1_max = xmax;
    axis2_max = ymax;
    axis3_max = zmax;
    daxis1 = dx;
    daxis2 = dy;
    daxis3 = dz;
    axis1_sign = actuator_sign_x;
    axis2_sign = actuator_sign_y;
    axis3_sign = actuator_sign_z;
    stage_axis1_zero = stage_x_zero;
    stage_axis2_zero = stage_y_zero;
    stage_axis3_zero = stage_z_zero;
  }else if(axisOrder == "xzy"){
    axis1 = x;
    axis2 = z;
    axis3 = y;
    axis1_min = xmin;
    axis2_min = zmin;
    axis3_min = ymin;
    axis1_max = xmax;
    axis2_max = zmax;
    axis3_max = ymax;
    daxis1 = dx;
    daxis2 = dz;
    daxis3 = dy;
    axis1_sign = actuator_sign_x;
    axis2_sign = actuator_sign_z;
    axis3_sign = actuator_sign_y;
    stage_axis1_zero = stage_x_zero;
    stage_axis2_zero = stage_z_zero;
    stage_axis3_zero = stage_y_zero;
  }else if(axisOrder == "yxz"){
    axis1 = y;
    axis2 = x;
    axis3 = z;
    axis1_min = ymin;
    axis2_min = xmin;
    axis3_min = zmin;
    axis1_max = ymax;
    axis2_max = xmax;
    axis3_max = zmax;
    daxis1 = dy;
    daxis2 = dx;
    daxis3 = dz;
    axis1_sign = actuator_sign_y;
    axis2_sign = actuator_sign_x;
    axis3_sign = actuator_sign_z;
    stage_axis1_zero = stage_y_zero;
    stage_axis2_zero = stage_x_zero;
    stage_axis3_zero = stage_z_zero;
  }else if(axisOrder == "yzx"){
    axis1 = y;
    axis2 = z;
    axis3 = x;
    axis1_min = ymin;
    axis2_min = zmin;
    axis3_min = xmin;
    axis1_max = ymax;
    axis2_max = zmax;
    axis3_max = xmax;
    daxis1 = dy;
    daxis2 = dz;
    daxis3 = dx;
    axis1_sign = actuator_sign_y;
    axis2_sign = actuator_sign_z;
    axis3_sign = actuator_sign_x;
    stage_axis1_zero = stage_y_zero;
    stage_axis2_zero = stage_z_zero;
    stage_axis3_zero = stage_x_zero;
  }else if(axisOrder == "zxy"){
    axis1 = z;
    axis2 = x;
    axis3 = y;
    axis1_min = zmin;
    axis2_min = xmin;
    axis3_min = ymin;
    axis1_max = zmax;
    axis2_max = xmax;
    axis3_max = ymax;
    daxis1 = dz;
    daxis2 = dx;
    daxis3 = dy;
    axis1_sign = actuator_sign_z;
    axis2_sign = actuator_sign_x;
    axis3_sign = actuator_sign_y;
    stage_axis1_zero = stage_z_zero;
    stage_axis2_zero = stage_x_zero;
    stage_axis3_zero = stage_y_zero;
  }else if(axisOrder == "zyx"){
    axis1 = z;
    axis2 = y;
    axis3 = x;
    axis1_min = zmin;
    axis2_min = ymin;
    axis3_min = xmin;
    axis1_max = zmax;
    axis2_max = ymax;
    axis3_max = zmax;
    daxis1 = dz;
    daxis2 = dy;
    daxis3 = dx;
    axis1_sign = actuator_sign_z;
    axis2_sign = actuator_sign_y;
    axis3_sign = actuator_sign_x;
    stage_axis1_zero = stage_z_zero;
    stage_axis2_zero = stage_y_zero;
    stage_axis3_zero = stage_x_zero;
  }else{
    exit(1);
  }

  if(flag_stage_coordinate == 1){
    stage_axis1_zero = 0;
    stage_axis2_zero = 0;
    stage_axis3_zero = 0;
  }

  Region *region = new FMRegion();
  std::cout << "#\t1" << std::endl;
  std::cout << "#\t2" << std::endl;
  std::cout << "#\t3" << std::endl;

  while(axis3_min <= axis3 && axis3 <= axis3_max){
    while(axis2_min <= axis2 && axis2 <= axis2_max){
      while(axis1_min <= axis1 && axis1 <= axis1_max){
        double tempx, tempy, tempz;
        getXYZ(&tempx, &tempy, &tempz, axis1, axis2, axis3, axisOrder);
        if(region->isIncluded(tempx,tempy,tempz)){
          if(flag_stage_coordinate == 2){
            double act_3, act_2, act_1;
            act_1 = axis1 - stage_axis1_zero;
            act_2 = axis2 - stage_axis2_zero;
            act_3 = axis3 - stage_axis3_zero;

            if(axis1_sign == "-")
              act_1 = -act_1;
            if(axis2_sign == "-")
              act_2 = -act_2;
            if(axis3_sign == "-")
              act_3 = -act_3;

            std::cout << act_1 << '\t' << act_2 << '\t' << act_3 << std::endl;
          }else{
            std::cout << axis1 << '\t' << axis2 << '\t' << axis3 << std::endl;
          }
        }
        axis1 += daxis1;
      }
      std::cout << "#\t1" << std::endl;

      if(axis1_sign == "+")
        axis1 = axis1_min;
      else
        axis1 = axis1_max;

      axis2 += daxis2;
    }
    std::cout << "#\t2" << std::endl;

    if(axis2_sign == "+")
      axis2 = axis2_min;
    else
      axis2 = axis2_max;

    axis3 += daxis3;
  }
}

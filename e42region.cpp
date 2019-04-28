#include "e42region.hpp"
#include <cmath>

bool E42Region::isIncluded(double x, double y, double z){
  double r = sqrt(pow(x-300,2) + pow(y-300,2));
  return r <= 300 && -300 <= z && z <= 300;
}

bool E42Region::isFine(double x, double y, double z){
  return false;
}

int E42Region::fineFactor(){
  return 2;
}

E42Region::~E42Region(){}

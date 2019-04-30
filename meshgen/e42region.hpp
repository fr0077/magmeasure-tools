#include <cmath>
#include "region.hpp"

class E42Region : public Region
{
  bool isIncluded(double x, double y, double z){
    double r = sqrt(pow(x,2) + pow(y,2));
    return r <= 300 && -300 <= z && z <= 300;
  }

  ~E42Region(){}
};

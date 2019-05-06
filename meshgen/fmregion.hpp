#include <cmath>
#include "region.hpp"

class FMRegion : public Region
{
  public:
    bool isIncluded(double x, double y, double z){
      double r = sqrt(pow(x,2) + pow(z,2));
      return r <= 700 && -700 <= y && y <= 700 && !isColide(x,y,z) && !isCut(x,y,z) && !isHidden(x,y,z);
    }

  private:
    bool isColide(double x, double y, double z){
      if(fabs(y) > sqrt(pow(z,2) + pow(x,2)) && fabs(y) > 200)
        return true;
      else
        return false;
    }

    bool isCut(double x, double y, double z){
      if(z < -200 && x < -z && x > z){
        return true;
      }else{
        return false;
      }
    }

    bool isHidden(double x, double y, double z){
      if((y > x || y < -x) && z < 0 && abs(y) > 200)
        return true;
      else
        return false;
    }

    ~FMRegion(){}
};

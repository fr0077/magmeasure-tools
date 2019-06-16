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
    const double offset_up = 70;
    const double offset_down = 70;

    bool isColide(double x, double y, double z){
      double r = sqrt(pow(z,2) + pow(x,2));

      if(y >= 0){
        if(r <= y + offset_up * sqrt(2) && y >= 200 - offset_up)
          return true;
      }else{
        if(r <= fabs(y - offset_down * sqrt(2)) && y <= -200 + offset_down)
          return true;
      }
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
      if(y >= 0){
        if(y - offset_up * sqrt(2) >= fabs(x) && y > 200 - offset_up && z < 0)
          return true;
      }else{
        if(y - offset_down * sqrt(2) <= -fabs(x) && y <= -200 + offset_down && z < 0)
          return true;
      }
      return false;
    }

    ~FMRegion(){}
};

#include "region.hpp"

class E42Region : public Region
{
  public:
    bool isFine(double, double, double);
    bool isIncluded(double,double,double);
    int fineFactor();
    ~E42Region();
};

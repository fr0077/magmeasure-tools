#ifndef REGION
#define REGION

class Region{
  public:
    //測定領域に含まれるならtrue, 含まれないならfalse
    //座標は磁石系
    virtual bool isIncluded(double x, double y, double z) = 0;
};

#endif

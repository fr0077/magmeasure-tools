#ifndef REGION
#define REGION

class Region{
  public:
    //測定領域に含まれるならtrue, 含まれないならfalse
    virtual bool isIncluded(double x, double y, double z) = 0;

    //倍精度で測る領域ならtrue, そうでないならfalse
    virtual bool isFine(double x, double y, double z) = 0;

    //fine領域を何倍の精度で測るか
    virtual int fineFactor() = 0;
};

#endif

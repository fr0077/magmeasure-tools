#include "region.hpp"

class E42Region : public Region
{
  public:
    //未実装。常にTrueを返す
    bool isFine(double, double, double);

    //x,y,z(測定点の座標。アクチュエーター座標ではない）を受け取り、それが測定領域に含まれるならtrue, 含まれないならfalseを返す
    bool isIncluded(double,double,double);

    //未実装。常に2を返す
    int fineFactor();

    ~E42Region();
};

#include <iostream>
#include <Eigen/Eigen>


class Joint
{
public:
Joint();
Joint(double length_rigid1,double length_rigid2,double length_continuum);
double getLengthRigid1();
double getLengthRigid2();
double getLengthContinuum();
Eigen::Matrix4d getTransform();
private:
double length_rigid1,length_rigid2,length_continuum;
Eigen::Matrix4d transform;

};

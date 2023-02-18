#include <LEigenQP_CPP/Core.hpp>
#include <iostream>
int main()
{
    lee::eigen_qp::LEigenQP<2> qp(2);
    qp.A << 1,0,0,1;
    qp.b << 2,2;
    qp.updateHf();
    auto res = qp.getResult();
    res = qp.getResult();
    std::cout<<res<<", "<<qp.x.transpose()<<std::endl;
    return 0;
}
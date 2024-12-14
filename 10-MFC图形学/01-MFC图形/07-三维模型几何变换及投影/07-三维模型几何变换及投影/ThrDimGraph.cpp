#include"stdafx.h"
#include"ThrDimGraph.h"
void GraphMulVaryMatrix(double * x,double * y,double * z,double matrix[][4])
{
    double vec[4]= {*x,*y,*z,1.0};
    *x=0,*y=0,*z=0;
    for(int i=0; i<4; i++)
    {
        *x+=matrix[i][0]*vec[i];
        *y+=matrix[i][1]*vec[i];
        *z+=matrix[i][2]*vec[i];
    }
}

void GraphMove(double * x,double * y,double * z,double mx,double my,double mz)
{
    double matrix[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,1,0},{mx,my,mz,1}};
    GraphMulVaryMatrix(x,y,z,matrix);
}

void GraphScale(double * x,double * y,double * z,double sx,double sy,double sz)
{
    double matrix[4][4]= {{sx,0,0,0},{0,sy,0,0},{0,0,sz,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrix);
}

void GraphSpin(double * x,double * y,double * z,double sx,double sy,double sz)
{
    double matrixX[4][4]= {{1,0,0,0},{0,cos(sx),sin(sx),0},{0,-sin(sx),cos(sx),0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixX);
    double matrixY[4][4]= {{cos(sy),0,-sin(sy),0},{0,1,0,0},{sin(sy),0,cos(sy),0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixY);
    double matrixZ[4][4]= {{cos(sz),sin(sz),0,0},{-sin(sz),cos(sz),0,0},{0,0,1,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixZ);
}

void GraphReflact(double * x,double * y,double * z,bool bx,bool by,bool bz)
{
    if(bx)
    {
        double matrixX[4][4]= {{1,0,0,0},{0,-1,0,0},{0,0,-1,0},{0,0,0,1}};
        GraphMulVaryMatrix(x,y,z,matrixX);
    }
    if(by)
    {
        double matrixY[4][4]= {{-1,0,0,0},{0,1,0,0},{0,0,-1,0},{0,0,0,1}};
        GraphMulVaryMatrix(x,y,z,matrixY);
    }
    if(bz)
    {
        double matrixZ[4][4]= {{-1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,0,0,1}};
        GraphMulVaryMatrix(x,y,z,matrixZ);
    }
}
void GraphFlatReflact(double * x,double * y,double * z,bool bxoy,bool byoz,bool bxoz)
{
    if(bxoy)
    {
        double matrixX[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,-1,0},{0,0,0,1}};
        GraphMulVaryMatrix(x,y,z,matrixX);
    }
    if(byoz)
    {
        double matrixY[4][4]= {{-1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
        GraphMulVaryMatrix(x,y,z,matrixY);
    }
    if(bxoz)
    {
        double matrixZ[4][4]= {{1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,0,0,1}};
        GraphMulVaryMatrix(x,y,z,matrixZ);
    }
}
void GraphMiscut(double * x,double * y,double * z,double xgz,double xdy,double yhz,double ybx,double zfy,double zcx)
{
    double matrixX[4][4]= {{1,0,0,0},{xdy,1,0,0},{xgz,0,1,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixX);
    double matrixY[4][4]= {{1,ybx,0,0},{0,1,0,0},{0,yhz,1,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixY);
    double matrixZ[4][4]= {{1,0,zcx,0},{0,1,zfy,0},{0,0,1,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixZ);
}

void OrgMove(double * x,double * y,double * z,double mx,double my,double mz)
{
    double matrix[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,1,0},{-mx,-my,-mz,1}};
    GraphMulVaryMatrix(x,y,z,matrix);
}
void OrgSpin(double * x,double * y,double * z,double sx,double sy,double sz)
{
     double matrixX[4][4]= {{1,0,0,0},{0,cos(sx),-sin(sx),0},{0,sin(sx),cos(sx),0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixX);
    double matrixY[4][4]= {{cos(sy),0,sin(sy),0},{0,1,0,0},{-sin(sy),0,cos(sy),0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixY);
    double matrixZ[4][4]= {{cos(sz),-sin(sz),0,0},{sin(sz),cos(sz),0,0},{0,0,1,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixZ);
}
void OrgReflact(double * x,double * y,double * z,bool bx,bool by,bool bz)
{
    GraphReflact(x,y,z,bx,by,bz);
}
void OrgFlatReflact(double * x,double * y,double * z,bool bxoy,bool byoz,bool bxoz)
{
    GraphFlatReflact(x,y,z,bxoy,byoz,bxoz);
}

void ProjOrthogonal(double * x,double * y,double * z)
{
    *z=0;
    //double matrixX[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,0,0},{0,0,0,1}};
    //GraphMulVaryMatrix(x,y,z,matrixX);
}
void ProjMainView(double * x,double * y,double * z)
{
    double matrixX[4][4]= {{0,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}
void ProjSideView(double * x,double * y,double * z)
{
   double matrixX[4][4]= {{0,0,-1,0},{0,1,0,0},{0,0,0,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}
void ProjTopView(double * x,double * y,double * z)
{
    double matrixX[4][4]= {{0,-1,0,0},{0,0,0,0},{0,0,1,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}
void ProjOblique(double * x,double * y,double * z,double a,double b)
{
    double matrixX[4][4]= {{1,0,0,0},{0,1,0,0},{1.0/(-tan(a))*cos(b),1.0/(-tan(a))*sin(b),0,0},{0,0,0,1}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}

void ProjWorldOrgToViewOrg(double * x,double * y,double * z,double R,double a,double b)
{
    double matrixX[4][4]= {{cos(a),-cos(b)*sin(a),-sin(b)*sin(a),0},{0,sin(b),-cos(b),0},{-sin(a),-cos(b)*cos(a),-sin(b)*cos(a),0},{0,0,R,1}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}
void ProjViewOrgToScreenOrg(double * x,double * y,double * z,double d)
{
    double matrixX[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,0,1.0/d},{0,0,0,0}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}
void ProjWorldOrgToScreenOrg(double * x,double * y,double * z,double R,double d,double a,double b)
{
    double matrixX[4][4]= {{cos(a),-cos(b)*sin(a),0,-sin(b)*sin(a)/d},{0,sin(b),0,-cos(b)/d},{-sin(a),-cos(b)*cos(a),0,-sin(b)*cos(a)/d},{0,0,0,R/d}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}

void ProjOnePoint(double * x,double * y,double * z,double R,double d)
{
    double matrixX[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,0,-1.0/d},{0,0,0,R/d}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}
void ProjTwoPoint(double * x,double * y,double * z,double R,double d)
{
    double sq2=sqrt(2.0);
    double matrixX[4][4]= {{sq2/2,0,0,-sq2/(2*d)},{0,1,0,0},{-sq2/2,0,0,-sq2/(2*d)},{0,0,0,R/d}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}
void ProjThreePoint(double * x,double * y,double * z,double R,double d)
{
    double sq2=sqrt(2.0);
    double matrixX[4][4]= {{sq2/2,-1.0/2,0,-1.0/(2*d)},{0,sq2/2,0,-sq2/(2*d)},{-sq2/2,-1.0/2,0,-1.0/(2*d)},{0,0,0,R/d}};
    GraphMulVaryMatrix(x,y,z,matrixX);
}

void ProjViewOrgToDeepScreenD3Org(double * x,double * y,double * z,double d,double Near,double Far)
{
    double rx=d*(*x)/(*z);
    double ry=d*(*y)/(*z);
    double rz=Far*(1.0-Near/(*z))/(Far-Near);
    *x=rx;
    *y=ry;
    *z=rz;
}

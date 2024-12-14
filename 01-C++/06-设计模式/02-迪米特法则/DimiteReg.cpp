#include<iostream>
#include<vector>
#include<string>
#include<iterator>
using namespace std;
/*
������ԭ��
�ֽ�����֪ʶ��ԭ�򣬱�¶���ⲿ�Ľӿ�Խ��Խ��
����ʹ���м��˵�ģʽ���н��ӿڼ򻯣����ٽӿڵı�¶
*/
class AbstractBuilding
{
public:
    virtual void sale()=0;
    virtual string getQuality()=0;
};
class BuildingA : public AbstractBuilding
{
public:
    virtual void sale()
    {
        cout << "BuildingA be sale." <<endl;
    }
    virtual string getQuality()
    {
        return "height";
    }
};
class BuildingB : public AbstractBuilding
{
public:
    virtual void sale()
    {
        cout << "BuildingB be sale." <<endl;
    }
    virtual string getQuality()
    {
        return "low";
    }
};
class Medianer
{
public:
    Medianer()
    {
        mBuilding.push_back(new BuildingA());
        mBuilding.push_back(new BuildingB());
    }
    ~Medianer()
    {
        for(vector<AbstractBuilding*>::iterator it=mBuilding.begin();it!=mBuilding.end();it++)
        {
            if(*it!=NULL)
                delete *it;
        }
    }
    AbstractBuilding* getCustomBuilding(string qulity)
    {
        for(vector<AbstractBuilding*>::iterator it=mBuilding.begin();it!=mBuilding.end();it++)
        {
            if((*it)->getQuality()==qulity)
                return *it;
        }
        return NULL;
    }
private:
    vector<AbstractBuilding*> mBuilding;
};
void test()
{
    Medianer * med=new Medianer();
    AbstractBuilding* bld=med->getCustomBuilding("height");
    if(bld)
        bld->sale();
    else
        cout << "Not Found this Building"<<endl;
}
int main()
{
    test();
    return 0;
}

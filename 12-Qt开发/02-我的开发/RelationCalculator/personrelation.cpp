#include "personrelation.h"
QString RelationNode::getIndexName(RelationIndex index)
{
    static QString names[]={"父亲","母亲","哥哥","弟弟","姐姐","妹妹","儿子","女儿","老公","老婆","义父","义母","义子","义女"};
    return names[(int)(index)];
}
RelationNode * RelationNode::buildNode(QString nodeName,
                                   QString fuQinName,QString muQinName,
                                   QString laoGongName,QString laoPoName,
                                   QString erZiName,QString nvErName,
                                   QString geGeName,QString diDiName,
                                   QString jieJieName,QString meiMeiName,
                                   QString yiFuName,QString yiMuName,
                                   QString yiZiName,QString yiNvName
                                   )
{
    RelationNode * node=new RelationNode(nodeName);
    node->setNotes(fuQinName,muQinName,
                   laoGongName,laoPoName,
                   erZiName,nvErName,
                   geGeName,diDiName,
                   jieJieName,meiMeiName,
                   yiFuName,yiMuName,
                   yiZiName,yiNvName);
    return node;
}
void RelationNode::setNotes(
              QString fuQinName,QString muQinName,
              QString laoGongName,QString laoPoName,
              QString erZiName,QString nvErName,
              QString geGeName,QString diDiName,
              QString jieJieName,QString meiMeiName,
              QString yiFuName,QString yiMuName,
              QString yiZiName,QString yiNvName
              )
{
    if(fuQinName!="")
        this->setRelationValue(RelationNode::FuQin,new RelationNode(fuQinName));
    if(muQinName!="")
        this->setRelationValue(RelationNode::MuQin,new RelationNode(muQinName));
    if(laoGongName!="")
        this->setRelationValue(RelationNode::LaoGong,new RelationNode(laoGongName));
    if(laoPoName!="")
        this->setRelationValue(RelationNode::LaoPo,new RelationNode(laoPoName));
    if(erZiName!="")
        this->setRelationValue(RelationNode::ErZi,new RelationNode(erZiName));
    if(nvErName!="")
        this->setRelationValue(RelationNode::NvEr,new RelationNode(nvErName));
    if(geGeName!="")
        this->setRelationValue(RelationNode::GeGe,new RelationNode(geGeName));
    if(diDiName!="")
        this->setRelationValue(RelationNode::DiDi,new RelationNode(diDiName));
    if(jieJieName!="")
        this->setRelationValue(RelationNode::JieJie,new RelationNode(jieJieName));
    if(meiMeiName!="")
        this->setRelationValue(RelationNode::MeiMei,new RelationNode(meiMeiName));
    if(yiFuName!="")
        this->setRelationValue(RelationNode::YiFu,new RelationNode(yiFuName));
    if(yiMuName!="")
        this->setRelationValue(RelationNode::YiMu,new RelationNode(yiMuName));
    if(yiZiName!="")
        this->setRelationValue(RelationNode::YiZi,new RelationNode(yiZiName));
    if(yiNvName!="")
        this->setRelationValue(RelationNode::YiNv,new RelationNode(yiNvName));

}
void RelationNode::setNotes(RelationNode * fuQin,RelationNode * muQin,
              RelationNode * laoGong,RelationNode * laoPo,
              RelationNode * erZi,RelationNode * nvEr,
              RelationNode * geGe,RelationNode * diDi,
              RelationNode * jieJie,RelationNode * meiMei,
              RelationNode * yiFu,RelationNode * yiMu,
              RelationNode * yiZi,RelationNode * yiNv
              )
{
    if(fuQin!=NULL)
        this->setRelationValue(RelationNode::FuQin,fuQin);
    if(muQin!=NULL)
        this->setRelationValue(RelationNode::MuQin,muQin);
    if(laoGong!=NULL)
        this->setRelationValue(RelationNode::LaoGong,laoGong);
    if(laoPo!=NULL)
        this->setRelationValue(RelationNode::LaoPo,laoPo);
    if(erZi!=NULL)
        this->setRelationValue(RelationNode::ErZi,erZi);
    if(nvEr!=NULL)
        this->setRelationValue(RelationNode::NvEr,nvEr);
    if(geGe!=NULL)
        this->setRelationValue(RelationNode::GeGe,geGe);
    if(diDi!=NULL)
        this->setRelationValue(RelationNode::DiDi,diDi);
    if(jieJie!=NULL)
        this->setRelationValue(RelationNode::JieJie,jieJie);
    if(meiMei!=NULL)
        this->setRelationValue(RelationNode::MeiMei,meiMei);
    if(yiFu!=NULL)
        this->setRelationValue(RelationNode::YiFu,yiFu);
    if(yiMu!=NULL)
        this->setRelationValue(RelationNode::YiMu,yiMu);
    if(yiZi!=NULL)
        this->setRelationValue(RelationNode::YiZi,yiZi);
    if(yiNv!=NULL)
        this->setRelationValue(RelationNode::YiNv,yiNv);
}

RelationNode::RelationNode()
{
    initConstruct();
}

RelationNode::RelationNode(QString name)
{
    initConstruct();
    m_name=name;
}

RelationNode::RelationNode(const RelationNode & pr)
{
    this->endDistruct();
    m_name=pr.m_name;
    for(int i=0;i<MAX_RELATION_COUNT;i++)
    {
        RelationNode * node=new RelationNode();
        node->m_name=pr.m_name;
        for(int j=0;j<MAX_RELATION_COUNT;j++)
        {
            node->m_relationMap[j]=pr.m_relationMap[j];
        }
        m_relationMap[i]=node;
    }
}

RelationNode RelationNode::operator=(const RelationNode & pr)
{
    this->endDistruct();
    m_name=pr.m_name;
    for(int i=0;i<MAX_RELATION_COUNT;i++)
    {
        RelationNode * node=new RelationNode();
        node->m_name=pr.m_name;
        for(int j=0;j<MAX_RELATION_COUNT;j++)
        {
            node->m_relationMap[j]=pr.m_relationMap[j];
        }
        m_relationMap[i]=node;
    }
}

void RelationNode::initConstruct()
{
    m_name="未知称呼";
     for(int i=0;i<MAX_RELATION_COUNT;i++)
     {
         m_relationMap[i]=NULL;
     }
}

void RelationNode::endDistruct()
{
    m_name="未知称呼";
     for(int i=0;i<MAX_RELATION_COUNT;i++)
     {
         if(m_relationMap[i]!=NULL)
         {
             delete m_relationMap[i];
             m_relationMap[i]=NULL;
         }
     }
}

RelationNode::~RelationNode()
{
    endDistruct();
}

void RelationNode::setName(QString name)
{
    m_name=name;
}

QString RelationNode::getName()
{
    return m_name;
}

RelationNode & RelationNode::setRelationValue(RelationIndex index,const RelationNode * pr)
{
    removeRelationValue(index);
    int in=(int)index;
    m_relationMap[in]=const_cast<RelationNode *>(pr);
    return *this;
}

RelationNode * RelationNode::getRelationValue(RelationIndex index)
{
    int in=(int)index;
    return m_relationMap[in];
}
bool RelationNode::removeRelationValue(RelationIndex index)
{
    int in=(int)index;
    if(m_relationMap[in]!=NULL)
    {
        delete m_relationMap[in];
        m_relationMap[in]=NULL;
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////


PersonRelation::PersonRelation()
{
    initConstruct();
}

PersonRelation::~PersonRelation()
{
    endDistruct();
}
RelationNode * PersonRelation::getMe()
{
    return m_rootRel;
}

QString PersonRelation::routeRelation(QList<RelationNode::RelationIndex> list)
{
    bool mixRelate=false;
    int Level=0;
    RelationNode * preNode=m_rootRel;
    int index=0;
    while(index<list.length())
    {
        switch(list.at(index))
        {
        case RelationNode::FuQin:
        case RelationNode::MuQin:
        case RelationNode::YiFu:
        case RelationNode::YiMu:
            Level++;
            break;
        case RelationNode::ErZi:
        case RelationNode::NvEr:
        case RelationNode::YiZi:
        case RelationNode::YiNv:
            Level--;
            break;
        case RelationNode::LaoGong:
        case RelationNode::LaoPo:
        case RelationNode::GeGe:
        case RelationNode::DiDi:
        case RelationNode::JieJie:
        case RelationNode::MeiMei:
            break;
        }
        if(index>0)
        {
            if(list.at(index-1)==RelationNode::LaoPo && list.at(index)==RelationNode::LaoPo
                    ||list.at(index-1)==RelationNode::LaoGong && list.at(index)==RelationNode::LaoGong)
            {
                mixRelate=true;
            }
        }
        if(preNode!=NULL)
            preNode=preNode->getRelationValue(list.at(index));
        index++;
    }
    static int beifenCode[]={-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,-999};
    static QString beifen[]={"耳孙","云孙","仍孙","晜孙","来孙","玄孙","曾孙/曾孙女","孙/孙女","侄甥/子女","兄弟姊妹","叔伯姑婶/父母","爷爷奶奶/祖","老祖/曾祖","老天天/高祖","天祖","烈祖","太祖","远祖","鼻祖"};

    QString str="超过十八代了！！";
    if(preNode!=NULL)
    {
        str=preNode->getName();
    }
    else
    {
        int i=0;
        while(beifenCode[i]!=-999)
        {
            if(beifenCode[i]==Level)
            {
                str=beifen[i];
                break;
            }
            i++;
        }
    }
    if(mixRelate)
        str+="（关系可能混乱）";
    return str;
}

void PersonRelation::initConstruct()
{
    //我的直接关系
    m_rootRel=RelationNode::buildNode("我",
                                      "父亲/爸爸","母亲/妈妈",
                                      "老公","老婆",
                                      "儿子","女儿",
                                      "哥哥","弟弟",
                                      "姐姐","妹妹",
                                      "义父","义母",
                                      "义子","义女");
    RelationNode * me=m_rootRel;


    //父亲的直接关系
    RelationNode * node=m_rootRel->getRelationValue(RelationNode::FuQin);
    node->setNotes("祖父/爷爷","祖母/奶奶",
                   "","",
                   "","",
                   "伯伯","叔叔",
                   "姑姑","姑姑");
    RelationNode * baba=node;

    //母亲的直接关系
    node=m_rootRel->getRelationValue(RelationNode::MuQin);
    node->setNotes("外祖父/外公/姥爷","外祖母/外婆/姥姥",
                   "","",
                   "","",
                   "舅舅","舅舅",
                   "姨妈","姨妈");
    RelationNode * mama=node;
    //父亲母亲夫妻关系
    baba->setRelationValue(RelationNode::LaoPo,mama);
    mama->setRelationValue(RelationNode::LaoGong,baba);

    //老婆的直接关系
    node=m_rootRel->getRelationValue(RelationNode::LaoPo);
    node->setNotes("岳父/老丈人","岳母/老丈娘",
                   "","",
                   "","",
                   "大舅子","小舅子",
                   "大姨姐","小姨子");
    node->getRelationValue(RelationNode::GeGe)->setNotes("","",
                                                         "","嫂子");
    node->getRelationValue(RelationNode::DiDi)->setNotes("","",
                                                         "","弟妹");
    node->getRelationValue(RelationNode::JieJie)->setNotes("","",
                                                         "连襟","");
    node->getRelationValue(RelationNode::MeiMei)->setNotes("","",
                                                         "连襟","");
    RelationNode * laopo=node;

    //老公的直接关系
    node=m_rootRel->getRelationValue(RelationNode::LaoGong);
    node->setNotes("公公/爸","婆婆/妈",
                   "","",
                   "","",
                   "大伯哥","小叔子",
                   "大姑子","小姑子");
    node->getRelationValue(RelationNode::GeGe)->setNotes("","",
                                                         "","妯娌");
    node->getRelationValue(RelationNode::DiDi)->setNotes("","",
                                                         "","妯娌");
    node->getRelationValue(RelationNode::JieJie)->setNotes("","",
                                                         "大姑夫","");
    node->getRelationValue(RelationNode::MeiMei)->setNotes("","",
                                                         "小姑夫","");
    RelationNode * laogong=node;
    //我老公/老婆和我的夫妻关系
    node->setRelationValue(RelationNode::LaoPo,me);
    node->setRelationValue(RelationNode::LaoGong,me);

    //儿子的直接关系
    node=m_rootRel->getRelationValue(RelationNode::ErZi);
    node->setNotes("","",
                   "","儿媳",
                   "孙子","孙女");
    //孙女的直接关系
    node->getRelationValue(RelationNode::NvEr)->setNotes("","",
                                                         "孙女婿","",
                                                         "曾外孙","曾外孙女");
    RelationNode * erzi=node;
    //儿子儿媳的夫妻关系
    erzi->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,erzi);

    //女儿的直接关系
    node=m_rootRel->getRelationValue(RelationNode::NvEr);
    node->setNotes("","",
                   "女婿","",
                   "外孙","外孙女");
    //外孙的直接关系
    node->getRelationValue(RelationNode::ErZi)->setNotes("","",
                                                         "","外孙媳",
                                                         "外曾孙","外曾孙女");
    node->getRelationValue(RelationNode::ErZi)->setNotes("","",
                                                         "外孙女婿","",
                                                         "外曾孙","外曾孙女");
    RelationNode * nver=node;
    //女婿女儿的夫妻关系
    nver->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,nver);

    //哥哥的直接关系
    node=m_rootRel->getRelationValue(RelationNode::GeGe);
    node->setNotes("","",
                   "","嫂子",
                   "侄子","侄女");
    //侄子的子女
    node->getRelationValue(RelationNode::ErZi)->setNotes("","",
                                                         "","",
                                                         "侄孙男","侄孙女");
    node->getRelationValue(RelationNode::NvEr)->setNotes("","",
                                                         "","",
                                                         "侄外孙","侄外孙女");
    RelationNode * gege=node;
    //哥哥嫂子的夫妻关系
    gege->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,gege);

    //弟弟的直接关系
    node=m_rootRel->getRelationValue(RelationNode::DiDi);
    node->setNotes("","",
                   "","弟媳",
                   "侄子","侄女");
    //侄子的子女
    node->getRelationValue(RelationNode::ErZi)->setNotes("","",
                                                         "","",
                                                         "侄孙男","侄孙女");
    node->getRelationValue(RelationNode::NvEr)->setNotes("","",
                                                         "","",
                                                         "侄外孙","侄外孙女");
    RelationNode * didi=node;
    //弟弟弟媳的夫妻关系
    didi->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,didi);

    //姐姐的直接关系
    node=m_rootRel->getRelationValue(RelationNode::JieJie);
    node->setNotes("","",
                   "姐夫","",
                   "外甥","外甥女");
    //外甥的子女
    node->getRelationValue(RelationNode::ErZi)->setNotes("","",
                                                         "","",
                                                         "甥孙男","甥孙女");
    node->getRelationValue(RelationNode::NvEr)->setNotes("","",
                                                         "","",
                                                         "甥外孙男","甥外孙女");
    RelationNode * jiejie=node;
    //姐姐姐夫的夫妻关系
    jiejie->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,jiejie);

    //妹妹的直接关系
    node=m_rootRel->getRelationValue(RelationNode::MeiMei);
    node->setNotes("","",
                   "妹夫","",
                   "外甥","外甥女");
    //外甥的子女
    node->getRelationValue(RelationNode::ErZi)->setNotes("","",
                                                         "","",
                                                         "甥孙男","甥孙女");
    node->getRelationValue(RelationNode::NvEr)->setNotes("","",
                                                         "","",
                                                         "甥外孙男","甥外孙女");
    RelationNode * meimei=node;
    //妹妹妹夫的夫妻关系
    meimei->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,meimei);

    //祖父的直接关系
    node=baba->getRelationValue(RelationNode::FuQin);
    node->setNotes("曾祖父/老祖","曾祖母/老祖",
                   "","",
                   "","",
                   "伯祖父/伯公","叔祖父/叔公",
                   "姑祖母/姑婆","姑祖母/姑婆");
    RelationNode * zufu=node;
    //曾祖父曾祖母的夫妻关系
    zufu->getRelationValue(RelationNode::FuQin)->setRelationValue(RelationNode::LaoPo,zufu->getRelationValue(RelationNode::MuQin));
    zufu->getRelationValue(RelationNode::MuQin)->setRelationValue(RelationNode::LaoGong,zufu->getRelationValue(RelationNode::FuQin));



    //祖母的直接关系
    node=baba->getRelationValue(RelationNode::MuQin);
    node->setNotes("","",
                   "","",
                   "","",
                   "舅祖父/舅公/舅奶爷","舅祖父/舅公/舅奶爷",
                   "姨祖母/姨婆/姨奶奶","姨祖母/姨婆/姨奶奶");
    RelationNode * zumu=node;
    //祖父祖母的夫妻关系
    zufu->setRelationValue(RelationNode::LaoPo,zumu);
    zumu->setRelationValue(RelationNode::LaoGong,zufu);

    //伯伯的直接关系
    node=baba->getRelationValue(RelationNode::GeGe);
    node->setNotes("","",
                   "","伯娘",
                   "堂兄弟","堂姊妹");
    //伯伯伯娘的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);

    //叔叔的直接关系
    node=baba->getRelationValue(RelationNode::DiDi);
    node->setNotes("","",
                   "","婶婶",
                   "堂兄弟","堂姊妹");
    //叔叔婶婶的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);


    //姑姑的直接关系
    node=baba->getRelationValue(RelationNode::JieJie);
    node->setNotes("","",
                   "姑父","",
                   "表兄弟","表姊妹");
    //姑姑姑父的夫妻关系
    node->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,node);


    //姑姑的直接关系
    node=baba->getRelationValue(RelationNode::MeiMei);
    node->setNotes("","",
                   "姑父","",
                   "表兄弟","表姊妹");
    //姑姑姑父的夫妻关系
    node->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,node);

    //外祖父的直接关系
    node=mama->getRelationValue(RelationNode::FuQin);
    node->setNotes("外曾祖父/老祖","外曾祖母/老祖",
                   "","",
                   "表舅","表姨妈",
                   "伯外公","叔外公",
                   "姑婆/大姑姥姥","姑婆/小姑姥姥");
    RelationNode * waizufu=node;
    //外曾祖父外曾祖母的夫妻关系
    waizufu->getRelationValue(RelationNode::FuQin)->setRelationValue(RelationNode::LaoPo,waizufu->getRelationValue(RelationNode::MuQin));
    waizufu->getRelationValue(RelationNode::MuQin)->setRelationValue(RelationNode::LaoGong,waizufu->getRelationValue(RelationNode::FuQin));


    //外祖母的直接关系
    node=mama->getRelationValue(RelationNode::MuQin);
    node->setNotes("","",
                   "","",
                   "舅舅","姨妈",
                   "舅王父/舅姥爷","舅王父/舅姥爷",
                   "姨王母/姨姥姥","姨王母/姨姥姥");
    RelationNode * waizumu=node;
    //外祖父外祖母的夫妻关系
    waizufu->setRelationValue(RelationNode::LaoPo,waizumu);
    waizumu->setRelationValue(RelationNode::LaoGong,waizufu);

    //舅舅的直接关系
    node=mama->getRelationValue(RelationNode::GeGe);
    node->setNotes("","",
                   "","舅妈",
                   "表兄弟","表姊妹");
    //舅舅舅妈的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);

    //舅舅的直接关系
    node=mama->getRelationValue(RelationNode::DiDi);
    node->setNotes("","",
                   "","舅妈",
                   "表兄弟","表姊妹");
    //舅舅舅妈的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);

    //姨妈的直接关系
    node=mama->getRelationValue(RelationNode::JieJie);
    node->setNotes("","",
                   "姨夫","",
                   "表兄弟","表姊妹");
    //姨妈姨夫的夫妻关系
    node->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,node);

    //姨妈的直接关系
    node=mama->getRelationValue(RelationNode::MeiMei);
    node->setNotes("","",
                   "姨夫","",
                   "表兄弟","表姊妹");
    //姨妈姨夫的夫妻关系
    node->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,node);

    //孙子的直接关系
    node=erzi->getRelationValue(RelationNode::ErZi);
    node->setNotes("","",
                   "","孙媳妇",
                   "曾孙","曾孙女");
    RelationNode * sunzi=node;
    //孙子孙媳妇的夫妻关系
    sunzi->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,sunzi);

    //曾祖父的直接关系
    node=zufu->getRelationValue(RelationNode::FuQin);
    node->setNotes("高祖父/老天天","高祖母/老天天");
    //高祖父高祖母的夫妻关系
    node->getRelationValue(RelationNode::FuQin)->setRelationValue(RelationNode::LaoPo,node->getRelationValue(RelationNode::MuQin));
    node->getRelationValue(RelationNode::MuQin)->setRelationValue(RelationNode::LaoGong,node->getRelationValue(RelationNode::FuQin));

    //伯祖父的直接关系
    node=zufu->getRelationValue(RelationNode::GeGe);
    node->setNotes("","",
                   "","伯祖母/姆婆",
                   "堂叔","堂姑");
    //伯祖父伯祖母的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);

    //叔祖父的直接关系
    node=zufu->getRelationValue(RelationNode::DiDi);
    node->setNotes("","",
                   "","叔祖母/婶婆",
                   "堂叔","堂姑");
    //叔祖父叔祖母的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);

    //姑祖母的直接关系
    node=zufu->getRelationValue(RelationNode::JieJie);
    node->setNotes("","",
                   "姑祖父/姑公","",
                   "表叔","表姑");
    //姑祖母姑祖父的夫妻关系
    node->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,node);

    //姑祖母的直接关系
    node=zufu->getRelationValue(RelationNode::MeiMei);
    node->setNotes("","",
                   "姑祖父/姑公","");
    //姑祖母姑祖父的夫妻关系
    node->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,node);

    //舅祖父的直接关系
    node=zumu->getRelationValue(RelationNode::GeGe);
    node->setNotes("","",
                   "","舅祖母/妗婆");
    //舅祖父舅祖母的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);


    //舅祖父的直接关系
    node=zumu->getRelationValue(RelationNode::DiDi);
    node->setNotes("","",
                   "","舅祖母/妗婆");
    //舅祖父舅祖母的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);


    //姨祖母的直接关系
    node=zumu->getRelationValue(RelationNode::JieJie);
    node->setNotes("","",
                   "姨祖父/姨公","");
    //姨祖母姨祖父的夫妻关系
    node->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,node);


    //姨祖母的直接关系
    node=zumu->getRelationValue(RelationNode::MeiMei);
    node->setNotes("","",
                   "姨祖父/姨公","");
    //姨祖母姨祖父的夫妻关系
    node->getRelationValue(RelationNode::LaoGong)->setRelationValue(RelationNode::LaoPo,node);

    //外曾祖父的直接关系
    node=waizufu->getRelationValue(RelationNode::FuQin);
    node->setNotes("外高祖父/老天天","外高祖母/老天天");
    //外高祖父外高祖母的夫妻关系
    node->getRelationValue(RelationNode::FuQin)->setRelationValue(RelationNode::LaoPo,node->getRelationValue(RelationNode::MuQin));
    node->getRelationValue(RelationNode::MuQin)->setRelationValue(RelationNode::LaoGong,node->getRelationValue(RelationNode::FuQin));

    //曾孙的直接关系
    node=sunzi->getRelationValue(RelationNode::ErZi);
    node->setNotes("","",
                   "","曾孙媳",
                   "玄孙","玄孙女");
    //曾孙曾孙媳的夫妻关系
    node->getRelationValue(RelationNode::LaoPo)->setRelationValue(RelationNode::LaoGong,node);
}

void PersonRelation::endDistruct()
{
    if(m_rootRel!=NULL)
    {
        delete m_rootRel;
        m_rootRel=NULL;
    }
}

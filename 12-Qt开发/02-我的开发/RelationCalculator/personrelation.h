#ifndef PERSONRELATION_H
#define PERSONRELATION_H
#include<QString>
#include<QList>
#define MAX_RELATION_COUNT 14
class RelationNode
{
public:
    enum RelationIndex{FuQin=0,MuQin,GeGe,DiDi,JieJie,MeiMei,ErZi,NvEr,LaoGong,LaoPo,YiFu,YiMu,YiZi,YiNv};
    static QString getIndexName(RelationIndex index);
    static RelationNode * buildNode(QString nodeName,
                                    QString fuQinName="",QString muQinName="",
                                    QString laoGongName="",QString laoPoName="",
                                    QString erZiName="",QString nvErName="",
                                    QString geGeName="",QString diDiName="",
                                    QString jieJieName="",QString meiMeiName="",
                                    QString yiFuName="",QString yiMuName="",
                                    QString yiZiName="",QString yiNvName=""
                                    );
    void setNotes(QString fuQinName="",QString muQinName="",
                  QString laoGongName="",QString laoPoName="",
                  QString erZiName="",QString nvErName="",
                  QString geGeName="",QString diDiName="",
                  QString jieJieName="",QString meiMeiName="",
                  QString yiFuName="",QString yiMuName="",
                  QString yiZiName="",QString yiNvName=""
                  );
    void setNotes(RelationNode * fuQin=NULL,RelationNode * muQin=NULL,
                  RelationNode * laoGong=NULL,RelationNode * laoPo=NULL,
                  RelationNode * erZi=NULL,RelationNode * nvEr=NULL,
                  RelationNode * geGe=NULL,RelationNode * diDi=NULL,
                  RelationNode * jieJie=NULL,RelationNode * meiMei=NULL,
                  RelationNode * yiFu=NULL,RelationNode * yiMu=NULL,
                  RelationNode * yiZi=NULL,RelationNode * yiNv=NULL
                  );
    RelationNode();
    RelationNode(QString name);
    RelationNode(const RelationNode & pr);
    RelationNode operator=(const RelationNode & pr);
    virtual ~RelationNode();
    void setName(QString name);
    QString getName();
    RelationNode & setRelationValue(RelationIndex index,const RelationNode * pr);
    RelationNode * getRelationValue(RelationIndex index);
    bool removeRelationValue(RelationIndex index);
private:
    void initConstruct();
    void endDistruct();
    QString m_name;
    RelationNode * m_relationMap[MAX_RELATION_COUNT];
};

class PersonRelation
{
public:
    PersonRelation();
    virtual ~PersonRelation();
    RelationNode * getMe();
    QString routeRelation(QList<RelationNode::RelationIndex> list);
private:
    void initConstruct();
    void endDistruct();
    RelationNode * m_rootRel;
};

#endif // PERSONRELATION_H

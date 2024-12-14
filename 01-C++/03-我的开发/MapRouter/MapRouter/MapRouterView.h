
// MapRouterView.h : CMapRouterView ��Ľӿ�
//

#pragma once
#include<vector>
#include<stack>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>

double getDistance(double x1, double y1, double x2, double y2);

typedef struct _map_point{
	double x; // X ����
	double y; // Y ����
	double z; // Z ����
} MapPoint;

typedef struct _map_edge{
	int sidx; // ����߿�ʼ�±�
	int eidx; // ����߽����±�
	double weight; // �����Ȩ��
} MapEdge;

class Maps {
public:
	std::vector<MapPoint> points;
	std::vector<MapEdge> edges;
	int * linkMap;
public:
	Maps(){
		points.clear();
		edges.clear();
		linkMap = NULL;
	}
	Maps(const Maps& map){
		linkMap = NULL;
		clean();
		for (int i = 0; i < map.points.size(); i++){
			this->points.push_back(map.points.at(i));
		}
		for (int i = 0; i < map.edges.size(); i++){
			this->edges.push_back(map.edges.at(i));
		}
		prepareMap();
	}
	Maps(Maps&& map){
		linkMap = NULL;
		clean();
		for (int i = 0; i < map.points.size(); i++){
			this->points.push_back(map.points.at(i));
		}
		for (int i = 0; i < map.edges.size(); i++){
			this->edges.push_back(map.edges.at(i));
		}
		prepareMap();
	}
	Maps& operator=(const Maps& map){
		clean();
		for (int i = 0; i < map.points.size(); i++){
			this->points.push_back(map.points.at(i));
		}
		for (int i = 0; i < map.edges.size(); i++){
			this->edges.push_back(map.edges.at(i));
		}
		prepareMap();
	}
	Maps& operator=(Maps&& map){
		clean();
		for (int i = 0; i < map.points.size(); i++){
			this->points.push_back(map.points.at(i));
		}
		for (int i = 0; i < map.edges.size(); i++){
			this->edges.push_back(map.edges.at(i));
		}
		prepareMap();
	}
	~Maps(){
		clean();
	}
	void clean(){
		points.clear();
		edges.clear();
		if (linkMap != NULL){
			delete[] linkMap;
		}
		linkMap = NULL;
	}
	void prepareMap(){
		if (linkMap != NULL){
			delete[] linkMap;
		}
		int size = points.size();
		linkMap = new int[size*size];
		for (int i = 0; i < size*size; i++){
			linkMap[i] = 0;
		}
		for (int i = 0; i < edges.size(); i++){
			MapEdge edge = edges.at(i);
			map(edge.sidx, edge.eidx, 1);
		}
	}
	int size(){
		return points.size();
	}
	int map(int x, int y){
		int size = points.size();
		return linkMap[y*size+x];
	}
	void map(int x, int y, int val){
		int size = points.size();
		linkMap[y*size + x] = val;
	}
	std::vector<int> row(int r)
	{
		std::vector<int> ret;
		int size = points.size();
		for (int i = 0; i < size; i++){
			ret.push_back(map(r, i));
		}
		return ret;
	}
	void removePoint(int idx){
		if (idx < 0){
			return;
		}
		if (idx >= points.size()){
			return;
		}
		points.erase(points.begin() + idx);
		std::vector<MapEdge> data;
		for (int i = 0; i < edges.size(); i++){
			MapEdge e = edges.at(i);
			if (e.sidx == idx || e.eidx == idx){
				continue;
			}
			else if(e.sidx>idx){
				e.sidx--;
				data.push_back(e);
			}
			else if (e.eidx > idx){
				e.eidx--;
				data.push_back(e);
			}
			else{
				data.push_back(e);
			}
		}
		this->edges = data;
	}
	int findEdge(int sidx, int eidx){
		if (sidx < 0 || eidx < 0){
			return -1;
		}
		if (sidx >= points.size() || eidx >= points.size()){
			return -1;
		}
		for (int i = 0; i < edges.size(); i++){
			MapEdge e = edges.at(i);
			if (e.sidx == sidx && e.eidx == eidx){
				return i;
			}
		}
		return -1;
	}
	void removeEdge(int sidx, int eidx){
		if (sidx < 0 || eidx < 0){
			return;
		}
		if (sidx >= points.size() || eidx >= points.size()){
			return;
		}
		for (int i = 0; i < edges.size(); i++){
			MapEdge e = edges.at(i);
			if (e.sidx == sidx && e.eidx == eidx){
				edges.erase(edges.begin()+i);
				break;
			}
		}
	}
	void addEdge(int sidx, int eidx){
		if (sidx < 0 || eidx < 0){
			return;
		}
		if (sidx >= points.size() || eidx >= points.size()){
			return;
		}
		bool isIn = false;
		for (int i = 0; i < edges.size(); i++){
			MapEdge e = edges.at(i);
			if (e.sidx == sidx && e.eidx == eidx){
				isIn = true;
				break;
			}
		}
		if (!isIn){
			MapEdge e = { 0 };
			e.sidx = sidx;
			e.eidx = eidx;
			edges.push_back(e);
		}
	}
	void setWeightsByDistance(bool zoreFill)
	{
		for (int i = 0; i < edges.size(); i++){
			if (zoreFill){
				edges[i].weight = 0;
			}
			else{
				MapPoint sp = points[edges[i].sidx];
				MapPoint ep = points[edges[i].eidx];
				double wei = getDistance(sp.x, sp.y, ep.x, ep.y);
				edges[i].weight = wei;
			}
		}
	}
};

typedef struct _map_route_result
{
	bool pass;
	std::vector<int> routes;
}MapRouteResult;

typedef struct _map_route_step{
	int pre;
	int loc;
}RouteStep;

class MapRouter
{
public:
	std::vector<MapRouteResult> routeMap(Maps map, int sidx, int eidx,bool useWeight,bool fullMin){
		std::vector<MapRouteResult> ret;
		if (sidx < 0 || eidx < 0){
			return ret;
		}
		if (sidx >= map.points.size() || eidx >= map.points.size()){
			return ret;
		}
		if (sidx == eidx){
			MapRouteResult rs;
			rs.pass = true;
			rs.routes.push_back(sidx);
			ret.push_back(rs);
			return ret;
		}
		map.prepareMap();

		RouteStep p = { 0 };
		p.pre = -1;
		p.loc = sidx;
		std::vector<RouteStep> queue;
		queue.push_back(p);
		int cp = 0;
		while (true){
			if (cp >= queue.size()){
				break;
			}
			p = queue.at(cp);
			if (p.loc == eidx){
				MapRouteResult rs = { 0 };
				rs.pass = true;
				std::stack<int> routes;
				while (true){
					routes.push(p.loc);
					if (p.pre == -1){
						break;
					}
					p = queue.at(p.pre);
				}
				rs.routes.clear();
				while (!routes.empty()){
					int pv = routes.top();
					rs.routes.push_back(pv);
					routes.pop();
				}
				ret.push_back(rs);
				cp++;
				continue;
			}
			std::vector<int> nextRoutes = map.row(p.loc);

			//ʹ��Ȩ�أ�������ֲ�Ȩ�أ�
			if (useWeight){
				std::vector<int> minNextRoutes;
				std::vector<double> minNextWeights;
				//��ȡ��һ�����ߵ㼰��һ��Ȩ��
				for (int i = 0; i < nextRoutes.size(); i++){
					if (nextRoutes[i] == 1){
						minNextRoutes.push_back(i);
						int qidx = map.findEdge(p.loc, i);
						MapEdge pe = map.edges.at(qidx);
						double pwei = pe.weight;
						minNextWeights.push_back(pwei);
					}
				}
				//����Ȩ����С��������
				for (int i = 0; i < minNextRoutes.size(); i++){
					bool swap = false;
					for (int j = i; j < minNextRoutes.size() - 1; j++){
						if (minNextWeights[j]>minNextWeights[j + 1]){
							swap = true;
							double tpw = minNextWeights[j];
							minNextWeights[j] = minNextWeights[j + 1];
							minNextWeights[j + 1] = tpw;

							int tpi = minNextRoutes[j];
							minNextRoutes[j] = minNextRoutes[j + 1];
							minNextRoutes[j + 1] = tpi;
						}
					}
					if (!swap){
						break;
					}
				}
				//����Ѱ·����һ��
				RouteStep pp = p;
				for (int i = 0; i < minNextRoutes.size(); i++){
					int csp = minNextRoutes[i];
					p = pp;
					//�ж��Ƿ����߹�����ֹѭ��
					bool isSteped = false;
					while (true){
						if (p.pre == -1){
							break;
						}
						p = queue.at(p.pre);
						if (p.loc == csp){
							isSteped = true;
							break;
						}
					}
					if (!isSteped){
						RouteStep np;
						np.loc = csp;
						np.pre = cp;
						queue.push_back(np);
					}
				}
			}
			else{
				//��ʹ��Ȩ��
				RouteStep pp = p;
				for (int i = 0; i < nextRoutes.size(); i += 1){
					if (nextRoutes[i] == 1){
						p = pp;
						bool isSteped = false;
						while (true){
							if (p.pre == -1){
								break;
							}
							p = queue.at(p.pre);
							if (p.loc == i){
								isSteped = true;
								break;
							}
						}
						if (!isSteped){
							RouteStep np;
							np.loc = i;
							np.pre = cp;
							queue.push_back(np);
						}
					}
				}
			}
			cp++;
		}
		//ȫ����С
		if (fullMin){
			if (useWeight){
				std::vector<double> fullWeight;
				for (int i = 0; i < ret.size(); i++){
					double swei = 0;
					for (int j = 1; j < ret[i].routes.size(); j++){
						int ei = map.findEdge(ret[i].routes[j - 1], ret[i].routes[j]);
						double wei = map.edges[ei].weight;
						swei += wei;
					}
					fullWeight.push_back(swei);
				}
				for (int i = 0; i < fullWeight.size(); i++){
					bool swap = false;
					for (int j = i; j < fullWeight.size() - 1; j++){
						if (fullWeight[j]>fullWeight[j + 1]){
							swap = true;
							double tpw = fullWeight[j];
							fullWeight[j] = fullWeight[j + 1];
							fullWeight[j + 1] = tpw;

							MapRouteResult tpi = ret[j];
							ret[j] = ret[j + 1];
							ret[j + 1] = tpi;
						}
					}
					if (!swap){
						break;
					}
				}
			}
		}
		return ret;
	}
};

enum OperType{OT_NULL,OT_EDIT_POINT,OT_EDIT_EDGE,OT_SET_SE_POINT};

class CMapRouterView : public CView
{
private:
	bool isLBtnDown;
	bool isRBtnDown;
	bool isMBtnDown;
	int beginIdx;
	int endIdx;
	CPoint beginPoint;
	Maps map;
	OperType operType;
	double recogRadius;

	IMAGE bgImg;

	int mostDisplayCount;

	bool isShowBgImg;
	bool isBlackPanel;

	bool isEdgeDirectDbl;

	bool isPointDistanceAsEdgeWeight;
	bool isFullWeightPrior;

	bool isShowWeight;

	std::vector<MapRouteResult> routes;

	void drawArrow(CDC * pDC,double x1, double y1, double x2, double y2);
	void drawMapContent(CDC * pDC);

	int findPointIdx(double x,double y, double radius);
	

protected: // �������л�����
	CMapRouterView();
	DECLARE_DYNCREATE(CMapRouterView)

// ����
public:
	CMapRouterDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMapRouterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnEditPoint();
	afx_msg void OnEditEdge();
	afx_msg void OnEditBeginEndPoint();
	afx_msg void OnRunRoute();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnCleanEdges();
	afx_msg void OnCleanMap();
	afx_msg void OnDisplayResultOne();
	afx_msg void OnDisplayResultThird();
	afx_msg void OnDisplayResultAll();
	afx_msg void OnEditNone();
	afx_msg void OnSwitchBgimgShow();
	afx_msg void OnSwitchThemeColor();
	afx_msg void OnSwitchEdgeDirectDbl();
	afx_msg void OnSwitchPointDistanceAsWeight();
	afx_msg void OnSwitchFullPriorWeight();
	afx_msg void OnSwitchShowWeight();
};

#ifndef _DEBUG  // MapRouterView.cpp �еĵ��԰汾
inline CMapRouterDoc* CMapRouterView::GetDocument() const
   { return reinterpret_cast<CMapRouterDoc*>(m_pDocument); }
#endif


void CMy04多面体三角化View::BulidLinearMatrix()
{
	/*
	建立以每个点为中心，周围最近的3个点,建立邻接矩阵m_matrix
	这三个点和中心点组成三角形
	#define CENTER 0 条件编译
	*/
	
#define CENTER 0	//是否采用中心点形成三个三角形，否则去除中心点形成一个三角形
#if CENTER
	int LinerPointCount = 3;
	this->m_tranglecount = this->m_pointcount*LinerPointCount;
#else
	this->m_tranglecount = this->m_pointcount;
#endif
	this->m_trangle = (int**)malloc(sizeof(int*)*this->m_tranglecount);
	for (int f = 0; f < m_tranglecount; f++)
	{
		this->m_trangle[f] = (int*)malloc(sizeof(int)* 3);
	}
	//allocate memory for m_matrix
	m_matrix = (PMAPNODE)malloc(sizeof(MAPNODE)*this->m_pointcount);
	//for every point calcul linear point
	PMATRIXNODE distPrePoint = (PMATRIXNODE)malloc(sizeof(MATRIXNODE)*this->m_pointcount);
	for (int i = 0; i < m_pointcount; i++)
	{
		m_matrix[i].prePointIndex = i;
		//calcul one point distance
		for (int j = 0; j < m_pointcount; j++)
		{
			distPrePoint[j].drtPointIndex = j;
			distPrePoint[j].distance = DISTANCE(this->m_points[i][0], this->m_points[i][1], this->m_points[i][2], \
				this->m_points[j][0], this->m_points[j][1], this->m_points[j][2], );
		}
		//get 5 point of min
		for (int m = 0; m < 3 + 2; m++)
		{
			//find the m th. min number
			int minIndex = m;
			for (int n = m; n < m_pointcount; n++)
			{
				if (n == i)
					continue;
				if (distPrePoint[n].distance < distPrePoint[minIndex].distance)
				{
					minIndex = n;
				}
			}
			//swap min distance point to m index
			MATRIXNODE temp;
			temp.drtPointIndex = distPrePoint[minIndex].drtPointIndex;
			temp.distance = distPrePoint[minIndex].distance;
			distPrePoint[minIndex].distance = distPrePoint[m].distance;
			distPrePoint[minIndex].drtPointIndex = distPrePoint[m].drtPointIndex;
			distPrePoint[m].distance = temp.distance;
			distPrePoint[m].drtPointIndex = temp.drtPointIndex;

		}

		//copy trangle data to m_trangle
		for (int h = 0; h < 3; h++)
		{
			m_matrix[i].linearPointIndexs[h] = distPrePoint[h].drtPointIndex;
		}
#if CENTER
		int PointArr[20][3];/* = { { 0, 0, 1 }, { 0, 1, 2 }, { 0, 2, 0 } };*/
		for (int b = 0; b < LinerPointCount; b++)
		{
			PointArr[b][0] = i;
			PointArr[b][1] = b;
			PointArr[b][2] = b + 1;
		}
		PointArr[LinerPointCount - 1][0] = i;
		PointArr[LinerPointCount - 1][1] = LinerPointCount - 1;
		PointArr[LinerPointCount - 1][2] = 0;
		for (int g = 0; g < LinerPointCount; g++)
		{
			for (int h = 0; h < 3; h++)
				this->m_trangle[LinerPointCount*i + g][h] = distPrePoint[PointArr[g][h]].drtPointIndex;
		}
#else
		for (int h = 0; h < 3; h++)
		{
			this->m_trangle[i][h] = distPrePoint[h].drtPointIndex;
		}
#endif
			
	}
	this->m_vectorNum = 3;
	free(distPrePoint);
	FILE * linearTxt = fopen("LinearMatrix.txt","w");
	for (int i = 0; i < m_pointcount; i++)
	{
		fprintf(linearTxt, "%d\t: %d\t%d\t%d\n", m_matrix[i].prePointIndex, m_matrix[i].linearPointIndexs[0], m_matrix[i].linearPointIndexs[1], m_matrix[i].linearPointIndexs[2] );
	}
	fclose(linearTxt);
}

void CMy04多面体三角化View::BulidLinearMatrix()
{
	/*
	建立以每个点为中心，周围最近的3个点,建立邻接矩阵m_matrix
	这三个点组成一个三角形
	*/
	
	this->m_tranglecount = this->m_pointcount;
	this->m_trangle = (int**)malloc(sizeof(int*)*this->m_tranglecount);
	for (int f = 0; f < m_tranglecount; f++)
	{
		this->m_trangle[f] = (int*)malloc(sizeof(int)* 3);
	}
	//allocate memory for m_matrix
	m_matrix = (PMAPNODE)malloc(sizeof(MAPNODE)*this->m_pointcount);
	//for every point calcul linear point
	PMATRIXNODE distPrePoint = (PMATRIXNODE)malloc(sizeof(MATRIXNODE)*this->m_pointcount);
	for (int i = 0; i < m_pointcount; i++)
	{
		m_matrix[i].prePointIndex = i;
		//calcul one point distance
		for (int j = 0; j < m_pointcount; j++)
		{
			distPrePoint[j].drtPointIndex = j;
			distPrePoint[j].distance = DISTANCE(this->m_points[i][0], this->m_points[i][1], this->m_points[i][2], \
				this->m_points[j][0], this->m_points[j][1], this->m_points[j][2], );
		}
		//get 5 point of min
		for (int m = 0; m < 3 + 2; m++)
		{
			//find the m th. min number
			int minIndex = m;
			for (int n = m; n < m_pointcount; n++)
			{
				if (n == i)
					continue;
				if (this->m_points[distPrePoint[n].drtPointIndex][2] - this->m_points[i][2]<10e-2)
					continue;
				if (distPrePoint[n].distance < distPrePoint[minIndex].distance)
				{
					minIndex = n;
				}
			}
			//swap min distance point to m index
			MATRIXNODE temp;
			temp.drtPointIndex = distPrePoint[minIndex].drtPointIndex;
			temp.distance = distPrePoint[minIndex].distance;
			distPrePoint[minIndex].distance = distPrePoint[m].distance;
			distPrePoint[minIndex].drtPointIndex = distPrePoint[m].drtPointIndex;
			distPrePoint[m].distance = temp.distance;
			distPrePoint[m].drtPointIndex = temp.drtPointIndex;

		}

		//copy trangle data to m_trangle
		for (int h = 0; h < 3; h++)
		{
			this->m_trangle[i][h] = distPrePoint[h].drtPointIndex;
			m_matrix[i].linearPointIndexs[h] = distPrePoint[h].drtPointIndex;
		}
			
	}
	this->m_vectorNum = 3;
	free(distPrePoint);
	FILE * linearTxt = fopen("LinearMatrix.txt","w");
	for (int i = 0; i < m_pointcount; i++)
	{
		fprintf(linearTxt, "%d\t: %d\t%d\t%d\n", m_matrix[i].prePointIndex, m_matrix[i].linearPointIndexs[0], m_matrix[i].linearPointIndexs[1], m_matrix[i].linearPointIndexs[2] );
	}
	fclose(linearTxt);
}


void CMy04多面体三角化View::BulidLinearMatrix()
{
	/*
	建立以每个点为中心，周围最近的LinerPointCount个点，
	以中心点和LinerPointCount个点中的两个组成LinerPointCount个三角形（伞状）
	LinerPointCount最大值为20
	最小值为3
	*/
	PMAPNODE m_matrix;
	int LinerPointCount = 3;
	this->m_tranglecount = this->m_pointcount*LinerPointCount;
	this->m_trangle = (int**)malloc(sizeof(int*)*this->m_tranglecount);
	for (int f = 0; f < m_tranglecount; f++)
	{
		this->m_trangle[f] = (int*)malloc(sizeof(int)* 3);
	}
	//allocate memory for m_matrix
	m_matrix = (PMAPNODE)malloc(sizeof(MAPNODE)*this->m_pointcount);
	for (int i = 0; i < this->m_pointcount; i++)
	{
		m_matrix[i].prePointIndex = i;
	}
	//for every point calcul linear point
	PMATRIXNODE distPrePoint = (PMATRIXNODE)malloc(sizeof(MATRIXNODE)*this->m_pointcount);
	for (int i = 0; i < m_pointcount; i++)
	{
		//calcul one point distance
		for (int j = 0; j < m_pointcount; j++)
		{
			distPrePoint[j].drtPointIndex = j;
			distPrePoint[j].distance = DISTANCE(this->m_points[i][0], this->m_points[i][1], this->m_points[i][2], \
				this->m_points[j][0], this->m_points[j][1], this->m_points[j][2], );
		}
		//get 5 point of min
		for (int m = 0; m < LinerPointCount + 2; m++)
		{
			//find the m th. min number
			int minIndex = m;
			for (int n = m; n < m_pointcount; n++)
			{
				if (n == i)
					continue;
				if (this->m_points[distPrePoint[n].drtPointIndex][2] - this->m_points[i][2]<10e-2)
					continue;
				if (distPrePoint[n].distance < distPrePoint[minIndex].distance)
				{
					minIndex = n;
				}
			}
			//swap min distance point to m index
			MATRIXNODE temp;
			temp.drtPointIndex = distPrePoint[minIndex].drtPointIndex;
			temp.distance = distPrePoint[minIndex].distance;
			distPrePoint[minIndex].distance = distPrePoint[m].distance;
			distPrePoint[minIndex].drtPointIndex = distPrePoint[m].drtPointIndex;
			distPrePoint[m].distance = temp.distance;
			distPrePoint[m].drtPointIndex = temp.drtPointIndex;

		}

		//copy trangle data to m_trangle
		int PointArr[20][3];/* = { { 0, 0, 1 }, { 0, 1, 2 }, { 0, 2, 0 } };*/
		for (int b = 0; b < LinerPointCount; b++)
		{
			PointArr[b][0] = i;
			PointArr[b][1] = b;
			PointArr[b][2] = b + 1;
		}
		PointArr[LinerPointCount - 1][0] = i;
		PointArr[LinerPointCount - 1][1] = LinerPointCount - 1;
		PointArr[LinerPointCount - 1][2] = 0;
		for (int g = 0; g < LinerPointCount; g++)
		{
			for (int h = 0; h < 3; h++)
				this->m_trangle[LinerPointCount*i + g][h] = distPrePoint[PointArr[g][h]].drtPointIndex;
		}

	}
	this->m_vectorNum = 3;
	free(distPrePoint);
	free(m_matrix);
}

void CMy04多面体三角化View::BulidLinearMatrix()
{
	/*
	建立以每个点为中心，周围最近的3个点，
	这三个点组成一个三角形
	*/
	PMAPNODE m_matrix;
	this->m_tranglecount = this->m_pointcount;
	this->m_trangle = (int**)malloc(sizeof(int*)*this->m_tranglecount);
	for (int f = 0; f < m_tranglecount; f++)
	{
		this->m_trangle[f] = (int*)malloc(sizeof(int)*3);
	}
	//allocate memory for m_matrix
	m_matrix = (PMAPNODE)malloc(sizeof(MAPNODE)*this->m_pointcount);
	for (int i = 0; i < this->m_pointcount; i++)
	{
		m_matrix[i].prePointIndex = i;
	}
	//for every point calcul linear point
	PMATRIXNODE distPrePoint = (PMATRIXNODE)malloc(sizeof(MATRIXNODE)*this->m_pointcount);
	for (int i = 0; i < m_pointcount; i++)
	{
		//calcul one point distance
		for (int j = 0; j < m_pointcount; j++)
		{
			distPrePoint[j].drtPointIndex = j;
			distPrePoint[j].distance = DISTANCE(this->m_points[i][0], this->m_points[i][1], this->m_points[i][2],\
				this->m_points[j][0], this->m_points[j][1], this->m_points[j][2], );
		}
		//get 5 point of min
		for (int m = 0; m < 3+2; m++)
		{
			//find the m th. min number
			int minIndex = m;
			for (int n = m; n < m_pointcount; n++)
			{
				if (n == i)
					continue;
				if (this->m_points[distPrePoint[n].drtPointIndex][2]-this->m_points[i][2]<10e-2)
					continue;
				if (distPrePoint[n].distance < distPrePoint[minIndex].distance)
				{
					minIndex = n;
				}
			}
			//swap min distance point to m index
			MATRIXNODE temp;
			temp.drtPointIndex = distPrePoint[minIndex].drtPointIndex;
			temp.distance = distPrePoint[minIndex].distance;
			distPrePoint[minIndex].distance = distPrePoint[m].distance;
			distPrePoint[minIndex].drtPointIndex = distPrePoint[m].drtPointIndex;
			distPrePoint[m].distance = temp.distance;
			distPrePoint[m].drtPointIndex = temp.drtPointIndex;
			
		}

		//copy trangle data to m_trangle
		for (int h = 0; h < 3; h++)
			this->m_trangle[i][h] = distPrePoint[h].drtPointIndex;
	}
	this->m_vectorNum = 3;
	free(distPrePoint);
	free(m_matrix);
}


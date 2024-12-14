
void CMFCGraph06View::Line(CPoint p1,CPoint p2)
{
	CClientDC dc(this);
	COLORREF color=0x0000ff;
	CPoint tp1,tp2;
	
	if(abs(p1.x-p2.x)<=1e-6)
	{
		if(p1.y>p2.y)
		{
			tp1=p2;
			tp2=p1;
		}
		else
		{
			tp1=p1;
			tp2=p2;
		}
		for(double i=tp1.y;i<tp2.y;i+=1)
		{
			dc.SetPixelV((int)(tp1.x+0.5),(int)(i+0.5),color);
		}
	}
	else
	{
		double k=0,d=0;
		k=1.0*(p2.y-p1.y)/(p2.x-p1.x);
		if(k>1.0)
		{
			if(p1.y>p2.y)
			{
				tp1=p2;
				tp2=p1;
			}
			else
			{
				tp1=p1;
				tp2=p2;
			}
			d=1-0.5*k;
			for(double y=tp1.y,x=tp1.x;y<tp2.y;y+=1)
			{
				dc.SetPixelV((int)(x+0.5),(int)(y+0.5),color);
				
				if(d>=0)
				{
					x+=1;
					d+=1-k;
				}else
					d+=1;
			}
		}
		else if(k>=0.0 && k<=1.0)
		{
			if(p1.x>p2.x)
			{
				tp1=p2;
				tp2=p1;
			}
			else
			{
				tp1=p1;
				tp2=p2;
			}
			d=0.5-k;
			for(double y=tp1.y,x=tp1.x;x<tp2.x;x+=1)
			{
				dc.SetPixelV((int)(x+0.5),(int)(y+0.5),color);
				if(d<0)
				{
					y+=1;
					d+=1-k;
				}else
					d-=k;
			}
		}
		else if(k<0.0 && k>=-1.0)
		{
			if(p1.x>p2.x)
			{
				tp1=p2;
				tp2=p1;
			}
			else
			{
				tp1=p1;
				tp2=p2;
			}
			d=-0.5-k;
			for(double y=tp1.y,x=tp1.x;x<tp2.x;x+=1)
			{
				dc.SetPixelV((int)(x+0.5),(int)(y+0.5),color);
				if(d<0)
				{
					y-=1;
					d-=1-k;
				}else
					d-=k;
			}
		}
		else if(k<-1.0)
		{
			if(p1.y>p2.y)
			{
				tp1=p2;
				tp2=p1;
			}
			else
			{
				tp1=p1;
				tp2=p2;
			}
			d=-1-0.5*k;
			for(double y=tp1.y,x=tp1.x;y>tp2.y;y-=1)
			{
				dc.SetPixelV((int)(x+0.5),(int)(y+0.5),color);
				if(d<0)
				{
					x+=1;
					d-=1+k;
				}else
					d-=1;
			}
		}
	}

}
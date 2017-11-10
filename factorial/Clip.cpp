#pragma once
#include "Clip.h"
#include <math.h>

float psc(point A, point B)
{
	return A.x * B.y - A.y * B.x;
}

bool Clip(point &A, point &B, point Pmin, point Pmax){	float x1, y1, x2, y2, xmin, xmax, ymin, ymax, e, n, t1, t2;	point p, p1, pp, s1, s2, s3, s4, ss, q;	int i = 1, k = 0;	bool special_case = true;	x1 = A.x; y1 = A.y;	x2 = B.x; y2 = B.y;	xmin = Pmin.x; ymin = Pmin.y;	xmax = Pmax.x; ymax = Pmax.y;	p.x = x2 - x1; p.y = y2 - y1;	p1.x = x1; p1.y = y1;	pp.x = xmax - p1.x; pp.y = ymin - p1.y;	e = psc(p, pp);	s1.x = xmin - p1.x; s1.y = ymin - p1.y;	s2.x = xmin - p1.x; s2.y = ymax - p1.y;	s3.x = xmax - p1.x; s3.y = ymax - p1.y;	s4.x = xmax - p1.x; s4.y = ymin - p1.y;	while ((i <= 4) && (k != 2))	{		switch (i)		{		case 1:			ss.x = s1.x; ss.y = s1.y;			break;		case 2:			ss.x = s2.x; ss.y = s2.y;			break;		case 3:			ss.x = s3.x; ss.y = s3.y;			break;		case 4:			ss.x = s4.x; ss.y = s4.y;			break;		}		n = psc(p, ss);		if ((e * n < 0) || ((e * n == 0) && (e != 0)) || ((e * n == 0) && (n != 0) && special_case))		{			k++;			switch (i)			{			case 1:				q.x = s4.x - s1.x; q.y = s4.y - s1.y;				ss.x = s1.x; ss.y = s1.y;				break;			case 2:				q.x = s1.x - s2.x; q.y = s1.y - s2.y;				ss.x = s2.x; ss.y = s2.y;				break;			case 3:				q.x = s2.x - s3.x; q.y = s2.y - s3.y;				ss.x = s3.x; ss.y = s3.y;				break;			case 4:				q.x = s3.x - s4.x; q.y = s3.y - s4.y;				ss.x = s4.x; ss.y = s4.y;				break;			}			switch (k)
			{
			case 1:
				t1 = psc(ss, q) / psc(p, q);
				break;
			case 2:
				t2 = psc(ss, q) / psc(p, q);
				break;
			}		}		if ((e == 0) && (n == 0))			special_case = true;		else special_case = false;		e = n;		i++;	}	if (k < 2) return false;	if (((t1 < 0) && (t2 < 0)) || ((t1 > 1) && (t2 > 1))) return false;	if (t1 > t2)	{		float a = t1;		t1 = t2;		t2 = a;	}	float oldx1, oldy1, oldx2, oldy2;	oldx1 = x1; oldy1 = y1;	oldx2 = x2; oldy2 = y2;	if (t1 > 0)	{		x1 = oldx1 + (oldx2 - oldx1) * t1;		y1 = oldy1 + (oldy2 - oldy1) * t1;		A.x = x1; A.y = y1;	}	if (t2 < 1)	{		x2 = oldx1 + (oldx2 - oldx1) * t2;		y2 = oldy1 + (oldy2 - oldy1) * t2;		B.x = x2; B.y = y2;	}	return true;}
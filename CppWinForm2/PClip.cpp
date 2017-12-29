#pragma once
#include "Transform.h"
#include "PClip.h"

polygon^ PClip(polygon^ P, point Pmin, point Pmax) {
	int i = 1;
	int n1 = P->Count;
	int n2;
	polygon^ P1 = gcnew polygon(0);
	P1 = P;

	point N, F;
	int k;
	float q0, q1;
	point p0;
	float t;
	point f;
	f.x = Pmax.x;
	f.y = Pmin.y;
	while (i <= 4) {
		if (i == 1)
		{
			N.x = 1;
			N.y = 0;
			F.x = Pmin.x;
			F.y = Pmin.y;
		}
		if (i == 2)
		{
			N.x = 0;
			N.y = -1;
			F.x = Pmin.x;
			F.y = Pmax.y;
		}
		if (i == 3)
		{
			N.x = -1;
			N.y = 0;
			F.x = Pmax.x;
			F.y = Pmax.y;
		}
		if (i == 4)
		{
			N.x = 0;
			N.y = 1;
			F.x = Pmax.x;
			F.y = Pmin.y;
		}

		k = 1;
		q0 = (P1[n1 - 1].x - F.x) * (f.x - F.x) + (P1[n1 - 1].y - F.y) * (f.y - F.y);
		p0.x = P1[n1 - 1].x;
		p0.y = P1[n1 - 1].y;
		n2 = 0;

		polygon^ P2 = gcnew polygon(0);
		while (k <= n1) 
		{
			q1 = (P1[k - 1].x - F.x) * (f.x - F.x) + (P1[k - 1].y - F.y) * (f.y - F.y);

			if (q0 * q1 < 0) 
			{
				t = q0 / (q0 - q1);
				point t0;
				t0.x = p0.x - (p0.x - P1[k - 1].x) * t;
				t0.y = p0.y - (p0.y - P1[k - 1].y) * t;
				P2->Add(t0);
				n2++;
			}

			if (q1 >= 0) 
			{
				point t0;
				t0.x = P1[k - 1].x;
				t0.y = P1[k - 1].y;
				P2->Add(t0);
				n2++;
			}
			q0 = q1;
			p0.x = P1[k - 1].x;
			p0.y = P1[k - 1].y;
			k++;
		}
		P1 = P2;
		n1 = n2;
		f.x = F.x;
		f.y = F.y;
		if (n1 == 0)
			return P1;
		else
			i++;
	}
	return P1;
}
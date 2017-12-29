#pragma once
//#include "stdafx.h"
#include "Transform.h"
#include <algorithm>
#include "Clip.h"

void Clip1Left(point &A, float dx, float dy, float dxl)
{
	
	A.y += dxl*(dy / dx);
	A.x += dxl;
}

void Clip1Top(point &A, float dx, float dy, float dyt)
{
	
	A.y += dyt;
	A.x += dyt*(dx/dy);
}

void Clip1Bottom(point &A, float dx, float dy, float dyb)
{
	
	A.y += dyb;
	A.x += dyb*(dx/dy);
}

void Clip2Right(point &B, float dx, float dy, float dxr)
{
	
	B.y += dxr*(dy / dx);
	B.x += dxr;
}

void Clip2Top(point &B, float dx, float dy, float dyt)
{
	
	B.y += dyt;
	B.x += dyt*(dx/dy);
}

void Clip2Bottom(point &B, float dx, float dy, float dyb)
{
	
	B.y = B.y + dyb;
	B.x = B.x + dyb*(dx/dy);
}

bool clip(point &A, point &B, point Pmin, point Pmax)
{
	
	bool ans;
	if (A.x > B.x) {
		std::swap(A.x, B.x);
		std::swap(A.y, B.y);
	}
	float x1 = A.x,
		y1 = A.y,
		x2 = B.x,
		y2 = B.y,
		xmin = Pmin.x,
		ymin = Pmin.y,
		xmax = Pmax.x,
		ymax = Pmax.y;
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dxr = xmax - x1;
	float dyt = ymax - y1;
	float dyb = ymin - y1;
	float dxl = xmin - x1;

	float dxr2 = xmax - x2;
	float dyt2 = ymax - y2;
	float dyb2 = ymin - y2;
	float dxl2 = xmin - x2;
	int c1 = 0;
	if (x1 < xmin) c1++;
	if (x1 > xmax) c1 += 2;
	if (y1 < ymin) c1 += 4;
	if (y1 > ymax) c1 += 8;

	int c2 = 0;
	if (x2 < xmin) c2++;
	if (x2 > xmax) c2 += 2;
	if (y2 < ymin) c2 += 4;
	if (y2 > ymax) c2 += 8;

	if ((c1 & c2) != 0)
	{
		ans = false;
		return ans;
	}

	

	if (c1 == 0)
	{
		if (c2 == 0)
		{
			ans = true;
			return ans;
		}
		
		if (dy >= 0)
		{
			
			if (dy * dxr < dx* dyt)
				Clip2Right(B, dx, dy, dxr2);
			else Clip2Top(B, dx, dy, dyt2);
			goto step10;
		}
		if (dy < 0)
		{
			
			if (dy*dxr < dx*dyb)
				Clip2Bottom(B, dx, dy, dyb2);
			else Clip2Right(B, dx, dy, dxr2);
			goto step10;
		}
	}

	if (c1 == 1)
	{
		
		if (c2 == 0)
		{
			Clip1Left(A, dx, dy, dxl);
			goto step10;
		}
		if (dy >= 0)
		{
			if (dy*dxl > dx*dyt)
				goto step11;
			
			if (dy*dxr < dx*dyt)
				Clip2Right(B, dx, dy, dxr2);
			else Clip2Top(B, dx, dy, dyt2);
			Clip1Left(A, dx, dy, dxl);
			goto step10;
		}
		if (dy < 0)
		{
			
			if (dy*dxl < dx*dyb)
				goto step11;
			
			if (dy*dxr < dx*dyb)
				Clip2Bottom(B, dx, dy, dyb2);
			else Clip2Right(B, dx, dy, dxr2);
			Clip1Left(A, dx, dy, dxl);
			goto step10;
		}
	}

	if (c1 == 4)
	{
		
		if (c2 == 0)
		{
			Clip1Bottom(A, dx, dy, dyb);
			goto step10;
		}
		if (dy > 0)
		{
			if (dy*dxr < dx*dyb)
				goto step11;
			
			if (dy*dxr < dx*dyt)
				Clip2Right(B, dx, dy, dxr2);
			else Clip2Top(B, dx, dy, dyt2);
			Clip1Bottom(A, dx, dy, dyb);
			goto step10;
		}
		if (dy <= 0)
		{
			goto step11;
		}
	}

	if (c1 == 5)
	{
		
		if (dy > 0)
		{
			
			if (dy*dxl > dx*dyt)
				goto step11;
			
			if (dy*dxr < dx*dyb)
				goto step11;

			if (dyb*dxr < dxl*dyt)
			{
				if (dy*dxl < dx*dyb)
				{
					Clip1Bottom(A, dx, dy, dyb);
					if (x2 > xmax)
						Clip2Right(B, dx, dy, dxr2);
					goto step10;
				}
				Clip1Left(A, dx, dy, dxl);
				if (c2 == 0)
					goto step10;
				if ((dy*dxr < dx*dyt) && (c2 != 0))
				{
					Clip2Right(B, dx, dy, dxr2);
					goto step10;
				}
				Clip2Top(B, dx, dy, dyt);
				goto step10;
			}
			else
			{
				if (dy*dxr < dx*dyt)
				{
					Clip1Bottom(A, dx, dy, dyb);
					if (x2 > xmax)
						Clip2Right(B, dx, dy, dxr2);
					goto step10;
				}
				if (dy*dxl < dx*dyb)
				{
					Clip1Bottom(A, dx, dy, dyb);
					if (c2 != 0)
						Clip2Top(B, dx, dy, dyt2);
					goto step10;
				}
				Clip1Left(A, dx, dy, dxl);
				if (c2 == 0)
					goto step10;
				Clip2Top(B, dx, dy, dyt2);
				goto step10;
			}
		}
		else if (dy <= 0)
		{
			goto step11;
		}
	}

	if (c1 == 8)
	{
		
		if (c2 == 0)
		{
			Clip1Top(A, dx, dy, dyt);
			goto step10;
		}
		if (dy < 0)
		{
			if (dy*dxr>dx*dyt)
				goto step11;
			
			if (dy*dxr > dx*dyb)
				Clip2Right(B, dx, dy, dxr2);
			else Clip2Bottom(B, dx, dy, dyb2);
			Clip1Top(A, dx, dy, dyt);
			goto step10;
		}
		else if (dy >= 0)
		{
			goto step11;
		}
	}

	if (c1 == 9)
	{
		
		if (dy < 0)
		{
			
			if (dy*dxr>dx*dyt)
				goto step11;
			
			if (dy*dxl<dx*dyb)
				goto step11;
			if (dyt*dxr>dxl*dyb)
			{
				if (dy*dxl > dx*dyt)
				{
					Clip1Top(A, dx, dy, dyt);
					if (x2 > xmax)
						Clip2Right(B, dx, dy, dxr2);
					goto step10;
				}
				Clip1Left(A, dx, dy, dxl);
				if (c2==0)
					goto step10;
				if (dy*dxr > dx*dyb)
				{
					Clip2Right(B, dx, dy, dxr2);
					goto step10;
				}
				Clip2Bottom(B, dx, dy, dyb2);
				goto step10;
			}
			else
			{
				if (dy*dxr > dx*dyb)
				{
					Clip1Top(A, dx, dy, dyt);
					if (x2 > xmax)
						Clip2Right(B, dx, dy, dxr2);
					goto step10;
				}
				if (dy*dxl > dx*dyt)
				{
					Clip1Top(A, dx, dy, dyt);
					if (c2 != 0)
						Clip2Bottom(B, dx, dy, dyb2);
					goto step10;
				}
				Clip1Left(A, dx, dy, dxl);
				if (c2 != 0) Clip2Bottom(B, dx, dy, dyb2);
				goto step10;
			}
		}
		else if (dy >= 0)
		{
			goto step10;
		}
		else return true;
	}
step10:
	ans = true; //шаг 10
	return ans;
step11:
	ans = false; //шаг 11
	return ans;
}


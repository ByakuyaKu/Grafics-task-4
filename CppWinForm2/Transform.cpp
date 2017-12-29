#pragma once
#include "Transform.h"
#include <math.h>

mat T;
void times(mat a, mat b, mat &c)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			float skalaar = 0;
			for (int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec &c)
{
	for (int i = 0; i < M; i++)
	{
		float skalaar = 0;
		for (int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat a, mat &b)
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec &b)
{
	b[0] = a.x;
	b[1] = a.y;
	b[2] = 1;
}

void vec2point(vec a, point &b)
{
	b.x = ((float)a[0]) / a[2];
	b.y = ((float)a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec &c)
{
	c[0] = x;
	c[1] = y;
	c[2] = 1;
}

void unit(mat &a)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (i == j)
				a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat &c)
{
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, mat &c)
{
	unit(c);
	c[0][0] = cos(phi);
	c[0][1] = -sin(phi);
	c[1][0] = sin(phi);
	c[1][1] = cos(phi);
}

void scale(float S, mat &c)
{
	unit(c);
	c[0][0] = S;
	c[1][1] = S;
}

void rotate_centre(float Xa, float Ya, float phi, mat &c)
{
	unit(c);
	mat m, m1;
	move(Xa, Ya, m);
	rotate(phi, c);
	times(m, c, m1);
	unit(m);
	move(-Xa, -Ya, m);
	times(m1, m, c);
	/*
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] = cos(phi);
	c[0][2] = Xa*(1 - cos(phi)) + Ya*sin(phi);
	c[1][2] = Ya*(1 - cos(phi)) - Xa*sin(phi);
	*/
}

void scale2(float Sx, float Sy, mat &c)
{
	unit(c);
	c[0][0] = Sx;
	c[1][1] = Sy;
}

void frame(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &c)
{
	unit(c);
	mat c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;

	move(-Vcx, -Vcy, c1);
	times(c1, c, c2);

	scale2(Wx / Vx, Wy / Vy, c3);
	times(c3, c2, c4);

	unit(c5);
	c5[1][1] = -1;
	times(c5, c4, c6);

	move(Wcx, Wcy, c7);
	times(c7, c6, c8);

	set(c8, c);
}




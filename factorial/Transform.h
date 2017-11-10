#pragma once
value struct point {
	float x, y;
};
value struct line {
	point start, end;
	System::String^ name;
};

#define M 3
typedef float vec[M];
typedef float mat[M][M];

extern mat T;


void times(mat a, mat b, mat c);
void timesMatVec(mat a, vec b, vec c);
void set(mat a, mat b);
void point2vec(point a, vec b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec c);
void unit(mat a);
void move(float Tx, float Ty, mat c);
void rotate(float phi, mat c);
void scale(float S, mat c);
void miry(mat a);
void mirx(mat a);
void s1(float S, mat c);
void s2(float S, mat c);
void frame(float Vx, float Vy, float Vcx, float Vcy,
	float Wx, float Wy, float Wcx, float Wcy,
	mat c);
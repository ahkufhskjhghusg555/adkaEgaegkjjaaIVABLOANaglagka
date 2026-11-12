#include "MathUtils.h"

Vec2D::Vec2D(double X, double Y) {
	x = X;
	y = Y;
}
Vec2D::Vec2D() {
	x = 0;
	y = 0;
}
Vec2D Vec2D::operator+(const Vec2D& v) {

	return Vec2D(x + v.x, y + v.y);

}
Vec2D Vec2D::operator-(const Vec2D& v) {

	return Vec2D(x - v.x, y - v.y);

}
double Vec2D::operator*(const Vec2D& v) {

	return x * v.x + y * v.y;

}
Vec2D Vec2D::operator*(const double& k) {

	return Vec2D(x * k, y * k);

}
Vec2D Vec2D::operator/(const double& k) {

	return Vec2D(x / k, y / k);

}
double Vec2D::normsqr() {
	return x * x + y * y;
}
double Vec2D::norm() {
	return sqrt(x * x + y * y);
}
Vec2D Vec2D::normalize() {
	if (x == 0 and y == 0) {
		return (*this);
	}
	return (*this) / (this->norm());
}

Vec3D::Vec3D(double X, double Y, double Z) {
	x = X;
	y = Y;
	z = Z;
}
Vec3D::Vec3D() {
	x = 0;
	y = 0;
	z = 0;
}
Vec3D Vec3D::operator+(const Vec3D& v) {

	return Vec3D(x + v.x, y + v.y, z + v.z);

}
Vec3D Vec3D::operator-(const Vec3D& v) {

	return Vec3D(x - v.x, y - v.y, z - v.z);

}
double Vec3D::operator*(const Vec3D& v) {

	return x * v.x + y * v.y + z*v.z;

}
Vec3D Vec3D::operator*(const double& k) {

	return Vec3D(x * k, y * k, z * k);

}
Vec3D Vec3D::operator/(const double& k) {

	return Vec3D(x / k, y / k, z / k);

}
double Vec3D::normsqr() {
	return x * x + y * y + z * z;
}
double Vec3D::norm() {
	return sqrt(x * x + y * y + z * z);
}
Vec3D Vec3D::normalize() {
	if (x == 0 and y == 0) {
		return (*this);
	}
	return (*this) / (this->norm());
}

Particle::Particle() {
}

Particle::Particle(Vec3D pos, Vec3D vel) {
	position = pos;
	velocity = vel;
}

struct rgb convertToRGB(hsv in)
{
	float C = in.sat * in.val;
	float m = in.val - C;
	float X = C * (1 - fabsf(fmodf(in.hue / 60.0, 2.0) - 1));

	struct rgb _tmp(0, 0, 0);
	switch ((int)(in.hue / 60)) {
	case(0):
		_tmp.set(C, X, 0);
		break;
	case(1):
		_tmp.set(X, C, 0);
		break;
	case(2):
		_tmp.set(0, C, X);
		break;
	case(3):
		_tmp.set(0, X, C);
		break;
	case(4):
		_tmp.set(X, 0, C);
		break;
	case(5):
		_tmp.set(C, 0, X);
		break;
	}
	rgb out(_tmp.red + m, _tmp.green + m, _tmp.blue + m);
	return out;
}

Vec3D boxSpaceToRenderSpace(Vec3D position, Vec3D worldSize) {
	return position - worldSize * 0.5;
}
Vec3D cross(Vec3D a, Vec3D b) {
	return Vec3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

double clamp(double value, double minimum, double maximum) {
	return fmax(fmin(value, maximum), minimum);
}
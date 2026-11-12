#include <math.h>
#include <GLFW/glfw3.h>

#define M_PI 3.14159265358979323846

class Vec2D {

public:
	double x, y;
	Vec2D(double x, double y);
	Vec2D();

	Vec2D operator+(const Vec2D& v);
	Vec2D operator-(const Vec2D& v);
	double operator*(const Vec2D& v);
	Vec2D operator*(const double& k);
	Vec2D operator/(const double& k);

	double normsqr();
	double norm();

	Vec2D normalize();
};

class Vec3D {
public:
	double x, y, z;
	Vec3D(double x, double y, double z);
	Vec3D();

	Vec3D operator+(const Vec3D& v);
	Vec3D operator-(const Vec3D& v);
	double operator*(const Vec3D& v);
	Vec3D operator*(const double& k);
	Vec3D operator/(const double& k);

	double normsqr();
	double norm();

	Vec3D normalize();
};

class Particle {

public:

	Particle();
	Particle(Vec3D pos, Vec3D vel);

	Vec3D position, velocity;
	int id = -1;

};

struct rgb {
	float red, green, blue;
	struct rgb(float r, float g, float b) {
		red = r;
		green = g;
		blue = b;
	}
	void set(float r, float g, float b) {
		red = r;
		green = g;
		blue = b;
	}
};
struct hsv {
	float hue, sat, val;
	struct hsv(float h, float s, float v) {
		hue = h;
		sat = s;
		val = v;
	}
};

struct rgb convertToRGB(hsv in);

Vec3D boxSpaceToRenderSpace(Vec3D position, Vec3D worldSize);
Vec3D cross(Vec3D a, Vec3D b);

double clamp(double value, double minimum, double maximum);
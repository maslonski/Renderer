#ifndef INT3_H
#define INT3_H

struct int3
{
     union {
		 struct { int x, y, z; };
		 struct { int r, g, b; };
		 float p[3];
    };

    int3(): x(0), y(0), z(0) {}

    int3(int _x, int _y, int _z=0):
        x(_x), y(_y), z(_z) {}

    float &operator[](int idx) { return p[idx]; } // inaczej lekko niz na notatkach z szajerowych slajdow
};

#endif // INT3_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "complex.h"

using namespace std;

struct Color {
	unsigned char r, g, b;
};

Complex func(Complex z, Complex c) {
	Complex f = z * z + c;
	return f;
}


int main() {
    int width = 800, height = 800;
	float x0 = -2.0f, x1 = 2.0f;
	float y0 = -2.0f, y1 = 2.0f;

	Color* data = (Color*)malloc(sizeof(Color) * width * height);

	Complex z0 = {0, 0};

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
            z0 = {0, 0};
			Complex c = {x0 + (x1-x0) / width * i, y0 + (y1-y0) / width * j};
			Complex f = func(z0, c);
			for(int n = 0; n < 99; n++) {
                f = func(f, c);
            }
            float red = abs(f);
            if(red > 255) {
                red = 255;
            }
			data[i + width * j].r = 255 - red;
			data[i + width * j].g = 0;
			data[i + width * j].b = 0;
		}
	}

	FILE* file = fopen("mandelbrot.ppm", "wb");
	fprintf(file, "P6\n%d %d\n255\n", width, height);
	fwrite(data, sizeof(Color), height * width, file);
	fclose(file);

	free(data);

	return 0;
}

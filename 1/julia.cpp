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


int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Error: found %d arguments. Needs exactly 3", argc-1);
        return 1;
    }

	int width = 800, height = 800;
	float x0 = -2.0f, x1 = 2.0f;
	float y0 = -2.0f, y1 = 2.0f;

	Color* data = (Color*)malloc(sizeof(Color) * width * height);

	Complex c = {0, 0};
	int maxn = 0;
	sscanf(argv[1], "%f", &c.re);
	sscanf(argv[2], "%f", &c.im);
	sscanf(argv[3], "%d", &maxn);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Complex z = {x0 + (x1-x0) / width * i, y0 + (y1-y0) / width * j};
			Complex f = func(z, c);
			for(int n = 1; n < maxn; n++) {
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

	FILE* file = fopen("julia.ppm", "wb");
	fprintf(file, "P6\n%d %d\n255\n", width, height);
	fwrite(data, sizeof(Color), height * width, file);
	fclose(file);

	free(data);

	return 0;
}

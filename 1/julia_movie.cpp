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
    Complex c = {-1.5, -0.5};
	int max_time_steps = 150;
	Complex step = {0.01, 0.01};
	for (int time = 0; time < max_time_steps; time++)
	{
		c += step;
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				Complex z = {x0 + (x1-x0) / width * i, y0 + (y1-y0) / width * j};
				Complex f = func(z, c);
				for(int n = 0; n < 19; n++) {
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

		char filename[100];
		sprintf(filename, "animation/complex_%03d.ppm", time);

		FILE* file = fopen(filename, "wb");
		fprintf(file, "P6\n%d %d\n255\n", width, height);
		fwrite(data, sizeof(Color), height * width, file);
		fclose(file);
	}
	free(data);
}

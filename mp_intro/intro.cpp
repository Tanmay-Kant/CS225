#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <math.h>

void rotate(std::string inputFile, std::string outputFile) {
	cs225::PNG png3, png4;
	png3.readFromFile(inputFile);
	png4 = cs225::PNG(png3.width(), png3.height());
	for (unsigned x = 0; x < png3.width(); x++) {
		for (unsigned y = 0; y < png3.height(); y++) {
			cs225::HSLAPixel& inputPix = png3.getPixel(x, y);
			cs225::HSLAPixel& outputPix  = png4.getPixel(png3.width() - x - 1, png3.height() - y - 1);
			outputPix = inputPix;
		}
	}
	png4.writeToFile(outputFile);
  // TODO: Part 2
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
	double corruptPixel = 0;
  cs225::PNG png(width, height);
  // TODO: Part 3
	for (unsigned x = 0; x < png.width(); x++) {
		for (unsigned y = 0; y < png.height(); y++) {
			cs225::HSLAPixel & curPixel = png.getPixel(x, y);
			double intensity = tan(corruptPixel * x) * tan(corruptPixel * y);
			curPixel.h = intensity * 40 + 300 * (double(y) / double(height)) * (corruptPixel * 0.0075);
			curPixel.s = 1.0;
			curPixel.l = tan(double(y)/double(x));
			curPixel.a = 1.0;
			corruptPixel += 0.00125;
		}
	}
  return png;
}

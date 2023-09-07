#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

void Image::lighten() {
    /*Lighten an Image by increasing the luminance of every pixel by 0.1.
    This function ensures that the luminance remains in the range [0, 1].*/
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = std::min(1.0, pixel.l + 0.1);
        }
    }
}

void Image::lighten(double amount) {
    //same as lighten, where amount = the desired increase in luminance. 
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = std::min(1.0, pixel.l + amount);
        }
    }
}

void Image::darken() {
    //opposite of lighten
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = std::max(0.0, pixel.l - 0.1);
        }
    }
}

void Image::darken(double amount) {
    //opposite of lighten so - instead of +
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = std::max(0.0, pixel.l - amount);
        }
    }
}

void Image::saturate() {
    //same thing as lighten except use saturation instead of luminance
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = std::min(1.0, pixel.s + 0.1);
        }
    }
}

void Image::saturate(double amount) {
    //same thing as saturate but defined amount
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = std::min(1.0, pixel.s + amount);
        }
    }
}

void Image::desaturate() {
    //the opposite of saturate lol
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = std::max(0.0, pixel.s - 0.1);
        }
    }
}

void Image::desaturate(double amount) {
    //you get the idea, amount is defined for amount of loss of saturation
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = std::max(0.0, pixel.s - amount);
        }
    }
}

void Image::grayscale() {
    //no need for anything fancy just set saturation to 0 for all pixels
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = 0.0;
        }
    }
}

void Image::rotateColor(double degrees) {
    //mess with the hue by adding it, then run checks
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.h += degrees;
            //run a check for under 360 so that range falls between 0 and 360
            while (pixel.h < 0.0){
                pixel.h += 360.0;
            } 
            //run a check for over 360 so that range falls between 0 and 360
            while (pixel.h > 360.0){
                pixel.h -= 360.0;
            } 
        }
    }
}

void Image::illinify() {
    //literally copy from my lab_intro
    for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {

      HSLAPixel & pixel = getPixel(x, y);
      double currhue = pixel.h;
      //check for blue or orange
      if (currhue >= 113 && currhue < 293) {
        pixel.h = 216;
      }
      else {
        pixel.h = 11;
      }
        }
    }
}


void Image::scale(double factor) {
    Image same = Image(*this);
    //if not that then this
    unsigned scaledWidth = width() * factor;
    unsigned scaledHeight = height() * factor;
    resize(scaledWidth, scaledHeight);

    for (unsigned x = 0; x < scaledWidth; x ++) {
        for (unsigned y = 0; y < scaledHeight; y ++) {
            HSLAPixel & thisPixel = getPixel(x,y);
            //use same method as the art mp
            HSLAPixel & copyPixel = same.getPixel(x/factor, y/factor);
            thisPixel = copyPixel;
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    //take in w and h, then using the original width and height, call the scale function with the calculated factor as to not stretch
    double defScaledWidth = double(w) / width();
    double defScaledHeight = double(h) / height();
    double factor = std::min(defScaledWidth, defScaledHeight);
    scale(factor);
}

#include <iostream>
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include <vector>

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  array = new Image*[max];
  base = new Image(picture);
  max_ = max;
  x_axis = new unsigned[max];
  y_axis = new unsigned[max];
  for (unsigned i = 0; i < max_; i++){
    array[i] = NULL;
    x_axis[i] = 0;
    y_axis[i] = 0;
  }

}
StickerSheet::~StickerSheet(){
  clear();
  }

StickerSheet::StickerSheet(const StickerSheet &other){
copy(other);

}
void StickerSheet::clear(){
  if(array != NULL){
  for (unsigned i = 0; i < max_; i++){
        delete array[i];
    array[i] = NULL;
  }
}
  delete[] array;
  array = NULL;
  delete[] x_axis;
  x_axis = NULL;
  delete[] y_axis;
  y_axis = NULL;
}

void StickerSheet::copy(const StickerSheet &other){
  base = new Image(*other.base);
  max_ = other.max_;
  x_axis = new unsigned[max_];
  y_axis = new unsigned[max_];
  array = new Image*[max_];
  for (unsigned int i = 0; i < max_; i++){
    if(other.array[i] != NULL){
    array[i] = new Image(*other.array[i]);
    x_axis[i] = other.x_axis[i];
    y_axis[i] = other.y_axis[i];
  }
  else array[i] = NULL;
  }
}
const StickerSheet& StickerSheet::operator= (const StickerSheet&other){
  if(this!=&other){
  clear();
  copy(other);
}
return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){
  if(max == max_) {
    return;
  }
  Image ** temp = new Image*[max];
  unsigned * tempx = new unsigned[max];
  unsigned * tempy = new unsigned[max];
  if (max>max_){
    for (unsigned int i = 0; i < max_; i++){
    temp[i] = array[i];
    tempx[i] = x_axis[i];
    tempy[i] = y_axis[i];
  }
    for (unsigned int i = max_; i < max; i++){
      temp[i] = NULL;
      tempx[i] = 0;
      tempy[i] = 0;
    }
max_=max;
}
  else{

    for (unsigned int i = 0; i < max; i++){
      temp[i] = array[i];
      tempx[i] = x_axis[i];
      tempy[i] = y_axis[i];
        }
    for (unsigned i = max; i < max_;i++){
      delete array[i];
    }
  }
    delete[] array;
    array = temp;
    x_axis = tempx;
    y_axis = tempy;
    max_ = max;

  }



int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){

  for (unsigned i = 0; i < max_; i++){
    if (array[i] == NULL){
      array[i] = new Image(sticker);

      x_axis[i] = x;

      y_axis[i] = y;
      return i;
    }
  }
  return -1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if (index > max_-1)
    return false;
  if (array[index] == NULL)
      return false;
  else{
  x_axis[index] = x;
  y_axis[index] = y;
  return true;
  }
}
void StickerSheet::removeSticker(unsigned index){
  if (index > max_-1)
    return;
  if (array[index] == NULL)
    return;

  delete array[index];
  array[index] = NULL;
  x_axis[index] = 0;
  y_axis[index] = 0;
  return;

}
Image * StickerSheet::getSticker (unsigned index) const{

  if (index > max_-1){
    return NULL;
  }

  if (array[index] == NULL){
    return NULL;
}
  return array[index];

}
Image StickerSheet::render() const{

    unsigned int w_t = base->width();
    unsigned int h_t = base->height();
    for (unsigned int i=0; i < max_; i++){
      if(array[i] != NULL){
      unsigned w = x_axis[i] + array[i]->width();
      unsigned h = y_axis[i] + array[i]->height();

      if (w>w_t) w_t=w;
      if (h>h_t) h_t=h;
    }
  }

    Image *out = new Image(*base);
    out->resize(w_t, h_t);
    for (unsigned int i = 0; i < max_; i++){
      if(array[i] != NULL){
      for(unsigned int a = x_axis[i]; a < x_axis[i] + array[i]->width(); a++){
        for(unsigned int b = y_axis[i]; b < y_axis[i] + array[i]->height(); b++){
          HSLAPixel & picOut= out->getPixel(a,b);
          HSLAPixel & sticker = array[i]->getPixel(a - x_axis[i],b - y_axis[i]);
          if (sticker.a != 0){
            picOut= sticker;
          }
        }
      }
    }
}
    Image output = *out;
    delete out;
    return output;
}
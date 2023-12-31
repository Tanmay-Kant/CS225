/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace cs225;
//set up stickersheet class using doxygen
class StickerSheet{
    public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet& operator = (const StickerSheet&other);
    void changeMaxStickers(unsigned max);
    int addSticker (Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker (unsigned index) const;
    Image render() const;
    void copy(const StickerSheet &other);
    void clear();

    private:
    Image** array;
    Image *base;
    unsigned * x_axis;
    unsigned * y_axis;
    unsigned max_;

};

 

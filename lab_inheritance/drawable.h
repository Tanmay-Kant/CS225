/**
 * @file drawable.h
 * Declaration of the Drawable class.
 */

#pragma once

#include "cs225/PNG.h"

/**
 * A pure virtual interface class that can draw itself to a canvas
 */
class Drawable
{
  public:
//adding virtual to line below as it is not following definition above
   virtual ~Drawable()
    { /* Nothing */
    }

    /**
     * This method will draw the object onto the canvas.
     *
     * @param canvas to draw onto.
     */
    virtual void draw(cs225::PNG* canvas) const = 0;
};


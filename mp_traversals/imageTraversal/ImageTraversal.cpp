#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
    curr = Point(-1, -1);
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal_, Point point_){
  traversal = traversal_;
  curr = point_;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
    curr = traversal->pop();
    //right pixel
    if(curr.x + 1 < traversal->png_.width() && traversal->visited[curr.x + 1][curr.y] == false && calculateDelta(traversal->png_.getPixel(curr.x + 1, curr.y), traversal->png_.getPixel(traversal->start_.x, traversal->start_.y)) <= traversal->tolerance_){
      Point right(curr.x + 1, curr.y);
      traversal->add(right);
    }

    //below pixel
    if(curr.y + 1 < traversal->png_.height() && traversal->visited[curr.x][curr.y + 1] == false && calculateDelta(traversal->png_.getPixel(curr.x, curr.y + 1), traversal->png_.getPixel(traversal->start_.x, traversal->start_.y)) <= traversal->tolerance_){
      Point below(curr.x, curr.y + 1);
      traversal->add(below);
    }

    //left pixel
    if(curr.x > 0 && traversal->visited[curr.x - 1][curr.y] == false && calculateDelta(traversal->png_.getPixel(curr.x - 1, curr.y), traversal->png_.getPixel(traversal->start_.x, traversal->start_.y)) <= traversal->tolerance_){
      Point left(curr.x - 1, curr.y);
      traversal->add(left);
    }

    //above pixel
    if(curr.y > 0 && traversal->visited[curr.x][curr.y - 1] == false && calculateDelta(traversal->png_.getPixel(curr.x, curr.y - 1), traversal->png_.getPixel(traversal->start_.x, traversal->start_.y)) <= traversal->tolerance_){
      Point above(curr.x, curr.y - 1);
      traversal->add(above);
    }

    traversal->visited[curr.x][curr.y] = true;

    curr = traversal->peek();

    while(!traversal->pList.empty()){
      if(traversal->visited[curr.x][curr.y] == true){
        curr = traversal->pop();
        curr = traversal->peek();
      }
      else{
        break;
        }
    }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(this->curr == other.curr);
}


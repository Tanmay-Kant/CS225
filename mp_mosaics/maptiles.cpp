/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    vector<Point<3>> points;
    map<Point<3>, TileImage*> map_;
    for (TileImage& tile : theTiles) {
    	LUVAPixel pixel_ = tile.getAverageColor();
    	Point<3> point_ = convertToXYZ(pixel_);
    	points.push_back(point_);
    	map_[point_] = &tile;
    }
    KDTree<3> kdt_avgcolor(points);
    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (int i = 0; i < canvas->getRows(); i++) {
    	for (int j = 0; j < canvas->getColumns(); j++) {
    		Point<3> second_ = convertToXYZ(theSource.getRegionColor(i, j)); 
    		Point<3> first_ = kdt_avgcolor.findNearestNeighbor(second_); 
    		TileImage* found = map_[first_]; 
    		canvas->setTile(i, j, found); 
    	}
    }

    return canvas;

}


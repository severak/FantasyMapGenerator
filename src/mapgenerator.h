#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "extents2d.h"
#include "dcel.h"
#include "poissondiscsampler.h"
#include "voronoi.h"
#include "vertexmap.h"
#include "nodemap.h"

#include "jsoncons/json.hpp"

namespace gen {

class MapGenerator {

public:
    MapGenerator();
    MapGenerator(Extents2d extents, double resolution);

    void initialize();
    void normalize();
    void round();
    void relax();
    void setSeaLevel(double level);
    void setSeaLevelToMedian();
    void addHill(double px, double py, double radius, double height);
    void addCone(double px, double py, double radius, double height);
    void addSlope(double px, double py, double dirx, double diry, 
                  double radius, double height);

    void outputVoronoiDiagram(std::string filename);
    void outputVertices(std::string filename);
    void outputEdgeVertices(std::string filename);
    void outputInteriorVertices(std::string filename);
    void outputHeightMap(std::string filename);

private:
    jsoncons::json _getExtentsJSON();
    void _outputVertices(std::vector<dcel::Vertex> &verts, 
                         std::string filename);

    Extents2d _extents;
    double _resolution;

    dcel::DCEL _voronoi;
    VertexMap _vertexMap;
    NodeMap<double> _heightMap;
    bool _isInitialized = false;

    double _samplePadFactor = 1.5;

};

}

#endif
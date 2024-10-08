//
// Created by Pablo Deputter on 25/03/2021.
//

#include "ZBuffer.h"

ZBuffer::ZBuffer(const unsigned int width, const unsigned int height) {

    this->buffer = std::vector<std::vector<double>>(width,
                std::vector<double> (height, std::numeric_limits<double>::infinity()));
}

double ZBuffer::calculate_z_value(unsigned int i, unsigned int a, const double &Za, const double &Zb) {

    return ( (double)i / (double)a / (double)Za + ((double)1 - (double)i / (double)a) / (double)Zb);
}

bool ZBuffer::check_z_value(unsigned int width, unsigned int height, const double &z) {

    if (z < this->buffer[width][height]) {
        this->buffer[width][height] = z;
        return true;
    }
    return false;
}

std::vector<Face> ZBuffering::triangulate(const Face &face) {

    std::vector<Face> triangles;

    for (unsigned int i = 1; i <= face.get_point_indexes().size() - 2; i++) {

        Face face_i = Face({face.get_point_indexes()[0], face.get_point_indexes()[i], face.get_point_indexes()[i + 1]});
        triangles.emplace_back(face_i);
    }
    return triangles;
}

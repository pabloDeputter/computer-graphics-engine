//
// Created by Pablo Deputter on 22/02/2021.
//

#include "Line2D.h"
#include "ZBuffer.h"

void Line2D::line2D_scale(const double & x) {

    // Scale all points
    p1.setX(p1.getX()*x);
    p1.setY(p1.getY()*x);
    p2.setX(p2.getX()*x);
    p2.setY(p2.getY()*x);
}

void Line2D::line2D_move(const double & dx, const double & dy) {

    // Move all points
    p1.setX(p1.getX()+dx);
    p1.setY(p1.getY()+dy);
    p2.setX(p2.getX()+dx);
    p2.setY(p2.getY()+dy);
}

void Line2D::round() {

    // Round all points to int's
    p1.setX(static_cast<int>(std::round(p1.getX())));
    p1.setY(static_cast<int>(std::round(p1.getY())));
    p2.setX(static_cast<int>(std::round(p2.getX())));
    p2.setY(static_cast<int>(std::round(p2.getY())));
}

std::tuple<std::pair<double, double>, std::pair<double, double>> Line2D::Line2D_findMax(Lines2D &line2D) {

    double x = line2D.begin()->getP1().getX();
    double X = line2D.begin()->getP1().getX();

    double y = line2D.begin()->getP2().getY();
    double Y = line2D.begin()->getP2().getY();

    for (Line2D & i : line2D) {

        double p1x = i.getP1().getX();
        double p1y = i.getP1().getY();

        x = p1x < x ? p1x : x;
        y = p1y < y ? p1y : y;
        X = p1x > X ? p1x : X;
        Y = p1y > Y ? p1y : Y;

        double p2x = i.getP2().getX();
        double p2y = i.getP2().getY();

        x = p2x < x ? p2x : x;
        y = p2y < y ? p2y : y;
        X = p2x > X ? p2x : X;
        Y = p2y > Y ? p2y : Y;
    }
    return std::make_tuple(std::make_pair(x, y), std::make_pair(X, Y));
}

void Line2D::draw2DLines(Lines2D &line2D, const int &size, img::EasyImage & image, bool ZBuffering) {

    // Calculate x-min, y-min, x-max and y-max
    std::tuple<std::pair<double, double>, std::pair<double, double>> max_line2D = Line2D::Line2D_findMax(line2D);

    double x = std::get<0>(max_line2D).first;
    double y = std::get<0>(max_line2D).second;

    double X = std::get<1>(max_line2D).first;
    double Y = std::get<1>(max_line2D).second;

    // Calculate x-range, y-range
    double xrange = X - x;
    double yrange = Y - y;

    // Calculate max(xrange, yrange)
    double range = xrange > yrange ? xrange : yrange;

    // Calculate dimensions of image
    double image_x = size*(xrange/range);
    double image_y = size*(yrange/range);

    // Calculate scale-factor
    double d = 0.95*(image_x/xrange);

    // Multiply coordinates of all points with scale-factor
    for (Line2D & i : line2D) {
        i.line2D_scale(d);
    }

    double DC_x = d*((x + X)/2);
    double DC_y = d*((y + Y)/2);

    double dx = (image_x/2) - DC_x;
    double dy = (image_y/2) - DC_y;

    // Move all coordinates
    for (Line2D & i : line2D) {
        i.line2D_move(dx, dy);
    }

    // Round all points
    for (Line2D & i : line2D) {
        i.round();
    }

    // Change image dimensions
    image.image_resize(static_cast<int>(std::round(image_x)), static_cast<int>(std::round(image_y)));

    // Draw lines
    if (!ZBuffering) {
        for (Line2D & i : line2D) {

            std::tuple<double, double, double> color_values = i.getColor().getColor();
            image.draw_line(static_cast<int>(std::round(i.getP1().getX())),
                            static_cast<int>(std::round(i.getP1().getY())),
                            static_cast<int>(std::round(i.getP2().getX())),
                            static_cast<int>(std::round(i.getP2().getY())),
                            img::Color(std::get<0>(color_values),
                                    std::get<1>(color_values),
                                            std::get<2>(color_values)));
        }
    }
    else {
        ZBuffer buffer = ZBuffer((unsigned int)(std::round(image_x)), (unsigned int)(std::round(image_y)));


        for (Line2D & i : line2D) {

            std::tuple<double, double, double> color_values = i.getColor().getColor();

            image.draw_zbuf_line(buffer, (unsigned int)(std::round(i.getP1().getX())),
                                 (unsigned int)(std::round(i.getP1().getY())), i.getZ1(),
                                 (unsigned int)(std::round(i.getP2().getX())),
                                 (unsigned int)(std::round(i.getP2().getY())), i.getZ2(),
                                 img::Color(std::get<0>(color_values),
                                         std::get<1>(color_values),
                                                 std::get<2>(color_values)));
        }


    }
}

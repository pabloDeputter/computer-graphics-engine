//
// Created by Pablo Deputter on 08/03/2021.
//

#include "LSystem2D.h"


std::string LSystem_2D::generate_string(const LParser::LSystem & l_system, int iter, std::string & l_system_string) {

    // Base case of recursion
    if (iter == 0) return l_system_string;

    // Make new string
    std::string x;

    // Iterate over all char's
    for (const char & i : l_system_string) {
        if (i == '+' || i == '-' || i == '[' || i == ']' || i == '(' || i == ')') { // Ignore these char's
            x += i;
            continue;
        }
        else if (l_system.get_stochastic()) {
            x += l_system.get_replacement_stochastic(i);
            continue;
        }
        // Find replacement for char
        x += l_system.get_replacement(i);
    }
    // Enter recursion
    return generate_string(l_system, iter - 1, x);
}

Lines2D LSystem_2D::drawLSystem(LParser::LSystem2D & l_system_2D, const cc::Color & color) {

    int iter = l_system_2D.get_nr_iterations();
    std::string x = l_system_2D.get_initiator();

    // Generate full string
    std::string l_system_string = generate_string(l_system_2D, iter, x);

    double angle = l_system_2D.get_starting_angle() * M_PI / 180;

    Point2D starting_position = Point2D(0.0, 0.0);

    Lines2D l_system_lines;

    std::stack<std::pair<Point2D, double>> stack;

    for (const char & i : l_system_string) {
        // Rotate left
        if (i == '+') {
            angle += l_system_2D.get_angle() * M_PI / 180;
        }
            // Rotate right
        else if (i == '-') {
            angle -= l_system_2D.get_angle() * M_PI / 180;
        }

            // Push on stack
        else if (i == '(' || i == '[') {
            stack.push(std::make_pair(starting_position, angle));
        }
            // Pop the stack
        else if (i == ')' || i == ']') {
            starting_position = stack.top().first;
            angle = stack.top().second;
            stack.pop();
        }
        else {
            // Move forward
            Point2D old_position = starting_position;

            starting_position.setX(starting_position.getX() + std::cos(angle));
            starting_position.setY(starting_position.getY() + std::sin(angle));

            // "Draw" line
            if (l_system_2D.draw(i)) {
                Line2D y = Line2D(old_position, starting_position, color);
                l_system_lines.emplace_back(y);
            }
        }
    }
    return l_system_lines;
}


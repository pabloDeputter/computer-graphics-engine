//
// Created by Pablo Deputter on 22/03/2021.
//

#include "LSystem3D.h"
#include <fstream>

Figure LSystem_3D::drawLSystem(LParser::LSystem3D &l_system_3D) {

    unsigned int iter = l_system_3D.get_nr_iterations();
    std::string x = l_system_3D.get_initiator();

    // Generate full string
    std::string l_system_string = generate_string(l_system_3D, iter, x);

    // Hold lines in 3D-environment
    Figure l_system;

    // Holds current position (x,y,z)
    Vector3D current_position = Vector3D::point(0, 0, 0);

    // Holds current angle
    double current_angle = l_system_3D.get_angle() * M_PI / 180;

    // Current direction - initialized on x-axis
    Vector3D H = Vector3D::vector(1, 0, 0);
    // Perpendicular to H-vector, initialized on y-axis
    Vector3D L = Vector3D::vector(0, 1, 0);
    // Upwards direction - initialized on z-axis
    Vector3D U = Vector3D::vector(0, 0, 1);

    // Needed to store data in stack
    struct Data {
    public:
        Vector3D current_position;
        Vector3D H;
        Vector3D L;
        Vector3D U;

    public:
        Data(const Vector3D &currentPosition, const Vector3D &h, const Vector3D &l, const Vector3D &u)
                : current_position(currentPosition), H(h), L(l), U(u) {}

        virtual ~Data() = default;
    };


    std::ofstream out("../out.txt");

    std::stack<Data> stack_data;

    for (const char & i : l_system_string) {
        if (i == '+') {
            Vector3D H_ = H * cos(current_angle) + L * sin(current_angle);
            Vector3D L_ = -H * sin(current_angle) + L * cos(current_angle);
            H = H_;
            L = L_;
        }
        else if (i == '-') {
            Vector3D H_ = H * cos(-current_angle) + L * sin(-current_angle);
            Vector3D L_ =  -H * sin(-current_angle) + L * cos(-current_angle);
            H = H_;
            L = L_;
        }
        else if (i == '^') {
            Vector3D H_ = H * cos(current_angle) + U * sin(current_angle);
            Vector3D U_= -H * sin(current_angle) + U * cos(current_angle);
            H = H_;
            U = U_;
        }
        else if (i == '&') {
            Vector3D H_ = H * cos(-current_angle) + U * sin(-current_angle);
            Vector3D U_ = -H * sin(-current_angle) + U * cos(-current_angle);
            H = H_;
            U = U_;
        }
        else if (i == '\\') {
            Vector3D L_ = L*cos(current_angle) - U*sin(current_angle);
            Vector3D U_ = L*sin(current_angle) + U*cos(current_angle);
            L = L_;
            U = U_;
        }
        else if (i == '/') {
            Vector3D L_ = L * cos(-current_angle) - U * sin(-current_angle);
            Vector3D U_ = L * sin(-current_angle) + U * cos(-current_angle);
            L = L_;
            U = U_;
        }
        else if (i == '|') {
            H = -H;
            L = -L;
        }
        else if (i == '(') {
            // Push data on the stack
            stack_data.push(Data(current_position, H, L, U));
        }
        else if (i == ')') {
            // Retrieve data from stack and pop last added element (LIFO)
            current_position = stack_data.top().current_position;
            H = stack_data.top().H;
            L = stack_data.top().L;
            U = stack_data.top().U;
            // Pop data from stack
            stack_data.pop();
        }
        else {
            Vector3D new_position = current_position;
            current_position = current_position + H;

            if (l_system_3D.draw(i)) {
                // "Draw" line from old position to new position
                l_system.get_points().emplace_back(new_position);
                l_system.get_points().emplace_back(current_position);
                // Add to faces
                l_system.get_faces().emplace_back(Face({int(l_system.get_points().size() - 1),
                                                   int(l_system.get_points().size() - 2)}));
                continue;
            }
        }
    }

    out << H << " " << L << " " << U << std::endl;
    out << current_position << std::endl;
    out.close();

    return l_system;
}

std::string LSystem_3D::generate_string(const LParser::LSystem &l_system, int iter, std::string &l_system_string) {


    // Base case of recursion
    if (iter == 0) return l_system_string;

    // Make new string
    std::string x;

    // Iterate over all char's
    for (const char & i : l_system_string) {
        if (i == '+' || i == '-' || i == '[' || i == ']' || i == '(' || i == ')' ||
            i == '&' || i == '\\' || i == '/' || i == '|' || i == '^' ) { // Ignore these char's
            x += i;
            continue;
        }
        // Find replacement for char
        x += l_system.get_replacement(i);
    }
    // Enter recursion
    return generate_string(l_system, iter - 1, x);
}

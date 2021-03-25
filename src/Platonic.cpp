//
// Created by Pablo Deputter on 12/03/2021.
//

#include "Platonic.h"

Figure Platonic::cube() {

    // Origin is located in center of cube
    Figure cube;

    // Add point
    cube.add_point(std::make_tuple(1,-1,-1));
    cube.add_point(std::make_tuple(-1,1,-1));
    cube.add_point(std::make_tuple(1,1,1));
    cube.add_point(std::make_tuple(-1,-1,1));
    cube.add_point(std::make_tuple(1,1,-1));
    cube.add_point(std::make_tuple(-1,-1,-1));
    cube.add_point(std::make_tuple(1,-1,1));
    cube.add_point(std::make_tuple(-1,1,1));

    // Add faces 0 -> 1
    cube.get_faces().emplace_back(Face({1,5,3,7}));
    cube.get_faces().emplace_back(Face({5,2,8,3}));
    cube.get_faces().emplace_back(Face({2,6,4,8}));
    cube.get_faces().emplace_back(Face({6,1,7,4}));
    cube.get_faces().emplace_back(Face({7,3,8,4}));
    cube.get_faces().emplace_back(Face({1,6,2,5}));

    cube.correct_indexes();
    return cube;
}

Figure Platonic::tetrahedron() {

    Figure tetrahedron;

    tetrahedron.add_point(std::make_tuple(1,-1,-1));
    tetrahedron.add_point(std::make_tuple(-1,1,-1));
    tetrahedron.add_point(std::make_tuple(1,1,1));
    tetrahedron.add_point(std::make_tuple(-1,-1,1));

    tetrahedron.get_faces().emplace_back(Face({1,2,3}));
    tetrahedron.get_faces().emplace_back(Face({2,4,3}));
    tetrahedron.get_faces().emplace_back(Face({1,4,2}));
    tetrahedron.get_faces().emplace_back(Face({1,3,4}));

    tetrahedron.correct_indexes();
    return tetrahedron;
}

Figure Platonic::octahedron() {

    Figure octahedron;

    octahedron.add_point(std::make_tuple(1,0,0));
    octahedron.add_point(std::make_tuple(0,1,0));
    octahedron.add_point(std::make_tuple(-1,0,0));
    octahedron.add_point(std::make_tuple(0,-1,0));
    octahedron.add_point(std::make_tuple(0,0,-1));
    octahedron.add_point(std::make_tuple(0,0,1));

    octahedron.get_faces().emplace_back(Face({1,2,6}));
    octahedron.get_faces().emplace_back(Face({2,3,6}));
    octahedron.get_faces().emplace_back(Face({3,4,6}));
    octahedron.get_faces().emplace_back(Face({4,1,6}));
    octahedron.get_faces().emplace_back(Face({2,1,5}));
    octahedron.get_faces().emplace_back(Face({3,2,5}));
    octahedron.get_faces().emplace_back(Face({4,3,5}));
    octahedron.get_faces().emplace_back(Face({1,4,5}));

    octahedron.correct_indexes();
    return octahedron;
}

Figure Platonic::icosahedron() {

    Figure icosahedron;

    icosahedron.get_points().emplace_back(Vector3D::point(0, 0, sqrt(5) / 2));

    for (int i = 2; i < 7; ++i) {
        icosahedron.get_points().emplace_back(Vector3D::point(cos((i - 2) * 2 * M_PI / 5),
                                                              sin((i - 2) * 2 * M_PI / 5),
                                                              0.5));
    }
    for (int i = 7; i < 12; ++i) {
        icosahedron.get_points().emplace_back(
                Vector3D::point(cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5),
                                sin(M_PI / 5 + (i - 7) * 2 * M_PI / 5),
                                -0.5));
    }

    icosahedron.get_points().emplace_back(Vector3D::point(0, 0, -sqrt(5) / 2));

    icosahedron.get_faces().emplace_back(Face({1, 2, 3}));
    icosahedron.get_faces().emplace_back(Face({1, 3, 4}));
    icosahedron.get_faces().emplace_back(Face({1, 4, 5}));
    icosahedron.get_faces().emplace_back(Face({1, 5, 6}));
    icosahedron.get_faces().emplace_back(Face({1, 6, 2}));
    icosahedron.get_faces().emplace_back(Face({2, 7, 3}));
    icosahedron.get_faces().emplace_back(Face({3, 7, 8}));
    icosahedron.get_faces().emplace_back(Face({3, 8, 4}));
    icosahedron.get_faces().emplace_back(Face({4, 8, 9}));
    icosahedron.get_faces().emplace_back(Face({4, 9, 5}));
    icosahedron.get_faces().emplace_back(Face({5, 9, 10}));
    icosahedron.get_faces().emplace_back(Face({5, 10, 6}));
    icosahedron.get_faces().emplace_back(Face({6, 10, 11}));
    icosahedron.get_faces().emplace_back(Face({6, 11, 2}));
    icosahedron.get_faces().emplace_back(Face({2, 11, 7}));
    icosahedron.get_faces().emplace_back(Face({12, 8, 7}));
    icosahedron.get_faces().emplace_back(Face({12, 9, 8}));
    icosahedron.get_faces().emplace_back(Face({12, 10, 9}));
    icosahedron.get_faces().emplace_back(Face({12, 11, 10}));
    icosahedron.get_faces().emplace_back(Face({12, 7, 11}));

    icosahedron.correct_indexes();

    return icosahedron;
}

Figure Platonic::dodecahedron() {

    Figure dodecahedron;
    Figure ico = icosahedron();

    // Traverse faces of icosahedron
    for (const Face & i : ico.get_faces()) {

        // Take middle of each coordinate
        double x = (ico.get_points()[i.get_point_indexes()[0]].x +
                    ico.get_points()[i.get_point_indexes()[1]].x +
                    ico.get_points()[i.get_point_indexes()[2]].x) / 3;

        double y = (ico.get_points()[i.get_point_indexes()[0]].y +
                    ico.get_points()[i.get_point_indexes()[1]].y +
                    ico.get_points()[i.get_point_indexes()[2]].y) / 3;

        double z = (ico.get_points()[i.get_point_indexes()[0]].z +
                    ico.get_points()[i.get_point_indexes()[1]].z +
                    ico.get_points()[i.get_point_indexes()[2]].z) / 3;

        dodecahedron.add_point_double(std::make_tuple(x,y,z));
    }

    dodecahedron.get_faces().emplace_back(Face({1,2,3,4,5}));
    dodecahedron.get_faces().emplace_back(Face({1,6,7,8,2}));
    dodecahedron.get_faces().emplace_back(Face({2,8,9,10,3}));
    dodecahedron.get_faces().emplace_back(Face({3,10,11,12,4}));
    dodecahedron.get_faces().emplace_back(Face({4,12,13,14,5}));
    dodecahedron.get_faces().emplace_back(Face({5,14,15,6,1}));
    dodecahedron.get_faces().emplace_back(Face({20,19,18,17,16}));
    dodecahedron.get_faces().emplace_back(Face({20,15,14,13,19}));
    dodecahedron.get_faces().emplace_back(Face({19,13,12,11,18}));
    dodecahedron.get_faces().emplace_back(Face({18,11,10,9,17}));
    dodecahedron.get_faces().emplace_back(Face({17,9,8,7,16}));
    dodecahedron.get_faces().emplace_back(Face({16,7,6,15,20}));

    dodecahedron.correct_indexes();
    return dodecahedron;
}

void Platonic::create_triangles(Figure & ico) {

    // Store new faces for sphere
    std::vector<Face> faces;

    for (Face & i : ico.get_faces()) {

        // Triangle "ABC"
        Vector3D & a = ico.get_points()[i.get_point_indexes()[0]];
        Vector3D & b = ico.get_points()[i.get_point_indexes()[1]];
        Vector3D & c = ico.get_points()[i.get_point_indexes()[2]];

        // Calculate points D, E, F
        Vector3D d = Vector3D::point( (a.x + b.x) / 2,
                                      (a.y + b.y) / 2,
                                      (a.z + b.z) / 2 );

        Vector3D e = Vector3D::point( (a.x + c.x) / 2,
                                     (a.y + c.y) / 2,
                                     (a.z + c.z) / 2 );

        Vector3D f = Vector3D::point( (c.x + b.x) / 2,
                                     (c.y + b.y) / 2,
                                     (c.z + b.z) / 2 );

        // Push back points D, E, F
        ico.get_points().push_back(d);
        ico.get_points().push_back(e);
        ico.get_points().push_back(f);

        // Get face_indexes off points A, B, C
        const int A = i.get_point_indexes()[0];
        const int B = i.get_point_indexes()[1];
        const int C = i.get_point_indexes()[2];

        // Get face_indexes off points D, F, E
        const int D = ico.get_points().size()-3;
        const int E = ico.get_points().size()-2;
        const int F = ico.get_points().size()-1;

        // Add triangles to faces

        // ADE
        faces.emplace_back(Face({A,D,E}));
        // BFD
        faces.emplace_back(Face({B,F,D}));
        // CEF
        faces.emplace_back(Face({C,E,F}));
        // DFE
        faces.emplace_back(Face({D,F,E}));
    }

    ico.clear_faces();
    ico.get_faces() = faces;
}

Figure Platonic::sphere(const int & n) {

    Figure sphere = icosahedron();
    // Create triangles
    for (int i = 0; i != n; i++) {
        Platonic::create_triangles(sphere);
    }
    // Rescale
    for (Vector3D & i : sphere.get_points()) {
        i.normalise();
    }
    return sphere;
}

Figure Platonic::cone(const int &n, const double &h) {

    Figure cone;

    // 0 - n points (ground)
    for (int i = 0; i != n; i++) {
        cone.add_point_double(std::make_tuple(cos(2 * i * M_PI / n),
                                              sin(2 * i * M_PI / n),
                                              0));
    }

    // n + 1 point (top)
    cone.add_point_double(std::make_tuple(0, 0, h));

    // 0 - n faces (from ground to top)
    for (int i = 0; i != n; i++) {
        cone.get_faces().emplace_back(Face({n, i % n, (i + 1) % n}));
    }

    return cone;
}

Figure Platonic::cylinder(const int &n, const double &h) {

    Figure cylinder;

    // 2n points
    for (int i = 0; i != n; i++) {
        // Ground surface
        cylinder.add_point_double(std::make_tuple(cos(2 * i * M_PI / n),
                                              sin(2 * i * M_PI / n),
                                              0));
        // Not ground surfcae
        cylinder.add_point_double(std::make_tuple(cos(2 * i * M_PI / n),
                                              sin(2 * i * M_PI / n),
                                              h));
    }

    // Surfaces of cylinder
    for (int i = 0; i != 2 * n; i = i + 2) {
        // counter clockwise TODO
        cylinder.get_faces().emplace_back(Face({(i + 2) % (2 * n),
                                                (i + 3) % (2 * n),
                                                (i + 1) % (2 * n),
                                                i % (2 * n)}));
//        std::cout << i % (2 * n) << std::endl;
//        std::cout << (i+1) % (2 * n) << std::endl;
//        std::cout << (i+2) % (2 * n) << std::endl;
//        std::cout << (i+3) % (2 * n) << std::endl;
//        std::cout << "iunr^^foazrbfpuauz" << std::endl;
    }

    return cylinder;
}

Figure Platonic::torus(const double &r, const double &R, const int &n, const int &m) {

    Figure torus;

    for (int i = 0; i != n; i++) {

        double u = 2 * i * M_PI / n;

        for (int j = 0; j != m; j++) {

            double v = 2 * j * M_PI / m;

            torus.add_point_double(std::make_tuple( (R + r * cos(v) ) * cos(u),
                                                      (R + r * cos(v) ) * sin(u),
                                                      r * sin(v) ) );

            // i max = n, j max = m
            const int a1 = i * m + j;
            const int a2 = (i + 1) % n * m + j;
            const int a3 = (i + 1) % n * m + (j + 1) % m;
            const int a4 = i * m + (j + 1) % m;

            torus.get_faces().emplace_back(Face({a1, a2, a3, a4}));
        }
    }


    // torus.correct_indexes();

    return torus;
}

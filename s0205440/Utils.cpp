//
// Created by Pablo Deputter on 27/03/2021.
//

#include "Utils.h"

void Utils::fractal(Figure & figure, Figures3D & fractal, const int iter, const double & scale) {

    fractal.emplace_back(figure);
    int i = iter;

    while (i != 0) {
        Figures3D fractal_new;

        for (Figure& fig : fractal) {

            for (unsigned int j = 0; j < fig.get_points().size(); j++) {

                Figure figure_new = fig;

                Matrix matrix_scale = Figure::scale_figure(1 / scale);
                figure_new.apply_transformation(matrix_scale);

                Vector3D point_i = fig.get_points()[j];
                Vector3D point_i_ = figure_new.get_points()[j];

                Matrix matrix_translate = Figure::translate(point_i - point_i_);
                figure_new.apply_transformation(matrix_translate);

                fractal_new.emplace_back(figure_new);
            }

        }
        fractal = fractal_new;
        i = i - 1;
    }
}

void Utils::generate_lines(Figures3D & figures, Lines2D & figures_lines, const Matrix & trans_matrix) {

    for (Figure & fig : figures) {

        fig.apply_transformation(trans_matrix);
        Lines2D figure_lines = fig.do_projection();
        figures_lines.splice(figures_lines.end(), figure_lines);
    }
}

void Utils::clipping_near_far(std::vector<Face> &new_faces, const Face &j, Figure &i, const double &d_val) {

    if (i.get_points()[j.get_point_indexes()[0]].z > d_val && i.get_points()[j.get_point_indexes()[1]].z > d_val &&
        i.get_points()[j.get_point_indexes()[2]].z > d_val) {

        new_faces.emplace_back(j);
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[1]].z < d_val &&
             i.get_points()[j.get_point_indexes()[2]].z < d_val) {

        // DO NOTHING
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[1]].z < d_val){

        double p = d_val - i.get_points()[j.get_point_indexes()[2]].z / i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[2]].z;

        double p_ = d_val - i.get_points()[j.get_point_indexes()[2]].z / i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[2]].z;

        std::cout << p << std::endl;

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[2]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[1]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[2]};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[2]].z < d_val){

        double p = d_val - i.get_points()[j.get_point_indexes()[1]].z / i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[1]].z;

        double p_ = d_val - i.get_points()[j.get_point_indexes()[1]].z / i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[1]].z;

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[1]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[1]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), j.get_point_indexes()[1], (int)(i.get_points().size() - 1)};
        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());

    }

    else if (i.get_points()[j.get_point_indexes()[1]].z < d_val && i.get_points()[j.get_point_indexes()[2]].z < d_val){

        double p = d_val - i.get_points()[j.get_point_indexes()[0]].z / i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[0]].z;

        double p_ = d_val - i.get_points()[j.get_point_indexes()[0]].z / i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[0]].z;

        Vector3D S = p * i.get_points()[j.get_point_indexes()[1]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[0]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0], (int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1)};
        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val) {

        double p = d_val - i.get_points()[j.get_point_indexes()[1]].z / i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[1]].z;

        double p_ = d_val - i.get_points()[j.get_point_indexes()[2]].z / i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[2]].z;

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[1]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[0]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[1], j.get_point_indexes()[2]};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[1]].z < d_val) {

        double p = d_val - i.get_points()[j.get_point_indexes()[0]].z / i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[0]].z;

        double p_ = d_val - i.get_points()[j.get_point_indexes()[2]].z / i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[2]].z;

        Vector3D S = p * i.get_points()[j.get_point_indexes()[1]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[1]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0],(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[2]};
        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[2]].z < d_val) {

        double p = d_val - i.get_points()[j.get_point_indexes()[0]].z / i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[0]].z;

        double p_ = d_val - i.get_points()[j.get_point_indexes()[1]].z / i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[1]].z;

        Vector3D S = p * i.get_points()[j.get_point_indexes()[2]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[1]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0], j.get_point_indexes()[1], (int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1)};
        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }
}

void Utils::clipping_left_right(std::vector<Face> &new_faces, const Face &j, Figure &i, const double &d_val, const clipping_data & clippingData) {

    if (i.get_points()[j.get_point_indexes()[0]].z > d_val && i.get_points()[j.get_point_indexes()[1]].z > d_val &&
        i.get_points()[j.get_point_indexes()[2]].z > d_val) {

        new_faces.emplace_back(j);
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[1]].z < d_val &&
             i.get_points()[j.get_point_indexes()[2]].z < d_val) {

        // DO NOTHING
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[1]].z < d_val){

        double p = (i.get_points()[j.get_point_indexes()[2]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[2]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[2]].x - i.get_points()[j.get_point_indexes()[0]].x) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[0]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[2]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[2]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[2]].x - i.get_points()[j.get_point_indexes()[1]].x) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[1]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[2]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[1]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[2]};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[2]].z < d_val){

        double p = (i.get_points()[j.get_point_indexes()[1]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[1]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[1]].x - i.get_points()[j.get_point_indexes()[0]].x) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[0]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[1]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[1]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[1]].x - i.get_points()[j.get_point_indexes()[2]].x) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[2]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[1]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[1]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), j.get_point_indexes()[1], (int)(i.get_points().size() - 1)};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[1]].z < d_val && i.get_points()[j.get_point_indexes()[2]].z < d_val){

        double p = (i.get_points()[j.get_point_indexes()[0]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[0]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[0]].x - i.get_points()[j.get_point_indexes()[1]].x) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[1]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[0]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[0]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[0]].x - i.get_points()[j.get_point_indexes()[2]].x) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[2]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[1]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[0]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0], (int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1)};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val) {

        double p = (i.get_points()[j.get_point_indexes()[1]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[1]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[1]].x - i.get_points()[j.get_point_indexes()[0]].x) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[0]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[2]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[2]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[2]].x - i.get_points()[j.get_point_indexes()[0]].x) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[0]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[1]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[0]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[1], j.get_point_indexes()[2]};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[1]].z < d_val) {

        double p = (i.get_points()[j.get_point_indexes()[0]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[0]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[0]].x - i.get_points()[j.get_point_indexes()[1]].x) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[1]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[2]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[2]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[2]].x - i.get_points()[j.get_point_indexes()[1]].x) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[1]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[1]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[1]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0],(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[2]};
        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[2]].z < d_val) {

        double p = (i.get_points()[j.get_point_indexes()[0]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[0]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[0]].x - i.get_points()[j.get_point_indexes()[2]].x) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[2]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[1]].x * clippingData.d_near + i.get_points()[j.get_point_indexes()[1]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[1]].x - i.get_points()[j.get_point_indexes()[2]].x) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[2]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[2]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[1]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0], j.get_point_indexes()[1], (int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1)};
        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

}

void Utils::clipping_top_bottom(std::vector<Face> &new_faces, const Face &j, Figure &i, const double &d_val,
                                const clipping_data &clippingData) {


    if (i.get_points()[j.get_point_indexes()[0]].z > d_val && i.get_points()[j.get_point_indexes()[1]].z > d_val &&
        i.get_points()[j.get_point_indexes()[2]].z > d_val) {

        new_faces.emplace_back(j);
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[1]].z < d_val &&
             i.get_points()[j.get_point_indexes()[2]].z < d_val) {

        // DO NOTHING
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[1]].z < d_val){

        double p = (i.get_points()[j.get_point_indexes()[2]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[2]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[2]].y - i.get_points()[j.get_point_indexes()[0]].y) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[0]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[2]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[2]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[2]].y - i.get_points()[j.get_point_indexes()[1]].y) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[1]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[2]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[1]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[2]};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val && i.get_points()[j.get_point_indexes()[2]].z < d_val){

        double p = (i.get_points()[j.get_point_indexes()[1]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[1]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[1]].y - i.get_points()[j.get_point_indexes()[0]].y) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[0]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[1]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[1]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[1]].y - i.get_points()[j.get_point_indexes()[2]].y) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[2]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[1]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[1]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), j.get_point_indexes()[1], (int)(i.get_points().size() - 1)};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[1]].z < d_val && i.get_points()[j.get_point_indexes()[2]].z < d_val){

        double p = (i.get_points()[j.get_point_indexes()[0]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[0]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[0]].y - i.get_points()[j.get_point_indexes()[1]].y) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[1]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[0]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[0]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[0]].y - i.get_points()[j.get_point_indexes()[2]].y) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[2]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[1]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[0]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0], (int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1)};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[0]].z < d_val) {

        double p = (i.get_points()[j.get_point_indexes()[1]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[1]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[1]].y - i.get_points()[j.get_point_indexes()[0]].y) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[0]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[2]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[2]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[2]].y - i.get_points()[j.get_point_indexes()[0]].y) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[0]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[0]] + (1 - p) * i.get_points()[j.get_point_indexes()[1]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[0]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[1], j.get_point_indexes()[2]};

        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[1]].z < d_val) {

        double p = (i.get_points()[j.get_point_indexes()[0]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[0]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[0]].y - i.get_points()[j.get_point_indexes()[1]].y) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[1]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[2]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[2]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[2]].y - i.get_points()[j.get_point_indexes()[1]].y) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[2]].z - i.get_points()[j.get_point_indexes()[1]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[1]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[1]] + (1 - p_) * i.get_points()[j.get_point_indexes()[2]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0],(int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1), j.get_point_indexes()[2]};
        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }

    else if (i.get_points()[j.get_point_indexes()[2]].z < d_val) {

        double p = (i.get_points()[j.get_point_indexes()[0]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[0]].z * d_val) /
                   ((i.get_points()[j.get_point_indexes()[0]].y - i.get_points()[j.get_point_indexes()[2]].y) * clippingData.d_near +
                    (i.get_points()[j.get_point_indexes()[0]].z - i.get_points()[j.get_point_indexes()[2]].z) * d_val);

        double p_ = (i.get_points()[j.get_point_indexes()[1]].y * clippingData.d_near + i.get_points()[j.get_point_indexes()[1]].z * d_val) /
                    ((i.get_points()[j.get_point_indexes()[1]].y - i.get_points()[j.get_point_indexes()[2]].y) * clippingData.d_near +
                     (i.get_points()[j.get_point_indexes()[1]].z - i.get_points()[j.get_point_indexes()[2]].z) * d_val);

        Vector3D S = p * i.get_points()[j.get_point_indexes()[2]] + (1 - p) * i.get_points()[j.get_point_indexes()[0]];

        Vector3D S_ = p_ * i.get_points()[j.get_point_indexes()[2]] + (1 - p_) * i.get_points()[j.get_point_indexes()[1]];

        i.get_points().emplace_back(S);
        i.get_points().emplace_back(S_);

        std::vector<int> new_face = {j.get_point_indexes()[0], j.get_point_indexes()[1], (int)(i.get_points().size() - 2), (int)(i.get_points().size() - 1)};
        Face a(new_face);

        std::vector<Face> triangles = ZBuffering::triangulate(a);
        new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
    }
}

std::tuple<double, double, double, double, double> Utils::prep_zbuffering(Figures3D &figures, Lines2D &figures_lines,
                                                                            const Matrix &trans_eye_matrix, const int size,
                                                                          bool clipping, const clipping_data & clippingData) {

    figures_lines.clear();

    // Traverse figures and triangulate every face
    for (Figure & i : figures) {

        std::vector<Face> new_faces;

        for (Face & j : i.get_faces()) {

            std::vector<Face> triangles = ZBuffering::triangulate(j);
            new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
        }
        i.get_faces().clear();
        i.get_faces() = new_faces;
    }

    if (clipping) {

        for (Figure & i : figures) {

            std::vector<Face> new_faces;

            for (Face & j : i.get_faces()) {

                Utils::clipping_near_far(new_faces, j, i, clippingData.d_near * (-1.0));
                Utils::clipping_near_far(new_faces, j, i, clippingData.d_far * (-1.0));
                Utils::clipping_left_right(new_faces, j, i,
                                           (static_cast<double>(clippingData.d_near) / 2) * (-1.0), clippingData);
                Utils::clipping_left_right(new_faces, j, i,
                                            static_cast<double>(clippingData.d_near) / 2, clippingData);
                Utils::clipping_top_bottom(new_faces, j, i,
                                           (static_cast<double>(clippingData.d_near) / 2) * (-1.0), clippingData);
                Utils::clipping_top_bottom(new_faces, j, i,
                                           static_cast<double>(clippingData.d_near) / 2, clippingData);

            }
            i.get_faces().clear();
            i.get_faces() = new_faces;
            std::cout << new_faces.size() << std::endl;
        }
    }

    Utils::generate_lines(figures, figures_lines, trans_eye_matrix);

    // Calculate x-min, y-min, x-max and y-max
    std::tuple<std::pair<double, double>, std::pair<double, double>> max_line2D = Line2D::Line2D_findMax(figures_lines);

    double x = std::get<0>(max_line2D).first;
    double y = std::get<0>(max_line2D).second;

    double X = std::get<1>(max_line2D).first;
    double Y = std::get<1>(max_line2D).second;

    // Calculate x-range, y-range
    double xrange = X - x;
    double yrange = Y - y;

    double _size = static_cast<double>(std::round(size));

    // Calculate dimensions of image
    double image_x = _size * (xrange / std::max(xrange, yrange) );
    double image_y = _size * (yrange / std::max(xrange, yrange) );

    // Calculate scale-factor
    double d = 0.95 * (image_x / xrange);

    double a = x + X;
    double b = y + Y;

    double DC_x = d * (a / static_cast<double>(2) );
    double DC_y = d * (b / static_cast<double>(2) );

    double dx = (image_x / static_cast<double>(2) ) - DC_x;
    double dy = (image_y / static_cast<double>(2) ) - DC_y;

    return std::make_tuple(image_x, image_y, d, dx, dy);
}
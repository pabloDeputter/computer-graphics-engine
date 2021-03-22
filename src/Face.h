//
// Created by Pablo Deputter on 05/03/2021.
//

#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H

#include <utility>
#include <vector>

class Face {

private:
    /**
     * \brief Each index refers to a point in the "points" vector of a Figure-object
     */
    std::vector<int> point_indexes;
public:
    explicit Face(std::vector<int> x) : point_indexes(x) {}

    const std::vector<int> &get_point_indexes() const {
        return point_indexes;
    }

    void correct_indexes() {

        for (int & i : point_indexes) {
            i--;
        }
    }

};


#endif //ENGINE_FACE_H

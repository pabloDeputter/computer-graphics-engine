//
// Created by Pablo Deputter on 05/03/2021.
//

#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H

#include <utility>
#include <vector>

/**
 * @brief The Face class
 */
class Face {

private:
    /**
     * \brief Each index refers to a point in the "points" vector of a Figure-object
     */
    std::vector<int> point_indexes;
public:
    /**
     * @brief Constructor for Face object
     *
     * @param x std::vector of int
     */
    explicit Face(const std::vector<int> &x) : point_indexes(x) {}

    /**
     * @brief Get point indexes
     *
     * @return point_indexes as const by reference
     */
    const std::vector<int> &get_point_indexes() const {
        return point_indexes;
    }

    /**
     * @brief Correct indexes of Face by reducing every index by 1
     */
    void correct_indexes() {
        for (int &i : point_indexes) {
            i--;
        }
    }
};


#endif //ENGINE_FACE_H

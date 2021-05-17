//
// Created by Pablo Deputter on 22/03/2021.
//

#ifndef ENGINE_LSYSTEM3D_H
#define ENGINE_LSYSTEM3D_H

#include <stack>
#include "l_parser.h"
#include "Figure.h"

namespace LSystem_3D {

    /**
     * \brief           Converts a LSystem to a list of Lines2D objects representing straight lines
    * @param l_system_3D  LSystem containing all the data that is needed to replace char's in the string by replacement rules
    */
    Figure drawLSystem(LParser::LSystem3D &l_system_3D);

    /**
    * \brief            Generate LSystem string recursively
    *
    * \param l_system 	LSystem containing all the data that is needed to replace char's in the string by replacement rules
    * \param iter       Amount of iterations that generate_string needs to be called
    * \param l_system_string Original string containing the initiator of the LSystem, will be passed trough recursively
    */
    std::string generate_string(const LParser::LSystem &l_system, int iter, std::string &l_system_string);

};

#endif //ENGINE_LSYSTEM3D_H

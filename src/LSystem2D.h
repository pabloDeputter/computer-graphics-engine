//
// Created by Pablo Deputter on 08/03/2021.
//

#ifndef ENGINE_LSYSTEM2D_H
#define ENGINE_LSYSTEM2D_H


#include <stack>
#include "l_parser.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"


namespace LSystem_2D {

    /**
    * \brief            Generate LSystem string recursively
    *
    * \param l_system 	LSystem containing all the data that is needed to replace char's in the string by replacement rules
    * \param iter       Amount of iterations that generate_string needs to be called
    * \param l_system_string Original string containing the initiator of the LSystem, will be passed trough recursively
    */
    std::string generate_string(const LParser::LSystem & l_system, int iter, std::string & l_system_string);

    /**
     * \brief           Converts a LSystem to a list of Lines2D objects representing straight lines
     * @param l_system_2D  LSystem containing all the data that is needed to replace char's in the string by replacement rules
     * @param color     Color of lines that need to be drawn
     */
    Lines2D drawLSystem(LParser::LSystem2D & l_system_2D, const cc::Color & color);

};


#endif //ENGINE_LSYSTEM2D_H

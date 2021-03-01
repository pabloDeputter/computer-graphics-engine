#include "easy_image.h"
#include "ini_configuration.h"
#include <fstream>
#include <unistd.h>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include "l_parser.h"

using namespace std;

/**
 * \brief Scales colors of vector
 * \param colors Vector with color values in 0-1 range
 * \return Vector of colors in 0-256 range in img::Color object
 */
img::Color scale_colors(std::vector<double> & colors) {

    for (double & i : colors) {
        i = i*255;
    }
    return img::Color(colors[0], colors[1], colors[2]);
}

/**
 * \brief Read a LSystem2D file in
 * \param file_name Name of input-file
 * \return LSystem2D object-type
 */
LParser::LSystem2D LSystem2D(const std::string & file_name) {

    LParser::LSystem2D l_system;

    std::ifstream input_stream(file_name);
    input_stream >> l_system;
    input_stream.close();
    return l_system;

}

/**
 * \brief Generates a image off a .ini file
 * \return EasyImage object-type
 */
img::EasyImage generate_image(const ini::Configuration &configuration) {

    // General data for every image
    std::string type = configuration["General"]["type"].as_string_or_die();
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> bg = configuration["General"]["backgroundcolor"].as_double_tuple_or_default({0, 0, 0});

    // Create new image
    img::EasyImage image = img::EasyImage(size, size, scale_colors(bg));

    // 2DLSystem as type
    if (type == "2DLSystem") {
        std::string file_name = configuration[type]["inputfile"].as_string_or_die();
        std::vector<double> color = configuration[type]["color"].as_double_tuple_or_default({0, 0, 0});
        LParser::LSystem2D l_system = LSystem2D(file_name);
        image.drawLSystem(l_system, size, scale_colors(color));
    }
    return image;
}

int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                for(int i = 1; i < argc; ++i)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(argv[i]);
                                std::cout << argv[i] << std::endl;

                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string fileName(argv[i]);
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << argv[i] << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}

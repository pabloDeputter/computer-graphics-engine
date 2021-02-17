#include "easy_image.h"
#include "ini_configuration.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;


// Scale colors to RGB-values
img::Color blocks_scaleColors(vector<double> & toScale) {

    for (double & i : toScale) {
        if (i == 1.0) {
            i = (i-0.01)*256;
            continue;
        }
        i = i*256;
    }

    img::Color color = img::Color(toScale[0], toScale[1], toScale[2]);
    return color;
}

// Calculate distance between two lines of line structure
pair<double, double> lines_calculateLine(const int & Hi, const int & Wi, const int & N) {

    // Calculate distance between two adjacent lines
    double Hs = Hi/(N-1);
    double Ws = Wi/(N-1);

    return make_pair(Hs, Ws);
}

// Draw quarter circle
int lines_quarterCircle(img::EasyImage & image, const int & Hi, const int & Wi, const int & N, const img::Color & color_lines, const img::Color & color_bg, const bool & inverse) {

    // Calculate distance between two adjacent lines
    pair<double, double> lineDimension = lines_calculateLine(Hi, Wi, N);
    int Hs = lineDimension.first;
    int Ws = lineDimension.second;

    int x1 = 0;
    int y2 = Hi - 1;

    int y1 = 0;
    int lim_y1 = Hi;
    int _y1 = -1;

    int x2 = 0;
    int lim_x2 = Wi;
    int _x2 = -1;

    if (inverse) {
        x1 = Wi - 1;
        y2 = 0;

        y1 = Hi - 1;
        lim_y1 = 0;
        _y1 = 1;

        x2 = Wi - 1;
        lim_x2 = 0;
        _x2 = 1;

        Hs = Hs * -1;
        Ws = Ws * -1;

    }

    int i = 0;
    for (i, y1, x2; i < N; i++, y1 += Hs, x2 += Ws) {

        if (y1 == lim_y1) y1 += _y1;
        if (y1 <= 0) y1 = 0;

        if (x2 == lim_x2) x2 += _x2;
        if (x2 <= 0) x2 = 0;

        image.draw_line(x1, y1, x2, y2, color_lines);
    }

    return 0;
}

// Draw line consisting of 2 quarter circles
int lines_eye(img::EasyImage & image, const int & Hi, const int & Wi, const int & N, const img::Color & color_lines, const img::Color & color_bg) {

    lines_quarterCircle(image, Hi, Wi, N, color_lines, color_bg, false);
    lines_quarterCircle(image, Hi, Wi, N, color_lines, color_bg, true);


    return 0;
}

// Helper function to draw diamond
int lines_diamond_helper(img::EasyImage & image, const int & Hi, const int & Wi, const int & N, const img::Color & color_lines, const bool & inverse) {

    // Calculate distance between two adjacent lines
    pair<double, double> lineDimension = lines_calculateLine(Hi/2, Wi/2, N);
    int Hs = lineDimension.first;
    int Ws = lineDimension.second;

    int x1 = Wi/2;
    int y1 = Hi/2;

    int x2 = Wi/2;
    int y2 = Hi - 1;

    if (inverse) {
        x1 = Wi - 1;
        y2 = Wi/2;

        Ws = Ws*(-1);
    }

    for (int i = 0; i < N; i++) {

        if (x1 >= Wi) {
            x1 = Wi - 1;
        }
        if (y2 < 0) {
            y2 = 0;
        }
        image.draw_line(x1, y1, x2, y2, color_lines);

        x1 += Ws;
        y2 -= Hs;
    }

    x1 = Wi/2;
    y1 = 0;

    x2 = Wi/2;
    y2 = Hi/2;

    if (inverse) {
        y1 = Hi - 1;

        Hs = Hs*(-1);
        Ws = Ws*(-1);
    }

    for (int i = 0; i < N; i++) {

        if (y1 >= Hi) {
            y1 = Hi - 1;
        }
        if (x2 < 0) {
            x2 = 0;
        }
        image.draw_line(x1, y1, x2, y2, color_lines);

        y1 += Hs;
        x2 -= Ws;
    }
    return 0;
}

// Draw diamond consisting of 4 quarter circles
int lines_diamond(img::EasyImage & image, const int & Hi, const int & Wi, const int & N, const img::Color & color_lines, const img::Color & color_bg) {

    lines_diamond_helper(image, Hi, Wi, N, color_lines, false);
    lines_diamond_helper(image, Hi, Wi, N, color_lines, true);
    return 0;
}

// Calculate width and height of one block in block pattern
pair<double, double> blocks_calculateBlock(const int & Wi, const int & Hi, const int & Nx, const int & Ny) {

    // Calculate dimensions of one block
    double block_width = Wi/Nx;
    double block_height = Hi/Ny;

    return make_pair(block_width, block_height);
}

// Draw chessboard pattern consisting off blocks
int colorBlocks(img::EasyImage & image, const int & Wi, const int & Hi, const int & Nx, const int & Ny, const img::Color & white, const img::Color & black) {

    // Calculate dimensions of one block
    pair<double, double> blockDimension = blocks_calculateBlock(Wi, Hi, Nx, Ny);
    double block_width = blockDimension.first;
    double block_height = blockDimension.second;

    // Traverse all pixels
    for ( int i = 0; i < Wi; i++) {
        for ( int j = 0; j < Hi; j++) {

            // Calculate coordinates of block to check if even
            int Bx = floor(i/block_width);
            int By = floor(j/block_height);

            // Even
            if ((Bx + By)%2 == 0) {
                image(i, j) = white;
            }
            // Uneven
            else image(i, j) = black;
        }
    }
    return 1;
}

// Draw RGB Rectangle
int colorRectangle(img::EasyImage & image) {

    for(unsigned int i = 0; i < image.get_height(); i++)
    {
        for(unsigned int j = 0; j < image.get_width(); j++)
        {
            image(i,j).red = i;
            image(i,j).green = j;
            image(i,j).blue = (i+j)%256;
        }
    }
    return 0;
}

// Generate EasyImage
img::EasyImage generate_image(const ini::Configuration &configuration) {

    string type = configuration["General"]["type"].as_string_or_die();
    int width = configuration["ImageProperties"]["width"].as_int_or_die();
    int height = configuration["ImageProperties"]["height"].as_int_or_die();

    // If BlockProperties exist
    int Nx; // # Blocks in x
    int Ny;
    img::Color white;
    img::Color black;
    if (configuration["BlockProperties"]["nrXBlocks"].as_int_if_exists(Nx)) {

        // Gather information of image
        Ny = configuration["BlockProperties"]["nrYBlocks"].as_int_or_die(); // # Blocks in y
        vector<double> colorWhite = configuration["BlockProperties"]["colorWhite"].as_double_tuple_or_die(); // Color of white blocks
        vector<double> colorBlack = configuration["BlockProperties"]["colorBlack"].as_double_tuple_or_die(); // Color of black blocks
        bool invertColors = configuration["BlockProperties"]["invertColors"].as_bool_or_default(false); // false if non-existent

        // Invert colors if invertColors is true
        if (invertColors) {
            white = blocks_scaleColors(colorBlack);
            black = blocks_scaleColors(colorWhite);
        }
        else {
            white = blocks_scaleColors(colorWhite);
            black = blocks_scaleColors(colorBlack);
        }
    }

    // If LineProperties exist
    string figure;
    img::Color color_lines;
    img::Color color_bg;
    int N; // # Lines
    if (configuration["LineProperties"]["figure"].as_string_if_exists(figure)) {

        vector<double> lines = configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();
        color_lines = blocks_scaleColors(lines);
        vector<double> bg = configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
        color_bg = blocks_scaleColors(bg);
        N = configuration["LineProperties"]["nrLines"].as_int_or_die();

    }

    // Create new image
    img::EasyImage image_a = img::EasyImage(width, height);

    // Color rectangle
    if (type == "IntroColorRectangle") colorRectangle(image_a);

    // Color blocks
    if (type == "IntroBlocks") colorBlocks(image_a,width, height, Nx, Ny, white, black);

    // LineProperties

    // Color quarter circle
    if (figure == "QuarterCircle") {
        // Fill background color
        image_a.clear(color_bg);
        lines_quarterCircle(image_a, height, width, N, color_lines, color_bg, false);
    }

    // Color eye structure
    if (figure == "Eye") {
        // Fill background color
        image_a.clear(color_bg);
        lines_eye(image_a, height, width, N, color_lines, color_bg);
    }

    // Color diamond structure
    if (figure == "Diamond") {
        // Fill background color
        image_a.clear(color_bg);
        lines_diamond(image_a, height, width, N, color_lines, color_bg);
    }
    return image_a;
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
                                cout << argv[i] << endl;

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

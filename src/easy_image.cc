/*
 * easy_image.cc
 * Copyright (C) 2011  Daniel van den Akker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "easy_image.h"
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <iostream>

#ifndef le32toh
#define le32toh(x) (x)
#endif

namespace
{
	//structs borrowed from wikipedia's article on the BMP file format
	struct bmpfile_magic
	{
			uint8_t magic[2];
	};

	struct bmpfile_header
	{
			uint32_t file_size;
			uint16_t reserved_1;
			uint16_t reserved_2;
			uint32_t bmp_offset;
	};
	struct bmp_header
	{
			uint32_t header_size;
			int32_t width;
			int32_t height;
			uint16_t nplanes;
			uint16_t bits_per_pixel;
			uint32_t compress_type;
			uint32_t pixel_size;
			int32_t hres;
			int32_t vres;
			uint32_t ncolors;
			uint32_t nimpcolors;
	};
	//copy-pasted from lparser.cc to allow these classes to be used independently from each other
	class enable_exceptions
	{
		private:
			std::ios& ios;
			std::ios::iostate state;
		public:
			enable_exceptions(std::ios& an_ios, std::ios::iostate exceptions) :
				ios(an_ios)
			{
				state = ios.exceptions();
				ios.exceptions(exceptions);
			}
			~enable_exceptions()
			{
				ios.exceptions(state);
			}
	};
	//helper function to convert a number (char, int, ...) to little endian
	//regardless of the endiannes of the system
	//more efficient machine-dependent functions exist, but this one is more portable
	template<typename T> T to_little_endian(T value)
	{
		//yes, unions must be used with caution, but this is a case in which a union is needed
		union
		{
				T t;
				uint8_t bytes[sizeof(T)];
		} temp_storage;

		for (uint8_t i = 0; i < sizeof(T); i++)
		{
			temp_storage.bytes[i] = value & 0xFF;
			value >>= 8;
		}
		return temp_storage.t;
	}

	template<typename T> T from_little_endian(T value)
	{
		//yes, unions must be used with caution, but this is a case in which a union is needed
		union
		{
				T t;
				uint8_t bytes[sizeof(T)];
		} temp_storage;
		temp_storage.t = value;
		T retVal = 0;

		for (uint8_t i = 0; i < sizeof(T); i++)
		{
			retVal = (retVal << 8) | temp_storage.bytes[sizeof(T) - i - 1];
		}
		return retVal;
	}

}
img::Color::Color() :
	blue(0), green(0), red(0)
{
}
img::Color::Color(uint8_t r, uint8_t g, uint8_t b) :
	blue(b), green(g), red(r)
{
}
img::Color::~Color()
{
}

img::UnsupportedFileTypeException::UnsupportedFileTypeException(std::string const& msg) :
	message(msg)
{
}
img::UnsupportedFileTypeException::UnsupportedFileTypeException(const UnsupportedFileTypeException &original)
: std::exception(original)
, message(original.message)
{
}
img::UnsupportedFileTypeException::~UnsupportedFileTypeException() throw ()
{
}
img::UnsupportedFileTypeException& img::UnsupportedFileTypeException::operator=(UnsupportedFileTypeException const& original)
{
	this->message = original.message;
	return *this;
}
const char* img::UnsupportedFileTypeException::what() const throw ()
{
	return message.c_str();
}

img::EasyImage::EasyImage() :
	width(0), height(0), bitmap()
{
}

img::EasyImage::EasyImage(unsigned int _width, unsigned int _height, Color color) :
	width(_width), height(_height), bitmap(width * height, color)
{
}

img::EasyImage::EasyImage(EasyImage const& img) :
	width(img.width), height(img.height), bitmap(img.bitmap)
{
}

img::EasyImage::~EasyImage()
{
	bitmap.clear();
}

img::EasyImage& img::EasyImage::operator=(img::EasyImage const& img)
{
	width = img.width;
	height = img.height;
	bitmap.assign(img.bitmap.begin(),img.bitmap.end());
	return (*this);
}

unsigned int img::EasyImage::get_width() const
{
	return width;
}

unsigned int img::EasyImage::get_height() const
{
	return height;
}

void img::EasyImage::clear(Color color)
{
	for (std::vector<Color>::iterator i = bitmap.begin(); i != bitmap.end(); i++)
	{
		*i = color;
	}
}

img::Color& img::EasyImage::operator()(unsigned int x, unsigned int y)
{
	assert(x < this->width);
	assert(y < this->height);
	return bitmap.at(x * height + y);
}

img::Color const& img::EasyImage::operator()(unsigned int x, unsigned int y) const
{
	assert(x < this->width);
	assert(y < this->height);
	return bitmap.at(x * height + y);
}

void img::EasyImage::draw_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, Color color)
{
	assert(x0 < this->width && y0 < this->height);
	assert(x1 < this->width && y1 < this->height);
	if (x0 == x1)
	{
		//special case for x0 == x1
		for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++)
		{
			(*this)(x0, i) = color;
		}
	}
	else if (y0 == y1)
	{
		//special case for y0 == y1
		for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++)
		{
			(*this)(i, y0) = color;
		}
	}
	else
	{
		if (x0 > x1)
		{
			//flip points if x1>x0: we want x0 to have the lowest value
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);
		if (-1.0 <= m && m <= 1.0)
		{
			for (unsigned int i = 0; i <= (x1 - x0); i++)
			{
				(*this)(x0 + i, (unsigned int) round(y0 + m * i)) = color;
			}
		}
		else if (m > 1.0)
		{
			for (unsigned int i = 0; i <= (y1 - y0); i++)
			{
				(*this)((unsigned int) round(x0 + (i / m)), y0 + i) = color;
			}
		}
		else if (m < -1.0)
		{
			for (unsigned int i = 0; i <= (y0 - y1); i++)
			{
				(*this)((unsigned int) round(x0 - (i / m)), y0 - i) = color;
			}
		}
	}
}
std::ostream& img::operator<<(std::ostream& out, EasyImage const& image)
{

	//temporaryily enable exceptions on output stream
	enable_exceptions(out, std::ios::badbit | std::ios::failbit);
	//declare some struct-vars we're going to need:
	bmpfile_magic magic;
	bmpfile_header file_header;
	bmp_header header;
	uint8_t padding[] =
	{ 0, 0, 0, 0 };
	//calculate the total size of the pixel data
	unsigned int line_width = image.get_width() * 3; //3 bytes per pixel
	unsigned int line_padding = 0;
	if (line_width % 4 != 0)
	{
		line_padding = 4 - (line_width % 4);
	}
	//lines must be aligned to a multiple of 4 bytes
	line_width += line_padding;
	unsigned int pixel_size = image.get_height() * line_width;

	//start filling the headers
	magic.magic[0] = 'B';
	magic.magic[1] = 'M';

	file_header.file_size = to_little_endian(pixel_size + sizeof(file_header) + sizeof(header) + sizeof(magic));
	file_header.bmp_offset = to_little_endian(sizeof(file_header) + sizeof(header) + sizeof(magic));
	file_header.reserved_1 = 0;
	file_header.reserved_2 = 0;
	header.header_size = to_little_endian(sizeof(header));
	header.width = to_little_endian(image.get_width());
	header.height = to_little_endian(image.get_height());
	header.nplanes = to_little_endian(1);
	header.bits_per_pixel = to_little_endian(24);//3bytes or 24 bits per pixel
	header.compress_type = 0; //no compression
	header.pixel_size = pixel_size;
	header.hres = to_little_endian(11811); //11811 pixels/meter or 300dpi
	header.vres = to_little_endian(11811); //11811 pixels/meter or 300dpi
	header.ncolors = 0; //no color palette
	header.nimpcolors = 0;//no important colors

	//okay that should be all the header stuff: let's write it to the stream
	out.write((char*) &magic, sizeof(magic));
	out.write((char*) &file_header, sizeof(file_header));
	out.write((char*) &header, sizeof(header));

	//okay let's write the pixels themselves:
	//they are arranged left->right, bottom->top, b,g,r
	for (unsigned int i = 0; i < image.get_height(); i++)
	{
		//loop over all lines
		for (unsigned int j = 0; j < image.get_width(); j++)
		{
			//loop over all pixels in a line
			//we cast &color to char*. since the color fields are ordered blue,green,red they should be written automatically
			//in the right order
			out.write((char*) &image(j, i), 3 * sizeof(uint8_t));
		}
		if (line_padding > 0)
			out.write((char*) padding, line_padding);
	}
	//okay we should be done
	return out;
}
std::istream& img::operator>>(std::istream& in, EasyImage & image)
{
	enable_exceptions(in, std::ios::badbit | std::ios::failbit);
	//declare some struct-vars we're going to need
	bmpfile_magic magic;
	bmpfile_header file_header;
	bmp_header header;
	//a temp buffer for reading the padding at the end of each line
	uint8_t padding[] =
	{ 0, 0, 0, 0 };

	//read the headers && do some sanity checks
	in.read((char*) &magic, sizeof(magic));
	if (magic.magic[0] != 'B' || magic.magic[1] != 'M')
		throw UnsupportedFileTypeException("Could not parse BMP File: invalid magic header");
	in.read((char*) &file_header, sizeof(file_header));
	in.read((char*) &header, sizeof(header));
	if (le32toh(header.pixel_size) + le32toh(file_header.bmp_offset) != le32toh(file_header.file_size))
		throw UnsupportedFileTypeException("Could not parse BMP File: file size mismatch");
	if (le32toh(header.header_size) != sizeof(header))
		throw UnsupportedFileTypeException("Could not parse BMP File: Unsupported BITMAPV5HEADER size");
	if (le32toh(header.compress_type) != 0)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only uncompressed BMP files can be parsed");
	if (le32toh(header.nplanes) != 1)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only one plane should exist in the BMP file");
	if (le32toh(header.bits_per_pixel) != 24)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only 24bit/pixel BMP's are supported");
	//if height<0 -> read top to bottom instead of bottom to top
	bool invertedLines = from_little_endian(header.height) < 0;
	image.height = std::abs(from_little_endian(header.height));
	image.width = std::abs(from_little_endian(header.width));
	unsigned int line_padding = from_little_endian(header.pixel_size) / image.height - (3 * image.width);
	//re-initialize the image bitmap
	image.bitmap.clear();
	image.bitmap.assign(image.height * image.width, Color());
	//okay let's read the pixels themselves:
	//they are arranged left->right., bottom->top if height>0, top->bottom if height<0, b,g,r
	for (unsigned int i = 0; i < image.get_height(); i++)
	{
		//loop over all lines
		for (unsigned int j = 0; j < image.get_width(); j++)
		{
			//loop over all pixels in a line
			//we cast &color to char*. since the color fields are ordered blue,green,red, the data read should be written in the right variables
			if (invertedLines)
			{
				//store top-to-bottom
				in.read((char*) &image(j, image.height - 1 - i), 3 * sizeof(uint8_t));
			}
			else
			{
				//store bottom-to-top
				in.read((char*) &image(j, i), 3 * sizeof(uint8_t));
			}
		}
		if (line_padding > 0)
		{
			in.read((char*) padding, line_padding);
		}
	}
	//okay we're done
	return in;
}

std::tuple<std::pair<double, double>, std::pair<double, double>> img::EasyImage::Line2D_findMax(Lines2D &line2D) {

    double x = line2D.begin()->getP1().getX();
    double X = line2D.begin()->getP1().getX();

    double y = line2D.begin()->getP2().getY();
    double Y = line2D.begin()->getP2().getY();

    // Stackoverflow source cannot find :(
    for (Line2D & i : line2D) {

        double p1x = i.getP1().getX();
        double p1y = i.getP1().getY();

        x = p1x < x ? p1x : x;
        y = p1y < y ? p1y : y;
        X = p1x > X ? p1x : X;
        Y = p1y > Y ? p1y : Y;

        double p2x = i.getP2().getX();
        double p2y = i.getP2().getY();

        x = p2x < x ? p2x : x;
        y = p2y < y ? p2y : y;
        X = p2x > X ? p2x : X;
        Y = p2y > Y ? p2y : Y;
    }
    return std::make_tuple(std::make_pair(x, y), std::make_pair(X, Y));
}

void img::EasyImage::draw2DLines(Lines2D & line2D, const int size) {

    // Calculate x-min, y-min, x-max and y-max
    std::tuple<std::pair<double, double>, std::pair<double, double>> max_line2D = Line2D_findMax(line2D);

    double x = std::get<0>(max_line2D).first;
    double y = std::get<0>(max_line2D).second;

    double X = std::get<1>(max_line2D).first;
    double Y = std::get<1>(max_line2D).second;

    // Calculate x-range, y-range
    double xrange = X - x;
    double yrange = Y - y;

    // Calculate max(xrange, yrange)
    double range = xrange > yrange ? xrange : yrange;

    // Calculate dimensions of image
    double image_x = size*(xrange/range);
    double image_y = size*(yrange/range);

    // Calculate scale-factor
    double d = 0.95*(image_x/xrange);

    // Multiply coordinates of all points with scale-factor
    for (Line2D & i : line2D) {
        i.line2D_scale(d);
    }

    double DC_x = d*((x + X)/2);
    double DC_y = d*((y + Y)/2);

    double dx = (image_x/2) - DC_x;
    double dy = (image_y/2) - DC_y;

    // Move all coordinates
    for (Line2D & i : line2D) {
        i.line2D_move(dx, dy);
    }

    // Round all points
    for (Line2D & i : line2D) {
        i.round();
    }

    // Change image dimensions
    this->width = static_cast<int>(std::round(image_x));
    this->height = static_cast<int>(std::round(image_y));

    // Draw lines
    for (Line2D & i : line2D) {

        std::tuple<double, double, double> color_values = i.getColor().getColor();
        this->draw_line(i.getP1().getX(), i.getP1().getY()
                        , i.getP2().getX(), i.getP2().getY()
                        , img::Color(std::get<0>(color_values)
                        ,std::get<1>(color_values)
                        , std::get<2>(color_values)));
    }
}

std::string img::EasyImage::generate_string(const LParser::LSystem & l_system, int iter, std::string & l_system_string) {

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

void img::EasyImage::drawLSystem(LParser::LSystem2D & l_system_2D, const int size, const cc::Color & color) {

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
    this->draw2DLines(l_system_lines, size);
}




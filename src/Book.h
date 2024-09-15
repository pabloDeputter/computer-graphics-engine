//
// Created by Pablo Deputter on 02/09/2021.
//

#ifndef ENGINE_BOOK_H
#define ENGINE_BOOK_H

#include "Color.h"

class Book {
    int coverWidth;
    int coverHeight;

    int width;
    int height;

    cc::Color pageColor;
    cc::Color backgroundColor;
    cc::Color foregroundColor;
    cc::Color bookmarkColor;

    bool bookmark;

    double foregroundChance = 0.7;
    double bookmarkChance = 0.1;
    double mirrorChance = 0.6;

    std::vector<std::vector<int>> cover;

private:
    void randomCover();

public:
    Book(const int &coverWidth, const int &coverHeight);

};


#endif //ENGINE_BOOK_H

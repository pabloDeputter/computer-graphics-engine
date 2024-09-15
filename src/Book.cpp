//
// Created by Pablo Deputter on 02/09/2021.
//

#include "Book.h"

Book::Book(const int &coverWidth, const int &coverHeight) {

    Book::coverWidth = coverWidth;
    Book::coverHeight = coverHeight;
    Book::width = Book::coverWidth + 3;
    Book::height = Book::coverHeight + 6;
}


void Book::randomCover() {

    for (int i = 0; i < coverWidth; i++) {
        for (int j = 0; i < coverHeight; j++) {
            Book::cover[i][j] =  (rand() % static_cast<int>(1)) < Book::foregroundChance ? 1 : 0;
        }
    }

}

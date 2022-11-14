//
// Created by 金海林 on 2022/11/13.
//

#include "PixelFont.h"

constexpr char PixelFont::_alphabet[26][7][10];

void PixelFont::printWord(std::string word, int interval) {
    std::cout << std::endl;
    for(int i = 0; i < 7; ++i){
        for(auto j : word){
            if(j >= 'a') {
                std::cout << _alphabet[j - 'a'][i];
            } else {
                std::cout << _alphabet[j - 'A'][i];
            }
            for(int k = 0; k < interval; ++k)
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

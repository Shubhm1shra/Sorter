#include "Sorter.hpp"

#include <iostream>
#include <conio.h>

const int nScreenWidth = 800;
const int nScreenHeight = 600;

int main(void){
    std::string algo = "";
    std::cout << "Algorithm : ";
    std::cin >> algo;

    if(algo.size() == 0 || algo == "b" || algo == "Bubble Sort") algo = "Bubble Sort";
    else if(algo == "s" || algo == "Selection Sort")  algo = "Selection Sort";
    else if(algo == "m" || algo == "Merge Sort") algo = "Merge Sort";
    else if(algo == "q" || algo == "Quick Sort") algo = "Quick Sort";
    else{
        std::cerr << "Invalid Algorighm Name provided!" << std::endl;
        _getch();
        return 1;
    }

    std::cout << std::endl;

    sf::RenderWindow window(sf::VideoMode(nScreenWidth, nScreenHeight), "Sorter!");
    window.setVerticalSyncEnabled(true);
    std::cout << window.getSize().x << std::endl;

    window.requestFocus();

    Sorter sort(window, 900, algo);

    sort.start();

    return 0;
}

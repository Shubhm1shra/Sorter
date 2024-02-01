#include "Sorter.hpp"

const int nScreenWidth = 800;
const int nScreenHeight = 600;

int main(void){
    sf::RenderWindow window(sf::VideoMode(nScreenWidth, nScreenHeight), "Sorter!");
    window.setVerticalSyncEnabled(true);

    Sorter sort(window, 400, "Merge Sort");

    sort.test();

    return 0;
}
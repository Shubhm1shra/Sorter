#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

#define SCALE_FACTOR 300

#define MIN_IN_ARRAY 10
#define MAX_IN_ARRAY 100

#define PADDINGX 0
#define PADDINGY 100

class Sorter{
public:
    Sorter(sf::RenderWindow& window, int arrSize, const std::string& algo);

    ~Sorter();

    void start();
    void test();

    void merge(std::vector<std::vector<int>>& m_steps, std::vector<int>& arr, int l, int m, int r);
    int partition(std::vector<std::vector<int>>& m_steps, std::vector<int>& arr, int l, int r);

    std::vector<std::vector<int>> getBubbleSteps(const std::vector<int>& arr);
    std::vector<std::vector<int>> getSelectionSteps(const std::vector<int>& arr);
    std::vector<std::vector<int>> getMergeSteps(const std::vector<int>& arr);
    std::vector<std::vector<int>> getQuickSteps(const std::vector<int>& arr);

private:
    sf::RenderWindow& m_window;
    std::vector<int> dataArray;
    int arraySize;
    float rectWidth;

    int maxInArr;
    int minInArr;

    std::vector<std::vector<int>> steps;

    void drawArray(const std::vector<int>& arr);

    void setRandArray();
    std::vector<float> getNormalizedHeight(const std::vector<int>& arr);

    void initialize();
    void swap(int index1, int index2);
};
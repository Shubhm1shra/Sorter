#include <iostream>
#include <algorithm>

#include "Sorter.hpp"

/*
Parameterised Construction :-
sf::RenderWindow& window -> Reference to predefined window
int arrSize -> Size of Array to Sort
const std::string& algo -> Algo Name
*/
Sorter::Sorter(sf::RenderWindow& window, int arrSize, const std::string& algo) : m_window(window), arraySize(arrSize){
    initialize();

    if(algo == "Bubble Sort") steps = getBubbleSteps(dataArray);
    else if(algo == "Selection Sort") steps = getSelectionSteps(dataArray);
    else if(algo == "Merge Sort") steps = getMergeSteps(dataArray);
    else if(algo == "Quick Sort") steps = getQuickSteps(dataArray);
    else{
        std::cerr << "Invalid Algorithm name given!" << std::endl;
        return;
    }
}

// No Allocations in heap -> No need for removing anything (I think)
Sorter::~Sorter() = default;

void Sorter::start(){
    sf::Event event;

    int step_itr = 0;
    std::size_t total_steps = steps.size();

    while(m_window.isOpen()){
        while(m_window.pollEvent(event)){
            if(event.type == sf::Event::Closed) m_window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) m_window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) step_itr = 0;
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) step_itr -= 10;
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) step_itr += 10;
        }

        if(step_itr < 0) step_itr = 0;
        if(step_itr > total_steps - 1) step_itr = total_steps - 1;

        drawArray(steps[step_itr]);
        step_itr++;
    }
}

// Helper function for Testing
void showVector(std::vector<int> arr){
    for(int i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

// Helper function for Testing
void showVector(std::vector<float> arr){
    for(int i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

// Helper function for Testing
void showMatrix(std::vector<std::vector<int>> arr){
    for(std::vector<int> row : arr){
        for(int i : row) std::cout << i << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Just for changing code here rather than start function
void Sorter::test(){
    sf::Event event;

    int step_iter = 0;
    std::size_t total_steps = steps.size();

    while(m_window.isOpen()){
        while(m_window.pollEvent(event)){
            if(event.type == sf::Event::Closed) m_window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) m_window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) step_iter = 0;
        }

        drawArray(steps[step_iter]);

        if(step_iter != total_steps - 1) step_iter++;
    }
}

/*
const std::vector<int>& arr -> Array to Sort

Generates steps in form of std::vector<std::vector<int>> by sorting how bubble sort is supposed to, and pushing the updated vector to steps
*/
std::vector<std::vector<int>> Sorter::getBubbleSteps(const std::vector<int>& arr){
    std::vector<std::vector<int>> m_steps;
    std::vector<int> m_arr(arr);

    bool swapped;

    for(int i = 0; i < arraySize - 1; i++){
        swapped = false;
        for(int j = 0; j < arraySize - i - 1; j++){
            if(m_arr[j] > m_arr[j+1]){
                std::swap(m_arr[j], m_arr[j+1]);
                m_steps.push_back(m_arr);
                swapped = true;
            }
        }
        if(!swapped) break;
    }

    return m_steps;
}

// Same stuff as Bubble Sort as Selection Sort
std::vector<std::vector<int>> Sorter::getSelectionSteps(const std::vector<int>& arr){
    std::vector<std::vector<int>> m_steps;
    std::vector<int> m_arr(arr);

    int minIdx;

    for(int i = 0; i < arraySize - 1; i++){
        minIdx = i;

        for(int j = i + 1; j < arraySize; j++) if(m_arr[j] < m_arr[minIdx]) minIdx = j;

        if(minIdx != i){
            std::swap(m_arr[minIdx], m_arr[i]);
            m_steps.push_back(m_arr);
        }
    }

    return m_steps;
}

void Sorter::merge(std::vector<std::vector<int>>& m_steps, std::vector<int>& arr, int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++) L[i] = arr[l + i];
    for(int i = 0; i < n2; i++) R[i] = arr[m + i + 1];

    int i = 0;
    int j = 0;
    int k = l;

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            m_steps.push_back(arr);
            i++;
        } else{
            arr[k] = R[j];
            m_steps.push_back(arr);
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        m_steps.push_back(arr);
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        m_steps.push_back(arr);
        j++;
        k++;
    }
}

// Same stuff as Bubble Sort but Merge
std::vector<std::vector<int>> Sorter::getMergeSteps(const std::vector<int>& arr){
    std::vector<std::vector<int>> m_steps;
    std::vector<int> m_arr(arr);

    int curSize, leftStart;

    for(curSize = 1; curSize <= arraySize - 1; curSize = 2 * curSize){
        for(leftStart = 0; leftStart < arraySize - 1; leftStart += 2*curSize){
            int mid = std::min(leftStart + curSize - 1, arraySize - 1);
            int rightEnd = std::min(leftStart + 2 * curSize - 1, arraySize - 1);

            merge(m_steps, m_arr, leftStart, mid, rightEnd);
        }
    }

    return m_steps;
}

int Sorter::partition(std::vector<std::vector<int>>& m_steps, std::vector<int>& arr, int l, int r){
    int x = arr[r];
    int i = (l - 1);

    for(int j = l; j <= r-1; j++){
        if(arr[j] <= x){
            i++;
            std::swap(arr[i], arr[j]);
            m_steps.push_back(arr);
        }
    }

    std::swap(arr[i+1], arr[r]);
    m_steps.push_back(arr);
    return (i+1);
}

// Same stuff as Bubble Sort but Quick Sort
std::vector<std::vector<int>> Sorter::getQuickSteps(const std::vector<int>& arr){
    std::vector<std::vector<int>> m_steps;
    std::vector<int> m_arr(arr);

    int l = 0;
    int r = arraySize - 1;

    std::vector<int> stack(r - l + 1);
    int top = -1;

    stack[++top] = l;
    stack[++top] = r;

    while(top >= 0){
        r = stack[top--];
        l = stack[top--];

        int p = partition(m_steps, m_arr, l, r);

        if(p - 1 > l){
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        if(p + 1 < r){
            stack[++top] = p + 1;
            stack[++top] = r;
        }
    }

    return m_steps;
}

// Take the Vector -> Normalize the vector -> Scale it to Scaling Factor -> Calculate Height for individual data (width calcualted on the basis of vector size) -> Create sf::RectagleShape and draw on window
void Sorter::drawArray(const std::vector<int>& arr){
    m_window.clear();

    std::vector<float> normalHeights = getNormalizedHeight(arr);


    for(int i = 0; i < arraySize; i++){
        sf::RectangleShape rect(sf::Vector2f(rectWidth, normalHeights[i] * SCALE_FACTOR));
        rect.setPosition((rectWidth + PADDINGX) * i, m_window.getSize().y - normalHeights[i] * SCALE_FACTOR - PADDINGY);

        m_window.draw(rect);
    }

    m_window.display();
}

void Sorter::setRandArray(){
    dataArray.clear();

    for(int i = 0; i < arraySize; i++) dataArray.push_back(MIN_IN_ARRAY + std::rand() % (MAX_IN_ARRAY - MIN_IN_ARRAY + 1));
}

std::vector<float> Sorter::getNormalizedHeight(const std::vector<int>& arr){
    std::vector<float> result(arraySize);

    float normalVal;

    for(int i = 0; i < arraySize; i++){
        normalVal = static_cast<float>(arr[i] - minInArr) / static_cast<float>(maxInArr - minInArr);
        result[i] = normalVal;
    }

    return result;
}

// Set seed on the basis of time (to get better random values) -> Assign Random value in Data Vector -> Calculate Width for each Data Value
void Sorter::initialize(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    setRandArray();

    if(arraySize > m_window.getSize().x) arraySize = m_window.getSize().x;
    rectWidth = static_cast<float>(m_window.getSize().x) / static_cast<float>(arraySize) - PADDINGX;

    if(rectWidth <= 0){
        arraySize = static_cast<int>(m_window.getSize().x) / (PADDINGX + 1) ;
        rectWidth = static_cast<float>(m_window.getSize().x) / static_cast<float>(arraySize) - PADDINGX;
    }

    maxInArr = dataArray[0];
    minInArr = 1;

    for(int i : dataArray) if(maxInArr < i) maxInArr = i;
}

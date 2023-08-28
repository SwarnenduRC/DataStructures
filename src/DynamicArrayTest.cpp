#include "DynamicArrayTest.h"
#include "DynamicArray.h"

#include <iostream>

using swarnendu::DyArray;

static void displayArray(const DyArray<int>& arr)
{
    std::cout << std::endl << std::endl;
    if (!arr.empty())
    {
        std::cout << "The array size is: " << arr.size() << std::endl << std::endl;

        for (size_t idx = 0; idx < arr.size(); ++idx)
        {
            std::cout << arr[idx];
            if (idx != (arr.size() -1)) 
                std::cout << ", ";
        }
    }
    else
    {
        std::cout << "Empty array passed" << std::endl;
    }
    std::cout << std::endl << std::endl;
}

static void fillArray(DyArray<int>& arr, const size_t size)
{
    if (size)
    {
        for (size_t cnt = 0; cnt < size; ++cnt)
            arr[cnt] = cnt;
    }
}

static void fillArrayReverse(DyArray<int>& arr, const size_t size)
{
    if (size)
    {
        for (auto idx = static_cast<int>(arr.size() - 1), val = 0; idx >= 0; --idx, ++val)
            arr[idx] = val;
    }
}

void testDynamicArray()
{
    std::cout << std::endl << std::endl << "=============Empty array test================" << std::endl << std::endl;
    DyArray<int> array;
    displayArray(array);
    std::cout << std::endl << std::endl << "=============Empty array test================" << std::endl << std::endl;

    std::cout << std::endl << std::endl << "=============Fill array test================" << std::endl << std::endl;
    DyArray<int> arr2(5);
    fillArray(arr2, 5);
    displayArray(arr2);
    std::cout << std::endl << std::endl << "=============Fill array test================" << std::endl << std::endl;

    std::cout << std::endl << std::endl << "=============Array assignment test================" << std::endl << std::endl;
    array = arr2;
    displayArray(array);
    std::cout << std::endl << std::endl << "=============Array assignment test================" << std::endl << std::endl;

    std::cout << std::endl << std::endl << "=============Array move assignment test================" << std::endl << std::endl;
    /* array.clear();
    std::cout << "Printing array after clearing it" << std::endl;
    displayArray(array);
    array = std::move(arr2);
    std::cout << "Printing array after moving it" << std::endl;
    displayArray(array);
    std::cout << "Printing empty array after moving it" << std::endl;
    displayArray(arr2); */
    DyArray<int> arr3(7);
    fillArrayReverse(arr3, 7);
    std::cout << "Printing array after filling it in reversed order" << std::endl;
    displayArray(arr3);
    array = std::move(arr3);
    std::cout << "Printing array after moving it" << std::endl;
    displayArray(array);
    std::cout << "Printing empty array after moving it" << std::endl;
    displayArray(arr3);
    std::cout << std::endl << std::endl << "=============Array move assignment test================" << std::endl << std::endl;

    std::cout << std::endl << std::endl << "=============Array move constructor test================" << std::endl << std::endl;
    DyArray<int> arr4 = std::move(array);
    std::cout << "Printing array after moving it" << std::endl;
    displayArray(arr4);
    std::cout << "Printing empty array after moving it" << std::endl;
    displayArray(array);
    std::cout << std::endl << std::endl << "=============Array move constructor test================" << std::endl << std::endl;

    std::cout << std::endl << std::endl << "=============Array resize test================" << std::endl << std::endl;
    displayArray(arr4);
    arr4.resize(10);
    displayArray(arr4);
    std::cout << std::endl << std::endl << "=============Array resize test================" << std::endl << std::endl;
}
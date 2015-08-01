#include <iostream>
#include <array>
#include <list>
#include <functional>
#include <assert.h>

#include "sort_algo.hpp"

using namespace std;

template<typename TStream, typename TIter>
void PrintCollection(std::string const & title, TStream & stream, TIter const & beg, TIter const & end)
{
  stream << title;
  static_assert(iter::ForwardIterCheck<TIter>::value, "");
  for (TIter element = beg; element != end; ++element)
    stream << *element << " ";
  stream << std::endl;
}

template<size_t N>
std::array<int, N> RandomArray(int maxValue)
{
  std::array<int, N> arr;

  for (int & element : arr)
    element = std::rand() % maxValue;

  return arr;
};

enum ESortMethod
{
  SORT_BUBBLE,
  SORT_SELECTION,
  SORT_INSERTION,
  SORT_MERGE
};

void SortArrayTest(std::string const & title, ESortMethod method)
{
  size_t const COLLECTION_SIZE = 30;
  int const maxValue = 100;

  {
    using TArray = std::array<int, COLLECTION_SIZE>;
    TArray arr = RandomArray<std::tuple_size<TArray>::value>(maxValue);
    TArray::iterator b = begin(arr);
    TArray::iterator e = end(arr);

    switch (method)
    {
      case SORT_BUBBLE: sort::BubbleSort(b, e);
        break;
      case SORT_SELECTION: sort::SelectionSort(b, e);
        break;
      case SORT_INSERTION: sort::InsertionSort(b, e);
        break;
      case SORT_MERGE: sort::MergeSort(b, e);
        break;
      default:
        assert(false);
    }
    PrintCollection(title, std::cout, begin(arr), end(arr));
  }
}

int main()
{
  using TClock = std::chrono::system_clock;
  std::srand(TClock::now().time_since_epoch().count());
  //std::srand(50);

  SortArrayTest("Bubble sort : ", SORT_BUBBLE);
  SortArrayTest("Selection sort : ", SORT_SELECTION);
  SortArrayTest("Insertion sort : ", SORT_INSERTION);
  SortArrayTest("Merge sort : ", SORT_MERGE);
  return 0;
}

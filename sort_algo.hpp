//
// Created by Yury Rakhuba on 24/07/15.
//

#pragma once

#include "iter_traits.hpp"

#include <iterator>

namespace sort
{

template <typename TIter, typename TLess>
void SelectionSort(TIter const & beg, TIter const & end, TLess const & cmp)
{
  static_assert(iter::ForwardIterCheck<TIter>::value, "");

  for (TIter outerIter = beg; outerIter != end; ++outerIter)
  {
    TIter minElement = outerIter;
    for (TIter innerIter = iter::NextIter(outerIter, 1); innerIter != end; ++innerIter)
    {
      if (cmp(*innerIter, *minElement))
        minElement = innerIter;
    }

    iter::SwapValues(outerIter, minElement);
  }
}

template <typename TIter>
void SelectionSort(TIter const & beg, TIter const & end)
{
  SelectionSort(beg, end, std::less<typename std::iterator_traits<TIter>::value_type>());
}

template <typename TIter, typename TLess>
void InsertionSort(TIter const & beg, TIter const & end, TLess const & cmp)
{
  static_assert(iter::BidirIterCheck<TIter>::value, "");

  for (TIter outerIter = iter::NextIter(beg, 1); outerIter != end; ++outerIter)
  {
    TIter innerIter = outerIter;
    TIter prevIter = iter::NextIter(innerIter, -1);
    while (innerIter != beg && cmp(*innerIter, *prevIter))
    {
      iter::SwapValues(innerIter, prevIter);
      innerIter = prevIter;
      prevIter = iter::NextIter(innerIter, -1);
    }
  }
}

template <typename TIter>
void InsertionSort(TIter const & beg, TIter const & end)
{
  InsertionSort(beg, end, std::less<typename std::iterator_traits<TIter>::value_type>());
};

template <typename TIter, typename TLess>
void BubbleSort(TIter const & beg, TIter const & end, TLess const & cmp)
{
  static_assert(iter::ForwardIterCheck<TIter>::value, "");

  for (TIter i = beg; i != end; ++i)
  {
    for (TIter j = iter::NextIter(i, 1); j != end; ++j)
    {
      if (cmp(*j, *i))
        iter::SwapValues(i, j);
    }
  }
};

template <typename TIter>
void BubbleSort(TIter const & beg, TIter const & end)
{
  BubbleSort(beg, end, std::less<typename std::iterator_traits<TIter>::value_type>());
}

}

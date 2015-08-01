//
// Created by Yury Rakhuba on 24/07/15.
//

#pragma once

#include "iter_traits.hpp"

#include <iterator>
#include <vector>

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

namespace impl
{

template <typename TIter>
void FindMergeRange(TIter & beg1, TIter end1, TIter & beg2, TIter end2)
{
  static_assert(iter::ForwardIterCheck<TIter>::value, "");

  if (beg1 == end1)
  {
    assert(beg2 != end2);
    beg2 = end2;
    return;
  }

  if (beg2 == end2)
  {
    beg1 = end1;
    return;
  }

  if (*beg2 < *beg1)
  {
    FindMergeRange(beg2, end2, beg1, end1);
  }
  else
  {
    while (beg1 != end1 && *beg1 <= *beg2)
      ++beg1;
  }
}

template <typename TInsertIter, typename TIter>
void Merge(TInsertIter output, TIter const & beg1, TIter const & end1, TIter const & beg2, TIter const & end2)
{
  static_assert(iter::ForwardIterCheck<TIter>::value, "");
  //static_assert(iter::OutputIterCheck<TInsertIter>::value, "");

  TIter start1 = beg1;
  TIter mid1 = start1;
  TIter start2 = beg2;
  TIter mid2 = start2;

  auto copyFn = [](TInsertIter & output, TIter & b, TIter & e)
  {
    std::copy(b, e, output);
    std::advance(output, std::distance(b, e));
    b = e;
  };

  while (mid1 != end1 || mid2 != end2)
  {
    FindMergeRange(mid1, end1, mid2, end2);
    copyFn(output, start1, mid1);
    copyFn(output, start2, mid2);
  }
};

} // namespace impl

template <typename TIter>
void MergeSort(TIter beg, TIter end)
{
  static_assert(iter::ForwardIterCheck<TIter>::value, "");
  //static_assert(iter::OutputIterCheck<TIter>::value, "");

  size_t dist = std::distance(beg, end);
  using TValue = typename std::iterator_traits<TIter>::value_type;
  std::vector<TValue> addMemory(dist);

  for (size_t step = 1; step < dist; step *= 2)
  {
    for (size_t lower = 0; lower < dist - step; lower += step << 1)
    {
      TIter s = iter::NextIter(beg, lower);
      TIter m = iter::NextIter(s, step);
      size_t upperOffset = step << 1;
      if (lower + upperOffset > dist)
        upperOffset = dist - lower;

      TIter e = iter::NextIter(s, upperOffset);
      impl::Merge(iter::NextIter(addMemory.begin(), lower), s, m, m, e);
    }

    std::copy(addMemory.begin(), addMemory.end(), beg);
  }
}

} // namespace sort

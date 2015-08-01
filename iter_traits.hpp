//
// Created by Yury Rakhuba on 24/07/15.
//

#pragma once

#include <type_traits>
#include <iterator>

namespace iter
{

template<typename TIter, typename TIterTag>
struct BaseIterCheck
{
  constexpr static bool value = std::is_base_of<TIterTag, typename std::iterator_traits<TIter>::iterator_category>::value;
};

template<typename TIter>
struct RandomAccessIterCheck : BaseIterCheck<TIter, std::random_access_iterator_tag> {};

template<typename TIter>
struct BidirIterCheck : BaseIterCheck<TIter, std::bidirectional_iterator_tag> {};

template<typename TIter>
struct ForwardIterCheck : BaseIterCheck<TIter, std::forward_iterator_tag> {};

template<typename TIter>
struct OutputIterCheck : BaseIterCheck<TIter, std::output_iterator_tag> {};

template<typename TIter>
void SwapValues(TIter & iter1, TIter & iter2)
{
  std::swap(*iter1, *iter2);
}

template<typename TIter>
TIter NextIter(TIter const & iter, typename std::iterator_traits<TIter>::difference_type n = 1)
{
  TIter copy = iter;
  return std::next(copy, n);
}

}

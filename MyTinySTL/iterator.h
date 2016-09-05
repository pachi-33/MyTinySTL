#ifndef ITERATOR_H
#define ITERATOR_H

#ifndef USE_CSTDDEF
#define USE_CSTDDEF
#include <cstddef>	//for ptrdiff_t
#endif // !USE_CSTDDEF

namespace MyTinySTL {

	//五种迭代器类型
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	//input_iterator
	template <class T, class Distance>
	struct input_iterator {
		typedef input_iterator_tag			iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//output_iterator
	template <class T, class Distance>
	struct output_iterator {
		typedef output_iterator_tag			iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//forward_iterator
	template <class T, class Distance>
	struct forward_iterator {
		typedef forward_iterator_tag		iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//bidirectional_iterator
	template <class T, class Distance>
	struct bidirectional_iterator {
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//random_access_iterator
	template <class T, class Distance>
	struct random_access_iterator {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//iterator
	template <class Category, class T, class Distance = ptrdiff_t , 
		class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	//萃取迭代器特性
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	//针对原生指针的特化版本
	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	//这个函数决定某个迭代器的 category
	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	//这个函数决定某个迭代器的 distance type
	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type*
		distance_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	//这个函数决定某个迭代器的 value type
	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	// distance 函数：迭代器的距离
	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last) {
		typedef typename iterator_traits<InputIterator>::iterator_category category;
		return __distance(first, last, category());
	}

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		__distance(InputIterator first, InputIterator last, input_iterator_tag) {
		iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}

	template <class RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type
		__distance(RandomAccessIterator first, RandomAccessIterator last,
			random_access_iterator_tag) {
		return last - first;
	}

	// advance 函数：迭代器前进 n 个距离
	template <class InputIterator, class Distance>
	inline void advance(InputIterator& i, Distance n) {
		__advance(i, n, iterator_category(i));
	}

	template <class InputIterator, class Distance>
	inline void __advance(InputIterator& i, Distance n, input_iterator_tag) {
		while (n--)	++i;
	}

	template <class BidirectionalIterator, class Distance>
	inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
		if (n >= 0)
			while (n--)	++i;
		else
			while (n++)	--i;
	}

	template <class RandomAccessIterator, class Distance>
	inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag) {
		i += n;
	}
}
#endif // !ITERATOR_H

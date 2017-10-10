template <typename BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
	typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
	--n;

	while (n > 0)
	{
		typename std::iterator_traits<BidirIt>::value_type tmp = *first;

		*first++ = *--last;
		*last = tmp;

		n -= 2;
	}
}

/**
    std::string v("This is OK!");
		my_reverse(v.begin(), v.end());
		for (char n : v)
		{
			std::cout << n;
		}
		std::cout << "\n";
*/

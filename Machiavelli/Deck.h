#pragma once

#include <deque>
#include <algorithm>

template <typename T> 
class Deck
{
public:
	Deck();
	Deck(std::initializer_list<T> cards);
	~Deck();

	bool stackIsEmpty() const;
	bool discardPileEmpty() const;

	template<typename Iter>
		Deck(Iter b, Iter e);

	void shuffleStack();

	T draw();

	void discard(const T& card);
	void discard(T&&  card);

	void push_bottom_stack(const T& card);
	void push_bottom_stack(T&& card);

	void push_top_stack(const T& card);
	void push_top_stack(T&& card);

	void merge_stacks(bool shuffle_afterwards = true);

private:
	std::deque<T> deck;
	std::deque<T> discardPile;
};


#pragma once

#include <deque>
#include <algorithm>
#include <random>
#include "util\RandomGenerator.h"

template <typename T> 
class Deck
{
public:
	Deck()
	{
	}

	Deck(std::initializer_list<T> cards) : deck(cards)
	{
	}

	~Deck()
	{
	}

	bool stackIsEmpty() const
	{
		if (deck.empty()) {
			return true;
		}

		return false;
	}
	bool discardPileEmpty() const
	{
		if (discardPile.empty()) {
			return true;
		}

		return false;
	}

	template<typename Iter>
		Deck(Iter b, Iter e);

	void shuffleStack()
	{

		std::shuffle(deck.begin(), deck.end(), util::RandomGenerator::instance().random_generator());
	}

	T draw()
	{
		return deck.front();
	}

	void discard(const T& card)
	{
		discardPile.push_back(card);
		deck.erase(std::remove(deck.begin(), deck.end(), card));
	}
	void discard(T&&  card)
	{
		discardPile.push_back(card);
		deck.erase(std::remove(deck.begin(), deck.end(), card));
	}

	void push_bottom_stack(const T& card)
	{
		deck.push_back(card);
	}
	void push_bottom_stack(T&& card)
	{
		deck.push_back(card);
	}

	void push_top_stack(const T& card)
	{
		deck.push_front(card);
	}
	void push_top_stack(T&& card)
	{
		deck.push_front(card);
	}

	void merge_stacks(bool shuffle_afterwards = true)
	{
		if (!discardPileEmpty) {
			for (auto card : discardPile) {
				deck.push_back(std::move(card));
			}
		}

		if (shuffle_afterwards) {
			shuffleStack();
		}
	}

private:
	std::deque<T> deck;
	std::deque<T> discardPile;
};


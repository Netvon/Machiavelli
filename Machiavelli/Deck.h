#pragma once

#include <deque>
#include <algorithm>
#include <random>
#include <functional>
#include "util\RandomGenerator.h"

namespace machiavelli
{
	template <typename T>
	class Deck
	{
	public:

		Deck() = default;

		Deck(std::initializer_list<T> cards) : deck(cards)
		{
		}

		~Deck() = default;

		typename std::deque<T>::const_iterator begin() const {
			return deck.begin();
		}

		typename std::deque<T>::const_iterator end() const {
			return deck.end();
		}

		typename std::deque<T>::iterator begin() {
			return deck.begin();
		}

		typename std::deque<T>::iterator end() {
			return deck.end();
		}

		bool stackIsEmpty() const
		{
			return deck.empty();
		}

		bool discardPileEmpty() const
		{
			if (discardPile.empty()) {
				return true;
			}

			return false;
		}

		int sizeOfStack() const
		{
			int amountOfCards = 0;

			for (auto& card : deck) {
				amountOfCards++;
			}

			return amountOfCards;
		}

		void shuffleStack()
		{
			std::shuffle(deck.begin(), deck.end(), util::RandomGenerator::instance().random_generator());
		}

		void swapStack(Deck<T>& pOther)
		{
			deck.swap(pOther.deck);
		}

		void swap_if(Deck<T>& other, std::function<bool(const T&)> predicate) 
		{
			std::deque<T> temp_a;
			std::deque<T> temp_b;

			for (const T& item : deck) {
				if (predicate && predicate(item)) {
					temp_a.push_back(item);
				}
			}

			for (const T& item : other.deck) {
				if (predicate && predicate(item)) {
					temp_b.push_back(item);
				}
			}

			other.deck.swap(temp_a);
			deck.swap(temp_b);

		}

		T draw()
		{
			if (deck.empty()) {
				return T();
			}

			auto drawnCard = deck.front();
			deck.erase(std::remove(deck.begin(), deck.end(), drawnCard));

			return drawnCard;
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

		void push_discard_top(T&& card) {
			discardPile.push_front(card);
		}

		void push_discard_top(const T& card) {
			discardPile.push_front(card);
		}

		void merge_stacks(bool shuffle_afterwards = true)
		{
			if (!discardPileEmpty) {
				for (auto& card : discardPile) {
					deck.push_back(card);
				}

				discardPile.clear();
			}

			if (shuffle_afterwards) {
				shuffleStack();
			}
		}

		size_t size() const {
			return deck.size();
		}

		void replace_deck(Deck<T>& other) {
			deck = std::move(other.deck);
		}

		void clear() {
			deck.clear();
			discardPile.clear();
		}

	private:
		std::deque<T> deck;
		std::deque<T> discardPile;
	};

	template<typename T>
	std::istream& operator>>(std::istream& is, Deck<T>& deck)
	{
		std::istream::sentry s(is);

		if (s) {
			while (!is.eof()) {
				T temp;

				is >> temp;

				if (is.good()) {
					deck.push_bottom_stack(std::move(temp));
				}
			}
		}

		return is;
	}
}

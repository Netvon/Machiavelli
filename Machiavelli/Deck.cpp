#include "Deck.h"



template<typename T>
Deck<T>::Deck()
{
}

template<typename T>
Deck<T>::Deck(std::initializer_list<T> cards) : deck(cards)
{
}

template<typename T>
Deck<T>::~Deck()
{
}

template<typename T>
bool Deck<T>::stackIsEmpty() const
{
	if (deck.empty()) {
		return true;
	}

	return false;
}

template<typename T>
bool Deck<T>::discardPileEmpty() const
{
	if (discardPile.empty()) {
		return true;
	}

	return false;
}

template<typename T>
void Deck<T>::shuffleStack()
{
	std::random_device rd;
	std::mt19937 g(rd());

	auto shuffledStack = std::shuffle(deck.begin(), deck.end(), g);

	deck = shuffledStack;
}

template<typename T>
T Deck<T>::draw()
{
	return deck.front();
}

template<typename T>
void Deck<T>::discard(const T & card)
{
	discardPile.push_back(card);
	deck.erase(card);
}

template<typename T>
void Deck<T>::discard(T && card)
{
	discardPile.push_back(card);
	deck.erase(card);
}

template<typename T>
void Deck<T>::push_bottom_stack(const T & card)
{
	deck.push_back(card);
}

template<typename T>
void Deck<T>::push_bottom_stack(T && card)
{
	deck.push_back(card);
}

template<typename T>
void Deck<T>::push_top_stack(const T & card)
{
	deck.push_front(card);
}

template<typename T>
void Deck<T>::push_top_stack(T && card)
{
	deck.push_front(card);
}

template<typename T>
void Deck<T>::merge_stacks(bool shuffle_afterwards)
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

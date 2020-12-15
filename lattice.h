#pragma once

#include <array>
#include <set>
#include "poset.h"

template<size_t N>
struct Lattice : public Poset<N>
{
	explicit
	Lattice(const Poset<N>& _poset, bool disp_err = true) : Poset<N>{ _poset }
	{
		is_lattice(disp_err);
	}
	
	std::array<std::array<int, N>, N>   inf;
	std::array<std::array<int, N>, N>   sup;

	bool has_inf(int x, int y, int& inf);
	bool has_sup(int x, int y, int& sup);

	bool is_lattice(bool disp_err = true);
};

template<size_t N>
bool Lattice<N>::has_inf(int x, int y, int& inf)
{
	std::set<int> inf_set;
	for (int i = 0; i < N; i++)
		if (order[i][x] && order[i][y])
			inf_set.insert(i);
	int inf_candidate{};
	
	bool is_set_inf_candidate = false;
	// find maximum
	for (const auto& el : inf_set)
	{
		if (!is_set_inf_candidate)
		{ 
			is_set_inf_candidate = true;
			inf_candidate = el;
		}
		else
		{

			if (order[inf_candidate][el])
				inf_candidate = el;
		}
	}
	
	if (!is_set_inf_candidate)
	{
		//std::cout << "Not lower semilattice. No common lower bound for x = " << x << " and y = " << y ".\n";
		return false;
	}
	// check if all elements are comparable
	for (const auto& el : inf_set)
		if (!order[el][inf_candidate])
		{ 
			//std::cout << "Not lower semilattice. No Inf for x = " << x << " and y =  " << y << ".\n";
			return false;
		}

	inf = inf_candidate;
	return true;
}

template<size_t N>
bool Lattice<N>::has_sup(int x, int y, int& sup)
{
	std::set<int> sup_set;

	for (int i = 0; i < N; i++)
		if (order[x][i] && order[y][i])
		{
			sup_set.insert(i);
		}

	int sup_candidate{};
	bool is_set_sup_candidate = false;
	// find minimum
	for (const auto& el : sup_set)
	{
		if (!is_set_sup_candidate)
		{
			is_set_sup_candidate = true;
			sup_candidate = el;
		}
		else
		{
			if (order[el][sup_candidate])
				sup_candidate = el;
		}
	}

	if (!is_set_sup_candidate)
	{
		//std::cout << "Not upper semilattice. No common upper bound for x = " << x << " and y = " << y ".\n";
		return false;
	}

	// check if all elements are comparable
	for (const auto& el : sup_set)
		if (!order[sup_candidate][el])
		{
			//std::cout << "Not upper semilattice. No Sup for x = " << x << " and y =  " << y << ".\n";
			return false;
		}	

	sup = sup_candidate;	
	return true;
}

template<size_t N>
bool Lattice<N>::is_lattice(bool disp_err)
{
	//std::cout << "HHH\n";
	int tmp{};
	// inf
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (has_inf(i, j, tmp))
				inf[i][j] = tmp;
			else
			{
				if (disp_err)
					std::cout << "Not lattice. Inf of x = " << i << "and y = " << j << " does not exist.\n";
				return false;
			}
	// sup
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (has_sup(i, j, tmp))
				sup[i][j] = tmp;
			else
			{
				if (disp_err)
					std::cout << "Not lattice. Sup of x = " << i << "and y = " << j << " does not exist.\n";
				return false;
			}

	return true;
}


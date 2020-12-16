#pragma once

#include <iostream>
#include <array>

template<size_t N>
struct Poset
{
	explicit 
	Poset(const std::array<std::array<int, N>, N>& _order, bool check = true, bool disp_err = true) : order{ _order }
	{
		if (check)
			is_poset(disp_err);
	}

	std::array<std::array<int, N>, N> order;

	bool is_reflexive(bool disp_err = true);
	bool is_antisymmetric(bool disp_err = true);
	bool is_transitive(bool disp_err = true);

	bool is_poset(bool disp_err = true);
};

template<size_t N>
bool Poset<N>::is_reflexive(bool disp_err)
{
	for (int i = 0; i < N; i++)
		if (!order[i][i])
		{
			if (disp_err)
				std::cout << "Not reflexive for i  = " << i << ".\n";
			return false;
		}

	return true;
}

template<size_t N>
bool Poset<N>::is_antisymmetric(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (order[i][j] && order[j][i] && i != j)
			{
				if (disp_err)
					std::cout << "Not antisymmetric for i = " << i << " and j = " << j << ".\n";
				return false;
			}

	return true;
}

template<size_t N>
bool Poset<N>::is_transitive(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				if (order[i][j] && order[j][k] && !order[i][k])
				{
					if (disp_err)
						std::cout << "Not transitive for i = " << i << ",  j = " << j << " and k = " << k << ".\n";
					return false;
				}

	return true;
}

template<size_t N>
bool Poset<N>::is_poset(bool disp_err)
{
	return is_reflexive(disp_err) && is_antisymmetric(disp_err) && is_transitive(disp_err);
}


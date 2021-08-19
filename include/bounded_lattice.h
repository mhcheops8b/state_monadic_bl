#pragma once

#include <iostream>
#include "lattice.h"


template<size_t N>
struct Bounded_Lattice : public Lattice<N>
{
	explicit
	Bounded_Lattice(const Lattice<N>& _lat, int _zero = 0, int _unit = N - 1, bool check = true, bool disp_err = true) 
		: Lattice<N>{ _lat }, zero{ _zero }, unit{ _unit }
	{
		if (check)
			is_bounded_lattice(disp_err);
	}
	
	int zero;
	int unit;

	bool is_bounded_lattice(bool disp_err = true);
};

template<size_t N>
bool Bounded_Lattice<N>::is_bounded_lattice(bool disp_err)
{
	for (int i = 0; i < N; i++)
		if (!this->order[zero][i])
		{
			if (disp_err)
				std::cout << "Element `" << zero << "` is not bottom element.\n";
			return false;
		}

	for (int i = 0; i < N - 1; i++)
		if (!this->order[i][unit])
		{
			if (disp_err)
				std::cout << "Element `" << unit << "` is not top element.\n";
			return false;
		}

	return true;
}

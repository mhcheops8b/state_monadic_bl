#pragma once

#include "bounded_lattice.h"
#include "print_utils.h"

template<size_t N>
struct BL : public Bounded_Lattice<N>
{
	explicit
	BL(const Bounded_Lattice<N>& _blat,
		const std::array<std::array<int, N>, N>& _dot,
		const std::array<std::array<int, N>, N>& _impl, bool check = true, bool disp_err = true) : Bounded_Lattice<N>{ _blat }, dot{ _dot }, impl{ _impl }
	{
		if (check)
			is_BL(disp_err);
	}

	std::array<std::array<int, N>, N>   dot;
	std::array<std::array<int, N>, N>  impl;

	bool has_dot_commutative(bool disp_err = true);
	bool has_dot_associative(bool disp_err = true);
	bool is_unit_dot_neutral(bool disp_err = true);

	bool is_monoid(bool disp_err = true);

	bool has_residual_property(bool disp_err = true);
	bool has_divisibility(bool disp_err = true);
	bool has_prelinearity(bool disp_err = true);

	bool is_BL(bool disp_err = true);

	void disp();
};

template<size_t N>
bool BL<N>::has_dot_commutative(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (dot[i][j] != dot[j][i])
			{
				if (disp_err)
					std::cout << "Not commutative: i = " << i << ", j = " << j << ": i * j <> j * i.\n";
				return false;
			}

	return true;
}

template<size_t N>
bool BL<N>::has_dot_associative(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				if (dot[dot[i][j]][k] != dot[i][dot[j][k]])
				{
					if (disp_err)
						std::cout << "Not associative: i = " << i << ", j = " << ", k = " << k << ": (i * j) * k <> i * (j * k).\n";
					return false;
				}

	return true;
}

template<size_t N>
bool BL<N>::is_unit_dot_neutral(bool disp_err)
{
	for (int i = 0; i < N; i++)
		if (dot[i][unit] != i)
		{
			if (disp_err)
				std::cout << "Element `" << unit << "` is not neutral for i = " << i << ".\n";
			return false;
		}

	return false;
}

template<size_t N>
bool BL<N>::is_monoid(bool disp_err)
{
	return has_dot_commutative(disp_err) && has_dot_associative(disp_err) && is_unit_dot_neutral(disp_err);
}

template<size_t N>
bool BL<N>::has_residual_property(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
			{
				if (order[dot[i][j])][k] && !order[i][impl[j][k]]
				{
					if (disp_err)
						std::cout << "Residual property: i = " << i << ", j = " << j << ", k = " << k << ": i * j <= k =/=> i <= j -> k.\n";
					return false;
				}

				if (order[i][impl[j][k]] && !order[dot[i][j]][k])
				{
					if (disp_err)
						std::cout << "Residual property: i = " << i << ", j = " << j << ", k = " << k << ": i <= j -> k =/=> i * j <= k.\n";
					return false;
				}
			}

	return true;
}

template<size_t N>
bool BL<N>::has_divisibility(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (inf[i][j] != dot[i][impl[i][j]])
			{
				if (disp_err)
					std::cout << "Divisibility: i = " << i << "j = " << j << ": i ^ j <> i * (i -> j).\n";
				return false;
			}
	return false;
}

template<size_t N>
bool BL<N>::has_prelinearity(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sup[impl[i][j]][impl[j][i]] != unit)
			{
				if (disp_err)
					std::cout << "Prelinearity: i = " << i << ", j = " << j << ": (i->j) v (j->i) <> 1.\n";
				return false;
			}
	return false;
}

template<size_t N>
bool BL<N>::is_BL(bool disp_err)
{
	return is_monoid(disp_err) && has_divisibility(disp_err) && has_prelinearity(disp_err);
	return false;
}

template<size_t N>
void BL<N>::disp()
{
	std::cout << "Order:\n";
	Print_Utils<N>::disp_binary_op(order);

	std::cout << "\nInf:\n";
	Print_Utils<N>::disp_binary_op(this->inf);

	std::cout << "\nSup:\n";
	Print_Utils<N>::disp_binary_op(this->sup);

	std::cout << "\nDot:\n";
	Print_Utils<N>::disp_binary_op(dot);

	std::cout << "\nImpl:\n";
	Print_Utils<N>::disp_binary_op(dot);
}

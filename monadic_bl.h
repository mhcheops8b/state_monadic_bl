#pragma once

#include <iostream>
#include "bl.h"
#include "print_utils.h"

template<size_t N>
struct Monadic_BL : public BL<N>
{
	explicit
	Monadic_BL(const BL<N>& bl) : BL<N>{ bl }, fa{}, ex{}
	{
		fa[zero] = ex[zero] = zero;
		fa[unit] = ex[unit] = unit;
	}
	explicit
	Monadic_BL(const BL<N>& _bl, const std::array<int, N>& _fa,
		const std::array<int, N>& _ex, bool disp_err = true) : BL<N>{ _bl }, fa{ _fa }, ex{ _ex }
	{
		is_monadic_BL(disp_err);
	}

	std::array<int, N> fa; // for all
	std::array<int, N> ex; // exists

	bool has_M1(bool disp_err = true);
	bool has_M2(bool disp_err = true);
	bool has_M3(bool disp_err = true);
	bool has_M4(bool disp_err = true);
	bool has_M5(bool disp_err = true);

	bool is_monadic_BL(bool disp_err = true);
	void disp();

	void gen_all_fa(int level);
	void gen_all_ex(int level);
};

template<size_t N>
bool Monadic_BL<N>::has_M1(bool disp_err)
{
	for (int i = 0; i < N; i++)
		if (impl[fa[i]][i] != unit)
		{
			if (disp_err)
				std::cout << "M1: i = " << i << ": forall(i) -> i <> 1.\n";
			return false;
		}

	return true;
}

template<size_t N>
bool Monadic_BL<N>::has_M2(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (fa[impl[i][fa[j]]] != impl[ex[i]][fa[j]])
			{
				if (disp_err)
					std::cout << "M2: i = " << i << ", j = " << j << ": forall(i->forall(j)) <> exists(i)->forall(j).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool Monadic_BL<N>::has_M3(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (fa[impl[fa[i]][j]] != impl[fa[i]][fa[j]])
			{
				if (disp_err)
					std::cout << "M3: i = " << i << ", j = " << j << ": forall(forall(i)->j) <> forall(i)->forall(j).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool Monadic_BL<N>::has_M4(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (fa[sup[ex[i]][j]] != sup[ex[i]][fa[j]])
			{
				if (disp_err)
					std::cout << "M4: i = " << i << ", j = " << j << ": forall(exists(i) v j) <> exists(i) v exists(j).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool Monadic_BL<N>::has_M5(bool disp_err)
{
	for (int i = 0; i < N; i++)
		if (ex[dot[i][i]] != dot[ex[i]][ex[i]])
		{
			if (disp_err)
				std::cout << "M5: i = " << i << ": exists(i * i) <> exists(i) * exists(i).\n";
			return false;
		}

	return true;
}

template<size_t N>
bool Monadic_BL<N>::is_monadic_BL(bool disp_err)
{
	return has_M1(disp_err) && has_M2(disp_err) &&
		has_M3(disp_err) && has_M4(disp_err) && has_M5(disp_err);
}

template<size_t N>
void Monadic_BL<N>::disp()
{
	BL<N>::disp();
	std::cout << "For all:\n";
	Print_Utils<N>::disp_unary_op(fa);
	std::cout << "Exists:\n";
	Print_Utils<N>::disp_unary_op(ex);

}

template<size_t N>
void Monadic_BL<N>::gen_all_fa(int level)
{
	if (level == N - 1)
	{
		gen_all_ex(1);
	}
	else
	{
		for (int i = 0; i < N; i++)
			if (order[i][level])
			{
				fa[level] = i;
				gen_all_fa(level + 1);
			}
	}
}

template<size_t N>
void Monadic_BL<N>::gen_all_ex(int level)
{
	if (level == N - 1)
	{
		if (is_monadic_BL(false))
		{
			std::cout << "For all:\n";
			Print_Utils<N>::disp_unary_op(fa);
			std::cout << "Exists:\n";
			Print_Utils<N>::disp_unary_op(ex);
		}
	}
	else
	{
		for (int i = 0; i < N; i++)
			if (order[level][i])
			{
				ex[level] = i;
				gen_all_ex(level + 1);
			}
	}
}



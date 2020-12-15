#pragma once

#include <iostream>
#include "monadic_bl.h"
#include "state_bl.h"

template<size_t N>
struct State_Monadic_BL : public Monadic_BL<N>
{
	explicit
	State_Monadic_BL(const Monadic_BL<N>& _mbl) : Monadic_BL<N>{ _mbl }, sg{}
	{
		sg[zero] = zero;
		sg[unit] = unit;
	}

	explicit
	State_Monadic_BL(const Monadic_BL<N>& _mbl, const std::array<int, N>& _sg, bool disp_err = true)
		: Monadic_BL<N>{ _mbl }, sg{ _sg }
	{
		is_state_monadic_BL(disp_err);
	}

	explicit
	State_Monadic_BL(const State_BL<N>& _sbl, const std::array<int, N>& _fa, const std::array<int, N>& _ex, bool disp_err = true)
		: Monadic_BL<N>{ 
				BL<N>{
					Bounded_Lattice<N>{
						Lattice<N>
						{
							Poset<N>{_sbl.order, disp_err},
							disp_err
						}, 
						_sbl.zero, 
						_sbl.unit,
						disp_err
					}, 
					_sbl.dot, 
					_sbl.impl,
					disp_err
				}, 
				_fa, 
				_ex,
				disp_err
		   }, sg{ _sbl.sg }
	{
		is_state_monadic_BL(disp_err);
	}

	std::array<int, N> sg; // sigma (internal state)

	bool has_SM1(bool disp_err = true);
	bool has_SM2(bool disp_err = true);
	bool has_SM3(bool disp_err = true);
	bool has_SM4(bool disp_err = true);
	bool has_SM5(bool disp_err = true);
	bool has_SM6(bool disp_err = true);
	bool has_SM7(bool disp_err = true);

	bool is_state_monadic_BL(bool disp_err = true);
};

template<size_t N>
bool State_Monadic_BL<N>::has_SM1(bool disp_err)
{
	if (sg[zero] != zero)
	{
		if (disp_err)
			std::cout << "SM1: sigma(zero) <> zero for zero = " << zero << ".\n";
		return false;
	}
	return true;
}

template<size_t N>
bool State_Monadic_BL<N>::has_SM2(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[impl[i][j]] != impl[sg[i]][sg[inf[i][j]]])
			{
				if (disp_err)
					std::cout << "SM2: i = " << i << ", j = " << j << ": sigma(i -> j) <> sigma(i) -> sigma(i ^ j).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool State_Monadic_BL<N>::has_SM3(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[dot[i][j]] != dot[sg[i]][sg[impl[i][dot[i][j]]]])
			{
				if (disp_err)
					std::cout << "SM3: i = " << i << ", j = " << j << ": sigma(i * j) <> sigma( i -> (i * j) ).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool State_Monadic_BL<N>::has_SM4(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[dot[sg[i]][sg[j]]] != dot[sg[i]][sg[j]])
			{
				if (disp_err)
					std::cout << "SM4: i = " << i << ", j = " << j << ": sigma(sigma(i) * sigma(j) <> sigma(i) * sigma(j).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool State_Monadic_BL<N>::has_SM5(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[impl[sg[i]][sg[j]]] != impl[sg[i]][sg[j]])
			{
				if (disp_err)
					std::cout << "SM5: i = " << i << ", j = " << j << ": sigma(sigma(i) -> sigma(j) <> sigma(i) -> sigma(j).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool State_Monadic_BL<N>::has_SM6(bool disp_err)
{
	for (int i = 0; i < N; i++)
		if (sg[fa[i]] != fa[sg[i]])
		{
			if (disp_err)
				std::cout << "SM6: i = " << i << ": sigma(forall(i)) <> forall(sigma(i)).\n";
			return false;
		}

	return true;
}

template<size_t N>
bool State_Monadic_BL<N>::has_SM7(bool disp_err)
{
	for (int i = 0; i < N; i++)
		if (sg[ex[i]] != ex[sg[i]])
		{
			if (disp_err)
				std::cout << "SM7: i = " << i << ": sigma(exists(i)) <> exists(sigma(i)).\n";
			return false;
		}

	return true;
}

template<size_t N>
bool State_Monadic_BL<N>::is_state_monadic_BL(bool disp_err)
{
	return has_SM1(disp_err) && has_SM2(disp_err) && has_SM3(disp_err) &&
		has_SM4(disp_err) && has_SM5(disp_err) && has_SM6(disp_err) &&
		has_SM7(disp_err);
}



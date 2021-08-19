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
		sg[this->zero] = this->zero;
		sg[this->unit] = this->unit;
	}

	explicit
	State_Monadic_BL(const Monadic_BL<N>& _mbl, const std::array<int, N>& _sg, bool check = true, bool disp_err = true)
		: Monadic_BL<N>{ _mbl }, sg{ _sg }
	{
		if (check)
			is_state_monadic_BL(disp_err);
	}

	explicit
	State_Monadic_BL(const State_BL<N>& _sbl, const std::array<int, N>& _fa, const std::array<int, N>& _ex, bool check = true, bool disp_err = true)
		: Monadic_BL<N>{ 
				BL<N>{
					Bounded_Lattice<N>{
						Lattice<N>
						{
							Poset<N>
							{ 
								_sbl.order,
								check,
								disp_err
							},
							disp_err
						}, 
						_sbl.zero, 
						_sbl.unit,
						check,
						disp_err
					}, 
					_sbl.dot, 
					_sbl.impl,
					check,
					disp_err
				}, 
				_fa, 
				_ex,
				check,
				disp_err
		   }, sg{ _sbl.sg }
	{
		if (check)
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
	State_BL<N> get_state_BL_reduct();
};

template<size_t N>
bool State_Monadic_BL<N>::has_SM1(bool disp_err)
{
	if (sg[this->zero] != this->zero)
	{
		if (disp_err)
			std::cout << "SM1: sigma(zero) <> zero for zero = " << this->zero << ".\n";
		return false;
	}
	return true;
}

template<size_t N>
bool State_Monadic_BL<N>::has_SM2(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[this->impl[i][j]] != this->impl[sg[i]][sg[this->inf[i][j]]])
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
			if (sg[this->dot[i][j]] != this->dot[sg[i]][sg[this->impl[i][this->dot[i][j]]]])
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
			if (sg[this->dot[sg[i]][sg[j]]] != this->dot[sg[i]][sg[j]])
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
			if (sg[this->impl[sg[i]][sg[j]]] != this->impl[sg[i]][sg[j]])
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
		if (sg[this->fa[i]] != this->fa[sg[i]])
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
		if (sg[this->ex[i]] != this->ex[sg[i]])
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
	return get_state_BL_reduct().is_state_BL(disp_err) && 
		has_SM6(disp_err) && has_SM7(disp_err);
}

template<size_t N>
State_BL<N> State_Monadic_BL<N>::get_state_BL_reduct()
{
	return
		State_BL<N>{
			BL<N>{
				Bounded_Lattice<N>{
					Lattice<N>{
						Poset<N>{this->order, false}, 
						false
					}, 
					this->zero, 
					this->unit, 
					false
				},
				this->dot, 
				this->impl, 
				false
			}, 
			sg, 
			false
		};
}


// modal_state_bl.cpp : Defines the entry point for the application.
//

//#include "modal_state_bl.h"

//using namespace std;

#include <iostream>
#include <array>
#include <set>

std::array<std::array<int, 5>, 5> ex3_1_ord = { {
	{1, 1, 1, 1, 1},
	{0, 1, 0, 0, 1},
	{0, 0, 1, 0, 1},
	{0, 1, 1, 1, 1},
	{0, 0, 0, 0, 1}
} };

std::array<std::array<int, 5>, 5> ex3_1_inf = { {
	{0, 0, 0, 0, 0},
	{0, 1, 3, 3, 1},
	{0, 3, 2, 3, 2},
	{0, 3, 3, 3, 3},
	{0, 1, 2, 3, 4}
} };

std::array<std::array<int, 5>, 5> ex3_1_sup = { {
	{0, 1, 2, 3, 4},
	{1, 1, 4, 1, 4},
	{2, 4, 2, 2, 4},
	{3, 1, 2, 3, 4},
	{4, 4, 4, 4, 4}
} };


std::array<std::array<int, 5>, 5> ex3_1_dot = { {
	{0, 0, 0, 0, 0},
	{0, 1, 3, 3, 1},
	{0, 3, 2, 3, 2},
	{0, 3, 3, 3, 3},
	{0, 1, 2, 3, 4}
} };

std::array<std::array<int, 5>, 5> ex3_1_imp = { {
	{4, 4, 4, 4, 4},
	{0, 4, 2, 2, 4},
	{0, 1, 4, 1, 4},
	{0, 4, 4, 4, 4},
	{0, 1, 2, 3, 4}
} };

std::array<int, 5> ex3_1_sg1{ 0, 3, 4, 3, 4 };
std::array<int, 5> ex3_1_sg2{ 0, 1, 2, 3, 4 };
std::array<int, 5> ex3_1_sg3{ 0, 4, 3, 3, 4 };
std::array<int, 5> ex3_1_sg4{ 0, 1, 4, 1, 4 };
std::array<int, 5> ex3_1_sg5{ 0, 4, 2, 2, 4 };
std::array<int, 5> ex3_1_sg6{ 0, 4, 4, 4, 4 };

std::array<int, 5> ex3_1_fa1{ 0, 0, 0, 0, 4 };
std::array<int, 5> ex3_1_fa2{ 0, 3, 3, 3, 4 };
std::array<int, 5> ex3_1_fa3{ 0, 1, 2, 3, 4 };

std::array<int, 5> ex3_1_ex1{ 0, 4, 4, 4, 4 };
std::array<int, 5> ex3_1_ex2{ 0, 4, 4, 3, 4 };
std::array<int, 5> ex3_1_ex3{ 0, 1, 2, 3, 4 };


template<int N>
bool has_SM1(const std::array<int, N>& sg)
{
	return (sg[0] == 0);
}

template<int N>
bool has_SM2(const std::array<int, N>& sg, const std::array<std::array<int, N>, N> &inf, const std::array<std::array<int, N>, N>& imp)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[imp[i][j]] != imp(sg[i], sg[inf[i][j]]))
				return false;

	return true;
}

template<int N>
bool has_SM3(const std::array<int, N>& sg, const std::array<std::array<int, N>, N>& dot, const std::array<std::array<int, N>, N>& imp)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[dot[i][j]] != dot[ sg[i] ][ sg[ imp[ i ][ dot[i][j] ] ]])
				return false;

	return true;
}

template<int N>
bool has_SM4(const std::array<int, N>& sg, const std::array<std::array<int, N>, N>& dot)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[ dot[sg[i]][sg[j]] ]!= dot[sg[i]][sg[j]])
				return false;

	return true;
}

template<int N>
bool has_SM5(const std::array<int, N>& sg, const std::array<std::array<int, N>, N>& imp)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[imp[sg[i]][sg[j]]] != imp[sg[i]][sg[j]])
				return false;

	return true;
}

template<int N>
bool has_SM6(const std::array<int, N>& sg, const std::array<int, N>& fa)
{
	for (int i = 0; i < N; i++)
		if (sg[fa[i]] != fa[sg[i]])
			return false;
	
	return true;
}

template<int N>
bool has_SM7(const std::array<int, N>& sg, const std::array<int, N>& ex)
{
	for (int i = 0; i < N; i++)
		if (sg[ex[i]] != ex[sg[i]])
			return false;

	return true;
}

template<size_t N>
struct BL
{
	BL(const std::array<std::array<int, N>, N>& _order,
		const std::array<std::array<int, N>, N>& _dot,
		const std::array<std::array<int, N>, N>& _impl,
		size_t _zero = 0, size_t _unit = N - 1) :
		order(_order), dot(_dot), 
		impl(_impl), zero(_zero), unit(_unit), inf{}, sup{}
	{
		init();
	}
	std::array<std::array<int, N>, N> order;
	std::array<std::array<int, N>, N>   dot;
	std::array<std::array<int, N>, N>  impl;

	int zero;
	int unit;
	std::array<std::array<int, N>, N>   inf;
	std::array<std::array<int, N>, N>   sup;
	
	// initializes inf and sup arrays and checks whether it is a bounded lattice
	bool init();
	
	bool has_inf(int x, int y, int &inf);
	bool has_sup(int x, int y, int &sup);
	
	bool has_dot_commutative();
	bool has_dot_associative();
	bool is_unit_dot_neutral();

	bool is_monoid();

	bool has_residual_property();
	bool has_divisibility();
	bool has_prelinearity();
	
	bool is_BL();

	static void disp_bin_op(const std::array<std::array<int, N>, N> &bin_op);
	static void disp_unary_op(const std::array<int, N> &bin_op);
	void disp();
};

template<size_t N>
struct monadic_BL : public BL<N>
{
	monadic_BL(const BL<N> &bl) : BL<N>{ bl }, fa{}, ex{} 
	{
		fa[zero] = ex[zero] = zero;  
		fa[unit] = ex[unit] = unit;
	}
	monadic_BL(const BL<N> & _bl, const std::array<int, N> & _fa, 
		const std::array<int, N> & _ex) : BL<N>{ _bl }, fa{ _fa }, ex{ _ex } {}

	std::array<int, N> fa; // for all
	std::array<int, N> ex; // exists

	bool has_M1(bool disp_err = true);
	bool has_M2(bool disp_err = true);
	bool has_M3(bool disp_err = true);
	bool has_M4(bool disp_err = true);
	bool has_M5(bool disp_err = true);

	bool is_monadic_BL(bool disp_err = true);

	void gen_all_fa(int level);
	void gen_all_ex(int level);
};

template<size_t N>
struct state_monadic_BL : public monadic_BL<N>
{
	state_monadic_BL(const monadic_BL &_mbl) : monadic_BL{ _mbl }, sg{} 
	{
		sg[zero] = zero; 
		sg[unit] = unit;
	}

	state_monadic_BL(const monadic_BL &_mbl, const std::array<int, N> & _sg)
		: monadic_BL{ _mbl }, sg{ _sg } {}

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
struct state_BL : public BL<N>
{
	state_BL(const BL<N> &_bl) : BL<N>(_bl), sg{} 
	{
		sg[zero] = zero;
		sg[unit] = unit;
	};
	state_BL(const BL<N> &_bl, const std::array<int, N> &_sg) : BL<N>(_bl), sg(_sg) {}
	std::array<int, N> sg; // sigma (internal state)

	// same as for state monadic
	bool has_SM1(bool disp_err = true);
	bool has_SM2(bool disp_err = true);
	bool has_SM3(bool disp_err = true);
	bool has_SM4(bool disp_err = true);
	bool has_SM5(bool disp_err = true);

	bool is_state_BL(bool disp_err = true);

	void disp();
	void gen_all_sg(int level);
};




template<size_t N>
bool BL<N>::init()
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
				std::cout << "Not lattice. Sup of x = " << i << "and y = " << j << " does not exist.\n";
				return false;
			}

	for (int i = 0; i < N; i++)
		if (!order[zero][i])
		{
			std::cout << "Element `" << zero << "` is not bottom element.\n";
			return false;
		}

	for (int i = 0; i < N - 1; i++)
		if (!order[i][unit])
		{
			std::cout << "Element `" << unit << "` is not top element.\n";
			return false;
		}
	return true;
}

template<size_t N>
bool BL<N>::has_inf(int x, int y, int &inf)
{
	std::set<int> inf_set;
	for (int i = 0; i < N; i++)
		if (order[i][x] && order[i][y])
			inf_set.insert(i);
	int inf_candidate = 0;
	// find minimum
	for (const auto& el : inf_set)
		if (order[inf_candidate][el])
			inf_candidate = el;
	// check if all elements are comparable
	for (const auto& el : inf_set)
		if (!order[el][inf_candidate])
			return false;

	inf = inf_candidate;
	return true;
}

template<size_t N>
bool BL<N>::has_sup(int x, int y, int& sup)
{
	std::set<int> sup_set;

	//std::cout << "x = " << x << ", y = " << y << ": ";
	for (int i = 0; i < N; i++)
		if (order[x][i] && order[y][i])
		{ 
			sup_set.insert(i);
			//std::cout << i << ", ";
		}
	//std::cout << '\n';



	int sup_candidate = N - 1;
	// find minimum
	for (const auto& el : sup_set)
		if (order[el][sup_candidate])
			sup_candidate = el;

	// check if all elements are comparable
	for (const auto& el : sup_set)
		if (!order[sup_candidate][el])
			return false;

	sup = sup_candidate;
	//std::cout << sup_candidate << '\n';
	return true;
}

template<size_t N>
bool BL<N>::has_dot_commutative()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (dot[i][j] != dot[j][i])
			{
				std::cout << "Not commutative: i = " << i << ", j = " << j << ": i * j <> j * i.\n";
				return false;
			}
	
	return true;
}

template<size_t N>
bool BL<N>::has_dot_associative()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				if (dot[dot[i][j]][k] != dot[i][dot[j][k]])
				{
					std::cout << "Not associative: i = " << i << ", j = " << ", k = " << k ": (i * j) * k <> i * (j * k).\n";
					return false;
				}
	
	return true;
}

template<size_t N>
bool BL<N>::is_unit_dot_neutral()
{
	for (int i = 0; i < N; i++)
		if (dot[i][unit] != i)
		{
			std::cout << "Element `" << unit << "` is not neutral for i = " << i ".\n";
			return false;
		}
	
	return false;
}

template<size_t N>
bool BL<N>::is_monoid()
{
	return has_dot_commutative() && has_dot_associative() && is_unit_dot_neutral();
}

template<size_t N>
bool BL<N>::has_residual_property()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
			{ 
				if (order[dot[i][j])][k] && !order[i][impl[j][k]]
				{
					std::cout << "i = " << i << ", j = " << j << ", k = " << k << ": i * j <= k =/=> i <= j -> k.\n";
					return false;
				}
				if (order[i][impl[j][k]] && !order[dot[i][j]][k])
				{
					std::cout << "i = " << i << ", j = " << j << ", k = " << k << ": i <= j -> k =/=> i * j <= k.\n";
					return false;
				}
			}
	
	return true;
}

template<size_t N>
bool BL<N>::has_divisibility()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (inf[i][j] != dot[i][impl[i][j]])
			{
				std::cout << "i = " << i << "j = " << j << ": i ^ j <> i * (i -> j).\n";
				return false;
			}
	return false;
}

template<size_t N>
bool BL<N>::has_prelinearity()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sup[impl[i][j]][impl[j][i]] != unit)
			{
				std::cout << "i = " << i << ", j = " << j << ": (i->j) v (j->i) <> 1.\n";
				return false;
			}
	return false;
}

template<size_t N>
bool BL<N>::is_BL()
{
	return is_monoid() && has_divisibility() && has_prelinearity();
	return false;
}

template<size_t N>
void BL<N>::disp_bin_op(const std::array<std::array<int, N>, N>& bin_op)
{
	for (int i = 0; i < N; i++)
	{
		bool is_first = true;
		for (int j = 0; j < N; j++)
		{
			if (is_first)
				is_first = false;
			else
			{
				std::cout << ", ";
			}

			std::cout << bin_op[i][j];
		}

		std::cout << '\n';
	}
}

template<size_t N>
void BL<N>::disp_unary_op(const std::array<int, N>& unary_op)
{
	bool is_first = true;
	for (int i = 0; i < N; i++)
	{
		if (is_first)
			is_first = false;
		else
		{
			std::cout << ", ";
		}

		std::cout << unary_op[i];
	}

	std::cout << '\n';
}

template<size_t N>
void BL<N>::disp()
{
	std::cout << "Order:\n";
	BL<N>::disp_bin_op(order);

	std::cout << "\nInf:\n";
	BL<N>::disp_bin_op(this->inf);

	std::cout << "\nSup:\n";
	BL<N>::disp_bin_op(this->sup);

	std::cout << "\nDot:\n";
	BL<N>::disp_bin_op(dot);

	std::cout << "\nImpl:\n";
	BL<N>::disp_bin_op(dot);
}




template<size_t N>
bool monadic_BL<N>::has_M1(bool disp_err)
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
bool monadic_BL<N>::has_M2(bool disp_err)
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
bool monadic_BL<N>::has_M3(bool disp_err)
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
bool monadic_BL<N>::has_M4(bool disp_err)
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
bool monadic_BL<N>::has_M5(bool disp_err)
{
	for (int i = 0; i < N; i++)
		if (ex[ dot[i][i] ] != dot[ex[i]][ex[i]])
		{
			if (disp_err)
				std::cout << "M5: i = " << i << ": exists(i * i) <> exists(i) * exists(i).\n";
			return false;
		}

	return true;
}

template<size_t N>
bool monadic_BL<N>::is_monadic_BL(bool disp_err)
{
	return has_M1(disp_err) && has_M2(disp_err) && 
		has_M3(disp_err) && has_M4(disp_err) && has_M5(disp_err);
}

template<size_t N>
void monadic_BL<N>::gen_all_fa(int level)
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
void monadic_BL<N>::gen_all_ex(int level)
{
	if (level == N - 1)
	{
		if (is_monadic_BL(false))
		{ 
			std::cout << "For all:\n";
			BL<N>::disp_unary_op(fa);
			std::cout << "Exists:\n";
			BL<N>::disp_unary_op(ex);
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


template<size_t N>
bool state_monadic_BL<N>::has_SM1(bool disp_err)
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
bool state_monadic_BL<N>::has_SM2(bool disp_err)
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
bool state_monadic_BL<N>::has_SM3(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[dot[i][j]] != dot[ sg[i] ][ sg[ impl[i][dot[i][j]] ] ] )
			{
				if (disp_err)
					std::cout << "SM3: i = " << i << ", j = " << j << ": sigma(i * j) <> sigma( i -> (i * j) ).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool state_monadic_BL<N>::has_SM4(bool disp_err)
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
bool state_monadic_BL<N>::has_SM5(bool disp_err)
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
bool state_monadic_BL<N>::has_SM6(bool disp_err)
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
bool state_monadic_BL<N>::has_SM7(bool disp_err)
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
bool state_monadic_BL<N>::is_state_monadic_BL(bool disp_err)
{
	return has_SM1(disp_err) && has_SM2(disp_err) && has_SM3(disp_err) && 
		has_SM4(disp_err) && has_SM5(disp_err) && has_SM6(disp_err) && 
		has_SM7(disp_err);
}

template<size_t N>
bool state_BL<N>::has_SM1(bool disp_err)
{
	if (sg[zero] != zero)
	{
		if (disp_err)
			std::cout << "SM1: sg(zero) <> zero for zero = " << zero << ".\n";
		return false;
	}
	return true;
}

template<size_t N>
bool state_BL<N>::has_SM2(bool disp_err)
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
bool state_BL<N>::has_SM3(bool disp_err)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sg[dot[i][j]] != dot[ sg[i] ][ sg[ impl[i][dot[i][j]] ] ] )
			{
				if (disp_err)
					std::cout << "SM3: i = " << i << ", j = " << j << ": sigma(i * j) <> sigma( i -> (i * j) ).\n";
				return false;
			}

	return true;
}

template<size_t N>
bool state_BL<N>::has_SM4(bool disp_err)
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
bool state_BL<N>::has_SM5(bool disp_err)
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
bool state_BL<N>::is_state_BL(bool disp_err)
{
	return has_SM1(disp_err) && has_SM2(disp_err) && has_SM3(disp_err) &&
		   has_SM4(disp_err) && has_SM5(disp_err);
}

template<size_t N>
void state_BL<N>::disp()
{
	BL<N>::disp();
	std::cout << "\nSigma (internal state):\n";
	BL<N>::disp_unary_op(sg);
}

template<size_t N>
void state_BL<N>::gen_all_sg(int level)
{
	if (level == N)
	{
		if (is_state_BL(false))
		{
			BL<N>::disp_unary_op(sg);
		}

	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			sg[level] = i;
			gen_all_sg(level + 1);
			sg[level] = 0;
		}
	}
}

int main()
{
	BL<5> ex3_1_bl{ ex3_1_ord , ex3_1_dot, ex3_1_imp };

	if (ex3_1_bl.init())
	{
		state_BL<5> sbl1{ ex3_1_bl, ex3_1_sg1 };
		state_BL<5> sbl2{ ex3_1_bl, ex3_1_sg2 };
		state_BL<5> sbl3{ ex3_1_bl, ex3_1_sg3 };
		state_BL<5> sbl4{ ex3_1_bl, ex3_1_sg4 };
		state_BL<5> sbl5{ ex3_1_bl, ex3_1_sg5 };
		state_BL<5> sbl6{ ex3_1_bl, ex3_1_sg6 };

		//sbl1.disp();
		std::cout << "SBL1: ";
		if (sbl1.is_state_BL())
			std::cout << "OK.\n";
		else
			std::cout << "NO!\n";

		std::cout << "SBL2: ";
		if (sbl2.is_state_BL())
			std::cout << "OK.\n";
		else
			std::cout << "NO!\n";

		std::cout << "SBL3: ";
		if (sbl3.is_state_BL())
			std::cout << "OK.\n";
		else
			std::cout << "NO!\n";

		std::cout << "SBL4: ";
		if (sbl4.is_state_BL())
			std::cout << "OK.\n";
		else
			std::cout << "NO!\n";

		std::cout << "SBL5: ";
		if (sbl5.is_state_BL())
			std::cout << "OK.\n";
		else
			std::cout << "NO!\n";

		std::cout << "SBL6: ";
		if (sbl6.is_state_BL())
			std::cout << "OK.\n";
		else
			std::cout << "NO!\n";

		state_BL<5> sbl{ ex3_1_bl };
		
		sbl.gen_all_sg(1);

		monadic_BL<5> mbl{ ex3_1_bl };
		mbl.gen_all_fa(1);

		std::array<std::array<int, 5>, 6> arr_sg{ ex3_1_sg1, ex3_1_sg2, ex3_1_sg3, ex3_1_sg4, ex3_1_sg5,ex3_1_sg6 };
		std::array<monadic_BL<5>, 3> arr_mbl {
			monadic_BL<5>{ex3_1_bl, ex3_1_fa1, ex3_1_ex1},
			monadic_BL<5>{ex3_1_bl, ex3_1_fa2, ex3_1_ex2},
			monadic_BL<5>{ex3_1_bl, ex3_1_fa3, ex3_1_ex3}
		};

		for (int i= 0; i < 3; i++)
			for (int j = 0; j < 6; j++)
			{
				state_monadic_BL<5> smbl{arr_mbl[i], arr_sg[j]};
				if (smbl.is_state_monadic_BL(false))
					std::cout << "sigma_" << (j + 1) << ", forall_" << (i + 1) << ", exists_" << (i + 1) << '\n';

			}

	}

	return 0;
}
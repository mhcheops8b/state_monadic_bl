#pragma once

template<size_t N>
struct State_BL : public BL<N>
{
	explicit
	State_BL(const BL<N>& _bl) : BL<N>{ _bl }, sg{}
	{
		sg[zero] = zero;
		sg[unit] = unit;
	}
	
	explicit
	State_BL(const BL<N>& _bl, const std::array<int, N>& _sg, bool check = true, bool disp_err = true) : BL<N>{ _bl }, sg{ _sg }
	{
		if (check)
			is_state_BL(disp_err);
	}
	
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
bool State_BL<N>::has_SM1(bool disp_err)
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
bool State_BL<N>::has_SM2(bool disp_err)
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
bool State_BL<N>::has_SM3(bool disp_err)
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
bool State_BL<N>::has_SM4(bool disp_err)
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
bool State_BL<N>::has_SM5(bool disp_err)
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
bool State_BL<N>::is_state_BL(bool disp_err)
{
	return has_SM1(disp_err) && has_SM2(disp_err) && has_SM3(disp_err) &&
		has_SM4(disp_err) && has_SM5(disp_err);
}

template<size_t N>
void State_BL<N>::disp()
{
	BL<N>::disp();
	std::cout << "\nSigma (internal state):\n";
	Print_Utils<N>::disp_unary_op(sg);
}

template<size_t N>
void State_BL<N>::gen_all_sg(int level)
{
	if (level == N)
	{
		if (is_state_BL(false))
		{
			Print_Utils<N>::disp_unary_op(sg);
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


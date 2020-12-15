#pragma once

#include <array>
#include <iostream>

template<size_t N>
struct Print_Utils
{
	static void disp_binary_op(const std::array<std::array<int, N>, N>& bin_op);
	static void disp_unary_op(const std::array<int, N>& bin_op);
};


template<size_t N>
void Print_Utils<N>::disp_binary_op(const std::array<std::array<int, N>, N>& bin_op)
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
void Print_Utils<N>::disp_unary_op(const std::array<int, N>& unary_op)
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
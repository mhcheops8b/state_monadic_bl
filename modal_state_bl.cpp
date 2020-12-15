// modal_state_bl.cpp : Defines the entry point for the application.
//

//#include "modal_state_bl.h"

//using namespace std;

#include <iostream>
#include <array>
#include <set>

#include "bl.h"
#include "monadic_bl.h"
#include "state_monadic_bl.h"
#include "state_bl.h"

#include "print_utils.h"

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

int main()
{
	BL<5> ex3_1_bl{ Bounded_Lattice<5>{Lattice<5>{Poset<5>{ex3_1_ord}}} , ex3_1_dot, ex3_1_imp };

#if 0
	if (ex3_1_bl.init())
	{
#endif
		State_BL<5> sbl1{ ex3_1_bl, ex3_1_sg1 };
		State_BL<5> sbl2{ ex3_1_bl, ex3_1_sg2 };
		State_BL<5> sbl3{ ex3_1_bl, ex3_1_sg3 };
		State_BL<5> sbl4{ ex3_1_bl, ex3_1_sg4 };
		State_BL<5> sbl5{ ex3_1_bl, ex3_1_sg5 };
		State_BL<5> sbl6{ ex3_1_bl, ex3_1_sg6 };

#if 0
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
#endif
		State_BL<5> sbl{ ex3_1_bl };
		
		sbl.gen_all_sg(1);

		Monadic_BL<5> mbl{ ex3_1_bl };
		mbl.gen_all_fa(1);

		std::array<std::array<int, 5>, 6> arr_sg{ ex3_1_sg1, ex3_1_sg2, ex3_1_sg3, ex3_1_sg4, ex3_1_sg5,ex3_1_sg6 };
		std::array<Monadic_BL<5>, 3> arr_mbl {
			Monadic_BL<5>{ex3_1_bl, ex3_1_fa1, ex3_1_ex1},
			Monadic_BL<5>{ex3_1_bl, ex3_1_fa2, ex3_1_ex2},
			Monadic_BL<5>{ex3_1_bl, ex3_1_fa3, ex3_1_ex3}
		};

		for (int i= 0; i < 3; i++)
			for (int j = 0; j < 6; j++)
			{
				State_Monadic_BL<5> smbl{arr_mbl[i], arr_sg[j], false};
				if (smbl.is_state_monadic_BL(false))
					std::cout << "sigma_" << (j + 1) << ", forall_" << (i + 1) << ", exists_" << (i + 1) << '\n';

			}
#if 0
	}
#endif

	return 0;
}


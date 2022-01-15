#include "tests.h"

START_TEST(Day1_P1)
{	
	int exampleResult = day1_p1("../src/Day1/day1.example");
	if(showResults){
		printf("Day1 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day1_p1("../src/Day1/day1.input");
		printf("Day1 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 7);
}
END_TEST

START_TEST(Day1_P2)
{	
	int exampleResult = day1_p2("../src/Day1/day1.example");
	if(showResults){
		printf("Day1 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day1_p2("../src/Day1/day1.input");
		printf("Day1 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 5);
}
END_TEST

START_TEST(Day2_P1)
{	
	int exampleResult = day2_p1("../src/Day2/day2.example");
	if(showResults){
		printf("Day2 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day2_p1("../src/Day2/day2.input");
		printf("Day2 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 150);
}
END_TEST

START_TEST(Day2_P2)
{	
	int exampleResult = day2_p2("../src/Day2/day2.example");
	if(showResults){
		printf("Day2 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day2_p2("../src/Day2/day2.input");
		printf("Day2 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 900);
}
END_TEST

START_TEST(Day3_P1)
{	
	int exampleResult = day3_p1("../src/Day3/day3.example");
	if(showResults){
		printf("Day3 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day3_p1("../src/Day3/day3.input");
		printf("Day3 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 198);
}
END_TEST

START_TEST(Day3_P2)
{	
	int exampleResult = day3_p2("../src/Day3/day3.example");
	if(showResults){
		printf("Day3 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day3_p2("../src/Day3/day3.input");
		printf("Day3 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 230);
}
END_TEST

START_TEST(Day4_P1)
{	
	int exampleResult = day4_p1("../src/Day4/day4.example");
	if(showResults){
		printf("Day4 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day4_p1("../src/Day4/day4.input");
		printf("Day4 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 4512);
}
END_TEST

START_TEST(Day4_P2)
{	
	int exampleResult = day4_p2("../src/Day4/day4.example");
	if(showResults){
		printf("Day4 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day4_p2("../src/Day4/day4.input");
		printf("Day4 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 1924);
}

START_TEST(Day5_P1)
{	
	int exampleResult = day5_p1("../src/Day5/day5.example");
	if(showResults){
		printf("Day5 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day5_p1("../src/Day5/day5.input");
		printf("Day5 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 5);
}
END_TEST

START_TEST(Day5_P2)
{	
	int exampleResult = day5_p2("../src/Day5/day5.example");
	if(showResults){
		printf("Day5 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day5_p2("../src/Day5/day5.input");
		printf("Day5 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 12);
}
END_TEST

START_TEST(Day6_P1)
{	
	int exampleResult = day6_p1("../src/Day6/day6.example");
	if(showResults){
		printf("Day6 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day6_p1("../src/Day6/day6.input");
		printf("Day6 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 5934);
}
END_TEST

START_TEST(Day6_P2)
{	
	long long int exampleResult = day6_p2("../src/Day6/day6.example");
	if(showResults){
		printf("Day6 Part2 Example: %lld\n", exampleResult);
	
		long long int inputResult = day6_p2("../src/Day6/day6.input");
		printf("Day6 Part2 Input  : %lld\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 26984457539);
}
END_TEST

START_TEST(Day7_P1)
{	
	int exampleResult = day7_p1("../src/Day7/day7.example");
	if(showResults){
		printf("Day7 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day7_p1("../src/Day7/day7.input");
		printf("Day7 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 37);
}
END_TEST

START_TEST(Day7_P2)
{	
	int exampleResult = day7_p2("../src/Day7/day7.example");
	if(showResults){
		printf("Day7 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day7_p2("../src/Day7/day7.input");
		printf("Day7 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 168);
}
END_TEST

START_TEST(Day8_P1)
{	
	int exampleResult = day8_p1("../src/Day8/day8.example");
	if(showResults){
		printf("Day8 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day8_p1("../src/Day8/day8.input");
		printf("Day8 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 26);
}
END_TEST

START_TEST(Day8_P2)

{	
	int exampleResult = day8_p2("../src/Day8/day8.example");
	if(showResults){
		printf("Day8 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day8_p2("../src/Day8/day8.input");
		printf("Day8 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 61229);
}
END_TEST

START_TEST(Day9_P1)
{	
	int exampleResult = day9_p1("../src/Day9/day9.example");
	if(showResults){
		printf("Day9 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day9_p1("../src/Day9/day9.input");
		printf("Day9 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 15);
}
END_TEST

START_TEST(Day9_P2)

{	
	int exampleResult = day9_p2("../src/Day9/day9.example");
	if(showResults){
		printf("Day9 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day9_p2("../src/Day9/day9.input");
		printf("Day9 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 1134);
}
END_TEST

START_TEST(Day10_P1)
{	
	long long int exampleResult = day10_p1("../src/Day10/day10.example");
	if(showResults){
		printf("Day10 Part1 Example: %lld\n", exampleResult);
	
		long long int inputResult = day10_p1("../src/Day10/day10.input");
		printf("Day10 Part1 Input  : %lld\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 26397);
}
END_TEST

START_TEST(Day10_P2)

{	
	long long int exampleResult = day10_p2("../src/Day10/day10.example");
	if(showResults){
		printf("Day10 Part2 Example: %lld\n", exampleResult);
	
		long long int inputResult = day10_p2("../src/Day10/day10.input");
		printf("Day10 Part2 Input  : %lld\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 288957);
}
END_TEST

START_TEST(Day11_P1)
{	
	int exampleResult = day11_p1("../src/Day11/day11.example");
	if(showResults){
		printf("Day11 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day11_p1("../src/Day11/day11.input");
		printf("Day11 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 1656);
}
END_TEST

START_TEST(Day11_P2)
{	
	int exampleResult = day11_p2("../src/Day11/day11.example");
	if(showResults){
		printf("Day11 Part2 Example: %d\n", exampleResult);
	
		int inputResult = day11_p2("../src/Day11/day11.input");
		printf("Day11 Part2 Input  : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 195);
}
END_TEST

START_TEST(Day12_P1)
{	
	int exampleResult = day12_p1("../src/Day12/day12.example");
	int exampleResult2 = day12_p1("../src/Day12/day12.example2");
	int exampleResult3 = day12_p1("../src/Day12/day12.example3");
	if(showResults){
		printf("Day12 Part1 Example : %d\n", exampleResult);
		printf("Day12 Part1 Example2: %d\n", exampleResult2);
		printf("Day12 Part1 Example3: %d\n", exampleResult3);
	
		int inputResult = day12_p1("../src/Day12/day12.input");
		printf("Day12 Part1 Input   : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 10);
	ck_assert_int_eq(exampleResult2 , 19);
	ck_assert_int_eq(exampleResult3 , 226);
}
END_TEST

START_TEST(Day12_P2)
{	
	int exampleResult = day12_p2("../src/Day12/day12.example");
	int exampleResult2 = day12_p2("../src/Day12/day12.example2");
	int exampleResult3 = day12_p2("../src/Day12/day12.example3");
	if(showResults){
		printf("Day12 Part2 Example : %d\n", exampleResult);
		printf("Day12 Part2 Example2: %d\n", exampleResult2);
		printf("Day12 Part2 Example3: %d\n", exampleResult3);
	
		int inputResult = day12_p2("../src/Day12/day12.input");
		printf("Day12 Part2 Input   : %d\n", inputResult);
		printf("\n");
	}
	ck_assert_int_eq(exampleResult , 36);
	ck_assert_int_eq(exampleResult2 , 103);
	ck_assert_int_eq(exampleResult3 , 3509);

}
END_TEST

START_TEST(Day13_P1)
{	
	int exampleResult = day13_p1("../src/Day13/day13.example");
	if(showResults){
		printf("Day13 Part1 Example: %d\n", exampleResult);
	
		int inputResult = day13_p1("../src/Day13/day13.input");
		printf("Day13 Part1 Input  : %d\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 17);
}
END_TEST

START_TEST(Day13_P2)
{	
	if(showResults){
		printf("Day13 Part2 Example:\n");
		day13_p2("../src/Day13/day13.example");

		printf("\n");
		printf("Day13 Part2 Input  :\n");
		day13_p2("../src/Day13/day13.input");
		printf("\n");
	}

	//No assert because the solution is printed as letters in screen
	ck_assert_int_eq(0,0);
	//ck_assert_str_eq(exampleResult, "o");
}
END_TEST

START_TEST(Day14_P1)
{	
	long long int exampleResult = day14_p1("../src/Day14/day14.example");
	if(showResults){
		printf("Day14 Part1 Example: %lld\n", exampleResult);
	
		long long int inputResult = day14_p1("../src/Day14/day14.input");
		printf("Day14 Part1 Input  : %lld\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 1588);
}
END_TEST

START_TEST(Day14_P2)
{	
	long long int exampleResult = day14_p2("../src/Day14/day14.example");
	if(showResults){
		printf("Day14 Part2 Example: %lld\n", exampleResult);
	
		long long int inputResult = day14_p2("../src/Day14/day14.input");
		printf("Day14 Part2 Input  : %lld\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 2188189693529);
}
END_TEST

Suite* createAocTests(){
	Suite *s;
	TCase *tc;

	s = suite_create("Aoc2021");
	tc = tcase_create("Core");

	tcase_add_test(tc, Day1_P1);
	tcase_add_test(tc, Day1_P2);
	tcase_add_test(tc, Day2_P1);
	tcase_add_test(tc, Day2_P2);
	tcase_add_test(tc, Day3_P1);
	tcase_add_test(tc, Day3_P2);
	tcase_add_test(tc, Day4_P1);
	tcase_add_test(tc, Day4_P2);
	tcase_add_test(tc, Day5_P1);
	tcase_add_test(tc, Day5_P2);
	tcase_add_test(tc, Day6_P1);
	tcase_add_test(tc, Day6_P2);
	tcase_add_test(tc, Day7_P1);
	tcase_add_test(tc, Day7_P2);
	tcase_add_test(tc, Day8_P1);
	tcase_add_test(tc, Day8_P2);
	tcase_add_test(tc, Day9_P1);
	tcase_add_test(tc, Day9_P2);
	tcase_add_test(tc, Day10_P1);
	tcase_add_test(tc, Day10_P2);
	tcase_add_test(tc, Day11_P1);
	tcase_add_test(tc, Day11_P2);
	tcase_add_test(tc, Day12_P1);
	tcase_add_test(tc, Day12_P2);
	tcase_add_test(tc, Day13_P1);
	tcase_add_test(tc, Day13_P2);
	tcase_add_test(tc, Day14_P1);
	tcase_add_test(tc, Day14_P2);
	suite_add_tcase(s, tc);

	return s;
}

int main(int argc, char **argv){
	if(argc > 1 && strcmp(argv[1], "-sr")==0){
		showResults = true;		
	}else
		showResults = false;


	Suite *suite;
	SRunner *runner;
	int failed = 0;
	
	suite = createAocTests();
	runner = srunner_create(suite);

	srunner_run_all(runner, CK_NORMAL);
	failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return ((failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}

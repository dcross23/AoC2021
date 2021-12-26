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
	}
	ck_assert_int_eq(exampleResult , 5);
	printf("\n");
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
	}
	ck_assert_int_eq(exampleResult , 900);
	printf("\n");
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
	}
	ck_assert_int_eq(exampleResult , 230);
	printf("\n");
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
	}
	ck_assert_int_eq(exampleResult , 1924);
	printf("\n");
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
	}
	ck_assert_int_eq(exampleResult , 12);
	printf("\n");
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

START_TEST(Day6_P2)
{	
	long long int exampleResult = day6_p2("../src/Day6/day6.example");
	if(showResults){
		printf("Day6 Part2 Example: %lld\n", exampleResult);
	
		long long int inputResult = day6_p2("../src/Day6/day6.input");
		printf("Day6 Part2 Input  : %lld\n", inputResult);
	}
	ck_assert_int_eq(exampleResult , 26984457539);
	printf("\n");
}


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

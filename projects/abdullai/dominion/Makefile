CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: cleanall tests

tests: randomtestadventurer.c randomtestcard1.c dominion.c rngs.c test_utils.c
	gcc -o randomtestadventurer adventurer.c smithy.c village.c dominion.c rngs.c test_utils.c randomtestadventurer.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov adventurer.c >> randomtestadventurer.out -b

	gcc -o randomtestcard1 adventurer.c smithy.c village.c dominion.c rngs.c test_utils.c randomtestcard1.c $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov smithy.c >> randomtestcard1.out -b

	gcc -o randomtestcard2 adventurer.c smithy.c village.c dominion.c rngs.c test_utils.c randomtestcard2.c $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov village.c >> randomtestcard2.out -b

clean:
	rm -f randomtestadventurer.out randomtestcard1.out randomtestcard2.out

cleanall:
	rm -f randomtestadventurer.out randomtestadventurer randomtestcard1 randomtestcard1.out randomtestcard2 randomtestcard2.out *.gcda *.gcno *.gcov

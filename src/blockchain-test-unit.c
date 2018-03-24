/**
 *  BlockChain ADT: automated unit test driver
 *
 *  COMP220: Assignment 3
 *  Author:  Karan Nedunagdi
 *  Date:    Mar. 17, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "trnslist.h"
#include "puzzle.h"
#include "block.h"
#include "blockchain.h"

const int SET_DIFFICULTY = 2;    // Default difficulty for hashing puzzles, increase to make mining harder


/*
 * Run a single test case
 * Report on failed test
 * Return 0 if test successful, 1 otherwise
 */
int run_test(int result, int expected, char* msg) 
{
   if (result != expected)
   {
      printf("\nTest failed: %s \n\tFunction returned %d but expected %d\n", msg, result, expected);
      return(1);
   }
   return(0);
}


/*
 * Run a series of test cases.
 * Report on failed tests
 */
void main()
{
    int i;
    int failed_test_counter = 0;
    printf("Unit Test Suite for BlockChan ADT operations...\n");
    
    //Test 1: Constructor
    BlockChain chain = bcNew();
    printf("1");
    failed_test_counter += run_test(bcLen(chain), 0, "Constructor fails to create empty blockchain.");
    printf(".");
    
    //create a transaction list
    TransactionList t1 = tlistCreate();
    for(i=0; i<5; i++) {
        tlistAppend(&t1, "Joel", i+50, "Armia");
    }
    
    Block_t* block1 = blkCreate(t1, SET_DIFFICULTY, NULL_NONCE);
    Puzzle_t puzzle = blkCreatePuzzle(*block1, bcTail(chain)->hash);
    block1->proof_of_work = puzzleMine(puzzle);
    
    
    //Test2: Append blocks
    bcAppend(&chain, block1);
    printf("3");
    failed_test_counter != run_test(bcLen(chain), 1, "Failed to append block.");
    
    TransactionList t2 = tlistCreate();
    for(i=0; i<5; i++) {
        tlistAppend(&t2, "arab", i+50, "oil");
    }
    
    Block_t* block2 = blkCreate(t2, SET_DIFFICULTY, NULL_NONCE);
    Puzzle_t puzzle2 = blkCreatePuzzle(*block2, bcTail(chain)->hash);
    block2->proof_of_work = puzzleMine(puzzle2);
    
    bcAppend(&chain, block2);
    printf("4");
    failed_test_counter != run_test(bcLen(chain), 2, "Failed to append second block.");
    
    
    //Test5: Validate
    printf("5");
    bool valid = bcIsValid(chain);
    failed_test_counter += run_test(valid, true, "Blockchain does not validate with mined PoW");
    printf(".");
    
    
    //Test 5: Deustructor (white-box tests)
    printf("6");
    bcDelete(&chain);
    printf(".");
    
    printf("\n\nUnit Test Complete: ");
    if(failed_test_counter == 0) printf("ALL TESTS PASSED\n");
    else printf("FAILED %d TESTS\n", failed_test_counter);
}
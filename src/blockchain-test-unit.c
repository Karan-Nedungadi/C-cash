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
    
    TransactionList tl1 = tlistCreate();
    for(i=0; i<5; i++) {
        tlistAppend(&tl1, "Joe", (i+3)*2+99.0/(i+1), "Tim");
    }
    
    Block_t* block1 = blkCreate(tl1, SET_DIFFICULTY, NULL_NONCE);
    
    //Test 1: Constructor
    BlockChain chain = bcNew();
    printf("1");
    failed_test_counter += run_test(bcLen(chain), 0, "Constructor fails to create empty blockchain.");
    printf(".");
    
    //Test2: Append blocks
    for(i=0; i<10; i++) {
        bcAppend(&chain, block1);
    }
    
    //Test3: Validate
    printf("3");
    bool valid = bcIsValid(chain);
    failed_test_counter += run_test(valid, true, "Blockchain does not validate with mined PoW");
    printf(".");
}
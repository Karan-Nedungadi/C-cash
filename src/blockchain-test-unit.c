/**
 *  BlockChain ADT: automated unit test driver
 *
 *  COMP220: Assignment 3
 *  Author:  Karan Nedunagdi
 * Collaborated with: Robert Bell, Benjamin Hynes, Tim Wriglesworth
 *  Date: (start)  Mar. 17, 2018 , (end) Mar. 24, 2018
 * 
 * Develop a test driver! 
 * It does not have to be fancy – it could be interactive or automated or a mixture of both 
 * (like the linked list test driver from labs 5 & 6). 
 * Write some tests for every function you develop so that you can verify and debug each function independently.
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
    
    
    //Test2: Append one block
    printf("2");
    bcAppend(&chain, block1);
    failed_test_counter != run_test(bcLen(chain), 1, "Failed to append first block.");
    printf(".");
    
    //Test3: Append multiple blocks
    printf("3");
    TransactionList t2 = tlistCreate();
    for(i=0; i<5; i++) {
        tlistAppend(&t2, "arab", 2*i+33, "oil");
    }
    
    //making a second block with a new transaction list
    Block_t* block2 = blkCreate(t2, SET_DIFFICULTY, NULL_NONCE);
    Puzzle_t puzzle2 = blkCreatePuzzle(*block2, bcTail(chain)->hash);
    block2->proof_of_work = puzzleMine(puzzle2);
    
    
    bcAppend(&chain, block2);
    failed_test_counter != run_test(bcLen(chain), 2, "Failed to append second block.");
    
    
    TransactionList t3 = tlistCreate();
    for(i=0; i<5; i++) {
        tlistAppend(&t3, "Karan", 3*i+42, "Hope");
    }
    
    //making a third block with a new transaction list
    Block_t* block3 = blkCreate(t3, SET_DIFFICULTY, NULL_NONCE);
    Puzzle_t puzzle3 = blkCreatePuzzle(*block3, bcTail(chain)->hash);
    block3->proof_of_work = puzzleMine(puzzle3);
    
    bcAppend(&chain, block3);
    failed_test_counter != run_test(bcLen(chain), 3, "Failed to append second block.");
    printf(".");
    
    //Test4: Validate
    printf("4");
    bool valid = bcIsValid(chain);
    failed_test_counter += run_test(valid, true, "Blockchain does not validate with mined PoW");
    printf(".");
    
    
    //------------- WHITE-BOX TESTING -----------------
    //Test 5: Append:  try appending a non valid block
    printf("5");
    TransactionList t4 = tlistCreate();
    for(i=0; i<10; i++) {
        tlistAppend(&t4, "Logan", 30.00, "Paul");
    }
    
    TransactionList tscam = tlistCreate();
    for (i=0; i<5; i++) {
        tlistAppend(&tscam, "Scam", 30.00, "Scam");
    }
    
    Block_t* block4 = blkCreate(t4 , SET_DIFFICULTY, NULL_NONCE);
    Block_t* FalsifiedBlk = blkCreate(tscam , SET_DIFFICULTY, NULL_NONCE);
    
    Puzzle_t newPuzzle5 = blkCreatePuzzle(*block4, chain.tail->hash);
    Puzzle_t WrongPuzzle = blkCreatePuzzle(*FalsifiedBlk, chain.tail->hash);
    
    FalsifiedBlk->proof_of_work = puzzleMine(newPuzzle5);   // give the wrong proof of work (ie blk is not valid)
   
   bool blkvalid = blkValidates(*FalsifiedBlk, chain.tail->hash, FalsifiedBlk->proof_of_work);
   failed_test_counter += run_test(blkvalid, false, "Blockchain validates invalid block.");
   printf(".");
   
   //Test 6: Deustructor
    printf("6");
    bcDelete(&chain);
    printf(".");
   
   for(i=0; i<10; i++) {
       printf(".");
   }
   
   printf("\n\nUnit Test Complete: ");
   if(failed_test_counter == 0) printf("ALL TESTS PASSED\n");
   else printf("FAILED %d TESTS\n", failed_test_counter);
}
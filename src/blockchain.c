/**
 *  BlockChain ADT : private implementation / algorithms
 *
 *  COMP220: Assignment 3
 *  Author:  Karan Nedunagdi
 *  Date:    Feb. 1, 2018
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

/***********************
 * BLOCKCHAIN private implementation details
 ***********************/
const int DEFAULT_DIFFICULTY = 2;              // Default difficulty for hashing puzzles, increase to make mining harder

void bcPop(BlockChain* chain);
bool bcIsEmpty(BlockChain chain);
void blkPrint(Block_t blk);

/*
 * prints a block on STDOUT
 */
void blkPrint(Block_t blk) {
    printf("----------------- \n");
    printf("|\tBlock: # %d\t|\n", blk.id);
    printf("|\tNonce: %lu  \t|\n", blk.proof_of_work.i_nonce);
    tlistPrint(blk.transactions);
    printf("|\tPrev:  %s  \t|\n", blkPrevHash(blk));
    printf("|\tHash:  %s  \t|\n", blk.hash);
    printf("----------------- \n");
}

BlockChain bcNew() {
    Block_t* genesis = blkCreate(tlistCreate(), DEFAULT_DIFFICULTY, NULL_NONCE);
    BlockChain bc = {genesis, genesis};
}

void bcDelete(BlockChain *chain) {
    assert(bcLen(*chain) > 0);
    while(chain->head->next != NULL) {
        bcPop(chain);
    }
}

/*
 * Delete the block at the front of the list
 * PRE: make sure list is not empty
 */
void bcPop(BlockChain* chain) {
    assert(!bcIsEmpty(*chain));
    Block_t* blk = chain->head->next;
    chain->head->next = blk->next;
    blk->next->prev = chain->head;
    if(chain->tail == blk) {
        chain->tail = chain->head;
    }
    blkDelete(blk);
}

void bcPrint(const BlockChain chain) {
    Block_t*cur = chain.head->next;
    printf("\n BlockChain:\n");
    while(cur != NULL) {
        blkPrint(*cur);
        printf("\n");
        cur = cur->next;
    }
    printf("\n\n");
}

int bcLen(const BlockChain chain) {
    int len = 0;
    Block_t* cur = chain.head->next;
    while(cur != NULL) {
        cur = cur->next;
        len++;
    }
    return len;
}

bool bcIsValid(const BlockChain chain) {
    Block_t* cur = chain.head->next;
    while(cur != NULL) {
        if(blkIsValid(*cur))
            cur = cur->next;
            else {
                return false;
            }
    }
    return true;
}

Block_t* bcTail(const BlockChain chain) {
    return chain.tail;
}

/*
 * Checks if the chain is empty
 */
bool bcIsEmpty(BlockChain chain) {
    return chain.head->next == NULL;
}

void bcAppend(BlockChain *chain, Block_t* new_block) {
    assert(blkValidates(*new_block, bcTail(*chain)->hash, new_block->proof_of_work));
    if(bcIsEmpty(*chain)) {
        chain->head->next = chain->tail = new_block;
        new_block->prev = chain->head;
    }
    else {
        blkChainTo(bcTail(*chain), new_block);
    }
    assert(bcTail(*chain) == new_block && blkIsValid(*new_block));
}
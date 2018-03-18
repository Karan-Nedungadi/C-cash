all: tunit punit bunit bcunit

tunit: trnslist.h trnslist.c tlist-test-unit.c
	gcc trnslist.c tlist-test-unit.c -o tunit

punit: puzzle.h puzzle.c puzzle-test-unit.c
	gcc puzzle.c puzzle-test-unit.c sha1/sha1.c -o punit

bunit: puzzle.h puzzle.c trnslist.h trnslist.c block.h block.c block-test-unit.c
	gcc puzzle.c trnslist.c block.c block-test-unit.c sha1/sha1.c -o bunit

bcunit: puzzle.h puzzle.c trnslist.h trnslist.c block.h block.c blockchain.h blockchain.c blockchain-test-unit.c
	gcc puzzle.c trnslist.c block.c blockchain.c blockchain-test-unit.c sha1/sha1.c -o bcunit

clean:
	@rm -f *.o tunit punit bunit bcunit
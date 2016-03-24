#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct Row {
	int tag;
	int valid;
};

struct Set{
	int index;
	int num_rows;
	int eviction_row;
	struct Row *rows;
};

struct Cache {
	int size;
	int block_size;
	int ways;
	struct Set *sets;
};

struct Address {
	int index;
	int tag;
};


int numOfSets(struct Cache cache) {
	return cache.size / (cache.ways * cache.block_size);
}


struct Row new_row() {
	struct Row r;
	r.tag = 0;
	r.valid = 0;
	return r;
}


struct Set new_set(int index, int num_rows) {
	struct Set s;
	s.index = index;
	s.num_rows = num_rows;
	s.eviction_row = 0;
	s.rows = malloc(num_rows * sizeof(struct Row));
	int i = 0;
	for (; i < num_rows; i++) {
		s.rows[i] = new_row();
	}
	return s;
}

struct Cache new_cache(int size, int block_size, int ways) {
	struct Cache c;
	c.size = size;
	c.block_size = block_size;
	c.ways = ways;	
	c.sets = malloc(numOfSets(c) * sizeof(struct Set));
	int i = 0;
	for (; i < numOfSets(c); i++) {
		c.sets[i] = new_set(i, ways);
	}
	return c;
}

struct Address new_address(struct Cache cache, int addr) {
	struct Address a;
	a.tag = addr / (cache.size / cache.ways);
	a.index = addr / cache.block_size % numOfSets(cache);
	return a;
}


void simulation(struct Cache cache, struct Address address) {
	int i = 0, n = 0;
	for (; i < numOfSets(cache); i++) {
		if (cache.sets[i].index == address.index) {
			for (; n < cache.sets[i].num_rows; n++) {
				if (cache.sets[i].rows[n].tag == address.tag && cache.sets[i].rows[n].valid) {
					printf("HIT \n");
					return;
				}
				if (!cache.sets[i].rows[n].valid) {
					cache.sets[i].rows[n].tag = address.tag;
					cache.sets[i].rows[n].valid = 1;
					printf("MISS \n");
					return;
				}
			}
			cache.sets[i].rows[cache.sets[i].eviction_row].tag = address.tag;
			printf("MISS \n");
			cache.sets[i].eviction_row = (cache.sets[i].eviction_row + 1) % cache.sets[i].num_rows;
		}
	}
}



int main(int argc, char const *argv[]) {

	int arr[] = { 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52,
		56, 60, 64, 68, 72, 76, 80, 0, 4, 8, 12, 16, 71, 3,
		41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41 };
	int i = 0;

	// Assume a 128-byte, direct-mapped cache with 8-byte cache blocks
	printf("\nTEST 1\n");
	struct Cache test1 = new_cache(128, 8, 1);
	for (i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
		struct Address adr1 = new_address(test1, arr[i]);
		printf("Address: %d \t Tag: %d \t Index: %d \t", arr[i], adr1.tag, adr1.index);
		simulation(test1, adr1);
	}



	// Assume a 64-byte, 2-way set associative cache with 8-byte cache blocks
	printf("\nTEST 2\n");
	struct Cache test2 = new_cache(64, 8, 2);
	for (i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
		struct Address adr2 = new_address(test2, arr[i]);
		printf("Address: %d \t Tag: %d \t Index: %d \t", arr[i], adr2.tag, adr2.index);
		simulation(test2, adr2);
	}



	// Assume a 128-byte, direct-mapped cache with 16-byte cache blocks
	printf("\nTEST 3\n");
	struct Cache test3 = new_cache(128, 16, 1);
	for (i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
		struct Address adr3 = new_address(test3, arr[i]);
		printf("Address: %d \t Tag: %d \t Index: %d \t", arr[i], adr3.tag, adr3.index);
		simulation(test3, adr3);
	}



	// Assume a 64-byte, fully associative cache with 8-byte cache blocks
	printf("\nTEST 4\n");
	struct Cache test4 = new_cache(64, 8, 8);
	for (i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
		struct Address adr4 = new_address(test4, arr[i]);
		printf("Address: %d \t Tag: %d \t Index: %d \t", arr[i], adr4.tag, adr4.index);
		simulation(test4, adr4);
	}

	return 0;

}

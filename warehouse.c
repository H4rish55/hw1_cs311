#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>

#define UNUSED_STEP (-1)

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Please invoke as %s <order_file>\n", argv[0]);
        return 1;
    }
    if (!openOrder(argv[1])) return 1;

    int last_used[NUMSLOTS];
    for (int i = 0; i < NUMSLOTS; i++) {
		last_used[i] = UNUSED_STEP;
	}

    int step = 0;

    do {
        int pn  = nextPartNumber();
        int bin = pn / 10;
		/* Replace the following code with a better implementation */

        int hit_slot   = -1;
        int empty_slot = -1;

		// least used slots 
        int lu_slot = -1;
        int lu_time = INT_MAX;

        for (int i = 0; i < NUMSLOTS; i++) {
            int b = binInSlot(i);
            if (b == bin){
				hit_slot = i;
			} 
            if (b == -1 && empty_slot == -1){
				empty_slot = i;
			} 
            if (b != -1 && last_used[i] < lu_time) {
                lu_time = last_used[i];
                lu_slot = i;
            }
        }

        int use_slot;
        if (hit_slot != -1) {
            use_slot = hit_slot;
        } else {
            use_slot = (empty_slot != -1) ? empty_slot : lu_slot;
            assert(use_slot != -1);
            fetchBin(bin, use_slot);
        }

        last_used[use_slot] = step++;
		/* End of simple implementation */
    } while (fetchNextPart());

    closeOrder();
    return 0;
}
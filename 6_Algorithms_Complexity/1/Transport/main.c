#include <stdio.h>
#include <stdlib.h>

int compare(const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int discard(int* array, int* new_array, int length) {
    int t=-1;
    int max_dist = 0;
    for (int i=0; i<length; i++) {
        if (array[i] != array[i+1]) {
            max_dist++;
            new_array[++t] = array[i];
        }
    }
    return max_dist;
}

int main() {

    int NKDTs[4]; // NKDTs0] : number of cars | NKDTs0[1] : number of stations | NKDTs[2] : distance | NKDTs[3] : time
    for (int i=0; i<4; i++) {
        scanf("%d", &NKDTs[i]);
    }

    int cars[2][NKDTs[0]];
    for (int i=0; i<NKDTs[0]; i++) {
        scanf("%d", &cars[0][i]); // read price
        scanf("%d", &cars[1][i]); // read capacity
    }

    int distances[NKDTs[1]];
    int distances_nd[NKDTs[1]];
    for (int i=0; i<NKDTs[1]; i++) {
        scanf("%d", &distances[i]); // array of stations
    }

    int TCs[4];
    for (int i=0; i<4; i++) { // TCs[0] : Ts | TCs[1] : Cs | TCs[2] : Tf | TCs[3] : Cf
        scanf("%d", &TCs[i]);
    }

    qsort(distances, NKDTs[1], sizeof(int), compare); // sort distances of stations

    int max_dist;
    max_dist = discard(distances, distances_nd, NKDTs[1]); // discard duplicate distances

//    for (int i=0; i<NKDTs[0]; i++) {
//
//    }

}

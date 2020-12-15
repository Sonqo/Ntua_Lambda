#include <iostream>

#define COLUMNS 1500

using namespace std;

void merge(int* array, int* indices, int left, int border, int right) {

    int i, j, k;
    int p2 = right-border;
    int p1 = border-left+1;

    int TempL[p1];
    int TempIndicesL[p1];
    int TempR[p2];
    int TempIndicesR[p2];

    for (i=0; i<p1; i++) { // spit arrays to TempL(eft) and TempR(ight)
        TempL[i] = array[left+i];
        TempIndicesL[i] = indices[left+i];
    }
    for (i=0; i<p2; i++) {
        TempR[i] = array[border+i+1];
        TempIndicesR[i] = indices[border+i+1];
    }

    i = 0;
    j = 0;
    k = left;
    while (i<p1 && j<p2) {
        if (TempL[i] <= TempR[j]) {
            array[k] = TempL[i];
            indices[k++] = TempIndicesL[i++];
        }
        else {
            array[k] = TempR[j];
            indices[k++] = TempIndicesR[j++];
        }
    }

    while (i<p1) { // filling unsorted items
        array[k] = TempL[i];
        indices[k++] = TempIndicesL[i++];
    }
    while (j<p2) {
        array[k] = TempR[j];
        indices[k++] = TempIndicesR[j++];
    }
}

void merge_sort(int* array, int* indices, int left, int right) {

    if (left>=right) {
        return;
    }

    int border = left + (right-left)/2;

    merge_sort(array, indices, left, border);
    merge_sort(array, indices, border+1, right);

    merge(array, indices, left, border, right);
}

int ware2int (char input) {
    switch(input) {
        case 'A':
            return 1;
        case 'B':
            return 2;
        case 'C':
            return 3;
        default:
            return 0;
    }
}

int main() {

    auto *average = (int *) malloc(4* sizeof(int));
    auto *pointers = (int *) malloc(10 * sizeof(int));
    auto *buying_pointers = (int *) malloc(10* sizeof(int));

    auto **value = (int **) malloc(10 * sizeof(int *));
    auto **amount = (int **) malloc(10 * sizeof(int *));

    for (int i=1; i<10; i++) {
        pointers[i] = 0;
        buying_pointers[i] = 0;
        value[i] = (int *) malloc(COLUMNS * sizeof(int));
        amount[i] = (int *) malloc(COLUMNS * sizeof(int));
    }

    int NMs[2];
    for (int & NM : NMs) { // read N, M
        scanf("%d", &NM);
    }

    int curr_int;
    char curr[2];
    for (int i=0; i<NMs[1]; i++) { // read amount and values for each merchant
        scanf("%s", curr);
        curr_int = curr[0] - '0' - 1;
        scanf("%d", &amount[3*curr_int+ware2int(curr[1])][pointers[3*curr_int+ware2int(curr[1])]]);
        scanf("%d", &value[3*curr_int+ware2int(curr[1])][pointers[3*curr_int+ware2int(curr[1])]++]);
    }

    for (int i=1; i<10; i++) { // sort value of wares, keep amount indices intact
        merge_sort(value[i], amount[i], 0, pointers[i]-1);
    }

    for (int i=1; i<10; i++) {
        for (int j=0; j<pointers[i]; j++) {
            std::cout << amount[i][j] << " " << value[i][j] << " ";
        }
        std::cout << std::endl;
        if (i == 3) {
            std::cout << std::endl;
        }
    }

    int sum_v, min_a;
//    while ((count < NMs[0]) && (flag != 3)) {
        for (int i=0; i<3; i++) {
            sum_v = value[3*i+1][buying_pointers[3*i+1]] + value[3*i+2][buying_pointers[3*i+2]] + value[3*i+3][buying_pointers[3*i+3]];
            min_a = min({amount[3*i+1][buying_pointers[3*i+1]], amount[3*i+2][buying_pointers[3*i+2]], amount[3*i+3][buying_pointers[3*i+3]]});
            if (min_a == 0) {
                average[i] = -1;
            } else {
                average[i] = sum_v / min_a;
            }
            cout << average[i] << endl;
        }
//    }

    //TODO : which merchant has the minimum average
    //TODO : buying handling

    return 0;
}
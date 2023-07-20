#include <stdio.h>
#include <time.h>

typedef struct {
    int array[320][240];
} loadImg;

/*
Load greyscale pixel values into a 320x240 array of integers given a filename
*/
//7.1.k. The names of any pointer variables shall begin with the letter ‘p’. For example, p_led_reg

void loadImage(loadImg* img, const char* filename) { //Use of the keyword char shall be restricted to the declaration of and
                                                    //        operations concerning strings rule 5.2 barr-c
    int row;
    int  col;


    //Open file, return error if it cannot
    FILE* file = fopen(filename, "r");  //7.1.n. The names of any variables representing non-pointer handles for objects, e.g., 
                                        //file handles, shall begin with the letter ‘h’. For example, h_input_file
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }
    // Write pixel values to array
    for (row = 0; row < 320; row++) { //check rule 8.4 BARR-C
            // Descriptively-named constants prevent defects and aid readability.
        for (col = 0; col < 240; col++) {//is this a magic number rule 8.4 page 66?
            fscanf(file, "%d", &img->array[i][j]);
        }
    }
    fclose(file);
}

/*
Print array for testing purposes
*/
void printArray(loadImg* img) {
    int row;
    int col; //avoid commas per BARR-C 8.1
    for ( row= 0; row < 320; row++) {
        for (col = 0; col < 240; col++) {//is this a magic number rule 8.4 page 66?
            printf("%d ", img->array[i][j]);
        }
        printf("\n");
    }
}


/*
Perform SAD on two 16x16 blocks, B is the reference block and A is the current comparison block

(x,y) is the position of current block
(r,s) is the motion vector (displacement of current block A relative to reference block B)
*/

int SAD(int32_t A[16][16], int32_t B[16][16], int x, int y, int r, int s, int bestMatch){//assumed the arrays are 32 bit integers
    int diff = 0; //if fixed/known bit width int32_t
    int sad = 0; 
    int row;
    int col; //satement 8.1 naming 7.1
    for(row=0; row<16; row++){  //7.1.e No variable name shall be shorter than 3 characters, including loop counters
        for(col=0; col<16; col++){//is this a magic number rule 8.4 page 66?
            diff = A[x+i][y+j] - B[(x+r) + i][(y+s) + j];  //suggested optimization of local/temp varibles in loops
            if(diff < 0){
                diff -= diff;
            } else{
`                ;
            }
        sad += diff; 
        }
    }
    //printf("SAD: %d\n", sad);
    // Check if current SAD is better than the best match
    if(sad < bestMatch){
        bestMatch = sad;
    }
else{ //added empty else for each if statement according to BAAR-C rule 8.2
;
}
    return bestMatch; 
}

int main() {
    //ARM compiler does not like declaring a variable within a for loop so its done here
    int row;
    int col; 
    int x; //better naming if possible 3 char or more 7.1.e page 60
    int y; 
   int32_t blockA[16][16]; // current block for comparison
    int32_t blockB[16][16]; //reference block *currently static*
    int32_t bestMatch = 200; //Keeping track of lowest SAD is this a magic number rule 8.4 page 66?

    // Load reference frame
    loadImg reference;
    loadImage(&reference, "reference.txt");

    //Load forward frame 
    loadImg forward;
    loadImage(&forward, "forward.txt");

    // Clock to keep track of execution time
    clock_t start, end; 
    double execution_time; 
    start = clock(); 


    // Load reference block
    // I want to load the first 16x16 block of the reference array into a new one
    for(row = 0; row < 16; row++){
        for(col = 0; col < 16; col++){
            blockB[i][j] = reference.array[i][j];
        }
    }

    /*
    (320 - 16 = 304)
    (240 - 16 = 224)
    top left pixel is the reference pixel.
    These x,y loops loop through all possible x,y positions of the forward frame (block A)
    */

    for(x = 1; x < 304; x++){
        for(y = 1; y < 224; y++){

            // Load 16x16 block A from forward image
            for(0 = i; i < 16; i++){
                for(0 = j; j < 16; j++){
                    blockA[i][j] = forward.array[i][j];
                }
            }
        // Perform SAD current block
        // in this example with only one reference block the current position is the same as the motion vector
        bestMatch = SAD(blockA, blockB, x, y, x, y, bestMatch);

        }
    }

    // print lowest SAD value *add motion vector here*
    printf("Best Match: %d\n", bestMatch);

    // end and print execution time
    end = clock(); 
    execution_time = ((double) (end - start)) / CLOCKS_PER_SEC; //here double is casted is it possible to avoid if not comment on why is nessary according to 
                                                                //Barr- C
    printf("Execution Time: %f\n", execution_time);

    return 0;
}
//reference https://barrgroup.com/sites/default/files/barr_c_coding_standard_2018.pdf

#include <stdio.h>
#include <stdlib.h> // for malloc()
#include <string.h> // for (snprintf)
#include <time.h> // for time()
#include <unistd.h> // for fsync()

void writezeros(FILE* output, FILE* input, char* zerodata, size_t filesize) {	
	printf("Making a 1 GB file full of zeros...\n");
		
	time_t starttime = time(NULL);

	fread(zerodata, 1, filesize, input);
	fwrite(zerodata, 1, filesize, output);
	fflush(output);

	if (fsync(fileno(output)) != 0) {
		perror("fsync");
	}
	
	
		
	//time_t endtime = difftime(time(NULL), starttime);
	time_t endtime = time(NULL) - starttime;
	
	int wspeed = filesize / endtime / 1000 / 1000; // User's writing speed in MB/s

	printf("To write a 1 GB file full of zeros it took: %ld seconds\n", endtime);
	printf("Your writing speed is: %dMB/s", wspeed);	
}




int main(int argc, char *argv[]) {
    if (argc != 2) {
	    printf("USAGE: %s <disk-to-run-the-benchmark-on>", argv[0]);
	    return 0; // There isn't really an error so I am not going to indicate an error
    }

    size_t filesize = (size_t) 1000L * 1000L * 1000L;
    char *zerodata = malloc(filesize);
    char *outputfile = argv[1];
    char FinalPath[100];
    snprintf(FinalPath, sizeof(FinalPath), "%s/%s", outputfile, "zeroout.bin"); // File full of zeros
    
    FILE* pzero = fopen("/dev/zero", "r");
    //FILE* prand = fopen("/dev/random", "r");
    FILE* pout = fopen(FinalPath, "w");
    //FILE* poutrand = fopen(FinalPath, "")
    
    if (pzero == NULL) {
	    perror("Failed to open directory /dev/zero\n");
	    return 1;
    }

    if (pout == NULL) {
	    printf("Failed to open %s output file\n", FinalPath);
	    return 1;
    }
    
    else {
	    writezeros(pout, pzero, zerodata, filesize);
    }
    
    free(zerodata);
    remove(FinalPath);
    
    fclose(pzero);
    fclose(pout);

}

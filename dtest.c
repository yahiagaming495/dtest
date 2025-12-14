#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main (int argc, char *argv[]) {

    if (argc != 3) {
		printf("You must enter 2 arguments in this format: %s [FILE_GB's] [DISK]", argv[0]);
    }

    int usergb = atoi(argv[1]);

    char *disk = argv[2];
    strcat(disk, "output.bin");

	char *diskrand = argv[2];
	strcat(diskrand, "randout.bin");


    FILE* pzero = fopen("/dev/zero", "r");
    FILE* prand = fopen("/dev/random", "r");
    FILE* pout = fopen(disk, "w");    
	FILE* poutrand = fopen(diskrand, "w");


	if (pzero == NULL || prand == NULL || pout == NULL || poutrand == NULL) {
		perror("Error while opening files: ");
	}

    
    size_t datasize = usergb * 1000L * 1000L * 1000L;
    char* data = malloc(datasize);
    printf("Writing zeros to disk to check it's speed...\n");
    
    time_t starttime = time(NULL);
    
    fread(data, 1048576, 1048576, pzero);
    fwrite(data, 1048576, 1048576, pout); 
    
    time_t endtime = time(NULL) - starttime;

	int wspeed = datasize / endtime / 1000 / 1000;

    printf("\nTo write a %d GB file of zeros it took: %ld seconds\n", usergb, endtime);
    printf("Your writing speed is: %dMB/s\n\n", wspeed);



	printf("Writing random bytes to disk...\n\n");

	time_t starttimerand = time(NULL);

	fread(data, 1048576, 1048576, prand);
	fwrite(data, 1048576, 1048576, poutrand);

	time_t endtimerand = time(NULL) - starttimerand;

	int wspeedrand = datasize / endtimerand / 1000 / 1000;

	printf("To write a %d GB file of random bytes it took: %ld seconds\n", usergb, endtimerand);
	printf("Your writing speed is: %dMB/s\n", wspeedrand);

	remove(disk);
	remove(diskrand);
	    
    fclose(pzero);
    fclose(pout);
    fclose(prand);
    fclose(poutrand);
  

}

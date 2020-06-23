#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define N 1024


int main(int argc, char* argv[]){
    /*Variables declaration*/
    int original_code, copy_code, read_code, write_code;
    


    /*Checking whether number of arguments is proper*/
    if(argc != 3){
        printf("Program %s takes two command line args but %d were given!\n", argv[0], argc-1);
        exit(1);
    }
    else
        printf("Way of copying: content of %s -> %s\n", argv[1], argv[2]);


    /*Opening argv[1] i argv[2]*/
    if( 
        ( (original_code
 = open(argv[1], O_RDONLY)) == -1 )
            ||
        ( (copy_code = open(argv[2], O_RDWR | O_CREAT | O_APPEND, S_IRWXU)) == -1 )
    ){
        perror("OPENING FAIL!");
        exit(1);
    }
    else
        printf("Files %s and %s are opened properly! original_code=%d\tcopy_code=%d\n",
        argv[1], argv[2], original_code, copy_code);


    /*Reading content of file to N-sized buffer and writing to new file*/
    while(1){
        char buffer[N];
        read_code = read(original_code, buffer, N);  
        printf("read_code=%d\n", read_code);
        if(read_code==-1){ 
            perror("READING ERROR!"); 
            exit(1);
        }
        
        if(read_code==0){ 
            printf("End of file reached!\n");
            break;
        }
        else{ 
            write_code = write(copy_code, buffer, read_code); 
            printf("write_code=%d\n", write_code);
        }

        if(write_code==-1){ 
            perror("WRITING ERROR!\n"); 
            exit(1); 
        }
   }

    printf("Copying ended correctly!\n");
    return 0;
}

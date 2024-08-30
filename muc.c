#include <stdio.h>
#include <string.h>

//TODO helper class for allocating array for tokens
//TODO helper klass tokenizer = token_reader

int main(int argc, char *argv[]){
    if(argc != 2 ){
        printf("Wrong Usage.\n Correct usage is muc <input.mu>");
    }

    else{
        printf("Lexical analysis starting");
        token_reader(argv[1]);
    }

    return 0;
}

char** token_reader(char* filename){
    FILE* input = fopen(filename, 'r');
    if(input != NULL){
        char* buffer[50];
        int read;
        while (read = fgetc(input) != EOF)
        {
            
        }
        
        fclose(input);
    }

    else{
        printf("Could not open file");
        fclose(input);
    }
}
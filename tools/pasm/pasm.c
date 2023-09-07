#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int symbol_table[1000];

int current_address = 0;

void compile_code(FILE* file) {
    char line[100];
    char* token;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        strtok(line, "\n");
        
        token = strtok(line, " ");
        
        if (token == NULL) {
            continue;
        }
        
        // If is instruction add
        if (strcmp(token, "add") == 0) {
            // Getting operands and target adress
            int operand1, operand2, target;
            token = strtok(NULL, " ");
            operand1 = atoi(token);
            token = strtok(NULL, " ");
            operand2 = atoi(token);
            token = strtok(NULL, " ");
            target = atoi(token);
            
            symbol_table[target] = symbol_table[operand1] + symbol_table[operand2];
        }
        
        // If is instruction jmp
        else if (strcmp(token, "jmp") == 0) {
            // Getting target adress
            token = strtok(NULL, " ");
            current_address = atoi(token);
        }
        
        // If is instruction text
        else if (strcmp(token, "text") == 0) {
    
            token = strtok(NULL, "\"");
            printf("%s\n", token);
        }
        
        // If syntax error
        else {
            printf("Error: unknown instruction: %s\n", token);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: pasm <source_file>\n");
        return 1;
    }
    
    const char* input_filename = argv[1];
    FILE* input_file = fopen(input_filename, "r");
    
    if (input_file == NULL) {
        printf("Error opening file %s\n", input_filename);
        return 1;
    }
    
    compile_code(input_file);
    
    fclose(input_file);
    
    return 0;
}
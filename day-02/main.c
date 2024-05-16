#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

void part1(FILE *fp);
void part2(FILE *fp);

int number_of_digits (int number){
    int result = number;
    int counter = 0;

    while(result > 0){
        result = result / 10;
        counter ++;
    }

    return counter;
}

bool validate_set(char *game, int start, int end){
    char color = 0;
    int number = 0;
    bool result = true;

    for(int i = start; i < end; i++){
        if(isdigit(game[i])){
            number =  atoi(&game[i]);

            int padding = 1 + number_of_digits(number);
            color = game[i+padding];

            switch(color){
                case 'r':
                    result &= MAX_RED >= number;
                break;

                case 'g':
                    result &= MAX_GREEN >= number;
                break;

                case 'b':
                    result &= MAX_BLUE >= number;
                break;
            }

            printf("(%d) - %d - %c - result: %d\n", i, number, color, result);
        }
    }

    return result;
}

int calculate_min_set_power(char *game, int start, int end){
    char color = 0;
    int number = 0;

    int min_red = 0;
    int min_green = 0;
    int min_blue = 0;

    for(int i = start; i < end; i++){
        if(isdigit(game[i])){
            number =  atoi(&game[i]);

            int padding = 1 + number_of_digits(number);
            color = game[i+padding];

            printf("%d%c", number, color);
            printf(" ");

            switch(color){
                case 'r':
                    if(number > min_red){
                        min_red = number;
                    }
                break;

                case 'g':
                    if(number > min_green){
                        min_green = number;
                    }
                break;

                case 'b':
                    if(number > min_blue){
                        min_blue = number;
                    }
                break;
            }

        }
    };
    printf("\n");

    printf("%d %d %d", min_red, min_green, min_blue);

    printf("\n");
    int power =  min_red * min_green * min_blue;
    printf("power: %d", power);
    printf("\n");

    return power;
}

int main (int argc, char *argv[]) { 
    FILE *fp = fopen("./input.txt", "r");
    
    if(!fp){
        return 1;
    }

    // part1(fp);

    part2(fp);

    fclose(fp);
    return 0;
} 

void part1(FILE *fp){
    
    char line_buffer[MAX_LINE_LENGTH] = {0};
    int line_number = 1;

    int sum = 0;

    while(fgets(line_buffer, MAX_LINE_LENGTH, fp)){
        int line_length = strlen(line_buffer);
        bool is_game_possible = true;

        printf("%s", line_buffer);
        
        char * haystack = line_buffer;

        char needle = ':';
        haystack = strchr(haystack, needle);
        int start = haystack - line_buffer + 2;

        needle = ';';
        haystack = strchr(haystack, needle);
        int end = haystack - line_buffer;

        printf("Primeira Jogada: %d - %d \n", start, end);
        is_game_possible &= validate_set(line_buffer, start, end);
        haystack++;

        while((haystack = strchr(haystack, needle)) != NULL){

            int pos = haystack - line_buffer;
            printf(": %d  \n", pos);

            start = end;
            end = pos;

            printf("Jogada Seguinte: %d - %d \n", start, end);
            is_game_possible &= validate_set(line_buffer, start, end);

            haystack++;
        }

        start = end;
        end = line_length;

        printf("Jogada Final: %d - %d \n", start, end);
        is_game_possible &= validate_set(line_buffer, start, end);
        printf("is_game_possible: %d \n", is_game_possible);
        if(is_game_possible){
            
            sum+=line_number;
        }
        
        printf("===========\n");
        line_number++;
    }

    printf("Total: %d\n", sum);
}

void part2(FILE *fp){
   char line_buffer[MAX_LINE_LENGTH] = {0};
    int line_number = 1;

    int sum = 0;

    while(fgets(line_buffer, MAX_LINE_LENGTH, fp)){
        int line_length = strlen(line_buffer);

        char * haystack = line_buffer;

        char needle = ':';
        haystack = strchr(haystack, needle);

        int start = haystack - line_buffer + 2;
        int end = line_length - 1;

        int power = calculate_min_set_power(line_buffer, start, end);

        sum += power;
    }

    printf("Sum: %d", sum);
}
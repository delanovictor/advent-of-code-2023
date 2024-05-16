#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LINE_LENGTH 256
char *digits[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

void part1(FILE *fp);
void part2(FILE *fp);

int main(){
  FILE *fp = fopen("./input.txt", "r");
  
  if(!fp){
    printf("Error opening file");
    return 1;
  }

  part1(fp);
  part2(fp);

  fclose(fp);

  return 0;
}

void part1(FILE *fp){
  fseek(fp, 0, SEEK_END);

  int file_length = ftell(fp);
  char * buffer = malloc(file_length + 1);
  
  fseek(fp, 0, SEEK_SET);

  fread(buffer, 1, file_length, fp);

  buffer[file_length - 1] = '\0';

  int total_sum = 0;

  int first_digit = 0;
  int first_digit_found = 0;

  int last_digit = 0;

  for(int i = 0; i < file_length; i++){
    if(!first_digit_found && buffer[i] > 46 && buffer[i] < 58){
      first_digit = buffer[i] - 48;
      // printf("\nfirst_digit_found: %d\n", first_digit);
      first_digit_found = 1;
    }

    if(buffer[i] > 47 && buffer[i] < 58){
      last_digit =  buffer[i] - 48;
      // printf("\nlast_digit_found: %d\n", last_digit);
    }

    if(buffer[i] == '\n' || buffer[i] == '\0'){
      int line_sum = (first_digit * 10) + last_digit;
      printf("  --  Line Sum: %d\n", line_sum);

      total_sum += line_sum;

      last_digit = 0;
      
      first_digit = 0;
      first_digit_found = 0;
    }

  }

  // printf("%d\n", file_length);
  // printf("%s\n", buffer);
  printf("\nTotal Sum: %d\n", total_sum);
}


int match_string_digit(char* str, int start){
  int length = strlen(str);
  int end = start + 6;

  for(int i = 0; i < 10; i ++){
    int is_equal = 1;
    // printf("\n\n");
    for(int j = start, k = 0; j < end; j++, k++){
      if(digits[i][k] == '\0'){
        break;
      }
      is_equal &= str[j] == digits[i][k];
      // printf("%c == %c\n",str[j], digits[i][k]);
    }

    if(is_equal){
      return i;
    }
  }
  
  return -1;
}

int find_first_string_digit(char* line, int end){
  int size = strlen(line);
  int min_index = size;
  
  for(int i = 0; i < 10; i++){
    char *digit = digits[i];
    // printf("%s\n", digit);
    // printf("%s\n", line);
    char *pos = line;

    while((pos = strstr(pos, digit)) != NULL){
      int index =  pos - line;

      // printf("%d!\n", index);
      // printf("Achou!\n");
      
      pos += strlen(digit);

      if(min_index > index && end >= index){
        min_index = index;
      }
    }

  }
  
  if(size == min_index){
    return -1;
  }

  return match_string_digit(line, min_index);
}

int find_last_string_digit(char* line, int start){
  int size = strlen(line);
  int max_index = -1;

  for(int i = 0; i < 10; i++){
    char *digit = digits[i];
    // printf("%s\n", digit);
    // printf("%s\n", line);
    char *pos = line;

    while((pos = strstr(pos, digit)) != NULL){
      int index =  pos - line;

      // printf("%d!\n", index);
      // printf("Achou!\n");
      
      pos += strlen(digit);

      if(index > max_index && index >= start){
        max_index = index;
      }
    }
  }
  
  if(max_index == -1){
    return -1;
  }

  return match_string_digit(line, max_index);
}

void part2(FILE *fp){

  char line_buffer[MAX_LINE_LENGTH] = {};

  int total_sum = 0;



  while(fgets(line_buffer, MAX_LINE_LENGTH, fp)){
    int first_numerical_digit_found = 0;
    int first_numerical_digit = 0;
    int first_numerical_digit_index = 0;

    int last_numerical_digit = 0;
    int last_numerical_digit_index = 0;

    int first_string_digit = 0;
    int last_string_digit = 0;
    
    int first_digit = 0;
    int last_digit = 0;

    int i = 0;
    printf("\n\n%s\n", line_buffer);
    
    while(line_buffer[i] != '\0'){
      if(!first_numerical_digit_found && line_buffer[i] > 46 && line_buffer[i] < 58){
        first_numerical_digit = line_buffer[i] - 48;
        first_numerical_digit_found = 1;
        first_numerical_digit_index = i;
      }

      if(line_buffer[i] > 47 && line_buffer[i] < 58){
        last_numerical_digit =  line_buffer[i] - 48;
        last_numerical_digit_index = i;
      }
      i++;
    }

    printf("first_numerical_digit - %d (%d)\n", first_numerical_digit, first_numerical_digit_index);
    printf("last_numerical_digit - %d (%d)\n", last_numerical_digit, last_numerical_digit_index);

    first_string_digit = find_first_string_digit(line_buffer, first_numerical_digit_index);

    // if(first_numerical_digit_index == last_numerical_digit_index){
    //   last_string_digit = find_last_string_digit(line_buffer, MAX_LINE_LENGTH);
    // }else{
    last_string_digit = find_last_string_digit(line_buffer, last_numerical_digit_index);
    // }

    printf("first_string_digit - %d\n", first_string_digit);
    printf("last_string_digit - %d\n", last_string_digit);

    first_digit = first_string_digit == -1 ? first_numerical_digit : first_string_digit;
    last_digit = last_string_digit == -1 ? last_numerical_digit : last_string_digit;

    int line_sum  =(10 * first_digit) + last_digit;

    printf("line sum - %d\n", line_sum);

    total_sum += line_sum;
    
    // printf("%s", line_buffer);

    // printf("first_digit - %d\n", first_digit);
    // printf("last_digit - %d\n", last_digit);
    // printf("\n");
  }

  printf("total_sum - %d\n", total_sum);
}
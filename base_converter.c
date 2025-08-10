// version 3.3
// This version supports arbitary argument sequence
// And supports argument like 10 without "-" when casting a base
// Comprehensive - to bo completed
// Still going to change to multi-files
#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MODE_NUM 3
#define MAX_STR_LEN

enum MODE { 
    SIMPLIFIED,
    COMPREHENSIVE
};

struct command {
    int input_mode;
    int output_mode;
    int mode[MODE_NUM];
    long long int target;
    char ori_str[MAX_STR_LEN];
};

void print_usage(void);

struct command *new_cmd(void);

void handle_input(char *argv[], int argc, struct command *cmd);

int judge_input_method(char s[]);

void calculate(struct command *cmd);

void print_in_given_base(struct command *cmd);

char* get_in_given_base(struct command *cmd);

char digit2alpabet(int d);

int cal_len(int tar, int base);

void print_comprehensive(struct command *cmd);


int main(int argc, char *argv[]) {
    if (argc <= 1 || argc > 5) {
        print_usage();
        return 0;
    }
    struct command *cmd = new_cmd();
    if (argc >= 3) {
        handle_input(argv, argc, cmd);
    }
    strcpy(cmd->ori_str, argv[argc - 1]);
    if (cmd->input_mode == -1) {
        cmd->input_mode = judge_input_method(cmd->ori_str);
    }

    if (cmd->output_mode <= 1 && cmd->output_mode != -1) {
        printf("invalid output mode: %d\n", cmd->output_mode);
        return 1;
    }

    calculate(cmd);
    free(cmd);
    return 0;
}

int alphabet2digit(char c) {
    if (c <= '9' && c >= '0') {
        return c - '0';
    } else if (c <= 'z' && c >= 'a') {
        return c - 'a' + 10;
    } else if (c <= 'Z' && c >= 'A') {
        return c - 'A' + 10;
    } else {
        printf("recieved letter: %d\n", c);
        fprintf(stderr, "invalid input, cast by a2d\n");
        exit(EXIT_FAILURE);
    }
}

int judge_input_method(char s[]) {
    int len = strlen(s);
    if (s[0] == '0') {
        if (s[1] == 'b') {
            return 2;
        } else if (s[1] == 'o') {
            return 8;
        } else if (s[1] == 'd') {
            return 10;
        } else if (s[1] == 'x') {
            return 16;
        }
    }
    int base = 2;
    int max = -1;
    for (int i = 0; i < len; i++) {
        max = max > alphabet2digit(s[i]) ? max : alphabet2digit(s[i]);
    }
    if (max < 2) {
        return 2;
    } else if (max < 10) {
        return 10;
    } else if (max < 16) {
        return 16;
    } else {
        return max;
    }
}

int judge_mode(char m) {
    if (m == 'b') {
        return 2;
    } else if (m == 'o') {
        return 8;
    } else if (m == 'd') {
        return 10;
    } else if (m == 'h') {
        return 16;
    }
    return -1;
}

int is_base(char *string) {
    return 0;
}

int base2digit(char *string) {
    if (string[0] <= '9' && string[0] >= '0') {
        return atoi(string);
    }
    if (string[0] == '-') {
        if (string[1] <= '9' && string[1] >= '0') {
            return -atoi(string);
        } else if (string[1] == 'b') {
            return 2;
        } else if (string[1] == 'o') {
            return 8;
        } else if (string[1] == 'd') {
            return 10;
        } else if (string[1] == 'h') {
            return 16;
        }
    }
    return 0;
}

void handle_input(char *argv[], int argc, struct command *cmd) {
    // a counter to decide input or output
    int base_count = 0;
    int base[2] = {-1, -1};
    for (int i = 1; i < argc - 1;i++) {
        if (base2digit(argv[i])) {
            base[base_count] = base2digit(argv[i]);
            base_count++;
            if (base_count > 2) {
                printf("Too many base arguments\n");
                printf("The third base recieved: %s", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-s") == 0) {
            cmd->mode[SIMPLIFIED] = 1;
        } else if (strcmp(argv[i], "-c") == 0) {
            cmd->mode[COMPREHENSIVE] = 1;            
        }
    }
    if (base_count == 2) {
        cmd->input_mode = base[0];
        cmd->output_mode = base[1];
    } else if (base_count == 1) {
        cmd->output_mode = base[0];
    }
}

struct command *new_cmd(void) {
    struct command *cmd = malloc(sizeof(struct command));
    cmd->input_mode = -1;
    cmd->output_mode = -1;
    for (int i = 0; i < MODE_NUM; i++) {
        cmd->mode[i] = 0;
    }
    return cmd;
}

void calculate(struct command *cmd) {

    if (cmd->mode[SIMPLIFIED] != 1) {

        printf("converting %s in base %d to ", cmd->ori_str, cmd->input_mode);

        if (cmd->output_mode != -1) {
            printf("base %d\n", cmd->output_mode);
        } else {
            printf("unspecified base\n");
        }
    }

    if (cmd->ori_str[0] == '0') {
        if (strchr("bdox", cmd->ori_str[1]) == NULL) {
            printf("Warning: unknown type start with 0, negelect first two chars\n");
        }
    }

    if (strlen(cmd->ori_str) <= 2) {
        cmd->target = atoi(cmd->ori_str);
    }

    int len = strlen(cmd->ori_str);
    int first_digit = 0;
    if (cmd->ori_str[0] == '0') {
        first_digit = 2;
    }
    //printf("first digit:%d : %c\n", first_digit, cmd->ori_str[first_digit]);
    //printf("string:%swith length %ld\n", cmd->ori_str, strlen(cmd->ori_str));
    for (int i = 0;i < strlen(cmd->ori_str);i++) {
        //printf("%dth c:%c(%d)\n", i, cmd->ori_str[i], cmd->ori_str[i]);
    }
    int mul = 1;
    int sum = 0;
    for (int i = len - 1; i >= first_digit;i--) {
        //printf("c: %c", cmd->ori_str[i]);
        if (isprint(cmd->ori_str[i])) {

            int digit = alphabet2digit(cmd->ori_str[i]);
            //printf("%d\n", digit);
            if (digit > cmd->input_mode - 1) {
                fprintf(stderr, "incompatible input, digit %d exist in base %d\n", digit, cmd->input_mode);
                exit(EXIT_FAILURE);
            }
            sum += mul * digit;
            mul *= cmd->input_mode;

        } else {
            printf("Be careful, some none printable ascii got\n");
        }

    }
    cmd->target = sum;
    // assume ans is now in deimal
    if (cmd->mode[SIMPLIFIED]) {
        char *str = get_in_given_base(cmd);
        printf("%s\n", str);
        free(str);
    } else {
        printf("in base (10), the number is %d\n", sum);
        if (cmd->output_mode != -1) {
            print_in_given_base(cmd);
        }
    }
    if (cmd->mode[COMPREHENSIVE]) {
        print_comprehensive(cmd);
    }
    
}

char *get_in_given_base(struct command *cmd) {
    if (cmd->output_mode == -1) {
        cmd->output_mode = 10;
    }

    int tar = cmd->target;
    int base = cmd->output_mode;
    int len = cal_len(tar, base);
    char *str = malloc(len + 1);
    str[len] = '\0';
    for (int i = len - 1; i >= 0; i--) {
        str[i] = digit2alpabet(tar % base);
        tar = tar / base;
    }
    return str;
}

void print_in_given_base(struct command *cmd) {


    char *str = get_in_given_base(cmd);
    int base = cmd->output_mode;

    printf("in base (%d), the number is %s\n", base, str);
    free(str);
    return;
}

char digit2alpabet(int d) {
    if (d <= 9 && d >= 0) {
        return d + '0';
    } else if (d <= 36 && d >= 10) {
        return d + 'A' - 10;
    } else {
        perror("invalid input, cast by d2a");
        exit(EXIT_FAILURE);
    }
}

int cal_len(int tar, int base) {
    int ans = 1;
    while (tar >= base) {
        tar = tar / base;
        ans++;
    }
    return ans;
}


void print_comprehensive(struct command *cmd) {

    printf("TO be continued\n");

}

void print_usage(void) {
    printf("Usage: ./base_converter (-input base) (-output base) (-<command>) "
           "<number>\n");
    printf("<base for choosing>\n");
    printf("b - binary\n");
    printf("d/o - decimal/octal\n");
    printf("h - hexadecimal\n");
    printf("d - any integer\n");
    printf("<mode>\n");
    printf("s - simplified\n");
    printf("c - comprehensive\n");
}

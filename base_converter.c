#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MODE_NUM 3
#define MAX_STR_LEN

enum MODE { SIMPLIFIED };

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

char digit2alpabet(int d);

int cal_len(int tar, int base);


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

    calculate(cmd);
    free(cmd);
    return 1;
}

int alphabet2digit(char c) {
    if (c <= '9' && c >= '0') {
        return c - '0';
    } else if (c <= 'z' && c >= 'a') {
        return c - 'a' + 10;
    } else if (c <= 'Z' && c >= 'A') {
        return c - 'A' + 10;
    } else {
        perror("invalid input, cast by a2d");
        exit(EXIT_FAILURE);
    }
}

int judge_input_method(char s[]) {
    int len = strlen(s);
    if (s[0] == '0') {
        if (s[1] == 'b') {
            return 2;
        } else if (s[1] == 'd' || s[1] == 'o') {
            return 10;
        } else if (s[1] == 'h') {
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
    } else if (m == 'd' || m == 'o') {
        return 10;
    } else if (m == 'h') {
        return 16;
    }
    return -1;
}

void handle_input(char *argv[], int argc, struct command *cmd) {
    // a counter to decide input or output
    int base_count = 0;
    
    for (int i = 1; i < argc - 1; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] <= '9' && argv[i][1] >= '0') {
                if (base_count == 0) {
                    cmd->input_mode = -atoi(argv[i]);
                } else if (base_count == 1) {
                    cmd->output_mode = -atoi(argv[i]);
                }
                base_count++;
            }
        }
        if (strlen(argv[i]) == 2 && strstr("-b-d-o-h",argv[i]) != NULL) {
            if (base_count == 0) {
                cmd->input_mode = judge_mode(argv[i][1]);
            } else if (base_count == 1) {
                cmd->output_mode = judge_mode(argv[i][1]);
            }
            
            base_count++;
        }

    }
}

struct command *new_cmd(void) {
    struct command *cmd = malloc(sizeof(struct command));
    cmd->input_mode = -1;
    cmd->output_mode = -1;
    for (int i = 0; i < MODE_NUM; i++) {
        cmd->mode[i] = -1;
    }
    return cmd;
}

void calculate(struct command *cmd) {
    printf("converting %s in base %d to ", cmd->ori_str, cmd->input_mode);
    if (cmd->output_mode != -1) {
        printf("base %d", cmd->output_mode);
    } else {
        printf("unspecified base");
    }

    if (cmd->mode[SIMPLIFIED] == 1) {
        printf("(Simplified)");
    }
    printf("\n");

    if (strlen(cmd->ori_str) <= 2) {
        cmd->target = atoi(cmd->ori_str);
    }

    int len = strlen(cmd->ori_str);
    int first_digit = 0;
    if (cmd->ori_str[0] == '0') {
        first_digit = 2;
    }
    int mul = 1;
    int sum = 0;
    for (int i = len - 1; i >= first_digit; i--) {
        int digit = alphabet2digit(cmd->ori_str[i]);
        if (digit > cmd->input_mode - 1) {
            perror("incompatible input");
        }
        sum += mul * digit;
        mul *= cmd->input_mode;
    }

    // assume ans is now in deimal
    cmd->target = sum;
    printf("in base (10), the number is %d\n", sum);
    print_in_given_base(cmd);
}

void print_in_given_base(struct command *cmd) {
    int tar = cmd->target;
    int base = cmd->output_mode;
    int len = cal_len(tar, base);
    char *str = malloc(len + 1);
    str[len] = '\0';
    for (int i = len - 1; i >= 0; i--) {
        str[i] = digit2alpabet(tar % base);
        tar = tar / base;
    }
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
    while (tar > base) {
        tar = tar / base;
        ans++;
    }
    return ans;
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
}


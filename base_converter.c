
// version 3.1

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
        } else if (s[1] == 'd' || s[1] == 'o') {
            return 10;
        } else if (s[1] == 'x' || s[1] == 'h') {

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
    while (tar >= base) {
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

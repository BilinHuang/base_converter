#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define MODE_NUM 3
#define MAX_STR_LEN

struct command {
    int input_mode;
	int output_mode;
	int mode[MODE_NUM];
	long long int target;
	char ori_str[MAX_STR_LEN];
};

enum MODE
{
	SIMPLIFIED
};


void print_usage(void) {
	printf("Usage: ./base_converter (-input base) (-output base) (-<command>) -<number>\n");
	printf("<base for choosing>\n");
	printf("b - binary\n");
	printf("d/o - decimal/octal\n");
	printf("h - hexadecimal\n");
	printf("d - any integer\n");
	printf("<mode>\n");
	printf("s - simplified\n");
}

struct command *new_cmd(void) {
	struct command *cmd = malloc(sizeof(struct command));
	cmd->input_mode = -1;
	cmd->output_mode = -1;
	for (int i = 0;i < MODE_NUM;i++) {
		cmd->mode[i] = -1;
	}
	return cmd;
}

void calculate(struct command *cmd);

void handle_input(char *i, struct command *cmd) {
	if (strcmp(i, "-b") == 0) {
		cmd->input_mode = 2;
	} else if (strcmp(i, "-d") * strcmp(i, "-o") == 0) {
		cmd->input_mode = 10;
	} else if (strcmp(i, "-h") == 0) {
		cmd->input_mode = 16;
	} else if (i[0] == '-') {
		cmd->input_mode = -atoi(i);
		printf("%d\n", cmd->input_mode);
	}
}


void handle_complex(char *i, struct command *cmd) {

	if (strcmp(i, "-b") == 0) {
		cmd->output_mode = 2;
	} else if (strcmp(i, "-d") * strcmp(i, "-o") == 0) {
		cmd->output_mode = 10;
	} else if (strcmp(i, "-h") == 0) {
		cmd->output_mode = 16;
	} else if (i[0] == '-') {
		cmd->output_mode = -atoi(i);
	} else if (strcmp(i, "-s") == 0) {
		cmd->mode[SIMPLIFIED] = 1;
	}

}


void handle_output(char *i, struct command *cmd) {
	if (strcmp(i, "-s") == 0) {
		cmd->mode[SIMPLIFIED] = 1;
	}

}

int cal_num(char *strnum, struct command *cmd) {
	if (strlen(strnum) <= 2) {
		printf("%s:%lu\n", strnum, strlen(strnum));
		return atoi(strnum);
	} else if (strnum[0] == '0') {
		if (strnum[1] == 'b') {
			printf("in base(2)\n");
			strnum += 2;
			int value_d = (int)strtol(strnum, NULL, 2);
			printf("input mode: %d\n", cmd->input_mode);
			if (cmd->input_mode != -1 && cmd->input_mode != 2) {
				printf("invalid input num type (0b) conflicts with input type\n");
				exit(EXIT_FAILURE);
			}
			cmd->input_mode = 2;
			return value_d;
		}
		if (strnum[1] == 'x') {
			printf("in base(16)\n");
			strnum += 2;
			int value_d = (int)strtol(strnum, NULL, 16);
			printf("target from cal_num:%d\n", value_d);
			if (cmd->input_mode != -1 && cmd->input_mode != 16) {
				printf("invalid input num type (0x) conflicts with input type\n");
				exit(EXIT_FAILURE);
			}
			cmd->input_mode = 16;
			return value_d;
		}
	}
	return atoi(strnum);
}

int main(int argc, char *argv[]) {
	printf("%s\n", argv[argc - 1]);
	if (argc <= 1 || argc > 5) {
		print_usage();
		return 0;
	}

	struct command *cmd = new_cmd();
	if (argc >= 3) {
		handle_input(argv[1], cmd);
	}
	if (argc >= 4) {
		handle_complex(argv[2],cmd);
	}
	if (argc == 5) {
		handle_output(argv[3], cmd);
	}
	strcpy(cmd->ori_str, argv[argc - 1]);
	cmd->target = cal_num(argv[argc - 1], cmd);
	calculate(cmd);
	free(cmd);
	return 1;
	
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


	// TODO: transfer cmd->target in base cmd->input_mode to 10



	// assume ans is now in deimal
	int ans = cmd->target;
	printf("(10)%d\n", ans);



}



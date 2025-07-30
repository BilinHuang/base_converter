#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "base_adt.c"




struct command *new_cmd(void) {
	struct command *cmd = malloc(sizeof(struct command));
	cmd->input_base = -1;
	cmd->output_base = -1;
	for (int i = 0;i < MODE_NUM;i++) {
		cmd->mode[i] = -1;
	}
	return cmd;
}


struct command *build_cmd(int argc, char *argv[]) {
    printf("debugging info from build_cmd:\n");
    printf("ori string: %s\n", argv[argc - 1]);
	if (argc <= 1 || argc > 5) {
		print_usage();
		exit(EXIT_FAILURE);
	}
    struct command *cmd = new_cmd();

    return cmd;
}


void print_ans(struct command *cmd) {

	printf("converting %s in base %d to ", cmd->ori_str, cmd->input_base);
	if (cmd->output_base != -1) {
		printf("base %d", cmd->output_base);
	} else {
		printf("unspecified base");
	}
	if (cmd->mode[SIMPLIFIED] == 1) {
		printf("(Simplified)");
	}
	printf("\n");

}


int main(int argc, char *argv[]) {
	struct command *cmd = build_cmd(argc, argv);

	calculate(cmd);
	
    print_ans(cmd);

    free(cmd);
    return 1;
}
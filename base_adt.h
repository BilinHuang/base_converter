#define MODE_NUM 3
#define MAX_STR_LEN

struct command {
    int input_base;
	int output_base;
	int mode[MODE_NUM];
    long long int target;
	char ori_str[MAX_STR_LEN];
};

enum MODE
{
	SIMPLIFIED
};

void print_usage(void);

void calculate(struct command *cmd) {
    
}
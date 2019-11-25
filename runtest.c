#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include <omp.h>

int testcaseNum;

typedef struct testcase{
	int number;
	int fullScore;
	char file[100];
	char name[64];
} Testcase;

int run_test_nil(Testcase test) {
	printf("Running %s:\n", test.name);
	//printf("KERNEL_SPACE_SIZE=%d\nVIRTUAL_SPACE_SIZE=%d\nPAGE_SIZE=%d\nMAX_PROCESS_NUM=%d\n", KERNEL_SPACE_SIZE, VIRTUAL_SPACE_SIZE, PAGE_SIZE, MAX_PROCESS_NUM);
	FILE * file = fopen(test.file, "r");
	if(file == NULL){
		printf("cannot open %s\n", test.file);
		return -1;
	}
	char var[256];
	fscanf(file, "%s %d", var, &KERNEL_SPACE_SIZE);
	fscanf(file, "%s %d", var, &VIRTUAL_SPACE_SIZE);
	fscanf(file, "%s %d", var, &PAGE_SIZE);
	fscanf(file, "%s %d", var, &MAX_PROCESS_NUM);

	int score = 0;
	struct Kernel * kernel = init_kernel();
	char * buf = (char *)malloc(128);
	char * temp_buf = (char *)malloc(512);
	char * write_buf = (char *)malloc(512);
	char action[64];
	for(int i = 0; i < test.number; i++){
		fscanf(file, "%s", action);
		if(strcmp(action, "create") == 0){
			int memory, answer;
			fscanf(file, "%d %d", &memory, &answer);
			int pid = proc_create_vm(kernel, memory);
			if(pid == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}

		}else if(strcmp(action, "read") == 0){
			int pid , addr, size, bufSize, answer;
			fscanf(file, "%d %d %d %d %s %d", &pid, &addr, &size, &bufSize, write_buf, &answer);
			memset(temp_buf, 0, bufSize);
			int read = vm_read(kernel, pid, (char *)addr, size, temp_buf);
			if(strcmp(write_buf, "nil")!=0){
				if(read == answer){
					if(strcmp(write_buf, temp_buf) == 0){
						score += 1;
					}
				}
			}else{
				if(read == answer){
					score += 1;
				}
			}
			temp_buf[0] = '\0';
			write_buf[0] = '\0';
		}else if(strcmp(action, "write") == 0){

			int pid ,addr, size, bufSize, answer;
			memset(temp_buf, 0, bufSize);
			memset(write_buf, 0, bufSize);
			fscanf(file, "%d %d %d %d %s %d", &pid, &addr, &size, &bufSize, write_buf , &answer);
			int write;
			if(strcmp(write_buf, "nil")!=0){
				write = vm_write(kernel, pid, (char *)addr, size, write_buf);
			}else{
				write = vm_write(kernel, pid, (char *)addr, size, temp_buf);
			}
			if(write == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
			temp_buf[0] = '\0';
			write_buf[0] = '\0';
		}else if(strcmp(action, "exit") == 0){
			int pid, answer;
			fscanf(file, "%d %d", &pid, &answer);
			int exit = proc_exit_vm(kernel, pid);
			if(exit == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
		}else if(strcmp(action, "check") == 0){
			//print_kernel_free_space(kernel);
			char str_buf[128], ch;
			fscanf(file, "%s", str_buf);
			while((ch = getc(file))!= '#')
				strncat(str_buf, &ch, 1);
			strncat(str_buf,"\n", 1);
			get_kernel_free_space_info(kernel, buf);

			if(strcmp(buf, str_buf) == 0){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
		}
	}
	printf("Full Score: %d, Your Score: %d\n", test.fullScore ,score);
	return score;
}

void run_test_full(Testcase test, int someInt) {
	printf("Running %s:\n", test.name);
	//printf("KERNEL_SPACE_SIZE=%d\nVIRTUAL_SPACE_SIZE=%d\nPAGE_SIZE=%d\nMAX_PROCESS_NUM=%d\n", KERNEL_SPACE_SIZE, VIRTUAL_SPACE_SIZE, PAGE_SIZE, MAX_PROCESS_NUM);
	FILE * file = fopen(test.file, "r");
	if(file == NULL){
		printf("cannot open %s\n", test.file);
		return -1;
	}
	char var[256];
	fscanf(file, "%s %d", var, &KERNEL_SPACE_SIZE);
	fscanf(file, "%s %d", var, &VIRTUAL_SPACE_SIZE);
	fscanf(file, "%s %d", var, &PAGE_SIZE);
	fscanf(file, "%s %d", var, &MAX_PROCESS_NUM);

	int score = 0, prev = 0;
	struct Kernel * kernel = init_kernel();
	char * buf = (char *)malloc(128);
	char * temp_buf = (char *)malloc(512);
	char * write_buf = (char *)malloc(512);
	char action[64];
	for(int i = 0; i < test.number; i++){
		fscanf(file, "%s", action);
		if(strcmp(action, "create") == 0){
			int memory, answer;
			fscanf(file, "%d %d", &memory, &answer);
			int pid = proc_create_vm(kernel, memory);
			if(pid == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}

		}else if(strcmp(action, "read") == 0){
			int pid , addr, size, bufSize, answer;
			fscanf(file, "%d %d %d %d %s %d", &pid, &addr, &size, &bufSize, write_buf, &answer);
			memset(temp_buf, 0, bufSize);
			int read = vm_read(kernel, pid, (char *)addr, size, temp_buf);
			if(strcmp(write_buf, "nil")!=0){
				if(read == answer){
					if(strcmp(write_buf, temp_buf) == 0){
						score += 1;
					}
				}
			}else{
				if(read == answer){
					score += 1;
				}
			}
			temp_buf[0] = '\0';
			write_buf[0] = '\0';
		}else if(strcmp(action, "write") == 0){

			int pid ,addr, size, bufSize, answer;
			memset(temp_buf, 0, bufSize);
			memset(write_buf, 0, bufSize);
			fscanf(file, "%d %d %d %d %s %d", &pid, &addr, &size, &bufSize, write_buf , &answer);
			int write;
			if(strcmp(write_buf, "nil")!=0){
				write = vm_write(kernel, pid, (char *)addr, size, write_buf);
			}else{
				write = vm_write(kernel, pid, (char *)addr, size, temp_buf);
			}
			if(write == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
			temp_buf[0] = '\0';
			write_buf[0] = '\0';
		}else if(strcmp(action, "exit") == 0){
			int pid, answer;
			fscanf(file, "%d %d", &pid, &answer);
			int exit = proc_exit_vm(kernel, pid);
			if(exit == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
		}else if(strcmp(action, "check") == 0){
			//print_kernel_free_space(kernel);
			char str_buf[128], ch;
			fscanf(file, "%s", str_buf);
			while((ch = getc(file))!= '#')
				strncat(str_buf, &ch, 1);
			strncat(str_buf,"\n", 1);
			get_kernel_free_space_info(kernel, buf);

			if(strcmp(buf, str_buf) == 0){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
		}
		if(prev==score)
		{
			printf("Testcase %d action %d %s failed\n", someInt, i, action);
		}
		prev = score;
	}
	printf("Testcase %d Full Score: %d, Your Score: %d\n", someInt, test.fullScore ,score);
}

int run_test(Testcase test, int someInt) {
	printf("Running %s:\n", test.name);

	FILE * file = fopen(test.file, "r");
	if(file == NULL){
		printf("cannot open %s\n", test.file);
		return -1;
	}
	char var[256];
	fscanf(file, "%s %d", var, &KERNEL_SPACE_SIZE);
	fscanf(file, "%s %d", var, &VIRTUAL_SPACE_SIZE);
	fscanf(file, "%s %d", var, &PAGE_SIZE);
	fscanf(file, "%s %d", var, &MAX_PROCESS_NUM);

	printf("KERNEL_SPACE_SIZE=%d\nVIRTUAL_SPACE_SIZE=%d\nPAGE_SIZE=%d\nMAX_PROCESS_NUM=%d\n", KERNEL_SPACE_SIZE, VIRTUAL_SPACE_SIZE, PAGE_SIZE, MAX_PROCESS_NUM);
	int score = 0, prev = 0;
	struct Kernel * kernel = init_kernel();
	char * buf = (char *)malloc(128);
	char * temp_buf = (char *)malloc(512);
	char * write_buf = (char *)malloc(512);
	char action[64];

	for(int i = 0; i < test.number; i++){
		fscanf(file, "%s", action);
		if(strcmp(action, "create") == 0){
			int memory, answer;
			fscanf(file, "%d %d", &memory, &answer);
			int pid = proc_create_vm(kernel, memory);
			if(pid == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}

		}else if(strcmp(action, "read") == 0){
			int pid , addr, size, bufSize, answer;
			fscanf(file, "%d %d %d %d %s %d", &pid, &addr, &size, &bufSize, write_buf, &answer);
			memset(temp_buf, 0, bufSize);
			printf("Before reading pages of process %d\n", pid);
			print_kernel_free_space(kernel);
			print_memory_mappings(kernel, pid);
			int read = vm_read(kernel, pid, (char *)addr, size, temp_buf);
			if(strcmp(write_buf, "nil")!=0){
				if(read == answer){
					if(strcmp(write_buf, temp_buf) == 0){
						score += 1;
					}
				}
			}else{
				if(read == answer){
					score += 1;
				}
			}
			temp_buf[0] = '\0';
			write_buf[0] = '\0';
			printf("After reading pages of process %d\n", pid);
			print_kernel_free_space(kernel);
			print_memory_mappings(kernel, pid);
		}else if(strcmp(action, "write") == 0){

			int pid ,addr, size, bufSize, answer;
			memset(temp_buf, 0, bufSize);
			memset(write_buf, 0, bufSize);
			fscanf(file, "%d %d %d %d %s %d", &pid, &addr, &size, &bufSize, write_buf , &answer);
			printf("Before writing pages of process %d\n", pid);
			print_kernel_free_space(kernel);
			print_memory_mappings(kernel, pid);
			int write;
			if(strcmp(write_buf, "nil")!=0){
				write = vm_write(kernel, pid, (char *)addr, size, write_buf);
			}else{
				write = vm_write(kernel, pid, (char *)addr, size, temp_buf);
			}
			if(write == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
			temp_buf[0] = '\0';
			write_buf[0] = '\0';
			printf("After writing pages of process %d\n", pid);
			print_kernel_free_space(kernel);
			print_memory_mappings(kernel, pid);
		}else if(strcmp(action, "exit") == 0){
			int pid, answer;
			fscanf(file, "%d %d", &pid, &answer);
			int exit = proc_exit_vm(kernel, pid);
			if(exit == answer){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
			printf("After process %d exits\n", pid);
			print_kernel_free_space(kernel);
		}else if(strcmp(action, "check") == 0){
			//print_kernel_free_space(kernel);
			char str_buf[128], ch;
			fscanf(file, "%s", str_buf);
			while((ch = getc(file))!= '#')
				strncat(str_buf, &ch, 1);
			strncat(str_buf,"\n", 1);
			get_kernel_free_space_info(kernel, buf);

			if(strcmp(buf, str_buf) == 0){
				score += 1;
				//printf("Action %d Correct\n", i);
			}else{
				//printf("Action %d Wrong\n", i);
			}
		}
		if(prev==score)
		{
			printf("testcase %d action %d %s failed\n", someInt, i, action);
		}
		prev = score;
	}
	printf("Full Score: %d, Your Score: %d\n", test.fullScore ,score);
	return score;
}

void printResult(int correct, int wrong, int total){
	printf("----------------Testcase Result-----------------\n");
	printf("|\tTOTAL\t|\tPASS\t|\tFAIL\t|\n");
	printf("------------------------------------------------\n");
	printf("|\t%d\t|\t%d\t|\t%d\t|\n", total, correct, wrong);
	printf("------------------------------------------------\n");
	if(total == correct){
		printf("Congratulations! You pass all my testcase.\n");
	}
}
// A simple test case totally 19 scores for you to debug.
int main(int agrc, char* argv[]) {
	  if(agrc != 2){
    printf("Usage: %s <test case no.>\n\n"
           "\ttest case no.:\n"
           "\t\t'0'~'9' to select a test case;\n"
           "\t\t\'10' to run all the test cases\n\n"
           , argv[0]);
		printf("\t\t'11' to run all test cases separately\n");
    return -10;
  	}
	int select = atoi(argv[1]);

	FILE * fr = fopen("./testcase/testsuite.txt","r");
	if( fr == NULL ){
		printf("ERROR: cannot open the inputfile.txt file.\n");
		exit(1);
	}
	fscanf(fr , "%d", &testcaseNum);
	Testcase* testcases = (Testcase*)malloc(sizeof(Testcase) * testcaseNum);
	for(int i = 0; i < testcaseNum; i ++) {
		fscanf(fr, "%d %s", &testcases[i].number,testcases[i].file);
		testcases[i].fullScore = testcases[i].number;
		sprintf(testcases[i].name, "testcase%d", i);
	}

	printf("----------Testcase Program (by Sinyi)---------\n");
	printf("This is a testing program for CSCI3150 Asgn3.\n");
	printf("It's not a official testing program. \n");
	printf("So you might not get a full mark after passing this program. \n");
	printf("----------------------------------------------\n\n");

	if( select == 10 ){
		int correct = 0 ;
		#pragma omp parallel for
		for(int i = 0; i < testcaseNum; i++){
			if(run_test_nil(testcases[i]) == testcases[i].fullScore)
				correct += 1;
		}
		printResult(correct, testcaseNum - correct, testcaseNum);
	} else if(select >=0 && select < 10) {
		run_test(testcases[select], select);
	}
	else if(select==11)
	{
		int correct = 0 ;
		#pragma omp parallel for
		for(int i = 0; i < testcaseNum; i++){
			if(run_test_nil(testcases[i]) == testcases[i].fullScore)
				correct += 1;
		}
		printResult(correct, testcaseNum - correct, testcaseNum);
		#pragma omp parallel for
		for(int k=0; k<testcaseNum; k++)
		{
			run_test_full(testcases[k], k);
		}
	}
	else {
		printf("Please type a number of '0' ~ '11'!\n");
		return 0;
	}
}

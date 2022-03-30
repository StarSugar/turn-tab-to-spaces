#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool filecpy(FILE *input_file, FILE *output_file) {
#ifdef DEBUG
	printf("filecpy has been called!\n");
#endif//DEBUG
	if (input_file == NULL && output_file == NULL) return false;
	char tmp = '\0';
	rewind(input_file);
	rewind(output_file);
	while (1) {
		if (tmp = fgetc(input_file), tmp == EOF) {
			if (ferror(input_file)) {printf("Unable to read file.\n");return false;}
			if (feof(input_file)) {return true;}
		}
		if ((fputc(tmp, output_file) == EOF)) {
			printf("Unable to write the file!\n");
			return 0;
		}
	}
	return true;
}

int string_to_number(char *string) {
#ifdef DEBUG
	printf("string_to_number has been called!\n");
#endif//DEBUG
	int len = (int)strlen(string);
	if (len >= 10) return 0;
	int res = 0;
	for (int i = 0; i < len; i++) {
		switch (string[i]) {
			case '0': break;
			case '1': res += (1 * (int)pow(10, (len - i - 1)));break;
			case '2': res += (2 * (int)pow(10, (len - i - 1)));break;
			case '3': res += (3 * (int)pow(10, (len - i - 1)));break;
			case '4': res += (4 * (int)pow(10, (len - i - 1)));break;
			case '5': res += (5 * (int)pow(10, (len - i - 1)));break;
			case '6': res += (6 * (int)pow(10, (len - i - 1)));break;
			case '7': res += (7 * (int)pow(10, (len - i - 1)));break;
			case '8': res += (8 * (int)pow(10, (len - i - 1)));break;
			case '9': res += (9 * (int)pow(10, (len - i - 1)));break;
			default : return 0;
		}
	}
#ifdef DEBUG
	printf("result of string_to_number == %d\n",res);
#endif//DEBUG
      	if (res > 2048) {
		printf("The number specific to turn tab into space can't bigger than 2047!\n");
		return 0;
	}
	return res;
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
	printf("progress start working.\n");
	printf("argc == %d\n",argc);
#endif//DEBUG
	FILE *input_file = NULL;
	FILE *output_file = NULL;
	FILE *tmp = NULL;
	char *input_file_path = NULL;
	char *output_file_path = NULL;
	int  change_number = 4;
	bool gived_input_file = false;
	bool gived_output_file = false;
	bool gived_change_number = false;
	bool used_tmp = false;
	char cache = '\0';

	if (argc < 2){
		printf("Too few parameters!\nAt least give the input file.\n");
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		switch (argv[i][0]) {
			case '-':
				if (strcmp(argv[i], "-n") == 0) {
#ifdef DEBUG
					printf("used -n\n");
#endif//DEBUG
      					if (gived_change_number) {printf("The parameter -n has been gived.\n"); return 0;}
					i++;
					if (!(i < argc)) {printf("Invalid parameter -n.\n"); return 0;}
					if ((change_number = string_to_number(argv[i]), change_number == 0)) {printf("Invalid number!\nExpected a number after -n.\n"); return 0;}
					gived_change_number = true;
				} else if (strcmp(argv[i], "-o") == 0) {
#ifdef DEBUG
					printf("used -o\n");
#endif//DEBUG
      					if (gived_output_file) {printf("The out put file has been gived!\n"); return 0;}
					if (!gived_input_file) {printf("Expected input file first!\n"); return 0;};
					i++;
					output_file_path = argv[i];
					if (strcmp(input_file_path, output_file_path) == 0) {
#ifdef DEBUG
						printf("input file equal to output file.\n");
#endif//DEBUG
						tmp = fopen("./tmp","wt+");
						if (tmp == NULL) {
							printf("Unable to use the same file as input file and output file,\nbecause cannot create the temporary file!\n");return 0;
						}
						filecpy(input_file, tmp);
						fclose(input_file);
						fclose(tmp);	
						input_file = fopen("./tmp","rt");
						used_tmp = true;
						goto GO_ON;
					}
					if (output_file = fopen(argv[i], "r"), output_file != NULL) {
						printf("Unable to write the file,\nbecause there is already a file named %s\n",argv[i]);
						return 0;
					}
GO_ON:
					if (!(i < argc)) {printf("Invalid parameter -o.\n"); return 0;}
					if (output_file = fopen(argv[i],"wt"), output_file == NULL) {printf("Unable to write the file %s", argv[i]); return 0;};
					gived_output_file = true;
				}
				break;
			default:
#ifdef DEBUG
				printf("Start getting input file.\n");
				printf("gived_input_file == %d\n", gived_input_file);
#endif//DEBUG
				if (gived_input_file) {printf("The input file has been gived!\n"); return 0;}
				input_file_path = argv[i];
				if (input_file = fopen(argv[i],"rt"), input_file == NULL) {printf("Unable to read the file %s", argv[i]); return 0;};
				gived_input_file = true;
		}
	}

	if (!gived_input_file) {printf("Expected input file!\n"); return 0;}
	if (!gived_output_file) {
		output_file_path = "./a.out";
		output_file = fopen(output_file_path, "rt");
		if (output_file != NULL) {
#ifdef DEBUG
			printf("Used a.out as output file.\n");
#endif//DEBUG
			printf("Default output file a.out exist.\nPlease specific an output file by parameter -o!\n");
			fclose(output_file);
			return 0;
		}
		output_file = fopen(output_file_path, "wt");
	}

	char spaces[2048] = {0};

	int times = change_number / 32;

	change_number = change_number - 32 * times;

	for (int i = 0; i < times; i++) {
		strcat(spaces, "                                ");
	}

	for (int i = 0; i < change_number; i++) {
		strcat(spaces," ");
	}

#ifdef DEBUG
	printf("input_file = %s\noutput_file = %s\nspaces = %s\n",input_file_path,output_file_path,spaces);
	if (used_tmp) {
		printf("used tmp\n");
	}
	rewind(input_file);
	rewind(output_file);
#endif//DEBUG
	while (1) {
READ:
		if (cache = fgetc(input_file), cache == EOF) {
			if (ferror(input_file)) {
				printf("Unable to read the input file!\n");
				if (used_tmp == true) {
					filecpy(input_file, output_file);
					fclose(input_file);
					fclose(output_file);
					remove("./tmp");
					return 0;
				} else {					
					fclose(input_file);
					fclose(output_file);
					remove(output_file_path);
					return 0;
				}
			} else {
				printf("Finished!\n");
				if (used_tmp == true) {	
					fclose(input_file);
					fclose(output_file);
					remove("./tmp");
					return 0;
				} else {
					fclose(input_file);
					fclose(output_file);
					return 0;
				}
			}
		}
		if (cache == '\t') {
			if (fputs(spaces, output_file) == EOF) {			
				printf("Unable to write the output file!\n");
				if (used_tmp == true) {
					filecpy(input_file, output_file);
					fclose(input_file);
					fclose(output_file);
					remove("./tmp");
					return 0;
				}
				fclose(input_file);
				fclose(output_file);
				remove(output_file_path);
				return 0;
			}
			goto READ;
		}
		if (fputc(cache, output_file) == EOF) {
			printf("Unable to write the output file!\n");
			if (used_tmp == true) {
				filecpy(input_file, output_file);
				fclose(input_file);
				fclose(output_file);
				remove("./tmp");
				return 0;
			}
			fclose(input_file);
			fclose(output_file);
			remove(output_file_path);
			return 0;
		}
	}

	return 0;
}

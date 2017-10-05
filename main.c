#include "stdio.h"
#include "stdlib.h"
#define FILE_PROCESSING_H_
#include "file_processing.h"
#define _GNU_SOURCE
#include <string.h>
#include "environment.h"
#include "command_parser.h"

typedef enum{ false = 0 , true = 1 } bool ;
FILE *file;
FILE *log;
FILE *history;
int maxLength;
const char* path;
  char *line = NULL;

const char* home;
int bufsize = 1024;
char *buffer;  //buffer for 1024 characters
char c; //for reading new lines
int index1; // for index in newline
 //of dynamic size to read command with unknown length
void start_shell(bool read_from_file);
void shell_loop(bool input_from_file);
int main(int argc, char *argv[])
{

         setup_environment();
         path= get_path();
         home= get_home();
         maxLength = get_max_length();

        if( argc > 1 ){
            start_shell(true);
        }
        else{
            start_shell(false);
        }




    return 0;
}

void start_shell(bool read_from_file)
{
	chdir (home); // let shell starts from home


	if(read_from_file){
		// file processing functions should be called from here
        open_commands_batch_file();
        file = get_commands_batch_file();
        shell_loop(true);
	}
	else{
		shell_loop(false);
	}
}

void shell_loop(bool input_from_file)
{
	bool from_file = input_from_file;

	while(true){
		if(from_file){
			//read next instruction from file
//char line[256];

  //  while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
      //  printf("%s", line);
    //}

    		// if end of file {from_file = false; continue;}
		}
		else{

			buffer = malloc(sizeof(char) * bufsize);
                index1 =0;
                printf("\n Shell> ");


                     while((c = getchar()) != '\n' && c != EOF)
                    {

                       buffer[index1] = c;


                       index1++;

                       if (index1 >= bufsize) {
                      bufsize += 1024;
                      buffer = realloc(buffer, bufsize);

                      }

                    }

                    buffer[index1] = '\0';
                    if(index1 != 0 ) {
                        parse_command(buffer);
                    }
                    free(buffer);


		}


	}
}

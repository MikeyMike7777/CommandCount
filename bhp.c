/** 
 * file:  bhp.c 
 * author:  Michael Mathews 
 * course: CSI 3336 
 * assignment:  project 5 
 * due date:  3/3/2023 
 * 
 * date modified:  3/1/2023 
 *    - file created
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
	/** Name of the command **/
	char cmdName[ 13 ];

	/** Frequency of commands encountered **/
	int cmdCount;
} CmdRec;

void resize(CmdRec **cmds, int size, int *capacity) {
    *capacity *= 2;
    CmdRec *temp = malloc(*capacity * sizeof(CmdRec));
    free(*cmds);
    *cmds = temp;
}

int main(int argc, char **argv){
CmdRec *cmds = malloc(8 * sizeof(CmdRec));
    int capacity = 8;
    int size = 0, index, i, j, backTick = 0;
    char line[MAX_LINE_LENGTH];
    char trash[MAX_LINE_LENGTH];
    char cmd[13];

    //get a new line
    while(scanf("%[^\n]%*c", line) != EOF){
        int counter = 1;
        for (i = 0; line[i] != '\0'; i++) {
             if (line[i] == '|') {
                 line[i+1] = '\n';
                 counter++;
             }
             else if(line[i] == '`' && backTick == 0){
                 backTick = 1;
                 line[i] = '\n';
                 counter++;
             }
             else if(line[i] == '`' && backTick == 1){
                 line[i] = ' ';
                 backTick = 0;
             }
        }
        line[i] = '\n';
        //get command
        int start = 0;
        for (i = 0; i < counter; i++){
            sscanf(line + start, "%12s", cmd);
            start += strlen(cmd);
            sscanf(line + start, "%[^\n]%*c", trash);
            start += strlen(trash);
            //find if command in array
            index = -1;
            for(j = 0; j < size; j++){
                if(strcmp(cmd, cmds[j].cmdName) == 0){
                    index = j;
                    break;
                }
            }

            //add command if not in array
            if(index == -1){
                //make room in array
                if(size >= capacity){
                    resize(&cmds, size, &capacity);
                }
                //save command
                strcpy(cmds[size].cmdName, cmd);
                cmds[size].cmdCount = 1;
                size++;
            }
            else {
                //increase command count
                cmds[index].cmdCount++;
            }
        }
        memset(line, 0, sizeof(line));
    }

    //print 
    for(i = 0; i < size; i++){
        printf("%-12s %4d\n", cmds[i].cmdName, cmds[i].cmdCount);
    }

    free(cmds);

    return 0;
}

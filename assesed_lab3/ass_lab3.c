/*CITS2002 Assesed Lab 3
By Finlay Thomson SID: 23953297*/

#include<stdio.h>
#include <stdlib.h>

struct song_slot {
    int playlist_id;
    int track_num;
    int last_played;
};



//open a file
FILE* open_file(char filename[]) {
    FILE *fp;
    fp=fopen(filename, "r");
    if (fp == NULL) {
        printf("file error\n");
        return NULL;
    }
    return fp;
}

//given a line and process structure, will write that line to the struct
int line_parse(char *line, struct song_slot *dest) {
    
    int used;//bit of the line already parsed
    int ints;//all the int values that arent the name or fault positions
    char *name = NULL;

    //first assign name
    if (sscanf(line, "%ms%n", &name, &used) != 1) {
         return 1;
    } 
    dest->playlist_id = atoi(&name[8]);


    
}

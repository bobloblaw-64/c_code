/*CITS2002 Assesed Lab 3
By Finlay Thomson SID: 23953297*/

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct song_slot {
    int playlist_id;
    int track_num;
    int last_played;
};

struct playlist {
    int id;
    int song_qty;
    int *song_array;
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
int line_parse(char *line, struct playlist *dest) {
    
    int used;//bit of the line already parsed
    
    char *name = NULL;

    //first assign name
    if (sscanf(line, "%ms%n", &name, &used) != 1) {
         return 1;
    } 
    dest->id = atoi(&name[8]);

    char *songs = line + used;
    
    dest->song_qty = 0;
    int capacity = 2;

    while (true) {
        
        if (sscanf(songs, "%d%n", &dest->song_array[i], &used) != 1) {

        }
    }
    


    
}

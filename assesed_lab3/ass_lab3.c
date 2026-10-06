/*CITS2002 Assesed Lab 3
By Finlay Thomson SID: 23953297*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 1000

//song defined by its playlist and track no
typedef struct  {
    int playlist_id;
    int track_num;
    int last_played;
} song_slot;

//playlist as written in inpput doc
typedef struct {
    int id;
    int request_qty;
    int requests[MAX_REQUESTS];
} playlist;

//fix this:
void make_library(song_slot *out) {
    
    for (int plst; plst < 8; plst++) {
        for (int track; track < 4; track++) {
            out->playlist_id = plst;
            out->track_num = track;
        }
    }
}

//open a file
FILE* open_file(char filename[]) {
    FILE *fp;
    fp=fopen(filename, "r");
    if (fp == NULL) return NULL;
    
    return fp;
}

void line_parse(char *line, playlist *dest) {

    char name[10];
    int used;
    sscanf(line, "%9s%n", name, &used);
    dest->id = atoi(&name[8]);

    char *songs = line + used;

    int i = 0;

    while(sscanf(songs, "%d%n", &dest->requests[i], &used) == 1 && i < MAX_REQUESTS) {
        songs = songs + used;
        i++;
    } 
    dest->request_qty = i;
}

//read playlist file and copy to array
int file_parse(char filename[], playlist playlists[]){

    FILE *file = open_file(filename);
    if (file == NULL) return 1;
    
    char line[MAX_REQUESTS * sizeof(int)];
    int i = 0;

    while(fgets(line, sizeof(line), file) && i < 8) {

        line_parse(line, &playlists[i]);
        i++;
    }

    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {

    playlist playlist_array[10]; 

    //if(argc != 3) return 1;

    if (file_parse(argv[1], playlist_array) == 1) return 1;

    //test looop:
    int i = 0;
    
    while (i < 8) {
        printf("id %d qty %d requests:", playlist_array[i].id, playlist_array[i].request_qty);
        int j = 0;
        while (j < playlist_array[i].request_qty) {
            printf("%d ", playlist_array[i].requests[j]);
            j++;
        }
        printf("\n");
        i++;
    }

}

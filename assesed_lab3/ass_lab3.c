/*CITS2002 Assesed Lab 3
By Finlay Thomson SID: 23953297*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 1000
#define NOT_CACHED 99

int global_time = 0;

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
    int track_location[4];
    int next_request;
} playlist;

//creates library data and pointers:
void make_library(song_slot data[32], song_slot *ptrs[32]) {
    int i;
    for (int plst = 0; plst < 8; plst++) {

        for (int track = 0; track < 4; track++) {
            //calculate index
            i = plst * 4 + track;
            //initialise data:
            data[i].playlist_id = plst;
            data[i].track_num = track;
            data[i].last_played = 0;
            //initialise pointers:
            ptrs[i] = &data[i];
        }
    }
}



void line_parse(char *line, playlist *dest) {

    char name[10];
    int used;
    sscanf(line, "%9s%n", name, &used);
    dest->id = atoi(&name[8]);

    char *songs = line + used;

    int i = 0;

    while (i < MAX_REQUESTS && sscanf(songs, "%d%n", &dest->requests[i], &used) == 1) {
      songs = songs + used;
      i++;
    }
    dest->request_qty = i;
}

//read playlist file and copy to array
int file_parse(char filename[], playlist playlists[]){

    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("file read error\n");
        fclose(file);
        return 1;
    }
    char line[(MAX_REQUESTS * 2 + 10) * sizeof(char)];
    int i = 0;

    while (i < 8 && fgets(line, sizeof(line), file)) {

      line_parse(line, &playlists[i]);
      i++;
    }

    if (i != 8) return 1;

    fclose(file);
    return 0;
}

//initialise next request and tracks cache location for playlist array
void init_playlist(playlist dest[8]) {

    for (int plst = 0; plst < 8; plst++) {

        dest[plst].next_request = 0;

        for (int i = 0; i < 4; i++) {

            dest[plst].track_location[i] = NOT_CACHED;
        }
    }
}

//todo
int write_report(song_slot **lib[], song_slot **cache[]) {

}

int main(int argc, char *argv[]) {

    //check correct argument number
    if(argc != 3) {
        printf("incorrect number of arguments\n");
        return 1;
    }
    //initialise all the structures we will need:
    playlist playlist_array[8]; 
    song_slot library_data[32];
    song_slot *library_ptrs[32];
    song_slot *cache[16] = {NULL};

    //setup library array:
    make_library(library_data, library_ptrs);

    //parse text file and copy to array, then initialise next request and cache location array
    if (file_parse(argv[1], playlist_array) == 1) return 1;
    init_playlist(playlist_array);


}

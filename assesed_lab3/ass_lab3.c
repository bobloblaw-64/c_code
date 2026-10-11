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

//write results to text file
int write_report(char filename[], playlist playlists[], song_slot *cache[]) {

    FILE *file;
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("file write error\n");
        return 1;
    }

    fprintf(file, "Track tables:\n");
    for (int plst = 0; plst < 8; plst++) {
        
        fprintf(file, "Playlist%d: %d, %d, %d, %d\n", plst, 
            playlists[plst].track_location[0], playlists[plst].track_location[1],
            playlists[plst].track_location[2], playlists[plst].track_location[3]);
    }

    fprintf(file, "\nSong Cache:\n");
    for (int i = 0; i < 16; i++) {

        if (cache[i] == NULL) {
            
            fprintf(file, "Slot %d: NULL\n", i);
            continue;
        
        }
        fprintf(file, "Slot %d: %d, %d, %d", i,
        cache[i]->playlist_id, cache[i]->track_num, cache[i]->last_played);
        
        if (i != 15) {
            fprintf(file, ";\n");
        }
        else {
            fprintf(file, "\n");
        }
    }
    fclose(file);
    return 0;
}


//todo! this is shit so just start over lol
int slot_choose(playlist p, song_slot *c[]) {

    int cache_slot;

    for (int i = 0; i < 16; i++) {
        if (c[i] == NULL) return i;
    }

    int least_recent = NOT_CACHED;
    for (int i = 0; i < 4; i++) {

        int last_played = c[p.track_location[i]]->last_played;

        if (last_played < least_recent) {

            least_recent = last_played;
            cache_slot = p.track_location[i];
        }
    }

    if (least_recent == NOT_CACHED) {

        for (int i = 0; i < 16; i++) {

        int last_played = c[i]->last_played;

        if (last_played < least_recent) {

            least_recent = last_played;
            cache_slot = i;
            }
        }
    }

    return cache_slot;
}

void request_song(int t, playlist p, song_slot *lib[], song_slot *cache[]) {
    int cache_pos = p.track_location[t];

    if (cache_pos != NOT_CACHED) {//is song in cache if so set last played to current time?
        cache[cache_pos]->last_played = global_time;
    }

    else {

        cache_pos = slot_choose(p, cache);
        p.track_location[t] = cache_pos;

        int lib_pos = p.id * 4 + t;
        cache[cache_pos] = lib[lib_pos];
    }
}

//main sim loop
void playlist_loop(playlist plsts[], song_slot *lib[], song_slot *cache[]) {
    
    int finished_plsts;

    while (true) {

        finished_plsts = 0;
        for (int i = 0; i < 8; i++) {

            int nxt_req = plsts[i].next_request;
            //skip playlist if requests fullfilled
            if (nxt_req >= plsts[i].request_qty) {
                finished_plsts ++;
                continue;
            }

            int track = plsts[i].requests[nxt_req];
            request_song(track, plsts[i], lib, cache);

            plsts[i].next_request++;
            global_time++;
        }
        if (finished_plsts == 8) break;
    }
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

    write_report(argv[2], playlist_array, cache);

}

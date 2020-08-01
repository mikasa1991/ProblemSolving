#ifndef LIBRARY_H
#define LIBRARY_H

#define BUFFER_LENGTH 200
#define NUM_DIRECTORY_ARTIST 256
#define NUM_DIRECTORY_INDEX 5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _artist artist;
typedef struct _song song;
typedef struct _node node;

typedef struct _song
{
	int index;			//uniquely identifiable id
	char* title;
	artist* artist;
	char* path;			//absolute path name of mp3 file
}song;

typedef struct _node
{
	song* song;
	node* prev;
	node* next;
}node;

typedef struct _artist
{
	char* name;
	artist* next;		//pointer to the next artist
	node* head;			//head of double linked list of nodes
	node* tail;			//tail of double linked list of nodes
}artist;

void initialize();
void search_song(char* name);
void search_song2(char* name, char* title);
void add_song(char* name, char* title, char* path);	//if success, return 1
void delete(int index);
void play(int index);
void status();											//display all songs in the library
void load(FILE* fp);
void save(FILE* fp);
void save_artist(artist* p, FILE* fp);
void save_song(song* ptr_song, FILE* fp);
void remove_node(artist* ptr_artist, node* ptr_node);
void destroy_song(song* ptr_song);
void remove_artist(artist* ptr_artist);
void print_index_directory(node* n);

node* create_node_instance(song* ptr_song);
song* create_song_instance(artist* ptr_artist, char* title, char* path);
artist* create_artist_instance(char* name);
artist* find_artist(char* name);
artist* add_artist(char* name);
void print_artist(artist* p);
void print_song(song* p);
void insert_node(artist* ptr_artist, node* ptr_node);
void insert_to_index_directory(song* ptr_song);
node* find_node(artist* ptr_artist, char* title);
node* find_song(int index);

#endif	//LIBRARY_H
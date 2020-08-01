#include "library.h"
#include "string_tools.h"

/*
artist* 배열을 생성해서 artist명의 맨 앞글자의 숫자를 배열의 인덱스로 하여,
artist를 저장하기 위함.
예를 들어,
 a 97   aman -> amy -> ...  
 b 98   black pink -> brother -> ...
 c 99
 d 100
 ...
*/
static artist* artist_directory[NUM_DIRECTORY_ARTIST] = {NULL, };

static node* index_directory[NUM_DIRECTORY_INDEX]  = {NULL, };
static int num_index = 0;

#if 0
//전역변수로 초기화를 했기 때문에, 이니셜라이즈 함수가 따로 필요없다고 생각되는데
void initialize()
{
	for(int i = 0; i < NUM_DIRECTORY_ARTIST; i++)
	{
		artist_directory[i] = NULL;
	}

	for(int i = 0; i < NUM_DIRECTORY_INDEX; i++)
	{
		index_directory[i] = NULL;
	}
}
#endif

//txt -> memory
/*
strdup 함수를 이용해 name, title, path변수에 값을 할당하는 이유는?
load함수가 종료된 이후에도 위 변수에 접근해야하기 때문이다.
*/
void load(FILE* fp)
{
	char buffer[BUFFER_LENGTH]  ={0, };
	char* name = NULL;
	char* title = NULL;
	char* path = NULL;

	while(1)
	{
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)	//get a line
		{
			break;
		}
		name = strtok(buffer, "#");
		if(strcmp(name, " ") == 0) {name = NULL;}
		else {name = strdup(name);}

		title = strtok(NULL, "#");
		if(strcmp(title, " ") == 0) {title = NULL;}
		else {title = strdup(title);}

		path = strtok(NULL, "#");
		if(strcmp(path, " ") == 0) {path = NULL;}
		else {path = strdup(path);}

		printf("%s %s %s\n", name, title, path); //for debug
		add_song(name, title, path);
	}
}

void search_song(char* name)	//argument: artist name
{
	artist* ptr_artist = find_artist(name);
	//if Not search name
	if(ptr_artist == NULL)
	{
		puts("No such artist exists.");
		return;
	}

	//if search name
	puts("Found:");
	print_artist(ptr_artist);
}

void search_song2(char* name, char* title)	//argument: artist name, music title
{
	artist* ptr_artist = find_artist(name);
	//if Not search name
	if(ptr_artist == NULL)
	{
		puts("No such artist exists.");
		return;
	}

	//if search name
	node* ptr_node = find_node(ptr_artist, title);
	
	if(ptr_node != NULL)
	{
		puts("Found:");
		print_song(ptr_node->song);
	}
	else
	{
		puts("No such song exists.");
		return;
	}
}

node* find_node(artist* ptr_artist, char* title)
{
	node* ptr_node = ptr_artist->head;
	
	//while(ptr_node != NULL && strcmp(ptr_node->song->title, title) != 0)
	while(ptr_node != NULL && strcmp(ptr_node->song->title, title) < 0) //in ordered list, it is more effective.
	{
		ptr_node = ptr_node->next;
	}

	if(ptr_node != NULL && strcmp(ptr_node->song->title, title) == 0)
	{	
		return ptr_node;
	}

	//if search not title
	else
	{
		return NULL;
	}
}

void add_song(char* name, char* title, char* path)
{
	/*
	 *case1. original artist exist
	 *case2. original artist not exist
	 */

	//case1. find if the artist already exists
	artist* ptr_artist = find_artist(name);	//return NULL if not
	
	//case2.find if the artist not exist
	if(ptr_artist == NULL)
	{
		ptr_artist = add_artist(name);
	}
	
	//add the song to the artist pointed by ptr_artist
	song* ptr_song = create_song_instance(ptr_artist, title, path);
	node* ptr_node = create_node_instance(ptr_song);

	//insert node
	insert_node(ptr_artist, ptr_node); //for artist directory
	insert_to_index_directory(ptr_song); //for index directory
}

void insert_to_index_directory(song* ptr_song)
{
	node* ptr_node = create_node_instance(ptr_song);

	// index can have val: 0 ~ 9
	int index = (ptr_song->index) % NUM_DIRECTORY_INDEX;
	node* p = index_directory[index];	//head
	node* q = NULL;

	//for ordered list
	while(p != NULL && strcmp(p->song->title, ptr_song->title) < 0)
	{
		q = p; //q is always the prev of p
		p = p->next;
	}

#if 0
	if(q == NULL && p == NULL)	//add unique
	{
		index_directory[index] = ptr_node;
	}
	else if(q == NULL)	//add_first
	{
		ptr_node->next = index_directory[index];
		index_directory[index] = ptr_node;

	}
#endif
	//linked list
	//case1. add unique or add_first
	if(q == NULL)
	{
		ptr_node->next = index_directory[index];
		index_directory[index] = ptr_node;

	}
	//case2. add after q
	else
	{
		ptr_node->next = p;
		q->next = ptr_node;
	}
}

node* create_node_instance(song* ptr_song)
{
	node* ptr_node = (node*)malloc(sizeof(node));
	ptr_node->song = ptr_song;
	ptr_node->next = NULL;
	ptr_node->prev = NULL;
	return ptr_node;
}

void insert_node(artist* ptr_artist, node* ptr_node)
{
	node* p = ptr_artist->head;
	
	//오름차순 정렬을 유지한 채로 삽입을 하기 위해서
	while(p != NULL && strcmp(p->song->title, ptr_node->song->title) < 0)
	{
		p = p->next;
	}

	/*
	double linked list에서는 tail이 존재하기 때문에,
	case1과 case2를 합칠 수 없다.
	*/

	//case1. node empty
	if(ptr_artist->head == NULL)
	{
		ptr_artist->head = ptr_node;
		ptr_artist->tail = ptr_node; 
	}
	//case2. add at the front
	else if(p == ptr_artist->head)
	{
		ptr_node->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_node;
		ptr_artist->head = ptr_node;
	}
	//case3. add at the end
	else if(p == NULL)	// &&(ptr_artist->head != NULL)
	{
		ptr_node->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_node;
		ptr_artist->tail = ptr_node;
	}
	//case4. add in the middle
	else	//add_before_p
	{
		ptr_node->next = p;
		ptr_node->prev = p->prev;
		p->prev->next = ptr_node;
		p->prev = ptr_node;
	}
}

song* create_song_instance(artist* ptr_artist, char* title, char* path)
{
	song* ptr_song = (song*)malloc(sizeof(song));
	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;
	return ptr_song;
}

artist* find_artist(char* name)	//pic04
{
	artist* p = artist_directory[(unsigned char)name[0]];	//first artist with initial name[0]
	
	/*
	artist를 오름차순으로 보관하고 있기 때문에,
	기존의 artist목록에서 내가 입력하고자 하는 artist명보다
	처음으로 같거나 큰 경우에 반복문을 탈출한다.
	위와같이 하면, 같은 게 없을 경우 전체를 무의미하게 탐색하는 것을
	방지할 수 있으므로 더 효율적이다.

	이 시점에서 같으면 해당 artist목록에 입력받은 artist명이
	존재한다는 것이고, 더 크다면 이 때는 입력받은 artist명이
	없다는 것이다.
	*/
	//while(p != NULL && strcmp(p->name, name) != 0)
	while(p != NULL && strcmp(p->name, name) < 0)
	{
		p = p->next;
	}

	if(p != NULL && strcmp(p->name, name) == 0) { return p; }		//if find success, return p
	else { return NULL; }											//if find fail, return NULL
}

artist* add_artist(char* name)
{
	artist* ptr_artist = create_artist_instance(name);

	artist* p = artist_directory[(unsigned char)name[0]];	//p indicate artist head
	artist* q = NULL;										//q is always the prev of p...because artist is one-way linkedlist

	/*
	artist를 오름차순으로 보관하고 있기 때문에,
	기존의 artist목록에서 내가 입력하고자 하는 artist명보다
	처음으로 같거나 큰 경우에 반복문을 탈출한다.
	이 때 q는 처음으로 같거나 큰 경우에 해당되는 노드의
	앞의 노드를 가르킨다.
	*/
	while(p != NULL && strcmp(p->name, name) < 0)
	{
		q = p;
		p = p->next;
	}

#if 0	
	//i think you don't have to separate case1 from case2
	//case1. node empty
	if(p == NULL && q == NULL)	//same expression
	//if(artist_directory[(unsigned char)name[0]] == NULL)
	{
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}

	//case2. add at the front
	else if(q == NULL)	//if p is not NULL ;add at front
	{
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
#endif
	//case1. node empty, or, case2. add at the front
	if(q == NULL)
	{
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;	
	}

	//case3. add in the middle
	else //add betweens q and p ;add_after(q)
	{
		q->next = ptr_artist;
		ptr_artist->next = p;
	}
	return ptr_artist;
}

artist* create_artist_instance(char* name)
{
	artist* ptr_artist = (artist*)malloc(sizeof(artist));
	ptr_artist->name = name;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	ptr_artist->next = NULL;
	return ptr_artist;
}

void status()
{
	for(int i = 0; i < NUM_DIRECTORY_ARTIST; i++)
	{
		artist* p = artist_directory[i];
		while(p != NULL)
		{
			printf("%d\n", i);
			print_artist(p);
			p = p->next;
		}
	}
	puts(" ");

	for(int i = 0; i < NUM_DIRECTORY_INDEX; i++)
	{
		node* n = index_directory[i];
		//while(n != NULL)
		if(n != NULL)
		{
			printf("index: %d family\n", i);
			print_index_directory(n);
			n = n->next;
		}
	}
}

void print_index_directory(node* head)
{
	node* p = head;
	while(p != NULL)
	{
		printf("	%d: %s, %s, %s\n"
		, p->song->index, p->song->title, p->song->path, p->song->artist->name);
		p = p -> next;
	}
}

void print_artist(artist* p)
{
	printf("%s\n", p->name);
	node* ptr_node = p->head;
	while(ptr_node != NULL)
	{
		print_song(ptr_node->song);
		ptr_node = ptr_node->next;
	}
}

void print_song(song* p)
{
	printf("	%d: %s, %s\n", p->index, p->title, p->path);
}

node* find_song(int index)
{
	node* ptr_node = index_directory[index % NUM_DIRECTORY_INDEX];
	while(ptr_node != NULL && ptr_node->song->index != index)
	{
		ptr_node = ptr_node->next;
	}
	return ptr_node;
}

void play(int index)
{
	node* ptr_node = find_song(index);
	if(ptr_node == NULL)
	{
		puts("No such song exists.");
		return;
	}

	printf("%s, %s is now playing.\n", ptr_node->song->artist->name, ptr_node->song->title); //for debug
}

void save(FILE* fp)
{
	for(int i = 0; i < NUM_DIRECTORY_ARTIST; i++)
	{
		artist* p = artist_directory[i];
		while(p != NULL)
		{
			save_artist(p, fp);
			p = p->next;
		}
	}
}

void save_artist(artist* p, FILE* fp)
{
	node* ptr_node = p->head;
	while(ptr_node != NULL)
	{
		save_song(ptr_node->song, fp);
		ptr_node = ptr_node->next;
	}
}

void save_song(song* ptr_song, FILE* fp)
{
	if(ptr_song->artist != NULL) fprintf(fp, "%s#", ptr_song->artist->name);
	else fprintf(fp, " #");
	if(ptr_song->title != NULL) fprintf(fp, "%s#", ptr_song->title);
	else fprintf(fp, " #");
	if(ptr_song->path != NULL) fprintf(fp, "%s#", ptr_song->path);
	else fprintf(fp, " #\n");
}

void delete(int index)
{
	//puts("delete!");
	node* q = NULL;
	node* p = index_directory[index % NUM_DIRECTORY_INDEX];
	while(p != NULL && p->song->index != index)
	{
		q = p;
		p = p->next;
	}

	//1. free memory from index_directory
	if(p == NULL) 	//empty list or the index not exist
	{
		puts("No such song exists.");
		return;
	}

	song* ptr_song = p->song;
	
	if(q == NULL)	// && ( p != NULL) //remove first
	{
		//p = p->next;
		index_directory[index % NUM_DIRECTORY_INDEX] = p->next;
		//printf("%p\n", p);
		//printf("%p\n", index_directory[index % NUM_DIRECTORY_INDEX]);
	}
	else			//remove after q
	{
		q->next = p->next;
	}
	free(p);

	//2. free memory from artist_directory
	artist* ptr_artist = ptr_song->artist;
	node* ptr_node = find_node(ptr_artist, ptr_song->title);
	
	//if the node (you wanna find) not exist
	if(ptr_node == NULL)
	{
		puts("Not found node - something wrong.");
		return;
	}

	//if the node (you wanna find) exist
	remove_node(ptr_artist, ptr_node);
	destroy_song(ptr_song);
}

void destroy_song(song* ptr_song)
{
	if(ptr_song->title != NULL) free(ptr_song->title);
	if(ptr_song->path != NULL)  free(ptr_song->path);
	free(ptr_song);
}

void remove_node(artist* ptr_artist, node* ptr_node)
{
	node* head = ptr_artist->head;
	node* tail = ptr_artist->tail;

	//case1. remove unique
	if(head == ptr_node && tail == ptr_node)
	{
		ptr_artist->head = NULL;
		ptr_artist->tail = NULL;
		remove_artist(ptr_artist);
	}
	//case2. remove head
	else if(head == ptr_node)
	{
		ptr_artist->head = ptr_node->next;
		ptr_node->next->prev = NULL;
	}
	//case3. remove tail
	else if(tail == ptr_node)
	{
		ptr_artist->tail = ptr_node->prev;
		ptr_node->prev->next = NULL;
	}
	//case4. remove sth in the middle
	else
	{
		ptr_node->prev->next = ptr_node->next;
		ptr_node->next->prev = ptr_node->prev;
	}
	free(ptr_node);
}

//if song nothing, i wanna delete the artist.
void remove_artist(artist* ptr_artist)
{
	char* name = ptr_artist->name;
	artist* p = artist_directory[(unsigned char)name[0]];
	artist* q = NULL;

	//while( p!= NULL && strcmp(p->name, name) == 0)
	while( p!= NULL && strcmp(p->name, name) < 0 )	//in ordered list, more effective
	{
		q = p;
		p = p->next;
	}

	//any artist not exist
	if(p == NULL)
	{
		return;
	}

	//error: it can not execute all time.
	//case1. the node i wanna remove not exist, but another nodes exist.
	if(strcmp(p->name, name) != 0)
	{
		puts("error: the artist that will be removed not exist.");
		return;
	}

	//remove in front or remove unique
	if(q == NULL)	// %% p != NULL
	{
		artist_directory[(unsigned char)name[0]] = p->next;
	}

	//remove after q
	else
	{
		q->next = p->next;
	}
}
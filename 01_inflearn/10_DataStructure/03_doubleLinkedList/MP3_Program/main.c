#include "string_tools.h"
#include "library.h"

void process_command();
void handle_add();
void handle_load();
void handle_search();
void handle_play();
void handle_save();
void handle_remove();

void main()
{
	//initialize();
	handle_load();
	process_command();	
}

void process_command()
{
	char command_line[BUFFER_LENGTH] = {0, };
	char* command = NULL;

	while(1)
	{
		printf("$ ");	//prompt
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)	//get a line
		{
			continue;
		}
		command = strtok(command_line, " ");

		/*
		add
		search
		delete index
		status
		play index
		save as filename
		*/
		if     (strcmp(command, "add") == 0) 	handle_add();
		else if(strcmp(command, "search") == 0) handle_search();
		else if(strcmp(command, "delete") == 0) handle_remove();
		else if(strcmp(command, "status") == 0) status();
		else if(strcmp(command, "play") == 0)	handle_play();
		else if(strcmp(command, "save") == 0)
		{
			char* tmp = strtok(NULL, " ");
			if(tmp == NULL || strcmp(tmp, "as") != 0)
			{
				puts("input format: save as filename");
				continue;
			}
			handle_save();
		} 
		else if(strcmp(command, "exit") == 0) 	break;
		else puts("Invalid command.");
	}
}

void handle_remove()	//remove ? by using index
{
	char* id_str = strtok(NULL, " ");
	if(id_str == NULL)
	{
		puts("input format: delete index.");
		return;
	}
	int index = atoi(id_str);
	delete(index);
}

void handle_save()	//save as filename
{
	char* file_name = strtok(NULL, " ");
	FILE* fp = fopen(file_name, "w");
	save(fp);	//memory -> txt
	fclose(fp);
}

void handle_load()	//filename
{
	char buffer[BUFFER_LENGTH] = {0, };
	printf("Data file name ? ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0)	//get a line
	{
		puts("you didn't put the txt file.");
		return;
	}
	FILE* fp = fopen(buffer, "r");
	
	//file not exists
	if(fp == NULL)
	{
		printf("No such file exists.\n");
		return;
	}

	//file exists
	load(fp);
	fclose(fp);
	puts("load success");
}

void handle_play()	//play sth index
{
	char* id_str = strtok(NULL, " ");
	if(id_str == NULL)
	{
		puts("input format: delete index.");
		return;
	}
	int index = atoi(id_str);
	play(index);
}

void handle_search()
{
	char buffer[BUFFER_LENGTH] = {0, };
	char* name = NULL;
	char* title = NULL;

	printf("	artist: ");
	if(read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
	{
		puts("you have to input your artist.");
		return;
	}
	else name = strdup(buffer);

	printf("	title: ");
	int title_len = read_line(stdin, buffer, BUFFER_LENGTH);
	title = strdup(buffer);
	//title = buffer;	//no problem, right?

	if(title_len <= 0) search_song(name);
	else 			   search_song2(name, title);
}

void handle_add()
{
	char buffer[BUFFER_LENGTH] = {0, };
	char* name = NULL;
	char* title = NULL;
	char* path = NULL;

	printf("	artist: ");
	if(read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
	{
		puts("you have to input a name");
		return;
	} 
	//if(read_line(stdin, buffer, BUFFER_LENGTH) > 0) 
	{
		name = strdup(buffer);	//have to input
	}
	
	printf("	title: ");
	if(read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
	{
		puts("you have to input a title");
		return;
	}
	//if(read_line(stdin, buffer, BUFFER_LENGTH) > 0)
	{
		title = strdup(buffer);	//have to input
	} 
	
	printf("	path: ");
	/*
	//path는 입력되도 안되도 상관없으므로, 하기의 내용 주석처리
	if(read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
	{
		puts("you have to input a title");
		return;
	}
	*/
	if(read_line(stdin, buffer, BUFFER_LENGTH) > 0)
	{
		path = strdup(buffer);
	}
	printf("%s %s %s\n", name, title, path);	//for debug
	add_song(name, title, path);
}
/*
F(key) -> hashcode -> index -> value

검색하고자하는 키값을 입력받아서 해쉬함수를 돌려서
반환받은 해쉬코드를
배열의 인덱스로 환산을 해서
 >배열의 인덱스로 어떻게 환산할까?
 배열공간을 고정된 크기만큼 미리 만들어놓고
 해쉬코드를 배열의 갯수로 나머지 연산을 해서
 배열에 나눠 담는다
데이터의 값에 접근하는 자료구조다

collision
키가 달라도 해시코드가 같을 수 있다.
해시코드가 달라도 같은 배열의 인덱스일 수 있다.
이런 collision을 줄이기 위해서 해시함수를 어떻게 만드느냐가 중요하다.
*/

/*
F(key) -> hashcode -> index -> value
문자열 -> 아스키값 -> 해시코드%배열크기 -> value
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_TABLE 3
#define MAX_KEY 64
#define MAX_DATA 128

typedef struct _node node;
typedef struct _node
{
	char key[MAX_KEY+1];
	char value[MAX_DATA+1]; 
	struct node* prev;
	struct node* next;
}node;

typedef struct _hashTable
{
	char key[MAX_KEY+1];
	char value[MAX_DATA+1];
	node* head;
}hashTable;

hashTable tb[MAX_TABLE];

int get_hashcode(char* key)
{
	int hashcode = 0;
	for(int i = 0; i < strlen(key); i++)
	{
		hashcode += key[i];
	}
	return hashcode;
}

int convertToIndex(int hashcode)
{
	return hashcode % MAX_TABLE;
}

/*
인덱스로 배열방을 찾은 이후에
배열방에 노드가 여러개 존재하는 경우에
검색키를 가지고 해당노드를 찾아오는 함수 정의하자
*/
node* search_key(node* list, char* key)
{
	if(list == null) return null;

}

void put(char* key, char* value)
{
	int hashcode = get_hashcode(key);
	int index = convertToIndex(hashcode);
	tb[index]

}

void main()
{
	get_hashcode("sung");
}
#include "linkedlist.h"

void main()
{
	head = create_node_instance("Lee Donghee");
	(void)add(0, "Kim Jinwoo");	//0: Kim Jinwoo, 1: Lee Donghee
	(void)add(1, "Kim Kahee");	//0: Kim Jinwoo, 1: Kim Kahee, 2: Lee Donghee
	(void)add(2, "Kim Taehee");	//0: Kim Jinwoo, 1: Kim Kahee, 2: Kim Taehee, 3: Lee Donghee
	
	print_node(head);
	(void)remove_index(4);
	(void)remove_index(2);	//0: Kim Jinwoo, 1: Kim Kahee, 2: Lee Donghee
	
	print_node(head);
	(void)find_item("Lee Donghee");	//Found!
	(void)find_item("Lee Donghe");	//Can't find!

	//case2. you wanna delete head
	(void)remove_item("Kim Jinwoo");

	//case3.
	(void)remove_item("Lee Donghee");

	//case1. can't find input in items
	(void)remove_item("Kim Kahe");

	//case1. not exist any node
	(void)remove_item("Kim Kahee");
	(void)remove_item("Kim Kahee");
	print_node(head);

	add_to_ordered_list("Lee");
	add_to_ordered_list("Kim");
	add_to_ordered_list("Woo");
	print_node(head);
}
#include <iostream>

using namespace std;

asm(".intel_syntax noprefix\n\t");

int main()
{
	const int size = 5;
	int** src = new int*[size];
	int** dst = new int*[size];

	for (size_t i = 0; i < size; ++i){
	src[i] = new int[size];
	dst[i] = new int[size];
	for (size_t j = 0; j < size; ++j){
	src[i][j] = rand() % 9;
	}
}

	for (size_t i = 0; i < size; ++i){
	for (size_t j = 0; j < size; ++j) 
	cout << src[i][j] << ' ';
	cout << endl;
	}
	cout << endl;

//for (size_t i = 0; i < size; ++i){
//	for (size_t j = 0; j < size; ++j){
//		dst[j][size - i - 1] = src[i][j];
//	}
//}

	asm(
		"	mov	rax, 0\n\t"	// i = 0
		".i_loop:\n\t"
		"	cmp	rax, rcx\n\t"
		"	jge	.EXIT\n\t"
		"	mov	rbx, 0\n\t"	// j = 0
		".j_loop:\n\t"
		"	cmp	rbx, rcx\n\t"
		"	jge	inc_i_loop\n\t"
		"	mov r9, [rsi + rax * 8]\n\t"  	// src[i]
		"	mov r8d, [r9 + rbx * 4]\n\t"   	// src[i][j]
		"	mov r10, rcx\n\t"				// size
		"	sub r10, rax\n\t"				// size - i
		"	sub r10, 1\n\t"					// size - i - 1
		"	mov r13, [rdi + rbx * 8]\n\t" 	// dst[j]
		"	mov [r13 + r10 * 4], r8d\n\t"  	// dst[j][size - i - 1]
		"	add	rbx, 1\n\t"	// ++j
		"	jmp	.j_loop\n\t"
		"inc_i_loop:\n\t"
		"	add	rax, 1\n\t"	// ++i
		"	jmp	.i_loop\n\t"
		".EXIT:\n\t"
		:
		: "S" (src), "D" (dst), "c" (size)
		:
	);

	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		cout << dst[i][j] << ' ';
		cout << endl;
	}

return 0;
}

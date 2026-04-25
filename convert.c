#include <stdlib.h>
#include <stdio.h>
#include <string>


int main(){

	//values will be input as a stream of bytes
	//These bytes will need to be converted into binary 
	char* map[16] ={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	FILE *out;
	out=fopen("output.txt", "w")
	if(out == NULL){
		fprintf(stderr, "\nError opened file\n");
		exit(-1);
	}	

	


}

char* handle_one(char* byte[8]){

	if(byte[0] == 1){
		
	}

}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



struct Car {

	char* car_name;
	int price;
	int max_speed;

};

void set_data(struct Car* car, char* name, int price, int max_speed){

	car->car_name = malloc(strlen(name)+1);

	strcpy(car->car_name, name);
	car->price = price;
	car->max_speed = max_speed;

}


int main(){
	


	FILE* fp;

	fp = fopen("test_file.txt", "r");

	int c = 0;
       
	while(c != EOF){
		c = fgetc(fp);
		printf("%c",c);

	}


	fclose(fp);



	return 0;
}

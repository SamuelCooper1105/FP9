#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

struct one{
    bool OVERDIVE;
    bool MALF;
    bool ref_pulse;
    bool ALDL_mode;
    bool dia_pos;
    bool aldl_pos;
    bool high_bat_volt;
    bool shigt_light;
};
struct two{
    char* PROMID_ONE[8];

};
struct three{
    char* PROMID_TWO[8];
};

struct four{
    int step_count;
};

struct five{
    int COOLANT_TEMP;
};

struct six{
    int MPH;
};
struct seven{
    int EGR_duty_cycle;
};

struct eight{
    int RPM;
};

struct nine{
    int THROTTLE_POS:
};

struct ten{
    int BPCLC;
};

struct eleven{
    int OXYGEN_SENSOR;
};

struct twelve{
    bool MAT_SENS;
    bool C22;
    bool C21;
    bool C16;
    bool C15;
    bool C14;
    bool C13;
    bool C12;
};

struct thirteen{
   // bool C35;
    bool C34;
    bool C33;
    bool C32;
    //bool C31;
    //bool C26;
    bool C25;
    bool C24;
};

struct fourteen{
    bool C51;
    bool C46;
    bool C45;
    bool C44;
    bool C43;
    bool C42;
    bool C41;
    bool C36;
};

struct fifteen{
    bool C54;
    bool C53;
    bool C52;
    bool C51;
};

struct sixteen{
    bool LCEF;
    bool VSSF;
    bool ES02RLF;
    bool RICH_LEANF;
    bool CLOSED_LOOPF;
};

struct seventeen{
    int temp;
};

struct eighteen{
    bool PARK_NET;
    bool NOT_THIRD;
    bool ODR;
    bool PS;
    bool EGR_DSC;
    bool TCC_LOCKED;
    bool FAN_REQ;
    bool AC_REQ;
};

struct nineteen{
    int OLDPA3;
};
struct twenty{
    int BLM;
};
struct twentyone{
    int ALDL_CHANGE_COUNTER;
};
struct twentytwo{
    char *AFR_MSB[8];
};
struct twentythree{
    char *AFR_LSB[8];
};
struct twentyfour{
    char *MSB_IBPW[8];
};
struct twentyfive{
    char *LSB_IBPW[8];
};

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
	//read until first white space
	
	int serial_port = open("/dev/ttyACM0", O_RDWR);

	if(serial_port < 0){
		perror("error opening serial port");
		return 1;
	}

	struct termios tty;

	togetattr(serial_port, &tty);
	cfsetispeed(&tty, B9600);
	cfsetopseed(&tty, B9600);
	tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~PARENB; // No parity    
	tty.c_cflag &= ~CSTOPB; // 1 stop bit    
	tty.c_cflag &= ~CSIZE;   // Clear the current char size mask    
	tty.c_cflag |= CS8;      // 8 data bits    
	tcsetattr(serial_port, TCSANOW, &tty);

	char read_buf[256];
	while(1){
		int num_bytes = read(serial_port, read_buf, sizeof(read_buf));
		if (num_bytes > 0){
			read_buf[num_bytes]='\0';
		}
	}
	close(serial_port);


	fclose(out);
	return 0;
}

char* handle_one(char* byte[8]){

	if(byte[0] == 1){
		
	}

}

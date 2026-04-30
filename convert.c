#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdbool.h>

struct one{
    bool OVERDRIVE;
    bool MALF;
    bool ref_pulse;
    bool ALDL_mode;
    bool dia_pos;
    bool aldl_pos;
    bool high_bat_volt;
    bool shigt_light;
};
struct two{
    char PROMID_ONE[9];

};
struct three{
    char PROMID_TWO[9];
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
    float EGR_duty_cycle;
};

struct eight{
    int RPM;
};

struct nine{
    int THROTTLE_POS;
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
    char AFR_MSB[9];
};
struct twentythree{
    char AFR_LSB[9];
};
struct twentyfour{
    char MSB_IBPW[9];
};
struct twentyfive{
    char LSB_IBPW[9];
};

void translate(char hex[3], char res[9]) {
    char* map[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    int im;
    int il;
    if(hex[0] >= '0' && hex[0] <= '9'){
        im = hex[0] - '0';

    }
    else if(hex[0] >= 'A' && hex[0] <= 'F'){
        im = hex[0] - 'A'+10;
    }
    if(hex[1] >= '0' && hex[1] <='9'){
        il = hex[1] - '0';
    }
    else if(hex[1] >= 'A' && hex[1] <= 'F'){
        il = hex[1] - 'A' +10;
    }
    strcpy(res,map[im]);
    strcat(res,map[il]);

}

struct one *handle_one(char byte[9]){
    struct one *one = malloc(sizeof(struct one));
    if(one==NULL){
        fprintf(stderr,"%s: could not allocate memory for one; %s\n", "one", strerror(errno));
        exit(-1);
    }
	if(byte[0] == '1'){
	    one->OVERDRIVE = 1;
	}
	else{
	    one->OVERDRIVE = 0;

	}

	if(byte[1] == '1'){
	    one->MALF = 1;
	}
	else{
	    one->MALF = 0;
	}

	if(byte[2] == '1'){
	    one->ref_pulse = 1;
	}
	else{
	    one->ref_pulse = 0;
	}

	if(byte[3] == '1'){
	    one->ALDL_mode = 1;
	}
	else{
	    one->ALDL_mode = 0;
	}

	if(byte[4] == '1'){
	    one->dia_pos = 1;
	}
	else{
	    one->dia_pos = 0;
	}

	if(byte[5] == '1'){
	    one->aldl_pos = 1;
	}
	else{
	    one->aldl_pos = 0;
	}

	if(byte[6] == '1'){
	    one->high_bat_volt = 1;
	}
	else{
	    one->high_bat_volt = 0;
	}

	if(byte[7] == '1'){
	    one->shigt_light = 1;
	}
	else{
	    one->shigt_light = 0;
	}

	return one;
}
struct two *handle_two(char byte[9]){
	struct two *two = malloc(sizeof(struct two));
    if(two==NULL){
        fprintf(stderr,"%s: could not allocate memory for two; %s\n", "two", strerror(errno));
        exit(-1);
    }
	strcpy(two->PROMID_ONE, byte);
	return two;
}
struct three *handle_three(char byte[9]){
	struct three *three = malloc(sizeof(struct three));
    if(three==NULL){
        fprintf(stderr,"%s: could not allocate memory for three; %s\n", "three", strerror(errno));
        exit(-1);
    }
	strcpy(three->PROMID_TWO, byte);
	return three;
}
struct four *handle_four(char byte[9]){
    struct four *four = malloc(sizeof(struct four));
    if(four==NULL){
        fprintf(stderr,"%s: could not allocate memory for four; %s\n", "four", strerror(errno));
        exit(-1);
    }
    int step =0;
    for(int i =0;i<8;i++){
        if(byte[i]=='1'){
            step |= (1 << i);
        }
    }
    four->step_count = step;
    return four;
}
struct five *handle_five(char byte[9]){
    struct five *five = malloc(sizeof(struct five));
    if(five==NULL){
        fprintf(stderr,"%s: could not allocate memory for five; %s\n", "five", strerror(errno));
        exit(-1);
    }
    int temp=0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            temp |= (1 << i);
        }
    }
    float coolant_temp = temp *(192.0f/256.0f) -40;
    five->COOLANT_TEMP = coolant_temp;

	return five;
}
struct six *handle_six(char byte[9]){
    struct six *six = malloc(sizeof(struct six));
    if(six==NULL){
        fprintf(stderr,"%s: could not allocate memory for six; %s\n", "six", strerror(errno));
        exit(-1);
    }
    int MPH =0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            MPH |= (1 << i);
        }
    }
    six->MPH = MPH;
    return six;
}
struct seven *handle_seven(char byte[9]){
    struct seven *seven = malloc(sizeof(struct seven));
    if(seven==NULL){
        fprintf(stderr,"%s: could not allocate memory for seven; %s\n", "seven", strerror(errno));
        exit(-1);
    }
    int EDR = 0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            EDR |= (1 << i);
        }
    }
    float EGR_duty_cycle = EDR * 2.56;
    seven->EGR_duty_cycle = EGR_duty_cycle;
    return seven;
}
struct eight *handle_eight(char byte[9]){
    struct eight *eight = malloc(sizeof(struct eight));
    if(eight==NULL){
        fprintf(stderr,"%s: could not allocate memory for eight; %s\n", "eight", strerror(errno));
        exit(-1);
    }
    int RPM = 0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            RPM |= (1 << i);
        }
    }
    RPM = RPM * 25;
    eight->RPM = RPM;
    return eight;
}
struct nine *handle_nine(char byte[9]) {
    struct nine *nine = malloc(sizeof(struct nine));
    if(nine==NULL){
        fprintf(stderr,"%s: could not allocate memory for nine; %s\n", "nine", strerror(errno));
        exit(-1);
    }
    int tmp = 0;
    for(int i =0;i<8;++i){
        if(byte[i] == '1'){
            tmp |= (1 << i);
        }
    }
    float TP = tmp * .0196;
    nine->THROTTLE_POS = TP;
    return nine;
}
struct ten *handle_ten(char byte[9]){
    struct ten *ten = malloc(sizeof(struct ten));
    if(ten==NULL){
        fprintf(stderr,"%s: could not allocate memory for ten; %s\n", "ten", strerror(errno));
        exit(-1);
    }
    int BP = 0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            BP |= (1 << i);
        }
    }

    ten->BPCLC = BP;
    return ten;
}
struct eleven *handle_eleven(char byte[9]){
    struct eleven *eleven = malloc(sizeof(struct eleven));
    if(eleven==NULL){
        fprintf(stderr,"%s: could not allocate memory for eleven; %s\n", "eleven", strerror(errno));
        exit(-1);
    }
    int tmp = 0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            tmp |= (1 << i);
        }
    }
    float OS = tmp * 4.44;
    eleven->OXYGEN_SENSOR = OS;
    return eleven;
}
struct twelve *handle_twelve(char byte[9]){
    struct twelve *twelve = malloc(sizeof(struct twelve));
    if(twelve==NULL){
        fprintf(stderr,"%s: could not allocate memory for twelve; %s\n", "twelve", strerror(errno));
        exit(-1);
    }
    if(byte[0] == '1'){
	    twelve -> MAT_SENS = 1;
	}
	else{
	    twelve->MAT_SENS = 0;
	}

	if(byte[1] == '1'){
	    twelve->C22 = 1;
	}
	else{
	    twelve->C22 = 0;
	}

	if(byte[2] == '1'){
	    twelve->C21 = 1;
	}
	else{
	    twelve->C21 = 0;
	}

	if(byte[4] == '1'){
	    twelve->C15 = 1;
	}
	else{
	    twelve->C15 = 0;
	}

	if(byte[5] == '1'){
	    twelve->C14 = 1;
	}
	else{
	    twelve->C14 = 0;
	}

	if(byte[6] == '1'){
	    twelve->C13 = 1;
	}
	else{
	    twelve->C13 = 0;
	}

	if(byte[7] == '1'){
	    twelve->C12 = 1;
	}
	else{
	    twelve->C12 = 0;
	}
	return twelve;
}
struct thirteen *handle_thirteen(char byte[9]){
    struct thirteen *thirteen = malloc(sizeof(struct thirteen));
    if(thirteen==NULL){
        fprintf(stderr,"%s: could not allocate memory for thirteen; %s\n", "thirteen", strerror(errno));
        exit(-1);
    }
    if(byte[1]=='1'){
        thirteen->C34=1;
    }
    else{
        thirteen->C34=0;
    }
    if(byte[2]=='1'){
        thirteen->C33=1;
    }
    else{
        thirteen->C33=0;
    }
    if(byte[3]=='1'){
        thirteen->C32=1;
    }
    else{
        thirteen->C32=0;
    }

    if(byte[6]=='1'){
        thirteen->C25=1;
    }
    else{
        thirteen->C25=0;
    }
    if(byte[7]=='1'){
        thirteen->C24=1;
    }
    else{
        thirteen->C24=0;
    }
    return thirteen;
}
struct fourteen * handle_fourteen(char byte[9]){
    struct fourteen *fourteen = malloc(sizeof(struct fourteen));
    if(fourteen==NULL){
        fprintf(stderr,"%s: could not allocate memory for fourteen; %s\n", "fourteen", strerror(errno));
        exit(-1);
    }
    if(byte[0]=='1'){
        fourteen->C51=1;
    }
    else{
        fourteen->C51=0;
    }
    if(byte[1]=='1'){
        fourteen->C46=1;
    }
    else{
        fourteen->C46=0;
    }
    if(byte[2]=='1'){
        fourteen->C45=1;
    }
    else{
        fourteen->C45=0;
    }
    if(byte[3]=='1'){
        fourteen->C44=1;
    }
    else{
        fourteen->C44=0;
    }
    if(byte[4]=='1'){
        fourteen->C43 = 1;
    }
    else{
        fourteen->C43 = 0;
    }
    if(byte[5]=='1'){
        fourteen->C42 = 1;
    }
    else{
        fourteen->C42 = 0;
    }
    if(byte[6]=='1'){
        fourteen->C41=1;
    }
    else{
        fourteen->C41=0;
    }
    if(byte[7]=='1'){
        fourteen->C36=1;
    }
    else{
        fourteen->C36=0;
    }
    return fourteen;
}
struct fifteen * handle_fifteen(char byte[9]){
    struct fifteen *fifteen = malloc(sizeof(struct fifteen));
    if(fifteen==NULL){
        fprintf(stderr,"%s: could not allocate memory for fifteen; %s\n", "fifteen", strerror(errno));
        exit(-1);
    }
    if(byte[4]=='1'){
        fifteen->C54=1;
    }
    else{
        fifteen->C54=0;
    }
    if(byte[5]=='1'){
        fifteen->C53=1;
    }
    else{
        fifteen->C53=0;
    }
    if(byte[6]=='1'){
        fifteen->C52=1;
    }
    else{
        fifteen->C52=0;
    }
    if(byte[7]=='1'){
        fifteen->C51=1;
    }
    else{
        fifteen->C51=0;
    }
    return fifteen;
}
struct sixteen * handle_sixteen(char byte[9]){
    struct sixteen *sixteen = malloc(sizeof(struct sixteen));
    if(sixteen==NULL){
        fprintf(stderr,"%s: could not allocate memory for sixteen; %s\n", "sixteen", strerror(errno));
        exit(-1);
    }
    if(byte[1]=='1'){
        sixteen->LCEF=1;
    }
    else{
        sixteen->LCEF=0;
    }
    if(byte[4]=='1'){
        sixteen->VSSF=1;
    }
    else{
        sixteen->VSSF=0;
    }
    if(byte[5]=='1'){
        sixteen->ES02RLF=1;
    }
    else{
        sixteen->ES02RLF=0;
    }
    if(byte[6]=='1'){
        sixteen->RICH_LEANF=1;
    }
    else{
        sixteen->RICH_LEANF=0;
    }
    if(byte[7]=='1'){
        sixteen->CLOSED_LOOPF=1;
    }
    else{
        sixteen->CLOSED_LOOPF=0;
    }
    return sixteen;
}
struct seventeen *handle_seventeen(char byte[9]) {
    struct seventeen *seventeen = malloc(sizeof(struct seventeen));
    if(seventeen==NULL){
        fprintf(stderr,"%s: could not allocate memory for seventeen; %s\n", "seventeen", strerror(errno));
        exit(-1);
    }
    // Convert binary string to integer
    int raw = (int)strtol(byte, NULL, 2);

    // Lookup table of known points {raw_value, temp}
    int lookup[][2] = {
        {0,   0},
        {33,  33},
        {46,  46},
        {56,  56},
        {64,  64},
        {71,  71},
        {77,  77},
        {83,  83},
        {90,  90},
        {96,  96},
        {104, 104},
        {111, 111},
        {119, 121},
        {133, 133},
        {149, 149},
        {178, 178},
        {240, 240}
    };
    int n = sizeof(lookup) / sizeof(lookup[0]);

    for (int i = 0; i < n; i++) {
        if (raw == lookup[i][0]) {
            seventeen->temp = lookup[i][1];
            seventeen->temp = seventeen->temp-40;
            return seventeen;
        }
    }

    if (raw < lookup[0][0]) {
        seventeen->temp = lookup[0][1];
        seventeen->temp = seventeen->temp-40;
        return seventeen;
    }


    if (raw > lookup[n-1][0]) {
        seventeen->temp = lookup[n-1][1];
        seventeen->temp = seventeen->temp-40;
        return seventeen;
    }

    for (int i = 0; i < n - 1; i++) {
        if (raw > lookup[i][0] && raw < lookup[i+1][0]) {
            int x0 = lookup[i][0],   y0 = lookup[i][1];
            int x1 = lookup[i+1][0], y1 = lookup[i+1][1];
            seventeen->temp = y0 + (raw - x0) * (y1 - y0) / (x1 - x0);
            seventeen->temp = seventeen->temp-40;
            return seventeen;
        }
    }

    return seventeen;
}
struct eighteen *handle_eighteen(char byte[9]) {
    struct eighteen *eighteen = malloc(sizeof(struct eighteen));
    if(eighteen==NULL){
        fprintf(stderr,"%s: could not allocate memory for eighteen; %s\n", "eighteen", strerror(errno));
        exit(-1);
    }
    if(byte[0]=='1'){
        eighteen->PARK_NET=1;
    }
    else{
        eighteen->PARK_NET=0;
    }
    if(byte[1]=='1'){
        eighteen->NOT_THIRD=1;
    }
    else{
        eighteen->NOT_THIRD=0;
    }
    if(byte[2]=='1'){
        eighteen->ODR=1;
    }
    else{
        eighteen->ODR=0;
    }
    if(byte[3]=='1'){
        eighteen->PS=1;
    }
    else{
        eighteen->PS=0;
    }
    if(byte[4]=='1'){
        eighteen->EGR_DSC=1;
    }
    else{
        eighteen->EGR_DSC=0;
    }
    if(byte[5]=='1'){
        eighteen->TCC_LOCKED=1;
    }
    else{
        eighteen->TCC_LOCKED=0;
    }
    if(byte[6]=='1'){
        eighteen->FAN_REQ=1;
    }
    else{
        eighteen->FAN_REQ=0;
    }
    if(byte[7]=='1'){
        eighteen->AC_REQ=1;
    }
    else{
        eighteen->AC_REQ=0;
    }
    return eighteen;
}

struct nineteen *handle_nineteen(char byte[9]) {
    struct nineteen *nineteen = malloc(sizeof(struct nineteen));
    if(nineteen==NULL){
        fprintf(stderr,"%s: could not allocate memory for nineteen; %s\n", "nineteen", strerror(errno));
        exit(-1);
    }
    int OLDPA3=0;
    for(int i =0; i<8;++i){
        if(byte[i]=='1'){
            OLDPA3 |= (1 << i);
        }
    }
    nineteen->OLDPA3 = OLDPA3;

    return nineteen;
}

struct twenty *handle_twenty(char byte[9]) {
    struct twenty *twenty = malloc(sizeof(struct twenty));
    if(twenty==NULL){
        fprintf(stderr,"%s: could not allocate memory for twenty; %s\n", "twenty", strerror(errno));
        exit(-1);
    }
    int BLM=0;
    for(int i =0; i<8;++i){
        if(byte[i]=='1'){
            BLM |= (1 << i);
        }
    }
    twenty->BLM = BLM;

    return twenty;
}

struct twentyone *handle_twentyone(char byte[9]) {
    struct twentyone *twentyone = malloc(sizeof(struct twentyone));
    if(twentyone==NULL){
        fprintf(stderr,"%s: could not allocate memory for twentyone; %s\n", "twentyone", strerror(errno));
        exit(-1);
    }
    int ALDL_CHANGE_COUNTER=0;
    for(int i =0; i<8;++i){
        if(byte[i]=='1'){
            ALDL_CHANGE_COUNTER |= (1 << i);
        }
    }
    twentyone->ALDL_CHANGE_COUNTER = ALDL_CHANGE_COUNTER;

    return twentyone;
}

struct twentytwo *handle_twentytwo(char byte[9]) {
    struct twentytwo *twentytwo = malloc(sizeof(struct twentytwo));
    if(twentytwo==NULL){
        fprintf(stderr,"%s: could not allocate memory for twentytwo; %s\n", "twentytwo", strerror(errno));
        exit(-1);
    }
    strcpy(twentytwo->AFR_MSB, byte);
    return twentytwo;
}

struct twentythree *handle_twentythree(char byte[9]) {
    struct twentythree *twentythree = malloc(sizeof(struct twentythree));
    if(twentythree==NULL){
        fprintf(stderr,"%s: could not allocate memory for twentythree; %s\n", "twentythree", strerror(errno));
        exit(-1);
    }
    strcpy(twentythree->AFR_LSB, byte);
    return twentythree;
}

struct twentyfour *handle_twentyfour(char byte[9]) {
    struct twentyfour *twentyfour = malloc(sizeof(struct twentyfour));
    if(twentyfour==NULL){
        fprintf(stderr,"%s: could not allocate memory for twentyfour; %s\n", "twentyfour", strerror(errno));
        exit(-1);
    }
    strcpy(twentyfour->MSB_IBPW, byte);
    return twentyfour;
}

struct twentyfive *handle_twentyfive(char byte[9]) {
    struct twentyfive *twentyfive = malloc(sizeof(struct twentyfive));
    if(twentyfive==NULL){
        fprintf(stderr,"%s: could not allocate memory for twentyfive; %s\n", "twentyfive", strerror(errno));
        exit(-1);
    }
    strcpy(twentyfive->LSB_IBPW, byte);
    return twentyfive;
}

int main(){

	//values will be input as a stream of bytes
	//output file for decoded values
	FILE *out;
	out=fopen("output.txt", "w");
	if(out == NULL){
		fprintf(stderr, "\nError opened file\n");
		exit(-1);
	}
	//open serial port
	int serial_port = open("/dev/ttyACM0", O_RDWR);

	if(serial_port < 0){
		perror("error opening serial port");
		return 1;
	}

	struct termios tty;
	//associates serial port with tty struct
	tcgetattr(serial_port, &tty);
	cfsetispeed(&tty, B115200);
	cfsetospeed(&tty, B115200);
	tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~PARENB; // No parity
	tty.c_cflag &= ~CSTOPB; // 1 stop bit
	tty.c_cflag &= ~CSIZE;   // Clear the current char size mask
	tty.c_cflag |= CS8;      // 8 data bits
	tty.c_lflag |= ICANON;
	tty.c_lflag &= ~(ECHO | ECHOE | ISIG);

	tty.c_iflag &= ~(IXON | IXOFF | IXANY);
	tty.c_iflag &= ~(ICRNL | INLCR | IGNCR);
	tty.c_oflag &= ~OPOST;
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 0;

	tcsetattr(serial_port, TCSANOW, &tty);

	char read_buf[256];
	while(1){
		memset(read_buf, 0, size(read_buf));
	    int p = 0;
		while(p < sizeof(read_buf)-1){
			char c;
			int n = read(serial_port, &c,1);
			if(n>0){
				if(c=='\n') break;
				if(c!='\r') read_buf[p++]=c;
			}
		}
		read_buf[p] = '\0';

		if(p ==0)continue;
		if(p<74){
			fprintf(stderr, "short frame (%d chars)\n",p);
			continue;
		}


        	printf("Line: '%s'\n", read_buf);
        	printf("Length: %d chars\n", p);

		char one_h[3];
		one_h[0] = read_buf[0];
		one_h[1] = read_buf[1];
		one_h[2] = '\0';
		char one_d[9];
		translate(one_h, one_d);
		struct one *one = handle_one(one_d);
		fprintf(out, "OVERDRIVE: %d\n", one->OVERDRIVE);
		fprintf(out, "MALF: %d\n", one->MALF);
		fprintf(out, "ref_pulse: %d\n", one->ref_pulse);
		fprintf(out, "ALDL_mode: %d\n", one->ALDL_mode);
		fprintf(out, "dia_pos: %d\n", one->dia_pos);
		fprintf(out, "aldl_pos: %d\n", one->aldl_pos);
		fprintf(out, "high_bat_volt: %d\n", one->high_bat_volt);
		fprintf(out, "shigt_light: %d\n", one->shigt_light);
		free(one);
		char two_h[3];
		two_h[0] = read_buf[3];
		two_h[1] = read_buf[4];
		two_h[2] = '\0';
		char two_d[9];
		translate(two_h, two_d);
		struct two *two = handle_two(two_d);
		fprintf(out, "PROMID_ONE: %s\n", two->PROMID_ONE);
		free(two);
		char three_h[3];
		three_h[0] = read_buf[6];
		three_h[1] = read_buf[7];
		three_h[2] = '\0';
		char three_d[9];
		translate(three_h,three_d);
		struct three *three = handle_three(three_d);
		fprintf(out,"PROMID_TWO: %s\n", three->PROMID_TWO);
		free(three);
		char four_h[3];
		four_h[0] = read_buf[9];
		four_h[1] = read_buf[10];
		four_h[2] = '\0';
		char four_d[9];
		translate(four_h,four_d);
		struct four *four = handle_four(four_d);
		fprintf(out,"step_count: %d\n",four->step_count);
		free(four);
		char five_h[3];
		five_h[0] = read_buf[12];
		five_h[1] = read_buf[13];
		five_h[2] = '\0';
		char five_d[9];
		translate(five_h,five_d);
		struct five *five = handle_five(five_d);
		fprintf(out,"COOLANT_TEMP: %d\n", five->COOLANT_TEMP);
		free(five);
		char six_h[3];
		six_h[0] = read_buf[15];
		six_h[1] = read_buf[16];
		six_h[2] = '\0';
		char six_d[9];
		translate(six_h,six_d);
		struct six *six = handle_six(six_d);
		fprintf(out,"MPH: %d\n", six->MPH);
		free(six);
		char seven_h[3];
		seven_h[0] = read_buf[18];
		seven_h[1] = read_buf[19];
		seven_h[2] = '\0';
		char seven_d[9];
		translate(seven_h,seven_d);
		struct seven *seven = handle_seven(seven_d);
		fprintf(out,"EGR_duty_cycle: %f\n", seven->EGR_duty_cycle);
		free(seven);
		char eight_h[3];
		eight_h[0] = read_buf[21];
		eight_h[1] = read_buf[22];
		eight_h[2] = '\0';
		char eight_d[9];
		translate(eight_h, eight_d);
		struct eight *eight = handle_eight(eight_d);
		fprintf(out,"RPM: %d\n", eight->RPM);
		free(eight);
		char nine_h[3];
		nine_h[0] = read_buf[24];
		nine_h[1] = read_buf[25];
		nine_h[2] = '\0';
		char nine_d[9];
		translate(nine_h, nine_d);
		struct nine *nine = handle_nine(nine_d);
		fprintf(out,"THROTTLE_POS: %d\n",nine->THROTTLE_POS);
		free(nine);
		char ten_h[3];
		ten_h[0] = read_buf[27];
		ten_h[1] = read_buf[28];
		ten_h[2] = '\0';
		char ten_d[9];
		translate(ten_h, ten_d);
		struct ten *ten = handle_ten(ten_d);
		fprintf(out,"BPCLC: %d\n", ten->BPCLC);
		free(ten);
		char eleven_h[3];
		eleven_h[0] = read_buf[30];
		eleven_h[1] = read_buf[31];
		eleven_h[2] = '\0';
		char eleven_d[9];
		translate(eleven_h,eleven_d);
		struct eleven *eleven = handle_eleven(eleven_d);
		fprintf(out,"OXYGEN_SENSOR: %d\n", eleven->OXYGEN_SENSOR);
		free(eleven);
		char twelve_h[3];
		twelve_h[0] = read_buf[33];
		twelve_h[1] = read_buf[34];
		twelve_h[2] = '\0';
		char twelve_d[9];
		translate(twelve_h,twelve_d);
		struct twelve *twelve = handle_twelve(twelve_d);
		fprintf(out,"MAT_SENS: %d\n", twelve->MAT_SENS);
		fprintf(out,"C22: %d\n", twelve->C22);
		fprintf(out,"C21: %d\n", twelve->C21);
		fprintf(out,"C15: %d\n", twelve->C15);
		fprintf(out,"C14: %d\n", twelve->C14);
		fprintf(out,"C13: %d\n", twelve->C13);
		fprintf(out,"C12: %d\n", twelve->C12);
		free(twelve);
		char thirteen_h[3];
		thirteen_h[0] = read_buf[36];
		thirteen_h[1] = read_buf[37];
		thirteen_h[2] = '\0';
		char thirteen_d[9];
		translate(thirteen_h,thirteen_d);
		struct thirteen *thirteen = handle_thirteen(thirteen_d);
		fprintf(out,"C34: %d\n", thirteen->C34);
		fprintf(out,"C33: %d\n", thirteen->C33);
		fprintf(out,"C32: %d\n", thirteen->C32);
		fprintf(out,"C25: %d\n", thirteen->C25);
		fprintf(out,"C24: %d\n", thirteen->C24);
		free(thirteen);
		char fourteen_h[3];
		fourteen_h[0] = read_buf[39];
		fourteen_h[1] = read_buf[40];
		fourteen_h[2] = '\0';
		char fourteen_d[9];
		translate(fourteen_h,fourteen_d);
		struct fourteen *fourteen = handle_fourteen(fourteen_d);
		fprintf(out,"C51: %d\n", fourteen->C51);
		fprintf(out,"C46: %d\n", fourteen->C46);
		fprintf(out,"C45: %d\n", fourteen->C45);
		fprintf(out,"C44: %d\n", fourteen->C44);
		fprintf(out,"C43: %d\n", fourteen->C43);
		fprintf(out,"C42: %d\n", fourteen->C42);
		fprintf(out,"C41: %d\n", fourteen->C41);
		fprintf(out,"C36: %d\n", fourteen->C36);
		free(fourteen);
		char fifteen_h[3];
		fifteen_h[0] = read_buf[42];
		fifteen_h[1] = read_buf[43];
		fifteen_h[2] = '\0';
		char fifteen_d[9];
		translate(fifteen_h,fifteen_d);
		struct fifteen *fifteen = handle_fifteen(fifteen_d);
		fprintf(out,"C54: %d\n", fifteen->C54);
		fprintf(out,"C53: %d\n", fifteen->C53);
		fprintf(out,"C52: %d\n", fifteen->C52);
		fprintf(out,"C51: %d\n", fifteen->C51);
		free(fifteen);
		char sixteen_h[3];
		sixteen_h[0] = read_buf[45];
		sixteen_h[1] = read_buf[46];
		sixteen_h[2] = '\0';
		char sixteen_d[9];
		translate(sixteen_h,sixteen_d);
		struct sixteen *sixteen = handle_sixteen(sixteen_d);
		fprintf(out,"LCEF: %d\n", sixteen->LCEF);
		fprintf(out,"VSSF: %d\n", sixteen->VSSF);
		fprintf(out,"ES02RLF: %d\n", sixteen->ES02RLF);
		fprintf(out,"RICH_LEANF: %d\n", sixteen->RICH_LEANF);
		fprintf(out,"CLOSED_LOOPF: %d\n", sixteen->CLOSED_LOOPF);
		free(sixteen);
		char seventeen_h[3];
		seventeen_h[0] = read_buf[48];
		seventeen_h[1] = read_buf[49];
		seventeen_h[2] = '\0';
		char seventeen_d[9];
		translate(seventeen_h,seventeen_d);
		struct seventeen *seventeen = handle_seventeen(seventeen_d);
		fprintf(out,"Temp: %d\n", seventeen->temp);
		free(seventeen);
		char eighteen_h[3];
		eighteen_h[0] = read_buf[51];
		eighteen_h[1] = read_buf[52];
		eighteen_h[2] = '\0';
		char eighteen_d[9];
		translate(eighteen_h,eighteen_d);
		struct eighteen *eighteen = handle_eighteen(eighteen_d);
		fprintf(out,"PARK_NET: %d\n", eighteen->PARK_NET);
		fprintf(out,"NOT_THIRD: %d\n", eighteen->NOT_THIRD);
		fprintf(out,"ODR: %d\n", eighteen->ODR);
		fprintf(out,"PS: %d\n", eighteen->PS);
		fprintf(out,"EGR_DSC: %d\n", eighteen->EGR_DSC);
		fprintf(out,"TCC_LOCKED: %d\n", eighteen->TCC_LOCKED);
		fprintf(out,"FAN_REQ: %d\n", eighteen->FAN_REQ);
		fprintf(out,"AC_REQ: %d\n", eighteen->AC_REQ);
		free(eighteen);
		char nineteen_h[3];
		nineteen_h[0] = read_buf[54];
		nineteen_h[1] = read_buf[55];
		nineteen_h[2] = '\0';
		char nineteen_d[9];
		translate(nineteen_h,nineteen_d);
		struct nineteen *nineteen = handle_nineteen(nineteen_d);
		fprintf(out,"OLDPA3: %d\n", nineteen->OLDPA3);
		free(nineteen);
		char twenty_h[3];
		twenty_h[0] = read_buf[57];
		twenty_h[1] = read_buf[58];
		twenty_h[2] = '\0';
		char twenty_d[9];
		translate(twenty_h,twenty_d);
		struct twenty *twenty = handle_twenty(twenty_d);
		fprintf(out,"BLM: %d\n", twenty->BLM);
		free(twenty);
		char twentyone_h[3];
		twentyone_h[0] = read_buf[60];
		twentyone_h[1] = read_buf[61];
		twentyone_h[2] = '\0';
		char twentyone_d[9];
		translate(twentyone_h,twentyone_d);
		struct twentyone *twentyone = handle_twentyone(twentyone_d);
		fprintf(out,"ALDL_CHANGE_COUNTER: %d\n", twentyone->ALDL_CHANGE_COUNTER);
		free(twentyone);
		char twentytwo_h[3];
		twentytwo_h[0] = read_buf[63];
		twentytwo_h[1] = read_buf[64];
		twentytwo_h[2] = '\0';
		char twentytwo_d[9];
		translate(twentytwo_h,twentytwo_d);
		struct twentytwo *twentytwo = handle_twentytwo(twentytwo_d);
		fprintf(out,"AFR_MSB: %s\n", twentytwo->AFR_MSB);
		free(twentytwo);
		char twentythree_h[3];
		twentythree_h[0] = read_buf[66];
		twentythree_h[1] = read_buf[67];
		twentythree_h[2] = '\0';
		char twentythree_d[9];
		translate(twentythree_h,twentythree_d);
		struct twentythree *twentythree = handle_twentythree(twentythree_d);
		fprintf(out,"AFR_LSB: %s\n", twentythree->AFR_LSB);
		free(twentythree);
		char twentyfour_h[3];
		twentyfour_h[0] = read_buf[69];
		twentyfour_h[1] = read_buf[70];
		twentyfour_h[2] = '\0';
		char twentyfour_d[9];
		translate(twentyfour_h,twentyfour_d);
		struct twentyfour *twentyfour = handle_twentyfour(twentyfour_d);
		fprintf(out,"MSB_IBPW: %s\n", twentyfour->MSB_IBPW);
		free(twentyfour);
		char twentyfive_h[3];
		twentyfive_h[0] = read_buf[72];
		twentyfive_h[1] = read_buf[73];
		twentyfive_h[2] = '\0';
		char twentyfive_d[9];
		translate(twentyfive_h,twentyfive_d);
		struct twentyfive *twentyfive = handle_twentyfive(twentyfive_d);
		fprintf(out,"LSB_IBPW: %s\n", twentyfive->LSB_IBPW);
		free(twentyfive);
		//break;
	}

	close(serial_port);
	fclose(out);
	return 0;
}

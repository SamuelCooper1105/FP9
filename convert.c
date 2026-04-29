#include <stdlib.h>
#include <stdio.h>
#include <string>

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
    float EGR_duty_cycle;
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


	fclose(out);

}

struct one *handle_one(char* byte[8]){

    struct one *one = malloc(sizeof(struct one));

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
	    one->ALDL_PULSE = 1;
	}
	else{
	    one->ALDL_PULSE = 0;
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

struct two *handle_two(char* byte[8]){
	struct two *two = malloc(sizeof(struct two));
	two->PROMID_ONE = byte;
	return two;
}

struct three *handle_three(char* byte[8]){
	struct three *three = malloc(sizeof(struct three));
	three->PROMID_TWO = byte;
	return three;
}

struct four *handle_four(char* byte[8]){
    struct four *four = malloc(sizeof(struct four));
    int step =0;
    for(int i =0, ;i<8;i++){
        if(byte[i]=='1'){
            step |= (1 << i);
        }
    }
    four->step = step;
    return four;
}

struct five *handle_five(char* byte[8]){
    struct five *five = malloc(sizeof(struct five));
    int temp=0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            temp |= (1 << i);
        }
    }
    temp = temp *(192/256) -40;
    five->COOLANT_TEMP = temp;

	return five;
}

struct six *handle_six(char* byte[8]){
    struct six *six = malloc(sizeof(struct six));
    int MPH =0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            MPH |= (1 << i);
        }
    }
    six->MPH = MPH;
    return six;
}
struct seven *handle_seven(char* byte[8]){
    struct seven *seven = malloc(sizeof(struct seven));
    int EGR_duty_cycle = 0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            EGR_duty_cycle |= (1 << i);
        }
    }
    float EGR_duty_cycle = EGR_duty_cycle * 2.56
    seven->EGR_duty_cycle = EGR_duty_cycle;
    return seven;
}

struct eight *handle_eight(char* byte[8]){
    struct eight *eight = malloc(sizeof(struct eight));
    int RPM = 0;
    for(int i = 0; i < 8; i++) {
        if(byte[i] == '1') {
            RPM |= (1 << i);
        }
    }
    eight->RPM = RPM;
    return eight;
}

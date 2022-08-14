#include <at89c5131.h>
//File used as it is from Lab-7
//with changes in serial_7.c in receive_char() func.
#include "lcd_7.h"              
#include "serial_7.c"

#include <stdio.h>
#include <string.h>

//Global variables
unsigned char inter_count = 0;
unsigned char time_out = 0;
int disp_flag = 1;
int num = 0;

unsigned char actual_num[]="8888888888";
unsigned char word_index[]="zzzzzzzzzz";
int k = 0;
int j = 0;

int ch = 0;
bit b0 = 0;
unsigned char state = 0;
unsigned char temp_state = 0;
unsigned char str[]="0123456789ABCDEFGHIJKLMNOPQRSTU";

//Display name function
//Left-side of || for displaying words 1st states wrt state
//Right-side of || for displaying words while taking input
//disp_flag to switch between left-side and right-side
void disp_name(void){
	if((state==0x00) || ((word_index[j]==str[0x00])&&(disp_flag==1)))
		lcd_write_string("alex");
	else if((state==0x01) || ((word_index[j]==str[0x01])&&(disp_flag==1)))
		lcd_write_string("kilo");
	else if((state==0x02) || ((word_index[j]==str[0x02])&&(disp_flag==1)))
		lcd_write_string("lola");
	else if((state==0x03) || ((word_index[j]==str[0x03])&&(disp_flag==1)))
		lcd_write_string("nova");
	else if((state==0x04) || ((word_index[j]==str[0x04])&&(disp_flag==1)))
		lcd_write_string("peru");
	else if((state==0x05) || ((word_index[j]==str[0x05])&&(disp_flag==1)))
		lcd_write_string("poem");
	else if((state==0x06) || ((word_index[j]==str[0x06])&&(disp_flag==1)))
		lcd_write_string("next");
	else if((state==0x07) || ((word_index[j]==str[0x07])&&(disp_flag==1)))
		lcd_write_string("news");
	else if((state==0x08) || ((word_index[j]==str[0x08])&&(disp_flag==1)))
		lcd_write_string("risk");
	else if((state==0x09) || ((word_index[j]==str[0x09])&&(disp_flag==1)))
		lcd_write_string("solo");
	else if((state==0x0A) || ((word_index[j]==str[0x0A])&&(disp_flag==1)))
		lcd_write_string("soda");
	else if((state==0x0B) || ((word_index[j]==str[0x0B])&&(disp_flag==1)))
		lcd_write_string("pump");
	else if((state==0x0C) || ((word_index[j]==str[0x0C])&&(disp_flag==1)))
		lcd_write_string("acid");
	else if((state==0x0D) || ((word_index[j]==str[0x0D])&&(disp_flag==1)))
		lcd_write_string("bank");
	else if((state==0x0E) || ((word_index[j]==str[0x0E])&&(disp_flag==1)))
		lcd_write_string("bali");
	else if((state==0x0F) || ((word_index[j]==str[0x0F])&&(disp_flag==1)))
		lcd_write_string("easy");
	else if((state==0x10) || ((word_index[j]==str[0x10])&&(disp_flag==1)))
		lcd_write_string("damn");
	else if((state==0x11) || ((word_index[j]==str[0x11])&&(disp_flag==1)))
		lcd_write_string("flex");
	else if((state==0x12) || ((word_index[j]==str[0x12])&&(disp_flag==1)))
		lcd_write_string("toga");
	else if((state==0x13) || ((word_index[j]==str[0x13])&&(disp_flag==1)))
		lcd_write_string("fame");
	else if((state==0x14) || ((word_index[j]==str[0x14])&&(disp_flag==1)))
		lcd_write_string("drum");
	else if((state==0x15) || ((word_index[j]==str[0x15])&&(disp_flag==1)))
		lcd_write_string("fish");
	else if((state==0x16) || ((word_index[j]==str[0x16])&&(disp_flag==1)))
		lcd_write_string("xray");
	else if((state==0x17) || ((word_index[j]==str[0x17])&&(disp_flag==1)))
		lcd_write_string("door");
	else if((state==0x18) || ((word_index[j]==str[0x18])&&(disp_flag==1)))
		lcd_write_string("zero");
	else if((state==0x19) || ((word_index[j]==str[0x19])&&(disp_flag==1)))
		lcd_write_string("cuba");
	else if((state==0x1A) || ((word_index[j]==str[0x1A])&&(disp_flag==1)))
		lcd_write_string("axis");
	else if((state==0x1B) || ((word_index[j]==str[0x1B])&&(disp_flag==1)))
		lcd_write_string("frog");
	else if((state==0x1C) || ((word_index[j]==str[0x1C])&&(disp_flag==1)))
		lcd_write_string("cave");
	else if((state==0x1D) || ((word_index[j]==str[0x1D])&&(disp_flag==1)))
		lcd_write_string("star");
	else if((state==0x1E) || ((word_index[j]==str[0x1E])&&(disp_flag==1)))
		lcd_write_string("tina");
}

//Initialize lfsr with non-zero state 
void init_lfsr(void){
	b0 = 1;
	state = 0x01;
}

//5-bit LFSR with period 31
void load_state(void){
	state = state>>1 ;
	state = state + ((b0^((state & 0x02)>>1))<<4); 
	b0 = (state & 0x01);
}

void start_game(void){
	
	int score = 0;
	int max_score = 0;
	
	while(1){
	lcd_cmd(0x80);
	lcd_write_string("Memory Game");
	msdelay(2000);
	lcd_cmd(0x01);
	disp_flag=0;
	for(k=0; k<10; k++){
		lcd_cmd(0x80);
		load_state();
		disp_name();
		word_index[k] = str[state];
		lcd_write_char(' ');
		
		load_state();
		num = state%10;
		lcd_write_char(str[num]);
		actual_num[k] = str[num];
		
		//1 sec delay
		msdelay(1000);
		lcd_cmd(0x01);
	}
	
	k = 0;
	lcd_cmd(0x80);
	lcd_write_string("Get Ready");
	msdelay(3000);
	lcd_cmd(0x01);
	
	j = 0;
	
	//Storing state elsewhere
	//So it dont interefere with disp_flag
	//in disp_name function
	temp_state = state;
	state = 0x22;		//Any non-possible value
	
	//Taking input
	disp_flag=1;
	for(j = 0; j<10; j++){
		lcd_cmd(0x80);
		disp_name();
		//start timer here :
		TR0 = 1;
		time_out = 0;
		ch = receive_char(&time_out);
		
		if(actual_num[j] == ch){
			score++;
		}
		
		lcd_cmd(0x0C0);
		lcd_write_char(ch);
		inter_count = 0;
		
		msdelay(1000);
		lcd_cmd(0x01);
	}
	
	if (max_score<=score){
		max_score = score;
	}
	
	//Displaying scores
	lcd_cmd(0x80);
	lcd_write_string("Score: ");
	lcd_write_string("     ");
	lcd_write_char(str[score]);
	lcd_cmd(0x0C0);
	lcd_write_string("High Score: ");
	lcd_write_char(str[max_score]);
	
	msdelay(3000);
	lcd_cmd(0x01);
	
	state = temp_state;
	score = 0;
	//max_score = 0;
	
}
}

//For 3 secs delay while taking input
// 
void interrupt_timer0(void) interrupt 1{
	inter_count = inter_count+1;
	if (inter_count==91){
		TH0 = 0x72;
		TL0 = 0x80;
	}
	else if (inter_count==92){
		TR0 = 0;
		time_out = 1;
	}
	else{
		TH0 = 0x00;
		TL0 = 0x00;
	}
}

void main(void){
	lcd_init();
	uart_init();
	init_lfsr();
	start_game();
}
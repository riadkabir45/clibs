#ifndef _STRING_EX_
#define _STRING_EX_


#include "stdlib.h"
#include "math.h"
#include "string.h"

void despace(char arg[]);
void cleanSpace(char arg[]);
void revstr(char *text);
void intstr(int val, char num[]);
int strint(char num[]);
bool chkstr(char atext[],char btext[]);
void strcpyex(char s[],char d[],int start,int dis);
int strfind(char s[],char t[],int n);
int sparse(char s[],char t[]);

void despace(char arg[]){
	int i = 0;
	int j = 0;
	while(arg[j] != '\0'){
		while(arg[j] == ' '){
			j++;
		}
		arg[i] = arg[j];
		j++;
		i++;
	}
	arg[i] = '\0';
}

void cleanSpace(char arg[]){
	int i = 0;
	int j = 0;
	while(arg[j] != '\0'){
		while(arg[j] == ' ' and arg[j+1] == ' ')
			j++;
		if(arg[j] == ' ' and arg[j+1] == '\0')
			break;
		if(i == 0 and arg[j] == ' ')
			j++;
		arg[i] = arg[j];
		i++;
		j++;
	}
	arg[i] = '\0';
}

void revstr(char *text){
	int n = strlen(text);
	char tmp[n+1];
	strcpy(tmp,text);
	for(int i = 0;i < n;i++)
	    text[i] = tmp[n-i-1];
}

void intstr(int val, char num[]){
	int n = 0;
	bool negetive = false;
	if(val == 0){
	    num[0] = '0';
	    num[1] = '\0';
	    return;
	}
	if(val < 0){
		val = abs(val);
		negetive = true;
	}
	while(val > 0){
		num[n] = val%10 + '0';
		val /= 10;
		n++;
	}
	
	if(negetive){
		num[n] = '-';
		n++;
	}
	num[n] = '\0';
	revstr(num);
}

bool chkstr(char atext[],char btext[]){
	bool state = true;
	for(int i = 0;atext[i] != '\0';i++){
	    for(int j = 0;btext[j] != '\0';j++){
	    	if(atext[i] == btext[j]){
	    		state = true;
	    		break;
	    	}else
	    	    state = false;
	    }
	    if(!state)
	    	return false;
	}
	return true;
}

int strint(char num[]){
	bool negetive = false;
	if(!chkstr(num,"-0123456789"))
	    return 0;
	int val = 0;
	if(num[0] == '-'){
		negetive = true;
	}
	strcpyex(num,num,1,strlen(num)-1);
	for(int i = 0;i < strlen(num);i++){
	    val *= 10;
	    val += num[i]-'0';
	}
	if(negetive)
		val = 0- val;
	return val;
}


void strcpyex(char s[],char d[],int start,int dis){
	if(dis < 1)
	    return;
	for(int i = 0;i < dis;i++)
	    d[i] = s[i+start];
	d[dis] = '\0';
}

int strfind(char s[],char t[],int n = 0){
	int tn = 0;
	char tmp[strlen(t)+1];
	for(int i = 0;i < strlen(s)-strlen(t)+1;i++){
		strcpyex(s,tmp,i,strlen(t));
		if(!strcmp(tmp,t))
			if(n == tn)
				return i;
			else
				tn++;
	}
	return -1;
}


#endif

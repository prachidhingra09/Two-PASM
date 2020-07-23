#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
    authors:    iimashfaaq
                prachidhingra09
*/

void strreverse(char* begin, char* end) {
	char aux;
	while(end>begin)
		aux=*end, *end--=*begin, *begin++=aux;
}
void itoa(int value, char* str, int base) {
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char* wstr=str;
	int sign;
	div_t res;

	// Validate base
	if (base<2 || base>35){ *wstr='\0'; return; }

	// Take care of sign
	if ((sign=value) < 0) value = -value;

	// Conversion. Number is reversed.
	do {
		res = div(value,base);
		*wstr++ = num[res.rem];
	}while(value=res.quot);
	if(sign<0) *wstr++='-';
	*wstr='\0';

	// Reverse string
	strreverse(str,wstr-1);
}

void main() {
	char a[10],ad[10],label[10],opcode[10],operand[10],mnemonic[10],symbol[10];
	int i,address,sa,code,add,len,actual_len,tcount=10;
	FILE *fp1,*fp2,*fp3,*fp4,*fp5;
	fp1=fopen("asmlist.dat","w");
	fp2=fopen("symtab.dat","r");
	fp3=fopen("intermediate.dat","r");
	fp4=fopen("opTab.dat","r");
	fp5=fopen("out.dat","w");
	fscanf(fp3,"%s%s%s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		fprintf(fp1,"\t%s\t%s\t%s\n",label,opcode,operand);
		fprintf(fp5, "H%6s%6s26",label,operand );
		fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
		sa=address;
	}
	while(strcmp(opcode,"END")!=0)
	{
		if(strcmp(opcode,"BYTE")==0)
		{
		fprintf(fp1,"%d\t%s\t%s\t%s\t",address,label,opcode,operand);
		len=strlen(operand);
		actual_len=len-3;
		for(i=2;i<(actual_len+2);i++)
		{
			itoa(operand[i],ad,16);
			fprintf(fp1,"%s",ad);
		}
		fprintf(fp1,"\n");
		}
		else if(strcmp(opcode,"WORD")==0)
		{
		len=strlen(operand);
		itoa(atoi(operand),a,10);
		fprintf(fp1,"%d\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,a);
		}
		else if((strcmp(opcode,"RESB")==0)||(strcmp(opcode,"RESW")==0))
		{
		fprintf(fp1,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);

		}
		else
		{
		rewind(fp4);
		fscanf(fp4,"%s%d",mnemonic,&code);
		while(strcmp(opcode,mnemonic)!=0)
		fscanf(fp4,"%s%d",mnemonic,&code);
		if(strcmp(operand,"~")==0)
		{
			fprintf(fp1,"%d\t%s\t%s\t%s\t%d0000\n",address,label,opcode,operand,code);
					if (tcount==10){
							fprintf(fp5, "\nT%d%d%d0000",address,00,code );
							tcount=0;
					}else{
							fprintf(fp5, "%d0000",code );
							tcount++;
					}

		}
		else
		{
			rewind(fp2);
			fscanf(fp2,"%s%d",symbol,&add);
			while(strcmp(operand,symbol)!=0)
			{
			fscanf(fp2,"%s%d",symbol,&add);
			}
			fprintf(fp1,"%d\t%s\t%s\t%s\t%d%d\n",address,label,opcode,operand,code,add);
			//fprintf(fp5, "T%d%d%d%d\n",address,00,code,add );
					if (tcount==10){
							fprintf(fp5, "\nT%d%d%d%d",address,00,code,add );
							tcount=0;
					}else{
							fprintf(fp5, "%d%d",code,add );
							tcount++;
					}
		}
		}
		fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
	}
	fprintf(fp1,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
	fprintf(fp5, "\nE%6d\n",sa );
	printf("Finished");
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	getchar();
}
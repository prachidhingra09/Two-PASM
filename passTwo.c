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
		aux = *end, *end--= *begin, *begin++ = aux;
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
	}while(value = res.quot);
	if(sign<0) *(wstr++)='-';
	*wstr='\0';

	// Reverse string
	strreverse(str,wstr-1);
}

void main()

{
	char a[10],ad[10],label[10],opcode[10],operand[10],mnemonic[10],symbol[10];
	int i, address, sa, code, add, len, actual_len, bcount=10;
	FILE *asmFile, *symTab, *interFile, *opTab, *output;
	
	asmFile = fopen("asmlist.txt","w");
	symTab = fopen("symtab.txt","r");
	interFile = fopen("intermediate.txt","r");
	opTab = fopen("opTab.txt","r");
	output = fopen("out.txt","w");

	fscanf(interFile,"%s%s%s",label,opcode,operand);

	if(strcmp(opcode,"START")==0)
	{
		fprintf(asmFile,"\t%s\t%s\t%s\n",label,opcode,operand);
		fprintf(output, "H%6s%6s26",label,operand );
		fscanf(interFile,"%d%s%s%s",&address,label,opcode,operand);
		sa=address;
	}
	while(strcmp(opcode,"END")!=0)
	{
		if(strcmp(opcode,"BYTE")==0)
		{
		fprintf(asmFile,"%d\t%s\t%s\t%s\t",address,label,opcode,operand);
		len=strlen(operand);
		actual_len=len-3;
		for(i=2;i<(actual_len+2);i++)
		{
			strcpy(ad, itoa(operand[i],ad,16));
			fprintf(asmFile,"%s",ad);
		}
		fprintf(asmFile,"\n");
		}
		else if(strcmp(opcode,"WORD")==0)
		{
		len=strlen(operand);
		strcpy(a, itoa(atoi(operand),a,10));
		fprintf(asmFile,"%d\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,a);
		}
		else if((strcmp(opcode,"RESB")==0)||(strcmp(opcode,"RESW")==0))
		{
		fprintf(asmFile,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);

		}
		else
		{
		rewind(opTab);
		fscanf(opTab,"%s%d",mnemonic,&code);
		while(strcmp(opcode,mnemonic)!=0)
		fscanf(opTab,"%s%d",mnemonic,&code);
		if(strcmp(operand,"~")==0)
		{
			fprintf(asmFile,"%d\t%s\t%s\t%s\t%d0000\n",address,label,opcode,operand,code);
					if (bcount==10){
							fprintf(output, "\nT%d%d%d0000",address,00,code );
							bcount=0;
					}else{
							fprintf(output, "%d0000",code );
							bcount++;
					}

		}
		else
		{
			rewind(symTab);
			fscanf(symTab,"%s%d",symbol,&add);
			while(strcmp(operand,symbol)!=0)
			{
			fscanf(symTab,"%s%d",symbol,&add);
			}
			fprintf(asmFile,"%d\t%s\t%s\t%s\t%d%d\n",address,label,opcode,operand,code,add);
			//fprintf(output, "T%d%d%d%d\n",address,00,code,add );
					if (bcount==10){
							fprintf(output, "\nT%d%d%d%d",address,00,code,add );
							bcount=0;
					}else{
							fprintf(output, "%d%d",code,add );
							bcount++;
					}
		}
		}
		fscanf(interFile,"%d%s%s%s",&address,label,opcode,operand);
	}
	fprintf(asmFile,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
	fprintf(output, "\nE%6d\n",sa );
	printf("Finished");
	
	fclose(asmFile);
	fclose(symTab);
	fclose(interFile);
	fclose(opTab);
    fclose(output);
    
	getchar();
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
    authors:    iimashfaaq
                prachidhingra09
*/

int main() {
    char opcode[10],mnemonic[3],operand[10],label[10],code[10];
    int locctr,start,length;
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("input.dat","r");
    fp2=fopen("symtab.dat","w");
    fp3=fopen("intermediate.dat","w");
    fp4=fopen("opTab.dat","r");

    // scan the first line (should be start)
    fscanf(fp1,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        start=atoi(operand);  // Get starting address
        locctr=start; // set locctr as the starting address

        //print to output and scan next line from input
        fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1,"%s%s%s",label,opcode,operand);
    }
    else
        // No start opcode, take locctr as 0
        locctr=0;


    while(strcmp(opcode,"END")!=0)
    {
        fprintf(fp3,"%d\t",locctr);
        if(strcmp(label,"~")!=0)
        fprintf(fp2,"%s\t%d\n",label,locctr);

        rewind(fp4);  // goto beginning of file
        fscanf(fp4,"%s",code);  // scan first code
        while(strcmp(code,"END")!=0)  // check for end opcode
        {
        if(strcmp(opcode,code)==0)  // compare all opcodes
        {
            locctr+=3;  // 3 bytes
            break;
        }
        fscanf(fp4,"%s",code);
        }
        if(strcmp(opcode,"WORD")==0)
        locctr+=3;  // 1 word = 3 byte
        else if(strcmp(opcode,"RESW")==0)
        locctr+=(3*(atoi(operand)));  // n words
        else if(strcmp(opcode,"RESB")==0)
        locctr+=(atoi(operand));  // n bytes
        else if(strcmp(opcode,"BYTE")==0)
        ++locctr; // 1 byte

        //print to output and scan next line from input
        fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1,"%s%s%s",label,opcode,operand);
    }

    // END opcode
    fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    length=locctr-start;
    printf("The length of the program is %d",length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    getchar();
    return 0;
}
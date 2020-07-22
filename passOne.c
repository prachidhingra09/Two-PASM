#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
    authors:    iimashfaaq
                prachidhingra09
*/

int main()
{
    char opcode[10],mnemonic[3],operand[10],label[10],code[10];
    int locctr,start,length;
    FILE *inpFile,*symTab,*interFile,*opTab;
    inpFile=fopen("./files/input.txt","r");
    symTab=fopen("./files/symTab.txt","w");
    interFile=fopen("./files/intermediate.txt","w");
    opTab=fopen("./files/opTab.txt","r");

    // scan the first line (should be start)
    fscanf(inpFile,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        start=atoi(operand);  // Get starting address
        locctr=start; // set locctr as the starting address

        //print to output and scan next line from input
        fprintf(interFile,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(inpFile,"%s%s%s",label,opcode,operand);
    }
    else
        // No start opcode, take locctr as 0
        locctr=0;


    while(strcmp(opcode,"END")!=0)
    {
        fprintf(interFile,"%d\t",locctr);
        if(strcmp(label,"~")!=0)
        fprintf(symTab,"%s\t%d\n",label,locctr);

        rewind(opTab);  // goto beginning of file
        fscanf(opTab,"%s",code);  // scan first code
        while(strcmp(code,"END")!=0)  // check for end opcode
        {
        if(strcmp(opcode,code)==0)  // compare all opcodes
        {
            locctr+=3;  // 3 bytes
            break;
        }
        fscanf(opTab,"%s",code);
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
        fprintf(interFile,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(inpFile,"%s%s%s",label,opcode,operand);
    }

    // END opcode
    fprintf(interFile,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    length=locctr-start;
    printf("The length of the program is %d",length);

    fclose(inpFile);
    fclose(symTab);
    fclose(interFile);
    fclose(opTab);

    getchar();
    return 0;
}

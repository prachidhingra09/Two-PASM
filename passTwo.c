#include <stdio.h>
#include <string.h>

/*
    authors:    iimashfaaq
                prachidhingra09
*/

int main() {
    FILE *inp, *symTab, *opTab , *length;
    char address[20],label[20],mnemonic[20],operand[20],start[20],opmne[20],op[20],symtab[20],symadd[20];
    int len,i;
    //clrscr();
    inp = fopen("inp.txt","r");
    symTab = fopen("symTab.txt","r");
    opTab = fopen("opTab.txt","r");
    length = fopen("len.txt","r");

    fscanf(inp,"%s%s%s%s",address,label,mnemonic,operand);
    printf("\n%s %s %s %s",address,label,mnemonic,operand);

    if(strcmp(mnemonic,"START") == 0)
    {
        strcpy(start,operand);
        fscanf(length,"%d",&len);
    }
    printf("\nH^%s^%s^%d\nT^00%s^",label,start,len,start);
    fscanf(inp,"%s%s%s%s",address,label,mnemonic,operand);
    while(strcmp(mnemonic,"END")!=0)
    {
        fscanf(opTab,"%s%s",opmne,op);
        while(!feof(opTab))  
        {
            if(strcmp(mnemonic,opmne)==0)
            {
                fclose(opTab);
                fscanf(symTab,"%s%s",symadd,symtab);
                while(!feof(symTab))
                {
                    if(strcmp(operand,symtab)==0)   
                    {
                        printf("%s%s^",op,symadd);
                        break;
                    }
                    else
                        fscanf(symTab,"%s%s",symadd,symtab);
                }
                break;
            }
            else
                fscanf(opTab,"%s%s",opmne,op);
        }
        if((strcmp(mnemonic,"BYTE")==0)||(strcmp(mnemonic,"WORD")==0))
        {
           if(strcmp(mnemonic,"WORD")==0)
               printf("0000%s^",operand);
            else
            {
                len=strlen(operand);
                for(i=2;i<len;i++)
                {
                   printf("%d",operand[i]);
                }
                printf("^");
            }
        }
        fscanf(inp,"%s%s%s%s",address,label,mnemonic,operand);
        opTab=fopen("opTab.txt","r");
        fseek(opTab,SEEK_SET,0);
    }
    printf("\nE^00%s",start);
    fclose(inp);
    fclose(opTab);
    fclose(symTab);
    fclose(length);
    //fclose(fout);

    //getch();
    //getline();
    return 0;
}

#include <stdio.h>
#include <string.h>

/*
    authors:    iimashfaaq
                prachidhingra09
*/

int main() {
    FILE *inp, *symTab, *opTab;
    int locationCounter,startAddr,l,opAddr,o,len;
    char mnemonic[20],label[20],operation[20],otp[20];
    //clrscr();
    
    inp = fopen("input.txt","r");
    symTab = fopen("symtab.txt","w");
    
    fscanf(inp,"%s %s %d",label,mnemonic,&opAddr);
    
    if(strcmp(mnemonic,"START") == 0)
    {
            startAddr = opAddr;
            locationCounter = startAddr;
            printf("\t%s\t%s\t%d\n",label,mnemonic,opAddr);
    }
    else
            locationCounter = 0;
    
    fscanf(inp,"%s %s",label,mnemonic);
    
    while(!feof(inp))
    {
        fscanf(inp,"%s",operation);
        printf("\n%d\t%s\t%s\t%s\n",locationCounter,label,mnemonic,operation);
        
        if(strcmp(label,"-") != 0)
        {
            fprintf(symTab,"\n%d\t%s\n",locationCounter,label);
        }
        
        opTab = fopen("optab.txt","r");
        fscanf(opTab,"%s %d",otp,&o);
        
        while(!feof(opTab))
        {
            if(strcmp(mnemonic,otp) == 0)
            {
                locationCounter = locationCounter + 3;
                break;
            }
            fscanf(opTab,"%s %d",otp,&o);
        }
        
        fclose(opTab);
        
        if(strcmp(mnemonic,"WORD") == 0)
        {
            locationCounter = locationCounter + 3;
        }
        else if(strcmp(mnemonic,"RESW") == 0)
        {
            opAddr = atoi(operation);
            locationCounter = locationCounter + (3 * opAddr);
        }
        else if(strcmp(mnemonic,"BYTE") == 0)
        {
            if(operation[0] == 'X')
            locationCounter = locationCounter + 1;
            else
            {
                len = strlen(operation) - 2;
                locationCounter = locationCounter + len;
                
            }
        }
        else if(strcmp(mnemonic,"RESB") == 0)
        {
            opAddr = atoi(operation);
            locationCounter = locationCounter + opAddr;
        }
        fscanf(inp,"%s%s",label,mnemonic);
    }
    
    if(strcmp(mnemonic,"END") == 0)
    {
        printf("Program length =%d\n\n",locationCounter - startAddr);
    }
    fclose(inp);
    fclose(symTab);
    //getch();
    return 0;
}

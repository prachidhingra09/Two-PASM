#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    authors:    iimashfaaq
                prachidhingra09
*/

int main() {
    FILE *inp, *symTab, *opTab, *interFile;
    int locationCounter, startAddr, opAddr, o, len;
    char mnemonic[20], label[20], operation[20], code[20];
    //clrscr();
    
    inp = fopen("./files/input.txt","r");
    symTab = fopen("./files/symtab.txt","w");
    interFile = fopen("./files/intermediate.txt", "w");

    fscanf(inp,"%s %s %d",label,mnemonic,&opAddr);
    
    if(strcmp(mnemonic,"START") == 0)
    {
        startAddr = opAddr;
        locationCounter = startAddr;
        fprintf(interFile,"%s\t%s\t%d\n",label,mnemonic,opAddr);
        fscanf(inp,"%s %s %s",label,mnemonic, operation);
    }
    else
        locationCounter = 0;
    
    while(strcmp(mnemonic,"END")!=0)
    {
        // fscanf(inp,"%s",operation);
        printf("\n%d\t%s\t%s\t%s\n",locationCounter,label,mnemonic,operation);
        
        if(strcmp(label,"~") != 0)
        {
            fprintf(symTab,"\n%s\t%d\n",label, locationCounter);
        }
        
        opTab = fopen("./files/opTab.txt","r");
        fscanf(opTab,"%s %d",code,&o);
        
        while(strcmp(code,"END")!=0)
        {
            if(strcmp(mnemonic,code) == 0)
            {
                locationCounter += 3;
                break;
            }
            fscanf(opTab,"%s %d",code,&o);
        }
        
        if(strcmp(mnemonic,"WORD") == 0) {
            locationCounter += 3;
        }
        else if(strcmp(mnemonic,"RESW") == 0) {
            opAddr = atoi(operation);
            locationCounter += (3 * opAddr);
        }
        else if(strcmp(mnemonic,"BYTE") == 0) {
            ++locationCounter;
        }
        else if(strcmp(mnemonic,"RESB") == 0) {
            opAddr = atoi(operation);
            locationCounter += opAddr;
        }
        fprintf(interFile,"%s\t%s\t%s\n",label,mnemonic,operation);
        fscanf(inp,"%s%s%s",label, mnemonic, operation);
    }
    
    fprintf(interFile,"%d\t%s\t%s\t%s\n",locationCounter,label,mnemonic,operation);
    printf("Program length = %d\n\n",locationCounter - startAddr);

    fclose(opTab);
    fclose(inp);
    fclose(symTab);
    fclose(interFile);
    //getch();
    return 0;
}

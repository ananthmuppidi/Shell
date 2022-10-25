#include "../Headers/root.h"
void pinfo(char command[])
{

    char tokenizedInput[MAX_TOKENS][MAX_TOKEN_SIZE];
    int tokens = tokenizeAnd(command, tokenizedInput);

    char tempProc[100] = {'\0'};
    char exec[100] = {'\0'};

    int calcPid;
    if(tokens == 1) calcPid = shellPid;
    else calcPid = atoi(tokenizedInput[1]);
   
    sprintf(tempProc, "/proc/%d/stat", shellPid);
    sprintf(exec, "/proc/%d/exe", shellPid);

    FILE *fp = fopen(tempProc, "r");
    FILE *fp2 = fopen(exec, "r");

    if (tokens == 1)
    {

        char read[10000];
        fread(read, sizeof(char), 10000, fp);
        fclose(fp);

        char readTokens[1000][1000];
        int stuff = tokenizeSpace(read, readTokens);

        printf("pid - %d\n", shellPid);
        printf("process - %s\n", readTokens[2]);
        printf("memory - %s\n", readTokens[22]);

        char temp[10000];
        readlink(exec, temp, 10000);
        fclose(fp2);


        printf("executable - %s\n", temp);

       
    } else {
        printf("shell : pinfo : too many args");
        return;
    }
}
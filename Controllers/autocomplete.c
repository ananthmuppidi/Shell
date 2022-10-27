#include "../Headers/root.h"


int compare (const void * a, const void * b) {
    size_t fa = strlen((const char *)a);
    size_t fb = strlen((const char *)b);
    return (fa > fb) - (fa < fb);
}




void autoComplete(char command[], int len)
{

    char options[1000][1000];
    int idx = 0;

    int entities = 0;

    char path[10000];
    getCurrDir(path);

    char temp[10102] = {'\0'};
    char lastCommand[10102] = {'\0'};

    DIR *dp;
    dp = opendir(path);
    struct dirent **ep;
    int n;

    n = scandir(path, &ep, 0, alphasort);

    for (int i = 0; i < n; i++)
    {

        char fullPath[MAX_PATH_SIZE];
        strcpy(fullPath, path);

        if (fullPath[strlen(fullPath) - 1] != '/')
        {
            strcat(fullPath, "/");
            strcat(fullPath, ep[i]->d_name);
        }
        else
        {
            strcat(fullPath, ep[i]->d_name);
        }
        struct stat stats;
        if (stat(fullPath, &stats) == -1)
        {
            continue;
        }
        sprintf(options[idx++], "%s", ep[i]->d_name);
    }

    if (len)
    {
        
        for (int i = len - 1; i >= 0; i--)
        {
            if (command[i] != ' ')
                temp[len - i - 1] = command[i];
            else
                break;
        }

        for (int i = 0; i < strlen(temp); i++)
        {
            lastCommand[i] = temp[strlen(temp) - 1 - i];
        }

        if(!strlen(lastCommand)){
            return;
        }
        
    }
    else
    {
        promptUser();

        return;
    }

    if (!strlen(lastCommand))
    {
        DIR *dp;
        dp = opendir(path);
        struct dirent **ep;
        int n;

        n = scandir(path, &ep, 0, alphasort);

        for (int i = 0; i < n; i++)
        {

            char fullPath[MAX_PATH_SIZE];
            strcpy(fullPath, path);

            if (fullPath[strlen(fullPath) - 1] != '/')
            {
                strcat(fullPath, "/");
                strcat(fullPath, ep[i]->d_name);
            }
            else
            {
                strcat(fullPath, ep[i]->d_name);
            }
            struct stat stats;
            if (stat(fullPath, &stats) == -1)
            {
                continue;
            }
            sprintf(options[idx++], "%s", ep[i]->d_name);
        }

        for (int i = 0; i < idx; i++)
        {
            printf("%s\n", options[i]);
        }
        promptUser();
        return;
    }

    char matchedOptions[1000][1000];
    int matches = 0;
    for (int i = 0; i < idx; i++)
    {
        if (!strncmp(lastCommand, options[i], strlen(lastCommand)))
        {

            sprintf(matchedOptions[matches++], "%s", options[i]);
        }
    }
    if(matches == 0){
        return;
    }
    if (matches == 1)
    {
    
        // here we need to make the prompt the same as the only matching option
        // we will only have the last thing matching, we just need to finsh it
        int iterator = 0;

        while (command[iterator++] != '\0'){}
        while (command[--iterator] != ' '){}
        iterator++;
        char out[1000] = {'\0'};
        int outIdx = 0;

        char temp[1000];
        strcpy(temp, command);

        for (int j = 0; j < strlen(matchedOptions[0]); j++)                         
        {
            command[iterator++] = matchedOptions[0][j];
        }
        command[iterator] = '\0';
        int tempIdx = 0;
        while(temp[tempIdx] == command[tempIdx]){
            tempIdx++;
        }

        while(command[tempIdx] != '\0'){

            out[outIdx++] = command[tempIdx++];
        }
        
        out[outIdx] = '\0';
        printf("%s", out);
        return;
    }
    else if(matches > 1)
    {
        printf("\n");
	qsort(matchedOptions, matches, 1000, compare);
        for(int i = 0; i < matches; i++ ){
            printf("%s\n", matchedOptions[i]);
        }

        char c;
        char matched[1000];
        int index = 0;
        memset(matched, 1000, '\0');


	int flag = 0;
        
       	for(int i = 0; i < strlen(matchedOptions[0]); i++){
		c = matchedOptions[0][i];
		for(int j = 0; j < matches; j++){
			if(matchedOptions[j][i] != c){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			matched[index++] = c;
		}
	}
	matched[index] = '\0';
    int iterator = 0;

        while (command[iterator++] != '\0'){}
        while (command[--iterator] != ' '){}
        iterator++;
        // now we are at the part that we need to autocomplete

        int iterator2 = 0;
        while(command[iterator] == matched[iterator2]){
            iterator++;
            iterator2++;
        }

        while(matched[iterator2] != '\0'){
            command[iterator++] = matched[iterator2++];
        }
        command[iterator] = '\0';
       

    
    


        promptUser();
        fflush(stdout);
        autocompleted = 1;
 
    }

    promptUser();

    return;
}

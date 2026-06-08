#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
int main(){
    bool stop = false;
    int ch;
    while(stop == false){
    size_t capacity = 10;
    size_t capacity2 = 10;
    size_t capacity3 = 10;
    size_t capacity4 = 10;
    size_t capacity5 = 10;
    //size_t length = 0;
    char *before = malloc(capacity*sizeof(char));//malloc
    char *after = malloc(capacity2*sizeof(char));//malloc
    char **argv = malloc(capacity3*sizeof(char *));//malloc
    char **argv_before = malloc(capacity4*sizeof(char *));//malloc
    char **argv_after = malloc(capacity5*sizeof(char *));//malloc
    char *command = NULL;
    size_t len = 0;
    bool pipe_found = false;    
    bool ampersand = false;
    printf("Your command>");
    fflush(stdout);
    ssize_t n = getline(&command, &len, stdin);
    if(n==-1){
        perror("No arguments.\n");
        continue;
    }

    if(command[n-1]=='\n'){
        command[n-1]='\0';
    }
   
   
    //if pipe is true, split command array into separate arrays. otherwise pipe is false and use original command array.
    for (int i=0; i<n;i++){
        if(command[i] == '|'){
            pipe_found = true;
            for(int a=0; a<i; a++){
                //realloc
                if(a==capacity-1){
                    capacity = capacity*2;
                    before = realloc(before, capacity*sizeof(char));
                }
                before[a] = command[a];
            }
            before[i] = '\0';
            int c=0;
            for(int b=i+1; b<n; b++){
                //realloc
                if(b==capacity2-1){
                    capacity2 = capacity2*2;
                    after = realloc(after, capacity2*sizeof(char));
                }
                after[c++] = command[b];
            }
            after[c] = '\0';
            break;
        
        }
    }
    //checking for ampersand. Note: if before and after are not initialized due to no pipe,
    //then check will return false in first 2 loops, but ampersand should be found in third loop.
    if(pipe_found == true){
    for(int i=0; i<n;i++){
        if(before[i] == '&'){
            ampersand = true;
        }
    }
}
    if(pipe_found == true){
    for(int i=0; i<n;i++){
        if(after[i] == '&'){
            ampersand = true;
        }
    }
}
    if(pipe_found == false){
    for(int i=0; i<n;i++){
        if(command[i] == '&'){
            ampersand = true;
        }
    }
}


if (pipe_found == true){
    int count = 0;
    const char delim[] = " &";
    char *token1 = strtok(before, delim);
    while(token1 != NULL){
        //realloc
        if(count==capacity4-1){
                    capacity4 = capacity4*2;
                    argv_before = realloc(argv_before, capacity4*sizeof(char *));
                }
        argv_before[count] = token1;
        count++;        
        token1 = strtok(NULL, delim);
        
    }
    argv_before[count] = NULL;
    
    int count2 = 0;
    char *token2 = strtok(after, delim);
    while(token2 != NULL){
        //realloc
        if(count2==capacity5-1){
                    capacity5 = capacity5*2;
                    argv_after = realloc(argv_after, capacity5*sizeof(char *));
                }
        argv_after[count2] = token2;
        count2++;        
        token2 = strtok(NULL, delim);
    }
    argv_after[count2] = NULL;
    char leave[] = "exit";
    if(argv_before[0]==NULL){
        fprintf(stderr, "Invalid argument\n");
        free(before);
        free(after);
        free(argv);
        free(argv_before);
        free(argv_after);
        free(command);
        continue;
    }
    if(strcmp(argv_before[0], leave) == 0){
        stop = true;
        free(before);
        free(after);
        free(argv);
        free(argv_before);
        free(argv_after);
        free(command);
        exit(0);
    }
    if(argv_after[0]==NULL){
        fprintf(stderr, "Invalid argument\n");
        free(before);
        free(after);
        free(argv);
        free(argv_before);
        free(argv_after);
        free(command);
        continue;
    }
    else if(strcmp(argv_after[0], leave) == 0){
        stop = true;
        free(before);
        free(after);
        free(argv);
        free(argv_before);
        free(argv_after);
        free(command);
        exit(0);
    }
    
    int fd[2];
    if(pipe(fd) == -1){
        perror("Error making pipe.\n");
    }
    pid_t pid = fork();
    if(pid<0){
        perror("Fork failure.\n");
        exit(1);
    }
    //first child
    if(pid==0){
        //left side of pipe
            close(fd[0]);
            dup2(fd[1],1); //redirect stdout to pipe write end
            close(fd[1]);
            execvp(argv_before[0], argv_before);
            perror("Execvp error.\n");
            exit(1);
        
    }
    else{
    pid_t pid2 = fork();
    if(pid2<0){
        perror("Fork failure.\n");
        exit(1);
    }
    //second child
    if(pid2 == 0){
        //right side of pipe
        close(fd[1]);
        dup2(fd[0],0); //redirect stdin to pipe read end
        close(fd[0]);
        execvp(argv_after[0], argv_after);
        perror("Execvp error.\n");
        exit(1);

    }
     
        //parent process
            close(fd[0]);
            close(fd[1]);
            if(ampersand!=true){
            waitpid(pid, NULL, 0);
            waitpid(pid2, NULL, 0);
            
        }
    

} 
}
if(pipe_found == false){
    int count3 = 0;
    const char delim[] = " &";
    char *token = strtok(command, delim);
    while(token != NULL){
        //realloc
        if(count3==capacity3-1){
                    capacity3 = capacity3*2;
                    argv = realloc(argv, capacity3*sizeof(char *));
                }
        argv[count3] = token;
        count3++;        
        token = strtok(NULL, delim);
    }
    argv[count3] = NULL;
    char leave[] = "exit";
    if(argv[0]==NULL){
        fprintf(stderr, "Invalid argument\n");
        free(before);
        free(after);
        free(argv);
        free(argv_before);
        free(argv_after);
        free(command);
        continue;
    }
    if(strcmp(argv[0], leave) == 0){
        stop = true;
        free(before);
        free(after);
        free(argv);
        free(argv_before);
        free(argv_after);
        free(command);
        exit(0);
}
 //check for cd and apply cd
    if((strcmp(argv[0], "cd")==0)){
        if(argv[1]==NULL){
            perror("Missing location of new directory.\n");
            free(argv);
            continue;
        }
        if (chdir(argv[1])==0){
            printf("Directory changed successfully.\n");
            free(before);
            free(after);
            free(argv);
            free(argv_before);
            free(argv_after);
            free(command);
            continue;
        }
        else{
            perror("Directory change failed.\n");
            free(before);
            free(after);
            free(argv);
            free(argv_before);
            free(argv_after);
            free(command);
            continue;
        }
       
}
else{
pid_t pid = fork();
if(argv[0]==NULL){
        fprintf(stderr, "Invalid argument\n");
        free(before);
        free(after);
        free(argv);
        free(argv_before);
        free(argv_after);
        free(command);
        continue;
    }
if (pid==0){
    execvp(argv[0], argv);//only child process executes commands here as there is only one command array.
    perror("Execvp error.\n");
    free(before);
    free(after);
    free(argv);
    free(argv_before);
    free(argv_after);
    free(command);
    exit(1);
}
else if (pid>0){
    if (ampersand != true){
        waitpid(pid, NULL, 0); 
    }
}
else{
    perror("Fork failure.\n");
    free(before);
    free(after);
    free(argv);
    free(argv_before);
    free(argv_after);
    free(command);
    continue;
}
}
}
free(before);
free(after);
free(argv);
free(argv_before);
free(argv_after);
free(command);
}
return 0;
}


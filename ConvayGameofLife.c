#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MAX = 15;

struct element{
    int first;
    int second;
}*matrix;

void initRandom(){
    for(int x = 0; x < MAX; x++){
        for(int y = 0; y < MAX; y++){
            matrix[x*MAX + y].first = rand() % 2;
        }
    }
}

void allocate(){
    matrix = (struct element*)malloc(MAX^2 * sizeof(struct element));
    if(matrix == NULL)
    {
        printf("error!\n");
        exit(1);
    }

}

void print(){
    
    for(int x = 0; x < MAX; x++){
        for(int y = 0; y < MAX; y++){
            matrix[x*MAX + y].first ? printf("#") : printf(".");
            matrix[x*MAX + y].first = matrix[x*MAX + y].second;
        }
        printf("\n");
    }
}

int exists(int x, int y){
    return x >= 0 && x < MAX && y >= 0 && y < MAX;
}

int count(int x, int y){
    int c = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if((i == 0 && j == 0) == 0 && exists(x + i, y+j) ){
                c+=matrix[(x+i)*MAX + y+j].first;
            }
        }
    }
    return c;
}

void update(){
    for(int x = 0; x < MAX; x++){
        for(int y = 0; y < MAX; y++){
            int c = count(x, y);
            matrix[x*MAX + y].second = matrix[x*MAX + y].first ? c == 2 ||c == 3 : c == 3;
        }
    }
}

int main(int argc, char* argv[]){
    
    srand (time(NULL));
    
    if (argc == 2){
        MAX = atoi(argv[1]);
    }
    
    allocate();
    initRandom();
    
    time_t frameStart;
    time_t frameEnd;
    time_t frameDelay = 100;

    for(int tick = 0; 1; tick++){
        time(&frameStart);
        
        update();
        print();

        time(&frameEnd);
        _sleep(frameDelay - (frameEnd-frameStart));
    }

    return 0;
}
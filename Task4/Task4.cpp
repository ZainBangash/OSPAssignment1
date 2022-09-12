#include "Task4.h"
// #include "../Task2/Task2.h"
#include "../Functions.h"
int main(int argc, char* argv[]){
    dirtyFileName = argv[1];
    cleanFileName = argv[2];
    TaskFilter(dirtyFileName);

    pthread_t threads[2];
    int* x = 0;
    for(int i = 0; i < TOTALWORDLENGTHS; i++){
        if(mkfifo(fifoName[i], 0777) == -1){
            perror("Already created");
        }
    }
    if(pthread_create(&threads[1], NULL, &reduce4, NULL) != 0) 
    {
        perror("Failed to create thread");
    }
    if(pthread_create(&threads[0], NULL, &map4, NULL) != 0) 
    {
        perror("Failed to create thread");
    }
    if (pthread_join(threads[1], (void**)x) != 0) {
        perror("Failed to join thread");
    }
    if (pthread_join(threads[0], NULL) != 0) {
        perror("Failed to join thread");
    }
    free(x);
    
    return 0;
}; 

void* reduce4(void* arg){
    std::vector<std::vector<std::string>> finalList;
    std::vector<std::string> wordsToSort;
    std::string line;
    int fd[TOTALWORDLENGTHS];
    uint i;
    for(i  = 0; i < TOTALWORDLENGTHS; i++){
        fd[i] = open(fifoName[i], O_RDONLY);
        if(fd[i] == -1){
            perror("error occured while opening to read");
        }
        finalList.push_back(std::vector<std::string>());
    }

    for(i = 0;i < TOTALWORDLENGTHS; i++){
        for( uint p = 0; p < indexArray[i].size(); p++){
            if(read(fd[i], &line, sizeof(std::string)) == -1){
                perror("Unable to read");
            }else {
                finalList[i].push_back(line);
            }
        }
        wordsToSort.push_back(finalList[i][0]);
        close(fd[i]);
    }
    std::ofstream output;
    output.open(cleanFileName);
    int arrayIndex[TOTALWORDLENGTHS] = {STARTINGINDEX,STARTINGINDEX,STARTINGINDEX,STARTINGINDEX,STARTINGINDEX,STARTINGINDEX,
    STARTINGINDEX,STARTINGINDEX,STARTINGINDEX,STARTINGINDEX,STARTINGINDEX,STARTINGINDEX};

    while(!wordsToSort.empty())
    {
        std::sort(wordsToSort.begin(), wordsToSort.end(), compare);
        std::string& lowestWord = wordsToSort[0];
        int length = lowestWord.length();
        output << lowestWord << '\n';
        arrayIndex[length-WORDLENGTH] += 1;

        wordsToSort.erase(wordsToSort.begin());
        while(arrayIndex[length-WORDLENGTH] != (int)finalList[length-WORDLENGTH].size())
        {
            line = finalList[length-WORDLENGTH][arrayIndex[length-WORDLENGTH]];
            if(!line.empty())
            {
                wordsToSort.push_back(line);
                break;
            }
        }
    }

    output.close();
    double totalWords = globalArray.size();
    for(i = 0;i < TOTALWORDLENGTHS; i++){
        std::cout << "Total words of length " << i+WORDLENGTH <<  " = " << finalList[i].size() <<'\n';
        std::cout << "Percentage of the words of length " << i + WORDLENGTH << " = " << ((double)finalList[i].size() / totalWords) *100 << '\n';
    }
    
    pthread_exit(arg);
}

pthread_t th[TOTALWORDLENGTHS];   


void* map4(void* arg){
    for(int i = 0; i < TOTALWORDLENGTHS; i++){
        indexArray.push_back(std::vector<int>());
    }
    for(size_t i = 0; i < globalArray.size(); i++ ) {
        indexArray[globalArray[i].length() - 3].push_back(i);
    }
    int i;
    for (i = WORDLENGTH; i < TOTALWORDLENGTHS + WORDLENGTH; i++) {
        int* a = (int*)malloc(sizeof(int)); 
        *a = i - 3;
        if(pthread_create(&th[*a], NULL, &sort, a) != 0) {
            perror("Failed to create thread");
        }
        setScheduling(th[*a], SCHED_RR, prioList[*a]);
        int storePolicy;
        sched_param storeParam;
        pthread_getschedparam(th[*a], &storePolicy, &storeParam);
        std::cout << "For length " << *a << " a priority " << storeParam.sched_priority << " and policy of " << storePolicy << " has been set\n" ;
       
    }
    for (i = WORDLENGTH; i < TOTALWORDLENGTHS + WORDLENGTH; i++) {
        if (pthread_join(th[i-WORDLENGTH], NULL) != 0) {
            perror("Failed to join thread");
        }
        
    }
    pthread_exit(arg);
} 

void* sort(void* arg){
    int wordLength = *(int*)arg;
    std::vector<std::string> wordsToSort;
    std::sort(indexArray[wordLength].begin(), indexArray[wordLength].end(), compareString);
    int fd = open(fifoName[wordLength], O_WRONLY);
    std::string* line = new std::string;
    for(uint i = 0; i < indexArray[wordLength].size(); i++){
        line = &globalArray[indexArray[wordLength][i]];
        int writeF = write(fd, line, sizeof(std::string));
        if(writeF == -1){ //sizeof(std::string))
            perror("Unable to write");
            //break;
        }
    }
    close(fd);
    free(arg);
    
    pthread_exit(arg);
}

static void setScheduling(pthread_t &th, int policy, int priority) {
    sched_param param;
    param.sched_priority = priority;
    if(pthread_setschedparam(th, policy, &param)) {
        std::cerr << "Failed to set Thread scheduling : " << std::strerror(errno)<< std::endl;
    }

}

void TaskFilter(std::string dirtyFileName){

    std::ifstream dirtyFile;
    std::string line;

    std::cout << "Opening " << dirtyFileName << " to clean \n";
    dirtyFile.open(dirtyFileName);
    if(dirtyFile){
        while(!dirtyFile.eof()){ 
            getline(dirtyFile,line);
            if (containsOnlyLetters(line) & (line.length() > 2) & (line.length() < 16) & (uniqueCharacters(line) == true)){  
                globalArray.push_back(line);
            }
        }
    }
    std::cout << "Closing " << dirtyFileName << " data has been cleaned\n";
    dirtyFile.close();
}


bool compareString(const int &V1, const int &V2) {
    return strcmp(globalArray[V1].data() + 2, globalArray[V2].data() + 2) < 0;
}



#include "Task2.h"
#include "../Functions.h"


int main(int argc, char* argv[]){
    std::string dirtyFileName = argv[1];
    std::string cleanFileName = argv[2];
    std::cout << "Filtering Data\n";
    TaskFilter(dirtyFileName);
    std::cout << "Sorting Data\n";
    Map2();
    std::cout << "Performing merge sort\n";
    reduce2(cleanFileName);
    return 0;
}; 


void reduce2(std::string cleanFileName)
{
    std::ifstream wlist[TOTALWORDLENGTHS];
    std::ofstream output = std::ofstream(cleanFileName);

    for(int i = WORDLENGTH; i < WORDLENGTH + TOTALWORDLENGTHS; i++)
    {
        std::string fileName = "length";
        std::string num = std::to_string(i).append(".txt");
        wlist[i - WORDLENGTH] = std::ifstream(fileName.append(num));
    }

    std::vector<std::string> wordsToSort;
    for(int i = 0; i < TOTALWORDLENGTHS; i++)
    {
        std::string word;
        std::getline(wlist[i], word);      
        wordsToSort.push_back(word);
    }

    std::cout << "Sorting words and writting to output file" << std::endl;

    std::string word;
    while(!wordsToSort.empty())
    {
        std::sort(wordsToSort.begin(), wordsToSort.end(), compare);
        std::string& lowestWord = wordsToSort[0];
        int length = lowestWord.length();
        output << lowestWord << '\n';
        wordsToSort.erase(wordsToSort.begin());

        while(!wlist[length - WORDLENGTH].eof())
        {
            std::getline(wlist[length - WORDLENGTH], word);
            if(!word.empty())
            {
                wordsToSort.push_back(word);
                break;
            }
        }
    }

    for(std::ifstream& file : wlist)
    {
        file.close();
    }

    output.close();
}

pid_t Map2(){
    std::vector<std::vector<std::string>> vec;
    for(int i = 0; i < TOTALWORDLENGTHS; i++){
        vec.push_back(std::vector<std::string>());
    }
    std::cout << "Separating different word length into lists\n";
    for(uint i= 0; i < globalArray.size(); i++){
        vec[globalArray[i].length() - WORDLENGTH].push_back(globalArray[i]);
    }
    std::cout << "Creating 13 forks, assigning to to sort a wordlength list and writting the sorted list to a file\n";
    for (int i = 0 ; i < TOTALWORDLENGTHS ; i++){
        if(fork() == 0) {
            std::sort(vec[i].begin(), vec[i].end(), compare);
            std::ofstream writeFile;
            std::string fileName = "length";
            std::string num = std::to_string(i + WORDLENGTH).append(".txt");
            fileName.append(num);
            writeFile.open(fileName);
            if(writeFile){
                for(uint e = 0; e < vec[i].size(); e++){
                    writeFile<<vec[i][e]<<'\n';
                }
            }       
            writeFile.close();
            exit(0);
        }
    }
    while(wait(NULL) != -1 || errno != ECHILD);
    return EXIT_SUCCESS;

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

    

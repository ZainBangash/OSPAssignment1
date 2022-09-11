#include "Task1Filter.h"
#include "../Functions.h"


int main(int argc, char* argv[]){
    std::string dirtyFileName = argv[1];
    std::string cleanFileName = argv[2];
    TaskFilter(dirtyFileName, cleanFileName);
    return 0;
}; 

void TaskFilter(std::string dirtyFileName, std::string cleanFileName){
    std::ofstream cleanFile;
    std::ifstream dirtyFile;
    std::string line;

    std::cout << "Opening " << dirtyFileName << " to clean \n";
    dirtyFile.open(dirtyFileName);
    
    std::cout << "Opening " << cleanFileName << " to write clean data in \n";
    cleanFile.open(cleanFileName);

    std::cout << "Writing to " << cleanFileName << " the dirty data meets filtering requirement \n";
    if(dirtyFile && cleanFile){
        while(!dirtyFile.eof()){ 
            getline(dirtyFile,line);
            if (containsOnlyLetters(line) & (line.length() > 2) & (line.length() < 16) & (uniqueCharacters(line) == true)){  
                cleanFile << line << '\n';
            }
        }
    }
    std::cout << "Closing " << dirtyFileName << '\n';
    dirtyFile.close();
    std::cout << "Closing " << cleanFileName << '\n';
    cleanFile.close();
}

    

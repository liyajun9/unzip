#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include <sstream>
#include "unzip.h"

int main() {
    std::cout << "start..." << std::endl;

    unzFile zipfile = unzOpen("/home/ralph/CLionProjects/test/monthData.zip");
    if(zipfile == NULL)
        return 0;

    //get info about the zip file
    unz_global_info global_info;
    if(unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK) {
        unzClose(zipfile);
        return 0;
    }

    //loop to extract all files
    char r_buf[102400];
    for(int i = 0; i < global_info.number_entry; ++i){
        unz_file_info file_info;
        char filename[1024];
        if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 1024, NULL, 0, NULL, 0) != UNZ_OK){
            unzClose(zipfile);
            return 0;
        }

        //check if this entry is a directory or file
        const size_t filename_length = strlen(filename);
        if(filename[filename_length - 1] == '/'){
            mkdir(filename, std::ios::in);
        }else{
            if(unzOpenCurrentFile(zipfile) != UNZ_OK){
                unzClose(zipfile);
                return 0;
            }

            //read data
            unzReadCurrentFile(zipfile, r_buf, 102400);

            std::stringstream ss;
            ss.str(r_buf);
            std::string sLine;
            while(getline(ss, sLine)){
                std::cout << sLine << std::endl;
            }
        }

        unzCloseCurrentFile(zipfile);

        //go to the next entry listed in the zip file
        if((i+1) < global_info.number_entry){
            if(unzGoToNextFile(zipfile) != UNZ_OK){
                unzClose(zipfile);
                return 0;
            }
        }
    }

    unzClose(zipfile);

    return 0;
}

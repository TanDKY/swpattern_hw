//
// Created by T_Dooky on 2/18/2016 AD.
//

#include "ReadingFileLib.h"
#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
    ifstream fp(argv[1], ios::binary);

    ReadingFile::MyReadingFile reader;

    vector<ReadingFile::MyReadingFile::SYLLABLE_DATA_RECORD> results = reader.readFile(fp);

    long total = reader.recordCounting(results);

    printf("Total records: %d\n", total);

    return 0;
}


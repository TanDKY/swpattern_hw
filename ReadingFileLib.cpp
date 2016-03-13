//
// Created by T_Dooky on 2/18/2016 AD.
//

#include "ReadingFileLib.h"

#include <stdexcept>
#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <iconv.h>
#include <vector>

#define FILEID_SIZE (256)
#define MAX_SYLLABLE_TEXTSIZE (1023)

using namespace std;

namespace ReadingFile{

    typedef union _fileid_un{
        struct fileid_crack_at
        {
            uint16_t ui16MagicKey;
            uint16_t ui16Type;
            uint16_t ui16EntrySize;
            uint16_t _filler;
            uint32_t ui32NumEntry;
            time_t tTimeStamp;
        } crack;
        char szRaw[FILEID_SIZE];
    } FILEID;

    vector<MyReadingFile::SYLLABLE_DATA_RECORD> MyReadingFile::readFile(ifstream &fp){

        FILEID id;
        vector<MyReadingFile::SYLLABLE_DATA_RECORD> records;

        // read header1
        fp.read((char*) &id, sizeof(id));

        while(true){
            SYLLABLE_DATA_RECORD data;

            // read header
            fp.read((char*) &data, sizeof(data) - MAX_SYLLABLE_TEXTSIZE - 1);

            // end of file
            if(!fp){
                break;
            }

            // read text
            char buffer[MAX_SYLLABLE_TEXTSIZE];
            fp.getline((char*) buffer, MAX_SYLLABLE_TEXTSIZE, 0);

            // translate
            iconv_t charset = iconv_open("UTF8", "CP874");
            size_t inSize = MAX_SYLLABLE_TEXTSIZE;
            size_t outSize = MAX_SYLLABLE_TEXTSIZE;
            char *input = &buffer[0];
            char *output = &data.szText[0];
            iconv(charset, &input, &inSize, &output, &outSize);

            records.push_back(data);

            //cout << "ID: " << data.ui32SylID << " Word: " << data.szText << endl;
        }

        return records;
    }

    long MyReadingFile::recordCounting(std::vector<SYLLABLE_DATA_RECORD> &v) {
        return v.size();
    }

}



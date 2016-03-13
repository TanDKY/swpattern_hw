//
// Created by T_Dooky on 2/18/2016 AD.
//

#ifndef PROJECT_READINGFILE_H
#define PROJECT_READINGFILE_H

#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <vector>

namespace ReadingFile {

    class MyReadingFile {

    public:

        #define MAX_SYLLABLE_TEXTSIZE (1023)
        typedef struct syllable_data_record_at
        {
            uint32_t ui32SylID;
            uint16_t ui2Lang:2;
            uint16_t ui10Len:10;
            uint16_t ui1HasTailSpace:1;
            uint16_t ui1IsUnused:1;
            uint16_t ui1Numeric:1;
            uint16_t _filler:1;
            uint32_t ui32MapFilePos;
            time_t tTimeStamp;
            char szText[MAX_SYLLABLE_TEXTSIZE];
        } SYLLABLE_DATA_RECORD;

        static std::vector<SYLLABLE_DATA_RECORD> readFile(std::ifstream &fp);

        static long recordCounting(std::vector<SYLLABLE_DATA_RECORD> &v);

    };
}


#endif //PROJECT_READINGFILE_H

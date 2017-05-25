#include "FileIO.h"

size_t FileIO::getFileSize(std::string path){
    stream.open(path, std::ios::binary | std::ios::ate|std::ios::in );

    if(!stream.is_open())
        return 0;
    size_t fileSize = stream.tellg();
    stream.clear();
    stream.close();

    return fileSize;
}

bool FileIO::readFile(std::string path,char **bufferOut, size_t *sizeFile) {

    size_t size = getFileSize(path);
    if(size == 0)
        return false; // the file couldn't be opened.

    if(sizeFile != nullptr)
        *sizeFile = size;

    *bufferOut = new char[size];

    stream.open (path, std::ios::in | std::ios::binary);
    if(!stream.is_open())
        return false;

    if(*bufferOut != nullptr)
        if(!stream.read(*bufferOut,size))
            return false;

    stream.clear();
    stream.close();
    return true;

}

bool FileIO::writeEncodedFile(std::string path, std::string fileExtension,std::deque<int> frequencies,std::deque<char> symbols,int padding) {



    stream.open(path + fileExtension, std::ios::binary | std::ios::out);
    if(!stream.is_open())
        return false; //error opening file


    unsigned long aux = frequencies.size();
   stream.write(reinterpret_cast<char*>(&aux),sizeof(int));
    for(unsigned long i = 0; i <frequencies.size();i++){
        stream.write(&(symbols.at(i)),sizeof(char));
        stream.write(reinterpret_cast<char*>(&(frequencies.at(i))),sizeof(int));
    }

    //writing how many bits will not be considered at the end of the file (padding)
    stream.write(reinterpret_cast<char*>(&padding),sizeof(int));

    //File won't be closed here, so the content may be written by other function
    return true;

}

void FileIO::writeEncodedByte(const char bits[], unsigned long bufferSize){
    char byte[bufferSize];
    int j = 0;
    int x = 0;
    byte[0] = 0;

    for (int i = 0; i < 8*bufferSize; i++)
    {
        byte[j] |= (bits[i] & 1) << x++;
        if(x == 8){
            j++;
            x = 0;
            byte[j] = 0;
        }
    }
    stream.write(byte,bufferSize);

}


bool FileIO::readerHeader(std::string path,std::deque<int> *frequencies,std::deque<char> *symbols,int *padding){
    int size;
    int frequency;
    char symbol;

    stream.open(path, std::ios::binary | std::ios::in);
    if(!stream.is_open())
        return false;

    stream.read(reinterpret_cast<char*>(&size),sizeof(int));
    for(int i = 0; i < size; i ++){
        stream.read(&symbol,sizeof(char));
        symbols->push_back(symbol);
        stream.read(reinterpret_cast<char*>(&frequency),sizeof(int));
        frequencies->push_back(frequency);
    }

    stream.read(reinterpret_cast<char*>(padding),sizeof(int));

    //file will be closed after the content has been read
    return true;

}

void FileIO::readSymbols(std::deque<char> *symbols) {
    //Constructing a vector of symbols to be decoded by program.
    char c;
    while(!stream.eof()){
        stream.read(&c,sizeof(char));
        symbols->push_back(c);

    }
    // Needs to remove one char, refered to EOF byte.
    symbols->pop_back();
    stream.close();

}

bool FileIO::writeDecodedFile(std::string path) {
    stream.open(path,std::ios::binary|std::ios::out);

    if(!stream.is_open())
        return false; //error opening file
}

void FileIO::writeDecodedByte(const char bits) {

    stream.put(bits);

}

void FileIO::closeFile() {
    if(stream.is_open())
        stream.close();
}

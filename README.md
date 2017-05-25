# HuffmanCompressor
Compressor and Extractor of files using Huffman Algorithm.
# How to use it!
The compilation of the file is as simple as it follows:
  - On terminal (linux): g++ -std=c++11 Huffman.cpp Node.cpp FileIO.cpp main.cpp -o main -O3
  - On Command Prompt (windows): g++ -std=c++11 Huffman.cpp Node.cpp FileIO.cpp main.cpp -o main.exe -O3
  
In order to compress or decompress a file, the following must be done when executing the file:
 - Compression
    - On terminal (linux) :./main "-c" "InputFilePath" "OutputFilePath"
    - On Command Prompt (windows): main "-c" "InputFilePath" "OutputFilePath"
 - Decompression
    - On terminal (linux) :./main "-e" "InputFilePath" "OutputFilePath"
    - On Command Prompt (windows): main "-e" "InputFilePath" "OutputFilePath"
    
The example below describes the process:
 - Compressing the file "song.mp3" to the output file of name "compressed", considering the files are in the root of the project.   
    - ./main "-c" song.mp3 compressed
 - Decompressing the file "compressed.tfs" back to the original file, considering the files are in the root of the project.
    - ./main "-e" compressed.tfs extracted.mp3

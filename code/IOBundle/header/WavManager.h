#ifndef WAVMANAGER_HH
#define WAVMANAGER_HH

#include <iostream>
#include <fstream>
#include <list>

class WavManager {
private:
    template<typename Word> static
    std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word)) {
        for (; size; --size, value >>= 8) {
            outs.put(static_cast<char>(value & 0xFF));
        }
        return outs;
    }
public:
    static void writeWav(const std::string& pathFile, const std::list<double>& sound, double scale) {
        std::ofstream file(pathFile, std::ios::binary);
        // Write the file headers
        file << "RIFF----WAVEfmt ";
        write_word(file,     16, 4); // no extension data
        write_word(file,      1, 2); // PCM - integer samples
        write_word(file,      2, 2); //  channels
        write_word(file,  44000, 4); // samples per second (Hz)
        write_word(file, 176400, 4); // (Sample Rate * BitsPerSample * Channels)
                                     // / 8
        write_word(file,      4, 2); // data block (2[channels] integer sample)
        write_word(file,     16, 2); // number of bits per sample (n*8)

        // Write the data chunk header
        size_t data_chunk_pos = file.tellp();
        file << "data----"; // (chunk size to be filled in later)

        // Write the audio samples
        for (double s : sound) {
            write_word(file, (int)(s * scale), 2);
            write_word(file, (int)(s * scale), 2);
        }

        // (We'll need the final file size to fix the chunk sizes above)
        size_t file_length = file.tellp();
        // Fix the data chunk header to contain the data size
        file.seekp(data_chunk_pos + 4);
        write_word(file, file_length - data_chunk_pos + 8);
        // Fix the file header to contain the proper RIFF chunk size, which is
        // (file
        // size - 8) bytes
        file.seekp(0 + 4);
        write_word(file, file_length - 8, 4);
    }
};

#endif // ifndef WAVMANAGER_HH

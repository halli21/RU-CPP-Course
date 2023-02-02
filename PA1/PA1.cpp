#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Riff Chunk
const string chunk_id = "RIFF";
const string chunk_size = "----";
const string format = "WAVE";

// FMT
const string subchunk1_id = "fmt ";
const int subchunk1_size = 16;
const int audio_format = 1;

const int num_channels = 1;
const int sample_rate = 44100;
const int byte_rate = sample_rate * num_channels * (subchunk1_size / 8);
const int block_align = num_channels * (subchunk1_size / 8);
const int bits_per_sample = 16;

// Data
const string subchunk2_id = "data";
const string subchunk2_size = "----";

// const int freq = 440;
// const double duration = 0.5;
// int no_samples = duration * sample_rate;

void write_as_bytes(ofstream &file, int value, int byte_size)
{
    for (int i = 0; i < byte_size; i++)
    {
        char byte = (value >> (i * 8)) & 0xFF;
        file.write(&byte, 1);
    }
}

int main(int argc, char *argv[])
{
    ofstream wav;
    string filename;
    int freq;
    double duration;

    if (argc == 4)
    {
        filename = argv[1];
        freq = std::atoi(argv[2]);
        duration = std::atof(argv[3]);
    }
    else
    {
        cout << "Please enter a filename without the file ending: ";
        cin >> filename;
        cout << "Please enter the frequency of the note: ";
        cin >> freq;
        cout << "Please enter the duration of the note in seconds: ";
        cin >> duration;
    }

    filename = filename + ".wav";
    int no_samples = duration * sample_rate;
    wav.open(filename, ios::binary);
    if (wav.is_open())
    {
        wav << chunk_id;
        wav << chunk_size;
        wav << format;

        wav << subchunk1_id;
        write_as_bytes(wav, subchunk1_size, 4);
        write_as_bytes(wav, audio_format, 2);
        write_as_bytes(wav, num_channels, 2);
        write_as_bytes(wav, sample_rate, 4);
        write_as_bytes(wav, byte_rate, 4);
        write_as_bytes(wav, block_align, 2);
        write_as_bytes(wav, bits_per_sample, 2);

        wav << subchunk2_id;
        wav << subchunk2_size;

        int start_audio = wav.tellp();

        for (int i = 0; i < no_samples; i++)
        {
            double sample = cos(freq * i * 3.142 / sample_rate);
            double sample_16 = sample * 32767;
            write_as_bytes(wav, sample_16, 2);
        }

        int end_audio = wav.tellp();
        wav.seekp(start_audio - 4);
        write_as_bytes(wav, end_audio - start_audio, 4);

        wav.seekp(4, ios::beg);
        write_as_bytes(wav, end_audio - 8, 4);
    }

    wav.close();

    return 0;
}
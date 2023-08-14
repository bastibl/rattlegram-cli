#include "encoder.hh"
#include <cstdint>

static EncoderInterface *encoder;

int main(int argc, char **argv) {

    int rate = 8000;
    int channel = 0;
    int noise_symbols = 1;
    int carrier_freq = 1500;
    int output_bits = 16;
    int psk = 4;
    int guard_length_fraction = 8;
    char *out_file = "out.wav";

    if (argc < 3 || argc > 11) {
        std::cerr << "usage: " << argv[0] << " MESSAGE CALLSIGN [NOISE_SYMBOLS] [CARRIER_FREQUENCY] [RATE] [BITS] [CHANNEL] [MAPPING] [GUARD_LENGTH] [FILE] " << std::endl;
        return 1;
    }
    std::string mesg(argv[1]);
    const char *call_sign = argv[2];
    if (argc > 3)
        noise_symbols = std::atoi(argv[3]);
    if (argc > 4)
        carrier_freq = std::atoi(argv[4]);
    if (argc > 5)
        rate = std::atoi(argv[5]);
    if (argc > 6)
        output_bits = std::atoi(argv[6]);
    if (argc > 7)
        channel = std::atoi(argv[7]);
    if (argc > 8)
        psk = std::atoi(argv[8]);   
    if (argc > 9)
        guard_length_fraction = std::atoi(argv[9]);
    if (argc > 10)
        out_file = argv[10];

    char message[192] = {0};
    for (int i = 0; i < mesg.length(); i++) {
        if (i < 192)
            message[i] = mesg[i];
    }
    int channel_count = 1;
    if (channel != 0) {
        channel_count = 2;
    }
    DSP::WriteWAV<float> output_file(out_file, rate, output_bits, channel_count);
    switch (rate) {
        case 8000:
            switch (psk) {
                case 2:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<8000, 2, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<8000, 2, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<8000, 2, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<8000, 2, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<8000, 2, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 4:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<8000, 4, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<8000, 4, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<8000, 4, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<8000, 4, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<8000, 4, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 8:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<8000, 8, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<8000, 8, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<8000, 8, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<8000, 8, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<8000, 8, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 16:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<8000, 16, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<8000, 16, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<8000, 16, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<8000, 16, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<8000, 16, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                default:
                    std::cerr << "Unsupported symbol mapping." ;
                    std::cerr << "Supported PSK: 2/4/8. Supported QAM: 16."<< std::endl;
                    return 1;
            }
            break;
        case 16000:
            switch (psk) {
                case 2:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<16000, 2, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<16000, 2, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<16000, 2, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<16000, 2, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<16000, 2, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 4:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<16000, 4, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<16000, 4, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<16000, 4, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<16000, 4, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<16000, 4, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 8:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<16000, 8, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<16000, 8, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<16000, 8, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<16000, 8, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<16000, 8, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 16:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<16000, 16, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<16000, 16, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<16000, 16, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<16000, 16, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<16000, 16, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                default:
                    std::cerr << "Unsupported symbol mapping." ;
                    std::cerr << "Supported PSK: 2/4/8. Supported QAM: 16."<< std::endl;
                    return 1;
            }
            break;
        case 32000:
            switch (psk) {
                case 2:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<32000, 2, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<32000, 2, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<32000, 2, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<32000, 2, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<32000, 2, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 4:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<32000, 4, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<32000, 4, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<32000, 4, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<32000, 4, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<32000, 4, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 8:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<32000, 8, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<32000, 8, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<32000, 8, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<32000, 8, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<32000, 8, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 16:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<32000, 16, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<32000, 16, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<32000, 16, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<32000, 16, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<32000, 16, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                default:
                    std::cerr << "Unsupported symbol mapping." ;
                    std::cerr << "Supported PSK: 2/4/8. Supported QAM: 16."<< std::endl;
                    return 1;
            }
            break;
        case 44100:
            switch (psk) {
                case 2:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<44100, 2, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<44100, 2, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<44100, 2, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<44100, 2, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<44100, 2, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 4:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<44100, 4, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<44100, 4, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<44100, 4, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<44100, 4, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<44100, 4, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 8:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<44100, 8, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<44100, 8, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<44100, 8, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<44100, 8, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<44100, 8, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 16:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<44100, 16, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<44100, 16, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<44100, 16, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<44100, 16, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<44100, 16, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                default:
                    std::cerr << "Unsupported symbol mapping." ;
                    std::cerr << "Supported PSK: 2/4/8. Supported QAM: 16."<< std::endl;
                    return 1;
            }
            break;
        case 48000:
            switch (psk) {
                case 2:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<48000, 2, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<48000, 2, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<48000, 2, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<48000, 2, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<48000, 2, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 4:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<48000, 4, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<48000, 4, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<48000, 4, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<48000, 4, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<48000, 4, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 8:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<48000, 8, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<48000, 8, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<48000, 8, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<48000, 8, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<48000, 8, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 16:
                    switch (guard_length_fraction) {
                        case 1:
                            encoder = new(std::nothrow) Encoder<48000, 16, 1>(&output_file);
                            break;
                        case 2:
                            encoder = new(std::nothrow) Encoder<48000, 16, 2>(&output_file);
                            break;
                        case 4:
                            encoder = new(std::nothrow) Encoder<48000, 16, 4>(&output_file);
                            break;
                        case 8:
                            encoder = new(std::nothrow) Encoder<48000, 16, 8>(&output_file);
                            break;
                        case 16:
                            encoder = new(std::nothrow) Encoder<48000, 16, 16>(&output_file);
                            break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                default:
                    std::cerr << "Unsupported symbol mapping." ;
                    std::cerr << "Supported PSK: 2/4/8. Supported QAM: 16."<< std::endl;
                    return 1;
            }
            break;
        default:
            std::cerr << "Unsupported sample rate." ;
            std::cerr << "Supported rates: 8000/16000/32000/44100/48000."<< std::endl;
            return 1;
    }
    encoder->configure(reinterpret_cast<const uint8_t*>(&message[0]), 
        reinterpret_cast<const int8_t*>(&call_sign[0]), 
        carrier_freq, 
        noise_symbols, 
        false);
    //not sure how often to iterate. up to testing
    for (int i = 0; i < 12 + noise_symbols; ++i) {
        encoder->produce_write(channel);
	}

    return 0;
}
#include "decoder.hh"
#include "wav.hh"
#include <cstdint>
#include "AudioFile.h"

static DecoderInterface *decoder;

int main(int argc, char **argv) {
	if (argc < 4 || argc > 5) {
        std::cerr << "usage: " << argv[0] << " FILE CHANNEL [MAPPING] [GUARD LENGTH]" << std::endl;
        return 1;
    }
	const char* input_name = argv[1];
	int channel = std::atoi(argv[2]);
	int psk = 4;
	int guard_length_fraction = 8;
	if (argc > 3)
		psk = std::atoi(argv[3]);
	if (argc > 4)
		guard_length_fraction = std::atoi(argv[4]);
	AudioFile<int16_t> audioFile;
	audioFile.load(input_name);
	int rate = audioFile.getSampleRate();
	int channel_count = audioFile.getNumChannels();
	if (channel < 0 || channel > 4) {
		std::cout << "Channel must be between 0 and 5." << std::endl;
		return 1; 
	}
	if (!(channel_count == 1 || channel_count == 2)) {
		std::cout << "Only mono and stereo audio is supported." << std::endl;
		return 1;
	}
	if ((channel > 0 && channel < 5) && (channel_count != 2)) {
		std::cout << "Channel 1 - 4 are only supported for stereo audio." << std::endl;
		return 1; 
	}
	if (channel_count == 1) {
	std::cout << "Mono audio. Channel set to 0." << std::endl;
	channel = 0;
	}
	int file_length = audioFile.getNumSamplesPerChannel() * channel_count;
	int symbol_length = (1280 * rate) / 8000;
	int guard_length = symbol_length / 8;
	int extended_length = symbol_length + guard_length;
	//int record_count = rate/50;
    int record_count = rate/10;

	int16_t file[file_length + 22 * record_count];
	//for (int i = 0; i < file_length + record_count; i++) {
	//	file[i] = 0;
	//}
	for (int i = 0; i < file_length/channel_count; i++) {
		for (int c = 0; c < channel_count; c++) {
			file[i * channel_count + c] = audioFile.samples[c][i];
		}
	}
	switch (rate) {
        case 8000:
            switch (psk) {
                case 2:
                    switch (guard_length_fraction) {
                        case 1:
                            decoder = new(std::nothrow) Decoder<8000, 2, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<8000, 2, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<8000, 2, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<8000, 2, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<8000, 2, 16>();
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
                            decoder = new(std::nothrow) Decoder<8000, 4, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<8000, 4, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<8000, 4, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<8000, 4, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<8000, 4, 16>();
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
                            decoder = new(std::nothrow) Decoder<8000, 8, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<8000, 8, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<8000, 8, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<8000, 8, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<8000, 8, 16>();
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
                            decoder = new(std::nothrow) Decoder<8000, 16, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<8000, 16, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<8000, 16, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<8000, 16, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<8000, 16, 16>();
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
                            decoder = new(std::nothrow) Decoder<16000, 2, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<16000, 2, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<16000, 2, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<16000, 2, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<16000, 2, 16>();
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
                            decoder = new(std::nothrow) Decoder<16000, 4, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<16000, 4, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<16000, 4, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<16000, 4, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<16000, 4, 16>();
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
                            decoder = new(std::nothrow) Decoder<16000, 8, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<16000, 8, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<16000, 8, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<16000, 8, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<16000, 8, 16>();
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
                            decoder = new(std::nothrow) Decoder<16000, 16, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<16000, 16, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<16000, 16, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<16000, 16, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<16000, 16, 16>();
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
                            decoder = new(std::nothrow) Decoder<32000, 2, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<32000, 2, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<32000, 2, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<32000, 2, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<32000, 2, 16>();
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
                            decoder = new(std::nothrow) Decoder<32000, 4, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<32000, 4, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<32000, 4, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<32000, 4, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<32000, 4, 16>();
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
                            decoder = new(std::nothrow) Decoder<32000, 8, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<32000, 8, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<32000, 8, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<32000, 8, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<32000, 8, 16>();
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
                            decoder = new(std::nothrow) Decoder<32000, 16, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<32000, 16, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<32000, 16, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<32000, 16, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<32000, 16, 16>();
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
                            decoder = new(std::nothrow) Decoder<44100, 2, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<44100, 2, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<44100, 2, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<44100, 2, 8>();
                            break;
                        //case 16:
                        //    decoder = new(std::nothrow) Decoder<44100, 2, 16>();
                        //    break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 4:
                    switch (guard_length_fraction) {
                        case 1:
                            decoder = new(std::nothrow) Decoder<44100, 4, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<44100, 4, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<44100, 4, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<44100, 4, 8>();
                            break;
                        // case 16:
                        //     decoder = new(std::nothrow) Decoder<44100, 4, 16>();
                        //     break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 8:
                    switch (guard_length_fraction) {
                        case 1:
                            decoder = new(std::nothrow) Decoder<44100, 8, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<44100, 8, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<44100, 8, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<44100, 8, 8>();
                            break;
                        //case 16:
                        //    decoder = new(std::nothrow) Decoder<44100, 8, 16>();
                        //    break;
                        default:
                            std::cerr << "Unsupported guard length." ;
                            std::cerr << "Supported guard lengths: 1 (1), 1/2 (2), 1/4 (4), 1/8 (8) and 1/16 (16)"<< std::endl;
                            return 1;
                    }
                    break;
                case 16:
                    switch (guard_length_fraction) {
                        case 1:
                            decoder = new(std::nothrow) Decoder<44100, 16, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<44100, 16, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<44100, 16, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<44100, 16, 8>();
                            break;
                        //case 16:
                         //   decoder = new(std::nothrow) Decoder<44100, 16, 16>();
                        //    break;
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
                            decoder = new(std::nothrow) Decoder<48000, 2, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<48000, 2, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<48000, 2, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<48000, 2, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<48000, 2, 16>();
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
                            decoder = new(std::nothrow) Decoder<48000, 4, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<48000, 4, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<48000, 4, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<48000, 4, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<48000, 4, 16>();
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
                            decoder = new(std::nothrow) Decoder<48000, 8, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<48000, 8, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<48000, 8, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<48000, 8, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<48000, 8, 16>();
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
                            decoder = new(std::nothrow) Decoder<48000, 16, 1>();
                            break;
                        case 2:
                            decoder = new(std::nothrow) Decoder<48000, 16, 2>();
                            break;
                        case 4:
                            decoder = new(std::nothrow) Decoder<48000, 16, 4>();
                            break;
                        case 8:
                            decoder = new(std::nothrow) Decoder<48000, 16, 8>();
                            break;
                        case 16:
                            decoder = new(std::nothrow) Decoder<48000, 16, 16>();
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
 

	for (int i = 0; i * record_count * channel_count < file_length + 10 * channel_count * record_count; i++) {
		if (decoder->feed(&file[i*record_count*channel_count], record_count, channel)) {
			int status = decoder->process();
			float cfo = -1.0;
			int32_t mode = -1;
			uint8_t call_sign[192] = {0}; 
			uint8_t payload[170] = {0};
 
			switch (status) {
				case 0:
					break;
				case 1:
					std::cout << "PREAMBLE FAIL" << std::endl;
					break;
				case 2:
					decoder->staged(&cfo, &mode, call_sign);
					std::cout << "SYNC:" << std::endl 
							<< "CFO: " 
							<< cfo << std::endl 
							<< "Mode: "
							<< mode << std::endl 
							<< "Call sign: "
							<< (reinterpret_cast<char*>(call_sign))
							<< std::endl;
					break;
				case 3:
					std::cout << "Bit flips: " << decoder->fetch(payload) << std::endl;
					std::cout << "DONE:  payload: " 
							<< (reinterpret_cast<char*>(payload))
							<< std::endl;
					break;
				case 4:
					std::cout << "HEAP ERROR" << std::endl;
					break;
				case 5:
					decoder->staged(&cfo, &mode, call_sign);
					std::cout << "NOPE:"
							<< "  CFO "
							<< cfo
							<< "  mode: "
							<< mode
							<< "  call sign: "
							<< (reinterpret_cast<char*>(call_sign))
							<< std::endl;
					break;
				case 6: 
					decoder->staged(&cfo, &mode, call_sign);
					std::cout << "PING:"
							<< "  CFO "
							<< cfo
							<< "  mode: "
							<< mode
							<< "  call sign: "
							<< (reinterpret_cast<char*>(call_sign))
							<< std::endl;
					break;
				default:
					std::cout << "UNDEFINED BEHAVIOUR" << std::endl;
					return 1;

			}
		}
	}

    return 0;
}
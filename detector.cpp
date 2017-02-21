#include "bitmap.h"
#include "decoderfactory.h"
#ifndef WIN32
#include "unistd.h"
#endif
using namespace BNDecoder;

int main(int argc, char** argv){
	std::string path;
	std::string out("o.bmp");
	int bitCount = 0;
	bool grey = false;

	int result;
	while((result = getopt(argc, argv, "i:o:b:gh")) != -1){
		switch(result){
			case 'i':
				path.assign(optarg);
				break;
			case 'o':
				out.assign(optarg);
				break;
			case 'b':
				bitCount = atoi(optarg);
				break;
			case 'g':
				grey = true;
				break;
			case 'h':
				std::cout << "usage: " << argv[0] << "[-i infile] [-b bitCount] [-o outfile] [-g] [-h] [infile]" << std::endl;
		}
	}
	if ( optind < argc ) {  
        path.assign(argv[optind]);
    } 
	IDecoder *decoder,*encoder;
	try{
		if(path.empty()){
			throw "please enter the source file";
		}
		Bitmap pic = Bitmap::loadBMP(path.c_str());
		if(bitCount==0) bitCount = pic.getBitCount();
		decoder = DecoderFactory::createDecoder(pic.getBitCount());
		encoder = DecoderFactory::createDecoder(bitCount);
		std::list<Pixel> data = decoder->decode(pic.getData(),pic.getPlanes());
		if(grey){
			data = decoder->grey(data);
		}
		pic.setData(encoder->encode(data, pic.getPlanes()), bitCount);
		pic.out(out.c_str());
	}catch(const char* &e){
		std::cerr << e << std::endl; 
	}catch(UnknowException& e){
		std::cerr << e.what() << std::endl;  
	}
	delete decoder;
	delete encoder;
	return 0;
}


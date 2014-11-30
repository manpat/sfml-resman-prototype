#include "logger.h"

using std::ofstream;
using std::string;

namespace{
	static ofstream logfile;
}

void InitLogFile(string fname){
	logfile.open(fname);
}

ofstream& GetLogFile(){
	return logfile;
}
#include <p24fxxxx.h>
#define BUSPIRATEV1A //http://hackaday.com/2009/01/22/how-to-bus-pirate-v1-improved-universal-serial-interface/
//#define BUSPIRATEV2 

#if defined(BUSPIRATEV1A)
	#include "hardwarev1a.h"
#elif defined(BUSPIRATEV2)
	#include "hardwarev3.h"
#else
	#error "No hardware defined in base.h."
#endif

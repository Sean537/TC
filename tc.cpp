#include "./tc.hpp"



#include "./tc.h"
#define _GLIBCXX_HAS_GTHREADS
#define __GLIBC__
#include <thread>
#include <chrono>
void tsleep(int milliseconds){  
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));  
}
void tprint(std::wstring content, int SleepTime, int times){  
	for(int i=0;i<times;i++) std::wcout<<content; //此函数作用是：在输出times个content后，
	tsleep(SleepTime);        //再去等待SleepTime毫秒 
}

/*
class t{
	public:
		void tsleep(int milliseconds){  
    		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));  
		}
		//template<typename T>
		void tprint(std::wstring content, int SleepTime=0, int times=1){  
			for(int i=0;i<times;i++)
				std::cout<<content; //此函数作用是：在输出times个content后，
			tsleep(SleepTime);        //再去等待SleepTime毫秒 
		}
};
*/
/*
namespace t{
	
	void tsleep(int milliseconds){  
    	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));  
	}
	
	template<typename T>
	void tprint(T content, int SleepTime=0, int times=1){  
		for(int i=0;i<times;i++)
			std::cout<<content; //此函数作用是：在输出times个content后，
		tsleep(SleepTime);        //再去等待SleepTime毫秒 
	}
	
}
*/

extern "C"{

}
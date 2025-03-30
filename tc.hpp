/*
tc.hpp

Copyright (C) 2024-2025 Sean537. All rights reserved.
*/

#ifndef _TC_HPP_
#define _TC_HPP_

#include <iostream>
#include <string>

void tsleep(int milliseconds){  
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));  
}
void tprint(std::wstring content, int SleepTime, int times){  
	for(int i=0;i<times;i++) std::wcout<<content; //此函数作用是：在输出times个content后，
	tsleep(SleepTime);        //再去等待SleepTime毫秒 
}

#endif

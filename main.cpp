#include "crawler.h"
#include "ctext.h"
#include "config.h"
#include <iostream>

int main()
{
	Crawler crawler;
	crawler.init();
	crawler.run();
	return 0;
}

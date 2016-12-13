#include "ctext.h"
#include <string>
#include <string.h>

CText::CText()
{
	str = NULL;
}

CText::CText(char* str)
{
	this->str = str;
}

void CText::removeSpace()
{
	char* curptr;
	char temp[strlen(str)+1];
	int index = 0;
	while('\0' != *curptr)
	{
		if(' ' == *curptr || 9 == *curptr)
		{
			curptr++;
			continue;
		}
		temp[index++] = *curptr++;
	}
	temp[index] = '\0';
	strncpy(str, temp, strlen(temp)+1);
}

int CText::converLower()
{
	char* curptr;
	while('\0' != *curptr)
	{
		if('A' <= *curptr && 'Z'>= *curptr)
		{
			*curptr += 32;
		}
		curptr++;
	}
}
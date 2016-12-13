#ifndef _TEXT_
#define _TEXT_

class CText
{
public:
	CText();
	CText(char* str);

	//ÒÆ³ý×Ö·û´®ÖÐµÄ¿Õ¸ñºÍtab×Ö·û
	void removeSpace();

	int converLower();
	
	char* str;
	
private:
		
};

#endif

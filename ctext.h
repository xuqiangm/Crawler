#ifndef _TEXT_
#define _TEXT_

class CText
{
public:
	CText();
	CText(char* str);

	//�Ƴ��ַ����еĿո��tab�ַ�
	void removeSpace();

	int converLower();
	
	char* str;
	
private:
		
};

#endif

#include "Coroutine.h"
#include "debug.h"

CCoroutine::CCoroutine(void)
{
}


CCoroutine::~CCoroutine(void)
{
}

void CCoroutine::Init()
{
	if (0!=this->State)
	{
		OutputDebug("CCoroutine:Init:��γ�ʼ��");
		return;
	}else{
		this->State=1;
	}



}

/*

*/
void CCoroutine::GOMAXPROCS(int m_NewValueCPU)
{
	if (0!=this->State)
	{
		OutputDebug("CCoroutine:GOMAXPROCS:���������ʼ��");
		return;
	}else{
		if (this->m_NumCPU < m_NewValueCPU)
		{
			this->m_NumCPU = m_NewValueCPU;
		}
	}



}

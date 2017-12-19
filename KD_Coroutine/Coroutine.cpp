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
		OutputDebug("CCoroutine:Init:多次初始化");
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
		OutputDebug("CCoroutine:GOMAXPROCS:在启动后初始化");
		return;
	}else{
		if (this->m_NumCPU < m_NewValueCPU)
		{
			this->m_NumCPU = m_NewValueCPU;
		}
	}



}

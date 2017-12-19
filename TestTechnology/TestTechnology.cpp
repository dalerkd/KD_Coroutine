// TestTechnology.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include "debug.h"

const static int PAGE_SIZE = 4*1024;

class CStackManage
{
public:


	//Ԥ��
	void StartMemory(size_t Number_Page_Size){
		m_Address = VirtualAlloc(NULL,Number_Page_Size*PAGE_SIZE,MEM_RESERVE,PAGE_EXECUTE_READWRITE);
	}

	//����
	LPVOID GetMemory(PVOID Address,size_t len){
		return VirtualAlloc(Address,len,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	}
	void EndNeedAll(){
		VirtualFree(m_Address,NULL,MEM_RELEASE);
	}
	LPVOID GetBaseAddress(){
		return m_Address;
	}
private:
	PVOID m_Address;

};

CStackManage* g_p ;

//����ϴδ����쳣�ĵ�ַ����ֹ�쳣��ѭ��
LPVOID LastExceptionAddress=nullptr;

LONG StackExceptionDecide(EXCEPTION_RECORD SavedExceptRec,PVOID pMinStack,PVOID pMaxStack){
	/*�����ָ���쳣���鿴�ڴ��Ƿ��ڷ�Χ��*/

	/*
	�ں��ı��P658�м�̽���
	SavedExceptRec.ExceptionInformationֻ��AV�쳣���õ���
	SavedExceptRec.ExceptionInformation[0]		0��ʾ���쳣��1��ʾд�쳣
	����
	SavedExceptRec.ExceptionInformation[1]ָ��������ǣ��쳣������ַ�������Ǵ����ַ��������Ҫ�����
	SavedExceptRec.ExceptionInformation[2]�ƺ���[0]�仯��������

	*/
	LPVOID ExceptionAdd =(LPVOID)SavedExceptRec.ExceptionInformation[1];

	if(EXCEPTION_ACCESS_VIOLATION==SavedExceptRec.ExceptionCode){
		if(ExceptionAdd>=pMinStack||ExceptionAdd<pMaxStack){
			if (ExceptionAdd==LastExceptionAddress)//����ϴδ����쳣�ĵ�ַ����ֹ�쳣��ѭ��
			{
				return (EXCEPTION_CONTINUE_SEARCH);
			}
			else
			{
				ExceptionAdd==LastExceptionAddress;
			}
			g_p->GetMemory(ExceptionAdd,PAGE_SIZE*1);
			OutputDebug("����ִ��\r\n");
			return (EXCEPTION_CONTINUE_EXECUTION);//����ִ��

		}else{//��ָ����Χ���쳣 ����
			OutputDebug("��ִ�з�Χ�쳣\r\n");
			return (EXCEPTION_CONTINUE_SEARCH);
		}
	}else{
		//��ָ��AV�쳣 ����
		OutputDebug("��ִ���쳣\r\n");
		return (EXCEPTION_CONTINUE_SEARCH);
	}
}

void UserStack(PVOID pMinStack,PVOID pMaxStack/*����������ַ*/){
	
	LastExceptionAddress = nullptr;
	__try{

		int a = ((char*)pMinStack)[0];
		OutputDebug("Success! %d",a);
	}
	__except(
		StackExceptionDecide(*(GetExceptionInformation())->ExceptionRecord,pMinStack,pMaxStack)
		){}
	LastExceptionAddress = nullptr;
}


/*
����
��δ�����ĵ�ַ�������ʹ�ϵ�󣬲����쳣���쳣�����жϲ�����
�ٴη���


*/
void TestExceptionMalloc(){
	g_p = new CStackManage();

	const static int page_size = 5;
	g_p ->StartMemory(5);
	printf("%p\r\n",g_p ->GetBaseAddress());

	UserStack(g_p->GetBaseAddress(),(char*)(g_p->GetBaseAddress())+PAGE_SIZE*page_size);

	PVOID p1 = g_p -> GetMemory(g_p  ->GetBaseAddress(),4*1024);

	//UserStack(g_p->GetBaseAddress(),(char*)(g_p->GetBaseAddress())+PAGE_SIZE*page_size);


}

/*
Э��ר�÷���ʱ��Ƭ�����š�Coroutine����ռ��P����״̬���棬�����Ŷӡ��൱��Sleep(0),���ǲ���������

���Ĵ���ѹջ Ȼ����ת�� ��Ԫ��������߼����ͷ�P��
*/
void WorkSleep(){

}


int _tmain(int argc, _TCHAR* argv[])
{
	TestExceptionMalloc();


	PCONTEXT a;


	return 0;
}


// TestTechnology.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "debug.h"

const static int PAGE_SIZE = 4*1024;

class CStackManage
{
public:


	//预定
	void StartMemory(size_t Number_Page_Size){
		m_Address = VirtualAlloc(NULL,Number_Page_Size*PAGE_SIZE,MEM_RESERVE,PAGE_EXECUTE_READWRITE);
	}

	//调拨
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

//标记上次触发异常的地址，防止异常死循环
LPVOID LastExceptionAddress=nullptr;

LONG StackExceptionDecide(EXCEPTION_RECORD SavedExceptRec,PVOID pMinStack,PVOID pMaxStack){
	/*如果是指定异常，查看内存是否在范围内*/

	/*
	在核心编程P658有简短介绍
	SavedExceptRec.ExceptionInformation只在AV异常被用到。
	SavedExceptRec.ExceptionInformation[0]		0表示读异常，1表示写异常
	另发现
	SavedExceptRec.ExceptionInformation[1]指向的内容是：异常产生地址，而不是代码地址。我们需要这个。
	SavedExceptRec.ExceptionInformation[2]似乎和[0]变化，不明。

	*/
	LPVOID ExceptionAdd =(LPVOID)SavedExceptRec.ExceptionInformation[1];

	if(EXCEPTION_ACCESS_VIOLATION==SavedExceptRec.ExceptionCode){
		if(ExceptionAdd>=pMinStack||ExceptionAdd<pMaxStack){
			if (ExceptionAdd==LastExceptionAddress)//检查上次触发异常的地址，防止异常死循环
			{
				return (EXCEPTION_CONTINUE_SEARCH);
			}
			else
			{
				ExceptionAdd==LastExceptionAddress;
			}
			g_p->GetMemory(ExceptionAdd,PAGE_SIZE*1);
			OutputDebug("继续执行\r\n");
			return (EXCEPTION_CONTINUE_EXECUTION);//继续执行

		}else{//非指定范围内异常 不管
			OutputDebug("非执行范围异常\r\n");
			return (EXCEPTION_CONTINUE_SEARCH);
		}
	}else{
		//非指定AV异常 不管
		OutputDebug("非执行异常\r\n");
		return (EXCEPTION_CONTINUE_SEARCH);
	}
}

void UserStack(PVOID pMinStack,PVOID pMaxStack/*不包括本地址*/){
	
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
测试
与未调拨的地址发生访问关系后，产生异常对异常进行判断并处理
再次访问


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
协程专用放弃时间片重新排。Coroutine放弃占用P，将状态保存，重新排队。相当于Sleep(0),但是不会阻塞。

将寄存器压栈 然后跳转到 单元打包重排逻辑。释放P。
*/
void WorkSleep(){

}


int _tmain(int argc, _TCHAR* argv[])
{
	TestExceptionMalloc();


	PCONTEXT a;


	return 0;
}


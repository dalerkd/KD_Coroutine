/*
###协程任务获取顺序：
本P的任务队列>全局>其他P
###P的流程
1. 获取任务/检查是否**全局退出**
2. 依照任务信息：恢复任务M的执行状态。标记执行状态。
3. 开始执行

4. 指定范围AV异常
拓展栈

5. 正常退出
销毁该协程申请的资源(其他类负责？)，并且。删除该任务在队列中。

5. 半路退出
保存当前信息为一个新的结点。将该节点的信息投入到全局任务队列。(建议由节点诞生类处理)
注意jmp出来是否会导致try出现问题之类？要不要裸函数？
*/





#include <windows.h>


extern bool ExitCoroutine;



/*
struct st_Node{
	eip
		pushad结果
		pushfd结果

		栈min
		栈max
		其他管理结构：暂停次数
		其他管理结构：当前状态：正在执行/未执行过

};*/


struct st_INFO_Coroutine{
	DWORD EIP;

	//pushad
	DWORD EAX;
	DWORD ECX;
	DWORD EDX;
	DWORD EBX;

	DWORD ESP;
	DWORD EBP;
	DWORD ESI;
	DWORD EDI;
	//pushad end

	DWORD EFLAGS;//pushfd

	DWORD Stack_Limit_Min;
	DWORD Stack_Limit_Max;

	DWORD PauseTimes;//暂停次数
	DWORD NowState;//正在执行/未执行过
};



/*
处理器函数
将该线程ID传入
*/
class CNodeDecide
{
public:
	st_INFO_Coroutine* GetTopNode(){}
protected:

private:

};

const static int PNumber = 5;
CNodeDecide* pCoroutineWorldNodeDecide[PNumber];

const static int RunState = 1;
const static int UnRunState = 0;
DWORD WINAPI Processor(DWORD ProID)
{
	//检查退出标记
	if (ExitCoroutine==true)
	{
		return 0;
	}

	CNodeDecide* p = pCoroutineWorldNodeDecide[ProID];

	st_INFO_Coroutine* pInfo = p->GetTopNode();
	//标记运行状态
	pInfo->NowState = RunState;

	//恢复运行状态
	/*
		异常监测的问题应该由处理共同处理。
	
	1. 太复杂了：
	如果该节点是由别的P处理过的，那么它的异常链中存放的是别的P的代码地址。

	除非协程异常检测代码存放在用户的代码中。
	或者独立的代码(即所有的P共用一段异常检测代码)？

	 P-----异常初始化函数-------被执行的协程代码

	 似乎可以。

	*/



}
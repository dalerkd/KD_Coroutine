/*
###Э�������ȡ˳��
��P���������>ȫ��>����P
###P������
1. ��ȡ����/����Ƿ�**ȫ���˳�**
2. ����������Ϣ���ָ�����M��ִ��״̬�����ִ��״̬��
3. ��ʼִ��

4. ָ����ΧAV�쳣
��չջ

5. �����˳�
���ٸ�Э���������Դ(�����ฺ��)�����ҡ�ɾ���������ڶ����С�

5. ��·�˳�
���浱ǰ��ϢΪһ���µĽ�㡣���ýڵ����ϢͶ�뵽ȫ��������С�(�����ɽڵ㵮���ദ��)
ע��jmp�����Ƿ�ᵼ��try��������֮�ࣿҪ��Ҫ�㺯����
*/





#include <windows.h>


extern bool ExitCoroutine;



/*
struct st_Node{
	eip
		pushad���
		pushfd���

		ջmin
		ջmax
		��������ṹ����ͣ����
		��������ṹ����ǰ״̬������ִ��/δִ�й�

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

	DWORD PauseTimes;//��ͣ����
	DWORD NowState;//����ִ��/δִ�й�
};



/*
����������
�����߳�ID����
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
	//����˳����
	if (ExitCoroutine==true)
	{
		return 0;
	}

	CNodeDecide* p = pCoroutineWorldNodeDecide[ProID];

	st_INFO_Coroutine* pInfo = p->GetTopNode();
	//�������״̬
	pInfo->NowState = RunState;

	//�ָ�����״̬
	/*
		�쳣��������Ӧ���ɴ���ͬ����
	
	1. ̫�����ˣ�
	����ýڵ����ɱ��P������ģ���ô�����쳣���д�ŵ��Ǳ��P�Ĵ����ַ��

	����Э���쳣�����������û��Ĵ����С�
	���߶����Ĵ���(�����е�P����һ���쳣������)��

	 P-----�쳣��ʼ������-------��ִ�е�Э�̴���

	 �ƺ����ԡ�

	*/



}
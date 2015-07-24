#include "stdafx.h"
#include "NewSocket.h"
#include "网络聊天室服务器端Dlg.h"
#include "网络聊天室服务器端.h"


NewSocket::NewSocket()
{
	m_Length = 0;
	memset(m_Buffer, 0, sizeof(m_Buffer));
}


NewSocket::~NewSocket()
{
	if (m_hSocket != INVALID_SOCKET) Close();
}


void NewSocket::OnReceive(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);

	C网络聊天室服务器端App *pApp = (C网络聊天室服务器端App*)AfxGetApp();
	C网络聊天室服务器端Dlg *pDlg = (C网络聊天室服务器端Dlg*)pApp->m_pMainWnd;
	CString tmp(m_Buffer), temp = L"接收到:";temp += tmp;
	pDlg->m_ListBox.InsertString(0, temp);

	if (memcmp(m_Buffer, "AmIConnected", sizeof("AmIConnected")-1) == 0)
	{
		my_SendData = L"YouAreConnected";
	}
	else
	{
		if (memcmp(m_Buffer, "LoginMyName", sizeof("LoginMyName")-1) == 0)
		{
			CString tmp1(&m_Buffer[sizeof("LoginMyName") - 1]);
			pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
			try
			{
				CString command1 = L"SELECT * FROM 用户表 WHERE 姓名 = '";command1 += tmp1;command1 += L"'";
				pDlg->m_pRecordSet->Open(_variant_t(command1), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			}
			catch (_com_error e)
			{
				CString errormessage;
				errormessage.Format(L"打开数据表失败!\r\n错误信息:%s", e.ErrorMessage());
				AfxMessageBox(errormessage);
				//发出退出命令给客户端
				//......
				PostQuitMessage(0);
			}
			if (!pDlg->m_pRecordSet->adoEOF)
			{
				//pDlg->m_ListBox.InsertString(0, (CString)pDlg->m_pRecordSet->GetCollect("账号"));
				my_SendData = L"HereYouAre";
				if (my_SendData != "")
				{
					int Length = 0;
					char Buffer[4096];
					memset(Buffer, 0, sizeof(Buffer));
					Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
					WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
					Buffer[Length + 1] = '\0';
					Send(Buffer, Length, 0);
					CString tmp(Buffer), temp = L"发送出:";temp += tmp;
					pDlg->m_ListBox.InsertString(0, temp);
				}

				memset(m_Buffer, 0, sizeof(m_Buffer));
				do
				{
					m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);
				} while (m_Buffer[0] == '\0');
				CString tmp(m_Buffer), temp = L"接收到:";temp += tmp;
				pDlg->m_ListBox.InsertString(0, temp);
				if (memcmp(m_Buffer, "LoginMyPassword", sizeof("LoginMyPassword") - 1) == 0)
				{
					CString tmp1(&m_Buffer[sizeof("LoginMyPassword") - 1]);
					if ((CString)pDlg->m_pRecordSet->GetCollect("密码") == tmp1)
					{
						my_SendData = L"YourPasswordIsRight";
						pDlg->m_pRecordSet->PutCollect("在线", _variant_t(L"Online"));
						pDlg->m_pRecordSet->Update();
						//_variant_t RecordsAffected;
						//pDlg->m_pServerDB->Execute("UPDATE 用户表 SET 在线 = '1' WHERE 姓名 = '张胜东'", &RecordsAffected, adCmdText);
					}
					else
					{
						my_SendData = L"YourPasswordIsWrong";
						pDlg->m_pRecordSet->PutCollect("在线", _variant_t(L"Offline"));
						pDlg->m_pRecordSet->Update();
						//_variant_t RecordsAffected;
						//pDlg->m_pServerDB->Execute("UPDATE 用户表 SET 在线 = '0' WHERE 姓名 = '张胜东'", &RecordsAffected, adCmdText);
					}
				}
			}
			else
			{
				my_SendData = L"YouAreNotHere";
			}

			pDlg->m_pRecordSet->Close();
		}
		else
		{
			if (memcmp(m_Buffer, "SearchFriendOnline", sizeof("SearchFriendOnline")-1) == 0)
			{
				CString tmp2(&m_Buffer[sizeof("SearchFriendOnline") - 1]);
				pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
				try
				{
					CString command2 = L"SELECT * FROM 用户表 WHERE 账号 = '";command2 += tmp2;command2 += L"'";
					pDlg->m_pRecordSet->Open(_variant_t(command2), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
				}
				catch (_com_error e)
				{
					CString errormessage;
					errormessage.Format(L"打开数据表失败!\r\n错误信息:%s", e.ErrorMessage());
					AfxMessageBox(errormessage);
					//发出退出命令给客户端
					//......
					PostQuitMessage(0);
				}
				if (!pDlg->m_pRecordSet->adoEOF)
				{
					if ((CString)pDlg->m_pRecordSet->GetCollect("在线") == L"Online")
					{
						my_SendData = L"Online";
					}
					else
					{
						my_SendData = L"Offline";
					}
				}
				else
				{
					//向客户端发送,查无此人
					//......
				}

				pDlg->m_pRecordSet->Close();
			}
		}
	}


	AsyncSelect(FD_WRITE);

	CAsyncSocket::OnReceive(nErrorCode);
}


void NewSocket::OnSend(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (my_SendData != "")
	{
		int Length = 0;
		char Buffer[4096];
		memset(Buffer, 0, sizeof(Buffer));
		Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
		Buffer[Length + 1] = '\0';
		Send(Buffer, Length, 0);

		C网络聊天室服务器端App *pApp = (C网络聊天室服务器端App*)AfxGetApp();
		C网络聊天室服务器端Dlg *pDlg = (C网络聊天室服务器端Dlg*)pApp->m_pMainWnd;
		CString tmp(Buffer), temp = L"发送出:";temp += tmp;
		pDlg->m_ListBox.InsertString(0, temp);
	}
	
	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}

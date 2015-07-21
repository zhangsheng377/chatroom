
// 网络聊天室客户端Dlg.h : 头文件
//

#include "ShowWaitDlg.h"
#include "NewSocket.h"
#include <vector>
//const int NameLengthMax = 10;
#pragma once


// C网络聊天室客户端Dlg 对话框
class C网络聊天室客户端Dlg : public CDialogEx
{
// 构造
public:
	C网络聊天室客户端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	
	CNewSocket m_Socket;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnNcPaint();
	static UINT WaitToConnectServer(LPVOID pParam);
	ShowWaitDlg *m_ShowWaitDlg;

	typedef struct ThreadInfo{
		CNewSocket *m_Socket;
		ShowWaitDlg *m_ShowWaitDlg;
		C网络聊天室客户端Dlg *m_Wind;
	}thread,*lpthread;

	_ConnectionPtr m_pClientDB;				//连接ADO数据库,把生成的.tlh复制到项目文件夹中
	_RecordsetPtr m_pRecordSet;
	void FreshFriendList();
	CListBox m_FriendList;

	class FRIEND {
	public:
		int account;
		//char name[NameLengthMax];
		CString name;
	};
	std::vector<FRIEND> friends;
};

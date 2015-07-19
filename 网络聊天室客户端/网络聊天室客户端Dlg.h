
// 网络聊天室客户端Dlg.h : 头文件
//

#include "ShowWaitDlg.h"

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
	_ConnectionPtr m_ClientDB;				//连接ADO数据库,把生成的.tlh复制到项目文件夹中
	ShowWaitDlg *m_ShowWaitDlg;
};

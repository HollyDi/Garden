
// DealJPGDlg.h : 头文件
//

#pragma once
#include<atlimage.h>
#include <direct.h> 
#include "afxcmn.h"
#include "afxwin.h"

// CDealJPGDlg 对话框
class CDealJPGDlg : public CDialogEx
{
// 构造
public:
	CDealJPGDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DEALJPG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	bool CDealJPGDlg::ChangeJPGSize(CString szOldFileName, CString szNewFilName);

	VOID CDealJPGDlg::FindAllFile(CString csOldDirectoryPath,CString csNewDirectoryPath);
	BOOL CDealJPGDlg::IsFileJPG(CString csPath);
	VOID CDealJPGDlg::EmptyDirectory(CString csDirectoryPath);
	VOID CDealJPGDlg::InitialPath();
	UINT CDealJPGDlg::GetDirectoryFileNum(CString csDirectoryPath);
	CString csOldPath;
	CString csNewPath;
public:
	CProgressCtrl m_ProgressCtrl;
	afx_msg void OnBnClickedButtonStart();
	CButton m_StartButton;
	UINT m_ulWidth;
	VOID CDealJPGDlg::CreateMyDirectory();
	afx_msg void OnBnClickedButtonEmptysou();
	afx_msg void OnBnClickedButtonEmptytar();
	VOID CDealJPGDlg::EmptyDirectory2(CString csDirectoryPath);
	BOOL m_IsEmpty;
	UINT n;
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

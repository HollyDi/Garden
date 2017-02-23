
// DealJPGDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DealJPG.h"
#include "DealJPGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDealJPGDlg �Ի���




CDealJPGDlg::CDealJPGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDealJPGDlg::IDD, pParent)
	, m_ulWidth(500)
	, m_IsEmpty(FALSE)
	, n(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	csOldPath = "E:\\���Ų���Ƭ\\������\\";
	csNewPath = "E:\\���Ų���Ƭ\\�Ѵ���\\";
}

void CDealJPGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_ProgressCtrl);
	DDX_Control(pDX, IDC_BUTTON_START, m_StartButton);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_ulWidth);
	DDX_Check(pDX, IDC_CHECK_ISEMPTYSOU, m_IsEmpty);
}

BEGIN_MESSAGE_MAP(CDealJPGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CDealJPGDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_EMPTYSOU, &CDealJPGDlg::OnBnClickedButtonEmptysou)
	ON_BN_CLICKED(IDC_BUTTON_EMPTYTAR, &CDealJPGDlg::OnBnClickedButtonEmptytar)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CDealJPGDlg ��Ϣ�������

BOOL CDealJPGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UpdateData(FALSE);

	DragAcceptFiles(TRUE);
	
	CreateMyDirectory();
	
	InitialPath();

	SetWindowText(L"���Ų�С����");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDealJPGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDealJPGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDealJPGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





bool CDealJPGDlg::ChangeJPGSize(CString szOldFileName, CString szNewFilName)
{
	UpdateData(TRUE);
	int WIDTH = m_ulWidth;
	int HEIGHT = m_ulWidth;
	CImage oldimg;
	CImage newimg;
	oldimg.Load(szOldFileName);
	if(oldimg.IsNull())
		return false;
	int nWidth = 0;
	int nHeight = 0;

	nWidth = oldimg.GetWidth();
	nHeight = oldimg.GetHeight();

	if(nWidth > WIDTH)
	{
		double dRatio = nWidth * 1.0 / nHeight;
		if(nWidth > nHeight)
		{
			nWidth = WIDTH;
			nHeight = nWidth / dRatio;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return FALSE;
	}

	if(!newimg.CreateEx(nWidth, nHeight, 24, BI_RGB))
	{
		oldimg.Destroy();
		return false;
	}

	int nPreMode = ::SetStretchBltMode(newimg.GetDC(),  HALFTONE);
	newimg.ReleaseDC();
	oldimg.Draw(newimg.GetDC(), 0, 0, nWidth, nHeight, 0, 0, oldimg.GetWidth(), oldimg.GetHeight());
	newimg.ReleaseDC();
	::SetBrushOrgEx(newimg.GetDC(), 0, 0, NULL); 
	newimg.ReleaseDC();
	::SetStretchBltMode(newimg.GetDC(), nPreMode);
	newimg.ReleaseDC();

	BOOL bOk = newimg.Save(szNewFilName);

	if (bOk != 0)
	{
//		MessageBox(L"�����Ѵ�����Ƭ��������·���Ƿ���Ч",L"Error",MB_OK|MB_ICONERROR);
	}
	newimg.Destroy();
	oldimg.Destroy();

	return true;
}


VOID CDealJPGDlg::FindAllFile(CString csOldDirectoryPath,CString csNewDirectoryPath)
{
	
	CFileFind FileFind;
	CString strPath = csOldDirectoryPath;
	CString csNewName;
	UINT ulFileNum = 0;
	BOOL bRet;

	if (strPath.Right(1) != "\\")
	{
		strPath += "\\";
	}

	strPath += "*.*";

	ulFileNum = GetDirectoryFileNum(strPath);

	if (ulFileNum == -1)
	{
		return;
	}
	else if (ulFileNum == 0)
	{
		MessageBox(L"ԴĿ¼Ϊ��",L"Attention" ,MB_OK);
	}

	m_ProgressCtrl.SetRange(0,ulFileNum + 1);
	m_ProgressCtrl.SetStep(1);
	m_ProgressCtrl.SetPos(1);

	if (FileFind.FindFile(strPath))
	{
		do 
		{
			bRet = FileFind.FindNextFile();
			if (FileFind.IsDots())
			{
				continue;
			}
			strPath = FileFind.GetFilePath();
			if (!FileFind.IsDirectory())
			{
				if (IsFileJPG(strPath))
				{
					csNewName.Empty();
					csNewName.Format(L"New_%d",++n);
					csNewName = csNewPath + csNewName;
					csNewName += ".jpg";
					if (!ChangeJPGSize(strPath,csNewName))
					{
						bRet = FALSE;
					}
					
					m_ProgressCtrl.StepIt();
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		} while (bRet);
	}

	UpdateData(TRUE);
	if (m_IsEmpty == TRUE)
	{
		EmptyDirectory2(csOldPath);
	}
	
}


BOOL CDealJPGDlg::IsFileJPG(CString csPath)
{
	CString strPath = csPath;
	if (strPath.Right(3) == _T("jpg") || strPath.Right(3) == _T("JPG"))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


VOID CDealJPGDlg::EmptyDirectory(CString csDirectoryPath)
{
	CFileFind FileFind;
	CString strPath = csDirectoryPath;
	BOOL bRet;
	
	if (strPath.Right(1) != "\\")
	{
		strPath += "\\";
	}

	strPath += "*.*";
	if (FileFind.FindFile(strPath))
	{
		do 
		{
			bRet = FileFind.FindNextFile();
			if (FileFind.IsDots())
			{
				continue;
			}
			strPath = FileFind.GetFilePath();
			if (!FileFind.IsDirectory())
			{
				
				::SetFileAttributes(strPath,FILE_ATTRIBUTE_NORMAL);
				::DeleteFile(strPath);
			}
			else
			{
				EmptyDirectory(strPath);
				::SetFileAttributes(strPath,FILE_ATTRIBUTE_NORMAL);
				::DeleteFile(strPath);
			}
		} while (bRet);
		MessageBox(L"���Ŀ¼�ɹ�",L"Success",MB_OK);
	}
	else
	{
		MessageBox(L"����Ŀ¼�Ƿ����",L"Error",MB_OK|MB_ICONERROR);
	}
}

VOID CDealJPGDlg::EmptyDirectory2(CString csDirectoryPath)
{
	CFileFind FileFind;
	CString strPath = csDirectoryPath;
	BOOL bRet;

	if (strPath.Right(1) != "\\")
	{
		strPath += "\\";
	}

	strPath += "*.*";
	if (FileFind.FindFile(strPath))
	{
		do 
		{
			bRet = FileFind.FindNextFile();
			if (FileFind.IsDots())
			{
				continue;
			}
			strPath = FileFind.GetFilePath();
			if (!FileFind.IsDirectory())
			{

				::SetFileAttributes(strPath,FILE_ATTRIBUTE_NORMAL);
				::DeleteFile(strPath);
			}
			else
			{
				EmptyDirectory(strPath);
				::SetFileAttributes(strPath,FILE_ATTRIBUTE_NORMAL);
				::DeleteFile(strPath);
			}
		} while (bRet);

	}
	else
	{
		
	}
}

VOID CDealJPGDlg::InitialPath()
{
	GetDlgItem(IDC_STATIC_SOUDIR)->SetWindowText(csOldPath);
	GetDlgItem(IDC_STATIC_TARDIR)->SetWindowText(csNewPath);
}

UINT CDealJPGDlg::GetDirectoryFileNum(CString csDirectoryPath)
{
	UINT ulFileNum = 0;

	CFileFind FileFind;
	CString strPath = csDirectoryPath;
	BOOL bRet;

	
	if (FileFind.FindFile(strPath))
	{
		do 
		{
			bRet = FileFind.FindNextFile();
			if (FileFind.IsDots())
			{
				continue;
			}
			strPath = FileFind.GetFilePath();
			if (!FileFind.IsDirectory())
			{
				ulFileNum++;
			}
		} while (bRet);
	}
	else
	{
		MessageBox(L"·����Ч,����ԴĿ¼�Ƿ����",L"Error",MB_OK | MB_ICONERROR);
		return -1;
	}

	return ulFileNum;
}

void CDealJPGDlg::OnBnClickedButtonStart()
{
	m_StartButton.EnableWindow(FALSE);
	FindAllFile(csOldPath,csNewPath);
	m_StartButton.EnableWindow(TRUE);
}


VOID CDealJPGDlg::CreateMyDirectory()
{
	CreateDirectory(L"E:\\���Ų���Ƭ",NULL);
	CreateDirectory(L"E:\\���Ų���Ƭ\\������",NULL);
	CreateDirectory(L"E:\\���Ų���Ƭ\\�Ѵ���",NULL);
}

void CDealJPGDlg::OnBnClickedButtonEmptysou()
{
	EmptyDirectory(csOldPath);
}


void CDealJPGDlg::OnBnClickedButtonEmptytar()
{
	EmptyDirectory(csNewPath);
	n = 0;
}


void CDealJPGDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	WCHAR wzFileName[MAX_PATH] = {0};
	DragQueryFile(hDropInfo,0,wzFileName,MAX_PATH);
	if (IsFileJPG(wzFileName))
	{
		CString csNewName;
		csNewName.Empty();
		csNewName.Format(L"New_%d",++n);
		csNewName = csNewPath + csNewName;
		csNewName += ".jpg";
		ChangeJPGSize(wzFileName,csNewName);
		MessageBox(L"�����޸ĳɹ�",L"Success",MB_OK);
	}
	else
	{
		MessageBox(L"������Ĳ���JPG�ļ�",L"Success",MB_OK|MB_ICONERROR);
	}

	CDialogEx::OnDropFiles(hDropInfo);
}

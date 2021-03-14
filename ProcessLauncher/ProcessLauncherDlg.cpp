
// ProcessLauncherDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "ProcessLauncher.h"
#include "ProcessLauncherDlg.h"
#include "afxdialogex.h"
#include <ctime>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CProcessLauncherDlg



CProcessLauncherDlg::CProcessLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessLauncherDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH, inPath);
	DDX_Control(pDX, IDC_LIST_LIST, inList);
	DDX_Control(pDX, IDC_LIST_TASK, taskList);
}

BEGIN_MESSAGE_MAP(CProcessLauncherDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CProcessLauncherDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CProcessLauncherDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_TO_TASK, &CProcessLauncherDlg::OnBnClickedButtonToTask)
	ON_BN_CLICKED(IDC_BUTTON_FROM_TASK, &CProcessLauncherDlg::OnBnClickedButtonFromTask)
	ON_BN_CLICKED(IDC_BUTTON_START, &CProcessLauncherDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_KILL, &CProcessLauncherDlg::OnBnClickedButtonKill)
	ON_WM_TIMER(ID_TIMER_1, &CProcessLauncherDlg::OnTimer)
END_MESSAGE_MAP()


// ����������� ��������� CProcessLauncherDlg

BOOL CProcessLauncherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// ����� � EditControl ��� ������� ��� ��� ������� ����
	wchar_t path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);									// ��������� ������� ������� ����������
	inPath.SetWindowText(path);

	// ��������� ������� � ListControl
	inList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT);		// LVS_EX_FULLROWSELECT - ��� ������ �������� ���������� ��� ������; LVS_EX_TRACKSELECT - ������������� ��������, �� ������� ������ ������
	inList.SetHoverTime(9999);												// ����� ������������ �������������
	inList.InsertColumn(0, L"��� �����", LVCFMT_LEFT, 364);					// �����, ���, ������������ � ������ �������

	taskList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT);
	taskList.SetHoverTime(9999);
	taskList.InsertColumn(0, L"����������", LVCFMT_LEFT, 250);
	taskList.InsertColumn(1, L"������", LVCFMT_LEFT, 114);
	taskList.InsertColumn(2, L"����", LVCFMT_LEFT, 0);
	taskList.InsertColumn(3, L"Handle", LVCFMT_LEFT, 0);

	CProcessLauncherDlg::OnBnClickedButtonRefresh();	// ��� ���������� ������ ������

	SetTimer(ID_TIMER_1, 500, NULL);

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CProcessLauncherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CProcessLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CProcessLauncherDlg::OnBnClickedButtonSelect()
{
	BROWSEINFO bi;
	wchar_t path[MAX_PATH];

	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = path;
	bi.lpszTitle = L"����� ����������";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;			// ���� ��� �������� ������ ��������� �������� �������
	bi.lpfn = NULL;
	bi.lParam = 0;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != NULL && SHGetPathFromIDList(pidl, path))
	{
		inPath.SetWindowText(path);
	}

	CProcessLauncherDlg::OnBnClickedButtonRefresh();
}


void CProcessLauncherDlg::OnBnClickedButtonRefresh()
{
	inList.DeleteAllItems();								// �������� ��������� �� ������

	CString dir;
	inPath.GetWindowText(dir);
	CFileFind tempFind;
	CString tempFileFind;
	tempFileFind.Format(_T("%s\\*.exe"), dir);				// ��� ���������� ������ *.exe

	BOOL isFinished = tempFind.FindFile(tempFileFind);		// ��������� ������ ������ ����������
	int counter = 0;
	while (isFinished)										// ���� ���� �� ����������� �����
	{
		isFinished = tempFind.FindNextFile();				// ������� � ���������� ����� �� ������ ������
		if (!tempFind.IsDots())								// ���� ��� �� �����
		{
			CString fileName = tempFind.GetFileName();		// ��������� ����� �����
			inList.InsertItem(counter, fileName);			// �������� � ������� � ������ counter
			counter++;
		}
	}
	tempFind.Close();
}


void CProcessLauncherDlg::OnBnClickedButtonToTask()
{
	if (inList.GetSelectedCount() == 0)
	{
		MessageBox(L"�������� ����������(�).", L"��������!", MB_ICONWARNING);
		return;
	}

	for (int i = 0; i < inList.GetItemCount(); i++)
	{
		if (inList.GetItemState(i, LVIS_SELECTED))
		{
			CString path;
			inPath.GetWindowText(path);

			taskList.InsertItem(taskList.GetItemCount(), inList.GetItemText(i, 0));
			taskList.SetItemText(taskList.GetItemCount() - 1, 1, L"�����������");
			taskList.SetItemText(taskList.GetItemCount() - 1, 2, path);
		}
	}
}


void CProcessLauncherDlg::OnBnClickedButtonFromTask()
{
	if (taskList.GetSelectedCount() == 0)
	{
		MessageBox(L"�������� ����������(�).", L"��������!", MB_ICONWARNING);
		return;
	}

	for (int i = 0; i < taskList.GetItemCount(); i++)
	{
		if (taskList.GetItemState(i, LVIS_SELECTED))
		{
			if (taskList.GetItemText(i, 1) == "��������")
			{
				MessageBox(L"������� ��������� ������� " + taskList.GetItemText(i, 0), L"��������!", MB_ICONWARNING);
				continue;
			}

			taskList.DeleteItem(i);
		}
	}
}


void CProcessLauncherDlg::OnBnClickedButtonStart()
{
	if (taskList.GetSelectedCount() != 1)
	{
		MessageBox(L"������������ �����", L"��������!", MB_ICONWARNING);
		return;
	}

	for (int i = 0; i < taskList.GetItemCount(); i++)
	{
		if (taskList.GetItemState(i, LVIS_SELECTED))
		{
			if (taskList.GetItemText(i, 1) == "��������")
			{
				MessageBox(L"������� ��� �������", L"��������!", MB_ICONWARNING);
				return;
			}

			STARTUPINFO info;
			PROCESS_INFORMATION processInfo;

			ZeroMemory(&info, sizeof(STARTUPINFO));						// ��������� ����������
			ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));

			if (CreateProcess(taskList.GetItemText(i, 2) + "\\" + taskList.GetItemText(i, 0), L"", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
			{
				CString handle;
				handle.Format(L"%d", processInfo.hProcess);

				taskList.SetItemText(i, 1, L"��������");
				taskList.SetItemText(i, 3, handle);
				break;
			}
			else
			{
				MessageBox(L"������ ������� ��������\n" + taskList.GetItemText(i, 2) + "\\" + taskList.GetItemText(i, 0), L"��������!", MB_ICONERROR);
				break;
			}
		}
	}
}


void CProcessLauncherDlg::OnBnClickedButtonKill()
{
	if (taskList.GetSelectedCount() != 1)
	{
		MessageBox(L"������������ �����", L"��������!", MB_ICONWARNING);
		return;
	}

	for (int i = 0; i < taskList.GetItemCount(); i++)
	{
		if (taskList.GetItemState(i, LVIS_SELECTED))
		{
			if (taskList.GetItemText(i, 1) == "�����������")
			{
				MessageBox(L"������� ��� ����������", L"��������!", MB_ICONWARNING);
				return;
			}

			if (!TerminateProcess((HANDLE)_wtoi(taskList.GetItemText(i, 3)), -1))
			{
				MessageBox(L"������ ��������� �������� " + taskList.GetItemText(i, 0), L"��������!", MB_ICONERROR);
			}
			else
			{
				taskList.SetItemText(i, 1, L"�����������");
			}

			break;
		}
	}
}


void CProcessLauncherDlg::OnTimer(UINT_PTR nIDEvent)
{
	DWORD exitCode;

	for (int i = 0; i < taskList.GetItemCount(); i++)
	{
		HANDLE handler = (HANDLE)_wtoi(taskList.GetItemText(i, 3));
		if (handler == 0)
		{
			continue;
		}

		GetExitCodeProcess(handler, &exitCode);
		if (exitCode != 0x103)								// DEC 259, HEX 0x103 - ���������� (�������) ��������
		{
			taskList.SetItemText(i, 1, L"�����������");
			taskList.SetItemText(i, 3, L"");
			CloseHandle(handler);
		}
	}
}


// ProcessLauncherDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// ���������� ���� CProcessLauncherDlg
class CProcessLauncherDlg : public CDialogEx
{
// ��������
public:
	CProcessLauncherDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_PROCESSLAUNCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSelect();
	// ��������� �������
	CEdit inPath;
	// ������ ������ � ����������
	CListCtrl inList;
	// ������ ������, ������� �����  �����������/���������������
	CListCtrl taskList;
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonToTask();
	afx_msg void OnBnClickedButtonFromTask();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonKill();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

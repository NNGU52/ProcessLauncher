
// ProcessLauncherDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CProcessLauncherDlg
class CProcessLauncherDlg : public CDialogEx
{
// Создание
public:
	CProcessLauncherDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_PROCESSLAUNCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSelect();
	// Выбранный каталог
	CEdit inPath;
	// Список файлов в директории
	CListCtrl inList;
	// Список файлов, которые будут  запускаться/останавливаться
	CListCtrl taskList;
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonToTask();
	afx_msg void OnBnClickedButtonFromTask();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonKill();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

// upnpDlg.h : ͷ�ļ�
//

#pragma once

#include "Resource.h"
#include "afxwin.h"
// CupnpDlg �Ի���
class CupnpDlg : public CDialog
{
// ����
public:
	CupnpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPNP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedButton1();

public:
	CEdit m_APort;
public:
	CEdit m_BPort;
public:
	BOOL m_rand;
};

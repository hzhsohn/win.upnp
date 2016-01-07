// upnpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "upnpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CupnpDlg �Ի���




CupnpDlg::CupnpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CupnpDlg::IDD, pParent)

	, m_rand(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CupnpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, m_APort);
	DDX_Control(pDX, IDC_EDIT2, m_BPort);
	DDX_Check(pDX, IDC_CHECK1, m_rand);
}

BEGIN_MESSAGE_MAP(CupnpDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CupnpDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CupnpDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CupnpDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CupnpDlg ��Ϣ�������

BOOL CupnpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	m_APort.SetWindowText(_T("2323"));
	m_BPort.SetWindowText(_T("2323"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CupnpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CupnpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CupnpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////      ���д���   ///////////////////////////////////////
#include "../upnp/CzhUPnP.h"

CzhUPnP g_upnp;
CzhUPnP::UPNPNAT_MAPPING g_mudp,g_mtcp;
void CupnpDlg::OnBnClickedOk()
{
	CString A;
	CString B;
////////////////////tcp
	m_APort.GetWindowText(A);
	m_BPort.GetWindowText(B);
	g_mtcp.internalPort = _ttoi(A.GetBuffer());
	g_mtcp.externalPort = _ttoi(B.GetBuffer());
	g_mtcp.protocol = CzhUPnP::UNAT_TCP;
	g_mtcp.description = _T("CzhUPnP-TCP");

	if(g_upnp.AddNATPortMapping(&g_mtcp,m_rand)== CzhUPnP::UNAT_OK ){
		TCHAR sss[150];
		wsprintf(sss,_T("Added UPnP NAT Support: (%s) NAT ROUTER/FIREWALL:%i -> %s:%i"),
					g_mtcp.description, g_mtcp.externalPort, g_upnp.GetLocalIPStr(), g_mtcp.internalPort);
		GetDlgItem(IDC_STATIC)->SetWindowText(sss);
	}
	else
	{
		MessageBox(g_upnp.GetLastError());
		return;
	}
//////////////////////udp
	g_mudp.internalPort = _ttoi(A.GetBuffer());;
	g_mudp.externalPort = _ttoi(B.GetBuffer());;
	g_mudp.protocol = CzhUPnP::UNAT_UDP;
	g_mudp.description = _T("CzhUPnP-UDP");

	if(g_upnp.AddNATPortMapping(&g_mudp,m_rand)== CzhUPnP::UNAT_OK ){
		TCHAR sss[150];
		wsprintf(sss,_T("Added UPnP NAT Support: (%s) NAT ROUTER/FIREWALL:%i -> %s:%i"),
					g_mudp.description, g_mudp.externalPort, g_upnp.GetLocalIPStr(), g_mudp.internalPort);
		GetDlgItem(IDC_STATIC2)->SetWindowText(sss);
	}
	else
	{
		MessageBox(g_upnp.GetLastError());
		return;
	}
}

void CupnpDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CupnpDlg::OnBnClickedButton1()
{
	if(g_upnp.RemoveNATPortMapping(g_mtcp)==CzhUPnP::UNAT_OK)
		GetDlgItem(IDC_STATIC)->SetWindowText(_T("�Ƴ�TCPӳ��ɹ�"));
	else
		GetDlgItem(IDC_STATIC)->SetWindowText(g_upnp.GetLastError());

	if(g_upnp.RemoveNATPortMapping(g_mudp)==CzhUPnP::UNAT_OK)
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("�Ƴ�UDPӳ��ɹ�"));
	else
		GetDlgItem(IDC_STATIC2)->SetWindowText(g_upnp.GetLastError());
}

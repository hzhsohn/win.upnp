// upnpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "upnpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CupnpDlg 对话框




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


// CupnpDlg 消息处理程序

BOOL CupnpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_APort.SetWindowText(_T("2323"));
	m_BPort.SetWindowText(_T("2323"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CupnpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CupnpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////      所有代码   ///////////////////////////////////////
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
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CupnpDlg::OnBnClickedButton1()
{
	if(g_upnp.RemoveNATPortMapping(g_mtcp)==CzhUPnP::UNAT_OK)
		GetDlgItem(IDC_STATIC)->SetWindowText(_T("移除TCP映射成功"));
	else
		GetDlgItem(IDC_STATIC)->SetWindowText(g_upnp.GetLastError());

	if(g_upnp.RemoveNATPortMapping(g_mudp)==CzhUPnP::UNAT_OK)
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("移除UDP映射成功"));
	else
		GetDlgItem(IDC_STATIC2)->SetWindowText(g_upnp.GetLastError());
}

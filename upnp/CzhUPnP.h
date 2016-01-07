#ifndef MYUPNP_H_

#pragma once
#include <afx.h>
#include <afxtempl.h>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

typedef unsigned long ulong;
typedef unsigned char		uchar;
typedef unsigned char		uint8;
typedef	  signed char		sint8;

typedef unsigned short		uint16;
typedef	  signed short		sint16;

typedef unsigned int		uint32;
typedef	  signed int		sint32;

typedef unsigned __int64	uint64;
typedef   signed __int64	sint64;

class  CzhUPnP
{
public:
	typedef enum _UPNPNAT_RETURN{
		UNAT_OK,						// Successfull
		UNAT_ERROR,						// Error, use GetLastError() to get an error description
		UNAT_NOT_OWNED_PORTMAPPING,		// Error, you are trying to remove a port mapping not owned by this class
		UNAT_EXTERNAL_PORT_IN_USE,		// Error, you are trying to add a port mapping with an external port in use
		UNAT_NOT_IN_LAN					// Error, you aren't in a LAN -> no router or firewall
	} UPNPNAT_RETURN;

	typedef enum _UPNPNAT_PROTOCOL{
		UNAT_TCP,						// TCP Protocol
		UNAT_UDP						// UDP Protocol
	} UPNPNAT_PROTOCOL;

	typedef struct _UPNPNAT_MAPPING{
		WORD internalPort;				// Port mapping internal port
		WORD externalPort;				// Port mapping external port
		UPNPNAT_PROTOCOL protocol;		// Protocol-> TCP (UPNPNAT_PROTOCOL:UNAT_TCP) || UDP (UPNPNAT_PROTOCOL:UNAT_UDP)
		CString description;			// Port mapping description
	} UPNPNAT_MAPPING;

	CzhUPnP();
	~CzhUPnP();

	UPNPNAT_RETURN AddNATPortMapping(UPNPNAT_MAPPING *mapping, bool tryRandom = false);
	UPNPNAT_RETURN RemoveNATPortMapping(UPNPNAT_MAPPING mapping, bool removeFromList = true);
	void clearNATPortMapping();

	CString		GetLastError();
	CString		GetLocalIPStr();
	WORD		GetLocalIP();
	bool		IsLANIP(WORD nIP);

protected:
	void		InitLocalIP();
	void		SetLastError(CString error);

	bool addPortmap(int eport, int iport, const CString& iclient,
					   const CString& descri, const CString& type);
	bool deletePortmap(int eport, const CString& type);

	bool		isComplete() const { return !m_controlurl.IsEmpty(); }

	bool		Search(int version=1);
	bool		GetDescription();
	CString		GetProperty(const CString& name, CString& response);
	bool		InvokeCommand(const CString& name, const CString& args);

	bool		Valid()const{return (!m_name.IsEmpty()&&!m_description.IsEmpty());}
	bool		InternalSearch(int version);
	CString		m_devicename;
	CString		m_name;
	CString		m_description;
	CString		m_baseurl;
	CString		m_controlurl;
	CString		m_friendlyname;
	CString		m_modelname;
	int			m_version;

private:
	CList<UPNPNAT_MAPPING, UPNPNAT_MAPPING> m_Mappings;

	CString		m_slocalIP;
	CString		m_slastError;
	WORD		m_uLocalIP;

	bool		isSearched;
};
#endif

/*
 * CPeer.cpp
 *
 *  Created on: 2011-12-29
 *      Author: wangwei
 */

#include "CPeer.h"

void NatPunchthroughServerFramework::Init(RakNet::RakPeerInterface *rakPeer)
{
	if (isSupported==SUPPORTED)
	{
		m_pNPS = new NatPunchthroughServer;
		rakPeer->AttachPlugin(m_pNPS);
		m_pNPS->SetDebugInterface(this);
		isSupported = QUERY;
	}
}

void NatPunchthroughServerFramework::Shutdown(RakNet::RakPeerInterface *rakPeer)
{
	if (m_pNPS)
	{
		rakPeer->DetachPlugin(m_pNPS);
		delete m_pNPS;
		m_pNPS = 0;
	}
	isSupported = SUPPORTED;
}

//CPeer::CPeer(unsigned short port, bool  server){
//    // TODO Auto-generated constructor stub
//
//     m_pPeer = RakPeerInterface::GetInstance();
//
//    socketDescriptors[0].port = port;
//    socketDescriptors[0].socketFamily=AF_INET; // Test out IPV4
//	if(!server)
//		m_pPeer->Startup(1,socketDescriptors, 1);
//
//
//}

CPeer::CPeer(unsigned short port, bool server, char * ip)
{
	 m_pPeer = RakPeerInterface::GetInstance();

	 socketDescriptors[0].port = port;

	 if(ip)
		 strcpy(socketDescriptors[0].hostAddress, ip);

	 socketDescriptors[0].socketFamily=AF_INET; // Test out IPV4
	 if(!server)
		 m_pPeer->Startup(100,socketDescriptors, 1);

	 m_pNatPunchServer = NULL;
}

CPeer::~CPeer(){
	if (m_pNatPunchServer)
	{
		m_pNatPunchServer->Shutdown(m_pPeer);
		delete m_pNatPunchServer;
	}
    RakPeerInterface::DestroyInstance(m_pPeer);
}

///创建一个主机
///参数[in]maxConnections 设置连接到此主机的连接数。
///参数[in]port 设置此主机端口号
///参数[in]passwordData 设置此主机的密码
///参数[in]passwordDataLength 此主机的密码长度。
///返回值见枚举StartupResult
StartupResult CPeer::Startup(unsigned     short     maxConnections,
                             unsigned     short     port,
                             const         char *   passwordData,
                                           int      passwordDataLength)
{
    m_pPeer->SetIncomingPassword(passwordData, passwordDataLength);
    m_pPeer->SetTimeoutTime(60000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);


    socketDescriptors[0].port = port;
    socketDescriptors[0].socketFamily=AF_INET; // Test out IPV4
    socketDescriptors[1].port = port;
    socketDescriptors[1].socketFamily=AF_INET6; // Test out IPV6

    StartupResult result;


	bool b = (result =m_pPeer->Startup(maxConnections, socketDescriptors, 1 ))==RakNet::RAKNET_STARTED;
	m_pPeer->SetMaximumIncomingConnections(maxConnections);
//	if (!b)
//	{
//		// Try again, but leave out IPV6
//		b = (result = m_pPeer->Startup(maxConnections, socketDescriptors, 1 ))==RakNet::RAKNET_STARTED;
//	}

	if (b)
	{
		if (!m_pNatPunchServer)
		{
			m_pNatPunchServer = new NatPunchthroughServerFramework;
			m_pNatPunchServer->Init(m_pPeer);
		}
	}

	m_pPeer->SetOccasionalPing(true);
	m_pPeer->SetUnreliableTimeout(1000);

    return result;
}

///使用IP地址或域名加端口连接到指定的主机。
///参数[in]host 要连接主机的IP或主机域名。
///参数[in]remotePort 要连接主机的端口。
///参数[in]passwordData 要连接主机的密码。
///参数[in]passwordDataLength 要连接主机的密码长度。
///返回值见枚举ConnectionAttemptResult
ConnectionAttemptResult CPeer::Connect( const       char *        	host,
                                        unsigned    short			remotePort,
                                        const       char *        	passwordData,
                                                    int     		passwordDataLength)
{
    ConnectionAttemptResult result;

    result = m_pPeer->Connect(host, remotePort, passwordData, passwordDataLength);

    return result;
}

///发送一块数据到指定的已连接的结点；
///第一个字节为这条消息的唯一标识；
///参数[in]data，表示要发送的数据；
///参数[in]length，表示发送数据的长度；
///参数[in]priority,表示发送数据的优先级，参见优先级描述；
///参数[in]reliability,表示发送数据的可靠性，参见可靠性描述；
///参数[in]systemIdentifer,接收者。
///参数[in]broadcast 当为true时表示发送消息到所有的已连接结点。
///返回值 0 表示参数有误. 其它数字标识此条信息.
uint32_t CPeer::Send(const     	char *             	 data,
                     const     	int                	 length,
                            	PacketPriority       priority,
                            	PacketReliability    reliability,
                     const    	AddressOrGUID        systemIdentifier,
                     	 	 	bool                 broadcast)
{
    uint32_t result;
    if(broadcast)
        result = m_pPeer->Send(data, length, priority, reliability, 0, UNASSIGNED_SYSTEM_ADDRESS, broadcast);
    else
        result = m_pPeer->Send(data, length, priority, reliability, 0, systemIdentifier, broadcast);

    return result;
}

uint32_t CPeer::Send(const RakNet::BitStream 				* bitStream,
										PacketPriority      	priority,
										PacketReliability   	reliability,
						const    		AddressOrGUID        systemIdentifier,
										bool	              broadcast)
{
	uint32_t result;
	if(broadcast)
		result = m_pPeer->Send(bitStream, priority, reliability, 0, UNASSIGNED_SYSTEM_ADDRESS, broadcast);
	else
		result = m_pPeer->Send(bitStream, priority, reliability, 0, systemIdentifier, broadcast);

	return result;
}

/// 从消息队列获取一个消息.
/// 处理完一个消息后使用DeallocatePacket()函数释放这个消息.
/// 返回值 0 表示没有消息包，否则将返回消息包的指针.
Packet* CPeer::Receive()
{
    return m_pPeer->Receive();
}

/// 当调用Receive（）处理完一个消息后，调用此函数将包释放
/// 参数[in] packet 消息包的指针.
void CPeer::DeallocatePacket(Packet *packet)
{
    m_pPeer->DeallocatePacket(packet);
}

///获取包的ID
///参数[in]p 表示收到数据包的指针。
///返回值为包的ID
unsigned char CPeer::GetPacketIdentifier(RakNet::Packet *p)
{
    if (p==0)
        return 255;

    if ((unsigned char)p->data[0] == ID_TIMESTAMP)
    {
        RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
        return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
    }
    else
        return (unsigned char) p->data[0];
}

///断开连接后，所有连接该结点的用户都将收到此用户断开消息
void CPeer::Disconnect()
{
	if (m_pNatPunchServer)
	{
		m_pNatPunchServer->Shutdown(m_pPeer);
		delete m_pNatPunchServer;
		m_pNatPunchServer = NULL;
	}
    m_pPeer->Shutdown(300);
}

///断开连接到本主机上的指定的客户端
///参数[in] target表示要断开的客户端连接
void CPeer::CloseConnection(const AddressOrGUID target)
{
    m_pPeer->CloseConnection(target, true, 0);
}

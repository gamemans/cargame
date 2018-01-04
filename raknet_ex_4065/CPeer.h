/*
 * CPeer.h
 *
 *  Created on: 2011-12-29
 *      Author: wangwei
 */

#ifndef CPEER_H_
#define CPEER_H_

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "RakNetTypes.h"

#include "NatPunchthroughServer.h"
using namespace RakNet;

enum FeatureSupport
{
	SUPPORTED,
	UNSUPPORTED,
	QUERY
};

struct SampleFramework
{
	virtual ~SampleFramework() {}
	virtual const char * QueryName(void)=0;
	virtual const char * QueryRequirements(void)=0;
	virtual const char * QueryFunction(void)=0;
	virtual void Init(RakNet::RakPeerInterface *rakPeer)=0;
	virtual void ProcessPacket(RakNet::RakPeerInterface *rakPeer, Packet *packet)=0;
	virtual void Shutdown(RakNet::RakPeerInterface *rakPeer)=0;

	FeatureSupport isSupported;
};

struct NatPunchthroughServerFramework : public SampleFramework, public NatPunchthroughServerDebugInterface_Printf
{
public:
	NatPunchthroughServerFramework() {isSupported=SUPPORTED; m_pNPS=0;}
	virtual ~NatPunchthroughServerFramework() {}
	virtual const char * QueryName(void) {return "NatPunchthroughServerFramework";}
	virtual const char * QueryRequirements(void) {return "None";}
	virtual const char * QueryFunction(void) {return "Coordinates NATPunchthroughClient.";}
	virtual void Init(RakNet::RakPeerInterface *rakPeer);
	virtual void ProcessPacket(RakNet::RakPeerInterface *rakPeer, Packet *packet){}
	virtual void Shutdown(RakNet::RakPeerInterface *rakPeer);
private:
	NatPunchthroughServer *m_pNPS;
};

class CPeer {
public:
    //CPeer(unsigned short port, bool server = true);
    CPeer(unsigned short port, bool server = true, char * ip = NULL);
    virtual ~CPeer();


    ///创建一个主机
    ///参数[in] 设置连接到此主机的连接数。
    ///参数[in] 设置此主机端口号
    ///参数[in] 设置此主机的密码
    ///参数[in] 此主机的密码长度。
    ///返回值见枚举StartupResult
    StartupResult Startup(	unsigned     short     	maxConnections,
    						unsigned     short     	port = 0,
    						const        char *    	passwordData = NULL,
    									 int 		passwordDataLength = 0);


    ///使用IP地址或域名加端口连接到指定的主机。
    ///参数[in] 要连接主机的IP或主机域名。
    ///参数[in] 要连接主机的端口。
    ///参数[in] 要连接主机的密码。
    ///参数[in] 要连接主机的密码长度。
    ///返回值见枚举ConnectionAttemptResult
    virtual ConnectionAttemptResult Connect(const       char *     	host,
                                            unsigned    short     	remotePort = 0,
                                            const       char *    	passwordData = NULL,
                                                        int			passwordDataLength = 0);


    ///发送一块数据到指定的已连接的结点；
    ///第一个字节为这条消息的唯一标识；
    ///参数[in]data，表示要发送的数据；
    ///参数[in]length，表示发送数据的长度；
    ///参数[in]priority,表示发送数据的优先级，参见优先级描述；
    ///参数[in]reliability,表示发送数据的可靠性，参见可靠性描述；
    ///参数[in]systemIdentifer,接收者。
    ///参数[in]broadcast 当为true时表示发送消息到所有的已连接结点。
    ///返回值 0 表示参数有误. 其它数字标识此条信息.
    virtual uint32_t Send(const		char *                data,
                          const     int                   length,
                          	  	  	PacketPriority        priority,
                                    PacketReliability     reliability,
                          const     AddressOrGUID         systemIdentifier,
                                    bool                  broadcast = false);


    uint32_t Send(const 	RakNet::BitStream		* bitStream,
    						PacketPriority    	priority,
    						PacketReliability   	reliability,
    				const 	AddressOrGUID        systemIdentifier,
    						bool	              broadcast);

    /// 从消息队列获取一个消息.
    /// 处理完一个消息后使用DeallocatePacket()函数释放这个消息.
    /// 返回值 0 表示没有消息包，否则将返回消息包的指针.
    virtual Packet* Receive( void );

    /// 当调用Receive（）处理完一个消息后，调用此函数将包释放
    /// 参数[in] packet 消息包的指针.
    virtual void DeallocatePacket( Packet *packet );

    ///获取包的ID
    ///参数[in]p 表示收到数据包的指针。
    ///返回值为包的ID
    static unsigned char GetPacketIdentifier(RakNet::Packet *p);

    ///断开连接后，所有连接该结点的用户都将收到此用户断开消息
    void Disconnect();

    ///断开连接到本主机上的指定的客户端
    ///参数[in] target表示要断开的客户端连接
    void CloseConnection(const AddressOrGUID target);

public:
    RakNet::RakPeerInterface * m_pPeer;

private:
    // Holds packets
    RakNet::Packet* m_pPacket;

    // GetPacketIdentifier returns this
    unsigned char packetIdentifier;

    ///Socket描述
    SocketDescriptor socketDescriptors[2];

    SampleFramework* m_pNatPunchServer;
};

#endif /* CPEER_H_ */

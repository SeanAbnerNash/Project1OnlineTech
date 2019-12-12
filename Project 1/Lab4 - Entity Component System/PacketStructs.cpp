#include "PacketStructs.h"

//@Author Sean Nash & Oisin Wilson
//@Login C00217019 & C00213826
//Project 1
//Time Taken 8 Hours.	

namespace PS
{
	ChatMessage::ChatMessage(const std::string & msg)
		:m_message(msg)
	{
	}

	std::shared_ptr<Packet> ChatMessage::toPacket()
	{
		std::shared_ptr<Packet> p = std::make_shared<Packet>();
		p->Append(PacketType::ChatMessage);
		p->Append(m_message.size());
		p->Append(m_message);
		return p;
	}

	std::shared_ptr<Packet> FileDataBuffer::toPacket()
	{
		std::shared_ptr<Packet> p = std::make_shared<Packet>();
		p->Append(PacketType::FileTransferByteBuffer);
		p->Append(m_size);
		p->Append(m_databuffer, m_size);
		return p;
	}


	ConnectionID::ConnectionID(const std::string& str)
		:m_message(str)
	{
	}

	std::shared_ptr<Packet> ConnectionID::toPacket()

	{
		std::shared_ptr<Packet> p = std::make_shared<Packet>();
		p->Append(PacketType::ConnectionID);
		p->Append(m_message.size());
		p->Append(m_message);
		return p;
	}
}
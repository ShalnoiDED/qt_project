#ifndef A03TEXTMESSAGE_H
#define A03TEXTMESSAGE_H

#include "../Packet.h"

class A03TextMessage : public Packet {
public:
    A03TextMessage(const QString& sender, const QString& receiver, bool received) {
        header.packetType = PacketType::TextMessage;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с подтверждением получения
        payload = received ? "MessageReceived" : "MessageNotReceived";
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isReceived() const {
        return payload == "MessageReceived";
    }
};

#endif // A03TEXTMESSAGE_H

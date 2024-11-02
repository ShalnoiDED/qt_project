#ifndef C03TEXTMESSAGE_H
#define C03TEXTMESSAGE_H

#include "../Packet.h"

class C03TextMessage : public Packet {
public:
    C03TextMessage(const QString& sender, const QString& receiver, const QString& message) {
        header.packetType = PacketType::TextMessage;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с текстом сообщения
        payload = message.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    QString getMessage() const {
        return QString::fromUtf8(payload);
    }
};

#endif // C03TEXTMESSAGE_H

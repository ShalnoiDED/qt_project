#ifndef R03TEXTMESSAGE_H
#define R03TEXTMESSAGE_H

#include "../Packet.h"

class R03TextMessage : public Packet {
public:
    R03TextMessage(const QString& sender, const QString& receiver, bool delivered, const QString& statusMessage) {
        header.packetType = PacketType::TextMessage;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с результатом доставки сообщения и статусом
        payload = QByteArray("delivered=") + (delivered ? "true" : "false") + ";status=" + statusMessage.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isDelivered() const {
        return QString(payload).section(';', 0, 0).split('=').value(1) == "true";
    }

    QString getStatusMessage() const {
        return QString(payload).section(';', 1, 1).split('=').value(1);
    }
};

#endif // R03TEXTMESSAGE_H

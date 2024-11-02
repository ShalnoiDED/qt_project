#ifndef R05CONNECTIONCHECK_H
#define R05CONNECTIONCHECK_H

#include "../Packet.h"

class R05ConnectionCheck : public Packet {
public:
    R05ConnectionCheck(const QString& sender, const QString& receiver, bool active, const QString& statusMessage) {
        header.packetType = PacketType::ConnectionCheck;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с результатом проверки активности и статусом соединения
        payload = QByteArray("active=") + (active ? "true" : "false") + ";status=" + statusMessage.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isActive() const {
        return QString(payload).section(';', 0, 0).split('=').value(1) == "true";
    }

    QString getStatusMessage() const {
        return QString(payload).section(';', 1, 1).split('=').value(1);
    }
};

#endif // R05CONNECTIONCHECK_H

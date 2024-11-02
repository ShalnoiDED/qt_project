#ifndef A05CONNECTIONCHECK_H
#define A05CONNECTIONCHECK_H

#include "../Packet.h"

class A05ConnectionCheck : public Packet {
public:
    A05ConnectionCheck(const QString& sender, const QString& receiver) {
        header.packetType = PacketType::ConnectionCheck;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с ответом на проверку активности
        payload = QByteArray("Pong");
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    QByteArray getPayload() const {
        return payload;
    }
};

#endif // A05CONNECTIONCHECK_H

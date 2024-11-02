#ifndef C05CONNECTIONCHECK_H
#define C05CONNECTIONCHECK_H

#include "../Packet.h"

class C05ConnectionCheck : public Packet {
public:
    C05ConnectionCheck(const QString& sender, const QString& receiver) {
        header.packetType = PacketType::ConnectionCheck;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Полезная нагрузка пустая, так как пакет предназначен только для проверки активности
        payload = QByteArray("Ping");
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    QByteArray getPayload() const {
        return payload;
    }
};

#endif // C05CONNECTIONCHECK_H

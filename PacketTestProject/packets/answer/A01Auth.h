#ifndef A01AUTH_H
#define A01AUTH_H

#include "../Packet.h"

class A01Auth : public Packet {
public:
    A01Auth(const QString& sender, const QString& receiver, bool success) {
        header.packetType = PacketType::Authorization;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с результатом авторизации
        payload = success ? "Success" : "Failure";
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isSuccess() const {
        return payload == "Success";
    }
};

#endif // A01AUTH_H

#ifndef A02AUTHRESPONSE_H
#define A02AUTHRESPONSE_H

#include "../Packet.h"

class A02AuthResponse : public Packet {
public:
    A02AuthResponse(const QString& sender, const QString& receiver, bool authSuccessful, const QString& message) {
        header.packetType = PacketType::AuthorizationResponse;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с результатом авторизации и сообщением
        payload = QByteArray("authSuccessful=") + (authSuccessful ? "true" : "false") + ";message=" + message.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isAuthSuccessful() const {
        return QString(payload).section(';', 0, 0).split('=').value(1) == "true";
    }

    QString getMessage() const {
        return QString(payload).section(';', 1, 1).split('=').value(1);
    }
};

#endif // A02AUTHRESPONSE_H

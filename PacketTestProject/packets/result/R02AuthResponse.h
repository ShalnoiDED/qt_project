#ifndef R02AUTHRESPONSE_H
#define R02AUTHRESPONSE_H

#include "../Packet.h"

class R02AuthResponse : public Packet {
public:
    R02AuthResponse(const QString& sender, const QString& receiver, bool authorized, const QString& details) {
        header.packetType = PacketType::AuthorizationResponse;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с деталями авторизации и сообщением
        payload = QByteArray("authorized=") + (authorized ? "true" : "false") + ";details=" + details.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isAuthorized() const {
        return QString(payload).section(';', 0, 0).split('=').value(1) == "true";
    }

    QString getDetails() const {
        return QString(payload).section(';', 1, 1).split('=').value(1);
    }
};

#endif // R02AUTHRESPONSE_H

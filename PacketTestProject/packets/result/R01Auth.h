#ifndef R01AUTH_H
#define R01AUTH_H

#include "../Packet.h"

class R01Auth : public Packet {
public:
    R01Auth(const QString& sender, const QString& receiver, bool authorized, const QString& message) {
        header.packetType = PacketType::Authorization;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с результатом авторизации и сообщением
        payload = QByteArray("authorized=") + (authorized ? "true" : "false") + ";message=" + message.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isAuthorized() const {
        return QString(payload).section(';', 0, 0).split('=').value(1) == "true";
    }

    QString getMessage() const {
        return QString(payload).section(';', 1, 1).split('=').value(1);
    }
};

#endif // R01AUTH_H

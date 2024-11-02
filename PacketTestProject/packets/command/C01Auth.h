#ifndef C01AUTH_H
#define C01AUTH_H

#include "../Packet.h"

class C01Auth : public Packet {
public:
    C01Auth(const QString& sender, const QString& receiver, const QString& username, const QString& password) {
        header.packetType = PacketType::Authorization;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с данными авторизации
        payload = QByteArray("username=" + username.toUtf8() + ";password=" + password.toUtf8());
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    QString getUsername() const {
        // Разбор строки полезной нагрузки для получения имени пользователя
        return QString(payload).section(';', 0, 0).split('=').value(1);
    }

    QString getPassword() const {
        // Разбор строки полезной нагрузки для получения пароля
        return QString(payload).section(';', 1, 1).split('=').value(1);
    }
};

#endif // C01AUTH_H

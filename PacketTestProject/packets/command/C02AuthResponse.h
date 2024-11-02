#ifndef C02AUTHRESPONSE_H
#define C02AUTHRESPONSE_H

#include "../Packet.h"

class C02AuthResponse : public Packet {
public:
    C02AuthResponse(const QString& sender, const QString& receiver, bool authGranted) {
        header.packetType = PacketType::AuthorizationResponse;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с флагом успешной авторизации
        payload = authGranted ? "AuthGranted" : "AuthDenied";
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isAuthGranted() const {
        return payload == "AuthGranted";
    }
};

#endif // C02AUTHRESPONSE_H

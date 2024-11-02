#ifndef A06ERRORREPORT_H
#define A06ERRORREPORT_H

#include "../Packet.h"

class A06ErrorReport : public Packet {
public:
    A06ErrorReport(const QString& sender, const QString& receiver, bool errorReceived) {
        header.packetType = PacketType::ErrorReport;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с подтверждением получения сообщения об ошибке
        payload = errorReceived ? "ErrorReceived" : "ErrorNotReceived";
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isErrorReceived() const {
        return payload == "ErrorReceived";
    }
};

#endif // A06ERRORREPORT_H

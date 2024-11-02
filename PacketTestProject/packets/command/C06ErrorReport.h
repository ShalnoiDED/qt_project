#ifndef C06ERRORREPORT_H
#define C06ERRORREPORT_H

#include "../Packet.h"

class C06ErrorReport : public Packet {
public:
    C06ErrorReport(const QString& sender, const QString& receiver, const QString& errorMessage) {
        header.packetType = PacketType::ErrorReport;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с сообщением об ошибке
        payload = errorMessage.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    QString getErrorMessage() const {
        return QString::fromUtf8(payload);
    }
};

#endif // C06ERRORREPORT_H

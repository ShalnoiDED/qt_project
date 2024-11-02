#ifndef R06ERRORREPORT_H
#define R06ERRORREPORT_H

#include "../Packet.h"

class R06ErrorReport : public Packet {
public:
    R06ErrorReport(const QString& sender, const QString& receiver, bool resolved, const QString& resolutionMessage) {
        header.packetType = PacketType::ErrorReport;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с результатом обработки ошибки и статусом решения
        payload = QByteArray("resolved=") + (resolved ? "true" : "false") + ";resolution=" + resolutionMessage.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isResolved() const {
        return QString(payload).section(';', 0, 0).split('=').value(1) == "true";
    }

    QString getResolutionMessage() const {
        return QString(payload).section(';', 1, 1).split('=').value(1);
    }
};

#endif // R06ERRORREPORT_H

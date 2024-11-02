#ifndef R04DATATRANSFER_H
#define R04DATATRANSFER_H

#include "../Packet.h"

class R04DataTransfer : public Packet {
public:
    R04DataTransfer(const QString& sender, const QString& receiver, bool success, const QString& statusMessage) {
        header.packetType = PacketType::DataTransfer;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с результатом передачи данных и статусом
        payload = QByteArray("success=") + (success ? "true" : "false") + ";status=" + statusMessage.toUtf8();
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isSuccess() const {
        return QString(payload).section(';', 0, 0).split('=').value(1) == "true";
    }

    QString getStatusMessage() const {
        return QString(payload).section(';', 1, 1).split('=').value(1);
    }
};

#endif // R04DATATRANSFER_H

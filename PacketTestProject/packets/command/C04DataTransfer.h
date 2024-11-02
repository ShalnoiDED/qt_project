#ifndef C04DATATRANSFER_H
#define C04DATATRANSFER_H

#include "../Packet.h"

class C04DataTransfer : public Packet {
public:
    C04DataTransfer(const QString& sender, const QString& receiver, const QByteArray& data) {
        header.packetType = PacketType::DataTransfer;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с данными
        payload = data;
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    QByteArray getData() const {
        return payload;
    }
};

#endif // C04DATATRANSFER_H

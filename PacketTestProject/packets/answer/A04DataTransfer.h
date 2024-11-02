#ifndef A04DATATRANSFER_H
#define A04DATATRANSFER_H

#include "../Packet.h"

class A04DataTransfer : public Packet {
public:
    A04DataTransfer(const QString& sender, const QString& receiver, bool dataReceived) {
        header.packetType = PacketType::DataTransfer;
        header.senderAddress = sender;
        header.receiverAddress = receiver;
        header.timestamp = QDateTime::currentDateTime();

        // Устанавливаем полезную нагрузку с подтверждением получения данных
        payload = dataReceived ? "DataReceived" : "DataNotReceived";
        header.dataLength = payload.size();

        // Вычисляем контрольную сумму
        checksum = calculateChecksum(payload);
    }

    bool isDataReceived() const {
        return payload == "DataReceived";
    }
};

#endif // A04DATATRANSFER_H

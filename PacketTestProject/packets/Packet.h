#ifndef PACKET_H
#define PACKET_H

#include <QString>
#include <QDateTime>
#include <QByteArray>

enum PacketType {
    Authorization,
    AuthorizationResponse,
    TextMessage,
    DataTransfer,
    ConnectionCheck,
    ErrorReport
};

// Базовая структура заголовка пакета
struct PacketHeader {
    PacketType packetType;      // Тип пакета
    uint32_t dataLength;        // Длина данных
    QString senderAddress;      // Адрес отправителя
    QString receiverAddress;    // Адрес получателя
    QDateTime timestamp;        // Временная метка
};

// Базовый класс для пакетов
class Packet {
public:
    PacketHeader header;         // Заголовок пакета
    QByteArray payload;          // Полезная нагрузка
    uint32_t checksum;           // Контрольная сумма для проверки целостности

    virtual ~Packet() = default;

protected:
    // Метод для вычисления контрольной суммы
    uint32_t calculateChecksum(const QByteArray& data) const {
        uint32_t checksum = 0;
        for (auto byte : data) {
            checksum += static_cast<uint8_t>(byte);
        }
        return checksum;
    }
};

#endif // PACKET_H

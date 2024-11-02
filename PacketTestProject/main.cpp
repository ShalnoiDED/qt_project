#include <QCoreApplication>
#include <QDebug>

#include "packets/answer/A01Auth.h"
#include "packets/command/C01Auth.h"
#include "packets/result/R01Auth.h"

#include "packets/answer/A02AuthResponse.h"
#include "packets/command/C02AuthResponse.h"
#include "packets/result/R02AuthResponse.h"

#include "packets/answer/A03TextMessage.h"
#include "packets/command/C03TextMessage.h"
#include "packets/result/R03TextMessage.h"

#include "packets/answer/A04DataTransfer.h"
#include "packets/command/C04DataTransfer.h"
#include "packets/result/R04DataTransfer.h"

#include "packets/answer/A05ConnectionCheck.h"
#include "packets/command/C05ConnectionCheck.h"
#include "packets/result/R05ConnectionCheck.h"

#include "packets/answer/A06ErrorReport.h"
#include "packets/command/C06ErrorReport.h"
#include "packets/result/R06ErrorReport.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Тест пакета авторизации
    C01Auth authCommand("user1", "server", "user1", "password123");
    qDebug() << "C01Auth created with payload:" << authCommand.getPassword();

    A01Auth authAnswer("server", "user1", true);
    qDebug() << "A01Auth received:" << authAnswer.isSuccess();

    R01Auth authResult("server", "user1", true, "Authorization successful");
    qDebug() << "R01Auth status:" << authResult.isAuthorized() << "Message:" << authResult.getMessage();

    // Тест пакетов для авторизационного ответа
    C02AuthResponse authResponseCommand("client", "server", true);
    qDebug() << "AuthResponseCommand created. Auth granted:" << authResponseCommand.isAuthGranted();

    A02AuthResponse authResponseAnswer("server", "client", true, "Welcome, user!");
    qDebug() << "AuthResponseAnswer status:" << authResponseAnswer.isAuthSuccessful() << "Message:" << authResponseAnswer.getMessage();

    R02AuthResponse authResponseResult("server", "client", true, "User authenticated successfully.");
    qDebug() << "AuthResponseResult status:" << authResponseResult.isAuthorized() << "Details:" << authResponseResult.getDetails();

    // Тест пакета текстового сообщения
    C03TextMessage textMessage("user1", "user2", "Hello, World!");
    qDebug() << "C03TextMessage with message:" << textMessage.getMessage();

    A03TextMessage textAnswer("user2", "user1", true);
    qDebug() << "A03TextMessage received:" << textAnswer.isReceived();

    R03TextMessage textResult("user2", "user1", true, "Delivered successfully");
    qDebug() << "R03TextMessage delivered:" << textResult.isDelivered() << "Status:" << textResult.getStatusMessage();

    // Тест пакета передачи данных
    QByteArray dataPayload("Sample data");
    C04DataTransfer dataCommand("user1", "user2", dataPayload);
    qDebug() << "C04DataTransfer with data:" << dataCommand.getData();

    A04DataTransfer dataAnswer("user2", "user1", true);
    qDebug() << "A04DataTransfer received:" << dataAnswer.isDataReceived();

    R04DataTransfer dataResult("user2", "user1", true, "Transfer successful");
    qDebug() << "R04DataTransfer success:" << dataResult.isSuccess() << "Status:" << dataResult.getStatusMessage();

    // Тест пакета проверки активности
    C05ConnectionCheck connCheck("client", "server");
    qDebug() << "C05ConnectionCheck payload:" << connCheck.getPayload();

    A05ConnectionCheck connAnswer("server", "client");
    qDebug() << "A05ConnectionCheck payload:" << connAnswer.getPayload();

    R05ConnectionCheck connResult("server", "client", true, "Connection active");
    qDebug() << "R05ConnectionCheck active:" << connResult.isActive() << "Status:" << connResult.getStatusMessage();

    // Тест пакета об ошибке
    C06ErrorReport errorCommand("client", "server", "Unknown error occurred");
    qDebug() << "C06ErrorReport message:" << errorCommand.getErrorMessage();

    A06ErrorReport errorAnswer("server", "client", true);
    qDebug() << "A06ErrorReport received:" << errorAnswer.isErrorReceived();

    R06ErrorReport errorResult("server", "client", false, "Issue unresolved");
    qDebug() << "R06ErrorReport resolved:" << errorResult.isResolved() << "Resolution message:" << errorResult.getResolutionMessage();

    return a.exec();
}

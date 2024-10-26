#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QListWidget>
#include <QSplitter>

class MessengerWindow : public QWidget {
    Q_OBJECT

public:
    MessengerWindow(QWidget *parent = nullptr) : QWidget(parent) {

        QSplitter *splitter = new QSplitter(this);

        chatList = new QListWidget(this);
        chatList->addItem("Chat 1");
        chatList->addItem("Chat 2");
        chatList->addItem("Chat 3");

        QWidget *messageWidget = new QWidget(this);
        QVBoxLayout *messageLayout = new QVBoxLayout(messageWidget);

        messageList = new QListWidget(this);
        messageLayout->addWidget(messageList);

        inputField = new QLineEdit(this);
        messageLayout->addWidget(inputField);

        QPushButton *sendButton = new QPushButton("Send", this);
        messageLayout->addWidget(sendButton);

        splitter->addWidget(chatList);
        splitter->addWidget(messageWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(splitter);

        connect(sendButton, &QPushButton::clicked, this, &MessengerWindow::sendMessage);
        connect(inputField, &QLineEdit::returnPressed, this, &MessengerWindow::sendMessage);

        connect(chatList, &QListWidget::itemClicked, this, &MessengerWindow::chatSelected);
    }

private slots:
    void sendMessage() {
        QString message = inputField->text();
        if (!message.isEmpty()) {
            messageList->addItem(message);
            inputField->clear();
        }
    }

    void chatSelected(QListWidgetItem *item) {
        messageList->clear();
        messageList->addItem("Selected chat: " + item->text());
    }

private:
    QLineEdit *inputField;
    QListWidget *messageList;
    QListWidget *chatList;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MessengerWindow window;
    window.setWindowTitle("Messenger");
    window.resize(600, 400);
    window.show();

    return app.exec();
}

#include "main.moc"

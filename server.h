#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTcpSocket>

class QLabel;
class QPushButton;
class QTcpServer;
class QNetworkSession;

//------------------------------------------------------------------
enum COMMAND{
    CONNECT,
    CONNECT_RESP,
    SHAKE,
    SHAKE_RESP,
    CHECKIN,
    CHECKIN_RESP,
    COMMIT,
    COMMIT_RESP,
    ROLLBACK,
    ROLLBACK_RESP,
    TERMINATE,
    TERMINATE_RESP,
    CHARGE,
    CHARGE_RESP
};

enum COMMAND_LENGTH{
    LENGTH_CONNECT         = 44,
    LENGTH_CONNECT_RESP    = 20,
    LENGTH_SHAKE           = 16,
    LENGTH_SHAKE_RESP      = 20,
    LENGTH_CHECKIN         = 98,
    LENGTH_CHECKIN_RESP    = 82,
    LENGTH_COMMIT          = 78,
    LENGTH_COMMIT_RESP     = 20,
    LENGTH_ROLLBACK        = 70,
    LENGTH_ROLLBACK_RESP   = 20,
    LENGTH_TERMINATE       = 16,
    LENGTH_TERMINATE_RESP  = 20,
    LENGTH_CHARGE          = 48,
    LENGTH_CHARGE_RESP     = 74
};
//------------------------------------------------------------------
struct Header{
  int MsgLength;
  int CommandId;
  int RequestId;
  int SessionId;
};

struct ConnectMsg{
    Header header;
    char Username[10];
    char Password[10];
    int Station;
    int Timeout;
};

struct ShakeMsg{
    Header header;
};

struct EncryptMsg{
    int MsgLength;
    char* MsgContent;
};

class Server : public QDialog
{
    Q_OBJECT

public:
    Server(QWidget *parent = 0);

private slots:
    void sessionOpened();
    void sendFortune();
    void createSocket();
    void readyRead();

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QTcpServer *tcpServer;
    QStringList fortunes;
    QNetworkSession *networkSession;
    QTcpSocket *tcpSocket;

    QByteArray decrypt(char* input, int size, int &cmdType);
};

#endif

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QHostAddress>
#include <QAbstractSocket>

class Server : public QObject{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
    ~Server();

    QTcpServer *server;
    QTcpSocket *socket;
    bool imaKonekciju;

public slots:
    void novaKonekcija();
    void primanjePoruke();

signals:
    void dobijeneKoordinate(int, int, int, int);
};

#endif // SERVER_H

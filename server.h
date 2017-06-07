#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
    ~Server();

    QTcpServer *server;
    QTcpSocket *socket;

public slots:
    void newConnection();
    //void incomingConnection(quintptr socketDescriptor) override;
    void startRead();
};

#endif // SERVER_H

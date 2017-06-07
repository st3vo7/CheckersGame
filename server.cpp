#include "server.h"
#include "game.h"

#include <QTime>

Server::Server(QObject *parent)
    : QObject(parent)
{
    socket = NULL;
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(server->listen(QHostAddress::Any, 1234))
        qDebug() << "Server osluskuje!";
    else
        qDebug() << "Server ne osluskuje!";
}

Server::~Server(){
    if(socket != NULL)
        socket->close();

    if(server != NULL)
        server->close();

    delete socket;
    delete server;
}

void Server::newConnection(){
    socket = server->nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), this, SLOT(startRead()));

    startRead();

    socket->waitForBytesWritten(3000);
}
/*
void Server::incomingConnection(qintptr socketDescriptor){
    Connection *connection = new Connection(this);
    connection->setSocketDescriptor(socketDescriptor);
    emit newConnection(connection);
}*/

void Server::startRead(){
   // QString odKlijenta = QString::fromUtf8(socket->readAll());

}

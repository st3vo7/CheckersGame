#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent)
{
    socket = NULL;
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(novaKonekcija()));
}

Server::~Server(){
    if(socket != NULL)
        socket->close();

    if(server != NULL)
        server->close();

    delete socket;
    delete server;
}

void Server::novaKonekcija(){
    if(!imaKonekciju){
        socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), this, SLOT(primanjePoruke()));
        connect(socket, SIGNAL(connected()), this, SLOT(konektovan()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(diskonektovan()));

        imaKonekciju = true;
    }
}

void Server::primanjePoruke(){
    QString poruka(QString::fromUtf8(socket->readAll()));
    qDebug() << poruka;
    QStringList lista = poruka.split(",");
    int fx = lista[1].toInt();
    int fy = lista[2].toInt();
    int px = lista[3].toInt();
    int py = lista[4].toInt();

    emit dobijeneKoordinate(fx, fy, px, py);
}

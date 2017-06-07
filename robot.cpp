#include "robot.h"
#include "game.h"
#include "potez.h"
#include "figure.h"
#include <vector>
#include <QtTest/QTest>
#include <QString>
#include <string>
#include <bits/stdc++.h>



using namespace std;
extern Game* game;



/*Robot::Robot()
    :_najvecaEfikasnost(0)
{
    _dubina=dubina;
}*/

Potez Robot::vratiNajboljiPotez()
{
    cout<<"U funkciji vratiNajboljipotez1 sam"<<endl;
    std::vector<Potez> moguciPotezi = generisiPoteze("PLAYER2");
    cout<<"Generisao sam vektor mogucih poteza za igraca 2"<<endl;
    cout<<"BROJ MOGUCIH POTEZA JE: "<<moguciPotezi.size()<<endl;
    for(unsigned i=0;i<moguciPotezi.size();i++){
        cout<<"Probam jedan potez"<<endl;
        cout<<"stare koordinate figure iz moguciPotezi:x "<<moguciPotezi[i].vratiFiguru()->getX()<<" y"<<moguciPotezi[i].vratiFiguru()->getY()<<endl;
        probajPotez(moguciPotezi[i]);
        cout<<"nove koordinate figure iz moguciPotezi:x "<<moguciPotezi[i].vratiFiguru()->getX()<<" y"<<moguciPotezi[i].vratiFiguru()->getY()<<endl;

        //odigram taj potez i sad mi treba metod koji ce da ga oceni
        //i da vrati taj skor. Tako uradim za svaki potez i smestim ocene u vektor
        //pozovem onda AlfaBeta nad tim vektorom.
        //Na kraju prodjem kroz vektor poteza i vratim onaj koji ima skor
        //koji mi je vratio AlfaBeta
        //plot twist mislim da je to samo dubine 1 mozda bih ja to trebao
        //da implementiram u AlfaBeta metodu da mi radi do dubine 4
        int sc=0;
        //int sc =  moguciPotezi[i].vratiRezultat();
         sc+=AlfaBeta(0,MIN_SCORE,MAX_SCORE,true);
        //moguciPotezi[i].
        //postavi sc na _score za taj
        moguciPotezi[i].postaviRezultat(sc);
        inverzPotez(moguciPotezi[i]);

        //ostaje da ponovo prodjes i vratis onaj sa najboljom ocenom

    }

//    OVAJ NACIN TREBA DA RADI
//    std::sort(moguciPotezi.begin(),moguciPotezi.end()); //tu mi prijavljuje gresku
//                                                         //iako sam overloadovao operator <
//    unsigned i=0;
//    for(;i<moguciPotezi.size();i++){
//        if(moguciPotezi[i].vratiRezultat() != moguciPotezi[i+1].vratiRezultat())
//            break;
//    }

//    srand(time(NULL));
//    int index = (i!=0?rand()%i:0);
//    Potez rez = moguciPotezi[index];
//    return rez;

//    POMOCNO RESENJE 1
//      Potez rez = moguciPotezi[1];
//      return rez;

//    POMOCNO RESENJE 2
    if(moguciPotezi.size()!=0){
      int max=moguciPotezi[0].vratiRezultat();
      for(unsigned i=1;i<moguciPotezi.size();i++){
          if(moguciPotezi[i].vratiRezultat() >= max)
              max=moguciPotezi[i].vratiRezultat();
      }
      for(unsigned i=1;i<moguciPotezi.size();i++){
          if(moguciPotezi[i].vratiRezultat() == max)
              return moguciPotezi[i];
      }
    }
    else{
        cout<<"UU la la la"<<endl;
        game->displayEndWindow("Player1");
    }

    /*if(moguciPotezi.size()!=0)
        return moguciPotezi[0];
    else{
        //game->end();
        game->displayEndWindow("Player1");
        //kako da ga sprecim da nastavi dalje??
    }*/

}

Potez Robot::vratiNajboljiPotez2()
{
    cout<<"U funkciji vratiNajbolji potez2 sam"<<endl;
    std::vector<Potez> moguciPotezi = generisiPoteze("PLAYER2");
    cout<<"Generisao sam vektor mogucih poteza za igraca 2"<<endl;
    cout<<"BROJ MOGUCIH POTEZA JE: "<<moguciPotezi.size()<<endl;
 /*   for(unsigned i=0;i<moguciPotezi.size();i++){
        cout<<"Probam jedan potez"<<endl;
        cout<<"stare koordinate figure iz moguciPotezi:x "<<moguciPotezi[i].vratiFiguru()->getX()<<" y"<<moguciPotezi[i].vratiFiguru()->getY()<<endl;
        probajPotez(moguciPotezi[i]);
        cout<<"nove koordinate figure iz moguciPotezi:x "<<moguciPotezi[i].vratiFiguru()->getX()<<" y"<<moguciPotezi[i].vratiFiguru()->getY()<<endl;

        //odigram taj potez i sad mi treba metod koji ce da ga oceni
        //i da vrati taj skor. Tako uradim za svaki potez i smestim ocene u vektor
        //pozovem onda AlfaBeta nad tim vektorom.
        //Na kraju prodjem kroz vektor poteza i vratim onaj koji ima skor
        //koji mi je vratio AlfaBeta
        //plot twist mislim da je to samo dubine 1 mozda bih ja to trebao
        //da implementiram u AlfaBeta metodu da mi radi do dubine 4
        int sc=0;
        //int sc =  moguciPotezi[i].vratiRezultat();
         sc+=AlfaBeta(0,MIN_SCORE,MAX_SCORE,true);
        //moguciPotezi[i].
        //postavi sc na _score za taj
        moguciPotezi[i].postaviRezultat(sc);
        inverzPotez(moguciPotezi[i]);

        //ostaje da ponovo prodjes i vratis onaj sa najboljom ocenom

    }

//    OVAJ NACIN TREBA DA RADI
//    std::sort(moguciPotezi.begin(),moguciPotezi.end()); //tu mi prijavljuje gresku
//                                                         //iako sam overloadovao operator <
//    unsigned i=0;
//    for(;i<moguciPotezi.size();i++){
//        if(moguciPotezi[i].vratiRezultat() != moguciPotezi[i+1].vratiRezultat())
//            break;
//    }

//    srand(time(NULL));
//    int index = (i!=0?rand()%i:0);
//    Potez rez = moguciPotezi[index];
//    return rez;

//    POMOCNO RESENJE 1
//      Potez rez = moguciPotezi[1];
//      return rez;

//    POMOCNO RESENJE 2
    if(moguciPotezi.size()!=0){
      int max=moguciPotezi[0].vratiRezultat();
      for(unsigned i=1;i<moguciPotezi.size();i++){
          if(moguciPotezi[i].vratiRezultat() >= max)
              max=moguciPotezi[i].vratiRezultat();
      }
      for(unsigned i=1;i<moguciPotezi.size();i++){
          if(moguciPotezi[i].vratiRezultat() == max)
              return moguciPotezi[i];
      }
    }
    else{
        game->displayEndWindow("Player1");
    }*/
    cout<<"Dosao sam do ovde"<<endl;
    if(moguciPotezi.size()==0){
        //game->end();
        //on nikada ne udje ovde
        cout<<"UU la la la la"<<endl;
        game->displayEndWindow("Player1");
        //QApplication::quit();
        //kako da ga sprecim da nastavi dalje??

    }
    else
        return moguciPotezi[qrand()%moguciPotezi.size()];


}

void Robot::odigraj()
{

    cout<<"U funkciji odigraj1 sam"<<endl;
    Potez p = vratiNajboljiPotez();
    cout<<"Napravio sam potez koji cu da odigram"<<endl;
    //sad izvrsi potez p
    //vidi ovo sa
    //jer treba i to da prikazes na tabli i da postavis lepo u figures
    Figure *f1 = p.vratiFiguru();
    cout<<"napravio sam figuru od poteza"<<endl;
    /*game->pickUpFigure(f1);
    koord(this);
    game->f->setZValue(100);*/
//    for(int i=0;i<game->table->figures.length();i++){
//        if(game->table->figures[i]->pos()==f1->pos())
//            game->scene->removeItem(game->table->figures[i]);
//    }

    Field *p1 = p.vratiNovoPolje();
    cout<<"napravio sam polje od poteza"<<endl;
    /*game->f->setX(p1->getx());
    game->f->setY(p1->gety());*/

    game->placeFigure1(f1,p1);
    cout<<"X koordinata novog polja:"<<p1->getx()<<"Y koordinata novog polja"<<p1->gety()<<endl;
    cout<<"pozvao sam placefigure1"<<endl;


    for(int i=0;i<game->table->figures.length();i++){
        if(game->table->figures[i]->getOwner()=="h")
            game->table->figures[i]->setOwner("NONE");
            if(game->table->figures[i]->notEmpty(game->table->figures[i]) && game->table->figures[i]->getOwner()=="NONE")
                game->scene->removeItem(game->table->figures[i]);
    }

}

void Robot::odigraj2()
{
    cout<<"U funkciji odigraj2 sam"<<endl;
    Potez p = vratiNajboljiPotez2();
    cout<<"Napravio sam potez koji cu da odigram"<<endl;
    //sad izvrsi potez p
    //vidi ovo sa
    //jer treba i to da prikazes na tabli i da postavis lepo u figures
    //if(p!=NULL)
    Figure *f1 = p.vratiFiguru();
    cout<<"napravio sam figuru od poteza"<<endl;
    /*game->pickUpFigure(f1);
    koord(this);
    game->f->setZValue(100);*/
//    for(int i=0;i<game->table->figures.length();i++){
//        if(game->table->figures[i]->pos()==f1->pos())
//            game->scene->removeItem(game->table->figures[i]);
//    }

    Field *p1 = p.vratiNovoPolje();
    cout<<"napravio sam polje od poteza"<<endl;
    /*game->f->setX(p1->getx());
    game->f->setY(p1->gety());*/

    game->placeFigure1(f1,p1);
    cout<<"X koordinata novog polja:"<<p1->getx()<<"Y koordinata novog polja"<<p1->gety()<<endl;
    cout<<"pozvao sam placefigure1"<<endl;


    for(int i=0;i<game->table->figures.length();i++){
        if(game->table->figures[i]->getOwner()=="h")
            game->table->figures[i]->setOwner("NONE");
            if(game->table->figures[i]->notEmpty(game->table->figures[i]) && game->table->figures[i]->getOwner()=="NONE")
                game->scene->removeItem(game->table->figures[i]);
    }

}

void Robot::probajPotez(Potez p)
{
    //nisam siguran da ovo sljaka bas tako (vidi sa Milicom)
    //msm da moras i da "izbrises" njegovu figuru
    //i da je dodas u figures

    //ustvari hocu da menjamkopiju vektora figures,
    //jer moram i unazad da se vracam, kao da necu taj potez

    //Figure *f = p.vratiFiguru();
    cout<<"Napravim figuru"<<endl;
    /*Field *p1 p.vratiFiguru()= p.vratiNovoPolje();*/
    cout<<"I novo polje"<<endl;
    cout<<"koordinate novog polja:x "<<p.vratiNovoPolje()->getx()<<
          "y "<<p.vratiNovoPolje()->gety()<<endl;
    p.vratiFiguru()->setX(p.vratiNovoPolje()->getx());
    p.vratiFiguru()->setY(p.vratiNovoPolje()->gety());
   // cout<<"I postavim je na polje"<<endl;
    //game->placeFigure1(f);

}

void Robot::inverzPotez(Potez p)
{
    //Figure *f=p.vratiFiguru();
    //Field *p1 = p.vratiStaroPolje();
    p.vratiFiguru()->setX(p.vratiStaroPolje()->getx());
    p.vratiFiguru()->setY(p.vratiStaroPolje()->gety());

}

bool Robot::skrozokej(Figure *f)
{
    if ((f->getX()==4 || f->getX()==78 || f->getX()==152 ||f->getX()==226 ||f->getX()==300 ||f->getX()==374 ||f->getX()==448 ||f->getX()==522) && (f->getY()==4 || f->getY()==78 || f->getY()==152 ||f->getY()==226 ||f->getY()==300 ||f->getY()==374 ||f->getY()==448 ||f->getY()==522))
        return true;
    return false;

}


std::vector<Potez> Robot::generisiPoteze(string igrac)
{
    cout<<"U funkciji generisiPoteze sam"<<endl;
    std::vector<Potez> v;
    cout<<"Napravio sam prazan vektor poteza v velicine "<<v.size()<<endl;
    int i=0;
    for(i;i<game->table->figures.size();i++){
       // cout<<"Krecem se kroz figures po i koji je velicine"<<game->table->figures.size()<<endl;
        //Figure *f=game->table->figures[i];
        //cout<<"Napravim novu figuru f koja je figures[i]"<<endl;
        QString qigrac = QString::fromStdString(igrac);
        if(game->table->figures[i]->getOwner() == qigrac){
            cout<<"figura je bas od igraca argumenta f-je"<<endl;
           // game->table->figures[i]->probna();//sumnjivo mesto no. 1! checked
            if(game->checkIfKonflikt(game->whosTurn)){
                if(game->table->figures[i]->hasConf())
                    game->postaviH(game->table->figures[i],game->table->figures[i]->getX(),game->table->figures[i]->getY());

            else
                continue;
            }
            game->postaviH(game->table->figures[i],game->table->figures[i]->getX(),game->table->figures[i]->getY());


            cout<<"pozovem cukica za nju"<<endl;
            //game->validan(f,f->getX(),f->getY());
            cout<<"odredim validna polja"<<endl;
            int j=0;
            for(j;j<game->table->figures.size();j++){
                cout<<"krecem se kroz figures cija je duzina"<<game->table->figures.size()<<endl;
                if(game->table->figures[j]->getOwner()=="h"){
                    cout<<"j mi je:"<<j<<endl;

                    cout<<"H figura koord: x"<<game->table->figures[j]->getX()<<" y"<<game->table->figures[j]->getY()<<endl;
                    cout<<"trazim h polja"<<endl;
                    if(skrozokej(game->table->figures[j])){

                    Field *f1 = new Field(game->table->figures[i]->getX(),game->table->figures[i]->getY());
                    cout<<"Koordinate starog polja: x"<<f1->getx()<<"y "<<f1->gety()<<endl;
                    //Field *f2 = new Field(game->table->figures[j]->getX(),game->table->figures[j]->getY());
                    Field *f2=new Field();
                    f2->setx(game->table->figures[j]->getX());
                    f2->sety(game->table->figures[j]->getY());
                    cout<<"Koordinate novog polja: x"<<f2->getx()<<" y "<<f2->gety()<<endl;
                    Potez *p = new Potez(game->table->figures[i],f1,f2,0);
                    cout<<"napravio sam potez"<<endl;
                    v.push_back(*p);
                    cout<<"gurnuo sam ga u v"<<endl;
                    }


                    if(j!=game->table->figures.size()-1){
                        cout<<"vlasnik j+1 je:"<<game->table->figures[j+1]->getOwner().toStdString()<<endl;

                        cout<<"sa sledecim koordinatama:X "<<game->table->figures[j+1]->getX()<<
                              "i Y"<<game->table->figures[j+1]->getY()<<endl;

                        if(skrozokej(game->table->figures[j+1])){

                            cout<<"jeste skrozokej"<<endl;
                            Field *f1 = new Field(game->table->figures[i]->getX(),game->table->figures[i]->getY());
                            cout<<"Koordinate starog polja: x"<<f1->getx()<<"y "<<f1->gety()<<endl;
                            //Field *f2 = new Field(game->table->figures[j]->getX(),game->table->figures[j]->getY());
                            Field *f2=new Field();
                            f2->setx(game->table->figures[j+1]->getX());
                            f2->sety(game->table->figures[j+1]->getY());
                            cout<<"Koordinate novog polja: x"<<f2->getx()<<" y "<<f2->gety()<<endl;
                            Potez *p = new Potez(game->table->figures[i],f1,f2,0);
                            cout<<"napravio sam potez"<<endl;
                            v.push_back(*p);
                            cout<<"gurnuo sam ga u v"<<endl;
                          }


                    }

                    //if(j==game->table->figures.size()){
                        cout<<"Zovem cukica2 da imitira desni klik"<<endl;
                        game->pobrisiHove();
                        cout<<"Cukic 2 je imitirao desni klik"<<endl;
                       // }

                }
            }
            cout<<"zovem cukica2 da imitira desni klik"<<endl;
            game->pobrisiHove();
            cout<<"cukic 2 je imitirao desni klik"<<endl;


        }

    }
    cout<<"Vracam v"<<endl;
    return v;
    cout<<"Vratio sam v"<<endl;
}

int Robot::AlfaBeta(int depth, int alfa, int beta, bool max)
{
    //mozda treba da mu prosledim potez kao argument
    //ili ovaj metod da prebacim u klasu potez
    //pa da pozivam sa p->AlfaBeta();

    cout<<"Usao sam u alfabeta"<<endl;
    if(depth==1){
        cout<<"zovem evaluate"<<endl;
        return evaluate("PLAYER2");//msm da ovde treba za komp igraca
    }

    if(game->end()){
        return max ? MAX_SCORE : MIN_SCORE;
        cout<<"jeste kraj igre"<<endl;
    }
    cout<<"nije kraj igre"<<endl;
    std::vector<Potez> detePotezi;

    if(max){
        cout<<"generisacu decu za p1"<<endl;
        detePotezi = generisiPoteze("PLAYER1");
        cout<<"generisao sam ih i smestio u detePotezi za p1"<<endl;
    }

    else{
        cout<<"generisacu decu za p2"<<endl;
        detePotezi = generisiPoteze("PLAYER2");
        cout<<"generisao sam ih i smestio u detePotezi za p2"<<endl;
    }

    cout<<"Da li je dete potezi prazno?"<<endl;
    if(detePotezi.empty())
        return max ? MAX_SCORE : MIN_SCORE;
    cout<<"NIJE"<<endl;

    int vr;
    if(max){
        cout<<"cvor robota"<<endl;
        vr=MIN_SCORE;

        for(unsigned i=0;i<detePotezi.size();i++){
            probajPotez(detePotezi[i]);
//        for(std::vector<Potez>::iterator it = detePotezi.begin(); it!=detePotezi.end();it++){
//            probajPotez(it);

            vr=std::max(vr,AlfaBeta(depth+1,alfa,beta,!max));
            alfa=std::max(alfa,vr);
            inverzPotez(detePotezi[i]);

            if(beta <= alfa)
                break;
        }
        return vr;
    }

    else{
        vr=MAX_SCORE;

        for(unsigned i=0;i<detePotezi.size();i++){
            probajPotez(detePotezi[i]);

//        for(std::vector<Potez>::iterator it = detePotezi.begin(); it!=detePotezi.end();it++){
//            probajPotez(it);
            vr=std::min(vr,AlfaBeta(depth+1,alfa,beta,max));
            beta=std::min(beta,vr);
            inverzPotez(detePotezi[i]);

            if(beta <= alfa)
                break;
        }
        return vr;
    }

   // qDebug() << "Ovde, ako sam dosao, onda nesto ne valja";
    return 0;

   /* if(max){
        int best = MIN_SCORE;
        //msm da ovde nece moci 2
        for(unsigned i =0;i<2;i++){
            int val=AlfaBeta(depth+1,alfa, beta,false);
            best=max(best,val);
            alfa=max(alfa,best);

            if(beta <= alfa)
                break;
        }
        return best;
    }
    else
    {
        int best=MAX_SCORE;
        for(unsigned i=0;i<2;i++){
            int val = AlfaBeta(depth+1,alfa,beta,true);
            best=min(best,val);
            beta=min(beta,best);

            if(beta<=alfa)
                break;
        }
        return best;

        }
    }*/
}

int Robot::evaluate(string igrac)
{
    cout<<"U FUNKCIJI EVALUATE SAM"<<endl;
    int score=0;
    int brFiguraRobot=0, brFiguraIgrac=0;
    int brKraljicaRobot=0, brKraljicaIgrac=0;

    QString qkomp = QString::fromStdString(igrac);
    QString qprotivnik = QString::fromStdString("PLAYER1");

    for(int i=0;i<game->table->figures.size();i++){
        if(game->table->figures[i]->getOwner()==qkomp){
            if(game->table->figures[i]->isQueen)
                brKraljicaRobot++;
            else brFiguraRobot++;
        }
        if(game->table->figures[i]->getOwner()==qprotivnik){
            if(game->table->figures[i]->isQueen)
                brKraljicaIgrac++;
            else brFiguraIgrac++;
        }
    }

    if (brFiguraIgrac+brKraljicaIgrac==0)
        return MAX_SCORE;

    if(brFiguraRobot+brKraljicaRobot==0)
        return MIN_SCORE;

    score=brFiguraRobot+2*brKraljicaRobot-brFiguraIgrac-2*brKraljicaIgrac;
    return score;
    cout<<"izlazim iz nje"<<endl;

}

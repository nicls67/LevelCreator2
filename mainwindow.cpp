/*
 *Creation de niveau pour Sobokan
 *
 *v2.0
 *
 *14/05/2013
 *
 */

#include "mainwindow.h"




/*
 *Constructeur
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //resize(400,400);
    zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    QGridLayout *layoutGrille = new QGridLayout;
    QGroupBox *boxGrille = new QGroupBox("Position des objets");
    QGroupBox *boxMario = new QGroupBox("Position de Mario");

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            groupbox[i][j]= new QGroupBox("Case "+QString::number(i+1)+","+QString::number(j+1));
            layoutGrille->addWidget(groupbox[i][j],i,j);

            radioButton[i][j][0] = new QRadioButton("Vide");
            radioButton[i][j][1] = new QRadioButton("Mur");
            radioButton[i][j][2] = new QRadioButton("Caisse");
            radioButton[i][j][3] = new QRadioButton("Objectif");
            radioButton[i][j][0]->setChecked(true);

            vbox[i][j] = new QVBoxLayout;
            vbox[i][j]->addWidget(radioButton[i][j][0]);
            vbox[i][j]->addWidget(radioButton[i][j][1]);
            vbox[i][j]->addWidget(radioButton[i][j][2]);
            vbox[i][j]->addWidget(radioButton[i][j][3]);

            groupbox[i][j]->setLayout(vbox[i][j]);
        }
    }
    boxGrille->setLayout(layoutGrille);

    QLabel *labelY = new QLabel("Ligne : ");
    QLabel *labelX = new QLabel("Colonne : ");
    spinBoxY = new QSpinBox;
    spinBoxX = new QSpinBox;
    spinBoxX->setRange(1,W);
    spinBoxY->setRange(1,H);
    QHBoxLayout *layoutMario1 = new QHBoxLayout;
    QHBoxLayout *layoutMario2 = new QHBoxLayout;
    QVBoxLayout *layoutMario = new QVBoxLayout;
    layoutMario1->addWidget(labelX);
    layoutMario1->addWidget(spinBoxX);
    layoutMario2->addWidget(labelY);
    layoutMario2->addWidget(spinBoxY);
    layoutMario->addLayout(layoutMario1);
    layoutMario->addLayout(layoutMario2);
    boxMario->setLayout(layoutMario);


    QPushButton *button = new QPushButton("Enregistrer");


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(boxGrille);

    QVBoxLayout *layoutDroite = new QVBoxLayout;
    layoutDroite->addWidget(boxMario);
    layoutDroite->addWidget(button);

    layout->addLayout(layoutDroite);

    connect(button,SIGNAL(clicked()),this,SLOT(createMap()));

    zoneCentrale->setLayout(layout);
}

MainWindow::~MainWindow()
{
    
}

int MainWindow::type_obj(QRadioButton *b[4]){
    int i;

    if(b[1]->isChecked()==true)
        i=MUR;
    else if (b[2]->isChecked()==true)
        i=CAISSE;
    else if (b[3]->isChecked()==true)
        i=OBJECTIF;
    else
        i=VIDE;

    return i;
}

void MainWindow::createMap(){
    int tab[H][W];
    position pos;
    int nbCaisse=0;
    int nbObj=0;

    //creation carte
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            tab[i][j]=type_obj(radioButton[i][j]);
            if(tab[i][j]==CAISSE)
                nbCaisse++;
            if(tab[i][j]==OBJECTIF)
                nbObj++;
        }
    }
    if(nbObj==0){
        QMessageBox::critical(this, "Erreur", "Vous devez placer au moins un objectif !");
        return;
    }
    if(nbObj!=nbCaisse){
        QMessageBox::critical(this, "Erreur", "Il doit y avoir autant de caisses que d'objectifs !");
        return;
    }

    //position Mario
    int posX = spinBoxX->value()-1;
    int posY = spinBoxY->value()-1;
    if(tab[posX][posY]==VIDE){
        pos.x=posX;
        pos.y=posY;
    }
    else{
        QMessageBox::critical(this, "Erreur", "Mario doit être placé sur une case vide !");
        return;
    }


    //enregistrement fichier
    QString nom = QInputDialog::getText(this, "Nom de niveau", "Entrez un nom de niveau");
    nom = "levels//"+nom+".lvl";

    ofstream f (nom.toStdString().c_str(), ios::out | ios::binary);

    if(!f.is_open())
        QMessageBox::critical(this, "Erreur", "Impossible d'enregistrer le niveau");
    else{
        f.write((char*)&tab,sizeof(int[H][W]));
        f.write((char*)&pos,sizeof(position));
        f.close();
    }

    this->close();
}

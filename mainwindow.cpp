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
    h=5;
    w=5;

    //resize(400,400);
    zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    QGridLayout *layoutGrille = new QGridLayout;
    QGroupBox *boxGrille = new QGroupBox("Position des objets");
    QGroupBox *boxMario = new QGroupBox("Position de Mario");


    groupbox = new QGroupBox**[h];
    vbox = new QVBoxLayout**[h];

    for(int k=0;k<4;k++)
        radioButton[k] = new QRadioButton**[h];


    for(int i=0;i<h;i++){

        groupbox[i]= new QGroupBox*[w];
        vbox[i] = new QVBoxLayout*[w];

        for(int k=0;k<4;k++)
            radioButton[k][i] = new QRadioButton*[w];

        for(int j=0;j<w;j++){
            groupbox[i][j]= new QGroupBox("Case "+QString::number(i+1)+","+QString::number(j+1));
            layoutGrille->addWidget(groupbox[i][j],i,j);

            radioButton[0][i][j] = new QRadioButton("Vide");
            radioButton[1][i][j] = new QRadioButton("Mur");
            radioButton[2][i][j] = new QRadioButton("Caisse");
            radioButton[3][i][j] = new QRadioButton("Objectif");
            radioButton[0][i][j]->setChecked(true);

            vbox[i][j] = new QVBoxLayout;
            vbox[i][j]->addWidget(radioButton[0][i][j]);
            vbox[i][j]->addWidget(radioButton[1][i][j]);
            vbox[i][j]->addWidget(radioButton[2][i][j]);
            vbox[i][j]->addWidget(radioButton[3][i][j]);

            groupbox[i][j]->setLayout(vbox[i][j]);
        }
    }
    boxGrille->setLayout(layoutGrille);

    QLabel *labelY = new QLabel("Ligne : ");
    QLabel *labelX = new QLabel("Colonne : ");
    spinBoxY = new QSpinBox;
    spinBoxX = new QSpinBox;
    spinBoxX->setRange(1,w);
    spinBoxY->setRange(1,h);
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

int MainWindow::type_obj(QRadioButton ***b[4],int a,int c){
    int i;

    if(b[1][a][c]->isChecked()==true)
        i=MUR;
    else if (b[2][a][c]->isChecked()==true)
        i=CAISSE;
    else if (b[3][a][c]->isChecked()==true)
        i=OBJECTIF;
    else
        i=VIDE;

    return i;
}

void MainWindow::createMap(){
    int **tab;
    tab = new int*[h];
    position pos;
    int nbCaisse=0;
    int nbObj=0;

    //creation carte
    for(int i=0;i<H;i++){
        tab[i] = new int[w];
        for(int j=0;j<W;j++){
            tab[i][j]=type_obj(radioButton,i,j);
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
        f.write((char*)&w,sizeof(int));
        f.write((char*)&h,sizeof(int));
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                f.write((char*)&tab[i][j],sizeof(int));
            }
        }
        f.write((char*)&pos,sizeof(position));
        f.close();
    }

    this->close();
}

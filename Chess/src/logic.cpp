#include "logic.h"
#include <QList>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QHash>
#include <QThread>
#include <QFileDialog>

struct Figure
{
    char col;
    int type;
    int x;
    int y;
    int rotat;
    bool state;
};


struct Logic::Impl{
    QList<Figure> figures;

    int findByPosition(int x, int y);
};

int Logic::Impl::findByPosition(int x, int y) {
    for (int i(0); i<figures.size(); ++i) {
        if (figures[i].x != x || figures[i].y != y ) {
            continue;
        }
        return i;
    }
    return -1;
}


Logic::Logic(QObject *parent)
    : QAbstractListModel(parent)
    , impl(new Impl()){
    countStep = -1;
    createNew();

}
Logic::~Logic() {

}
int Logic::boardSize() const {
    return BOARD_SIZE;
}

int Logic::rowCount(const QModelIndex & ) const {
    return impl->figures.size();
}

QHash<int, QByteArray> Logic::roleNames() const { 
    QHash<int, QByteArray> names;
    names.insert(Roles::Type      , "type");
    names.insert(Roles::PositionX , "positionX");
    names.insert(Roles::PositionY , "positionY");
    names.insert(Roles::Rotat , "rotat");
    return names;
}

void Logic::staps(Figure &figures, int x, int y){ // rules for figures
    int t;
    if(figures.type >= 10){
        figures.type == 10 ? t=5 : t =4;
    }else if(figures.type > 6){
        t = figures.type - 6;
    }else{
        t = figures.type;
    }

    switch (t) {
    case 0: // pawn
        if(figures.x != x ){
            if((y == figures.y+1 && (x == figures.x+1 || x == figures.x - 1))&& impl->findByPosition(x,y) >= 0){
                if(y == BOARD_SIZE-1){
                    figures.type = 5;
                }
                attak(figures,x,y);
            }
        }
        if(figures.y == 1 && y <= figures.y + 2 && y >= figures.y && impl->findByPosition(x,y) <= 0){
            figures.y = y;
        }else if(y <= figures.y + 1 && y >= figures.y && impl->findByPosition(x,y) <= 0){
            if(y == BOARD_SIZE-1){
                figures.type = 5;
            }
            figures.y = y;
        }break;
    case 1 : // rook
        if((x > figures.x || x < figures.x) && y == figures.y){
            if(figures.x > x){
                bool c = true;
                for(int j = figures.x-1;j>x;j--){
                    if(impl->findByPosition(j,y)>=0){
                        c = false;
                    }
                }
                if(c == true){
                    if(impl->findByPosition(x,y)>=0){
                        attak(figures,x,y);
                    }else{
                        figures.x = x;
                    }

                }
            }else if(figures.x < x){
                bool c = true;
                for(int j = figures.x+1;j<x;j++){
                    if(impl->findByPosition(j,y)>=0){
                        c = false;
                    }
                }
                if(c == true){
                    if(impl->findByPosition(x,y)>=0){
                        attak(figures,x,y);
                    }else{
                        figures.x = x;
                    }
                }
            }
        }else if((y > figures.y || y < figures.y)&& x == figures.x){
            if(figures.y > y){
                bool c = true;

                for(int j = figures.y-1;j>y;j--){
                    if(impl->findByPosition(x,j)>0){
                        c = false;
                    }
                }
                if(c == true){
                    if(impl->findByPosition(x,y)>=0){
                        attak(figures,x,y);
                    }else{
                        figures.y = y;
                    }

                }
            }else if(figures.y < y){
                bool c = true;

                for(int j = figures.y+1;j<y;j++){
                    if(impl->findByPosition(x,j)>0){
                        c = false;

                    }
                }
                if(c == true){
                    if(impl->findByPosition(x,y)>=0){
                        attak(figures,x,y);
                    }else{
                        figures.y = y;
                    }
                }
            }
        }break;
    case 2 : // knight
        if((x == figures.x+2 && ((y == figures.y+1)|| (y == figures.y-1))) || (x == figures.x-2 && ((y == figures.y+1)|| (y == figures.y-1)) )){
            if(impl->findByPosition(x,y)>=0){
                attak(figures,x,y);
            }else{
                figures.x = x;
                figures.y = y;
            }
        }else if ((y == figures.y+2 && (x == figures.x+1|| x == figures.x-1)) || (y == figures.y-2 && (x == figures.x+1|| x == figures.x-1) )){
            if(impl->findByPosition(x,y)>=0){
                attak(figures,x,y);
            }else{
                figures.x = x;
                figures.y = y;
            }
        }break;
    case 3 : // bishop
        if(pow(x - figures.x, 2) == pow(y - figures.y, 2)){
            if(x > figures.x ){
                bool c = true;
                if(y > figures.y){
                    for(int i = 1; i <y-figures.y; i++){
                        if(impl->findByPosition(figures.x+i,figures.y+i)>=0){
                            c = false;
                            break;
                        }
                    }
                    if(c == true){
                        if(impl->findByPosition(x,y)>=0){
                            attak(figures,x,y);
                        }else{
                            figures.x = x;
                            figures.y = y;
                        }
                    }
                }
                if(y < figures.y){
                    for(int i = 1; i <figures.y-y; i++){
                        if(impl->findByPosition(figures.x+i,figures.y-i)>=0){
                            c = false;
                            break;
                        }
                    }
                    if(c == true){
                        if(impl->findByPosition(x,y)>=0){
                            attak(figures,x,y);
                        }else{
                            figures.x = x;
                            figures.y = y;
                        }
                        figures.x = x;
                        figures.y = y;
                    }
                }

            }
            if(x < figures.x ){
                bool c = true;
                if(y > figures.y){
                    for(int i = 1; i <y-figures.y; i++){
                        if(impl->findByPosition(figures.x-i,figures.y+i)>=0){
                            c = false;
                            break;
                        }
                    }
                    if(c == true){
                        if(impl->findByPosition(x,y)>=0){
                            attak(figures,x,y);
                        }else{
                            figures.x = x;
                            figures.y = y;
                        }
                        figures.x = x;
                        figures.y = y;
                    }
                }
                if(y < figures.y){
                    for(int i = 1; i <figures.y-y; i++){
                        if(impl->findByPosition(figures.x-i,figures.y-i)>=0){
                            c = false;
                            break;
                        }
                    }
                    if(c == true){
                        if(impl->findByPosition(x,y)>=0){
                            attak(figures,x,y);
                        }else{
                            figures.x = x;
                            figures.y = y;
                        }
                        figures.x = x;
                        figures.y = y;
                    }
                }

            }

        }break;
    case 4 : // king
        if((x == figures.x || x == figures.x+1 || x == figures.x - 1) && (y == figures.y || y == figures.y+1 || y == figures.y-1) ){
            if(impl->findByPosition(x,y)>=0){
                attak(figures,x,y);
            }else{
                figures.x = x;
                figures.y = y;
            }
        }break;
    case 5 : // queen

        if((x > figures.x || x < figures.x) && y == figures.y){
            if(figures.x > x){
                bool c = true;
                for(int j = figures.x-1;j>x;j--){
                    if(impl->findByPosition(j,y)>=0){
                        c = false;
                    }
                }
                if(c == true){
                    if(impl->findByPosition(x,y)>=0){
                        attak(figures,x,y);
                    }else{
                        figures.x = x;
                    }

                }
            }else if(figures.x < x){
                bool c = true;
                for(int j = figures.x+1;j<x;j++){
                    if(impl->findByPosition(j,y)>=0){
                        c = false;
                    }
                }
                if(c == true){
                    if(impl->findByPosition(x,y)>=0){
                        attak(figures,x,y);
                    }else{
                        figures.x = x;
                    }
                }
            }
        }else if((y > figures.y || y < figures.y)&& x == figures.x){
            if(figures.y > y){
                bool c = true;

                for(int j = figures.y-1;j>y;j--){
                    if(impl->findByPosition(x,j)>0){
                        c = false;
                    }
                }
                if(c == true){
                    if(impl->findByPosition(x,y)>=0){
                        attak(figures,x,y);
                    }else{
                        figures.y = y;
                    }

                }
            }else if(figures.y < y){
                bool c = true;

                for(int j = figures.y+1;j<y;j++){
                    if(impl->findByPosition(x,j)>0){
                        c = false;

                    }
                }
                if(c == true){
                    if(impl->findByPosition(x,y)>=0){
                        attak(figures,x,y);
                    }else{
                        figures.y = y;
                    }
                }
            }
        }else if(pow(x - figures.x, 2) == pow(y - figures.y, 2)){
            if(x > figures.x ){
                bool c = true;
                if(y > figures.y){
                    for(int i = 1; i <y-figures.y; i++){
                        if(impl->findByPosition(figures.x+i,figures.y+i)>=0){
                            c = false;
                            break;
                        }
                    }
                    if(c == true){
                        if(impl->findByPosition(x,y)>=0){
                            attak(figures,x,y);
                        }else{
                            figures.x = x;
                            figures.y = y;
                        }
                    }
                }
                if(y < figures.y){
                    for(int i = 1; i <figures.y-y; i++){
                        if(impl->findByPosition(figures.x+i,figures.y-i)>=0){
                            c = false;
                            break;
                        }
                    }
                    if(c == true){
                        if(impl->findByPosition(x,y)>=0){
                            attak(figures,x,y);
                        }else{
                            figures.x = x;
                            figures.y = y;
                        }
                        figures.x = x;
                        figures.y = y;
                    }
                }

            }
            if(x < figures.x ){
                bool c = true;
                if(y > figures.y){
                    for(int i = 1; i <y-figures.y; i++){
                        if(impl->findByPosition(figures.x-i,figures.y+i)>=0){
                            c = false;
                            break;
                        }
                    }
                    if(c == true){
                        if(impl->findByPosition(x,y)>=0){
                            attak(figures,x,y);
                        }else{
                            figures.x = x;
                            figures.y = y;
                        }
                        figures.x = x;
                        figures.y = y;
                    }
                }
                if(y < figures.y){
                    for(int i = 1; i <figures.y-y; i++){
                        if(impl->findByPosition(figures.x-i,figures.y-i)>=0){
                            c = false;
                            break;
                        }
                    }
                    if(c == true){
                        if(impl->findByPosition(x,y)>=0){
                            attak(figures,x,y);
                        }else{
                            figures.x = x;
                            figures.y = y;
                        }
                        figures.x = x;
                        figures.y = y;
                    }
                }

            }
        }break;
    case 6: // pawn
        if(figures.x != x ){
            if((y == figures.y-1 && (x == figures.x+1 || x == figures.x - 1))&& impl->findByPosition(x,y) >= 0){
                if(y == 0){
                    figures.type = 11;
                }
                attak(figures,x,y);
            }break;
        }
        if(figures.y == BOARD_SIZE-2 && y >= figures.y - 2 && y <= figures.y && impl->findByPosition(x,y) <= 0){
            figures.y = y;
        }else if(y >= figures.y - 1 && y <= figures.y && impl->findByPosition(x,y) <= 0){
            if(y == 0){
                figures.type = 11;
            }
            figures.y = y;
        }break;
    default: break;
    }
}


void Logic::attak(Figure &figures, int x, int y){
    int temp = impl->findByPosition(x,y);
    if(figures.col == 'w'){
        if(b_y_couter > 4) {
            b_y_couter = 0;
            b_x_couter--;
        }
        impl->figures[temp].x = b_x_couter;
        impl->figures[temp].y = b_y_couter++;
        impl->figures[temp].state = false;
        logsList << QString::number(temp)+","+QString::number(impl->figures[temp].x)+","+QString::number(impl->figures[temp].y)+","+QString::number(impl->figures[temp].type);
    }else{
        if(w_y_couter < 3 ) {
            w_y_couter = 7;
            w_x_couter++;
        }
        impl->figures[temp].x = w_x_couter;
        impl->figures[temp].y = w_y_couter--;
        impl->figures[temp].state = false;
        logsList << QString::number(temp)+","+QString::number(impl->figures[temp].x)+","+QString::number(impl->figures[temp].y)+","+QString::number(impl->figures[temp].type);

    }
    QModelIndex topLeft = createIndex(temp, 0);
    QModelIndex bottomRight = createIndex(temp, 0);
    emit dataChanged(topLeft, bottomRight);
    figures.x = x;
    figures.y = y;
}

QVariant Logic::data(const QModelIndex & modelIndex, int role) const {
    if (!modelIndex.isValid()) {
        return QVariant();
    }

    int index = static_cast<int>(modelIndex.row());

    if (index >= impl->figures.size() || index < 0) {
        return QVariant();
    }

    Figure & figure = impl->figures[index];

    switch (role) {
    case Roles::Type     : return figure.type;
    case Roles::PositionX: return figure.x;
    case Roles::PositionY: return figure.y;
    case Roles::Rotat: return figure.rotat;
    }
    return QVariant();
}

void Logic::close() {

    beginResetModel();


    impl->figures.clear();
    endResetModel();
}

void Logic::createNew(){
    logsList.clear();
    for(int i(0),j(1); i<BOARD_SIZE;i++){ // initialization of white figures
        if(i<5){
            impl->figures << Figure {'w',j, i, 0, 0, 1};
            j++;
        }else{
            j = BOARD_SIZE - i;
            impl->figures << Figure {'w', j, i, 0, 0, 1 };
        }
        impl->figures << Figure { 'w', 0, i , 1, 0, 1 };
    }
    for(int i(0),j(7); i<BOARD_SIZE;i++){ // initialization of black figures
        if(i<5){
            impl->figures << Figure {'b',j,BOARD_SIZE - i - 1, 7, 0, 1};
            j++;
        }else{
            j = BOARD_SIZE - i +6;
            impl->figures << Figure {'b', j, BOARD_SIZE - i - 1, 7, 0, 1};
        }
        impl->figures << Figure {'b', 6, i , 6 , 0, 1};
    }

    rotate = 180;
    color_step = 'w';
    w_x_couter = 8;
    w_y_couter = 7;
    b_x_couter = -1;
    b_y_couter = 0;
    endResetModel();
}

bool Logic::move(int fromX, int fromY, int toX, int toY) {
    int index = impl->findByPosition(fromX, fromY);

    if(impl->figures[index].col != color_step){
        endResetModel();
        return 0;
    }
    if(impl->figures[index].state == true){
        int index2 =  impl->findByPosition(toX, toY);
        if (index < 0 || index == index2){
            endResetModel();
            return false;
        }

        if ((toX < 0 || toX >= BOARD_SIZE) || (toY < 0 || toY >= BOARD_SIZE)) {
            endResetModel();
            return false;
        }
        if((index2>=0 && impl->figures[index].col != impl->figures[index2].col) || index2 < 0){
            staps(impl->figures[index], toX, toY);

        }
        if(impl->figures[index].x == toX && impl->figures[index].y == toY){
            if(color_step == 'w'){
                color_step = 'b';
            }else{
                color_step = 'w';
            }
            for(int i(0);i < impl->figures.size();i++){
                impl->figures[i].rotat += 180;
                QModelIndex topLeft = createIndex(i, 0);
                QModelIndex bottomRight = createIndex(i, 0);
                emit dataChanged(topLeft, bottomRight);
                rotate =+180;

            }
            logsList << QString::number(index)+","
                        +QString::number(impl->figures[index].x)+","
                        +QString::number(impl->figures[index].y)+","
                        +QString::number(impl->figures[index].type);

            QModelIndex topLeft = createIndex(index, 0);
            QModelIndex bottomRight = createIndex(index, 0);
            emit dataChanged(topLeft, bottomRight);
            return true;
        }
        endResetModel();
        return false;
    }
    return false;
}

int Logic::rotat(){
    return rotate;
}

int Logic::saveGame(){
    QString fileName;
    fileName = QFileDialog::getSaveFileName(0,"Save your game","/chessLogs/game","(*.log)");
    QFile chessFile(fileName);
    if(chessFile.open( QIODevice::WriteOnly )){
        QTextStream textStream( &chessFile );
        textStream << logsList.join(';');
        chessFile.close();
    }
    return 1;
}
void Logic::loadGame(){
    QString file;
    file = QFileDialog::getOpenFileName(0,"Select a saved game","/chessLogs/game","(*.log)");

    if(file.length()==0){
        qDebug() << "file is not selected";
    }else{
        logsLoadList.clear();
        countStep = -1;
        close();
        QFile chessFile(file);
        if(chessFile.open(QIODevice::ReadOnly |QIODevice::Text)){
            while(!chessFile.atEnd()){
                //читаем строку
                QString logs = chessFile.readAll();
                logsLoadList = logs.split(";");
            }

        }else{
            qDebug()<< "don't open file";
        }
        for(int i(0),j(1); i<BOARD_SIZE;i++){
            if(i<5){
                impl->figures << Figure {'w',j, i, 0, 0, 1};
                j++;
            }else{
                j = BOARD_SIZE - i;
                impl->figures << Figure {'w', j, i, 0, 0, 1 };
            }
            impl->figures << Figure { 'w', 0, i , 1, 0, 1 };
        }
        for(int i(0),j(7); i<BOARD_SIZE;i++){
            if(i<5){
                impl->figures << Figure {'b',j,BOARD_SIZE - i - 1, 7, 0, 1};
                j++;
            }else{
                j = BOARD_SIZE - i +6;
                impl->figures << Figure {'b', j, BOARD_SIZE - i - 1, 7, 0, 1};
            }
            impl->figures << Figure {'b', 6, i , 6 , 0, 1};
        }
        endResetModel();
    }

}
void Logic::stepNext(){


    if(logsLoadList.empty() || countStep >= logsLoadList.size()-1){
    }else{
        QString str;
        QStringList list;
        countStep++;
        str =  logsLoadList.at(countStep);
        list = str.split(',');
        int index = 0, x = 0 , y = 0, type = 0;
        for(int j = 0; j < list.size();j++){
            switch (j) {
            case 0:  index = list.at(j).toInt();
                break;
            case 1:  x = list.at(j).toInt();
                list[j] =  QString::number(impl->figures[index].x);
                break;
            case 2:  y = list.at(j).toInt();
                list[j] =  QString::number(impl->figures[index].y);
                break;
            case 3:  type = list.at(j).toInt();
                list[j] =  QString::number(impl->figures[index].type);
                break;
            default:
                break;
            }
        }

        str = list.join(',');
        logsLoadList[countStep] = str;
        impl->figures[index].x = x;
        impl->figures[index].y = y;
        impl->figures[index].type = type;

        endResetModel();
    }



}
void Logic::stepPrew(){
    if(countStep < 0){
    }else{
        countStep--;
        QString str =  logsLoadList.at(countStep+1);
        QStringList list = str.split(',');
        int index = 0, x = 0 , y = 0, type = 0;

        for(int j = 0; j < list.size();j++){
            switch (j) {
            case 0:  index = list.at(j).toInt();

                break;
            case 1:  x = list.at(j).toInt();
                list[j] =  QString::number(impl->figures[index].x);

                break;
            case 2:  y = list.at(j).toInt();
                list[j] =  QString::number(impl->figures[index].y);
                break;
            case 3:  type = list.at(j).toInt();
                list[j] =  QString::number(impl->figures[index].type);
                break;
            default:
                break;
            }
        }

        str = list.join(',');
        logsLoadList[countStep+1] = str;
        impl->figures[index].x = x;
        impl->figures[index].y = y;
        impl->figures[index].type = type;
        endResetModel();

    }

}

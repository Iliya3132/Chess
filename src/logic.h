#pragma once
#include <memory>
#include <QAbstractListModel>
#include <QFile>
#include <QTextStream>
#include <QStringList>
struct Figure;
class Logic: public QAbstractListModel
{
    Q_OBJECT
public:

    enum GlobalConstants {

        BOARD_SIZE = 8
    };

    enum Roles {
        Type = Qt::UserRole,
        PositionX,
        PositionY,
        Rotat,
    };
    
public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    Q_PROPERTY(int boardSize READ boardSize CONSTANT)
    int boardSize() const;

    Q_INVOKABLE void close();
    Q_INVOKABLE void createNew();
    Q_INVOKABLE bool move(int fromX, int fromY, int toX, int toY);
    Q_INVOKABLE int rotat();
    Q_INVOKABLE int saveGame();
    Q_INVOKABLE void loadGame();
    Q_INVOKABLE void stepNext();
    Q_INVOKABLE void stepPrew();
protected:
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void staps(Figure &figures, int x, int y);
    void attak (Figure &figures, int x, int y);

private:    
    QStringList logsList;
    QStringList logsLoadList;
    struct Impl;
    int countStep;
    int rotate;
    char color_step;
    double w_x_couter;
    double w_y_couter;
    double b_x_couter;
    double b_y_couter;
    std::unique_ptr<Impl> impl;
};

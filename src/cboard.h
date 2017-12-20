#ifndef CBOARD_H
#define CBOARD_H
#include <memory>
#include <QAbstractListModel>

class CBoard
{
public:
    CBoard();
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleName() const override;
};

#endif // CBOARD_H

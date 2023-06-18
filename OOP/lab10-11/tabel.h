#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <QFont>
#include "offer.h"
#include <vector>
#include <qdebug.h>
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <QFont>
#include <vector>
#include <qdebug.h>

using std::vector;

class MyTableModel : public QAbstractTableModel {
private:
    vector<offer> oList;

public:
    MyTableModel(const std::vector<offer>& oList) :oList{ oList } {
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return oList.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
        if (role == Qt::DisplayRole) {
            offer Offer = oList[index.row()];
            if (index.column() == 0)
                return QString::number(Offer.getId());
            else if (index.column() == 1)
                return QString::fromStdString(Offer.getName());
            else if (index.column() == 2)
                return QString::fromStdString(Offer.getDest());
            else if (index.column() == 3)
                return QString::fromStdString(Offer.getType());
            else if (index.column() == 4)
                return QString::number(Offer.getPrice());
        }

        return QVariant();
    }

    void setOffers(const vector<offer> oList) {
        this->oList = oList;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomR);
        emit layoutChanged();
    }
};

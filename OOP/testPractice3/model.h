#include <QAbstractTableModel>
#include <vector>

#include "product.h"

using namespace std;


class MyTableModel : public QAbstractTableModel {
private:
    vector<Product> pList;
    vector<bool> filtered;

public:
    MyTableModel(vector<Product> pList, vector<bool> filtered) : pList{ pList }, filtered{ filtered } {
        
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return pList.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
        if (role == Qt::DisplayRole) {
            Product product = pList[index.row()];
            if (index.column() == 0)
                return QString::number(product.getId());
            else if (index.column() == 1)
                return QString::fromStdString(product.getName());
            else if (index.column() == 2)
                return QString::fromStdString(product.getType());
            else if (index.column() == 3)
                return QString::number(product.getPrice());
        }

        //color the rows where filtered is false to red
        if (role == Qt::BackgroundRole) {
			if (filtered[index.row()] == false)
				return QBrush(Qt::red);
		}

        return QVariant();
    }

    void setProducts(vector<Product> pList, vector<bool> filtered) {
        this->pList = pList;
        this->filtered = filtered;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomR);
        emit layoutChanged();
    }
};
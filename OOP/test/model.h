#include <QAbstractTableModel>
#include <qbrush.h>
#include <vector>

#include "student.h"

using namespace std;

class MyTableModel : public QAbstractTableModel {
private:
    vector<Student> sortedSList;

public:
    MyTableModel(vector<Student> sortedSList) : sortedSList{ sortedSList } {
        this->setHeaderData(0, Qt::Horizontal, "Nr Matricol");
        this->setHeaderData(1, Qt::Horizontal, "Nume");
        this->setHeaderData(2, Qt::Horizontal, "Varsta");
        this->setHeaderData(3, Qt::Horizontal, "Facultate");
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return sortedSList.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
        Student student = sortedSList[index.row()];
        if (role == Qt::DisplayRole) {
            if (index.column() == 0)
                return QString::number(student.getId());
            else if (index.column() == 1)
                return QString::fromStdString(student.getName());
            else if (index.column() == 2)
                return QString::number(student.getAge());
            else if (index.column() == 3)
                return QString::fromStdString(student.getFacultate());

        }
        if (role == Qt::BackgroundRole) {
            if (student.getFacultate() == "mate")
                return QBrush(Qt::red);

            if (student.getFacultate() == "mate-info")
                return QBrush(Qt::yellow);

            if (student.getFacultate() == "info")
                return QBrush(Qt::blue);

            if (student.getFacultate() == "ai")
                return QBrush(Qt::green);
        }

        return QVariant();
    }

    vector<Student> getStudents() {
		return sortedSList;
	}

    void setStudents(vector<Student> sortedSList) {
        this->sortedSList = sortedSList;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomR);
        emit layoutChanged();
    }
};
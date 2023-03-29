#pragma once

#include <QtGui>

class CCatalogList;
class CCatalog;

class CCatalogSelectionModel: public QAbstractTableModel
{
public:
	CCatalogSelectionModel(CCatalogList* data, QObject* parent);

	~CCatalogSelectionModel();

    void update();

    void clearSelection();

    void setSelection(const QStringList& catalogList);

    void setSelection(const QString& catalogName, bool select = true);

    QStringList getSelection(void) const;

    QList<CCatalog*> selectedList(void) const;

    bool isSelected(const QString& catalogName);

    QString indexToName(const QModelIndex& index) const;
    QModelIndex nameToIndex(const QString& catalogName, int col = 0) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override { return 1; }

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

protected:
    struct tCatalog
    {
        QString name;
        bool checked;
        tCatalog() : checked(false) {}
    };

    CCatalogList* m_data;
    QList<tCatalog*> m_rows;
};

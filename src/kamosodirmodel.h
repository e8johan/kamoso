/*************************************************************************************
 *  Copyright (C) 2012 by Aleix Pol <aleixpol@kde.org>                               *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/

#ifndef KAMOSODIRMODEL_H
#define KAMOSODIRMODEL_H

#include <KDirModel>
#include <KDirSortFilterProxyModel>

class KamosoDirModel : public KDirSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QStringList mimeFilter READ mimeFilter WRITE setMimeFilter NOTIFY filterChanged)
    Q_PROPERTY(QString nameFilter READ nameFilter WRITE setNameFilter)
    public:
        enum Roles {
            Path = KDirModel::ColumnCount+1,
            MimeType
        };

        explicit KamosoDirModel(QObject* parent = 0);
        void setUrl(const QUrl& url);
        QUrl url() const;

        QString nameFilter() const;
        void setNameFilter(const QString& filter);

        void setMimeFilter(const QStringList& mimes);
        QStringList mimeFilter() const;

        QHash<int, QByteArray> roleNames() const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Q_SIGNALS:
        void urlChanged();
        void filterChanged();

    private:
        KDirModel* m_dirModel;
};

#endif // KAMOSODIRMODEL_H

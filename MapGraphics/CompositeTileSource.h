#ifndef COMPOSITETILESOURCE_H
#define COMPOSITETILESOURCE_H

#include "MapTileSource.h"
#include "MapGraphics_global.h"

#include <QList>
#include <QHash>
#include <QMap>
#include <QSharedPointer>
#include <QMutex>

class MAPGRAPHICSSHARED_EXPORT CompositeTileSource : public MapTileSource
{
    Q_OBJECT
public:
    explicit CompositeTileSource(QObject *parent = 0);
    virtual ~CompositeTileSource();

    //pure-virtual from MapTileSource
    virtual QPointF ll2qgs(const QPointF& ll, quint8 zoomLevel) const;

    //pure-virtual from MapTileSource
    virtual QPointF qgs2ll(const QPointF& qgs, quint8 zoomLevel) const;

    //pure-virtual from MapTileSource
    virtual quint64 tilesOnZoomLevel(quint8 zoomLevel) const;

    //pure-virtual from MapTileSource
    virtual quint16 tileSize() const;

    //pure-virtual from MapTileSource
    virtual quint8 minZoomLevel(QPointF ll);

    //pure-virtual from MapTileSource
    virtual quint8 maxZoomLevel(QPointF ll);

    //pure-virtual from MapTileSource
    virtual QString name() const;

    //pure-virtual from MapTileSource
    virtual QString tileFileExtension() const;


    void addSourceTop(QSharedPointer<MapTileSource>, qreal opacity = 1.0);
    void addSourceBottom(QSharedPointer<MapTileSource>, qreal opacity = 1.0);
    int numSources() const;
    QSharedPointer<MapTileSource> getSource(int index) const;


protected:
    virtual void fetchTile(quint32 x,
                           quint32 y,
                           quint8 z);
    
signals:
    /*!
     \brief Emitted when anything changes about the layers. One is added/deleted, moved, transparency is changed, etc.

    */
    void sourcesChanged();
    
public slots:

private slots:
    void handleTileRetrieved(quint32 x, quint32 y, quint8 z);

private:
    QMutex * _globalMutex;
    QList<QSharedPointer<MapTileSource> > _childSources;
    QList<qreal> _childOpacities;

    QHash<QString, QMap<quint32, QImage *> * > _pendingTiles;
    
};

#endif // COMPOSITETILESOURCE_H

/*
 * objectselectiontool.h
 * Copyright 2010, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OBJECTROTATIONTOOL_H
#define OBJECTROTATIONTOOL_H

#include "abstractobjecttool.h"

#include <QSet>

namespace Tiled {
namespace Internal {

class MapObjectItem;
class RotationRectangle;

class ObjectRotationTool : public AbstractObjectTool
{
    Q_OBJECT

public:
    explicit ObjectRotationTool(QObject *parent = 0, bool ccw = false);
    ~ObjectRotationTool();

    void mousePressed(QGraphicsSceneMouseEvent *event);

    void mouseEntered();
    void mouseReleased(QGraphicsSceneMouseEvent *event);

    void languageChanged();

private:
    bool rotateCCW;

};

} // namespace Internal
} // namespace Tiled

#endif // OBJECTROTATIONTOOL_H

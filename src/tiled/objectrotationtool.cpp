/*
 * objectrotationtool.cpp
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

#include "objectrotationtool.h"

#include "layer.h"
#include "map.h"
#include "mapdocument.h"
#include "mapobject.h"
#include "mapobjectitem.h"
#include "maprenderer.h"
#include "mapscene.h"
#include "rotatemapobject.h"
#include "objectgroup.h"
#include "preferences.h"

#include <QApplication>
#include <QGraphicsItem>
#include <QUndoStack>

using namespace Tiled;
using namespace Tiled::Internal;

ObjectRotationTool::ObjectRotationTool(QObject *parent, bool ccw)
    : AbstractObjectTool(tr(ccw ? "Rotate CCW" : "Rotate CW"),
          QIcon(QLatin1String(ccw ? ":images/22x22/tool-rotate-ccw.png": ":images/22x22/tool-rotate-cw.png")),
          QKeySequence(tr(ccw ? "<" : ">")),
          parent)
    , rotateCCW(ccw)
{
}

ObjectRotationTool::~ObjectRotationTool()
{
}

void ObjectRotationTool::mousePressed(QGraphicsSceneMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:

        foreach (QGraphicsItem *item, mapScene()->items(event->scenePos())) {
            MapObjectItem *objectItem = dynamic_cast<MapObjectItem*>(item);
            if (!objectItem) continue;
            objectItem->setTransformOriginPoint(QPointF(16.0,-16.0));
            const int oldRotation = objectItem->rotation();
            int newRotation = oldRotation + (rotateCCW ? -90 : 90);
            while (newRotation > 360) newRotation -= 360;
            while (newRotation < 0) newRotation += 360;
            objectItem->setRotation(newRotation);

            QUndoStack *undoStack = mapDocument()->undoStack();
            undoStack->beginMacro(tr("Rotating", ""));

            MapObject *object = objectItem->mapObject();
            object->setRotation(newRotation);
            undoStack->push(new RotateMapObject(mapDocument(), object, oldRotation));

            undoStack->endMacro();

            printf("Found item and setRotation = %d\n", newRotation);
        }
        break;
    default:
        AbstractObjectTool::mousePressed(event);
        break;
    }
}

void ObjectRotationTool::languageChanged()
{
    setName(tr("Rotate CCW"));
    setShortcut(QKeySequence(tr("S")));
}

void ObjectRotationTool::mouseEntered()
{
}

void ObjectRotationTool::mouseReleased(QGraphicsSceneMouseEvent *event)
{
}

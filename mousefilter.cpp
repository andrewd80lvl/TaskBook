#include "mousefilter.h"

#include <QtWidgets>
#include <QDebug>
#include <QListView>
#include <QDateTime>

#include "MouseFilter.h"


// ----------------------------------------------------------------------
MouseFilter::MouseFilter(QObject* pobj/*= 0*/)
    : QObject(pobj)
{
 x = 0; y = 0;


}

// ----------------------------------------------------------------------

/*virtual*/bool MouseFilter::eventFilter(QObject* pobj, QEvent* pe)
{

    if (pe->type() == QEvent::MouseButtonPress) {

        QMouseEvent *event = static_cast<QMouseEvent*>(pe);

        if (event->button() == Qt::LeftButton) {

            qDebug() << "Press: " << " x:" << event->screenPos().x() << ",y:" << event->screenPos().y();

            x = event->screenPos().x();
            y = event->screenPos().y();

            xb = event->x();
            yb = event->y();

            sec_from_press = QDateTime::currentMSecsSinceEpoch();

            emit sign_press(xb,yb);

            return true;
        }
    }

    if (pe->type() == QEvent::MouseButtonRelease) {

            QMouseEvent *event = static_cast<QMouseEvent*>(pe);

            if (event->button() == Qt::LeftButton) {


                qDebug() << "Release: " << " x:" << event->screenPos().x() << ",y:" << event->screenPos().y();

                emit sign_realese(event->x(),event->y());

                int offset_x = abs(event->screenPos().x() - x);
                int offset_y = abs(event->screenPos().y() - y);

                if(abs(offset_x - offset_y) < SING_TOUCH_OFFSET)
                {
                    if(QDateTime::currentMSecsSinceEpoch() - sec_from_press > LONG_TOUCH_OFFSET_MSEC)
                        emit sign_long_touch(xb ,yb);
                    else
                        emit sign_touch(xb ,yb);
                }
                else if(offset_x > offset_y)
                {

                    if(x > event->screenPos().x()){
                        qDebug() << "sign_left" ;
                        emit sign_left(xb ,yb);
                    }
                    else{
                        qDebug() << "sign_right";
                        emit sign_right(xb ,yb);
                    }

                }else{

                    if(x > event->screenPos().x())
                        emit sign_top (xb ,yb);
                    else
                        emit sign_bottom(xb ,yb);
                }


                return true;
            }
        }

        return false;
}

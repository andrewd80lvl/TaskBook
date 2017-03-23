#ifndef MOUSEFILTER_H
#define MOUSEFILTER_H

#include <QObject>

#define SING_TOUCH_OFFSET 50
#define LONG_TOUCH_OFFSET_MSEC 750

// ======================================================================
class MouseFilter : public QObject {

    Q_OBJECT

public:
    MouseFilter(QObject* pobj = 0);

protected:

    int x;
    int y;

    int xb;
    int yb;


    virtual bool eventFilter(QObject*, QEvent*);

    qint64 sec_from_press;

signals:
    void sign_press(int x,int y);
    void sign_realese(int x,int y);

    void sign_left(int x, int y);
    void sign_right(int x, int y);

    void sign_top(int x, int y);
    void sign_bottom(int x, int y);

    void sign_touch(int x ,int y);
    void sign_long_touch(int x ,int y);


};

#endif

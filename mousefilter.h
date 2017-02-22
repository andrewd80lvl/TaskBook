#ifndef MOUSEFILTER_H
#define MOUSEFILTER_H

#include <QObject>

#define sign_OFFSET 50

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

signals:
    void touch_press(int x,int y);
    void touch_realese(int x,int y);

    void sign_left(int x, int y);
    void sign_right(int x, int y);

    void sign_top(int x, int y);
    void sign_bottom(int x, int y);

    void sign_touch(int x ,int y);


};

#endif

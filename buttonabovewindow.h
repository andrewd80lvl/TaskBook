#ifndef BUTTONABOVEWINDOW_H
#define BUTTONABOVEWINDOW_H

#include <QWidget>
#include <QLabel>



class ButtonAboveWindow  : public QLabel  {
    Q_OBJECT

public:
    ButtonAboveWindow(QWidget* parent = 0);
    ~ButtonAboveWindow();

    void showToast( const QString& message, const char* const styleClass );


public slots:
    void resizeMainWindow( );

protected:
   void paintEvent(QPaintEvent *pe);

private:

    QWidget * m_parent;
    QPixmap pixmap;
};






#endif // BUTTONABOVEWINDOW_H

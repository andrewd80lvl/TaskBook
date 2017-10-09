#include "buttonabovewindow.h"

#include <QLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QScrollBar>
#include <QPainter>



#include <QDebug>

static const char* const LABEL_STYLESHEET =
      "QLabel {"
    "  font-weight: bold;"
    "  border: 2px solid orange;"
    "background-position: center;    "
//    "  background-image: url(:/images/icons/plus.png); "
//    "  background-image: url(:/images/icons/add-doc_black.png); "
    "  border-radius: 100px;"
    "}"
    "[class=Info] {"
    "  background-color: rgba(255, 255, 153, 200);"
    "  border-color: orange;"
    "}"
    "[class=Ok] {"
    "  background-image: url(:/images/icons/add-doc_black.png); "
    "  background-color: rgba(204, 255, 153, 200);"
    "  border-color: green;"
    "}"
    "[class=Error] {"
    "  background-color: rgba(255, 153, 153, 200);"
    "  border-color: red;"
    "}"
    "[class=Wait] {"
    "  background-color: rgba(224, 224, 224, 200);"
    "  border-color: gray;"
    "}";



ButtonAboveWindow::ButtonAboveWindow(QWidget *parent) : QLabel( parent ) {

   m_parent = parent;


    setAlignment( Qt::AlignCenter );
    setProperty( "class", "Info" );
    setStyleSheet( LABEL_STYLESHEET );

    setGeometry(QRect(0,0,200,200));
    setScaledContents(true );


  //  pixmap.load(":/images/icons/plus.png");
      pixmap.load(":/images/icons/add-doc_black.png");

    raise();

}

ButtonAboveWindow::~ButtonAboveWindow()
{

}

void ButtonAboveWindow::resizeMainWindow() {


    int x = ( m_parent->width() - width()*1.2 ) ;
    int y = ( m_parent->height() - height()*1.2 ) ;

    qDebug() << " m_parent->width():" << m_parent->width();

    move( x, y );
    //m_label->repaint();

}

void ButtonAboveWindow::paintEvent(QPaintEvent *pe)
{

    qDebug() << "paintEvent!!!";
    QPainter paint(this);

    int widWidth = this->width();
    int widHeight = this->height();

    pixmap = pixmap.scaled(widWidth-100, widHeight-100, Qt::KeepAspectRatioByExpanding);


    QPoint centerOfLabel = rect().center();
    QRect  rectOfPixmap =  pixmap.rect();
    rectOfPixmap.moveCenter(centerOfLabel);
    paint.drawPixmap(rectOfPixmap.topLeft(),pixmap);

    QWidget::paintEvent(pe);

}

void ButtonAboveWindow::showToast( const QString& message, const char* const styleClass ) {

    setText( message );
    setProperty( "class", styleClass );
    style()->unpolish( this );
    style()->polish( this );
    update();
    adjustSize();
    show();

    resizeEvent( NULL );

}

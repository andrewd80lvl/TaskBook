#ifndef NEW_EDIT_FORM_H
#define NEW_EDIT_FORM_H

#include <QWidget>
#include <QDate>

namespace Ui {
class new_edit_form;
}

class newEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit newEditForm(QWidget *parent = 0);
    ~newEditForm();

    void setData(QString task);

    QString getData();
private:
    Ui::new_edit_form *ui;
};

#endif // NEW_EDIT_FORM_H

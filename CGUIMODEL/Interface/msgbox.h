#ifndef MSGBOX_H
#define MSGBOX_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>

class CMsgBox : public QDialog
{
    Q_OBJECT

public:
    explicit CMsgBox(QWidget *parent = 0);
    ~CMsgBox();
public:
    void translateLanguage();
    void setInfo(QString title_info, QString info, QPixmap pixmap, bool is_check_hidden, bool is_ok_hidden);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent( QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent( QMouseEvent *);
signals:
    void msgChecked(bool,bool);
    void okMessageHidden(bool);
public slots:
    void okOperate();
    void cancelOperate();
private:
    bool mouse_press;
    QPushButton *close_button;
    QPushButton *ok_button;
    QPushButton *cancel_button;
    QLabel *title_label;
    QLabel *msg_label;
    QLabel * ask_label;
    QCheckBox *check_box;
    QString ok_text;
    QString cancel_text;
    QPoint move_point;
};

#endif // MSGBOX_H

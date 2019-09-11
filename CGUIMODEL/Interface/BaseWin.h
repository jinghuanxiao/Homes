#ifndef BASEWIN_H
#define BASEWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QBitmap>
#include <QTextEdit>
#include "basetopBar.h"

class CBaseWidget : public QWidget
{
    Q_OBJECT

public:
    CBaseWidget(QWidget *parent = 0);
    ~CBaseWidget();

private slots:
    void closeWin();
    void minWin();
    void maxWin();

protected:
    QWidget* m_winContent;
    CBaseTopBar *m_topBar;
private:
    void initFrameless();
    virtual void initGUI();
};

#endif // BASEWIN_H

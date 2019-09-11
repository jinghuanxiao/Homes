#include "msgbox.h"

CMsgBox::CMsgBox(QWidget *parent)
 : QDialog(parent)
{
  this->resize(240, 160);
  this->setAttribute(Qt::WA_TranslucentBackground);

  //获取主界面的宽度
  int width = this->width();
  int height = this->height();

  //初始化为未按下鼠标左键
  mouse_press = false;

  //设置标题栏隐藏
  this->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog|Qt::WindowStaysOnTopHint);

  close_button = new QPushButton(this);
  close_button->setGeometry(width-30, 0, 27, 24);
  close_button->setIcon(QPixmap(":/w_close.png"));
  close_button->setIconSize(QSize(27,24));
  close_button->setStyleSheet("background:transparent;");

  //设置标题
  title_label = new QLabel(this);
  title_label->setObjectName(QString::fromUtf8("labelOne"));
  QFont font = title_label->font();
  font.setBold(true);
  title_label->setFont(font);
  title_label->setGeometry(0, 0, width-50, 30);
  title_label ->setStyleSheet("QLabel{font-size:14px;color: #d5ffff;}");

  //设置提示图片
  msg_label = new QLabel(this);
  msg_label->setGeometry(20, 50, 36, 36);
  msg_label->setScaledContents(true);

  //设置提示信息，让QLabel能够自动判断并换行显示：
  ask_label = new QLabel(this);
  ask_label->setGeometry(65, 60, width-100, 25*2);
  ask_label->setWordWrap(true);
  ask_label->setAlignment(Qt::AlignTop);
  ask_label->setStyleSheet("QLabel{font-size:13px;color: #d5ffff;}");

  check_box = new QCheckBox(this);
  check_box->setGeometry(10, height - 35, 160, 25);
  check_box->setHidden(true);

  cancel_button = new QPushButton(this);
  cancel_button->resize(70, 25);
  cancel_button->move(width - cancel_button->width() - 10, height - 35);

  ok_button = new QPushButton(this);
  ok_button->resize(70, 25);
  ok_button->move(width - ok_button->width() - cancel_button->width() - 20, height - 35);

  check_box->setStyleSheet("background:transparent;");

  ok_button->setObjectName(QString::fromUtf8("pushButtonTwo"));
  cancel_button->setObjectName(QString::fromUtf8("pushButtonTwo"));

  QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(okOperate()));
  QObject::connect(close_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));
  QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));

  this->translateLanguage();
}
CMsgBox::~CMsgBox()
{

}
void CMsgBox::translateLanguage()
{
  check_box->setText(tr("remember"));
  ok_text =QString::fromLocal8Bit("确定");
  cancel_text =QString::fromLocal8Bit("取消");
}

void CMsgBox::setInfo(QString title_info, QString info, QPixmap pixmap, bool is_check_hidden, bool is_ok_hidden)
{
  title_label->setText(QString("  ") + title_info);

  //设置提示信息
  ask_label->setText(info);
  msg_label->setPixmap(pixmap);

  //是否隐藏复选框
  check_box->setChecked(false);
  check_box->setHidden(is_check_hidden);

  //是否隐藏确定按钮
  ok_button->setHidden(is_ok_hidden);
  if(is_ok_hidden)
  {
    cancel_button->setText(ok_text);
  }
  else
  {
    ok_button->setText(ok_text);
    cancel_button->setText(cancel_text);
  }

}

void CMsgBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setBrush(QBrush(QColor(41, 77, 110)));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, 15, 15);
    QWidget::paintEvent(event);
}

void CMsgBox::mousePressEvent( QMouseEvent * event )
{
  //只能是鼠标左键移动和改变大小
  if(event->button() == Qt::LeftButton)
  {
    mouse_press = true;
  }

  //窗口移动距离
  move_point = event->globalPos() - pos();
}

void CMsgBox::mouseReleaseEvent( QMouseEvent *)
{
  mouse_press = false;
}

void CMsgBox::mouseMoveEvent(QMouseEvent *event)
{
  //移动窗口
  if(mouse_press)
  {
    QPoint move_pos = event->globalPos();
    move(move_pos - move_point);
  }
}

void CMsgBox::okOperate()
{
      bool is_hidden = check_box->isHidden();
      if(!is_hidden)
      {
        bool is_checked = check_box->isChecked();
        emit msgChecked(is_checked, true);
      }
      this->accept();
}

void CMsgBox::cancelOperate()
{
      bool is_check_hidden = check_box->isHidden();
      bool is_ok_hidden = ok_button->isHidden();
      if(!is_check_hidden)
      {
        bool is_checked = check_box->isChecked();
        if(!is_ok_hidden)
        {
          emit msgChecked(is_checked, false);
        }
           else
           {
             emit okMessageHidden(is_checked);
           }
      }

      this->reject();
}

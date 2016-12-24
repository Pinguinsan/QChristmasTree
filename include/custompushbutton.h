#ifndef QCHRISTMASTREE_CUSTOMPUSHBUTTON_H
#define QCHRISTMASTREE_CUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>


class CustomPushButton : public QPushButton
{

    Q_OBJECT
public:
    CustomPushButton(QWidget *parent = nullptr) :
        QPushButton{parent},
        m_number{0},
        m_state{false}
    {

    }

    void setNumber(int number)
    {
        this->m_number = number;
    }

    void setState(bool state)
    {
        this->m_state = state;
    }

    void flipState()
    {
        this->m_state = !this->m_state;
    }

    bool state() const
    {
        return this->m_state;
    }

    int number() const
    {
        return this->m_number;
    }

    void setCustomChecked(bool checked)
    {
        /*
        if (checked) {
            this->setStyleSheet(CustomPushButton::CHECKED_STYLESHEET);
        } else {
            this->setStyleSheet(CustomPushButton::UNCHECKED_STYLESHEET);
        }
        */
        this->setChecked(checked);
        this->setFlat(checked);
        //return QPushButton::setChecked(checked);
    }


signals:
    void leftClicked(CustomPushButton *cpb);
    void rightClicked(CustomPushButton *cpb);
    void leftClickReleased(CustomPushButton *cpb);
    void longLeftClickReleased(CustomPushButton *cpb);
    void rightClickReleased(CustomPushButton *cpb);

private slots:
    void mousePressEvent(QMouseEvent *mouseEvent)
    {
        if (mouseEvent->button() == Qt::MouseButton::LeftButton) {
            if (this->rect().contains(mouseEvent->pos())) {
                emit(leftClicked(this));
            }
        } else if (mouseEvent->button() == Qt::MouseButton::RightButton) {
            if (this->rect().contains(mouseEvent->pos())) {
                emit(rightClicked(this));
            }
        }
    }

    void mouseReleaseEvent(QMouseEvent *mouseEvent)
    {
        if (mouseEvent->button() == Qt::MouseButton::LeftButton) {
            if (this->rect().contains(mouseEvent->pos())) {
                emit(leftClickReleased(this));
            }
        } else if (mouseEvent->button() == Qt::MouseButton::RightButton) {
            if (this->rect().contains(mouseEvent->pos())) {
                emit(rightClickReleased(this));
            }
        }
    }

private:
    int m_number;
    bool m_state;

    const char * const CHECKED_STYLESHEET{"background-color: rgb(0,255,0); border: 2px solid #8f8f91;"};
    const char * const UNCHECKED_STYLESHEET{""};
};

#endif //QCHRISTMASTREE_CUSTOMPUSHBUTTON_H
